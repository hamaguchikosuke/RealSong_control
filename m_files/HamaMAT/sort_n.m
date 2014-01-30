function [Y,I1,I2,varargout]=sort_n(X)
% SORT_N(X) returns the sorted vector Y.
% X can be a vector and matrix. 
% [Y,I1,I2,...,In]=sort_n(x)
% In is the index of n-dimension of x.
% 
% Y is the sorted vector in ascending order,
% I1, I2, ... are index in the dimension of X.
% Y(i) = X(I1(i),I2(i));
% 
% 
%
%% ex) 
% X = [1:16]; X = reshape(X,8,2);
% X = randn(4,5,3)
% [Y,I1,I2,I3]=sort_n(X);
%% by KH 20080221.

Xdim = size(X);
[Y,I]=sort(reshape(X,1,prod(Xdim)));

switch length(Xdim)
    case 2
        [I1,I2] = ind2sub(Xdim,I) ;
    case 3 
        [I1,I2,I3] = ind2sub(Xdim,I) ;
        varargout{1}=I3;
    case 4
        [I1,I2,I3,I4] = ind2sub(Xdim,I) ;
         varargout{1}=I3;
         varargout{2}=I4;
    otherwise
        error(['please write the code more than dim>=',num2str(length(Xdim))])
end

% ii=7; X(I1(ii),I2(ii),I3(ii))
% ii=11; X(I1(ii),I2(ii))