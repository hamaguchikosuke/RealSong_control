function [h1,h2] = OverlayPlot(X1,Y1,X,N)
%
% Overlay plot the line plot on the bar graph.
% Usage:OverlayPlot(X1,Y1,X,N)
%
% by K.H. 30.Mar.2003

clf

bar(X,N);
h1 = gca;
set(h1,'XLim',[X1(1),X1(end)]);
set(h1,'YAxisLocation','right');

h2 = axes('Position',get(h1,'Position'));
plot(X1,Y1,'LineWidth',2)
set(h2,'YAxisLocation','left','Color','none','XtickLabel',[]);
set(h2,'Layer','top');

%xlimits = get(h1,'XLim');
ylimits1 = get(h1,'YLim');
ylimits2 = get(h2,'YLim');

%incN = size(get(h2,'YTick'),2)
%xinc = (xlimits(2)-xlimits(1))/5;

yinc1 = (ylimits1(2)-ylimits1(1))/5;
yinc2 = (ylimits2(2)-ylimits2(1))/5;

set(h1,'YTick',[ylimits1(1):yinc1:ylimits1(2)]);
set(h1,'YTickLabel',[ylimits1(1):yinc1:ylimits1(2)]);
set(h2,'YTick',[ylimits2(1):yinc2:ylimits2(2)]);
set(h2,'YTickLabel',[ylimits2(1):yinc2:ylimits2(2)]);

grid on