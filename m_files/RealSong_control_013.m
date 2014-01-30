function varargout = RealSong_control_013(varargin)
% REALSONG_CONTROL_013 MATLAB code for RealSong_control_013.fig
%      REALSONG_CONTROL_013, by itself, creates a new REALSONG_CONTROL_013 or raises the existing
%      singleton*.
%
%      H = REALSONG_CONTROL_013 returns the handle to a new REALSONG_CONTROL_013 or the handle to
%      the existing singleton*.
%
%      REALSONG_CONTROL_013('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in REALSONG_CONTROL_013.M with the given input arguments.
%
%      REALSONG_CONTROL_013('Property','Value',...) creates a new REALSONG_CONTROL_013 or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before RealSong_control_013_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to RealSong_control_013_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help RealSong_control_013

% Last Modified by GUIDE v2.5 19-Apr-2013 15:01:34

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
    'gui_Singleton',  gui_Singleton, ...
    'gui_OpeningFcn', @RealSong_control_013_OpeningFcn, ...
    'gui_OutputFcn',  @RealSong_control_013_OutputFcn, ...
    'gui_LayoutFcn',  [] , ...
    'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before RealSong_control_013 is made visible.
function RealSong_control_013_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to RealSong_control_013 (see VARARGIN)

% Choose default command line output for RealSong_control_013
handles.output = hObject;
handles.gph.fig_hn=gcf;
handles=popup_targetselection_Callback(handles.popup_targetselection, eventdata, handles);

% previous_session_data='C:/home/matlab/xPCtarget/RTSAC_control_previous_session_data.mat';

pm=handles.pm;
path=which(mfilename);path=strsplit(path,filesep);
path=fullfile(path{1:end-1});

previous_session_data=fullfile(path,[mfilename,'_previous_session_data.mat']);

handles.pm.StimFamily_func='StimFamily_Manager_001';
% tg_OpenStimFamilyManager_Callback(handles.tg_OpenStimFamilyManager, eventdata, handles);

try
    load(previous_session_data,'pm');
    fprintf('Recovering previous session data.\n');
    %     file=fullfile(pm.param_pathname,pm.paramfile);
    %     fprintf('presyllable detection: %s\n',file);
    handles=pb_loadparam_Callback(hObject, eventdata, handles,pm.paramfile,pm.param_pathname);
    
    handles.pm.songstim_dir=pm.songstim_dir;
    handles.pm.songstim_file=pm.songstim_file;
    file=fullfile(pm.songstim_dir,pm.songstim_file);
    set(handles.text_songstimfile,'String',...
        sprintf(':%s',pm.songstim_file));
    
    %      handles.pm.pulsestim_dir=pm.pulsestim_dir;
    %     handles.pm.pulsestim_file=pm.pulsestim_file;
    %      file=fullfile(pm.pulsestim_dir,pm.pulsestim_file);
    %     set(handles.text_pulsestimfile,'String',...
    %         sprintf('pulse stim file: %s',pm.pulsestim_file));
    %
catch
    if FileExists(previous_session_data)
        fprintf('Error detected in previous session data. Discarded.');
        delete(previous_session_data);
    end
end




% Update handles structure
guidata(hObject, handles);

% UIWAIT makes RealSong_control_013 wait for user response (see UIRESUME)
% uiwait(handles.RealSong_figure);


% --- Outputs from this function are returned to the command line.
function varargout = RealSong_control_013_OutputFcn(hObject, eventdata, handles)
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;



% --- Executes on button press in pb_build.
function pb_build_Callback(hObject, eventdata, handles)
% hObject    handle to pb_build (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

switch handles.pm.target
    % SIMULATION, no need to connect target PC.
    case 'Simulation'
        
        handles.pm.modelname='test_PCI6052E_20120104_04_sim';
        open_system(handles.pm.modelname);
        
        %  use targetPC.
    otherwise
        switch handles.pm.target
            case {'RealSong(PCI6521,FullMode)','RealSong(PCI6521,MIConly)'}
                handles.pm.modelname='test_PCI6251_20130416_3ch';
                      
            case {'RealSong(PCI6052E,FullMode)','RealSong(PCI6052E,MIConly)'}
                  handles.pm.modelname='test_PCI6052E_20130416_3ch';
                
            case {'RealSong(PCI6070E,FullMode)'}
                % This is for PCI-MIO-16E (PCI6070E), both MIC and E1.
                % 12bit AD/DA.
                handles.pm.modelname='test_PCI6070E_20130416_3ch';
            case 'RealSong(PCI6070E,MIConly)'
                handles.pm.modelname='test_PCI6070_20130416_MIConly';
            otherwise
                error('Unknown model %s',handles.pm.target);
        end
        close_system(handles.pm.modelname,0);
        load_system(handles.pm.modelname);
        % For MIC only mode, delete unnecessary blocks for
                % lighter computational burden.
                
%         if strfind(handles.pm.target,'MIConly')
%              dynamic_generate_miconly_system=1;
%                 if ~isempty(strfind(handles.pm.target,'MIConly')) && (dynamic_generate_miconly_system)
%                     
%                     BlkName=[handles.pm.modelname '/RealSongControl'];
%                     hin=return_line_handles_simulink_model(BlkName);
%                     delete_line(hin{2});
%                     
%                     
%                     % find the destination block for OscilloAnticromic.
%                     Ports=get_param([handles.pm.modelname '/OscilloAntidromic'],'PortConnectivity');
%                     BusHandle=Ports(end).DstBlock;
%                     BusName=get_param(BusHandle,'Name');
%                     
%                     BlkName=[handles.pm.modelname '/OscilloAntidromic'];
%                     [hin,hout]=return_line_handles_simulink_model(BlkName);
%                     for dd=1:length(hin),delete_line(hin{dd});end
%                     for dd=1:length(hout),delete_line(hout{dd});end
%                     
%                     % replace_block('test_PCI6052E_20121026','OscilloAntidromic','Gain')
%                     
%                     % delete_line('test_PCI6052E_20121026', 'RealSongControl/1', 'PCI-6052E_AD/1');
%                     set_param([ handles.pm.modelname,'/PCI-6052E_AD'],...
%                         'channel','[1]','range','[-10 ]','Coupling','[0 ]');
%                     add_line( handles.pm.modelname,'Dummy/1','RealSongControl/2');
%                     add_line( handles.pm.modelname,'Dummy/1',[BusName,'/1']);
%                     add_line( handles.pm.modelname,'Dummy/1',[BusName,'/2']);
%                     delete_block([ handles.pm.modelname,'/OscilloAntidromic']);
%                     try
%                         save_system(handles.pm.modelname,[handles.pm.modelname,'_miconly']);
%                     end
%                     handles.pm.modelname=[handles.pm.modelname,'_miconly'];
%                 end
%         end
        %Check Connection Between Host and Target PC
        % Use 'xpctargetping' to test for a proper host-target connection.
        if ~strcmp(xpctargetping, 'success')
            errordlg('Connection with target cannot be established.');
            return;
        end
        
        %Open, Build, and Download Model to the Target PC
        
        %         close_system(handles.pm.modelname,0);
        %         load_system(handles.pm.modelname);
        
end

handles.pm.SampRate=evalin('base','SampRate');
handles.pm.ana_hopSize=evalin('base','ana_hopSize');
handles.oscil.AO1_TTL_Freq = 1;
assignin('base','AO1_TTL_Freq',handles.oscil.AO1_TTL_Freq);
handles.pm.Ts      = 1/handles.pm.SampRate;

% Secure fixed memory spaces for stimulation file later.
handles.pm.max_stim_T=6; %sec
handles.pm.max_stim_Tsamp=ceil(handles.pm.max_stim_T*handles.pm.SampRate);
% initialize song stim
assignin('base','init_stim_vector',zeros(handles.pm.max_stim_Tsamp,1));
%initialize spectrum-based filter.

handles.pm.findex=evalin('base','findex'); % load findex from base workspace.
handles.pm.maintarget_spectrum_filter=ones(length(handles.pm.findex),1);
handles.pm.mSpectrum_Filter_Threshold=1;

% Initialize spectrum based targetting parameters.
assignin('base','maintarget_spectrum_filter',handles.pm.maintarget_spectrum_filter);
assignin('base','Spectrum_Filter_Threshold',handles.pm.mSpectrum_Filter_Threshold);

if handles.pm.SampRate~=handles.pm.TemplateSampRate
    warning('Template sampling rte is different from RealSong Sampling rate. Please check result is correct..');
end
% Build the model and download the image, xpcosc.dlm,h to the target PC.
set_param(handles.pm.modelname,'RTWVerbose','off'); % Configure RTW for a non-Verbose build.
rtwbuild(handles.pm.modelname);
handles.pm.CorrectSampleTime=evalin('base','tg.SampleTime');
handles.pm.CorrectSampRate  = 1/handles.pm.CorrectSampleTime;

handles.tg=evalin('base','tg');
guidata(hObject,handles);
assignin('base','handles',handles);





% --- Executes on button press in pb_start.
function pb_start_Callback(hObject, eventdata, handles)
% hObject    handle to pb_start (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% handles.tg = evalin('base','tg');               % Create an xPC Target Object
% pm.UI_status=collect_status(hObject,eventdata,handles)
% handles.pm.UI_status=pm.UI_status;

assignin('base','handles',handles)

val=get(hObject,'Value');

if (val)
    try
        [handles.pm.savename, handles.pm.save_pathname] = uiputfile(fullfile(handles.pm.save_pathname,handles.pm.savename), 'Save data as');
    catch
        [handles.pm.savename, handles.pm.save_pathname] = uiputfile('*.mat', 'Save data as');
    end
    
    if isequal(handles.pm.savename,0) || isequal(handles.pm.save_pathname,0)
        disp('User pressed cancel');
        return;
    else
        disp(['User selected ', fullfile(handles.pm.save_pathname, handles.pm.savename)])
    end
    
    
    %----------------------------------------------%
    % Initialize recording parameters
    %----------------------------------------------%
    handles=init_rectime_param(handles);
    
    handles=edit_catch_ratio_Callback(handles.edit_catch_ratio, eventdata, handles);
    handles=tg_burstrigrec_Callback(handles.tg_burstrigrec, eventdata, handles);
    handles=edit_speakergain_Callback(handles.edit_speakergain, eventdata, handles);
    
    PreT_bin    =handles.pm.PreTrigger_Sec*handles.pm.SampRate;
    TotalT_bin  =handles.pm.MaxRecTime_Sec*handles.pm.SampRate;
    Minimum_SongDur = handles.pm.MinSoundDur2Rec; % Sound event must be this duration long. I recommend 0.6~0.8sec.
    
    fprintf('PreTrigger Time =%3.3g (%5d), Max Recording Time = %3.3g (%5d)\n',...
        handles.pm.PreTrigger_Sec,PreT_bin,...
        handles.pm.MaxRecTime_Sec,TotalT_bin);
    
    %-----------------------------------------------
    %----- Initialize stimulation files ------------
    %-----------------------------------------------
    fprintf('Loaded song stim: %s\n',fullfile(handles.pm.songstim_dir,handles.pm.songstim_file));
    handles=pb_loadsongstim_Callback(hObject, eventdata, handles,...
        handles.pm.songstim_file,handles.pm.songstim_dir);
    
    %--- make sure to reflect the state of pulse mode.
    handles=pb_dynamicpulse_Callback(handles.pb_dynamicpulse, eventdata, handles);
    
    set(handles.pb_start,'Value',1); % set them again because it is stopped by load stim.
    
    %----- make sure no-pretarget setting is reflected ----%
    handles=tgl_nopretarget_Callback(handles.tgl_nopretarget, eventdata, handles);
    
    %----------------------------------------------
    % make sure trigger will not occur at the beginning
    %----------------------------------------------
    
    id=getparamid(handles.tg,'RealSongControl/TriggerButton/TrigVal','Value');
    setparam(handles.tg,id,1);
  
    id=getparamid(handles.tg,'RealSongControl/DSPBlock/StimFamilyTriggerButton/TrigVal','Value');
    setparam(handles.tg,id,1);
 
    
    %----------------------------------------------%
    % setup signal id for recording and triggering.
    %----------------------------------------------%
    [channel_names,selected_val,bias,gain,value]=xpc_channel_selection_dlg();
    selected_channel_names={channel_names{find(selected_val)}};
    
    %     selected_val
    handles.pm.plot_channel_names = {channel_names{find(selected_val)}};
    handles.pm.plot_bias         =bias(find(selected_val));
    handles.pm.plot_gain         =gain(find(selected_val));
    set(handles.popup_trigch_selection,'String',handles.pm.plot_channel_names );
    set(handles.popup_trigch_selection,'Value',1);
    %     handles=control_plot_bias_gain(hObject,eventdata,handles);
    
    yplot_range=[min(bias)-40,max(bias)+10];
    handles.pm.rec_rawsignal_datanames=[];
    for ss=1:length(selected_channel_names)
        %     ss
        switch selected_channel_names{ss}
            case 'MIC'
                correct_channel_name='RealSongControl/MICGain';
            case 'E1'
                correct_channel_name='RealSongControl/Electrode1Gain';
            case 'Im'
                correct_channel_name='RealSongControl/ImOutGain';
            case 'Speaker'
                correct_channel_name='RealSongControl/SpeakerOutputREC';
            case 'TTL'
                correct_channel_name= 'RealSongControl/PulseStimOutputGain';
            otherwise
                error('Unknown option!');
        end
        handles.pm.rec_rawsignal_datanames{ss}=correct_channel_name;
    end
    
    n_rawsig=length(handles.pm.rec_rawsignal_datanames);
    
    fprintf('Recording signals are ');
    fprintf('%s, ',selected_channel_names{:});
    fprintf(' (%d channels).\n',n_rawsig);
    
    handles.pm.rec_MIC_index   = ...
        strmatch('RealSongControl/MICGain',handles.pm.rec_rawsignal_datanames);
    
    
    % If you want to record traces when you stimulate through speaker (AO0), use this.
    %     handles.pm.rec_Stimulus_index   = ...
    %         strmatch('RealSongControl/SpeakerOutputREC',handles.pm.rec_rawsignal_datanames);
    
    % If you want to record traces when you stimulate through TTL (AO1), use this.
    handles.pm.rec_Stimulus_index   = ...
        strmatch('RealSongControl/PulseStimOutputGain',handles.pm.rec_rawsignal_datanames);
    
     handles.pm.rec_Speaker_index   = ...
            strmatch('RealSongControl/SpeakerOutputREC',handles.pm.rec_rawsignal_datanames);
    
    handles.pm.rec_E1_index   = ...
        strmatch('RealSongControl/Electrode1Gain',handles.pm.rec_rawsignal_datanames);
    
    handles.pm.rec_Im_index   = ...
        strmatch('RealSongControl/ImOutGain',handles.pm.rec_rawsignal_datanames);
    
    
    
    handles.pm.rec_feature_datanames={...
        'RealSongControl/DSPBlock/FeaturesGain'};
    
    
    
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % ----- organization of feature data -----------%
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    % 0: init vector (-1)
    % 1: amplitude
    % 2: entropy
    % 3: frequency
    % 4: FM
    % 5: pitch
    % 6: pitchgoodness
    % 7: precisepitch
    % 8:MainSylGate(0/1)
    % 9:Predictor (0/1)
    % 10: ImOut
    % 11: SpectCorr
    % 12: mainsyl_detect
%   % 13: FF (Fundamental Frequency) 
%   % 14: Trigger Button
%   % 15: StimFamily Trigger Button
    % 11-(anal_hopf): zeros. You can more data here later.
    
    %   name          plot_or_not, gain, bias, style, depend_on_index,
    handles.pm.features_vec_names={...
        'amplitude',        1,  1,0,'b-';...
        'entropy',          0,  1,0,'-';...
        'frequency',        0,  1,0,'-';...
        'FM',               0,  1,0,'-';...
        'pitch',            0,  1,0,'-';......
        'pitchgoodness',    0,  1,0,'-';......
        'precisepitch',     0,  1,0,'-';......
        'MainSylGate',      1,  5,0,'r-';......
        'Predictor',        1,  1,0,'y-';...
        'ImOut',            0,  1,0,'k-';...
        'SpectCorr',        1,  1,0,'r';...
        'mainsyl_detect',   1,  5,0,'m';...
        'FF',               0,  1,0,'m';...
        'TriggerButton',    0,  1,0,'k';...
        'StimFamilyTriggerButton',    0,  1,0,'r'};
    
    handles.pm.initvec_val = -1;
    handles.pm.feat.amplitude_index=strmatch('amplitude',{handles.pm.features_vec_names{:,1}}, 'exact');
    handles.pm.feat.entropy_index=strmatch('entropy',{handles.pm.features_vec_names{:,1}}, 'exact');
    handles.pm.feat.frequency_index=strmatch('frequency',{handles.pm.features_vec_names{:,1}}, 'exact');
    handles.pm.feat.FM_index=strmatch('FM',{handles.pm.features_vec_names{:,1}}, 'exact');
    handles.pm.feat.pitch_index=strmatch('pitch',{handles.pm.features_vec_names{:,1}}, 'exact');
    handles.pm.feat.pitchgoodness_index=strmatch('pitchgoodness',{handles.pm.features_vec_names{:,1}}, 'exact');
    handles.pm.feat.precisepitch_index=strmatch('precisepitch',{handles.pm.features_vec_names{:,1}}, 'exact');
    handles.pm.feat.MainSylGate_index=strmatch('MainSylGate',{handles.pm.features_vec_names{:,1}}, 'exact');
    handles.pm.feat.Predictor_index=strmatch('Predictor',{handles.pm.features_vec_names{:,1}}, 'exact');
    handles.pm.feat.ImOut_index=strmatch('ImOut',{handles.pm.features_vec_names{:,1}}, 'exact');
    handles.pm.feat.SpectCorr_index=strmatch('SpectCorr',{handles.pm.features_vec_names{:,1}}, 'exact');
    handles.pm.feat.mainsyl_detect_index=strmatch('mainsyl_detect',{handles.pm.features_vec_names{:,1}}, 'exact');
    handles.pm.feat.FF_index=strmatch('FF',{handles.pm.features_vec_names{:,1}}, 'exact');
    handles.pm.feat.TriggerButton_index=strmatch('TriggerButton',{handles.pm.features_vec_names{:,1}}, 'exact');
    handles.pm.feat.StimFamilyTriggerButton_index=strmatch('StimFamilyTriggerButton',{handles.pm.features_vec_names{:,1}}, 'exact');
   
    
    
    n_featdata=1;
    n_featdata_plot=size(handles.pm.features_vec_names,1);
    plot_features= [handles.pm.features_vec_names{:,2}];
    feat_gain    = [handles.pm.features_vec_names{:,3}];
    feat_bias    = [handles.pm.features_vec_names{:,4}];
    feat_style    = {handles.pm.features_vec_names{:,5}};
    
    handles.pm.n_rec_channel    =n_rawsig+n_featdata;
    
    handles.pm.NoRec_feature_datanames={...
        'RealSongControl/DSPBlock/BoutCounter/BoutONGAINSEC'};
    
    n_NoRec_featdata=length(handles.pm.NoRec_feature_datanames);
    plot_NonRec_features=[0];
    
    handles.pm.rec_feature_BoutONCnt_index   = strmatch('RealSongControl/DSPBlock/BoutCounter/BoutONGAINSEC',handles.pm.NoRec_feature_datanames)+handles.pm.n_rec_channel;
    
    axes(handles.axes_data);cla;
    handles.gph.axes_data_plot=plot(NaN(n_rawsig),NaN(n_rawsig));
    axes(handles.axes_feature);cla;
    handles.gph.axes_feature_plot=[];
    for gg=1:n_featdata_plot
        handles.gph.axes_feature_plot(gg)=plot(NaN,NaN,feat_style{gg});hold on;
    end
    
    handles.gph.axes_NoRec_feature_plot=plot(NaN(n_NoRec_featdata),NaN(n_NoRec_featdata));
    handles.gph.axes_ampthresh_plot = plot(NaN,NaN,'b--');
    % guidata(hObject,handles);
    
    axes(handles.axes_data_trigger);cla;
    handles.gph.axes_data_trigger_plot=plot(NaN(n_rawsig),NaN(n_rawsig));
    axes(handles.axes_feature_trigger);cla;
    handles.gph.axes_feature_trigger_plot=[];
    for gg=1:n_featdata_plot
        handles.gph.axes_feature_trigger_plot(gg)=plot(NaN,NaN,feat_style{gg});hold on;
    end
    
    %------------------------------------%
    % setup host scope0 for both raw and feature data.
    %------------------------------------%
    
    if ~isempty(intersect([5, 6],handles.tg.Scopes)) % If there remains old scope, remove them.
        remscope(handles.tg,[5, 6]);
    end
    db_sc0 = addscope(handles.tg, 'host',[5, 6]);  % double buffer host soft scope 1 for pretrigger
    db_sc0_ids=get(db_sc0,'ScopeId'); sdb_sc0_ids=circshift([db_sc0_ids{:}],[0,1]);
    
    
    
    signals0=zeros(n_rawsig+n_featdata+n_NoRec_featdata,1);
    % Assign signals to each recording channels.
    for ii=1:n_rawsig
        tmp_sigid=getsignalid(handles.tg,handles.pm.rec_rawsignal_datanames{ii});
        if (isempty(tmp_sigid))||(tmp_sigid==0)
            error('Wrong signal name %s!',handles.pm.rec_rawsignal_datanames{ii});
        end
        signals0(ii) = tmp_sigid;
    end
    
    for ii=1:n_featdata
        tmp_signalID=getsignalid(handles.tg,handles.pm.rec_feature_datanames{ii});
        if isempty(tmp_signalID), error('Unknown signal name!');end;
        signals0(n_rawsig+ii) = tmp_signalID;
        if (signals0(n_rawsig+ii)==0) || isempty(signals0(n_rawsig+ii))
            error('Wrong signal name %s!',handles.pm.rec_feature_datanames{ii});
        end
    end
    
    
    for ii=1:n_NoRec_featdata
        tmp_signalID=getsignalid(handles.tg,handles.pm.NoRec_feature_datanames{ii});
        if isempty(tmp_signalID), error('Unknown signal name!');end;
        ind=n_rawsig+n_featdata+ii;
        signals0(ind) = tmp_signalID;
        if (signals0(ind)==0) || isempty(signals0(ind))
            error('Wrong signal name %s!',handles.pm.NoRec_feature_datanames{ii});
        end
    end
    
    addsignal(db_sc0,signals0);
    
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % -- online spectrum calculation parameters   --%
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    nWinsize = 256;
    [E2,V] = dpss(nWinsize,4,2);
    Ec=E2(:,1);
    Es=E2(:,2);
    nFFT     = 1024/handles.pm.decimation;
    f = [0:nFFT]*handles.pm.SampRate/nFFT/handles.pm.decimation;
    plot_findex= find(f>400 & f<10000);
    f_plot = f(plot_findex);
    
    %     plot_matrix= NaN(length(handles.pm.findex),handles.gph.online_spectrum_fftplot);
    %     size(f_plot)
    %     size(plot_matrix)
    
    
    
    
    % get(db_sc0(1))
    set(db_sc0,...
        'NumSamples',handles.pm.buff_time_nbin,...
        'TriggerSample', -1,...
        'TriggerMode','Scope',...
        'Decimation', handles.pm.decimation); % sampling rate is now 11025.
    
    
    
    cbuffer = circbuff(handles.pm.buff_time_nbin,handles.pm.n_buff,handles.pm.n_rec_channel+1);
    
    Fsd = handles.pm.SampRate/handles.pm.decimation;
    
    
    setappdata(handles.gph.fig_hn,'cbuff_handle',cbuffer);
    guidata(hObject,handles);
    trigtic=[tic tic];
    
    for ii=1:length(db_sc0),db_sc0(ii).TriggerScope = sdb_sc0_ids(ii);end
    
    %% Start the scopes and the model.
    start([db_sc0]);
    start(handles.tg);
    
    % Start things off by triggering scope 1.
    % n_repeat=max_rec_time/buff_time;
    % feature_t   =zeros(buff_time_nbin_feature*max_rec_time/buff_time,1);
    % feature     =zeros(buff_time_nbin_feature*max_rec_time/buff_time,length(signals0));
    % data_t      =zeros(buff_time_nbin_rawdata*max_rec_time/buff_time,1);
    % data        =zeros(buff_time_nbin_rawdata*max_rec_time/buff_time,length(signals1));
    
    n=1;
    scNum = 1;
    
    % Trigger the first scope, then wait
    trigger([db_sc0(scNum)]);
    
    Rec_Wait_state='Off';
    last_rectime=clock;
    x0 = zeros(nWinsize,1); % to be used for sound_snippets_from_last_scope;
    
    % Use the two scopes as a double buffer to log the data.
    %----------- start of recording --------------
    
    % initialize counter for recording.
    post_bout_ctr=my_counter;
    post_stim_ctr=my_counter;
    rec_ctr      =my_counter;
    oscillo_ctr  =my_counter;
    StimFamily_Counter.Stimulating=0; % 0: Interval, 1: Stimulating
    StimFamily_Counter.StimCount=0;
    StimFamily_Counter.IntervalTime=0;
    
    while get(handles.pb_start,'Value') %while it's ON
        
        
        % Wait until this scope has finished acquiring samples
        % or the model stops (scope is interrupted).
        
        while (~strcmp(db_sc0(scNum).Status, 'Finished')||...
                strcmp(db_sc0(scNum).Status, 'Interrupted'))
            %
            %       pause(0.01);
            if strcmp(db_sc0(scNum).Status, 'Ready for being Triggered')
                fprintf('Scope stopped and retriggered. Scope%d) 1)%s,2)%s\n',...
                    scNum,db_sc0(1).Status,db_sc0(2).Status);
                trigger(db_sc0(scNum));
                %                 fprintf('1)%s,%s\n',db_sc0(1).Status,db_sc0(2).Status);
            elseif strncmp(handles.tg.CPUOverload,'detected',4)
                -handles.tg;
                set(handles.pb_start,'Value',0);
                msgbox('CPU Overload detected!');
                break;
            end
        end
        %         triglapsetime=toc(trigtic(scNum));
        %         fprintf('Scope%d) Finished. %g sec from last start. 1)%s,2)%s\n',...
        %             scNum,triglapsetime,db_sc0(1).Status,db_sc0(2).Status);
        
        % Stop buffering data when the model stops.
        if (strcmp(handles.tg.Status, 'stopped')||...
                strcmp(db_sc0(scNum).Status, 'Pre-Acquiring'))
            set(handles.pb_start,'Value',0);
            break;
        elseif strncmp(handles.tg.CPUOverload,'detected',4)
            -handles.tg;
            set(handles.pb_start,'Value',0);
            msgbox('CPU Overload detected!');
            break;
        end
        %  fprintf('2)%s,%s\n',db_sc0(1).Status,db_sc0(2).Status);
        %     tic;
        sound_snippets_from_last_scope = x0(end-nWinsize+1:end,1);
        
        try
            t0=db_sc0(scNum).Time;
            x0=db_sc0(scNum).Data;
        catch ME
            if strcmp(db_sc0(scNum).Status, 'Ready for being Triggered')
                fprintf('now)%s,next)%s\n',db_sc0(scNum).Status,db_sc0(3-scNum).Status);
                trigger(db_sc0(scNum));
                %                 fprintf('1)%s,%s\n',db_sc0(1).Status,db_sc0(2).Status);
                disp('scope stopped (%s) and retriggered.',ME)
                
            end
        end
        %   toc;
        
        % Prepare this scope to start again.
        %   fprintf('3)%s,%s\n',db_sc0(1).Status,db_sc0(2).Status);
        start([db_sc0(scNum)]); %trigger(db_sc0(scNum));
        trigtic(scNum)=tic;
        
%         % Special Case to stop recording. 
%         meanV=mean(x0(:,handles.pm.rec_E1_index))*100
%         if meanV>0 || meanV<-120
%             disp('Membrane potential is outside of range. Stop recording.')
%             break;
%         end
        
        skip=2;
        
        cnt=1;
        
        
        %--------- plot recording data ----%
        for ii=1:n_rawsig
            set(handles.gph.axes_data_plot(ii),...
                'XData',t0(1:skip:end),...
                'YData',handles.pm.plot_bias(ii)+handles.pm.plot_gain(ii)*x0(1:skip:end,ii));
            %       set(handles.gph.axes_data_plot(2),'XData',t0(1:skip:end),'YData',-90+50*x0(1:skip:end,2));
            %       set(handles.gph.axes_data_plot(3),'XData',t0(1:skip:end),'YData',100*x0(1:skip:end,3));
        end
        set(handles.axes_feature,'XLim',[t0(1),t0(end)]);
        if isempty( handles.pm.rec_E1_index)
            E1mean = 0;
        else
            E1mean=100*median(x0(1:skip:end,handles.pm.rec_E1_index));
        end
      
%         yplot_range
       yplot_range_tmp= [min(yplot_range(1),E1mean-10),yplot_range(2)];
        set(handles.axes_data,'XLim',[t0(1),t0(end)],'YLim',yplot_range_tmp);
        
        % ------- plot spectrum feature data ---%
        feature_start_index=find(x0(:,n_rawsig+n_featdata)==handles.pm.initvec_val);
        
        for ii=1:n_featdata_plot%[1,4,5,6];%n_featdata
            if plot_features(ii)
                indp=feature_start_index+ii;
                if (indp(end)>size(x0,1))
                    indp=indp(1:end-1);
                end
                set(handles.gph.axes_feature_plot(ii),...
                    'XData',t0(indp),...
                    'YData',feat_bias(ii)+feat_gain(ii)*x0(indp,n_rawsig+n_featdata));
            end
        end
        
        % obtain mainsylgate data.
        mainsyl_detect_indp = feature_start_index+handles.pm.feat.mainsyl_detect_index;
        if (mainsyl_detect_indp(end)>size(x0,1)),mainsyl_detect_indp=mainsyl_detect_indp(1:end-1);end
        mainsyl_detect = x0(mainsyl_detect_indp,n_rawsig+n_featdata);
        
        
        % obtain max of sound amplitude
        amplitude_indp = feature_start_index+handles.pm.feat.amplitude_index;
        max_amp= max(x0(amplitude_indp(1:end-1),n_rawsig+n_featdata));
        
        % obtain manual trigger button
        triggerbutton_indp = feature_start_index+handles.pm.feat.TriggerButton_index;
        if (triggerbutton_indp(end)>size(x0,1)),triggerbutton_indp=triggerbutton_indp(1:end-1);end
        triggerbutton_pressed = x0(triggerbutton_indp,n_rawsig+n_featdata);
        
         % obtain stim family trigger button
        triggerbutton_indp = feature_start_index+handles.pm.feat.StimFamilyTriggerButton_index;
        if (triggerbutton_indp(end)>size(x0,1)),triggerbutton_indp=triggerbutton_indp(1:end-1);end
        StimFamilyTriggered = x0(triggerbutton_indp,n_rawsig+n_featdata);
        
        
        % ------- plot Non-recorded other data ---%
        for ii=1:length(plot_NonRec_features);%[1,4,5,6];%n_featdata
            if plot_NonRec_features(ii)
                set(handles.gph.axes_NoRec_feature_plot(ii),'XData',t0(1:skip:end),'YData',x0(1:skip:end,handles.pm.n_rec_channel+ii));
            end
        end
        
        amp_thresh=str2double(get(handles.edit_amp_thresh,'String'));
        
        set(handles.gph.axes_ampthresh_plot,'XData',[t0(1) t0(end)],'YData',amp_thresh*ones(1,2))
        %         axis([t0(1) t0(end) 0 10*amp_thresh]);
        set(handles.axes_feature,'YLim',[0 max(10*amp_thresh,max_amp)]);
        
        %            triglapsetime=toc(trigtic(scNum));
        %         fprintf('Scope%d) Finish plot task. %g sec from last start. 1)%s,2)%s\n',...
        %             scNum,triglapsetime,db_sc0(1).Status,db_sc0(2).Status);
        
        % putdata in buffer. first channel is the time vector.
        cbuffer.putdata([t0,x0(:,[1:handles.pm.n_rec_channel])]);
        
        
        %--- detect sound onset, ----%
        %   SoundONCnt=x0(1:handles.pm.ana_hopSize:end,handles.pm.rec_feature_SoundONCnt_index);
        %   SoundOFFCnt=x0(1:handles.pm.ana_hopSize:end,handles.pm.rec_feature_SoundOFFCnt_index);
        % Now, BoutOnCnt is in sec.
        BoutONCnt=x0(1:handles.pm.ana_hopSize:end,handles.pm.rec_feature_BoutONCnt_index);
        Stimulated        = find(triggerbutton_pressed,1,'First');
        %         Stimulated        = find(x0(:,handles.pm.rec_Stimulus_index)>0,1,'First');
        %         Predicted        = 0;%any(x0(:,handles.pm.rec_feature_Predictor_index)>0.0);
        RecON             =get(handles.pb_REC,'Value');
        RecStimOn         =get(handles.rb_stim_and_rec,'Value');
        dBCnt           = diff(BoutONCnt>Minimum_SongDur);
        
        if (RecON)
            ScheduleRecON=get(handles.rb_scheduledrec,'Value');
            if (ScheduleRecON)
                RecON =0;
                RecTimerVal=eval(get(handles.edit_scheduledrec_timer,'String'));
                elapsed_time=etime(clock,last_rectime);
                %             fprintf('%gsec to start scheduled recording\n',RecTimerVal-elapsed_time)
                if elapsed_time>RecTimerVal
                    RecON=1;
                end
            end
        end
        
        % Recording state changed cyclicway like 'Off'->'REC'->'TransientOff'->'Off'.
        % When sound event longer than Minimum_SongDur occurs, state changes 'Off' -> 'On', set
        % REC_counter = 3; % we want to record one chunk of data before the onset.
        % When next chunk of sound comes in, increment REC_counter = REC_counter + 1;
        %   If the BoutOnCnt drops off from a value larger than Minimum_SongDur to zero,
        % makes transition 'On' -> 'TransientOff'.
        % When the state is 'TransientOff', set state 'Off', and record the data
        %  by using the index = [-nChunk*REC_counter+1:0].
        
        %         triglapsetime=toc(trigtic(scNum));
        %         fprintf('Scope%d) Finished putting data and detect sound.\n %g sec from last start. 1)%s,2)%s\n',...
        %             scNum,triglapsetime,db_sc0(1).Status,db_sc0(2).Status);
        post_stim_ctr.update(handles.pm.buff_time_nbin);
        post_bout_ctr.update(handles.pm.buff_time_nbin);
        
        switch Rec_Wait_state
            case 'Off'
                On_Crossing_event = find(dBCnt>0);
                Over_Crossing_event = find(BoutONCnt>Minimum_SongDur,1,'first');
                
                %                           if (~isempty(On_Crossing_event)||Stimulated) % If Bout Duration Crosses the Miminum recording threshold for the first time
                if (~isempty(On_Crossing_event)) % If Bout Duration Crosses the Miminum recording threshold for the first time
                    n_shift=1;%On_Crossing_event;
                    
                    %              fprintf('On event happend (%d)\n',n_shift);
                    Rec_Wait_state='On';
                    REC_counter     = 3;
                    %                     REC_countdown   = [];
                    
                    fprintf('Detect Song Onset:');
                    %end
                     saveopt='';
                    % If stimulation occured outside of vocalization
                elseif (~isempty(Stimulated))
                    Rec_Wait_state='On';
                    
                    
                    if (RecON) % In REC mode.
                        REC_counter=1;
                        %                         REC_countdown   = [];
                    else
                        REC_counter = 2;
                    end
                    
                    stimmax=max(handles.pm.dynpulse.burst_dur/1000,handles.pm.L_songstim_len_sec);
                    n_shift=handles.pm.buff_time_nbin - ceil(Stimulated*handles.pm.ana_hopSize/handles.pm.decimation);
                    %                     n_shift=n_shift-ceil(stimmax*Fsd)
                    %
                    %                     post_stim_ctr.set(-n_shift+handles.pm.buff_time_nbin-ceil(handles.pm.PostSilentRecDur_Sec*Fsd));% Consider n_shift is negative value, incremented each time point, when it is zero, that is the end of recording.
                    %
                    %
                    fprintf('Detect Stimulation Onset:');
                    SongVal=get(handles.popup_SongStimSelect,'Value');
                    SongStr=get(handles.popup_SongStimSelect,'String');
                    
                    saveopt=['_trig_',SongStr{SongVal}];
                    
                    % If REC button is turned ON, and
                    %         % Bout Duration does not crosses the Miminum recording threshold for the first time
                elseif (RecON)
                    %                    rec_ctr.stop;
                    %                    rec_ctr.start;
                    %                    rec_ctr.update(handles.pm.buff_time_nbin);
                    %
                    Rec_Wait_state='On';
                    REC_counter = 1;
                    %                     REC_countdown= handles.pm.MaxRecTime_Sec;
                    fprintf('Recording Start:');
                    last_rectime=clock;
                    n_shift=1;
                    if (RecStimOn)
                        pb_trigger_Callback(handles.pb_trigger, [], handles);
                    end
                    %           end
                    saveopt='_autoREC';
                    
                elseif get(handles.tg_burstrigrec,'Value')
                    
                    spk=voltage2spkmatrix_silent(x0(:,handles.pm.rec_E1_index),15/100,ceil(1/1000*handles.pm.SampRate/handles.pm.decimation));
                    isi=1000*diff(find(spk))/(handles.pm.SampRate/handles.pm.decimation);
                    burstind=find(isi<5,1,'first');
                    if ~isempty(burstind)
                        %                         rec_ctr.stop;
                        %                         rec_ctr.start;
                        %                         rec_ctr.update(burstind(1));
                        
                        fprintf('Burst (%3.3g<5ms) detected!',isi(burstind(1)));
                        n_shift=1;%On_Crossing_event;
                        %              fprintf('On event happend (%d)\n',n_shift);
                        Rec_Wait_state='On';
                        REC_counter = 3;
                        %                         REC_countdown = 3;
                        %                         counter.post_bout =  handles.pm.buff_time_nbin-burstind(1);
                    end
              
                saveopt='_burst';
                end
                
            case 'On'
                
                End_Crossing_event = find(dBCnt<0,1,'first');
                
                if ~isempty(End_Crossing_event) % If Bout Duration Crosses the Miminum recording threshold for the first time
                    % init counter.
                    %                     n_shift=handles.pm.buff_time_nbin-End_Crossing_event*handles.pm.ana_hopSize/handles.pm.decimation;
                    Rec_Wait_state='TransientOff';
                    fprintf('Detect End Song (song dur=');
                    fprintf('%4.2f,', 1000*post_bout_ctr.parameter);
                    fprintf('[msec].)\n')
                    %                     fprintf('Rec:%d.,',REC_countdown)
                elseif get(handles.tg_burstrigrec,'Value')&&(~RecON)
                    % progress counter.
                    %                     counter.post_bout = counter.post_bout+handles.pm.buff_time_nbin;
                    Rec_Wait_state='TransientOff';
                else
                    % progress counter.
                    %                     counter.post_bout = counter.post_bout+handles.pm.buff_time_nbin;
                    fprintf('.');
                    
                end
                
                
                REC_counter = ceil(REC_counter +1);
                if REC_counter == handles.pm.rec_max_n_buff-1
                    fprintf('Approaching the end of recording limit. \n');
                    Rec_Wait_state='TransientOff';
                end
                
                %                REC_countdown = REC_countdown-handles.pm.buff_time;
                %                fprintf('%3.1f.',REC_countdown)
                %                 if  REC_counter ==handles.pm.rec_max_n_buff-1
                %
                %                     fprintf('Approaching the end of recording limit. \n');
                %                     Rec_Wait_state='TransientOff';
                %                 end
                %
                %                if REC_countdown <handles.pm.buff_time
                % %                    fprintf('Approaching the end of recording limit. \n');
                %                    Rec_Wait_state='TransientOff';
                %                    if strncmp(post_bout_ctr.state,'start',5)
                %                        REC_period = post_bout_ctr.parameter+handles.pm.PostSilentRecDur_Sec;
                %                        n_shift=post_bout_ctr.counter;
                %                        post_bout_ctr.stop;
                %
                %                    elseif strncmp(post_stim_ctr.state,'start',5)
                %                        REC_period = post_stim_ctr.parameter+handles.pm.PostSilentRecDur_Sec;
                %                        n_shift=post_stim_ctr.counter;
                %                        post_stim_ctr.stop;
                %                    elseif strncmp(rec_ctr.state,'start',5)
                %                        REC_period =  handles.pm.MaxRecTime_Sec;
                %                        n_shift=1;
                %                        rec_ctr.stop;
                %                    end
                %                    fprintf('Save in On\n')
                %                    handles=pb_acquiredata_Callback(hObject, eventdata, handles,...
                %                        REC_period,n_shift);
                %                    REC_counter=0;
                %
                %                end
                
                
            case 'TransientOff'
                Rec_Wait_state= 'Off';
                REC_counter = ceil(REC_counter +1);
                %                 n_shift
                pb_acquiredata_Callback(hObject, eventdata, handles,...
                    REC_counter,n_shift,saveopt);
                REC_counter=0;
                
                
                %                 triglapsetime=toc(trigtic(scNum));
                %                 fprintf('Scope%d) Save Finished. %g sec from last start. 1)%s,2)%s\n',...
                %                     scNum,triglapsetime,db_sc0(1).Status,db_sc0(2).Status);
                
                %          fprintf('Saved.\n');
                
            otherwise
                error('Unknown option %s',Rec_Wait_state);
        end
        
        
        
        % do it again, to find the case where if sound event on -> transient-off,
        % within the same sound chunk of data.
        
        switch Rec_Wait_state
            case 'On'
                End_Crossing_event = find(dBCnt<0);
                
                if ~isempty(End_Crossing_event) % If Bout Duration Crosses the Miminum recording threshold for the first time
                    Rec_Wait_state='TransientOff';
                    fprintf('Detect End Songg (song dur=');
                    fprintf('%4.2f,', 1000*BoutONCnt(End_Crossing_event));
                    fprintf('[msec].)\n')
                    
                    %                     post_bout_ctr.stop;
                    %                     post_bout_ctr.start;
                    %                     n_shift=handles.pm.buff_time_nbin-End_Crossing_event*handles.pm.ana_hopSize/handles.pm.decimation;
                    %                     post_bout_ctr.set(n_shift);% then, add time shift for onset of bout.
                    %                     post_bout_ctr.parameter = handles.pm.PreTrigger_Sec+BoutONCnt(End_Crossing_event);
                    %
                    %                     REC_countdown   = n_shift/Fsd;
                    %
                    
                end
                
                % REC_counter = ceil(REC_counter +1); This time, no increment.
                
            case 'TransientOff'
                Rec_Wait_state= 'TransientOff';
                %          REC_counter = ceil(REC_counter +1);
                %          pb_acquiredata_Callback(hObject, eventdata, handles,REC_counter)
                %          REC_counter=0;
                
            case 'Off'
                On_Crossing_event = find(dBCnt>0);
                if ~isempty(On_Crossing_event) % If Bout Duration Crosses the Miminum recording threshold for the first time
                    Rec_Wait_state='On';
                    REC_counter = 2;
                    fprintf('Detect Song Onset2:');
                end
            otherwise
                error('Unknown option %s',Rec_Wait_state);
        end
        
        %------------------- ----------------- -------------------------%
        %------------------- StimFamily Control -------------------------%
        %------------------- ----------------- -------------------------%
        
        if get(handles.tg_OpenStimFamilyManager,'Value')
            
            %-------- RUN ----------%
            if get(handles.tg_Run_StimFamily,'Value')
            StimFamily=getappdata(handles.tg_OpenStimFamilyManager,'StimFamily');
            StimFamily_handles=getappdata(handles.tg_OpenStimFamilyManager,'StimFamily_handles');
            
            
            if (~StimFamily_Counter.Stimulating) % During Interval,
                StimFamily_Counter.IntervalTime=StimFamily_Counter.IntervalTime+handles.pm.buff_time;
                if (StimFamily_Counter.IntervalTime>StimFamily.Param.StimInterval) && ~get(handles.tg_Pause_StimFamily,'Value')
                    [StimGo,StimFamily_saveopt,StimFamily.Param.StimInterval]=...
                        control_StimFamily(hObject,eventdata,handles,'next_stim',StimFamily_handles);
                    if (StimGo)
                        StimFamilyTrigger_Callback(hObject, eventdata, handles);
                        StimFamily_Counter.Stimulating=1;
                    else
                        set(handles.tg_Run_StimFamily,'Value',0);
                    end
                        
                end
            else % Now Stimulating.
                StimFamilyTrigger_index=find(StimFamilyTriggered,1,'first');
                
                if ~isempty(StimFamilyTrigger_index) % If there is a trigger,
                    StimFamily_Counter.StimCount;
                    
                    
                    StimFamily_Counter.StimCount = StimFamilyTrigger_index+(StimFamily.Param.RecIntervalN-1);
                    % flip the plot index, now relative to the end of
                    % recording.
                    % now, if there is any positive, which means we have to
                    % wait more data to plot.
                end
                fprintf('*')
                StimFamily_Counter.StimCount = StimFamily_Counter.StimCount -handles.pm.buff_time_nbin;

                if StimFamily_Counter.StimCount<0
                    % update oscillo;
                    index = [-StimFamily.Param.RecIntervalN+1, 0] +StimFamily_Counter.StimCount;

                    %                     cbdata = cbuffer.getdata(index(1):index(end));
                    StimFamily_REC_counter = StimFamily.Param.RecIntervalN/handles.pm.buff_time_nbin;
                    n_shift = -StimFamily_Counter.StimCount;
                    
                    [hd,cbdata]=pb_acquiredata_Callback(hObject, eventdata, handles,...
                    StimFamily_REC_counter,n_shift, StimFamily_saveopt);
                
                    StimFamily_Counter.Stimulating=0; % Now in "Interval" state.
                    StimFamily_Counter.IntervalTime=StimFamily_Counter.StimCount/handles.pm.SampRate;
                 fprintf('Done.\n');
%                   fprintf('Retrieving cbdata took %3.1fsec\n',toc_time);
                    StimFamily_Counter.StimCount = inf;
                    
                    % now, push obrained data to 
%                     fprintf('Pushing data\n')
                    control_StimFamily(hObject,eventdata,handles,...
                        'push_data',StimFamily_handles,cbdata(:,handles.pm.rec_E1_index+1));
                    
%                       control_StimFamily(hObject,eventdata,handles,...
%                         'push_data',StimFamily_handles,cbdata(:,handles.pm.rec_Speaker_index+1));
%                     
                end
            end
            
          
            end
            
        end
        
        %------------------- ----------------- -------------------------%
        %-------------- END of StimFamily Control -----------------------%
        %------------------- -----------------  -------------------------%
        
        %--- update time -----%
        hours   =floor(t0(end)/3600);
        minutes =floor(mod(t0(end),3600)/60);
        seconds =floor(mod(t0(end),60));
        %   millseconds = num2str(t0(end)-floor(t0(end)));
        time_string=sprintf('t = %2.2d:%2.2d:%2.2d',...
            hours,minutes,seconds);
        set(handles.text_sample_processed,'String',time_string);
        
        
        if get(handles.tg_sonogram_OnOff,'Value')
            [y,f,t,p]=calc_spectrogram(x0(:,handles.pm.rec_MIC_index),handles);
            
            h=getappdata(handles.gph.fig_hn,'sonogram_plot_handle');
            p=10*log10(abs(p));
            set(h,'CData',p);
           
            h=getappdata(handles.gph.fig_hn,'sonogram_axes_handle');
            set(h,'CLim',[-80 -50]);
%             [ min(min(p)), max(max(p))]
% caxis([-80 -50])
           
%             caxis()
        end
        
        % Update Triggered Oscilloscope Window.
        if get(handles.tg_trigoscillo,'Value')
            trig_oscillo_ch_val=get(handles.popup_trigch_selection,'Value');
            trig_oscillo_thresh=str2double(get(handles.edit_trigch_threshold,'String'));
            trig_oscillo_xrange = str2double(get(handles.edit_trigge_xrange,'String'))/1000;
            
            tmpx=handles.pm.plot_bias(trig_oscillo_ch_val)+handles.pm.plot_gain(trig_oscillo_ch_val)*x0(:,trig_oscillo_ch_val);
            oscillo_trigger_index=find(diff(tmpx>trig_oscillo_thresh),1,'first');
            if ~isempty(oscillo_trigger_index) && (oscillo_ctr.stopping)
                
                plot_index = oscillo_trigger_index+ceil(trig_oscillo_xrange*Fsd*[-1 1]);
                % flip the plot index, now relative to the end of
                % recording.
                % now, if there is any positive, which means we have to
                % wait more data to plot.
                plot_index = plot_index -handles.pm.buff_time_nbin;
                
                oscillo_ctr.parameter = plot_index;
                oscillo_ctr.start;
                oscillo_ctr.set(plot_index(end));
            elseif (oscillo_ctr.running)% if oscillo_ctr is running,
                oscillo_ctr.update(-handles.pm.buff_time_nbin);
            end
            
            
            if oscillo_ctr.counter<0
                % update oscillo;
                plot_index = [oscillo_ctr.counter  - ceil(2*trig_oscillo_xrange*Fsd*[1 0])];
                oscillo_ctr.stop;
                cbdata = cbuffer.getdata(plot_index(1):plot_index(end));
                t0trig=1000*(cbdata(:,1)-cbdata(1,1)-trig_oscillo_xrange);
                x0trig=cbdata(:,2:end);
                
                %--------- plot recording data ----%
                for ii=1:n_rawsig
                    
                    set(handles.gph.axes_data_trigger_plot(ii),...
                        'XData',t0trig,...
                        'YData',handles.pm.plot_bias(ii)+handles.pm.plot_gain(ii)*x0trig(:,ii));
                    %       set(handles.gph.axes_data_plot(2),'XData',t0(1:skip:end),'YData',-90+50*x0(1:skip:end,2));
                    %       set(handles.gph.axes_data_plot(3),'XData',t0(1:skip:end),'YData',100*x0(1:skip:end,3));
                end
%                 [t0trig(1),t0trig(end)]
%                 1000*trig_oscillo_xrange*[-1 0 1]
                set(handles.axes_feature_trigger,'XLim',[t0trig(1),t0trig(end)],'XTick',1000*trig_oscillo_xrange*[-1 0 1]);
                set(handles.axes_data_trigger,'XLim',[t0trig(1),t0trig(end)],'YLim',yplot_range);
                
                % ------- plot spectrum feature data ---%
                feature_start_index=find(x0trig(:,n_rawsig+n_featdata)==handles.pm.initvec_val);
                
                for ii=1:n_featdata_plot%[1,4,5,6];%n_featdata
                    if plot_features(ii)
                        indp=feature_start_index+ii;
                        if (indp(end)>size(x0trig,1))
                            indp=indp(1:end-1);
                        end
                        set(handles.gph.axes_feature_trigger_plot(ii),...
                            'XData',t0trig(indp),...
                            'YData',feat_bias(ii)+feat_gain(ii)*x0trig(indp,n_rawsig+n_featdata));
                    end
                end
                
                
            end
        end
        drawnow;
        
        if get(handles.tg_use_spectrum_filter,'Value')
            %
            is_mainsyl_detect = detect_thresholded_regions(abs(mainsyl_detect),...
                0.5,3,1000,100,1,0);
            %             is_mainsyl_detect
            obj.f=      f_plot;
            obj.spec = [];
            online_speccorr=zeros(1,length(is_mainsyl_detect));
            online_speccorr_indp = feature_start_index+handles.pm.feat.SpectCorr_index;
            
            for mm=1:length(is_mainsyl_detect)
                online_speccorr(mm)=x0(online_speccorr_indp(is_mainsyl_detect(mm)),n_rawsig+n_featdata);
                
                index_online_fft = [1:nWinsize]+ is_mainsyl_detect(mm)*handles.pm.ana_hopSize/handles.pm.decimation-nWinsize+1;
                %                 fprintf('Found main target at index = [%d %d] (%d/%d in feature)\n',...
                %                     index_online_fft(1),index_online_fft(end),...
                %                     is_mainsyl_detect(mm),length(is_mainsyl_detect));
                
                if any(index_online_fft<1),
                    mictmp = [sound_snippets_from_last_scope;x0(1:nWinsize,1)];
                    index_online_fft = index_online_fft + nWinsize;
                    mictmp = mictmp(index_online_fft);
                else
                    mictmp=x0(index_online_fft,1);
                end
                J1=fft(mictmp.*Ec,nFFT);
                J2=fft(mictmp.*Es,nFFT);
                
                m_powSpec=real(J1.*conj(J1)+(J2.*conj(J2)));
                m_powSpec=m_powSpec(plot_findex);
                obj.spec=   [obj.spec, m_powSpec(:)];
            end
            if ~isempty(mm)
                %              online_speccorr
                SpectrumFilterDesign_001('pb_get_spec_Callback',...
                    handles.spectrum_design_handles, eventdata, ...
                    guidata(handles.spectrum_design_handles),obj,...
                    online_speccorr);
            end
        end
        
        
        % Switch to the next scope.
        scNum = 3 - scNum;
        n=n+1;
        
    end
    % Remove the scopes we added.
    remscope(handles.tg,[sdb_sc0_ids]);
else
    %     handles.tg = evalin('base','tg');               % Create an xPC Target Object
    -handles.tg;
end

%
% handles.rec.feature.t=feature_t;
% handles.rec.feature.x=feature;
%
% handles.rec.data.t=data_t;
% handles.rec.data.x=data;

%





% --- Executes during object creation, after setting all properties.
function axes_feature_CreateFcn(hObject, eventdata, handles)
% hObject    handle to axes_feature (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: place code in OpeningFcn to populate axes_feature


% --- Executes during object creation, after setting all properties.
function axes_data_CreateFcn(hObject, eventdata, handles)
% hObject    handle to axes_data (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: place code in OpeningFcn to populate axes_data


% --- Executes on button press in pb_trigger.
function pb_trigger_Callback(hObject, eventdata, handles)
% hObject    handle to pb_trigger (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%  get_param('test_PCI6052E_20120104_01/TriggerButton/TrigVal','Value')

% val=get_param([handles.pm.modelname,'/TriggerButton/TrigVal'],'Value');
% val=evalin('base',val);
% set_param([handles.pm.modelname,'/TriggerButton/TrigVal'],'Value',-val);
id=getparamid(handles.tg,'RealSongControl/TriggerButton/TrigVal','Value');
% TrigVal=evalin('base','TrigVal');
val=getparam(handles.tg,id);
setparam(handles.tg,id,-val);
fprintf('Triggered...\n');


% --- Executes on button press in pb_trigger.
function StimFamilyTrigger_Callback(hObject, eventdata, handles)
% hObject    handle to pb_trigger (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%  get_param('test_PCI6052E_20120104_01/TriggerButton/TrigVal','Value')

% val=get_param([handles.pm.modelname,'/TriggerButton/TrigVal'],'Value');
% val=evalin('base',val);
% set_param([handles.pm.modelname,'/TriggerButton/TrigVal'],'Value',-val);

id=getparamid(handles.tg,'RealSongControl/DSPBlock/StimFamilyTriggerButton/TrigVal','Value');
% TrigVal=evalin('base','TrigVal');
val=getparam(handles.tg,id);
setparam(handles.tg,id,-val);
fprintf('StimFamily Triggered:');


% --- Executes on selection change in popup_targetselection.
function handles=popup_targetselection_Callback(hObject, eventdata, handles)
% hObject    handle to popup_targetselection (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns popup_targetselection contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popup_targetselection
contents = cellstr(get(handles.popup_targetselection,'String'));
handles.pm.target=contents{get(handles.popup_targetselection,'Value')};

guidata(hObject,handles);

% --- Executes during object creation, after setting all properties.
function popup_targetselection_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popup_targetselection (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pb_loadparam.
function handles=pb_loadparam_Callback(hObject, eventdata, handles,varargin)
% hObject    handle to pb_loadparam (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% parameters for the system.

%     load('C:\home\LabVIEW\data\LMANbiProbeImplant\org935m\20111222_saline\presyl_a_svmdata.mat')
%     load('C:\home\LabVIEW\data\LMANbiProbeImplant\juv002m\20120104_withpur899m\pur899m_before_harmonicstack_svmdata.mat')

% load('C:\home\LabVIEW\data\LMANbiProbeImplant\juv002m\20120104_withpur899m\pur899m_before_harmonicstack_svmdata.mat')


if nargin==5
    handles.pm.paramfile=varargin{1};
    handles.pm.param_pathname=varargin{2};
else
    
    try
        [handles.pm.paramfile,handles.pm.param_pathname] = uigetfile({fullfile(handles.pm.param_pathname,'*.mat')}, 'Pick a parameter file');
    catch % In case no wave file is chosen.
        [handles.pm.paramfile,handles.pm.param_pathname] = uigetfile({'*.mat';fullfile(pwd,'param.mat')}, 'Pick a parameter file');
        %             error([mfilename, ': Please chose a .wav file.']);
    end
end

% fprintf('loading %s\n',fullfile(handles.pm.param_pathname,handles.pm.paramfile));
load(fullfile(handles.pm.param_pathname,handles.pm.paramfile),'presyl','mainsyl','pm');
fprintf('This svm data contains %d teacher data\n',length(presyl.sv.Ys));

handles.presyl.amp_thresh=presyl.amp_thresh; %dB
handles.pm.TemplateSampRate=pm.TargetSampRate;

scaling_factor=presyl.template_scaling_factor;
scaling_factor(1)=scaling_factor(1)*pm.nstepsize*1.e3/pm.TargetSampRate;

assignin('base','svmdata',presyl.sv);
assignin('base','scaling_factor',scaling_factor);
assignin('base','mingap',presyl.mingap);
assignin('base','minsyl',presyl.minsyl);
assignin('base','presyl_cntmin',presyl.presyl_cntmin);
assignin('base','max_presyl_cancel_counter',presyl.max_presyl_cancel_counter);
assignin('base','maindetection_startcnt',presyl.maindetection_startcnt);
assignin('base','maindetection_endcnt',presyl.maindetection_endcnt);
assignin('base','max_maindetection_cancel_cnt',presyl.max_maindetection_cancel_cnt);
assignin('base','amp_thresh',presyl.amp_thresh);

% handles=set_presyl_param(hObject,eventdata,handles);
% handles=set_mainsyl_param(hObject,eventdata,handles);

% set mainsyl threshold in case old parameter model was used.
if ~isfield(mainsyl,'maindetection_threshold')
    mainsyl.maindetection_threshold=3;
end
assignin('base','mainsyl',mainsyl);
assignin('base','presyl',presyl);

% assign frequency range to compute mean frequency and entropy.
f=pm.Fsong*((1:pm.nFFT)-1)/pm.nFFT;
findex=find(f>=pm.frange(1)&f<=pm.frange(2));
if isfield(pm,'efrange')
    efrange=pm.efrange;
else
    efrange=[1000 10000];
end
efindex=find(f>=efrange(1)&f<=efrange(2));

pm.cepst_nfft=2048;    % nfft size for cepstrum.

up_pitch= 8000;%
low_pitch=400;%

quefrency = [0:pm.cepst_nfft]'*pm.nFFT/(pm.Fsong*pm.cepst_nfft); % quefrency in [sec].
quefrency_index=find((1./quefrency<up_pitch & 1./quefrency > low_pitch)); % select quefrency in 400 to 8000 Hz range.

% we assign these parameter in base workspace so that my simulink model can
% access to these information.
assignin('base','findex',findex);
assignin('base','efindex',efindex);
assignin('base','quefrency_index',quefrency_index);

handles.pm.findex = findex;
handles.pm.efindex = efindex;
handles.pm.quefrency_index = quefrency_index;
handles.pm.nFFT = pm.nFFT;
handles.pm.frange = pm.frange;


%
handles.pm.MinPauseLength = 0.2; % 200 [ms].
handles.pm.MinSyllableLength=0.01; % 10 [ms].

set(handles.text_paramfile,...
    'String',sprintf('param file: %s',handles.pm.paramfile),...
    'ToolTip',sprintf('param file: %s',handles.pm.paramfile));
guidata(hObject,handles);


% --- Executes on button press in pb_loadsongstim.
function handles=pb_loadsongstim_Callback(hObject, eventdata, handles,varargin)
% hObject    handle to pb_loadsongstim (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% if target PC is running, stop now.
try -handles.tg; catch handles.tg=evalin('base','tg');end
set(handles.pb_start,'Value',0);
% set(handles.pb_start,'Value',0);

if nargin==5
    handles.pm.songstim_file=varargin{1};
    handles.pm.songstim_dir=varargin{2};
else
    
    
    try
        [handles.pm.songstim_file,handles.pm.songstim_dir] = uigetfile({fullfile(handles.pm.songstim_dir,'*.mat')}, 'Pick a songstim file');
    catch % In case no wave file is chosen.
        [handles.pm.songstim_file,handles.pm.songstim_dir] = uigetfile({fullfile(pwd,'*.mat')}, 'Pick a songstim file');
        %             error([mfilename, ': Please chose a .wav file.']);
    end
end
file=fullfile(handles.pm.songstim_dir,handles.pm.songstim_file);
stim=load(file,'stim');

handles.pm.SongStim.Stim=stim.stim;
% stim=stim.stim;

stim_vector_tmp=[];
handles.pm.SongStim.MaxSongLen=0;
handles.pm.SongStim.StartIndices=zeros(1,length(stim));
handles.pm.SongStim.EndIndices  =zeros(1,length(stim));

for ii=1:length(handles.pm.SongStim.Stim)
    handles.pm.SongStim.StartIndices(ii)=1+ length(stim_vector_tmp);
    stim_vector_tmp=[stim_vector_tmp,handles.pm.SongStim.Stim(ii).song];
    handles.pm.SongStim.EndIndices(ii)=length(stim_vector_tmp);
    handles.pm.SongStim.MaxSongLen=max(handles.pm.SongStim.MaxSongLen,length(handles.pm.SongStim.Stim(ii).song));
end
handles.pm.SongStim.Len_StimVals=handles.pm.SongStim.EndIndices(ii);
set(handles.popup_SongStimSelect,'String',{handles.pm.SongStim.Stim.type});
val=get(handles.popup_SongStimSelect,'Value');
if val>=length({handles.pm.SongStim.Stim.type})
    val=1;
end
set(handles.popup_SongStimSelect,'Value',val);
% assignin('base','songdata',stim.stim.song);
handles=upload_songstim_xPC(hObject,eventdata,handles,stim_vector_tmp);
handles=set_songstim_xPC(hObject,eventdata,handles,...
    get(handles.popup_SongStimSelect,'Value'),'RealSong');

set(handles.text_songstimfile,'String',...
    sprintf(':%s',handles.pm.songstim_file));

guidata(hObject,handles);
% assignin('base','handles',handles);


function handles=set_songstim_xPC(hObject,eventdata,handles,Song_ind,opt)

maxcount_id  =getparamid(handles.tg,'RealSongControl/triggered_signal_source_Song/Max_count','Value');
ref_cnt_id   =getparamid(handles.tg,'RealSongControl/triggered_signal_source_Song/Ref','Value');
start_cnt_id =getparamid(handles.tg,'RealSongControl/triggered_signal_source_Song/Start_Cnt','Value');
end_cnt_id   =getparamid(handles.tg,'RealSongControl/triggered_signal_source_Song/End_Cnt','Value');
delay_cnt_id =getparamid(handles.tg,'RealSongControl/triggered_signal_source_Song/Delay','Value');


if  isempty(maxcount_id) || isempty(ref_cnt_id) || isempty(start_cnt_id) || ...
        isempty(end_cnt_id) || isempty(delay_cnt_id)
    errordlg('Wrong paramid path! Otherwise build the model first!');
end

fprintf('%s selected as Song Stimli.\n',handles.pm.SongStim.Stim(Song_ind).type);

% set refractoriness in sample size.
ref=str2double(get(handles.edit_songstim_ref,'String'));
stimL=handles.pm.SongStim.EndIndices(Song_ind)-handles.pm.SongStim.StartIndices(Song_ind)+1;
ref=ceil(ref/1000*handles.pm.SampRate)+stimL;
setparam(handles.tg,ref_cnt_id,ref);

% set MaxCount in sample size.
setparam(handles.tg,maxcount_id,handles.pm.SongStim.Len_StimVals+1);

%set Start_Cnt in sample size
handles.pm.SongStim.StartIndices(Song_ind);
setparam(handles.tg,start_cnt_id,handles.pm.SongStim.StartIndices(Song_ind));

%set End_Cnt in sample size
setparam(handles.tg,end_cnt_id,handles.pm.SongStim.EndIndices(Song_ind));

% The only difference in song stim is delay part.
switch opt
    case 'StimFamily'
           StimFamily=getappdata(handles.tg_OpenStimFamilyManager,'StimFamily');
  
         delay=StimFamily.Song.PreT*1000; % in ms
    case 'RealSong'
        delay=eval(get(handles.edit_songstim_delay,'String')); % in ms
end

delay_cnt=floor(delay/1000*handles.pm.SampRate);
setparam(handles.tg,delay_cnt_id,delay_cnt);

% file=fullfile(handles.pm.songstim_dir,handles.pm.songstim_file);
handles.pm.L_songstim_len_sec=handles.pm.SongStim.Len_StimVals/handles.pm.SampRate;

function handles=upload_songstim_xPC(hObject,eventdata,handles,stim_vector_tmp)

outval_id   =getparamid(handles.tg,'RealSongControl/triggered_signal_source_Song/OutValues_and_zero','Value');
stim_vector=evalin('base','init_stim_vector');
if handles.pm.SongStim.Len_StimVals>length(stim_vector)
    error('The size of stimulation vector (%d) is larger than initial size(%d)!',...
        handles.pm.SongStim.Len_StimVals,length(stim_vector));
else
    % Init vector, length+1 because it added 0 in the simulink code to prevent any DC-shift after stimulation.
    stim_vector=zeros(length(stim_vector)+1,1);
    stim_vector(1:length(stim_vector_tmp))=stim_vector_tmp;
end
setparam(handles.tg,outval_id,stim_vector);

% --- Executes on button press in pb_design_param.
function pb_design_param_Callback(hObject, eventdata, handles)
% hObject    handle to pb_design_param (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Note: TemplateMaker_RTSAC_005 does not use fundamental frequency (FF)
% estimated in YIN algorithm. 
% To use FF, the dimension of the feature space is increased,
% which requires changing the Simulink model.
% Therefore, RealSong_control_013 or higher version uses FF,
% and need to use TemplateMaker_RTSAC_006, 
% but RealSong_control_012 series does not use and 
% need to use TemplateMaker_RTSAC_005. 

 TemplateMaker_RTSAC_006(mfilename,handles.RealSong_figure);

           

function handles=edit_pretrigger_sec_Callback(hObject, eventdata, handles)
% hObject    handle to edit_pretrigger_sec (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_pretrigger_sec as text
%        str2double(get(hObject,'String')) returns contents of edit_pretrigger_sec as a double

handles.pm.PreTrigger_Sec=str2double(get(hObject,'String'));
fprintf('PreTrigger Time is set to %3.3f sec\n',handles.pm.PreTrigger_Sec);
guidata(hObject,handles);

% --- Executes during object creation, after setting all properties.
function edit_pretrigger_sec_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_pretrigger_sec (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% --- Executes on button press in pb_designsong.
function pb_designsong_Callback(hObject, eventdata, handles)
% hObject    handle to pb_designsong (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

songedit_03p2;

function handles=edit_minsounddur2rec_Callback(hObject, eventdata, handles)
% hObject    handle to edit_minsounddur2rec (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_minsounddur2rec as text
%        str2double(get(hObject,'String')) returns contents of edit_minsounddur2rec as a double

% handles.pm.MinTotalRecTime=str2double(get(hObject,'String'));
handles.pm.MinSoundDur2Rec = str2double(get(hObject,'String'));
fprintf('Minimum Sound Duration to record is set to %3.3f sec\n',handles.pm.MinSoundDur2Rec);
guidata(hObject,handles);


% --- Executes during object creation, after setting all properties.
function edit_minsounddur2rec_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_minsounddur2rec (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pb_acquiredata.
function [handles,varargout]=pb_acquiredata_Callback(hObject, eventdata, handles,varargin)
% hObject    handle to pb_acquiredata (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

cbuff=getappdata(handles.gph.fig_hn,'cbuff_handle');
if nargin>=4
    REC_period = varargin{1};
    fprintf('(%1.0fms)\n',REC_period*1000)
    if nargin>=5
        shift_index= varargin{2}-1;
    else
        shift_index= 0;
    end
    
    if nargin>=6
        saveopt=varargin{3};
    else
        saveopt='';
    end
    
    %       fprintf('shift=%2.3f (%d)\n',shift_index/handles.pm.SampRate*handles.pm.decimation,shift_index);
    index = [(floor(-handles.pm.buff_time_nbin*REC_period)+1):0]-shift_index;
    %     index = [(-handles.pm.buff_time_nbin*REC_counter+1):0];
    %     [index(1), index(end)]
    
    cbdata = cbuff.getdata(index);
else
    cbdata = cbuff.getdata;
end

pm=handles.pm;
pm.UI_status=collect_status(hObject,eventdata,handles);

% assignin('base','cbdata',cbdata);
% figure(1);plot(cbdata(:,3));
savename=sprintf('%s%s_%s.mat',...
    strrep(handles.pm.savename,'.mat',''),...
    saveopt,...
    datestr(clock,'yyyy_mm_dd_HHMMSS') );
fprintf('Save file: %s\n',savename);

save(fullfile(handles.pm.save_pathname,savename),'cbdata','pm');


handles=update_dynamic_pulse(hObject,eventdata,handles);

if nargout==2
    varargout{1}=cbdata;
end

% --- Executes during object deletion, before destroying properties.
function uipanel1_DeleteFcn(hObject, eventdata, handles)
% hObject    handle to uipanel1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

pm=handles.pm;
path=which(mfilename);path=strsplit(path,filesep);
path=fullfile(path{1:end-1});
previous_session_data=fullfile(path,[mfilename,'_previous_session_data.mat']);
fprintf('Savind session data in %s\n',previous_session_data)
save(previous_session_data,'pm');


function handles=edit_postsilentrecdur_Callback(hObject, eventdata, handles)
% hObject    handle to edit_postsilentrecdur (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_postsilentrecdur as text
%        str2double(get(hObject,'String')) returns contents of edit_postsilentrecdur as a double


handles.pm.PostSilentRecDur_Sec=str2double(get(hObject,'String'));
fprintf('PostSilentRecDur is set to %3.3f sec\n',handles.pm.PostSilentRecDur_Sec);
guidata(hObject,handles);

% --- Executes during object creation, after setting all properties.
function edit_postsilentrecdur_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_postsilentrecdur (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


function handles=edit_maxrectime_Callback(hObject, eventdata, handles)
% hObject    handle to edit_maxrectime (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_maxrectime as text
%        str2double(get(hObject,'String')) returns contents of edit_maxrectime as a double

handles.pm.MaxRecTime_Sec=str2double(get(hObject,'String'));
fprintf('Max Rec Time (sec) for each save file is set to %3.3f sec\n',handles.pm.MaxRecTime_Sec);
guidata(hObject,handles);

% --- Executes during object creation, after setting all properties.
function edit_maxrectime_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_maxrectime (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


function handles=edit_amp_thresh_Callback(hObject, eventdata, handles,varargin)
% hObject    handle to edit_amp_thresh (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_amp_thresh as text
%        str2double(get(hObject,'String')) returns contents of edit_amp_thresh as a double
if nargin==4
    handles.presyl.amp_thresh=varargin{1};
else
    handles.presyl.amp_thresh=str2double(get(hObject,'String'));
end

fprintf('amp_thresh set to %3.3f sec\n',handles.presyl.amp_thresh);
assignin('base','amp_thresh',handles.presyl.amp_thresh);
set(hObject,'String',num2str(handles.presyl.amp_thresh));

id=getparamid(handles.tg,'RealSongControl/DSPBlock/amp_thresh','Value');
setparam(handles.tg,id,handles.presyl.amp_thresh);

guidata(hObject,handles);

% --- Executes during object creation, after setting all properties.
function edit_amp_thresh_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_amp_thresh (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% --- Executes on button press in pb_designpulse.
function pb_designpulse_Callback(hObject, eventdata, handles)
% hObject    handle to pb_designpulse (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

design_pulse;


% --- Executes on button press in pb_REC.
function pb_REC_Callback(hObject, eventdata, handles)
% hObject    handle to pb_REC (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

val=get(hObject,'Value');
if val==1
    set(hObject,'ForegroundColor',[1 0 0]);
    handles.pm.ContinuousREC=1;
else
    set(hObject,'ForegroundColor',[0 0 0]);
    handles.pm.ContinuousREC=0;
end


guidata(hObject,handles);


% --- Executes on button press in rb_scheduledrec.
function rb_scheduledrec_Callback(hObject, eventdata, handles)
% hObject    handle to rb_scheduledrec (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of rb_scheduledrec


val=get(hObject,'Value');
if val==1
    handles.pm.ScheduleREC=1;
else
    handles.pm.ScheduleREC=0;
end


guidata(hObject,handles);

function edit_scheduledrec_timer_Callback(hObject, eventdata, handles)
% hObject    handle to edit_scheduledrec_timer (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_scheduledrec_timer as text
%        str2double(get(hObject,'String')) returns contents of edit_scheduledrec_timer as a double


% --- Executes during object creation, after setting all properties.
function edit_scheduledrec_timer_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_scheduledrec_timer (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% % --- Executes on button press in tg_tab_RealSong.
% function tg_tab_RealSong_Callback(hObject, eventdata, handles)
% % hObject    handle to tg_tab_RealSong (see GCBO)
% % eventdata  reserved - to be defined in a future version of MATLAB
% % handles    structure with handles and user data (see GUIDATA)
%
%
% % --- Executes on button press in tg_tab_Oscillo.
% function tg_tab_Oscillo_Callback(hObject, eventdata, handles)
% % hObject    handle to tg_tab_Oscillo (see GCBO)
% % eventdata  reserved - to be defined in a future version of MATLAB
% % handles    structure with handles and user data (see GUIDATA)


% --- Executes when selected object is changed in ui_ProgramSelection.
function ui_ProgramSelection_SelectionChangeFcn(hObject, eventdata, handles)
% hObject    handle to the selected object in ui_ProgramSelection
% eventdata  structure with the following fields (see UIBUTTONGROUP)
%	EventName: string 'SelectionChanged' (read only)
%	OldValue: handle of the previously selected object or empty if none was selected
%	NewValue: handle of the currently selected object
% handles    structure with handles and user data (see GUIDATA)


mode=get(get(handles.ui_ProgramSelection,'SelectedObject'),'Tag');

id=getparamid(handles.tg,'ProgramSelectionConstant','Value');

switch mode
    case 'tg_tab_RealSong'
        disp('RealSong_control mode selected.');
        setparam(handles.tg,id,1); % move to program 1 (RealSong)
        msgtxt={'Wait a second',...
            'Transition to RealSong mode',...
            'Just a moment please'};
        
        rand_n=ceil(rand(1)*length(msgtxt)); if rand_n==0, rand_n=1;end
        h = msgbox(msgtxt{rand_n});
        pause(1);
        close(h);
    case 'tg_tab_Oscillo'
        disp('Oscillo mode selected.');
        set(handles.pb_start,'Value',0);
        setparam(handles.tg,id,2);  % move to program 2 (xPC_oscillo)
        handles=DaqOscilloAxoClamp2B_for_xPC_AntidAct3('RealSong_main',handles.RealSong_figure);
        %         DaqOscilloAxoClamp2B_for_xPC('init_params',ho,eventdata,handles);
        assignin('base','handles',handles);
    otherwise
        error('Unknown tag!')
        % Code for when there is no match.
end



function handles=edit_catch_ratio_Callback(hObject, eventdata, handles)
% hObject    handle to edit_catch_ratio (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_catch_ratio as text
%        str2double(get(hObject,'String')) returns contents of edit_catch_ratio as a double


handles.pm.CatchRatio=str2double(get(hObject,'String'));
fprintf('Catch ratio set to %3.3f (0: all stim., 1: all escape)\n',...
    handles.pm.CatchRatio);

id=getparamid(handles.tg,'RealSongControl/DSPBlock/FeatureBasedTrigger/RndCatchMainGateWindow/EnabledCatchSignalBox/CatchRatioConstant','Value');
setparam(handles.tg,id,handles.pm.CatchRatio);
guidata(hObject,handles);

% --- Executes during object creation, after setting all properties.
function edit_catch_ratio_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_catch_ratio (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function handles=edit_songstim_ref_Callback(hObject, eventdata, handles)
% hObject    handle to edit_songstim_ref (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_songstim_ref as text
%        str2double(get(hObject,'String')) returns contents of edit_songstim_ref as a double
ref_cnt_id      =getparamid(handles.tg,'RealSongControl/triggered_signal_source_Song/Ref','Value');

% set refractoriness in sample size.
ref=str2double(get(handles.edit_songstim_ref,'String'));
handles.pm.songstim_ref=ref;
ref=ceil(ref/1000*handles.pm.SampRate)+handles.pm.SongStim.Len_StimVals;

setparam(handles.tg,ref_cnt_id,ref);

fprintf('Song stim refractoriness set to %3.3f(msec)\n',...
    handles.pm.songstim_ref);

guidata(hObject,handles);


% --- Executes during object creation, after setting all properties.
function edit_songstim_ref_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_songstim_ref (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit_pulsestim_ref_Callback(hObject, eventdata, handles)
% hObject    handle to edit_pulsestim_ref (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_pulsestim_ref as text
%        str2double(get(hObject,'String')) returns contents of edit_pulsestim_ref as a double

handles.pm.pulsestim_ref=str2double(get(hObject,'String'));
fprintf('Pulse stim refractoriness set to %3.3f(msec)\n',...
    handles.pm.pulsestim_ref);
%
id=getparamid(handles.tg,'RealSongControl/triggered_dynamic_Pulse/ref','Value');
setparam(handles.tg,id,ceil(handles.pm.pulsestim_ref/1000*handles.pm.SampRate));
guidata(hObject,handles);


% --- Executes during object creation, after setting all properties.
function edit_pulsestim_ref_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_pulsestim_ref (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pb_dynamicpulse.
function handles=pb_dynamicpulse_Callback(hObject, eventdata, handles)
% hObject    handle to pb_dynamicpulse (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

val=get(hObject,'Value');
block_path='RealSongControl/triggered_dynamic_Pulse/gain';
id=getparamid(handles.tg,block_path,'Gain');

% Turn ON/OFF dynamic pulse by changing gain of output.
if (val) % ON
    handles.design_pulse=design_pulse_realsong('RealSong_main',handles.RealSong_figure);
    setparam(handles.tg,id,1); % set to 5V output.
    fprintf('Dynamic Pulse Mode\n');
    set(handles.text_pulsestiminfo,'String','Dynamic Pulse Mode');
else
    handles.design_pulse=design_pulse_realsong('RealSong_main',handles.RealSong_figure);
    fprintf('No Pulse Mode\n');
    set(handles.text_pulsestiminfo,'String','No Pulse');
    setparam(handles.tg,id,0); % set to 0V output.
    
end
handles=update_dynamic_pulse(hObject,eventdata,handles);
guidata(hObject,handles);
% assignin('base','handles',handles);


%--- ask design_pulse_realsong to update pulse parameter in xPC target.
function handles=update_dynamic_pulse(hObject,eventdat,handles)



DynPulseMode=get(handles.pb_dynamicpulse,'Value');

if (DynPulseMode)
    
    [delay,pulse_dur,ipi,burst_dur,amp,ref]=...
        design_pulse_realsong('return_pulse_param',handles.design_pulse,[],guidata(handles.design_pulse));
    
    handles.pm.dynpulse.delay=delay;
    handles.pm.dynpulse.pulse_dur=pulse_dur;
    handles.pm.dynpulse.ipi=ipi;
    handles.pm.dynpulse.burst_dur=burst_dur  ;
    handles.pm.dynpulse.amp=amp  ;
    handles.pm.dynpulse.ref=ref  ;  

else
    handles.pm.dynpulse.delay       =0;
    handles.pm.dynpulse.pulse_dur   =0;
    handles.pm.dynpulse.ipi         =0;
    handles.pm.dynpulse.burst_dur   =0  ;
    handles.pm.dynpulse.amp         =0  ;
    handles.pm.dynpulse.ref         =0  ;
   
end
 %update parameters in xPC.
upload_dynamic_pulse_parameter(handles.pm.dynpulse.delay,...
    handles.pm.dynpulse.pulse_dur,...
    handles.pm.dynpulse.ipi,...
    handles.pm.dynpulse.burst_dur,...
    handles.pm.dynpulse.amp,...
    handles.pm.dynpulse.ref,...
    handles);

function upload_dynamic_pulse_parameter(delay,pulse_dur,ipi,burst_dur,amp,ref,handles)
block_path='RealSongControl/triggered_dynamic_Pulse/';

    fprintf('DynPulse: delay=%3.1fms, pulse_dur=%3.1fms, ISP=%3.1fms, burst_dur=%3.1fms, gain=%3.1fmV, ref=%3.1fms\n',...
        delay,pulse_dur,ipi,burst_dur,amp,ref);
    
    id=getparamid(handles.tg,[block_path,'delay'],'Value');
    setparam(handles.tg,id,ceil(delay*handles.pm.SampRate/1000));
    
    id=getparamid(handles.tg,[block_path,'pulse_dur'],'Value');
    setparam(handles.tg,id,ceil(pulse_dur*handles.pm.SampRate/1000));
    
    id=getparamid(handles.tg,[block_path,'IPI'],'Value');
    setparam(handles.tg,id,ceil(ipi*handles.pm.SampRate/1000));
    
    id=getparamid(handles.tg,[block_path,'burst_dur'],'Value');
    setparam(handles.tg,id,ceil(burst_dur*handles.pm.SampRate/1000));
    
    id=getparamid(handles.tg,[block_path,'gain'],'Gain');
    setparam(handles.tg,id,amp/1000);
    
    id=getparamid(handles.tg,[block_path,'ref'],'Value');
    setparam(handles.tg,id,ceil(ref*handles.pm.SampRate/1000));
    
% --- Executes on button press in tgl_nopretarget.
function handles=tgl_nopretarget_Callback(hObject, eventdata, handles)
% hObject    handle to tgl_nopretarget (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of tgl_nopretarget
param='RealSongControl/DSPBlock/FeatureBasedTrigger/TriggeredSVMPredictor/TrigAllPreTarget_OnOff';

NoPreTarget=get(hObject,'Value');
id=getparamid(handles.tg,param,'Value');

% always trigger pre-target detected signal.
% therefore, always looking for main-target.
if (NoPreTarget)
    fprintf('Turn OFF Pre-target detection. Detect main target features straight ahead.\n')
    handles.pm.NoPreTarget=1;
else % use pre-target.
    fprintf('Turn ON Pre-target detection. Find pre-target, then look for main target features (Default).\n')
    handles.pm.NoPreTarget=0;
end
setparam(handles.tg,id,handles.pm.NoPreTarget);


% --- Executes on button press in tg_burstrigrec.
function handles=tg_burstrigrec_Callback(hObject, eventdata, handles)
% hObject    handle to tg_burstrigrec (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of tg_burstrigrec

val=get(hObject,'Value');
handles.pm.tg_bursttrig=val;

guidata(hObject,handles);



function handles=edit_speakergain_Callback(hObject, eventdata, handles)
% hObject    handle to edit_speakergain (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_speakergain as text
%        str2double(get(hObject,'String')) returns contents of edit_speakergain as a double
% id=getparamid(handles.tg,'RealSongControl/SpeakerOutputGain','gain'

gain_value=str2double(get(hObject,'String'));
id=getparamid(handles.tg,'RealSongControl/SpeakerOutputGain','Gain');
setparam(handles.tg,id,gain_value);
fprintf('Speaker Output gain is set to %d\n',gain_value);

% --- Executes during object creation, after setting all properties.
function edit_speakergain_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_speakergain (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function pathname=return_latest_savedir(hObject,eventdata,handles,varargin)


handles=guidata(hObject);

try
    pathname=handles.pm.save_pathname;
catch
    pathname=handles.pm.param_pathname;
end


function UI_status=collect_status(hObject,eventdata,handles)

UI_names={'edit_speakergain',...
    'edit_catch_ratio',...
    'edit_amp_thresh',...
    'tg_burstrigrec'};


for ii=1:length(UI_names)
    if strncmp(UI_names{ii},'edit',4)
        UI_status.(UI_names{ii})=eval(get(handles.(UI_names{ii}),'String'));
    elseif strncmp(UI_names{ii},'tg',2)
        UI_status.(UI_names{ii})=get(handles.(UI_names{ii}),'Value');
    else
        
    end
end


% --- Executes on button press in tg_use_spectrum_filter.
function tg_use_spectrum_filter_Callback(hObject, eventdata, handles)
% hObject    handle to tg_use_spectrum_filter (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of tg_use_spectrum_filter

block_path='RealSongControl/DSPBlock/FeatureBasedTrigger/Spectrum_based_MainSylDetection/';


% set spectrum based filter.
% 1) The online power spectrum is normalized to have area 1.
% 2) The spectrum filter (weight) is normalized to have area 0, and only takes values
% -1, 0, 1. Therefore, if all the non-zero online power spectrum falls
% in the positive region of filter, the filter-weighted sum of power spectrum
% becomes 1. It only takes the value between -1 to 1.

% The TTL is triggered only when the weighted sum of spectrum exceeds
% a certain threshold, and only when a set of pre-set mainsyl criteria are
% met.

UseSpectrumFilterMode=get(handles.tg_use_spectrum_filter,'Value');

if (UseSpectrumFilterMode)
    
    
    if ~isfield(handles.pm,'SampRate')
        errordlg('Please open sepctrum filter mode after building the model.');
        set(hObject,'Value',0);
        return;
    end
    
    set([handles.text_speccorr,handles.edit_speccorr_threshold],'Enable','on');
    
    
    handles.spectrum_design_handles=SpectrumFilterDesign_001(mfilename,...
        handles.RealSong_figure);
    
    SpectrumFilterDesign_001('set_parameters',...
        handles.spectrum_design_handles,[],guidata(handles.spectrum_design_handles),...
        'edit_samprate',handles.pm.SampRate,...
        'edit_fft_windowsize',handles.pm.nFFT,...
        'edit_frange',handles.pm.frange)
    
    
    handles.pm.target_filter=SpectrumFilterDesign_001('return_spectrum_filter',...
        handles.spectrum_design_handles,eventdata,guidata(handles.spectrum_design_handles));
    
    
else
    
    set([handles.text_speccorr,handles.edit_speccorr_threshold],'Enable','off');
    
end

guidata(hObject,handles);

function out=update_spectrum_filter_parameters(hObject,eventdata,handles,obj)


block_path='RealSongControl/DSPBlock/FeatureBasedTrigger/Spectrum_based_MainSylDetection/';

UseSpectrumFilterMode=get(handles.tg_use_spectrum_filter,'Value');

if (UseSpectrumFilterMode)
    
    %     target_filter=SpectrumFilterDesign_001('return_spectrum_filter',...
    %     handles.spectrum_design_handles,eventdata,guidata(handles.spectrum_design_handles));
    target_filter = obj;
    
    handles.pm.target_filter=target_filter;
    handles.pm.maintarget_spectrum_filter = handles.pm.target_filter.spec;
    
    %update parameters in xPC.
    
    fprintf('Comb filter design: filter band at ');
    fprintf('%d ',handles.pm.target_filter.boundaries);
    fprintf('with +-%d Hz band.\n',handles.pm.target_filter.bandwidth);
    
    handles.pm.Spectrum_Filter_Threshold=eval(get(handles.edit_speccorr_threshold,'String'));
    
    id=getparamid(handles.tg,[block_path,'Spectrum_Filter_Threshold'],'Value');
    current_Spectrum_Filter_Threshold=getparam(handles.tg,id);
    fprintf('SpecCorr Threshold: changed from %f to %f\n',...
        current_Spectrum_Filter_Threshold,handles.pm.Spectrum_Filter_Threshold);
    
    setparam(handles.tg,id,handles.pm.Spectrum_Filter_Threshold);
    
    handles.pm.Spectrum_Filter_Threshold = eval(get(handles.edit_speccorr_threshold,'String'));
    
    id=getparamid(handles.tg,[block_path,'Spectrum_Filter_Constant'],'Value');
    current_Spectrum_Filter=getparam(handles.tg,id);
    setparam(handles.tg,id,handles.pm.maintarget_spectrum_filter);
    
    assignin('base','Spectrum_Filter_Threshold',handles.pm.Spectrum_Filter_Threshold);
    assignin('base','maintarget_spectrum_filter',handles.pm.maintarget_spectrum_filter);
    
    
end
out=1;





function edit_speccorr_threshold_Callback(hObject, eventdata, handles)
% hObject    handle to edit_speccorr_threshold (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_speccorr_threshold as text
%        str2double(get(hObject,'String')) returns contents of edit_speccorr_threshold as a double


% --- Executes during object creation, after setting all properties.
function edit_speccorr_threshold_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_speccorr_threshold (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in rb_stim_and_rec.
function rb_stim_and_rec_Callback(hObject, eventdata, handles)
% hObject    handle to rb_stim_and_rec (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of rb_stim_and_rec


% --- Executes on button press in tg_sonogram_OnOff.
function tg_sonogram_OnOff_Callback(hObject, eventdata, handles)
% hObject    handle to tg_sonogram_OnOff (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of tg_sonogram_OnOff

if get(hObject,'Value')
    
    %    ishandle(handles.axes_data)
    
    sonogram_axes = axes(...
        'Unit',         get(handles.axes_data,'unit'),...
        'Position',     get(handles.axes_data,'position'),...
        'Parent',       get(handles.axes_data,'parent'));
    
    setappdata(handles.gph.fig_hn,'sonogram_axes_handle',sonogram_axes);
    %     getappdata(handles.gph.fig_hn,'sonogram_axes_handle');
    
    if ~isfield(handles.pm,'buff_time_nbin')
        handles=init_rectime_param(handles);
    end
    
    [y,f,t,p]=calc_spectrogram(randn(handles.pm.buff_time_nbin,1),handles);
    h=imagesc(t,f,10*log10(abs(p)));
     colormap revblue;
    set(sonogram_axes,...
        'XTickLabel',       [],...
        'YAxisLocation',    'right',...
        'Color',            'none',...
        'YDir',             'normal');
    
    %     uistack(sonogram_axes,'top');
    %     get(sonogram_axes,'position')
    %     get(handles.axes_data,'position')
    setappdata(handles.gph.fig_hn,'sonogram_plot_handle',h);
    
    set(handles.axes_data,'Color','none');
    
    uistack(handles.axes_data,'top');
    
else
    
    set(handles.axes_data,'Visible','on');
    sonogram_axes=getappdata(handles.gph.fig_hn,'sonogram_axes_handle');
    ishandle(sonogram_axes);
    delete(sonogram_axes);
end


% To use the same parameter to calculate spectrogram, always use this.
function [y,f,t,p]=calc_spectrogram(x,handles)
% handles.pm.SampRate
[y,f,t,p] = spectrogram(x,256,128,1024,handles.pm.SampRate/handles.pm.decimation);




function handles=init_rectime_param(handles)

handles=edit_pretrigger_sec_Callback(handles.edit_pretrigger_sec, [], handles);
handles=edit_postsilentrecdur_Callback(handles.edit_postsilentrecdur, [], handles);
handles=edit_minsounddur2rec_Callback(handles.edit_minsounddur2rec, [], handles);
handles=edit_maxrectime_Callback(handles.edit_maxrectime, [], handles);


buff_time=1; % [sec].
max_rec_time=handles.pm.MaxRecTime_Sec; % [sec].
max_buff_time = max_rec_time+handles.pm.PreTrigger_Sec+handles.pm.PostSilentRecDur_Sec+2*buff_time;
handles.pm.decimation=2;

try
    buff_time_nbin =ceil(buff_time*handles.pm.SampRate/handles.pm.decimation);
    n_buff = ceil(max_buff_time/buff_time);
catch
    handles.pm.SampRate=44100;
    handles.pm.decimation = 2;
    buff_time_nbin =ceil(buff_time*handles.pm.SampRate/handles.pm.decimation);
    n_buff = ceil(max_buff_time/buff_time);
end

handles.pm.buff_time         =buff_time;
handles.pm.buff_time_nbin    =buff_time_nbin;
handles.pm.n_buff            =n_buff;
handles.pm.rec_max_n_buff    =ceil(max_rec_time/buff_time);





% --- Executes on selection change in popup_trigch_selection.
function popup_trigch_selection_Callback(hObject, eventdata, handles)
% hObject    handle to popup_trigch_selection (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns popup_trigch_selection contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popup_trigch_selection

contents = cellstr(get(hObject,'String'));
selected=contents{get(hObject,'Value')};


% --- Executes during object creation, after setting all properties.
function popup_trigch_selection_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popup_trigch_selection (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit_plot_bias_Callback(hObject, eventdata, handles)
% hObject    handle to edit_plot_bias (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_plot_bias as text
%        str2double(get(hObject,'String')) returns contents of edit_plot_bias as a double

value=str2double(get(hObject,'String'));
n=get(handles.popup_rawdata_selection_Callback,'Value');




function edit_trigge_xrange_Callback(hObject, eventdata, handles)
% hObject    handle to edit_trigge_xrange (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_trigge_xrange as text
%        str2double(get(hObject,'String')) returns contents of edit_trigge_xrange as a double


% --- Executes during object creation, after setting all properties.
function edit_trigge_xrange_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_trigge_xrange (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes during object creation, after setting all properties.
function edit_trigch_threshold_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_trigch_threshold (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit_trigch_threshold_Callback(hObject, eventdata, handles)
% hObject    handle to edit_trigch_threshold (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_trigch_threshold as text
%        str2double(get(hObject,'String')) returns contents of edit_trigch_threshold as a double


% --- Executes on button press in tg_dynamic_maintrig.
function tg_dynamic_maintrig_Callback(hObject, eventdata, handles)
% hObject    handle to tg_dynamic_maintrig (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of tg_dynamic_maintrig


% --- Executes on button press in tg_trigoscillo.
function tg_trigoscillo_Callback(hObject, eventdata, handles)
% hObject    handle to tg_trigoscillo (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of tg_trigoscillo

function push_criteria_xPC(hObject,eventdata,handles,varargin)
fprintf('%s received mainsyl criteria.\n',mfilename);
mainsyl=varargin{1};
presyl=varargin{2};

% mainsyl contains...
mainsyl.criteria;
mainsyl.featurename;

%  mainsyl.maindetection_threshold
 id=getparamid(handles.tg,'RealSongControl/DSPBlock/FeatureBasedTrigger/MainSyllableMeetCriteria/MainSylCriteria','Value');
 setparam(handles.tg,id,mainsyl.criteria);
 
 fprintf('==== New mainsyl criteria =====\n')
 for ii=1:length(mainsyl.featurename)
     fprintf('%14s\t: min=%4.1f, max=%4.1f\n',...
         mainsyl.featurename{ii},mainsyl.criteria(ii,1),mainsyl.criteria(ii,2));
 end
 
 
 id=getparamid(handles.tg,'RealSongControl/DSPBlock/FeatureBasedTrigger/RndCatchMainGateWindow/MainTrig_Delay','Value');
  setparam(handles.tg,id,presyl.maindetection_startcnt);
  w= presyl.maindetection_endcnt-presyl.maindetection_startcnt;
 id=getparamid(handles.tg,'RealSongControl/DSPBlock/FeatureBasedTrigger/RndCatchMainGateWindow/MainTrig_Width','Value');
 setparam(handles.tg,id,w);
 
 fprintf('Main target delay      = %4d count\n',presyl.maindetection_startcnt);
 fprintf('Main target gate width = %4d count\n',w);


% --- Executes on button press in tg_Run_StimFamily.
function tg_Run_StimFamily_Callback(hObject, eventdata, handles)
% hObject    handle to tg_Run_StimFamily (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of tg_Run_StimFamily

if get(hObject,'Value')
%     StimFamily=getappdata(handles.tg_OpenStimFamilyManager,'StimFamily');
    StimFamily_handles=getappdata(handles.tg_OpenStimFamilyManager,'StimFamily_handles');
    
    feval(handles.pm.StimFamily_func,...
            'StimFamily_state_Callback',...
            StimFamily_handles,eventdata,guidata(StimFamily_handles),...
            'init_Iteration');
end

set(handles.tg_Pause_StimFamily,'Value',0);
set(handles.pb_Stop_StimFamily,'Value',0);

 disp('Selected "RUN" in StimFamily Mode');

 %  StimFamily_handles=getappdata(handles.tg_OpenStimFamilyManager,'StimFamily_handles');

%  for ii=1:2
%      control_StimFamily(hObject,eventdata,handles,'next_stim',StimFamily_handles);
%      handles.tg.Status
%      pause(0.5);
%      handles.tg.Status
%      pause(0.5);
%  end


% --- Executes on button press in tg_Pause_StimFamily.
function tg_Pause_StimFamily_Callback(hObject, eventdata, handles)
% hObject    handle to tg_Pause_StimFamily (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of tg_Pause_StimFamily\
if get(hObject,'Value')
    set(handles.tg_Run_StimFamily,'Enable','Off');
else
    set(handles.tg_Run_StimFamily,'Enable','On');
end
set(handles.pb_Stop_StimFamily,'Value',0);

% --- Executes on button press in tg_OpenStimFamilyManager.
function tg_OpenStimFamilyManager_Callback(hObject, eventdata, handles)
% hObject    handle to tg_OpenStimFamilyManager (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of tg_OpenStimFamilyManager


 
 
val=get(hObject,'Value');
StimFamilyButton_handles=[handles.tg_Run_StimFamily,handles.tg_Pause_StimFamily,handles.pb_Stop_StimFamily];
if val
    set(StimFamilyButton_handles,'Visible','On');
    fprintf('Opening StimFamily Manager \n');
    StimFamily_handles=guidata(feval(handles.pm.StimFamily_func,mfilename,handles.RealSong_figure));
    StimFamily_handles= StimFamily_handles.figure_StimFamily_Manager;
    
    setappdata(handles.tg_OpenStimFamilyManager,'StimFamily_handles',StimFamily_handles);
    Restore_StimInformation(hObject,eventdata,handles,'store','RealSong');
%     try 
%         Restore_StimInformation(hObject,eventdata,handles,'retrieve', 'StimFamily');
%     end
    
else
    try
    StimFamily_handles=getappdata(handles.tg_OpenStimFamilyManager,'StimFamily_handles');
    close(StimFamily_handles);
    end
    set(StimFamilyButton_handles,'Value',0,'Visible','Off');
     Restore_StimInformation(hObject,eventdata,handles,'store', 'StimFamily');

     Restore_StimInformation(hObject,eventdata,handles,'retrieve','RealSong');
    
end
guidata(hObject,handles);

function Restore_StimInformation(hObject,eventdata,handles,opt,condition)

remember_handle_names={...
    'edit_songstim_ref',    'String';...
    'edit_songstim_delay',  'String';...
    'edit_speakergain',     'String';...
    'popup_SongStimSelect', 'Value'};
 Previous_Setting=getappdata(handles.tg_OpenStimFamilyManager,'Previous_Setting');
      
switch opt
    case 'store'
        for ii=1:size(remember_handle_names,1)
            name    =remember_handle_names{ii,1};
            varname =remember_handle_names{ii,2};
            Previous_Setting.(condition).(name)=get(handles.(name),varname);
        end
        setappdata(handles.tg_OpenStimFamilyManager,'Previous_Setting',Previous_Setting);
        
    case 'retrieve'
        Previous_Setting=getappdata(handles.tg_OpenStimFamilyManager,'Previous_Setting');
        if ~isempty(Previous_Setting)
            for ii=1:size(remember_handle_names,1)
                name    =remember_handle_names{ii,1};
                varname =remember_handle_names{ii,2};
                set(handles.(name),varname,Previous_Setting.(condition).(name));
            end
        end
    otherwise
        error;
end


function [out,varargout]=control_StimFamily(hObject,eventdata,handles,...
    opt,StimFamily_handles,varargin)

SFunc=handles.pm.StimFamily_func;
% opt
% StimFamily_handles is guidata(StimFamily_handles.figure_StimFamily_Manager)
% StimFamily_handles
% guidata(StimFamily_handles)
switch opt
    case 'init'
        %         StimFamily_Manager_001('lb_song_lists_Callback',hObject,eventdata,guidata(hObject))
           
           [StimFamily.Song.PreT,...
            StimFamily.Song.PostT,...
            StimFamilu.Song.SongStimSelection,...
            StimFamily.Song.Dur,...
            StimFamily.Song.DurN,...
            StimFamily.Song.StimNames,...
            StimFamily.Song.StimFileName]=feval(SFunc,...
            'StimFamily_state_Callback',...
            StimFamily_handles,eventdata,guidata(StimFamily_handles),...
            'return_SongStimRecParam');
    
              
           [StimFamily.Pulse.Delay,...
            StimFamily.Pulse.Duration,...
            StimFamily.Pulse.Interval,...
            StimFamily.Pulse.BurstDur,...
            StimFamily.Pulse.StimFormat,...
            StimFamily.Pulse.CurrentInj_schedule]=...
            feval(SFunc,...
            'StimFamily_state_Callback',...
           StimFamily_handles,eventdata,guidata(StimFamily_handles),...
            'return_PulseStimRecParam');
    

            [StimFamily.Param.maxItr,StimFamily.Param.StimInterval] =...
                feval(SFunc,...
             'StimFamily_state_Callback',...
             StimFamily_handles,eventdata,guidata(StimFamily_handles),...
             'init');
   
            
        fprintf('Song:PreT=%3.1f, PostT=%3.1f[sec]\n',...
            StimFamily.Song.PreT,StimFamily.Song.PostT);
         fprintf('Pulse:Delay=%3.1f,Duration=%3.1f,Pulse-Interval=%4.1f[sec],Total Duration=%4.1f[sec]\n',...
            StimFamily.Pulse.Delay,StimFamily.Pulse.Duration,...
            StimFamily.Pulse.Interval,StimFamily.Pulse.BurstDur+StimFamily.Pulse.Delay);
       
        fprintf('CurrentInj=[');fprintf('%3.1f,',StimFamily.Pulse.CurrentInj_schedule);fprintf(']pA.\n');
        
        fprintf('Song={');fprintf('%s,',StimFamily.Song.StimNames{:});fprintf('}\n');
        fprintf('Max Iteration=%d.\n',StimFamily.Param.maxItr);
        fprintf('FileName:%s\n',StimFamily.Song.StimFileName);
%         handles.StimFamily
    
        out=1;
    case 'next_stim'
        out=1;
        StimFamily=getappdata(handles.tg_OpenStimFamilyManager,'StimFamily');
         [I_ind,Song_ind,Iteration,StimInterval]=feval(SFunc,...
            'StimFamily_state_Callback',...
            StimFamily_handles,eventdata,guidata(StimFamily_handles),...
            'next_State');
        
        StimFamily.I_ind=I_ind;
        StimFamily.Song_ind=Song_ind;
        StimFamily.Iteration=Iteration;
        
        saveopt= sprintf('_%1.0fpA_%s',...
            StimFamily.Pulse.CurrentInj_schedule(I_ind),...
            StimFamily.Song.StimNames{Song_ind});
        
        
        if isempty(I_ind) || isempty(Song_ind)
            fprintf('=============== StimFamily done %d trials =============\n',Iteration);         
            set(handles.tg_Run_StimFamily,'Value',0);
            out=0;
            varargout{1}= saveopt;
            varargout{2}=StimInterval;
            return;
        end
        StimFamily.Param.RecIntervalN = ceil(length(StimFamily.Pulse.StimFormat)/handles.pm.decimation);
       
        
        fprintf('=Itr=%d(/%d): I=%4.1fpA(%d/%d), Song=''%s''(%d/%d), RecPeriod=%4.1f ===\n',...
            Iteration,StimFamily.Param.maxItr,...
            StimFamily.Pulse.CurrentInj_schedule(I_ind),I_ind,length(StimFamily.Pulse.CurrentInj_schedule),...
            StimFamily.Song.StimNames{Song_ind},Song_ind,length(StimFamily.Song.StimNames),...
            StimFamily.Param.RecIntervalN/handles.pm.SampRate*handles.pm.decimation);
        
     
        
        
        if isempty(I_ind) || isempty(Song_ind)
            set(handles.tg_Run_StimFamily,'Value',0);
            return;
        end
             
       handles=set_songstim_xPC(hObject,eventdata,handles,Song_ind,'StimFamily');
       
       % input current is 10*Hfactor*nA/V.
       % when Hfactror=0.1,  1V =1nA output.
       outputV=StimFamily.Pulse.CurrentInj_schedule(I_ind)/1000;
    
 
      
       upload_dynamic_pulse_parameter(...
           StimFamily.Pulse.Delay*1000,...       % Delay
            StimFamily.Pulse.Duration*1000,...   % Duration
            StimFamily.Pulse.Interval*1000,...   % Interval
            StimFamily.Pulse.BurstDur*1000,...   % TotalDuration
            outputV,... % Now converted to mV 
            StimFamily.Pulse.BurstDur+0.1,...% Ref,
            handles);
      
        if strncmp(handles.tg.CPUOverload,'detected',4)
            -handles.tg;
            set(handles.pb_start,'Value',0);
            msgbox('CPU Overload detected!');
            return;
        end
        
        varargout{1}= saveopt;
        varargout{2}=StimInterval;
    case 'push_data'
        
        StimFamily=getappdata(handles.tg_OpenStimFamilyManager,'StimFamily');
        if nargin>=6
            vm=varargin{1};
        end
        
        param.I_ind    =StimFamily.I_ind;
        param.Song_ind =StimFamily.Song_ind;
        param.Iteration=StimFamily.Iteration;
%         fprintf('Pushding data to %s\n',SFunc)
        
        feval(SFunc,...
            'push_data_Callback',...
            StimFamily_handles,eventdata,guidata(StimFamily_handles),...
            vm,param);
        
        
    case 'save'
        
    case 'info'
        
    otherwise
end

setappdata(handles.tg_OpenStimFamilyManager,'StimFamily',StimFamily);
% getappdata(handles.tg_OpenStimFamilyManager,'StimFamily');


% --- Executes on button press in pb_Stop_StimFamily.
function pb_Stop_StimFamily_Callback(hObject, eventdata, handles)
% hObject    handle to pb_Stop_StimFamily (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.tg_Run_StimFamily,'Value',0);
set(handles.tg_Pause_StimFamily,'Value',0);


% --- Executes on selection change in popup_SongStimSelect.
function popup_SongStimSelect_Callback(hObject, eventdata, handles)
% hObject    handle to popup_SongStimSelect (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns popup_SongStimSelect contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popup_SongStimSelect

% here, change start_cnt, end_cnt of SongStim, Delayed signal source.
handles=set_songstim_xPC(hObject,eventdata,handles,get(hObject,'Value'),'RealSong');


% --- Executes during object creation, after setting all properties.
function popup_SongStimSelect_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popup_SongStimSelect (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit_songstim_delay_Callback(hObject, eventdata, handles)
% hObject    handle to edit_songstim_delay (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_songstim_delay as text
%        str2double(get(hObject,'String')) returns contents of edit_songstim_delay as a double
delay_cnt_id      =getparamid(handles.tg,'RealSongControl/triggered_signal_source_Song/Delay','Value');
%set Delay_Cnt in sample size
delay_in_ms=eval(get(handles.edit_songstim_delay,'String'));
delay_cnt=floor(delay_in_ms/1000*handles.pm.SampRate);
fprintf('Delay is set to %dms.\n',delay_in_ms);
setparam(handles.tg,delay_cnt_id,delay_cnt);

% --- Executes during object creation, after setting all properties.
function edit_songstim_delay_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_songstim_delay (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
