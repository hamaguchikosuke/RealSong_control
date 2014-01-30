function [a, b, c] = IntegF2(t,v,opt,Inp)
% this is a test function to test runge-kutta method.
% Usage:
%  rungekutta2(initial-value);
% by K.H. 18.Dec.2001.

global Vre Vth L It

if isempty(opt)% no option: return x dots.
  
  if size(Inp,1) == 2
    It = interp1(Inp(1,:), Inp(2,:), t);
  else 
    It = Inp(1);
  end
  
  % x dots
  a = -L*(v-Vre)+It;
  return;
  
end


switch(opt)
 case 'init'
  disp('cheking initial condition..')

 Vre = 0;  % Resting Potential
 Vth = 20; % Threshold Potential
 L = 0.1;  % decay rate
 v0 = Vre;  % Initial state of v.

  a = v0;
  
  
 case 'threshould'
  Vre = 0;  % Resting Potential
 Vth = 20; % Threshold Potential
  a = Vth;
  b = Vre;

 otherwise
error(['invalid option:', opt]);

end

%end of IntegF2.m
