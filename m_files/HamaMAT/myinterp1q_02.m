function yi = myinterp1q_02(x,y,xi,varargin)
%
% Very quick 1-D linear interpolation.
% Only applicable when the components of x is
% monotonic increasing with even intervals.
% USAGE: myinterp1q(x,y,xi);
% x and y must be monotonic vector. xi does not have to be 
% monotonic. x, y, and xi can be either 1xN or Nx1 vector.
% by K.H. 2003.Dec.07

% updated 2012.Nov.03
% 
% 
yi = repmat(NaN,size(xi));

dx = x(2)-x(1); % grid size
xx = x-x(1);    % align x to be all positive.
xi = xi-x(1);   

if any(xx)<0 || dx<0
    error('input x must be monotonic increasing');
elseif any(diff(x)~=dx)
    error('input x must be even spacing');
end

r = floor(xi/dx)+1; 
r(xi==xx(end))=length(xx)-1;

ind=find((r>0) & (r<length(xx)));
rind = r(ind); 

u = (xi(ind)-xx(rind))/dx;
yi(ind)=y(rind)+(y(rind+1)-y(rind)).*u;

% end of file.