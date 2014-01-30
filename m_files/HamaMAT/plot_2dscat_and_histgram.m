function [N1,Xgrid,N2,Ygrid,h1,h2,h3]=plot_2dscat_and_histgram(x,y,Xgrid,Ygrid,varargin)
% % Plot 2D scatter plot and their histgram below X axis and next to Y axis.
% usage: plot_2dscat_and_histgram(x,y,Xgrid,Ygrid)
% usage: plot_2dscat_and_histgram(x,y,Xgrid,Ygrid,title,xlabel,ylabel)
% % ex)
% x = randn(1,500); Xgrid = [-2:.1:2];
% y = randn(1,500); Ygrid = [-2:.1:2];
% [N1,Xgrid,N2,Ygrid]=plot_2dscat_and_histgram(x,y,Xgrid,Ygrid);
%  where N1 and N2 are histgram of x and y.
% [N1,Xgrid,N2,Ygrid,h1,h2,h3]=plot_2dscat_and_histgram(x,y,Xgrid,Ygrid);
%  where h1, h2, h3 are the axes handle of the three axes.
%
% % you can also put title and xlabel, ylabel.
% title_txt = 'test of plot\_2dscat\_and\_histgram';
% xlabel_txt = 'var1'; ylabel_txt = 'var2';
% [N1,Xgrid,N2,Ygrid]=plot_2dscat_and_histgram(x,y,Xgrid,Ygrid,title_txt,xlabel_txt,ylabel_txt);
% 
% % by K.H. 20080321

xmax = max(Xgrid);
xmin = min(Xgrid);
ymax = max(Ygrid);
ymin = min(Ygrid);

if nargin>=5
    titlelabel = varargin{1};
else
    titlelabel= ['Distribution of max-min(rate) and max-min(CV_2) over population'];
end


if nargin>=6
    xlabel_txt = varargin{2};
else
    xlabel_txt= ['max-min(rate)'];
end


if nargin>=7
    ylabel_txt = varargin{3};
else
    ylabel_txt= ['max-min(CV_2)'];
end

h1=axes('Position',[.3 .3 .6 .6])
plot(x,y,'o','MarkerSize',3);
axis([xmin xmax ymin ymax]);
title(titlelabel);


h2=axes('Position',[.3 .1 .6 .1])
N1=histc(x,Xgrid);
bar(Xgrid,N1,'histc')
xlabel(xlabel_txt);
axis([xmin xmax ylim]);


h3=axes('Position',[.1 .3 .1 .6])
N2=histc(y,Ygrid);
barh(Ygrid,N2,'histc')
axis([xlim ymin ymax]);
ylabel(ylabel_txt);