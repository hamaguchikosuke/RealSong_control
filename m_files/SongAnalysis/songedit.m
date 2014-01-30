function varargout = songedit(varargin)
% SONGEDIT M-file for songedit.fig
%      SONGEDIT, by itself, creates a new SONGEDIT or raises the existing
%      singleton*.
%
%      H = SONGEDIT returns the handle to a new SONGEDIT or the handle to
%      the existing singleton*.
%
%      SONGEDIT('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in SONGEDIT.M with the given input arguments.
%
%      SONGEDIT('Property','Value',...) creates a new SONGEDIT or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before songedit_OpeningFunction gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to songedit_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help songedit

% Last Modified by GUIDE v2.5 09-Jun-2008 18:24:11

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @songedit_OpeningFcn, ...
                   'gui_OutputFcn',  @songedit_OutputFcn, ...
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


% --- Executes just before songedit is made visible.
function songedit_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to songedit (see VARARGIN)

% Obtain song data.
[filename, pathname, filterindex] = uigetfile('*.wav', 'Pick a song (.wav) file');
[handles.ss.song,handles.ss.F,handles.ss.NBits]=wavread([pathname,filename]);

handles.ss.t   = linspace(0,length(handles.ss.song)/handles.ss.F,length(handles.ss.song));

% song vector is row vector.
if size(handles.ss.song,1)~=1,    handles.ss.song=handles.ss.song';end


axes(handles.Original_Song_Amplitude);
set(handles.Original_Song_Amplitude,'XTickLabel',[]);
plot(handles.ss.t,handles.ss.song);
axis([handles.ss.t(1) handles.ss.t(end) ylim]);

axes(handles.Original_Song_Specgram);

nfft = 1012;
fftwindow=nfft;
numoverlap=ceil(nfft/1.1);

specgram(handles.ss.song,nfft,handles.ss.F,fftwindow,numoverlap);
axis([handles.ss.t(1) handles.ss.t(end) ylim]);

zoom on;

% initialize modified song data.
handles.ms.t    =[];
handles.ms.song =[];
handles.ms.F    =handles.ss.F;
handles.ms.NBits=handles.ss.NBits;


% Choose default command line output for songedit
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes songedit wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = songedit_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in Play_Original_Song.
function Play_Original_Song_Callback(hObject, eventdata, handles)
% hObject    handle to Play_Original_Song (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


tt=get(handles.Original_Song_Specgram,'XLim'); 
tti=ceil(tt*handles.ss.F)+1;

tti(1)=max(1,tti(1));  % start index > 1.
tti(2)=min(length(handles.ss.song),tti(2)); % end index < length(song)

% sound(ss.song(tti(1):tti(2)),ss.F);

sound(handles.ss.song(tti(1):tti(2)),handles.ss.F);

% --- Executes on button press in Add_Song_to_ModSong.
function Add_Song_to_ModSong_Callback(hObject, eventdata, handles)
% hObject    handle to Add_Song_to_ModSong (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

tt=get(handles.Original_Song_Specgram,'XLim'); 
ttd = diff(tt);

tti=ceil(tt*handles.ms.F)+1;

tti(1)=max(1,tti(1));  % start index > 1.
tti(2)=min(length(handles.ss.song),tti(2)); % end index < length(song)

if isempty(handles.ms.t),    maxt = 0; else,    maxt=max(handles.ms.t);end
t = linspace(0,ttd,diff(tti)+1)+maxt;

handles.ms.t_old=handles.ms.t;
handles.ms.song_old=handles.ms.song;
handles.ms.t = [handles.ms.t,t];
handles.ms.song=[handles.ms.song,handles.ss.song(tti(1):tti(2))];

axes(handles.Modified_Song_Amplitude); 
plot(handles.ms.t,handles.ms.song);
axis([handles.ms.t(1) handles.ms.t(end) ylim]);

axes(handles.Modified_Song_Specgram); 

nfft = 1012;
fftwindow=nfft;
numoverlap=ceil(nfft/1.1);

specgram(handles.ms.song,nfft,handles.ms.F,fftwindow,numoverlap);
axis([handles.ms.t(1) handles.ms.t(end) ylim]);

guidata(hObject, handles);


% --- Executes on button press in Play_Mod_Song.
function Play_Mod_Song_Callback(hObject, eventdata, handles)
% hObject    handle to Play_Mod_Song (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


tt=get(handles.Modified_Song_Specgram,'XLim'); 
tti=ceil(tt*handles.ms.F)+1;

tti(1)=max(1,tti(1));  % start index > 1.
tti(2)=min(length(handles.ms.song),tti(2)); % end index < length(song)

sound(handles.ms.song(tti(1):tti(2)),handles.ms.F);

% --- Executes on button press in pushbutton4.
function pushbutton4_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in Add_Silence.
function Add_Silence_Callback(hObject, eventdata, handles)
% hObject    handle to Add_Silence (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


user_entry = str2double(get(handles.String_SilencePeriod,'string'));
if isnan(user_entry)
	errordlg('You must enter a numeric value','Bad Input','modal')
	return
end

handles.ms.silence_period=user_entry;


tt=handles.ms.silence_period/1000; % Convert from msec to sec.
lentt=ceil(tt*handles.ms.F)+1;      % length of tt in sampling rate F.

if isempty(handles.ms.t),    maxt = 0; else,    maxt=max(handles.ms.t);end
t = linspace(0,tt,lentt)+maxt;

handles.ms.t_old=handles.ms.t;
handles.ms.song_old=handles.ms.song;

handles.ms.t = [handles.ms.t,t];
handles.ms.song=[handles.ms.song,zeros(1,lentt)];

axes(handles.Modified_Song_Amplitude); 
plot(handles.ms.t,handles.ms.song);
axis([handles.ms.t(1) handles.ms.t(end) ylim]);

axes(handles.Modified_Song_Specgram); 

nfft = 1012;
fftwindow=nfft;
numoverlap=ceil(nfft/1.1);

specgram(handles.ms.song,nfft,handles.ms.F,fftwindow,numoverlap);
axis([handles.ms.t(1) handles.ms.t(end) ylim]);

guidata(hObject, handles);


% --- Executes during object creation, after setting all properties.
function Original_Song_Specgram_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Original_Song_Specgram (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: place code in OpeningFcn to populate Original_Song_Specgram





function String_SilencePeriod_Callback(hObject, eventdata, handles)
% hObject    handle to String_SilencePeriod (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of String_SilencePeriod as text
%        str2double(get(hObject,'String')) returns contents of String_SilencePeriod as a double


% --- Executes during object creation, after setting all properties.
function String_SilencePeriod_CreateFcn(hObject, eventdata, handles)
% hObject    handle to String_SilencePeriod (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.

if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end






% --- Executes on button press in Add_Noise.
function Add_Noise_Callback(hObject, eventdata, handles)
% hObject    handle to Add_Noise (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in Clr_Song.
function Clr_Song_Callback(hObject, eventdata, handles)
% hObject    handle to Clr_Song (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
handles.ms.t    =[];
handles.ms.song =[];

Child = get(handles.Modified_Song_Amplitude,'Children');
set(Child,'XData',[],'YData',[]); 


Child = get(handles.Modified_Song_Specgram,'Children');
set(Child,'XData',[],'YData',[],'CData',[]); 

guidata(hObject, handles);



% --- Executes on button press in Save_Mod_Song.
function Save_Mod_Song_Callback(hObject, eventdata, handles)
% hObject    handle to Save_Mod_Song (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


[filename, pathname] = uiputfile({'*.wav';'*.*'}, 'Save Modified Song Data as');
wavwrite(handles.ms.song,handles.ms.F,handles.ms.NBits,[pathname,filename])



% --- Executes on button press in Back_bottun.
function Back_bottun_Callback(hObject, eventdata, handles)
% hObject    handle to Back_bottun (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

handles.ms.t    =handles.ms.t_old;
handles.ms.song =handles.ms.song_old;

Child = get(handles.Modified_Song_Amplitude,'Children');
set(Child,'XData',handles.ms.t,'YData',handles.ms.song); 

axes(handles.Modified_Song_Specgram); 

nfft = 1012;
fftwindow=nfft;
numoverlap=ceil(nfft/1.1);

specgram(handles.ms.song,nfft,handles.ms.F,fftwindow,numoverlap);
axis([handles.ms.t(1) handles.ms.t(end) ylim]);

guidata(hObject, handles);
