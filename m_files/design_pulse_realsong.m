function varargout = design_pulse_realsong(varargin)
% DESIGN_PULSE_REALSONG M-file for design_pulse_realsong.fig
%      DESIGN_PULSE_REALSONG, by itself, creates a new DESIGN_PULSE_REALSONG or raises the existing
%      singleton*.
%
%      H = DESIGN_PULSE_REALSONG returns the handle to a new DESIGN_PULSE_REALSONG or the handle to
%      the existing singleton*.
%
%      DESIGN_PULSE_REALSONG('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in DESIGN_PULSE_REALSONG.M with the given input arguments.
%
%      DESIGN_PULSE_REALSONG('Property','Value',...) creates a new DESIGN_PULSE_REALSONG or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before design_pulse_realsong_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to design_pulse_realsong_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help design_pulse_realsong

% Last Modified by GUIDE v2.5 04-Oct-2012 14:53:06

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @design_pulse_realsong_OpeningFcn, ...
                   'gui_OutputFcn',  @design_pulse_realsong_OutputFcn, ...
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


% --- Executes just before design_pulse_realsong is made visible.
function design_pulse_realsong_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to design_pulse_realsong (see VARARGIN)

% Choose default command line output for design_pulse_realsong
handles.output = hObject;


mainGuiInput = find(strcmp(varargin, 'RealSong_main'));
if (isempty(mainGuiInput)) ...
    || (length(varargin) <= mainGuiInput) ...
    || (~ishandle(varargin{mainGuiInput+1}))

    disp('design_pulse_realsong (Standalone) mode');
else % for the case of RealSong_main
    % Remember the handle, and adjust our position
    handles.ParentGUI = varargin{mainGuiInput+1};  
    % Obtain handles using GUIDATA with the caller's handle 
    handles.ParentHandles = guidata(handles.ParentGUI);
    disp('design_pulse (RealSong) mode');

end

 
fn=fieldnames(handles);
initialized=strmatch('amp',fn);

if isempty(initialized) %yet initialized
    fprintf('Initializing parameters...\n')
    handles=init_parameters(hObject,eventdata,handles);  
else %
    % do nothing.
end

handles=pb_MakePulse_Callback(hObject, eventdata, handles);
% Update handles structure
guidata(hObject, handles);
% out=handles.design_pulse_realsong_figure;
% assignin('base','designpulse_handle',handles)

% UIWAIT makes design_pulse_realsong wait for user response (see UIRESUME)
% uiwait(handles.figure1);

function handles=init_parameters(hObject,eventdata,handles)

handles.amp         = 5000;     % [mV]
handles.delay       = 0;        %[ms]
handles.singlepulseT=0.5;       %[ms]
handles.InterPulseT = 100;      %[ms]
handles.burstT      = 100;      %[ms]
handles.Fs          = 44100;    % [Hz]
handles.pulse       =[];
handles.t           =[];

set(handles.ed_Amp,'String',num2str(handles.amp));
set(handles.ed_delay,'String',num2str(handles.delay));
set(handles.ed_single_pulse_duration,'String',num2str(handles.singlepulseT));
set(handles.ed_InterPulseDuration,'String',num2str(handles.InterPulseT));
set(handles.ed_burstT,'String',num2str(handles.burstT));
set(handles.ed_SampFreq,'String',num2str(handles.Fs));
   

% --- Outputs from this function are returned to the command line.
function varargout = design_pulse_realsong_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;



function ed_burstT_Callback(hObject, eventdata, handles)
% hObject    handle to ed_burstT (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of ed_burstT as text
%        str2double(get(hObject,'String')) returns contents of ed_burstT as a double

handles.burstT=eval(get(hObject,'String'));

handles=pb_MakePulse_Callback(hObject, eventdata, handles);
guidata(hObject, handles);



function ed_delay_Callback(hObject, eventdata, handles)
% hObject    handle to ed_delay (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of ed_delay as text
%        str2double(get(hObject,'String')) returns contents of ed_delay as a double

handles.delay=eval(get(hObject,'String'));

handles=pb_MakePulse_Callback(hObject, eventdata, handles);
guidata(hObject, handles);




function ed_single_pulse_duration_Callback(hObject, eventdata, handles)
% hObject    handle to ed_single_pulse_duration (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of ed_single_pulse_duration as text
%        str2double(get(hObject,'String')) returns contents of ed_single_pulse_duration as a double

handles.singlepulseT=eval(get(hObject,'String'));

handles=pb_MakePulse_Callback(hObject, eventdata, handles);
guidata(hObject, handles);



function ed_InterPulseDuration_Callback(hObject, eventdata, handles)
% hObject    handle to ed_InterPulseDuration (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of ed_InterPulseDuration as text
%        str2double(get(hObject,'String')) returns contents of ed_InterPulseDuration as a double

handles.InterPulseT=eval(get(hObject,'String'));

handles=pb_MakePulse_Callback(hObject, eventdata, handles);
guidata(hObject, handles);



% --- Executes on button press in rb_SingePulse.
function rb_SingePulse_Callback(hObject, eventdata, handles)
% hObject    handle to rb_SingePulse (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of rb_SingePulse

handles.is_single_pulsemode=get(hObject,'Value');
if (handles.is_single_pulsemode)
    set(handles.ed_InterPulseDuration,...
        'String',num2str(handles.burstT),...
        'Enable','off');
    handles.InterPulseT=handles.burstT;
else
      set(handles.ed_InterPulseDuration,...
          'Enable','on');
end
handles=pb_MakePulse_Callback(hObject, eventdata, handles);
guidata(hObject, handles);

% --- Executes on button press in pb_MakePulse.
function handles=pb_MakePulse_Callback(hObject, eventdata, handles)
% hObject    handle to pb_MakePulse (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

handles.delay=eval(get(handles.ed_delay,'String'));
handles.singlepulseT =eval(get(handles.ed_single_pulse_duration,'String'));
handles.InterPulseT  =eval(get(handles.ed_InterPulseDuration,'String'));
handles.burstT =eval(get(handles.ed_burstT,'String'));
handles.ref    = eval(get(handles.edit_refractoriness,'String'));



handles.pulse=make_pulse(handles.delay,...
    handles.burstT,...
    handles.singlepulseT,...
    handles.InterPulseT,...
    handles.amp/1000,...
    handles.Fs);
handles.t=linspace(0,length(handles.pulse)/handles.Fs*1000,length(handles.pulse)+1);
handles.t=handles.t(1:end-1);
axes(handles.pulse_axes);
plot(handles.t,handles.pulse);
axis([-0.1*handles.t(end) handles.t(end) -0.1+min(handles.pulse) max(1,2*max(handles.pulse))])
guidata(hObject,handles);

% --- Executes on button press in pb_register.
function pb_register_Callback(hObject, eventdata, handles)
% hObject    handle to pb_register (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


if isempty(handles.pulse)
    error('You need to make a pulse first!');
end

val=get(handles.popup_FileType,'Value');
filetypes=get(handles.popup_FileType,'String');
filetype=filetypes{get(handles.popup_FileType,'Value')};


switch val
    case 1 % new file
        [savename,savedir]=uiputfile;
        stim(1).pulse=handles.pulse;
        stim(1).t   = handles.t/1000; % to make it sec.
        stim(1).Fs=handles.Fs;
        save(fullfile(savedir,savename),'stim');
        handles.savedir=savedir;
        handles.savename=savename;
    case 2
        try
            [savename,savedir]=uiputfile(fullfile(handles.savedir,handles.savename),'Append file');
        catch
            [savename,savedir]=uigetfile({'*.m';'*.mdl';'*.mat';'*.*'},'Pick an append file');
        end
        load(fullfile(savedir,savename),'stim');
        n=length(stim);
        fprintf('originally %s contains %d stimli\n',savename,n);
    
        stim(n+1).pulse=handles.pulse;
        stim(n+1).t=handles.t/1000; % to make it sec.
        stim(n+1).Fs=handles.Fs;
        save(fullfile(savedir,savename),'stim');
    otherwise
        error('Unknown option!')
end

guidata(hObject,handles);

% --- Executes on selection change in popup_FileType.
function popup_FileType_Callback(hObject, eventdata, handles)
% hObject    handle to popup_FileType (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns popup_FileType contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popup_FileType


% --- Executes during object creation, after setting all properties.
function popup_FileType_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popup_FileType (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes during object creation, after setting all properties.
function rb_SingePulse_CreateFcn(hObject, eventdata, handles)
% hObject    handle to rb_SingePulse (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called


handles.is_single_pulsemode=get(hObject,'Value');

guidata(hObject, handles);



function ed_SampFreq_Callback(hObject, eventdata, handles)
% hObject    handle to ed_SampFreq (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of ed_SampFreq as text
%        str2double(get(hObject,'String')) returns contents of ed_SampFreq as a double

Fs=str2double(get(hObject,'String'));
handles.Fs=Fs;
handles=pb_MakePulse_Callback(hObject, eventdata, handles);
guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function ed_SampFreq_CreateFcn(hObject, eventdata, handles)
% hObject    handle to ed_SampFreq (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function ed_Amp_Callback(hObject, eventdata, handles)
% hObject    handle to ed_Amp (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of ed_Amp as text
%        str2double(get(hObject,'String')) returns contents of ed_Amp as a double

% handles.amp=get(hObject,'Value');
handles.amp=str2double(get(hObject,'String'));
handles=pb_MakePulse_Callback(hObject, eventdata, handles);
guidata(hObject, handles);


% --- Executes during object creation, after setting all properties.
function ed_Amp_CreateFcn(hObject, eventdata, handles)
% hObject    handle to ed_Amp (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes during object creation, after setting all properties.
function ed_burstT_CreateFcn(hObject, eventdata, handles)
% hObject    handle to ed_burstT (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes during object creation, after setting all properties.
function ed_delay_CreateFcn(hObject, eventdata, handles)
% hObject    handle to ed_delay (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes during object creation, after setting all properties.
function ed_single_pulse_duration_CreateFcn(hObject, eventdata, handles)
% hObject    handle to ed_single_pulse_duration (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes during object creation, after setting all properties.
function ed_InterPulseDuration_CreateFcn(hObject, eventdata, handles)
% hObject    handle to ed_InterPulseDuration (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit7_Callback(hObject, eventdata, handles)
% hObject    handle to edit7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit7 as text
%        str2double(get(hObject,'String')) returns contents of edit7 as a double


% --- Executes during object creation, after setting all properties.
function edit7_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit8_Callback(hObject, eventdata, handles)
% hObject    handle to edit8 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit8 as text
%        str2double(get(hObject,'String')) returns contents of edit8 as a double


% --- Executes during object creation, after setting all properties.
function edit8_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit8 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit9_Callback(hObject, eventdata, handles)
% hObject    handle to edit9 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit9 as text
%        str2double(get(hObject,'String')) returns contents of edit9 as a double


% --- Executes during object creation, after setting all properties.
function edit9_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit9 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit10_Callback(hObject, eventdata, handles)
% hObject    handle to edit10 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit10 as text
%        str2double(get(hObject,'String')) returns contents of edit10 as a double


% --- Executes during object creation, after setting all properties.
function edit10_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit10 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


function [delay,singlepulseT,InterPulseT,burstT,amp,ref]=return_pulse_param(hObject, eventdata, handles,varargin)

delay=eval(get(handles.ed_delay,'String'));
singlepulseT =eval(get(handles.ed_single_pulse_duration,'String'));
InterPulseT  =eval(get(handles.ed_InterPulseDuration,'String'));
burstT =eval(get(handles.ed_burstT,'String'));
amp =eval(get(handles.ed_Amp,'String'));
ref = eval(get(handles.edit_refractoriness,'String'));


% --- Executes on button press in pb_updatexpc.
function pb_updatexpc_Callback(hObject, eventdata, handles)
% hObject    handle to pb_updatexpc (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

RealSong_control_010('update_dynamic_pulse',handles.ParentGUI,[],guidata(handles.ParentGUI));



function edit_refractoriness_Callback(hObject, eventdata, handles)
% hObject    handle to edit_refractoriness (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_refractoriness as text
%        str2double(get(hObject,'String')) returns contents of edit_refractoriness as a double



handles.ref=eval(get(hObject,'String'));

handles=pb_MakePulse_Callback(hObject, eventdata, handles);
guidata(hObject, handles);


% --- Executes during object creation, after setting all properties.
function edit_refractoriness_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_refractoriness (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
