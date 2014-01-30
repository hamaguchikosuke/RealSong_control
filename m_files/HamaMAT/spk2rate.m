function out = spk2rate(T,spkhist,varargin)
% This function calculate the firing rate within a given bin size. 
% 
% Usage: spk2rate(T,SpkHist)
% T:        1xN time vector,
% SpkHist:  MxN sparse matrix.
% 

ave_bin = 101;
if issparse(spkhist)
  bin_half = floor(ave_bin/2);
  [n,spk_len] = size(spkhist);
  
  spk_tmp = [spalloc(n,bin_half+1,0),spkhist,spalloc(n,bin_half,0)];
  prob = zeros(size(spkhist));
  for i = 1:size(spkhist,2)
    prob(:,i) = sum(spk_tmp(:,i:i+ave_bin),2)/ave_bin;
  end  

else
  prob = conv(ones(1,ave_bin)/ave_bin,spkhist);
  prob = prob(floor(ave_bin/2)+1:end-floor(ave_bin/2));
end

time_ave = (T(ave_bin)-T(1))/1000; % (ms) -> (sec)
rate = prob/time_ave*ave_bin;

out = rate;