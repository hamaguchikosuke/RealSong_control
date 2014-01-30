function [cv2mat,cv2cpm,state] = rem_first_last_cv2(count_threshold,filtbin,cv2cpm,varargin)
% ----- filter the first and last cv2 value, in the high-rate region.
% usage: [cv2mat,cv2cpm,state]= rem_first_last_cv2(count_threshold,filtbin,cv2cpm)
% usage: [cv2mat,cv2cpm,state]= rem_first_last_cv2(count_threshold,filtbin,cv2cpm,cv2mat)
% input argv; cv2cpm and cv2mat are trial_num X time_bin sparse matrix.
% cv2cpm can be just a spike matrix.
% output argv; 
% cv2mat contains cv2 values after removing first and the last cv2 value in
% the high-firing rate region. Rate is calculated by filtbin-size box-car
% filter, and high-rate is the region where it contains more than
% count_threshold spikes.
% 
%% ex) 
% count_threshold = 30;
% filtbin = 100;
% cv2cpm=sparse(rand(50,1001)<0.01);
% [cv2mat,cv2cpm,state]= rem_first_last_cv2(count_threshold,filtbin,cv2cpm);
% n_argin = 2;
%% by kh 20071229

n_argin = nargin; % uncomment 
[nTrials,nbins] = size(cv2cpm);

do_check_plot = 0;

if n_argin==4
    cv2mat = varargin{1};
elseif n_argin>=4
    error([mfilename, ': rem_first_last_cv2(cv2cpm,cv2mat);'])
else
    cv2mat = spk2cv2(cv2cpm);
end

countcv2 = conv2(full(sum(cv2cpm,1)),ones(1,filtbin),'same');
cv2_t = conv2(full(sum(cv2mat,1)),ones(1,filtbin),'same')./countcv2;
rindex=countcv2>count_threshold;

exitindex=[find(diff(rindex)~=0)];
state  = rindex(exitindex+1);
state0 = (countcv2(1)>count_threshold);
state = [state0, state];
startindex = [1,exitindex-1];
exitindex = [exitindex,nbins];

remove_index = zeros(2,nTrials);
remove_cv2cpm= spalloc(nTrials,nbins,nTrials*6); 
remove_cv2mat= spalloc(nTrials,nbins,nTrials*6);


%----- remove the first and the last cv2 value.
for jj=1:length(state)
    if (state(jj))
        for kk=1:nTrials
            ind=find(cv2cpm(kk,startindex(jj):exitindex(jj)));
            if ~isempty(ind)
            remove_index1 =startindex(jj)-1+ind(1);
            remove_index2 =startindex(jj)-1+ind(end);
            remove_cv2cpm(kk,[remove_index1,remove_index2])=cv2cpm(kk,[remove_index1,remove_index2]); 
            remove_cv2mat(kk,[remove_index1,remove_index2])=cv2mat(kk,[remove_index1,remove_index2]);
            end
        end
    else
        remove_cv2cpm(:,startindex(jj):exitindex(jj))=cv2cpm(:,startindex(jj):exitindex(jj));
        remove_cv2mat(:,startindex(jj):exitindex(jj))=cv2mat(:,startindex(jj):exitindex(jj));
%             cv2cpm(:,startindex(jj):exitindex(jj))=0; 
%             cv2mat(:,startindex(jj):exitindex(jj))=0; 
    end
%        set(1,'CurrentAxes',ax1);
%        [tr,tc]=find(remove_cv2cpm);
%        plot(tc*dt,tr,'go','MarkerSize',4);
end

if (do_check_plot)
    clf;subplot(2,1,1);
    plot(countcv2);
    subplot(2,1,2);
    [tr,tc]=find(cv2cpm);
    plot(tc,tr,'k.','MarkerSize',1);hold on;
    [tr,tc]=find(remove_cv2cpm);
    plot(tc,tr,'ro','MarkerSize',3);hold on;
end

cv2cpm= cv2cpm-remove_cv2cpm;
cv2mat= cv2mat-remove_cv2mat;

if (do_check_plot)
[tr,tc]=find(cv2cpm);
plot(tc,tr,'go','MarkerSize',3);
end
