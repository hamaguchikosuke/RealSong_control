function [synmatrix,varargout] = voltage2synevents_05( ...
    voltage,   ...  % time series as a vector
    threshold, ...  % threshold to define occurrence of synaptic events (multipled by STD of V)
    t_ref,...       % voltage over threshold within refractoriness is not counted as spike.
    F,...           % sampling frequency
    opt,varargin)   % opt: EPSP or IPSP.
% Voltage2SynEvents - returns sparse vector/matrix of synaptic events
% from voltage traces. 
%
% %Usage: 
%  synmatrix = voltage2synevents_XX( ...
%  voltage ,    ...      % time series as a vector/matrix
%  threshold,   ...      % threshold relative to STD of Delta_voltage 
%                        %   to define occurrence of synaptic events
%  refractoriness,...    % to neglect voltage trace over threshold 
%                        % after detection of a single event.
%  F,             ...    % sampling frequency
%  opt)                  % opt: EPSP 'e' and/or IPSP 'i'.
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
%  opt              : 'e' for EPSP only, 'i' for IPSP only, 'both' or 'ei'
%                   :  for both EPSP and IPSP
%                   : 'amp' for ampliutude onset, and offset (for sound
%                   onset-offset analysis)
% 
%  threshold is normalized to the SD of dV/dt = (V(t+dt)-V(t))/dt,
%  and default value of dt = 3ms.
% 
%  %Usage(2). You can change dt.
%  dt is in ms.  
%  synmatrix = voltage2synevents_03(v,threshold,ref,opt,dt)    
% 
% %Usage(3)
% [synmatrix, extremal_matrix, Dextremal_matrix]=...
%  voltage2synevents_03(voltage,threshold,refractoriness,F,opt) 
% %Output Arguments:
% synmatrix         : 1xN or NxM sparse binary matrix, representing the timing of 
%                     synaptic event. 
% extremal_matrix   : 1xN or NxM sparse matrix, representing the 
%                    extremal value and its timing. 
% Dextremal_matrix   : 1xN or NxM sparse matrix, representing the 
%                    difference of the extremal value from its baseline. 
% 
% For those data exported from Moonley Lab's LabView program 
% (SongPres,SongPresDual,SongPresTriple), 
% remove the first column data before use this program,
% because it contains the number of the column.
% 
% by KH 20081224

% update 20091112
% shift event timing dt. 
% This is because dv/dt is calculated by the difference between 
% time t+dt and t, so event actually occurs at t+dt. 
% by KH. 

%%  main code 
do_sanity_check=0;
use_slope_compensation =0;
use_zero_crossing=0;
use_fixed_threshold = 0;


if (use_zero_crossing) && (use_slope_compensation)
    error('both use_zero_crossing and use_slope_compensation cannot be TRUE');
end

% nargout

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

    

% % We remove this because it can happen that there is no spike within the data.
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

% assume spike occurs less than 0.01 percent of the data. 
% If more than that, sparse matrix automatically increases its size,
% but may take time to do so. Make it larger would be safe.

synmatrix = sparse([],[],[],n_trial,vol_len,ceil(n_trial*vol_len*0.0001));
if (do_check_extremal)
extremal_matrix = sparse([],[],[],n_trial,vol_len,ceil(n_trial*vol_len*0.0001));
Dextremal_matrix = sparse([],[],[],n_trial,vol_len,ceil(n_trial*vol_len*0.0001));
end

% In case there are NaN, we remove that effect.
for ii=1:size(voltage,1)
    ind=find(isnan(voltage(ii,:)));
    voltage(ii,ind)=nanmean(voltage(ii,:));
end

% dv=(voltage(:,D+1:end)-voltage(:,1:end-D))/D; 
% ddv=(dv(:,D+1:end)-dv(:,1:end-D))/D; 

% dv/dt is differently distributed in dv>0 and dv<0 region.
% dvstd = std(dv,0,2);


%---- if you want to see where is the threshold relative to dv/dt values.
if (do_sanity_check)
  
    myfigure(mfilename);
    
    fprintf('==== Sanity check mode in %s ==== \n',mfilename)
    t=linspace(0,length(voltage)/F,length(voltage))*1000;
    dt = t(2)-t(1);
    
