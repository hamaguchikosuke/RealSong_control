function out =  pssn(rate, time)

% MODIFIEF VERSION of MATH/InfoTheroy/pssn.m
% This is a poisson spike generator, with no refractory period.
% this generates a [spike time] row vector. 
% Usage: pssn(firing rate, time duration in second) 
% Feb.1.2002 by K. Hamaguchi
% 
 
ISI = 0;
now = 0;

%main loop
while now < time
  spk_t = - log(1-rand(1))/rate; % Using Inverse function of 
				 %exponential distribution. 
  if now +spk_t > time
    break;
  end
  now = now + spk_t;
  
  ISI = [ISI, now];
  
end

out = ISI(2:end);
