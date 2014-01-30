function n=psth_bar(spk,t_edges,Fs,varargin)
% generate psth bar plot, without overlaps.
% n=psth_bar(spk,t_edge,Fs), calculates number of spikes within 
% t_edges.
% %=== Inputs ====%
% spk:      MxT sparse matrix where M is the trial, T is time.
% t_edge:   1xK monotonic increasing vector [t1,t2,t3,...tk] in sec.
% spikes outside of [t1 tk] region is not counted.
% Fs    :   sampling rate
% 
% %=== outputs ===%
% n    :    1xK number of spike counts vector 
% It used hisc.m inside the program.
% To plot psth, use bar(t_edges,n,'histc');
% by KH 20091113
% 
% update: 2011/5/24
% n=psth_bar(spk,t_edge,Fs,'rate');
% returns psth which height is defined as spikes/sec per trial.
% 
% n=psth_bar(spk,t_edge,Fs,'sum');
% returns psth which height is defined as number of spikes in the bin 
% in all the trials (NOT averaged).
% 
% The default is 'sum'.
% 

t_offset=t_edges(1)*Fs;

[M,N]=size(spk);
[ic,ir]=find(spk);
ir=ir+t_offset;

if nargin==4
    opt=varargin{1};
else
    opt='sum';
end

if nargin==5
    do_plot=varargin{2};
    if ischar(do_plot) && strcmpi(do_plot,'plot')
        do_plot=1;
    elseif isnumeric(do_plot)
        do_plot;
    else
        error;
    end
else
    do_plot=0;
end

switch lower(opt)
    case 'rate'
        dt=t_edges(2)-t_edges(1);
        n=histc(ir,t_edges*Fs)/M/dt;
    case 'sum'
        n=histc(ir,t_edges*Fs);
    otherwise
        error('Unknown option psth_bar(t_edges,n,%s)!',opt);        
end


if(do_plot)
    bar(t_edges,n,'histc');
end