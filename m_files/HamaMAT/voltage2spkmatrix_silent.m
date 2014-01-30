function [spkmatrix,varargout] = voltage2spkmatrix( ...
    voltage,   ...  % time series as a vector
    threshold, ...  % threshold to define occurrence of spike
    t_ref,     ...  % voltage over threshold within refractoriness 
    varargin)       % is not counted as spike.

% Voltage2SpkMatrix - returns sparse vector/matrix of spikes from voltage
% traces. 
%
% %Usage: 
%  spkmatrix = voltage2spkmatrix( ...
%  voltage ,    ...      % time series as a vector/matrix
%  threshold,   ...      % threshold to define occurrence of spike
%  refractoriness)       % voltage over threshold within refractoriness is 
%                        %  not counted as spike.
% %Input Arguments:
%
%  voltage          : if 1xN or Nx1 vector, returns 1xN sparse spike matrix.
%                     if NxM matrix, each row represents one successive voltage trace.
%  threshold        : a cell spikes 
%                     if voltage(k+1)>=threshold && voltage(k)<threshold 
%  refractoriness   : Note! in number of index, not ms nor second.
% 
% %Output arguments:
% 
% spkmatrix         : Note that spkmatrix is sparse matrix. Non-zero values
%                     indicates the timings of the spike, values are
%                     height. So, to get spike number, you should use
%                     spk=spkmatrix~=0;
% 
% For SongPres* data, remove the first column data before use this program,
% because it contains the number of the column.
% 
% %% Usage2 (20090125)
% spkmatrix = voltage2spkmatrix(voltage,threshold,refractoriness,nBlockSize)      
% 
% To save Memory, this calculates spikes from [nBlockSize(=100 by default)] 
% rows at one time. 
%
% Usage3 (20090601)
% spkmatrix = voltage2spkmatrix(voltage,threshold,refractoriness,nBlockSize,...
%             [fmin, fmax],sampling_rate,GoOutDir);
% 
% [fmin,fmax]   : band-pass frequency
% sampling_rate : Sampling rate
% GoOutDir         : going-out direction from the threshold 
%                 'posi' to detect spike only when v is above threshold
%                 'nega' to detect spike only when v is below threshold
%                 'both' detect both. 
% 
%                 Default is 'both'.
% 
% To save Memory, this calculates spikes from [nBlockSize(=100 by default)] 
% rows at one time. 
% 
% by KH 20080529
  

% validate input

if ~( isnumeric(voltage) && length(voltage) > 1 )
  error( 'voltage2spkmatrix: 1st argument is not a numeric vector of length >= 2' )
end
% 
% if ~( isscalar(threshold) && isnumeric(threshold) )
%   error( 'voltage2spkmatrix: 2nd parameter threshold is not a numerical scalar.' )
% end

if ~( isscalar(t_ref) && isnumeric(t_ref) )
  error( 'voltage2spkmatrix: 3rd parameter threshold is not a numerical scalar.' )
end

if nargin<=3
    nBlockSize=100;
else
    nBlockSize=varargin{1};
end

% band-pass frequency
if nargin<=4
    fmin_detect=300;
    fmax_detect=3000;
else
    fminmax = varargin{2};
    fmin_detect=fminmax(1);
    fmax_detect=fminmax(2);
end

% Sampling rate
if nargin<=5
    sr = 11025;
else
    sr = varargin{3};
end

% Detection GoOutDir
if nargin<=6
    GoOutDir = 'both';
else
    GoOutDir = varargin{4};
end

% % We remove this because it can happen that there is no spike within the data.
% if threshold < min(min(voltage)) || threshold > max(max(voltage))
%   error('voltage2spkmatrix: 2nd parameter threshold is outside range of voltage')
% end

[n_trial,vol_len]=size(voltage);

if isvector(voltage) && n_trial~=1 % If vector is a Nx1 column vector,
    n_trial = 1; 
    vol_len = length(voltage);
    voltage = voltage';
end

% assume spike occurs less than 0.01 percent of the data. 
% If more than that, sparse matrix automatically increases its size,
% but may take time to do so. Make it larger would be safe.

spkmatrix = sparse([],[],[],n_trial,vol_len,ceil(n_trial*vol_len*0.0001));

% fmin_detect = 1000;              %high pass filter for detection
% fmax_detect = 3000;        
% sr          = 11025;
[b,a]=ellip(2,0.1,40,[fmin_detect fmax_detect]*2/sr);

% In case there are NaN, we remove that effect.
for ii=1:size(voltage,1)
    ind= isnan(voltage(ii,:));
    voltage(ii,ind)=nanmean(voltage(ii,:));
