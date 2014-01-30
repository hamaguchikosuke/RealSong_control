function [g,b] = predict(sv,X)
% [maxlmda,ind]=max(sv.lmda);

nsample=size(sv.Xs,2);
% zeros(nsample);
dot_xs = sum(sv.Xs.*sv.Xs,1);
XiXj    = sv.Xs'*sv.Xs;
unit_vec = ones(1,nsample);

K=[];
for ii=1:nsample
    %     K(ii,:)= exp(sigma2*(2*XiXj(ii,:)-dot_x-dot_x(ii)*unit_vec)).*;
    K(ii,:)= exp(sv.sigma*...
        (2*XiXj(ii,:)-dot_xs-dot_xs(ii)*unit_vec));
end

% get bias 
b=mean(sv.Ys(:)-K*(sv.lmda.*sv.Ys));
    
    
% b = sv.Ys(ind)-sv.lmda(ind)*sv_pol(sv.sigma,sv.Xs,sv.Xs(:,ind),sv.Ys,sv.lmda)'*sv.Ys;
% b = mean(sv.Ys(:)-sv.lmda.*(sv_pol(sv.sigma,sv.Xs,sv.Xs,sv.Ys,sv.lmda)'*sv.Ys));
% g = b + sv_pol(sv.sigma,X,sv.Xs,ones(length(X),1),ones(length(sv.Xs),1))*(sv.lmda.*sv.Ys);


%   dot_xs = sum(sv.Xs.*sv.Xs,1);
  dot_X = sum(X.*X,1);
  xxs =  X'*sv.Xs;
  
  K =  exp(sv.sigma *...
        (2 * xxs - dot_xs(ones(size(X,2),1),:) - repmat(dot_X(:),1,nsample)))...
        *(sv.lmda.*sv.Ys);
  
% get prediction   
g = b + K;
