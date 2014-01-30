function out = sqnorm(x,n)
% sqnorm(X,2) = (X(:,1).^2 + X(:,2).^2 + X(:,3).^2 + ...)^{1/2};
% sqnorm(X,1) = (X(1,:).^2 + X(2,:).^2 + X(3,:).^2 + ...)^{1/2};
%


if n == 2
    out = zeros(size(x(:,1)));
    for i=1:size(x,2),    out= out +x(:,i).^2;    end;
    out= sqrt(out);
elseif n == 1    
    out = zeros(size(x(1,:)));
    for i=1:size(x,1),    out= out +x(i,:).^2;   end;
    out= sqrt(out);
else
 error(['unknown option']);
end