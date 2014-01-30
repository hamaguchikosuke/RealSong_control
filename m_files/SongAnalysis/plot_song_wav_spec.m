function plot_song_wav_spec(song,F)
% Plot birdsong, edit, play. 
% usage: plot_song_wav_spec(song,F)
% 
% global variables, ss: related main figure. 
%                   s2: related sub-figure.
% KH 20080606.

% %%%%%  Initialization   %%%%%
global ss s2
%
if ~isvector(song)  % If song is the name of .wav file.
    if ischar(song) && strcmp(song(end-4:end),'.wav') % check 'song' is wav file.
        song_wavfile = song;
        [ss.song,ss.F,ss.NBits] = wavread(song_wavfile);
    end
else
    ss.song=song;
    ss.F   =F;
    ss.NBits=16;
end

% song vector is row vector.
if size(ss.song,1)~=1,
    ss.song=ss.song';
end

ss.t = [0,length(ss.song)/ss.F];
ss.t= linspace(ss.t(1),ss.t(end),length(ss.song)); % time.

% Initialize sub-figure data.
s2.song=[];
s2.F =ss.F;
s2.t=[];
s2.NBits=ss.NBits;

% %%%%%%%%%%%%%%%%%%%
figure(1);set(1,'Name','Main Song Panel')

mysubplot(2,1,1);
ss.axes(1)=plot(ss.t,ss.song); set(gca,'XTickLabel',[]);
axis([ss.t(1) ss.t(end) ylim]);

% Draw the region of specgram in song amplitude.
xx = xlim; yy=ylim;
ss.obj(1)=line([xx(1) xx(1) xx(2) xx(2)],[yy yy(end:-1:1)]);

mysubplot(2,1,2);

nfft = 1012;
fftwindow=nfft;
numoverlap=ceil(nfft/1.1);

specgram(ss.song,nfft,ss.F,fftwindow,numoverlap);
axis([ss.t(1) ss.t(end) ylim]);
ss.axes(2)=gca;


h1 = uicontrol('Style', 'pushbutton', 'String', 'Play',...
    'Position', [50 50 30 30],...
    'Callback', 'global ss; [tti,xs]=play_song_in_specwindow(ss); set(ss.obj(1),''XData'',[xs(1) xs(1) xs(2) xs(2)])');

h2 = uicontrol('Style', 'pushbutton', 'String', 'Add',...
    'Position', [80 50 30 30],...
    'Callback', 'global ss; add_specgram(ss.axes(2));');

% %%%%% Sub-figure %%%%%
figure(2);set(2,'Name','Main Panel')

mysubplot(2,1,1);
s2.axes(1)=plot(0,0);
set(gca,'XTickLabel',[]);
axis([ss.t(1) ss.t(end) ylim]);

mysubplot(2,1,2);
plot(0,0);
s2.axes(2)=gca;
% specgram(s2.song,nfft,ss.F,fftwindow,numoverlap);
axis([ss.t(1) ss.t(end) ylim]);


h3 = uicontrol('Style', 'pushbutton', 'String', 'Play',...
    'Position', [50 50 30 30],...
    'Callback', 'global s2; [tti,xs]=play_song_in_specwindow(s2.axes(2));');

h4 = uicontrol('Style', 'pushbutton', 'String', 'Clear',...
    'Position', [110 50 30 30],...
    'Callback', 'global s2; s2.t=[]; s2.song=[];[tti,xs]=play_song_in_specwindow(s2.axes(2));');

h5 = uicontrol('Style', 'pushbutton', 'String', 'Write',...
    'Position', [140 50 30 30],...
    'Callback', 'global s2; fn=input(''savename: '',''s'');wavwrite(s2.song,s2.F,s2.NBits,fn)');
