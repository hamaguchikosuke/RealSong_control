function [mtcoh_mat,fo,to,stat,varargout]=mtcoherency_02(x,y,D,nFFT,Fs,WinLength,nOverlap,NW,Detrend,nTapers)
% [coh,fo,to] = mtcoherency_03(X,Y,D,nFFT,Fs,WinLength,nOverlap,NW,Detrend,nTapers)
% [coh,fo,to,stat,Cxy,Axx,Ayy] = ...
%         mtcoherency_03(X,Y,D,nFFT,Fs,WinLength,nOverlap,NW,Detrend,nTapers)
% [coh,fo,to,stat,Cxy,Axx,Ayy,shiftCxy] = ...
%         mtcoherency_03(X,Y,D,nFFT,Fs,WinLength,nOverlap,NW,Detrend,nTapers)
% 
% INPUTS:
% X,Y       = Tx1 real valued vector, or TxM matrix
%             (M=number of trials, T=length of the trial (number of bins)).
% D         = length of the delay (in bin size).
% nFFT      = number of points of FFT to calculate (default 1024)
% Fs        = sampling frequency (default 2)
% WinLength = length of moving window (default is nFFT)
% nOverlap  = overlap between successive windows (default is WinLength/2)
% NW        = time bandwidth parameter (e.g. 3, 7/2, 4), default 3
% nTapers   = number of data tapers kept, default 2*NW -1
% 
% It returns the multitaper coherency function of signals X and Y,
% and their shift-predictors.
% 
% OUTPUTS:
% coh is 2*D+1 x nFFTChunks x nTrials matrix, 
% where i-th column is the multitaper coherency of X(:,i) and Y(:,i) 
% converted back in time domain.
% 
% fo is the fft frequency.
% to is the start time point of the moving window. 
% 
% stat.varX     = variance of [X,Y] within the moving window, nFFTChunks x nChannels x nTrials matrix 
% stat.meanX    = mean of [X,Y] within the moving window, nFFTChunks x nChannels x nTrials matrix
% 
% Cxy is the mutltaper cross-covariance of x and y.
% Axx is the multitaper auto-covariance of x, 
% Ayy is the multitaper auto-covariance of y,
% shiftcoh is the shifted predictor of multitaper cross-coherency of x and y.


% Kosuke Hamaguchi modified mtcsg in KenToolbox stolen from
% http://qneuro.rutgers.edu/Software.html
% included as my_mtcsg.




%% %  % ex1) 
% % 
% Fs= 1000; 
% D = ceil(0.5*Fs);
% nFFT=2*Fs;
% WinLength=2*Fs;
% nOverlap=ceil(WinLength/2);
% NW=4;
% Detrend='';
% nTapers=5;
% 
%  omega = 2*pi; M = 20;
%  t = linspace(0,5,5*Fs+1);
%  noise_c = randn(M,length(t));
%  c        = 0.5; Delay = 50; D = 200;
%  
%  noise_x = c*noise_c + (1-c)*randn(M,length(t));
%  noise_c = conv2([randn(M,Delay),noise_c(:,1:end-Delay)],ones(1,10)/10,'same');
% % noise_c=[randn(M,Delay),-noise_c(:,1:end-Delay)];
%  noise_y = c*noise_c + (1-c)*randn(M,length(t));
% x = cos(omega*t)+cos(3*omega*t);
% x = repmat(x,M,1)+noise_x;
% y = cos(2*omega*t)+cos(3.1*omega*t);
% y = repmat(y,M,1)+noise_y;
% % coh = mtcoherency_03(x',y',D,nFFT,Fs,WinLength,nOverlap,NW,Detrend,nTapers);


%% % ex2) 
% % 
% Fs= 11025; 
% D = ceil(0.5*Fs);
% nFFT=4*Fs;
% WinLength=2*Fs;
% nOverlap=0;ceil(WinLength);
% NW=4;
% Detrend='';
% nTapers=5;
% 
% load C:\home\LabVIEW\data\20000513_or251m\rm139_BOS_HVC.mat
% load C:\home\LabVIEW\data\20080811_pur733m\kh018_SL_HVC_X.mat
% x=voltage(:,2:end);
% x = voltage2spkmatrix(x,-40,5);
% fprintf('Median Filtering on neuron 1 data...\n')
% x=medfilt1(x,ceil(0.005*Fs),size(x,2),2);
% load C:\home\LabVIEW\data\20000513_or251m\rm139_BOS_LMAN.mat
% load C:\home\LabVIEW\data\20080811_pur733m\kh018_SL_LMAN.mat
% y=voltage(:,2:end);
% y = voltage2spkmatrix(y,-40,5);
% 
% fprintf('Median Filtering on neuron 2 data...\n')
% y=medfilt1(y,ceil(0.005*Fs),size(y,2),2);
% clear voltage;
% 
% fprintf('done\n')
% 
% D = ceil(0.5*Fs);
% % coh = mtcoherency_03(x,y,200);

