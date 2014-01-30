function y=shift_matrix(x,shift_index,dim)
% X=shift_matrix(X,shift_index,dim);
% 
% Here, X is a struct which contains matrix data of MxT size.
% shift_index must be 1xM or Mx1 vector.
% Each row is shifted by the amount of shift_index; 
%  
% In this code, re-align the time axis of matrix data by
% making a new matrix filled with NaN, 
% and filling each row with shifted data.
% In this case, the position of time zero will not change
% in the new matrix.
% 
% ex) x=[1 2 3 4 5; 6 7 8 9 10]; shift_index=[1,-1];
% y=shift_matrix(x,shift_index)
% 
% x=[1 2 3 4 5; 6 7 8 9 10]; shift_index=[2:-1:-2];
% y=shift_matrix(x,shift_index,1)
% 
% by KH 20121115

[N,M]=size(x);
y=nan(N,M);

% default is 2nd dimension shift.
if nargin==2
    dim=2;
end

if dim==2
    trialN=N;
elseif dim==1
    trialN=M;
else
    error('dim can be 1 or 2');
end


if length(shift_index)~=trialN
    error('length of shift_index (%d) is longer than the trial dimension of matrix (%d in %d x %d).\n',...
        length(shift_index),trialN,N,M);
end

if dim==2 % I try not to transpose huge matrix here.
    
    for nn=1:N
        if shift_index(nn)>0
            ind_to      =(1+shift_index(nn)):M;
            ind_from    =1:(M-shift_index(nn));
            y(nn,ind_to)=x(nn,ind_from);
        else
            ind_to      =1:(M+shift_index(nn));
            ind_from    =(1-shift_index(nn)):M;
            y(nn,ind_to)=x(nn,ind_from);
        end
    end
    
    
elseif dim==1
    
      
    for mm=1:M
        if shift_index(mm)>0
            ind_to      =(1+shift_index(mm)):N;
            ind_from    =1:(N-shift_index(mm));
            y(ind_to,mm)=x(ind_from,mm);
        else
            ind_to      =1:(N+shift_index(mm));
            ind_from    =(1-shift_index(mm)):N;
            y(ind_to,mm)=x(ind_from,mm);
        end
    end
    
end