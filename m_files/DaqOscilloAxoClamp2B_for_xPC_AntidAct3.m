function varargout = DaqOscilloAxoClamp2B_for_xPC_AntidAct3(varargin)
% DAQOSCILLOAXOCLAMP2B_FOR_XPC_ANTIDACT3 M-file for DaqOscilloAxoClamp2B_for_xPC_AntidAct3.fig
%      DAQOSCILLOAXOCLAMP2B_FOR_XPC_ANTIDACT3, by itself, creates a new DAQOSCILLOAXOCLAMP2B_FOR_XPC_ANTIDACT3 or raises the existing
%      singleton*.
%
%      H = DAQOSCILLOAXOCLAMP2B_FOR_XPC_ANTIDACT3 returns the handle to a new DAQOSCILLOAXOCLAMP2B_FOR_XPC_ANTIDACT3 or the handle to
%      the existing singleton*.
%
%      DAQOSCILLOAXOCLAMP2B_FOR_XPC_ANTIDACT3('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in DAQOSCILLOAXOCLAMP2B_FOR_XPC_ANTIDACT3.M with the given input arguments.
%
%      DAQOSCILLOAXOCLAMP2B_FOR_XPC_ANTIDACT3('Property','Value',...) creates a new DAQOSCILLOAXOCLAMP2B_FOR_XPC_ANTIDACT3 or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before DaqOscilloAxoClamp2B_for_xPC_AntidAct3_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to DaqOscilloAxoClamp2B_for_xPC_AntidAct3_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help DaqOscilloAxoClamp2B_for_xPC_AntidAct3

% Last Modified by GUIDE v2.5 23-Aug-2012 12:14:04

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
    'gui_Singleton',  gui_Singleton, ...
    'gui_OpeningFcn', @DaqOscilloAxoClamp2B_for_xPC_AntidAct3_OpeningFcn, ...
    'gui_OutputFcn',  @DaqOscilloAxoClamp2B_for_xPC_AntidAct3_OutputFcn, ...
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


%% initialize parameters.
function handles=init_params(hObject,eventdata,handles)
%
handles.oscil.ME1_Hfactor=0.1; % input current is 10*Hfactor*nA/V.
handles.oscil.Vmfactor=0.1*1.e3; % output voltage from AxoClamp2B is 10Vm. To make it mV, also used 1.e-3.
axes(handles.vol_axe);
% chld=get('Children',handles.vol_axe)
fn=fieldnames(handles);
h=find(strcmp(fn, 'vol_data'));
if (~isempty(h)&&ishandle(handles.vol_data)),delete(handles.vol_data);end
handles.vol_data=plot(NaN,NaN,'b','MarkerSize',5);hold on;

h=find(strcmp(fn, 'vertical_lines'));
if (~isempty(h)&&ishandle(handles.vertical_lines)),delete(handles.vertical_lines);end

handles.vertical_lines=plot([NaN,NaN],[NaN,NaN],'k--');
set(handles.vol_axe,'YLim',[-100 50]);
grid on;
handles.oscil.AIchannel_number=1;
handles.oscil.AO1_TTL_Freq    = 10;
set(gcf,'Unit','Pixel');
handles.tg=evalin('base','tg');

handles.oscil.OscilMode_pos=get(gcf,'Position');

handles.oscil.CorrectSampleTime=evalin('base','tg.SampleTime');
handles.oscil.CorrectSampRate  = 1/handles.oscil.CorrectSampleTime;

handles.oscil.TTL_PulsePeriod_inSamples_id=getparamid(handles.tg,'OscilloAntidromic/MultiPhasePulseGenerator','Period');
handles.oscil.TTL_PulseWidth_inSamples_id=getparamid(handles.tg,'OscilloAntidromic/MultiPhasePulseGenerator','PulseWidth');
handles.oscil.TTL_DelayedPulseWidth_inSamples_id=getparamid(handles.tg,'OscilloAntidromic/CorrectDelayedPulseGenerator/width','Value');
handles.oscil.TTL_DelayedPulseDelay_inSamples_id=getparamid(handles.tg,'OscilloAntidromic/CorrectDelayedPulseGenerator/delay','Value');



handles.oscil.TTL_AO1gain_id=getparamid( handles.tg,'OscilloAntidromic/AO1Gain','Gain');
handles.oscil.Vm_id         =getsignalid(handles.tg,'OscilloAntidromic/E1Gain');
handles.oscil.AbsVout_id    =getsignalid(handles.tg,'OscilloAntidromic/Abs');
handles.oscil.AO1_id        =getsignalid(handles.tg,'OscilloAntidromic/AO1Gain');
% handles.oscil.PulseFamilyTTLGain_id =getsignalid(handles.tg,'OscilloAntidromic/PulseFamilyTTLGain');

handles.oscil.spikethresh_id=getparamid( handles.tg,'OscilloAntidromic/SpikeThreshold/Constant','Value');

handles.oscil.OscilloAntidromic_SelectionConstant_id = getparamid(handles.tg,'OscilloAntidromic/OscilloAntidromic_SelectionConstant','Value');
setparam(handles.tg,handles.oscil.OscilloAntidromic_SelectionConstant_id,1);


assignin('base','AO1_TTL_Freq',handles.oscil.AO1_TTL_Freq);
set(handles.popup_channelselect,'Value',handles.oscil.AIchannel_number+1);

handles.oscil.oscil_handles=get(handles.DaqOscillo_Figure,'Children');
set(handles.vol_axe,'Unit','Normal');
handles.oscil.original_vol_axe_pos=get(handles.vol_axe,'Position');
set(handles.vol_axe,'Unit','pixel');

set(handles.ui_toggle_panel,'Unit','Normal');
handles.oscil.original_ui_toggle_panel_pos=get(handles.ui_toggle_panel,'Position');
set(handles.ui_toggle_panel,'Unit','pixel');

% set(handles.tg_CurrentFamily,'Visible','Off');

outputV=10*handles.oscil.ME1_Hfactor*local_get_current(handles)/1000;
handles.oscil.last_TTLAO1gain = outputV;
userdata.last_mode = 'Oscillo';
userdata.tab_open=0;
set(handles.DaqOscillo_Figure,'UserData',userdata);


% --- Executes just before DaqOscilloAxoClamp2B_for_xPC_AntidAct3 is made visible.
function DaqOscilloAxoClamp2B_for_xPC_AntidAct3_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to DaqOscilloAxoClamp2B_for_xPC_AntidAct3 (see VARARGIN)

% Choose default command line output for DaqOscilloAxoClamp2B_for_xPC_AntidAct3
handles.output=hObject;


AutoRun = false;

mainGuiInput = find(strcmp(varargin, 'RealSong_main'));
if (isempty(mainGuiInput)) ...
        || (length(varargin) <= mainGuiInput) ...
        || (~ishandle(varargin{mainGuiInput+1}))
    AutoRun = false;
    disp('Oscillo (Standalone) mode');
else
    % Remember the handle, and adjust our position
    handles.ParentGUI = varargin{mainGuiInput+1};
    % Obtain handles using GUIDATA with the caller's handle
    mainHandles = guidata(handles.ParentGUI);
    disp('Oscillo (RealSong) mode');
    AutoRun = true;
end

% Update handles structure
handles=init_params(hObject,eventdata,handles);
% Update handles structure
guidata(hObject, handles);

if (AutoRun)
    set(handles.pb_run,'Value',1);
    pb_run_Callback(handles.pb_run, eventdata, handles)
end
% Update handles structure
guidata(hObject, handles);

% UIWAIT makes DaqOscilloAxoClamp2B_for_xPC_AntidAct3 wait for user response (see UIRESUME)
% uiwait(handles.DaqOscillo_Figure);



%---------------------------------------------%
%        SLIDER CALLBACK                      %
%---------------------------------------------%
% --- Executes on slider movement.
function [current,outputV]=sl_current_Callback(hObject, eventdata, handles)
% hObject    handle to sl_current (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider
current=local_get_current(handles);
set(handles.ed_current,'String',num2str(current));
handles.oscil.current=current;

% input current is 10*Hfactor*nA/V.
% when Hfactror=0.1,  1V =1nA output.
outputV=10*handles.oscil.ME1_Hfactor*handles.oscil.current/1000;
% to make it nA to pA.

setparam(handles.tg,handles.oscil.TTL_AO1gain_id,outputV);
handles.oscil.last_TTLAO1gain = outputV; % -350pA.
% guidata(hObject,handles);

%%--- here comes the set param part.

function current=local_get_current(handles)
min_slider=str2num(get(handles.text_min_current,'String'));
max_slider=str2num(get(handles.text_max_current,'String'));
current=min_slider+(max_slider-min_slider)*get(handles.sl_current,'Value');

current=current;

% --- Executes during object creation, after setting all properties.
function sl_current_CreateFcn(hObject, eventdata, handles)
% hObject    handle to sl_current (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on selection change in popup_channelselect.
function popup_channelselect_Callback(hObject, eventdata, handles)
% hObject    handle to popup_channelselect (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns popup_channelselect contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popup_channelselect

contents = get(hObject,'String');
channel_number=contents{get(hObject,'Value')};
handles.oscil.AIchannel_number=str2num(channel_number);
guidata(hObject,handles);

% --- Executes during object creation, after setting all properties.
function popup_channelselect_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popup_channelselect (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function ed_min_current_Callback(hObject, eventdata, handles)
% hObject    handle to text_min_current (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of text_min_current as text
%        str2double(get(hObject,'String')) returns contents of text_min_current as a double


% --- Executes during object creation, after setting all properties.
function text_min_current_CreateFcn(hObject, eventdata, handles)
% hObject    handle to text_min_current (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end





% --- Executes on button press in pb_run.
function pb_run_Callback(hObject, eventdata, handles)
% hObject    handle to pb_run (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% make sure that correct mode and figure panels are set.
% handles=tg_Antidromic_Mode_Callback(handles.tg_Antidromic_Mode, eventdata, handles);
% handles=mode_select_panel_SelectionChangeFcn(handles.mode_select_panel, eventdata, handles);

run_oscillo=get(hObject,'Value');

% reset trigger current family button so that we won't trigger pulse.
id=getparamid(handles.tg,'OscilloAntidromic/TriggerButton/TrigVal','Value');
setparam(handles.tg,id,1);


if (run_oscillo)
    h = msgbox('Wait a second...');
    pause(1);
    close(h);
    
    
    % reflect current injection value if in Oscillo mode.
    userdata=get(handles.DaqOscillo_Figure,'UserData');
    if strncmp(userdata.last_mode,'Oscillo',7)
        handles=ui_toggle_panel_SelectionChangeFcn(handles.ui_toggle_panel, eventdata, handles);
        handles.oscil.current       =sl_current_Callback(handles.sl_current, eventdata, handles);
    end
    
    
    if ~isempty(intersect([7, 8],handles.tg.Scopes)) % If there remains old scope, remove them.
        remscope(handles.tg,[7,8]);
    end
    db_sc0 = addscope(handles.tg, 'host',[7, 8]);  % double buffer host soft scope 1 for pretrigger
    db_sc0_ids=get(db_sc0,'ScopeId'); sdb_sc0_ids=circshift([db_sc0_ids{:}],[0,1]);
    
    addsignal(db_sc0,[handles.oscil.Vm_id, ...
        handles.oscil.AbsVout_id,...
        handles.oscil.AO1_id]);
%     
%      addsignal(db_sc0,[handles.oscil.Vm_id, ...
%         handles.oscil.AbsVout_id,...
%         handles.oscil.AO1_id,...
%         handles.oscil.PulseFamilyTTLGain_id]);
    
    
    buff_time=.1; % [sec]
    max_rec_time=10; % [sec].
    handles.oscil.decimation=4;
    
    buff_time_nbin =ceil(buff_time*handles.oscil.CorrectSampRate/handles.oscil.decimation);
    % get(db_sc0(1))
    set(db_sc0,...
        'NumSamples', buff_time_nbin,...
        'TriggerSample', -1,...
        'TriggerMode','Scope',...
        'Decimation', handles.oscil.decimation); % sampling rate is now 11025.
    
    n_buff = ceil(max_rec_time/buff_time);
    % handles.oscil.buff_time_nbin   =buff_time_nbin;
    % handles.oscil.n_buff           =n_buff;
    % handles.oscil.n_rec_channel    =n_rawsig+n_featdata;
    
    cbuffer = circbuff(buff_time_nbin,n_buff,1);
    
    
    guidata(hObject,handles);
    
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
    plot_counter=-inf;
    
    % pause(1);
    trigger([db_sc0(scNum)]);
    
    % Use the two scopes as a double buffer to log the data.
    tic;
    while get(handles.pb_run,'Value')
        
        % Wait until this scope has finished acquiring samples
        % or the model stops (scope is interrupted).
        
        while (~strcmp(db_sc0(scNum).Status, 'Finished')||...
                strcmp(db_sc0(scNum).Status, 'Interrupted'))
            %
            %       pause(0.01);
            if strcmp(db_sc0(scNum).Status, 'Ready for being Triggered')
                fprintf('1)%s,%s\n',db_sc0(1).Status,db_sc0(2).Status);
                trigger(db_sc0(scNum));
                fprintf('1)%s,%s\n',db_sc0(1).Status,db_sc0(2).Status);
                disp('scope stopped and retriggered.')
            elseif (toc)>5
                fprintf('Realtime PC must be stopped. break!\n');
                 set(handles.pb_run,'Value',0);
                break;
            end
        end
        % Stop buffering data when the model stops.
        if (strcmp(handles.tg.Status, 'stopped')||strcmp(db_sc0(scNum).Status, 'Pre-Acquiring'))
            break
        end
        %  fprintf('2)%s,%s\n',db_sc0(1).Status,db_sc0(2).Status);
        %     tic;
        try
            t0=db_sc0(scNum).Time;
            x0=db_sc0(scNum).Data;
            mV=x0(:,1)*handles.oscil.Vmfactor;
            Timing=x0(:,2);
            TTL=x0(:,3);
            Stimulated    =0;
            cbuffer.putdata(mV);
            
        catch ME
            if strcmp(db_sc0(scNum).Status, 'Ready for being Triggered')
                %             fprintf('1)%s,%s\n',db_sc0(1).Status,db_sc0(2).Status);
                trigger(db_sc0(scNum));
                %                 fprintf('1)%s,%s\n',db_sc0(1).Status,db_sc0(2).Status);
                disp('scope stopped (%s) and retriggered.',ME)
                
            end
        end
        %   toc;
        
        
        TickTockOn = find(diff(Timing)>0.5,1,'first');
        TTLTriggered = find(diff(abs(TTL))>0,1,'first');
        
        mode=get(get(handles.ui_toggle_panel,'SelectedObject'),'Tag');
        switch mode
            case 'pb_HealthyCell'
                T=1.0;
            case 'pb_QuickMode'
                T=0.1;
            otherwise
                error('Unknown tag!')
        end
        
        index_s =ceil(T*handles.oscil.CorrectSampRate/handles.oscil.decimation);
        align_bin=ceil(index_s/4);
        
        oscillo_mode=getparam(handles.tg,handles.oscil.OscilloAntidromic_SelectionConstant_id);
        switch oscillo_mode
            case {1,2} % oscillo/antidromic
                trigger_graphic_mode=1; %'Triggered';
            case 3 % antidromic/spike collision
                trigger_graphic_mode=0; %'Flow';
            case 4 % current family
                trigger_graphic_mode=1; %'Triggered';
            otherwise
                error('Unknown option!');
        end
        
        %update voltage trace whenever timing signal (TickTock) is on.
        if ~isempty(TickTockOn)
            
            d = buff_time_nbin-TickTockOn;
            index= [(-index_s+1):0]-align_bin-d;
            vm_for_plot=cbuffer.getdata(index);
            
            xplot_range=[0 T];
            set(handles.vol_axe,'XLim',xplot_range);
            ttmp=[1:index_s]/handles.oscil.CorrectSampRate*handles.oscil.decimation;
            set(handles.vol_data,'XData',ttmp,'YData',vm_for_plot);
            drawnow;
        else
            % do nothing.
        end
        
        % When TTL trigger is detected, we have to wait for 50 ms to plot.
        if any(oscillo_mode==[2,3]) 
            %     [TickTockOn,        TTLTriggered]
            
            userdata=get(handles.DaqOscillo_Figure,'UserData');
            %          fprintf('Antidromic mode\n')
            
            
            if get(userdata.tg_Antid_Overlay1,'Value')
                axes_handle=userdata.AntidAxes1;
                do_update=1;
            elseif get(userdata.tg_Antid_Overlay2,'Value')
                axes_handle=userdata.AntidAxes2;
                do_update=1;
            else
                do_update=0;
            end
            
            if (do_update)&& (plot_counter==1)
                axes(axes_handle);
                ch=get(axes_handle,'Children');
                if ~isempty(ch), set(ch(1),'Color',[.7 .7 .7]);end
                ttmp=[1:index_s]/handles.oscil.CorrectSampRate*handles.oscil.decimation;
                vm_for_plot=cbuffer.getdata(antid_index);
                plot(ttmp*1000,vm_for_plot,'r','erasemode','none');hold on;
%                 set(axes_handle,'XLim',xplot_range,'YLim',[-100 100]);
                %         axis tight;
                
%                 if ylim
                drawnow;
            end
            
            
            plot_counter=ceil(plot_counter-1);
            
            if ~isempty(TTLTriggered)
                d = buff_time_nbin-TTLTriggered;
                antid_index= [(-index_s+1):0]-align_bin-d;
                plot_counter=1;
            end
        elseif oscillo_mode==4
              userdata=get(handles.DaqOscillo_Figure,'UserData');
    
              do_update=1;
              axes_handle=userdata.CurrentFamilyAxes;
            if (do_update)&& (plot_counter==1)
                axes(axes_handle);
               
                ttmp=[1:index_s_cf]/handles.oscil.CorrectSampRate*handles.oscil.decimation;
                vm_for_plot=cbuffer.getdata(currentfamily_index);
%                 [index_s_cf,length(vm_for_plot)];
                
                plot(ttmp*1000,vm_for_plot);hold on;
%                 set(axes_handle,'XLim',xplot_range,'YLim',[-100 100]);
                %         axis tight;
                
                drawnow;
            end
            
            
            plot_counter=ceil(plot_counter-1);
%             if plot_counter>0,      fprintf('%d.',plot_counter);end
            
            if ~isempty(TTLTriggered)
                cfT=(userdata.cf.preT+userdata.cf.durT+userdata.cf.postT)/1000;
                index_s_cf =ceil(cfT*handles.oscil.CorrectSampRate/handles.oscil.decimation);
                align_bin=ceil(userdata.cf.preT/1000*handles.oscil.CorrectSampRate/handles.oscil.decimation);
        
                d = buff_time_nbin-TTLTriggered;
                currentfamily_index= [(-index_s_cf+1):0]-align_bin-d;
                plot_counter=ceil(index_s_cf/buff_time_nbin);
            end
            
        end
        
        
        
        
        %  try
        start([db_sc0(scNum)]); tic;%trigger(db_sc0(scNum));
        %   break;
        %  end
        % Switch to the next scope.
        scNum = 3 - scNum;
        n=n+1;
        
    end
else
    % Remove the scopes we added.
    % remscope(handles.tg,[db_sc0_ids]);
    -handles.tg;
end

-handles.tg;
guidata(hObject,handles);

%---------------------------------------------%
%        ASSIGN AO.USERDATA AN OUTPUT         %
%---------------------------------------------%
function obj=local_set_output(obj,stim)
data=get(obj,'UserData');
data.output=stim.dataout;
set(obj,'UserData',data);


%---------------------------------------------%
%           HealtyCell/QuickMode selection    %
%---------------------------------------------%
% --- Executes when selected object is changed in ui_toggle_panel.
function handles=ui_toggle_panel_SelectionChangeFcn(hObject, eventdata, handles)
% hObject    handle to the selected object in ui_toggle_panel
% eventdata  structure with the following fields (see UIBUTTONGROUP)
%	EventName: string 'SelectionChanged' (read only)
%	OldValue: handle of the previously selected object or empty if none was selected
%	NewValue: handle of the currently selected object
% handles    structure with handles and user data (see GUIDATA)

% set parameter.
mode=get(get(handles.ui_toggle_panel,'SelectedObject'),'Tag');

switch mode
    case 'pb_HealthyCell'
        handles.oscil.AO1_TTL_Freq=1;
        handles.oscil.Toscillo=1/handles.oscil.AO1_TTL_Freq;
        set(handles.vol_axe,'XLim',[0 handles.oscil.Toscillo]);
        set(handles.vol_data,'MarkerSize',1,'Marker','.');
    case 'pb_QuickMode'
        handles.oscil.AO1_TTL_Freq=10;
        handles.oscil.Toscillo=1/handles.oscil.AO1_TTL_Freq;
        set(handles.vol_axe,'XLim',[0 handles.oscil.Toscillo]);
        set(handles.vol_data,'MarkerSize',5,'Marker','None');
        
    otherwise
        error('Unknown tag!')
        % Code for when there is no match.
end

setparam(handles.tg,handles.oscil.TTL_PulsePeriod_inSamples_id,[1]*ceil(1/handles.oscil.AO1_TTL_Freq/handles.tg.SampleTime));
setparam(handles.tg,handles.oscil.TTL_PulseWidth_inSamples_id,[1]*ceil(0.5/handles.oscil.AO1_TTL_Freq/handles.tg.SampleTime));
setparam(handles.tg,handles.oscil.TTL_DelayedPulseWidth_inSamples_id,...
    ceil(0.5/handles.oscil.AO1_TTL_Freq/handles.tg.SampleTime));

% setparam(handles.tg,handles.oscil.TTL_Freq_id,handles.oscil.AO1_TTL_Freq);
% guidata(hObject,handles);

function ed_current_Callback(hObject, eventdata, handles)
% hObject    handle to ed_current (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of ed_current as text
%        str2double(get(hObject,'String')) returns contents of ed_current as a double

val=str2num(get(hObject,'String'));

min_slider=str2num(get(handles.text_min_current,'String'));
max_slider=str2num(get(handles.text_max_current,'String'));

if val>max_slider
    set(handles.text_min_current,'String',num2str(-val));
    set(handles.text_max_current,'String',num2str(val));
    set(handles.sl_current,'Value',1);
elseif val<min_slider
    set(handles.text_min_current,'String',num2str(-abs(val)));
    set(handles.text_max_current,'String',num2str(abs(val)));
    set(handles.sl_current,'Value',0);
else
    set(handles.sl_current,'Value',(val-min_slider)/(max_slider-min_slider));
end

handles.oscil.current=sl_current_Callback(handles.sl_current, eventdata, handles);



% --- Executes during object creation, after setting all properties.
function ed_current_CreateFcn(hObject, eventdata, handles)
% hObject    handle to ed_current (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end




function ed_max_current_Callback(hObject, eventdata, handles)
% hObject    handle to text_max_current (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of text_max_current as text
%        str2double(get(hObject,'String')) returns contents of text_max_current as a double


% --- Executes during object creation, after setting all properties.
function text_max_current_CreateFcn(hObject, eventdata, handles)
% hObject    handle to text_max_current (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes during object creation, after setting all properties.
function ui_toggle_panel_CreateFcn(hObject, eventdata, handles)
% hObject    handle to ui_toggle_panel (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called


% --- Executes on button press in pb_HealthyCell.
function pb_HealthyCell_Callback(hObject, eventdata, handles)
% hObject    handle to pb_HealthyCell (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in pb_QuickMode.
function pb_QuickMode_Callback(hObject, eventdata, handles)
% hObject    handle to pb_QuickMode (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% --- Outputs from this function are returned to the command line.
function varargout = DaqOscilloAxoClamp2B_for_xPC_AntidAct3_OutputFcn(hObject, eventdata, handles)
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
if ~strcmp(xpctargetping, 'success')
    errordlg('Connection with target cannot be established.');
    return;
end

%Open, Build, and Download Model to the Target PC
handles.oscil.modelname='test_DAQOscillo';
open_system(handles.oscil.modelname);


handles.oscil.SampRate=44100;
handles.oscil.SampleTime=1/handles.oscil.SampRate;
assignin('base','Ts',handles.oscil.SampleTime);


% Build the model and download the image, xpcosc.dlm, to the target PC.
set_param(handles.oscil.modelname,'RTWVerbose','off'); % Configure RTW for a non-Verbose build.
rtwbuild(handles.oscil.modelname);
tg = evalin('base','tg');


handles.tg=evalin('base','tg');
guidata(hObject,handles);
assignin('base','handles',handles)



function [handles,userdata]=setup_new_panels(hObject,eventdata,handles)

figure(handles.DaqOscillo_Figure);
userdata=get(handles.DaqOscillo_Figure,'UserData');


handles_not_used_in_Antidromic_mode=[...
    handles.sl_current,...
    handles.ed_current,...
    ];

y_shift_pixel=400;
axis_pos=handles.oscil.original_vol_axe_pos;

dh_axes=axis_pos(4)/3.2;
dw_axes=axis_pos(3);
dx_axes=axis_pos(1);
dy_axes=0.05;

button_pos=handles.oscil.original_ui_toggle_panel_pos;

dh_button=button_pos(4)/6;
dw_button=button_pos(3);
dx_button=button_pos(1);
dy_button=0.05;

dy_button_top= dy_axes+2*dh_axes;
dy_button_middle= dy_axes+1*dh_axes;

% userdata.tab_open

switch eventdata
    case 'Antidromic'
        % First, switch to short pulse mode before changing gain.
        % otherwise, it is possible that we inject long current into a
        % cell.
        setparam(handles.tg,handles.oscil.OscilloAntidromic_SelectionConstant_id,2);
        
        % make TTL output 7V.
        handles.oscil.last_TTLAO1gain=getparam(handles.tg,handles.oscil.TTL_AO1gain_id);
        setparam(handles.tg,handles.oscil.TTL_AO1gain_id,7);
        fprintf('AO1 =%f[V]\n',getparam(handles.tg,handles.oscil.TTL_AO1gain_id));
        
        
        % make unnecessary Oscillo mode parameter Disabled.
        set(handles_not_used_in_Antidromic_mode,'Enable','Off');
                
        set(handles.DaqOscillo_Figure,'Visible','Off');
         if (userdata.tab_open)
            % clean up the remaining panels.
             ch=get(handles.DaqOscillo_Figure,'Children');
            delete_handles=setdiff(ch,handles.oscil.oscil_handles);
            delete(delete_handles);

         else
             handles.oscil.AntidromicMode_pos=handles.oscil.OscilMode_pos+...
                 [0 -y_shift_pixel 0 y_shift_pixel];
             set(handles.DaqOscillo_Figure,'Position',handles.oscil.AntidromicMode_pos);
             %             ch=get(handles.DaqOscillo_Figure,'Children');
             
             for ii=1:length(handles.oscil.oscil_handles)
                 pos=get(handles.oscil.oscil_handles(ii),'Position');
                 set(handles.oscil.oscil_handles(ii),'Position',pos+[0 y_shift_pixel 0 0]);
             end
         end
        
      
        handles.AntidAxes2=axes('Position',[dx_axes,dy_axes,dw_axes,dh_axes],'Parent',handles.DaqOscillo_Figure);
        handles.AntidAxes1=axes('Position',[dx_axes,dy_axes+dh_axes,dw_axes,dh_axes],'Parent',handles.DaqOscillo_Figure);
        set(handles.AntidAxes1,'XTickLabel','');
        figure(handles.DaqOscillo_Figure);
        % buttons for TTL (normal TTL)
        
          Callbacktxt=sprintf('feval(''%s'',''rb_Antid_MonoPolarMode'');',mfilename);
        handles.rb_Antid_MonoPolarMode = uicontrol('Style','radiobutton',...
            'String','MonoPolar mode','Unit','normalized',...
            'Position',[dx_button dy_button_top-dh_button dw_button*0.7 dh_button],...
            'Callback',Callbacktxt);
        
        handles.text_Antid_PulseWidth = uicontrol('Style','Text',...
            'String','Pulse width [us]','Unit','normalized',...
            'Position',[dx_button dy_button_top-2.3*dh_button dw_button*0.5 dh_button],...
            'Callback',Callbacktxt);
        
        Callbacktxt=sprintf('feval(''%s'',''ed_Antid_PulseWidth'');',mfilename);
        handles.ed_Antid_PulseWidth = uicontrol('Style','edit',...
            'String','200','Unit','normalized',...
            'Position',[dx_button+dw_button*0.7 dy_button_top-2*dh_button dw_button*0.3 dh_button],...
            'Callback',Callbacktxt);
   
        Callbacktxt=sprintf('feval(''%s'',''tg_Antid_Overlay1'');',mfilename);
        handles.tg_Antid_Overlay1 = uicontrol('Style','togglebutton',...
            'String','Overlay','Unit','normalized',...
            'Position',[dx_button dy_button_top-3*dh_button dw_button*0.7 dh_button],...
            'Callback',Callbacktxt);
        
        Callbacktxt=sprintf('feval(''%s'',''pb_Antid_Reset1'');',mfilename);
        handles.pb_Antid_Reset1 = uicontrol('Style','pushbutton',...
            'String','Reset','Unit','normalized',...
            'Position',[dx_button+dw_button*0.7 dy_button_top-3*dh_button dw_button*0.3 dh_button],...
            'Callback',Callbacktxt);
        
        % buttons for collision test.
        
        Callbacktxt=sprintf('feval(''%s'',''tg_Antid_Overlay2'');',mfilename);
        handles.tg_Antid_Overlay2 = uicontrol('Style','togglebutton',...
            'String','Overlay Spike Collision','Unit','normalized',...
            'Position',[dx_button dy_button_middle-dh_button dw_button*0.7 dh_button],...
            'Callback',Callbacktxt);
        
        Callbacktxt=sprintf('feval(''%s'',''pb_Antid_Reset2'');',mfilename);
        handles.pb_Antid_Reset2 = uicontrol('Style','pushbutton',...
            'String','Reset','Unit','normalized',...
            'Position',[dx_button+dw_button*0.7 dy_button_middle-dh_button dw_button*0.3 dh_button],...
            'Callback',Callbacktxt);
        
        %              Callbacktxt=sprintf('feval(''%s'',''edit_spikedetect_threshold'');',mfilename);
        handles.text_spikedetect_threshold = uicontrol('Style','Text',...
            'String','Spike threshold [mV]','Unit','normalized',...
            'Position',[dx_button dy_button_middle-2.3*dh_button dw_button*0.7 dh_button],...
            'Callback',Callbacktxt);
        
        Callbacktxt=sprintf('feval(''%s'',''edit_spikedetect_threshold'');',mfilename);
        handles.edit_spikedetect_threshold = uicontrol('Style','edit',...
            'String','-40','Unit','normalized',...
            'Position',[dx_button+dw_button*0.7 dy_button_middle-2*dh_button dw_button*0.3 dh_button],...
            'Callback',Callbacktxt);
        
        handles.line_spikedetect_threshold=plot(NaN,NaN,'k--','Parent',handles.vol_axe);
        
        % save plotted data.
        
        Callbacktxt=sprintf('feval(''%s'',''pb_Antid_Save'');',mfilename);
        handles.pb_Antid_Save = uicontrol('Style','pushbutton',...
            'String','Save','Unit','normalized',...
            'Position',[dx_button dy_button dw_button dh_button],...
            'Callback',Callbacktxt);
        
        
        newhandles={...
            'AntidAxes1',...
            'AntidAxes2',...
            'rb_Antid_MonoPolarMode',...
            'text_Antid_PulseWidth',...
            'ed_Antid_PulseWidth',...
            'tg_Antid_Overlay1',...
            'pb_Antid_Reset1',...
            'tg_Antid_Overlay2',...
            'pb_Antid_Reset2',...
            'text_spikedetect_threshold',...
            'edit_spikedetect_threshold',...
            'line_spikedetect_threshold',...
            'pb_Antid_Save'};
        
        userdata.new_AntidromicPanel_handles=zeros(1,length(newhandles));
        for nn=1:length(newhandles)
            userdata.(newhandles{nn})=handles.(newhandles{nn});
            userdata.new_AntidromicPanel_handles(nn)=handles.(newhandles{nn});
        end
        
        
        set(handles.DaqOscillo_Figure,'Visible','On');
        userdata.last_mode='Antidromic';
        userdata.tab_open=1;
        set(handles.DaqOscillo_Figure,'UserData',userdata);
        
    case 'CurrentFamily'
        % First, switch to short pulse mode before changing gain.
        % otherwise, it is possible that we inject long current into a
        % cell.
        setparam(handles.tg,handles.oscil.OscilloAntidromic_SelectionConstant_id,4);
        setparam(handles.tg,handles.oscil.TTL_AO1gain_id,1);
        % make TTL output 7V.
        handles.oscil.last_TTLAO1gain=getparam(handles.tg,handles.oscil.TTL_AO1gain_id);
        fprintf('AO1 =%f[V]\n',getparam(handles.tg,handles.oscil.TTL_AO1gain_id));
        
        
        
        
        set(handles_not_used_in_Antidromic_mode,'Enable','Off');
        
         set(handles.DaqOscillo_Figure,'Visible','Off');
         if (userdata.tab_open)
            % clean up the remaining panels.
             ch=get(handles.DaqOscillo_Figure,'Children');
            delete_handles=setdiff(ch,handles.oscil.oscil_handles);
            delete(delete_handles);

         else
             handles.oscil.AntidromicMode_pos=handles.oscil.OscilMode_pos+...
                 [0 -y_shift_pixel 0 y_shift_pixel];
             set(handles.DaqOscillo_Figure,'Position',handles.oscil.AntidromicMode_pos);
             %             ch=get(handles.DaqOscillo_Figure,'Children');
             
             for ii=1:length(handles.oscil.oscil_handles)
                 pos=get(handles.oscil.oscil_handles(ii),'Position');
                 set(handles.oscil.oscil_handles(ii),'Position',pos+[0 y_shift_pixel 0 0]);
             end
         end

        handles.CurrentFamilyAxes=axes('Position',[dx_axes,dy_axes,dw_axes,2*dh_axes],'Parent',handles.DaqOscillo_Figure);
        
        figure(handles.DaqOscillo_Figure);
        % buttons for TTL (normal TTL)
          handles.text_pulsefamily = uicontrol('Style','Text',...
            'String',{'pre             injection           post','duration [ms]'},'Unit','normalized',...
            'Position',[dx_button dy_button_top-1.4*dh_button dw_button dh_button],...
            'Callback','');
        
        Callbacktxt=sprintf('feval(''%s'',''update_CurrentFamilyParameters'');',mfilename);
        handles.edit_CF_preT = uicontrol('Style','edit',...
            'String','1000','Unit','normalized',...
            'Position',[dx_button dy_button_top-2*dh_button dw_button*0.3 dh_button],...
            'Callback',Callbacktxt);
          Callbacktxt=sprintf('feval(''%s'',''update_CurrentFamilyParameters'');',mfilename);
        handles.edit_CF_durT = uicontrol('Style','edit',...
            'String','1000','Unit','normalized',...
            'Position',[dx_button+dw_button*0.33 dy_button_top-2*dh_button dw_button*0.3 dh_button],...
            'Callback',Callbacktxt);
          Callbacktxt=sprintf('feval(''%s'',''update_CurrentFamilyParameters'');',mfilename);
        handles.edit_CF_postT = uicontrol('Style','edit',...
            'String','2000','Unit','normalized',...
            'Position',[dx_button+dw_button*0.66 dy_button_top-2*dh_button dw_button*0.3 dh_button],...
            'Callback',Callbacktxt);
        
            Callbacktxt=sprintf('feval(''%s'',''tg_Antid_Overlay1'');',mfilename);
        handles.text_pulsefamily = uicontrol('Style','Text',...
            'String',{'pre             injection           post','duration [ms]'},'Unit','normalized',...
            'Position',[dx_button dy_button_top-dh_button dw_button dh_button],...
            'Callback',Callbacktxt);
        
        % for pulse amplitudes.
                 handles.text_pulseamp = uicontrol('Style','Text',...
            'String',{'LOW             interval           HIGH','[pA]'},'Unit','normalized',...
            'Position',[dx_button dy_button_top-3.3*dh_button dw_button dh_button],...
            'Callback','');
        
        Callbacktxt=sprintf('feval(''%s'',''update_CurrentFamilyParameters'');',mfilename);
        handles.edit_CF_LowAmp = uicontrol('Style','edit',...
            'String','-600','Unit','normalized',...
            'Position',[dx_button dy_button_top-4*dh_button dw_button*0.3 dh_button],...
            'Callback',Callbacktxt);
          Callbacktxt=sprintf('feval(''%s'',''update_CurrentFamilyParameters'');',mfilename);
        handles.edit_CF_IntervalAmp = uicontrol('Style','edit',...
            'String','600','Unit','normalized',...
            'Position',[dx_button+dw_button*0.33 dy_button_top-4*dh_button dw_button*0.3 dh_button],...
            'Callback',Callbacktxt);
          Callbacktxt=sprintf('feval(''%s'',''update_CurrentFamilyParameters'');',mfilename);
        handles.edit_CF_HighAmp = uicontrol('Style','edit',...
            'String','600','Unit','normalized',...
            'Position',[dx_button+dw_button*0.66 dy_button_top-4*dh_button dw_button*0.3 dh_button],...
            'Callback',Callbacktxt);
        
        
     Callbacktxt=sprintf('feval(''%s'',''pb_Start_CurrentFamily'');',mfilename);
        handles.pb_Start_CurrentFamily = uicontrol('Style','pushbutton',...
            'String','START','Unit','normalized',...
            'Position',[dx_button dy_button_top-5*dh_button dw_button dh_button],...
            'Callback',Callbacktxt);
         
        Callbacktxt=sprintf('feval(''%s'',''pb_Clear_CurrentFamilyAxis'');',mfilename);
        handles.pb_Start_CurrentFamily = uicontrol('Style','pushbutton',...
            'String','Clear','Unit','normalized',...
            'Position',[dx_button dy_button_top-6*dh_button dw_button dh_button],...
            'Callback',Callbacktxt);
        
         % save plotted data.
        
        Callbacktxt=sprintf('feval(''%s'',''pb_CurrentFamily_Save'');',mfilename);
        handles.pb_CurrentFamily_Save = uicontrol('Style','pushbutton',...
            'String','Save','Unit','normalized',...
            'Position',[dx_button dy_button dw_button dh_button],...
            'Callback',Callbacktxt);
        
        
        newhandles={...
            'CurrentFamilyAxes',...
            'text_pulsefamily',...
            'edit_CF_preT',...
            'edit_CF_durT',...
            'edit_CF_postT',...
            'pb_Start_CurrentFamily',...
            'edit_CF_LowAmp',...
            'edit_CF_IntervalAmp',...
            'edit_CF_HighAmp',...
            'pb_CurrentFamily_Save'};
        
        userdata.new_AntidromicPanel_handles=zeros(1,length(newhandles));
        for nn=1:length(newhandles)
            userdata.(newhandles{nn})=handles.(newhandles{nn});
            userdata.new_AntidromicPanel_handles(nn)=handles.(newhandles{nn});
        end
        
        
        set(handles.DaqOscillo_Figure,'Visible','On');
        userdata.last_mode='CurrentFamily';
        userdata.tab_open=1;
        set(handles.DaqOscillo_Figure,'UserData',userdata);
        
         restore_currentfamily_values(hObject);
         
    case 'Oscillo'
        pos=get(handles.DaqOscillo_Figure,'Position');
        pos=[pos(1) pos(2) handles.oscil.OscilMode_pos(3) handles.oscil.OscilMode_pos(4)];
        set(handles.DaqOscillo_Figure,'Position',handles.oscil.OscilMode_pos);
        ch=get(handles.DaqOscillo_Figure,'Children');
        
        % return the TTL output gain previous value.
        %         if handles.oscil.last_TTLAO1gain > 1
        %             fprintf('Something is wrong. Set the output -350pA.')
        handles.oscil.last_TTLAO1gain=-0.35;
        setparam(handles.tg,handles.oscil.TTL_AO1gain_id,handles.oscil.last_TTLAO1gain);
        %         end
        
        
        fprintf('AO1 =%f[V]\n',getparam(handles.tg,handles.oscil.TTL_AO1gain_id));
        
        
        set(handles_not_used_in_Antidromic_mode,'Enable','On');
        if (userdata.tab_open)
            set(handles.DaqOscillo_Figure,'Visible','Off');
            for ii=1:length(handles.oscil.oscil_handles)
                pos=get(handles.oscil.oscil_handles(ii),'Position');
                set(handles.oscil.oscil_handles(ii),'Position',pos+[0 -y_shift_pixel 0 0]);
            end
            
            delete_handles=setdiff(ch,handles.oscil.oscil_handles);
            delete(delete_handles);
            %             delete(userdata.new_AntidromicPanel_handles);
            set(handles.DaqOscillo_Figure,'Visible','On');
        end
        userdata.last_mode='Oscillo';
        userdata.tab_open=0;
        
        set(handles.DaqOscillo_Figure,'UserData',userdata);
        setparam(handles.tg,handles.oscil.OscilloAntidromic_SelectionConstant_id,1);
        
    otherwise
        error('Unknown option %s',eventdata);
end




function handles=tg_Antid_Overlay1()
fprintf('Start overlaying antidromic traces\n')
val=get(gcbo,'Value');
if val
    handles=guidata(gcbo);
    userdata=get(handles.DaqOscillo_Figure,'UserData');
    % get(handles.AntidAxes1)
    set(userdata.tg_Antid_Overlay2,'Value',0);
    setparam(handles.tg,handles.oscil.OscilloAntidromic_SelectionConstant_id,2);
    set(userdata.line_spikedetect_threshold,'XData',NaN,'YData',NaN);
    zoom on;
else
    zoom off;
end
function handles=pb_Antid_Reset1()
fprintf('Reset.\n')
handles=guidata(gcbo);
userdata=get(handles.DaqOscillo_Figure,'UserData');
axes(userdata.AntidAxes1);cla;

function handles=tg_Antid_Overlay2()
fprintf('Start overlaying spike collision traces.\n')
val=get(gcbo,'Value');

handles=guidata(gcbo);
userdata=get(handles.DaqOscillo_Figure,'UserData');
if val
    % get(handles.AntidAxes1)
    set(userdata.tg_Antid_Overlay1,'Value',0);
    
    vthresh=str2num(get(userdata.edit_spikedetect_threshold,'String'));
    xrange=get(handles.vol_axe,'XLim');
    set(userdata.line_spikedetect_threshold,'XData',xrange,'YData',[1 1]*vthresh);
    setparam(handles.tg,handles.oscil.OscilloAntidromic_SelectionConstant_id,3);
     zoom on;
else
    setparam(handles.tg,handles.oscil.OscilloAntidromic_SelectionConstant_id,2);
    set(userdata.line_spikedetect_threshold,'XData',NaN,'YData',NaN);
    zoom off;
end

function handles=pb_Antid_Reset2()
fprintf('Reset spike collision traces\n')
handles=guidata(gcbo);
userdata=get(handles.DaqOscillo_Figure,'UserData');
axes(userdata.AntidAxes2);cla;



function handles=pb_Antid_Save()
fprintf('Save\n')
handles=guidata(gcbo)
userdata=get(handles.DaqOscillo_Figure,'UserData')

ch1=get(userdata.AntidAxes1,'Children');
data.anti.x=cell2mat([get(ch1,'XData')]);
data.anti.y=cell2mat([get(ch1,'YData')]);

ch2=get(userdata.AntidAxes2,'Children');
data.collision.x=cell2mat([get(ch2,'XData')]);
data.collision.y=cell2mat([get(ch2,'YData')]);

pathname=RealSong_control_010('return_latest_savedir',handles.ParentGUI)


try
    [userdata.savename, userdata.pathname] = uiputfile( ...
        fullfile(pathname,userdata.savename),...
        'Save antidromic data as (*.mat)');
catch
    [userdata.savename, userdata.pathname] = uiputfile( ...
        fullfile(pathname,['antidromic_data.mat']),...
        'Save antidromic data as (*.mat)');
end

if isequal(userdata.savename,0)
    disp('User Pressed Cancel');
else
    save(fullfile(userdata.pathname,[userdata.savename]),...
        'data');
    set(handles.DaqOscillo_Figure,'UserData',userdata);
end


function handles=edit_spikedetect_threshold()

handles=guidata(gcbo);
userdata=get(handles.DaqOscillo_Figure,'UserData');
vthresh=str2double(get(gcbo,'String'));
setparam(handles.tg,handles.oscil.spikethresh_id,...
    vthresh/handles.oscil.Vmfactor);
fprintf('Spike detection threshold is set to %4.2gmV\n',vthresh);
  xrange=get(handles.vol_axe,'XLim');
set(userdata.line_spikedetect_threshold,'XData',xrange,'YData',[1 1]*vthresh);
    
    
% factor 10 comes from 10Vm output of AxoClamp.





% --- Executes when selected object is changed in mode_select_panel.
function handles=mode_select_panel_SelectionChangeFcn(hObject, eventdata, handles)
% hObject    handle to the selected object in mode_select_panel
% eventdata  structure with the following fields (see UIBUTTONGROUP)
%	EventName: string 'SelectionChanged' (read only)
%	OldValue: handle of the previously selected object or empty if none was selected
%	NewValue: handle of the currently selected object
% handles    structure with handles and user data (see GUIDATA)

-handles.tg;

running_state=get(handles.pb_run,'Value');
set(handles.pb_run,'Value',0);
pb_run_Callback(handles.pb_run, eventdata, handles);
mode=get(get(handles.mode_select_panel,'SelectedObject'),'Tag');



switch lower(mode)
    case 'tg_oscillo'
        [handles,userdata]=setup_new_panels(hObject,'Oscillo',handles);
    case 'tg_antidromic_mode'
        [handles,userdata]=setup_new_panels(hObject,'Antidromic',handles);
    case 'tg_currentfamily'
        [handles,userdata]=setup_new_panels(hObject,'CurrentFamily',handles);
        
    otherwise
end
% set(handles.pb_run,'Value',running_state);
% pb_run_Callback(handles.pb_run, eventdata, handles);
    
    
    
function restore_currentfamily_values(hObject)
    
handles=guidata(gcbo);
userdata=get(handles.DaqOscillo_Figure,'UserData');
disp('Restoring previous current injection parameters')
if isfield(userdata,'cf')
    if isfield(userdata.cf,'preT') % there is a previous data.
         set(userdata.edit_CF_preT,'String',num2str(userdata.cf.preT));
         set(userdata.edit_CF_durT,'String',num2str(userdata.cf.durT));
         set(userdata.edit_CF_postT,'String',num2str(userdata.cf.postT));
         
         set(userdata.edit_CF_LowAmp,'String',num2str(userdata.cf.LowAmp));
         set(userdata.edit_CF_IntervalAmp,'String',num2str(userdata.cf.IntervalAmp));
         set(userdata.edit_CF_HighAmp,'String',num2str(userdata.cf.HighAmp));
         
    end
else
    disp('do nothing')
    % do nothing.
end
 if isfield(userdata,'cfs')
     disp('clean up the history of previous injection currents')
             userdata=rmfield(userdata,'cfs');
 end
         
set(handles.DaqOscillo_Figure,'UserData',userdata);

function userdata=update_CurrentFamilyParameters()

handles=guidata(gcbo);
userdata=get(handles.DaqOscillo_Figure,'UserData');

userdata.cf.preT     =str2num(get(userdata.edit_CF_preT,'String'));
userdata.cf.durT     =str2num(get(userdata.edit_CF_durT,'String'));
userdata.cf.postT    =str2num(get(userdata.edit_CF_postT,'String'));
userdata.cf.LowAmp   =str2num(get(userdata.edit_CF_LowAmp,'String'));
userdata.cf.IntervalAmp=str2num(get(userdata.edit_CF_IntervalAmp,'String'));
userdata.cf.HighAmp    =str2num(get(userdata.edit_CF_HighAmp,'String'));

fprintf('pre,during,post duration=[%4.4g,%4.4g,%4.4g]ms\n',...
    userdata.cf.preT,...
    userdata.cf.durT,...
    userdata.cf.postT);
fprintf('Low,interval,High current=[%3.3g,%3.3g,%3.3g]pA\n',...
    userdata.cf.LowAmp,...
    userdata.cf.IntervalAmp,...
    userdata.cf.HighAmp);

set(handles.DaqOscillo_Figure,'UserData',userdata);

function pb_Start_CurrentFamily()
    
block_path='OscilloAntidromic/triggered_pulse_family/';
    
    
handles=guidata(gcbo);
% userdata=get(handles.DaqOscillo_Figure,'UserData');
userdata=update_CurrentFamilyParameters();

if isfield(userdata,'cfs')
%     userdata = setfield(userdata.cfs,{length(userdata.cfs)+1},userdata.cf);
    n=length(userdata.cfs);
    userdata.cfs(n+1).cf=userdata.cf;
else
    userdata.cfs(1).cf=userdata.cf;
end
% userdata.cfs

amp=[userdata.cf.LowAmp:userdata.cf.IntervalAmp:userdata.cf.HighAmp];

% make sure output is not scaled.
 setparam(handles.tg,handles.oscil.TTL_AO1gain_id,1);
%update parameters in xPC.

delay_n=ceil(userdata.cf.preT*handles.oscil.CorrectSampRate/1000);
id=getparamid(handles.tg,[block_path,'delay'],'Value');
setparam(handles.tg,id,delay_n);


id=getparamid(handles.tg,[block_path,'lowamp'],'Value');
setparam(handles.tg,id,userdata.cf.LowAmp);
id=getparamid(handles.tg,[block_path,'interval'],'Value');
setparam(handles.tg,id,userdata.cf.IntervalAmp);
id=getparamid(handles.tg,[block_path,'highamp'],'Value');
setparam(handles.tg,id,userdata.cf.HighAmp);

dur_n=ceil(userdata.cf.durT*handles.oscil.CorrectSampRate/1000);
id=getparamid(handles.tg,[block_path,'pulse_dur'],'Value');
setparam(handles.tg,id,dur_n);

inter_pulse_interval_n=[userdata.cf.preT+userdata.cf.durT+userdata.cf.postT];
inter_pulse_interval_n= ceil(inter_pulse_interval_n/1000*handles.oscil.CorrectSampRate);
id=getparamid(handles.tg,[block_path,'IPI'],'Value');
setparam(handles.tg,id,inter_pulse_interval_n);

burst_dur_n=inter_pulse_interval_n*length(amp);
id=getparamid(handles.tg,[block_path,'burst_dur'],'Value');
setparam(handles.tg,id,burst_dur_n);

id=getparamid(handles.tg,[block_path,'ref'],'Value');
setparam(handles.tg,id,burst_dur_n);

set(handles.DaqOscillo_Figure,'UserData',userdata);

id=getparamid(handles.tg,'OscilloAntidromic/TriggerButton/TrigVal','Value');
val=getparam(handles.tg,id);
setparam(handles.tg,id,-val);

function pb_Clear_CurrentFamilyAxis()
 
handles=guidata(gcbo);
userdata=get(handles.DaqOscillo_Figure,'UserData');
axes(userdata.CurrentFamilyAxes);cla;



function handles=pb_CurrentFamily_Save()
fprintf('Save\n')
handles=guidata(gcbo);
userdata=get(handles.DaqOscillo_Figure,'UserData');
ch1=get(userdata.CurrentFamilyAxes,'Children');
data.cf.x=cell2mat([get(ch1,'XData')]);
data.cf.y=cell2mat([get(ch1,'YData')]);
data.cfs=userdata.cfs;

pathname=RealSong_control_010('return_latest_savedir',handles.ParentGUI)


try
    [userdata.savename, userdata.pathname] = uiputfile( ...
        fullfile(pathname,userdata.savename),...
        'Save current family data as (*.mat)');
catch
    [userdata.savename, userdata.pathname] = uiputfile( ...
        fullfile(pathname,['currentfamily_data.mat']),...
        'Save antidromic data as (*.mat)');
end


if isequal(userdata.savename,0)
    disp('User Pressed Cancel');
else
    save(fullfile(userdata.pathname,[userdata.savename]),...
        'data');
    set(handles.DaqOscillo_Figure,'UserData',userdata);
end

function rb_Antid_MonoPolarMode()
update_antidromic_pulse_parameters(gcbo);

function ed_Antid_PulseWidth()
update_antidromic_pulse_parameters(gcbo);

function update_antidromic_pulse_parameters(hObject)
handles=guidata(gcbo);
userdata=get(handles.DaqOscillo_Figure,'UserData');

MonoPolarMode=get(userdata.rb_Antid_MonoPolarMode,'Value');

PulseWidth=str2num(get(userdata.ed_Antid_PulseWidth,'String'));


delay_id=getparamid(handles.tg,'OscilloAntidromic/triggered_dynamic_Pulse/delay','Value');
delay_n=getparam(handles.tg,delay_id);

pulsedur_id=getparamid(handles.tg,'OscilloAntidromic/triggered_dynamic_Pulse/pulse_dur','Value');
pulsedur_n=getparam(handles.tg,pulsedur_id);

IPI_id=getparamid(handles.tg,'OscilloAntidromic/triggered_dynamic_Pulse/IPI','Value');
getparam(handles.tg,IPI_id);

burstdur_id=getparamid(handles.tg,'OscilloAntidromic/triggered_dynamic_Pulse/burst_dur','Value');
getparam(handles.tg,burstdur_id);

ref_id=getparamid(handles.tg,'OscilloAntidromic/triggered_dynamic_Pulse/ref','Value');
getparam(handles.tg,ref_id);

pulsedur_n=ceil(PulseWidth*1.e-6*handles.oscil.CorrectSampRate);
IPI_n= pulsedur_n+1;
if MonoPolarMode
    fprintf('Single pulse:');
   burstdur_n=IPI_n; 
else
     fprintf('Double pulse:');
   burstdur_n=IPI_n*2;
end

ref_n=ceil(0.5*handles.oscil.CorrectSampRate);

% 
setparam(handles.tg,pulsedur_id,pulsedur_n);
setparam(handles.tg,IPI_id,IPI_n);
setparam(handles.tg,burstdur_id,burstdur_n);
% setparam(handles.tg,ref_id,ref_n);
% 
fprintf('pulse =%3.4g[us](%dPts), Inter-pulse = %3.4g[us](%dPts),total=%3.4g[us](%dPts)\n',...
    PulseWidth,pulsedur_n,...
    IPI_n/handles.oscil.CorrectSampRate*1.e6,IPI_n,...
    burstdur_n/handles.oscil.CorrectSampRate*1.e6,burstdur_n);
%  

