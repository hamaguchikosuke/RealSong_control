function [kappa,lambda]=fitisigma(isi)
% fit Interspike Interval with gamma disrtibution.
% 
% by KH.

%% Gamfit
[N,x]=hist(isi,100);
param=gamfit(isi);
kappa=param(1);
lambda=param(2);

N = N/length(isi)/(x(2)-x(1));
stairs(x,N);hold on;

gamfity=gampdf(x,kappa,lambda);
plot(x,gamfity,'b--');

xlabel('ISI');
ylabel('P(ISI)');

%% cv2 fit
[cv2,nind]=cv2calc(isi) ;
estim_kappa = cv2tokappa(mean(cv2{:}));
estim_lambda = mean(isi)/estim_kappa;

estimy=gampdf(x,estim_kappa,estim_lambda);
plot(x,estimy,'g--');

%% Minimizing Squared Error 
q=fminsearch(@SE_N_gma,param,[],N,x)
xx = linspace(x(1),x(end),500);
y=gampdf(xx,q(1),q(2));
plot(xx,y,'r-');
axis([0 ceil(max(xx)*.4),ylim])


text(0.7*diff(xlim),0.7*diff(ylim),['gmafit \kappa=',num2str(kappa)],'Color','b');
text(0.7*diff(xlim),0.65*diff(ylim),['gmafit \lambda=',num2str(lambda)],'Color','b');

text(0.7*diff(xlim),0.55*diff(ylim),['CV_2 estim \kappa=',num2str(estim_kappa)],'Color','g');
text(0.7*diff(xlim),0.5*diff(ylim),['CV_2 estim \lambda=',num2str(estim_lambda)],'Color','g');

text(0.7*diff(xlim),0.4*diff(ylim),['fitted \kappa=',num2str(q(1))],'Color','r');
text(0.7*diff(xlim),0.35*diff(ylim),['fitted \lambda=',num2str(q(2))],'Color','r');

legend('Histgram','gamfit','Estimated','SE minimize');
function out = SE_N_gma(x0,N,x)
out= sum((N-gampdf(x,x0(1),x0(2))).^2);