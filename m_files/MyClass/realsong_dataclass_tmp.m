classdef realsong_dataclass_tmp < handle
% RealSong Data class.
% define rsd=realsong_dataclass(filename);
% 
% ex)
% rsd=realsong_dataclass('your_realsong_data_here.mat');
% rsd.vm;          % voltage input
% rsd.mic;         % mic input
% rsd.speaker;     % speaker output
% rsd.ttl          % TTL pulse output
% % if no data in the above entry, it will return empty.
% 
% % to calculate spectrum and its feature, type
% rsd.calc_spectrum_features;
% rsd.spect.m_spec_deriv; % returns spectrum derivative.
% 
% % you can also replace NAN data with zeros.
% rsd.replace_nan_with_zero
%
% usage2)
% rsd=realsong_dataclass('your_realsong_data_here.mat',index);
% it can return the data within the index. 
% 
% by KH 20120808

    properties (SetAccess = private)
        vm
        mic
        speaker
        ttl
        amplitude
        entropy
        frequency
        FM
        pitch
        pitchgoodness
        precisepitch
        MainSylGate
        Predictor
        ImOut
        t
        t_feat
        pm
        Fs
        filename
        spect
        SpectCorr
        mainsyl_detect
        FF
        TriggerButton
        StimFamilyTriggerButton
    end
    
    
    
    properties (Dependent)
        TotalSize
    end
    
    
    methods
        function obj = realsong_dataclass_tmp(filename,index)
            
                      
            if nargin==0
                [filename,pathname]=uigetfile();
                filename=fullfile(pathname,filename);
            end
            

            load(filename);
            [dataN,channelN] = size(cbdata);
            
            if nargin>=2
%                 index = index;
            else
                index = 1:dataN;
            end
                
               
            obj.filename=filename;
          	obj.t=cbdata(index,1);
            obj.pm = pm;
            obj.Fs = pm.SampRate/pm.decimation;
            
            name_conversion_matrix = ...
                {'MICGain',             'mic'; ...
                'SpeakerOutputGain',    'speaker';...
                'SpeakerOutputREC',     'speaker';...
                'PulseStimOutputGain',  'ttl';...
                'Electrode1Gain',       'vm';...
                'Multitaper_Feature/multitaper_feature_RTSAC/p1', 'amplitude';...
                'BoutOnCntGain',        'BoutOnCnt'};
            
            %---- sort out parameters ----%
            
            pm.AI_Channel_Names=[pm.rec_rawsignal_datanames(:)', pm.rec_feature_datanames];
            S=strrep(pm.AI_Channel_Names,'RealSongControl/', '');
            AI_Names=regexprep(S,{name_conversion_matrix{:,1}},{name_conversion_matrix{:,2}});
            
                       
              
            % find mic data.
            mic_index=find(strncmpi(AI_Names,'mic',3));
            if isempty(mic_index)
                obj.mic     = [];
            else
                obj.mic     = cbdata(index,mic_index+1);
            end
            
            % find v data. downsample.
            vm_index=find(strncmpi(AI_Names,'vm',2));
            if isempty(vm_index)
                obj.vm =[];
            else
                obj.vm = cbdata(index,vm_index+1)*100;
            end
            
            
            % find stim data. downsample.
            ttl_index=find(strncmpi(AI_Names,'ttl',3));
            if isempty(ttl_index)
                obj.ttl=[];
            else
                obj.ttl=cbdata(index,ttl_index+1);
            end
            
              % find speaker data. .
            speaker_index=find(strncmpi(AI_Names,'speaker',7));
            if isempty(speaker_index)
                obj.speaker=[];
            else
                obj.speaker=cbdata(index,speaker_index+1);
            end
            
            % If there are Feature data 
            if isfield(pm,'feat')
                cbdataTMP=cbdata(index,pm.n_rec_channel+1);
                init_index=find(cbdataTMP==pm.initvec_val);
                
                for ii=1:size(pm.features_vec_names,1);
                    name=pm.features_vec_names{ii,1};
                    indp=init_index+pm.feat.([name '_index']);
                    if indp(end)>length(cbdataTMP)
                        indp=indp(1:end-1);
                        obj.(name)=cbdataTMP(indp);
                        obj.(name)=[obj.(name);NaN];
                    else
                        obj.(name)=cbdataTMP(indp);
                    end
                end
                obj.t_feat=cbdata(init_index,1);
            end
                
            
        end
    end
    
    
    %-----------------------------------------------------
    methods
        
        function calc_spectrum_features(obj,arg1)
            [obj.spect.m_spec_deriv ,...
                obj.spect.m_AM, ...
                obj.spect.m_FM ,...
                obj.spect.m_Entropy , ...
                obj.spect.m_amplitude ,...
                obj.spect.m_frequency, ...
                obj.spect.m_PitchGoodness, ...
                obj.spect.m_Pitch , ...
                obj.spect.m_Pitch_chose ,...
                obj.spect.m_Pitch_weight,...
                obj.spect.f,...
                obj.spect.t,...
                obj.spect.param]=sam_spectrum_deriv7(obj.mic,obj.Fs,'Parameters_high_resol_adaptive_steps',obj.Fs);
            % spectrum time is aligned to the end of window.
            obj.spect.t= obj.spect.t-obj.spect.t(1)+obj.spect.param.window/obj.spect.param.fs;
        end
        
        function replace_offline_features(obj)
            [obj.spect.m_spec_deriv ,...
                obj.spect.m_AM, ...
                obj.FM ,...
                obj.entropy , ...
                obj.amplitude ,...
                obj.frequency, ...
                obj.pitchgoodness, ...
                obj.pitch , ...
                obj.spect.m_Pitch_chose ,...
                obj.spect.m_Pitch_weight,...
                obj.spect.f,...
                obj.spect.t,...
                obj.spect.param]=sam_spectrum_deriv8(obj.mic,obj.Fs,'Parameters_high_resol_adaptive_steps',obj.Fs);
            % spectrum time is aligned to the end of window.
            obj.t_feat= obj.spect.t-obj.spect.t(1)+obj.spect.param.window/obj.spect.param.fs;
        end
        
        
        function replace_nan_with_zero(obj,arg1)
            names={'mic','vm','ttl','speaker'};
            for nn=1:length(names)
                obj.(names{nn})(isnan(obj.(names{nn})))=0;
            end
        end
        
         function delete_nan_from_data(obj,arg1)
            names={'t','mic','vm','ttl','speaker'};
            for nn=1:length(names)
                obj.(names{nn})=obj.(names{nn})(~isnan(obj.(names{nn})));
            end
         end
         
       
    end
    
end