function out = rungekutta(model,y0)
% This is a Ode solver by Runge-Kutta method, which was described in 
% the 'introduction to theoretical neurobiology. p54'
% USAGE: rungekutta('the name of equation', initial state vector)
% it accepts column vector and returns column vector.
% by Kosuke Hamaguchi. 7.Dec.2001  

tn = 0;    % set the initial time
yn = y0;   % set the initial value
time = 10; % length of time
dt = 0.1; % delta t



% decide step length 
steplength = floor(time/dt);

for i = 1:steplength

  Kn1 = feval(model,tn(end),yn(:,end));
  Kn2 = feval(model,tn(end)+dt/2,yn(:,end)+dt*Kn1/2);
  Kn3 = feval(model,tn(end)+dt/2,yn(:,end)+dt*Kn2/2);
  Kn4 = feval(model,tn(end)+dt,yn(:,end)+dt*Kn3);
  
  tn = [tn (tn+dt)];
  ynn = (yn + dt.*(Kn1+2*Kn2+2*Kn3+Kn4)/6); %  ynn: next value of yn
  yn = [yn ynn];
  
  i = i+1; % incriment step
 
end

  out = [tn; yn];
