function [synmatrix,varargout] = voltage2synevents_03( ...
    voltage,   ...  % time series as a vector
    threshold, ...  % threshold to define occurrence of synaptic events (multipled by STD of V)
    t_ref,...       % voltage over threshold within refractoriness is not counted as spike.
    F,...           % sampling frequency
    opt,varargin)   ;        % opt: EPSP or IPSP.
% Voltage2SynEvents - returns sparse vector/matrix of synaptic events
% from voltage traces. 
%
% %Usage: 
%  synmatrix = voltage2synevents_03( ...
%  voltage ,    ...      % time series as a vector/matrix
%  threshold,   ...      % threshold relative to STD of Delta_voltage 
%                        %   to define occurrence of synaptic events
%  refractoriness,...    % voltage over threshold within refractoriness is not counted as spike.
%  F,             ...    % sampling frequency
%  opt)                  % opt: EPSP and/or IPSP
% 
% %Input Arguments:
%
%  voltage          : if 1xN or Nx1 vector, returns 1xN sparse spike matrix.
%                     if NxM matrix, each row represents one successive voltage trace.
%  threshold        : synaptic events at k-th index 
%                     if Delta_voltage(k+1)>=threshold*STD(voltage) &&...
%                        Deltavoltage(k)<threshold*STD(voltage);
%  refractoriness   : in millisecond. 
%  F                : Sampling frequency
%  opt              : 'e': EPSP only, 'i', IPSP only, 
%                   :  or 'both' for both e and i.
% 
%  It conputes dV = (V(t+dt)-V(t))/dt. Default is dt = 3ms.
% 
%  %Usage(2). You can change dt.
%  dt is in ms.  
%  synmatrix = voltage2synevents_03(v,threshold,ref,opt,dt)    
% 
% %Usage(3)
% [synmatrix, extremal_matrix, Dextremal_matrix]=...
%  voltage2synevents_03(voltage,threshold,refractoriness,F,opt) 
% %Output Arguments:
% synmatrix         : 1xN or NxM sparse matrix, representing the timing of 
%                     synaptic event. 
% extremal_matrix   : 1xN or NxM sparse matrix, representing the 
%                    extremal value and its timing. 
% extremal_matrix   : 1xN or NxM sparse matrix, representing the 
%                    difference of the extremal value from its baseline. 
% 
% For those data exported from Moonley Lab's LabView program 
% (SongPres,SongPresDual,SongPresTriple), 
% remove the first column data before use this program,
% because it contains the number of the column.
% 
% by KH 20081224

% update 20091112
% shift event timing by +dt. 
% This is because dv/dt is calculated by the difference between 
% time t+dt and t, and I assumed that event actually occurs at t+dt. 
% by KH. 

do_sanity_check=0;

if nargout>=2
    do_check_extremal = 1; % If 1, seach for the extremal value.
else
   do_check_extremal = 0; 
end

% validate input

if ~( isnumeric(voltage) && length(voltage) > 1 )
  error( '%s: 1st argument is not a numeric vector of length >= 2', mfilename)
end

if ~( isscalar(threshold) && isnumeric(threshold) )
  error( '%s: 2nd parameter threshold is not a numerical scalar.', mfilename)
end

if ~( isscalar(t_ref) && isnumeric(t_ref) )
  error( '%s: 3rd parameter t_ref is not a numerical scalar.', mfilename)
end

if ~( isscalar(t_ref) && isnumeric(t_ref) )
  error( '%s: 3rd parameter t_ref is not a numerical scalar.', mfilename)
end


% if  strmatch('e',lower(opt))
%     opt='e';
% elseif strmatch('i',lower(opt))
%     opt='i';
% else
%     error('voltage2synevents_03: 4th parameter opt should be {''e'',''I''}' );
% end
%     
    

% % We remove below line because it can happen that there is no spike within the data.
% if threshold < min(min(voltage)) || threshold > max(max(voltage))
%   error('voltage2synevents_03: 2nd parameter threshold is outside range of voltage')
% end

% Initializing parameters
if nargin>=6
    dt= varargin{1};
else
    dt= 3;              % [ms]
end

D = ceil(dt/1000*F);      % dV = (V(t+D)-V(t))/D;
ref_bin= ceil(t_ref/1000*F); % refractoriness in number of time points.

min_exceeding_period = 1; % time points
fprintf('synaptic event detection:\nthreshold=%d*std[dv/dt], dt=%3.1g[ms], ref=%3.2g[ms], F=%d, detection=%s.\n',...
    threshold,dt,t_ref,F,opt);

% Initializing variables
[n_trial,vol_len]=size(voltage);

if isvector(voltage) && n_trial~=1 % If vector is a Nx1 column vector,
    n_trial = 1; 
    vol_len = length(voltage);
    voltage = voltage';
end

