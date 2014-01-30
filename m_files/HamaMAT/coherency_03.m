function [coh,varargout]=coherency_03(x,y,D,WinLength,nOverlaps)
% [coh] = coherency_03(X,Y,D,WinLength,nOverlaps)
% 
% [coh,shifted_coh] = coherency_03(X,Y,D,WinLength,nOverlaps)
% 
% [coh,shifted_coh,Cxy,Axx,Ayy,sCxy] = coherency_03(X,Y,D,WinLength,nOverlaps)
% 
% 
% 
% It returns the coherency function of signals X and Y,
% and their shift-predictors.
% 
% === INPUTS ====
% X and Y are Tx1 real valued vector, or TxM matrix, 
% where M is the number of trials,
% T is the length of the trial (bin number).
% 
% D: length of delays around zero. [-D:D]
% WinLength = length of moving window (default is length of X)
% % nOverlap  = overlap between successive windows (default is WinLength/2)
% 
% === OUTPUTS ===
% coh is a (2d+1)xM matrix where i-th column 
% is the xcov of A(:,i) and B(:,i)
% 
% shifted_coh is a (2d+1)xM matrix. The i-th row 
% is the xcov of A(:,i) and B(:,j) where 
% if(i<M), j=i+1,  elseif(i==M), j=1; 
% 
% Axx is the auto-covariance of x, 
% Ayy is the auto-covariance of y,
% Cxy is the cross-covariance of x and y.
% sCxy is shifted predictor of cross-covariance.
%%  % ex1) 
% 
%  omega = 2*pi; F= 1000; M = 50; WinLength=5*F; nOverlaps=0;
%  t = linspace(0,5,5*F+1);
%  noise_c = randn(M,length(t));
%  c        = 0.5; Delay = 50; D = 200;
%   noise_x = c*noise_c + (1-c)*randn(M,length(t));
%  noise_c = conv2([randn(M,Delay),-noise_c(:,1:end-Delay)],ones(1,10)/10,'same');
% % noise_c=[randn(M,Delay),-noise_c(:,1:end-Delay)];
%  noise_y = c*noise_c + (1-c)*randn(M,length(t));
% x = cos(omega*t)+cos(3*omega*t);
% x = repmat(x,M,1)+noise_x;
% y = cos(omega*t)+cos(3*omega*t);
% y = repmat(y,M,1)+noise_y;
% coh = coherency_03(x',y',200,WinLength,nOverlaps);

%% % ex2) 
% 
% F= 11025; 
% cd C:\home\LabVIEW\data\20000513_or251m
% load rm139_BOS_HVC.mat
% x=voltage(:,2:end);
% fprintf('Median Filtering on neuron 1 data...\n')
% x=medfilt1(detrend(x','l'),ceil(0.005*F),size(x,2),1);
% 
% load rm139_BOS_LMAN.mat
% y=voltage(:,2:end);
% 
% fprintf('Median Filtering on neuron 2 data...\n')
% y=medfilt1(detrend(y','l'),ceil(0.005*F),size(y,2),1);
% clear voltage;
% 
% WinLength=length(x); nOverlaps=0;
% 
% fprintf('done\n')
% [T,M] = size(x);
% t = linspace(0,T/F,T);
%  
% D = ceil(0.2*F);
% % coh = coherency_03(x,y,200,WinLength,nOverlaps);
%

%% by KH 20080827.

[T,M]=size(x);
% nFFT=T;
nFFT=2^nextpow2(2*T-1);

if isempty(WinLength), WinLength=T; end

if WinLength>T
    error('WinLength should be smaller than length of x');
end


if WinLength<nOverlaps
    error('WinLength should be larger than nOverlaps');
end


winstep = WinLength - nOverlaps;

if T==WinLength
    nFFTChunks = 1;
else
    nFFTChunks = ceil((T-WinLength)/winstep);
end

coh = zeros(2*D+1,M,nFFTChunks);
if (nargout>=2),    scoh = zeros(2*D+1,M,nFFTChunks); ScohF=zeros(T,M); end
if (nargout>=3),    cxy  = zeros(2*D+1,M,nFFTChunks); end
if (nargout>=4),    cxx  = zeros(2*D+1,M,nFFTChunks); end
if (nargout>=5),    cyy  = zeros(2*D+1,M,nFFTChunks); end
if (nargout>=6),    scxy  = zeros(2*D+1,M,nFFTChunks); end

windw = repmat(hanning(WinLength),[1,M]);

for ii=1:nFFTChunks
    xx = x((ii-1)*winstep+[1:WinLength], :);
    yy = y((ii-1)*winstep+[1:WinLength], :);
    
%         xx=detrend(xx.*windw,'l');
%         yy=detrend(yy.*windw,'l');
    xx=detrend(xx,'l');
    yy=detrend(yy,'l');
    
    %% Calculate Coherency
    
    xf = fft(xx,nFFT,1);
    Pxx = xf.*conj(xf);
    if (nargout>=2)
    sxf = fft(circshift(xx,[0 -1]),nFFT,1); % Shift to left.
    sPxx = circshift(Pxx,[0 -1]); % Shift to left.
    end
    yf  = fft(yy,nFFT,1);
    Pyy = yf.*conj(yf);

    Pxy = yf.*conj(xf);
    cohF= Pxy./sqrt(abs(Pxx).*abs(Pyy));
    cohtmp = real(ifft(cohF,[],1));
    cohtmp = [cohtmp(end-D+1:end,:);cohtmp(1:D+1,:)];
    coh(:,:,ii)=cohtmp;
    
    %% Shift predictor
    if (nargout>=2),    
        sPxy = yf.*conj(sxf);
        ScohF= sPxy./sqrt(abs(sPxx).*abs(Pyy)); 
        ScohF = real(ifft(ScohF,[],1));   
        scoh(:,:,ii) = [ScohF(end-D+1:end,:);ScohF(1:D+1,:)];
    end
    
     
    %% Cross covariance
    if (nargout>=3),   
        cxytmp = ifft(Pxy,[],1)/T;
        cxy(:,:,ii) = [cxytmp(end-D+1:end,:);cxytmp(1:D+1,:)];
    end
    
    %% Auto-covariance
    if (nargout>=4)
        cxxtmp = ifft(Pxx,[],1)/T;
        cxx(:,:,ii) = [cxxtmp(end-D+1:end,:);cxxtmp(1:D+1,:)]; % Autocov of x.
    end
    
    %% Auto-covariance
    if (nargout>=5)
        cyytmp = ifft(Pyy,[],1)/T;
        cyy(:,:,ii) = [cyytmp(end-D+1:end,:);cyytmp(1:D+1,:)]; % Autocov of y.
    end
    
     %% shift-predictor of Cross-covariance
    if (nargout>=6)
        cxytmp = ifft(sPxy,[],1)/T;
        scxy(:,:,ii) = [cxytmp(end-D+1:end,:);cxytmp(1:D+1,:)]; % shuffled xy.
    end

end
  

%% Set output
if nargout>=2,varargout{1}=scoh;end
if nargout>=3,varargout{2}=cxy; end
if nargout>=4,varargout{3}=cxx; end
if nargout>=5,varargout{4}=cyy; end
if nargout>=6,varargout{5}=scxy; end