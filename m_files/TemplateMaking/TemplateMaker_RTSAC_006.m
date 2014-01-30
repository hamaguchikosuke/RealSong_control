function varargout = TemplateMaker_RTSAC_006(varargin)
% TEMPLATEMAKER_RTSAC_006 MATLAB code for TemplateMaker_RTSAC_006.fig
%      TEMPLATEMAKER_RTSAC_006, by itself, creates a new TEMPLATEMAKER_RTSAC_006 or raises the existing
%      singleton*.
%
%      H = TEMPLATEMAKER_RTSAC_006 returns the handle to a new TEMPLATEMAKER_RTSAC_006 or the handle to
%      the existing singleton*.
%
%      TEMPLATEMAKER_RTSAC_006('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in TEMPLATEMAKER_RTSAC_006.M with the given input arguments.
%
%      TEMPLATEMAKER_RTSAC_006('Property','Value',...) creates a new TEMPLATEMAKER_RTSAC_006 or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before TemplateMaker_RTSAC_006_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to TemplateMaker_RTSAC_006_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES
% 

% ver.003: FM value is deleted from feature estimation because of 
% unknown discrepancy between simulink and MATLAB code. 
% 01/06/2012
% 
% 

% Edit the above text to modify the response to help TemplateMaker_RTSAC_006

% Last Modified by GUIDE v2.5 05-Dec-2013 10:22:45

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
    'gui_Singleton',  gui_Singleton, ...
    'gui_OpeningFcn', @TemplateMaker_RTSAC_006_OpeningFcn, ...
    'gui_OutputFcn',  @TemplateMaker_RTSAC_006_OutputFcn, ...
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


% --- Executes just before TemplateMaker_RTSAC_006 is made visible.
function TemplateMaker_RTSAC_006_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to TemplateMaker_RTSAC_006 (see VARARGIN)

% Choose default command line output for TemplateMaker_RTSAC_006
handles.output = hObject;

if nargin>=4
    handles.parent_mfile=varargin{1};
    handles.ParentGUI = varargin{2};
    fprintf('Called by %s.\n',handles.parent_mfile);
else
    handles.parent_mfile=[];
    handles.ParentGUI = [];
    disp('Standalone mode');
end


% Update handles structure
guidata(hObject, handles);

% init parameters
handles.pm.nWinsize=256;
handles.pm.nFFT=1024;
handles.pm.nstepsize=44;
handles.pm.nOverlap = handles.pm.nWinsize-handles.pm.nstepsize;


handles.presyl.feature_names={...
    'amplitude',...
    'entropy',...
    'meanfreq',...
    'FM',...
    'AM',...
    'pitch',...
    'pitchgoodness',...
    'precisepitch',...
    'FF',...
    'Predictor',...
    'MainSylGate',...
    'vm'};

handles.presyl.teacher_feature_names={...
    'entropy',...`
    'meanfreq',...
    'FM',...
    'pitch',...
    'pitchgoodness'};

handles.mainsyl_criteria.feature_names={...
    'amplitude',...
    'entropy',...
    'meanfreq',...
    'FM',...
    'pitch',...
    'pitchgoodness',...
    'precisepitch',...
    'FF'};

 
 handles.presyl.template_scaling_factor=[...
                50,... % duration
                0.33,...  % Entropy
                385,... % MeanFreq
                8,...  % FM
                265,...  % Pitch
                10,...   % Pitchgoodness
                0.1,...  % Var Entropy
                4.e5,... % Var MeanFreq
                108,...  % Var FM
                5.e5,...  % Var Pitch
                2.e2];   % Var Pitchgoodness
            % empirically derived scaling factor so that syllable feature
            % distribution becomes close to spheric.
                


handles.presyl.TargetCode{1,1}=[1 0 0];
handles.presyl.TargetCode{1,2}='o';
handles.presyl.TargetCode{1,3}='target';

handles.presyl.TargetCode{2,1}=[0 1 0];
handles.presyl.TargetCode{2,2}='?';
handles.presyl.TargetCode{2,3}='unknown';

handles.presyl.TargetCode{3,1}=[0 0 1];
handles.presyl.TargetCode{3,2}='x';
handles.presyl.TargetCode{3,3}='Non-target';


handles.presyl.amp_thresh=str2double(get(handles.edit_ampthresh,'String'));
% pb_resettemplate_Callback(hObject, eventdata, handles);
handles.presyl.use_filenames=cell(1);
handles.presyl.target_data=[];
handles.presyl.nontarget_data=[];
handles=edit_targetsamplingrate_Callback(handles.edit_targetsamplingrate, eventdata, handles);
handles=ui_pretrigmode_selection_SelectionChangeFcn(hObject, eventdata, handles);

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes TemplateMaker_RTSAC_006 wait for user response (see UIRESUME)
% uiwait(handles.figure_TemplateMaker);


% --- Outputs from this function are returned to the command line.
function varargout = TemplateMaker_RTSAC_006_OutputFcn(hObject, eventdata, handles)
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on slider movement.
function slider1_Callback(hObject, eventdata, handles)
% hObject    handle to slider1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function slider1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes during object creation, after setting all properties.
function spectrum_axes_CreateFcn(hObject, eventdata, handles)
% hObject    handle to spectrum_axes (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: place code in OpeningFcn to populate spectrum_axes



% --- Executes on button press in pb_loadsong.
function pb_loadsong_Callback(hObject, eventdata, handles,varargin)
% hObject    handle to pb_loadsong (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

try delete(handles.gph.predicted_bars); end;
try delete(handles.gph.predicted_bar_num);end
try delete(handles.gph.mainsyl_bars);end;
try delete(handles.main_sylcriteria.spectcorr_plot);end

if nargin==5
    handles.pm.filename=varargin{2};
    handles.pm.sound_dir=varargin{1};
else
    
    try
        [handles.pm.filename,handles.pm.sound_dir] = uigetfile({'*.wav';fullfile(handles.pm.sound_dir,handles.pm.filename)}, 'Pick a song (.wav) file');
    catch % In case no wave file is chosen.
        [handles.pm.filename,handles.pm.sound_dir] = uigetfile('*.wav', 'Pick a song (.wav) file');
        %             error([mfilename, ': Please chose a .wav file.']);
    end
end

switch handles.pm.data_type
    case 'wav'
        try
            [handles.pm.song,Fsong]=wavread(fullfile(handles.pm.sound_dir,handles.pm.filename));
        catch
            original=fullfile(handles.pm.sound_dir,handles.pm.filename);
            backupfile=fullfile(handles.pm.sound_dir,'tmp.wav');
            copyfile(original,backupfile);
            try
                wavchunksizefix(fullfile(handles.pm.sound_dir,handles.pm.filename));
                [handles.pm.song,Fsong]=wavread(fullfile(handles.pm.sound_dir,handles.pm.filename));
                
            catch
                copyfile(backupfile,original);
                error('Failed to read/convert wave file');
            end
        end
    case 'realsong'
            rsd=realsong_dataclass(fullfile(handles.pm.sound_dir,handles.pm.filename)); 
            handles.pm.song =rsd.mic;
            Fsong           =rsd.Fs; 
            handles.pm.rsd  =rsd;
            
    otherwise
        error('Unknown data type! (%s)',handles.pm.data_type);
end


%
% if ~isfield(handles.pm,'Fsong')
%     handles.pm.Fsong=Fsong;
% end

% I remove this because RealSong_control does not use filter. 
 [B,A] = ellip(4,.1,50,[400/(Fsong/2) .99]);
 handles.pm.song=filtfilt(B,A,handles.pm.song);
 
if round(handles.pm.TargetSampRate)~=round(Fsong)
    fprintf('Resampling from %d to %d\n',Fsong,handles.pm.TargetSampRate);
    handles.pm.song=resample(handles.pm.song,handles.pm.TargetSampRate,Fsong);
end
handles.pm.Fsong=handles.pm.TargetSampRate;


set(handles.text_wavsamprate,'String',sprintf('Original Samp Rate: %d',Fsong));
handles=set_presyl_template_parameters(hObject,eventdata,handles);
handles=calc_spectrum_features(hObject,eventdata,handles);

set(gcf,'Name',sprintf('%s:%s',mfilename,handles.pm.filename));
guidata(hObject,handles);


% --- Executes on button press in pb_traintemplate.
function pb_traintemplate_Callback(hObject, eventdata, handles)
% hObject    handle to pb_traintemplate (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

handles= update_target_vector(hObject,eventdata,handles);
% ishandle(handles.gph.predicted_bars)

ntarget=size(handles.presyl.target_data,2);
nnontarget=size(handles.presyl.nontarget_data,2);
fprintf('Ntarget=%d, Nnontarget=%d\n',ntarget,nnontarget);

train_label=[ones(ntarget,1);-ones(nnontarget,1)];

Y=train_label;
X=[handles.presyl.target_data,handles.presyl.nontarget_data];
% size(X)
% size(Y)
sigma2=1/2;
handles.presyl.sv=my_trainsvm(X,Y,sigma2);
guidata(hObject,handles);


function handles=update_target_vector(hObject,eventdata,handles)
    
    if isempty(strmatch(handles.pm.filename,strvcat(handles.presyl.use_filenames{:}),'exact'))
        handles.presyl.use_filenames={handles.presyl.use_filenames{:},handles.pm.filename};
    else
        disp('this file has already used')
        return;
    end
    
    handles=get_target_vector(hObject,eventdata,handles);
    handles=get_nontarget_vector(hObject,eventdata,handles);
   
        % --- Executes on button press in pb_predicttemplate.

function handles=get_target_vector(hObject,eventdata,handles)
        
        start_ind=handles.pm.feature2.start_ind(find(handles.presyl.current_target_id>0));
        end_ind=handles.pm.feature2.end_ind(find(handles.presyl.current_target_id>0));
        index=end_ind-1;
        
        tmp_features=handles.pm.feature2.meanvar_features(:,index);
        duration=1.e3*handles.pm.feature2.counter(index-1)*handles.pm.nstepsize/handles.pm.Fsong;
        tmp_features=[duration(:)';tmp_features]; % add counter on top.
        tmp_features=tmp_features./repmat(handles.presyl.template_scaling_factor(:),1,size(tmp_features,2));
        handles.presyl.target_data= ...
            [handles.presyl.target_data,tmp_features];
        
function handles=get_nontarget_vector(hObject,eventdata,handles)

start_ind=handles.pm.feature2.start_ind(find(handles.presyl.current_target_id<0));
end_ind=handles.pm.feature2.end_ind(find(handles.presyl.current_target_id<0));
index=end_ind-1;

tmp_features=handles.pm.feature2.meanvar_features(:,index);
duration=1.e3*handles.pm.feature2.counter(index-1)*handles.pm.nstepsize/handles.pm.Fsong;
tmp_features=[duration(:)';tmp_features]; % add counter on top.
tmp_features=tmp_features./repmat(handles.presyl.template_scaling_factor(:),1,size(tmp_features,2));
handles.presyl.nontarget_data= ...
    [handles.presyl.nontarget_data,tmp_features];


            

% --- Executes on button press in pb_predicttemplate.
function pb_predicttemplate_Callback(hObject, eventdata, handles)
        % hObject    handle to pb_predicttemplate (see GCBO)
        % eventdata  reserved - to be defined in a future version of MATLAB
        % handles    structure with handles and user data (see GUIDATA)

%         handles=update_figures(hObject,eventdata,handles);
        
        
        %         size(handles.pm.feature2.counter)
        %         size(handles.pm.feature2.meanvar_features)
        duration=1.e3*handles.pm.feature2.counter*handles.pm.nstepsize/handles.pm.Fsong;
        % tmp_features=[duration(:)';tmp_features]; % add counter on top.
        tmp_features=[duration(:)';handles.pm.feature2.meanvar_features];
        x=tmp_features./repmat(handles.presyl.template_scaling_factor(:),1,size(tmp_features,2));
        
        [g_predict,b] = my_predictsvm(handles.presyl.sv, x);
        
        handles.prediction.g_predict=g_predict;
        handles.prediction.b=b;
        
        
        predicted_index=(g_predict-b>0);
        %         plot(handles.pm.feature2.t,predicted_index*max(ylim),'g');
        axes(handles.gph.template_mtf_axes);
        try delete(handles.gph.predicted_lines); end;
        
        if ishandle(handles.gph.predicted_lines)
%             disp('setting prediction lines...')
        set(handles.gph.predicted_lines,'XData',handles.pm.feature2.t,...
            'YData',predicted_index*max(ylim));
        else
%             disp('plotting prediction lines...')
            axes(handles.gph.template_mtf_axes);
            handles.gph.predicted_lines              =...
                plot(handles.pm.feature2.t,predicted_index*max(ylim)*0.99,...
                'Color',[0 1 0],'LineWidth',1);

        end
       
       % Now, count the number of time points 
       % that is predicted as pre-syllable".
       start_ind=handles.pm.feature2.start_ind;
       end_ind=handles.pm.feature2.end_ind-1;
        
       max_detection_count=zeros(length(start_ind),1);
       cancel_counter=zeros(length(start_ind),1);
       for ii=1:length(start_ind)
           tmp=0;
           for jj=start_ind(ii):(end_ind(ii)-1)
               if predicted_index(jj)>0
                   tmp=tmp+1;
                   cancel_counter(ii)=0;
               else
                   max_detection_count(ii)=max(max_detection_count(ii),tmp);
                   tmp=0;
                   cancel_counter(ii)=cancel_counter(ii)+1;
               end
           end
            max_detection_count(ii)=max(max_detection_count(ii),tmp);
       end
       
%        cancel_counter
%        max_detection_count
%        detected=find(predicted_index(end_ind)>0);

       detected=find(max_detection_count>handles.presyl.presyl_cntmin);
%        max_detection_count
%        cancel_counter
%        detected
%        cancel_counter(detected)
       detected=detected(cancel_counter(detected)<handles.presyl.max_presyl_cancel_counter);
       handles.presyl.detected=detected;
       
       axes(handles.gph.template_mtf_axes);
      
       try for ii=1:length(handles.gph.predicted_bars),delete(handles.gph.predicted_bars(ii)); end;end;
       try for ii=1:length(handles.gph.predicted_bar_num), delete(handles.gph.predicted_bar_num(ii));end;end
       try for ii=1:length(handles.gph.mainsyl_bars), delete(handles.gph.mainsyl_bars(ii));end;end
       try for ii=1:length(handles.main_sylcriteria.hit_plot), delete(handles.main_sylcriteria.hit_plot);end;end
       
       handles.gph.predicted_bars=zeros(1,length(detected));
       handles.gph.predicted_bar_num=zeros(1,length(detected));
       handles.gph.predicted_mainsyl_bars=zeros(1,length(detected));
       
       
       for ii=1:length(detected)
           tt=handles.pm.feature2.t([start_ind(detected(ii));end_ind(detected(ii))]);
           handles.gph.predicted_bars(ii)=...
               line(tt,[0;0],'Color',[1 0 0],'LineWidth',10);
           handles.gph.predicted_bar_num(ii)=text(mean(tt),0,sprintf('%d',max_detection_count(detected(ii))));
       end
       
       [index,tt]=get_mainsyl_detection_index(handles);
        handles.gph.predicted_bars=zeros(1,length(detected));
      
       for ii=1:length(detected)
           handles.gph.mainsyl_bars(ii)=...
               line(tt(ii,:),[0;0],'Color',[0 0 1],'LineWidth',10);
       end
       
%        assignin('base','handles',handles);   
       guidata(hObject,handles);
         
function [ind,tt]=get_mainsyl_detection_index(handles) 

start_ind=handles.pm.feature2.start_ind;
end_ind=handles.pm.feature2.end_ind;
if isempty(start_ind)
    errordlg('Predict pre-syllable detection first!');
end
detected=handles.presyl.detected;
main_start_end=[handles.presyl.maindetection_startcnt,handles.presyl.maindetection_endcnt];
timemode=get(handles.popup_maindetection_time_mode,'Value');

ind     =zeros(length(detected),2);
tt      =zeros(length(detected),2);

for ii=1:length(detected)
     
    if timemode==6 % relative to the end of pre-syllable
        ind(ii,:)=end_ind(detected(ii))+main_start_end;
        tt(ii,:)=handles.pm.feature2.t(ind(ii,:));
    elseif timemode<6
        
        
        if (detected(ii)+timemode)>length(start_ind)
            tt(ii,:)=[NaN,NaN];
            ind(ii,:)=[NaN];
        elseif (start_ind(detected(ii)+timemode)-end_ind(detected(ii))>handles.presyl.max_maindetection_cancel_cnt)
            tt(ii,:)=[NaN,NaN];
            ind(ii,:)=[NaN];
        else
            ind(ii,:)=start_ind(detected(ii)+timemode)+main_start_end;
            tt(ii,:)=handles.pm.feature2.t(ind(ii,:));
        end
    end
end
        
% --- Executes on button press in pb_resettemplate.
function pb_resettemplate_Callback(hObject, eventdata, handles)
% hObject    handle to pb_resettemplate (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

handles.presyl.use_filenames=cell(1);
handles.presyl.target_data=[];
handles.presyl.nontarget_data=[];
fprintf('Template reset.\n')
guidata(hObject,handles);

% --- Executes on button press in pb_savetemplate.
function pb_savetemplate_Callback(hObject, eventdata, handles)
% hObject    handle to pb_savetemplate (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
 
% sv=handles.presyl.sv;
% scaling_factor=handles.presyl.template_scaling_factor;

try
    [handles.pm.svmdata_name, handles.pm.svmdata_dir] = uiputfile('*.mat', 'Save pre-syllable detection svm file as',...
        fullfile(handles.pm.svmdata_dir,handles.pm.svmdata_name));
catch % In case no wave file is chosen.
    [handles.pm.svmdata_name, handles.pm.svmdata_dir] = uiputfile('*.mat', 'Save pre-syllable detection svm file as',...
        fullfile(handles.pm.sound_dir,'svmdata.mat'));
end

presyl  =handles.presyl;
pm      =handles.pm;

mainsyl.criteria=get(handles.uitable_mainsyl_criteria, 'Data');
mainsyl.criteria=mainsyl.criteria(:,[1,2]);
mainsyl.criteria=cell2mat(mainsyl.criteria);

if get(handles.tg_OpenSpectrumTargetMode,'Value')
    mainsyl.comb_filter=handles.pm.target_filter;
end


mainsyl.featurename=get(handles.uitable_mainsyl_criteria, 'RowName');
mainsyl.maindetection_threshold=handles.mainsyl.maindetection_threshold;
save(fullfile(handles.pm.svmdata_dir, handles.pm.svmdata_name),'presyl','pm','mainsyl');
guidata(hObject,handles);



% --- Executes on button press in pb_play.
function pb_play_Callback(hObject, eventdata, handles)
% hObject    handle to pb_play (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

tt=get(handles.spectrum_axes,'XLim');
tti=ceil(tt*handles.pm.Fsong)+1;

tti(1)=max(1,tti(1));  % start index > 1.
tti(2)=min(length(handles.pm.song),tti(2)); % end index < length(song)

% sound(ss.song(tti(1):tti(2)),ss.F);

sound(handles.pm.song(tti(1):tti(2))/(8*std(handles.pm.song)),handles.pm.Fsong);

function handles=edit_targetsamplingrate_Callback(hObject, eventdata, handles)
% hObject    handle to edit_targetsamplingrate (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_targetsamplingrate as text
%        str2double(get(hObject,'String')) returns contents of edit_targetsamplingrate as a double

handles.pm.TargetSampRate=str2double(get(hObject,'String'));

fprintf('Target Sampling Rate is %d\n',handles.pm.TargetSampRate);
guidata(hObject, handles);


% --- Executes during object creation, after setting all properties.
function edit_targetsamplingrate_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_targetsamplingrate (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

handles.pm.TargetSampRate=str2double(get(hObject,'String'));
guidata(hObject, handles);

function handles=init_feature_plots(hObject, eventdata, handles)
%
handles=init_template_figure_plot(handles);
handles=init_feature_figure_plot(handles);

function handles=init_feature_figure_plot(handles)
postmp=get(handles.spectrum_axes,'Position');
parn=get(handles.spectrum_axes,'Parent');
unit=get(handles.spectrum_axes,'Unit');

handles.feature_axes=axes('Parent',parn,'Unit',unit,'Position',postmp);

try
    h=getappdata(handles.feature_axes,'feature_plot_handle');
    delete(h);
end

handles.gph.template_feature_plots=[];
for ii=1:length(handles.presyl.feature_names)+1
    handles.gph.template_feature_plots(ii)=plot(NaN,NaN,'.');hold on;
end
set(handles.feature_axes,...
        'XTickLabel',       [],...
        'YAxisLocation',    'right',...
        'Color',            'none',...
        'YDir',             'normal');

setappdata(handles.feature_axes,'feature_plot_handle',handles.gph.template_feature_plots);
  
% linkaxes([handles.feature_axes,handles.spectrum_axes],'xy');

function handles=init_template_figure_plot(handles)
%set(handles.spectrum_axes,'Visible','off');
postmp=get(handles.spectrum_axes,'Position');
parn=get(handles.spectrum_axes,'Parent');
unit=get(handles.spectrum_axes,'Unit');

handles.gph.template_mtf_axes=axes('Unit',unit,'Parent',parn,'Position',postmp);

handles.gph.predicted_lines              =plot(NaN,NaN,'Color',[0 1 0],'LineWidth',2);hold on;
handles.gph.template_feature.mtf_region  = patch(0,0,'r');
set(handles.gph.template_mtf_axes,...
    'Color','none',...
    'XTickLabel',[],...
    'YTickLabel',[]);

% linkaxes([handles.feature_axes,handles.spectrum_axes],'xy');


function handles=calc_spectrum_features(hObject,eventdata,handles)


nWinsize=handles.pm.nWinsize;
nFFT=handles.pm.nFFT;
if handles.pm.Fsong==44100
    nstepsize=handles.pm.nstepsize;
elseif handles.pm.Fsong==22050
    nstepsize=handles.pm.nstepsize/2;
else
    error('Unknown sampling rate.')
end
nOverlap=handles.pm.nOverlap;

nsteps=floor((length(handles.pm.song)-nWinsize)/nstepsize)+1;

% handles.pm.feature2.t=[nWinsize/2:nOverlap:(nWinsize+(nsteps-1)*nOverlap)]/handles.pm.Fsong;
f=handles.pm.Fsong*((1:nFFT)-1)/nFFT;
handles.pm.frange=[400,10000];
handles.pm.findex=find(f>=handles.pm.frange(1)&f<=handles.pm.frange(2));
handles.pm.feature2.f=f(handles.pm.findex);

handles.pm.efrange=[1000,10000];
handles.pm.efindex=find(f>=handles.pm.frange(1)&f<=handles.pm.frange(2));


handles.pm.feature2.m_spec_deriv=zeros(length(handles.pm.findex),nsteps);
handles.pm.feature2.m_powSpec=zeros(length(handles.pm.findex),nsteps);
handles.pm.feature2.amplitude  = zeros(1,nsteps);
handles.pm.feature2.entropy    = zeros(1,nsteps);
handles.pm.feature2.FM         = zeros(1,nsteps);
handles.pm.feature2.AM         = zeros(1,nsteps);
handles.pm.feature2.meanfreq   = zeros(1,nsteps);
handles.pm.feature2.pitch      = zeros(1,nsteps);
handles.pm.feature2.pitchgoodness=zeros(1,nsteps);
handles.pm.feature2.precisepitch=zeros(1,nsteps);
handles.pm.feature2.t          =zeros(1,nsteps);
handles.pm.feature2.m_time_deriv_max=zeros(1,nsteps);
handles.pm.feature2.m_freq_deriv_max=zeros(1,nsteps);

[E2,V] = dpss(nWinsize,4,2);
Ec=E2(:,1);
Es=E2(:,2);

calc_precise_pitch=1;
param.up_pitch= 8000;% 
param.low_pitch=400;%

param.cepst_nfft=2048;         % nfft size for cepstrum;
quefrency = [0:param.cepst_nfft]*nFFT/(handles.pm.Fsong*param.cepst_nfft); % quefrency in [sec].
param.quefrency_select=((1./quefrency)<param.up_pitch & (1./quefrency) > param.low_pitch); % select quefrency in 400 to 8000 Hz range.

param.f         =f;
param.findex    =handles.pm.findex;
param.efindex   =handles.pm.efindex;

for ii=1:nsteps
    index=[1:nWinsize]+nstepsize*(ii-1);
    handles.pm.feature2.t(ii)=(nstepsize*(ii-1)+nWinsize/2)/handles.pm.Fsong;
    J1=fft(handles.pm.song(index).*Ec,nFFT);
    J2=fft(handles.pm.song(index).*Es,nFFT);
    
%     test_plot_t=2.19;
    test_plot_t=inf;
    dt=nstepsize/handles.pm.Fsong;
    tnow=index(1)/handles.pm.Fsong ;
    
    if (tnow>test_plot_t)&(tnow<test_plot_t+dt)
        test_plot=1;
    else
        test_plot=0;
    end
    
    [  handles.pm.feature2.m_spec_deriv(:,ii),...
        handles.pm.feature2.amplitude(ii),...
        handles.pm.feature2.entropy(ii),...
        handles.pm.feature2.FM(ii),...
        handles.pm.feature2.AM(ii),...
        handles.pm.feature2.meanfreq(ii),...
        handles.pm.feature2.pitch(ii),...
        handles.pm.feature2.pitchgoodness(ii),...
        handles.pm.feature2.precisepitch(ii),...
        handles.pm.feature2.m_time_deriv_max(ii),...
        handles.pm.feature2.m_freq_deriv_max(ii),...
        handles.pm.feature2.m_powSpec(:,ii)] = ...
        multitaper_feature_RTSAC3(J1(:),J2(:),...
        1/handles.pm.Fsong,nFFT,...
        param,...
        calc_precise_pitch, test_plot);
    
end
 [FF,t]=YIN_FF_estimator(handles.pm.song,handles.pm.Fsong,...
     4,2,handles.pm.feature2.t,0.1,'forward',-1);
handles.pm.feature2.FF=FF;

max_spec=max(handles.pm.feature2.m_spec_deriv(:));
min_spec=min(handles.pm.feature2.m_spec_deriv(:));
% cutoff=0.001;


axes(handles.spectrum_axes);cla;
% imagesc(handles.pm.feature2.t,...
%     handles.pm.feature2.f,...
%     handles.pm.feature2.m_spec_deriv,);
surf(handles.pm.feature2.t,...
    handles.pm.feature2.f,...
    handles.pm.feature2.m_spec_deriv,'EdgeColor','none');
caxis(handles.spectrum_axes,handles.caxis_cutoff*[-max_spec, max_spec]);
axis xy; axis tight;view(0,90);
colormap bone;
axis([0,handles.pm.feature2.t(end),0,handles.pm.frange(end)]);
set(handles.spectrum_axes,'YDir','Normal');

switch handles.pm.pretrig_mode
    case 'pb_pretrig_timeaverage_mode'
        handles=running_mean_var_of_features_fixed_duration(hObject,eventdata,handles);   
    case 'pb_pretrig_soundamp_mode'
        handles=running_mean_var_of_features(hObject,eventdata,handles);
    otherwise
end
% assignin('base','handles',handles)
handles=update_figures(hObject,eventdata,handles);

guidata(hObject,handles);

function out = calc_spectcorr(m_powSpec,target_filter)
% Calculate convolution of m_poweSpec and target_filter
if length(target_filter)~=size(m_powSpec,1)
    error('The size of filter (%d) and spectrum (%d) does not match!',...
         length(target_filter),size(m_powSpec,1));
end

out = sum(m_powSpec./repmat(sum(m_powSpec,1),size(m_powSpec,1),1).*repmat(target_filter(:),1,size(m_powSpec,2)),1);

function handles=update_figures(hObject,eventdata,handles)

handles=init_feature_plots(hObject, eventdata, handles);
linkaxes([handles.spectrum_axes,...
    handles.data_axes,...
    handles.gph.template_mtf_axes,...
    handles.feature_axes],'x');
handles=redraw_syllable_detection_boundaries(hObject,eventdata,handles);
handles=pb_set_unknown_Callback(handles.pb_set_unknown, eventdata, handles);

function handles=running_mean_var_of_features(hObject,eventdata,handles);
try 
    features=handles.pm.feature2;
catch
    error('Load data first!');
end
minbase=min(features.amplitude);
maxbase=max(features.amplitude);

handles.presyl.aboveind=(features.amplitude>handles.presyl.amp_thresh);
%
handles.presyl.mingap=2; % gap larger than 2 is considered as gap or silent region.
handles.presyl.minsyl=6;

counter=zeros(length(features.t),1);
% init mean and the variance variables
gap_counter=inf;
syllable_counter=0;
x=zeros(length(handles.presyl.teacher_feature_names),1);
iterative_mean_var(x,'init');


out=zeros(2*length(handles.presyl.teacher_feature_names),length(counter));
up_ind=[];
down_ind=[];

for ii=1:length(counter)
   
    if (handles.presyl.aboveind(ii)>0)
        % If above the threshold, start syllable counter.
        syllable_counter=syllable_counter+1;
        gap_counter=0;
    else
        % If below the threshold, reset syllable counter.
        syllable_counter=0;
        gap_counter=gap_counter+1;
    end
%   [syllable_counter,gap_counter]
    
    % If gap_counter is less than minimum gap, consider as above threshold.
%     AboveCond=(handles.presyl.aboveind(ii)>0)||...
%         (gap_counter<handles.presyl.mingap);
 AboveCond=(syllable_counter>=handles.presyl.minsyl)&&...
        (gap_counter<=handles.presyl.mingap);
         
         
    if (AboveCond) 
        counter(ii+1)=counter(ii)+1;
        if counter(ii)==0; % first time to meet AboveCondition. 
            out(:,ii)=iterative_mean_var(0);
            up_ind=[up_ind,ii];
        else
            
            for jj=1:length(handles.presyl.teacher_feature_names)
                try
                    x(jj)=features.(handles.presyl.teacher_feature_names{jj})(ii);
                catch
                    error('%s error',handles.presyl.teacher_feature_names{jj});
                end
            end
            out(:,ii)=iterative_mean_var(x);
        end
    else % 
        out(:,ii)=iterative_mean_var(0);
        counter(ii+1)=0;
        
        if counter(ii)~=0 % first time to miss the AboveCond.
            down_ind=[down_ind,ii];
        end
    end
    
end


counter=counter(1:end-1);


if isempty(up_ind) || isempty(down_ind)
    px=[];
    py=[];
    duration=[];
    fprintf('No motif or syllable detected! (min amp=%g, max amp=%g, thresh=%g)\n',...
        min(features.amplitude),...
        max(features.amplitude),...
        handles.presyl.amp_thresh);
%     fprintf('Temporally set to slightly above minimum amp + 0.1\n');
    
%     return;
elseif length(up_ind)==1 && length(down_ind)==1
    fprintf('Single call detected, or syllable threshold is too small. \n')
    handles.pm.syllable=[];
    if up_ind(1)>down_ind(1)
        fprintf('Detected: up_ind(1)>down_ind(1)\n')
%         return;
    end
end

% data start from above the threshold. This part is neglected.
if up_ind(1)>down_ind(1)
    down_ind = down_ind(2:end);
end

% data end above threshold. This part is neglected.
if up_ind(end)>down_ind(end)
    up_ind= up_ind(1:end-1);
end

handles.pm.feature2.meanvar_features=out;
handles.pm.feature2.counter=counter;
handles.pm.feature2.start_ind=up_ind;
handles.pm.feature2.end_ind=down_ind;

function handles=running_mean_var_of_features_fixed_duration(hObject,eventdata,handles);
try 
    features=handles.pm.feature2;
catch
    error('Load data first!');
end
minbase=min(features.amplitude);
maxbase=max(features.amplitude);

handles.presyl.aboveind=(features.amplitude>handles.presyl.amp_thresh);
%
handles.presyl.mingap=2; % gap larger than 2 is considered as gap or silent region.
handles.presyl.minsyl=6;

counter=zeros(length(features.t),1);
% init mean and the variance variables
gap_counter=inf;
syllable_counter=0;
% iterative_mean_var(x,'init');


up_ind=[];
down_ind=[];

% cb=circbuff(1,handles.presyl.presyl_averaging_val,length(handles.presyl.teacher_ ));

for ii=1:length(counter)
   
    if (handles.presyl.aboveind(ii)>0)
        % If above the threshold, start syllable counter.
        syllable_counter=syllable_counter+1;
        gap_counter=0;
    else
        % If below the threshold, reset syllable counter.
        syllable_counter=0;
        gap_counter=gap_counter+1;
    end
%   [syllable_counter,gap_counter]
    
    % If gap_counter is less than minimum gap, consider as above threshold.
%     AboveCond=(handles.presyl.aboveind(ii)>0)||...
%         (gap_counter<handles.presyl.mingap);
 AboveCond=(syllable_counter>=handles.presyl.minsyl)&&...
        (gap_counter<=handles.presyl.mingap);
         
         
    if (AboveCond) 
        counter(ii+1)=counter(ii)+1;
        if counter(ii)==0; % first time to meet AboveCondition. 
%             out(:,ii)=iterative_mean_var(0);
            up_ind=[up_ind,ii];
        end
    else % 
%         out(:,ii)=iterative_mean_var(0);
        counter(ii+1)=0;
        
        if counter(ii)~=0 % first time to miss the AboveCond.
            down_ind=[down_ind,ii];
        end
    end
   
end

x=zeros(length(handles.presyl.teacher_feature_names),length(features.(handles.presyl.teacher_feature_names{1})));
out=zeros(2*length(handles.presyl.teacher_feature_names),length(counter));


for jj=1:length(handles.presyl.teacher_feature_names)
    try
        x(jj,:)=features.(handles.presyl.teacher_feature_names{jj});
    catch
        error('%s error',handles.presyl.teacher_feature_names{jj});
    end
end

mean_filt=ones(1,handles.presyl.presyl_averaging_val)/handles.presyl.presyl_averaging_val;
meanx=conv2([zeros(size(x,1),handles.presyl.presyl_averaging_val),x],mean_filt,'full');
varx =conv2([zeros(size(x,1),handles.presyl.presyl_averaging_val),x].^2,mean_filt,'full')-meanx;
meanx=meanx(:,handles.presyl.presyl_averaging_val+[1:size(x,2)]);
varx=varx(:,handles.presyl.presyl_averaging_val+[1:size(x,2)]);

% size(x)
% size(meanx)
out=[meanx;varx];
    
counter=counter(1:end-1);


if isempty(up_ind) || isempty(down_ind)
    px=[];
    py=[];
    duration=[];
    fprintf('No motif or syllable detected! (min amp=%g, max amp=%g, thresh=%g)\n',...
        min(features.amplitude),...
        max(features.amplitude),...
        handles.presyl.amp_thresh);
%     fprintf('Temporally set to slightly above minimum amp + 0.1\n');
    
%     return;
elseif length(up_ind)==1 && length(down_ind)==1
    fprintf('Single call detected, or syllable threshold is too small. \n')
    handles.pm.syllable=[];
    if up_ind(1)>down_ind(1)
        fprintf('Detected: up_ind(1)>down_ind(1)\n')
%         return;
    end
end

% data start from above the threshold. This part is neglected.
if up_ind(1)>down_ind(1)
    down_ind = down_ind(2:end);
end

% data end above threshold. This part is neglected.
if up_ind(end)>down_ind(end)
    up_ind= up_ind(1:end-1);
end

handles.pm.feature2.meanvar_features=out;
handles.pm.feature2.counter=counter;
handles.pm.feature2.start_ind=up_ind;
handles.pm.feature2.end_ind=down_ind;


% --- Executes on slider movement.
function slider_spectrum_caxis_Callback(hObject, eventdata, handles)
% hObject    handle to slider_spectrum_caxis (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider

handles.caxis_cutoff=get(hObject,'Value');

max_spec=max(handles.pm.feature2.m_spec_deriv(:));
min_spec=min(handles.pm.feature2.m_spec_deriv(:));

caxis(handles.spectrum_axes,handles.caxis_cutoff*[-max_spec, max_spec]);

guidata(hObject,handles);

% --- Executes during object creation, after setting all properties.
function slider_spectrum_caxis_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider_spectrum_caxis (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end

set(hObject,'Value',0.001);
handles.caxis_cutoff=get(hObject,'Value');
guidata(hObject,handles);


% --- Executes on button press in rb_amplitude.
function rb_amplitude_Callback(hObject, eventdata, handles)
% hObject    handle to rb_amplitude (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of rb_amplitude

name=get(hObject,'String');
update_feature_plots(name,hObject,handles)



% --- Executes on button press in rb_entropy.
function rb_entropy_Callback(hObject, eventdata, handles)
% hObject    handle to rb_entropy (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of rb_entropy
name=get(hObject,'String');
update_feature_plots(name,hObject,handles)


% --- Executes on button press in radiobutton9.
function radiobutton9_Callback(hObject, eventdata, handles)
% hObject    handle to radiobutton9 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of radiobutton9
name=get(hObject,'String');
update_feature_plots(name,hObject,handles)


% --- Executes on button press in rb_pitch.
function rb_pitch_Callback(hObject, eventdata, handles)
% hObject    handle to rb_pitch (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of rb_pitch
name=get(hObject,'String');
update_feature_plots(name,hObject,handles)


% --- Executes on button press in rb_pitchgoodness.
function rb_pitchgoodness_Callback(hObject, eventdata, handles)
% hObject    handle to rb_pitchgoodness (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of rb_pitchgoodness

name=get(hObject,'String');
update_feature_plots(name,hObject,handles)

% --- Executes on button press in rb_meanfreq.
function rb_meanfreq_Callback(hObject, eventdata, handles)
% hObject    handle to rb_meanfreq (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of rb_meanfreq
name=get(hObject,'String');
update_feature_plots(name,hObject,handles)


function update_feature_plots(name,hObject,handles)
ii=strmatch(name,handles.presyl.feature_names);

if get(hObject,'Value')
    
    switch handles.pm.data_type
        case 'wav'
            %   handles.pm.feature2
            x=handles.pm.feature2.t;
            y=handles.pm.feature2.(name);
            % handles.gph.template_feature_plots
        case 'realsong'
             switch name
                 case 'vm' % Vm is sampled at 22050 Hz.
                     x=handles.pm.rsd.t-handles.pm.rsd.t(1);
                 otherwise
                     x=handles.pm.rsd.t_feat-handles.pm.rsd.t_feat(1);
             end
  
            y=handles.pm.rsd.(name);
            if isempty(y)
                fprintf('variable %s is not recorded in this data.\n',name);
                if strncmp(name,'FF',2)
                    fprintf('Calculated FF now...');
                    y=YIN_FF_estimator(handles.pm.song,handles.pm.Fsong,...
                        2,3,x,0.1,'forward',0);
                    
                else
                    return;
                end
            end
        otherwise
            error;
    end
    
    if ishandle(handles.gph.template_feature_plots(ii))
        
        set(handles.gph.template_feature_plots(ii),...
            'XData',x,...
            'YData',y);
        switch name
            case {'amplitude'}
                set(handles.feature_axes,'YLim',[0,max(handles.pm.feature2.amplitude)]);
            case {'meanfreq','pitch','FF'}
                set(handles.feature_axes,'YLim',[0,handles.pm.frange(end)]);
               set(handles.gph.pitch_plots,...
                    'XData',x,...
                    'YData',y,...
                    'Marker','.');
                
              
            case {'entropy'}
                set(handles.feature_axes,'YLim',[min(handles.pm.feature2.entropy),0]);
            case  'FM'
                set(handles.feature_axes,'YLim',[0,90]);
            case 'pitchgoodness'
                set(handles.feature_axes,'YLim',[0,max(handles.pm.feature2.pitchgoodness)]);
            case {'precisepitch'}
                set(handles.feature_axes,'YLim',[0,handles.pm.frange(end)]);
                set(handles.gph.template_feature_plots(ii),'Color',[0 1 0]);
                set(handles.gph.pitch_plots,...
                    'XData',x,...
                    'YData',y);

            otherwise
        end
    else
        error('No handle remains!')
    end
    
else
    
    if ishandle(handles.gph.template_feature_plots(ii))
        
        set(handles.gph.template_feature_plots(ii),...
            'XData',NaN,...
            'YData',NaN);
    end
    
      switch name
          case {'meanfreq','pitch','precisepitch'}
                set(handles.gph.pitch_plots,...
                    'XData',NaN,...
                    'YData',NaN);

      end
        
end




% --- Executes during object creation, after setting all properties.
function popup_templatenum_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popup_templatenum (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit_templatesize_Callback(hObject, eventdata, handles)
% hObject    handle to edit_templatesize (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_templatesize as text
%        str2double(get(hObject,'String')) returns contents of edit_templatesize as a double


% --- Executes during object creation, after setting all properties.
function edit_templatesize_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_templatesize (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function handles=edit_presyl_cntrmin_Callback(hObject, eventdata, handles)
% hObject    handle to edit_presyl_cntrmin (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_presyl_cntrmin as text
%        str2double(get(hObject,'String')) returns contents of edit_presyl_cntrmin as a double

val=str2double(get(hObject,'String'));

if round(val)~=val
    set(hObject,'String',num2str(round(val)));
    errordlg('Counter value must be an integer!Set to closest integet.');
end


handles.presyl.presyl_cntmin=val;
s=sprintf('= %3.3gms',1.e3*handles.presyl.presyl_cntmin*handles.pm.nstepsize/handles.pm.Fsong);
set(handles.txt_presyncnt_in_ms,'String',s);
guidata(hObject,handles);



% --- Executes during object creation, after setting all properties.
function edit_presyl_cntrmin_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_presyl_cntrmin (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function handles=edit_max_presyl_cancel_counter_Callback(hObject, eventdata, handles)
% hObject    handle to edit_max_presyl_cancel_counter (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_max_presyl_cancel_counter as text
%        str2double(get(hObject,'String')) returns contents of edit_max_presyl_cancel_counter as a double

val=str2double(get(hObject,'String'));

if round(val)~=val
    set(hObject,'String',num2str(round(val)));
    errordlg('Counter value must be an integer!Set to closest integet.');
end

handles.presyl.max_presyl_cancel_counter=val;
s=sprintf('count before end of syllable (=%3.3gms)',1.e3*val*handles.pm.nstepsize/handles.pm.Fsong);
set(handles.text_cancel_counter_in_ms,'String',s);
guidata(hObject,handles);


% --- Executes during object creation, after setting all properties.
function edit_max_presyl_cancel_counter_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_max_presyl_cancel_counter (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in popupmenu_countermode.
function popupmenu_countermode_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu_countermode (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns popupmenu_countermode contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu_countermode






function handles=set_presyl_template_parameters(hObject,eventdata,handles)
s=get(handles.edit_presyl_cntrmin,'String');
handles.presyl.presyl_cntmin=str2double(s);
s=sprintf('= %3.3gms',1.e3*handles.presyl.presyl_cntmin*handles.pm.nstepsize/handles.pm.Fsong);
set(handles.txt_presyncnt_in_ms,'String',s);

handles=edit_max_presyl_cancel_counter_Callback(handles.edit_max_presyl_cancel_counter, eventdata, handles);
handles=edit_maindetection_startcnt_Callback(handles.edit_maindetection_startcnt, eventdata, handles);
handles=edit_maindetection_endcnt_Callback(handles.edit_maindetection_endcnt, eventdata, handles);
handles=edit_max_maindetection_cancel_cnt_Callback(handles.edit_max_maindetection_cancel_cnt, eventdata, handles);

handles=edit_MainSylDetectThreshold_Callback(handles.edit_MainSylDetectThreshold,eventdata,handles);

% --- Executes on button press in rb_fixtemplatesize.
function rb_fixtemplatesize_Callback(hObject, eventdata, handles)
% hObject    handle to rb_fixtemplatesize (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of rb_fixtemplatesize



function handles=edit_ampthresh_Callback(hObject, eventdata, handles)
% hObject    handle to edit_ampthresh (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_ampthresh as text
%        str2double(get(hObject,'String')) returns contents of edit_ampthresh as a double

handles.presyl.amp_thresh=str2double(get(hObject,'String'));
fprintf('amplitude is set to %3.3g\n',handles.presyl.amp_thresh);

% handles=init_feature_figure_plot(handles);
handles=running_mean_var_of_features(hObject,eventdata,handles);
handles=redraw_syllable_detection_boundaries(hObject,eventdata,handles);
handles=pb_set_unknown_Callback(handles.pb_set_unknown, eventdata, handles)
guidata(hObject,handles);


% --- Executes during object creation, after setting all properties.
function edit_ampthresh_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_ampthresh (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


function handles=running_mean_var(hObject,eventdata,handles)


features=handles.pm.feature2;

minbase=min(features.amplitude);
maxbase=max(features.amplitude);

handles.presyl.aboveind=(features.amplitude>handles.presyl.amp_thresh);
%
counter=zeros(length(features.t),1);
% init mean and the variance variables


x=zeros(length(handles.presyl.teacher_feature_names),1);
iterative_mean_var(x,'init');
out=zeros(2*length(handles.presyl.feature_names),length(counter));
up_ind=[];
down_ind=[];
for ii=1:length(counter)
    if handles.presyl.aboveind(ii)==0 % below threshold
        out(:,ii)=iterative_mean_var(0);
        counter(ii+1)=0;
        if counter(ii)~=0 % previous time was above threshold
            down_ind=[down_ind,ii];
        end
    else            % above threshold
        counter(ii+1)=counter(ii)+1;
        if counter(ii)==0; % previous time was below threshold
            out(:,ii)=iterative_mean_var(0);
            up_ind=[up_ind,ii];
        else
            
            for jj=1:length(handles.presyl.feature_names)
                try
                    x(jj)=features.(handles.presyl.feature_names{jj})(ii);
                catch
                    error('%s error',handles.presyl.feature_names{jj});
                end
            end
            out(:,ii)=iterative_mean_var(x);
        end
    end
    
end


counter=counter(1:end-1);


if isempty(up_ind) || isempty(down_ind)
    px=[];
    py=[];
    duration=[];
    fprintf('No motif or syllable detected! (min amp=%g, max amp=%g, thresh=%g)\n',...
        min(features.amplitude),...
        max(features.amplitude),...
        handles.presyl.amp_thresh);
    return;
elseif length(up_ind)==1 && length(down_ind)==1
    fprintf('Single call detected, or syllable threshold is too small. \n')
    handles.pm.syllable=[];
    if up_ind(1)>down_ind(1)
        fprintf('Detected: up_ind(1)>down_ind(1)\n')
        return;
    end
end

% data start from above the threshold. This part is neglected.
if up_ind(1)>down_ind(1)
    down_ind = down_ind(2:end);
end

% data end above threshold. This part is neglected.
if up_ind(end)>down_ind(end)
    up_ind= up_ind(1:end-1);
end

handles.pm.feature2.meanvar_features=out;
handles.pm.feature2.counter=counter;
handles.pm.feature2.start_ind=up_ind;
handles.pm.feature2.end_ind=down_ind;

%--------------------------------------------------------------------%
%------------------- redraw syllable detection boundaries -----------%
%--------------------------------------------------------------------%
function handles=redraw_syllable_detection_boundaries(hObject,eventdata,handles)


up_ind=handles.pm.feature2.start_ind;
down_ind=handles.pm.feature2.end_ind;

if length(up_ind)>1
    handles.pm.MotifDetected=1;
else % there is only one pause in the song, which is very likely to be noise.
    % fprintf('No motif or syllable detected!\n')
    handles.pm.MotifDetected=0;
end


axes(handles.gph.template_mtf_axes);
set(handles.gph.template_mtf_axes,'YLim',[0,handles.pm.frange(end)]);
ylim_tmp=get(handles.gph.template_mtf_axes,'YLim');
maxy = max(ylim_tmp);
miny=  min(ylim_tmp);
% 
% px = [repmat(handles.pm.feature2.t(up_ind),2,1); NaN*ones(1,length(up_ind))];
% px = reshape(px,1,prod(size(px)));
% py = [repmat(ylim_tmp',1,length(up_ind)); NaN*ones(1,length(up_ind))];
% py = reshape(py,1,numel(py));
% 
% % val=handles.gph.template_feature.mtf_Strt;
% 
% try
% set(handles.gph.template_feature.mtf_Strt,'XData',px,'YData',py);
% catch
%     handles.gph.template_feature.mtf_Strt=...
%         plot(px,py,'Color',[1 0 0]);hold on;
% end
% 
% 
% px = [repmat(handles.pm.feature2.t(down_ind),2,1); NaN*ones(1,length(down_ind))];
% px = reshape(px,1,numel(px));
% py = [repmat(ylim_tmp',1,length(down_ind)); NaN*ones(1,length(down_ind))];
% py = reshape(py,1,prod(size(py)));
% 
% try
% set(handles.gph.template_feature.mtf_End,'XData',px,'YData',py);
% catch  
% handles.gph.template_feature.mtf_End     =...
%     plot(px,py,'Color',[1 0 0]);
% end
px = [handles.pm.feature2.t(up_ind); handles.pm.feature2.t(down_ind); handles.pm.feature2.t(down_ind);handles.pm.feature2.t(up_ind)];
py = [maxy-0.2*diff(ylim_tmp)*ones(1,2), maxy,maxy]';
py = repmat(py,1,size(px,2));
%         set(handles.gph.template_feature.mtf_region,'XData',px,'YData',py);


show_target_label   =1;
t_offset            =0.005;
label_num_offset    =maxy-0.1*diff(ylim_tmp);
font_size           =9;
% 
% delete(handles.gph.motifpatch_for_template);
% delete(handles.gph.motifpatch_for_template_label);
try, delete(handles.gph.motifpatch_for_template);end
try, delete(handles.gph.motifpatch_for_template_label);end
try delete(handles.main_sylcriteria.hit_plot);end
try delete(handles.main_sylcriteria.trigger_plot);end

child=get(handles.gph.template_mtf_axes,'Child');
delete(child);
axes(handles.gph.template_mtf_axes);
handles.presyl.current_target_id=[];
for ii=1:length(handles.pm.feature2.start_ind)
    userdata=[handles.pm.feature2.start_ind(ii), handles.pm.feature2.end_ind(ii)];
% 'callback', @(hObject,eventdata)myGui('button1_callback',hObject,eventdata,guidata(hObject))

    ButtonDownFcnTxt=sprintf('%s(''Toggle_Target_or_Not'')',mfilename);
    handles.gph.motifpatch_for_template(ii)=patch(px(:,ii),py(:,ii),'b',...
        'FaceAlpha',0.5,...
        'ButtonDownFcn',ButtonDownFcnTxt,...
        'Tag','DoNotIgnore','UserData',[userdata,ii]);
    handles.presyl.current_target_id(ii)=-1;
    if (show_target_label)
        handles.gph.motifpatch_for_template_label(ii)=text(mean(px(:,ii))-t_offset,label_num_offset,'x',...
            'FontSize',font_size);
        set(handles.gph.motifpatch_for_template_label(ii),...
            'HitTest', 'off',...
            'Tag','DoNotIgnore','UserData',[userdata,ii]);
    end
    
end


h=zoom;
set(h,'Motion','horizontal','ButtonDownFilter',@myzoomcallback,'Enable','on');
% 
% axes(handles.spectrum_axes);hold on;
hold on;
handles.gph.pitch_plots=plot(NaN,NaN,'g.');

function Toggle_Target_or_Not(hObject,eventdata,handles)

        % [1 0 0]; RED,  target.
        % [0 1 0]; GREEN, not clear.
        % [0 0 1]; BLUE, Non-target.
        handles     =guidata(gcbo);
        userdata    =get(gcbo,'UserData');
        id=userdata(3);
        LR=get(gcf,'SelectionType');
        switch LR
            case 'normal'
                d=1;
            case 'alt'
                d=-1;
            otherwise
                error;
        end
%       color_target=get(handles.gph.motifpatch_for_template(id),'FaceColor');
        color_target=get(gcbo,'FaceColor');
%         set(handles.gph.motifpatch_for_template(id),'FaceColor',circshift(color_target,[0,d]));
        set(gcbo,'FaceColor',circshift(color_target,[0,d]));

%         color_target_now=get(handles.gph.motifpatch_for_template(id),'FaceColor');
         color_target_now=get(gcbo,'FaceColor');
  
        set(handles.gph.motifpatch_for_template_label(userdata(3)),'String',handles.presyl.TargetCode{find(color_target_now),2});
        % 1: target, 0; not defined, -1: non-target syllable.
        handles.presyl.current_target_id(id)=round(2-find(color_target_now));
        
        guidata(gcbo,handles);
        
        

function [flag] = myzoomcallback(obj,event_obj)
% If the tag of the object is 'DoNotIgnore', then return true.
objTag = get(obj,'Tag');
if strcmpi(objTag,'DoNotIgnore')
   flag = true;
else
   flag = false;
end


% --- Executes on button press in pb_set_unknown.
function handles=pb_set_unknown_Callback(hObject, eventdata, handles)
% hObject    handle to pb_set_unknown (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

        
for ii=1:length(handles.presyl.current_target_id)

set(handles.gph.motifpatch_for_template(ii),'FaceColor',[0 1 0]);
set(handles.gph.motifpatch_for_template_label(ii),'String','?');
% 1: target, 0; not defined, -1: non-target syllable.
handles.presyl.current_target_id(ii)=0;
end

guidata(hObject,handles);


% --- Executes on button press in radiobutton15.
function radiobutton15_Callback(hObject, eventdata, handles)
% hObject    handle to radiobutton15 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of radiobutton15


% --- Executes on button press in pb_loaddir.
function pb_loaddir_Callback(hObject, eventdata, handles,opt)
% hObject    handle to pb_loaddir (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
handles=set_ONOFF_realsong_feature_rb(0,handles);

if nargin==4
    handles.pm.sound_dir=opt;
else
    
    try
        [handles.pm.sound_dir] = uigetdir(handles.pm.sound_dir, 'Pick a song (.wav) directory');
    catch % In case no wave file is chosen.
        [handles.pm.sound_dir] = uigetdir(pwd, 'Pick a song (.wav) directory');
        %             error([mfilename, ': Please chose a .wav file.']);
    end
end
s=dir(fullfile(handles.pm.sound_dir,'*.wav'));
set(handles.lb_songdir,'String',{s.name});
get(handles.lb_songdir,'Position');
handles.pm.data_type='wav';
guidata(hObject,handles);

% --- Executes on selection change in lb_songdir.
function lb_songdir_Callback(hObject, eventdata, handles)
% hObject    handle to lb_songdir (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns lb_songdir contents as cell array
%        contents{get(hObject,'Value')} returns selected item from lb_songdir

contents = cellstr(get(hObject,'String'));
songfile=contents{get(hObject,'Value')};
pb_loadsong_Callback(hObject, eventdata, handles,handles.pm.sound_dir,songfile);

% --- Executes during object creation, after setting all properties.
function lb_songdir_CreateFcn(hObject, eventdata, handles)
% hObject    handle to lb_songdir (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: listbox controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function handles=edit_maindetection_startcnt_Callback(hObject, eventdata, handles)
% hObject    handle to edit_maindetection_startcnt (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_maindetection_startcnt as text
%        str2double(get(hObject,'String')) returns contents of edit_maindetection_startcnt as a double

handles.presyl.maindetection_startcnt=str2double(get(handles.edit_maindetection_startcnt,'String'));
n=1.e3*handles.presyl.maindetection_startcnt*handles.pm.nstepsize/handles.pm.Fsong;
s=sprintf('count (= %3.3g ms)',n);
set(handles.text_mincnt_for_mainsyl_in_ms,'String',s);
guidata(hObject,handles);

% --- Executes during object creation, after setting all properties.
function edit_maindetection_startcnt_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_maindetection_startcnt (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function handles=edit_maindetection_endcnt_Callback(hObject, eventdata, handles)
% hObject    handle to edit_maindetection_endcnt (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_maindetection_endcnt as text
%        str2double(get(hObject,'String')) returns contents of edit_maindetection_endcnt as a double

handles.presyl.maindetection_endcnt=str2double(get(handles.edit_maindetection_endcnt,'String'));
n=1.e3*handles.presyl.maindetection_endcnt*handles.pm.nstepsize/handles.pm.Fsong;
s=sprintf('count (= %3.3g ms)',n);
set(handles.text_maxcnt_for_mainsyl_in_ms,'String',s);
guidata(hObject,handles);

% --- Executes during object creation, after setting all properties.
function edit_maindetection_endcnt_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_maindetection_endcnt (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



% --- Executes on button press in rb_precisepitch.
function rb_precisepitch_Callback(hObject, eventdata, handles)
% hObject    handle to rb_precisepitch (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of rb_precisepitch

name=get(hObject,'String');
update_feature_plots(name,hObject,handles)





% --- Executes on button press in pb_getinfo.
function out=pb_getinfo_Callback(hObject, eventdata, handles,varargin)
% hObject    handle to pb_getinfo (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

if nargin<=3
axes(handles.spectrum_axes);
[xposi,yposi]=ginput(1);
else
    tmp=varargin{1};
    xposi=tmp(1);
end

f=handles.pm.Fsong*((1:handles.pm.nFFT)-1)/handles.pm.nFFT;
handles.pm.frange=[400,10000];
findex=find(f>=handles.pm.frange(1)&f<=handles.pm.frange(2));
handles.pm.feature2.f=f(findex);

handles.pm.efrange=[1000,10000];
efindex=find(f>=handles.pm.frange(1)&f<=handles.pm.frange(2));


calc_precise_pitch=1;
param.up_pitch= 8000;% 
param.low_pitch=400;%

param.cepst_nfft=2048;         % nfft size for cepstrum;
quefrency = [0:param.cepst_nfft]*handles.pm.nFFT/(handles.pm.Fsong*param.cepst_nfft); % quefrency in [sec].
param.quefrency_select=(1./quefrency<param.up_pitch & 1./quefrency > param.low_pitch); % select quefrency in 400 to 8000 Hz range.

param.f         =f;
param.findex    =findex;
param.efindex   =efindex;

ind=find(handles.pm.feature2.t>xposi,1,'first');
index=ceil(handles.pm.feature2.t(ind)*handles.pm.Fsong);

% index=ceil(xposi*handles.pm.Fsong/handles.pm.nstepsize);
index=index+[1:handles.pm.nWinsize];

[E2,V] = dpss(handles.pm.nWinsize,4,2);
Ec=E2(:,1);
Es=E2(:,2);
calc_precise_pitch=1;
    J1=fft(handles.pm.song(index).*Ec,handles.pm.nFFT);
    J2=fft(handles.pm.song(index).*Es,handles.pm.nFFT);
    
    
    [  feature2.m_spec_deriv,...
        feature2.amplitude,...
        feature2.entropy,...
        feature2.FM,...
        feature2.AM,...
        feature2.meanfreq,...
        feature2.pitch,...
        feature2.pitchgoodness,...
        feature2.precisepitch,...
        feature2.m_time_deriv_max,...
        feature2.m_freq_deriv_max,...
        feature2.m_powSpec] = ...
        multitaper_feature_RTSAC3(J1(:),J2(:),...
        1/handles.pm.Fsong,handles.pm.nFFT,...
        param,...
        calc_precise_pitch,0);
    
    feature2.FF=YIN_FF_estimator(handles.pm.song,handles.pm.Fsong,...
     4,2,xposi,0.1,'forward',-1)
 
    out=feature2;
    song=handles.pm.song(index);
 save('testwave.mat','song');
% assignin('base','feature2',feature2);               % Create an xPC Target Object


% --- Executes when entered data in editable cell(s) in uitable_mainsyl_criteria.
function uitable_mainsyl_criteria_CellEditCallback(hObject, eventdata, handles)
% hObject    handle to uitable_mainsyl_criteria (see GCBO)
% eventdata  structure with the following fields (see UITABLE)
%	Indices: row and column indices of the cell(s) edited
%	PreviousData: previous data for the cell(s) edited
%	EditData: string(s) entered by the user
%	NewData: EditData or its converted form set on the Data property. Empty if Data was not changed
%	Error: error string when failed to convert EditData to appropriate value for Data
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in pb_getspectruminfo.
function pb_getspectruminfo_Callback(hObject, eventdata, handles, varargin)
% hObject    handle to pb_getspectruminfo (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

if nargin <=3
    [x,y]=ginput(1);
else
    tmp=varargin{1};
    x=varargin{1};
    y=varargin{2};
end


ii=find(handles.pm.feature2.t>x,1,'first');
FF=YIN_FF_estimator(handles.pm.song,handles.pm.Fsong,...
     4,2,x,0.1,'forward',-1)
 
datatmp=[      handles.pm.feature2.amplitude(ii),...
    handles.pm.feature2.entropy(ii),...
    handles.pm.feature2.meanfreq(ii),...
    handles.pm.feature2.FM(ii),...
    handles.pm.feature2.pitch(ii),...
    handles.pm.feature2.pitchgoodness(ii),...
    handles.pm.feature2.precisepitch(ii),...
    FF];

 
 data=get(handles.uitable_mainsyl_criteria, 'Data');
 for ii=1:length(datatmp)
 data{ii,3}=datatmp(ii);
 end
    set(handles.uitable_mainsyl_criteria, 'Data', data);
guidata(hObject,handles);


% --- Executes on selection change in popup_maindetection_time_mode.
function handles=popup_maindetection_time_mode_Callback(hObject, eventdata, handles)
% hObject    handle to popup_maindetection_time_mode (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns popup_maindetection_time_mode contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popup_maindetection_time_mode

%1: relative to next syllable onset;
%2: relative to end of pre-syllable onset.
contents = cellstr(get(hObject,'String'));
fprintf('Main syllable detection starts relative to %s\n',contents{get(hObject,'Value')});
handles.main_syl_timemode=get(hObject,'Value');
guidata(hObject,handles);

% --- Executes during object creation, after setting all properties.
function popup_maindetection_time_mode_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popup_maindetection_time_mode (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



% --- Executes on button press in pb_test.
function handles=pb_test_Callback(hObject, eventdata, handles)
% hObject    handle to pb_test (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


names=handles.mainsyl_criteria.feature_names;

[index,tt]=get_mainsyl_detection_index(handles);

data=get(handles.uitable_mainsyl_criteria, 'Data');

for ii=1:length(names)
    if ischar(data{ii,1})
        minvar(ii)=str2double(data{ii,1});
    elseif isnumeric(data{ii,1})
        minvar(ii)=data{ii,1};
    end
end

for ii=1:length(names)
    if ischar(data{ii,2})
        maxvar(ii)=str2double(data{ii,2});
    elseif isnumeric(data{ii,2})
        maxvar(ii)=data{ii,2};
    end
end


minvar=minvar(:);
maxvar=maxvar(:);

T=length(handles.pm.feature2.t);
hit=zeros(1,T);
trigger=zeros(1,T);

hit_counter=0;


if get(handles.tg_OpenSpectrumTargetMode,'Value')
    do_spectcorr=1;
else
    do_spectcorr=0;
end


for tt=1:T
    inside_mainsyl =  any((tt>index(:,1))&(tt<index(:,2)));
    if (inside_mainsyl)
        x=[];
        for kk=1:length(names)
            x=[x; handles.pm.feature2.(names{kk})(tt)];
        end
        hit(tt)=all((x>minvar)&(x<maxvar));
        
        if hit(tt)
            hit_counter=hit_counter+1;
        else
            hit_counter=0;
        end
        
        if (hit_counter>=handles.mainsyl.maindetection_threshold) 
          trigger(tt)=1;
        end
        
    end
end


% hit
try delete(handles.main_sylcriteria.hit_plot);end
try delete(handles.main_sylcriteria.trigger_plot);end


axes(handles.gph.template_mtf_axes);
handles.main_sylcriteria.hit_plot=...
    plot(handles.pm.feature2.t(hit>0),zeros(1,sum(hit)),'g*');
handles.main_sylcriteria.trigger_plot=...
    plot(handles.pm.feature2.t(trigger>0),zeros(1,sum(trigger)),'ro');
handles.pm.trigger = trigger;


% assignin('base','handles',handles);
guidata(hObject,handles);


function handles=edit_max_maindetection_cancel_cnt_Callback(hObject, eventdata, handles)
% hObject    handle to edit_max_maindetection_cancel_cnt (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_max_maindetection_cancel_cnt as text
%        str2double(get(hObject,'String')) returns contents of edit_max_maindetection_cancel_cnt as a double

handles.presyl.max_maindetection_cancel_cnt=...
    str2double(get(hObject,'String'));
n=1.e3*handles.presyl.max_maindetection_cancel_cnt*handles.pm.nstepsize/handles.pm.Fsong;
s=sprintf('count (= %3.3g ms)',n);
set(handles.text_cancel_mainsyl_cnt_in_ms,'String',s);
guidata(hObject,handles);

% --- Executes during object creation, after setting all properties.
function edit_max_maindetection_cancel_cnt_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_max_maindetection_cancel_cnt (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% --- Executes on button press in pb_loadtemplate.
function pb_loadtemplate_Callback(hObject, eventdata, handles)
% hObject    handle to pb_loadtemplate (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


try
    [handles.pm.svmdata_name,handles.pm.svmdata_dir] = uigetfile({fullfile(handles.pm.svmdata_dir,'*.mat')}, 'Pick a pre-syllable detection svm file');
catch % In case no wave file is chosen.
    [handles.pm.svmdata_name,handles.pm.svmdata_dir] = uigetfile({'*.mat';fullfile(handles.pm.sound_dir,'svmdata.mat')}, 'Pick a pre-syllable detection svm filee');
    %             error([mfilename, ': Please chose a .wav file.']);
end

load(fullfile(handles.pm.svmdata_dir,handles.pm.svmdata_name),'presyl','mainsyl');
handles.presyl=presyl;


set(handles.edit_ampthresh,'String',num2str(handles.presyl.amp_thresh));
handles=edit_ampthresh_Callback(handles.edit_ampthresh, eventdata, handles);

set(handles.edit_presyl_cntrmin,'String',num2str(handles.presyl.presyl_cntmin));
handles=edit_presyl_cntrmin_Callback(handles.edit_presyl_cntrmin, eventdata, handles);

set(handles.edit_max_presyl_cancel_counter,'String',num2str(handles.presyl.max_presyl_cancel_counter));
handles=edit_max_presyl_cancel_counter_Callback(handles.edit_max_presyl_cancel_counter, eventdata, handles);

set(handles.edit_max_maindetection_cancel_cnt,'String',num2str(handles.presyl.max_maindetection_cancel_cnt));
handles=edit_max_maindetection_cancel_cnt_Callback(handles.edit_max_maindetection_cancel_cnt,eventdata,handles);

set(handles.edit_maindetection_startcnt,'String',num2str(handles.presyl.maindetection_startcnt));
handles=edit_maindetection_startcnt_Callback(handles.edit_maindetection_startcnt, eventdata, handles);

set(handles.edit_maindetection_endcnt,'String',num2str(handles.presyl.maindetection_endcnt));
handles=edit_maindetection_endcnt_Callback(handles.edit_maindetection_endcnt, eventdata, handles);


data=get(handles.uitable_mainsyl_criteria, 'Data');
for ii=1:size(mainsyl.criteria,1)
    for jj=1:size(mainsyl.criteria,2)
        data{ii,jj}=mainsyl.criteria(ii,jj);
    end
end
set(handles.uitable_mainsyl_criteria, 'Data',data);

if isfield(mainsyl,'maindetection_threshold')
    set(handles.edit_MainSylDetectThreshold,'String',num2str(mainsyl.maindetection_threshold))    
end
handles=edit_MainSylDetectThreshold_Callback(handles.edit_MainSylDetectThreshold, eventdata, handles);

guidata(hObject,handles);


% --- Executes on button press in pb_assinginfeatures.
function pb_assinginfeatures_Callback(hObject, eventdata, handles)
% hObject    handle to pb_assinginfeatures (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% assignin('base','feature2',handles.pm.feature2);
% assignin('base','prediction',handles.prediction);


% --- Executes on button press in pb_SoundAmpTrig_PreSylDetection.
function pb_SoundAmpTrig_PreSylDetection_Callback(hObject, eventdata, handles)
% hObject    handle to pb_SoundAmpTrig_PreSylDetection (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of pb_SoundAmpTrig_PreSylDetection


% --- Executes on button press in pb_FixedDuration_DetectPresyl.
function pb_FixedDuration_DetectPresyl_Callback(hObject, eventdata, handles)
% hObject    handle to pb_FixedDuration_DetectPresyl (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of pb_FixedDuration_DetectPresyl


% --- Executes on button press in pb_loadrsdir.
function pb_loadrsdir_Callback(hObject, eventdata, handles,opt)
% hObject    handle to pb_loadrsdir (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

handles=set_ONOFF_realsong_feature_rb(1,handles);

if nargin==4
    handles.pm.sound_dir =opt;
else
    
    try
        [handles.pm.sound_dir] = uigetdir(handles.pm.sound_dir, 'Pick a RealSong data (.mat) directory');
    catch % In case no wave file is chosen.
        [handles.pm.sound_dir] = uigetdir(pwd, 'Pick a RealSong (.mat) directory');
        %             error([mfilename, ': Please chose a .wav file.']);
    end
end

s=dir(fullfile(handles.pm.sound_dir,'*.mat'));
set(handles.lb_songdir,'String',{s.name});
get(handles.lb_songdir,'Position');
handles.pm.data_type='realsong';
guidata(hObject,handles);



function edit_averagingduration_in_units_Callback(hObject, eventdata, handles)
% hObject    handle to edit_averagingduration_in_units (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_averagingduration_in_units as text
%        str2double(get(hObject,'String')) returns contents of edit_averagingduration_in_units as a double

val=str2double(get(hObject,'String'));

if round(val)~=val
    set(hObject,'String',num2str(round(val)));
    errordlg('Counter value must be an integer!Set to closest integet.');
end

handles.presyl.presyl_averaging_val  = val;
handles.presyl.presyl_averaging_index=[1:val];
s=sprintf('= %3.3gms',1.e3*handles.presyl.presyl_averaging_val*handles.pm.nstepsize/handles.pm.Fsong);
set(handles.text_averaging_duration_in_sec,'String',s);
guidata(hObject,handles);

% --- Executes during object creation, after setting all properties.
function edit_averagingduration_in_units_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_averagingduration_in_units (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit_nstepsize_Callback(hObject, eventdata, handles)
% hObject    handle to edit_nstepsize (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_nstepsize as text
%        str2double(get(hObject,'String')) returns contents of edit_nstepsize as a double


% --- Executes during object creation, after setting all properties.
function edit_nstepsize_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_nstepsize (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes during object creation, after setting all properties.
function ui_pretrigmode_selection_CreateFcn(hObject, eventdata, handles)
% hObject    handle to ui_pretrigmode_selection (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called


% --- Executes on button press in pb_pretrig_timeaverage_mode.
function pb_pretrig_timeaverage_mode_Callback(hObject, eventdata, handles)
% hObject    handle to pb_pretrig_timeaverage_mode (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in pb_pretrig_soundamp_mode.
function pb_pretrig_soundamp_mode_Callback(hObject, eventdata, handles)
% hObject    handle to pb_pretrig_soundamp_mode (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes when selected object is changed in ui_pretrigmode_selection.
function handles=ui_pretrigmode_selection_SelectionChangeFcn(hObject, eventdata, handles)
% hObject    handle to the selected object in ui_pretrigmode_selection 
% eventdata  structure with the following fields (see UIBUTTONGROUP)
%	EventName: string 'SelectionChanged' (read only)
%	OldValue: handle of the previously selected object or empty if none was selected
%	NewValue: handle of the currently selected object
% handles    structure with handles and user data (see GUIDATA)


handles.pm.pretrig_mode=get(get(handles.ui_pretrigmode_selection,'SelectedObject'),'Tag');
fprintf('Selected %s\n',handles.pm.pretrig_mode);

switch handles.pm.pretrig_mode
    case 'pb_pretrig_timeaverage_mode'
        set(handles.edit_averagingduration_in_units,'Enable','On');
        
    case 'pb_pretrig_soundamp_mode'
        set(handles.edit_averagingduration_in_units,'Enable','Off');
    otherwise
        error;
end

guidata(hObject,handles);



function handles=edit_MainSylDetectThreshold_Callback(hObject, eventdata, handles)
% hObject    handle to edit_MainSylDetectThreshold (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_MainSylDetectThreshold as text
%        str2double(get(hObject,'String')) returns contents of edit_MainSylDetectThreshold as a double


handles.mainsyl.maindetection_threshold=str2double(get(handles.edit_MainSylDetectThreshold,'String'));
n=1.e3*handles.mainsyl.maindetection_threshold*handles.pm.nstepsize/handles.pm.Fsong;
s=sprintf('count (= %3.3g ms)',n);
set(handles.text_mainsyldetectthreshold_in_ms,'String',s);
guidata(hObject,handles);

% --- Executes during object creation, after setting all properties.
function edit_MainSylDetectThreshold_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_MainSylDetectThreshold (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in tg_OpenSpectrumTargetMode.
function tg_OpenSpectrumTargetMode_Callback(hObject, eventdata, handles)
% hObject    handle to tg_OpenSpectrumTargetMode (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


if get(hObject,'Value')
    handles.spectrum_design_handles=SpectrumFilterDesign_001(mfilename,handles.figure_TemplateMaker);    
   SpectrumFilterDesign_001('set_parameters',...
    handles.spectrum_design_handles,[],guidata(handles.spectrum_design_handles),...
    'edit_samprate',handles.pm.Fsong,...
    'edit_fft_windowsize',handles.pm.nFFT,...
    'edit_frange',handles.pm.frange)

nFFT=handles.pm.nFFT;
  
    handles.pm.frange;
else
%     close(handles.gph.spectrum_target_mode);
end

guidata(hObject,handles);

function obj=return_target_spectrums(hObject, eventdata, handles)
% hObject    handle to tg_OpenSpectrumTargetMode (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

disp('returning spectrum data');

handles=pb_test_Callback(hObject, eventdata, handles);
trigger=handles.pm.trigger;

t_maintarget = detect_thresholded_regions(handles.pm.trigger,0.5,3,40,10,1,0)*handles.pm.nstepsize/handles.pm.TargetSampRate;
fprintf('Found target at ');
fprintf('%4.3fms ',t_maintarget*1000);
fprintf('\n');

obj.f=      handles.pm.feature2.f;
obj.spec = [];
for tt=1:length(t_maintarget)
out=pb_getinfo_Callback(hObject, eventdata, handles,t_maintarget(tt));
obj.spec=   [obj.spec, out.m_powSpec];
end


% --- Executes on button press in pb_calc_spectcorr.
function pb_calc_spectcorr_Callback(hObject, eventdata, handles)
% hObject    handle to pb_calc_spectcorr (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
   
target_filter=SpectrumFilterDesign_001('return_spectrum_filter',...
    handles.spectrum_design_handles,eventdata,guidata(handles.spectrum_design_handles));

handles.pm.target_filter=target_filter;


try delete(handles.main_sylcriteria.spectcorr_plot);end
if get(handles.tg_OpenSpectrumTargetMode,'Value')  
    axes(handles.data_axes);
   handles.pm.spectcorr=calc_spectcorr(handles.pm.feature2.m_powSpec,target_filter.spec) ;
   handles.main_sylcriteria.spectcorr_plot=...
    plot(handles.pm.feature2.t,handles.pm.spectcorr,'r.');
end
guidata(hObject,handles);


% --- Executes on button press in rb_FF.
function rb_FF_Callback(hObject, eventdata, handles)
% hObject    handle to rb_FF (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of rb_FF
name=get(hObject,'String');
update_feature_plots(name,hObject,handles)


% --- Executes on button press in rb_Predictor.
function rb_Predictor_Callback(hObject, eventdata, handles)
% hObject    handle to rb_Predictor (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of rb_Predictor

name=get(hObject,'String');
update_feature_plots(name,hObject,handles)


% --- Executes on button press in rb_MainSylGate.
function rb_MainSylGate_Callback(hObject, eventdata, handles)
% hObject    handle to rb_MainSylGate (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of rb_MainSylGate

name=get(hObject,'String');
update_feature_plots(name,hObject,handles)


% --- Executes on button press in rb_vm.
function rb_vm_Callback(hObject, eventdata, handles)
% hObject    handle to rb_vm (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of rb_vm
name=get(hObject,'String');
update_feature_plots(name,hObject,handles)

function handles=set_ONOFF_realsong_feature_rb(val,handles)

realsong_specific_vars={'Predictor','MainSylGate','vm'};

if (val)
    State='On';
else
    State= 'Off'
end

for ii=1:length(realsong_specific_vars)
        set(handles.(['rb_',realsong_specific_vars{ii}]),'Enable',State);
end

set(handles.uipanel_xPC,'Visible',State);

% --- Executes on button press in pb_refresh_list.
function pb_refresh_list_Callback(hObject, eventdata, handles)
% hObject    handle to pb_refresh_list (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
 

switch handles.pm.data_type
    case 'realsong'
        pb_loadrsdir_Callback(handles.pb_loadrsdir, eventdata, handles,handles.pm.sound_dir);
    case 'wav'
        pb_loaddir_Callback(handles.pb_loadrsdir, eventdata, handles,handles.pm.sound_dir);
    otherwise
end
% hObject    handle to pb_loadrsdir (see GCBO)
 


% --- Executes on button press in pb_push_criteria_xPC.
function pb_push_criteria_xPC_Callback(hObject, eventdata, handles)
% hObject    handle to pb_push_criteria_xPC (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

presyl  =handles.presyl;
pm      =handles.pm;
get(handles.uitable_mainsyl_criteria, 'Data');

mainsyl.criteria=get(handles.uitable_mainsyl_criteria, 'Data');
mainsyl.criteria=mainsyl.criteria(:,[1,2]);
mainsyl.criteria=cell2mat(mainsyl.criteria);

if get(handles.tg_OpenSpectrumTargetMode,'Value')
    mainsyl.comb_filter=handles.pm.target_filter;
end


mainsyl.featurename=get(handles.uitable_mainsyl_criteria, 'RowName');
mainsyl.maindetection_threshold=handles.mainsyl.maindetection_threshold;
% save(fullfile(handles.pm.svmdata_dir, handles.pm.svmdata_name),'presyl','pm','mainsyl');
% guidata(hObject,handles);
% handles.ParentGUI
realsong_version=regexp(handles.parent_mfile,'\d{3}','match');
realsong_version=str2double(realsong_version);

if realsong_version <=12 % RealSong_control_012px does not use FF as criteria.
    fprintf('RealSong_control version 12 or lesser does not use FF criteria. Removed.\n')
    nonFF_ind=find(~strncmp('FF',mainsyl.featurename,2));
    mainsyl.criteria=mainsyl.criteria(nonFF_ind,:);
    mainsyl.featurename={mainsyl.featurename{nonFF_ind}};
else
    % do nothing;
end
feval(handles.parent_mfile,'push_criteria_xPC',...
    handles.ParentGUI,eventdata,guidata(handles.ParentGUI),...
    mainsyl,presyl,pm);


% --- Executes on button press in pb_criteria_reset.
function pb_criteria_reset_Callback(hObject, eventdata, handles)
% hObject    handle to pb_criteria_reset (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

Data={...
    0.2,    Inf,    NaN,'','';... % amplitude
    -Inf,   0,      NaN,'','';... %  entropy
    0,      Inf,    NaN,'','';... %   meanfreq
    0,      Inf,    NaN,'','';... %   FM
    0,      Inf,    NaN,'','';... %   pitch
    0,      Inf,    NaN,'','';... %   pitchgoodness
    0,      Inf,    NaN,'','';... %   precisepitch
    0,      Inf,    NaN,'',''}; %   FF

set(handles.uitable_mainsyl_criteria, 'Data',Data)
