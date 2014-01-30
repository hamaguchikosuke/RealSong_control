function [param]=Parameters_high_resol_adaptive_steps(fs,varargin)
%Parameters_high_resol_adaptive_steps(fs);
% Parameters_high_resol_adaptive_steps(fs,resol);
% default is, resol=0.5/1000; %0.5ms resolut


if nargin==2
    resol=varargin{1};
else
    resol=0.5/1000; %0.5ms resolution.
end



            param.fs=fs;
            param.cutoff=10*758400000;
            param.winstep=floor(resol*param.fs);% 0.5ms resolution.
%             param.window= 19*param.winstep;    % ~10ms window.
            param.window= 2^nextpow2(19*param.winstep);    % ~10ms window.
            param.pad=1024;%2^(nextpow2(param.window)+2);% ~padding size is more than twice larger than window size.
            param.cutoff_value=5.5;
            param.spectrum_range=256;%index %???
            
            fgrid = psdfreqvec('npts',param.pad,'Fs',fs,'Range','half')';
            minfreq=400;
            maxfreq=10000;
            
            param.min_freq_ampl=find(fgrid>minfreq,1,'first');%index 
            param.max_freq_ampl=find(fgrid<maxfreq,1,'last');;%index
            
            minfreq=800;
            maxfreq=10000;
            
            param.min_freq_entropy=find(fgrid>minfreq,1,'first');%index
            param.max_freq_entropy=find(fgrid<maxfreq,1,'last');;%index
            
            param.up_pitch  =floor(fs/8000);% index 7200hz??
            param.low_pitch =floor(fs/400);%index 400hz??
%             up_pitch=floor(fs/8000);% index fs/up_pitch hz??
%             low_pitch=floor(fs/400);%index fs/low_pitch hz??
            param.pitch_HoP=1800;%hz
            param.gdn_HoP=10;
            param.up_wiener=-2;
            param.pitch_averaging=1;%adjust pitch by its goodness
            param.x_length=750;
            param.y_length=250;
            param.initial_axes='on';
            param.NW=0;
            param.k=0;
            param.low_amplitude_th=0.15;

