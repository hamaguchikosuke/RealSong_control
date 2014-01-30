function [sta,lags2] = spksta(spk,signal,lags);
% spike triggered average of signal by spike timings. 
% usage: sta = spksta(spk,signal,lags);
% usage: [sta,time] = spksta(spk,signal,lags);
% ====Inputs======
% spk    is NxT martix, in each row contains one trial of experiments.
% signal is NxT matrix, in each row contains the stimulus in that
% experiment.
% lag    is a scalar, which designates how much lag we computes.
% ===Outputs======
% sta is the 1x(2*lag+1) vector, which is the spike triggered average. 
% time is a vector [-lags:lags], NOT the real time.
%% ex) 
%     t      = linspace(0,4*pi,101); 
%     signal = sin(t)/2+1/2; signal=repmat(signal,10,1);
%     spk    = sparse(rand(10,101)<signal);
%     lags = 20;
%     [sta,lags]   = spksta(spk,signal,lags); plot(lags,sta);

[ma,mb] = size(spk);
[na,nb] = size(signal);

if (ma~=na) || (mb~=nb)
    fprintf('size(spk)=[%d %d], size(signal)=[%d,%d]\n',ma,mb,na,nb);
    error('spk and signal should be the same size matrix.')
end

% if (2*lags+1) > mb
% 
% end

lags2 = [-lags:lags];
stalen = 2*lags+1;

sta = zeros(1,stalen);
percent_done= 0; percent_done_before = 0;
%%
fprintf('STA Calculation: 0%%-')
% for ii=lags2
%    
%     percent_done = (ii+lags)/(2*lags+1);
%     if percent_done > percent_done_before+ 0.01
%        percent_done_before = percent_done;
%        fprintf('%d\%.',percent_done);
%     end
%     
%     if sign(ii)<0 % signal before spike
%        n = nnz(spk(:,1+abs(ii):end));
%        statmp = sum(sum(spk(:,1+abs(ii):end).*signal(:,1:end-abs(ii))))/n;
%     else          % signal after spike
%        n = nnz(spk(:,1:end-abs(ii)));
%        statmp = sum(sum(spk(:,1:end-abs(ii)).*signal(:,1+abs(ii):end)))/n;
%     end
%     sta(lags+ii+1) = statmp;
% end

mean_signal = mean(mean(signal));
  
for ii=1:size(spk,1) % loop for different trials.
      
    % To see how much percentage is done, 
    % because sometimes STA can be slow.
    percent_done = ii/ma;
    if percent_done > percent_done_before+ 0.1
        percent_done_before = percent_done;
        fprintf('%2.3g%%-',percent_done*100);
    end
    
    ind = find(spk(ii,:));
      if ~isempty(ind)
        for jj = 1:length(ind)
            
            % Setup index to add spike triggerd signal into STA vector.
            if (ind(jj)-lags)<=0 % signal(ind(jj)-lags<=0) does not exist.
                outN = abs(ind(jj)-lags);        % length of signal to be neglected.
                sigind = [1:stalen-outN];        % signal that goes to STA.
                staind = [outN+1:stalen];        % STA index to be merged.
            elseif (ind(jj)+lags)>=mb % signal(ind(jj)+lags>=mb) does not exist.
                outN = abs(ind(jj)+lags-mb);   
                sigind = [ind(jj)-lags:mb];      
                staind = [1:stalen-outN];
            else
                sigind = [ind(jj)-lags:ind(jj)+lags];
                staind = [1:stalen];
            end
            [staindlen]=length(staind); [sigindlen]=length(sigind);
            if (staindlen~=sigindlen)
                fprintf(' Error at ind(jj)=%d, stalen = %d, siglen= %d \n',ind(jj),staindlen,sigindlen);
            end
            sta(staind) = sta(staind)+(signal(ii,sigind)-mean_signal);    
        end
    end
end

%%
sta = sta/nnz(spk)+mean_signal; % divided by the number of spike trigger events.
fprintf('Done.\n');


