function out = merge(X1,X2,opt)
% This is to merge two sequences. It does not distinguish same value
% in time. I mean, [0 1 2; 1 1 1]+[0 1 3;2 2 2] you need to use
% 'removesame' function to make it clean sequence. 
% = [0 0 1 1 2 3;3 3 3 3 3 2]
% USAGE: merge(X1,X2,opt), opt is '+' or '-' 
% X1 = [time;value]
% Feb.1.2002 by Kosuke Hamaguchi.

S = size(X1);
if S(1) > S(2)% In the case of long column matrix, 
  X1 = X1';	      % we assume it as X[(:,time),(:,value)],
                      % change to wide matrix.
end

S = size(X2);
if S(1) > S(2)% In the case of long column matrix, 
  X2 = X2';     % we assume it as X[(:,time),(:,value)]
end 

  
X1_t = X1(1,:);
X2_t = X2(1,:);
X1_x = X1(2,:);
X2_x = X2(2,:);


X1_c = interp1(X1_t, X1_x, X2_t);
X2_c = interp1(X2_t, X2_x, X1_t);

X1 = sort([X1_t X2_t;X1_x X1_c]',1);
X2 = sort([X2_t X1_t;X2_x X2_c]',1);

X_t = X1(:,1)';
switch(opt)
 case '+'
  X_x =  X1(:,2)'+X2(:,2)';
 case '-'
  X_x =  X1(:,2)'-X2(:,2)';
 case '*'
  X_x =  X1(:,2)'.*X2(:,2)';
 case '/'
  X_x =  X1(:,2)'./X2(:,2)';
 otherwise
  error('[invalid option:]',opt)
end

  out = [X_t;X_x];

%plot(out(1,:), out(2,:));
