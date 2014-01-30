function [a, b, c] = IntegF(v,opt)
% this is a test function to test runge-kutta method.
% Usage:
%  rungekutta2('IntegF',initial-value);
% by K.H. 7.Dec.2001.

global Vrest Vth L It

if isempty(opt)% no option: return x dots.

% x dots
a = -L*(v -Vrest)+It;

return;
end


switch(opt)
case 'init'
disp('cheking initial condition..')
% Input I
It = 150;
% Resting Potential
Vrest = -60;
% Threshold Potential
Vth = 0;
% decay rate
L = 2;

a = Vth;
b = Vrest;

otherwise
error(['invalid option:', opt]);

end

%end of IntegF.m