end


nBlockLoop= ceil(n_trial/nBlockSize);

for ii=1:nBlockLoop
    if ii==nBlockLoop
        ind=[(ii-1)*nBlockSize+1:n_trial];
    else
        ind=[1:nBlockSize]+(ii-1)*nBlockSize;
    end
voltage(ind,:) =filtfilt(b,a,voltage(ind,:)')';
% voltage(ind,:) = (voltage(ind,:)-abs(threshold));
% voltage = sign(voltage-threshold); % convert to -1,0,1 data.
end


if nargout==2
    varargout{1}=voltage;
end

stdmin = 20;
stdmax = 50;

if isempty(threshold) % modified from amp_detect_wc.m from WaveClust.
    noise_std_detect = 1.5*median(median(abs(voltage)));
    threshold = stdmin * noise_std_detect;        %thr for detection is based on detect settings.
%     threshold_max = stdmax * noise_std_detect;     %thrmax for artifact removal is based on sorted settings.
    fprintf('Using adaptive threshold as  %d[SD]\n',threshold);
end

% fprintf('%s: threshold=%g, ref=%g, [fmin,fmax]=[%g,%g], SamplingRate=%d, GoOutDir=''%s''\n',...
%     mfilename,threshold,t_ref,fmin_detect,fmax_detect,sr,GoOutDir);


% Main Loop for trial 
for ii=1:n_trial
% voltage(ind,1:end-1) = diff(sign(voltage(ind,:)),1,2);    % [-1,-1,1,1,-1 -1] -> [0,2,0,-2,0]; detect potential timing of spike.
% voltage(ind,end)=0;     % Because voltage(ind,end) may have non-zero value, we set it 0.

% vmean = mean(voltage(ii,:));

switch GoOutDir 
    case 'both'
        vtmp=diff(sign(voltage(ii,:)-abs(threshold)),1,2)-...
             diff(sign(-voltage(ii,:)-abs(threshold)),1,2);
     case 'posi'
        vtmp=diff(sign(voltage(ii,:)-abs(threshold)),1,2);
     case 'nega'
        vtmp=diff(sign(-voltage(ii,:)-abs(threshold)),1,2);
    otherwise
        error('Unknown option')
end

vtmp(end)=0;  % Because voltage(ind,end) may have non-zero value, we set it 0.

p_spk_ind = find(vtmp); % potential spike timings.
% vtmp(p_spk_ind)
        
    if length(p_spk_ind)>=1 % If there is at least one spike in this row, always count as a spike.
        if length(p_spk_ind>=2), tind=[p_spk_ind(1):p_spk_ind(2)];
        else tind=[p_spk_ind(1):vol_len];
        end
        switch GoOutDir 
                    case 'both'
                        spkmatrix(ii,p_spk_ind(1))=sign(vtmp(p_spk_ind(1)))*max(abs(voltage(ii,tind)));      % assign one spike.
                    case 'posi'
                        spkmatrix(ii,p_spk_ind(1))=max(voltage(ii,tind));      % assign one spike.
                    case 'nega'
                        spkmatrix(ii,p_spk_ind(1))=min(voltage(ii,tind));      % assign one spike.
                    otherwise
                        error('Unknown option')
        end
    end
   
    if length(p_spk_ind)>1  % and then, if there is more than one spike in this row, we need to think about refractoriness.
       last_p_spk_ind=p_spk_ind(1);
        for jj = 2:length(p_spk_ind)
            ISI = p_spk_ind(jj)-last_p_spk_ind; % update ISI.
            if ISI>t_ref  && p_spk_ind(jj)<vol_len  % If spike occurs too immediately after a spike, it may be a noise.
                if p_spk_ind(jj)==p_spk_ind(end), tind=[p_spk_ind(jj):vol_len];
                else tind=[p_spk_ind(jj):p_spk_ind(jj+1)];
                end
%                 fprintf('tind(1):tind(end)=[%d,%d]\n',tind(1),tind(end))
                switch GoOutDir 
                    case 'both'
                        spkmatrix(ii,p_spk_ind(jj))=sign(vtmp(p_spk_ind(jj)))*max(abs(voltage(ii,tind)));      % assign one spike.
                    case 'posi'
                        spkmatrix(ii,p_spk_ind(jj))=max(voltage(ii,tind));      % assign one spike.
                    case 'nega'
                        spkmatrix(ii,p_spk_ind(jj))=min(voltage(ii,tind));      % assign one spike.
                    otherwise
                        error('Unknown option')
                end

                last_p_spk_ind=p_spk_ind(jj);
            end
        end
    end
end
