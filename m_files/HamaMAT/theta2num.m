function out = theta2num(theta,N,L)
%
% Usage: num2theta(theta,N,L) 
% it returns the index within [1,N] which represents 
% the position theta.
% We assume the region is [-L/2, L/2).
%          1     _?      N/2            N  N+1
%          |______________|______________|_|
%\theta   -L/2  theta     0                L/2
%
% please do not use outside of [-L/2, L/2] range.
%by K.H. 25.Apr.2004
if any(abs(theta)> L/2),  error(['please do not use outside of [-L/2, L/2] range.']);end

t = linspace(-L/2,L/2,N+1);
out = interp1(t,[1:N+1],theta,'nearest');
I = find(out==N+1);
if any(I)
    out(I)=1;
end

%% Old version.
% out = round((theta+L/2)./L*(N-1))+1;