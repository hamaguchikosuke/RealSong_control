function ClassifySAP_sub_routines_02(opt,varargin)
% global data datatmp gph pm
global sap

switch lower(opt)
    case 'init_variables_for_figure'
        
        sap.pm.cluster_types={'database','classified'};
           sap.pm.feature_names={...
            'amplitude',...
            'meanfreq',...
            'pitch',...
            'entropy',...
            'pgood'}
        
        sap.pm.xname = 'duration';
        sap.pm.yname = 'mean_entropy';
        
        sap.pm.CS    = [...
            0.5        0.5       0.5;...    % cluster0: unidentified sounds
            0         0    1.000;...       % introductory notes
            0     1.000        0;...       % 1st note
            1.0000         0        0;...       % 2nd note
            0     1.000    1.000;...
            1.0000         0    1.000;...
            1.0000     1.000       	0;...
            0.7500    0.7500   0.2500;...
            0.7500    0.2500   0.7500;...,...
            0         0         0];             % identified noise
        
        sap.pm.max_load_N=6000;
        sap.gpm.do_show_teacher=1;
    case 'init_variables'
        
       
        % zname = 'mean_pitch';
        figure(1);clf;
        sap.gph.ax(1)=axes('Position',[.25 .6 .5 .3]);
%         sap.pm.xind = strmatch(sap.pm.xname,sap.pm.names);
%         sap.pm.yind = strmatch(sap.pm.yname,sap.pm.names);
        sap.pm.key_index            =strmatch('recnum',sap.pm.names);
        sap.pm.cluster_index        =strmatch('cluster',sap.pm.names);
        sap.pm.serial_index         =strmatch('serial_number',sap.pm.names);
        sap.pm.start_on_index       =strmatch('start_on',sap.pm.names);
        sap.pm.duration_index       =strmatch('duration',sap.pm.names);
        sap.pm.mean_pitch_index     =strmatch('mean_pitch',sap.pm.names);         % 6
        sap.pm.mean_FM_index        =strmatch('mean_FM',sap.pm.names);         % 6
        sap.pm.mean_entropy_index   =strmatch('mean_entropy',sap.pm.names);         % 6
        sap.pm.mean_gpitch_index    =strmatch('mean_goodness_of_pitch',sap.pm.names);         % 6
        sap.pm.var_entropy_index    =strmatch('var_entropy',sap.pm.names);         % 6
        sap.pm.month_index          =strmatch('month',sap.pm.names);         % 6
        sap.pm.day_index            =strmatch('day',sap.pm.names);         % 6
        sap.pm.hour_index           =strmatch('hour',sap.pm.names);         % 6
        sap.pm.minute_index         =strmatch('minute',sap.pm.names);         % 6
        sap.pm.second_index         =strmatch('second',sap.pm.names);         % 6
      

        sap.pm.timevec_index=[sap.pm.month_index,...
                              sap.pm.day_index,...
                              sap.pm.hour_index,...
                              sap.pm.minute_index,...
                              sap.pm.second_index];
        
        % now, check this cluster already contains 'classified' column.                  
        if isempty(strmatch('classified',sap.pm.names)) % loaded new database never analyzed. 
            % sap.data must have new rows, {'classified','is_teacher'};
            sap.pm.names={sap.pm.names{:},'classified','is_teacher'};
            sap.data=[sap.data;zeros(2,size(sap.data,2))];
        else  % loaded database already analyzed. 
            sap.pm.classified_cluster_index   = strmatch('classified',sap.pm.names);
            % 'is_teacher' column is not uploaded, and is just used within matlab.
            % so we need to assign new row for them.
            sap.pm.names={sap.pm.names{:},'is_teacher'};
            sap.data=[sap.data;zeros(1,size(sap.data,2))];
        end
        
      
        sap.pm.classified_cluster_index     =strmatch('classified',sap.pm.names); 
        sap.pm.is_teacher_index             =strmatch('is_teacher',sap.pm.names); 
        sap.pm.cluster_index_in_data=[sap.pm.cluster_index,sap.pm.classified_cluster_index];
        
        feval(mfilename,'set_teacher_data','from_same_database');
