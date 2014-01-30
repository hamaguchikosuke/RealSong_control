function varargout = SpectrumFilterDesign_001(varargin)
% SpectrumFilterDesign_001 MATLAB code for SpectrumFilterDesign_001.fig
%      SpectrumFilterDesign_001, by itself, creates a new SpectrumFilterDesign_001 or raises the existing
%      singleton*.
%
%      H = SpectrumFilterDesign_001 returns the handle to a new SpectrumFilterDesign_001 or the handle to
%      the existing singleton*.
%
%      SpectrumFilterDesign_001('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in SpectrumFilterDesign_001.M with the given input arguments.
%
%      SpectrumFilterDesign_001('Property','Value',...) creates a new SpectrumFilterDesign_001 or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before SpectrumFilterDesign_001_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to SpectrumFilterDesign_001_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help SpectrumFilterDesign_001

% Last Modified by GUIDE v2.5 26-Feb-2013 17:57:45

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @SpectrumFilterDesign_001_OpeningFcn, ...
                   'gui_OutputFcn',  @SpectrumFilterDesign_001_OutputFcn, ...
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


% --- Executes just before SpectrumFilterDesign_001 is made visible.
function SpectrumFilterDesign_001_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to SpectrumFilterDesign_001 (see VARARGIN)

handles=init_var(hObject,eventdata,handles);

if nargin>=4
    handles.parent_mfile=varargin{1};
    handles.ParentGUI = varargin{2};
    fprintf('SpectrumFilterDesign (%s) mode\n',handles.parent_mfile);
else
    handles.parent_mfile=[];
    handles.ParentGUI = [];
    disp('SpectrumFilterDesign (Standalone) mode');
end


% Update handles structure
guidata(hObject, handles);


% Choose default command line output for SpectrumFilterDesign_001
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes SpectrumFilterDesign_001 wait for user response (see UIRESUME)
% uiwait(handles.figure_spectrumfilterdesign);


% --- Outputs from this function are returned to the command line.
function varargout = SpectrumFilterDesign_001_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;



function edit_boundaries_Callback(hObject, eventdata, handles)
% hObject    handle to edit_boundaries (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_boundaries as text
%        str2double(get(hObject,'String')) returns contents of edit_boundaries as a double

handles.pm.comb_filter=update_spectrum_boundaries(handles);
draw_comb_filter(handles.gph.comb_filter_plot,...
    handles.pm.comb_filter.f,...
    handles.pm.comb_filter.spec);
guidata(hObject,handles);


% --- Executes during object creation, after setting all properties.
function edit_boundaries_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_boundaries (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit_bandwidth_Callback(hObject, eventdata, handles)
% hObject    handle to edit_bandwidth (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_bandwidth as text
%        str2double(get(hObject,'String')) returns contents of edit_bandwidth as a double
handles.pm.comb_filter=update_spectrum_boundaries(handles);
draw_comb_filter(handles.gph.comb_filter_plot,...
    handles.pm.comb_filter.f,...
    handles.pm.comb_filter.spec);
guidata(hObject,handles);



% --- Executes during object creation, after setting all properties.
function edit_bandwidth_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_bandwidth (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pb_get_spec.
function pb_get_spec_Callback(hObject, eventdata, handles,varargin)
% hObject    handle to pb_get_spec (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% this returns obj.spec and obj.f and obj.spectrum
% fprintf('Adding %dth data...\n',handles.pm.n_target_added);

if nargin<=3
handles.pm.target_spectrums_obj(handles.pm.n_target_added)=...
    feval(handles.parent_mfile,'return_target_spectrums',...
    handles.ParentGUI,eventdata,guidata(handles.ParentGUI));
elseif nargin==4
    % % The format of target_spectrum_obj is as follows;
    % obj.f=      handles.pm.feature2.f;
    % obj.spec = [];
    % for tt=1:length(t_maintarget)
    % out=pb_getinfo_Callback(hObject, eventdata, handles,t_maintarget(tt));
    % obj.spec=   [obj.spec, out.m_powSpec];
    % end
    
    handles.pm.target_spectrums_obj(handles.pm.n_target_added)=...
        varargin{1};
    online_speccorr=[];
elseif nargin==5
    handles.pm.target_spectrums_obj(handles.pm.n_target_added)=...
        varargin{1};
    online_speccorr=varargin{2};
end

% handles.pm.target_spectrums_obj(handles.pm.n_target_added);
% handles=update_target_spectrum(handles);

axes(handles.axes_spectrum);hold on;
draw_target_spectrum(handles.pm.target_spectrums_obj(handles.pm.n_target_added));

axes(handles.axes_info);hold on;
h=get(gca,'Children');
n=size(handles.pm.target_spectrums_obj(handles.pm.n_target_added).spec,2);
index=length(h)+[1:n];

% handles.pm.comb_filter;
draw_speccorr_value(index,...
    handles.pm.target_spectrums_obj(handles.pm.n_target_added),...
    handles.pm.comb_filter);

if length(online_speccorr)>0
    plot(index,online_speccorr,'r.');
end
axis tight;

handles.pm.n_target_added   = handles.pm.n_target_added+1;

guidata(hObject,handles);


function draw_target_spectrum(obj);
plot(obj.f,obj.spec);

function draw_speccorr_value(index,obj,comb_filter)
%    size(obj.spec)
%    size(comb_filter.spec)
c= sum(obj.spec./repmat(sum(obj.spec,1),size(obj.spec,1),1).*repmat(comb_filter.spec(:),1,size(obj.spec,2)),1);
plot(index,c,'o');hold on;


function push_spec_speccorr_Callback(hObject, eventdata, handles,varargin)
% hObject    handle to pb_get_spec (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% this returns obj.spec and obj.f and obj.spectrum
fprintf('Pushed %dth data...\n',handles.pm.n_target_added);

% obj=varargin{1};

handles.pm.target_spectrums_obj(handles.pm.n_target_added)=varargin{1};

axes(handles.axes_spectrum);hold on;
draw_target_spectrum(handles.pm.target_spectrums_obj(handles.pm.n_target_added));

axes(handles.axes_info);hold on;
h=get(gca,'Children');
n=size(handles.pm.target_spectrums_obj(handles.pm.n_target_added).spec,2);
index=length(h)+[1:n]

handles.pm.comb_filter
draw_speccorr_value(index,...
    handles.pm.target_spectrums_obj(handles.pm.n_target_added),...
    handles.pm.comb_filter);

handles.pm.n_target_added   = handles.pm.n_target_added+1;

% guidata(hObject,handles);
% --- Executes on button press in pb_reset.
function pb_reset_Callback(hObject, eventdata, handles)
% hObject    handle to pb_reset (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
axes(handles.axes_spectrum);cla;hold on;
axes(handles.axes_info);cla;hold on;

handles=init_var(hObject,eventdata,handles);
handles.pm.comb_filter=update_spectrum_boundaries(handles);
draw_comb_filter(handles.gph.comb_filter_plot,...
    handles.pm.comb_filter.f,...
    handles.pm.comb_filter.spec);
guidata(hObject,handles);



% --- Executes on button press in pb_load.
function pb_load_Callback(hObject, eventdata, handles)
% hObject    handle to pb_load (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in pb_save.
function pb_save_Callback(hObject, eventdata, handles)
% hObject    handle to pb_save (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)




% --- Executes on button press in pb_undo.
function pb_undo_Callback(hObject, eventdata, handles)
% hObject    handle to pb_undo (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

function handles=update_target_spectrum(handles)

axes(handles.axes_spectrum);
delete_handles=get(handles.axes_spectrum,'Children')
delete_handles=setdiff(delete_handles,handles.gph.comb_filter_plot);
delete(delete_handles);

for ii=1:length(handles.pm.target_spectrums_obj)
    plot(handles.pm.target_spectrums_obj(ii).f,handles.pm.target_spectrums_obj(ii).spec,'k');
    hold on;
end

handles.pm.comb_filter=update_spectrum_boundaries(handles);
draw_comb_filter(handles.gph.comb_filter_plot,...
    handles.pm.comb_filter.f,...
    handles.pm.comb_filter.spec);

guidata(handles.axes_spectrum,handles);

function out=update_spectrum_boundaries(handles)

samprate= eval(get(handles.edit_samprate,'String'));
nFFT= eval(get(handles.edit_fft_windowsize,'String'));

frange= eval(get(handles.edit_frange,'String'));

f= samprate*[0:nFFT]/nFFT;
findex = find(f>frange(1) & f<frange(2));
f=f(findex);

comb_filter = zeros(length(findex),1);

boundaries= eval(get(handles.edit_boundaries,'String'));
bandwidth  = eval(get(handles.edit_bandwidth,'String'));

fprintf('Comb filter design: filter band at ');
fprintf('%d ',boundaries);
fprintf('with +-%d Hz band (1x%d).\n',bandwidth,length(findex));

for kk=1:length(boundaries)
posi_boundaries_index = find(f>=boundaries(kk) & f<boundaries(kk)+bandwidth);
comb_filter(posi_boundaries_index)=1;
nega_boundaries_index = find(f>=boundaries(kk)-bandwidth & f<boundaries(kk));
comb_filter(nega_boundaries_index)=-1;
end

if get(handles.tg_polarity,'Value')
    comb_filter = - comb_filter;
end

out.f= f;
out.spec= comb_filter;
out.nFFT = nFFT;
out.samprate = samprate;
out.frange   = frange;
out.boundaries= boundaries;
out.bandwidth= bandwidth;

if isempty(handles.parent_mfile)
    % standalone mode. do nothing.
else    
    feval(handles.parent_mfile,'update_spectrum_filter_parameters',...
        handles.ParentGUI,[],guidata(handles.ParentGUI),out);
end


function draw_comb_filter(h,f,spec)

set(h,'XData',f,'YData',spec);
axis tight;



% --- Executes on button press in tg_polarity.
function tg_polarity_Callback(hObject, eventdata, handles)
% hObject    handle to tg_polarity (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of tg_polarity

handles=update_spectrum_boundaries(handles);

function edit_samprate_Callback(hObject, eventdata, handles)
% hObject    handle to edit_samprate (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_samprate as text
%        str2double(get(hObject,'String')) returns contents of edit_samprate as a double
handles.pm.comb_filter=update_spectrum_boundaries(handles);
draw_comb_filter(handles.gph.comb_filter_plot,...
    handles.pm.comb_filter.f,...
    handles.pm.comb_filter.spec);
guidata(hObject,handles);

% --- Executes during object creation, after setting all properties.
function edit_samprate_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_samprate (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit_fft_windowsize_Callback(hObject, eventdata, handles)
% hObject    handle to edit_fft_windowsize (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_fft_windowsize as text
%        str2double(get(hObject,'String')) returns contents of edit_fft_windowsize as a double
handles.pm.comb_filter=update_spectrum_boundaries(handles);
draw_comb_filter(handles.gph.comb_filter_plot,...
    handles.pm.comb_filter.f,...
    handles.pm.comb_filter.spec);
guidata(hObject,handles);

% --- Executes during object creation, after setting all properties.
function edit_fft_windowsize_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_fft_windowsize (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end




function handles=init_var(hObject,eventdata,handles)
handles.pm.target_spectrums_= [];
handles.pm.n_target_added   = 1;
handles.pm.frange =         [400,10000];

axes(handles.axes_spectrum);
handles.gph.comb_filter_plot=plot(handles.pm.frange,[0 0],'r');

% --- Executes during object creation, after setting all properties.
function tg_polarity_CreateFcn(hObject, eventdata, handles)
% hObject    handle to tg_polarity (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called


function comb_filter =return_spectrum_filter(hObject,eventdata,handles)
handles.pm.comb_filter=update_spectrum_boundaries(handles);
guidata(hObject,handles);
comb_filter=handles.pm.comb_filter;



function edit_frange_Callback(hObject, eventdata, handles)
% hObject    handle to edit_frange (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_frange as text
%        str2double(get(hObject,'String')) returns contents of edit_frange as a double
handles.pm.comb_filter=update_spectrum_boundaries(handles);
draw_comb_filter(handles.gph.comb_filter_plot,...
    handles.pm.comb_filter.f,...
    handles.pm.comb_filter.spec);
guidata(hObject,handles);

% --- Executes during object creation, after setting all properties.
function edit_frange_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_frange (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


function set_parameters(hObject,eventdata,handles,varargin);

n = nargin -3;
if rem(n,2)~=0
    error('Input must be a pair of variable and values');
end

for ii=1:n/2
    h=varargin{2*ii-1};
    val=varargin{2*ii};
    evaltxt = sprintf('set(handles.%s,''String'',''[%s]'')', h,num2str(val));
    eval(evaltxt);
end
