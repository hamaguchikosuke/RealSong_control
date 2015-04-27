%% Here is an example of how to connect mysql server from matlab.
% First, I downloaded mysql JDBC connector from 
% http://dev.mysql.com/downloads/connector/j/
% and put it in my matlab path. 
% 
% dynamically addpath to JAVA program.
% javaaddpath({'C:\home\matlab\DataAnalysis\Read_SAPdata\mysql-connector-java-3.1.14-bin.jar'});


% URL format for MySQL is like this: jdbc:mysql://localhost/DATABASENAME 
% database('DATABASENAME','username','password','com.mysql.jdbc.Driver', url)

url = 'jdbc:mysql://localhost/awakeintra';
conn = database('awakeintra', 'root', '', 'com.mysql.jdbc.Driver', url);

% ping(conn)


if isconnection(conn)
% SQL query to get all fields from A table.
curs = exec(conn,'SELECT * FROM blu984m_20120917');
curs = fetch(curs);

data = curs.data; % Actual data.

end

close(conn);