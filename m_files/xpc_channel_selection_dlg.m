function [channel_names,selected_val,bias,gain,value]=xpc_channel_selection_dlg(opt,varargin)
%generate channel selection dialog panel.
% [channel_names,selected_val,bias,gain,value]=xpc_channel_selection_dlg();
% by KH 20120829

if nargin==0
    opt='selection'
end

switch opt
    case 'selection'
        
        S=strsplit(which(mfilename),'\');
        loadname=['last_',mfilename];
        loadname=fullfile(S{1:end-1},loadname);
        
        column_names={'channels','PlotBias','PlotGain'};
        
        [channel_names,selected_val,bias,gain]=feval(mfilename,'load_settings');
        
        
        
        fig_props = { ...
            'name'                   'Channel selection' ...
            'color'                  get(0,'DefaultUicontrolBackgroundColor') ...
            'resize'                 'off' ...
            'numbertitle'            'off' ...
            'menubar'                'none' ...
            'windowstyle'            'modal' ...
            'visible'                'off' ...
            'createfcn'              ''    ...
            'closerequestfcn'        'delete(gcbf)' ...
            };
        
        
        fig = figure(fig_props{:});
        
        
        top=1;
        ds=0.01;
        dx=0.05;
        dy=0;
        dh=1/((length(channel_names)+1)*1.05);
        dw=(1-2*dx-2*ds)/3;
        
        up=uipanel('Title','Recording Channel Selection','FontSize',12,...
            'Position',[0 dh 1 1-dh]);
        
        
        
        
        for kk=1:length(column_names)
            uicontrol('Style','Text','Unit','Normalized',...
                'pos',[dx+(kk-1)*dw top-dh,dw,dh],...
                'Parent',up,...
                'String',sprintf('%s',column_names{kk}),...
                'FontSize',18,...
                'HandleVisibility','off');
        end
        
        top=1-dh;
        for jj=1:length(channel_names)
            % Create three radio buttons in the button group.
            ui.ui_RB(jj) = uicontrol('Style','Radio','Unit','Normalized',...
                'pos',[dx top-dh*jj,dw,dh],...
                'Parent',up,...
                'String',sprintf('%s',channel_names{jj}),...
                'Value',selected_val(jj),...
                'FontSize',18,...
                'Callback',{@Change_enable,fig},...
                'HandleVisibility','off');
            if ~selected_val(jj),        set(ui.ui_RB(jj),'ForegroundColor',[0.7 .7 .7]);    end
            
            ui.ui_EB(jj) = uicontrol('Style','edit','Unit','Normalized',...
                'pos',[dx+dw+ds top-dh*jj,dw,dh],...
                'Parent',up,...
                'FontSize',12,...
                'String',bias(jj),'HandleVisibility','off');
            
            if ~selected_val(jj),        set(ui.ui_EB(jj),'Enable','Off');    end
            
            ui.ui_GN(jj) = uicontrol('Style','edit','Unit','Normalized',...
                'pos',[dx+2*dw+2*ds top-dh*jj,dw,dh],...
                'Parent',up,...
                'FontSize',12,...
                'String',gain(jj),'HandleVisibility','off');
            if ~selected_val(jj),        set(ui.ui_GN(jj),'Enable','Off');    end
        end
        
        set(fig,'UserData',ui);
        
        %%
        OKbtn=uicontrol('Style','pushbutton','Unit','Normalized','pos',[0.1 0 0.4 dh],...
            'String','OK','parent',fig,'Callback',{@do_OK,ui});
        
        uicontrol('Style','pushbutton','Unit','Normalized','pos',[0.5 0 0.4 dh],...
            'String','Cancel','parent',fig,'Callback',{@do_Cancel,ui});
        
        movegui(fig);
        set(fig, 'visible','on'); drawnow;
        
        % Focus on OK
        uicontrol(OKbtn);
        
        try
            % Give default focus to the listbox *after* the figure is made visible
            %     uicontrol(ui_buttonGp(1));
            uiwait(fig);
        catch
            if ishghandle(fig)
                delete(fig)
            end
        end
        
        if isappdata(0,'ListDialogAppData__')
            ad = getappdata(0,'ListDialogAppData__');
            selected_val = ad.selected_val;
            bias = ad.bias;
            gain = ad.gain;
            value = ad.value;
            rmappdata(0,'ListDialogAppData__')
        else
            % figure was deleted
            selection = [];
            bias = [];
            gain = [];
            value = 0;
        end
        
        % save data
        if (value)
            fprintf('Saving selected data as default in %s\n',loadname);
            feval(mfilename,'save_settings',channel_names,selected_val,bias,gain);       
%             save(loadname,'channel_names','selected_val','bias','gain','column_names');
        end
        
    case 'load_settings'
        if nargin==2
            loadname = varargin{1};
        else
            S=strsplit(which(mfilename),'\');
            loadname=['last_',mfilename];
            loadname=fullfile(S{1:end-1},loadname);
        end
        
        try
            load(loadname);
            fprintf('Loading previous default data in %s\n',loadname);
        catch
            
            channel_names={'MIC','E1','Im','Speaker','TTL'};
            selected_val=[1,1,0,1,0];
            bias        =[0 0 -90 0 0];
            gain        =[50 100 100 50 50];
        end
        value=1;
        
        
    case 'save_settings'
        channel_names    =varargin{1};
        selected_val     =varargin{2};
        bias             =varargin{3};
        gain             =varargin{4};
        
        S=strsplit(which(mfilename),'\');
        savename=['last_',mfilename];
        savename=fullfile(S{1:end-1},savename);
        
        save(savename,'channel_names','selected_val','bias','gain');
        
        value=1;
        
      
        
    otherwise
        
end
%%
function  Change_enable(change_btn,event,fig)

val=get(gcbo,'Value');
ui=get(fig,'UserData');

ind=find(ui.ui_RB==gcbo);

if (val)
    set(ui.ui_RB(ind),'ForegroundColor',[0 0 0]);
    set(ui.ui_EB(ind),'Enable','On');
    set(ui.ui_GN(ind),'Enable','On');
else
    set(ui.ui_RB(ind),'ForegroundColor',[0.7 .7 .7]);
    set(ui.ui_EB(ind),'Enable','Off');
    set(ui.ui_GN(ind),'Enable','Off');
end




%%
function  do_OK(ok_btn,event,ui)

if (~isappdata(0, 'ListDialogAppData__'))
    ad.value = 1;
    
    for ii=1:length(ui.ui_RB)
        ad.selected_val(ii)=  get(ui.ui_RB(ii),'Value');
        ad.bias(ii)=  str2double(get(ui.ui_EB(ii),'String'));
        ad.gain(ii)=  str2double(get(ui.ui_GN(ii),'String'));
    end
    
    setappdata(0,'ListDialogAppData__',ad);
    delete(gcbf);
end



%%
function  do_Cancel(cancel_btn,event,ui)

ad.value = 0;
ad.selected_val = [];
ad.bias = [];
ad.gain= [];
setappdata(0,'ListDialogAppData__',ad)
delete(gcbf);