%     for ii=1:size(voltage,1)
%         
%         dv=(voltage(ii,D+1:end)-voltage(ii,1:end-D))/(D*dt); 
% %         ddv=(dv(D+1:end)-dv(1:end-D))/D; 
%         
%         dve=dv;dve(find(dve<0))=NaN;
%         dvi=dv;dvi(find(dvi>0))=NaN;
%         dvstd_e=nanstd(dve,0,2);
%         dvstd_i=nanstd(dvi,0,2);
%         fprintf('min,max dvstd_e=%3.3g,%3.3g(D=%3.3d)\n',min(dvstd_e),max(dvstd_e),D);
%         
%         
%         threshold_e = abs(threshold)*dvstd_e;
%         threshold_i = abs(threshold)*dvstd_i;
% 
%         hh(1)=subplot(2,1,1,'replace');
%         title([num2str(ii) 'trial'])
%         plot(t,voltage(ii,:));
%         ylabel('mV');
%         
%         hh(2)=subplot(2,1,2,'replace');
%         plot(t(D+1:end),dv);
%         line(xlim,[threshold_e,threshold_e],'Color','k','LineStyle','--');
%         line(xlim,-[threshold_i,threshold_i],'Color','k','LineStyle','--');
%          line(xlim,[0 0],'Color','k');
%           ylabel('dV/dt');
%          
%           if use_slope_compensation
%               % y = ax +b, for given two points (x1,y1), (x2,y2),
%               %               % a = (y1-y2)/(x1-x2), b = y1-a*x1,
%               % here, dx = 1;
%               a = (dv(p_syn_ind_start(jj))-dv(p_syn_ind_start(jj)-1))/(1);
%               b = dv(p_syn_ind_start(jj))-a*p_syn_ind_start(jj);
%               true_ind = ceil(-b/a);
%           else
%               true_ind = p_syn_ind_start(jj);
%               
%           end
%           
%           true_ind_biased= true_ind+D;
%           
%           if (event(true_ind))>0
%               synmatrix(ii,true_ind_biased)=1;
%           else (event(true_ind))<0
%               synmatrix(ii,true_ind_biased)=-1;
%           end
%           
% %         
% %          hh(3)=subplot(3,1,3,'replace');
% %          plot(t(D+1:end-D),ddv(ii,:));
% %          line(xlim,[threshold_e(1:2)],'Color','k','LineStyle','--');
% %          line(xlim,-[threshold_i(1:2)],'Color','k','LineStyle','--');
% %          line(xlim,[0 0],'Color','k');
%         linkaxes(hh,'x');
%         pause;
%     end
end



% voltage = sign(voltage-threshold); % convert to -1,0,1 data.

% Main Loop for trial 
% if (use_fixed_threshold)
    dvMatrix = (voltage(:,D+1:end)-voltage(:,1:end-D))/D;
    dveMatrix = dvMatrix; dveMatrix(find(dvMatrix<0))=NaN;
    dviMatrix = dvMatrix; dviMatrix(find(dvMatrix>0))=NaN;
    
    dvstd_e   = mean(nanstd(dveMatrix,0,2));
    dvstd_i   = mean(nanstd(dviMatrix,0,2)); 
% end

