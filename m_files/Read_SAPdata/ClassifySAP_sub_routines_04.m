function varargout=ClassifySAP_sub_routines_04(opt,varargin)
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
        
        sap.pm.max_load_N=12000;
        sap.gpm.do_show_teacher=1;
        sap.pm.sound_dir=pwd;
        sap.pm.names=SAP_data_structure_in_MySQL();        sap.pm.names={sap.pm.names{:,1}};
        sap.distinct_data_filename={'Please LoadData'};
        sap.pm.ISI_thresh=200;
    case 'init_variables'
        
        
        sc=get(0,'ScreenSize');
        dw=sc(3)*.7;
        dh=sc(4)*.8;
        pos=[10  sc(4)-dh-100  dw dh];
        % zname = 'mean_pitch';
        h=figure(16);clf; set(h,'Position',pos,'ToolBar','figure');
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
        sap.pm.mean_amplitude       =strmatch('mean_amplitude',sap.pm.names);
        
        sap.pm.timevec_index=[sap.pm.month_index,...
            sap.pm.day_index,...
            sap.pm.hour_index,...
            sap.pm.minute_index,...
            sap.pm.second_index];
        
        sap.pm.classified_cluster_index     =strmatch('classified',sap.pm.names);
        sap.pm.is_teacher_index             =strmatch('is_teacher',sap.pm.names);
%         sap.pm.cluster_index_in_data=[sap.pm.cluster_index,sap.pm.classified_cluster_index];
        
   
        %       sap.teacher_data=sap.data(:,sap.data(sap.pm.cluster_index,:)~=0);
        %         sap.teacher_cluster_index=sap.pm.cluster_index;
        
        
        
        sap.pm.mean_feature_index=[sap.pm.duration_index,...
            sap.pm.mean_pitch_index,...
            sap.pm.mean_FM_index,...
            sap.pm.mean_entropy_index,...
            sap.pm.mean_gpitch_index];
        
        sap.pm.classify_dim_index=[sap.pm.mean_feature_index,sap.pm.var_entropy_index,sap.pm.mean_amplitude];
        
        sap.pm.feature_loadname=[];
        sap.pm.sonogram_caxis_cutooff_min=0.0001;
        sap.pm.sonogram_caxis_cutooff_max=0.1;
        sap.pm.sonogram_caxis_cutooff=0.06;
        
        
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
                sap.pm.teacher_database_colname=colname;
                diffnames=   setdiff(sap.pm.names,sap.pm.teacher_database_colname);
                
                if ~isempty(diffnames)
                    sap.pm.names={sap.pm.names{:},diffnames{:}};
                    tmpdata=cat(1,tmpdata,zeros(length(diffnames),size(tmpdata,2)));
                end
                tmpdata(sap.pm.is_teacher_index,:)=1;
%                 
%                 if isempty(strmatch('classified',colname))
%                     % sap.data must have new rows, {'classified','is_teacher'};
%                     
%                     tmpdata=cat(1,tmpdata,ones(2,size(tmpdata,2))); % append the teacher index (1).
%                 else  % loaded database already analyzed.
%                     tmpdata=cat(1,tmpdata,ones(1,size(tmpdata,2))); % append the teacher index (1).
%                 end
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
%                 size(tmpdata)
               
             
                sap.data=cat(2,sap.data(:,1:sap.pm.loaded_N),tmpdata);
            otherwise
                error;
        end
        
        
    case 'init_figures'
        
        
        % cluster selection button
        sap.gph.ui_cluster_type_select =uibuttongroup('Visible','off','Position',[.01 .9 .1 .08],'Title','showing cluster');
        dx = 1; dy=1/(length(sap.pm.cluster_types)+.1);
        
        
        for ii=1:length(sap.pm.cluster_types)
            % evaltxt = sprintf('sap.gph.ui_cluster_type(%d) = uicontrol(''Style'',''Radio'',''Value'',0,''String'',sap.pm.cluster_types{%d},''unit'',''normalized'',''pos'',[%g,%g,%g,dy],''parent'',sap.gph.ui_cluster_type_select,''HandleVisibility'',''off'',''CallBack'',''ClassifySAP_sub_routines_04(''''%s'''')'');',...
            %     ii,ii,0,1-(ii)*dy,.8,'select_cluster_data_type');
            % eval(evaltxt);
            
            evaltxt = sprintf('sap.gph.ui_cluster_type(%d) = uicontrol(''Style'',''Radio'',''Value'',0,''String'',sap.pm.cluster_types{%d},''unit'',''normalized'',''pos'',[%g,%g,%g,dy],''parent'',sap.gph.ui_cluster_type_select,''HandleVisibility'',''off'');',...
                ii,ii,0,1-(ii)*dy,.8);
            eval(evaltxt);
        end
        
        set(sap.gph.ui_cluster_type_select,'SelectionChangeFcn','ClassifySAP_sub_routines_04(''select_cluster_data_type'')');
        set(sap.gph.ui_cluster_type_select,'SelectedObject',sap.gph.ui_cluster_type(1));  % No selection
        % set(sap.gph.ui_cluster_type(1),'Value',1);
        set(sap.gph.ui_cluster_type_select,'Visible','on');
        
        sap.gph.ui_teacher_cluster_ONOFF = uicontrol('Style','Radio',...
            'Value',0,'String','teacher','unit','normalized','pos',[.12 .93 .1 .03],...
            'CallBack','ClassifySAP_sub_routines_04(''set_teacher_OnOff'');');
         sap.gph.ui_Stimlated_cluster_ONOFF = uicontrol('Style','Radio',...
            'Value',1,'String','stimulated','unit','normalized','pos',[.12 .90 .1 .03],...
            'CallBack','ClassifySAP_sub_routines_04(''set_Stimlated_cluster_ONOFF'');');
       
        sap.gph.ui_teacher_loadbutton = uicontrol('Style','pushbutton',...
            'Value',0,'String','LoadTeacherDatabase','unit','normalized','pos',[.25 .95 .1 .04],...
            'CallBack','ClassifySAP_sub_routines_04(''load_teacher_database'');');
        sap.gph.ui_teacher_clearbutton = uicontrol('Style','pushbutton',...
            'Value',0,'String','ClearTeacher','unit','normalized','pos',[.35 .95 .1 .04],...
            'CallBack','global sap; sap.data=sap.data(:,1:sap.pm.loaded_N); sap.data(sap.pm.classified_cluster_index,:)=0;sap.data(sap.pm.is_teacher_index,:)=0;');
        
        % cluster selection button
        sap.gph.ui_clusterselect = uipanel('Title','clusters','Position',[.01 .6 .2 .3]);
        dx = 1; dy=1/10;
        for ii=[0:8]
            evaltxt = sprintf('sap.gph.ui_cluster%d = uicontrol(''Style'',''Radio'',''Value'',1,''String'',[''cluster'' num2str(%d) '':(--)''],''unit'',''normalized'',''pos'',[%g,%g,%g,dy],''parent'',sap.gph.ui_clusterselect,''HandleVisibility'',''off'',''CallBack'',''ClassifySAP_sub_routines_04(''''%s'''')'');',...
                mod(ii,9),mod(ii,9),0,1-(ii+1)*dy,.6,'update_datatmp');
            eval(evaltxt);
        end
        ii=9; % for noise.
        evaltxt = sprintf('sap.gph.ui_cluster%d = uicontrol(''Style'',''Radio'',''Value'',1,''String'',[''noise'' num2str(%d) '':(--)''],''unit'',''normalized'',''pos'',[%g,%g,%g,dy],''parent'',sap.gph.ui_clusterselect,''HandleVisibility'',''off'',''CallBack'',''ClassifySAP_sub_routines_04(''''%s'''')'');',...
            ii,ii,0,1-(ii+1)*dy,.8,'update_datatmp');
        eval(evaltxt);
        
        sap.gph.ax(3)=axes('parent',sap.gph.ui_clusterselect,'unit','normalized','Position',[.6 dy/2 .25 1-dy]);
        feval(mfilename,'reload_converting_matrix');
        for ii=1:10
            plot(0,-ii,'ko','MarkerFaceColor',sap.pm.CS(ii,:));hold on;
            text(1,-ii,['=',sap.pm.converting_matrix{ii}],'Color',sap.pm.CS(ii,:));hold on;
        end
        axis off; axis tight;
        
        
        yh=0.03;
        uicontrol('Style', 'pushbutton','String', 'show syllable',...
            'Unit','Normalized','Position', [.25 .9 .09 yh],'Callback', 'ClassifySAP_sub_routines_04(''show_syllable'');');
        
        uicontrol('Style', 'pushbutton','String', 'redraw',...
            'Unit','Normalized','Position', [.35 .9 .09 yh],'Callback', 'ClassifySAP_sub_routines_04(''redraw'');');
        
        uicontrol('Style', 'pushbutton','String', 'select&annotate',...
            'Unit','Normalized','Position', [.45 .9 .09 yh],'Callback', 'ClassifySAP_sub_routines_04(''select_rect_annotate'');');
        
        
        
        uicontrol('Style', 'pushbutton','String', 'LoadDatabase',...
            'Unit','Normalized','Position', [.55 .9 .09 yh],'Callback', 'ClassifySAP_sub_routines_04(''load_database'');');
       
         uicontrol('Style', 'pushbutton','String', 'LoadDatabase+DAK',...
            'Unit','Normalized','Position', [.55 .95 .09 yh],...
            'Tooltip','Load mysql database generated by .dak data','Callback', 'ClassifySAP_sub_routines_04(''load_database_dak'');');
       
        
        uicontrol('Style', 'pushbutton','String', 'UploadDatabase',...
            'Unit','Normalized','Position', [.65 .9 .09 yh],'Callback', 'ClassifySAP_sub_routines_04(''upload_database'');');
       
           
        uicontrol('Style', 'pushbutton','String', 'EditAnalysisParam',...
            'Unit','Normalized','Position', [.75 .9 .09 yh],'Callback', 'ClassifySAP_sub_routines_04(''open_analysis_parameters'');');
        
        uicontrol('Style', 'pushbutton','String', 'ShowPrincomp',...
            'Unit','Normalized','Position', [.85 .9 .09 yh],'Callback', 'ClassifySAP_sub_routines_04(''show_princomp_axis'');');
      
        
        
        x=0.1;  dx=0.1;
        xw=0.08;
        pos0=[x, .4, xw, yh];
        pos1=pos0+[0 yh 0 0];
        uicontrol('Style', 'pushbutton','String', 'play song',...
            'Unit','Normalized','Position', pos0,'Callback', 'ClassifySAP_sub_routines_04(''play_wholesong'');');
        
         uicontrol('Style', 'pushbutton','String', 'print sonogram',...
            'Unit','Normalized','Position', pos1,'Callback', 'ClassifySAP_sub_routines_04(''print_sonogram'');');
        
        % uicontrol('Style', 'pushbutton','String', 'play syllable',...
        %     'Unit','Normalized','Position', [.2 .4 xw yh],'Callback', 'ClassifySAP_sub_routines_04(''play_syllable'');');
        
