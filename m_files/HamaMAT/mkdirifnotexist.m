function mkdirifnotexist(dir)
% mkdir if 'dir' does not exit.
% 
% by K.H.

try
    current_dir = pwd;
    eval(['cd ',dir])
     eval(['cd ',current_dir])
catch
    eval(['!mkdir ',dir])
end