function dat2mat(filename)
% convert ASCII format ABCD.dat file into ABCD.mat format. 
% Usage: dat2mat(filename) convert one file. 
% Usage: dat2mat           open userinterface to convert a .dat file.
% 
% The variable in .dat is saved as 'data'.
% This function overwrite the existing file, so be careful to use.
%% by KH 20080623.


if nargin==0 % If there is no input.
    [filename, pathname, filterindex] = uigetfile('*.dat', 'Pick data (.dat) file(s)','MultiSelect', 'on');
        
else     % filename is assigned.
    
    if isdir(filename) || nargin>1% This is the directory name.
        error(['dat2mat input is a filename; dat2mat(filename). To convert multiple files, type dat2mat;'])
    end   
       
end


if ischar(filename)==1 % filename is char.
    fprintf('...converting')
    data=load([pathname,filename]);
    save([pathname,filename(1:end-4),'.mat'],'data');
    fprintf('.done: saved in %s \n',[pathname,filename(1:end-4),'.mat']);
else                   % filename is cell array.
    for ii=1:length(filename)
        fprintf('...converting')
        try
        data=load([pathname,filename{ii}]);
        save([pathname,filename{ii}(1:end-4),'.mat'],'data');      
        fprintf('.done: saved in %s \n',[pathname,filename{ii}(1:end-4),'.mat']);
        catch 
             fprintf('.FAILED: bad file: %s \n',[pathname,filename{ii}(1:end-4),'.mat'])
        end
    end
end