function [data,colname]=return_features_from_database2(load_table_name,cluster)
%
% [data,colname]=return_features_from_database2(load_table_name,cluster);
% Input: load_table_name. This should be found in C:\mysql\data\mysql\
%        cluster:       a scholar or 'all'.
% 
% [data,colname]=return_features_from_database2(load_table_name,'all');
% returns all the data
% [data,colname]=return_features_from_database2(load_table_name,1);
% returns cluster1 data.
% 
% by KH 2010.Dec.07 

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
    do_get_all=0;
elseif ischar(cluster)
    if strmatch(cluster,'all');
        do_get_all=1;
    else
        error('Unknown option!: ''all''')
    end
end

logintimeout(5);
fprintf('Loading table from %s\n',strrep(load_table_name,'.MYD',''));
conn = database('mysql', '', '');
setdbprefs('DataReturnFormat','numeric')
if (do_get_all)
    conn_txt=sprintf('select * from %s ',strrep(load_table_name,'.MYD',''));
else
    conn_txt=sprintf('select * from %s where classified=%d ',strrep(load_table_name,'.MYD',''),cluster);
end
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




