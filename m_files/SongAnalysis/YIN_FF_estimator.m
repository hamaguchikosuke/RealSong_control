function [FF,t]=YIN_FF_estimator(x,Fs,varargin)
% Estimate fundamental frequency based on YIN-YANG algorithm
% proposed in Alain de Cheveigne and Hideki Kawahara,
% J. Acouts. Soc. Am, 111 (4), pp. 1917-1930, 2002.
%
% Implemented in MATLAB by Kosuke Hamaguchi, 2013.4.4.
% Note: the last step6, search for best local estimate was 
%
% Usage1)
% [FF,t]=YIN_FF_estimator(x,Fs);
% Input)
% x     : input singal (a vector).
% Fs    : sampling rate.
%
% Output)
% FF    : YIN estimate of fundamental frequency, estimated at every 1ms,
%       using default window size 2.5ms (suitable for zebra finch), and
%       search window lagT = 5ms.
% t     : time points.
%
% Usage2)
% [FF,t]=YIN_FF_estimator(x,Fs,winT,lagT,t);
%
% winT  : window size in ms. Default is 2.5ms (looking for FF > 400Hz).
% lagT  : length of search. Needs to be twice longer than the longest
%         expected period. Default is 5ms.
% t     : vector of time points to estimate FF.
%         t is placed at the center of winT, thus actual window is [t-winT/2,t+winT/2];
%         The sound in the window is compared to future time windows
%         until [t-winT/2+lagT t+winT/2+lagT].
%
%         If you prefer to compare the time in the past,
%         like actual real-time FF detection case,
%         use option 'backward' as below;
%
%
% Usage3)
% [FF,t]=YIN_FF_estimator(x,Fs,winT,lagT,t,threshold,option);
%
% threshold: absolute threshold to find minimum of "cumulative-mean
% normalized difference function". Default is 0.1.
%
% option: direction of search.
%       : 'forward' compares the time in the future (Default).
%       : 'backward' compares the time in the past
%          (real-time FF detection use this).
% 
% Usage4) You can check the details of analysis 
% [FF,t]=YIN_FF_estimator(x,Fs,winT,lagT,t,threshold,option,mode);
% mode :1 plot analysis.
%      :0 (default), just show progress bar. 
%      :-1 No verbose mode (No plotting, No progress bar).
%
%
%
%% example)
% % [x,Fs]=wavread('C:\home\Experiments\RealSong_ChronicData\grn1028m\SongData\grn1028m_41367.64484782_4_3_17_54_44.wav');
% 
% [x,Fs]=wavread('C:\home\Experiments\AivAxonStim_VTA_withErin\org1008m\org1008m_2013_03_11_115010.wav');
% 
% [B,A]=ellip(4,.1,50,[600,10000]/(Fs/2));
% x=filtfilt(B,A,x);
% 
% t=linspace(0,length(x)/Fs,length(x));
% figure(1);clf;
%  [y,f,t,p] = spectrogram(x,256,250,1024,Fs); 
%  imagesc(t,f,10*log10(abs(p)));set(gca,'YDir','normal');
% 
% 
% winT=4; % ms % lowest resolution is 1000/winT [Hz].
% lagT=2; % ms % needs to be twice longer than expected longest period.
% threshold= 0.1; % threshold for cumulative mean normalized difference function.
% option = 'forward';
% 
% t=[]; % use default, 1ms intervals.
% [FF,t]=YIN_FF_estimator(x,Fs,winT,lagT,t,threshold,option);
% 
% ca=caxis; caxis([+100 -5]+ca);
% hold on; plot(t,FF,'g');
%%

x=x(:); % make it column vector.
nx = length(x);

if nargin<3
    winT=2.5;
else
    winT=varargin{1};
end

if nargin<4
    lagT=5;
else
    lagT=varargin{2};
    if isempty(lagT)
        lagT=2*winT;
    end
end

if nargin<5
    t= winT/2/1000+[0:0.001:length(x)/Fs];
else
    t=varargin{3};
    if isempty(t)
        t= winT/2/1000+[0:0.001:length(x)/Fs];
    end
end

if nargin<6
    threshold=0.1;
else
    threshold=varargin{4};
    if isempty(threshold)
        threshold=0.1;
    end
end

if nargin<7
    option='forward';
else
    option = varargin{5};
    if isempty(option)
        option='forward';
    end
end

% Plot waveform difference function, and cumulative-mean normalized diff
% func.
if nargin<8
    mode=0;
else
    mode = varargin{6};
    if isempty(mode)
        option=0;
    end
end
if (mode>0)
figure(11);clf;
end

