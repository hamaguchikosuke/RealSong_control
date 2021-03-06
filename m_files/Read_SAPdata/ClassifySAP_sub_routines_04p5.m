function varargout=ClassifySAP_sub_routines_04p5(opt,varargin)
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
        
        sap.pm.mean_amplitude_index =strmatch('mean_amplitude',sap.pm.names);
        sap.pm.mean_pitch_index     =strmatch('mean_pitch',sap.pm.names);         % 6
        sap.pm.mean_FM_index        =strmatch('mean_FM',sap.pm.names);         % 6
        sap.pm.mean_entropy_index   =strmatch('mean_entropy',sap.pm.names);         % 6
        sap.pm.mean_meanfreq_index  =strmatch('mean_mean_frequency',sap.pm.names);
        sap.pm.mean_gpitch_index    =strmatch('mean_goodness_of_pitch',sap.pm.names);         % 6
        
        
        sap.pm.var_entropy_index    =strmatch('var_entropy',sap.pm.names);         % 6
        sap.pm.var_pitch_index     =strmatch('var_pitch',sap.pm.names);
        sap.pm.var_FM_index        =strmatch('var_FM',sap.pm.names);
        sap.pm.var_meanfreq_index  =strmatch('var_mean_frequency',sap.pm.names);
        
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
        
        sap.syllables=struct;
        sap.bout_durations=[];
        sap.N_motif_counts=[];
        sap.bout_stimulated_or_not=[];
        
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
        sap.pm.template_classify_dim_index=[...
            sap.pm.mean_amplitude_index,...
            sap.pm.mean_entropy_index,...
            sap.pm.mean_pitch_index,...
            sap.pm.mean_FM_index,...
            sap.pm.mean_meanfreq_index,...
            sap.pm.var_entropy_index,...
            sap.pm.var_pitch_index,...
            sap.pm.var_FM_index,...
            sap.pm.var_meanfreq_index];
        
        
        
        
        sap.pm.feature_loadname=[];
        sap.pm.sonogram_caxis_cutooff_min=0.0001;
        sap.pm.sonogram_caxis_cutooff_max=0.1;
        sap.pm.sonogram_caxis_cutooff=0.06;
        sap.SAPtablename=[];
        
        sap.gph.template_feature_fig=[];
        
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
               
                try
                    sql_dir=uigetdir;
                catch
                    sql_dir='C:\mysql\data\mysql\';
                end
                
                d=dir(fullfile(sql_dir,'*.myd'));
                databasename=strsplit(sql_dir,filesep);
                sap.databasename=databasename{end};
                
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
                conn = database(sap.databasename, '', '');
                setdbprefs('DataReturnFormat','numeric')
                conn_txt=sprintf('select * from %s where cluster>0 and duration>20',sap.Teachertablename);
                curs = exec(conn, conn_txt);
                curs = fetch(curs,sap.pm.max_load_N);
                tmpdata=curs.data';
                colname=columnnames(curs); colname=strrep(colname,'''','');
                colname=strsplit(colname,',');
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
            % evaltxt = sprintf('sap.gph.ui_cluster_type(%d) = uicontrol(''Style'',''Radio'',''Value'',0,''String'',sap.pm.cluster_types{%d},''unit'',''normalized'',''pos'',[%g,%g,%g,dy],''parent'',sap.gph.ui_cluster_type_select,''HandleVisibility'',''off'',''CallBack'',''ClassifySAP_sub_routines_04p5(''''%s'''')'');',...
            %     ii,ii,0,1-(ii)*dy,.8,'select_cluster_data_type');
            % eval(evaltxt);
            
            evaltxt = sprintf('sap.gph.ui_cluster_type(%d) = uicontrol(''Style'',''Radio'',''Value'',0,''String'',sap.pm.cluster_types{%d},''unit'',''normalized'',''pos'',[%g,%g,%g,dy],''parent'',sap.gph.ui_cluster_type_select,''HandleVisibility'',''off'');',...
                ii,ii,0,1-(ii)*dy,.8);
            eval(evaltxt);
        end
        
        set(sap.gph.ui_cluster_type_select,'SelectionChangeFcn','ClassifySAP_sub_routines_04p5(''select_cluster_data_type'')');
        set(sap.gph.ui_cluster_type_select,'SelectedObject',sap.gph.ui_cluster_type(1));  % No selection
        % set(sap.gph.ui_cluster_type(1),'Value',1);
        set(sap.gph.ui_cluster_type_select,'Visible','on');
        
        sap.gph.ui_teacher_cluster_ONOFF = uicontrol('Style','Radio',...
            'Value',0,'String','teacher','unit','normalized','pos',[.12 .93 .1 .03],...
            'CallBack','ClassifySAP_sub_routines_04p5(''set_teacher_OnOff'');');
        sap.gph.ui_Stimlated_cluster_ONOFF = uicontrol('Style','Radio',...
            'Value',1,'String','stimulated','unit','normalized','pos',[.12 .90 .1 .03],...
            'CallBack','ClassifySAP_sub_routines_04p5(''set_Stimlated_cluster_ONOFF'');');
        
        sap.gph.ui_teacher_loadbutton = uicontrol('Style','pushbutton',...
            'Value',0,'String','LoadTeacherDatabase','unit','normalized','pos',[.25 .95 .1 .04],...
            'CallBack','ClassifySAP_sub_routines_04p5(''load_teacher_database'');');
        sap.gph.ui_teacher_clearbutton = uicontrol('Style','pushbutton',...
            'Value',0,'String','ClearTeacher','unit','normalized','pos',[.35 .95 .1 .04],...
            'CallBack','global sap; sap.data=sap.data(:,1:sap.pm.loaded_N); sap.data(sap.pm.classified_cluster_index,:)=0;sap.data(sap.pm.is_teacher_index,:)=0;');
        
        % cluster selection button
        sap.gph.ui_clusterselect = uipanel('Title','clusters','Position',[.01 .6 .2 .3]);
        dx = 1; dy=1/10;
        for ii=[0:8]
            evaltxt = sprintf('sap.gph.ui_cluster%d = uicontrol(''Style'',''Radio'',''Value'',1,''String'',[''cluster'' num2str(%d) '':(--)''],''unit'',''normalized'',''pos'',[%g,%g,%g,dy],''parent'',sap.gph.ui_clusterselect,''HandleVisibility'',''off'',''CallBack'',''ClassifySAP_sub_routines_04p5(''''%s'''')'');',...
                mod(ii,9),mod(ii,9),0,1-(ii+1)*dy,.6,'update_datatmp');
            eval(evaltxt);
        end
        ii=9; % for noise.
        evaltxt = sprintf('sap.gph.ui_cluster%d = uicontrol(''Style'',''Radio'',''Value'',1,''String'',[''noise'' num2str(%d) '':(--)''],''unit'',''normalized'',''pos'',[%g,%g,%g,dy],''parent'',sap.gph.ui_clusterselect,''HandleVisibility'',''off'',''CallBack'',''ClassifySAP_sub_routines_04p5(''''%s'''')'');',...
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
            'Unit','Normalized','Position', [.25 .9 .09 yh],'Callback', 'ClassifySAP_sub_routines_04p5(''show_syllable'');');
        
        uicontrol('Style', 'pushbutton','String', 'redraw',...
            'Unit','Normalized','Position', [.35 .9 .09 yh],'Callback', 'ClassifySAP_sub_routines_04p5(''redraw'');');
        
        uicontrol('Style', 'pushbutton','String', 'select&annotate',...
            'Unit','Normalized','Position', [.45 .9 .09 yh],'Callback', 'ClassifySAP_sub_routines_04p5(''select_rect_annotate'');');
        
        
        
        uicontrol('Style', 'pushbutton','String', 'LoadDatabase',...
            'Unit','Normalized','Position', [.55 .9 .09 yh],'Callback', 'ClassifySAP_sub_routines_04p5(''load_database'');');
        
        uicontrol('Style', 'pushbutton','String', 'LoadDatabase+DAK',...
            'Unit','Normalized','Position', [.55 .95 .09 yh],...
            'Tooltip','Load mysql database generated by .dak data','Callback', 'ClassifySAP_sub_routines_04p5(''load_database_dak'');');
        
        
        uicontrol('Style', 'pushbutton','String', 'UploadDatabase',...
            'Unit','Normalized','Position', [.65 .9 .09 yh],'Callback', 'ClassifySAP_sub_routines_04p5(''upload_database'');');
        
        
        uicontrol('Style', 'pushbutton','String', 'EditAnalysisParam',...
            'Unit','Normalized','Position', [.75 .9 .09 yh],'Callback', 'ClassifySAP_sub_routines_04p5(''open_analysis_parameters'');');
        
        uicontrol('Style', 'pushbutton','String', 'ShowPrincomp',...
            'Unit','Normalized','Position', [.85 .9 .09 yh],'Callback', 'ClassifySAP_sub_routines_04p5(''show_princomp_axis'');');
        
        
        
        x=0.1;  dx=0.1;
        xw=0.08;
        pos0=[x, .4, xw, yh];
        pos1=pos0+[0 yh 0 0];
        uicontrol('Style', 'pushbutton','String', 'play song',...
            'Unit','Normalized','Position', pos0,'Callback', 'ClassifySAP_sub_routines_04p5(''play_wholesong'');');
        
        uicontrol('Style', 'pushbutton','String', 'print sonogram',...
            'Unit','Normalized','Position', pos1,'Callback', 'ClassifySAP_sub_routines_04p5(''print_sonogram'');');
        
        % uicontrol('Style', 'pushbutton','String', 'play syllable',...
        %     'Unit','Normalized','Position', [.2 .4 xw yh],'Callback', 'ClassifySAP_sub_routines_04p5(''play_syllable'');');
        
        %         x=x+dx;
        %         uicontrol('Style', 'pushbutton','String', 'show classification',...
        %             'Unit','Normalized','Position', [x .4 xw yh],'Callback', 'ClassifySAP_sub_routines_04p5(''show_classification'');');
        %
        % uicontrol('Style', 'pushbutton','String', 'load feature',...
        %     'Unit','Normalized','Position', [.4 .4 xw yh],...
        %     'Callback', 'ClassifySAP_sub_routines_04p5(''load_feature'');');
        
        %         x=x+dx;
        %         uicontrol('Style', 'pushbutton','String', 'AutoClassify',...
        %             'Unit','Normalized','Position', [x .4 xw yh], ...
        %             'ToolTips','Mahalnovis distance based classification',...
        %             'Callback','ClassifySAP_sub_routines_04p5(''auto_classify'');');
        %
        %
        %         x=x+dx;
        %         uicontrol('Style', 'pushbutton','String', 'AutoClassifyAll',...
        %             'FontSize',8,...
        %             'ForegroundColor','m',...
        %             'Unit','Normalized','Position', [x .4 xw yh], ...
        %             'ToolTips','Apply Mahalnovis distance based classification to all the unclassified sound',...
        %             'Callback','ClassifySAP_sub_routines_04p5(''auto_classify_all'');');
        
        
        %         x=x+dx;
        pos0=pos0+[dx,0 0,0];
        uicontrol('Style', 'pushbutton','String', {'ExportSyllable','Transitions'},...
            'FontSize',8,...
            'Unit','Normalized','Position', pos0, ...
            'ToolTips','Export the identified syllables into text format.',...
            'Callback','ClassifySAP_sub_routines_04p5(''export_syllable_transitions'');');
        
        
        pos0=pos0+[dx,0 0,0];
        uicontrol('Style', 'pushbutton','String', 'ShowTransMat',...
            'Unit','Normalized','Position', pos0, ...
            'ToolTips','Show transition matrix',...
            'Callback','ClassifySAP_sub_routines_04p5(''show_trans_matrix'');');
        
        
        pos0=pos0+[dx,0 0,0];
        uicontrol('Style', 'pushbutton','String', {'ShowSyllable','Transition'},...
            'FontSize',8,...
            'Unit','Normalized','Position', pos0, ...
            'ToolTips','Show Syllable Tree',...
            'Callback','ClassifySAP_sub_routines_04p5(''show_syllable_tree'');');
        
        pos1=pos0+[0,yh 0,0];
        uicontrol('Style', 'pushbutton','String', {'AlignSong'},...
            'FontSize',8,...
            'Unit','Normalized','Position', pos1, ...
            'ToolTips','Show Syllable Tree',...
            'Callback','ClassifySAP_sub_routines_04p5(''align_song'');');
        
        
        
        
        pos1=pos1+[0,yh 0,0];
        uicontrol('Style', 'pushbutton','String', {'BoutMotifHist'},...
            'FontSize',8,...
            'Unit','Normalized','Position', pos1, ...
            'ToolTips','Export Song/Motif histgram',...
            'Callback','ClassifySAP_sub_routines_04p5(''export_bout_durations'');');
        pos1=pos1+[dx,0 0,0];
        uicontrol('Style', 'pushbutton','String', {'Syl&GapHist'},...
            'FontSize',8,...
            'Unit','Normalized','Position', pos1, ...
            'ToolTips','Export syllable gap histgram',...
            'Callback','ClassifySAP_sub_routines_04p5(''export_syllable_gap_hist'');');
        
        
        
        
        pos0=pos0+[dx,0 0,0];
        uicontrol('Style', 'pushbutton','String', {'TrainSVM'},...
            'FontSize',8,...
            'Unit','Normalized','Position', pos0, ...
            'ToolTips','TrainSVM',...
            'Callback','ClassifySAP_sub_routines_04p5(''train_predict_svm'');');
        
        pos1=pos0+[0,yh 0,0];
        uicontrol('Style', 'pushbutton','String', {'AlignSonogram'},...
            'FontSize',8,...
            'Unit','Normalized','Position', pos1, ...
            'ToolTips','PlotAlignedSonogram',...
            'Callback','ClassifySAP_sub_routines_04p5(''align_sonogram_plot'');');
        
        pos0=pos0+[dx,0 0,0];
        uicontrol('Style', 'pushbutton','String', {'DeleteSong'},...
            'FontSize',8,...
            'Unit','Normalized','Position', pos0, ...
            'ToolTips','Delete this song from database and file',...
            'Callback','ClassifySAP_sub_routines_04p5(''delete_song_from_database'');');
        
        pos0=pos0+[dx,0 0,0];
        uicontrol('Style', 'pushbutton','String', {'ShowFeatures ToMakeTemplates'},...
            'FontSize',5,...
            'Unit','Normalized','Position', pos0, ...
            'ToolTips','Call TemplateMaker function',...
            'Callback','ClassifySAP_sub_routines_04p5(''show_features_to_make_templates'');');
       
        pos0=pos0+[dx,0 0,0];
        uicontrol('Style', 'pushbutton','String', {'ChangeSyllableThreshold'},...
            'FontSize',5,...
            'Unit','Normalized','Position', pos0, ...
            'ToolTips','Change syllable detection threshold',...
            'Callback','ClassifySAP_sub_routines_04p5(''change_syllable_threshold'');');
        
        pos00=pos0+[0,yh 0,0];
        uicontrol('Style', 'pushbutton','String', {'UpdateDetectedSyllables'},...
            'FontSize',5,...
            'Unit','Normalized','Position', pos00, ...
            'ToolTips','Update syllable date with new threshold',...
            'Callback','ClassifySAP_sub_routines_04p5(''update_detected_syllables'');');
        
        
        
        %         ClassifySAP_sub_routines_04p5('init_feature_vector');
        
        % x axis selection
        sap.gph.ui_xbuttonG = uibuttongroup('visible','off','Position',[.25 .5 .7 .05]);
        dx = 1/7; dy=.5;
        for ii=1:13
            evaltxt = sprintf('sap.gph.ui_xbutton%d = uicontrol(''Style'',''Radio'',''String'',sap.pm.names{%d},''unit'',''normalized'',''pos'',[%g,%g,%g,.5],''parent'',sap.gph.ui_xbuttonG,''HandleVisibility'',''off'');',...
                ii,ii+4,(mod(ii-1,7))*dx,1-ceil(ii/7)*dy,dx);
            eval(evaltxt);
        end
        % Initialize some button group properties.
        set(sap.gph.ui_xbuttonG,'SelectionChangeFcn','ClassifySAP_sub_routines_04p5(''chk_xaxis_button'')');
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
        set(sap.gph.ui_ybuttonG,'SelectionChangeFcn','ClassifySAP_sub_routines_04p5(''chk_yaxis_button'')');
        set(sap.gph.ui_ybuttonG,'SelectedObject',sap.gph.ui_ybutton4);  % No selection
        set(sap.gph.ui_ybuttonG,'Visible','on');
        
        sap.gph.ui_select_song_by_filename=uicontrol(...
            'Style', 'list',...
            'String', sap.distinct_data_filename,...
            'Unit','Normalized',...
            'Position', [.01 .1 .24 .3],...
            'Callback', 'ClassifySAP_sub_routines_04p5(''select_song_by_filename'');');
        
        sap.gph.sonogramAxes=axes('Position',[.25 .1 .6 .3],'YDir','Normal');
        sap.gph.sonogramImg = imagesc(NaN,NaN,NaN); hold on;   colormap gray;
        sap.gph.sonogram_feature_plots=plot(repmat(NaN,2,length(sap.pm.feature_names)),repmat(NaN,2,length(sap.pm.feature_names)));hold on;
        sap.gph.MotifThresh_line=plot(NaN,NaN,'b--');
        
        
        % y axis selection
        sap.gph.ui_featurepanel = uipanel('visible','off','Position',[0.87 .1 .12 .3]);
        dx = .9; dy=1/7;
        for ii=1:length(sap.pm.feature_names)
            evaltxt = sprintf('sap.gph.ui_featurebutton%d = uicontrol(''Style'',''Radio'',''String'',sap.pm.feature_names{%d},''unit'',''normalized'',''pos'',[%g,%g,%g,dy],''parent'',sap.gph.ui_featurepanel,''HandleVisibility'',''off'');',...
                ii,ii,floor(ii/7)*dx,1-(mod(ii-1,7)+1)*dy,dx);
            eval(evaltxt);
            button_uiname=sprintf('sap.gph.ui_featurebutton%d',ii);
            evaltxt=sprintf('set(%s,''Callback'',''ClassifySAP_sub_routines_04p5(''''chk_feature_button'''')'')',button_uiname);
            eval(evaltxt);
        end
        set(sap.gph.ui_featurepanel,'Visible','on');
        
        
        sap.gph.ui_shown_cluster_as_noise=uicontrol('Style','pushbutton','String', 'Register as Noise',...
            'FontSize',8,...
            'Unit','Normalized','Position', [.87 .05 .1 .05],'Callback', 'ClassifySAP_sub_routines_04p5(''register_shown_cluster_as_noise'');');
        
        
        sap.gph.ui_register_shown_cluster_to_Manual_cluster=uicontrol('Style','pushbutton','String', 'Register',...
            'Unit','Normalized','Position', [.87 0 .1 .05],'Callback', 'ClassifySAP_sub_routines_04p5(''register_shown_cluster_to_Manual_cluster'');');
        
        sap.gph.ui_spectrum_contrast=uicontrol('Style','slider','Value', 0.1*(1-sap.pm.sonogram_caxis_cutooff),...
            'Unit','Normalized','Position', [.85 0.1 .01 .3],'Callback', 'ClassifySAP_sub_routines_04p5(''set_spectrum_contrast'');');
        
        sap.gpm.amplitude_thresh=0.1;
        sap.gph.ui_amplitude_thresh=uicontrol('Style','slider','Value', sap.gpm.amplitude_thresh,...
            'Unit','Normalized','Position', [.86 0.1 .01 .3],...
            'ForegroundColor', [.5 1 .5],...
            'BackgroundColor', [.5 .5 1],...
            'Visible', 'on',...
            'Callback', 'ClassifySAP_sub_routines_04p5(''set_amp_thresh'');');
        
        sap.pm.MotifThreshold=get(sap.gph.ui_amplitude_thresh,'Value')*10;
        sap.pm.MinNoteLength = 20;
        sap.pm.LongestNoteLength=300;
        sap.pm.MinPauseLength=20;
        sap.pm.amplitude_thresh_plot_100x=100;
        % feval(mfilename,'set_amp_thresh');
        
    case 'set_amp_thresh'
        
        sap.pm.MotifThreshold=get(sap.gph.ui_amplitude_thresh,'Value')*10;
        
        
        
        
        sampF_spec=length(sap.pm.feature2.t)/(sap.pm.feature2.t(end)-sap.pm.feature2.t(1));
        fprintf('Threshold is set to %g\n',get(sap.gph.ui_amplitude_thresh,'Value')*10);
        set(sap.gph.MotifThresh_line,'XData',xlim,'YData',repmat(sap.pm.MotifThreshold,1,2)*sap.pm.amplitude_thresh_plot_100x);
        
        [up_ind,down_ind]=detect_thresholded_regions(...
            sap.pm.feature2.amplitude+70,...
            sap.pm.MotifThreshold,...
            sap.pm.MinNoteLength*sampF_spec/1000,...
            sap.pm.LongestNoteLength*sampF_spec/1000,...
            sap.pm.MinPauseLength*sampF_spec/1000);
        
        if isempty(up_ind) || isempty(down_ind)
            px=[];
            py=[];
            duration=[];
            fprintf('No motif or syllable detected!\n')
            return;
        elseif length(up_ind)==1 && length(down_ind)==1
            fprintf('Single call detected, or syllable threshold is too small. \n')
            sn.gpm.syllable=[];
            if up_ind(1)>down_ind(1)
                fprintf('Detected: up_ind(1)>down_ind(1)\n')
                return;
            end
        end
        
        
        if length(up_ind)>1
            sn.gpm.MotifDetected=1;
        else % there is only one pause in the song, which is very likely to be noise.
            % fprintf('No motif or syllable detected!\n')
            sn.gpm.MotifDetected=0;
        end
        
        
    case 'readonly_database'
        if nargin>=2
            sap.SAPtablename_old=varargin{1};
        else
            error('Please specify tablename!');
        end
        
        if nargin>=3
            feature_parent_dir=varargin{2};
        else
            feature_parent_dir=pwd;
        end
        
        
          % 2. then, reset everything.
        feval(mfilename,'init_variables_for_figure'); % load variables needed below;
        feval(mfilename,'init_variables');
        feval(mfilename,'init_figures');
        
        sap.SAPtablename=sap.SAPtablename_old;
        set(16,'Name',sprintf('%s: %s',mfilename,sap.SAPtablename_old));
         
         
        logintimeout(5);
        fprintf('Loading table from %s\n',sap.SAPtablename_old);
        
        try
            sql_dir=uigetdir;
        catch
            sql_dir='C:\mysql\data\mysql\';
        end
        
        if ~fileExists(fullfile(sql_dir,[sap.SAPtablename_old,'.MYD']))
            error('table name %s does not exist!');
        end
        
        databasename=strsplit(sql_dir,filesep);
        sap.databasename=databasename{end};
                
        conn = database(sap.databasename, '', '');
        setdbprefs('DataReturnFormat','numeric')
        conn_txt=sprintf('select * from %s where cluster<9 and duration>20',sap.SAPtablename_old);
        curs = exec(conn, conn_txt);
        curs = fetch(curs,sap.pm.max_load_N);
        sap.data=curs.data';
        colname=columnnames(curs); colname=strrep(colname,'''','');colname=strsplit(colname,',');
        sap.pm.names=colname;
        
        setdbprefs('DataReturnFormat','cellarray')
        conn_txt=sprintf('select distinct file_name from %s where cluster<9 and duration>20',sap.SAPtablename_old);
        curs = exec(conn, conn_txt);
        curs = fetch(curs,sap.pm.max_load_N);
        sap.distinct_data_filename=curs.data';
        set(sap.gph.ui_select_song_by_filename,'String', sap.distinct_data_filename,'Value',1);
        conn_txt=sprintf('select file_name from %s where cluster<9 and duration>20',sap.SAPtablename_old);
        curs = exec(conn, conn_txt);
        curs = fetch(curs,sap.pm.max_load_N);
        sap.data_filename=curs.data';
        
        sap.pm.loaded_N=length(sap.data_filename);
        %             set(1,'Name',sap.SAPtablename);
        
        close(conn);
        varnames=SAP_data_structure_in_MySQL;varnames={varnames{:,1}};
        diffnames=   setdiff(varnames,sap.pm.names);
        
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
        sap.pm.following_gap_index       = strmatch('following_gap',sap.pm.names);
        
        sap.pm.cluster_index_in_data=[sap.pm.cluster_index,sap.pm.classified_cluster_index];
        % assign the row number information in userdata
        for ii=1:length(sap.pm.cluster_types)
            evaltxt = sprintf('set(sap.gph.ui_cluster_type(%d),''UserData'',sap.pm.cluster_index_in_data(%d));',...
                ii,ii);
            eval(evaltxt);
        end
        
        feval(mfilename,'set_teacher_data','from_same_database');
%         
%         switch lower(opt)
%             case 'load_database'
                sap.pm.dak_mode=0;
                tmpdir=fullfile(feature_parent_dir,[strrep(sap.SAPtablename_old,'_x',''),'_feature']);
                if isdir(tmpdir)
                    sap.pm.feature_dir=tmpdir;
                else
                    sap.pm.feature_dir = uigetdir('C:\home\Labview\data\', 'Pick a Feature binary data directory');
                end
                
                s=strsplit(sap.pm.feature_dir,filesep);
                parent_dir= fullfile(s{1:end-1});   % The sound directory and feature directory must be in the same directory.
                s=strsplit(sap.pm.feature_dir,filesep);
                sap.pm.sound_dir=fullfile(parent_dir,strrep(s{end},'_feature',''));
                S=dir(fullfile(sap.pm.sound_dir,'*.wav'));
                if isempty(S)
                    sap.pm.sound_dir = uigetdir('C:\home\Labview\data\', 'Could not find .wav data. Pick a sound (.wav) directory');
                end
%             case 'load_database_dak'
%                 sap.pm.dak_mode=1;
%                 sap.pm.dakdata = uigetfile({'*.dak'}, 'Pick the original .dak data');
%                 sap.pm.sound_dir='Null';
%             otherwise
%                 error('Unknown option!');
%         end
        
        s=strsplit(sap.pm.feature_dir,filesep);
        s=fullfile(s{1:end-1});
        sap.pm.analysis_dir=fullfile(s,[sap.SAPtablename_old,'_analysis']);
        mkdir(sap.pm.analysis_dir);
        
        %     [sap.SAPtablename,pathname]=uigetfile( ...
        %         {'*.*',  'All Files (*.*)'}, ...
        %         'Pick a SAP exported data file');
        %
        %     cd(pathname);
        %     data= load(fullfile(pathname,sap.SAPtablename));
        %     sap.data = data.LocalDouble;
        
        
         feval(mfilename,'update_datatmp');
        feval(mfilename,'set_teacher_onoff');
        set(sap.gph.ui_cluster_type(2),'Value',1);
        feval(mfilename,'select_cluster_data_type');       
        feval(mfilename,'redraw');
        
    %---------------------------
    %------- Load database ----------
    %---------------------------
        
    case {'load_database','load_database_dak'}
        if nargin>=2
            sap.SAPtablename=varargin{1};
        else
            % do nothing;
        end
        % 1. if there is data already, ask to upload or not.
        if ~isempty(sap.SAPtablename)
            questtxt=sprintf('Before quit, do you want to upload data?');
            ButtonName=questdlg(questtxt, ...
                'Question', ...
                'YES','NO','Cancel');
            
            if strmatch(ButtonName,'YES')
                feval(mfilename,'upload_database');
            else
                disp('Data not-uploaded...')
            end
        end
        
        % 2. then, reset everything.
        feval(mfilename,'init_variables_for_figure'); % load variables needed below;
        feval(mfilename,'init_variables');
        feval(mfilename,'init_figures');
        
        try
            try 
                sql_dir=uigetdir('C:\mysql\data\mysql\','Please select database');
            catch
                sql_dir='C:\mysql\data\mysql\';
            end
            
            databasename=strsplit(sql_dir,filesep);
            sap.databasename=databasename{end};
        
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
                sap.SAPtablename_old=tablenames{s};
            else
                disp('No table selected!');
                return;
            end
            
            set(16,'Name',sprintf('%s: %s',mfilename,sap.SAPtablename_old));
            drawnow;
            pwd_now=pwd;
            cd(sql_dir);
            if isempty(strfind(sap.SAPtablename_old,'_x'))
                s=sprintf('%s.MYD',[sap.SAPtablename_old,'_x']);
            else
                s=[sap.SAPtablename_old,'.MYD'];
            end
            %             fid=fopen(fullfile(sql_dir,s));
            %             if fid>0 FileExists=1; else FileExists=0; end
            %
            if FileExists(fullfile(sql_dir,s))
                questtxt=sprintf('Detected previously generated already classified data %s, are you going to update data in here?',s);
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
                sap.SAPtablename=s;
                pathname=sql_dir;
            else
                [sap.SAPtablename, pathname] = uiputfile( ...
                    {s, 'MYD-file (*.MYD)'; ...
                    '*.MYD', 'MYD-file (*.MYD)'},...
                    'SELECT a table to save classified data');
            end
            cd(pwd_now);
            
            logintimeout(5);
            fprintf('Loading table from %s\n',sap.SAPtablename_old);
            conn = database(sap.databasename, '', '');
            setdbprefs('DataReturnFormat','numeric')
            conn_txt=sprintf('select * from %s where cluster<9 and duration>20',sap.SAPtablename_old);
            curs = exec(conn, conn_txt);
            curs = fetch(curs,sap.pm.max_load_N);
            sap.data=curs.data';
            colname=columnnames(curs); colname=strrep(colname,'''','');colname=strsplit(colname,',');
            sap.pm.names=colname;
            
            setdbprefs('DataReturnFormat','cellarray')
            conn_txt=sprintf('select distinct file_name from %s where cluster<9 and duration>20',sap.SAPtablename_old);
            curs = exec(conn, conn_txt);
            curs = fetch(curs,sap.pm.max_load_N);
            sap.distinct_data_filename=curs.data';
            set(sap.gph.ui_select_song_by_filename,'String', sap.distinct_data_filename,'Value',1);
            conn_txt=sprintf('select file_name from %s where cluster<9 and duration>20',sap.SAPtablename_old);
            curs = exec(conn, conn_txt);
            curs = fetch(curs,sap.pm.max_load_N);
            sap.data_filename=curs.data';
            
            sap.pm.loaded_N=length(sap.data_filename);
            %             set(1,'Name',sap.SAPtablename);
            
            if strmatch(sap.SAPtablename,sap.SAPtablename_old)
                fprintf('Same table is selected. ')
            else
                fprintf('Making new table %s...\n',sap.SAPtablename);
                %                 drop_table=sprintf('DROP table %s;',upload_table_name);
                %                 exec(conn,drop_table);
                create_table=sprintf('create table %s as select * from %s',strrep(sap.SAPtablename,'.MYD',''),sap.SAPtablename_old)
                exec(conn,create_table);
                sap.SAPtablename=strrep(sap.SAPtablename,'.MYD','');
                AlterClause=sprintf('ALTER TABLE %s ADD PRIMARY KEY (recnum);',sap.SAPtablename);
                exec(conn,AlterClause);
                jj=strmatch('classified',sap.pm.cluster_types);
                %                 for jj=2:length(sap.pm.cluster_types)
                alter_table=sprintf('ALTER TABLE %s ADD %s %s;',sap.SAPtablename,sap.pm.cluster_types{jj},'tinyint(4)');
                exec(conn,alter_table);
                
                alter_table=sprintf('ALTER TABLE %s ADD %s %s;',sap.SAPtablename,'following_gap','float');
                exec(conn,alter_table);
                %                 end
            end
            
            close(conn);
            varnames=SAP_data_structure_in_MySQL;varnames={varnames{:,1}};
            diffnames=   setdiff(varnames,sap.pm.names);
            
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
            sap.pm.following_gap_index       = strmatch('following_gap',sap.pm.names);
            
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
                    tmpdir=fullfile(pwd,[strrep(sap.SAPtablename,'_x',''),'_feature']);
                    if isdir(tmpdir)
                        sap.pm.feature_dir=tmpdir;
                    else
                        sap.pm.feature_dir = uigetdir('C:\home\Labview\data\', 'Pick a Feature binary data directory');
                    end
                    
                    s=strsplit(sap.pm.feature_dir,filesep);
                    parent_dir= fullfile(s{1:end-1});   % The sound directory and feature directory must be in the same directory.
                    s=strsplit(sap.pm.feature_dir,filesep);
                    sap.pm.sound_dir=fullfile(parent_dir,strrep(s{end},'_feature',''));
                    S=dir(fullfile(sap.pm.sound_dir,'*.wav'));
                    if isempty(S)
                        sap.pm.sound_dir = uigetdir('C:\home\Labview\data\', 'Could not find .wav data. Pick a sound (.wav) directory');
                    end
                case 'load_database_dak'
                    sap.pm.dak_mode=1;
                    sap.pm.dakdata = uigetfile({'*.dak'}, 'Pick the original .dak data');
                    sap.pm.sound_dir='Null';
                otherwise
                    error('Unknown option!');
            end
            
            s=strsplit(sap.pm.feature_dir,filesep);
            s=fullfile(s{1:end-1});
            sap.pm.analysis_dir=fullfile(s,[sap.SAPtablename,'_analysis']);
            mkdir(sap.pm.analysis_dir);
            
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
    case 'create_database'
        
        
        conn = database(sap.databasename, '', '');
        
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
        
    case 'upload_database'
        
        %         feval(mfilename,'create_database');
        
        
        conn = database(sap.databasename, '', '');
        
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
        
        conn = database(sap.databasename, '', '');
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
                    eval(sprintf('delete %s',fullfile(sap.pm.sound_dir,sap.pm.filename)))
                    eval(sprintf('delete %s',fullfile(sap.pm.feature_dir,strrep(sap.pm.filename,'.wav','.mat'))))
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
        
        %         feval(mfilename,'redraw');
        
        
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
        delete_handles=setdiff(get(sap.gph.sonogramAxes,'Children'),[sap.gph.sonogramImg,sap.gph.sonogram_feature_plots(:)',sap.gph.MotifThresh_line]);
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
                
                conn = database(sap.databasename, '', '');
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
                
                conn = database(sap.databasename, '', '');
                setdbprefs('DataReturnFormat','numeric')
                conn_txt=sprintf('select distinct serial_number from %s where file_name like ''%s''',...
                    sap.SAPtablename,sap.pm.filename);
                curs = exec(conn, conn_txt);
                if ~isempty(strfind(curs.Message,'doesn''t exist'))
                    error('%s',curs.Message);
                end
                curs = fetch(curs,10);
                sap.pm.serial=curs.data';
                close(curs);
                close(conn);
                
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
        wavfile=strrep(sap.pm.filename,'.mat','.wav');
        txt=strrep(sprintf('wavfile: %s',wavfile),'_','\_');
        
        [sap.pm.song,sap.pm.Fsong]=wavread(fullfile(sap.pm.sound_dir,wavfile));
        
        
        
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
        
        %         sap.pm.feature.m_spec_deriv=sam_spectrum_deriv5(sap.pm.song,sap.pm.Fsong);
        
        [sap.pm.feature.m_spec_deriv , ...
            sap.pm.feature2.m_AM,...
            sap.pm.feature2.m_FM ,...
            sap.pm.feature2.entropy ,...
            sap.pm.feature2.amplitude ,...
            sap.pm.feature2.meanfreq, ...
            sap.pm.feature2.pgood , ...
            sap.pm.feature2.pitch ,...
            sap.pm.feature2.Pitch_chose ,...
            sap.pm.feature2.Pitch_weight,f ]=sam_spectrum_deriv5(sap.pm.song,sap.pm.Fsong);
        
        sap.pm.feature2.t=linspace(0,length(sap.pm.song)/sap.pm.Fsong,size(sap.pm.feature.m_spec_deriv,1)+1);
        sap.pm.feature2.t=sap.pm.feature2.t(1:end-1);
        sap.pm.feature2.f=sap.pm.Fsong*(1:size(sap.pm.feature.m_spec_deriv ,2))/1024;
        
        sap.pm.feature2.amplitude_bias=sap.pm.feature2.amplitude+70;
        
        sap.gpm.max_spec=max(max(sap.pm.feature.m_spec_deriv));
        min_spec=min(min(sap.pm.feature.m_spec_deriv));
        
        t=linspace(0,length(sap.pm.song)/sap.pm.Fsong,size(sap.pm.feature.m_spec_deriv,1));
        freqind=0:(size(sap.pm.feature.m_spec_deriv,2)-1);
        f=freqind*sap.pm.Fsong/1024;
        set(sap.gph.sonogramImg,'XData',t,'YData',f,'CData',sap.pm.feature.m_spec_deriv');
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
            try             sound(sap.pm.song(ind)/(6*std(sap.pm.song)),sap.pm.Fsong); end
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
        
        sound(sap.pm.song(tti(1):tti(2))/(8*std(sap.pm.song)),sap.pm.Fsong);
        
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
        
        sound(sap.pm.song(ind)/(8*std(sap.pm.song)),sap.pm.Fsong);
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
        
        [onset,durations,motif_counts,stimulated]=feval(mfilename,'return_bout_onset_duration_nmotif',sap.pm.filename,sap.pm.ISI_thresh);
        for ii=1:length(onset)
            fprintf('onsets=%6.5gms,\t durations=%6.4gms, \t (%2d motifs) (stimulated=%d)\n',onset(ii),durations(ii),motif_counts(ii),stimulated(ii));
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
        
        index_sounds=index_sounds(index_sounds>=0);
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
            
            cluster=sap.data(which_cluster_type,sap.pm.same_serial_index(ii));
            
            stimornot=sap.data(sap.pm.stimulated_index,sap.pm.same_serial_index(ii));
            
            if stimornot>=0 % this is a syllable or sound
                is_stim=0;
                cluster_str=sap.pm.converting_matrix{cluster+1};
            else % this is stimulation
                is_stim=1;
                cluster_str='*';
            end
            
           
%            fprintf('cluster=%d,',cluster);
            
            if (is_stim)
%                 fprintf('Stim bar plotting...\n');
                  sap.gph.syllable_line(ii)=line(x-t_offset,[0 0],'Color','g','LineWidth',line_width/2,...
                'ButtonDownFcn','ClassifySAP_sub_routines_04p5(''return_feature_2D_posi'')',...
                'Tag','DoNotIgnore','UserData',sap.pm.same_serial_index(ii));
%            
%             
%                 if (show_label_num)
%                     sap.gph.syllable_label(ii)=text(mean(x)-t_offset,label_num_offset,num2str(cluster),...
%                         'Color','k','FontSize',font_size);
%                     set(sap.gph.syllable_label(ii),...
%                         'ButtonDownFcn','ClassifySAP_sub_routines_04p5(''manual_change_cluster'')',...
%                         'Tag','DoNotIgnore','UserData',[sap.pm.same_serial_index(ii),ii]);
%                 end
%                 
%                 if (show_label_char)
%                     sap.gph.syllable_label2(ii)=text(mean(x)-t_offset,label_char_offset,2,cluster_str,...
%                         'Color','k','FontSize',font_size);
%                 end
            else % bird's sound
                
                  sap.gph.syllable_line(ii)=line(x-t_offset,[0 0],'Color','m','LineWidth',line_width,...
                'ButtonDownFcn','ClassifySAP_sub_routines_04p5(''return_feature_2D_posi'')',...
                'Tag','DoNotIgnore','UserData',sap.pm.same_serial_index(ii));
           
            
                if (show_label_num)
                    sap.gph.syllable_label(ii)=text(mean(x)-t_offset,label_num_offset,num2str(cluster),...
                        'Color',sap.pm.CS(cluster+1,:),'FontSize',font_size);
                    set(sap.gph.syllable_label(ii),...
                        'ButtonDownFcn','ClassifySAP_sub_routines_04p5(''manual_change_cluster'')',...
                        'Tag','DoNotIgnore','UserData',[sap.pm.same_serial_index(ii),ii]);
                end
                
                if (show_label_char)
                    if sap.data(sap.pm.stimulated_index,sap.pm.same_serial_index(ii))
                        uplow_func='upper';
                    else
                        uplow_func='lower';
                    end
                    sap.gph.syllable_label2(ii)=text(mean(x)-t_offset,label_char_offset,2,...
                        feval(uplow_func,cluster_str),...
                        'Color',sap.pm.CS(cluster+1,:),'FontSize',font_size);
                end
            end
            h=zoom;
            set(h,'Motion','horizontal','ButtonDownFilter',@myzoomcallback,'Enable','on');
            
            
            
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
            copy_txt=sprintf('!copy %s %s',which('ClassifySAP_Default_analysis_parameters.m'),fullfile(sap.pm.sound_dir,'analysis_parameters.m'));
            eval(copy_txt);
            %             eval('analysis_parameters');
            %             feval(mfilename,'reload_analysis_parameters');
            edit('analysis_parameters');
        end
        cd(current_dir);
        
    case 'reload_converting_matrix'
        current_dir=pwd;
        
        try
            cd(sap.pm.sound_dir);
            eval('analysis_parameters'); % load converting matrix, etc.
            cd(current_dir);
        catch
            fprintf('analysis parameter does not exists in %s...\n Use default one.',sap.pm.sound_dir);
            copy_txt=sprintf('!copy %s %s',which('ClassifySAP_Default_analysis_parameters.m'),fullfile(sap.pm.sound_dir,'analysis_parameters.m'));
            eval(copy_txt);
            eval('analysis_parameters');
        end
        
        
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
            dt=sap.pm.feature.specT(2)-sap.pm.feature.specT(1);
            t=[0:dt:0.1]';
            ts=0.01;
            expt=1/ts*exp(-t/ts)*dt; %expt=expt(end:-1:1);
            
            for ii=1:size(rename_tables,1)
                sap.pm.feature.(rename_tables{ii,1})=sap.pm.feature.(rename_tables{ii,2});
                sap.pm.feature=rmfield(sap.pm.feature,(rename_tables{ii,2}));
                tmp=conv(sap.pm.feature.(rename_tables{ii,1}),expt);
                sap.pm.feature.([rename_tables{ii,1},'_conv'])=tmp(1:end-length(expt)+1);
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
        
        %
        %         if isempty(strmatch(sap.pm.filename,sap.pm.feature_loadname))
        %             feval(mfilename,'load_feature');
        %         end
        
        lf=length(sap.pm.feature_names);
        val=zeros(lf,1);
        for ii=1:lf
            s=['ui_featurebutton',num2str(ii)];
            val(ii)=get(sap.gph.(s),'Value');
        end
        ymax=max(get(sap.gph.sonogramAxes,'YLim'));
        for ii=1:lf
            if val(ii)
                switch sap.pm.feature_names{ii}
                    case 'amplitude'
                        tmp=sap.pm.feature2.(sap.pm.feature_names{ii});
                        tmp=(tmp+70)*sap.pm.amplitude_thresh_plot_100x;
                        %                         tmpmax=max(tmp);
                        %                         tmpmin=min(tmp);
                        %                         tmp=(tmp-tmpmin)/(tmpmax-tmpmin); % now [0,1];
                        %                         tmp=tmp*ymax;
                        
                    case 'meanfreq'
                        tmp=sap.pm.feature2.(sap.pm.feature_names{ii});
                        
                    case 'pitch'
                        % after KinkaSongAnalysis 3p5, mean_ and var_pitch are encoded in Hz.
                        tmp=sap.pm.Fsong/2./sap.pm.feature2.(sap.pm.feature_names{ii});
                        
                    case 'entropy'
                        tmp=sap.pm.feature2.(sap.pm.feature_names{ii});
                        tmpmax=max(tmp);
                        tmpmin=min(tmp);
                        tmp=(tmp-tmpmin)/(tmpmax-tmpmin); % now [0,1];
                        tmp=tmp*ymax;
                    case 'pgood'
                        tmp=sap.pm.feature2.(sap.pm.feature_names{ii});
                    otherwise
                        error('Unknown option of sap.pm.feature_names{ii}!');
                end
                lowamp_ind=find((sap.pm.feature2.amplitude_bias)<sap.pm.MotifThreshold);
                tmp(lowamp_ind)=NaN;
                set(sap.gph.sonogram_feature_plots(ii),'XData',sap.pm.feature2.t,'YData',tmp);
                
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
                                'ButtonDownFcn','ClassifySAP_sub_routines_04p5(''manual_change_cluster'')',...
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
                                'ButtonDownFcn','ClassifySAP_sub_routines_04p5(''manual_change_cluster'')',...
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
        
        %--------------------------------------------%
        %--------------------------------------------%
        %--------------------------------------------%
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
        h = waitbar(0,'Parsing identidied syllables and making transition matrix...');
        
        
        
        for ii=1:length(str)
            waitbar(ii/length(str),h);
            [onset,durations,motif_counts,stimulated]=feval(mfilename,'return_bout_onset_duration_nmotif',str{ii},sap.pm.ISI_thresh);
            sap.pm.same_serial_index=strmatch(str{ii},sap.data_filename);
            [s,sorted_index]=sort(sap.data(sap.pm.start_on_index,sap.pm.same_serial_index));
            sap.pm.same_serial_index=sap.pm.same_serial_index(sorted_index);
            
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
        close(h)
        
        show_index=[];
        for ii=1:9
            num_teacher=length(find(sap.data(sap.pm.classified_cluster_index,:)==ii));
%             num_teacher=length(find(sap.data(sap.pm.cluster_index,:)==ii));
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
        sap.pm.Ntrans.matrix=sap.pm.trans_matrix(show_index_y,show_index_x);
        
        sumP=sum(sap.pm.Ntrans.matrix,2);
        sap.pm.Ntrans.P=sap.pm.Ntrans.matrix./repmat(sumP,1,size(sap.pm.Ntrans.matrix,2));
        
        sap.pm.Ntrans.repeats_prob=diag(diag(sap.pm.Ntrans.P));
        sap.pm.Ntrans.P_wo_repeats=sap.pm.Ntrans.P;
        for ii=1:length(sap.pm.Ntrans.repeats_prob)
            sap.pm.Ntrans.P_wo_repeats(ii,ii)=0;
        end
        sap.pm.Ntrans.P_wo_repeats= sap.pm.Ntrans.P_wo_repeats./repmat(sum(sap.pm.Ntrans.P_wo_repeats,2),1,size(sap.pm.Ntrans.P_wo_repeats,2));
        varargout{1}=sap.pm.Ntrans.P;
        
        
        %--------------------------------------------%
        %--------
        %--------------------------------------------%
        
        
    case 'parse_autoclassified_notes_strict'
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
        h = waitbar(0,'Parsing identidied syllables and making transition matrix...');
        
        
        
        for ii=1:length(str)
            waitbar(ii/length(str),h);
            [onset,durations,motif_counts,stimulated]=feval(mfilename,'return_bout_onset_duration_nmotif',str{ii},sap.pm.ISI_thresh);
            sap.pm.same_serial_index=strmatch(str{ii},sap.data_filename);
            [s,sorted_index]=sort(sap.data(sap.pm.start_on_index,sap.pm.same_serial_index));
            sap.pm.same_serial_index=sap.pm.same_serial_index(sorted_index);
            
            %             sap.pm.same_serial_index = find(sap.data(sap.pm.serial_index,:)==unique_serials(ii));
            which_cluster_type=get(get(sap.gph.ui_cluster_type_select,'selectedobject'),'UserData');
            
            tmp=sap.data(which_cluster_type,sap.pm.same_serial_index);
            tmp(find(tmp==1))=9; % introductory note is temporally classified as noise.
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
        close(h)
        
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
        sap.pm.Ntrans.matrix=sap.pm.trans_matrix(show_index_y,show_index_x);
        
        sumP=sum(sap.pm.Ntrans.matrix,2);
        sap.pm.Ntrans.P=sap.pm.Ntrans.matrix./repmat(sumP,1,size(sap.pm.Ntrans.matrix,2));
        
        sap.pm.Ntrans.repeats_prob=diag(diag(sap.pm.Ntrans.P));
        sap.pm.Ntrans.P_wo_repeats=sap.pm.Ntrans.P;
        for ii=1:length(sap.pm.Ntrans.repeats_prob)
            sap.pm.Ntrans.P_wo_repeats(ii,ii)=0;
        end
        sap.pm.Ntrans.P_wo_repeats= sap.pm.Ntrans.P_wo_repeats./repmat(sum(sap.pm.Ntrans.P_wo_repeats,2),1,size(sap.pm.Ntrans.P_wo_repeats,2));
        varargout{1}=sap.pm.Ntrans.P;
        
        %------------------------------------------
        %---- Show Transition Matrix --------------
        %------------------------------------------
        
    case 'show_trans_matrix'
        figure(20);
        set(20,'Name','Transition Matrix')
        
        feval(mfilename,'parse_autoclassified_notes');
        figure(20);setPaperSize([7,6],10);clf;
        sap.gph.ui_Transmat_panel = uipanel('visible','on','Position',[0.05 0.05 .9 .85],'BackGroundColor','white','BorderWidth',0);
        sap.gph.trans_mat_axes=axes('Position',[.1 0 .78 .7],'Parent',sap.gph.ui_Transmat_panel);
        
        
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
        
        x=.5:1:10.5;
        sap.gph.trans_mat_IMG=  imagesc(sap.pm.Ntrans.P);
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
        caxis([0 .9])
        set(get(sap.gph.trans_mat_IMG,'Parent'),'XAxisLocation','top','XTick',1:length(labels_X),'YTick',1:length(labels_Y));
        set(get(sap.gph.trans_mat_IMG,'Parent'),'XTickLabel',labels_X,'YTickLabel',labels_Y);
        set(gca,'YDir','Reverse')
        h=colorbar;
        pos=get(sap.gph.trans_mat_axes,'Position');
        set(h,'Position',[.9 0 0.05 .7]);
        
        %         h=surf(X,Y,ones(length(x)));
        %         set(h,'FaceAlpha',0);
        
        p=sap.pm.Ntrans.P; zero_ind=find(p==0);
        tmp=-p.*log(p); tmp(zero_ind)=0;
        sap.pm.Ntrans.entropy=sum(tmp,2);
        
        % entropy without repeats
        p=sap.pm.Ntrans.P_wo_repeats; zero_ind=find(p==0);
        tmp=-p.*log(p); tmp(zero_ind)=0;
        sap.pm.Ntrans.entropy_wo_repeats=sum(tmp,2);
        
        % entropy without Repeats, Non-classified, and END of songs
        p=sap.pm.Ntrans.P_wo_repeats;
        p(:,end-1:end)=0; p=p(:,1:end-2)./repmat(sum(p,2),1,size(p,2)-2);
        zero_ind=find(p==0);
        tmp=-p.*log(p); tmp(zero_ind)=0;
        sap.pm.Ntrans.entropy_wo_RNE=sum(tmp,2);
        
        
        %         Ntrans_matrix=sap.pm.Ntrans_matrix;
        %         Ntrans_entropy=sap.pm.Ntrans_entropy;
        Ntrans=sap.pm.Ntrans;
        ISI_thresh=sap.pm.ISI_thresh;
        fprintf('transition matrix is saved in %s\n',fullfile(sap.pm.analysis_dir,[sap.SAPtablename,'_transMatrix.mat']))
        save(fullfile(sap.pm.analysis_dir,sprintf('%s_ISIthresh=%g.mat',[sap.SAPtablename,'_transMatrix'],sap.pm.ISI_thresh)),...
            'Ntrans','show_index','ISI_thresh');
        
        
        %         set(sap.gph.trans_mat_axes,'XAxisLocation','top',...
        %             'XTick',[1:9],'XTickLabel',[1:9],'YTick',[1:9],'YTickLabel',[1:9]);
        
        uicontrol('Style', 'pushbutton','String', 'show syllable','Parent',sap.gph.ui_Transmat_panel,...
            'Unit','Normalized','Position', [0 1 .2 .1],...
            'Callback', 'ClassifySAP_sub_routines_04p5(''choose_syllable_transition'');');
        sap.ui.decrement_transit_syllable=uicontrol('Style', 'pushbutton','String', '<','Parent',sap.gph.ui_Transmat_panel,...
            'Unit','Normalized','Position', [.2 1 .15 .1],...
            'Callback', 'ClassifySAP_sub_routines_04p5(''move_syllable_transition'',-1);');
        sap.ui.edit_transit_syllable=uicontrol('Style', 'edit','String', '1','Parent',sap.gph.ui_Transmat_panel,...
            'Unit','Normalized','Position', [.35 1 .15 .1],...
            'Callback', 'global sap; n=str2num(get(sap.ui.edit_transit_syllable,''String''));ClassifySAP_sub_routines_04p5(''move_syllable_transition'',n);');
        sap.ui.increment_transit_syllable=uicontrol('Style', 'pushbutton','String', '>','Parent',sap.gph.ui_Transmat_panel,...
            'Unit','Normalized','Position', [.5 1 .15 .1],...
            'Callback', 'ClassifySAP_sub_routines_04p5(''move_syllable_transition'',+1);');
        sap.ui.maxN_transit_syllable=uicontrol('Style', 'Text','String', 'MaxN','Parent',sap.gph.ui_Transmat_panel,...
            'Unit','Normalized','Position', [.65 1 .15 .1]);
        
        savename=fullfile(sap.pm.analysis_dir,['TransMat_',sap.SAPtablename])
        print(gcf,'-dill','-noui',[savename,'_coldfire2.ai']);
        print(gcf,'-dpng','-noui',[savename,'_coldfire2.png']);
        
        
        %%
        figure(3);setPaperSize([7,6],10);clf;
        sap.gph.ui_Transmat_panel2 = uipanel('visible','on','Position',[0.05 0.05 .9 .85],'BackGroundColor','white','BorderWidth',0);
        sap.gph.trans_mat_axes2=axes('Position',[.1 0 .78 .7],'Parent',sap.gph.ui_Transmat_panel2);
        
        sap.gph.trans_mat_IMG2=  imagesc(sap.pm.Ntrans.P_wo_repeats);
        xlabel('Following syllable');
        ylabel('Preceding syllable')
        %         x=.5:1:10.5;
        [X,Y]=meshgrid(x,x);
        line(X,Y,ones(size(X)),'Color',[1 1 1]);
        line(X',Y',ones(size(X')),'Color',[1 1 1]);
        load coldfire2;
        colormap(sap.gph.trans_mat_axes2,coldfire2);
        caxis([0 .9])
        set(get(sap.gph.trans_mat_IMG2,'Parent'),'XAxisLocation','top','XTick',1:length(labels_X),'YTick',1:length(labels_Y));
        set(get(sap.gph.trans_mat_IMG2,'Parent'),'XTickLabel',labels_X,'YTickLabel',labels_Y);
        set(gca,'YDir','Reverse')
        h=colorbar;
        pos=get(sap.gph.trans_mat_axes2,'Position');
        set(h,'Position',[.9 0 0.05 .7]);
        
        savename=fullfile(sap.pm.analysis_dir,['TransMat_wo_repeats_',sap.SAPtablename])
        print(gcf,'-dill','-noui',[savename,'_coldfire2.ai']);
        print(gcf,'-dpng','-noui',[savename,'_coldfire2.png']);
        
        close(3);
        %%
        figure(3);setPaperSize([7,6],10);clf;
        sap.gph.ui_Transmat_panel2 = uipanel('visible','on','Position',[0.05 0.05 .9 .85],'BackGroundColor','white','BorderWidth',0);
        sap.gph.trans_mat_axes2=axes('Position',[.1 0 .78 .7],'Parent',sap.gph.ui_Transmat_panel2);
        p=sap.pm.Ntrans.P_wo_repeats(:,1:end-2);
        p=p./repmat(sum(p,2),1,size(p,2));
        
        sap.gph.trans_mat_IMG2=  imagesc(p);
        xlabel('Following syllable');
        ylabel('Preceding syllable')
        %         x=.5:1:10.5;
        [X,Y]=meshgrid(x,x);
        line(X,Y,ones(size(X)),'Color',[1 1 1]);
        line(X',Y',ones(size(X')),'Color',[1 1 1]);
        load coldfire2;
        colormap(sap.gph.trans_mat_axes2,coldfire2);
        caxis([0 .9])
        set(get(sap.gph.trans_mat_IMG2,'Parent'),'XAxisLocation','top','XTick',1:length(labels_X),'YTick',1:length(labels_Y));
        set(get(sap.gph.trans_mat_IMG2,'Parent'),'XTickLabel',labels_X,'YTickLabel',labels_Y);
        set(gca,'YDir','Reverse')
        h=colorbar;
        pos=get(sap.gph.trans_mat_axes2,'Position');
        set(h,'Position',[.9 0 0.05 .7]);
        
        savename=fullfile(sap.pm.analysis_dir,['TransMat_wo_NRE_',sap.SAPtablename])
        print(gcf,'-dill','-noui',[savename,'_coldfire2.ai']);
        print(gcf,'-dpng','-noui',[savename,'_coldfire2.png']);
        
        close(3);
        
        
    case 'choose_syllable_transition'
        
        axes(sap.gph.trans_mat_axes);
        figure(20);
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
        try delete(sap.gph.uieditnow);        end
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
            'Callback', 'ClassifySAP_sub_routines_04p5(''enter_cluster_number'');');
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
        
        conn = database(sap.databasename, '', '');
        setdbprefs('DataReturnFormat','numeric')
        
        which_cluster_type=get(get(sap.gph.ui_cluster_type_select,'selectedobject'),'UserData');
        %         unique_serials=unique(sap.data(sap.pm.serial_index,:))
        %         rmfield(sap,'syllables');
        h = waitbar(0,'Exporting syllables from each song file...');
        sap.syllables=struct;
        dt_waitbar=0;
        
        % If there is a class classified as NaN, consider that as noise.
        nan_index=find(isnan(sap.data(which_cluster_type,:)));
        sap.data(which_cluster_type,nan_index)=9;
        
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
            
            DAF_index=find(sap.data(sap.pm.stimulated_index,same_serial_index)<0);
            Sound_index=find(sap.data(sap.pm.stimulated_index,same_serial_index)>=0);
            
            [sorted_start_on,sorted_start_on_ind]=sort(sap.data(sap.pm.start_on_index,same_serial_index(Sound_index)));
            sorted_duration=sap.data(sap.pm.duration_index,same_serial_index(Sound_index(sorted_start_on_ind)));
            
            % Only parse sounds, and not stimulated/DAFed region.
            for jj=1:length(sorted_start_on)
                
                ind_1=same_serial_index(jj+1)
                if jj==length(sorted_start_on)
                    ISI=inf;
                else
                    ISI=sap.data(sap.pm.start_on_index,same_serial_index(jj+1))-sap.data(sap.pm.start_on_index,same_serial_index(jj))-...
                        sap.data(sap.pm.duration_index,same_serial_index(jj));
                end
                
                if (sap.data(sap.pm.stimulated_index,same_serial_index(jj)))
                    uplow_func='upper';
                else
                    uplow_func='lower';
                end
                    
                if ISI<sap.pm.ISI_thresh % if note-note interval is more than 200ms, define the end of the song.
                    
                    % because we insert unclassified note as the first
                    % class, we need to +1 for the index to neglect them in this stage.
                    %                     [which_cluster,same_serial_index(jj)]
                    cluster= sap.pm.converting_matrix{sap.data(which_cluster_type,same_serial_index(jj))+1};
                    
                    sap.syllables(ii).note=[sap.syllables(ii).note, feval(uplow_func,cluster)];
                else
                    cluster= sap.pm.converting_matrix{sap.data(which_cluster_type,same_serial_index(jj))+1};
                    sap.syllables(ii).note=[sap.syllables(ii).note, sprintf('%s\n',feval(uplow_func,cluster))];
                    
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
        
        conn = database(sap.databasename, '', '');
        setdbprefs('DataReturnFormat','numeric')
        
        which_cluster_type=get(get(sap.gph.ui_cluster_type_select,'selectedobject'),'UserData');
        %         unique_serials=unique(sap.data(sap.pm.serial_index,:))
        %         rmfield(sap,'syllables');
        h = waitbar(0,'Exporting syllables from each song file...');
        dt_waitbar=0;
        kk=1;
        sap.bout_durations=[];
        sap.N_motif_counts=[];
        sap.bout_stimulated_or_not=[];
        for ii=1:length(str)
            [onset,durations,motif_counts,stimulated]=feval(mfilename,'return_bout_onset_duration_nmotif',str{ii},sap.pm.ISI_thresh);
            if ~isempty(onset)
                ind=find(durations>300);
                motif_counts=motif_counts(ind);
                durations=durations(ind);
                stimulated=stimulated(ind);
                sap.N_motif_counts=[sap.N_motif_counts,motif_counts];
                sap.bout_durations=[sap.bout_durations, durations];
                sap.bout_stimulated_or_not=[sap.bout_stimulated_or_not,stimulated];
            end
            if (ii/length(str)>dt_waitbar)
                waitbar(ii/length(str),h);
                dt_waitbar=dt_waitbar+0.1;
            end
        end
        sap.bout_stimulated_or_not=logical(sap.bout_stimulated_or_not);
        close(h);
        % close(curs);close(conn);
        
        figure(40);setPaperSize([8,8],9);clf;
        
        savename=sprintf('Song_Motif_hist_ISIthresh=%d',sap.pm.ISI_thresh);
        savename=fullfile(sap.pm.analysis_dir, savename);
        bout_duration=sap.bout_durations;
        N_motif_counts = sap.N_motif_counts;
        
        if any(sap.bout_stimulated_or_not)
            ButtonName=questdlg('Detected stimulated/non-stimulated songs. Plot separately?', ...
                'separate plot for bout durations/motif counts', ...
                'YES','NO','YES');
        else
            ButtonName='NO';
        end
        
        switch ButtonName
            case 'YES'
                motif_edges=[0:1:51];
                N_motifs=zeros(2,length(motif_edges));
                [N_motifs(1,:),bin]=hist(sap.N_motif_counts(sap.bout_stimulated_or_not),motif_edges);
                [N_motifs(2,:),bin]=hist(sap.N_motif_counts(~sap.bout_stimulated_or_not),motif_edges);
                
                bout_dur_edges=(0:.05:7);
                N_bout_dur=zeros(2,length(bout_dur_edges));
                [N_bout_dur(1,:),bin]=hist(sap.bout_durations(sap.bout_stimulated_or_not)/1000,bout_dur_edges);
                [N_bout_dur(2,:),bin]=hist(sap.bout_durations(~sap.bout_stimulated_or_not)/1000,bout_dur_edges);
                legend_txt={'stim','no stim'};
            case 'NO'
                motif_edges=[0:1:51];
                [N_motifs,bin]=hist(sap.N_motif_counts,motif_edges);
                bout_dur_edges=(0:.05:7);
                [N_bout_dur,bin]=hist(sap.bout_durations/1000,bout_dur_edges);
                legend_txt=[];
            otherwise
                error('Unknown option!')
        end
        %                 size(tmpdata)
        subplot(2,1,1);
        bar(motif_edges,N_motifs','histc');
        axis([min(motif_edges) max(motif_edges) ylim]);
        xlabel('# of elements in one bout');
        ylabel('frequency')
        title(savename,'FontSize',8);
        text(.1*diff(xlim),.9*diff(ylim),sprintf('Median=%g',median(sap.N_motif_counts)))
        subplot(2,1,2);
        
        bar(bout_dur_edges,N_bout_dur','histc');
        axis([min(bout_dur_edges) max(bout_dur_edges) ylim]);
        text(.1*diff(xlim),.9*diff(ylim),sprintf('Median=%g',median(sap.bout_durations/1000)))
        
        xlabel('bout duration [sec]');
        ylabel('# of bouts');
        
        if isempty(legend_txt)
            % do nothing
        else
            legend(legend_txt);
        end
        
        global sap
        
        notes={sap.syllables(:).note};
        ind=regexp(notes,'\w*i+a+b+c+d+\w*');
        num_stereotyped_bouts=length([ind{:}]);
        try
            num_bouts=length(sap.bout_durations);
        catch
            feval(mfilename,'export_bout_durations');
            num_bouts=length(sap.bout_durations);
        end
        
        song_stereotypy=num_stereotyped_bouts/num_bouts;
        fprintf('Song stereotypy=%g\n',song_stereotypy);
        %
        %         ind=regexp(notes,'\w*i+\w*');
        %         num_bouts_not_calls=length([ind{:}]);
        %
        %         song_stereotypy_wo_call=num_stereotyped_bouts/num_bouts_not_calls;
        %         fprintf('Song stereotypy(without calls)=%g',song_stereotypy_wo_call);
        %         sap.song_stereotypy_wo_call=song_stereotypy_wo_call;
        
        
        save(savename,'bout_duration','N_motif_counts','song_stereotypy');
        print(gcf,'-depsc2',[savename,'.eps']);
        print(gcf,'-dill',[savename,'.ai']);
        print(gcf,'-dpng',[savename,'.png']);
        
    case 'export_syllable_gap_hist'
        if all(sap.data(sap.pm.following_gap_index,1:sap.pm.loaded_N)==0)
            feval(mfilename,'calc_following_gap');
        end
        if any(isnan(sap.data(sap.pm.following_gap_index,1:sap.pm.loaded_N)))
            feval(mfilename,'calc_following_gap');
        end
        
        figure(40);setPaperSize([8,8],9);clf;
        
        savename=sprintf('SyllGap_hist');
        savename=fullfile(sap.pm.analysis_dir, savename);
        edges_gap=2.^[log2(10):.1:13];
        edges_dur=2.^[log2(10):.05:10];
        
        gaps=sap.data(sap.pm.following_gap_index,1:sap.pm.loaded_N);
        gap_n=histc(gaps,edges_gap);
        subplot(2,1,1);
        stairs(edges_gap,gap_n);
        set(gca,'XScale','Log');
        
        axis([min(edges_gap) max(edges_gap) ylim]);
        xlabel('Gap duration [ms]');
        ylabel('frequency')
        title(savename,'FontSize',8);
        text(.01*diff(xlim),.9*diff(ylim),sprintf('Median=%g',nanmedian(gaps)));
        elements_durs=sap.data(sap.pm.duration_index,1:sap.pm.loaded_N);
        dur_n=histc(elements_durs,edges_dur);
        subplot(2,1,2);
        stairs(edges_dur,dur_n);
        
        axis([min(edges_dur) max(edges_dur) ylim]);
        set(gca,'XScale','Log');
        text(.1*diff(xlim),.9*diff(ylim),sprintf('Median=%g',nanmedian(elements_durs)));
        
        xlabel('sound duration [ms]');
        ylabel('frequency');
        
        
        save(savename,'gap_n','dur_n','edges_dur','edges_gap','elements_durs','gaps');
        print(gcf,'-depsc2',[savename,'.eps']);
        print(gcf,'-dill',[savename,'.ai']);
        print(gcf,'-dpng',[savename,'.png']);
        
        %% calc following gap
    case 'calc_following_gap'
        
        %       sap.pm.ISI_thresh=200;
        val=get(sap.gph.ui_select_song_by_filename,'Value');
        str=get(sap.gph.ui_select_song_by_filename,'String');
        
        
        conn = database(sap.databasename, '', '');
        setdbprefs('DataReturnFormat','numeric')
        
        
        h = waitbar(0,'Calculating gaps from each song file...');
        dt_waitbar=0;
        str=get(sap.gph.ui_select_song_by_filename,'String');
        %
        
        for ii=1:length(str)
            sap.pm.same_serial_index=strmatch(str{ii},sap.data_filename);
            [s,sorted_index]=sort(sap.data(sap.pm.start_on_index,sap.pm.same_serial_index));
            sap.pm.same_serial_index=sap.pm.same_serial_index(sorted_index);
            
            %
            
            if isempty(sap.pm.same_serial_index)||length(sap.pm.same_serial_index)==1,
                continue;
            end
            
            
            syllable_start=sap.data(sap.pm.start_on_index,sap.pm.same_serial_index);
            syllable_duration=sap.data(sap.pm.duration_index,sap.pm.same_serial_index);
            syllable_following_gap= diff(syllable_start)-syllable_duration(1:end-1);
            sap.data(sap.pm.following_gap_index,sap.pm.same_serial_index(1:end-1))=syllable_following_gap;
            
            
            
            if (ii/length(str)>dt_waitbar)
                waitbar(ii/length(str),h);
                dt_waitbar=dt_waitbar+0.1;
            end
            
        end
        
        close(h);
        
        
        
    case 'return_bout_onset_duration_nmotif'
        %   [onset,motif_counts,duration]=ClassifySAP_...(filename,sap.pm.ISI_thresh);
        %    or 
        %   [onset,motif_counts,duration]=ClassifySAP_...(filename,sap.pm.ISI_thresh,new_motif_threshold);
        
        filename=varargin{1};
        ISI_thresh=varargin{2};
        
        if nargin>=4
            new_motif_thresh=varargin{3};
            use_predetected_data=0;
        else
            use_predetected_data=1;
        end
        
        onset=[];
        motif_counts=[];
        durations=[];
        stimulated=[];
        
        if (use_predetected_data)
        same_serial_index=strmatch(filename,sap.data_filename);
        end
        
        if isempty(same_serial_index) || (length(same_serial_index)==1)
            varargout{1}=onset;
            varargout{2}=durations;
            varargout{3}=motif_counts;
            varargout{4}=stimulated;
            return;
        end
        
        % at this point, there must be more than two syllables.
        % sort the order of syllables according to the start_on time.
        [sorted_start_on,sort_index]=sort(sap.data(sap.pm.start_on_index,same_serial_index),'ascend');
        
        % same_serial_index must be also sorted in ascending order of start_on.
        same_serial_index=same_serial_index(sort_index);
        sorted_durations=sap.data(sap.pm.duration_index,same_serial_index);
        sorted_stimulated_or_not=sap.data(sap.pm.stimulated_index,same_serial_index);
        
        %
        %             original_ISIs = sap.data(sap.pm.start_on_index,same_serial_index(2:end))-...
        %                 sap.data(sap.pm.start_on_index,same_serial_index(1:end-1))-...
        %                 sap.data(sap.pm.duration_index,same_serial_index(1:end-1));
        
        %    ISI: Inter-syllable intervals (length of gap)
        
        original_ISIs = sorted_start_on(2:end)-sorted_start_on(1:end-1)-sorted_durations(1:end-1);
        
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
            varargout{4}=stimulated;
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
        %             onset=sap.data(sap.pm.start_on_index,same_serial_index(bout_starts(start_index_to_consider)))
        onset=sorted_start_on(bout_starts(start_index_to_consider));
        
        %             durations= ...
        %                 sap.data(sap.pm.start_on_index,same_serial_index(bout_ends(start_index_to_consider)))-...
        %                 sap.data(sap.pm.start_on_index,same_serial_index(bout_starts(start_index_to_consider)))+...
        %                 sap.data(sap.pm.duration_index,same_serial_index(bout_ends(start_index_to_consider)));
        
        durations=sorted_start_on(bout_ends(start_index_to_consider))-...
            sorted_start_on(bout_starts(start_index_to_consider))+...
            sorted_durations(bout_ends(start_index_to_consider));
        
        
        motif_counts=nMotifs(start_index_to_consider);
        stimulated=false(1,length(durations));
        for ii=1:length(durations)
            stimulated(ii)=any(sorted_stimulated_or_not(bout_starts(start_index_to_consider(ii)):bout_ends(start_index_to_consider(ii))));
        end
        
        varargout{1}=onset;
        varargout{2}=durations;
        varargout{3}=motif_counts;
        varargout{4}=stimulated;
        
        
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
        selection=sprintf('in ');
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
                disp('register in teacher data');
                which_cluster_type=sap.pm.cluster_index;
            case 2
                disp('register in (temporally) clustered data');
                which_cluster_type=sap.pm.classified_cluster_index;
            case 3
                which_cluster_type=sap.pm.teacher_cluster_index;
                %             case 4
                %                 which_cluster_type=sap.pm.cluster_index;
            otherwise
                error('Unknown option!');
        end
        
        
        cluster=str2num(cluster{1});
        
        if (cluster<0)||(cluster>10) || ~isscalar(cluster)
            error('cluster number should be [0-9]');
        end
        
        sap.pm.show_column_bools= false(1,size(sap.data,2));
        
        %         which_cluster_type=get(get(sap.gph.ui_cluster_type_select,'selectedobject'),'UserData');
        
        for ii=0:9
            if (sap.pm.cluster_val(ii+1))
                sap.pm.show_column_bools =sap.pm.show_column_bools|(sap.data(which_cluster_type,:)==ii);
            end
        end
        
        %         which_cluster_type=get(get(sap.gph.ui_cluster_type_select,'selectedobject'),'UserData');
        sap.data(which_cluster_type,indx&indy&sap.pm.show_column_bools)=cluster;
        if cluster==0
            sap.data(sap.pm.is_teacher_index,indx&indy&sap.pm.show_column_bools)=0;
        else
            sap.data(sap.pm.is_teacher_index,indx&indy&sap.pm.show_column_bools)=1;
        end
        
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
        ClassifySAP_sub_routines_04p5('estimate_gaussian_mixture');
        
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
        
        % cross validation
        fprintf('==== Cross validation ======\n',class,length(find(train_label>0)))
        sap.pm.accuracy=zeros(3,9);
        for class=1:9
            fprintf('Class(%d):',class);
            train_label=(sap.data(sap.pm.cluster_index,train_index)'==class);
            [predict_label, accuracy, dec_values] = svmpredict(2*train_label-1,  ...
                norm_data(:,train_index)', sap.pm.model(class).param); % test the training data
            sap.pm.accuracy(:,class)=accuracy;
            
            
            %             test_label=sap.data(sap.pm.classified_cluster_index,test_index)'==class;
            %             [predict_label, accuracy, dec_values] = svmpredict(2*test_label-1,  ...
            %                 norm_data(:,test_index)', sap.pm.model(class).param); % test the training data
            %             fprintf('\n')
        end
        
        
        %     case 'predict_svm'
        test_ind=find(~sap.data(sap.pm.is_teacher_index,:));
        norm_data=sap.data(sap.pm.classify_dim_index,:);
        norm_data=norm_data./repmat(std(norm_data,[],2),1,size(norm_data,2));
        
        fprintf('==== Below lines show accuracy =0 because now we predict classes (no way to test accuracy), So please neglect the below lines...=====\n')
        for class=1:9
            [predict_label, accuracy, dec_values] = svmpredict(randn(length(test_ind),1),  ...
                norm_data(:,test_ind)', sap.pm.model(class).param); % test the training data
            sap.accuracy=accuracy;
            ind=find(predict_label==1);
            sap.data(sap.pm.classified_cluster_index,test_ind(ind))=class;
            ind=find(sap.data(sap.pm.cluster_index,train_index)==class);
            sap.data(sap.pm.classified_cluster_index,train_index(ind))=class;
        end
        ind=find(isnan(sap.data(sap.pm.classified_cluster_index,:)));
        sap.data(sap.pm.classified_cluster_index,ind)=0;
        
        cross_val_threshold=99;
        if any(sap.pm.accuracy(1,:)<cross_val_threshold)
            warning('Some class has cross validation results less than %g%% accuracy, please manually label more syllables.\n',cross_val_threshold);
        end
        
        feval(mfilename,'redraw_clusters');
        feval(mfilename,'redraw');
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
        
        if nargin>=3
            data_type=varargin{2};
        else
            ButtonName = questdlg('Is this data from CBR (Contingent Buffered Recording) mode in KinkaChronic.m?', ...
                'Color Question', ...
                'Yes', 'No', 'Cancel', 'No');
            switch ButtonName,
                case 'Yes',
                    data_type='cbr_mode';
                    sap.gph.aligned_vol_fig=figure(21);clf;
                case 'No',
                    data_type='';
                case 'Cancel',
                   return;
            end % switch

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
        sap.voldata=struct;
        vol_legend_h=[];
        legend_txt=[];
                        
        for val=1:length(str)
            
            if jj>=max_N+1, break; else fprintf('jj=%d (val=%d,maxN=%d)\n',jj,val,max_N);end
            % determine which file to read
            sap.pm.filename=str{val};
            set(sap.gph.ui_select_song_by_filename,'Value',rand_index(val));
            drawnow;
            % now find the note that matches detect_pattern.
            %                fprintf('note=s%s ',sap.syllables(val).note);
            
            % now, find the notes that belongs to this file.
            same_serial_index = strmatch(sap.pm.filename,sap.data_filename);
            index_sounds=sap.data(sap.pm.classified_cluster_index,same_serial_index);
            stimindex=sap.data(sap.pm.stimulated_index,same_serial_index);
            stimindex=find(stimindex>0);
            
            str2=sap.pm.converting_matrix(index_sounds+1);
            str2=[str2{:}];
            % change the stimulated syllable into upper case letter.
            str2(stimindex)=upper(str2(stimindex));
            
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
                
                txt=strrep(sprintf('wavfile: %s',sap.pm.filename),'_','\_');
                
                [sap.pm.song,sap.pm.Fsong]=wavread(fullfile(sap.pm.sound_dir,strrep(sap.pm.filename,'.mat','.wav')));
                
                sap.pm.feature.m_spec_deriv=sam_spectrum_deriv5(sap.pm.song,sap.pm.Fsong);
                
                sap.gpm.max_spec=max(max(sap.pm.feature.m_spec_deriv));
                min_spec=min(min(sap.pm.feature.m_spec_deriv));
                
                t=linspace(0,length(sap.pm.song)/sap.pm.Fsong,size(sap.pm.feature.m_spec_deriv,1));
                f=sap.pm.Fsong*(1:size(sap.pm.feature.m_spec_deriv,2))*1000/1024;
                
                
                for ll=1:length(ending_index)
                %                 sap.pm.show_sonogram_index=show_index_local(sap.pm.minind);
                sap.pm.show_sonogram_index=same_serial_index(ending_index(ll));
                onset_timing=unique(sap.data(sap.pm.start_on_index,sap.pm.show_sonogram_index)/1000);
                if isempty(onset_timing), continue;end
                onset_timing=onset_timing(1);
                %                 fprintf('%s starts at %g sec\n',search_pattern,onset_timing);
                
              
                h(jj)=mysubplot(max_N,1,jj,1);
                imagesc(t-onset_timing,f,sap.pm.feature.m_spec_deriv');
                
                feval(mfilename,'draw_bout_durationbar',h(jj),onset_timing);
                feval(mfilename,'show_classification',h(jj),onset_timing);
                
                colormap gray;
                cutoff=0.004;
                %                    text(min(xlim)+diff(xlim)*.05,max(ylim)-diff(ylim)*.1,sprintf('trial=%d',val));
                ylabel(sprintf('trial=%d',rand_index(val)));
                
                set(h(jj),'CLim',cutoff*[-1 1]*sap.gpm.max_spec,'YDir','Normal');
                set(h(jj),'Color',[.5 .5 .5]);
                
                
                switch data_type,
                    case 'cbr_mode',
                        load(fullfile(sap.pm.sound_dir,strrep(sap.pm.filename,'.wav','.mat')));
                        
                        sap.voldata(jj).v=wavedata(1:3:end,2);
                        sap.voldata(jj).offset=onset_timing;
                        sap.voldata(jj).Fs=sap.pm.Fsong/3;
                        
                        figure(sap.gph.aligned_vol_fig);
                        sap.voldata(jj).medv=my_medfilt1(sap.voldata(jj).v,ceil(0.005*sap.voldata(jj).Fs));
                        t=linspace(0,length(sap.voldata(jj).medv)/sap.voldata(jj).Fs,length(sap.voldata(jj).medv));
                        vol_legend_h(jj)=plot(t-sap.voldata(jj).offset,(sap.voldata(jj).medv-median(sap.voldata(jj).medv))*100,'Color',sap.pm.CS(jj,:)); hold on;
                        legend_txt{jj}=sprintf('trial=%d, mean V=%1.3gmV',rand_index(val),median(sap.voldata(jj).medv)*100);
                        figure(sap.gph.amplitude_img_fig);
                    case '',
                        % do nothing
                    otherwise
                end
                
                if jj<max_N
                    if (jj==1)
                        title(strrep(sprintf('Spectrum_iii.%s_in_%s',strrep(align_pattern,'.',''),strrep(detect_pattern,'\','')),'_','\_'));
                    end
                    set(h(jj),'XTickLabel',[],'YTickLabel',[]);
                    jj=jj+1;
                elseif jj>=max_N
                    jj=jj+1;  break;
                end
                  
                end
            else
                fprintf('Not found!\n')
            end
            
        end
        
         switch data_type,
                    case 'cbr_mode',
                        figure(sap.gph.aligned_vol_fig);
                        legend(vol_legend_h,legend_txt);
                        h=[h,gca];
                        figure(sap.gph.amplitude_img_fig);
                    case '',
                        % do nothing
                    otherwise
         end
                
        linkaxes(h,'x');
        if isscalar(N)
            Ntxt=sprintf('%d',N);
        else
            Ntxt={sprintf('%d_',N)};
            Ntxt=Ntxt{1};Ntxt=Ntxt(1:end-1);
        end
        savename=fullfile(sap.pm.analysis_dir,sprintf('Spectrum_iii.%s_in_%s_N=%s',strrep(align_pattern,'.',''),strrep(detect_pattern,'\',''),Ntxt));
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
        savename=fullfile(sap.pm.analysis_dir,sprintf('iii.%s_in_%s_%s',strrep(align_pattern,'.',''),strrep(detect_pattern,'\',''),plot_quantity));
        print(gcf,'-dpng',[savename,'.png']);
        print(gcf,'-depsc2',[savename,'.eps']);
        print(gcf,'-dill',[savename,'.ai']);
        AmpImg=sap.pm.ampImg;
        save([savename,'.mat'],'AmpImg');
        
    case 'show_features_to_make_templates'
        
        if isempty(sap.gph.template_feature_fig)||~ishandle(sap.gph.template_feature_fig)
            sap.gph.template_feature_fig=TemplateMaker_subroutine_0p1('init',sap);
        end
        TemplateMaker_subroutine_0p1('draw_sonogram_features',sap.pm.MotifThreshold);
        %         show_features_mean_std;
        
    case 'print_sonogram'
        figure(22);clf;
        
        if nargin==2
            time_range=varargin{1};
            wavout_name=fullfile(sap.pm.analysis_dir,[strrep(sap.pm.filename,'.wav',('')),sprintf('t=[%1.2g_%1.2g]',time_range(1),time_range(2))]);
            
        elseif nargin==3
            time_range=varargin{1};
            wavout_name=varargin{2};
        elseif nargin==1
            time_range=get(sap.gph.sonogramAxes,'XLim');
            wavout_name=fullfile(sap.pm.analysis_dir,[strrep(sap.pm.filename,'.wav',('')),sprintf('t=[%1.2g_%1.2g]',time_range(1),time_range(2))]);
        else
            error('option number is wrong!')
        end
        fprintf('Using t_range=[%1.2g_%1.2g], wav_outputfile=%s.wav\n',time_range(1),time_range(2),wavout_name);
        
        
        
        
        
        sap.pm.feature.m_spec_deriv=sam_spectrum_deriv5(sap.pm.song,sap.pm.Fsong);
        
        
        sap.gpm.max_spec=max(max(sap.pm.feature.m_spec_deriv));
        min_spec=min(min(sap.pm.feature.m_spec_deriv));
        
        t=linspace(0,length(sap.pm.song)/sap.pm.Fsong,size(sap.pm.feature.m_spec_deriv,1));
        f=sap.pm.Fsong*(1:size(sap.pm.feature.m_spec_deriv,2))/1024/1000;
        
        
        
        width = diff(time_range)*8;         % Initialize a variable for width.
        height = 4;          % Initialize a variable for height.
        dx1=.5;
        dx2=.5;
        dy=1;
        papersize=[width+dx1+dx2,height+2*dy];
        setPaperSize(papersize,12);clf;
        %         set(gcf, 'PaperUnits', 'centimeters');
        %         set(gcf, 'PaperSize', papersize);
        h=axes('Position',[dx1/(width+dx1+dx2),dy/(height+2*dy),width/(width+dx1+dx2),height/(height+2*dy)]);
        imagesc(t,f,sap.pm.feature.m_spec_deriv'); %shading interp; view(0,90);
        colormap gray;
        %          cutoff=0.004;
        cutoff=sap.pm.sonogram_caxis_cutooff;
        %                    text(min(xlim)+diff(xlim)*.05,max(ylim)-diff(ylim)*.1,sprintf('trial=%d',val));
        title(strrep(sap.pm.filename,'_','\_'));
        set(gca,'CLim',sap.pm.sonogram_caxis_cutooff*[-1 1]*sap.gpm.max_spec,'YDir','Normal','XLim',time_range);
        
        %          set(gca,'CLim',cutoff*[-1 1]*sap.gpm.max_spec,'YDir','Normal');
        set(gca,'Color',[.5 .5 .5]);
        
        
        feval(mfilename,'draw_bout_durationbar',gca,0);
        feval(mfilename,'show_classification',gca,0);
        
        %         savename=fullfile(sap.pm.analysis_dir,sap.pm.filename);
        print(gcf,'-dpng',[wavout_name,'.png']);
        print(gcf,'-dtiff',[wavout_name,'.tiff']);
        t=linspace(0,length(sap.pm.song)/sap.pm.Fsong,length(sap.pm.song));
        index=find((t>time_range(1)).*(t<=time_range(2)));
        wavwrite(sap.pm.song(index),sap.pm.Fsong,16,[wavout_name,'.wav']);
        
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
        
    case 'change_syllable_threshold'
        
        
    otherwise
        error('Unknown option')
end




function [flag] = myzoomcallback(obj,event_obj)
% If the tag of the object is 'DoNotIgnore', then return true.
objTag = get(obj,'Tag');
if strcmpi(objTag,'DoNotIgnore')
    flag = true;
else
    flag = false;
end
