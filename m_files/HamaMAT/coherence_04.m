function [coh,varargout]=coherence_04(x,y,D,WinLength,nOverlaps,nShiftPredictor)
% [coh] = coherence_04(X,Y,D,WinLength,nOverlaps,nShiftPredictor)
% 
% [coh,scoh] = coherence_04(X,Y,D,WinLength,nOverlaps,nShiftPredictor)
% [coh,scoh,cxx,cyy] = coherence_04(X,Y,D,WinLength,nOverlaps,nShiftPredictor)
% 
% 
% 
% It returns the coherence function of signals X and Y.
% and their shift-predictors. Note that, the coherence function is
% represented in Fourier domain.
%  
% === INPUTS ====
% X and Y are Tx1 real valued vector, or TxM matrix, 
% where M is the number of trials,
% T is the length of the trial (bin number).
% 
% D: length of delays around zero. [-D:D]
% WinLength = length of moving window (default is length of X)
% % nOverlap  = overlap between successive windows (default is WinLength/2)
% nShiftPredictor = number of shift predictor.
% 
% === OUTPUTS ===
% coh is a (2d+1)xM matrix where i-th column 
% is the xcov of A(:,i) and B(:,i)
% 
% scoh is a (2d+1) x nShiftPredictor matrix. 
% The i-th row is the coherency of A(:,i) and B(:,j) in time domain 
% where i ~= j.   
% 
% Cxx is the auto-covariance of x, 
% Cyy is the auto-covariance of y,
% 
%%  % ex1) 
% 
%  omega = 2*pi; F= 1000; M = 50; WinLength=5*F;
%  D=200;
%  nOverlaps=0;
%  nShiftPredictor=M*(M-1);
% 
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
% 
% % [coh,scoh] = coherence_04(x',y',D,WinLength,nOverlaps,nShiftPredictor);

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
% nShiftPredictor=M*(M-1);
% D = ceil(0.2*F);
% % coh = coherence_04(x,y,D,WinLength,nOverlaps,nShiftPredictor);
%

%% by KH 20080827.

[T,M]=size(x);
if isempty(x)
    coh=[];scoh=[];return;
end

nFFT=T;
% nFFT=2^nextpow2(2*T-1);

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

cohF = zeros(ceil(nFFT/2),M,nFFTChunks);
if (nargout>=2),    
    scoh = zeros(2*D+1,nShiftPredictor,nFFTChunks); 
end

windw = repmat(hanning(WinLength),[1,M]);

if (nargout>=3),    cxx  = zeros(2*D+1,M,nFFTChunks); end
if (nargout>=4),    cyy  = zeros(2*D+1,M,nFFTChunks); end

for ii=1:nFFTChunks
    xx = x((ii-1)*winstep+[1:WinLength], :);
    yy = y((ii-1)*winstep+[1:WinLength], :);
    xx=xx.*windw;
    yy=yy.*windw;
%         xx=detrend(xx.*windw,'l');
%         yy=detrend(yy.*windw,'l');
%     xx=detrend(xx,'l');
%     yy=detrend(yy,'l');
    
    %% Calculate Coherency
    
    xf = fft(xx,nFFT,1);
    Pxx = xf.*conj(xf);
    yf  = fft(yy,nFFT,1);
    Pyy = yf.*conj(yf);

    Pxy = xf.*conj(yf);                            % delay <0 is x leading.
    cohFtmp= Pxy.^2./(abs(Pxx).*abs(Pyy));
%     cohtmp = real(ifft(cohF,[],1));
%     cohtmp = [cohtmp(end-D+1:end,:);cohtmp(1:D+1,:)];
    cohF(:,:,ii)=cohFtmp(1:ceil(nFFT/2),:);
    %% Shift predictor
    if (nargout>=2)
        sPxx = Pxx; %circshift(Pxx,[0 -1]);                 % Shift to left.
        sxf  = xf./sqrt(abs(sPxx)); %circshift(xf, [0 -1])./sqrt(abs(sPxx));% Shift to left.
        syf  = conj(yf)./sqrt(abs(Pyy));                    % No shift.
        
        shiftP_step = M;
        nshift_loop = ceil(nShiftPredictor/shiftP_step);
        rem_M       = mod(nShiftPredictor,shiftP_step);
        if rem_M==0, rem_M=shiftP_step; end
        
        scoh_index_all = [1:nShiftPredictor];
        
        
        for nn=1:nshift_loop
            
            ls = 1+M*(nn-1);        % ls: start of recording index in scoh
            if nn<nshift_loop       % le: end of recording index in scoh
                le = ls-1 + M;
            else
                le = ls-1 + rem_M;
            end
            scoh_index = scoh_index_all(ls:le);
            local_index = [ls,le]-ls+1;
            
            sxf = circshift(sxf,[0 -1]);               % Shift to left.
            sPxy = real(ifft(sxf.*syf,[],1));  % sxf and syf are already normalized by sPxx and Pyy.
            scoh(:,scoh_index,ii) =...
                [sPxy(end-D+1:end,local_index(1):local_index(2));...
                sPxy(1:D+1,local_index(1):local_index(2))];
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

end % END of for loop in nFFTChunks
  

%% Set output
if nargout>=2,varargout{1}=scoh;end
if nargout>=3,varargout{2}=cxx; end
if nargout>=4,varargout{3}=cyy; end