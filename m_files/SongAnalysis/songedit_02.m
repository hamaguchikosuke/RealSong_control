function varargout = songedit_02(varargin)
% SONGEDIT_02 M-file for songedit_02.fig
%      SONGEDIT_02, by itself, creates a new SONGEDIT_02 or raises the existing
%      singleton*.
%
%      H = SONGEDIT_02 returns the handle to a new SONGEDIT_02 or the handle to
%      the existing singleton*.
%
%      SONGEDIT_02('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in SONGEDIT_02.M with the given input arguments.
%
%      SONGEDIT_02('Property','Value',...) creates a new SONGEDIT_02 or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before songedit_02_OpeningFunction gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to songedit_02_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help songedit_02

% Last Modified by GUIDE v2.5 02-Jun-2008 18:28:51
global handles

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @songedit_02_OpeningFcn, ...
                   'gui_OutputFcn',  @songedit_02_OutputFcn, ...
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


% --- Executes just before songedit_02 is made visible.
function songedit_02_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to songedit_02 (see VARARGIN)

% Obtain song data.
try 
    [filename, pathname, filterindex] = uigetfile('*.wav', 'Pick a song (.wav) file');
catch % In case no wave file is chosen.
    error([mfilename, ': Please chose a .wav file.']);
end

% Read wav data, and save in original song data, 'os.{song,F,Nbits}'
[handles.os.song,handles.os.F,handles.os.NBits]=wavread([pathname,filename]);

% make 1xN vector, not Nx1 vector.
if size(handles.os.song,1)~=1
    handles.os.song=handles.os.song';
end

% set time.
handles.os.t   = linspace(0,length(handles.os.song)/handles.os.F,length(handles.os.song));

% initialize upper panel song data.
handles.ss.t    =handles.os.t;
handles.ss.song =handles.os.song;
handles.ss.F    =handles.os.F;
handles.ss.NBits=handles.os.NBits;

% song vector is row vector.
if size(handles.ss.song,1)~=1,    handles.ss.song=handles.ss.song';end

% Set threshold for auto-detecting syllables.
handles.ss.thresh = 0.01; % 1% to the maximum peak;

% initialize power plot in upper panel. First, show nothing.
handles.ss.gcf_power(1)=plot(0,0);


% Reset upper panel
reset_upper_panel(hObject,handles);

zoom on;

% initialize lower panel, modified song data.
handles.ms.t    =[];
handles.ms.song =[];
handles.ms.F    =handles.ss.F;
handles.ms.NBits=handles.ss.NBits;


% Choose default command line output for songedit_02
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes songedit_02 wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = songedit_02_OutputFcn(hObject, eventdata, handles) 
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

reset_lower_panel(hObject,handles);

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

reset_lower_panel(hObject,handles);

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

[YN,noiseprop]=WhiteNoiseQApanel;

if strcmp(YN,'N')
   return;
end

nmean = noiseprop.mean;

nvar = noiseprop.var;

nlen = noiseprop.len;

nlen = nlen/1000;                          % Convert from ms to sec.
lentt=ceil(nlen*handles.ms.F)+1;      % length of tt in sampling rate F.

if isempty(handles.ms.t),    maxt = 0; else,    maxt=max(handles.ms.t);end
t = linspace(0,nlen,lentt)+maxt;

handles.ms.t_old=handles.ms.t;
handles.ms.song_old=handles.ms.song;

handles.ms.t = [handles.ms.t,t];
handles.ms.song=[handles.ms.song,sqrt(nvar)*randn(1,lentt)+nmean];


reset_lower_panel(hObject,handles);

guidata(hObject, handles);


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


reset_lower_panel(hObject,handles);

axes(handles.Modified_Song_Specgram); 

guidata(hObject, handles);


% --- Executes on button press in RB_BesselFilter.
function RB_BesselFilter_Callback(hObject, eventdata, handles)
% hObject    handle to RB_BesselFilter (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of RB_BesselFilter

Besselfilt_ON= get(hObject,'Value');

if (Besselfilt_ON)
    a = input('How many order of Bessel filter?: ');
    while a>25
        a = input('Too large a (a<=25). How many order of Bessel filter?: ');
    end
    fprintf('\nLimit freq of high-pass filter[Hz]? If 1x2 vector, \n');
    b = input('it sets [min, max] limit of band-pass filter:  ex)[0 1000]: ');
    %     [a,b]=bessel_param_inquiry;
    if isscalar(b)  % b is scalar, -> high pass filter
        [B,A]=besself(a,b/handles.os.F,'high');
    else
        [B,A]=besself(a,b/handles.os.F);
    end
    handles.ss.song=filter(B,A,handles.os.song);
    handles.besself_info = sprintf('%d-th order, %d Hz High Pass.',a,b);

else
    handles.besself_info = 'No filter';
    handles.ss.song=handles.os.song;
end
set(handles.Bessel_Filt_Info,'string',handles.besself_info);

reset_upper_panel(hObject,handles);

guidata(hObject, handles);

function Text_BesselFilter_Callback(hObject, eventdata, handles)
% hObject    handle to Text_BesselFilter (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Text_BesselFilter as text
%        str2double(get(hObject,'String')) returns contents of Text_BesselFilter as a double


% --- Executes during object creation, after setting all properties.
function Text_BesselFilter_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Text_BesselFilter (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --------------------------------------------------------------------
function Untitled_1_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


function reset_upper_panel(hObject,handles)
% re-plot upper panel
%
axes(handles.Original_Song_Amplitude);
set(handles.Original_Song_Amplitude,'XTickLabel',[]);
plot(handles.ss.t,handles.ss.song);
axis([handles.ss.t(1) handles.ss.t(end) ylim]);

axes(handles.Original_Song_Specgram);

nfft = 1012;
fftwindow=nfft;
numoverlap=ceil(nfft/1.2);

[y,f,t,p]=spectrogram(handles.ss.song,fftwindow,numoverlap,nfft,handles.ss.F);
% surf(t,f,10*log10(abs(p)),'EdgeColor','none');   view(0,90);
imagesc(t,f,10*log10(abs(p))); set(gca,'YDir','Normal');hold on;
axis([handles.ss.t(1) handles.ss.t(end) ylim]);

handles.ss.specP = p;
handles.ss.specT = t;
handles.ss.specF = f;

guidata(hObject, handles);


function reset_lower_panel(hObject,handles)
% re-plot lower panel
%

axes(handles.Modified_Song_Amplitude); 
plot(handles.ms.t,handles.ms.song);
axis([handles.ms.t(1) handles.ms.t(end) ylim]);

axes(handles.Modified_Song_Specgram); 

nfft = 1012;
fftwindow=nfft;
numoverlap=ceil(nfft/1.2);


[y,f,t,p]=spectrogram(handles.ms.song,fftwindow,numoverlap,nfft,handles.ms.F);
% surf(t,f,10*log10(abs(p)),'EdgeColor','none');   view(0,90);
imagesc(t,f,10*log10(abs(p))); set(gca,'YDir','Normal');
% specgram(handles.ms.song,nfft,handles.ms.F,fftwindow,numoverlap);
axis([handles.ms.t(1) handles.ms.t(end) ylim]);

handles.ms.specP = p;
handles.ms.specT = t;
handles.ms.specF = f;

guidata(hObject, handles);

% --- Executes on button press in Show_Power.
function Show_Power_Callback(hObject, eventdata, handles)
% hObject    handle to Show_Power (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of Show_Power


ShowPower_ON= get(hObject,'Value');

if (ShowPower_ON)
    show_power(hObject,handles)
else
     set(handles.ss.gcf_power(:),'XData',[],'YData',[]);
end

%%%%%%%%%%%%%%%%%%%%%%%
function show_power(hObject,handles)
% show power in upper panel.

axes(handles.Original_Song_Specgram);

nfft = 1012;
fftwindow=nfft;
numoverlap=ceil(nfft/1.2);

[y,f,t,p]=spectrogram(handles.ss.song,fftwindow,numoverlap,nfft,handles.ss.F);
% surf(t,f,10*log10(abs(p)),'EdgeColor','none');   view(0,90);
imagesc(t,f,10*log10(abs(p))); set(gca,'YDir','Normal');hold on;
axis([handles.ss.t(1) handles.ss.t(end) ylim]);

handles.ss.specP = p;
handles.ss.specT = t;
handles.ss.specF = f;
songpower = sum(abs(handles.ss.specP)); max_songpower=max(songpower);
%     handles.ss.gcf_power(1)=plot(handles.ss.specT,songpower/max_songpower*max(ylim),'r--');

highFind = handles.ss.specF>2000;
songpower_highF = sum(abs(handles.ss.specP(highFind,:)));
handles.ss.gcf_power(1)=plot(handles.ss.specT,songpower_highF/max_songpower*max(ylim),'b-');

axis([handles.ss.t(1) handles.ss.t(end) ylim]);

guidata(hObject, handles);

