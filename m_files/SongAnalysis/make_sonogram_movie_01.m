function out=make_sonogram_movie_01(wavdata,Fs,moviename)
% wavdata   : vector of sound data
% Fs        : sampling frequency
% moviename : name of the quicktime movie.
% 
% make_sonogram_movie_01(wavdata,Fs,moviename)
% 
% by KH 20100720

figure(10);clf;

gphl.movie_fig=uipanel('BackgroundColor','white',...
            'Unit',     'Normalized',...
            'Position',[0 0 1 1]);
gphl.song_axes=axes('Parent',gphl.movie_fig,'Position',[0 .8 1 .2]);
gphl.songplot=plot(NaN,NaN,'b');hold on;
gphl.spkplot=plot(NaN,NaN,'ms');hold on;

gphl.song_marker_Strt    =plot(1,1,'Color',[1 0 0]);
gphl.song_marker_End     =plot(1,1,'Color',[1 0 0]);
gphl.song_marker_region  = patch(0,0,'r');

gphl.sonogram_axes=axes('Parent',gphl.movie_fig,'Position',[0 0 1 .75],'YDir','Normal');
gphl.sonogram=imagesc(NaN,NaN,NaN); colormap pink; hold on;
gphl.main_power_plot=plot(NaN,NaN,'Color','k');
linkaxes([gphl.song_axes,gphl.sonogram_axes],'x');
        
t=linspace(0,length(wavdata)/Fs,length(wavdata));

m_spec_deriv=sam_spectrum_deriv2(wavdata,Fs);
spec_t=linspace(t(1),t(end),size(m_spec_deriv,1));

f=Fs*(1:size(m_spec_deriv,2))/1024;
max_spec=max(max(m_spec_deriv));
min_spec=min(min(m_spec_deriv));
cutoff=0.001;
ImageSizeXMax=1000;

tsteps=ceil(length(spec_t)/ImageSizeXMax);

set(gphl.songplot,'XData',t,'YData',wavdata);
axis(gphl.song_axes,[t(1) t(end) min(wavdata), max(wavdata)]);
axis(gphl.song_axes,'off');

set(gphl.sonogram,'XData',spec_t(1:tsteps:end),'YData',f,'CData',m_spec_deriv(1:tsteps:end,:)');
axis(gphl.sonogram_axes,[spec_t(1) spec_t(end) 0 max(f)]);
caxis(gphl.sonogram_axes,cutoff*[-max_spec, max_spec]);
axis(gphl.sonogram_axes,'off');
% 
% 
% p=m_spec_deriv';
% gpm.os.specP = p;
% gpm.os.specT = t;
% gpm.os.specF = f;

%%
fps = 30;
dF=ceil(Fs/fps);
% moviename=regexp(moviename,'\.','tokens');
moviename=[strrep(moviename,'.mov',''),'.mov'];

fprintf('Creating the movie %s.\n', moviename);
MakeQTMovie('cleanup');

MakeQTMovie('start',moviename);
MakeQTMovie('size', [840 480]);
% MakeQTMovie('size', [840 480]/4);
MakeQTMovie('quality', 1);

for tt=[1:dF:length(t)];
    set(gphl.song_marker_Strt,'XData',[t(tt) t(tt)],'YData',[min(wavdata), max(wavdata)]);
    drawnow;
    MakeQTMovie('addfigure');
end


MakeQTMovie('framerate', fps);
MakeQTMovie('addsound',wavdata, Fs);
MakeQTMovie('finish');
fprintf('=== DONE!====\n');
finish_sound(3);
