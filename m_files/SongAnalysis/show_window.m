function show_window(range,gph)
% subroutine to draw rectangular region in the panel given by a graphics handle (gph).
% ex) show_window(range,gca);
% KH 20080606

global ss;

ymax = max(ylim);
ymin = min(ylim);

set(gcf,'CurrentAxes',gph);
area([range,range(end:-1:1)],[ymax ymax ymin ymin],'Color',rand(1,3));