% if length(t)==1   
%     fprintf('winT=%3.1fms,lagT=%3.1fms,t=[%3.3f] (1x%d) vector.\n',...
%         winT,lagT,t(1),length(t));
% elseif length(t)==2
%     fprintf('winT=%3.1fms,lagT=%3.1fms,t=[%3.3f,...,%3.3f] (1x%d) vector.\n',...
%         winT,lagT,t(1),t(end),length(t));
% else
%      fprintf('winT=%3.1fms,lagT=%3.1fms,t=[%3.3f,...,%3.3f] (1x%d) vector.\n',...
%         winT,lagT,t(1),t(end),length(t));
% end
% fprintf('threshold=%3.1f,option=%s.\n',...
%     threshold,option)



nW=ceil(winT/1000*Fs);
nlag=ceil(lagT/1000*Fs);

% tic;
switch option
    case 'forward'
        W_index=1:nW;
        lag_index = nW+[0:(nlag-1)];
    case 'backward'
        
        W_index=nW:-1:1;
        lag_index = [0:-1:(-nlag+1)];
    otherwise
        error('Unknown option: Only available options are ''forward'' or ''backward''.');
end

%----- init FF and run --------%
FF=NaN(size(t));
%    h = waitbar(0,'Calculate YIN F0 estimates...');
           
last_progress=0;
last_pe = 0;

if (mode>=0), fprintf('YIN_FF_estimator:'); end
 
for ii=1:length(t)
    
    if (ii/length(t)>=last_progress+0.1) && (mode>=0)
        last_progress=last_progress+0.1;
        fprintf('%3.0d%%.',round(last_progress*100))
    end
    % Look for the first time of the window. 
    t_center_index=ceil((t(ii)-winT/2/1000)*Fs);
    
    wind=W_index+t_center_index;
    lagind=lag_index+t_center_index;
    
    % return NaN if one of the window falls outside of data. 
    if (wind(1)<1) || (wind(end)>nx)
        continue;
    elseif (lagind(1)<1) || (lagind(end)>nx)
        continue;
    end
    
    
%     xw=detrend(x(wind));
%     xl=detrend(x(lagind));
%  xl(1)=xw(end);

    xw=x(wind);
    xl=x(lagind);
    
   
    if (mode>0)
        subplot(3,1,1);cla;
        plot(wind,xw);hold on;
        plot(lagind,xl,'r');
    end

    
    % hankel matrix to generate time-lag matrix.
    d= hankel(xw,xl); 
    d=d-repmat(xw,1,nlag);
    
    d=sum(d.^2,1);
    if (mode>0)
        subplot(3,1,2);plot(d);
    end
    
    aved =cumsum(d)./[1:nlag];
    cumd = d./aved;
    cumd(1)=1;
    
    if (mode>0)
        subplot(3,1,3);cla;plot(cumd,'b.-');hold on;grid on;
        line(xlim,threshold*[1 1],'LineStyle','--');
    end
    
    
    
    % Bias on first dip below absolute threshold. 
    cumd_less_thresh=find(cumd<threshold,3,'first');
    
    % No bias in absolute threshold. 
%     cumd_less_thresh=find(cumd<threshold);
    if isempty(cumd_less_thresh) % No minimum lower than threshold, then take global minimum.
        [cumd_min,cumd_min_ind]=min(cumd);
    else % If there is a minimum lower than threshold,
        
         [cumd_min,cumd_min_ind]=min(cumd(cumd_less_thresh));
            cumd_min_ind=cumd_less_thresh(cumd_min_ind);
    end
    
    if (mode>0)
        plot(cumd_min_ind,cumd_min,'bo');
    end
    % toc
    
    df=1;
    % Calculate parabolic estimate (pe);
    if (cumd_min_ind==1)|| (cumd_min_ind==length(cumd))
        pe = 1;
        FF(ii)=NaN;
    else
        dy1 = cumd(cumd_min_ind-1)-cumd(cumd_min_ind);
        dy2 = cumd(cumd_min_ind)-cumd(cumd_min_ind+1);
        
        a = -(dy1-dy2)/(2*df^2);
        b = dy1/df - 2 * a * (cumd_min_ind-0.5);
        pe = -b/(2*a);
        c = cumd(cumd_min_ind-1)+a*(cumd_min_ind-1)^2+b*(cumd_min_ind-1);
        
        FF(ii)=Fs/(pe-1);
        last_pe=pe;
        
        if (mode>0)
            plot(pe,c+b^2/(4*a),'r.');
            line(pe*[1,1],ylim);
            fprintf('Parabolic estimate of FF=%4.1fHz\n',FF(ii));
        end
    end
    

end
% close(h);
if (mode>=0), fprintf('Done.\n'); end



