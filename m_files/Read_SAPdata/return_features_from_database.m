function [data,colname]=return_features_from_database(load_table_name,cluster)
% 
% [data,colname]=return_features_from_database(load_table_name,cluster)
% 
% by KH 2010

if isempty(load_table_name)
            pwd_now=pwd;
            sql_dir='C:\mysql\data\mysql\';
            cd(sql_dir);
%             s=sprintf('%s.MYD',[sap.SAPtablename,'_x']);
            [load_table_name, pathname] = uigetfile( ...
                {[s,';*.MYD;*.myd']; '*.*'},...
                'SELECT a table to load classified data');
            cd(pwd_now);
end

if isempty(cluster)
    prompt={'which cluster to load?'};
    name='load one cluster from a database';
    numlines=1;
    defaultanswer={'1'};
    
    cluster=inputdlg(prompt,name,numlines,defaultanswer);
    cluster=str2num(cluster{1});
end
      
            logintimeout(5);
            fprintf('Loading table from %s\n',strrep(load_table_name,'.MYD',''));
            conn = database('mysql', '', '');
            setdbprefs('DataReturnFormat','numeric')
            conn_txt=sprintf('select * from %s where classified=%d ',strrep(load_table_name,'.MYD',''),cluster);
            fprintf('%s\n',conn_txt);
            curs = exec(conn, conn_txt);
            curstmp = fetch(curs,10000);
            if strcmp(curstmp.Message,'Invalid Cursor')
                error(curs.Message);
                 close(curs); close(conn);
                return;
            end
            data=curstmp.data';
            colname=columnnames(curstmp); colname=strrep(colname,'''','');colname=strsplit(colname,',');
            close(curs); close(conn);
          
         
         
                
            