function out = setPaperSize(w,varargin)
% setPaperSize([width,height]), in centimeter.
% setPaperSize([width,height],fontsize); you can set fontsize also. Default is 10pt.
%

clf;
set(0,'DefaultFigurePaperPositionMode','manual')
set(gcf,'Units','centimeters','PaperUnit','centimeters');
papersize = get(gcf,'PaperSize');
graphsize = get(gcf,'PaperPosition');

w0 = graphsize(3);
h0 = graphsize(4);
if length(w)==2
        h = w(2);
        w = w(1);
else    
        h = h0*w/w0;
end
left = (papersize(1)-w)/2;
bottom = (papersize(2)-h)/2; 

myfiguresize = [left, bottom, w, h];

set(gcf,'PaperPosition',myfiguresize,'PaperPositionMode','manual');

% h = axes('Position',[.2 .2 .75 .75],'FontName','times');
h = axes('Position',[.15 .15 .75 .75]);
if nargin >=2
    ftsize = varargin{1};
else
    ftsize = 10;
end
set(gca,'FontName','Arial','FontSize',ftsize);