function varargout = songedit_03(varargin)
% SONGEDIT_03 M-file for songedit_03.fig
%      SONGEDIT_03, by itself, creates a new SONGEDIT_03 or raises the existing
%      singleton*.
%
%      H = SONGEDIT_03 returns the handle to a new SONGEDIT_03 or the handle to
%      the existing singleton*.
%
%      SONGEDIT_03('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in SONGEDIT_03.M with the given input arguments.
%
%      SONGEDIT_03('Property','Value',...) creates a new SONGEDIT_03 or raises the
%      existing singleton*.  Starting from the left, property value pairs
%      are
%      applied to the GUI before songedit_03_OpeningFunction gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to songedit_03_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help songedit_03

% Last Modified by GUIDE v2.5 15-Apr-2013 20:28:10


% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @songedit_03_OpeningFcn, ...
                   'gui_OutputFcn',  @songedit_03_OutputFcn, ...
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


% --- Executes just before songedit_03 is made visible.
function songedit_03_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to songedit_03 (see VARARGIN)

% 1. load original song data
% 2. reset systhesized song, clear synthesized song.
% 3. redraw original song, sonogram.
% 
% Obtain song data.


handles=pb_loadsong_Callback(hObject, eventdata, handles);


h = zoom;
set(h,'Motion','horizontal','Enable','on');

% Set axis synchronized.

linkaxes([handles.Original_Song_Amplitude,handles.Original_Song_Specgram],'x');
linkaxes([handles.Modified_Song_Amplitude,handles.Modified_Song_Specgram],'x');


% Initialize detected motif region plot
axes(handles.Original_Song_Amplitude);
hold on;
handles.gph.mtf_Strt    =plot(1,1,'Color',[1 0 0]); 

handles.gph.mtf_End     =plot(1,1,'Color',[1 0 0],'LineStyle','--');

handles.gph.mtr_region  = patch(0,0,'r');


% Choose default command line output for songedit_03
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes songedit_03 wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = songedit_03_OutputFcn(hObject, eventdata, handles) 
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

sound(handles.ss.song(tti(1):tti(2))/(6*std(handles.ss.song)),handles.ss.F);

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

sub_redraw_lower_panel(hObject,handles);

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

sound(handles.ms.song(tti(1):tti(2))/(6*std(handles.ms.song)),handles.ms.F);

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

sub_redraw_lower_panel(hObject,handles);

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

if strcmpi(YN,'Yes')
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


sub_redraw_lower_panel(hObject,handles);

guidata(hObject, handles);
end


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


sub_redraw_lower_panel(hObject,handles);

axes(handles.Modified_Song_Specgram); 

guidata(hObject, handles);


% --- Executes on button press in RB_ellip_filter.
function RB_ellip_filter_Callback(hObject, eventdata, handles)
% hObject    handle to RB_ellip_filter (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of RB_ellip_filter
EllipFilt_ON= get(hObject,'Value');

if (EllipFilt_ON)
    n = input('How many order of elliptic filter?: ');
    while n>25
        n = input('Too large a (a<=25). How many order of elliptic filter?: ');
    end
    
    Rp=input('Passband ripple, in decibels.');
    Rs=input('Stopband ripple, in decibels.');
        
    fprintf('\nLimit freq of low-pass filter[Hz]? \n');
    Wp = input('If 1x2 vector, it sets [min, max] limit of band-pass filter:  ex)[10 1000]: ');
    if max(Wp)>handles.os.F/2 
        fprintf('freq must be lower than Nyquest freq %d',handles.os.F);
        error(';\n');
    end
    [B,A]=ellip(n,Rp,Rs,2*Wp/handles.os.F);

    fprintf('filtering...\n');
    handles.ss.song=filter(B,A,handles.os.song);
    handles.besself_info = sprintf('%d-th order, Rp=%d%, Rs=%d, %d Hz Low Pass.',n,Rp,Rs,Wp);

else
    handles.besself_info = 'No filter';
    handles.ss.song=handles.os.song;
end
set(handles.Txt_Filt_Info,'string',handles.besself_info);

sub_redraw_upper_panel(hObject,handles);

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
    fprintf('\nLimit freq of low-pass filter[Hz]? If 1x2 vector, \n');
    b = input('it sets [min, max] limit of band-pass filter:  ex)[0 1000]: ');
    %     [a,b]=bessel_param_inquiry;
    if isscalar(b)  % b is scalar, -> high pass filter
        % besself(order,cut-off freq/Nyquist-freq)
        [B,A]=besself(a,2*b/handles.os.F);
    else
        [B,A]=besself(a,2*b/handles.os.F);
    end
    fprintf('filtering...\n');
    handles.ss.song=filter(B,A,handles.os.song);
    handles.besself_info = sprintf('%d-th order, %d Hz Low Pass.',a,b);

else
    handles.besself_info = 'No filter';
    handles.ss.song=handles.os.song;
end
set(handles.Txt_Filt_Info,'string',handles.besself_info);

sub_redraw_upper_panel(hObject,handles);

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





%%%%%%%%%%%%%%%%%%%%
function sub_redraw_upper_panel(hObject,handles)
% re-plot upper panel
%

axes(handles.Original_Song_Amplitude);cla;
axes(handles.Original_Song_Specgram);cla;

axes(handles.Original_Song_Amplitude);
set(handles.Original_Song_Amplitude,'XTickLabel',[]);
plot(handles.ss.t,handles.ss.song);
axis([handles.ss.t(1) handles.ss.t(end) min(handles.ss.song) max(handles.ss.song)]);

axes(handles.Original_Song_Specgram);


nfft = 1012;
fftwindow=nfft;
numoverlap=ceil(nfft/1.2);

[y,f,t,p]=spectrogram(handles.ss.song,fftwindow,numoverlap,nfft,handles.ss.F);
surf(t,f,10*log10(abs(p)),'EdgeColor','none');   view(0,90);
% imagesc(t,f,10*log10(abs(p))); set(gca,'YDir','Normal');hold on;
axis([handles.ss.t(1) handles.ss.t(end) ylim]);

handles.ss.specP = p;
handles.ss.specT = t;
handles.ss.specF = f;

guidata(hObject, handles);


function sub_redraw_lower_panel(hObject,handles)
% re-plot lower panel
%

axes(handles.Modified_Song_Amplitude);cla;
axes(handles.Modified_Song_Specgram);cla;

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
function handles=show_power(hObject,handles)
% show power in upper panel.

axes(handles.Original_Song_Specgram);

xlim_now=get(handles.Original_Song_Specgram,'XLim'); 
% create power which more than 2000Hz.
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
    %     handles.ss.gcf_power(1)=plot(handles.ss.specT,songpower/max_songp
    %     ower*max(ylim),'r--');
    
   % Calculate the power in high-freq region and normalize by its peak.
    highFind = handles.ss.specF>500;
    handles.ss.songpower_highF = sum(abs(handles.ss.specP(highFind,:)));
    handles.ss.songpower_highF=handles.ss.songpower_highF/max(handles.ss.songpower_highF);
    handles.ss.gcf_power(1)=plot(handles.ss.specT,handles.ss.songpower_highF*max(ylim),'b-');
% set(handles.ss.gcf_power(:),'XData',handles.ss.specT,'YData',handles.ss.songpower_highF*max(ylim))
    axis([xlim_now ylim]);

    guidata(hObject, handles);



% --- Executes on button press in Detect_Motif.
function Detect_Motif_Callback(hObject, eventdata, handles)
% hObject    handle to Detect_Motif (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


 set(handles.Show_Power,'Value',1);
 handles=show_power(hObject,handles);
 
% Detect positive gradient trigger (beginning of motifs). 
up_ind  =find(diff(handles.ss.songpower_highF>handles.motif_thresh*0.01)>0);  % [000011110000111]-> [00001000001]
down_ind=find(diff(handles.ss.songpower_highF<handles.motif_thresh*0.01)>0); % [111100001111000]-> [00001000001]

axes(handles.Original_Song_Amplitude);

% data start from above the threshold. This part is neglected.
if up_ind(1)>down_ind(1) 
 down_ind = down_ind(2:end);
end

% data end above threshold. This part is neglected.
if up_ind(end)>down_ind(end)
 up_ind= up_ind(1:end-1);
end

px = [repmat(handles.ss.specT(up_ind),2,1); NaN*ones(1,length(up_ind))];
px = reshape(px,1,prod(size(px)));
py = [repmat(ylim',1,length(up_ind)); NaN*ones(1,length(up_ind))];
py = reshape(py,1,numel(py));

set(handles.gph.mtf_Strt,'XData',px,'YData',py);


px = [repmat(handles.ss.specT(down_ind),2,1); NaN*ones(1,length(down_ind))];
px = reshape(px,1,numel(px));
py = [repmat(ylim',1,length(down_ind)); NaN*ones(1,length(down_ind))];
py = reshape(py,1,prod(size(py))); %#ok<PSIZE>

set(handles.gph.mtf_End,'XData',px,'YData',py);
% line([handles.ss.specT(up_ind);handles.ss.specT(up_ind)],repmat(ylim',1,length(up_ind)),'Color',[1 0 0]);
% 
% line([handles.ss.specT(down_ind);handles.ss.specT(down_ind)],repmat(ylim',1,length(down_ind)),'Color',[1 0 0]);

px = [handles.ss.specT(up_ind); handles.ss.specT(down_ind); handles.ss.specT(down_ind);handles.ss.specT(up_ind)];

maxy = max(ylim);
py = [maxy-0.05*diff(ylim)*ones(1,2), maxy,maxy]';
py = repmat(py,1,size(px,2));
% patch(px,py,'r');

set(handles.gph.mtr_region,'XData',px,'YData',py);

function Motif_Detect_Threshold_Callback(hObject, eventdata, handles)
% hObject    handle to Motif_Detect_Threshold (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Motif_Detect_Threshold as text
%        str2double(get(hObject,'String')) returns contents of Motif_Detect_Threshold as a double

handles.motif_thresh =  str2double(get(hObject,'String'))
guidata(hObject,handles);

% --- Executes during object creation, after setting all properties.
function Motif_Detect_Threshold_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Motif_Detect_Threshold (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



% Set threshold for auto-detecting syllables.

handles.motif_thresh = str2double(get(hObject,'String'));
guidata(hObject,handles);



% --- Executes during object creation, after setting all properties.
function Original_Song_Amplitude_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Original_Song_Amplitude (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: place code in OpeningFcn to populate Original_Song_Amplitude




% --- Executes on button press in pb_loadsong.
function handles = pb_loadsong_Callback(hObject, eventdata, handles)
% hObject    handle to pb_loadsong (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


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


%reset synthesized song
handles=sub_reset_ssong(hObject,handles);

% clear all plots
sub_clear_all_plots(handles);

% redraw upper panel.
sub_redraw_upper_panel(hObject,handles);
axes(handles.Original_Song_Specgram);
% handles.ss.gcf_power(1)=plot(0,0); hold on;

set(handles.RB_ellip_filter,'Value',0);
set(handles.RB_BesselFilter,'Value',0);

% initialize modified song
handles=sub_init_msong(hObject,handles);


function handles = sub_reset_ssong(hObject,handles)
% initialize filtered original song
% hObject    handle to pb_loadsong (see GCBO)
% handles    structure with handles and user data (see GUIDATA)

handles.ss.t    =handles.os.t;
handles.ss.song =handles.os.song;
handles.ss.F    =handles.os.F;
handles.ss.NBits=handles.os.NBits;

% song vector is row vector.
if size(handles.ss.song,1)~=1,    handles.ss.song=handles.ss.song';end



%
function sub_clear_all_plots(handles)
% Reset all axes so that previous data is removed.
axes(handles.Original_Song_Amplitude);cla;
axes(handles.Original_Song_Specgram);cla;
axes(handles.Modified_Song_Amplitude);cla;
axes(handles.Modified_Song_Specgram);cla;


function handles=sub_init_msong(hObject,handles)
% initialize lower panel, modified song data.
handles.ms.t    =[];
handles.ms.song =[];
handles.ms.F    =handles.ss.F;
handles.ms.NBits=handles.ss.NBits;







% --- Executes on button press in pb_Reverse.
function pb_Reverse_Callback(hObject, eventdata, handles)
% hObject    handle to pb_Reverse (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

handles.ms.t_old=handles.ms.t;
handles.ms.song_old=handles.ms.song;

handles.ms.song=handles.ms.song(end:-1:1);

sub_redraw_lower_panel(hObject,handles)



% --- Executes on button press in pb_Register.
function pb_Register_Callback(hObject, eventdata, handles)
% hObject    handle to pb_Register (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

if isempty(handles.ms.song)
    error('You need to add song region first!');
end

val=get(handles.popup_FileType,'Value');
songtypes=get(handles.popup_SongTypeSelect,'String');
songtype=songtypes{get(handles.popup_SongTypeSelect,'Value')};

switch val
    case 1 % new file
        [savename,savedir]=uiputfile;
        stim(1).song=handles.ms.song;
        stim(1).t   = handles.ms.t;
        stim(1).type=songtype;
        stim(1).Fsong=handles.os.F;
        save(fullfile(savedir,savename),'stim');
        handles.savedir=savedir;
        handles.savename=savename;
    case 2
        if ~isempty(handles.savedir)
            [savename,savedir]=uiputfile(fullfile(handles.savedir,handles.savename),'Append file');
        else
            [savename,savedir]=uigetfile({'*.m';'*.mdl';'*.mat';'*.*'},'Pick an append file');
        end
        load(fullfile(savedir,savename));
        n=length(stim);
        stim(n+1).song=handles.ms.song;
        stim(n+1).t=handles.ms.t;
        stim(n+1).type=songtype;
        stim(n+1).Fsong=handles.og.F;
        save(fullfile(savedir,savename),'stim');
    otherwise
        error('Unknown option!')
end

guidata(hObject,handles);


% --- Executes on selection change in popup_SongTypeSelect.
function popup_SongTypeSelect_Callback(hObject, eventdata, handles)
% hObject    handle to popup_SongTypeSelect (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns popup_SongTypeSelect contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popup_SongTypeSelect


% --- Executes during object creation, after setting all properties.
function popup_SongTypeSelect_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popup_SongTypeSelect (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


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




% --- Executes on button press in pb_AddRev.
function pb_AddRev_Callback(hObject, eventdata, handles)
% hObject    handle to pb_AddRev (see GCBO)
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
handles.ms.song=[handles.ms.song,handles.ss.song(tti(2):-1:tti(1))];

sub_redraw_lower_panel(hObject,handles);

guidata(hObject, handles);


% --- Executes on button press in pb_add_TTL.
function pb_add_TTL_Callback(hObject, eventdata, handles)
% hObject    handle to pb_add_TTL (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)



function edit_stim_name_Callback(hObject, eventdata, handles)
% hObject    handle to edit_stim_name (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_stim_name as text
%        str2double(get(hObject,'String')) returns contents of edit_stim_name as a double


% --- Executes during object creation, after setting all properties.
function edit_stim_name_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_stim_name (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
