function [Posi_peaks, Nega_peaks,varargout]=detect_posi_nega_peaks2(x,ci)
% [Posi_peaks, Nega_peaks,GlobalMaxMin]=detect_posi_nega_peaks2(x,ci)
% x: Nx1 or 1xN a vector;
% ci: Nx2 confidence limit.
% 
% added Global Maximum Minimum with confidence.
% modified 20090306 by KH
% 
%  ==== OUTPUT ====
%  Posi_peaks.val 
%  Posi_peaks.ind 
%  Nega_peaks.val 
%  Nega_peaks.ind 
% 
%  GMaxMin.gmax.val   % global max value
%  GMaxMin.gmax.ind   % global max index in delay
%  GmaxMin.gmax.conf  % above confidence limit or not. If 1, confidence. if 0, not confident. 
%  GMaxMin.gmin.val   % global min value
%  GMaxMin.gmin.ind   % global min index in delay
%  GMaxMin.gmin.conf  % below confidence limit or not. If 1, confidence. if 0, not confident. 
% 
% 
%% by KH. 20081204

hdn = ci(2,:)<0; % significantly below zero (down)
hup = ci(1,:)>0; % significantly above zero (up)

cL_exit_ind= find(diff(hup)>0);
cL_back_ind= find(diff(hup)<0);
% ==== find positive peaks =====
if any(hup) && ~isempty(cL_exit_ind) && ~isempty(cL_back_ind)
 
    
    if cL_back_ind(1)<cL_exit_ind(1) % coh start from above confidence limit
        %         cL_exit_ind=[1,cL_exit_ind];
        if length(cL_back_ind)>1
            cL_back_ind     = cL_back_ind(2:end);
        else
            cL_back_ind     = [];
        end
    end
    
    if cL_back_ind(end)<cL_exit_ind(end) % coh end with above confidence limit
        %            cL_back_ind=[cL_back_ind,length(ci)];
        cL_exit_ind=cL_exit_ind(1:end-1);
    end
    cind=[cL_exit_ind;cL_back_ind];
    
    Posi_peaks.val=zeros(1,size(cind,2));
    Posi_peaks.ind=zeros(1,size(cind,2));
    
    for ii=1:size(cind,2)
        [Posi_peaks.val(ii),Posi_peaks.ind(ii)]=max(x([cind(1,ii):cind(2,ii)]));
        Posi_peaks.ind(ii)=Posi_peaks.ind(ii)+cind(1,ii)-1;
    end
else
    Posi_peaks.val=[];
    Posi_peaks.ind=[];
end


 
% ==== find negative peaks =====
 cL_exit_ind= find(diff(hdn)>0);
 cL_back_ind= find(diff(hdn)<0);
if any(hdn) && ~isempty(cL_exit_ind) && ~isempty(cL_back_ind)
  
    
    if cL_back_ind(1)<cL_exit_ind(1) % coh start from above confidence limit
        %         cL_exit_ind=[1,cL_exit_ind];
        if length(cL_back_ind)>1
            cL_back_ind     = cL_back_ind(2:end);
        else
            cL_back_ind     = [];
        end
    end
    
    if cL_back_ind(end)<cL_exit_ind(end) % coh end with above confidence limit
        %         cL_back_ind=[cL_back_ind,length(ci)];
        cL_exit_ind=cL_exit_ind(1:end-1);
    end
    cind=[cL_exit_ind;cL_back_ind];
    
    Nega_peaks.val=zeros(1,size(cind,2));
    Nega_peaks.ind=zeros(1,size(cind,2));
    
    for ii=1:size(cind,2)
        [Nega_peaks.val(ii),Nega_peaks.ind(ii)]=min(x([cind(1,ii):cind(2,ii)]));
        Nega_peaks.ind(ii)=Nega_peaks.ind(ii)+cind(1,ii)-1;
    end
else
    Nega_peaks.val=[];
    Nega_peaks.ind=[];
end

%%
[maxx,maxx_ind] = max(x);
[minx,minx_ind] = min(x);

 GMaxMin.gmax.val = maxx;       % global max value
 GMaxMin.gmax.ind =maxx_ind;    % global max index in delay
 GMaxMin.gmax.conf=ci(1,maxx_ind)>0;  % above confidence limit or not. If 1, confidence. if 0, not confident. 
 GMaxMin.gmin.val = minx;     % global min value
 GMaxMin.gmin.ind =minx_ind;    % global min index in delay
 GMaxMin.gmin.conf=ci(2,minx_ind)<0; % below confidence limit or not. If 1, confidence. if 0, not confident. 

 varargout{1}=GMaxMin;
 

