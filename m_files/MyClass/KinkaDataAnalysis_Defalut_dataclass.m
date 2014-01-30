classdef KinkaDataAnalysis_Defalut_dataclass < handle
    % KinkaDataAnalysis Data class.
    % analysis=KinkaDataAnalysis_Default_dataclass(filename);
    %
    %
    % ex)
    % analysis  --gpm   (global parameters)
    %           --data  (data structure)
    %           --pmR   (parameter set from the first trial)
    %           --pmRAll(parameter set from all the trial)
    %
    
    %
    % by KH 20121111
    
    properties 
        gpm
        data
        pmR
        pmRAll
        
    end
    
    properties (Dependent)
      
    end
    
    
    methods
        function obj = KinkaDataAnalysis_Defalut_dataclass(filename)
            
            obj.init;
    
        end
        
        function obj=init(obj)
            obj.gpm.spk_threshold= [];
            obj.gpm.refractoriness_time = 0.001; % [sec]
            obj.gpm.v_names={'v1','v2','v3','v4'};
            obj.gpm.spk_names={'spk1','spk2','spk3','spk4'};
            obj.gpm.curr_trial = 1;
            obj.gpm.SongConds= {'BOS',...
                'REV',...
                'SL',...
                'CON',...
                'BOS2',...
                'BOS3',...
                'HET',...
                'BOS4',...
                'BOS5'};
            obj.gpm.channel_name={'E5','E6','E7','E8','E1','E2','E3','E4'}; % defined in MSAccess.
            obj.gpm.current_name={'IA5','IA6','IA7','IA8','IA1','IA2','IA3','IA4'}; % defined in MSAccess.
            obj.gpm.spike_analysis_bool=[];
            
            obj.gpm.data_type = '';
            
            obj.data.v          =[];
            obj.data.spk        =[];
            obj.data.syn_event  =[];
            obj.data.songID     =[];
            obj.data.T          =[];
            obj.data.rate       =[];
            obj.data.song       =[];
            obj.data.song_t     =[];
            obj.data.sonogram_f     =[];
            obj.data.sonogram_p     =[];
            obj.data.sonogram_t     =[];
            obj.data.medv           =[];
            obj.data.synevent_timing=[];
            obj.data.synevent_extremalVal=[];
            obj.data.synevent_DextremalVal=[];
            obj.data.stats=[];
            
        end
        
       
    end

    
end