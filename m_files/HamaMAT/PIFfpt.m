function [avg_nu, avg_nu2] = PIFfpt(x_reset,x_th,mu,sd,ps)

%PIFfpt First passage time for the PIF model with correlated inputs
%
% [avg_nu avg_nu2] = PIFfpt(x_reset,x_th,mu,sd,ps)
%
% This expression gives the solution to the first passage time
% equation for a perfect, nonleaky integrate-and-fire model neuron
% driven by stochastic inputs.  That is,
%
% X(t+dt) = X(t) + mu + sd*z
%
% where X represents the membrane potential and z is a binary random
% variable with z=1 or z=-1 with equal overall probabilities, such
% that <z>=0, <z^2>=1.  The key is that, in addition, z samples are
% correlated over time.  The correlation is determined by ps, which is
% the probability that the next z has the same sign as the previous
% one, so 
%
% ps = P(z_i=1|z_{i-1}=1) = P(z_i=-1|z_{i-1}=-1) 
%
% The probability of changing signs is pc=1-ps.  The cross correlation
% histogram of z goes like 
%
% <z_i z_j> = exp(-|i-j|dt/taucorr).
%
% where taucorr is the correlation time constant and
%
% ps = (1 + exp(-dt/taucorr))/2
%
% The quantity of interest is n, the number of steps that it takes for
% X to go from the starting position x_reset to the threshold x_th,
% assuming that there is a barrier at X=0 such that X cannot go below
% it. Notice that n is a random variable.  PIFfpt returns the first
% moment (the mean) <n> and the second moment <n^2> of n. The mean
% first passage time is simply
%
% T = <n>*dt
%
% and the coefficient of variation of the interspike intervals, which 
% measures the variability of the resulting spike train, is
%
% CV_{ISI} = sqrt(<n^2> - <n>^2)/<n>

% Emilio Salinas, April 2001

 if ps<0.5
     warning('1 >= ps >= 0.5 required')
     avg_nu = NaN;
     avg_nu2= NaN;
     return
 end

 if sd<0
     warning('sd should be positive')
     avg_nu = NaN;
     avg_nu2= NaN;
     return
 elseif sd==0 & mu<=0
     avg_nu = inf;
     avg_nu2= inf;
     return
 end

 if ps==0.5 | sd==0
     avg_nu = phi1A(x_th+sd,mu,sd) - phi1A(x_reset,mu,sd);
     if nargout>1
         avg_nu2 = phi2A(x_th+sd,mu,sd,x_th) ...
                   - phi2A(x_reset,mu,sd,x_th);
     end
 else
     if mu==0 
         avg_nu = phi1B(x_th+sd,sd,ps) - phi1B(x_reset,sd,ps);
         if nargout>1
             avg_nu2 = phi2B(x_th+sd,sd,ps,x_th) ...
                       - phi2B(x_reset,sd,ps,x_th);
         end
     else
         avg_nu = phi1C(x_th+sd,mu,sd,ps) ...
                  - phi1C(x_reset,mu,sd,ps);
         if nargout>1
             avg_nu2 = phi2C(x_th+sd,mu,sd,ps,x_th) ...
                       - phi2C(x_reset,mu,sd,ps,x_th);
         end
     end
 end

%====================================================================

% Computes the auxiliary function phi for <n> for the case ps=0.5;
% actually, there are three functions, depending on whether mu or sd
% are 0.

 function [phi] = phi1A(x,mu,sd)
     if sd>0 & mu==0
         phi = (x./sd)^2;
     elseif sd==0 & mu>0
         phi = x./mu;
     else
         alpha = 2*mu/(sd^2);
         c1 = 1/mu;
         c2 = 1/(alpha*mu);
         phi = c1*x + c2*exp(-alpha*x);
     end

%====================================================================

% Computes the auxiliary function phi for <nu^2> for the case ps=0.5;
% there are three functions, depending on whether mu or sd are 0.

 function [phi] = phi2A(x,mu,sd,x_th)
     if sd>0 & mu==0
         phi = (1/sd^4)*(2*x^2*(x_th+sd)^2 - ((x^4)/3));
     elseif sd==0 & mu>0
         phi = (2*x_th*x - x^2)/(mu^2);
     else
         alpha = 2*mu/(sd^2);
         cc = phi1A(x_th+sd,mu,sd);
         c1 = (2*cc)/(mu) + (sd^2)/(mu^3);
         c2 = -(1)/(mu^2);
         c3 = (cc*sd^2)/(mu^2) + (sd^4)/(mu^4);
         c4 = (sd^2)/(mu^3);
         phi = c1*x + c2*x^2 + (c3 + c4*x)*exp(-alpha*x);
     end

%====================================================================

% Computes the auxiliary function phi for <nu> for the case ps>0.5,
% mu=0, which can be solved exactly.

 function [phi] = phi1B(x,sd,ps)
     x  = x/sd;
     pc  = 1 - ps;
     h   = ps - pc;
     bet = sqrt(h/ps);
     bet2= bet^2;
     c0 = (ps*bet^5)/(2*pc);
     c1 = bet2*(bet + 1);
     c2 = pc/ps;
     c3 = ((bet^3)/2)*(1 + bet);
     if bet2>0
         c4 = 2/bet;
     else
         c4 = 0;  % this just to avoid the 1/0 error
     end
     phi = c0 + c1*x + c2*x^2 + c3*exp(-c4*x);