%         x=x+dx;
%         uicontrol('Style', 'pushbutton','String', 'show classification',...
%             'Unit','Normalized','Position', [x .4 xw yh],'Callback', 'ClassifySAP_sub_routines_04(''show_classification'');');
        %
        % uicontrol('Style', 'pushbutton','String', 'load feature',...
        %     'Unit','Normalized','Position', [.4 .4 xw yh],...
        %     'Callback', 'ClassifySAP_sub_routines_04(''load_feature'');');
        
%         x=x+dx;
%         uicontrol('Style', 'pushbutton','String', 'AutoClassify',...
%             'Unit','Normalized','Position', [x .4 xw yh], ...
%             'ToolTips','Mahalnovis distance based classification',...
%             'Callback','ClassifySAP_sub_routines_04(''auto_classify'');');
%         
%         
%         x=x+dx;
%         uicontrol('Style', 'pushbutton','String', 'AutoClassifyAll',...
%             'FontSize',8,...
%             'ForegroundColor','m',...
%             'Unit','Normalized','Position', [x .4 xw yh], ...
%             'ToolTips','Apply Mahalnovis distance based classification to all the unclassified sound',...
%             'Callback','ClassifySAP_sub_routines_04(''auto_classify_all'');');
        
       
%         x=x+dx;
        pos0=pos0+[dx,0 0,0];
        uicontrol('Style', 'pushbutton','String', {'ExportSyllable','Transitions'},...
            'FontSize',8,...
            'Unit','Normalized','Position', pos0, ...
            'ToolTips','Export the identified syllables into text format.',...
            'Callback','ClassifySAP_sub_routines_04(''export_syllable_transitions'');');
        
        
        pos0=pos0+[dx,0 0,0];
        uicontrol('Style', 'pushbutton','String', 'ShowTransMat',...
            'Unit','Normalized','Position', pos0, ...
            'ToolTips','Show transition matrix',...
            'Callback','ClassifySAP_sub_routines_04(''show_trans_matrix'');');
        
        
       pos0=pos0+[dx,0 0,0];
        uicontrol('Style', 'pushbutton','String', {'ShowSyllable','Transition'},...
            'FontSize',8,...
            'Unit','Normalized','Position', pos0, ...
            'ToolTips','Show Syllable Tree',...
            'Callback','ClassifySAP_sub_routines_04(''show_syllable_tree'');');
        
        pos1=pos0+[0,yh 0,0];
        uicontrol('Style', 'pushbutton','String', {'AlignSong'},...
            'FontSize',8,...
            'Unit','Normalized','Position', pos1, ...
            'ToolTips','Show Syllable Tree',...
            'Callback','ClassifySAP_sub_routines_04(''align_song'');');
        
         
       
       
         pos1=pos1+[0,yh 0,0];
        uicontrol('Style', 'pushbutton','String', {'SongMotifHist'},...
            'FontSize',8,...
            'Unit','Normalized','Position', pos1, ...
            'ToolTips','Export Song/Motif histgram',...
            'Callback','ClassifySAP_sub_routines_04(''export_bout_durations'');');
       
        
                
        
        pos0=pos0+[dx,0 0,0];
        uicontrol('Style', 'pushbutton','String', {'TrainSVM'},...
            'FontSize',8,...
            'Unit','Normalized','Position', pos0, ...
            'ToolTips','TrainSVM',...
            'Callback','ClassifySAP_sub_routines_04(''train_predict_svm'');');
        
        pos1=pos0+[0,yh 0,0];
        uicontrol('Style', 'pushbutton','String', {'AlignSonogram'},...
            'FontSize',8,...
            'Unit','Normalized','Position', pos1, ...
            'ToolTips','PlotAlignedSonogram',...
            'Callback','ClassifySAP_sub_routines_04(''align_sonogram_plot'');');
        
         pos0=pos0+[dx,0 0,0];
        uicontrol('Style', 'pushbutton','String', {'DeleteSong'},...
            'FontSize',8,...
            'Unit','Normalized','Position', pos0, ...
            'ToolTips','Delete this song from database and file',...
            'Callback','ClassifySAP_sub_routines_04(''delete_song_from_database'');');
        
       
        
%         ClassifySAP_sub_routines_04('init_feature_vector');
        
        % x axis selection
        sap.gph.ui_xbuttonG = uibuttongroup('visible','off','Position',[.25 .5 .7 .05]);
        dx = 1/7; dy=.5;
        for ii=1:13
            evaltxt = sprintf('sap.gph.ui_xbutton%d = uicontrol(''Style'',''Radio'',''String'',sap.pm.names{%d},''unit'',''normalized'',''pos'',[%g,%g,%g,.5],''parent'',sap.gph.ui_xbuttonG,''HandleVisibility'',''off'');',...
                ii,ii+4,(mod(ii-1,7))*dx,1-ceil(ii/7)*dy,dx);
            eval(evaltxt);
        end
        % Initialize some button group properties.
        set(sap.gph.ui_xbuttonG,'SelectionChangeFcn','ClassifySAP_sub_routines_04(''chk_xaxis_button'')');
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
        set(sap.gph.ui_ybuttonG,'SelectionChangeFcn','ClassifySAP_sub_routines_04(''chk_yaxis_button'')');
        set(sap.gph.ui_ybuttonG,'SelectedObject',sap.gph.ui_ybutton4);  % No selection
        set(sap.gph.ui_ybuttonG,'Visible','on');
        
        sap.gph.ui_select_song_by_filename=uicontrol(...
            'Style', 'list',...
            'String', sap.distinct_data_filename,...
            'Unit','Normalized',...
            'Position', [.01 .1 .24 .3],...
            'Callback', 'ClassifySAP_sub_routines_04(''select_song_by_filename'');');
        
        sap.gph.sonogramAxes=axes('Position',[.25 .1 .6 .3],'YDir','Normal');
        sap.gph.sonogramImg = imagesc(NaN,NaN,NaN); hold on;   colormap gray;
        sap.gph.sonogram_feature_plots=plot(repmat(NaN,2,length(sap.pm.feature_names)),repmat(NaN,2,length(sap.pm.feature_names)));
        
        % y axis selection
        sap.gph.ui_featurepanel = uipanel('visible','off','Position',[0.87 .1 .12 .3]);
        dx = .9; dy=1/7;
        for ii=1:length(sap.pm.feature_names)
            evaltxt = sprintf('sap.gph.ui_featurebutton%d = uicontrol(''Style'',''Radio'',''String'',sap.pm.feature_names{%d},''unit'',''normalized'',''pos'',[%g,%g,%g,dy],''parent'',sap.gph.ui_featurepanel,''HandleVisibility'',''off'');',...
                ii,ii,floor(ii/7)*dx,1-(mod(ii-1,7)+1)*dy,dx);
            eval(evaltxt);
            button_uiname=sprintf('sap.gph.ui_featurebutton%d',ii);
            evaltxt=sprintf('set(%s,''Callback'',''ClassifySAP_sub_routines_04(''''chk_feature_button'''')'')',button_uiname);
            eval(evaltxt);
        end
        set(sap.gph.ui_featurepanel,'Visible','on');
        
        
        sap.gph.ui_shown_cluster_as_noise=uicontrol('Style','pushbutton','String', 'Register as Noise',...
            'FontSize',8,...
            'Unit','Normalized','Position', [.87 .05 .1 .05],'Callback', 'ClassifySAP_sub_routines_04(''register_shown_cluster_as_noise'');');
        
        
        sap.gph.ui_register_shown_cluster_to_Manual_cluster=uicontrol('Style','pushbutton','String', 'Register',...
            'Unit','Normalized','Position', [.87 0 .1 .05],'Callback', 'ClassifySAP_sub_routines_04(''register_shown_cluster_to_Manual_cluster'');');
        
         sap.gph.ui_spectrum_contrast=uicontrol('Style','slider','Value', 0.1*(1-sap.pm.sonogram_caxis_cutooff),...
            'Unit','Normalized','Position', [.85 0.1 .01 .3],'Callback', 'ClassifySAP_sub_routines_04(''set_spectrum_contrast'');');
        
    
        
    case {'load_database','load_database_dak'}
        
        feval(mfilename,'init_variables_for_figure'); % load variables needed below;
        feval(mfilename,'init_variables');
        feval(mfilename,'init_figures');
        
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
            
            set(16,'Name',sprintf('%s: %s',mfilename,sap.SAPtablename));
            drawnow;
            pwd_now=pwd;
            cd(sql_dir);
            if isempty(strfind(sap.SAPtablename,'_x'))
                s=sprintf('%s.MYD',[sap.SAPtablename,'_x']);
            else
                s=[sap.SAPtablename,'.MYD'];
            end
            
            if FileExists(fullfile(sql_dir,s))
                questtxt=sprintf('Detected previously generated already classified data %s, overwrite?',s);
                 ButtonName=questdlg(questtxt, ...
                'Question', ...
                'YES','NO','Cancel');
            else
                 questtxt=sprintf('Classified database in default is %s. Use this?',s);
                 ButtonName=questdlg(questtxt, ...
                'Question', ...
                'YES','NO','Cancel');
            end
            
            if strmatch(ButtonName,'YES')
                upload_table_name=s;
                pathname=sql_dir;
            else   
                [upload_table_name, pathname] = uiputfile( ...
                    {s, 'MYD-file (*.MYD)'; ...
                    '*.MYD', 'MYD-file (*.MYD)'},...
                    'SELECT a table to save classified data');
            end
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
            set(sap.gph.ui_select_song_by_filename,'String', sap.distinct_data_filename,'Value',1);
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
%                 drop_table=sprintf('DROP table %s;',upload_table_name);
%                 exec(conn,drop_table);
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
            varnames=SAP_data_structure_in_MySQL;varnames={varnames{:,1}};
            diffnames=   setdiff(varnames,sap.pm.names)
            
            % check the columns which does not exist in the databse, and
            % append them.
            if ~isempty(diffnames)
                sap.pm.names={sap.pm.names{:},diffnames{:}};
                sap.data=cat(1,sap.data,zeros(length(diffnames),size(sap.data,2)));
            end
         
