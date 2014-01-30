function varargout = songedit_04(varargin)
% GUIDETESTWP053111 MATLAB code for Guidetestwp053111.fig
%      GUIDETESTWP053111, by itself, creates a new GUIDETESTWP053111 or raises the existing
%      singleton*.
%
%      H = GUIDETESTWP053111 returns the handle to a new GUIDETESTWP053111 or the handle to
%      the existing singleton*.
%
%      GUIDETESTWP053111('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in GUIDETESTWP053111.M with the given input arguments.
%
%      GUIDETESTWP053111('Property','Value',...) creates a new GUIDETESTWP053111 or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before Guidetestwp053111_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to Guidetestwp053111_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help Guidetestwp053111

% Last Modified by GUIDE v2.5 21-Jun-2011 18:48:06

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @Guidetestwp053111_OpeningFcn, ...
                   'gui_OutputFcn',  @Guidetestwp053111_OutputFcn, ...
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


% --- Executes just before Guidetestwp053111 is made visible.
function Guidetestwp053111_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to Guidetestwp053111 (see VARARGIN)

% Choose default command line output for Guidetestwp053111
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes Guidetestwp053111 wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = Guidetestwp053111_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in Load_Song.
function Load_Song_Callback(hObject, eventdata, handles)
% hObject    handle to Load_Song (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

%to choose recorded song in wav format to load
try 
    [filename, pathname, filterindex] = uigetfile('*.wav', 'Pick a song (.wav) file');
catch % In case no wave file is chosen.
    error([mfilename, ': Please chose a .wav file.']);
end

% Read wav data, and save in original song data, 'os.{song,F,Nbits}'
[handles.os.song,handles.os.F,handles.os.NBits]=wavread([pathname,filename]);

%create a backup of original loaded song
handles.rs.song=handles.os.song;
handles.rs.F=handles.os.F;
handles.rs.NBits=handles.os.NBits;

% make 1xN vector, not Nx1 vector.
if size(handles.os.song,1)~=1
    handles.os.song=handles.os.song';
end

% set time.
handles.os.t   = linspace(0,length(handles.os.song)/handles.os.F,length(handles.os.song));

%display filename of loaded song and clear name of previous motif
loadedsongname=fullfile(pathname,filename);
set(handles.Loaded_Song_Name,'String',loadedsongname);
set(handles.Created_Motif_Name,'string','Created Motif Name');

%init sliders matrix
try
    handles2=rmfield(handles,'sliders');
    handles=handles2;
catch
end
handles.sliders.updown=[];

try
    handles3=rmfield(handles,'Motif');
    handles=handles3;
catch
end
try
    handles4=rmfield(handles,'ramp');
    handles=handles4;
catch
end

%clear any previous song from plots and uncheck power  
cla(handles.Oscillogram_Song,'reset');
cla(handles.Spectrogram_Song,'reset'); 
cla(handles.Oscillogram_Modified_Song,'reset');
cla(handles.Spectrogram_Modified_Song,'reset'); 
set(handles.Show_Spectrogram_Power,'Value',0.0);
set(handles.Elliptic_Filter,'Value',0);
set(handles.Spectro_cutoff,'Value',0.001);
set(handles.Spectro_cutofftext,'string','0.001');

% plot song oscillogram,maximise x and y axes and reset zoom settings plus
% turn on horizontal zoom
plot(handles.Oscillogram_Song,handles.os.t,handles.os.song);
axis(handles.Oscillogram_Song,[handles.os.t(1) handles.os.t(end) min(handles.os.song) max(handles.os.song)]);
set(handles.Oscillogram_Song,'XTickLabel',[]);
zoom(gcf,'reset') ;
zoom xon;
 
% Written by Sigal Saar August 08 2005
% Modified by Kosuke Hamaguchi 04 2010 under mySAMIII. Applied here by WP
% 11.

%Generate Spectrum + other song features. Majority not used here. 
[handles.spec.os.m_spec_deriv , ...
    handles.spec.os.m_AM,...
    handles.spec.os.m_FM ,...
    handles.spec.os.m_Entropy ,...
    handles.spec.os.m_amplitude ,...
    handles.spec.os.m_frequency, ...
    handles.spec.os.m_PitchGoodness , ...
    handles.spec.os.m_Pitch ,...
    handles.spec.os.Pitch_chose ,...
    handles.spec.os.Pitch_weight,handles.spec.f,...
    handles.spec.os.specT]=sam_spectrum_deriv6(handles.os.song,handles.os.F);
% t=linspace(handles.os.t(1),handles.os.t(end),size(handles.spec.os.m_spec_deriv,1));
handles.spec.os.specF=handles.spec.f*2;
% handles.spec.os.specT=t; 

% plot song spectrogram, maximise x and y axes and reset zoom settings  
% max_spec=max(max(handles.spec.os.m_spec_deriv));
% min_spec=min(min(handles.spec.os.m_spec_deriv));
% cutoff=0.001;
% handles.spec.sonogram=imagesc(NaN,NaN,NaN,'Parent',handles.Spectrogram_Song); colormap copper;
% set(handles.spec.sonogram,'XData',handles.spec.os.specT,'YData',handles.spec.os.specF,'CData',handles.spec.os.m_spec_deriv(1:end,:)');
% caxis(handles.Spectrogram_Song,cutoff*[-max_spec, max_spec])
% set(handles.Spectrogram_Song,'XLim',[handles.os.t(1) handles.os.t(end)],'YLim',[0 handles.spec.os.specF(end)]);
% zoom(gcf,'reset') ;
% linkaxes([handles.Oscillogram_Song,handles.Spectrogram_Song],'x');
handles=Plot_Original_Song(hObject,handles); 

%initialize add song
handles=sub_init_msong(hObject,handles);

% Update handles structure
guidata(hObject,handles);

function handles=Plot_Original_Song(hObject,handles) 
max_spec=max(max(handles.spec.os.m_spec_deriv));
min_spec=min(min(handles.spec.os.m_spec_deriv));
cutoff_value = get(handles.Spectro_cutoff,'Value');
cutoff=cutoff_value;
handles.spec.sonogram=imagesc(NaN,NaN,NaN,'Parent',handles.Spectrogram_Song); colormap copper;
set(handles.spec.sonogram,'XData',handles.spec.os.specT,'YData',handles.spec.os.specF,'CData',handles.spec.os.m_spec_deriv(1:end,:)');
caxis(handles.Spectrogram_Song,cutoff*[-max_spec, max_spec])
set(handles.Spectrogram_Song,'XLim',[handles.os.t(1) handles.os.t(end)],'YLim',[0 handles.spec.os.specF(end)]);
zoom(gcf,'reset') ;
linkaxes([handles.Oscillogram_Song,handles.Spectrogram_Song],'x');

%plot syllable sliders if already present
try
    if size(handles.sliders.updown_indtime,2)>0
        for ii=1:size(handles.sliders.updown_indtime,2)
            %plot sliderpoint in mid of yaxis
            ylim=get(handles.Spectrogram_Song,'Ylim');
            midypos=ylim(1,2)/2;
            handles.sliders.updown{ii}=impoint(handles.Spectrogram_Song,handles.sliders.updown_indtime(1,ii),midypos);
            textstring=num2str(ii);
            b=handles.sliders.updown{ii};
            if mod(ii,2) == 0
                setColor(b,'b');%number is even
            else
                setColor(b,'k');%number is odd
            end
            setString(b,textstring);
            addNewPositionCallback(b,@(b) title(sprintf('(%1.3f,%1.0f,%1.0d)',b(1),b(2),ii)));
            
            %constraint sliderpoint to move only horizontally.
            fcn=makeConstrainToRectFcn('impoint',get(handles.Spectrogram_Song,'Xlim'),[midypos midypos]);
            setPositionConstraintFcn(b,fcn);
            clear b;
        end
    end
catch
end
 
try 
       if size(handles.Motif)>0
           ylim=get(handles.Spectrogram_Song,'Ylim');
           ylim=ylim(1,2)-(0.01*ylim(1,2));
           handles.ylim2=repmat(ylim,1,size(handles.spec.os.specT(handles.Motif.starttimexindex:handles.Motif.endtimextindex),2));
           axes(handles.Spectrogram_Song);hold on;
           %plot motif range
           handles.Motif.plot=plot(handles.Spectrogram_Song,handles.spec.os.specT(handles.Motif.starttimexindex:handles.Motif.endtimextindex),handles.ylim2,'g');
           ylim=get(handles.Spectrogram_Song,'Ylim');
           ylim3=ylim(1,2)-(0.25*ylim(1,2));
           findpoints=find(handles.sliders.pospoint>=handles.Motif.starttime&handles.sliders.pospoint<=handles.Motif.endtime);
           numpoints=size(findpoints,1);
           numelement=numpoints-1;
           for ii=1:numelement
               texttimetoplot(1,ii)=handles.Motif.Element.time(1,ii)+handles.Motif.Element.timediff(1,ii);
           end
           for ii=1:numelement
               axes(handles.Spectrogram_Song);
               handles.Motif.textplot{1,ii}=text(texttimetoplot(1,ii),ylim3,handles.Motif.Element.text{ii},'BackgroundColor','white');
           end
           handles.Motif.playpop=horzcat(handles.Motif.name,handles.Motif.Element.text);
           set(handles.Play_Motif_Popup,'string',handles.Motif.playpop);
           set(handles.Add_Popup,'string',handles.Motif.playpop);
           set(handles.Revadd_popup,'string',handles.Motif.playpop);
       end
catch
end

%update handles structure
guidata(hObject,handles);

function handles=Replot_Original_Song(hObject,handles) 
tt=get(handles.Oscillogram_Song,'XLim'); 
max_spec=max(max(handles.spec.os.m_spec_deriv));
min_spec=min(min(handles.spec.os.m_spec_deriv));
cutoff_value = get(handles.Spectro_cutoff,'Value');
cutoff=cutoff_value;
handles.spec.sonogram=imagesc(NaN,NaN,NaN,'Parent',handles.Spectrogram_Song); colormap copper;
set(handles.spec.sonogram,'XData',handles.spec.os.specT,'YData',handles.spec.os.specF,'CData',handles.spec.os.m_spec_deriv(1:end,:)');
caxis(handles.Spectrogram_Song,cutoff*[-max_spec, max_spec])
set(handles.Spectrogram_Song,'XLim',[tt(1) tt(2)],'YLim',[0 handles.spec.os.specF(end)]);
linkaxes([handles.Oscillogram_Song,handles.Spectrogram_Song],'x');

%plot syllable sliders if already present 
if size(handles.sliders.updown,1)>0
    for ii=1:size(handles.sliders.updown_indtime,2)
        %plot sliderpoint in mid of yaxis
        ylim=get(handles.Spectrogram_Song,'Ylim');
        midypos=ylim(1,2)/2;
        handles.sliders.updown{ii}=impoint(handles.Spectrogram_Song,handles.sliders.updown_indtime(1,ii),midypos);
        textstring=num2str(ii);
        b=handles.sliders.updown{ii};
        if mod(ii,2) == 0
            setColor(b,'b');%number is even
        else
            setColor(b,'k');%number is odd
        end
        setString(b,textstring);
        addNewPositionCallback(b,@(b) title(sprintf('(%1.3f,%1.0f,%1.0d)',b(1),b(2),ii)));
        
        %constraint sliderpoint to move only horizontally.
        fcn=makeConstrainToRectFcn('impoint',get(handles.Spectrogram_Song,'Xlim'),[midypos midypos]);
        setPositionConstraintFcn(b,fcn);
        clear b;
    end
end

%update handles structure
guidata(hObject,handles);



% --- Executes on button press in Play_Loaded_Song.
function Play_Loaded_Song_Callback(hObject, eventdata, handles)
% hObject    handle to Play_Loaded_Song (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

%to play back song displayed within xaxis (Written by Kosuke)
tt=get(handles.Oscillogram_Song,'XLim'); 
tti=ceil(tt*handles.os.F)+1;
tti(1)=max(1,tti(1));  % start index > 1.
tti(2)=min(length(handles.os.song),tti(2)); % end index < length(song)
sound(handles.os.song(tti(1):tti(2))/(6*std(handles.os.song)),handles.os.F);

% --- Executes on button press in Show_Spectrogram_Power.
function Show_Spectrogram_Power_Callback(hObject, eventdata, handles)
% hObject    handle to Show_Spectrogram_Power (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
 
%Created by Kosuke, modified by Wendy to show amplitude
ShowPower_ON= get(hObject,'Value');
if (ShowPower_ON)
    axes(handles.Spectrogram_Song);hold on;
    xlim_now=get(handles.Spectrogram_Song,'XLim');
    ylim=[min(handles.spec.os.specF) max(handles.spec.os.specF)];
    handles=cal_power(hObject,handles);
    handles.os.gcf_power=plot(handles.spec.os.specT,(handles.spec.os.m_amplitude')*max(ylim),'g-');
    axis([xlim_now ylim]);
else
    set(handles.os.gcf_power,'XData',[],'YData',[]);
end

% Update handles structure
guidata(hObject,handles);

function handles=cal_power(hObject,handles) 
    %modifed from cal power to normalize amplitude
    handles.spec.os.m_amplitude=handles.spec.os.m_amplitude+abs(min(handles.spec.os.m_amplitude));
    handles.spec.os.m_amplitude=handles.spec.os.m_amplitude/max(handles.spec.os.m_amplitude);
    % Update handles structure
    guidata(hObject, handles);

  % --- Executes on button press in Clear_Slider.
function Clear_Slider_Callback(hObject, eventdata, handles)
% hObject    handle to Clear_Slider (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

%delete away drawn syllable boundaries (will only work for latest set of
%boundaries)
axes(handles.Spectrogram_Song);
for ii=1:size(handles.sliders.updown,2)
    delete (handles.sliders.updown{ii});
end

%delete away previous detected syllable boundaries data
handles2=rmfield(handles,'sliders');
handles=handles2;

%reset Motif name 
set(handles.Created_Motif_Name,'string','Created Motif Name');

% Update handles structure
guidata(hObject,handles)
 

% --- Executes on button press in Detect_Syllables.
function Detect_Syllables_Callback(hObject, eventdata, handles)
% hObject    handle to Detect_Syllables (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

%cal power
handles=cal_power(hObject,handles);
 
% Detect positive and negative gradient trigger for amplitude  
data=str2double(get(handles.Threshold_Input,'String'));
handles.sliders.up_ind  =find(diff(handles.spec.os.m_amplitude>data*0.01)>0);  % [000011110000111]-> [00001000001]
handles.sliders.down_ind=find(diff(handles.spec.os.m_amplitude<data*0.01)>0); % [111100001111000]-> [00001000001]

% data start from above the threshold. Downsweep before first upsweep or upsweep after last downsweep is removed.
if ~isempty(handles.sliders.up_ind)&~isempty(handles.sliders.down_ind)
    if handles.sliders.up_ind(1)>handles.sliders.down_ind(1)
        handles.sliders.down_ind = handles.sliders.down_ind(2:end);
    end
    if handles.sliders.up_ind(end)>handles.sliders.down_ind(end)
        handles.sliders.up_ind= handles.sliders.up_ind(1:end-1);
    end
else
    errordlg('no syllables detected, adjust threshold input');
end

%convert indices to time and combine+sort up and down times in one vector
handles.sliders.up_indtime=handles.spec.os.specT(handles.sliders.up_ind);
handles.sliders.down_indtime=handles.spec.os.specT(handles.sliders.down_ind);
handles.sliders.updown_indtime = horzcat(handles.sliders.up_indtime, handles.sliders.down_indtime);
handles.sliders.updown_indtime =sort(handles.sliders.updown_indtime);

%Add sliders/points to indicate boundaries detected syllables
for ii=1:size(handles.sliders.updown_indtime,2)
    %plot sliderpoint in mid of yaxis
    ylim=get(handles.Spectrogram_Song,'Ylim');
    midypos=ylim(1,2)/2;
    handles.sliders.updown{ii}=impoint(handles.Spectrogram_Song,handles.sliders.updown_indtime(1,ii),midypos);
    textstring=num2str(ii); 
    b=handles.sliders.updown{ii};
    if mod(ii,2) == 0
        setColor(b,'b');%number is even
    else
        setColor(b,'k');%number is odd
    end  
    setString(b,textstring);
    addNewPositionCallback(b,@(b) title(sprintf('(%1.3f,%1.0f,%1.0d)',b(1),b(2),ii)));
 
    %constraint sliderpoint to move only horizontally.
    fcn=makeConstrainToRectFcn('impoint',get(handles.Spectrogram_Song,'Xlim'),[midypos midypos]);
    setPositionConstraintFcn(b,fcn);
    clear b;
end

% Update handles structure
guidata(hObject,handles);

% --- Executes on button press in Create_New_Sliders.
function Create_New_Sliders_Callback(hObject, eventdata, handles)
% hObject    handle to Create_New_Sliders (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

%plot sldierpoint to mid of yaxis
ylim=get(handles.Spectrogram_Song,'Ylim');
midypos=ylim(1,2)/2;

%calculate how many sliderpoints have already been plotted
TotalNumPrevSlider=size(handles.sliders.updown,2);
temxpos=getPosition(handles.sliders.updown{TotalNumPrevSlider});
temxpos=temxpos(1,1);
 
%add new points 10 msec after last sliderpoint and incorporate new sliderpoint into
%handle structure of all previous sliderpoints
Newtime=temxpos+0.01;
handles.sliders.updown{TotalNumPrevSlider+1} = impoint(handles.Spectrogram_Song,Newtime, midypos);
b=handles.sliders.updown{TotalNumPrevSlider+1};
setColor(b,'m');
textstring=num2str(TotalNumPrevSlider+1);
setString(b,textstring);
addNewPositionCallback(b,@(b) title(sprintf('(%1.3f,%1.0f,%1.0d)',b(1),b(2),TotalNumPrevSlider+1)));
fcn=makeConstrainToRectFcn('impoint',get(handles.Spectrogram_Song,'Xlim'),[midypos midypos]);
setPositionConstraintFcn(b,fcn);
clear b;

% Update handles structure
guidata(hObject,handles);

 
function Threshold_Input_Callback(hObject, eventdata, handles)
% hObject    handle to Threshold_Input (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

%return value of threshold 
handles.motif_thresh =  str2double(get(hObject,'String'));

%update handles structure
guidata(hObject,handles);


% --- Executes during object creation, after setting all properties.
function Threshold_Input_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Threshold_Input (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% --- Executes on button press in Create_Motif.
function Create_Motif_Callback(hObject, eventdata, handles)
% hObject    handle to Create_Motif (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

%Obtain latest x positions of all syllable boundaries created so far
for ii=1:size(handles.sliders.updown,2)
    b=handles.sliders.updown{ii};
    handles.sliders.pospoint(ii,1:2)=getPosition(b);
    clear b;
end 

%ask for user input to specific motif name and motif range
prompt={'Specify Motif Name:', 'Specify 2 Syllable Boundary ID number separated by space:'};
dlg_title = 'Create Motif';
num_lines = 1;
def={'',''};
answer = inputdlg(prompt,dlg_title,num_lines,def);
handles.Motif.name=answer{1,1};
Motifidentifier=str2num(answer{2,1});
handles.Motif.starttimeID=Motifidentifier(1,1);
handles.Motif.endtimeID=Motifidentifier(1,2);
handles.Motif.starttime=handles.sliders.pospoint(handles.Motif.starttimeID,1);
handles.Motif.endtime=handles.sliders.pospoint(handles.Motif.endtimeID,1);
handles.Motif.starttimexindex=max(find(handles.spec.os.specT<handles.Motif.starttime))+1;
handles.Motif.endtimextindex=min(find(handles.spec.os.specT>handles.Motif.endtime))-1;
set(handles.Created_Motif_Name,'String',handles.Motif.name);
ylim=get(handles.Spectrogram_Song,'Ylim');
ylim=ylim(1,2)-(0.01*ylim(1,2));
handles.ylim2=repmat(ylim,1,size(handles.spec.os.specT(handles.Motif.starttimexindex:handles.Motif.endtimextindex),2));
axes(handles.Spectrogram_Song);hold on;

%plot motif range 
handles.Motif.plot=plot(handles.Spectrogram_Song,handles.spec.os.specT(handles.Motif.starttimexindex:handles.Motif.endtimextindex),handles.ylim2,'g');

%calculate number of all slider points with x positions in between motif range
findpoints=find(handles.sliders.pospoint>=handles.Motif.starttime&handles.sliders.pospoint<=handles.Motif.endtime);
numpoints=size(findpoints,1);

%number of song elements = number of sliderpoints-1
numelement=numpoints-1;

%Determine time of sliders
for ii=1:numpoints
handles.Motif.Element.time(1,ii)=handles.sliders.pospoint(findpoints(ii,1));
handles.Motif.Element.time(2,ii)=findpoints(ii,1);
handles.Motif.Element.time(3,ii)=max(find(handles.spec.os.specT<handles.Motif.Element.time(1,ii)))+1;
handles.Motif.Element.time(4,ii)=max(find(handles.os.t<handles.Motif.Element.time(1,ii)));
end

%make sure sliders are referenced correctly index order of time
handles.Motif.Element.time=handles.Motif.Element.time';
handles.Motif.Element.time=sortrows(handles.Motif.Element.time,1);
handles.Motif.Element.time=handles.Motif.Element.time';

%cal mid point between sliderpoints to place syllable name
for ii=1:numelement
handles.Motif.Element.timediff(1,ii)=(handles.Motif.Element.time(1,ii+1)-handles.Motif.Element.time(1,ii))/2;
end
for ii=1:numelement
texttimetoplot(1,ii)=handles.Motif.Element.time(1,ii)+handles.Motif.Element.timediff(1,ii);
end

%ask user to input syllable name
for ii=1:numelement
    prompt2{1,ii}={'Name for syllable/gap/subsyllable:'};
    def2{1,ii}='';    
end
dlg_title2 = 'Provide names for element between each sliderpoint:';
num_lines = 1;
answer2=inputdlg(prompt2,dlg_title2,num_lines,def2);

%plot syllable names 
for ii=1:numelement
handles.Motif.Element.text{ii}=answer2{ii,1};
end
ylim=get(handles.Spectrogram_Song,'Ylim');
ylim3=ylim(1,2)-(0.25*ylim(1,2));
for ii=1:numelement
axes(handles.Spectrogram_Song);
handles.Motif.textplot{1,ii}=text(texttimetoplot(1,ii),ylim3,handles.Motif.Element.text{ii},'BackgroundColor','white');
end

%add created syllable name to pop up menu for play motif
handles.Motif.playpop=horzcat(handles.Motif.name,handles.Motif.Element.text);
set(handles.Play_Motif_Popup,'string',handles.Motif.playpop);
set(handles.Add_Popup,'string',handles.Motif.playpop);
set(handles.Revadd_popup,'string',handles.Motif.playpop);

%update handles structure
guidata(hObject,handles);
 


% --- Executes on button press in Play_Motif_Syllable.
function Play_Motif_Syllable_Callback(hObject, eventdata, handles)
% hObject    handle to Play_Motif_Syllable (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

%get user selected motif/syllable to play
element2play=get(handles.Play_Motif_Popup,'Value');

if element2play==1
    tt=[handles.Motif.starttime handles.Motif.endtime]; 
else
    tt=[handles.Motif.Element.time(1,element2play-1) handles.Motif.Element.time(1,element2play)];
end
 
tti=ceil(tt*handles.os.F)+1;
tti(1)=max(1,tti(1));  % start index > 1.
tti(2)=min(length(handles.os.song),tti(2)); % end index < length(song)
sound(handles.os.song(tti(1):tti(2))/(6*std(handles.os.song)),handles.os.F);


% --- Executes on button press in Clear_Motif.
function Clear_Motif_Callback(hObject, eventdata, handles)
% hObject    handle to Clear_Motif (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
 
%clear away motif range plot and data
set(handles.Play_Motif_Popup,'string','Play Popup','Value',1.0);
set(handles.Revadd_popup,'string','Revadd Popup','Value',1.0);
set(handles.Add_Popup,'string','Add Popup','Value',1.0);
set(handles.Add_ramp_popup,'string','Addramp popup','Value',1.0);
axes(handles.Spectrogram_Song);
delete (handles.Motif.plot);
for ii=1:size(handles.Motif.textplot,2)
delete (handles.Motif.textplot{1,ii});
end
handles3=rmfield(handles,'Motif');
handles=handles3;

try
    handles4=rmfield(handles,'ramp');
    handles=handles4;
catch
end
%reset Motif name 
set(handles.Created_Motif_Name,'string','Created Motif Name');

%update handles structure
guidata(hObject,handles)


% --- Executes on button press in Elliptic_Filter.
function Elliptic_Filter_Callback(hObject, eventdata, handles)
% hObject    handle to Elliptic_Filter (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

EllipFilt_ON= get(hObject,'Value');
if (EllipFilt_ON)
    prompt={'Order:','Passband ripple,in decibels:','Stopband ripple, in decibels:','Low Frequency Cutoff:'};
    dlg_title = 'Input elliptic filter parameters:';
    num_lines = 1;
    def={'4','0.1','50','300'};
    answer = inputdlg(prompt,dlg_title,num_lines,def);
    n=str2num(answer{1,1});
    while n>25
        error('Too large a (a<=25). Reinput Order');  
    end
    Rp=str2num(answer{2,1});
    Rs=str2num(answer{3,1});
    Wp=str2num(answer{4,1});
    Wp=2*Wp/handles.os.F;
    [B,A]=ellip(n,Rp,Rs,Wp,'high');
    fprintf('filtering...\n');
    handles.os.song=filter(B,A,handles.rs.song);
    handles.ellip_info = sprintf('%d-th order,Rp=%1.1f,Rs=%1.0f,%1.0f Hz Low Pass.',n,Rp,Rs,Wp(1,1));
else
    handles.ellip_info = 'No filter';
    %revert back to original loaded song setting
    handles.os.song=handles.rs.song;      
end

set(handles.Filter_Info,'string',handles.ellip_info);

% clear plots and replot song oscillogram and spectrogram
cla(handles.Oscillogram_Song,'reset');
cla(handles.Spectrogram_Song,'reset'); 
set(handles.Show_Spectrogram_Power,'Value',0.0);
plot(handles.Oscillogram_Song,handles.os.t,handles.os.song);
axis(handles.Oscillogram_Song,[handles.os.t(1) handles.os.t(end) min(handles.os.song) max(handles.os.song)]);
set(handles.Oscillogram_Song,'XTickLabel',[]);
zoom(gcf,'reset') ;
zoom xon;
handles=cal_spec(hObject,handles);
handles=Plot_Original_Song(hObject,handles); 

%update handles structure
guidata(hObject, handles);


function handles=cal_spec(hObject, handles)
handles=rmfield(handles,'spec');
[handles.spec.os.m_spec_deriv , ...
    handles.spec.os.m_AM,...
    handles.spec.os.m_FM ,...
    handles.spec.os.m_Entropy ,...
    handles.spec.os.m_amplitude ,...
    handles.spec.os.m_frequency, ...
    handles.spec.os.m_PitchGoodness , ...
    handles.spec.os.m_Pitch ,...
    handles.spec.os.Pitch_chose ,...
    handles.spec.os.Pitch_weight,handles.spec.f,...
     handles.spec.os.specT]=sam_spectrum_deriv6(handles.os.song,handles.os.F);
handles.spec.os.specF=handles.spec.f*2;

%update handles structure
guidata(hObject,handles);


% --- Executes on button press in Add.
function Add_Callback(hObject, eventdata, handles)
% hObject    handle to Add (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

%get user input from Add popup
element2add=get(handles.Add_Popup,'Value');
clear sadd;
if element2add==1
    sadd.time=[handles.Motif.starttime handles.Motif.endtime]; 
else
    sadd.time=[handles.Motif.Element.time(1,element2add-1) handles.Motif.Element.time(1,element2add)];  
end
sadd.tti(1)=max(find(handles.os.t<sadd.time(1,1)));
sadd.tti(2)=min(find(handles.os.t>sadd.time(1,2)));
%cal boundaries of selected syllables/motif
% tti=ceil(time*handles.os.F)+1;
% tti(1)=max(1,tti(1));  % start index > 1.
% tti(2)=min(length(handles.os.song),tti(2)); % end index < length(son
sadd.numtt =diff(sadd.tti);
sadd.maxttintime=(sadd.numtt)/handles.os.F;
if isempty(handles.ms.t)   
    sadd.maxt = 0; 
else
    sadd.maxt=max(handles.ms.t);
end
sadd.t = linspace(0,sadd.maxttintime,length(handles.os.song(sadd.tti(1):sadd.tti(2))))+sadd.maxt;

%add new element to end of existing added song
handles.ms.t_old=handles.ms.t;
handles.ms.song_old=handles.ms.song;
if size(handles.ms.t,1)>1
    handles.ms.t=handles.ms.t';
end
if size(sadd.t,1)>1
    sadd.t=sadd.t';
end
handles.ms.t = horzcat(handles.ms.t,sadd.t);
if size(handles.ms.song,1)>1
    handles.ms.song=handles.ms.song';
end
addsong=handles.os.song(sadd.tti(1):sadd.tti(2));
if size(addsong,1)>1
    addsong=addsong';
end
handles.ms.song=horzcat(handles.ms.song,addsong);
 
clear sadd;
% clear plots and replot modified song oscillogram and spectrogram
handles=Replot_Modified_Song(hObject,handles);

%update handles structure
guidata(hObject, handles);

function handles=cal_specMS(hObject, handles)
handles.msspec=[];
[handles.msspec.os.m_spec_deriv , ...
    handles.msspec.os.m_AM,...
    handles.msspec.os.m_FM ,...
    handles.msspec.os.m_Entropy ,...
    handles.msspec.os.m_amplitude ,...
    handles.msspec.os.m_frequency, ...
    handles.msspec.os.m_PitchGoodness , ...
    handles.msspec.os.m_Pitch ,...
    handles.msspec.os.Pitch_chose ,...
    handles.msspec.os.Pitch_weight,handles.msspec.f,...
     handles.msspec.os.specT]=sam_spectrum_deriv6(handles.ms.song,handles.ms.F);
handles.msspec.os.specF=handles.spec.f*2;

 %update handles structure
guidata(hObject,handles);


% --- Executes on button press in Add_Displayed_Song.
function Add_Displayed_Song_Callback(hObject, eventdata, handles)
% hObject    handle to Add_Displayed_Song (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
clear sadd;
sadd.time=get(handles.Oscillogram_Song,'Xlim');
sadd.osstarttimeindex=max(find(handles.os.t<=sadd.time(1,1)));
sadd.osendtimeindex=min(find(handles.os.t>=sadd.time(1,2)));
sadd.numtt =sadd.osendtimeindex-sadd.osstarttimeindex+1;
sadd.maxttintime=sadd.numtt/handles.os.F;
if isempty(handles.ms.t)   
    sadd.maxt = 0; 
else
    sadd.maxt=max(handles.ms.t);
end
sadd.t = linspace(0,sadd.maxttintime,sadd.numtt)+sadd.maxt;
handles.ms.t_old=handles.ms.t;
handles.ms.song_old=handles.ms.song;
if size(handles.ms.t,1)>1
    handles.ms.t=handles.ms.t';
end
if size(sadd.t,1)>1
    sadd.t=sadd.t';
end
handles.ms.t = horzcat(handles.ms.t,sadd.t);
if size(handles.ms.song,1)>1
    handles.ms.song=handles.ms.song';
end
addsong=handles.os.song(sadd.osstarttimeindex:sadd.osendtimeindex);
if size(addsong,1)>1
    addsong=addsong';
end
handles.ms.song=horzcat(handles.ms.song,addsong);
clear sadd;
handles=Replot_Modified_Song(hObject,handles);

% %update handles structure
guidata(hObject, handles);

function handles=Replot_Modified_Song(hObject,handles)
% clear plots and replot modified song oscillogram and spectrogram
cla(handles.Oscillogram_Modified_Song,'reset');
cla(handles.Spectrogram_Modified_Song,'reset'); 
plot(handles.Oscillogram_Modified_Song,handles.ms.t,handles.ms.song);
axis(handles.Oscillogram_Modified_Song,[handles.ms.t(1) handles.ms.t(end) min(handles.rs.song) max(handles.rs.song)]);
set(handles.Oscillogram_Modified_Song,'XTickLabel',[]);
handles=cal_specMS(hObject, handles);
max_spec=max(max(handles.spec.os.m_spec_deriv));
min_spec=min(min(handles.spec.os.m_spec_deriv));
cutoff_value = get(handles.MS_Spectro_cutoff,'Value');
cutoff=cutoff_value;
handles.msspec.sonogram=imagesc(NaN,NaN,NaN,'Parent',handles.Spectrogram_Modified_Song); colormap copper;
set(handles.msspec.sonogram,'XData',handles.msspec.os.specT,'YData',handles.msspec.os.specF,'CData',handles.msspec.os.m_spec_deriv(1:end,:)');
caxis(handles.Spectrogram_Modified_Song,cutoff*[-max_spec, max_spec])
set(handles.Spectrogram_Modified_Song,'XLim',[handles.ms.t(1) handles.ms.t(end)],'YLim',[0 handles.msspec.os.specF(end)]);
linkaxes([handles.Oscillogram_Modified_Song,handles.Spectrogram_Modified_Song],'x');
zoom(handles.Oscillogram_Modified_Song,'reset');
zoom xon;

%update handles structure
guidata(hObject,handles);

% --- Executes on button press in Play_Modified_Song.
function Play_Modified_Song_Callback(hObject, eventdata, handles)
% hObject    handle to Play_Modified_Song (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

tt=get(handles.Oscillogram_Modified_Song,'XLim'); 
tti=ceil(tt*handles.ms.F)+1;
tti(1)=max(1,tti(1));  % start index > 1.
tti(2)=min(length(handles.ms.song),tti(2)); % end index < length(song)
sound(handles.ms.song(tti(1):tti(2))/(6*std(handles.ms.song)),handles.ms.F);

% --- Executes on button press in Clear_Modified_Song.
function Clear_Modified_Song_Callback(hObject, eventdata, handles)
% hObject    handle to Clear_Modified_Song (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

cla(handles.Oscillogram_Modified_Song,'reset');
cla(handles.Spectrogram_Modified_Song,'reset'); 
handles=sub_init_msong(hObject,handles);

%update handles structure
guidata(hObject,handles);
 

function handles=sub_init_msong(hObject,handles)
% initialize lower panel, modified song data.
handles.ms.t    =[];
handles.ms.song =[];
handles.ms.F    =handles.os.F;
handles.ms.NBits=handles.os.NBits;
handles.msspec=[];

%update handles structure
guidata(hObject,handles);

% --- Executes on slider movement.
function Spectro_cutoff_Callback(hObject, eventdata, handles)
% hObject    handle to Spectro_cutoff (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider
handles=Replot_Original_Song(hObject,handles);

cutoff.value = get(handles.Spectro_cutoff,'Value');
cutoff.display=sprintf('%0.6f',cutoff.value);
set(handles.Spectro_cutofftext,'string',cutoff.display);

clear cutoff;

%update handles structure
guidata(hObject,handles);

% --- Executes on slider movement.
function MS_Spectro_cutoff_Callback(hObject, eventdata, handles)
% hObject    handle to MS_Spectro_cutoff (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider
handles=Replot_Modified_Song(hObject,handles);

cutoff.value = get(handles.MS_Spectro_cutoff,'Value');
cutoff.display=sprintf('%0.6f',cutoff.value);
set(handles.MS_Spectro_cutofftext,'string',cutoff.display);

clear cutoff;

%update handles structure
guidata(hObject,handles);

% --- Executes on button press in Revadd_displayed_song.
function Revadd_displayed_song_Callback(hObject, eventdata, handles)
% hObject    handle to Revadd_displayed_song (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

clear sadd;
sadd.time=get(handles.Oscillogram_Song,'Xlim');
sadd.osstarttimeindex=max(find(handles.os.t<=sadd.time(1,1)));
sadd.osendtimeindex=min(find(handles.os.t>=sadd.time(1,2)));
sadd.numtt =sadd.osendtimeindex-sadd.osstarttimeindex+1;
sadd.maxttintime=sadd.numtt/handles.os.F;
if isempty(handles.ms.t)   
    sadd.maxt = 0; 
else
    sadd.maxt=max(handles.ms.t);
end
sadd.t = linspace(0,sadd.maxttintime,sadd.numtt)+sadd.maxt;

%add new element to end of existing added song
handles.ms.t_old=handles.ms.t;
handles.ms.song_old=handles.ms.song;
if size(handles.ms.t,1)>1
    handles.ms.t=handles.ms.t';
end
if size(sadd.t,1)>1
    sadd.t=sadd.t';
end
handles.ms.t = horzcat(handles.ms.t,sadd.t);
if size(handles.ms.song,1)>1
    handles.ms.song=handles.ms.song';
end
revsong=handles.os.song(sadd.osstarttimeindex:sadd.osendtimeindex);
if size(revsong,1)>1
    revsong=revsong';
end
revsong=revsong(end:-1:1);
handles.ms.song=horzcat(handles.ms.song,revsong);
clear sadd;clear revsong;
handles=Replot_Modified_Song(hObject,handles);

% %update handles structure
guidata(hObject, handles);

% --- Executes on button press in Revadd_Motif.
function Revadd_Motif_Callback(hObject, eventdata, handles)
% hObject    handle to Revadd_Motif (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
element2add=get(handles.Revadd_popup,'Value');
clear sadd;
if element2add==1
    sadd.time=[handles.Motif.starttime handles.Motif.endtime]; 
else
    sadd.time=[handles.Motif.Element.time(1,element2add-1) handles.Motif.Element.time(1,element2add)];  
end
sadd.tti(1)=max(find(handles.os.t<sadd.time(1,1)));
sadd.tti(2)=min(find(handles.os.t>sadd.time(1,2)));

%cal boundaries of selected syllables/motif
% tti=ceil(time*handles.os.F)+1;
% tti(1)=max(1,tti(1));  % start index > 1.
% tti(2)=min(length(handles.os.song),tti(2)); % end index < length(son
sadd.numtt =diff(sadd.tti);
sadd.maxttintime=(sadd.numtt)/handles.os.F;
if isempty(handles.ms.t)   
    sadd.maxt = 0; 
else
    sadd.maxt=max(handles.ms.t);
end
sadd.t = linspace(0,sadd.maxttintime,length(handles.os.song(sadd.tti(1):sadd.tti(2))))+sadd.maxt;

%add new element to end of existing added song
handles.ms.t_old=handles.ms.t;
handles.ms.song_old=handles.ms.song;
if size(handles.ms.t,1)>1
    handles.ms.t=handles.ms.t';
end
if size(sadd.t,1)>1
    sadd.t=sadd.t';
end
handles.ms.t = horzcat(handles.ms.t,sadd.t);
if size(handles.ms.song,1)>1
    handles.ms.song=handles.ms.song';
end
addsong=handles.os.song(sadd.tti(1):sadd.tti(2));
if size(addsong,1)>1
    addsong=addsong';
end
addsong=addsong(end:-1:1);
handles.ms.song=horzcat(handles.ms.song,addsong);

clear sadd;
% clear plots and replot modified song oscillogram and spectrogram
handles=Replot_Modified_Song(hObject,handles);

%update handles structure
guidata(hObject, handles);

% --- Executes on button press in REVSO_motif.
function REVSO_motif_Callback(hObject, eventdata, handles)
% hObject    handle to REVSO_motif (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

sadd.tti(1)=handles.Motif.Element.time(4,1);
sadd.tti(2)=handles.Motif.Element.time(4,end);
sadd.numtt =diff(sadd.tti);
sadd.maxttintime=(sadd.numtt)/handles.os.F;
if isempty(handles.ms.t)   
    sadd.maxt = 0; 
else
    sadd.maxt=max(handles.ms.t);
end
sadd.t = linspace(0,sadd.maxttintime,length(handles.os.song(sadd.tti(1):sadd.tti(2))))+sadd.maxt;

%add new element to end of existing added song
handles.ms.t_old=handles.ms.t;
handles.ms.song_old=handles.ms.song;
if size(handles.ms.t,1)>1
    handles.ms.t=handles.ms.t';
end
if size(sadd.t,1)>1
    sadd.t=sadd.t';
end
handles.ms.t = horzcat(handles.ms.t,sadd.t);
jj=size(handles.Motif.Element.text,2);
for ii=1:size(handles.Motif.Element.text,2)
    if ii==1
       addsong=handles.os.song(handles.Motif.Element.time(4,jj):handles.Motif.Element.time(4,jj+1));
    else
    addsong=handles.os.song(handles.Motif.Element.time(4,jj)+1:handles.Motif.Element.time(4,jj+1));
    end
    if size(handles.ms.song,1)>1
        handles.ms.song=handles.ms.song';
    end
    if size(addsong,1)>1
        addsong=addsong';
    end
    handles.ms.song=horzcat(handles.ms.song,addsong);
    jj=jj-1;
    clear addsong;
end

% clear plots and replot modified song oscillogram and spectrogram
handles=Replot_Modified_Song(hObject,handles);

%update handles structure
guidata(hObject, handles);

% --- Executes on button press in Ramp_motif.
function Ramp_motif_Callback(hObject, eventdata, handles)
% hObject    handle to Ramp_motif (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
kk=1;
for ii=1:size(handles.Motif.Element.text,2)
    ramptemp.element2ramp=handles.os.song(handles.Motif.Element.time(4,ii):handles.Motif.Element.time(4,ii+1));
    if size(ramptemp.element2ramp,1)>1
        ramptemp.element2ramp=ramptemp.element2ramp';
    end
    ramptemp.vEnv(1:length(ramptemp.element2ramp)) = 1;
    rampperiod=3/1000*handles.os.F;
    ramptemp.loAngle = linspace(-pi/2,0,rampperiod);
    ramptemp.hiAngle = linspace(0,pi/2,rampperiod);
    ramptemp.loEnv = cos(ramptemp.loAngle);
    ramptemp.hiEnv = cos(ramptemp.hiAngle);
    ramptemp.vEnv(1:length(ramptemp.loEnv)) =ramptemp.loEnv;
    ramptemp.vEnv(end-length(ramptemp.hiEnv)+1:end) = ramptemp.hiEnv;
    if size(ramptemp.vEnv,1)>1
        ramptemp.vEnv=ramptemp.vEnv';
    end
    handles.ramp.(handles.Motif.Element.text{ii})= ramptemp.element2ramp.*ramptemp.vEnv;
    handles.ramp.rampelementtext{kk}=sprintf('%s',handles.Motif.Element.text{ii});
    kk=kk+1;
    clear ramptemp;
end
handles.ramp.rampelementtext{kk}=handles.Motif.name;
handles.ramp.rampelementtext{kk+1}=sprintf('REV %s',handles.Motif.name);
handles.ramp.rampelementtext{kk+2}=sprintf('REVSO %s',handles.Motif.name);
handles.ramp.rampelementtext{kk+3}='custom add';
set(handles.Add_ramp_popup,'string',handles.ramp.rampelementtext);

%update handles structure
guidata(hObject,handles);

% --- Executes on button press in Add_ramp.
function Add_ramp_Callback(hObject, eventdata, handles)
% hObject    handle to Add_ramp (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
element2add=get(handles.Add_ramp_popup,'Value');
clear sadd;
ii=element2add;
if element2add<(length(handles.ramp.rampelementtext)-3)
    sadd.tti=[handles.Motif.Element.time(4,ii) handles.Motif.Element.time(4,ii+1)];
    addsong=handles.ramp.(handles.Motif.Element.text{ii});
    sadd.numtt =diff(sadd.tti);
    sadd.maxttintime=(sadd.numtt)/handles.os.F;
    if isempty(handles.ms.t)
        sadd.maxt = 0;
    else
        sadd.maxt=max(handles.ms.t);
    end
    sadd.t = linspace(0,sadd.maxttintime,length(handles.os.song(sadd.tti(1):sadd.tti(2))))+sadd.maxt;
    %add new element to end of existing added song
    handles.ms.t_old=handles.ms.t;
    handles.ms.song_old=handles.ms.song;
    if size(handles.ms.t,1)>1
        handles.ms.t=handles.ms.t';
    end
    if size(sadd.t,1)>1
        sadd.t=sadd.t';
    end
    handles.ms.t = horzcat(handles.ms.t,sadd.t);
    if size(addsong,1)>1
        addsong=addsong';
    end
    handles.ms.song=horzcat(handles.ms.song,addsong);
    clear sadd;clear addsong;
    % clear plots and replot modified song oscillogram and spectrogram
    handles=Replot_Modified_Song(hObject,handles);
    
elseif  element2add==length(handles.ramp.rampelementtext)-3 %add motif with ramp at beginning and end only
    sadd.time=[handles.Motif.starttime handles.Motif.endtime];
    sadd.tti(1)=max(find(handles.os.t<sadd.time(1,1)));
    sadd.tti(2)=min(find(handles.os.t>sadd.time(1,2)));
    sadd.numtt =diff(sadd.tti);
    sadd.maxttintime=(sadd.numtt)/handles.os.F;
    if isempty(handles.ms.t)
        sadd.maxt = 0;
    else
        sadd.maxt=max(handles.ms.t);
    end
    sadd.t = linspace(0,sadd.maxttintime,length(handles.os.song(sadd.tti(1):sadd.tti(2))))+sadd.maxt;
    handles.ms.t_old=handles.ms.t;
    handles.ms.song_old=handles.ms.song;
    if size(handles.ms.t,1)>1
        handles.ms.t=handles.ms.t';
    end
    if size(sadd.t,1)>1
        sadd.t=sadd.t';
    end
    handles.ms.t = horzcat(handles.ms.t,sadd.t);
    if size(handles.ms.song,1)>1
        handles.ms.song=handles.ms.song';
    end
    addsong=handles.os.song(sadd.tti(1):sadd.tti(2));
    if size(addsong,1)>1
        addsong=addsong';
    end
    ramptemp.element2ramp=addsong;
    if size(ramptemp.element2ramp,1)>1
        ramptemp.element2ramp=ramptemp.element2ramp';
    end
    ramptemp.vEnv(1:length(ramptemp.element2ramp)) = 1;
    rampperiod=3/1000*handles.os.F;
    ramptemp.loAngle = linspace(-pi/2,0,rampperiod);
    ramptemp.hiAngle = linspace(0,pi/2,rampperiod);
    ramptemp.loEnv = cos(ramptemp.loAngle);
    ramptemp.hiEnv = cos(ramptemp.hiAngle);
    ramptemp.vEnv(1:length(ramptemp.loEnv)) =ramptemp.loEnv;
    ramptemp.vEnv(end-length(ramptemp.hiEnv)+1:end) = ramptemp.hiEnv;
    if size(ramptemp.vEnv,1)>1
        ramptemp.vEnv=ramptemp.vEnv';
    end
    handles.ramp.rampmotif= ramptemp.element2ramp.*ramptemp.vEnv;
    handles.ms.song=horzcat(handles.ms.song,handles.ramp.rampmotif);
    clear sadd;clear ramptemp;
    % clear plots and replot modified song oscillogram and spectrogram
    handles=Replot_Modified_Song(hObject,handles);
    
elseif element2add==length(handles.ramp.rampelementtext)-2 %add revmotif with ramp at beginning and end
    sadd.time=[handles.Motif.starttime handles.Motif.endtime];
    sadd.tti(1)=max(find(handles.os.t<sadd.time(1,1)));
    sadd.tti(2)=min(find(handles.os.t>sadd.time(1,2)));
    sadd.numtt =diff(sadd.tti);
    sadd.maxttintime=(sadd.numtt)/handles.os.F;
    if isempty(handles.ms.t)
        sadd.maxt = 0;
    else
        sadd.maxt=max(handles.ms.t);
    end
    sadd.t = linspace(0,sadd.maxttintime,length(handles.os.song(sadd.tti(1):sadd.tti(2))))+sadd.maxt;
    handles.ms.t_old=handles.ms.t;
    handles.ms.song_old=handles.ms.song;
    if size(handles.ms.t,1)>1
        handles.ms.t=handles.ms.t';
    end
    if size(sadd.t,1)>1
        sadd.t=sadd.t';
    end
    handles.ms.t = horzcat(handles.ms.t,sadd.t);
    if size(handles.ms.song,1)>1
        handles.ms.song=handles.ms.song';
    end
    addsong=handles.os.song(sadd.tti(1):sadd.tti(2));
    if size(addsong,1)>1
        addsong=addsong';
    end
    addsong=addsong(end:-1:1);
    ramptemp.element2ramp=addsong;
    if size(ramptemp.element2ramp,1)>1
        ramptemp.element2ramp=ramptemp.element2ramp';
    end
    ramptemp.vEnv(1:length(ramptemp.element2ramp)) = 1;
    rampperiod=3/1000*handles.os.F;
    ramptemp.loAngle = linspace(-pi/2,0,rampperiod);
    ramptemp.hiAngle = linspace(0,pi/2,rampperiod);
    ramptemp.loEnv = cos(ramptemp.loAngle);
    ramptemp.hiEnv = cos(ramptemp.hiAngle);
    ramptemp.vEnv(1:length(ramptemp.loEnv)) =ramptemp.loEnv;
    ramptemp.vEnv(end-length(ramptemp.hiEnv)+1:end) = ramptemp.hiEnv;
    if size(ramptemp.vEnv,1)>1
        ramptemp.vEnv=ramptemp.vEnv';
    end
    handles.ramp.rampREVmotif= ramptemp.element2ramp.*ramptemp.vEnv;
    handles.ms.song=horzcat(handles.ms.song,handles.ramp.rampREVmotif);
    clear sadd;clear ramptemp;
    % clear plots and replot modified song oscillogram and spectrogram
    handles=Replot_Modified_Song(hObject,handles);
    
elseif element2add==length(handles.ramp.rampelementtext)-1 %add REVSO motif with ramp at beginning and end
    sadd.tti(1)=handles.Motif.Element.time(4,1);
    sadd.tti(2)=handles.Motif.Element.time(4,end);
    sadd.numtt =diff(sadd.tti);
    sadd.maxttintime=(sadd.numtt)/handles.os.F;
    if isempty(handles.ms.t)
        sadd.maxt = 0;
    else
        sadd.maxt=max(handles.ms.t);
    end
    sadd.t = linspace(0,sadd.maxttintime,length(handles.os.song(sadd.tti(1):sadd.tti(2))))+sadd.maxt;
    handles.ms.t_old=handles.ms.t;
    handles.ms.song_old=handles.ms.song;
    if size(handles.ms.t,1)>1
        handles.ms.t=handles.ms.t';
    end
    if size(sadd.t,1)>1
        sadd.t=sadd.t';
    end
    handles.ms.t = horzcat(handles.ms.t,sadd.t);
    addsong=[];
    jj=size(handles.Motif.Element.text,2);
    for ii=1:size(handles.Motif.Element.text,2)
        if ii==1
            addsong2=handles.os.song(handles.Motif.Element.time(4,jj):handles.Motif.Element.time(4,jj+1));
        else
            addsong2=handles.os.song(handles.Motif.Element.time(4,jj)+1:handles.Motif.Element.time(4,jj+1));
        end
        if size(handles.ms.song,1)>1
            handles.ms.song=handles.ms.song';
        end
        if size(addsong2,1)>1
            addsong2=addsong2';
        end
        addsong=horzcat(addsong,addsong2);
        jj=jj-1;
        clear addsong2;
    end
    ramptemp.element2ramp=addsong;
    if size(ramptemp.element2ramp,1)>1
        ramptemp.element2ramp=ramptemp.element2ramp';
    end
    ramptemp.vEnv(1:length(ramptemp.element2ramp)) = 1;
    rampperiod=3/1000*handles.os.F;
    ramptemp.loAngle = linspace(-pi/2,0,rampperiod);
    ramptemp.hiAngle = linspace(0,pi/2,rampperiod);
    ramptemp.loEnv = cos(ramptemp.loAngle);
    ramptemp.hiEnv = cos(ramptemp.hiAngle);
    ramptemp.vEnv(1:length(ramptemp.loEnv)) =ramptemp.loEnv;
    ramptemp.vEnv(end-length(ramptemp.hiEnv)+1:end) = ramptemp.hiEnv;
    if size(ramptemp.vEnv,1)>1
        ramptemp.vEnv=ramptemp.vEnv';
    end
    handles.ramp.rampREVSOmotif= ramptemp.element2ramp.*ramptemp.vEnv;
    handles.ms.song=horzcat(handles.ms.song,handles.ramp.rampREVSOmotif);
    clear sadd;clear ramptemp;
    % clear plots and replot modified song oscillogram and spectrogram
    handles=Replot_Modified_Song(hObject,handles);
    
elseif element2add==length(handles.ramp.rampelementtext)
    prompt={'Specify song elements to combine (separate with space)'};
    dlg_title = 'Create custom song';
    num_lines = 1;
    def={''};
    answer = inputdlg(prompt,dlg_title,num_lines,def);
    answer2=regexp(answer,' ','split');
    for jj=1:size(answer2{1,1},2)
        val=strmatch(answer2{1,1}{1,jj},handles.ramp.rampelementtext);
        clear ii;
        ii=val;
        clear sadd;
        sadd.tti=[handles.Motif.Element.time(4,ii) handles.Motif.Element.time(4,ii+1)];
        addsong=handles.ramp.(handles.Motif.Element.text{ii});
        sadd.numtt =diff(sadd.tti);
        sadd.maxttintime=(sadd.numtt)/handles.os.F;
        if isempty(handles.ms.t)
            sadd.maxt = 0;
        else
            sadd.maxt=max(handles.ms.t);
        end
        sadd.t = linspace(0,sadd.maxttintime,length(handles.os.song(sadd.tti(1):sadd.tti(2))))+sadd.maxt;
        handles.ms.t_old=handles.ms.t;
        handles.ms.song_old=handles.ms.song;
        if size(handles.ms.t,1)>1
            handles.ms.t=handles.ms.t';
        end
        if size(sadd.t,1)>1
            sadd.t=sadd.t';
        end
        handles.ms.t = horzcat(handles.ms.t,sadd.t);
        if size(addsong,1)>1
            addsong=addsong';
        end
        handles.ms.song=horzcat(handles.ms.song,addsong);
        clear sadd;clear addsong;clear val;clear ii;
        % clear plots and replot modified song oscillogram and spectrogram
        handles=Replot_Modified_Song(hObject,handles);
    end
end

%update handles structure
guidata(hObject, handles);

% --- Executes on button press in Add_noise.
function Add_noise_Callback(hObject, eventdata, handles)
% hObject    handle to Add_noise (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
[YN,noiseprop]=WhiteNoiseQApanel;

if strcmpi(YN,'Yes')
nmean = noiseprop.mean;
nvar = noiseprop.var;
nlen = noiseprop.len;
nlen = nlen/1000;                          % Convert from ms to sec.
lentt=ceil(nlen*handles.ms.F)+1;      % length of tt in sampling rate F.
if isempty(handles.ms.t),    
    maxt = 0; 
else
    maxt=max(handles.ms.t);
end
t = linspace(0,nlen,lentt)+maxt;
handles.ms.t_old=handles.ms.t;
handles.ms.song_old=handles.ms.song;
if size(handles.ms.t,1)>1
    handles.ms.t=handles.ms.t';
end
if size(t,1)>1
    t=t';
end
handles.ms.t = horzcat(handles.ms.t,t);
if size(handles.ms.song,1)>1
    handles.ms.song=handles.ms.song';
end
addsong=sqrt(nvar)*randn(1,lentt)+nmean;
if size(addsong,1)>1
    addsong=addsong';
end
addsong=addsong(end:-1:1);
handles.ms.song=horzcat(handles.ms.song,addsong);

clear t;clear addsong;
handles=Replot_Modified_Song(hObject,handles);
end
 
guidata(hObject, handles);

% --- Executes on button press in Add_silence.
function Add_silence_Callback(hObject, eventdata, handles)
% hObject    handle to Add_silence (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

user_entry = str2double(get(handles.Silence_input,'string'));
if isnan(user_entry)
	errordlg('You must enter a numeric value','Bad Input','modal')
	return
end
handles.ms.silence_period=user_entry;
tt=handles.ms.silence_period/1000; % Convert from msec to sec.
lentt=ceil(tt*handles.ms.F)+1;      % length of tt in sampling rate F.
if isempty(handles.ms.t),    
    maxt = 0; 
else
    maxt=max(handles.ms.t);
end
t = linspace(0,tt,lentt)+maxt;
handles.ms.t_old=handles.ms.t;
handles.ms.song_old=handles.ms.song;
if size(handles.ms.t,1)>1
    handles.ms.t=handles.ms.t';
end
if size(t,1)>1
    t=t';
end
handles.ms.t = horzcat(handles.ms.t,t);
if size(handles.ms.song,1)>1
    handles.ms.song=handles.ms.song';
end
handles.ms.song=horzcat(handles.ms.song,zeros(1,lentt));

size(handles.ms.song)
size(handles.ms.t)
clear t; 
handles=Replot_Modified_Song(hObject,handles);

guidata(hObject, handles);


% --- Executes on button press in Undo.
function Undo_Callback(hObject, eventdata, handles)
% hObject    handle to Undo (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
handles.ms.t    =handles.ms.t_old;
handles.ms.song =handles.ms.song_old;
Child = get(handles.Oscillogram_Modified_Song,'Children');
set(Child,'XData',handles.ms.t,'YData',handles.ms.song); 
handles=Replot_Modified_Song(hObject,handles);

%update handles structure
guidata(hObject, handles);

% --- Executes on button press in Reverse_modified_song.
function Reverse_modified_song_Callback(hObject, eventdata, handles)
% hObject    handle to Reverse_modified_song (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

handles.ms.song=handles.ms.song(end:-1:1);
handles=Replot_Modified_Song(hObject,handles);

guidata(hObject,handles);

% --- Executes on button press in Register.
function Register_Callback(hObject, eventdata, handles)
% hObject    handle to Register (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

if isempty(handles.ms.song)
    error('You need to add song region first!');
end

val=get(handles.Reg_FileType,'Value');
songtypes=get(handles.Reg_SongType,'String');
songtype=songtypes{get(handles.Reg_SongType,'Value')};

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
        save(fullfile(savedir,savename),'stim');
    otherwise
        error('Unknown option!')
end

guidata(hObject,handles);

% --- Executes on button press in Save_wave.
function Save_wave_Callback(hObject, eventdata, handles)
% hObject    handle to Save_wave (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
if isempty(handles.ms.song)
    error('You need to add song region first!');
end
[filename, pathname] = uiputfile({'*.wav';'*.*'}, 'Save Modified Song Data as');
wavwrite(handles.ms.song,handles.ms.F,handles.ms.NBits,[pathname,filename])

% --- Executes on button press in Save_Motif.
function Save_Motif_Callback(hObject, eventdata, handles)
% hObject    handle to Save_Motif (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

if isempty(handles.Motif)
    error('You need to create motif first!');
end
[filename, pathname] = uiputfile({'*.mat';'*.*'}, 'Save Motif and Syllables detected as');
savename=fullfile(pathname,filename);
Syllable=handles.sliders;
Motif=handles.Motif;
save(savename,'Motif','Syllable');

% --- Executes on button press in Load_Motif_Setting.
function Load_Motif_Setting_Callback(hObject, eventdata, handles)
% hObject    handle to Load_Motif_Setting (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

[filename, pathname] = uigetfile({'*.mat';'*.*'}, 'Load Motif/Syllable slider as');
loadname=fullfile(pathname,filename);
loadmotif=load(loadname);
handles.loadmotif=loadmotif;
handles.Motif=handles.loadmotif.Motif;
handles.sliders=handles.loadmotif.Syllable;

for ii=1:size(handles.sliders.updown_indtime,2)
    %plot sliderpoint in mid of yaxis
    ylim=get(handles.Spectrogram_Song,'Ylim');
    midypos=ylim(1,2)/2;
    handles.sliders.updown{ii}=impoint(handles.Spectrogram_Song,handles.sliders.updown_indtime(1,ii),midypos);
    textstring=num2str(ii); 
    b=handles.sliders.updown{ii};
    if mod(ii,2) == 0
        setColor(b,'b');%number is even
    else
        setColor(b,'k');%number is odd
    end  
    setString(b,textstring);
    addNewPositionCallback(b,@(b) title(sprintf('(%1.3f,%1.0f,%1.0d)',b(1),b(2),ii)));
 
    %constraint sliderpoint to move only horizontally.
    fcn=makeConstrainToRectFcn('impoint',get(handles.Spectrogram_Song,'Xlim'),[midypos midypos]);
    setPositionConstraintFcn(b,fcn);
    clear b;
end
ylim=get(handles.Spectrogram_Song,'Ylim');
ylim=ylim(1,2)-(0.01*ylim(1,2));
handles.ylim2=repmat(ylim,1,size(handles.spec.os.specT(handles.Motif.starttimexindex:handles.Motif.endtimextindex),2));
axes(handles.Spectrogram_Song);hold on;

%plot motif range 
handles.Motif.plot=plot(handles.Spectrogram_Song,handles.spec.os.specT(handles.Motif.starttimexindex:handles.Motif.endtimextindex),handles.ylim2,'g');
ylim=get(handles.Spectrogram_Song,'Ylim');
ylim3=ylim(1,2)-(0.25*ylim(1,2));
findpoints=find(handles.sliders.pospoint>=handles.Motif.starttime&handles.sliders.pospoint<=handles.Motif.endtime);
numpoints=size(findpoints,1);
numelement=numpoints-1;
for ii=1:numelement
texttimetoplot(1,ii)=handles.Motif.Element.time(1,ii)+handles.Motif.Element.timediff(1,ii);
end
for ii=1:numelement
axes(handles.Spectrogram_Song);
handles.Motif.textplot{1,ii}=text(texttimetoplot(1,ii),ylim3,handles.Motif.Element.text{ii},'BackgroundColor','white');
end
handles.Motif.playpop=horzcat(handles.Motif.name,handles.Motif.Element.text);
set(handles.Play_Motif_Popup,'string',handles.Motif.playpop);
set(handles.Add_Popup,'string',handles.Motif.playpop);
set(handles.Revadd_popup,'string',handles.Motif.playpop);

guidata(hObject,handles);

% --- Executes on selection change in Add_Popup.
function Add_Popup_Callback(hObject, eventdata, handles)
% hObject    handle to Add_Popup (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns Add_Popup contents as cell array
%        contents{get(hObject,'Value')} returns selected item from Add_Popup

element2add=get(handles.Add_Popup,'Value');
 

% --- Executes on selection change in Play_Motif_Popup.
function Play_Motif_Popup_Callback(hObject, eventdata, handles)
% hObject    handle to Play_Motif_Popup (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns Play_Motif_Popup contents as cell array
%        contents{get(hObject,'Value')} returns selected item from Play_Motif_Popup
 
% --- Executes during object creation, after setting all properties.
function Play_Motif_Popup_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Play_Motif_Popup (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% --- Executes during object creation, after setting all properties.
function Add_Popup_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Add_Popup (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% --- Executes during object creation, after setting all properties.
function Spectro_cutoff_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Spectro_cutoff (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end

% --- Executes during object creation, after setting all properties.
function MS_Spectro_cutoff_CreateFcn(hObject, eventdata, handles)
% hObject    handle to MS_Spectro_cutoff (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end

% --- Executes on selection change in Revadd_popup.
function Revadd_popup_Callback(hObject, eventdata, handles)
% hObject    handle to Revadd_popup (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns Revadd_popup contents as cell array
%        contents{get(hObject,'Value')} returns selected item from Revadd_popup


% --- Executes during object creation, after setting all properties.
function Revadd_popup_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Revadd_popup (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Silence_input_Callback(hObject, eventdata, handles)
% hObject    handle to Silence_input (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Silence_input as text
%        str2double(get(hObject,'String')) returns contents of Silence_input as a double


% --- Executes during object creation, after setting all properties.
function Silence_input_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Silence_input (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in Add_ramp_popup.
function Add_ramp_popup_Callback(hObject, eventdata, handles)
% hObject    handle to Add_ramp_popup (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns Add_ramp_popup contents as cell array
%        contents{get(hObject,'Value')} returns selected item from Add_ramp_popup


% --- Executes during object creation, after setting all properties.
function Add_ramp_popup_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Add_ramp_popup (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in Reg_FileType.
function Reg_FileType_Callback(hObject, eventdata, handles)
% hObject    handle to Reg_FileType (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns Reg_FileType contents as cell array
%        contents{get(hObject,'Value')} returns selected item from Reg_FileType


% --- Executes during object creation, after setting all properties.
function Reg_FileType_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Reg_FileType (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in Reg_SongType.
function Reg_SongType_Callback(hObject, eventdata, handles)
% hObject    handle to Reg_SongType (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns Reg_SongType contents as cell array
%        contents{get(hObject,'Value')} returns selected item from Reg_SongType


% --- Executes during object creation, after setting all properties.
function Reg_SongType_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Reg_SongType (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
