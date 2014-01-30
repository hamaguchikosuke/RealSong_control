function [tti,tt]=add_specgram(gph)
% subroutine to add displayed song in main panel to sub-panel.
% song data is given in global variable 'ss'.
%
% % Usage: 
% add_specgram(gph)
%
% % it can return the index of x axis and xlim.
% [xindex]=play_song_in_specwindow(gca); 
% [xindex,xlim_of_specgram]=play_song_in_specwindow(gca); 
%
% KH 20080606

global ss s2;

% get absolute time.
tt=get(gph,'XLim'); 
tti=ceil(tt*ss.F)+1;

tti(1)=max(1,tti(1));  % start index > 1.
tti(2)=min(length(ss.song),tti(2)); % end index < length(song)

% get relative time difference.
ttd = diff(tt);         % length of time to be added.

% Update sub-figure data.
if isempty(s2.t),    maxt = 0; else,    maxt=max(s2.t);end
% length of t should be +1.
t = linspace(0,ttd,diff(tti)+1)+maxt;
s2.t=[s2.t,t];
s2.song=[s2.song,ss.song(tti(1):tti(2))];

set(s2.axes(1),'XData',s2.t,'YData',s2.song);

figure(2);
set(gcf,'CurrentAxes',s2.axes(2));

nfft = 1012;
fftwindow=nfft;
numoverlap=ceil(nfft/1.1);

specgram(s2.song,nfft,s2.F,fftwindow,numoverlap);




