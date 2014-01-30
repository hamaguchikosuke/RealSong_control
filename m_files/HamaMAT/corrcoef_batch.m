function [cxy,varargout]=corrcoef_batch(x,y,D,WinLength,nOverlaps,nShiftPredictor,varargin)
% [cxy] = corrcoef_batch(X,Y,D,WinLength,nOverlaps,nShiftPredictor,varargin)
% [cxy] = corrcoef_batch(X,Y,D,WinLength,nOverlaps,nShiftPredictor,nFFT)
% 
% [cxy,scxy] = corrcoef_batch(X,Y,D,WinLength,nOverlaps,nShiftPredictor)
% 
% [cxy,scxy,Axx,Ayy] = corrcoef_batch(X,Y,D,WinLength,nOverlaps,nShiftPredictor)
% 
% 
% Batch mode of correlation-coefficient. 
% It returns the normalized cross-covariance function of signals X and Y,
% which is equivalent to correlation-coefficient of X and Y with
% various time shift tau. 
% The shift-predictors can be also calculated efficiently in this m-file.
% 
% === INPUTS ====
% X and Y are Tx1 real valued vector, or TxM matrix, 
% where M is the number of trials,
% T is the length of the trial (bin number).
% 
% D: length of delays around zero. [-D:D]
% WinLength = length of moving window (default is length of X)
% nOverlap  = overlap between successive windows (default is WinLength/2)
% nShiftPredictor = number of shift predictor, 
%  the maximum number of nShiftPredictor is M*(M-1).
% 
% === OUTPUTS ===
% cxy is a (2d+1)xM matrix where i-th column 
% is the corrcoef of A(:,i) and B(:,i),
% where cxy(tau) = xcov(x,y)./sqrt(V(x)*V(y));
% 
% scxy is a (2d+1) x nShiftPredictor matrix. The i-th row 
% is the xcov of A(:,i) and B(:,j) where 
% if(i<M), j=i+1,  elseif(i==M), j=1; 
%  
% Axx is the auto-covariance of x, 
% Ayy is the auto-covariance of y,
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
% coh = corrcoef_batch(x',y',200,WinLength,nOverlaps,nShiftPredictor);

%% % ex2) 
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
% 
% fprintf('done\n')
% [T,M] = size(x);
% t = linspace(0,T/F,T);
%  
% D = ceil(0.5*F);
% 
% WinLength=ceil(2*F);; nOverlaps=0;nShiftPredictor=M;
% % [cxy,scxy] = corrcoef_batch(x,y,D,WinLength,nOverlaps,nShiftPredictor);
%

%% by KH 20080827.

[T,M]=size(x);
if nargin>=7
    nFFT=varargin{1};
else
    nFFT=T;
end
% nFFT=2^nextpow2(2*WinLength-1);

if nargin>=8
    is_hanning_on=strcmpi(varargin{2},'hanning_on');
else
    is_hanning_on=1;
end

if (is_hanning_on),     fprintf('Using Hanning Window for CorrCoef Calculation\n');
else                    fprintf('Not Using Hanning Window for CorrCoef Calculation\n');
end
if isempty(WinLength), WinLength=T; end

if WinLength>T
    fprintf('WinLength (%d) should be smaller than length of x (%d)',WinLength,T);
    error;
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

if (nShiftPredictor > M*(M-1))
    error('nShiftPredictor should be less than or equal to M*(M-1)');
end

cxy = zeros(2*D+1,M,nFFTChunks);
if (nargout>=2),    scxy = zeros(2*D+1,nShiftPredictor,nFFTChunks);  end
if (nargout>=3),    cxx  = zeros(2*D+1,M,nFFTChunks); end
if (nargout>=4),    cyy  = zeros(2*D+1,M,nFFTChunks); end

windw = repmat(hanning(WinLength),[1,M]);
%%
for ii=1:nFFTChunks
    xx = x((ii-1)*winstep+[1:WinLength], :);
    yy = y((ii-1)*winstep+[1:WinLength], :);
    
    if (is_hanning_on)
        xx=xx.*windw;
        yy=yy.*windw;
    end
    
    xx=detrend(xx,'l');
    yy=detrend(yy,'l');
    
    stdxx = std(xx,1);
    stdyy = std(yy,1);
    %% Calculate Correlation-Coefficient
    
    xf = fft(xx,nFFT,1);
    sxf = xf;
    yf  = fft(yy,nFFT,1);
    
    Pxx = xf.*conj(xf);
    Pyy = yf.*conj(yf);

    Pxy = xf.*conj(yf);
    cxytmp = ifft(Pxy,[],1)/T;
    cxy(:,:,ii) = [cxytmp(end-D+1:end,:);cxytmp(1:D+1,:)];
    cxy(:,:,ii) = cxy(:,:,ii)./repmat(stdxx.*stdyy,[2*D+1,1]);
    
%     cohF= Pxy./sqrt(abs(Pxx).*abs(Pyy));
%     cohtmp = real(ifft(cohF,[],1));
%     cohtmp = [cohtmp(end-D+1:end,:);cohtmp(1:D+1,:)];
%     coh(:,:,ii)=cohtmp;
    
    %% Shift predictor
    shiftP_step = M;
    nshift_loop = ceil(nShiftPredictor/shiftP_step);
    rem_M       = mod(nShiftPredictor,shiftP_step);
    if rem_M==0, rem_M=shiftP_step; end
    
    scoh_index_all = [1:nShiftPredictor];

    
    if (nargout>=2)
        for nn=1:nshift_loop
            ls = 1+M*(nn-1);
            if nn<nshift_loop
                le = ls-1 + M;
            else
                le = ls-1 + rem_M;
            end
            scoh_index = scoh_index_all(ls:le);
            local_index = [ls,le]-ls+1;
            
            sxf = circshift(sxf,[0 -1]);               % Shift to left.
            stdxx = circshift(stdxx,[0,-1]);           % Shift to left.
            sPxy = sxf.*conj(yf);
            scohtmp = real(ifft(sPxy(:,local_index(1):local_index(2)),[],1))/T;
            scxy(:,scoh_index,ii) = [scohtmp(end-D+1:end,:);scohtmp(1:D+1,:)];
            scxy(:,scoh_index,ii) = scxy(:,scoh_index,ii)./repmat(stdxx(local_index(1):local_index(2)).*stdyy(local_index(1):local_index(2)),[2*D+1,1]);
            
        end
    end
    
     

    %% Auto-covariance
    if (nargout>=3)
        cxxtmp = ifft(Pxx,[],1)/T;
        cxx(:,:,ii) = [cxxtmp(end-D+1:end,:);cxxtmp(1:D+1,:)]; % Autocov of x.
    end
    
    %% Auto-covariance
    if (nargout>=4)
        cyytmp = ifft(Pyy,[],1)/T;
        cyy(:,:,ii) = [cyytmp(end-D+1:end,:);cyytmp(1:D+1,:)]; % Autocov of x.
    end
    

end
  

%% Set output
if nargout>=2,varargout{1}=scxy;end
if nargout>=3,varargout{2}=cxx; end
if nargout>=4,varargout{3}=cyy; end