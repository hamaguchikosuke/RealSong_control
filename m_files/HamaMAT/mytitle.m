function out = mytitle(command,ttl,MxN,i,opt)
% Usage: mytitle(command,title,MxN,i,opt)
% opt: upright,upleft,downright,downleft.
% In subplot figure, do command only at the 'opt' position.
% ex) mytitle('xlabel','time [ms]',[3 2],i,'downleft');
% results in the following figure.
%  [  ]   [  ]
%  [  ]   [  ]
%  [  ]   [  ]
% time [ms]
N = MxN(2);
M = MxN(1);
switch lower(opt)
    case 'upright';         ind = N;
    case 'upleft';          ind = 1;
    case 'downleft';        ind =  N*(M-1)+1;
    case 'downright';       ind = M*N;
    otherwise
        error(['Unknown option']);
end
if i == ind
    feval(command,ttl);
end