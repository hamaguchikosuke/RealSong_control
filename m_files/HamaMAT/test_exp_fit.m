function test_exp_fit

data_t=0:20;
data_x=3+exp(-(data_t-2)/5)+rand(1,length(data_t));
data=[data_t;data_x];

[x,fval] = fminsearch(@(x) exp_fit(x,data),[1,1,1])

figure(1);clf;
plot(data_t,data_x,'r.');hold on;
tau=x(1);
b=x(2);
c=x(3);
plot(data_t,c+exp(-(data_t-b)/tau),'k-');

function sqerr=exp_fit(x,data)

tau=x(1);
b=x(2);
c=x(3);
data_t=data(1,:);
data_x=data(2,:);

exp_val=c+exp(-(data_t-b)/tau);
sqerr=sum((data_x-exp_val).^2);