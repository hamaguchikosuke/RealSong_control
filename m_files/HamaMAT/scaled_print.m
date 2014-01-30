function scaled_print(h,time_range,varargin)
% print figure with x-axis scale adjusted,
% so that same length is printed in the same figure width. 
% 
%
%
% by KH

width = diff(time_range)*8;         % Initialize a variable for width.
height = 4;          % Initialize a variable for height.
dx1=.5;
dx2=.5;
dy=1;
target_size=[width+dx1+dx2,height+2*dy];

papersize = get(h,'PaperSize');
graphsize = get(h,'PaperPosition');

left = (papersize(1)-target_size(1))/2;
bottom = (papersize(2)-target_size(2))/2; 

myfiguresize = [left, bottom, target_size];

set(gcf,'PaperPositionMode','manual','PaperPosition',myfiguresize);

print(h, varargin{:});
