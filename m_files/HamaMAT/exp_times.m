function out = exp_times(mu,span_max)
% returns exponentially distributed time series.
% USAGE: exp_times(mu,span_max)
% by K.H. 24.Oct.2002


time = cumsum(floor(exprnd(mu,1,100).*10)/10);
while time(end)<span_max
  time_tmp = cumsum(floor(exprnd(mu,1,100).*10)/10);
  time = [time,time(end)+time_tmp];
end

I = find(time>0 & time<span_max);
out = [0,time(I)];
