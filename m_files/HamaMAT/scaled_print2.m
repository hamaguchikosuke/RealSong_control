function scaled_print2(h,time_range,scaling,varargin)
% print figure with x-axis scale adjusted,
% so that same length is printed in the same figure width. 
% scaled_print(h,time_range,scaling)
% h: figure handle.
% time_range: time range to plot. 
% scaling: by default, 8 = (8cm/1 unit in x-axis.)
% 
% 
% scaled_print(gcf,time_range,scaling,)
% by KH
set(h,'PaperUnits','centimeters');
pos=get(h,'Position');

% scaling
% varargin{:}
if isempty(scaling) || ischar(scaling)   
    varargin = {scaling,varargin{:}};
    scaling=8;
end

% size of the figure is made from
% y-label + width of the axis 
width = diff(time_range)*scaling;         % Initialize a variable for width.
height = 4;          % Initialize a variable for height.
Left=1;
Right = 1;

Bottom=1;
Top   =1;

target_size=[width+Left+Right,height+Bottom+Top];

% papersize = get(h,'PaperSize');
% graphsize = get(h,'PaperPosition');

% left = (papersize(1)-target_size(1))/2;
% bottom = (papersize(2)-target_size(2))/2; 

myfiguresize = [Left Bottom, target_size];

set(h,'PaperPositionMode','manual','PaperPosition',myfiguresize);
set(h,'Position',[pos(1) pos(2) width*50 height*50]);
print(h, varargin{:});
