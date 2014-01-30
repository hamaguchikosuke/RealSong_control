function [tau_a,a,tau_b,b,c]=my_dualexp_fit_for_ICcurrentInj(t,y,varargin)
% dual exponential curve fit by minimizing squared error.
% [tau_a,a,tau_b,b,c]=my_exp_fit(t,x);
% [tau_a,a,tau_b,b,c]=my_exp_fit(t,x,x0);
% where exponential curve is a*exp(t/tau_a)+b*exp(t/tau_b)+c,
% == Inputs ==
% t is time vector, x is observed variable which
% you assume that it follows the exponential decay. 
% x0 is the estimate (initial guess) of [tau_a,a,tau_b,b,c].
% == Outputs ==
% tau_a, tau_b:  decay time constant
% c  :  limit of x in t->inf
% a,b  :  scale parameter,  (a+b+c) is estimated value x at t=0.
% 
%% ex)
% data_t=0:0.1:100;
% data_x=.4*exp(-data_t/20)+.8*exp(-data_t/2)+.02*rand(1,length(data_t))+.6;
% 
% [tau_a,a,tau_b,b,c]=my_dualexp_fit(data_t,data_x);
% 
% figure(1);clf;
% plot(data_t,data_x,'r');hold on;
% t=min(xlim):max(xlim);
% plot(t,c+a*exp(t/tau_a)+b*exp(t/tau_b),'k-');
%  by KH 20100915


if nargin==3
    x0=varargin{1};
else
    c=corrcoef(t,y);
    [max_t,maxind_t]=max(t);
    if c(1,2)<0        % decreasing  
        x0=[-(max(t)-min(t))/200,(max(y)-min(y))/40,-(max(t)-min(t))/2,(max(y)-min(y))/4,y(maxind_t)];
            else % increasing
        x0=[-(max(t)-min(t))/200,-(max(y)-min(y))/40,-(max(t)-min(t))/2,-(max(y)-min(y))/4,y(maxind_t)];
    end
end
fprintf('Initial estimate value: tau_a=%3.3g,a=%3.3g,tau_b=%3.3g,b=%3.3g,c=%3.3g\n',...
    x0(1),x0(2),x0(3),x0(4),x0(5));

data=[t;y];
% I set lower limit of the time constant of electrode as 1ms,
% because electrode capacitance is 1pF/mm of immersion length,
% therefore, if we use 100MOhm electrode, the time constant will be 0.1ms. 
LB=[-0.001,   0,     -inf,   0,   -inf]; % lower bound of tau_a,a,tau_b,b,c
% We used 1ms 
UB=[0,      inf,    0,     inf, inf];  % higher bound of tau_a,a,tau_b,b,c
[x,fval] = fminsearchbnd(@(x) dual_exp_fit(x,data),x0,LB,UB);

tau_a=x(1);
a=x(2);
tau_b=x(3);
b=x(4);
c=x(5);

if abs(tau_a)>abs(tau_b)
    d = a; a = b; b=d;
    tau_d = tau_a;    tau_a = tau_b; tau_b=tau_d;
end

fprintf('Estimated exp curve:    %3.3g*exp(t/%3.3g)+%3.3g*exp(t/%3.3g)+%3.3g\n',...
    a,tau_a,b,tau_b,c);
% 
% figure(1);clf;
% plot(data_t,data_x,'r.');hold on;
% plot(data_t,c+exp(-(data_t-b)/tau),'k-');



function sqerr=dual_exp_fit(x,data)

tau_a=x(1);
a=x(2);
tau_b=x(3);
b=x(4);
c=x(5);

t=data(1,:);
y=data(2,:);

exp_val=c+a*exp(t/(tau_a))+b*exp(t/tau_b);
sqerr=sum((y-exp_val).^2);

