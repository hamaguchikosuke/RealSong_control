function read_SAPexported_notedata()
% read SAP exported MATLAB format data of syllable database,
% check the syllable by eyes and ears, 
% by KH 20090729
% 
%% 
global data gph pm
% addpath('Sub_SyllableAnalysis_Mcodes');

pm.names={'recnum',...              % 1
    'serial_number',...             % 2
    'bird_ID',...                   % 3
    'start_on',...                  % 4
    'duration',...                  % 5
    'mean_pitch',...                % 6
    'mean_FM',...                   % 7
    'mean_entropy',...              % 8
    'mean_goodness_of_pitch',...    % 9
    'mean_mean_frequency',...       % 10
    'mean_am2',...                  % 11
    'mean_amplitude',...            % 12
    'var_pitch',...                 % 13
    'var_FM',...                    % 14
    'var_entropy',...               % 15
    'var_goodness_of_pitch',...     % 16
    'var_mean_frequency',...        % 17
    'var_am',...                    % 18
    'month',...                     % 19
    'day',...                       % 20
    'hour',...                      % 21
    'minute',...                    % 22
    'second',...                    % 23
    'cluster'};                     % 24

try
    sql_dir='C:\mysql\data\mysql\';
    d=dir(fullfile(sql_dir,'*.myd'));
    tablenames = {d.name};
    tablenames=strrep(tablenames,'.MYD','');
    tablenames=strrep(tablenames,'.myd','');
    
    [s,v] = listdlg('PromptString','Select a table to read:',...
        'SelectionMode','single',...
        'ListString',tablenames);
    if (v)
        pathname=sql_dir;
        SAPdatafile=tablenames{s};
    else
        disp('No table selected!');
        return;
    end
    
    fprintf('Loading table from %s\n',SAPdatafile);
    conn = database('mysql', '', '');
    conn_txt=sprintf('select * from %s where cluster<9',SAPdatafile);
    curs = exec(conn, conn_txt);
    curs = fetch(curs);
    data=curs.data;
    colname=columnnames(curs);
    close(curs);
    close(conn);
catch
    [SAPdatafile,pathname]=uigetfile( ...
        {'*.*',  'All Files (*.*)'}, ...
        'Pick a SAP exported data file');
    
    cd(pathname);
    data= load(fullfile(pathname,SAPdatafile));
    data = data.LocalDouble;
