function out=reshape_in_window(v,window_size,direction)
%  reshape_in_window can reshape NxM matrix into 
%  different element sized matrix, such as (window_size) x (N*N_window),
%  as oppose to standard reshape() command does not allow changing element
%  size. 
% 
%  ex) 
%  v=[1:100;1:100;1:100];
%  window_size=10;
%  direction=2;
%  out=reshape_in_window(v,window_size,direction);
%  
%  which will generate 3 columns of 
%  [1:10;11:20;21:30;31:40;41:50;51:60;61:70;71:80;81:90;91:100];
%
% 
%  
% 
%  by KH 20110428

if nargin<=2
    direction=1; % function(windowed(v),direction);
end

L=size(v,direction); % length of data 
NWindow=floor(L/(window_size)); % numner of window
N=size(v,3-direction);  % number of data session. 

if L<window_size
    error('the length of the data (%d) in this direction is smaller than window_size(%d)!',L,window_size);
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
out=v;