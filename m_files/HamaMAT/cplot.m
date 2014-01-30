function out = cplot(data)
% from Ohnishi's home page.
% modified by K.H. 2002.Apr.22
% data must be in the matrix shape.

%%%%%%%%% フォントサイズ指定 %%%%%%%%%%
fontsize = 14;
%%%%%%%%% 軸のラベル指定 %%%%%%%%%%
xla = 'num of neuron'; yla = 'num of neuron';
%%%%%%%%% x,y の範囲とかを指定%%%%%%%%%%
[x,y] = size(data) ;

xmin = 1; xmax = x; xtics = 1;
ymin = 1; ymax = y; ytics = 1;
zmin = 0; zmax = 64;
%%%%%%%%% グラフの書式 %%%%%%%%%%
iro = hot; % 黒→赤で z を表示(grayなら白黒)
G = [0.22 0.2 0.7 0.75]; % [left bottom width height]で指定

%======== 以下はこのまま使えば良い ===================
[x,y] = meshgrid(xmin:xtics:xmax, ymin:ytics:ymax); % x-yの範囲指定
subplot('position',G); % グラフの大きさと位置指定
image(data'); % 行列 mat の転置をメッシュで表示

axis([xmin xmax ymin ymax]);
shading flat; % 境界線なしにする
view(0,90); % 二次元上に z を色で表示
xlabel(xla); ylabel(yla); % ラベルの指定
set(gca,'FontSize',fontsize);
xlbl = get(gca,'XLabel'); set(xlbl,'FontSize',fontsize);
ylbl = get(gca,'YLabel'); set(ylbl,'FontSize',fontsize);
zlbl = get(gca,'ZLabel'); set(zlbl,'FontSize',fontsize);
% x,y の数値ラベルの指定
%X = [xmin -1 0 1 xmax]; Y = [ymin -0.25 0 0.25 ymax];
%set(gca,'XTick',X); set(gca,'YTick',Y);
colormap(iro);
ccc=colorbar;
axes(ccc);
axis([xlim,zmin,zmax]);
set(ccc,'FontSize',fontsize);
%print -depsc2 mat.ps % ps file を作成