function varargout = WhiteNoiseQApanel(varargin)
% WHITENOISEQAPANEL M-file for WhiteNoiseQApanel.fig
%      WHITENOISEQAPANEL by itself, creates a new WHITENOISEQAPANEL or raises the
%      existing singleton*.
%
%      H = WHITENOISEQAPANEL returns the handle to a new WHITENOISEQAPANEL or the handle to
%      the existing singleton*.
%      [H,noise_properties] = WHITENOISEQAPANEL returns the noise properties;
%      noise_properties.{mean,var,length}. 
%
%      WHITENOISEQAPANEL('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in WHITENOISEQAPANEL.M with the given input arguments.
%
%      WHITENOISEQAPANEL('Property','Value',...) creates a new WHITENOISEQAPANEL or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before WhiteNoiseQApanel_OpeningFunction gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to WhiteNoiseQApanel_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help WhiteNoiseQApanel

% Last Modified by GUIDE v2.5 05-Nov-2010 18:22:26

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @WhiteNoiseQApanel_OpeningFcn, ...
                   'gui_OutputFcn',  @WhiteNoiseQApanel_OutputFcn, ...
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

% --- Executes just before WhiteNoiseQApanel is made visible.
function WhiteNoiseQApanel_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to WhiteNoiseQApanel (see VARARGIN)

% Choose default command line output for WhiteNoiseQApanel
handles.output = 'Yes';
handles.noisemean = 0;
handles.noisevar  = 1;
handles.noiselength = 100;
handles.noisestart  = 100;
% Update handles structure
guidata(hObject, handles);

% Insert custom Title and Text if specified by the user
% Hint: when choosing keywords, be sure they are not easily confused 
% with existing figure properties.  See the output of set(figure) for
% a list of figure properties.
if(nargin > 3)
    for index = 1:2:(nargin-3),
        if nargin-3==index, break, end
        switch lower(varargin{index})
         case 'title'
          set(hObject, 'Name', varargin{index+1});
         case 'string'
          set(handles.text1, 'String', varargin{index+1});
        end
    end
end

% Determine the position of the dialog - centered on the callback figure
% if available, else, centered on the screen
FigPos=get(0,'DefaultFigurePosition');
OldUnits = get(hObject, 'Units');
set(hObject, 'Units', 'pixels');
OldPos = get(hObject,'Position');
FigWidth = OldPos(3);
FigHeight = OldPos(4);
if isempty(gcbf)
    ScreenUnits=get(0,'Units');
    set(0,'Units','pixels');
    ScreenSize=get(0,'ScreenSize');
    set(0,'Units',ScreenUnits);

    FigPos(1)=1/2*(ScreenSize(3)-FigWidth);
    FigPos(2)=2/3*(ScreenSize(4)-FigHeight);
else
    GCBFOldUnits = get(gcbf,'Units');
    set(gcbf,'Units','pixels');
    GCBFPos = get(gcbf,'Position');
    set(gcbf,'Units',GCBFOldUnits);
    FigPos(1:2) = [(GCBFPos(1) + GCBFPos(3) / 2) - FigWidth / 2, ...
                   (GCBFPos(2) + GCBFPos(4) / 2) - FigHeight / 2];
end
FigPos(3:4)=[FigWidth FigHeight];
set(hObject, 'Position', FigPos);
set(hObject, 'Units', OldUnits);

% UIWAIT makes WhiteNoiseQApanel wait for user response (see UIRESUME)
uiwait(handles.figure1);

% --- Outputs from this function are returned to the command line.
function varargout = WhiteNoiseQApanel_OutputFcn(hObject, eventdata, handles)
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;
noiseprop.mean= handles.noisemean;
noiseprop.var= handles.noisevar;
noiseprop.len= handles.noiselength;
noiseprop.start=handles.noisestart;
varargout{2} = noiseprop;
 
% The figure can be deleted now
delete(handles.figure1);

% --- Executes on button press in Yes_button.
function Yes_button_Callback(hObject, eventdata, handles)
% hObject    handle to Yes_button (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

handles.output = get(hObject,'String');

% Update handles structure
guidata(hObject, handles);

% Use UIRESUME instead of delete because the OutputFcn needs
% to get the updated handles structure.
uiresume(handles.figure1);

% --- Executes on button press in No_button.
function No_button_Callback(hObject, eventdata, handles)
% hObject    handle to No_button (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

handles.output = get(hObject,'String');

% Update handles structure
guidata(hObject, handles);

% Use UIRESUME instead of delete because the OutputFcn needs
% to get the updated handles structure.
uiresume(handles.figure1);


% --- Executes when user attempts to close figure1.
function figure1_CloseRequestFcn(hObject, eventdata, handles)
% hObject    handle to figure1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

if isequal(get(handles.figure1, 'waitstatus'), 'waiting')
    % The GUI is still in UIWAIT, us UIRESUME
    uiresume(handles.figure1);
else
    % The GUI is no longer waiting, just close it
    delete(handles.figure1);
end


% --- Executes on key press over figure1 with no controls selected.
function figure1_KeyPressFcn(hObject, eventdata, handles)
% hObject    handle to figure1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Check for "enter" or "escape"
if isequal(get(hObject,'CurrentKey'),'escape')
    % User said no by hitting escape
    handles.output = 'No';
    
    % Update handles structure
    guidata(hObject, handles);
    
    uiresume(handles.figure1);
end    
    
if isequal(get(hObject,'CurrentKey'),'return')
    uiresume(handles.figure1);
end    



function mean_noise_Callback(hObject, eventdata, handles)
% hObject    handle to mean_noise (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of mean_noise as text
%        str2double(get(hObject,'String')) returns contents of mean_noise as a double

user_entry = str2double(get(handles.mean_noise,'string'));
if isnan(user_entry)
	errordlg('You must enter a numeric value','Bad Input','modal')
	return
end

handles.noisemean=user_entry;

guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function mean_noise_CreateFcn(hObject, eventdata, handles)
% hObject    handle to mean_noise (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function var_noise_Callback(hObject, eventdata, handles)
% hObject    handle to var_noise (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of var_noise as text
%        str2double(get(hObject,'String')) returns contents of var_noise as a double


user_entry = str2double(get(handles.var_noise,'string'));
if isnan(user_entry)
	errordlg('You must enter a numeric value','Bad Input','modal')
	return
end

handles.noisevar=user_entry;

guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function var_noise_CreateFcn(hObject, eventdata, handles)
% hObject    handle to var_noise (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


function noise_length_Callback(hObject, eventdata, handles)
% hObject    handle to noise_length (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of noise_length as text
%        str2double(get(hObject,'String')) returns contents of noise_length as a double




user_entry = str2double(get(handles.noise_length,'string'));
if isnan(user_entry)
	errordlg('You must enter a numeric value','Bad Input','modal')
	return
end

handles.noiselength=user_entry;

guidata(hObject, handles);


% --- Executes during object creation, after setting all properties.
function noise_length_CreateFcn(hObject, eventdata, handles)
% hObject    handle to noise_length (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


user_entry = str2double(get(handles.ed_noise_start,'string'));
if isnan(user_entry)
	errordlg('You must enter a numeric value','Bad Input','modal')
	return;
end

handles.noisestart=user_entry;

guidata(hObject, handles);



function ed_noise_start_Callback(hObject, eventdata, handles)
% hObject    handle to ed_noise_start (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of ed_noise_start as text
%        str2double(get(hObject,'String')) returns contents of ed_noise_start as a double


% --- Executes during object creation, after setting all properties.
function ed_noise_start_CreateFcn(hObject, eventdata, handles)
% hObject    handle to ed_noise_start (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


