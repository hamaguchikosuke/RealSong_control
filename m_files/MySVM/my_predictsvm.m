function [g,b] = my_predictsvm(sv,X)
% [maxlmda,ind]=max(sv.lmda);

nsample=size(sv.Xs,2);
dot_xs = sum(sv.Xs.*sv.Xs,1);
XiXj    = sv.Xs'*sv.Xs;
unit_vec = ones(1,nsample);

K=[];
for ii=1:nsample
    %     K(ii,:)= exp(sigma2*(2*XiXj(ii,:)-dot_x-dot_x(ii)*unit_vec)).*;
    K(ii,:)= exp(sv.sigma2*...
        (2*XiXj(ii,:)-dot_xs-dot_xs(ii)*unit_vec));
end

b=mean(sv.Ys(:)-K*(sv.lmda.*sv.Ys));
    
    

  dot_X = sum(X.*X,1);
  xxs =  X'*sv.Xs;
  
  K =  exp(sv.sigma2 *...
        (2 * xxs - dot_xs(ones(size(X,2),1),:) - repmat(dot_X(:),1,nsample)))...
        *(sv.lmda.*sv.Ys);
  
% get prediction   
g = b + K;
