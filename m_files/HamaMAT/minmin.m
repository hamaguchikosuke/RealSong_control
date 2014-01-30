function [Y,I1,I2]=minmin(x)
%     
%   MINMIN(X) returns minimum of 2D matrix X.
%  [Y,I1,I2] = MINMIN(X).
%   Y is the minimum of X, and X(I1,I2)=Y;
%
% % ex)
%  x = randn(4,5);
%  [Y,I1,I2]=minmin(x);
%   x(I1,I2)==Y % <=should be 1.
% by KH. 20080221

[Y,I1]=min(x,[],1); % Look for minimum in 1st dim.
[Y,I2]=min(Y);
I1=I1(I2);