%% % ex3) 
% % 
% Fs= 11025; 
% D = ceil(0.5*Fs);
% nFFT=2*Fs;
% WinLength=2*Fs;
% nOverlap=ceil(WinLength/2);
% NW=4;
% Detrend='';
% nTapers=5
% % cd C:\home\LabVIEW\data\20080818_or734m
% 
% % load C:\home\LabVIEW\data\20080818_or734m\kh008_SL_HVC_RA.mat
% % load C:\home\LabVIEW\data\20000530_or230m\rm183_BOS_HVC_RA.mat
% load C:\home\LabVIEW\data\20080920_gr729m\kh004_BOS_HVC_X.mat
% xo=voltage(1:end,2:end);
% fprintf('Median Filtering on neuron 1 data...\n')
% x=medfilt1(xo,ceil(0.003*Fs),size(xo,2),2);
% % load C:\home\LabVIEW\data\20080818_or734m\kh008_SL_LMAN.mat
% % load C:\home\LabVIEW\data\20000530_or230m\rm183_BOS_LMAN.mat
% load C:\home\LabVIEW\data\20080920_gr729m\kh004_BOS_LMAN.mat
% yo=voltage(1:end,2:end);
% 
% fprintf('Median Filtering on neuron 2 data...\n')
% y=medfilt1(yo,ceil(0.003*Fs),size(yo,2),2);
% clear voltage;
% 
% fprintf('done\n')
% [M,T] = size(x);
% t = linspace(0,T/Fs,T);
%  
% D = ceil(0.5*Fs);
% coh = coherency_02(x,y,200);
% 
%% %  ex4)  Poisson spikes
% % % 
% Fs= 11025; 
% D = ceil(0.5*Fs);
% nFFT=2*Fs;
% WinLength=2*Fs;
% nOverlap=ceil(WinLength/2);
% NW=4;
% Detrend='';
% nTapers=5;
% 
% rate=4;
% noise_rate = 5;
% c = 1;
% shift = ceil(0.1*Fs);
% burst_shift = ceil(0.1*Fs);
% M=10;
% Tmax = 5;
% spkx = spalloc(5*Fs+1,M,M*Tmax*rate);
% spky = spalloc(5*Fs+1,M,M*Tmax*rate);
% nspkx = spalloc(5*Fs+1,M,M*Tmax*rate);
% nspky = spalloc(5*Fs+1,M,M*Tmax*rate);
% 
% for mm=1:M
%     
% [t,spk_c] = mkpssn([0 Tmax],rate*c,'dt',1/Fs);
% [t1,spk_1] = mkpssn([0 Tmax],rate*(1-c),'dt',1/Fs);
% [t2,spk_2] = mkpssn([0 Tmax],rate*(1-c),'dt',1/Fs);
% 
% spk_1 = spk_c + spk_1;
% spk_1 = spk_1 ; %spk_1(1,[end-burst_shift+1:end,1:end-burst_shift]);%...;
% %                + spk_1(1,[end-2*burst_shift+1:end,1:end-2*burst_shift]);
% spk_2 = spk_c(1,[end-shift+1:end,1:end-shift]) + spk_2;
% % spk_2=spk_1;
% 
% [to,noisy_spk1] = mkpssn([0 Tmax],noise_rate,'dt',1/Fs);
% [to,noisy_spk2] = mkpssn([0 Tmax],noise_rate,'dt',1/Fs);
% 
% spkx(:,mm)  = spk_1';
% spky(:,mm)  = spk_2';
% nspkx(:,mm) = noisy_spk1';
% nspky(:,mm) = noisy_spk2';
% end
% fprintf('\nDone\n');
% spkx    = spkx';   spky    = spky';
% nspkx   = nspkx';  nspky   = nspky';
% 
% % EPSP shapes of spk1
% tlen = length(spk_c);
% t = linspace(0,5,tlen);
% alpha1 = 1/0.02;
% % ts = linspace(0,10/alpha1,ceil(10/alpha1*Fs));
% % alpha1 = ts.*exp(-alpha1.*ts);
% ts = linspace(0,2/alpha1,ceil(2/alpha1*Fs));
% alpha1 = sin(2*pi*alpha1*ts);
% alp1_len = length(ts);
% 
% % EPSP shapes of spk2
% alpha2 = 1/0.01;
% % ts = linspace(0,10/alpha2,ceil(10/alpha2*Fs));
% % alpha2 = ts.*exp(-alpha2.*ts);
% ts = linspace(0,2/alpha2,ceil(2/alpha2*Fs));
% alpha2 = sin(2*pi*alpha2*ts);
% alp2_len = length(ts);
% 
% % plot(ts,alpha);
% noise_alpha = 1/0.02;
% ts = linspace(0,10/noise_alpha,ceil(10/noise_alpha*Fs));
% noise_alpha = ts.*exp(-noise_alpha.*ts)/noise_alpha;
% noisealp_len = length(ts);
% 
% x = conv2(full(spkx),alpha1,'full'); x=x(:,1:end-alp1_len+1);
% x= x+.5*conv2(full(nspkx),noise_alpha,'same');
% x = x+max(max(x))*0.001*rand(size(spkx));
% 
% y = conv2(full(spky),alpha2,'full'); y=y(:,1:end-alp2_len+1);
% y = y +0.5*conv2(full(nspky),noise_alpha,'same');
% y = y +max(max(y))*0.001*rand(size(spky));
% % x=full(spkx);
% % y=-full(spky);
% % 
% % common_noise = max(max(x))*0.001*randn(size(x));
% % x = x+common_noise;
% % y = y+common_noise;
% 
%  clf;plot(t,[x(1,:);y(1,:)]);
% % % % [mtcoh_mat,fo,to,stat]=mtcoherency_03(x,y,D,nFFT,Fs,WinLength,nOverlap,NW,Detrend,nTapers);
% % 
% %% % you can plot coherency 
% % 
% % ad hok method to remove synchrony peak at zero-lag. 
% 
% for jj=1:size(mtcoh_mat,3)
% for ii=1:size(mtcoh_mat,2)
%   [maxcoh,maxind]=max(mtcoh_mat(:,ii,jj));  
% mtcoh_mat(maxind,ii,jj)=mtcoh_mat(maxind+ceil(5*rand(1)),ii,jj);
% end
% end
% sigma= 2/1000;
% winx = 5*[-sigma,sigma]; winx = linspace(winx(1),winx(2),ceil(diff(winx)*Fs));
% window = normpdf(winx,0,sigma); window = window/sum(window);
% 
% mmtcoh=conv2(mean(mean(mtcoh_mat,3),2),window','same');clf;
% plot(delay*1000,mmtcoh,'LineWidth',2);hold on;
% % plot(delay*1000,mean(mean(mtcoh_mat,3),2));hold on;
% 
% mtshiftcoh=conv2(mean(mean(mtshiftcoh_mat,3),2),window','same');
% plot(delay*1000,mtshiftcoh,'LineWidth',2,'Color',[1 0 0]);hold on;
% % % plot(delay*1000,conv2(mean(mean(mtcov,3),2),ones(100,1)/100,'same'))
% n=10;
% index = [1:n:size(mtcoh_mat,1)];
% JNcoh = jackknife(@mean,permute(mtcoh_mat(index,:,:),[3,1,2]),1);
% N = size(JNcoh,1);
% JNstd = std(JNcoh,1)*(N-1)/N;
% JNstd = permute(JNstd,[2,3,1]);
% JNstd = conv2(JNstd,window(1:n:end)/sum(window(1:n:end)),'same');
% % % JNstd = conv2(mean(JNstd,2),ones(1,10)/10,'same');
% % 
% plot(delay(index)*1000,3*[JNstd,-JNstd],'-.');


%% Start of the program
%% Initialize X and Y
[T,nTrials]=size(x);

if nTrials>T  % number of trials is usually smaller than signal length, so make it tall matrix.
    x=x';
    [T,nTrials]=size(x);
end


[T,nTrials]=size(y);
if nTrials>T  % number of trials is usually smaller than signal length, so make it tall matrix.
    y=y';
    [T,nTrials]=size(y);
end

% default arguments and that
% [x,nFFT,Fs,WinLength,nOverlap,NW,Detrend,nTapers,nChannels,nSamples,nFFTChunks,winstep,select,nFreqBins,f,t] = my_mtparam(varargin);

% Ex  = mean(x,1); 
% Ey  = mean(y,1);
% for mm=1:nTrials
%     x(:,mm)=x(:,mm)-Ex(mm);
%     y(:,mm)=y(:,mm)-Ey(mm);
% end


t = linspace(0,T/Fs,T);

%

delay=[-D:D]/Fs;

winstep = WinLength - nOverlap;
% nFFTChunks = 1+floor((T-WinLength)/winstep);
if T==WinLength
    nFFTChunks = 1;
else
    nFFTChunks = ceil((T-WinLength)/winstep);
end
% nFFTChunks


mtcoh_mat = zeros(2*D+1,nFFTChunks,nTrials);
mtcov_mat = zeros(2*D+1,nFFTChunks,nTrials);
% if (nargout>=8)
    mtshiftcoh_mat = zeros(2*D+1,nFFTChunks,nTrials);
% end

% angle_mat = zeros(WinLength+1,nFFTChunks,nTrials);
fprintf('Multitapering...\n')
stat.varX=[];
stat.meanX=[];
for ii=1:nTrials
    if mod(ii,10)==1, fprintf('trial:');end
    fprintf(' %2d',ii); if mod(ii,10)==0, fprintf('\n');end
    [yo, fo, to, stattmp]=my_mtcsg([x(:,ii),y(:,ii)],nFFT,Fs,WinLength,nOverlap,NW,'',nTapers);
mtcohF = [yo(:,:,2,1)./sqrt(abs(yo(:,:,1,1)).*abs(yo(:,:,2,2)));...
          flipud(yo(2:end,:,1,2)./sqrt(abs(yo(2:end,:,1,1)).*abs(yo(1:end-1,:,2,2))))];
mtcoh = real(ifft(mtcohF,[],1));
mtcoh = [mtcoh(end-D+1:end,:);mtcoh(1:D+1,:)];
% size(mtcoh)
% size(mtcoh_mat)
mtcoh_mat(:,:,ii) =mtcoh; 

mtcovF = [yo(:,:,2,1);flipud(yo(2:end,:,1,2))];
mtcov = real(ifft(mtcovF,[],1));
mtcov = [mtcov(end-D+1:end,:);mtcov(1:D+1,:)];

mtcov_mat(:,:,ii) =mtcov; 

stat.varX = cat(3,stat.varX,stattmp.varX);
stat.meanX = cat(3,stat.meanX,stattmp.meanX);

% if nargout>=8
jj=ii+1; if (jj>nTrials), jj=1;end

[yo, fo, to, stattmp]=my_mtcsg([x(:,ii),y(:,jj)],nFFT,Fs,WinLength,nOverlap,NW,'',nTapers);
mtcohF = [yo(:,:,2,1)./sqrt(abs(yo(:,:,1,1)).*abs(yo(:,:,2,2)));...
    flipud(yo(2:end,:,1,2)./sqrt(abs(yo(2:end,:,1,1)).*abs(yo(1:end-1,:,2,2))))];
mtshiftcoh = real(ifft(mtcohF,[],1));
mtshiftcoh = [mtshiftcoh(end-D+1:end,:);mtshiftcoh(1:D+1,:)];
mtshiftcoh_mat(:,:,ii) =mtshiftcoh;
% end

% angle_mat(:,:,ii) = yo(:,:,2,1);
end
fprintf('\n');


%% ----- calculate Autocorrelation of x,y, and Cross Cov of x and y.


if nargout>=5   
    varargout{1}=mtcov_mat;
%     disp('Cxy is generated.')
end

if nargout>=6
    AxxF = [yo(:,:,1,1);flipud(conj(yo(:,:,1,1)))];
    Axx = ifft(AxxF,[],2)/size(x,2);
    Axx = [Axx(:,end-D+1:end),Axx(:,1:D+1)]; % Autocov of x.
    varargout{2}=Axx;
    clear AxxF;
end

if nargout>=7
    AyyF = [yo(:,:,2,2),conj(yo(end:-1:1,:,2,2))];
    Ayy = ifft(AyyF,[],2)/size(y,2);
    Ayy = [Ayy(:,end-D+1:end),Ayy(:,1:D+1)]; % Autocov of y.
    varargout{3}=Ayy;
    clear AyyF;
end

%% ------------- Calculate Shuffled Corrector -----------%
if nargout>=8
varargout{4}=mtshiftcoh_mat;
end
