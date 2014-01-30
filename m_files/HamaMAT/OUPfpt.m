function [avg_T, avg_T2, avg_T3] = fpt_oup(x_reset,x_th,mu,sd,tau,dt)

%FPT_OUP First passage time for the Ornstein-Uhlenbeck process
%
% [avg_T, avgT2, avg_T3] = fpt_oup(x_reset,x_th,mu,sd,tau,dt)
%
% This expression gives the first three moments of the first 
% passage time for the Ornstein-Uhlenbeck process.  That is,
%
% x(t+dt) = x(t)(1-h) + (mu + sd*z)*h
%
% where 
%
% h = 1 - exp(-dt/tau) 
%
% and z is a random variable with <z>=0 and <z^2>=1 and delta 
% correlation. This corresponds to the ODE
%
% tau*dx/dt = -x + mu + sd*z
%
% Here x roughly corresponds to cell voltage. The actual solution is 
% the mean time <T> that it takes for x to go from the starting position 
% x_reset to the threshold x_th (equal to dt*<nu>, where <nu> is the  
% mean number of steps).  This is given by
%
% <T> = dt*(sqrt(pi/2)/h) intgral_{(x_reset-mu)/sd1}^{(x_th-mu)/sd1} 
%                                 exp(y^2/2)*(1+erf(y/sqrt(2))*dy
%
% where
%
% sd1 = sqrt(h/2)*sd
%
% The second and third moments <T^2> and <T^3> of the first passage 
% time are computed similarly, using recurrence relations.

% Emilio Salinas, April 2001

 h = 1 - exp(-dt/tau); 
 % x_th1 takes into account that at least 1 step is required to 
 % exceed threshold even if the starting voltage is equal to it.
 x_th1 = x_th + h*sd*0.43; 
 %
 % compute analytic solutions for <T>, <T^2> and <T^3>
 %
 if sd > 0
     sd1 = sd*sqrt(h/2);
     arg1 = (x_reset - mu)/sd1;
     arg2 = (x_th1 - mu)/sd1;
     [phi11 phi21 phi31] = OUPphi(arg1);
     [phi12 phi22 phi32] = OUPphi(arg2);
     avg_T = (dt/h)*(phi11 - phi12);
     csi1 = phi21 - 2*phi12*phi11;
     csi2 = phi22 - 2*phi12*phi12;
     avg_T2= ((dt/h)^2)*(csi1 - csi2);
     csi1 = phi31 - 3*phi21*phi12 - phi11*(3*phi22 - 6*phi12^2);
     csi2 = phi32 - 3*phi22*phi12 - phi12*(3*phi22 - 6*phi12^2);
     avg_T3= ((dt/h)^3)*(csi1 - csi2);
 elseif sd == 0
     arg1 = (mu - x_reset)/(mu - x_th);
     if arg1 <= 0
         avg_T = inf;
         avg_T2= inf;
         avg_T3= inf;
     else
         avg_T = (dt/h)*log(arg1);
         avg_T2= avg_T^2;
         avg_T3= avg_T^3;
     end 
 else
     avg_T = NaN;
     avg_T2= NaN;
     avg_T3= NaN;
     warning('SD must be >= 0')
 end
 
%====================================================================

function [phi1, phi2, phi3] = OUPphi(x)

% OUPPHI Computes phi functions for the Ornstein-Uhlenbeck process
%
% [phi1 phi2 phi3] = OUPphi(x)
%
% Following Shinomoto et al., two asymptotic approximations (series
% solutions) are used to compute the functions phi, which are used to
% compute the first passage time of the OUP and its higher moments.
%
% The first function computed is
%
% phi1(x) = -sqrt(pi/2) integral_0^x (1+erf(z/sqrt(2)))*exp((1/2)*z^2) dz
%
% For formulae see 
%     Shinomoto et al., 1999, Neural Comput 11:935.  

 RSmax = 100;  
 KRmax = 10;
 xlo = -5.7;
 xhi = -5.5;

 % Ricciardi-Sato approximation.  This is a straightforward series
 % solution (Frobenius method) to the differential equation whose
 % solution is equal to the Ricciardi integral. This applies to 
 % most reasonable parameters.
 if x >= xlo
    % for RSphi1
    gammaA = -sqrt(pi/2); 
    gammaB = -1/2; 
    RSphi1 = gammaA*x;
    RSphi1 = RSphi1 + gammaB*(x^2);
    % for phi2
    w1A = log(2);
    w1B = 0;
    RSphi2 = gammaA*w1A*x;
    RSphi2 = RSphi2 + gammaB*w1B*(x^2);
    % for RSphi3
    w2A = (pi^2)/12;
    w2B = 0;
    RSphi3 = gammaA*(w2A + w1A^2)*x;
    RSphi3 = RSphi3 + gammaB*(w2B + w1B^2)*(x^2);
    for n=3:RSmax
        m = n-2;
        y = x^n;
        % for RSphi1
        gamma  = (m/((m+2)*(m+1)))*gammaA;
        gammaA = gammaB;
        gammaB = gamma;
        RSphi1 = RSphi1 + gamma*y;
        % for RSphi2
        w1  = w1A - (1/m);
        w1A = w1B;
        w1B = w1;
        RSphi2 = RSphi2 + (w1*gamma)*y;
        % for RSphi3
        w2  = w2A - (1/(m^2));
        w2A = w2B;
        w2B = w2;
        RSphi3 = RSphi3 + ((w2 + w1^2)*gamma)*y;
    end
    RSphi2 = 2*RSphi2;
    RSphi3 = 3*RSphi3;
 end
 % Keilson-Ross approximation.  Seldom used.  Taken directly from
 % Shinomoto et al.
 if x < xhi
    p0 = 1;
    p1 = 0.63518142;
    p2 = 0.81857797;
    p3 = 0.78512305;
    z = log(abs(x));
    KRphi1 = p0*z + p1;
    KRphi2 = (1/2)*p0*(z^2) + p1*z + p2;
    KRphi3 = (1/6)*p0*(z^3) + (1/2)*p1*(z^2) + p2*z + p3;
    a = 0;
    b = 0.5;
    c = -0.5;
    for n=1:KRmax
        y = x^(-2*n);
        z = log(abs(x));
        p0= a*p0;
        p1= b*p0 + a*p1;
        p2= c*p0 + b*p1 + a*p2;
        p3=  0   + c*p1 + b*p2 + c*p3;
        KRphi1 = KRphi1 + y*(p0*z + p1);
        KRphi2 = KRphi2 + y*((1/2)*p0*(z^2) + p1*z + p2);
        KRphi3 = KRphi3 + y*((1/6)*p0*(z^3) + (1/2)*p1*(z^2) + p2*z + p3);
        a = -2*n*(2*n+1)/(2*n+2);
        b = (2*n + (2*n+1))/(2*n+2);
        c = -1/(2*n + 2);
    end
    KRphi2 = 2*KRphi2;
    KRphi3 = 3*2*KRphi3;
 end

 if x<-5.70, phi1=KRphi1; else phi1=RSphi1; end
 if x<-5.55, phi2=KRphi2; else phi2=RSphi2; end
 if x<-5.50, phi3=KRphi3; else phi3=RSphi3; end

%====================================================================

