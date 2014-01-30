function out = sort_on1strow(X1)
%
%
%
%
%


X1_t = X1(1,:);
X1_x = X1(2,:);

[X1_t, I] = sort(X1_t);
X1_x = X1_x(I);

out = [X1_t;X1_x];
