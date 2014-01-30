function [tti,tt]=play_song_in_specwindow(handles)
% subroutine to play displayed song in panel given by a graphics handle (handles).
% song data is given in global variable 'ss'.
%
% % Usage: 
% play_song_in_specwindow(gca);
%
% % it can return the index of x axis and xlim.
% [xindex]=play_song_in_specwindow(gca); 
% [xindex,xlim_of_specgram]=play_song_in_specwindow(gca); 
%
% KH 20080606

tt=get(handles.axes(2),'XLim'); 
tti=ceil(tt*handles.F)+1;

tti(1)=max(1,tti(1));  % start index > 1.
tti(2)=min(length(handles.song),tti(2)); % end index < length(song)

% sound(ss.song(tti(1):tti(2)),ss.F);

sound(handles.song(tti(1):tti(2)),handles.F);