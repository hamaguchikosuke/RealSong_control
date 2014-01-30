function out = rungekuttaIF(y0)
% This is a Ode solver by Runge-Kutta method, which was described in 
% the 'introduction to theoretical neurobiology. p54'
% use this with IntegF.m
% USAGE: 
%  rungekuttaIF('IntegF', initial stat of v)
% it accepts column vector and returns column vector.
%
% I omitted the tn(,:end) in the Kn*, I am not sure how to use the value.
% this is bad /> bacause some model have contain t positively.
% by Kosuke Hamaguchi. 17.Dec.2001  

tn = 0;    % set the initial time
yn = y0;   % set the initial value
time = 10; % length of time
dt = 0.1; % delta t
 


% decide step length 
steplength = floor(time/dt);

[Vth Vre] = feval('IntegF',[], 'init');


for i = 1:steplength
%sprintf('now step %d', i)

  Kn1 = feval('IntegF',yn(:,end),[]);
  Kn2 = feval('IntegF',yn(:,end)+dt*Kn1/2,[]);
  Kn3 = feval('IntegF',yn(:,end)+dt*Kn2/2,[]);
  Kn4 = feval('IntegF',yn(:,end)+dt*Kn3,[]);

  tn = [tn (tn(:,end)+dt)];
  ynn = (yn(:,end) + dt.*(Kn1+2*Kn2+2*Kn3+Kn4)/6); %  ynn: next value of yn

  if ynn > Vth, ynn = Vre; end;
  yn = [yn ynn];
  
  i = i+1; % incriment step
 
end

  out = [tn; yn];

clf;

plot(tn,yn(1,:));

