function out = setLineColor(M)
child = get(gca,'Children');
for i = 1:length(child)
  set(child(i),'Color',M);
end

