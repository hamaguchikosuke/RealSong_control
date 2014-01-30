%  test my_trainsvm

n1=50;
n2=50;

x1m = [2,2,2]';
x1s = 2;

x2m = [-2,-2,-2]';
x2s = 2;

dim=length(x1m);

x1 = repmat(x1m,1,n1)+ randn(dim,n1)*x1s;
x2 = repmat(x2m,1,n2)+ randn(dim,n2)*x2s;
y1 = ones(n1,1);
y2 = -ones(n2,1);

X=[x1,x2];
Y=[y1;y2];
figure(1);clf;
plot3(X(1,1:n1),X(2,1:n1),X(3,1:n1),'r.');hold on;
plot3(X(1,n1+1:end),X(2,n1+1:end),X(3,n1+1:end),'b.');

sigma2=1/(1.8);
%% generate test samples
n1t=10;
n2t=10;

x1 = repmat(x1m,1,n1t)+ randn(dim,n1t)*x1s;
x2 = repmat(x2m,1,n2t)+ randn(dim,n2t)*x2s;
y1 = ones(n1t,1);
y2 = -ones(n2t,1);

Xt=[x1,x2];
Yt=[y1;y2];

plot3(Xt(1,1:n1t),Xt(2,1:n1t),Xt(3,1:n1t),'m.');
plot3(Xt(1,n1t+1:end),Xt(2,n1t+1:end),Xt(3,n1t+1:end),'c.');


%%
sv=my_trainsvm(X,Y,sigma2);
[g_predict,b] = my_predictsvm(sv, Xt);
error_rate=nnz(g_predict.*Yt<0)/(n1t+n2t);
fprintf('Error rate: %g%%.\n', error_rate*100);


