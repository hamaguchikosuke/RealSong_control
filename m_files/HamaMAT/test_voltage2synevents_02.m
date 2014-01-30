% Usage: test_voltage2synevents_02.m
% 
% When you run this code, this program will ...
% 1) ask to select an ASCII data file (say, test.dat) which contains a
%    matrix of voltage. Each column is one trial, 
%    except for the first value that is a trial number. 
% 2) It calculates median filtered traces to remvoe spike. This may take time.
% 3) Once it's done, it shows the detected onset and peaks of EPSP events
% 4) press return to check all the trials.
% 5) It computes the delta EPSPs (peak of EPSP - baseline (10% value of that trial))
% 6) plot the histgram and cumulative frequency of Delta EPSP and 
% 7) save data into 'test_nEPSP.mat' in the same directory of test.dat, 
% 8) make Figs/ directory and save the figure as 'test_nEPSP.eps' and 'test_nEPSP.png'.

%% read data in ASCII format
% Please make sure that SongPres exported data is 
% (T+1)xM size matrix where T is the number of time bins,
% M is the number of trials.

do_check_trace=1;

%  You can tweak these parameters, mainly param.threshold.
param.threshold =1.2;
param.F         =11025;
param.ref       =3;
param.opt       ='e';
param.dt        =4;



[filename,pathname]=uigetfile;
v=load(fullfile(pathname,filename),'-ASCII');

trial=v(1,:); v=v(2:end,:)/10; 
fprintf('Median filtering with 5ms running window... may take time...\n')
mv=my_medfilt1(v,ceil(0.005*param.F),1)';
% Now mv is Mx(T+1) matrix (transposed).
%%
% for ii=1:length(trial)

[synmatrix, extremal_matrix, Dextremal_matrix]=...
voltage2synevents_02(mv,param.threshold,param.ref,param.F,param.opt,param.dt);

mv_sorted=sort(mv,2,'ascend');
percentile_for_baseline=0.1;
fprintf('Use baseline as the %d-percentile value of each trace\n',percentile_for_baseline*100)
baseline=mv_sorted(:,ceil(size(mv,2)*percentile_for_baseline));

if (do_check_trace)
figure(4);clf;
D=ceil(param.dt/1000*param.F);

fprintf('Hit any key to go next trial:\n (if you want to skip this, please set do_check_trace=0 near the first line in the code.)\n')
for ii=1:length(trial)
    figure(4);
dvdt=(mv(ii,D+1:end)-mv(ii,1:end-D))/D;
stddvdt=std(dvdt);
t=linspace(0,length(mv)/param.F,length(mv));

h(1)=subplot(2,1,1,'replace');
plot(t,mv(ii,:));hold on;ind=find(synmatrix(ii,:)); plot(t(ind),mv(ii,ind),'bo');
inde=find(extremal_matrix(ii,:)); plot(t(inde),mv(ii,inde),'r^');
title(sprintf('Trial: %d',trial(ii)));
xlabel('t');ylabel('V [mV]');
plot(xlim,baseline(ii)*ones(1,2),'k--');

h(2)=subplot(2,1,2,'replace');
plot(t(1:length(dvdt)),dvdt); line([xlim],param.threshold*[stddvdt stddvdt]); hold on;
linkaxes(h,'x');
xlabel('t');ylabel(sprintf('dV/dt (dt=%d)',param.dt));
dvdt_sign=sign(dvdt-param.threshold*stddvdt);
diff_dvdt_sign=diff(dvdt_sign,[],2);
plot(t(1:length(dvdt)),dvdt_sign*stddvdt*param.threshold,'m');
pause
end
fprintf('Done');
end

%%
baseline_sparse=spalloc(size(extremal_matrix,1),size(extremal_matrix,2),nnz(extremal_matrix));
for ii=1:length(trial)
ind=find(extremal_matrix(ii,:)~=0);
baseline_sparse(ii,ind)=baseline(ii);
end

dEPSP=extremal_matrix-baseline_sparse;
%%
figure(6);clf;

edges=linspace(0,100,100);

ind=find(dEPSP~=0);
n_dEPSP=histc(full(dEPSP(ind)),edges);

subplot(2,1,1);
bar(edges,n_dEPSP,'histc');
xlabel('\Delta EPSP');ylabel('# of event');
title(savename)

n_dEPSP=n_dEPSP/sum(n_dEPSP); % Normalized.
subplot(2,1,2);
stairs(edges,cumsum(n_dEPSP)); 
xlabel('\Delta EPSP');ylabel('cumulative frequency');

%% save data and print
savename=[filename(1:end-4) '_dEPSP'];

fprintf('saving dEPSP data in %s.mat\n',fullfile(pathname,savename));
save([fullfile(pathname,savename),'.mat'],'n_dEPSP','dEPSP','synmatrix','extremal_matrix','Dextremal_matrix','param')

mkdir(fullfile(pathname,'Figs'));
printname=fullfile(pathname,'Figs',savename);
print(gcf,'-depsc2',[printname '.eps']);
print(gcf,'-dpng',[printname '.png']);
