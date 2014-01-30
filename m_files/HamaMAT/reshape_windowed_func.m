function out=reshape_windowed_func(func,v,window_size,direction,varargin)
%  reshape NxM matrix into (window_size) x (N*N_window)
%  and calculate func(reshaped_matrix,direction).
%  You can set the direction of the data; 1: columm wise, 2: row wise.
%  
%  ex) 
%  v=[1:100];
%  window_size=10;
%  func=@sum;
%  direction=2;
%  out=reshape_windowed_func(func,v,window_size,direction);
%  
%  which is equivalent to calculate 
% x=[1:10;11:20;21:30;31:40;41:50;51:60;61:70;71:80;81:90;91:100];
% sum(x,direction);
% 
%  
% 
%  by KH 20110428

if nargin<=3
    direction=1; % function(windowed(v),direction);
end

L=size(v,direction); % length of data 
NWindow=floor(L/(window_size)); % numner of window
N=size(v,3-direction);  % number of data session. 

if L<window_size
    error('the length of the data in this direction is smaller than window_size!');
end
switch direction
    case 1
        v=v(1:ceil(window_size*NWindow),:);
        v=reshape(v,[window_size,NWindow*N]);
    case 2
        v=v(:,1:ceil(window_size*NWindow));
        v=reshape(v',[window_size,NWindow*N])';
    otherwise
        error('Only for 2-D matrix! (direction can be 1 or 2)');
end
out=feval(func,v,3-direction);