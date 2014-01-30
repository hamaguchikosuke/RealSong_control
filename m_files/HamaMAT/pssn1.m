function spk =  pssn1(rate, time)
% 
% This is a poisson spike generator, with no refractory period.
% this generates a [(time,:) ;  (height,:)] vector. 
% Usage: pssn(firing rate, time duration in second) 
% Nov.1.2001 by K. Hamaguchi
% 
  global ds; % the spike duration time, very small time.  

clf;
ISI = 0;
now = 0;
ds = 0.05;

%main loop
% one trial loop
% every trial's data is stored in ISI

while now < time
spk_t = - log(1-rand(1))/rate; % Using Inverse function of exponential distribution. 
% if generated spk_t is more than ds and does not exceed time,

 if now +spk_t +ds +0.001 > time
 break;
 end;

now = now + spk_t +ds+0.001;

ISI = [ISI, now];

end


% plot and show Firing rate.
ISI = ISI([2:end]); % To remove the first spike at time 0.

No_spikes =  length(ISI);
Firing_Rate = No_spikes/ time;

% making 4 points which designate the 4 angle of spike shapes.
ISI = [ISI', ones(No_spikes,1)];
K = [1 1 1 1; 0, 0.001, ds, ds+0.001];
ISI = reshape((ISI*K)',1, 4*No_spikes);
spk= [ISI; repmat([0 1 1 0], 1,No_spikes)];
end_t = max(time, spk(1,end));

spk = [[0;0], spk,[end_t;0] ]; % adding first and last time border.

plot(spk(1,:), spk(2,:));


% end of pssn1.m
