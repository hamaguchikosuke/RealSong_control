function varargout = StimFamily_Manager_001(varargin)
% STIMFAMILY_MANAGER_001 MATLAB code for StimFamily_Manager_001.fig
%      STIMFAMILY_MANAGER_001, by itself, creates a new STIMFAMILY_MANAGER_001 or raises the existing
%      singleton*.
%
%      H = STIMFAMILY_MANAGER_001 returns the handle to a new STIMFAMILY_MANAGER_001 or the handle to
%      the existing singleton*.
%
%      STIMFAMILY_MANAGER_001('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in STIMFAMILY_MANAGER_001.M with the given input arguments.
%
%      STIMFAMILY_MANAGER_001('Property','Value',...) creates a new STIMFAMILY_MANAGER_001 or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before StimFamily_Manager_001_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to StimFamily_Manager_001_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help StimFamily_Manager_001

% Last Modified by GUIDE v2.5 08-May-2013 14:52:44

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @StimFamily_Manager_001_OpeningFcn, ...
                   'gui_OutputFcn',  @StimFamily_Manager_001_OutputFcn, ...
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


% --- Executes just before StimFamily_Manager_001 is made visible.
function varargout=StimFamily_Manager_001_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to StimFamily_Manager_001 (see VARARGIN)

% Choose default command line output for StimFamily_Manager_001
handles.output = hObject;

% AutoRun = false;

mainGuiInput = find(strncmp('RealSong',varargin,8));
songload_h=[handles.pb_designsong,handles.pb_load_songstim]; 
if (isempty(mainGuiInput)) ...
        || (length(varargin) <= mainGuiInput) ...
        || (~ishandle(varargin{mainGuiInput+1}))
    handles.main_mfile=[];
    handles.ParentGUI = [];
    handles.SampRate = 100;
    disp('StimFamily (Standalone) mode');
    
    set(songload_h,'Enable','On');
     
     
else
    handles.main_mfile = varargin{mainGuiInput}; 
    handles.ParentGUI  = varargin{mainGuiInput+1};
    disp('StimFamily (RealSong) mode');
    tmp=guidata(handles.ParentGUI);
    try
        handles.SampRate = tmp.pm.SamplingRate;
    catch
        handles.SampRate = 44100;
    end
    handles=pb_load_songstim_Callback(hObject, eventdata, handles,...
        tmp.pm.songstim_file,tmp.pm.songstim_dir);
    set(songload_h,'Enable','Off');
%     AutoRun = true;
end
handles=init_params(hObject,eventdata,handles);
panel_current_order_SelectionChangeFcn(hObject, eventdata, handles);

varargout{1}=handles;

% Update handles structure
% handles=init_params(hObject,eventdata,handles);
% assignin('base','handles',handles);

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes StimFamily_Manager_001 wait for user response (see UIRESUME)
% uiwait(handles.figure_StimFamily_Manager);


% --- Outputs from this function are returned to the command line.
function varargout = StimFamily_Manager_001_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure

varargout{1} = handles.output;


% --- Executes on selection change in lb_song_lists.
function lb_song_lists_Callback(hObject, eventdata, handles)
% hObject    handle to lb_song_lists (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns lb_song_lists contents as cell array
%        contents{get(hObject,'Value')} returns selected item from lb_song_lists
val=get(hObject,'Value');
if isfield(handles,'songstim')
    song=handles.songstim(val).song;
%     size(song)
      [y,f,t,p] = spectrogram(song,256,250,1024,handles.SampRate); 
%       surf(t,f,10*log10(abs(p)),'EdgeColor','none');   
p=10*log10(abs(p));
[SongPreT,SongPostT,SongStimSelection,SongDur,SongDurN]=...
    return_SongStimRecParam(hObject,eventdata,handles);

set(handles.SF.stim_sonogram_image,'XData',t+SongPreT,'YData',f,'CData',p);
set(handles.axes_SF_stim_sonogram,'XLim',[0 t(end)+SongPostT],'YLim',[f(1) f(end)]);
set(handles.axes_SF_stim_sonogram,'CLim',[min(min(p))+20 max(max(p))-20],'YDir','Normal');
% set(get(handles.SF.stim_sonogram_image,'Parent'),);
end

% --- Executes during object creation, after setting all properties.
function lb_song_lists_CreateFcn(hObject, eventdata, handles)
% hObject    handle to lb_song_lists (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: listbox controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

    
% --- Executes on button press in pb_clear.
function pb_clear_Callback(hObject, eventdata, handles)
% hObject    handle to pb_clear (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in pb_load_songstim.
function handles=pb_load_songstim_Callback(hObject, eventdata, handles,varargin)
% hObject    handle to pb_load_songstim (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% if target PC is running, stop now.

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
load(file,'stim');

set(handles.text_songstim_filename,'String',handles.pm.songstim_file);


% S.name
set(handles.lb_song_lists,'String',{stim.type},...
    'Max',length({stim.type}),...
    'Value',1:length({stim.type}));
set(handles.lb_song_lists,'FontSize',8);
handles.songstim=stim;

guidata(hObject,handles);



function edit_max_I_Callback(hObject, eventdata, handles)
% hObject    handle to edit_max_I (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_max_I as text
%        str2double(get(hObject,'String')) returns contents of edit_max_I as a double

MakePulse(hObject, eventdata, handles);

% --- Executes during object creation, after setting all properties.
function edit_max_I_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_max_I (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit_step_I_Callback(hObject, eventdata, handles)
% hObject    handle to edit_step_I (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_step_I as text
%        str2double(get(hObject,'String')) returns contents of edit_step_I as a double
MakePulse(hObject, eventdata, handles);

% --- Executes during object creation, after setting all properties.
function edit_step_I_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_step_I (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit_min_I_Callback(hObject, eventdata, handles)
% hObject    handle to edit_min_I (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_min_I as text
%        str2double(get(hObject,'String')) returns contents of edit_min_I as a double
MakePulse(hObject, eventdata, handles);


% --- Executes during object creation, after setting all properties.
function edit_min_I_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_min_I (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit_max_repeatN_Callback(hObject, eventdata, handles)
% hObject    handle to edit_max_repeatN (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_max_repeatN as text
%        str2double(get(hObject,'String')) returns contents of edit_max_repeatN as a double


% --- Executes during object creation, after setting all properties.
function edit_max_repeatN_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_max_repeatN (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit_current_Itr_Callback(hObject, eventdata, handles)
% hObject    handle to edit_current_Itr (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_current_Itr as text
%        str2double(get(hObject,'String')) returns contents of edit_current_Itr as a double


% --- Executes during object creation, after setting all properties.
function edit_current_Itr_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_current_Itr (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit_SongPreT_Callback(hObject, eventdata, handles)
% hObject    handle to edit_SongPreT (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_SongPreT as text
%        str2double(get(hObject,'String')) returns contents of edit_SongPreT as a double


% --- Executes during object creation, after setting all properties.
function edit_SongPreT_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_SongPreT (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit_SongPostT_Callback(hObject, eventdata, handles)
% hObject    handle to edit_SongPostT (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_SongPostT as text
%        str2double(get(hObject,'String')) returns contents of edit_SongPostT as a double


% --- Executes during object creation, after setting all properties.
function edit_SongPostT_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_SongPostT (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit_StimInterval_Callback(hObject, eventdata, handles)
% hObject    handle to edit_StimInterval (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_StimInterval as text
%        str2double(get(hObject,'String')) returns contents of edit_StimInterval as a double


% --- Executes during object creation, after setting all properties.
function edit_StimInterval_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_StimInterval (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbutton6.
function pushbutton6_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on selection change in popup_data_to_show.
function popup_data_to_show_Callback(hObject, eventdata, handles)
% hObject    handle to popup_data_to_show (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns popup_data_to_show contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popup_data_to_show
update_axes_SF_hist(hObject,eventdata,handles);


% --- Executes during object creation, after setting all properties.
function popup_data_to_show_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popup_data_to_show (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbutton7.
function pushbutton7_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on selection change in popup_stimulus_to_show.
function popup_stimulus_to_show_Callback(hObject, eventdata, handles)
% hObject    handle to popup_stimulus_to_show (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns popup_stimulus_to_show contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popup_stimulus_to_show

update_axes_SF_hist(hObject,eventdata,handles);


% --- Executes during object creation, after setting all properties.
function popup_stimulus_to_show_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popup_stimulus_to_show (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% function handles=init_rectime_param(handles)
% 
% handles.SF.SongPreT     =eval(get(handles.edit_SongPreT,'String'));
% handles.SF.SongPostT    =eval(get(handles.edit_SongPostT,'String'));
% handles.SF.intervalT=eval(get(handles.edit_StimInterval));
% handles.SF.decimation=2;
% handles.SF.SampRate = handles.pm.SampRate;
% handles.SF.decimation = handles.pm.decimation;
% 
% handles.pm.preT_nbin         =ceil(handles.SF.SongPreT*handles.SF.SampRate/handles.SF.decimation);
% handles.pm.postT_nbin        =ceil(handles.SF.SongPostT*handles.SF.SampRate/handles.SF.decimation);


function [SongPreT,SongPostT,SongStimSelection,...
    SongDur,SongDurN,StimNames,StimFileName]=...
    return_SongStimRecParam(hObject,eventdata,handles)


if get(handles.tg_OFF_songstim,'Value')
    if get(handles.tg_OFF_pulsestim,'Value')
        error('Both Song and Pulse cannot be turned off.');
    end
    SongPreT =NaN;
    SongPostT=NaN;
    SongStimSelection=NaN;
    SongDur  =NaN;
    SongDurN =NaN;
    StimNames=NaN;
    StimFileName=NaN;

else
    
    
    SongPreT            =eval(get(handles.edit_SongPreT,'String'));
    SongPostT           =eval(get(handles.edit_SongPostT,'String'));
    SongStimSelection   =get(handles.lb_song_lists,'Value');
    
    if isfield(handles,'songstim')
        for ii=1:length(handles.songstim)
            SongDur(ii)=handles.songstim(ii).t(end)-handles.songstim(ii).t(1);
            SongDurN(ii)=length(handles.songstim(ii).song);
            % Add delay in song stimulus. 
        end
    else
        errordlg('Please load SongStim first, or Turn Off.');
        error;
    end
   
    StimNames=get(handles.lb_song_lists,'String');
    StimFileName = fullfile(handles.pm.songstim_dir,handles.pm.songstim_file);


end


% intervalT=eval(get(handles.edit_StimInterval,'String'));


function [PulseDelay,...
    PulseDuration,...
    PulseInterval,...
    Pulse_TotalDur,...
    PulseStimFormat,...
    CurrentInj_schedule]=...
    return_PulseStimRecParam(hObject,eventdata,handles)


if get(handles.tg_OFF_pulsestim,'Value')
    if get(handles.tg_OFF_songstim,'Value')
        error('Both Song and Pulse cannot be turned off.');
    end
    PulseDelay      =NaN;
    PulseDuration   =NaN;
    PulseInterval   =NaN;
    Pulse_TotalDur  =NaN;
    PulseStimFormat =NaN;
    CurrentInj_schedule=NaN;
else
    
    PulseDelay     =eval(get(handles.edit_Pulse_Delay,'String'));
    PulseDuration  =eval(get(handles.edit_Pulse_Duration,'String'));
    PulseInterval  =eval(get(handles.edit_Pulse_Interval,'String'));
    
    % intervalT=eval(get(handles.edit_StimInterval,'String'));
    
    if get(handles.tg_OFF_songstim,'Value')
        Pulse_TotalDur  =eval(get(handles.edit_Pulse_TotalDur,'String'))-PulseDelay;
    else
        [SongPreT,SongPostT,SongStimSelection,SongDur,SongDurN]=return_SongStimRecParam(hObject,eventdata,handles);
        Pulse_TotalDur  =max(SongDur)+SongPreT+SongPostT-PulseDelay;
    end
    
    if PulseInterval==0
        % This is a special case, single pulse mode.
        PulseInterval=Pulse_TotalDur;
    end
%     handles.SampRate
    
    PulseStimFormat=make_pulse(...
        PulseDelay*1000,...
        Pulse_TotalDur*1000,...
        PulseDuration*1000,...
        PulseInterval*1000,...
        1,...
        handles.SampRate);
    CurrentInj_schedule=get_CurrentInj_schedule(hObject,eventdata,handles);
end


function edit_manual_I_Callback(hObject, eventdata, handles)
% hObject    handle to edit_manual_I (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_manual_I as text
%        str2double(get(hObject,'String')) returns contents of edit_manual_I as a double
MakePulse(hObject, eventdata, handles);


% --- Executes during object creation, after setting all properties.
function edit_manual_I_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_manual_I (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --------------------------------------------------------------------
function uipanel_songstim_ButtonDownFcn(hObject, eventdata, handles)
% hObject    handle to uipanel_songstim (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes when selected object is changed in panel_current_order.
function panel_current_order_SelectionChangeFcn(hObject, eventdata, handles,varargin)
% hObject    handle to the selected object in panel_current_order 
% eventdata  structure with the following fields (see UIBUTTONGROUP)
%	EventName: string 'SelectionChanged' (read only)
%	OldValue: handle of the previously selected object or empty if none was selected
%	NewValue: handle of the currently selected object
% handles    structure with handles and user data (see GUIDATA)

mode=get(get(handles.panel_current_order,'SelectedObject'),'Tag');
manual_group=[handles.edit_manual_I];
non_manual_group=[handles.edit_max_I,handles.edit_step_I,handles.edit_min_I];

if nargin==4
    mode=varargin{1};
end

switch mode
    case 'rb_manual_I'
        disp('Manually set current injections');
        set(manual_group,'Enable','On');
        set(non_manual_group,'Enable','Off');
    case {'rb_order_I','rb_random_I'}
         disp('Use current injections with buttons')
        set(manual_group,'Enable','Off');
        set(non_manual_group,'Enable','On');
    case 'TurnOff'
          set(manual_group,'Enable','Off');
        set(non_manual_group,'Enable','Off');
    otherwise
        error('Unknown radio button Tag (%s)!',mode);
end

CurrentInj_schedule=get_CurrentInj_schedule(hObject,eventdata,handles);

function CurrentInj_schedule=get_CurrentInj_schedule(hObject,eventdata,handles)

mode=get(get(handles.panel_current_order,'SelectedObject'),'Tag');
manual_group=[handles.edit_manual_I];
non_manual_group=[handles.edit_max_I,handles.edit_step_I,handles.edit_min_I];

switch mode
    case 'rb_manual_I'
      CurrentInj_schedule=eval(get(handles.edit_manual_I,'String'));
    case {'rb_order_I'}
       CurrentInj_schedule=eval(get(handles.edit_min_I,'String')):eval(get(handles.edit_step_I,'String')):eval(get(handles.edit_max_I,'String'));
    case 'rb_random_I'
        CurrentInj_schedule=eval(get(handles.edit_min_I,'String')):eval(get(handles.edit_step_I,'String')):eval(get(handles.edit_max_I,'String'));
        ind=randperm(length(CurrentInj_schedule));
        CurrentInj_schedule=CurrentInj_schedule(ind);
    otherwise
       error('Unknown radio button Tag (%s)!',mode);
end


% --- Executes during object creation, after setting all properties.
function panel_current_order_CreateFcn(hObject, eventdata, handles)
% hObject    handle to panel_current_order (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called


function handles=init_params(hObject,eventdata,handles)
%
handles.SF.ME1_Hfactor=0.1; % input current is 10*Hfactor*nA/V.
handles.SF.Vmfactor=0.1*1.e3; % output voltage from AxoClamp2B is 10Vm. To make it mV, also used 1.e-3.

axes(handles.axes_SF_stim_sonogram);
% chld=get('Children',handles.vol_axe)
fn=fieldnames(handles.SF);
h=find(strcmp(fn, 'stim_sonogram_image'));
if (~isempty(h)&&ishandle(handles.SF.stim_sonogram_image)),
    delete(handles.SF.stim_sonogram_image);
end
handles.SF.stim_sonogram_image=imagesc([1:10],[1:10],zeros(10,10));hold on;

h=find(strcmp(fn, 'vm_plot'));
if (~isempty(h)&&ishandle(handles.SF.vm_plot)),
    delete(handles.SF.vm_plot);
end
axes(handles.axes_SF_vm);
handles.SF.vm_plot=plot([NaN,NaN],[NaN,NaN],'k');
set(handles.axes_SF_vm,'YLim',[-100 50]);

linkaxes([handles.axes_SF_stim_sonogram,handles.axes_SF_vm,handles.axes_SF_Pulse],'x');

function varargout=push_data_Callback(hObject,eventdata,handles,vm,paramtmp,varargin)
% if nargin>=4
%    vm=varargin{1};
% end
% 
% if nargin>=5
%     paramtmp=varargin{2};
% end


vm = vm*100; % to make it mV.
spk=voltage2spkmatrix(vm,20,ceil(0.003*handles.SampRate));

% param = getappdata(handles.axes_SF_hist,'param');
vm_struct  = getappdata(handles.axes_SF_hist,'vm_struct');
spk_struct  = getappdata(handles.axes_SF_hist,'spk_struct');

% cbdata is all column vector.
vm_struct(paramtmp.Song_ind,paramtmp.I_ind).data=...
    [vm_struct(paramtmp.Song_ind,paramtmp.I_ind).data,vm];

% Note, spk_struct put data in each column, because
% sparse matrix becomes slow if we put data in each row.
spk_struct(paramtmp.Song_ind,paramtmp.I_ind).data=...
    [spk_struct(paramtmp.Song_ind,paramtmp.I_ind).data,spk(:)];

if length(vm_struct(paramtmp.Song_ind,paramtmp.I_ind).t)~=length(vm),
    vm_struct(paramtmp.Song_ind,paramtmp.I_ind).t = linspace(0,2*length(vm)/handles.SampRate,length(vm));
    spk_struct(paramtmp.Song_ind,paramtmp.I_ind).t = vm_struct(paramtmp.Song_ind,paramtmp.I_ind).t;
end
    

setappdata(handles.axes_SF_hist,'vm_struct',vm_struct);
setappdata(handles.axes_SF_hist,'spk_struct',spk_struct);

update_axes_SF_hist(handles.axes_SF_hist,eventdata,handles);

function varargout=update_axes_SF_hist(hObject,eventdata,handles)

StimToShow=get(handles.popup_stimulus_to_show,'String');
StimToShow=StimToShow{get(handles.popup_stimulus_to_show,'Value')};
Song_ind=get(handles.popup_stimulus_to_show,'Value');

DataToShow=get(handles.popup_data_to_show,'String');
DataToShow=DataToShow{get(handles.popup_data_to_show,'Value')};

AnalysisMethod=get(handles.popup_method_to_analyze,'String');
AnalysisMethod=AnalysisMethod{get(handles.popup_method_to_analyze,'Value')};

fprintf('%s:%s:%s\n',StimToShow,DataToShow,AnalysisMethod);

DataToShow=strrep(DataToShow,'\n','');
AnalysisMethod=strrep(AnalysisMethod,'\n','');

switch DataToShow
    case 'spike'
        x  = getappdata(handles.axes_SF_hist,'spk_struct')'; % make it row vector as one trial.
        
        t=x(Song_ind,1).t;
        x=[x(Song_ind,:).data]';
        x=(x~=0);
    case 'vm'
        x  = getappdata(handles.axes_SF_hist,'vm_struct');
        t=x(Song_ind,1).t;
        x=[x(Song_ind,:).data]';

    otherwise
        error('Unknown DataToShow (%s)',DataToShow);
end


 axes(handles.axes_SF_hist);cla;
%  size(x)
 
 
switch AnalysisMethod
    case 'heatmap'
       
        imagesc(t,1:size(x,1),x);
        medx=median(x,1);
        if ~isnan(medx)
            minmedianx=min(median(x,1));
            caxis([minmedianx,minmedianx+20]);
            colormap jet;
        end
    case 'raster'
       spikeraster(x,t);
    case 'overlaid_plot'
        plot(t,x);
    otherwise
        error('Unknown AnalysisMethod (%s)',AnalysisMethod);
end



    
function varargout=StimFamily_state_Callback(hObject,eventdata,handles,varargin)
% disp('Init Stimulus Family');
% handles



if nargin==4
    opt=varargin{1};
else
    error;
end

% When define_stimulus_set is pressed, 
% RealSong_control() execute the following 'init',
% 'return_SongStimRecParam', 'return_PulseStimRecParam'.

switch opt
    case 'init'
        disp('Init Stimulus Family');
         
        SF.song_ind=1;
        SF.Iteration = 1;
        SF.Totaliteration=1;
        SF.CurrentInj_ind=0;
        SF.maxItr =eval(get(handles.edit_max_repeatN,'String'));
        
        StimInterval=eval(get(handles.edit_StimInterval,'String'));
        
        
        varargout{1}=SF.maxItr;
        varargout{2}=StimInterval;
        setappdata(handles.uipanel_Info,'SF',SF);
        
    case 'return_SongStimRecParam'

    [SongPreT,SongPostT,SongStimSelection,...
    SongDur,SongDurN,StimNames,StimFileName]=...
    return_SongStimRecParam(hObject,eventdata,handles);
        

        varargout{1}=SongPreT;
        varargout{2}=SongPostT;
        varargout{3}=SongStimSelection;
        varargout{4}=SongDur;
        varargout{5}=SongDurN;
        varargout{6}=StimNames;
        varargout{7}=StimFileName;
        
    case 'return_PulseStimRecParam'
        [PulseDelay,PulseDuration,PulseInterval,...
            Pulse_TotalDur,PulseStimFormat,CurrentInj_schedule]=...
    return_PulseStimRecParam(hObject,eventdata,handles);

        varargout{1}=PulseDelay;
        varargout{2}=PulseDuration;
        varargout{3}=PulseInterval;
        varargout{4}=Pulse_TotalDur;
        varargout{5}=PulseStimFormat;
        varargout{6}=CurrentInj_schedule;
    case 'init_Iteration'
 
         SF= getappdata(handles.uipanel_Info,'SF');
         SF.song_ind=1;
         SF.Iteration=1;
         SF.CurrentInj_ind=0;
         
         setappdata(handles.uipanel_Info,'SF',SF);
    case 'next_State'
        
        if ~get(handles.tg_define_stimli_xPC,'Value')
            errordlg('Define the stimli set by pressing "Define Stimli Set" button in Stimlus Manager Before you start.');
            return;
        end
        SF= getappdata(handles.uipanel_Info,'SF');
%           SF.maxItr 
        SelectedSong_ind=get(handles.lb_song_lists,'Value');
        SongSets=get(handles.lb_song_lists,'String');
        SelectedSongSets={SongSets{get(handles.lb_song_lists,'Value')}};
        CurrentInj_schedule=get_CurrentInj_schedule(hObject,eventdata,handles);
        
        % If current injection schedule is done for one cycle, move to next song.
        % Reset SF.CurrentInj_ind to zero.
        SF.CurrentInj_ind=SF.CurrentInj_ind+1;
        if SF.CurrentInj_ind>length(CurrentInj_schedule)
            SF.song_ind=SF.song_ind+1;
            SF.CurrentInj_ind=1;
        end
        
        % Now, if song stimulus is done for one cycle, increment Iteration number.
        % Reset CurrentSong_ind.
        if SF.song_ind>length(SelectedSongSets)
            SF.Iteration = SF.Iteration +1;
            SF.Totaliteration=SF.Totaliteration+1;
            SF.song_ind=1;
        end
        
        SF.CurrentSong_ind=SelectedSong_ind(SF.song_ind);
        
        
        
        if SF.Iteration>SF.maxItr
            SF.CurrentInj_ind=[];
            SF.CurrentSong_ind=[];
            SF.Iteration=      SF.maxItr;
        end
%         SF
        txt={sprintf('Iteration: %d (in total %d)',SF.Iteration,SF.Totaliteration),...
            sprintf('Song: %s',SongSets{SF.CurrentSong_ind}),...
            sprintf('I   =%5.3fpA',CurrentInj_schedule(SF.CurrentInj_ind))};
        set(handles.text_status_window,'String',txt);
        
        StimInterval=eval(get(handles.edit_StimInterval,'String'));
        
        varargout{1} = SF.CurrentInj_ind;
        varargout{2} = SF.CurrentSong_ind;
        varargout{3} = SF.Iteration;
        varargout{4} = StimInterval;
        
        % set(handles.lb_song_lists,'Value',CurrentSong_ind);
        drawnow;
        setappdata(handles.uipanel_Info,'SF',SF);
          
    case 'current_State'
        SF=getappdata(handles.uipanel_Info,'SF');
        varargout{1} = SF.CurrentInj_ind;
        varargout{2} = SF.CurrentSong_ind;
        varargout{3} = SF.Iteration;
        varargout{4} = StimInterval;
    otherwise
        error('Unknown option in StimFamily_state_Callback (%s)',opt);
end

guidata(hObject,handles);



% --- Executes on button press in pb_designsong.
function pb_designsong_Callback(hObject, eventdata, handles)
% hObject    handle to pb_designsong (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

songedit_03p2;


% --- Executes on button press in tg_define_stimli_xPC.
function tg_define_stimli_xPC_Callback(hObject, eventdata, handles)
% hObject    handle to tg_define_stimli_xPC (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% send stimulus information to RealSong_control.
feval(handles.main_mfile,'control_StimFamily',...
    handles.ParentGUI,eventdata,guidata(handles.ParentGUI),'init',handles.figure_StimFamily_Manager);

fix_handles=[...
    handles.edit_SongPreT,...
    handles.edit_SongPostT,...
    handles.lb_song_lists,...
    handles.edit_Pulse_Delay,...
    handles.edit_Pulse_Duration,...
    handles.edit_Pulse_Interval,...
    handles.edit_max_repeatN];

if get(hObject,'Value')
    State='Off';
    disp('Define Stimulus set. Fix the parameters.')
    panel_current_order_SelectionChangeFcn(hObject, eventdata, handles,'TurnOff');
    
    [SongPreT,SongPostT,SongStimSelection,...
        SongDur,SongDurN,StimNames,StimFileName]=...
        return_SongStimRecParam(hObject,eventdata,handles);
    
    param.SongPreT = SongPreT;
    param.SongPostT = SongPostT;
    param.SongStimSelection = SongStimSelection;
    param.SongDur = SongDur;
    param.SongDurN = SongDurN;
    param.StimNames = StimNames;
    param.StimFileName=StimFileName;
    
    param.SelectedStimNames={StimNames{SongStimSelection}};
    
    param.SongStimData= handles.songstim(SongStimSelection);
    
    [PulseDelay,PulseDuration,PulseInterval,...
        Pulse_TotalDur,PulseStimFormat,CurrentInj_schedule]=...
        return_PulseStimRecParam(hObject,eventdata,handles);
    
    param.PulseDelay=PulseDelay;
    param.PulseDuration=PulseDuration;
    param.PulseInterval=PulseInterval;
    param.Pulse_TotalDur=Pulse_TotalDur;
    param.PulseStimFormat=PulseStimFormat;
    param.CurrentInj_schedule = CurrentInj_schedule;
    
    
    vm_struct=[];
    spk_struct=[];
    for ii=1:length(SongStimSelection)
        for jj=1:length(CurrentInj_schedule)
            vm_struct(ii,jj).data=[];
            spk_struct(ii,jj).data=[];
            % Note that, stimlus are encoded in 2*SampRate.
           TotalN = ceil(SongDurN(SongStimSelection(ii))/2)+ceil((SongPreT+SongPostT)*handles.SampRate);
            vm_struct(ii,jj).t   = linspace(0,TotalN/handles.SampRate+1,TotalN);
            vm_struct(ii,jj).t   = vm_struct(ii,jj).t(1:end-1) ;
            spk_struct(ii,jj).t  = vm_struct(ii,jj).t ;
        end
    end
    
    setappdata(handles.axes_SF_hist,'param',param);
    setappdata(handles.axes_SF_hist,'vm_struct',vm_struct);
    setappdata(handles.axes_SF_hist,'spk_struct',spk_struct);
    
    set(handles.popup_stimulus_to_show,'String',param.SelectedStimNames);
else
    State='On';
     disp('Undefine Stimulus set. Release the parameters.')
     panel_current_order_SelectionChangeFcn(hObject, eventdata, handles);

end
set(fix_handles,'Enable',State);

 




function edit_Pulse_Delay_Callback(hObject, eventdata, handles)
% hObject    handle to edit_Pulse_Delay (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_Pulse_Delay as text
%        str2double(get(hObject,'String')) returns contents of edit_Pulse_Delay as a double
MakePulse(hObject, eventdata, handles);


% --- Executes during object creation, after setting all properties.
function edit_Pulse_Delay_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_Pulse_Delay (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit_Pulse_Duration_Callback(hObject, eventdata, handles)
% hObject    handle to edit_Pulse_Duration (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_Pulse_Duration as text
%        str2double(get(hObject,'String')) returns contents of edit_Pulse_Duration as a double
MakePulse(hObject, eventdata, handles);


% --- Executes during object creation, after setting all properties.
function edit_Pulse_Duration_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_Pulse_Duration (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit_Pulse_Interval_Callback(hObject, eventdata, handles)
% hObject    handle to edit_Pulse_Interval (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_Pulse_Interval as text
%        str2double(get(hObject,'String')) returns contents of edit_Pulse_Interval as a double
MakePulse(hObject, eventdata, handles);


% --- Executes during object creation, after setting all properties.
function edit_Pulse_Interval_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_Pulse_Interval (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in tg_OFF_pulsestim.
function tg_OFF_pulsestim_Callback(hObject, eventdata, handles)
% hObject    handle to tg_OFF_pulsestim (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of tg_OFF_pulsestim

Pulse_button_handles=[handles.edit_Pulse_Delay,...
    handles.edit_Pulse_Duration,...
    handles.edit_Pulse_Interval,...
    handles.edit_Pulse_TotalDur];

val=get(hObject,'Value');

if (val)
    set(Pulse_button_handles,'Enable','Off');
else
     set(Pulse_button_handles,'Enable','On');
end

function edit_Pulse_TotalDur_Callback(hObject, eventdata, handles)
% hObject    handle to edit_Pulse_TotalDur (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_Pulse_TotalDur as text
%        str2double(get(hObject,'String')) returns contents of edit_Pulse_TotalDur as a double

MakePulse(hObject, eventdata, handles);

% --- Executes during object creation, after setting all properties.
function edit_Pulse_TotalDur_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_Pulse_TotalDur (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in tg_OFF_songstim.
function tg_OFF_songstim_Callback(hObject, eventdata, handles)
% hObject    handle to tg_OFF_songstim (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of tg_OFF_songstim

val=get(hObject,'Value');
songstim_button_handles=[handles.lb_song_lists,...
    handles.edit_SongPreT,handles.edit_SongPostT,...
    handles.pb_load_songstim,handles.pb_designsong];

if (val)
    fprintf('No Song Stimuli\n');
    set(handles.edit_Pulse_TotalDur,'Visible','On');
    set(handles.text_Pulse_Total_Dur,'String','TotalDur:');
    set(songstim_button_handles,'Enable','Off');
else
     set(handles.edit_Pulse_TotalDur,'Visible','Off');
    set(handles.text_Pulse_Total_Dur,'String','TotalDur: Follows Song Stimulus duration');
    set(songstim_button_handles,'Enable','On');
end


% --- Executes on button press in pb_MakePulse.
function handles=MakePulse(hObject, eventdata, handles)
% hObject    handle to pb_MakePulse (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

CurrentInj_schedule=get_CurrentInj_schedule(hObject,eventdata,handles);

 [PulseDelay,PulseDuration,PulseInterval,Pulse_TotalDur,PulseStimFormat]=...
    return_PulseStimRecParam(hObject,eventdata,handles);


pulse_t=linspace(0,length(PulseStimFormat)/handles.SampRate,length(PulseStimFormat)+1);
pulse_t=pulse_t(1:end-1);

% size(pulse)

axes(handles.axes_SF_Pulse);
plot(pulse_t,CurrentInj_schedule(:)*PulseStimFormat(:)','Color',[.5 .5 .5]);
guidata(hObject,handles);


% --- Executes during object deletion, before destroying properties.
function figure_StimFamily_Manager_DeleteFcn(hObject, eventdata, handles)
% hObject    handle to figure_StimFamily_Manager (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
disp('Saving parameters...')
previous_parameter_name=sprintf('%s_previous_param',mfilename);
save(previous_parameter_name,'handles')


% --- Executes on selection change in popup_method_to_analyze.
function popup_method_to_analyze_Callback(hObject, eventdata, handles)
% hObject    handle to popup_method_to_analyze (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns popup_method_to_analyze contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popup_method_to_analyze
update_axes_SF_hist(hObject,eventdata,handles);



% --- Executes during object creation, after setting all properties.
function popup_method_to_analyze_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popup_method_to_analyze (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pb_savedata.
function pb_savedata_Callback(hObject, eventdata, handles)
% hObject    handle to pb_savedata (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
param= getappdata(handles.axes_SF_hist,'param');
vm_struct  = getappdata(handles.axes_SF_hist,'vm_struct');
spk_struct  = getappdata(handles.axes_SF_hist,'spk_struct');

try
    [handles.pm.savename, handles.pm.save_pathname] = uiputfile(fullfile(handles.pm.save_pathname,handles.pm.savename), 'Save StimFamily data as');
catch
    [handles.pm.savename, handles.pm.save_pathname] = uiputfile('*.mat', 'Save data as');
end

save(fullfile(handles.pm.save_pathname,handles.pm.savename),'param','vm_struct','spk_struct');

guidata(hObject,handles);