%OUPtrace Single time trace for the Ornstein-Uhlenbeck process
%
%  X(t+dt) = X(t)(1-eps) + eps*(mu + sd*r)
%
% When X reaches a threshold, a spike is produced and X -> X_reset.
% Here mu and sd are constants and r is a random variable such that 
%
% <r> = 0 
% <r^2> = 1 
% <r_j r_i> = exp(-|i-j|*dt/ctau)
%
% Two distributions can be used for r, Gaussian  or binomial.  The
% variable X stands for the voltage of the leaky integrate-and-fire
% neuron, which is closely related to the Ornstein-Uhlenbeck process
% that models a random walk. 

% Emilio Salinas, April 2000

 %
 % integrator parameters
 %
 dt  = 0.1;           % time step in ms
 tau = 1;             % membrane time constant
 sd  = 1.0;         
 mu  = 0.50;
 pdf = 1;             % 1=Gaussian; 2=binomial
 X_th    = 1;         % threshold voltage
 X_reset = 0;         % reset voltage
 taucorr = 0.0;       % correlation time constant
 %
 % run parameters
 %
 nsteps= 10000;                % number of time steps 
 %
 % internal parameters
 %
 nrand= 10000;                 % random numbers sampled simultaneously
 nu   = zeros(nsteps,1);       % number of steps from reset to threshold
 hh   = 1 - exp(-dt/tau);
 if taucorr>0 
     eps = exp(-dt/taucorr); 
 else 
     eps = 0; 
 end
 ps = (1+eps)/2;               % probability of same sign, for binary inputs
 sdfac = sqrt(1-eps^2);
 %
 % initialize graphics
 %
 clf, hold on
 axis([0 dt*nsteps -2.5 X_th+1.00])
 plot([0 dt*nsteps],[X_th X_th],'b-')
 set(gca,'drawmode','fast','ytick',[-3 -2 -1 0 1])
 line1 = line('color','y', 'erase','none');
 xlabel('Time (ms)')
 ylabel('X')
 %
 % main loop
 %
 if pdf==2
     x = -1 + 2*(rand<0.5); 
 else
     x = sd*randn*eps; 
 end
 X=X_reset; Xold=X_reset; 
 jj=0; ispike=0; jrand=nrand+1; xn=0;
 for j=1:nsteps
     jj = jj+1;
     jrand = jrand+1;
     if jrand > nrand
         jrand = 1;
         if pdf == 1
             xnew = sd*randn(1,nrand) + mu;
         elseif pdf == 2
             xnew = sd*( -1 + 2*(rand(1,nrand)<ps) );
         else
             error('Undefined PDF type')
         end
     end
     if pdf==2
         xold = x - mu;
         x = sign(xold)*xnew(jrand) + mu;
     else
         x = x*eps + sdfac*xnew(jrand);
     end
     % Update voltage
     X = X + hh*(-X + x);
     % Update graph
     xn = xn + 1;
     set(line1, 'xdata',dt*[xn-1 xn], 'ydata', [Xold Xold]);
     set(line1, 'xdata',dt*[xn xn], 'ydata', [Xold X]);
     drawnow
     % Check for a spike
     if X > X_th 
         set(line1, 'xdata',dt*[xn xn], 'ydata', [X X_th+1.00], 'color','m');
         set(line1, 'xdata',dt*[xn xn], 'ydata', [X_reset X_reset], 'color','y');
         X = X_reset;
         ispike = ispike+1;
         nu(ispike) = jj;
         jj = 0;
     end
     Xold = X;
 end
 nu(ispike+1:end) = [];
 % Compute <T>, <T^2> and <T^3> from simulations
 if nu > 0
     m1sim = dt*mean(nu);
     m2sim = (dt^2)*mean(nu.^2);
     m3sim = (dt^3)*mean(nu.^3);
 else
     m1sim = inf;
     m2sim = inf;
     m3sim = inf;
 end
 %
 % Compute <T>, <T^2> and <T^3> from analytic solutions
 % Good for uncorrelated inputs (ps=1/2).
 %
 [m1eq m2eq m3eq] = OUPfpt(X_reset,X_th,mu,sd,tau,dt);
 %
 % Compute CVs, convert to rates and print results
 %
 cvsim = sqrt(m2sim - m1sim.^2)./m1sim;
 cvest = sqrt(m2eq - m1eq.^2)./m1eq;
 rout  = 1000/m1sim;
 rest  = 1000/m1eq;
 disp(['output rate: ' num2str(rout) ' spikes/s'])
 disp(['CV_ISI     : ' num2str(cvsim)])
 disp(['mu         : ' num2str(mu)])
 disp(['sd         : ' num2str(sd)])
 disp(['taucorr    : ' num2str(taucorr)])  
 disp(['est rate   : ' num2str(rest) ' spikes/s'])
 disp(['est cv     : ' num2str(cvest) ' spikes/s'])
 disp([' '])