end
%%
time_stamp = datenum([repmat(2009,size(data,2),1) data(19,:)' data(20,:)' data(21,:)' data(22,:)' data(23,:)']);

pm.xname = 'duration';
pm.yname = 'mean_entropy';
% zname = 'mean_pitch';
figure(1);clf;
gph.ax(1)=axes('Position',[.25 .6 .5 .3]);
pm.xind = strmatch(pm.xname,pm.names);
pm.yind = strmatch(pm.yname,pm.names);

cluster_ID = unique(data(end,:));
get(gcf,'DefaultAxesColorOrder');
% pm.CS     = {'r.','b.','g.','y.','c.','m.'};
pm.CS    = [...
         0         0    1.000;...
         0     1.000        0;...
    1.0000         0        0;...
         0     1.000    1.000;...
    1.0000         0    1.000;...
    1.0000     1.000       	0;...
    0.7500    0.7500   0.7500;...
    0.5       0.5           0;...
    0           0           0,...
    0           0.25        0.25,...
    .25         .25         0];

for ii=1:length(cluster_ID)
    pm.plotind = find(data(end,:)==cluster_ID(ii));
    if (cluster_ID(ii)==0)
        CSnow=[0 0 0];
    else
        CSnow = pm.CS(ii,:);
    end
    h=plot(data(pm.xind,pm.plotind),data(pm.yind,pm.plotind),'ko','MarkerSize',2);hold on;
    set(h,'MarkerFaceColor',CSnow,'MarkerEdgeColor','none');
end

xlabel(strrep(pm.xname,'_','\_'));ylabel(strrep(pm.yname,'_','\_'));


 
uicontrol('Style', 'pushbutton','String', 'show syllable',...
    'Unit','Normalized','Position', [.25 .9 .08 .04],'Callback', 'readSAP_sub_routines(''show_syllable'');');

uicontrol('Style', 'pushbutton','String', 'redraw',...
    'Unit','Normalized','Position', [.35 .9 .08 .04],'Callback', 'readSAP_sub_routines(''redraw'');');

uicontrol('Style', 'pushbutton','String', 'play song',...
    'Unit','Normalized','Position', [.1 .4 .08 .04],'Callback', 'readSAP_sub_routines(''play_wholesong'');');

uicontrol('Style', 'pushbutton','String', 'play syllable',...
    'Unit','Normalized','Position', [.2 .4 .08 .04],'Callback', 'readSAP_sub_routines(''play_syllable'');');

uicontrol('Style', 'pushbutton','String', 'show classification',...
    'Unit','Normalized','Position', [.3 .4 .08 .04],'Callback', 'readSAP_sub_routines(''show_classification'');');

% cluster selection button
gph.ui_clusterselect = uipanel('Title','clusters','Position',[.01 .6 .15 .3]);
dx = 1; dy=1/9;
for ii=[1:9]
evaltxt = sprintf('gph.ui_cluster%d = uicontrol(''Style'',''Radio'',''Value'',1,''String'',[''cluster'' num2str(%d) '':(%d)''],''unit'',''normalized'',''pos'',[%g,%g,%g,dy],''parent'',gph.ui_clusterselect,''HandleVisibility'',''off'',''CallBack'',''readSAP_sub_routines(''''%s'''')'');',...
    mod(ii,9),mod(ii,9),length(find(data(end,:)==mod(ii,9))),0,1-(ii)*dy,.8,'update_datatmp');
eval(evaltxt);
end
gph.ax(3)=axes('parent',gph.ui_clusterselect,'unit','normalized','Position',[.85 dy/2 .1 1-dy]);
for ii=1:9
           plot(0,-ii,'ko','MarkerFaceColor',pm.CS(ii,:));hold on;
end
axis off; axis tight;
readSAP_sub_routines('update_datatmp');

% x axis selection
gph.ui_xbuttonG = uibuttongroup('visible','off','Position',[.25 .5 .7 .05]);
dx = 1/7; dy=.5;
for ii=1:13
evaltxt = sprintf('gph.ui_xbutton%d = uicontrol(''Style'',''Radio'',''String'',pm.names{%d},''unit'',''normalized'',''pos'',[%g,%g,%g,.5],''parent'',gph.ui_xbuttonG,''HandleVisibility'',''off'');',...
    ii,ii+4,(mod(ii-1,7))*dx,1-ceil(ii/7)*dy,dx);
eval(evaltxt);
end
% Initialize some button group properties. 
set(gph.ui_xbuttonG,'SelectionChangeFcn','readSAP_sub_routines(''chk_xaxis_button'')');
set(gph.ui_xbuttonG,'SelectedObject',gph.ui_xbutton1);  % No selection
set(gph.ui_xbuttonG,'Visible','on');

% y axis selection
gph.ui_ybuttonG = uibuttongroup('visible','off','Position',[0.76 .6 .19 .3]);
dx = 1/2; dy=1/7;
for ii=1:13
evaltxt = sprintf('gph.ui_ybutton%d = uicontrol(''Style'',''Radio'',''String'',pm.names{%d},''unit'',''normalized'',''pos'',[%g,%g,%g,dy],''parent'',gph.ui_ybuttonG,''HandleVisibility'',''off'');',...
    ii,ii+4,floor(ii/7)*dx,1-(mod(ii-1,7)+1)*dy,dx);
eval(evaltxt);
end
% Initialize some button group properties. 
set(gph.ui_ybuttonG,'SelectionChangeFcn','readSAP_sub_routines(''chk_yaxis_button'')');
set(gph.ui_ybuttonG,'SelectedObject',gph.ui_ybutton4);  % No selection
set(gph.ui_ybuttonG,'Visible','on');

gph.ax(2)=axes('Position',[.1 .1 .7 .3]);
