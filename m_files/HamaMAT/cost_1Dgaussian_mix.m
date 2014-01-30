 function log_posterior = cost_1Dgaussian_mix(p,x)
% fitting 1-D data points x by K-component gaussian.
% log_posterior = cost_gaussian_mix(x,p) where 
% p = [Ak; mu_k,sigma_k] are 3xK matrix, K is the number of gaussian.
% x should be 1xN or Nx1 vector.
% %
% ex) 
% Make data
%  x = randn(1000,1)+1; x = [x;.25*randn(500,1)-2];
%  Ak = [.5,.5]; muk = [.1,-.1];sigk = [1,1];
%  p = [Ak;muk;sigk];
%  cost_1Dgaussian_mix(p,x);
% % For graphical purpose.
%   xgrid=[-3:.1:3]
%  [N]=histc(x,xgrid);hold on;
%  N = N/sum(N)/(xgrid(2)-xgrid(1));
%  stairs(xgrid,N);
%% by KH 20080824
Ak      = p(1,:);
muk     = p(2,:);
sigk    = p(3,:);

if size(x,1)==1, x=transpose(x);end
x = repmat(x,1,length(muk));
Ak = Ak/sum(Ak); % It should be sum(Ak)=1;

A = -sum(log(Ak));
Ak = repmat(Ak,length(x),1);
muk = repmat(muk,length(x),1);
sigk = repmat(sigk,length(x),1);

log_posterior = sum(sum((x-muk).^2./(sigk).^2/2))-length(x)*A;
 

%%

 