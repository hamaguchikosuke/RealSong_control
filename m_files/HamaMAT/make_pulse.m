function [pulse,varargout]=make_pulse(delay,duration,w,pT,amp,Fs)
% make a train of TTL pulses
% pulse=make_pulse(delay,duration,width,pulse_interval,amp,Fs)
% 
% delay     =0;      % delay to trigger pulse  [ms]
% duration  =10;     % total duration of pulse train [ms]
% width     = .5;    % single pulse width      [ms]
% pulse_interval = 3;% Inter-pulse interval   
% amp       = 5      % pulse amplitude
% Fs        =44100;  % sampling frequency      [Hz]
% 
% pulse_interval can be a vector to design arbitrary pulses,
% and the last pulse has no pulse_interval.
% Therefore, if pulse_interval is 2x1 vector, it generates 3 pulses at
% maximum. The maximum duration of the pulse train is always 'duration'.
% pulse_interval parameter assigned over the 'duration' will be negcted.
% 
% If there is only one pulse interval,
% it means all the pulse_interval is the same.
% ex) pulse_interval=3, is equal to [3,3,3,...]
% 
% 
%                              duration
%        <----------------------------------------------->
%|       pulse_interval(1), pulse_interval(2),..        |
%        <----------------><------------->               
%|                                                      |
%        width
%|       <--->                                          |
%         ___               ___            ___       ___  <--amp
%|_______|   |_____________|   |__________|   |____ |  
%|<----->|                                                      
%   delay
% 
%% by KH 20100223



if numel(pT)==1
    is_regular_train=1; % all the pulse-intervals are the same. 
    Npulse=ceil(duration/pT);
    pT=repmat(pT,Npulse,1);
elseif isvector(pT)
    is_regular_train=0; %all the pulse-intervals are the same.
    Npulse=numel(pT)+1;
    totalpT=sum(pT);
else
    error('pulse interval must be a scalar or a vector');
end


if  any(w>pT)
    error('single pulse width must be shorter than pulse interval!');
elseif any(pT>duration)
    error('pulse interval must be shorter than the total duration!');
end

Fs=Fs/1000; % To make [ms].


delay_ind   =floor(Fs*delay);
pT_ind      =floor(Fs*pT);
len         =floor(Fs*duration)+delay_ind;

pulse_width_index=[1:floor(Fs*w)];

if isempty(pulse_width_index) || isempty(len) || isempty(delay_ind) || isempty(pT_ind)
    error('One of the parameter is too small for this sampling rate!'); 
end
    
pulse=zeros(len,1);
pos=delay_ind;
for ii=1:Npulse
    high_ind=pos+pulse_width_index;
    if high_ind(end)>len
        high_ind=[high_ind(1):len];
    end
    pulse(high_ind)=amp;
    if (ii~=Npulse), pos=pos+pT_ind(ii); end
    if pos>len, break; end
end

t=linspace(0,duration,len+1); t=t(1:end-1);
varargout{1}= t;


