function yi = myinterp1q2(x,y,xi,varargin)
%
% Very quick 1-D linear interpolation.
% Only applicable when the components of x has even interval.
% USAGE: myinterp1q2(x,y,xi);
% x and y must be monotonic vector. xi does not have to be 
% monotonic. x, y, and xi can be either 1xN or Nx1 vector.
% If xi is outside of x region, yi = Y(end) if xi>x(end), 
% else yi = y(1) ifxi < x(1).
% by K.H. 2003.Dec.07
dx = x(2)-x(1);
if any(diff(x)/dx ~=1), error(['input x must be even interval for this code!']); end;
yi = repmat(0,size(xi));

dx = x(2)-x(1);
xx = x-x(1);
xi = xi-x(1);
r = floor(xi/dx)+1;
%r(xi==xx(end))=length(xx)-1;
uind = find(r>=length(xx));
lind = find(r<=0);
ind=find((r>0) & (r<length(xx)));
rind = r(ind); 
u = (xi(ind)-xx(rind))./(xx(rind+1)-xx(rind));
yi(ind)=y(rind)+(y(rind+1)-y(rind)).*u;
yi(uind) = y(end);
yi(lind) = y(1);
% end of file.