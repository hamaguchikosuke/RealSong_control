function out = num2thetaL(i,N,varargin)
% Usage: theta = num2thetaL(i,N);
% Usage: theta = num2thetaL(i,N,L);
%
% it returns theta within [-L/2,L/2] which is represented  
% by index num. Default L is pi.
% We assume the region is [-L/2, L/2).
%          1     num     N/2            N  N+1
%          |______________|______________|_|
%\theta   -L/2    ?       0                L/2
%by K.H. 04.Mar.2003

if nargin>=3
    L = varargin{1};
else
    L = 2*pi;
end

out = ((i-1)/N-1/2)*L;
