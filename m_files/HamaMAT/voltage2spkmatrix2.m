function [spkmatrix,varargout] = voltage2spkmatrix2( ...
    voltage,   ...  % time series as a vector
    threshold, ...  % threshold to define occurrence of spike
    t_ref,     ...  % voltage over threshold within refractoriness 
    varargin)       % is not counted as spike.

% Voltage2SpkMatrix2 - returns sparse vector/matrix of spikes from voltage
% traces. 
% 
% Update: 20130911.
% Now it can return the voltage data around ([-10 10] ms) the onset of spikes
% 
% [spkmatrix,SpkStat] =
% voltage2spkmatrix2(voltage,threshold,ref,nBlockSize,[fmin, fmax],sampling_rate,GoOutDir)
% 
% SpkStat(1).data:       % a matrix contains all the spike data +-10ms around the onset of spikes. 
% SpkStat(1).spikethresh % spiking threshold is the Vm when dV/dt exceeds 10STD(Vm)
% 
% SpkStat(1).halfwidth   % half width of spike measured at Vm= (spike threshold + peak of spike)/2
% SpkStat(1).AHP         % minimum Vm within 5ms after spike - baseline
% 
% SpkStat(1).burst_rate  % burst is defined as ISI < 5ms, and burst rate is the number of burst
% onsets per sec in the file.
% SpkStat(1).duration_burst % duration of the burst. End of the burst is
% defined as ISI>200ms.
% SpkStat(1).numspk_in_burst % number of spikes in one burst.
% SpkStat(1).burst_duration  % duration of burst. 

