function [r,cv,mutmp]=r_star(r,tau,tauref,J,Ce,g,beta,muext,sig2ext,Vth,Vr,VL)
% usage: [r,cv]=r_star(r,tau,tauref,J,Ce,g,beta,muext,sig2ext,Vth,Vr,VL)
% returns the r and cv of the model,
% mu = J*(muext + Ce*(1-g*beta)*r)
% sigma^2 = J^2*(muext + Ce*(1+g^2*beta)*r)
% r is self-consistnetly determined.
% cv is also calculated.
% by KH 20070725
max_iteration = 1000; 
Epsilon = 1.e-12;
rold = r;

if nargin~= 12
  error(['input error: r_star(r,tau,tauref,J,Ce,g,beta,muext,sig2ext,Vth,Vr,VL)']);
end
for t = 1:max_iteration
  muin = J*Ce*(1-g*beta)*r;
  sig2in = J^2*Ce*(1+g^2*beta)*r;
  mu = muin+muext;mutmp(t)=mu;
  sig2 = sig2in+sig2ext;
  sig = sqrt(sig2);
  
%   if (mu==0)
%       r = 0
%       return;
%   end
  
  yth = (Vth-VL-mu)/sig;    yr = (Vr-VL-mu)/sig;
  
  rtmp = rate_mex(yth,yr,tau,tauref);
  if r <.001
    dt = .2; % To acceralate 
  else
    dt = .05;
  end
  % dr/dt = -r + f(r);
  r = (1-dt)*rold+dt*rtmp;
%   dr = [r-rold];
  if  r==rold
      [cv,r2]= cv_mex(yth,yr,tau,tauref);
%       fprintf('mu=%3.3g, sig2=%3.3g\n',mu,sig2);
%       fprintf('r=%3.3g cv=%3.3g, r2=%3.3g\n',r*1000,cv,r2*1000);
%    fprintf('r=%3.3g\n',r);  
    return;    
  end
  rold = r; % 
end

[cv,r2]= cv_mex(yth,yr,tau,tauref);
% fprintf('r=%3.3g cv=%3.3g, r2=%3.3g\n',r*1000,cv,r2*1000);
% fprintf('mu=%3.3g, sig2=%3.3g\n',mu,sig2);