% assume synaptic inputs occur sparsely, less than 0.01 percent of the data. 
% If more than that, sparse matrix automatically increases its size,
% but may take time to do so. Make it larger would be safe.

synmatrix = sparse([],[],[],n_trial,vol_len,ceil(n_trial*vol_len*0.0001));
if (do_check_extremal)
extremal_matrix = sparse([],[],[],n_trial,vol_len,ceil(n_trial*vol_len*0.0001));
Dextremal_matrix = sparse([],[],[],n_trial,vol_len,ceil(n_trial*vol_len*0.0001));
end

% In case there are NaN, replace by mean.
for ii=1:size(voltage,1)
    ind=find(isnan(voltage(ii,:)));
    voltage(ii,ind)=nanmean(voltage(ii,:));
end

dv=(voltage(:,D+1:end)-voltage(:,1:end-D))/D; 
dvstd = std(dv,0,2);

threshold = repmat(abs(threshold)*dvstd,[1,size(dv,2)]);


%---- if you want to see where is the threshold relative to dv/dt values.
if (do_sanity_check)
  
    fig_h=findobj('Name',mfilename);
    if ~isempty(fig_h)
        figure(fig_h);clf;        
    else
        figure('Name',mfilename,'NumberTitle','off');
    end
    fprintf('==== Sanity check mode in %s ==== \n',mfilename)
    t=linspace(0,length(voltage)/F,length(voltage))*1000;
    for ii=1:size(dv,1)
        hh(1)=subplot(2,1,1,'replace');
        title([num2str(ii) 'trial'])
        plot(t,voltage(ii,:));
        hh(2)=subplot(2,1,2,'replace');
        plot(t(D+1:end),dv(ii,:));
        line(xlim,[threshold(1:2)],'Color','k','LineStyle','--');
        line(xlim,-[threshold(1:2)],'Color','k','LineStyle','--');
         line(xlim,[0 0],'Color','k');
        linkaxes(hh,'x');
%         pause;
    end
end

switch lower(opt)
    case 'e'
dv = sign(dv-threshold);
    case 'i' 
dv = -sign(dv+threshold);
    case {'both','ei'}
dv = sign(abs(dv)-threshold);
    otherwise 
        error('Unknown option!')
end

dv = diff(dv,[],2);    % [-1,-1,1,1,-1 -1] -> [0,2,0,-2,0]; detect potential timing of spike.

% Main Loop for trial 
for ii=1:n_trial
   %% First, determine the synaptic event timings
    p_syn_ind_start = find(dv(ii,:)>0); % potential synaptic event timings.
    lendv=length(dv(ii,:));
    
    for jj=1:length(p_syn_ind_start)
        
         if jj>1
             ISI= p_syn_ind_start(jj)-p_syn_ind_start(jj-1);
         else
             ISI=inf;
         end
         
        length_above_threshold=find(dv(ii,p_syn_ind_start(jj):end)<0,1,'first');
        
        if isempty(length_above_threshold),
            length_above_threshold=lendv-p_syn_ind_start(jj)+1;
        end
        
        if (length_above_threshold > min_exceeding_period) && (ISI>ref_bin)
%             [ISI,ref_bin]
            synmatrix(ii,p_syn_ind_start(jj)+D)=1;
%              synmatrix(ii,p_syn_ind_start(jj)+D)=1;
        end
    end
    
    %% If do_check_extreme, search the extremal values between two spikes.
    
    if (do_check_extremal) && length(p_syn_ind_start)>=1
        sinds = find(synmatrix(ii,:));
        einds = [sinds(2:end),length(synmatrix(ii,:))];
        
        for kk=1:length(sinds)
            
            switch opt
                case 'e'
                    [extp,p_synext_ind] = max(voltage(ii,sinds(kk):einds(kk))); % potential timings of reaching max value.
                case 'i'
                    [extp,p_synext_ind] = min(voltage(ii,sinds(kk):einds(kk))); % potential timings of reaching min value.
                case {'both','ei'}
                    [extpe,p_synext_ind_e] = max(voltage(ii,sinds(kk):einds(kk))); % potential timings of reaching max value.
                    [extpi,p_synext_ind_i] = min(voltage(ii,sinds(kk):einds(kk))); % potential timings of reaching min value.
                    extp=[extpe,extpi];
                    p_synext_ind=[p_synext_ind_e,p_synext_ind_i];
                otherwise
                    error('Unknown option!')
            end
            extremal_matrix(ii,sinds(kk)+p_synext_ind-1)=extp;
            Dextremal_matrix(ii,sinds(kk)+p_synext_ind-1)=extp-voltage(ii,sinds(kk));
        end
    end
 
end

if (do_check_extremal) 
    varargout{1}=extremal_matrix;
    varargout{2}=Dextremal_matrix;
end


    