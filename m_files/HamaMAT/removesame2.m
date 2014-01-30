function out = removesame2(Z)
% Based on ...
%   this is a m-file to add two plot.
%   Usage:addseq(X, Y) 
%   Dec.18.2001 by K. Hamaguchi
% remove same point on the 1st row

t = Z(1,:); x=Z(2,:);
num = size(Z,2);
Z_t(1) = t(1);
Z_x(1) = x(1);
pos = 1;

for i = 1:num-1
  if t(i) == t(i+1)
    Z_x(pos) = Z_x(pos) + x(i+1);
  else 
    pos = pos +1;
    Z_t(pos) = t(i+1);
    Z_x(pos) = x(i+1);
  end
end

out = [Z_t;Z_x]


% end of removeseq2.m
