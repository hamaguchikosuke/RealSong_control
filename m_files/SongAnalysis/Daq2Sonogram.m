% Daq2Sonogram 
% It converts .daq file into sonogram in .png format,
% in a certain directory. It generates same name direcoty and put the png
% file there.
% 
% by KH 2010/02/09

figure(66);clf;
dirname=uigetdir;
S=dir(fullfile(dirname,'*.daq'));

nfft = 2^10;
fftwindow=nfft;
numoverlap=ceil(nfft/2);


for ss=1:length(S)
    loadname=fullfile(dirname,S(ss).name);
    fprintf('Loading %s,....\n',loadname);
    [data,time]=daqread(loadname);
    info=daqread(loadname,'info');
    FS=info.ObjInfo.SampleRate;
    
    savedir=fullfile(dirname,S(ss).name(1:end-4));
    fprintf('Making directory %s\n',savedir);
    mkdir(savedir);
    warning off;
    
%     [Y,FS,NBITS] = wavread(loadname);
[Tsize,Nch]=size(data);
ch=1;
nanind=find(isnan(data(:,ch)));
for nn=1:length(nanind)+1
    if nn==1
        start_ind=1;
        end_ind=nanind(nn)-1;
      
    elseif nn==length(nanind)+1
        start_ind=nanind(end)+1;
        end_ind=Tsize;
    else
        start_ind=nanind(nn-1)+1;
        end_ind=nanind(nn)-1;
    end
    t_start=time(start_ind);
    t_end=time(end_ind);
    Y=data(start_ind:end_ind,ch);
    
    [y,f,t,p]=spectrogram(Y,fftwindow,numoverlap,nfft,FS);
%     surf(t,f,10*log10(abs(p)),'EdgeColor','none');   view(0,90);
    imagesc(t,f,10*log10(abs(p))); set(gca,'YDir','Normal');
%     drawnow; pause(.1);
    title(sprintf('%s t=[%1.3g_%1.3g](%d)',...
        fullfile(dirname,S(ss).name),t_start,t_end,nn));
     saveopt=sprintf('%s_t=[%1.3g_%1.3g]_n=[%d]',...
        S(ss).name,t_start,t_end,nn);
    savename=S(ss).name(1:end-4);
    savename=fullfile(savedir,[savename,saveopt,'.png']);
    fprintf('saving %s...\n',savename);
    print(gcf,'-dpng',savename);
    
end
end