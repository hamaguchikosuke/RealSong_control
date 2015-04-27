
conn = database('awakeintra', 'root', 'sap2011');
% setdbprefs('DataReturnFormat','cellarray');
% curs = exec(conn,'show tables');
% tablenames = fetch(curs);
% tablenames=tablenames.Data;
% 
% [s,v] = listdlg('PromptString','SELECT a table to load:',...
%     'SelectionMode','single',...
%     'ListString',tablenames,...
%     'ListSize',[250 500],...
%     'Name',['Load Database in ' 'awakeintra']);
% if (v)
%     sap.SAPtablename_old=tablenames{s};
% else
%     disp('No table selected!');
%     return;
% end

%%
 e = exec(conn,['create table BULKTEST (salary decimal, '...
   'player varchar(25), signed_date varchar(25), '...
   'team varchar(25))']);
close(e)

A = {100000.00,'KGreen','06/22/2011','Challengers'};
A = A(ones(10000,1),:);

fid = fopen('c:\temp\tmp.txt','wt');
for i = 1:size(A,1)
   fprintf(fid,'%10.2f \t %s \t %s \t %s \n',...
   A{i,1},A{i,2},A{i,3},A{i,4});
end
fclose(fid);

e = exec(conn,['load data local infile '...
   ' ''C:\\temp\\tmp.txt'' into table BULKTEST '...
   'fields terminated by ''\t'' lines terminated '...
   'by ''\n''']);

close(e);
%%
e = exec(conn, 'select * from BULKTEST');
results = fetch(e)
