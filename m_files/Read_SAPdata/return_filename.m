function [filename,timevec]=return_filename(data)

% return something like 7814_400083365_7_14_8_4_40.wav
%                       recnum serial  m  d h m s
filename=sprintf('%d_%d_%d_%d_%d_%d_%d',data(3),data(2),data(19),data(20),data(21),data(22),data(23));
timevec=[data(19),data(20),data(21),data(22),data(23)];