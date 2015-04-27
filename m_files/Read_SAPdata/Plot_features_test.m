 
            pwd_now=pwd;
            sql_dir='C:\mysql\data\mysql\';
            cd(sql_dir);
%             s=sprintf('%s.MYD',[sap.SAPtablename,'_x']);
            [load_table_name, pathname] = uigetfile( ...
                {[s,';*.MYD;*.myd']; '*.*'},...
                'SELECT a table to load classified data');
            cd(pwd_now);
            
            prompt={'which cluster to load?'};
            name='load one cluster from a database';
            numlines=1;
            defaultanswer={'1'};
            
            which_cluster=inputdlg(prompt,name,numlines,defaultanswer);
            which_cluster=str2num(which_cluster{1});
            
            list_of_features={'duration','mean_pitch','mean_FM','mean_entropy','mean_gpitch'}
            n=listdlg('PromptString','Select features to plot (at maximum three)','ListString',list_of_features); 
            
           
            logintimeout(5);
            fprintf('Loading table from %s\n',strrep(load_table_name,'.MYD',''));
            conn = database('mysql', '', '');
            setdbprefs('DataReturnFormat','numeric')
            conn_txt=sprintf('select * from %s where classified=%d ',strrep(load_table_name,'.MYD',''),which_cluster);
            fprintf('%s\n',conn_txt);
            curs = exec(conn, conn_txt);
            curs = fetch(curs,sap.pm.max_load_N);
            data=curs.data';
            colname=columnnames(curs); colname=strrep(colname,'''','');colname=strsplit(colname,',');
          close(curs); close(conn);
            
            figure(20);
            if length(n)==1
                ind1=strmatch(list_of_features{n(1)},colname);
                plot(rand(length(data(ind1,:)),1),data(ind1,:),'k.');
%             plot(1:length(data(ind1,:)),data(ind1,:),'k.');
            elseif  length(n)==2
                ind1=strmatch(list_of_features{n(1)},colname);
                ind2=strmatch(list_of_features{n(2)},colname);
                plot(data(ind1,:),data(ind2,:),'r.');
            elseif  length(n)==3
                ind1=strmatch(list_of_features{n(1)},colname);
                ind2=strmatch(list_of_features{n(2)},colname);
                ind3=strmatch(list_of_features{n(3)},colname)
                plot3(data(ind1,:),data(ind2,:),data(ind3,:),'r.');
            else 
                error('max variables to plot is three!');
            end
                
            