function [tau,a,c]=my_exp_fit(t,y,varargin)
% exponential curve fit by minimizing squared error.
% [tau,a,c]=my_exp_fit(t,x);
% [tau,a,c]=my_exp_fit(t,x,x0);
% where exponential curve is a*exp(t/tau)+c,
% == Inputs ==
% t is time vector, x is observed variable which
% you assume that it follows the exponential decay. 
% x0 is the estimate (initial guess) of [tau,a,b,c].
% == Outputs ==
% tau:  decay time constant
% c  :  limit of x in t->inf
% a  :  scale parameter,  (a+c) is estimated value x at t=0.
% 
%% ex)
% data_t=[55+fix(10*rand(1,10)),90,100,200];
% data_x=.4*exp(-(data_t-50)/5)+.3*rand(1,length(data_t))+.6;
% 
% [tau,a,c]=my_exp_fit(data_t,data_x);
% 
% figure(1);clf;
% plot(data_t,data_x,'ro');hold on;
% t=min(xlim):max(xlim);
% plot(t,c+a*exp(t/tau),'k-');
%  by KH 20100915


if nargin==3
    x0=varargin{1};
else
    c=corrcoef(t,y);
    [max_t,maxind_t]=max(t);
    if c(1,2)<0        % decreasing  
        x0=[-(max(t)-min(t))/2,(max(y)-min(y)),y(maxind_t)];
            else % increasing
        x0=[-(max(t)-min(t))/2,-(max(y)-min(y)),y(maxind_t)];
    end
end
fprintf('Init value: tau=%3.3g,a=%3.3g,c=%3.3g\n',x0(1),x0(2),x0(3));

data=[t;y];

[x,fval] = fminsearch(@(x) exp_fit(x,data),x0);

tau=x(1);
a=x(2);
c=x(3);

fprintf('Estimated exp curve: %3.3g+%3.3g*exp(t/%3.3g)\n',c,a,tau);
% 
% figure(1);clf;
% plot(data_t,data_x,'r.');hold on;
% plot(data_t,c+exp(-(data_t-b)/tau),'k-');



function sqerr=exp_fit(x,data)

tau=x(1);
a=x(2);
c=x(3);

t=data(1,:);
y=data(2,:);

exp_val=c+a*exp(t/tau);
sqerr=sum((y-exp_val).^2);

