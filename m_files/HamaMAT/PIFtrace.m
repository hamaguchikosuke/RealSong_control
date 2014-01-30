%PIFtrace Single trace for perfect integrator:  X(t+dt) = X(t) + mu + sd*r
%
% Here mu and sd are constants and r is a random variable such that 
%
% <r> = 0 
% <r^2> = 1 
% <r_j r_i> = exp(-|i-j|*dt/taucorr)
%
% where taucorr is the correlation time constant of the inputs.  r may
% be Gaussian or binomial. The variable X stands for the voltage of
% the perfect integrate-and-fire neurons.  There is a barrier at X=0
% such that X cannot become negative.

% Emilio Salinas, April 2001

 %
 % Integrator parameters
 %
 dt  = 1.0;           % time step
 tau = 10;            % membrane time constant
 sd  = 1.40;
 mu  = 0.10;
 pdf = 2;             % 1=Gaussian; 2=binomial
 sd  = sd*dt/tau;     % renormalized mu 
 mu  = mu*dt/tau;     % renormalized sd
 X_th    = 1;         % threshold 
 X_reset = X_th/3;    % reset value
 taucorr = 0.0;       % correlation time constant
 %
 % Run parameters
 %
 nsteps= 1000;                  % number of time steps 
 %
 % Internal parameters
 %
 nrand = 10000;                 % random numbers sampled simultaneously
 nu = zeros(nsteps,1);          % number of steps from reset to threshold
 if taucorr>0 
     eps = exp(-dt/taucorr); 
 else 
     eps = 0; 
 end
 ps = (1+eps)/2;                % probability of same sign, for binary inputs
 sdfac = sqrt(1-eps^2);
 %
 % Initialize graphics
 %
 clf, hold on
 axis([0 dt*nsteps -0.25 X_th+0.75])
 plot([0 dt*nsteps],[X_th X_th],'b-')
 set(gca,'drawmode','fast','ytick',[0 1])
 line1 = line('color','y', 'erase','none');
 xlabel('Time (ms)')
 ylabel('X')
 %
 % Main loop
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
         if pdf==1
             xnew = sd*randn(1,nrand) + mu;
         elseif pdf==2
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
     X = X + x;
     % Enforce the barrier
     if X<0 
         X = 0; 
     end 
     % Update graph
     xn = xn + 1;
     set(line1, 'xdata',dt*[xn-1 xn], 'ydata', [Xold Xold]);
     set(line1, 'xdata',dt*[xn xn], 'ydata', [Xold X]);
     drawnow
     % Check for a spike
     if X > X_th 
         set(line1, 'xdata',dt*[xn xn], 'ydata', [X X_th+0.75], 'color','m');
         set(line1, 'xdata',dt*[xn xn], 'ydata', [X_reset X_reset], 'color','y');
         X = X_reset;
         ispike = ispike + 1;
         nu(ispike) = jj;
         jj = 0;
     end
     Xold = X;
 end
 nu(ispike+1:end) = [];
 % Compute <nu> and <nu^2> from simulation.
 if nu > 0
     m1sim = mean(nu);
     m2sim = mean(nu.^2);
 else
     m1sim = inf;
     m2sim = inf;
 end
 %
 % Compute <nu> and <nu^2> from analytic solution.
 % Good for binary inputs.
 %
 [m1eq m2eq] = PIFfpt(X_reset,X_th,mu,sd,ps);
 %
 % Compute CVs, convert to rates and print results
 %
 cvsim= sqrt(m2sim - m1sim.^2)./m1sim;
 cveq = sqrt(m2eq - m1eq.^2)./m1eq;
 rout = 1000/(dt*m1sim);
 rest = 1000/(dt*m1eq);
 disp(['output rate: ' num2str(rout) ' spikes/s'])
 disp(['CV_ISI     : ' num2str(cvsim)])
 disp(['mu         : ' num2str(mu)])
 disp(['sd         : ' num2str(sd)])
 disp(['taucorr    : ' num2str(taucorr)])  
 disp(['est rate   : ' num2str(rest) ' spikes/s'])
 disp(['est cv     : ' num2str(cveq) ' spikes/s'])
 disp([' '])
 
       