% %            
%             % now, check this cluster already contains 'classified' column.
%             if isempty(strmatch('classified',sap.pm.names)) % loaded new database never analyzed.
%                 % sap.data must have new rows, {'classified','is_teacher'};
%                 sap.pm.names={sap.pm.names{:},'classified','is_teacher'};
%                 sap.data=[sap.data;zeros(2,size(sap.data,2))];
%             else  % loaded database already analyzed.
%                 % 'is_teacher' column is not uploaded, and is just used within matlab.
%                 % so we need to assign new row for them.
%                 sap.pm.names={sap.pm.names{:},'is_teacher'};
%                 sap.data=[sap.data;zeros(1,size(sap.data,2))];
%             end            
            sap.pm.classified_cluster_index   = strmatch('classified',sap.pm.names);
            sap.pm.is_teacher_index           =strmatch('is_teacher',sap.pm.names);
            sap.pm.stimulated_index          = strmatch('stimulated',sap.pm.names);
            
            sap.pm.cluster_index_in_data=[sap.pm.cluster_index,sap.pm.classified_cluster_index];
            % assign the row number information in userdata
            for ii=1:length(sap.pm.cluster_types)
                  evaltxt = sprintf('set(sap.gph.ui_cluster_type(%d),''UserData'',sap.pm.cluster_index_in_data(%d));',...
                    ii,ii);
                eval(evaltxt);
            end
        
            feval(mfilename,'set_teacher_data','from_same_database');
             
            switch lower(opt)
                case 'load_database'
                    sap.pm.dak_mode=0;
                    sap.pm.feature_dir = uigetdir('C:\home\Labview\data\', 'Pick a Feature binary data directory');
                    s=strsplit(sap.pm.feature_dir,filesep);
                    parent_dir= fullfile(s{1:end-1});   % The sound directory and feature directory must be in the same directory.
                    s=strsplit(sap.pm.feature_dir,filesep);
                    sap.pm.sound_dir=fullfile(parent_dir,strrep(s{end},'_feature',''))
                case 'load_database_dak'
                    sap.pm.dak_mode=1;
                    sap.pm.dakdata = uigetfile({'*.dak'}, 'Pick the original .dak data');
                    sap.pm.sound_dir='Null';
                otherwise
                    error('Unknown option!');
            end
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
   
        feval(mfilename,'update_datatmp');
        feval(mfilename,'set_teacher_onoff');
        feval(mfilename,'redraw');
        
    case 'load_teacher_database'
        feval(mfilename,'set_teacher_data','from_another_database');
        
    case 'upload_database'
        conn = database('mysql', '', '');
        
        fprintf('Making new table %s...\n',sap.SAPtablename);
        drop_table=sprintf('DROP table %s;',sap.SAPtablename);
        exec(conn,drop_table);
        create_table=sprintf('create table %s as select * from %s',sap.SAPtablename,strrep(sap.SAPtablename,'_x',''))
        exec(conn,create_table);
        AlterClause=sprintf('ALTER TABLE %s ADD PRIMARY KEY (recnum);',sap.SAPtablename);
        exec(conn,AlterClause);
        jj=strmatch('classified',sap.pm.cluster_types);
        %                 for jj=2:length(sap.pm.cluster_types)
        alter_table=sprintf('ALTER TABLE %s ADD %s %s;',sap.SAPtablename,sap.pm.cluster_types{jj},'tinyint(4)');
        exec(conn,alter_table);
        
        
        
        %         setdbprefs('DataReturnFormat','numeric');
        set(conn,'AutoCommit','on');
        h = waitbar(0,'Uploading cluster data...');
        for kk=1:sap.pm.loaded_N; 
            whereClause=sprintf(' WHERE recnum=%d;',sap.data(1,kk));
            updateClause=sprintf('UPDATE %s SET', sap.SAPtablename);
            %             for ll=1:length(sap.pm.cluster_types)
%             ll= strmatch('classified',sap.pm.cluster_types);
             updateClause=[updateClause,sprintf(' cluster=%d, classified=%d',sap.data(sap.pm.cluster_index_in_data(1),kk),sap.data(sap.pm.cluster_index_in_data(2),kk))];
            %             end
%             updateClause=updateClause(1:end-1);% to remove the last ','.
            exec(conn,[updateClause,whereClause]);
            %             update(conn,sap.SAPtablename,sap.pm.cluster_types,sap.data(sap.pm.cluster_index_in_data,kk),whereClause);
            waitbar(kk/sap.pm.loaded_N,h);
        end
        commit(conn);
        %         set(conn,'AutoCommit','on');
        close(h);
        close(conn);
    case 'delete_song_from_database'
 
        conn = database('mysql', '', '');
        same_serial_index = strmatch(sap.pm.filename,sap.data_filename);
        serial_to_delete=unique(sap.data(sap.pm.serial_index,same_serial_index));
        if length(serial_to_delete)>1
            error('this song includes more than one serial number! cannot delete!');
        else
            
            ButtonName=questdlg('Do you really want to delete this song data from database?', ...
                'Question', ...
                'YES','NO','Cancel');
            
            if strmatch(ButtonName,'YES')
                delete_song_from_table=sprintf('DELETE FROM %s WHERE serial_number=%d;',...
                    sap.SAPtablename,serial_to_delete);
                exec(conn,delete_song_from_table);
%                 fprintf('Delete song %s from %s ...\n',sap.pm.filename,sap.SAPtablename);
                fprintf('%s\n',delete_song_from_table);
                %         close(h);
                
                ButtonName=questdlg('Do you also want to delete this song .wav file? (Note! this will permanently delete the file.)', ...
                    'Question', ...
                    'YES','NO','Cancel');
                if strmatch(ButtonName,'YES')
                    eval(sprintf('!rm %s',fullfile(sap.pm.sound_dir,sap.pm.filename)))
                    eval(sprintf('!rm %s',fullfile(sap.pm.feature_dir,strrep(sap.pm.filename,'.wav','.mat'))))
                end
                
            else
                fprintf('Canceled;')
            end
        end
        close(conn);
    case 'set_teacher_onoff'
        sap.gpm.do_show_teacher=get(gcbo,'Value');
        feval(mfilename,'redraw_clusters');
    case {'set_stimlated_cluster_onoff'}
        
        get(gcbo,'Value');
        feval(mfilename,'redraw_clusters');
        
    case 'set_spectrum_contrast'
        val=get(sap.gph.ui_spectrum_contrast,'Value');
%         sap.pm.sonogram_caxis_cutooff_min=0.01;
%         sap.pm.sonogram_caxis_cutooff_max=0.1;
%         sap.pm.sonogram_caxis_cutooff=0.06;     
        dval=sap.pm.sonogram_caxis_cutooff_max-sap.pm.sonogram_caxis_cutooff_min;
        sap.pm.sonogram_caxis_cutooff=dval*(1-tanh(10*val))+sap.pm.sonogram_caxis_cutooff_min;
%          set(sap.gph.sonogramAxes,'CLim',sap.pm.sonogram_caxis_cutooff*[-1 1]*sap.gpm.max_spec);
        set(sap.gph.sonogramAxes,'CLim',sap.pm.sonogram_caxis_cutooff*[-1 1]);
 
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
        delete_handles=setdiff(get(sap.gph.sonogramAxes,'Children'),[sap.gph.sonogramImg,sap.gph.sonogram_feature_plots(:)']);
        delete(delete_handles);
%         try delete(sap.gph.syllable_label);end
%         try delete(sap.gph.syllable_label2);end
%         try delete(sap.gph.syllable_label3);end
%         try delete(sap.gph.wavefile_text);end
        
         feval(mfilename,'reload_converting_matrix');
         
        switch lower(opt)
            case 'show_syllable'
                % we will not show the teacher data here,
                axes(sap.gph.ax(1));
                [xposi,yposi]=ginput(1);
                % here syllables are searched through only in the
                % to-be-analyzed data, not the teacher data.
                local_show_bools=sap.pm.show_column_bools; %&~sap.data(sap.pm.is_teacher_index,:);
                datatmp=sap.data(:,local_show_bools);
                if isempty(datatmp)
                    error('No data remains!');
                end
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
                if sap.pm.show_sonogram_index>length(sap.data_filename)
                    error('Teacher data cannot be called.');
                end
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
                
                % determine which file to read
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
%                 sap.pm.show_sonogram_index=[];
                
                set(sap.gph.ui_select_song_by_filename,'Value',val);
               
                % now, find the notes that belongs to this file.
                same_serial_index = strmatch(sap.pm.filename,sap.data_filename);
                index_sounds=sap.data(sap.pm.classified_cluster_index,same_serial_index);
                str2=sap.pm.converting_matrix(index_sounds+1);
                str2=[str2{:}];
                 str2=filter_syllable_structure(str2,sap.pm.replace_chart,{});
                
                search_pattern=sprintf('iii');
                search_pattern2=get(sap.pm.current_syllable_branch_txt,'String');
                for ss=1:length(search_pattern2)
                    search_pattern=[search_pattern,sprintf('%s+',search_pattern2(ss))];
                end
                Num_Ns=strfind(str2,'N');
                str2=strrep(str2,'N','');
%                 search_pattern
               fprintf('look for %s in %s\n',search_pattern,str2);
               ending_index=regexp(str2,search_pattern,'end');
               Num_Ns_in_str2=length(intersect(Num_Ns,[1:ending_index]));
               fprintf('and detected %s\n', str2(1:ending_index+Num_Ns_in_str2));
               
%                  index=regexp(str2,remaining_notes)
%                 strfind();
                
%                 sap.pm.show_sonogram_index=show_index_local(sap.pm.minind);
                sap.pm.show_sonogram_index=same_serial_index(ending_index);
                sap.pm.do_highlight_note=1;
                
%         disp('!')
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
        sap.gpm.max_spec=max(max(m_spec_deriv));
        min_spec=min(min(m_spec_deriv));
        
        t=linspace(0,length(sap.pm.song)/sap.pm.Fsong,size(m_spec_deriv,1));
        freqind=0:(size(m_spec_deriv,2)-1);
        f=freqind*sap.pm.Fsong/1024;
        set(sap.gph.sonogramImg,'XData',t,'YData',f,'CData',m_spec_deriv');
        colormap(sap.gph.sonogramAxes,gray);
%         cutoff=0.006;
        cutoff=sap.pm.sonogram_caxis_cutooff;
%         set(sap.gph.sonogramAxes,'CLim',cutoff*[-1 1]*sap.gpm.max_spec);
         set(sap.gph.sonogramAxes,'CLim',cutoff*[-1 1]);
        
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
try             sound(sap.pm.song(ind)/(6*std(sap.pm.song)),sap.pm.Fsong);
end
        end
%         feval(mfilename,'init_feature_button');
   
        feval(mfilename,'draw_bout_durationbar');
        feval(mfilename,'show_classification');
%         [onset,durations,motif_counts]=feval(mfilename,'return_bout_onset_duration_nmotif',sap.pm.filename,sap.pm.ISI_thresh);
     
        
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
        ind = ceil(sap.pm.Fsong*sap.data(sap.pm.start_on_index,sap.pm.show_sonogram_index)/1000)+[1:ceil(sap.pm.Fsong*sap.data(sap.pm.duration_index,sap.pm.show_sonogram_index)/1000)-1];
        
        sound(sap.pm.song(ind)/(6*std(sap.pm.song)),sap.pm.Fsong);
    case 'draw_bout_durationbar'
        if nargin>=2
            axes_handle=varargin{1};
            t_offset=varargin{2};
            ylim_axes=get(axes_handle,'YLim');
            remove_previous_labels=0;
            line_width=10;
        else
            axes_handle=sap.gph.sonogramAxes;
            t_offset=0;
            remove_previous_labels=1;
            line_width=5;
        end
        
        axes(axes_handle);
%         sap.pm.filename
        sap.pm.same_serial_index = strmatch(sap.pm.filename,sap.data_filename);
        
        if (remove_previous_labels)
            try delete(sap.gph.bout_bar);end
        end
        
        [onset,durations,motif_counts]=feval(mfilename,'return_bout_onset_duration_nmotif',sap.pm.filename,sap.pm.ISI_thresh);
        for ii=1:length(onset)
            fprintf('onsets=%6.4gms,\t durations=%6.4gms, \t (%2d motifs)\n',onset(ii),durations(ii),motif_counts(ii));
        end
        sap.gph.bout_bar=[];
        for ii=1:length(onset)
          x = [onset(ii),onset(ii)+durations(ii)]/1000;        
            sap.gph.bout_bar(ii)=line(x-t_offset,[0 0],'Color','c','LineWidth',line_width);
        end   
        
    case 'show_classification'
        
        if nargin>=2
            axes_handle=varargin{1};
            t_offset=varargin{2};
            ylim_axes=get(axes_handle,'YLim');
            show_label_char=1;  % show alphabetical labels
            show_label_num =0;  % show numerical labels
            label_char_offset= max(ylim_axes)-diff(ylim_axes)*0.1;
            label_num_offset= [];
            remove_previous_labels=0;
            line_width=6;
            font_size=18;
            show_white_bar=1;
        else
            axes_handle=sap.gph.sonogramAxes;
            t_offset=0;
            show_label_char=1;  % show alphabetical labels
            show_label_num =1;  % show numerical labels
            ylim_axes=get(axes_handle,'YLim');
            label_offset= max(ylim_axes)-diff(ylim_axes)*0.1;
            label_char_offset=-0.2*diff(ylim_axes);
            label_num_offset =-0.15*diff(ylim_axes);
            remove_previous_labels=1;
            line_width=3;
            font_size=12;
            show_white_bar=0;
        end
        
        axes(axes_handle);
        sap.pm.same_serial_index = strmatch(sap.pm.filename,sap.data_filename);
        
        if (remove_previous_labels)
            try delete(sap.gph.syllable_label);end
            try delete(sap.gph.syllable_label2);end
            try delete(sap.gph.syllable_label3);end
            try delete(sap.gph.syllable_line);end
        end
        sap.gph.syllable_label=zeros(1,length(sap.pm.same_serial_index));
        sap.gph.syllable_label2=zeros(1,length(sap.pm.same_serial_index));
        sap.gph.syllable_label3=zeros(1,length(sap.pm.same_serial_index));
        sap.gph.syllable_line =zeros(1,length(sap.pm.same_serial_index));
        
%         feval(mfilename,'reload_converting_matrix');
        
        
        which_cluster_type=get(get(sap.gph.ui_cluster_type_select,'selectedobject'),'UserData');
        index_sounds=sap.data(which_cluster_type,sap.pm.same_serial_index);
        str2=sap.pm.converting_matrix(index_sounds+1);
        str2=[str2{:}];
        
%         current_dir=pwd;
%         cd(sap.pm.sound_dir);
%         eval('analysis_parameters'); % load converting matrix, etc.
%         cd(current_dir);
        
        str2=filter_syllable_structure(str2,sap.pm.replace_chart,{});
        if (show_white_bar) white_bar_h=draw_rectangles(min(xlim),max(ylim)-0.17*diff(ylim),diff(xlim),0.17*diff(ylim),...
                'FaceAlpha',1,'FaceColor',[1 1 1]);
        end
        
        for ii=1:length(sap.pm.same_serial_index)
            x = [sap.data(sap.pm.start_on_index,sap.pm.same_serial_index(ii)),...
                sap.data(sap.pm.start_on_index,...
                sap.pm.same_serial_index(ii))+sap.data(sap.pm.duration_index,sap.pm.same_serial_index(ii))]/1000;
            sap.gph.syllable_line(ii)=line(x-t_offset,[0 0],'Color','m','LineWidth',line_width,...
                'ButtonDownFcn','ClassifySAP_sub_routines_04(''return_feature_2D_posi'')',...
                'UserData',sap.pm.same_serial_index(ii));
            cluster=sap.data(which_cluster_type,sap.pm.same_serial_index(ii));
            
            cluster_str=sap.pm.converting_matrix{cluster+1};
          
            if (show_label_num)
                sap.gph.syllable_label(ii)=text(mean(x)-t_offset,label_num_offset,num2str(cluster),...
                    'Color',sap.pm.CS(cluster+1,:),'FontSize',font_size);
                set(sap.gph.syllable_label(ii),...
                    'ButtonDownFcn','ClassifySAP_sub_routines_04(''manual_change_cluster'')',...
                    'UserData',[sap.pm.same_serial_index(ii),ii]);
            end
             if (show_label_char)
            sap.gph.syllable_label2(ii)=text(mean(x)-t_offset,label_char_offset,2,cluster_str,...
                'Color',sap.pm.CS(cluster+1,:),'FontSize',font_size);
             end
             
                  
        
            %             sap.gph.syllable_label3(ii)=text(mean(x),-0.25*diff(ylim),str2(ii),...
            %                 'Color',sap.pm.CS(cluster+1,:));
            
         
            
        end
    case 'open_analysis_parameters'
         current_dir=pwd;
        cd(sap.pm.sound_dir);
        if FileExists('analysis_parameters.m'); % load converting matrix, etc.
            edit('analysis_parameters');
        else
            fprintf('analysis parameter does not exists in %s...\n Use default one.',sap.pm.sound_dir);
            copy_txt=sprintf('!cp %s %s',which('ClassifySAP_Default_analysis_parameters.m'),fullfile(sap.pm.sound_dir,'analysis_parameters.m'));
            eval(copy_txt);
%             eval('analysis_parameters');
%             feval(mfilename,'reload_analysis_parameters');
            edit('analysis_parameters'); 
        end
        cd(current_dir);
        
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
        sap.pm.replace_chart    =replace_chart;
        sap.pm.replace_repeats_chart=replace_repeats_chart;
        
        replace_chart_in_index=sap.pm.replace_chart;
        for ii=1:length(sap.pm.converting_matrix)
            replace_chart_in_index=strrep(replace_chart_in_index,...
                sap.pm.converting_matrix{ii},num2str(ii-1));
        end
        sap.pm.replace_chart_in_index=replace_chart_in_index;
    
    case 'chk_xaxis_button'
        sap.pm.xname=get(get(sap.gph.ui_xbuttonG,'selectedobject'),'String');
        feval(mfilename,'redraw_clusters');
         feval(mfilename,'redraw');
    case 'chk_yaxis_button'
        sap.pm.yname=get(get(sap.gph.ui_ybuttonG,'selectedobject'),'String');
        feval(mfilename,'redraw_clusters');
        feval(mfilename,'redraw');
    case {'redraw_clusters','redraw_clusters_in_princomp'}
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
        
        if get(sap.gph.ui_Stimlated_cluster_ONOFF,'Value') % show stimulated data
            %             sap.pm.show_column_bools =sap.pm.show_column_bools&(sap.data(sap.pm.is_teacher_index,:));
            stimulated_bools =sap.pm.show_column_bools&sap.data(sap.pm.stimulated_index,:);
            if sap.gpm.do_show_teacher % show all the data
                %       
            else % do not show the teacher data
                stimulated_bools =stimulated_bools&~(sap.data(sap.pm.is_teacher_index,:));
            end
        else % do not show the stimulated data
            stimulated_bools=false(1,size(sap.data,2));
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
                
                datatmp=sap.data(:,show_index&stimulated_bools);
                h=plot(datatmp(sap.pm.xind,:),datatmp(sap.pm.yind,:),'ko','MarkerSize',6);hold on;
               
                set(h,'MarkerFaceColor','None','MarkerEdgeColor',CSnow);
                
            end
        end
                axis([xlim_now ylim_now]);
        xlabel(strrep(sap.pm.xname,'_','\_'));ylabel(strrep(sap.pm.yname,'_','\_'));
        
        try
            sap.gph.selected_note_posi=plot(sap.data(sap.pm.xind,sap.gph.selected_note_index),...
                sap.data(sap.pm.yind,sap.gph.selected_note_index),'ro','MarkerSize',5);
        catch
            %             disp('!')
        end
        feval(mfilename,'update_cluster_info');
        
    case 'update_cluster_info'
        for ii=[0:8]
            evaltxt = sprintf('set(sap.gph.ui_cluster%d, ''String'',[''cluster'' num2str(%d) '':(%d)'']);',...
                mod(ii,9),mod(ii,9),length(find(sap.data(sap.pm.cluster_index,:)==mod(ii,9))));
            eval(evaltxt);
        end
        ii=9; % for noise.
        evaltxt = sprintf('set(sap.gph.ui_cluster%d,''String'',[''noise'' num2str(%d) '':(%d)'']);',...
            ii,ii,length(find(sap.data(sap.pm.cluster_index,:)==ii)));
        eval(evaltxt);
        
    case 'redraw'
        axis tight;
    case 'load_feature'
        
        
        sap.pm.feature_loadname=sap.pm.filename;
        
        if isempty(strfind(sap.pm.feature_loadname,'.wav'))
            feature_filename=fullfile(sap.pm.feature_dir,[sap.pm.feature_loadname,'.dat']);
            sap.pm.feature_data_is_mfile=0;
        else
            feature_filename=fullfile(sap.pm.feature_dir,strrep(sap.pm.feature_loadname,'.wav','.dat'));
            if ~FileExists(feature_filename)
                feature_filename=fullfile(sap.pm.feature_dir,strrep(sap.pm.feature_loadname,'.wav','.mat'));
                if ~FileExists(feature_filename)
                    error('%s (neigher .dat  or .m) does not exist!',feature_filename);
                else
                    sap.pm.feature_data_is_mfile=1;
                end
            end
        end
        
        if (sap.pm.feature_data_is_mfile)
            fprintf('loading feature mfile\n')
            load(feature_filename,'features');
            sap.pm.feature=features;
            rename_tables={ ...
                'amplitude',    'm_amplitude'; ...
                'meanfreq',     'm_frequency';...
                'pitch',        'm_Pitch';...
                'entropy',      'm_Entropy';...
                'pgood',        'm_PitchGoodness'};
            for ii=1:size(rename_tables,1)
                sap.pm.feature.(rename_tables{ii,1})=sap.pm.feature.(rename_tables{ii,2});
                sap.pm.feature=rmfield(sap.pm.feature,(rename_tables{ii,2}));
            end
            sap.pm.feature.t=sap.pm.feature.specT;
        else
             fprintf('loading feature binary file\n')
            sap.pm.feature=read_sap_feature(feature_filename);
            
        dt=9.27/2/1000;
        sap.pm.feature.t=linspace(dt,length(sap.pm.song)/44100-dt,length(sap.pm.feature.amplitude));
        end
        
        
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
%     case 'init_feature_vector'
%         % calculate the mean feature vector of each syllables.
%         % duration, mean_pitch, mean_FM,mean_entropy,mean_gpitch.
%         
%         sap.pm.feature_vector=zeros(length(sap.pm.mean_feature_index),9);
%         for ii=1:9
%             index = (sap.data(sap.pm.cluster_index,:)==mod(ii,9));
%             tmp=sap.data(sap.pm.mean_feature_index,index);
%             sap.pm.feature_vector(:,ii)=mean(tmp,2);
%         end
%         
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
                                'ButtonDownFcn','ClassifySAP_sub_routines_04(''manual_change_cluster'')',...
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
                                'ButtonDownFcn','ClassifySAP_sub_routines_04(''manual_change_cluster'')',...
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
        %         unique_serials=unique(sap.data(2,:));
        
        try
            sap.pm.replace_chart_in_index;
        catch
            replace_chart_in_index=sap.pm.replace_chart;
            for ii=1:length(sap.pm.converting_matrix)
                replace_chart_in_index=strrep(replace_chart_in_index,...
                    sap.pm.converting_matrix{ii},num2str(ii-1));
            end
            sap.pm.replace_chart_in_index=replace_chart_in_index;
        end
        
        sap.pm.trans_matrix=zeros(10);
        sap.pm.trans_matrix_serials=cell(10);
%         val=get(sap.gph.ui_select_song_by_filename,'Value');
        str=get(sap.gph.ui_select_song_by_filename,'String');
%        sap.pm.filename=str{val};
       
        for ii=1:length(str)
            [onset,durations,motif_counts]=feval(mfilename,'return_bout_onset_duration_nmotif',str{ii},sap.pm.ISI_thresh);
            sap.pm.same_serial_index=strmatch(str{ii},sap.data_filename);
            
%             sap.pm.same_serial_index = find(sap.data(sap.pm.serial_index,:)==unique_serials(ii));
            which_cluster_type=get(get(sap.gph.ui_cluster_type_select,'selectedobject'),'UserData');
            
            tmp=sap.data(which_cluster_type,sap.pm.same_serial_index);
            tmp(find(tmp==0))=9; % unclassified one is temporally classified as noise.
            tmp=filter_syllable_structure(sprintf('%d',tmp),sap.pm.replace_chart_in_index,{});
            
            tmp2=zeros(1,length(tmp));
            for tt=1:length(tmp)
                tmp2(tt)=str2double(tmp(tt));
            end
           
%             fprintf('%s->%s\n',tmp,sprintf('%d',tmp2));
              tmp=tmp2;
            if isempty(tmp), continue;end
            for jj=1:length(sap.pm.same_serial_index)
                syllable_start=sap.data(sap.pm.start_on_index,sap.pm.same_serial_index(jj));
                
                
                % if this syllable is too short and not classified as a
                % song, skip it.               
                is_within_bout=any((syllable_start>=onset).*(syllable_start<(onset+durations)))&(motif_counts>2);
                if ~is_within_bout,   
%                     if (ii==7),
%                         onset,
%                         durations,
%                        
%                         fprintf('%d-th syllable at t=%g skipped!\n',jj,syllable_start)
%                         continue;    
%                     else
%                         continue;
%                     end
                    continue;          
                    
                end
              
               
                % if last syllable, consider that as the end of the song.
                if (jj==length(sap.pm.same_serial_index))
                    ISI=inf;
                else
                    ISI=sap.data(sap.pm.start_on_index,sap.pm.same_serial_index(jj+1))-sap.data(sap.pm.start_on_index,sap.pm.same_serial_index(jj))-...
                        sap.data(sap.pm.duration_index,sap.pm.same_serial_index(jj));
                end
                
                if ISI<sap.pm.ISI_thresh % if note-note interval is more than 200ms, define the end of the song.
                    if (jj==length(sap.pm.same_serial_index))
                        sap.pm.trans_matrix(tmp(jj),10)=ceil(sap.pm.trans_matrix(tmp(jj),10)+1);
                        sap.pm.trans_matrix_serials{tmp(jj),10}=[sap.pm.trans_matrix_serials{tmp(jj),10},...
                            sap.pm.same_serial_index(jj)];
                    else
                        sap.pm.trans_matrix(tmp(jj),tmp(jj+1))=ceil(sap.pm.trans_matrix(tmp(jj),tmp(jj+1))+1);
                        sap.pm.trans_matrix_serials{tmp(jj),tmp(jj+1)}=[sap.pm.trans_matrix_serials{tmp(jj),tmp(jj+1)},...
                            sap.pm.same_serial_index(jj)];
                    end
                else
                    sap.pm.trans_matrix(tmp(jj),10)=ceil(sap.pm.trans_matrix(tmp(jj),10)+1);
                    sap.pm.trans_matrix_serials{tmp(jj),10}=[sap.pm.trans_matrix_serials{tmp(jj),10}, ...
                        sap.pm.same_serial_index(jj)];
                end
            end
            
            if(is_within_bout)
                sap.pm.trans_matrix(tmp(end),10)=ceil(sap.pm.trans_matrix(tmp(end),10)+1);
                sap.pm.trans_matrix_serials{tmp(end),10}=[sap.pm.trans_matrix_serials{tmp(end),10}, sap.pm.same_serial_index(end)];
            end
        end
        
        sumP=sum( sap.pm.trans_matrix,2);
        sap.pm.Ntrans_matrix=sap.pm.trans_matrix./repmat(sumP,1,size(sap.pm.trans_matrix,2));
       
        sap.pm.Nrepeat_prob=diag(sap.pm.Ntrans_matrix);
        for ii=1:size(sap.pm.Ntrans_matrix)
            sap.pm.Ntrans_matrix(ii,ii)=0;
        end
        sap.pm.Ntrans_matrix=sap.pm.Ntrans_matrix./repmat(sum(sap.pm.Ntrans_matrix,2),1,size(sap.pm.trans_matrix,2));
        varargout{1}=sap.pm.Ntrans_matrix;
        
    case 'show_trans_matrix'
        figure(2);setPaperSize([7,6],10);clf;
        
        feval(mfilename,'parse_autoclassified_notes');
        sap.gph.ui_Transmat_panel = uipanel('visible','on','Position',[0.05 0.05 .85 .85],'BackGroundColor','white','BorderWidth',0);
        sap.gph.trans_mat_axes=axes('Position',[.1 0 .8 .7],'Parent',sap.gph.ui_Transmat_panel);
       
      
        show_index=[];
        for ii=1:9
        num_teacher=length(find(sap.data(sap.pm.cluster_index,:)==ii));
        if (num_teacher>0)
            show_index=[show_index,ii];
        end
        end
        show_index_x=unique([show_index,9,10]);
        show_index=setdiff(show_index,9); % remove noise part.
        show_index_y=show_index;
        sap.pm.show_index_y_for_sylltrans=show_index_y;
        sap.pm.show_index_x_for_sylltrans=show_index_x;
        
        tmp=sap.pm.converting_matrix;
        labels=[tmp(2:end-1),'N','End'];
        labels_X=labels(show_index_x);
        labels_Y=labels(show_index_y);
        sap.pm.Ntrans_matrix=sap.pm.Ntrans_matrix(show_index_y,show_index_x);
        %         sap.pm.trans_matrix_serials={sap.pm.trans_matrix_serials{show_index_y,show_index_x};
        x=.5:1:10.5;
        sap.gph.trans_mat_IMG=  imagesc(sap.pm.Ntrans_matrix);
%         sap.gph.trans_mat_IMG=  surf(sap.pm.Ntrans_matrix);
        
       %         sap.gph.trans_mat_IMG=imagesc(sap.pm.Ntrans_matrix(show_index_y,show_index_x)); x=.5:1:10.5;
%         sap.gph.trans_mat_IMG=surf(sap.pm.Ntrans_matrix(show_index_y,show_index_x));  x=0:1:10;view(0,90);
%         axis([0 show_index_x(end)+1 0 show_index_y(end)+1])
        xlabel('Following syllable');
        ylabel('Preceding syllable')
%         x=.5:1:10.5;
        [X,Y]=meshgrid(x,x);
        line(X,Y,ones(size(X)),'Color',[1 1 1]);
        line(X',Y',ones(size(X')),'Color',[1 1 1]);
        load coldfire2;
        colormap(sap.gph.trans_mat_axes,coldfire2);
        set(get(sap.gph.trans_mat_IMG,'Parent'),'XAxisLocation','top','XTick',1:length(labels_X),'YTick',1:length(labels_Y));
        set(get(sap.gph.trans_mat_IMG,'Parent'),'XTickLabel',labels_X,'YTickLabel',labels_Y);
        set(gca,'YDir','Reverse')
 
%         h=surf(X,Y,ones(length(x)));
%         set(h,'FaceAlpha',0);
        p=sap.pm.Ntrans_matrix; zero_ind=find(p==0);
        tmp=-p.*log(p); tmp(zero_ind)=0;
        sap.pm.Ntrans_entropy=sum(tmp,2);
        Ntrans_matrix=sap.pm.Ntrans_matrix;
        Ntrans_entropy=sap.pm.Ntrans_entropy;
        cd_now=pwd;
        cd(sap.pm.sound_dir);
        fprintf('transition matrix is saved in %s\n',fullfile(sap.pm.sound_dir,[sap.SAPtablename,'_transMatrix.mat']))
        save([sap.SAPtablename,'_transMatrix.mat'],...
            'Ntrans_matrix','Ntrans_entropy','show_index')
        cd(cd_now);
%         set(sap.gph.trans_mat_axes,'XAxisLocation','top',...
%             'XTick',[1:9],'XTickLabel',[1:9],'YTick',[1:9],'YTickLabel',[1:9]);
        
        uicontrol('Style', 'pushbutton','String', 'show syllable','Parent',sap.gph.ui_Transmat_panel,...
            'Unit','Normalized','Position', [0 1 .2 .1],...
            'Callback', 'ClassifySAP_sub_routines_04(''choose_syllable_transition'');');
        sap.ui.decrement_transit_syllable=uicontrol('Style', 'pushbutton','String', '<','Parent',sap.gph.ui_Transmat_panel,...
            'Unit','Normalized','Position', [.2 1 .15 .1],...
            'Callback', 'ClassifySAP_sub_routines_04(''move_syllable_transition'',-1);');
        sap.ui.edit_transit_syllable=uicontrol('Style', 'edit','String', '1','Parent',sap.gph.ui_Transmat_panel,...
            'Unit','Normalized','Position', [.35 1 .15 .1],...
            'Callback', 'global sap; n=str2num(get(sap.ui.edit_transit_syllable,''String''));ClassifySAP_sub_routines_04(''move_syllable_transition'',n);');
        sap.ui.increment_transit_syllable=uicontrol('Style', 'pushbutton','String', '>','Parent',sap.gph.ui_Transmat_panel,...
            'Unit','Normalized','Position', [.5 1 .15 .1],...
            'Callback', 'ClassifySAP_sub_routines_04(''move_syllable_transition'',+1);');
        sap.ui.maxN_transit_syllable=uicontrol('Style', 'Text','String', 'MaxN','Parent',sap.gph.ui_Transmat_panel,...
            'Unit','Normalized','Position', [.65 1 .15 .1]);
        
        savename=fullfile(sap.pm.feature_dir,['TransMat_',sap.SAPtablename])
        print(gcf,'-dill','-noui',[savename,'_coldfire2.ai']);
        print(gcf,'-dpng','-noui',[savename,'_coldfire2.png']);

    case 'choose_syllable_transition'
        
        axes(sap.gph.trans_mat_axes);
        figure(2);
        [xposi,yposi]=ginput(1);
        xposi=round(xposi);                 yposi=round(yposi);
        txt=sprintf('%d -> %d',yposi,xposi);
        fprintf('%s\n',txt);
        sap.pm.showing_trans_matrix_serials=sap.pm.trans_matrix_serials{sap.pm.show_index_y_for_sylltrans(yposi),sap.pm.show_index_x_for_sylltrans(xposi)};
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
        
%         fprintf('!')
        sap.pm.show_sonogram_index=sap.gph.selected_note_index;
        feval(mfilename,'play_syllable');
        
    case 'manual_change_cluster'
        tmp=get(gcbo,'UserData');
%         fprintf('This cluster (%dth note) has neighbors:',tmp(2));
%         fprintf('%d ',tmp(3:end));fprintf('\n');
        
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
            'Callback', 'ClassifySAP_sub_routines_04(''enter_cluster_number'');');
        waitfor(sap.gph.uieditnow);
        
    case 'enter_cluster_number'
        
        str=get(sap.gph.uieditnow,'String');
        if ~ischar(str)
            delete(sap.gph.uieditnow);
            error('The cluster number must be a numeric!');
        end
        Userdata=get(sap.gph.uieditnow,'UserData');
        index=Userdata(1);
        set(sap.gph.syllable_label(sap.gph.syllable_label_tag),'String',str,'FontWeight','bold');
        
%         which_cluster_type=get(get(sap.gph.ui_cluster_type_select,'selectedobject'),'UserData');
        which_cluster_type=sap.pm.cluster_index;
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
%             selection=sprintf('in ')
%             for ii=1:length(sap.pm.cluster_types)
%                 selection=[selection sprintf('%s(%d),',sap.pm.cluster_types{ii},ii)];
%             end
%             prompt={selection};
%             
%             %             prompt={'Then,in SAP(1),Mahr(2),EM(3),Manual(4)?'};
%             name='Register in which database';
%             numlines=1;
%             defaultanswer={'1'};
%             
%             which_database=inputdlg(prompt,name,numlines,defaultanswer);
%             num=str2num(which_database{1});
%             switch num
%                 case 1
%                     which_database=sap.pm.cluster_index;
%                 case 2
%                     which_database=sap.pm.classified_cluster_index;
%                     %                 case 3
%                     %                     which_database=sap.pm.EM_cluster_index;
%                     %                 case 4
%                     %                     which_database=sap.pm.cluster_index;
%                 otherwise
%                     error('Unknown option!');
%             end
            
            
            for ii=1:length(sap.gph.syllable_label)
                set(sap.gph.syllable_label(ii),'String','9');
                index=get(sap.gph.syllable_label(ii),'UserData');
                sap.data(sap.pm.cluster_index,index(1))=9; % register as a noise
                sap.data(sap.pm.classified_cluster_index,index(1))=9; % register as a noise
%                 sap.data(which_database,index(1))=9; % register as a noise
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
        dt_waitbar=0;
        for ii=1:length(str)
%             conn_txt=sprintf('select distinct serial_number from %s where file_name like ''%s''',...
%                 sap.SAPtablename,str{ii});
%             curs = exec(conn, conn_txt);
%             curs = fetch(curs,10);
%             sap.pm.serial=curs.data';
            %             sap.pm.serial
%             if isnumeric(sap.pm.serial)
%                 same_serial_index=find(sap.data(sap.pm.serial_index,:)==sap.pm.serial);
%             else
%                 continue;
%             end
            same_serial_index=strmatch(str{ii},sap.data_filename);
            sap.syllables(ii).note='';
            
            for jj=1:length(same_serial_index)
                if jj==length(same_serial_index)
                    ISI=inf;
                else
                    ISI=sap.data(sap.pm.start_on_index,same_serial_index(jj+1))-sap.data(sap.pm.start_on_index,same_serial_index(jj))-...
                    sap.data(sap.pm.duration_index,same_serial_index(jj));
                end
                if ISI<200 % if note-note interval is more than 200ms, define the end of the song.
                    
                    % because we insert unclassified note as the first
                    % class, we need to +1 for the index to neglect them in this stage.
%                     [which_cluster,same_serial_index(jj)]
                    cluster= sap.pm.converting_matrix{sap.data(which_cluster_type,same_serial_index(jj))+1};
                    sap.syllables(ii).note=[sap.syllables(ii).note, cluster];
                else
                    cluster= sap.pm.converting_matrix{sap.data(which_cluster_type,same_serial_index(jj))+1};
                    sap.syllables(ii).note=[sap.syllables(ii).note, sprintf('%s\n',cluster)];
                end
            end
            
            
            %             sap.syllables(ii).note=sap.data(which_cluster_type,same_serial_index);
            sap.syllables(ii).filename=str{ii};
            if (ii/length(str)>dt_waitbar)
                waitbar(ii/length(str),h);
                dt_waitbar=dt_waitbar+0.1;
            end
        end
        
        close(h);      
% close(curs);close(conn);
  case {'export_bout_durations'}
        
%       sap.pm.ISI_thresh=200;
        val=get(sap.gph.ui_select_song_by_filename,'Value');
        str=get(sap.gph.ui_select_song_by_filename,'String');
        sap.pm.filename=str{val};
        
        conn = database('mysql', '', '');
        setdbprefs('DataReturnFormat','numeric')
        
        which_cluster_type=get(get(sap.gph.ui_cluster_type_select,'selectedobject'),'UserData');
        %         unique_serials=unique(sap.data(sap.pm.serial_index,:))
        %         rmfield(sap,'syllables');
        h = waitbar(0,'Exporting syllables from each song file...');
        dt_waitbar=0;
        kk=1;
        sap.bout_durations=[];
        sap.N_motif_counts=[];
       
        for ii=1:length(str)
             [onset,durations,motif_counts]=feval(mfilename,'return_bout_onset_duration_nmotif',str{ii},sap.pm.ISI_thresh);
            if ~isempty(onset) 
                ind=find(durations>300);
                motif_counts=motif_counts(ind);
                durations=durations(ind);
             sap.N_motif_counts=[sap.N_motif_counts,motif_counts];
             sap.bout_durations=[sap.bout_durations, durations];
            end
%             same_serial_index=strmatch(str{ii},sap.data_filename);
%     
%             if isempty(same_serial_index)
%                 continue;
%             end
%             motif_counts=1;
%             onset=sap.data(sap.pm.start_on_index,same_serial_index(1));
%             
%             for jj=1:length(same_serial_index)
%               
%                 if (jj==length(same_serial_index))
%                     ISI=inf;
%                 else
%                     ISI=sap.data(sap.pm.start_on_index,same_serial_index(jj+1))-...
%                         sap.data(sap.pm.start_on_index,same_serial_index(jj))-...
%                         sap.data(sap.pm.duration_index,same_serial_index(jj));
%                 end
%                 
%                 if (ISI<sap.pm.ISI_thresh)% if note-note interval is more than 200ms, define the end of the song.
%                     
%                     % song continues;    
%                      motif_counts=ceil(motif_counts+1);  
%                     
%                 else
%                     if motif_counts<=1, % single noise or call, reset counter.
%                         motif_counts=0;
%                         onset=sap.data(sap.pm.start_on_index,same_serial_index(jj));
%                         continue;
%                     else
%                         sap.N_motif_counts(kk)=motif_counts;
%                         sap.bout_durations(kk)=-onset+...
%                             sap.data(sap.pm.start_on_index,same_serial_index(jj))+sap.data(sap.pm.duration_index,same_serial_index(jj));
%                         kk=ceil(kk+1);
%                         if (jj==length(same_serial_index))
%                             onset=inf;
%                             motif_counts=inf;
%                         else
%                             onset=sap.data(sap.pm.start_on_index,same_serial_index(jj+1));
%                             motif_counts=0;
%                         end
%                     end
%                  
%                 end
%             end
            
            
            %             sap.syllables(ii).note=sap.data(which_cluster_type,same_serial_index);
%             sap.syllables(ii).filename=str{ii};
            if (ii/length(str)>dt_waitbar)
                waitbar(ii/length(str),h);
                dt_waitbar=dt_waitbar+0.1;
            end
        end
        
        close(h);      
% close(curs);close(conn);

        figure(40);clf;
        
         savename=sprintf('Song_Motif_hist_ISIthresh=%d',sap.pm.ISI_thresh);
        savename=fullfile(sap.pm.feature_dir, savename);
         bout_duration=sap.bout_durations;
        N_motif_counts = sap.N_motif_counts;
        
        
        subplot(2,1,1);
        hist(sap.N_motif_counts,[0:1:51]);
        axis([0 51 ylim]);
        xlabel('# of elements in one bout');
        ylabel('frequency')
        title(savename,'FontSize',8);
        subplot(2,1,2);
        hist(sap.bout_durations/1000,50);
        axis([0 7 ylim]);
        xlabel('bout duration [sec]');
        ylabel('# of bouts');
        
       
        save(savename,'bout_duration','N_motif_counts');
        print(gcf,'-depsc2',[savename,'.eps']);
        print(gcf,'-dill',[savename,'.ai']);
        print(gcf,'-dpng',[savename,'.png']);
    case 'return_bout_onset_duration_nmotif'
%         [onset,motif_counts,duration]=ClassifySAP_...(filename,sap.pm.ISI_thresh);
%       

          filename=varargin{1};
          ISI_thresh=varargin{2};
          
          onset=[];
          motif_counts=[];
          durations=[];
          
          same_serial_index=strmatch(filename,sap.data_filename);

          if isempty(same_serial_index) || (length(same_serial_index)==1)
              varargout{1}=onset;
              varargout{2}=durations;
              varargout{3}=motif_counts;
              return;
          end
            
          % at this point, there must be more than two syllables.
          
            original_ISIs = sap.data(sap.pm.start_on_index,same_serial_index(2:end))-...
                sap.data(sap.pm.start_on_index,same_serial_index(1:end-1))-...
                sap.data(sap.pm.duration_index,same_serial_index(1:end-1));
            ISIs=[inf,original_ISIs inf]; % because there is no sound before the start of the file
%             ISIs(end)=inf; %  because the last ISI is always the end of the song.
%             pause;
%             ISIs
            
            bout_inds=ISIs<ISI_thresh; % equals to [0, original_ISI<ISI_thresh, 0];
            d_bout_inds=sign(diff(bout_inds));
            bout_starts=find(d_bout_inds>0);
            bout_ends  =find(d_bout_inds<0);
            
            if isempty(bout_starts)
                varargout{1}=onset;
                varargout{2}=durations;
                varargout{3}=motif_counts;
                return;
            end
            
          
            try
                if (bout_starts(1)>bout_ends(1)) || (bout_starts(end)>bout_ends(end))
                    error('something is wrong!');
                end
            catch
                filename
                error('something is wrong!');
            end
            
            nMotifs=-bout_starts+bout_ends+1;
            
            start_index_to_consider=find(nMotifs>1);
            onset=sap.data(sap.pm.start_on_index,same_serial_index(bout_starts(start_index_to_consider)));
            durations= ...
                sap.data(sap.pm.start_on_index,same_serial_index(bout_ends(start_index_to_consider)))-...
                sap.data(sap.pm.start_on_index,same_serial_index(bout_starts(start_index_to_consider)))+...
                sap.data(sap.pm.duration_index,same_serial_index(bout_ends(start_index_to_consider)));
            motif_counts=nMotifs(start_index_to_consider);
%             motif_counts(end)=motif_counts(end)+1;
            
            varargout{1}=onset;
            varargout{2}=durations;
            varargout{3}=motif_counts;
            
            
    case 'show_syllable_tree'
        %         feval(mfilename,'export_syllable_transitions');
        %         str=sap.syllables(1).note;
        [sap.iii,sap.iii_labels]=Parse_Song_Structure_01p2('parse',{sap.syllables(:).note},mfilename);
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
        ClassifySAP_sub_routines_04('estimate_gaussian_mixture');
        
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
        for class=1:9
            train_label=(sap.data(sap.pm.cluster_index,train_index)'==class);
            
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
        
        fprintf('Neglect the below lines...\n')
        for class=1:9
            [predict_label, accuracy, dec_values] = svmpredict(randn(length(test_ind),1),  ...
                norm_data(:,test_ind)', sap.pm.model(class).param); % test the training data
            ind=find(predict_label==1);
            sap.data(sap.pm.classified_cluster_index,test_ind(ind))=class;
            ind=find(sap.data(sap.pm.cluster_index,train_index)==class);
            sap.data(sap.pm.classified_cluster_index,train_index(ind))=class;
        end
        ind=find(isnan(sap.data(sap.pm.classified_cluster_index,:)));
        sap.data(sap.pm.classified_cluster_index,ind)=0;
        
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
        
    case 'align_sonogram_plot'
        if nargin>=2
            detect_pattern=varargin{1};
        else
            prompt={'Enter the detection pattern (ex: iiia+b+c+*)',...
                'Enter the pattern to align (ex: iiia+)',...
                'Enter number of bouts to show'};
            name='Input for aligning song patterns';
            numlines=1;
            defaultanswer={'iiia+','iiia','3'};
            detect_pattern=inputdlg(prompt,name,numlines,defaultanswer);
            N=str2num(detect_pattern{3});
            align_pattern=detect_pattern{2};
            detect_pattern=detect_pattern{1};
            fprintf('detect_pattern=%s\nalign_pattern=%s,N=%d',detect_pattern,align_pattern,N);
            
            
            
        end
        
        sap.gph.amplitude_img_fig=figure(17);clf;
        set(sap.gph.amplitude_img_fig,'Name','Aligned Sonogram')
        pre_start=1000; % index
        post_start=5000;% index
        %         N=3;
        str=get(sap.gph.ui_select_song_by_filename,'String');
      
        if any(N>length(str))
            error('maximum number of bouts (%s) is %d!',detect_pattern,length(sap.syllable_tree_to_show_index));
        end
        %          rand_index=randperm(length(sap.syllable_tree_to_show_index));
        %          rand_index=sort(rand_index(1:N));
      
        if isscalar(N)
            max_N=N;
            rand_index=1:length(str);
        else
            max_N=length(N);
            rand_index=N;
        end
        str=str(rand_index);
        %          rand_index=1:length(sap.syllable_tree_to_show_index);
        jj=1;
         for val=1:length(str)
             % determine which file to read
             sap.pm.filename=str{val};
             set(sap.gph.ui_select_song_by_filename,'Value',rand_index(val));
             drawnow;
             % now find the note that matches detect_pattern.
%                fprintf('note=s%s ',sap.syllables(val).note);
               
                % now, find the notes that belongs to this file.
                same_serial_index = strmatch(sap.pm.filename,sap.data_filename);
                index_sounds=sap.data(sap.pm.classified_cluster_index,same_serial_index);
                str2=sap.pm.converting_matrix(index_sounds+1);
                str2=[str2{:}];
                str2=filter_syllable_structure(str2,sap.pm.replace_chart,{});
                search_pattern=strrep(align_pattern,'.','+');
         
%                 search_pattern
%                fprintf('look for %s in %s\n',search_pattern,str2);
               ending_index=regexp(str2,search_pattern,'end');
               fprintf('look for %s in %s\n',detect_pattern,str2);
               is_exist_this_pattern=~isempty(regexp(str2,detect_pattern,'once'));
               %                fprintf('and detected %s\n', str2(1:ending_index));
               %                  index=regexp(str2,remaining_notes)
               %                 strfind();
               
               if (is_exist_this_pattern)
                   %                 sap.pm.show_sonogram_index=show_index_local(sap.pm.minind);
                   sap.pm.show_sonogram_index=same_serial_index(ending_index);
                   onset_timing=unique(sap.data(sap.pm.start_on_index,sap.pm.show_sonogram_index)/1000);
                   if isempty(onset_timing), continue;end
                   onset_timing=onset_timing(1);
                   %                 fprintf('%s starts at %g sec\n',search_pattern,onset_timing);
                
                   txt=strrep(sprintf('wavfile: %s',sap.pm.filename),'_','\_');
                   [sap.pm.song,sap.pm.Fsong]=wavread(fullfile(sap.pm.sound_dir,sap.pm.filename));
                           
                   m_spec_deriv=sam_spectrum_deriv2(sap.pm.song,sap.pm.Fsong);
                   size(m_spec_deriv);
                   sap.gpm.max_spec=max(max(m_spec_deriv));
                   min_spec=min(min(m_spec_deriv));
                   
                   t=linspace(0,length(sap.pm.song)/sap.pm.Fsong,size(m_spec_deriv,1));
                   f=sap.pm.Fsong*(1:size(m_spec_deriv,2))*1000/1024;
                   
                   h(jj)=mysubplot(max_N,1,jj,1);
                   imagesc(t-onset_timing,f,m_spec_deriv');
                   
                   feval(mfilename,'draw_bout_durationbar',h(jj),onset_timing);
                   feval(mfilename,'show_classification',h(jj),onset_timing);
                   colormap gray;
                   cutoff=0.004;
%                    text(min(xlim)+diff(xlim)*.05,max(ylim)-diff(ylim)*.1,sprintf('trial=%d',val));
                   ylabel(sprintf('trial=%d',rand_index(val)));
                  
                   set(h(jj),'CLim',cutoff*[-1 1]*sap.gpm.max_spec,'YDir','Normal');
                   set(h(jj),'Color',[.5 .5 .5]);
                   if jj<max_N
                       if (jj==1)
                           title(strrep(sprintf('Spectrum_iii.%s_in_%s',strrep(align_pattern,'.',''),strrep(detect_pattern,'\','')),'_','\_'));
                       end
                       set(h(jj),'XTickLabel',[],'YTickLabel',[]);
                   elseif jj==max_N
                       break;
                   end
                   
                 
        
                   
%                    start_index=find(sap.pm.feature.t<onset_timing,1,'last');
%                    tmpindex=[max(1,(start_index-pre_start)):min(length(sap.pm.feature.t),(start_index+post_start))];
%                    imgindex_start=max(pre_start-start_index,1);
%                    imgindex_end  =imgindex_start+length(tmpindex);
%                    
%                    songamp=sap.pm.feature.(plot_quantity)(tmpindex);
%                    %                 size(songamp)
%                    %                 size(imgindex_start:imgindex_end-1)
%                    % fprintf('index=[%d..%d]\n',imgindex_start,imgindex_end)
%                    sap.pm.ampImg(jj,imgindex_start:(imgindex_end-1))=songamp;
                   jj=jj+1;
               else
                   fprintf('Not found!\n')
               end
         end
       linkaxes(h,'x');
       if isscalar(N)
           Ntxt=sprintf('%d',N);
       else
           Ntxt={sprintf('%d_',N)};
           Ntxt=Ntxt{1};Ntxt=Ntxt(1:end-1);
       end
       savename=fullfile(sap.pm.feature_dir,sprintf('Spectrum_iii.%s_in_%s_N=%s',strrep(align_pattern,'.',''),strrep(detect_pattern,'\',''),Ntxt));
        print(gcf,'-depsc2',[savename,'.eps']);
%        print(gcf,'-dill',[savename,'.ai']);
        print(gcf,'-dtiff','-r600',[savename,'.tiff']);
        
        print(gcf,'-djpeg90',[savename,'.jpg']);
          print(gcf,'-dpng',[savename,'.png']);
    
    %------------------------------------------------------%
        case 'align_song'
        if nargin>=2
            detect_pattern=varargin{1};
        else
            prompt={'Enter the detection pattern (ex: iiia+b+c+*)','Enter the pattern to align (ex: iiia+)'};
            name='Input for aligning song patterns';
            numlines=1;
            defaultanswer={'iiia+','iiia'};
            detect_pattern=inputdlg(prompt,name,numlines,defaultanswer);
            align_pattern=detect_pattern{2};
            detect_pattern=detect_pattern{1};
            fprintf('detect_pattern=%s\nalign_pattern=%s',detect_pattern,align_pattern);
            
            plot_quantity=questdlg('What quantity to plot?', ...
                       'plot quantity', ...
                       'amplitude','meanfreq','entropy','amplitude');
 
            
        end
        align_pattern=strrep(align_pattern,'iii','');
        dots=repmat('.',length(align_pattern),1);
        align_pattern=[align_pattern',dots]';
        align_pattern=align_pattern(:)';
        
        evaltxt=sprintf('sap.iii.%sindex',align_pattern);
        sap.syllable_tree_to_show_index=unique(eval(evaltxt));
        sap.gph.amplitude_img_fig=figure(17);clf;
        set(sap.gph.amplitude_img_fig,'Name','Aligned Sound Amplitude')
        pre_start=1000; % index
        post_start=5000;% index
        switch plot_quantity
            case 'amplitude'
        sap.pm.ampImg=-70*ones(length(sap.syllable_tree_to_show_index),pre_start+post_start-1);
        caxis_range=[-70 -50];
            case 'entropy'
                sap.pm.ampImg=zeros(length(sap.syllable_tree_to_show_index),pre_start+post_start-1);
        caxis_range=[0 4];
            case 'cancel'
                return;
            otherwise
                error('Unknown plot quantity!')
        end
        jj=1;
         for ii=1:length(sap.syllable_tree_to_show_index)
             % determine which file to read
             sap.pm.current_syllable_branch_n=ii;
                val=sap.syllable_tree_to_show_index(sap.pm.current_syllable_branch_n);
                str=get(sap.gph.ui_select_song_by_filename,'String');
                sap.pm.filename=str{val};
                               
                set(sap.gph.ui_select_song_by_filename,'Value',val);
               drawnow;
               % now find the note that matches detect_pattern.
%                fprintf('note=s%s ',sap.syllables(val).note);
               
                % now, find the notes that belongs to this file.
                same_serial_index = strmatch(sap.pm.filename,sap.data_filename);
                index_sounds=sap.data(sap.pm.classified_cluster_index,same_serial_index);
                str2=sap.pm.converting_matrix(index_sounds+1);
                str2=[str2{:}];
                str2=filter_syllable_structure(str2,sap.pm.replace_chart,{});
                search_pattern=sprintf('iii%s',strrep(align_pattern,'.','+'));
         
%                 search_pattern
%                fprintf('look for %s in %s\n',search_pattern,str2);
               ending_index=regexp(str2,search_pattern,'end');
               fprintf('look for %s in %s\n',detect_pattern,str2);
               is_exist_this_pattern=~isempty(regexp(str2,detect_pattern,'once'));
               %                fprintf('and detected %s\n', str2(1:ending_index));
               %                  index=regexp(str2,remaining_notes)
               %                 strfind();
               
               if (is_exist_this_pattern)
                   %                 sap.pm.show_sonogram_index=show_index_local(sap.pm.minind);
                   sap.pm.show_sonogram_index=same_serial_index(ending_index);
                   onset_timing=unique(sap.data(sap.pm.start_on_index,sap.pm.show_sonogram_index)/1000);
                   if isempty(onset_timing), continue;end
                   onset_timing=onset_timing(1);
                   %                 fprintf('%s starts at %g sec\n',search_pattern,onset_timing);
                   feval(mfilename,'load_feature');
                   
                   start_index=find(sap.pm.feature.t<onset_timing,1,'last');
                   tmpindex=[max(1,(start_index-pre_start)):min(length(sap.pm.feature.t),(start_index+post_start))];
                   imgindex_start=max(pre_start-start_index,1);
                   imgindex_end  =imgindex_start+length(tmpindex);
                   
                   songamp=sap.pm.feature.(plot_quantity)(tmpindex);
                   %                 size(songamp)
                   %                 size(imgindex_start:imgindex_end-1)
                   % fprintf('index=[%d..%d]\n',imgindex_start,imgindex_end)
                   sap.pm.ampImg(jj,imgindex_start:(imgindex_end-1))=songamp;
                   jj=jj+1;
               else
                   fprintf('Not found!\n')
               end
         end
         if jj>1
             sap.pm.ampImg=sap.pm.ampImg(1:jj-1,:);
         else
             error('No such song!');
         end
         switch plot_quantity
             case 'amplitude'
                %
             case 'entropy'
               sap.pm.ampImg=-sap.pm.ampImg; % entropy is defined as positive value.
             otherwise
                 error('Unknown plot quantity!')
         end
        
       sap.gph.ampImg_axes=axes('Position',[.1 .2 .8 .7]);
       imagesc(sap.pm.ampImg); set(gca,'YDir','Normal');
       caxis(caxis_range);
       set(sap.gph.ampImg_axes,'XTick',[]);
       sap.gph.Mean_ampplot_axes=axes('Position',[.1 .1 .8 .1]);
       plot(mean(sap.pm.ampImg,1));
       axis([1 pre_start+post_start caxis_range]);
       savename=fullfile(sap.pm.feature_dir,sprintf('iii.%s_in_%s_%s',strrep(align_pattern,'.',''),strrep(detect_pattern,'\',''),plot_quantity));
       print(gcf,'-dpng',[savename,'.png']);
       print(gcf,'-depsc2',[savename,'.eps']);
       print(gcf,'-dill',[savename,'.ai']);
       AmpImg=sap.pm.ampImg;
       save([savename,'.mat'],'AmpImg');
       
    case 'print_sonogram'
        figure(22);clf;
        
        m_spec_deriv=sam_spectrum_deriv2(sap.pm.song,sap.pm.Fsong);
        size(m_spec_deriv);
        sap.gpm.max_spec=max(max(m_spec_deriv));
        min_spec=min(min(m_spec_deriv));
        
        t=linspace(0,length(sap.pm.song)/sap.pm.Fsong,size(m_spec_deriv,1));
        f=sap.pm.Fsong*(1:size(m_spec_deriv,2))/1024/1000;
        
       
        
        width = max(t)*8;         % Initialize a variable for width.
        height = 4;          % Initialize a variable for height.
        dx1=.5;
        dx2=.5;
        dy=1;
        papersize=[width+dx1+dx2,height+2*dy];
        setPaperSize(papersize,12);clf;
%         set(gcf, 'PaperUnits', 'centimeters');
%         set(gcf, 'PaperSize', papersize);
    h=axes('Position',[dx1/(width+dx1+dx2),dy/(height+2*dy),width/(width+dx1+dx2),height/(height+2*dy)]);
    imagesc(t,f,m_spec_deriv'); %shading interp; view(0,90);
         colormap gray;
%          cutoff=0.004;
         cutoff=sap.pm.sonogram_caxis_cutooff;
         %                    text(min(xlim)+diff(xlim)*.05,max(ylim)-diff(ylim)*.1,sprintf('trial=%d',val));
         title(strrep(sap.pm.filename,'_','\_'));
         set(gca,'CLim',sap.pm.sonogram_caxis_cutooff*[-1 1]*sap.gpm.max_spec,'YDir','Normal');
       
%          set(gca,'CLim',cutoff*[-1 1]*sap.gpm.max_spec,'YDir','Normal');
         set(gca,'Color',[.5 .5 .5]);
            
                   
        feval(mfilename,'draw_bout_durationbar',gca,0);
        feval(mfilename,'show_classification',gca,0);
        
        savename=fullfile(sap.pm.sound_dir,sap.pm.filename);
        print(gcf,'-dpng',[savename,'.png']);
        close(22);
    case 'show_princomp_axis'
        [pc,score,latent,tsquare] = princomp(zscore(sap.data(sap.pm.classify_dim_index,:)'));
        figure(33);clf;
        
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
        
        if get(sap.gph.ui_Stimlated_cluster_ONOFF,'Value') % show stimulated data
            %             sap.pm.show_column_bools =sap.pm.show_column_bools&(sap.data(sap.pm.is_teacher_index,:));
            stimulated_bools =sap.pm.show_column_bools&sap.data(sap.pm.stimulated_index,:);
            if sap.gpm.do_show_teacher % show all the data
                %       
            else % do not show the teacher data
                stimulated_bools =stimulated_bools&~(sap.data(sap.pm.is_teacher_index,:));
            end
        else % do not show the stimulated data
            stimulated_bools=false(1,size(sap.data,2));
        end
    
        
        
        
        %         sap.pm.show_column_bools=find(sap.pm.show_column_bools);
        %         length(sap.pm.show_column_bools)
        
        for ii=0:9
            if (sap.pm.cluster_val(ii+1))
                show_index=sap.data(which_cluster_type,:)==ii;
                h=plot3(score(show_index&local_show_bools,1),score(show_index&local_show_bools,2),score(show_index&local_show_bools,3),'ko','MarkerSize',2);hold on;
                
                CSnow = sap.pm.CS(ii+1,:);
                
                set(h,'MarkerFaceColor',CSnow,'MarkerEdgeColor','none');
                
              
            end
        end
         
      
        
%         plot(score(:,1),score(:,2),'r.');hold on;
%         biplot(pc(:,1:2),1),'VarLabels',sap.pm.names(sap.pm.classify_dim_index));
        origin=[4,-4,4];
        pctmp=pc*2;
        line([repmat(origin(1),size(pc,1),1),pctmp(:,1)+origin(1)]',...
            [repmat(origin(2),size(pc,1),1),pctmp(:,2)+origin(2)]',...
            [repmat(origin(3),size(pc,1),1),pctmp(:,3)+origin(3)]',...
            'Color','k');
        text(pctmp(:,1)+origin(1),pctmp(:,2)+origin(2),pctmp(:,3)+origin(3),...
            strrep(sap.pm.names(sap.pm.classify_dim_index),'_','\_'),...
            'FontSize',6);
        
    xlabel('1st component');ylabel('2nd component');zlabel('3rd component');
        
        
    otherwise
        error('Unknown option')
end
