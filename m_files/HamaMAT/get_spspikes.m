function spk = get_spspikes(v)
% Convert voltage traces to sparse spike matrix. 
% Stolen and modified from get_Spikes.m from wave_clus by Quian Quiroga. 
% Usage: spk = get_spspikes(v)
% v : MxT vector. 

handles.par.w_pre=20;                       %number of pre-event data points stored
handles.par.w_post=44;                      %number of post-event data points stored
handles.par.detection = 'both';              %type of threshold
handles.par.stdmin = 40.0;                  %minimum threshold
handles.par.stdmax = inf;                    %maximum threshold
handles.par.interpolation = 'y';            %interpolation for alignment
handles.par.int_factor = 2;                 %interpolation factor 
handles.par.detect_fmin = 300;              %high pass filter for detection
handles.par.detect_fmax = 3000;             %low pass filter for detection
handles.par.sort_fmin = 300;                %high pass filter for sorting
handles.par.sort_fmax = 3000;               %low pass filter for sorting
handles.par.segments = 1;                   %nr. of segments in which the data is cutted.
handles.par.sr = 11025;                     %sampling frequency, in Hz.
min_ref_per=1.5;                            %detector dead time (in ms)
handles.par.ref = floor(min_ref_per ...
    *handles.par.sr/1000);                  %number of counts corresponding to the dead time

[M,T]=size(v);
spk = spalloc(M,T,ceil(0.0001*M*T));
for mm=1:M      %that's for cutting the data into pieces
 
    % SPIKE DETECTION WITH AMPLITUDE THRESHOLDING
    [spikes,thr,index]  = amp_detect(v(mm,:),handles);       %detection with amp. thresh.
    spk(mm,index)=1;
end