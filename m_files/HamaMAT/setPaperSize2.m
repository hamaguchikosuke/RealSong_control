function out = setPaperSize2(w,varargin)
% setPaperSize(size) size is in centimeter.
% setPaperSize(size,gcf). without clf;
%
%
if nargin>=2
    current_fig = varargin{1}
else
    currnet_fig = gcf;
    clf;
end


set(current_fig,'PaperUnit','centimeters')
papersize = get(current_fig,'PaperSize');
graphsize = get(current_fig,'PaperPosition');

w0 = graphsize(3);
h0 = graphsize(4);

h = h0*w/w0;
left = (papersize(1)-w)/2;
bottom = (papersize(2)-h)/2; 

myfiguresize = [left, bottom, w, h];

set(current_fig,'PaperPosition',myfiguresize);
% h = axes('Position',[.2 .2 .75 .75],'FontName','times');
h = axes('Position',[.15 .15 .75 .75]);