%====================================================================

% Computes the auxiliary function phi for <nu^2> for the case ps>0.5,
% mu=0, which can be solved exactly.

 function [phi] = phi2B(x,sd,ps,x_th)
     cc = phi1B(x_th+sd,sd,ps);
     x = x/sd;
     pc  = 1 - ps;
     bet = sqrt((ps-pc)/ps);
     bet2= bet*bet; 
     bet3= bet2*bet; 
     bet4= bet3*bet; 
     bet5= bet4*bet; 
     bet6= bet5*bet; 
     bet7= bet6*bet; 
     bet8= bet7*bet; 
     bet9= bet8*bet; 
     alpha = 2/bet;
     c0 = +((bet5*ps*cc)/(pc)) - (bet7)/(4) + (bet9*ps)/(2*pc*pc);
     c1 = -((bet5*pc)/(2*ps)) + bet2*(1+bet)*(2*cc+bet4);
     c2 = -bet5 - bet6 + (2*pc*cc)/(ps);
     c3 = -(2*pc*bet2*(1+bet))/(3*ps);
     c4 = -(pc*pc)/(3*ps*ps);
     c5 = +bet4*(cc+bet4) - (bet3*(2*cc+bet4)/2) + ...
           (bet5*(1+bet2)/(4));
     c6 = bet4*(1+bet2)*(1+bet)/2;
     phi = c0 + c1*x + c2*x^2 + c3*x^3 + c4*x^4 ...
           + (c5 + c6*x)*exp(-alpha*x);

%====================================================================

% Computes the auxiliary function phi for <nu> when ps>0.5, mu~=0,
% sd>0, which requires finding the root of a cubic equation; this is
% done numerically by calling ROOTS through alpha_solve below.

 function [phi] = phi1C(x,mu,sd,ps)
     x  = x/sd;
     mu = mu/sd;
     pc = 1 - ps;
     h  = ps - pc;
     alpha = alpha_solve(ps,mu);
     A  = (alpha/2) - mu;
     c0 = h/(2*mu*pc);
     c1 = 1/mu;     
     c2 = -(1/(alpha*mu))*((A+1)/(A-1));
     phi = c0 + c1*x + c2*exp(-alpha*x);

%====================================================================

% Computes the auxiliary function phi for <nu^2> when ps>0.5, mu~=0,
% sd>0, which requires finding the root of a cubic equation; this is
% done numerically by calling ROOTS through alpha_solve below.

 function [phi] = phi2C(x,mu,sd,ps,x_th)
     cc = phi1C(x_th+sd,mu,sd,ps);
     x  = x/sd;
     mu = mu/sd;
     pc  = 1 - ps;
     h   = ps - pc;
     alpha = alpha_solve(ps,mu);
     A  = (alpha/2) - mu;
     Ad = (h/(mu*pc))*(1 - (1/(2*mu*mu))) - (h*cc/(mu*pc));
     Bd = h/(mu*mu*pc);
     Ba = -(2*cc/mu) - (ps/(pc*mu^3));
     Ca = 1/(mu^2);
     Cd = 0;
     Ea = -(2*h*A/mu) - (2*h/(mu*(A-1))) + h*alpha*(Bd-Ba) ...
          -(((h*alpha^2)/2) - mu*alpha - 2*pc)* ...
                              (A*(Bd-Ba) - (2/(alpha*mu*(A-1))));
     temp = alpha*(A-1)*(h-(h*alpha-mu)*A) + ...
            (((h*alpha^2)/2) - mu*alpha - 2*pc)*(A^2 + mu) + ...
             h*alpha*(mu+1-alpha);
     Ea = Ea/temp;
     Ed = Ea*A;
     Da = -(2/(alpha*mu*(A-1))) + Bd-Ba - Ea*(mu+1-alpha);
     Da = Da/(alpha*(A-1));
     Dd = -(2/(alpha*mu*(A-1))) + A*(Bd-Ba) + Ea*(A^2 + mu);
     Dd = Dd/(alpha*(A-1));
     c0 = -Ad;
     c1 = -(Ba + Bd);
     c2 = -(Ca + Cd);
     c3 = -(Da + Dd);
     c4 = -(Ea + Ed);
     phi = c0 + c1*x + c2*x^2 + (c3 + c4*x)*exp(-alpha*x);

%====================================================================

% Finds the appropriate root of the cubic equation for alpha, where
% alpha is the exponent required for <n> and <n^2> when ps>0.5 and
% mu~=0.

 function [alpha] = alpha_solve(ps,mu)
     pc = 1 - ps;
     h  = ps - pc;
     coef3 = h/4;
     coef2 = -mu*ps;
     coef1 = mu^2 - ps;
     coef0 = 2*pc*mu;
     alpha = roots([coef3 coef2 coef1 coef0]);
     alpha = alpha(imag(alpha)==0);
     if mu<0
         alpha = alpha(alpha<0);
         alpha = max(alpha);
     else
         alpha = alpha(alpha>0);
         alpha = min(alpha);
     end

%====================================================================


