function K=return_K(sigma2,X,Y)
% return yi \sigma_j lambda_j y_j K(Xi,Xj)
% by KH 2011/11/22

nsample=size(X,2);
% zeros(nsample);
dot_x = sum(X.*X,1);
XiXj    = X'*X;
unit_vec = ones(1,nsample);
for ii=1:nsample
%     K(ii,:)= exp(sigma2*(2*XiXj(ii,:)-dot_x-dot_x(ii)*unit_vec)).*;
    K(ii,:)= Y(ii)*exp(sigma2*(2*XiXj(ii,:)-dot_x-dot_x(ii)*unit_vec)).*Y';
end
% 
% 
% function G=return_G(sigma2,Xs,lmda,Ys,X)
% % return \sigma_s lambda_s y_s K(Xx,X) + b
% % by KH 2011/11/22
% 
% 
% nsample=size(X,2);
% 
% dot_xs = sum(Xs.*Xs,1);
% dot_x  = sum(X.*X,1);
% 
% XiXj    = X'*X;
% unit_vec = ones(1,nsample);
% for ii=1:nsample
% %     K(ii,:)= exp(sigma2*(2*XiXj(ii,:)-dot_x-dot_x(ii)*unit_vec)).*;
%     K(ii,:)= Y(ii)*exp(sigma2*(2*XiXj(ii,:)-dot_x-dot_x(ii)*unit_vec)).*Y';
% end