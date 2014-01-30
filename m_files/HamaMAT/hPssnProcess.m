function out =  hPssnProcess(rate, time)
% 
% This is a poisson process simulater, with refractory period ds.
% this generates a [(time,:) ;  (height,:)] vector. 
% Usage: hPssnProcess(firing rate, time duration in second) 
% Dec.14.2001 by K. Hamaguchi
% 
  global ds; % the spike duration time, very small time.  

%clf;
ISI = 0;
ds = 0.005;
Jump = 1;
v = 0;
now = 0;

%main loop
% one trial loop
% every trial's data is stored in ISI

while ISI(:,end) < time
  % Using Inverse function of exponential distribution. 
  spk_t = - log(1-rand(1))/rate; 
  now = ISI(:,end)+spk_t+ds;
  
  % If trial time is exceeded
  if now > time
    break;
  else % generated spk_t more than ds time separation.
    ISI = [ISI, now];
    v = [v, v(:,end)+Jump];
  end
end

% plot and show Firing rate.
ISI = ISI([2:end]); % NofEl. is N-1

No_spikes =  length(ISI);
Firing_Rate = No_spikes/ time;
%make the stem of sequence.
ISI =  reshape( [ISI; ISI+ds], 1, 2*No_spikes); %NofEl. is 2N-2
v = reshape( repmat(v,2,1), 1,2*length(v));   % NofEL. is 2N
v = v(1:end-1);                                      % NofEl. is 2N-1
% check the last ISI

if ISI(end) >= time % if the voltage increase time exceed the time duration
   vlast = interp1([0,ISI],v,time); % cal. the last v: 
   ISI= ISI(1:end-1);                  % remove the incorrect last v: No. of element is 2N-3
   v = [v(1:end-1), vlast];           % NofEl. is 2N-1
else
   v = [v, v(end)];                      % NofEl. 2N
end

ISI = [0, ISI, time];
%ISI = [0, ISI(1:end-1)];

out = [ISI; v]

%plot(ISI,v);

% end of pssn1.m

% making 4 points which designate the 4 angle of spike shapes.