% %Usage: 
%  spkmatrix = voltage2spkmatrix2( ...
%  voltage ,    ...      % time series as a vector/matrix
%  threshold,   ...      % threshold to define occurrence of spike
%  refractoriness)       % voltage over threshold within refractoriness is 
%                        %  not counted as spike.
% %Input Arguments:
%
%  voltage          : if 1xN or Nx1 vector, returns 1xN sparse spike matrix.
%                     if NxM matrix, each row represents one successive voltage trace.
%  threshold        : a cell spikes 
%                     if voltage(k+1)-baseline>=threshold && voltage(k)-baseline<threshold 
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
% spkmatrix = voltage2spkmatrix2(voltage,threshold,refractoriness,nBlockSize)      
% 
% To save Memory, this calculates spikes from [nBlockSize(=100 by default)] 
% rows at one time. 
%
% Usage3 (20090601)
% spkmatrix = voltage2spkmatrix2(voltage,threshold,refractoriness,nBlockSize,...
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
  

%% validate inputs

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

% We remove this because it can happen that there is no spike within the data.
% if threshold < min(min(voltage)) || threshold > max(max(voltage))
%   error('voltage2spkmatrix: 2nd parameter threshold is outside range of voltage')
% end

[n_trial,vol_len]=size(voltage);

if isvector(voltage) && n_trial~=1 % If vector is a Nx1 column vector,
    n_trial = 1; 
    vol_len = length(voltage);
    voltage = voltage';
end
original_v = voltage; 
%%

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
    do_return_Stat=1;
else
    do_return_Stat=0;
end

stdmin = 20;
stdmax = 50;

if isempty(threshold) % modified from amp_detect_wc.m from WaveClust.
    noise_std_detect = 1.5*median(median(abs(voltage)));
    threshold = stdmin * noise_std_detect;        %thr for detection is based on detect settings.
%     threshold_max = stdmax * noise_std_detect;     %thrmax for artifact removal is based on sorted settings.
    fprintf('Using adaptive threshold as  %d[SD]\n',threshold);
end

fprintf('%s: threshold=%g, ref=%g, [fmin,fmax]=[%g,%g], SamplingRate=%d, GoOutDir=''%s''\n',...
    mfilename,threshold,t_ref,fmin_detect,fmax_detect,sr,GoOutDir);


%% 
switch GoOutDir 
    case 'both'
        vdiff=diff(sign(abs(voltage)-abs(threshold)),1,2);
     case 'posi'
        vdiff=diff(sign(voltage-abs(threshold)),1,2);
     case 'nega'
        vdiff=diff(sign(-voltage-abs(threshold)),1,2);
    otherwise
        error('Unknown option')
end
vdiff(:,end)=0;% Because voltage(ind,end) may have non-zero value, we set it 0.

% Obtain pre-ISI. 
% sparse matrix is fast if we put value in column wise,
estimated_NUM_spike = nnz(vdiff>0);
preISI = spalloc(vol_len,n_trial,estimated_NUM_spike);

for ii=1:n_trial
    ind=find(vdiff(ii,:)>0);
    ISI = diff(ind);
    if ~isempty(ISI)
        preISI(ind,ii)=[inf;ISI(:)];
    end
end

preISI=preISI'; % make each row as one trial.
[spk_i,spk_j]=find(preISI>t_ref); % neglect spikes that occured within refractoriness period.
spkmatrix= sparse(spk_i,spk_j,1,n_trial,vol_len,length(spk_i)) ;  % remake spike matrix

% initialize SpkStat
PreSpikeTms  = 2;
PostSpikeTms = 5;


if (do_return_Stat)
    spike_pickup_index = [ceil(-PreSpikeTms/1000*sr):ceil(PostSpikeTms/1000*sr)];
    SpkStat.data = zeros(estimated_NUM_spike,length(spike_pickup_index));
    %      SpkStat.halfwidth = spkmatrix;
    %      SpkStat.sag       = spkmatrix;
    
    % Main Loop for trial
    cnt = 0;
    for ii=1:n_trial
        
        p_spk_ind = find(spkmatrix(ii,:)); % spike timings and end of data point.
        if ~isempty(p_spk_ind)
            Pspk_cond1=(p_spk_ind + spike_pickup_index(1))>1;
            Pspk_cond2=(p_spk_ind + spike_pickup_index(end))< vol_len;
            p_spk_ind = p_spk_ind(find(Pspk_cond1 & Pspk_cond2));
             if isempty(p_spk_ind)
                continue;
             end
            index       = repmat(p_spk_ind(:),1,length(spike_pickup_index))+...
                repmat(spike_pickup_index,length(p_spk_ind),1);
%             index_that_fit_voltage = find(index(:,1)>=1 | index(:,end)<=vol_len);
%             index = index(index_that_fit_voltage,:);
            
            voltmp=original_v(ii,:);
            cnt_index = cnt+[1:length(p_spk_ind)];
%             p_spk_ind
            if cnt_index(end)> estimated_NUM_spike
                break;
            end
%             cnt_index(end)
%             index
%             size(SpkStat.data)
% voltmp(index);
            SpkStat.data(cnt_index,:)= voltmp(index);
            cnt = cnt+length(p_spk_ind);
        end
    end
    SpkStat.data=SpkStat.data(1:cnt,:);
    SpkStat.Fs     = sr;
    SpkStat.t=spike_pickup_index/SpkStat.Fs;
    
    [SpkStat.halfwidth,SpkStat.AHP,SpkStat.SpkThresh] = return_halfwidth_spike(SpkStat);
    varargout{1}=SpkStat;
end

function [halfwidth,AHP,SpkThresh]=return_halfwidth_spike(Stat)
% return half width of the spike 
% Assume that time 0 is the onset of spike.

v=Stat.data;
t=Stat.t;
Fs = Stat.Fs;

dv = diff(v,1,2);
FirstQuarterDV= dv(:,1:ceil(size(v,2)/4));
FirstQuarterVm = v(:,1:ceil(size(v,2)/4));

BaselineDVSTD = mean(std(FirstQuarterDV,0,2));
BaselineVm    = mean(FirstQuarterVm(:));

meanv = mean(v,1);
meanDV= mean(dv,1);


STDCoef = 3;
SpikeOnsetIndex=[];
SpikeOffsetIndex=[];

while isempty(SpikeOnsetIndex)|| isempty(SpikeOffsetIndex)
    % if isempty(SpikeOnsetIndex) || isempty(SpikeOffsetIndex)
    
    SpikeOnsetIndex = find(meanDV> STDCoef * BaselineDVSTD,1,'first');
    SpikeOffsetIndex = find(meanDV< -STDCoef * BaselineDVSTD,1,'last');
    %     error('Too High STD threshold');
    STDCoef = STDCoef*0.9;
    if STDCoef < 0.5
        disp('There is no spike');
        AHP=[];
        halfwidth=[];
        SpkThresh=[];
        return;
    end
end

SpikeOnsets = meanv(SpikeOnsetIndex);
SpikeMax    = max(meanv,[],2);
VolMin      = min(meanv,[],2);

HalfSpikeHeight=mean((SpikeMax+SpikeOnsets)/2);
HalfWidth_start = find(meanv>HalfSpikeHeight,1,'first')-1;
HalfWidth_index = find(meanv((1+HalfWidth_start):end)<HalfSpikeHeight,1,'first');

if isempty(HalfWidth_index) || (HalfWidth_start<1)
    halfwidth = [];
    AHP         = [];
    SpkThresh   = [];
    
    return;
end


AHP         = VolMin-BaselineVm;
SpkThresh   = meanv(SpikeOnsetIndex);

halfwidth = (1+HalfWidth_index)/Fs;


fprintf('Spike Max=%2.3fmV,SpikeOnset=%2.3fmV,Spike Half Width = %2.3f usec at V=%2.3fmV\n',...
    mean(SpikeMax),mean(SpikeOnsets),halfwidth*1.e6,HalfSpikeHeight);
fprintf('Spike threshold = %3.1fmV, AHP = %2.3fmV\n',SpkThresh,AHP);

do_report_spike_parameters = 1;

if do_report_spike_parameters
figure(12);clf;

h(1)=subplot(2,1,1);
plot(t,v,'Color',[.8 .8 .8]);hold on;
plot(t,mean(v,1),'Color',[0 0 0]);hold on;

h(2)=subplot(2,1,2);
plot(t(1:end-1),diff(v,1,2),'Color',[.7 .7 .7]);hold on;
plot(t(1:end-1),diff(meanv,1,2),'Color',[0 0 0]);hold on;
xl = xlim;
% [xl(:),xl(:)];
% BaselineDVSTD.*[1 1;-1 -1];
line([xl(:),xl(:)],STDCoef*BaselineDVSTD*[1 -1;1 -1],'Color','r','LineStyle','--');

linkaxes(h,'x');
 
% [HalfWidth_start,HalfWidth_index,HalfSpikeHeight]

h(1)=subplot(2,1,1);
plot(Stat.t([HalfWidth_start,(HalfWidth_start+HalfWidth_index)]),...
    HalfSpikeHeight*[1 1],'r','LineWidth',2);

text(Stat.t(HalfWidth_start+HalfWidth_index),HalfSpikeHeight,...
    sprintf('%3.0f \\musec',halfwidth*1.e6));

plot(Stat.t(SpikeOnsetIndex),meanv(SpikeOnsetIndex),'ro');
plot(Stat.t(SpikeOffsetIndex),meanv(SpikeOffsetIndex),'ro');


text(min(xlim),SpkThresh+10,...
    sprintf('Threshold=%3.2fmV ',SpkThresh));

line([-0.001 0.002],SpikeMax*[1 1],'Color','r','LineStyle','--');
line([0 max(xlim)],VolMin*[1 1],'Color','r','LineStyle','--');
line(xlim,SpikeOnsets*[1 1],'Color',[.5 .5 .5],'LineStyle','--');
text(max(xlim)-diff(xlim)*0.25,SpikeOnsets+0.5*AHP,...
    sprintf('AHP=%3.2f mV',AHP));

line(xlim,BaselineVm*[1 1],'Color',[.7 .7 .7]);
text(min(xlim),BaselineVm-10,sprintf('Baseline=%3.2fmV',BaselineVm));
end