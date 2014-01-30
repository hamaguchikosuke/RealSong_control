function [C,SC] = corrcoef_of_xcov(x,y,delay)
% correlation coefficient of cross-covariance of signal x and y.
% usage): [C,SC] = corrcoef_of_xcov(x,y,delay);
% where x is NxT matrix, where N is the # of trial,
%  T is the length of time.
% Output: 
% C is the Nx(2*delay+1) matrix with each row represents 
% corrcoef of i-th rows in x and y, which is
% C(i,:) = xcov(x(i,:),y(i,;))/std(x(i,:))/std(y(i,:));
% SC is the shuffled corrector of Nx(2*delay+1) matrix, which is 
% SC(i,:) = xcov(x(i,:),y(i+1,;))/std(x(i,:))/std(y(i+1,:));
% 
% x and y can includes NaN, which is just ignored.
% ex)
% t = linspace(0,4*pi,201);
% x =  sin(t)+randn(1,201);
% y =  cos(t)+randn(1,201);
%  
% by KH 20080731.

if nargout==2
    do_ShiftCorrector = 1;
else
    do_ShiftCorrector = 0;
end

[N1,T1] = size(x);
[N2,T2] = size(y);

if (N1~=N2) || (T1~=T2)
    error(['size of x (%3d,%3d) should be equal to size  of y (%3d,%3d)'],N1,T1,N2,T2);
end


if (T1==1)  % Nx1 vector, transpose 1xN.
    T1 = N1; N1 = 1; 
    T2 = N2; N2 = 1;
    x = x'; y = y';
end
    
 if (do_ShiftCorrector) && N1 ==1
     error(['Need more than two trials to calculate shift corrector.'])     
 end

max_delay = 2*delay+1;

C   = ones(N1,max_delay);

if (do_ShiftCorrector)
    SC  = ones(N1,max_delay);
end

% corr_p      = zeros(1,max_delay);
% corr_time_up = zeros(1,max_delay);
% corr_time_dwn    = zeros(1,max_delay);
per_done = 0;
per_done_old = 0;

for ii=1:N1
    
    per_done = ii/N1;
    
    if ii==N1
        ii_next = 1;
    else
        ii_next = ii+1;
    end
  
    
    for jj=[-delay:delay]
        if jj<0
            [corval,pval,corval_up,corval_dwn] = corrcoef(x(ii,abs(jj)+1:end),y(ii,1:end-abs(jj)),'rows','complete');
            C(ii,jj+delay+1)       = corval(1,2);
            if (do_ShiftCorrector)
            [corval,pval,corval_up,corval_dwn] = corrcoef(x(ii,abs(jj)+1:end),y(ii_next,1:end-abs(jj)),'rows','complete');
            SC(ii,jj+delay+1)       = corval(1,2);
            end
        else
            [corval,pval,corval_up,corval_dwn] = corrcoef(x(ii,1:end-jj),y(ii,jj+1:end),'rows','complete');
            C(ii,jj+delay+1)       = corval(1,2);
             if (do_ShiftCorrector)
            [corval,pval,corval_up,corval_dwn] = corrcoef(x(ii,1:end-jj),y(ii_next,jj+1:end),'rows','complete');
            SC(ii,jj+delay+1)       = corval(1,2);
             end
        end
%         corr_p(ii)          = pval(1,2);
%         corr_time_up(ii)    = corval_up(1,2);
%         corr_time_dwn(ii)   = corval_dwn(1,2);
    end
    
      
    if per_done>per_done_old+0.1
            fprintf('%2.2d%%..',ceil(ii/N1*100));
            per_done_old = per_done;
    end
    
end