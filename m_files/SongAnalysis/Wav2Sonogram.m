% Wav2Sonogram 
% It converts .wav file into sonogram in .png format,
% in a certain directory.
% 
% by KH 2010/02/09

dirname=uigetdir;
S=dir(fullfile(dirname,'*.wav'));

nfft = 2^10;
fftwindow=nfft;
numoverlap=nfft-128;

figure(111);
for ss=1:length(S)
    loadname=fullfile(dirname,S(ss).name);
    fprintf('Loading %s,....\n',S(ss).name);
    [Y,FS,NBITS] = wavread(loadname);
    [y,f,t,p]=spectrogram(Y,fftwindow,numoverlap,nfft,FS);
    %     surf(t,f,10*log10(abs(p)),'EdgeColor','none');   view(0,90);
    width = t(end)*8;         % Initialize a variable for width.
    height = 4;          % Initialize a variable for height.
    dx1=.5;
    dx2=.5;
    dy=1;
    papersize=[width+dx1+dx2,height+2*dy];
    setPaperSize(papersize,12);clf;
    %         set(gcf, 'PaperUnits', 'centimeters');
    %         set(gcf, 'PaperSize', papersize);
    h=axes('Position',[dx1/(width+dx1+dx2),dy/(height+2*dy),width/(width+dx1+dx2),height/(height+2*dy)]);
    imagesc(t,f,10*log10(abs(p))); set(gca,'YDir','Normal');
    %     drawnow; pause(.1);
    title_txt=fullfile(dirname,S(ss).name);
    title_txt=strrep(title_txt,'\','\\');
    title_txt=strrep(title_txt,'_','\_');
    title(title_txt);
    savename=[loadname(1:end-4)];
    print(gcf,'-dpng',[savename,'.png'])
    
end