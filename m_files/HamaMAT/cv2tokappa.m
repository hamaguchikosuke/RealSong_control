function kestim = cv2tokappa(cvtwo)
%
% it returns kappa(cv2), by solving nonlinear equation
% 4^(-k+1).*gamma(2*k)/gamma(k)^2/k-cvtwo=0.
% This can be solved for k < 50, which is cvtwo < 0.2513...
% because of the diverging property of gamma function.
% 
% For cvtwo < 0.26, we cannot solve this and returns NaN.
% by KH. 20070829

kestim = zeros(size(cvtwo));
for ii=1:prod(size(cvtwo))
    if cvtwo(ii)<0.26 || isnan(cvtwo(ii)),
        kestim(ii)=NaN;
%         fprintf('too small CV_2...\n')
    else
        f = @(k)4^(-k+1).*gamma(2*k)/gamma(k)^2/k-cvtwo(ii);
        kestim(ii) = fzero(f,[0.0001,50]);
    end
end