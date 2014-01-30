function [coh,varargout]=coherency_01(x,y,D)
% [coh] = coherency(X,Y,d)
% 
% [coh,shifted_coh] = coherency_01(X,Y,D)
% 
% [coh,shifted_coh,Cxy,Axx,Ayy] = coherency_01(X,Y,D)
% 
% 
% 
% It returns the coherency function of signals X and Y,
% and their shift-predictors.
% 
% X and Y are 1xT real valued vector, or MxT matrix, 
% where M is the number of trials,
% T is the length of the trial (bin number).
% 
% coh is a Mx(2d+1) matrix where i-th row 
% is the xcov of A(i,:) and B(i,:)
% 
% shifted_coh is a Mx(2d+1) matrix. The i-th row 
% is the xcov of A(i,:) and B(j,:) where 
% if(i<M), j=i+1,  elseif(i==M), j=1; 
% 
% Axx is the auto-covariance of x, 
% Ayy is the auto-covariance of y,
% Cxy is the cross-covariance of x and y.
%%  % ex1) 
% 
%  omega = 2*pi; F= 1000; M = 50;
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
% % coh = coherency_01(x,y,200);
% 
%% % ex2) 
% 
% F= 11025; 
% cd C:\home\LabVIEW\data\20000513_or251m
% load rm139_BOS_HVC.mat
% x=voltage(:,2:end);
% fprintf('Median Filtering on neuron 1 data...\n')
% x=medfilt1(x,ceil(0.005*F),size(x,2),2);
% load rm139_BOS_LMAN.mat
% y=voltage(:,2:end);
% 
% fprintf('Median Filtering on neuron 2 data...\n')
% y=medfilt1(y,ceil(0.005*F),size(y,2),2);
% clear voltage;
% 
% fprintf('done\n')
% [M,T] = size(x);
% t = linspace(0,T/F,T);
%  
% D = ceil(0.2*F);
% coh = coherency_01(x,y,D);
%

%% by KH 20080827.


Ex  = mean(x,2); 
% if all(size(x)~=1) % x is matrix.
%     Ex = repmat(Ex,1,2*D+1);
% end

M = size(x,1);
% 
% for mm=1:M
%     x(mm,:)=x(mm,:)-Ex(mm);
% end
 
x = detrend(x,'linear');

window = hanning(size(x,2))';

% xf = fft(x.*repmat(window,M,1),2*size(x,2)-1,2);
% xf = fft(x.*repmat(window,M,1),size(x,2),2);
xf = fft(x,size(x,2),2);
% xf = fft(detrend(x).*repmat(window,M,1),2*size(x,2)-1,2);
Pxx = xf.*conj(xf);
% Pxx = abs(xf).^2;


Ey  = mean(y,2);
% if all(size(y)~=1) % x is matrix.
%     Ey = repmat(Ey,1,2*D+1);
% end


for mm=1:M
    y(mm,:)=y(mm,:)-Ey(mm);
end
% yf  = fft(y.*repmat(window,M,1),2*size(y,2)-1,2);
% yf  = fft(y.*repmat(window,M,1),size(y,2),2);
yf  = fft(y,size(y,2),2);
% yf  = fft(detrend(y).*repmat(window,M,1),2*size(y,2)-1,2);
Pyy = yf.*conj(yf);
% Pyy   = abs(yf).^2;

%% 
Pxy = yf.*conj(xf);
cohF= Pxy./sqrt(abs(Pxx).*abs(Pyy));
coh = real(ifft(cohF,[],2));
coh = [coh(:,end-D+1:end),coh(:,1:D+1)];
clear cohF;
%% ------------- Calculate Shuffled Corrector -----------%
if nargout>=2
sPxy = yf.*conj(xf([2:M,1],:));
% SAxy = ifft(Pxy,[],2)/size(x,2);
% SAxy = [SAxy(:,end-D+1:end),SAxy(:,1:D+1)];

ScohF= sPxy./sqrt(abs(Pxx([2:end,1],:)).*abs(Pyy));
shifted_coh = real(ifft(ScohF,[],2));
shifted_coh = [shifted_coh(:,end-D+1:end),shifted_coh(:,1:D+1)];
varargout{1}=shifted_coh;
end

%% ----- calculate Autocorrelation of x,y, and Cross Cov of x and y.

if nargout>=3    
    Cxy = ifft(Pxy,[],2)/size(x,2);
    Cxy = [Cxy(:,end-D+1:end),Cxy(:,1:D+1)];
    varargout{2}=Cxy;
end


if nargout>=4
    Axx = ifft(Pxx,[],2)/size(x,2);
    Axx = [Axx(:,end-D+1:end),Axx(:,1:D+1)]; % Autocov of x.
    varargout{3}=Axx;
end

if nargout>=5   
    Ayy = ifft(Pyy,[],2)/size(y,2);
    Ayy = [Ayy(:,end-D+1:end),Ayy(:,1:D+1)]; % Autocov of y.
    varargout{4}=Ayy;
end

