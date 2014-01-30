function [tn, yn, spk_time] = rungekuttaIF2(model,ts,X,Inp)
% This is a Ode solver by Runge-Kutta method, which was described in 
% the 'introduction to theoretical neurobiology. p54'
% use this with IntegF2.m
% USAGE: It cannot be used 
%  rungekuttaIF2('IntegF2', timespan, initial-val, Input-current.)
% it accepts column vector and returns column vector.
% 
% by Kosuke Hamaguchi. 19.Mar.2002  

inline(model);


t0= ts(1);
t_end = ts(2);
y0 = X;   % set the initial value
time_duration = t_end - t0; % length of time(msec)
dt = 0.01; % delta t(msec)



% decide step length 

steplength = floor(time_duration/dt)

[Vth Vre] = feval(model,[], [], 'threshould');
 
tn = ones(1,steplength+1); 
yn = ones(1,steplength+1);
spk_time = ones(1,steplength+1);

tn(1) = t0;
yn(1) = y0;
spk_time(1) = 0;

for i = 1:steplength
  
  %sprintf('now step %d', i)
  
  Kn1 = feval(model,tn(i),      yn(:,i),[], Inp);
  Kn2 = feval(model,tn(i)+dt/2, yn(:,i)+dt*Kn1/2,[],Inp);
  Kn3 = feval(model,tn(i)+dt/2, yn(:,i)+dt*Kn2/2,[],Inp);
  Kn4 = feval(model,tn(i)+dt,   yn(:,i)+dt*Kn3,[],Inp);
  tn(i+1) = tn(i) + dt;
  
  
  % IF v intersect the threshold, it comes back to Vre. with no refractory period
  ynn = ( yn(:,i)+dt.*(Kn1+2*Kn2+2*Kn3+Kn4)/6 ); %  ynn: next value of yn
  if ynn > Vth
    ynn = Vre;
    spk_time(i+1) = 1;
  
  else
    spk_time(i+1) = 0;
    
  end;
  yn(i+1) = ynn;
  
  i = i+1; % incriment step
end


     out = [tn; yn; spk_time];
