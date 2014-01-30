function out = cplot(data)
% from Ohnishi's home page.
% modified by K.H. 2002.Apr.22
% data must be in the matrix shape.

%%%%%%%%% $B%U%)%s%H%5%$%:;XDj(B %%%%%%%%%%
fontsize = 14;
%%%%%%%%% $B<4$N%i%Y%k;XDj(B %%%%%%%%%%
xla = 'num of neuron'; yla = 'num of neuron';
%%%%%%%%% x,y $B$NHO0O$H$+$r;XDj(B%%%%%%%%%%
[x,y] = size(data) ;

xmin = 1; xmax = x; xtics = 1;
ymin = 1; ymax = y; ytics = 1;
zmin = 0; zmax = 64;
%%%%%%%%% $B%0%i%U$N=q<0(B %%%%%%%%%%
iro = hot; % $B9u"*@V$G(B z $B$rI=<((B(gray$B$J$iGr9u(B)
G = [0.22 0.2 0.7 0.75]; % [left bottom width height]$B$G;XDj(B

%======== $B0J2<$O$3$N$^$^;H$($PNI$$(B ===================
[x,y] = meshgrid(xmin:xtics:xmax, ymin:ytics:ymax); % x-y$B$NHO0O;XDj(B
subplot('position',G); % $B%0%i%U$NBg$-$5$H0LCV;XDj(B
image(data'); % $B9TNs(B mat $B$NE>CV$r%a%C%7%e$GI=<((B

axis([xmin xmax ymin ymax]);
shading flat; % $B6-3&@~$J$7$K$9$k(B
view(0,90); % $BFs<!85>e$K(B z $B$r?'$GI=<((B
xlabel(xla); ylabel(yla); % $B%i%Y%k$N;XDj(B
set(gca,'FontSize',fontsize);
xlbl = get(gca,'XLabel'); set(xlbl,'FontSize',fontsize);
ylbl = get(gca,'YLabel'); set(ylbl,'FontSize',fontsize);
zlbl = get(gca,'ZLabel'); set(zlbl,'FontSize',fontsize);
% x,y $B$N?tCM%i%Y%k$N;XDj(B
%X = [xmin -1 0 1 xmax]; Y = [ymin -0.25 0 0.25 ymax];
%set(gca,'XTick',X); set(gca,'YTick',Y);
colormap(iro);
ccc=colorbar;
axes(ccc);
axis([xlim,zmin,zmax]);
set(ccc,'FontSize',fontsize);
%print -depsc2 mat.ps % ps file $B$r:n@.(B