function cv2=cvtocv2(cv)
% Convert from CV to CV2 under the assumption of gamma-process.
%
%
% 

k = 1./cv.^2;
cv2=4.^(-k+1).*gamma(2*k)./gamma(k).^2./k;