for ii=1:n_trial
   %% First, determine the synaptic event timings
  
    dv=dvMatrix(ii,:);
    
    if (use_fixed_threshold)
        % do nothing;
    else
      
        dvstd_e=nanstd(dveMatrix(ii,:),0,2);
        dvstd_i=nanstd(dviMatrix(ii,:),0,2);
        
        %    dv=(voltage(ii,D+1:end)-voltage(ii,1:end-D))/D;
        %    dve=dv;dve(find(dve<0))=NaN;
        %    dvi=dv;dvi(find(dvi>0))=NaN;
        %    dvstd_e=nanstd(dve,0,2);
        %    dvstd_i=nanstd(dvi,0,2);
        
    end
  
   % fprintf('min,max dvstd_e=%3.3g,%3.3g(D=%3.3d)\n',min(dvstd_e),max(dvstd_e),D);
   
   
   threshold_e = abs(threshold)*dvstd_e;
   threshold_i = abs(threshold)*dvstd_i;
   
   switch lower(opt)
       case 'e'
           dvs = sign(dv-threshold_e); %  dv > threshold
           event = diff(dvs,[],2);    % [-1,-1,1,1,-1 -1] -> [0,2,0,-2,0]; detect potential timing of spike.
           
       case 'i'
           error('not tested yet.')
           %         dv = -sign(dv+threshold_i); % -dv>-threshold -> dv<threshold
           %         dv = diff(dv,[],2);    % [-1,-1,1,1,-1 -1] -> [0,2,0,-2,0]; detect potential timing of spike.
           
       case {'both','ei'}
           dve = sign(dv-threshold_e);
           dvi = -sign(dv+threshold_i);% look for crossing event from above to below.
           dve = diff(dve,[],2);    % [-1,-1,1,1,-1 -1] -> [0,2,0,-2,0]; detect potential timing of spike.
           dvi = diff(dvi,[],2);    % [-1,-1,1,1,-1 -1] -> [0,2,0,-2,0]; detect potential timing of spike.
           event  = sum([dve;dvi/2],1);% 2 is for onset, 1 is for offset.
           
           dv = sign(abs(dv)-threshold);
           %         dv = diff(dv,[],2);    % [-1,-1,1,1,-1 -1] -> [0,2,0,-2,0]; detect potential timing of spike.
           
       case 'amp'
           dve = sign(dv-threshold_e);
           dvi = sign(dv+threshold_i);  % look for crossing event from below to above.
           dve = diff(dve,[],2);    % [-1,-1,1,1,-1 -1] -> [0,2,0,-2,0]; detect potential timing of spike.
           dvi = diff(dvi,[],2);    % [-1,-1,1,1,-1 -1] -> [0,2,0,-2,0]; detect potential timing of spike.
           event  = sum([dve;dvi/2],1);% 2 is for onset, 1 is for offset.
           %         find(dv>0)
           %         find(dv<0)
       otherwise
           error('Unknown option!')
   end
   
    p_syn_ind_start = find(event>0); % potential event timings.
    lendv=length(event);
    
    if (do_sanity_check)
        hh(1)=subplot(2,1,1,'replace');
        title([num2str(ii) 'trial'])
        plot(t,voltage(ii,:)); hold on;
        ylabel('mV');
        
        hh(2)=subplot(2,1,2,'replace');
        plot(t(D+1:end),dv); hold on;
        line(xlim,[threshold_e,threshold_e],'Color','k','LineStyle','--');
        line(xlim,-[threshold_i,threshold_i],'Color','k','LineStyle','--');
        line(xlim,[0 0],'Color','k');
        ylabel('dV/dt');
        
          linkaxes(hh,'x');
    end
    
    for jj=1:length(p_syn_ind_start)
        
         if jj>1
             ISI= p_syn_ind_start(jj)-p_syn_ind_start(jj-1);
         else
             ISI=inf;
         end
         
        length_above_threshold=find(event(p_syn_ind_start(jj):end)<0,1,'first');
        
        if isempty(length_above_threshold),
            length_above_threshold=lendv-p_syn_ind_start(jj)+1;
        end
        
        if (length_above_threshold > min_exceeding_period) && (ISI>ref_bin)
            
            if (use_slope_compensation)
                % Linear interpolation to obtain dV/dt zero-crossing timing,
                % at which timing synaptic input is assumed to be arise.
                % Let's assume that initial phase is well approximated
                % by linear function, y = ax +b.
                % for given two points (x1,y1), (x2,y2) near threshold,
                % we can calculate coefficients as
                % a = (y1-y2)/(x1-x2), b = y1-a*x1,
                % here, x1-x2 = 1 (sample based);
%                 dv
                a = (dv(p_syn_ind_start(jj))-dv(p_syn_ind_start(jj)-1))/(1);
                b = dv(p_syn_ind_start(jj))-a*p_syn_ind_start(jj);
                fprintf('y=%3.1f x + %3.1f\n',a,b);
                zero_cross_ind = ceil(-b/a);
                detection_ind  = zero_cross_ind;
            elseif (use_zero_crossing)
                zero_cross_ind=find(dv(1:p_syn_ind_start(jj))<0,1,'last');
                detection_ind  = zero_cross_ind;
            else
                detection_ind = p_syn_ind_start(jj);  
            end
            
            detection_ind_biased= detection_ind+D;
            
            
            if (event(p_syn_ind_start(jj)))>0
                synmatrix(ii,detection_ind_biased)=1;
            else (event(p_syn_ind_start(jj)))<0
                synmatrix(ii,detection_ind_biased)=-1;
            end
            
%             if (do_sanity_check)
%                 axes(hh(1)); plot(t(detection_ind_biased),voltage(ii,detection_ind_biased),'o');
%                 axes(hh(2)); plot(t(detection_ind_biased),threshold_e,'o');
%             end
        end
        
        
    end
    if (do_sanity_check)
        plot_ind = find(synmatrix(ii,:)~=0);
        axes(hh(1)); plot(t(plot_ind),voltage(ii,plot_ind),'ko','MarkerSize',5);
        if (use_slope_compensation) || (use_zero_crossing)
            yplot_position = 0;
        else
            yplot_position = threshold_e;
        end
        axes(hh(2)); plot(t(plot_ind),yplot_position,'ko','MarkerSize',5);
    end
    
    %% If do_check_extreme, search the extremal values between two spikes.
    
    if (do_check_extremal) && length(p_syn_ind_start)>=1
        sinds = find(synmatrix(ii,:)>0);
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
                case 'amp'
                    [extp,p_synext_ind] = max(voltage(ii,sinds(kk):einds(kk))); % potential timings of reaching max value.
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
% 
% function [timings,extramals,Dextremals]=find_synaptic_events(dv,)


    