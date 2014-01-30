function [Posi_peaks, Nega_peaks]=detect_posi_nega_peaks(x,ci)
% [Posi_peaks, Nega_peaks]=detect_posi_nega_peaks(x,ci)
% x: Nx1 or 1xN a vector;
% ci: Nx2 confidence limit.
% 
%  ==== OUTPUT ====
%  Posi_peaks.val 
%  Posi_peaks.ind 
%  Nega_peaks.val 
%  Nega_peaks.ind 
% 
%% by KH. 20081204

hdn = ci(2,:)<0;
hup = ci(1,:)>0;

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
    elseif all(hup) % coh is always above the confidence limit
        cind=[1; length(hup)];
        [Posi_peaks.val,Posi_peaks.ind]=max(x([cind(1):cind(2)]));
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
elseif all(hdn) % coh is always above the confidence limit
    cind=[1; length(hup)];
     [Nega_peaks.val,Nega_peaks.ind]=min(x([cind(1):cind(2)]));
else
    
    Nega_peaks.val=[];
    Nega_peaks.ind=[];
end