%       sap.teacher_data=sap.data(:,sap.data(sap.pm.cluster_index,:)~=0);
%         sap.teacher_cluster_index=sap.pm.cluster_index;
        
        
        
        sap.pm.mean_feature_index=[sap.pm.duration_index,...
            sap.pm.mean_pitch_index,...
            sap.pm.mean_FM_index,...
            sap.pm.mean_entropy_index,...
            sap.pm.mean_gpitch_index];
        
        sap.pm.classify_dim_index=[sap.pm.mean_feature_index,sap.pm.var_entropy_index];
        
        sap.pm.feature_loadname=[];
        
    case 'set_teacher_data'
        
        %         Here is how we set the teacher data
        %         0) by default, we simply use the already classified data in our database as the teacher.
        %         1) use already classified data by loading another database.
        %         2) use k-means clustering to cluster some data (not
        %         implemented yet).
        d=varargin{1};
        
        switch d
            case 'from_same_database'
                ind=(sap.data(sap.pm.cluster_index,:)~=0);
                sap.data(sap.pm.is_teacher_index,:)=0; % reset
                sap.data(sap.pm.is_teacher_index,ind)=1; % assign as teacher.
                
            case 'from_another_database'
                sql_dir='C:\mysql\data\mysql\';
                d=dir(fullfile(sql_dir,'*.myd'));
                tablenames = {d.name};
                tablenames=strrep(tablenames,'.MYD','');
                tablenames=strrep(tablenames,'.myd','');
                
                [s,v] = listdlg('PromptString','SELECT a table for teacher data. Already clustered data will be used.:',...
                    'SelectionMode','single',...
                    'ListString',tablenames,...
                    'ListSize',[250 500],...
                    'Name',['Load Database in ' sql_dir]);
                if (v)
                    pathname=sql_dir;
                    sap.Teachertablename=tablenames{s};
                else
                    disp('No table selected!');
                    return;
                end
                
                logintimeout(5);
                fprintf('Loading table from %s\n',sap.Teachertablename);
                conn = database('mysql', '', '');
                setdbprefs('DataReturnFormat','numeric')
                conn_txt=sprintf('select * from %s where cluster>0 and duration>20',sap.Teachertablename);
                curs = exec(conn, conn_txt);
                curs = fetch(curs,sap.pm.max_load_N);
                tmpdata=curs.data';
                colname=columnnames(curs); colname=strrep(colname,'''','');colname=strsplit(colname,',');
                if isempty(strmatch('classified',colname))
                    % sap.data must have new rows, {'classified','is_teacher'};
                 
                    tmpdata=cat(1,tmpdata,ones(2,size(tmpdata,2))); % append the teacher index (1).
                else  % loaded database already analyzed.
                   tmpdata=cat(1,tmpdata,ones(1,size(tmpdata,2))); % append the teacher index (1).
                end
%                 error('%s data is yet classified, cannot use as teacher database!',sap.Teachertablename);
           
                ButtonName=questdlg('Do you want to remove the teacher data in the original database?', ...
                    'How to set teacher data?', ...
                    'YES','NO','YES');
                
                switch ButtonName
                    case 'YES'
                        sap.data(sap.pm.is_teacher_index,:)=0;
                    case 'NO'
                        % do nothing
                    otherwise
                end
                
                sap.data=cat(2,sap.data(:,1:sap.pm.loaded_N),tmpdata);
            otherwise
                error;
        end
        
        
    case 'init_figures'
        
        
        % cluster selection button
        sap.gph.ui_cluster_type_select =uibuttongroup('Visible','off','Position',[.01 .9 .1 .08],'Title','showing cluster');
        dx = 1; dy=1/(length(sap.pm.cluster_types)+.1);
        
     
        for ii=1:length(sap.pm.cluster_types)
            % evaltxt = sprintf('sap.gph.ui_cluster_type(%d) = uicontrol(''Style'',''Radio'',''Value'',0,''String'',sap.pm.cluster_types{%d},''unit'',''normalized'',''pos'',[%g,%g,%g,dy],''parent'',sap.gph.ui_cluster_type_select,''HandleVisibility'',''off'',''CallBack'',''ClassifySAP_sub_routines_02(''''%s'''')'');',...
            %     ii,ii,0,1-(ii)*dy,.8,'select_cluster_data_type');
            % eval(evaltxt);
            
            evaltxt = sprintf('sap.gph.ui_cluster_type(%d) = uicontrol(''Style'',''Radio'',''Value'',0,''String'',sap.pm.cluster_types{%d},''unit'',''normalized'',''pos'',[%g,%g,%g,dy],''parent'',sap.gph.ui_cluster_type_select,''HandleVisibility'',''off'',''UserData'',sap.pm.cluster_index_in_data(ii));',...
                ii,ii,0,1-(ii)*dy,.8);
            eval(evaltxt);
        end
        
        set(sap.gph.ui_cluster_type_select,'SelectionChangeFcn','ClassifySAP_sub_routines_02(''select_cluster_data_type'')');
        set(sap.gph.ui_cluster_type_select,'SelectedObject',sap.gph.ui_cluster_type(1));  % No selection
        % set(sap.gph.ui_cluster_type(1),'Value',1);
        set(sap.gph.ui_cluster_type_select,'Visible','on');
        
        sap.gph.ui_teacher_cluster_ONOFF = uicontrol('Style','Radio',...
            'Value',0,'String','teacher','unit','normalized','pos',[.12 .95 .1 .05],...
            'CallBack','ClassifySAP_sub_routines_02(''set_teacher_OnOff'');');
        sap.gph.ui_teacher_loadbutton = uicontrol('Style','pushbutton',...
            'Value',0,'String','LoadTeacherDatabase','unit','normalized','pos',[.12 .9 .1 .05],...
            'CallBack','ClassifySAP_sub_routines_02(''load_teacher_database'');');
         sap.gph.ui_teacher_clearbutton = uicontrol('Style','pushbutton',...
            'Value',0,'String','ClearTeacher','unit','normalized','pos',[.22 .95 .1 .05],...
            'CallBack','global sap; sap.data=sap.data(:,1:sap.pm.loaded_N); sap.data(sap.pm.classified_cluster_index,:)=0;sap.data(sap.pm.is_teacher_index,:)=0;');
            
        % cluster selection button
        sap.gph.ui_clusterselect = uipanel('Title','clusters','Position',[.01 .6 .2 .3]);
        dx = 1; dy=1/10;
        for ii=[0:8]
            evaltxt = sprintf('sap.gph.ui_cluster%d = uicontrol(''Style'',''Radio'',''Value'',1,''String'',[''cluster'' num2str(%d) '':(%d)''],''unit'',''normalized'',''pos'',[%g,%g,%g,dy],''parent'',sap.gph.ui_clusterselect,''HandleVisibility'',''off'',''CallBack'',''ClassifySAP_sub_routines_02(''''%s'''')'');',...
                mod(ii,9),mod(ii,9),length(find(sap.data(sap.pm.cluster_index,:)==mod(ii,9))),0,1-(ii+1)*dy,.6,'update_datatmp');
            eval(evaltxt);
        end
        ii=9; % for noise.
        evaltxt = sprintf('sap.gph.ui_cluster%d = uicontrol(''Style'',''Radio'',''Value'',1,''String'',[''noise'' num2str(%d) '':(%d)''],''unit'',''normalized'',''pos'',[%g,%g,%g,dy],''parent'',sap.gph.ui_clusterselect,''HandleVisibility'',''off'',''CallBack'',''ClassifySAP_sub_routines_02(''''%s'''')'');',...
            ii,ii,length(find(sap.data(sap.pm.cluster_index,:)==ii)),0,1-(ii+1)*dy,.8,'update_datatmp');
        eval(evaltxt);
        
        sap.gph.ax(3)=axes('parent',sap.gph.ui_clusterselect,'unit','normalized','Position',[.6 dy/2 .25 1-dy]);
        feval(mfilename,'reload_converting_matrix');
        for ii=1:10
            plot(0,-ii,'ko','MarkerFaceColor',sap.pm.CS(ii,:));hold on;
            text(1,-ii,['=',sap.pm.converting_matrix{ii}],'Color',sap.pm.CS(ii,:));hold on;
        end
        axis off; axis tight;
        
 

uicontrol('Style', 'pushbutton','String', 'show syllable',...
    'Unit','Normalized','Position', [.25 .9 .09 .04],'Callback', 'ClassifySAP_sub_routines_02(''show_syllable'');');

uicontrol('Style', 'pushbutton','String', 'redraw',...
    'Unit','Normalized','Position', [.35 .9 .09 .04],'Callback', 'ClassifySAP_sub_routines_02(''redraw'');');

uicontrol('Style', 'pushbutton','String', 'select&annotate',...
    'Unit','Normalized','Position', [.45 .9 .09 .04],'Callback', 'ClassifySAP_sub_routines_02(''select_rect_annotate'');');



uicontrol('Style', 'pushbutton','String', 'LoadDatabase',...
    'Unit','Normalized','Position', [.55 .9 .09 .04],'Callback', 'ClassifySAP_sub_routines_02(''load_database'');');


uicontrol('Style', 'pushbutton','String', 'UploadDatabase',...
    'Unit','Normalized','Position', [.65 .9 .09 .04],'Callback', 'ClassifySAP_sub_routines_02(''upload_database'');');


x=0.1;  dx=0.1;
uicontrol('Style', 'pushbutton','String', 'play song',...
    'Unit','Normalized','Position', [x .4 .08 .04],'Callback', 'ClassifySAP_sub_routines_02(''play_wholesong'');');
% 
% uicontrol('Style', 'pushbutton','String', 'play syllable',...
%     'Unit','Normalized','Position', [.2 .4 .08 .04],'Callback', 'ClassifySAP_sub_routines_02(''play_syllable'');');

x=x+dx;
uicontrol('Style', 'pushbutton','String', 'show classification',...
    'Unit','Normalized','Position', [x .4 .08 .04],'Callback', 'ClassifySAP_sub_routines_02(''show_classification'');');
% 
% uicontrol('Style', 'pushbutton','String', 'load feature',...
%     'Unit','Normalized','Position', [.4 .4 .08 .04],...
%     'Callback', 'ClassifySAP_sub_routines_02(''load_feature'');');

x=x+dx;
uicontrol('Style', 'pushbutton','String', 'AutoClassify',...
    'Unit','Normalized','Position', [x .4 .08 .04], ...
    'ToolTips','Mahalnovis distance based classification',...
    'Callback','ClassifySAP_sub_routines_02(''auto_classify'');');


x=x+dx;
uicontrol('Style', 'pushbutton','String', 'AutoClassifyAll',...
   'FontSize',8,...
   'ForegroundColor','m',...
    'Unit','Normalized','Position', [x .4 .08 .04], ...
    'ToolTips','Apply Mahalnovis distance based classification to all the unclassified sound',...
    'Callback','ClassifySAP_sub_routines_02(''auto_classify_all'');');


x=x+dx;
uicontrol('Style', 'pushbutton','String', {'ExportSyllable','Transitions'},...
    'FontSize',8,...
    'Unit','Normalized','Position', [x .4 .08 .04], ...
    'ToolTips','Export the identified syllables into text format.',...
    'Callback','ClassifySAP_sub_routines_02(''export_syllable_transitions'');');


x=x+dx;
uicontrol('Style', 'pushbutton','String', 'ShowTransMat',...
    'Unit','Normalized','Position', [x .4 .08 .04], ...
    'ToolTips','Show transition matrix',...
    'Callback','ClassifySAP_sub_routines_02(''show_trans_matrix'');');


x=x+dx;
uicontrol('Style', 'pushbutton','String', {'ShowSyllable','Transition'},...
     'FontSize',8,...
    'Unit','Normalized','Position', [x .4 .08 .04], ...
    'ToolTips','Show Syllable Tree',...
    'Callback','ClassifySAP_sub_routines_02(''show_syllable_tree'');');


x=x+dx;
uicontrol('Style', 'pushbutton','String', {'TrainSVM'},...
     'FontSize',8,...
    'Unit','Normalized','Position', [x .4 .08 .04], ...
    'ToolTips','Show Syllable Tree',...
    'Callback','ClassifySAP_sub_routines_02(''train_predict_svm'');');


ClassifySAP_sub_routines_02('init_feature_vector');
% ClassifySAP_sub_routines_02('init_feature_vector');

% x axis selection
sap.gph.ui_xbuttonG = uibuttongroup('visible','off','Position',[.25 .5 .7 .05]);
dx = 1/7; dy=.5;
for ii=1:13
evaltxt = sprintf('sap.gph.ui_xbutton%d = uicontrol(''Style'',''Radio'',''String'',sap.pm.names{%d},''unit'',''normalized'',''pos'',[%g,%g,%g,.5],''parent'',sap.gph.ui_xbuttonG,''HandleVisibility'',''off'');',...
    ii,ii+4,(mod(ii-1,7))*dx,1-ceil(ii/7)*dy,dx);
eval(evaltxt);
end
% Initialize some button group properties. 
set(sap.gph.ui_xbuttonG,'SelectionChangeFcn','ClassifySAP_sub_routines_02(''chk_xaxis_button'')');
set(sap.gph.ui_xbuttonG,'SelectedObject',sap.gph.ui_xbutton1);  % No selection
set(sap.gph.ui_xbuttonG,'Visible','on');

% y axis selection
sap.gph.ui_ybuttonG = uibuttongroup('visible','off','Position',[0.76 .6 .19 .3]);
dx = 1/2; dy=1/7;
for ii=1:13
evaltxt = sprintf('sap.gph.ui_ybutton%d = uicontrol(''Style'',''Radio'',''String'',sap.pm.names{%d},''unit'',''normalized'',''pos'',[%g,%g,%g,dy],''parent'',sap.gph.ui_ybuttonG,''HandleVisibility'',''off'');',...
    ii,ii+4,floor(ii/7)*dx,1-(mod(ii-1,7)+1)*dy,dx);
eval(evaltxt);
end
% Initialize some button group properties. 
set(sap.gph.ui_ybuttonG,'SelectionChangeFcn','ClassifySAP_sub_routines_02(''chk_yaxis_button'')');
set(sap.gph.ui_ybuttonG,'SelectedObject',sap.gph.ui_ybutton4);  % No selection
set(sap.gph.ui_ybuttonG,'Visible','on');

sap.gph.ui_select_song_by_filename=uicontrol(...
    'Style', 'list',...
    'String', sap.distinct_data_filename,...
    'Unit','Normalized',...
    'Position', [.01 .1 .24 .3],...
    'Callback', 'ClassifySAP_sub_routines_02(''select_song_by_filename'');');

sap.gph.sonogramAxes=axes('Position',[.25 .1 .6 .3],'YDir','Normal');
sap.gph.sonogramImg = imagesc(NaN,NaN,NaN); hold on;
sap.gph.sonogram_feature_plots=plot(repmat(NaN,2,length(sap.pm.feature_names)),repmat(NaN,2,length(sap.pm.feature_names)));

% y axis selection
sap.gph.ui_featurepanel = uipanel('visible','off','Position',[0.85 .1 .14 .3]);
dx = .9; dy=1/7;
for ii=1:length(sap.pm.feature_names)
evaltxt = sprintf('sap.gph.ui_featurebutton%d = uicontrol(''Style'',''Radio'',''String'',sap.pm.feature_names{%d},''unit'',''normalized'',''pos'',[%g,%g,%g,dy],''parent'',sap.gph.ui_featurepanel,''HandleVisibility'',''off'');',...
    ii,ii,floor(ii/7)*dx,1-(mod(ii-1,7)+1)*dy,dx);
eval(evaltxt);
button_uiname=sprintf('sap.gph.ui_featurebutton%d',ii);
evaltxt=sprintf('set(%s,''Callback'',''ClassifySAP_sub_routines_02(''''chk_feature_button'''')'')',button_uiname);
eval(evaltxt);
end
set(sap.gph.ui_featurepanel,'Visible','on');


sap.gph.ui_shown_cluster_as_noise=uicontrol('Style','pushbutton','String', 'Register as Noise',...
    'FontSize',8,...
    'Unit','Normalized','Position', [.85 .06 .1 .05],'Callback', 'ClassifySAP_sub_routines_02(''register_shown_cluster_as_noise'');');


sap.gph.ui_register_shown_cluster_to_Manual_cluster=uicontrol('Style','pushbutton','String', 'Register',...
    'Unit','Normalized','Position', [.85 0 .1 .05],'Callback', 'ClassifySAP_sub_routines_02(''register_shown_cluster_to_Manual_cluster'');');

feval(mfilename,'update_datatmp');
  feval(mfilename,'set_teacher_onoff');
      
    case 'load_database'
        
        feval(mfilename,'init_variables_for_figure'); % load variables needed below;
        
        try
            sql_dir='C:\mysql\data\mysql\';
            d=dir(fullfile(sql_dir,'*.myd'));
            tablenames = {d.name};
            tablenames=strrep(tablenames,'.MYD','');
            tablenames=strrep(tablenames,'.myd','');
            
            [s,v] = listdlg('PromptString','SELECT a table to load:',...
                'SelectionMode','single',...
                'ListString',tablenames,...
                'ListSize',[250 500],...
                'Name',['Load Database in ' sql_dir]);
            if (v)
                pathname=sql_dir;
                sap.SAPtablename=tablenames{s};
            else
                disp('No table selected!');
                return;
            end
            pwd_now=pwd;
            cd(sql_dir);
            s=sprintf('%s.MYD',[sap.SAPtablename,'_x']);
               [upload_table_name, pathname] = uiputfile( ...
                {[s,';*.MYD;*.myd']; '*.*'},...
                'SELECT a table to save classified data');
            cd(pwd_now);
    
            logintimeout(5);
            fprintf('Loading table from %s\n',sap.SAPtablename);
            conn = database('mysql', '', '');
            setdbprefs('DataReturnFormat','numeric')
            conn_txt=sprintf('select * from %s where cluster<9 and duration>20',sap.SAPtablename);
            curs = exec(conn, conn_txt);
            curs = fetch(curs,sap.pm.max_load_N);
            sap.data=curs.data';
            colname=columnnames(curs); colname=strrep(colname,'''','');colname=strsplit(colname,',');
            sap.pm.names=colname;
            
            setdbprefs('DataReturnFormat','cellarray')
            conn_txt=sprintf('select distinct file_name from %s where cluster<9 and duration>20',sap.SAPtablename);
            curs = exec(conn, conn_txt);
            curs = fetch(curs,sap.pm.max_load_N);
            sap.distinct_data_filename=curs.data';
            
            conn_txt=sprintf('select file_name from %s where cluster<9 and duration>20',sap.SAPtablename);
            curs = exec(conn, conn_txt);
            curs = fetch(curs,sap.pm.max_load_N);
            sap.data_filename=curs.data';
            
            sap.pm.loaded_N=length(sap.data_filename);
%             set(1,'Name',sap.SAPtablename);
          
            if strmatch(upload_table_name,sap.SAPtablename)
                fprintf('Same table is selected. ')
            else
                fprintf('Making new table %s...\n',upload_table_name);
                drop_table=sprintf('DROP table %s;',upload_table_name);
                exec(conn,drop_table);
                create_table=sprintf('create table %s as select * from %s',strrep(upload_table_name,'.MYD',''),sap.SAPtablename)
                exec(conn,create_table);
                sap.SAPtablename=strrep(upload_table_name,'.MYD','');
                AlterClause=sprintf('ALTER TABLE %s ADD PRIMARY KEY (recnum);',sap.SAPtablename);
                exec(conn,AlterClause);
                jj=strmatch('classified',sap.pm.cluster_types);
%                 for jj=2:length(sap.pm.cluster_types)
                    alter_table=sprintf('ALTER TABLE %s ADD %s %s;',sap.SAPtablename,sap.pm.cluster_types{jj},'tinyint(4)');
                    exec(conn,alter_table);
%                 end
            end
            
           
            close(curs);
            close(conn);
            
            sap.pm.feature_dir = uigetdir('C:\home\', 'Pick a Feature binary data directory');
            s=strsplit(sap.pm.feature_dir,filesep);
            sap.pm.parent_dir= fullfile(s{1:end-1});   % The sound directory and feature directory must be in the same directory.
            s=strsplit(sap.pm.feature_dir,filesep);
            sap.pm.sound_dir=fullfile(sap.pm.parent_dir,strrep(s{end},'_feature',''))
            
            %     [sap.SAPtablename,pathname]=uigetfile( ...
            %         {'*.*',  'All Files (*.*)'}, ...
            %         'Pick a SAP exported data file');
            %
            %     cd(pathname);
            %     data= load(fullfile(pathname,sap.SAPtablename));
            %     sap.data = data.LocalDouble;
        catch e
            rethrow(e);
        end
        feval(mfilename,'init_variables');
        feval(mfilename,'init_figures');
    case 'load_teacher_database'
        feval(mfilename,'set_teacher_data','from_another_database');
        
    case 'upload_database' 
        conn = database('mysql', '', '');
%         setdbprefs('DataReturnFormat','numeric');
        set(conn,'AutoCommit','on');
        h = waitbar(0,'Uploading cluster data...');
        for kk=1:size(sap.data,2)
            whereClause=sprintf(' WHERE recnum=%d;',sap.data(1,kk));
            updateClause=sprintf('UPDATE %s SET', sap.SAPtablename);
%             for ll=1:length(sap.pm.cluster_types)
            ll= strmatch('classified',sap.pm.cluster_types);
            updateClause=[updateClause,sprintf(' %s=%d,',sap.pm.cluster_types{ll},sap.data(sap.pm.cluster_index_in_data(ll),kk))];
%             end
            updateClause=updateClause(1:end-1);% to remove the last ','. 
            exec(conn,[updateClause,whereClause]);
%             update(conn,sap.SAPtablename,sap.pm.cluster_types,sap.data(sap.pm.cluster_index_in_data,kk),whereClause);
            waitbar(kk/size(sap.data,2),h);
        end
        commit(conn);
%         set(conn,'AutoCommit','on');
        close(h);
        close(conn);
    case 'set_teacher_onoff'
        sap.gpm.do_show_teacher=get(gcbo,'Value');
        feval(mfilename,'redraw_clusters');
    case 'select_cluster_data_type'
        %         sap.gpm.cluster_selection=zeros(1,length(sap.pm.cluster_types));
        %         for ii=1:length(sap.pm.cluster_types)
        %             sap.gpm.cluster_selection(ii)=get(sap.gph.ui_cluster_type(ii)
        %             ,'Value');
        %         end
        sap.pm.selected_cluster_type=get(get(sap.gph.ui_cluster_type_select,'selectedobject'),'String');
        
        which_cluster_type=get(get(sap.gph.ui_cluster_type_select,'selectedobject'),'UserData');
        for ii=[0:8]
            evaltxt = sprintf('set(sap.gph.ui_cluster%d, ''String'',[''cluster'' num2str(%d) '':(%d)'']);',...
                ii,ii,length(find(sap.data(which_cluster_type,:)==ii)));
            eval(evaltxt);
        end
        ii=9; % for noise.
        evaltxt = sprintf('set(sap.gph.ui_cluster%d, ''String'',[''noise'' num2str(%d) '':(%d)'']);',...
            ii,ii,length(find(sap.data(which_cluster_type,:)==ii)));
        eval(evaltxt);
        
        feval(mfilename,'redraw_clusters');
        
        
    case 'update_datatmp'
        
        for ii=[0:9]
            evaltxt = sprintf('sap.pm.cluster_val(%d)=get(sap.gph.ui_cluster%d,''Value'');',ii+1,ii);
            eval(evaltxt);
        end
%         sap.pm.cluster_val;
%         sap.pm.show_column_bools=zeros(1,size(sap.data,2));
%         for ii=0:9
%             if (sap.pm.cluster_val(ii+1))
%                 sap.pm.show_column_bools =sap.pm.show_column_bools|(sap.data(sap.pm.cluster_index,:)==ii);
%             end
%         end
%         if ~sap.gpm.do_show_teacher
%             sap.pm.show_column_bools =sap.pm.show_column_bools|~sap.data(sap.pm.is_teacher_index,:);
%         end
        %         datatmp = sap.data(:,sap.pm.show_column_bools);
        feval(mfilename,'redraw_clusters');
        feval(mfilename,'init_cov_matrix');
    case 'choose_syllable_branch'
        
        str=get(gcbo,'UserData');
        txt='sap.iii';
        for ii=1:length(str)
            txt=sprintf('%s.%s',txt,str(ii));
        end
        txt=sprintf('%s.%s',txt,'index');
        fprintf('Selected %s branch\n',txt);
        sap.syllable_tree_to_show_index=unique(eval(txt));
        set(sap.pm.current_syllable_branch_txt,'String',str,'FontSize',12);
        set(sap.ui.maxN_current_syllable_tree,'String',num2str(length(sap.syllable_tree_to_show_index)),'FontSize',12);
        feval(mfilename,'move_to_syllable_branch',1);
        
    case {'show_syllable','show_syllable_transition','select_song_by_filename','show_syllable_branch'}
        try delete(sap.gph.syllable_label);end
        try delete(sap.gph.syllable_label2);end
        try delete(sap.gph.syllable_label3);end
        try delete(sap.gph.wavefile_text);end
        
        switch lower(opt)
            case 'show_syllable'
                % we will not show the teacher data here, 
                axes(sap.gph.ax(1));
                [xposi,yposi]=ginput(1);
                % here syllables are searched through only in the
                % to-be-analyzed data, not the teacher data.
                local_show_bools=sap.pm.show_column_bools&~sap.data(sap.pm.is_teacher_index,:);
                datatmp=sap.data(:,local_show_bools);
                distance=(datatmp(sap.pm.xind,:)-xposi).^2/var(datatmp(sap.pm.xind,:))+...
                    (datatmp(sap.pm.yind,:)-yposi).^2/var(datatmp(sap.pm.yind,:));
                
                
                
                [mindistnace,sap.pm.minind]=min(distance);
                show_index_local=find(local_show_bools);
                sap.pm.show_sonogram_index=show_index_local(sap.pm.minind);
                
                sap.pm.serial=datatmp(sap.pm.serial_index,sap.pm.minind);
                %                  datatmp(:,sap.pm.minind)
                fprintf('Look for the wavefile (serial=%d) \n',sap.pm.serial);
                %                    index=return_index_from_same_wavfile(sap.pm.serial,sap.data(sap.pm.timevec_index,sap.pm.show_sonogram_index));
                
                s=dir(fullfile(sap.pm.sound_dir,['*',num2str(sap.pm.serial),'*.wav']));
                sap.pm.filename=sap.data_filename{sap.pm.show_sonogram_index};
                if isempty(sap.pm.filename)
                    error('The sound file with serial number %d does not exist in %s',sap.pm.serial,sap.pm.sound_dir);
                end
                sap.pm.do_highlight_note=1;
                ind =strmatch(sap.pm.filename, get(sap.gph.ui_select_song_by_filename,'String'));
                set(sap.gph.ui_select_song_by_filename,'Value',ind);
                
            case 'show_syllable_transition'
                %                  axes(sap.gph.trans_mat_axes);
                %                  figure(2);
                %                  [xposi,yposi]=ginput(1);
                %                  xposi=round(xposi);                 yposi=round(yposi);
                %                  fprintf('Look for transition from syllable %d to %d',yposi,xposi);
                %                  sap.pm.show_sonogram_index=sap.pm.trans_matrix_serials{yposi,xposi};
                sap.pm.show_sonogram_index=sap.pm.showing_trans_matrix_serials(sap.pm.current_transit_n);
                sap.pm.filename=sap.data_filename{sap.pm.show_sonogram_index};
                sap.pm.serial=sap.data(sap.pm.serial_index,sap.pm.show_sonogram_index);
                sap.pm.do_highlight_note=1;
                ind =strmatch(sap.pm.filename, get(sap.gph.ui_select_song_by_filename,'String'));
                set(sap.gph.ui_select_song_by_filename,'Value',ind);
                
            case 'select_song_by_filename'
                val=get(sap.gph.ui_select_song_by_filename,'Value');
                str=get(sap.gph.ui_select_song_by_filename,'String');
                sap.pm.filename=str{val};
                
                conn = database('mysql', '', '');
                setdbprefs('DataReturnFormat','numeric')
                conn_txt=sprintf('select distinct serial_number from %s where file_name like ''%s''',...
                    sap.SAPtablename,sap.pm.filename);
                curs = exec(conn, conn_txt);
                curs = fetch(curs,10);
                sap.pm.serial=curs.data';
                serial=sap.pm.serial
                close(curs);close(conn);
                
                fprintf('Look for a song %s \n',sap.pm.filename);
                sap.pm.show_sonogram_index=[];
                
                
                
                sap.pm.do_highlight_note=0;
            case 'show_syllable_branch'
                
                val=sap.syllable_tree_to_show_index(sap.pm.current_syllable_branch_n);
                str=get(sap.gph.ui_select_song_by_filename,'String');
                sap.pm.filename=str{val};
                
                conn = database('mysql', '', '');
                setdbprefs('DataReturnFormat','numeric')
                conn_txt=sprintf('select distinct serial_number from %s where file_name like ''%s''',...
                    sap.SAPtablename,sap.pm.filename);
                curs = exec(conn, conn_txt);
                curs = fetch(curs,10);
                sap.pm.serial=curs.data';
                close(curs);close(conn);
                
                fprintf('Look for a song %s \n',sap.pm.filename);
                sap.pm.show_sonogram_index=[];
                
                set(sap.gph.ui_select_song_by_filename,'Value',val);
                
                sap.pm.do_highlight_note=0;
                
            otherwise
                error('Unknown option!')
                
        end
        
        
        
        
        
        %         axes(sap.gph.sonogramAxes); cla(sap.gph.sonogramAxes,'reset');
        txt=strrep(sprintf('wavfile: %s',sap.pm.filename),'_','\_');
        [sap.pm.song,sap.pm.Fsong]=wavread(fullfile(sap.pm.sound_dir,sap.pm.filename));
        
        
        
%         nfft = 1012;
%         fftwindow=nfft;
%         numoverlap=ceil(nfft/1.2);
%         [y,f,t,p]=spectrogram(sap.pm.song,fftwindow,numoverlap,nfft,sap.pm.Fsong);
%         logp=10*log10(abs(p));
%         set(sap.gph.sonogramImg,'XData',t,'YData',f,'CData',logp);colormap(jet);
%         max_spec=max(max(logp));
%         min_spec=min(min(logp));
%         cutoff=.55;
%         set(sap.gph.sonogramAxes,'CLim',cutoff*[min_spec, max_spec]);
%         
                m_spec_deriv=sam_spectrum_deriv2(sap.pm.song,sap.pm.Fsong);
                size(m_spec_deriv);
                max_spec=max(max(m_spec_deriv));
                min_spec=min(min(m_spec_deriv));
                cutoff=0.001;
                t=linspace(0,length(sap.pm.song)/sap.pm.Fsong,size(m_spec_deriv,1));
                f=sap.pm.Fsong*(1:size(m_spec_deriv,2))*1000/1024;
                 set(sap.gph.sonogramImg,'XData',t,'YData',f,'CData',m_spec_deriv');colormap(bone);
                 set(sap.gph.sonogramAxes,'CLim',cutoff*[-max_spec, max_spec]);
        
        
        set(sap.gph.sonogramAxes,'XLim',[min(t) max(t)],'YLim',[0 max(f)]);
        %         imagesc(t,f,logp); set(gca,'YDir','Normal'); hold on;
        axes(sap.gph.sonogramAxes);
        sap.gph.wavefile_text=text(min(xlim)+0.01*diff(xlim),max(ylim)-0.1*diff(ylim),txt);
        axis tight;
        
        if (sap.pm.do_highlight_note)
            try delete([sap.gph.syllable_start,sap.gph.syllable_end]);end
            sap.gph.syllable_start=line([sap.data(sap.pm.start_on_index,sap.pm.show_sonogram_index(1)),...
                sap.data(sap.pm.start_on_index,sap.pm.show_sonogram_index(1))]/1000,...
                ylim,[10 10],'Color','r','LineWidth',2);
            sap.gph.syllable_end  =line(([sap.data(sap.pm.start_on_index,sap.pm.show_sonogram_index(1)),...
                sap.data(sap.pm.start_on_index,sap.pm.show_sonogram_index(1))]+...
                sap.data(sap.pm.duration_index,sap.pm.show_sonogram_index(1)))/1000,ylim,'Color','r','LineWidth',2);
            
            ind = ceil(sap.pm.Fsong*sap.data(sap.pm.start_on_index,sap.pm.show_sonogram_index(1))/1000)+[0:ceil(sap.pm.Fsong*sap.data(sap.pm.duration_index,sap.pm.show_sonogram_index(1))/1000)];
            sound(sap.pm.song(ind)/(6*std(sap.pm.song)),sap.pm.Fsong);
        end
        
        feval(mfilename,'init_feature_button');
        feval(mfilename,'show_classification');
        
    case 'play_wholesong'
        if (sap.pm.do_highlight_note)
            Cs=get(sap.gph.syllable_start,'Color');
            Ce=get(sap.gph.syllable_end,'Color');
        end
        tt=get(sap.gph.sonogramAxes,'XLim');
        tti=ceil(tt*sap.pm.Fsong)+1;
        
        tti(1)=max(1,tti(1));  % start index > 1.
        tti(2)=min(length(sap.pm.song),tti(2)); % end index < length(song)
        
        % sound(ss.song(tti(1):tti(2)),ss.F);
        
        sound(sap.pm.song(tti(1):tti(2))/(6*std(sap.pm.song)),sap.pm.Fsong);
        
        %         sound(sap.pm.song,sap.pm.Fsong);
        if (sap.pm.do_highlight_note)
            pause(sap.data(sap.pm.start_on_index,sap.pm.show_sonogram_index)/1000-tti(1)/sap.pm.Fsong);
            set(sap.gph.syllable_start,'Color','k');
            set(sap.gph.syllable_end,'Color','k');
            pause(sap.data(sap.pm.duration_index,sap.pm.show_sonogram_index)/1000);
            set(sap.gph.syllable_start,'Color',Cs);
            set(sap.gph.syllable_end,'Color',Ce);
        end
    case 'play_syllable'
        ind = ceil(sap.pm.Fsong*sap.data(sap.pm.start_on_index,sap.pm.show_sonogram_index)/1000)+[0:ceil(sap.pm.Fsong*sap.data(sap.pm.duration_index,sap.pm.show_sonogram_index)/1000)];
        sound(sap.pm.song(ind)/(6*std(sap.pm.song)),sap.pm.Fsong);
        
    case 'show_classification'
        axes(sap.gph.sonogramAxes);
        %         sap.pm.serial=datatmp(sap.pm.serial_index,sap.pm.minind);
        %         datatmp=sap.data(:,sap.pm.show_column_bools);
        sap.pm.same_serial_index = strmatch(sap.pm.filename,sap.data_filename);
        
        
        try delete(sap.gph.syllable_label);end
        try delete(sap.gph.syllable_label2);end
        try delete(sap.gph.syllable_label3);end
        try delete(sap.gph.syllable_line);end
        sap.gph.syllable_label=zeros(1,length(sap.pm.same_serial_index));
        sap.gph.syllable_label2=zeros(1,length(sap.pm.same_serial_index));
        sap.gph.syllable_label3=zeros(1,length(sap.pm.same_serial_index));
        sap.gph.syllable_line =zeros(1,length(sap.pm.same_serial_index));
        
        feval(mfilename,'reload_converting_matrix');
     
        
        which_cluster_type=get(get(sap.gph.ui_cluster_type_select,'selectedobject'),'UserData');
        index_sounds=sap.data(which_cluster_type,sap.pm.same_serial_index);
        str2=sap.pm.converting_matrix(index_sounds+1);
        str2=[str2{:}];
        
        current_dir=pwd;
        cd(sap.pm.sound_dir);
        eval('analysis_parameters'); % load converting matrix, etc.
        cd(current_dir);
        
        str2=filter_syllable_structure(str2,replace_chart,{});
        
        for ii=1:length(sap.pm.same_serial_index)
            x = [sap.data(sap.pm.start_on_index,sap.pm.same_serial_index(ii)),...
                sap.data(sap.pm.start_on_index,...
                sap.pm.same_serial_index(ii))+sap.data(sap.pm.duration_index,sap.pm.same_serial_index(ii))]/1000;
            sap.gph.syllable_line(ii)=line(x,[0 0],'Color','m','LineWidth',3,...
                'ButtonDownFcn','ClassifySAP_sub_routines_02(''return_feature_2D_posi'')',...
                'UserData',sap.pm.same_serial_index(ii));
            cluster=sap.data(which_cluster_type,sap.pm.same_serial_index(ii));
            
            cluster_str=sap.pm.converting_matrix{cluster+1};
            
            sap.gph.syllable_label(ii)=text(mean(x),-0.15*diff(ylim),num2str(cluster),...
                'Color',sap.pm.CS(cluster+1,:));
            sap.gph.syllable_label2(ii)=text(mean(x),-0.2*diff(ylim),cluster_str,...
                'Color',sap.pm.CS(cluster+1,:));
%             sap.gph.syllable_label3(ii)=text(mean(x),-0.25*diff(ylim),str2(ii),...
%                 'Color',sap.pm.CS(cluster+1,:));
            
            set(sap.gph.syllable_label(ii),...
                'ButtonDownFcn','ClassifySAP_sub_routines_02(''manual_change_cluster'')',...
                'UserData',[sap.pm.same_serial_index(ii),ii]);
            
        end
    case 'reload_converting_matrix'
        current_dir=pwd;
        cd(sap.pm.sound_dir);
        try
            eval('analysis_parameters'); % load converting matrix, etc.
        catch
            fprintf('analysis parameter does not exists in %s...\n Use default one.',sap.pm.sound_dir);
            copy_txt=sprintf('!cp %s %s',which('ClassifySAP_Default_analysis_parameters.m'),fullfile(sap.pm.sound_dir,'analysis_parameters.m'));
            eval(copy_txt);
            eval('analysis_parameters');
        end
        cd(current_dir);
        
        sap.pm.converting_matrix=converting_matrix;
    case 'chk_xaxis_button'
        sap.pm.xname=get(get(sap.gph.ui_xbuttonG,'selectedobject'),'String');
        feval(mfilename,'redraw_clusters');
    case 'chk_yaxis_button'
        sap.pm.yname=get(get(sap.gph.ui_ybuttonG,'selectedobject'),'String');
        feval(mfilename,'redraw_clusters');
    case 'redraw_clusters'
        xlim_now=xlim;
        ylim_now=ylim;
        sap.pm.xind = strmatch(sap.pm.xname,sap.pm.names);
        sap.pm.yind = strmatch(sap.pm.yname,sap.pm.names);
        cla(sap.gph.ax(1),'reset');        axes(sap.gph.ax(1));
        %         sap.gph.ax(1)=axes('Position',[.1 .6 .7 .3]);
        sap.pm.show_column_bools= false(1,size(sap.data,2));
        
        which_cluster_type=get(get(sap.gph.ui_cluster_type_select,'selectedobject'),'UserData');
        
        for ii=0:9
            if (sap.pm.cluster_val(ii+1))
                sap.pm.show_column_bools =sap.pm.show_column_bools|(sap.data(which_cluster_type,:)==ii);
            end
        end
        
        if sap.gpm.do_show_teacher % show all the data
%             sap.pm.show_column_bools =sap.pm.show_column_bools&(sap.data(sap.pm.is_teacher_index,:));
            local_show_bools =sap.pm.show_column_bools;
        else % do not show the teacher data
            local_show_bools =sap.pm.show_column_bools&~(sap.data(sap.pm.is_teacher_index,:));
        end
        
%         sap.pm.show_column_bools=find(sap.pm.show_column_bools); 
%         length(sap.pm.show_column_bools)
        
        for ii=0:9
            if (sap.pm.cluster_val(ii+1))
                show_index=sap.data(which_cluster_type,:)==ii;
                datatmp=sap.data(:,show_index&local_show_bools);
                h=plot(datatmp(sap.pm.xind,:),datatmp(sap.pm.yind,:),'ko','MarkerSize',2);hold on;
                
                CSnow = sap.pm.CS(ii+1,:);
                
                set(h,'MarkerFaceColor',CSnow,'MarkerEdgeColor','none');
            end
        end
        %         axis([xlim_now ylim_now]);
        xlabel(strrep(sap.pm.xname,'_','\_'));ylabel(strrep(sap.pm.yname,'_','\_'));
        
        try
            sap.gph.selected_note_posi=plot(sap.data(sap.pm.xind,sap.gph.selected_note_index),...
                sap.data(sap.pm.yind,sap.gph.selected_note_index),'ro','MarkerSize',5);
        catch
%             disp('!')
        end
        
    case 'redraw'
        axis tight;
    case 'load_feature'
        
        
        sap.pm.feature_loadname=sap.pm.filename;
        
        if isempty(strfind(sap.pm.feature_loadname,'.wav'))
            sap.pm.feature=read_sap_feature(fullfile(sap.pm.feature_dir,[sap.pm.feature_loadname,'.dat']));
        else
            sap.pm.feature=read_sap_feature(fullfile(sap.pm.feature_dir,strrep(sap.pm.feature_loadname,'.wav','.dat')));
        end
        
        
        dt=9.27/2/1000;
        sap.pm.feature.t=linspace(dt,length(sap.pm.song)/44100-dt,length(sap.pm.feature.amplitude));
    case 'init_feature_button'
        
        lf=length(sap.pm.feature_names);
        for ii=1:lf
            s=['ui_featurebutton',num2str(ii)];
            set(sap.gph.(s),'Value',0);
        end
        feval(mfilename,'chk_feature_button');
        
    case 'chk_feature_button'
        
        
        if isempty(strmatch(sap.pm.filename,sap.pm.feature_loadname))
            feval(mfilename,'load_feature');
        end
        
        lf=length(sap.pm.feature_names);
        val=zeros(lf,1);
        for ii=1:lf
            s=['ui_featurebutton',num2str(ii)];
            val(ii)=get(sap.gph.(s),'Value');
        end
        ymax=max(get(sap.gph.sonogramAxes,'YLim'));
        for ii=1:lf
            if val(ii)
                tmp=sap.pm.feature.(sap.pm.feature_names{ii});
                tmpmax=max(tmp);
                tmpmin=min(tmp);
                tmp=(tmp-tmpmin)/(tmpmax-tmpmin); % now [0,1];
                tmp=tmp*ymax;
                set(sap.gph.sonogram_feature_plots(ii),'XData',sap.pm.feature.t,'YData',tmp);
            else
                set(sap.gph.sonogram_feature_plots(ii),'XData',NaN,'YData',NaN);
                
            end
        end
    case 'init_cov_matrix'
        % for the syllable detection, we use only
        % duration, mean_pitch, mean_FM,mean_entropy,mean_gpitch.
        
        sap.pm.covM=zeros(length(sap.pm.classify_dim_index));
        show_ind_local=find(sap.pm.show_column_bools);
        mean_val=mean(sap.data(sap.pm.classify_dim_index,show_ind_local),2);
        for ii=1:length(show_ind_local)
            tmp=sap.data(sap.pm.classify_dim_index,show_ind_local(ii))-mean_val;
            sap.pm.covM=sap.pm.covM+(tmp)*(tmp)';
        end
        sap.pm.covM=sap.pm.covM/length(show_ind_local);
        sap.pm.invcovM=inv(sap.pm.covM);
    case 'init_feature_vector'
        % calculate the mean feature vector of each syllables.
        % duration, mean_pitch, mean_FM,mean_entropy,mean_gpitch.
        
        sap.pm.feature_vector=zeros(length(sap.pm.mean_feature_index),9);
        for ii=1:9
            index = (sap.data(sap.pm.cluster_index,:)==mod(ii,9));
            tmp=sap.data(sap.pm.mean_feature_index,index);
            sap.pm.feature_vector(:,ii)=mean(tmp,2);
        end
        
    case 'auto_classify'
        
        if nargin>=2
            mode=varargin{1};
        else
            mode='show_gui';
        end
        
        if strmatch(mode,'nogui_mode')
            no_gui=1;
        else
            no_gui=0;
        end
       
        if nargin>=3
            method=varargin{2};
        else
            %             method='kGaussMix';
            method='kNN';
        end
      
        switch method
            case 'kNN'
                %         fprintf('Calculating Mahalanobis distance...\n');
                teacher_ind=sap.data(sap.pm.is_teacher_index,:);
                
                for ww=1:9
                    ind=teacher_ind&(sap.data(sap.pm.cluster_index,:)==ww);
                    weight(ww)=length(find(ind));
                end
                weight=weight./sum(weight);
                weight(weight==0)=inf;
                search_index=find(sap.pm.show_column_bools&teacher_ind);
                
                for ii=1:length(sap.pm.same_serial_index)
                    feature = sap.data(sap.pm.classify_dim_index,sap.pm.same_serial_index(ii));
                    cluster=sap.data(sap.pm.cluster_index,sap.pm.same_serial_index(ii));
                    
                    MaharDist=zeros(length(search_index),1);
                    
                    if (cluster==0)
                        %             dx=(repmat(feature,1,length(sap.pm.show_column_bools))-sap.data(sap.pm.mean_feature_index,sap.pm.show_column_bools));
                        for jj=1:length(search_index)
                            dx=feature-sap.data(sap.pm.classify_dim_index,search_index(jj));
                            MaharDist(jj)=dx'*sap.pm.invcovM*dx;
                            %                     MahalDist(jj,2)=sap.data(sap.pm.cluster_index,sap.pm.show_column_bools(jj));
                        end
                        
                        [MaharDist,I] = sort(MaharDist,1,'ascend');
                        % take the 10% of the data and its index.
                        c=floor(.01*length(search_index));
                        nb_clust=sap.data(sap.pm.cluster_index,search_index(I(1:c))); % nearby clusters.
                        nb_clust=nb_clust(nb_clust~=0); % pick up classified ones.
                        %                 N_nb_clust=hist(nb_clust,[1:9]);
                        N_nb_clust=hist(nb_clust,[1:9])./weight;
                        [max_N_nb_clust,max_nb_clust]=sort(N_nb_clust,'descend');
                        
                        %                 max_nb_clust
                        if ~(no_gui)
                            cluster_str=sap.pm.converting_matrix{max_nb_clust(1)+1};
                            set(sap.gph.syllable_label(ii),'String',num2str(max_nb_clust(1)),...
                                'ButtonDownFcn','ClassifySAP_sub_routines_02(''manual_change_cluster'')',...
                                'UserData',[sap.pm.same_serial_index(ii),ii,max_nb_clust]);
                        end
                        sap.data(sap.pm.classified_cluster_index,sap.pm.same_serial_index(ii))=max_nb_clust(1);
                    else
                        sap.data(sap.pm.classified_cluster_index,sap.pm.same_serial_index(ii))=sap.data(sap.pm.cluster_index,sap.pm.same_serial_index(ii));
                    end
                    
                end
            case 'kGaussMix'
                %         fprintf('Calculating Mahalanobis distance...\n');
             
                teacher_ind=sap.data(sap.pm.is_teacher_index,:);
               search_index=find(sap.pm.show_column_bools&teacher_ind);
                
                for ii=1:length(sap.pm.same_serial_index)
                    feature = sap.data(sap.pm.classify_dim_index,sap.pm.same_serial_index(ii));
                    cluster=sap.data(sap.pm.cluster_index,sap.pm.same_serial_index(ii));
                    
                    
                    
                    if (cluster==0)
                        Dist=zeros(size(sap.gpm.Gauss.M,2)+1,1);
                        %             dx=(repmat(feature,1,length(sap.pm.show_column_bools))-sap.data(sap.pm.mean_feature_index,sap.pm.show_column_bools));
                        for jj=1:size(sap.gpm.Gauss.M,2)
                            dx=feature-sap.gpm.Gauss.M(:,jj);
                            S = sqrt(det(sap.gpm.Gauss.V(:,:,jj)));
                            Dist(jj)=1/sap.gpm.Gauss.W(jj)/S*exp(-dx'*sap.gpm.Gauss.invV(:,:,jj)*dx/2);
                            %                     MahalDist(jj,2)=sap.data(sap.pm.cluster_index,sap.pm.show_column_bools(jj));
                        end
                        Dist;
                        Dist(9)=1.e-11;sap.gpm.Gauss.W(9)/S(1)*exp(-3/2);
                        
                        [max_N_nb_clust,max_nb_clust]=max(Dist);
                        
                        %                 max_nb_clust
                        if ~(no_gui)
                            cluster_str=sap.pm.converting_matrix{max_nb_clust(1)+1};
                            set(sap.gph.syllable_label(ii),'String',num2str(max_nb_clust(1)),...
                                'ButtonDownFcn','ClassifySAP_sub_routines_02(''manual_change_cluster'')',...
                                'UserData',[sap.pm.same_serial_index(ii),ii,max_nb_clust]);
                        end
                        sap.data(sap.pm.classified_cluster_index,sap.pm.same_serial_index(ii))=max_nb_clust(1);
                    else
                        sap.data(sap.pm.classified_cluster_index,sap.pm.same_serial_index(ii))=sap.data(sap.pm.cluster_index,sap.pm.same_serial_index(ii));
                    end
                    
                end
            otherwise
                error('unknown classification method!')
        end
    case 'auto_classify_all'
       
        
        ind=~sap.data(sap.pm.is_teacher_index,:);
        unique_serials=unique(sap.data(2,ind));
        if ~all(sap.pm.cluster_val)
            warning('one or more clusters are not selected, and will be neglected in the classification.');
        end
        sap.data(sap.pm.classified_cluster_index,:)=zeros(1,size(sap.data,2));
        try
            h = waitbar(0,'Classifying notes...');
            
            for ii=1:length(unique_serials)
                sap.pm.same_serial_index = find(sap.data(sap.pm.serial_index,:)==unique_serials(ii));
%                 feval(mfilename,'auto_classify','nogui_mode','kGaussMix');
                   feval(mfilename,'auto_classify','nogui_mode','kNN');
                waitbar(ii/length(unique_serials),h);
            end
            
            close(h)
        catch
            close(h)
        end
        
    case 'parse_autoclassified_notes'
        unique_serials=unique(sap.data(2,:));
        
        sap.pm.trans_matrix=zeros(10);
        sap.pm.trans_matrix_serials=cell(10);
        
        for ii=1:length(unique_serials)
            sap.pm.same_serial_index = find(sap.data(sap.pm.serial_index,:)==unique_serials(ii));
            which_cluster_type=get(get(sap.gph.ui_cluster_type_select,'selectedobject'),'UserData');
            
            tmp=sap.data(which_cluster_type,sap.pm.same_serial_index);
            
            for jj=1:length(sap.pm.same_serial_index)-1
                ISI=sap.data(sap.pm.start_on_index,sap.pm.same_serial_index(jj+1))-sap.data(sap.pm.start_on_index,sap.pm.same_serial_index(jj))-...
                    sap.data(sap.pm.duration_index,sap.pm.same_serial_index(jj));
                if ISI<200 % if note-note interval is more than 200ms, define the end of the song.
                    sap.pm.trans_matrix(tmp(jj),tmp(jj+1))=ceil(sap.pm.trans_matrix(tmp(jj),tmp(jj+1))+1);
                    sap.pm.trans_matrix_serials{tmp(jj),tmp(jj+1)}=[sap.pm.trans_matrix_serials{tmp(jj),tmp(jj+1)},...
                        sap.pm.same_serial_index(jj)];
                else
                    sap.pm.trans_matrix(tmp(jj),10)=ceil(sap.pm.trans_matrix(tmp(jj),10)+1);
                    sap.pm.trans_matrix_serials{tmp(jj),10}=[sap.pm.trans_matrix_serials{tmp(jj),10}, ...
                        sap.pm.same_serial_index(jj)];
                    
                end
            end
            sap.pm.trans_matrix(tmp(end),10)=ceil(sap.pm.trans_matrix(tmp(end),10)+1);
            sap.pm.trans_matrix_serials{tmp(end),10}=[sap.pm.trans_matrix_serials{tmp(end),10}, sap.pm.same_serial_index(end)];
            
        end
        
        sumP=sum( sap.pm.trans_matrix,2);
        sap.pm.Ntrans_matrix=sap.pm.trans_matrix./repmat(sumP,1,size(sap.pm.trans_matrix,2));
       
        sap.pm.Nrepeat_prob=diag(sap.pm.Ntrans_matrix);
        for ii=1:size(sap.pm.Ntrans_matrix)
            sap.pm.Ntrans_matrix(ii,ii)=0;
        end
        sap.pm.Ntrans_matrix=sap.pm.Ntrans_matrix./repmat(sum(sap.pm.Ntrans_matrix,2),1,size(sap.pm.trans_matrix,2));
        
    case 'show_trans_matrix'
        figure(2);clf;
        
        feval(mfilename,'parse_autoclassified_notes');
        sap.gph.ui_Transmat_panel = uipanel('visible','on','Position',[0.1 0 .9 .9]);
        sap.gph.trans_mat_axes=axes('Position',[.05 0 .9 .9],'Parent',sap.gph.ui_Transmat_panel);
        sap.gph.trans_mat_IMG=imagesc(sap.pm.Ntrans_matrix);
        set(sap.gph.trans_mat_axes,'XAxisLocation','top',...
            'XTick',[1:9],'XTickLabel',[1:9],'YTick',[1:9],'YTickLabel',[1:9]);
        
        uicontrol('Style', 'pushbutton','String', 'show syllable','Parent',sap.gph.ui_Transmat_panel,...
            'Unit','Normalized','Position', [0 1 .2 .1],...
            'Callback', 'ClassifySAP_sub_routines_02(''choose_syllable_transition'');');
        sap.ui.decrement_transit_syllable=uicontrol('Style', 'pushbutton','String', '<','Parent',sap.gph.ui_Transmat_panel,...
            'Unit','Normalized','Position', [.2 1 .15 .1],...
            'Callback', 'ClassifySAP_sub_routines_02(''move_syllable_transition'',-1);');
        sap.ui.edit_transit_syllable=uicontrol('Style', 'edit','String', '1','Parent',sap.gph.ui_Transmat_panel,...
            'Unit','Normalized','Position', [.35 1 .15 .1],...
            'Callback', 'ClassifySAP_sub_routines_02(''move_syllable_transition'',-1);');
        sap.ui.increment_transit_syllable=uicontrol('Style', 'pushbutton','String', '>','Parent',sap.gph.ui_Transmat_panel,...
            'Unit','Normalized','Position', [.5 1 .15 .1],...
            'Callback', 'ClassifySAP_sub_routines_02(''move_syllable_transition'',+1);');
        sap.ui.maxN_transit_syllable=uicontrol('Style', 'Text','String', 'MaxN','Parent',sap.gph.ui_Transmat_panel,...
            'Unit','Normalized','Position', [.65 1 .15 .1]);
    case 'choose_syllable_transition'
        
        axes(sap.gph.trans_mat_axes);
        figure(2);
        [xposi,yposi]=ginput(1);
        xposi=round(xposi);                 yposi=round(yposi);
        txt=sprintf('%d -> %d',yposi,xposi);
        sap.pm.showing_trans_matrix_serials=sap.pm.trans_matrix_serials{yposi,xposi};
        sap.pm.current_transit_n=1;
        set(sap.ui.edit_transit_syllable,'String','1');
        set(sap.ui.maxN_transit_syllable,'String',{num2str(length(sap.pm.showing_trans_matrix_serials)),txt});
        feval(mfilename,'show_syllable_transition',sap.pm.current_transit_n);
        
    case 'move_syllable_transition'
        d=varargin{1};
        if (sap.pm.current_transit_n+d)>length(sap.pm.showing_trans_matrix_serials)
            warning('No more syllables !');
            sap.pm.current_transit_n=length(sap.pm.showing_trans_matrix_serials);
        elseif (sap.pm.current_transit_n+d)<1
            warning('No more syllables !');
            sap.pm.current_transit_n=1;
        else
            sap.pm.current_transit_n=sap.pm.current_transit_n+d;
        end
        
        feval(mfilename,'show_syllable_transition',sap.pm.current_transit_n);
        set(sap.ui.edit_transit_syllable,'String',num2str(sap.pm.current_transit_n));
        
        %% =========== move to syllable branch ================
    case 'move_to_syllable_branch'
        d=varargin{1};
        if (d>length(sap.syllable_tree_to_show_index))
            warning('No more syllables !');
            sap.pm.current_syllable_branch_n=length(sap.syllable_tree_to_show_index);
        elseif (d<1)
            warning('No more syllables !');
            sap.pm.current_syllable_branch_n=1;
        else
            sap.pm.current_syllable_branch_n=d;
        end
        
        feval(mfilename,'show_syllable_branch',sap.pm.current_syllable_branch_n);
        set(sap.ui.edit_current_syllable_tree_n,'String',num2str(sap.pm.current_syllable_branch_n));
        
    case 'return_feature_2d_posi'
        try delete(sap.gph.selected_note_posi); end;
        sap.gph.selected_note_index=get(gcbo,'UserData');
        axes(sap.gph.ax(1));
        sap.gph.selected_note_posi=plot(sap.data(sap.pm.xind,sap.gph.selected_note_index),...
            sap.data(sap.pm.yind,sap.gph.selected_note_index),'ro','MarkerSize',5);
        
        fprintf('!')
        sap.pm.show_sonogram_index=sap.gph.selected_note_index;
        feval(mfilename,'play_syllable');
        
    case 'manual_change_cluster'
        tmp=get(gcbo,'UserData');
        fprintf('This cluster (%dth note) has neighbors:',tmp(2));
        fprintf('%d ',tmp(3:end));fprintf('\n');
        
        sap.gph.change_note_index=tmp(1);
        sap.gph.syllable_label_tag=tmp(2);
        
        Units = get(gcbo,'Units'); set(gcbo,'Units','Normalized');
        posi=get(gcbo,'Extent');  set(gcbo,'Units',Units);
        parent_posi=get(get(gcbo,'Parent'),'Position');
        o=parent_posi([1:2]); dx=parent_posi(3);dy=parent_posi(4);
        posi= o+[posi(1)*dx,posi(2)*dy];
        posi=[posi .03 .03];
        sap.gph.uieditnow=uicontrol('Style', 'edit','String', get(gcbo,'String'),...
            'Unit','Normalized','Position',posi,...
            'UserData',tmp,...
            'Callback', 'ClassifySAP_sub_routines_02(''enter_cluster_number'');');
        waitfor(sap.gph.uieditnow);
        
    case 'enter_cluster_number'
        
        str=get(sap.gph.uieditnow,'String');
        if ~ischar(str)
            delete(sap.gph.uieditnow);
            error('The cluster number must be a numeric!');
        end
        Userdata=get(sap.gph.uieditnow,'UserData');
        index=Userdata(1)
        set(sap.gph.syllable_label(sap.gph.syllable_label_tag),'String',str,'FontWeight','bold');
        
        which_cluster_type=get(get(sap.gph.ui_cluster_type_select,'selectedobject'),'UserData');
        sap.data(which_cluster_type,index)=str2num(str);
        sap.data(sap.pm.is_teacher_index,index)=1;
        delete(sap.gph.uieditnow);
        
    case  'register_shown_cluster_to_manual_cluster'
        
        ButtonName=questdlg('Do you want to register the clusters shown below as the manually clustered value?', ...
            'Genie Question', ...
            'YES','NO','Cancel');
        
        if strmatch(ButtonName,'YES')
            for ii=1:length(sap.gph.syllable_label)
                str=get(sap.gph.syllable_label(ii),'String');
                index=get(sap.gph.syllable_label(ii),'UserData');
                sap.data(sap.pm.cluster_index,index(1))=str2double(str);
                sap.data(sap.pm.is_teacher_index,index(1))=1;
            end
        end
        
    case  'register_shown_cluster_as_noise'
        
        ButtonName=questdlg('Do you want to register all the unclassified clusters shown below as the noise?', ...
            'Genie Question', ...
            'YES','NO','YES');
        
        
        
        if strmatch(ButtonName,'YES')
            selection=sprintf('in ')
            for ii=1:length(sap.pm.cluster_types)
                selection=[selection sprintf('%s(%d),',sap.pm.cluster_types{ii},ii)];
            end
            prompt={selection};
        
%             prompt={'Then,in SAP(1),Mahr(2),EM(3),Manual(4)?'};
            name='Register in which database';
            numlines=1;
            defaultanswer={'1'};
            
            which_database=inputdlg(prompt,name,numlines,defaultanswer);
            num=str2num(which_database{1});
            switch num
                case 1
                    which_database=sap.pm.cluster_index;
                case 2
                    which_database=sap.pm.classified_cluster_index;
%                 case 3
%                     which_database=sap.pm.EM_cluster_index;
%                 case 4
%                     which_database=sap.pm.cluster_index;
                otherwise
                    error('Unknown option!');
            end
            
            
            for ii=1:length(sap.gph.syllable_label)
                set(sap.gph.syllable_label(ii),'String','9');
                index=get(sap.gph.syllable_label(ii),'UserData');
                sap.data(which_database,index(1))=9; % register as a noise
                sap.data(sap.pm.is_teacher_index,index(1))=1;
            end
        end
    case 'export_syllable_transitions'
        
        val=get(sap.gph.ui_select_song_by_filename,'Value');
        str=get(sap.gph.ui_select_song_by_filename,'String');
        sap.pm.filename=str{val};
        
        conn = database('mysql', '', '');
        setdbprefs('DataReturnFormat','numeric')
        
        which_cluster_type=get(get(sap.gph.ui_cluster_type_select,'selectedobject'),'UserData');
        %         unique_serials=unique(sap.data(sap.pm.serial_index,:))
        %         rmfield(sap,'syllables');
            h = waitbar(0,'Exporting syllables from each song file...');
          sap.syllables=struct;  
          
        for ii=1:length(str)
            conn_txt=sprintf('select distinct serial_number from %s where file_name like ''%s''',...
                sap.SAPtablename,str{ii});
            curs = exec(conn, conn_txt);
            curs = fetch(curs,10);
            sap.pm.serial=curs.data';
            same_serial_index=strmatch(str{ii},sap.data_filename);
            sap.syllables(ii).note='';
            
            for jj=1:(length(same_serial_index)-1)
                ISI=sap.data(sap.pm.start_on_index,same_serial_index(jj+1))-sap.data(sap.pm.start_on_index,same_serial_index(jj))-...
                    sap.data(sap.pm.duration_index,same_serial_index(jj));
                if ISI<200 % if note-note interval is more than 200ms, define the end of the song.
                    
                      % because we insert unclassified note as the first
                      % class, we need to +1 for the index to neglect them in this stage.
                    cluster= sap.pm.converting_matrix{sap.data(which_cluster_type,same_serial_index(jj))+1};
                    sap.syllables(ii).note=[sap.syllables(ii).note, cluster];
                else
                     cluster= sap.pm.converting_matrix{sap.data(which_cluster_type,same_serial_index(jj))+1};
                   sap.syllables(ii).note=[sap.syllables(ii).note, sprintf('%s\n',cluster)];               
                end
            end
                
                
%             sap.syllables(ii).note=sap.data(which_cluster_type,same_serial_index);
            sap.syllables(ii).filename=str{ii};
            waitbar(ii/length(str),h);
        end
        
        close(h);        close(curs);close(conn);
    case 'show_syllable_tree'
%         feval(mfilename,'export_syllable_transitions');
%         str=sap.syllables(1).note;
        [sap.iii,sap.iii_labels]=Parse_Song_Structure_01p1('parse',{sap.syllables(:).note});
        %% select rectangular region and annotate them as a certain cluster
    case 'select_rect_annotate'
        
        axes(sap.gph.ax(1));
        [pl,xs,ys] = selectdata('selectionmode','rect');
        if ~iscell(xs)
            xs={xs}; ys={ys};
        end
        xs=cat(1,xs{:});
        ys=cat(1,ys{:});
        min_x=min(xs);
        max_x=max(xs);
        min_y=min(ys);
        max_y=max(ys);
        
        indx=(sap.data(sap.pm.xind,:)>=min_x)&(sap.data(sap.pm.xind,:)<=max_x);
        indy=(sap.data(sap.pm.yind,:)>=min_y)&(sap.data(sap.pm.yind,:)<=max_y);
        selection=sprintf('in ')
        for ii=1:length(sap.pm.cluster_types)
            selection=[selection sprintf('%s(%d),',sap.pm.cluster_types{ii},ii)];
        end
        prompt={'Enter the cluster number to register:',selection};
        name='Annotate the cluster';
        numlines=1;
        defaultanswer={'0','1'};
        
        cluster=inputdlg(prompt,name,numlines,defaultanswer);
        num=str2num(cluster{2});
        switch num
            case 1
                which_cluster_type=sap.pm.cluster_index;
            case 2
                which_cluster_type=sap.pm.classified_cluster_index;
            case 3
                which_cluster_type=sap.pm.teacher_cluster_index;
%             case 4
%                 which_cluster_type=sap.pm.cluster_index;
            otherwise
                error('Unknown option!');
        end
        
        
        cluster=str2num(cluster{1});
        
        if (cluster<1)||(cluster>10) || ~isscalar(cluster)
            error('cluster number should be [0-9]');
        end
        %         which_cluster_type=get(get(sap.gph.ui_cluster_type_select,'selectedobject'),'UserData');
        sap.data(which_cluster_type,indx&indy)=cluster;
        sap.data(sap.pm.is_teacher_index,indx&indy)=1;
        
        feval(mfilename,'redraw_clusters');
    case 'estimate_gaussian_mixture'
        
        prompt={'How many clusters you assume? '};
        name='Number of clusters';
        numlines=1;
        defaultanswer={'7'};
        
        nCluster=inputdlg(prompt,name,numlines,defaultanswer);
        nCluster=str2num(nCluster{1});
        teacher_ind=logical(sap.data(sap.pm.is_teacher_index,:));
        [d,n]=size(sap.data(sap.pm.classify_dim_index,teacher_ind));
        W=zeros(1,9);
        for ii=1:9
            W(ii)=nnz(sap.data(sap.pm.cluster_index,teacher_ind)==ii);
        end
            W=W/sum(W);
          
        %         sap.data(sap.pm.classify_dim_index,teacher_ind)
        
        
        M = zeros(nCluster,d);
        
        for ii=1:nCluster,  % Compute weights
            M(ii,:) =mean(sap.data(sap.pm.classify_dim_index,...
                find(sap.data(sap.pm.cluster_index,teacher_ind)==ii)),2);
        end
        
        V = zeros(d,d,nCluster);
        invV = zeros(d,d,nCluster);
        for ii=1:nCluster,
            index=find(sap.data(sap.pm.cluster_index,teacher_ind)==ii);
            if isempty(index)
                error('You assigned %d clusters but %d-th cluster is empty!',nCluster,ii);
            elseif length(index)==1
                V(:,:,ii) = ones(d)*eps;
            else
                tmp=sap.data(sap.pm.classify_dim_index,teacher_ind(index));
                dtmp=tmp-repmat(M(ii,:)',1,size(tmp,2));
                V(:,:,ii) = dtmp*dtmp'/length(index);
                invV(:,:,ii)=inv(V(:,:,ii));
            end
        end
        sap.gpm.Gauss.W=W;
        sap.gpm.Gauss.M=M';
        sap.gpm.Gauss.V=V;
        sap.gpm.Gauss.invV=invV;
    case 'kmeans_clustering'
        ClassifySAP_sub_routines_02('estimate_gaussian_mixture');
        
        [cidx, ctrs] = kmeans(sap.data(sap.pm.classify_dim_index,:)', 8, ...
            'Distance','correlation', ...
            'Start', sap.gpm.Gauss.M');
%         sap.data(sap.pm.cluster_index,:)=cidx;
     
        sap.data(sap.pm.classified_cluster_index,:)=cidx;
    case 'em_clustering'
        % This used EM-algorithm to
        % -- meaning of cluster number
        %         1 is the intro
        %         2 is the 2nd note
        %           ...
        %         0 is the unidentified sound
        %         9 is the noise
        %

        feval(mfilename,'estimate_gaussian_mixture');
       Init.W=sap.data.Gauss.W;
       Init.M=sap.data.Gauss.M;
       Init.V=sap.data.Gauss.V;
        %         teacher_ind=find(sap.data(sap.pm.cluster_index,:)~=0);
        %         [W,M,V,L] = EM_GM(sap.data(sap.pm.classify_dim_index,1:10:end)',7,.01,10,1);
        [W,M,V,L] = EM_kmeans_01p1(sap.data(sap.pm.classify_dim_index,1:2:end)',...
            [sap.data(sap.pm.classify_dim_index,teacher_ind);sap.data(sap.pm.cluster_index,teacher_ind)]',...
            nCluster,.0001,100,1,Init);
    case 'train_predict_svm'
        teacher_ind=sap.data(sap.pm.is_teacher_index,:);
        index=find(teacher_ind);
        
        train_index=index(1:end);
%         test_index=index(1001:end);
        
        norm_data=sap.data(sap.pm.classify_dim_index,:);
        norm_data=norm_data./repmat(std(norm_data,[],2),1,size(norm_data,2));
        
        sap.pm.model=struct;
         fprintf('training...\n')
        for class=1:8
            train_label=sap.data(sap.pm.cluster_index,train_index)'==class;
            
            fprintf('class=%d:(N=%d)',class,length(find(train_label>0)))
            
            sap.pm.model(class).param = svmtrain(2*train_label-1,...
                norm_data(:,train_index)', '-c 400 -g 0.01');
            
%             test_label=sap.data(sap.pm.classified_cluster_index,test_index)'==class;
%             [predict_label, accuracy, dec_values] = svmpredict(2*test_label-1,  ...
%                 norm_data(:,test_index)', sap.pm.model(class).param); % test the training data
            fprintf('\n')
        end
        
 
%     case 'predict_svm'
        test_ind=find(~sap.data(sap.pm.is_teacher_index,:));
        norm_data=sap.data(sap.pm.classify_dim_index,:);
        norm_data=norm_data./repmat(std(norm_data,[],2),1,size(norm_data,2));
        
        
        for class=1:8
            [predict_label, accuracy, dec_values] = svmpredict(randn(length(test_ind),1),  ...
                norm_data(:,test_ind)', sap.pm.model(class).param); % test the training data
            ind=find(predict_label==1);
            sap.data(sap.pm.classified_cluster_index,test_ind(ind))=class;
        end
        
    case 'train_validate_svm'
        teacher_ind=sap.data(sap.pm.is_teacher_index,:);
        index=find(teacher_ind);
        inL=length(index);
        train_index=index(1:ceil(inL/2));
        test_index=index(ceil(inL/2)+1:end);
        
        norm_data=sap.data(sap.pm.classify_dim_index,:);
        norm_data=norm_data./repmat(std(norm_data,[],2),1,size(norm_data,2));
        
        sap.pm.model=struct;
        for class=1:9
            fprintf('class=%d:',class)
            train_label=sap.data(sap.pm.classified_cluster_index,train_index)'==class;
            sap.pm.model(class).param = svmtrain(2*train_label-1,...
                norm_data(:,train_index)', '-c 40 -g 0.01');
            
            test_label=sap.data(sap.pm.classified_cluster_index,test_index)'==class;
            [predict_label, accuracy, dec_values] = svmpredict(2*test_label-1,  ...
                norm_data(:,test_index)', sap.pm.model(class).param); % test the training data
            fprintf('\n')
        end
    otherwise
        error('Unknown option')
end