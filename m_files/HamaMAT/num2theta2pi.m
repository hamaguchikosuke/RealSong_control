function out = num2theta2pi(i,N)
%
% Usage: num2theta(i,N) 
% it returns the theta at position i.
%i         1             N/2              N
%          |______________|_______________|
%\theta   -pi             0              pi
%
%by K.H. 04.Mar.2003
out = ((i-1)/N-1/2)*2*pi;

