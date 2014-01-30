function out= MyFontDefaultset(fontsize)
%
% change the fontsize of current gca.
%
%
%
%


xlbl = get(gca,'XLabel'); set(xlbl,'FontSize',fontsize);
ylbl = get(gca,'YLabel'); set(ylbl,'FontSize',fontsize);
zlbl = get(gca,'ZLabel'); set(zlbl,'FontSize',fontsize);