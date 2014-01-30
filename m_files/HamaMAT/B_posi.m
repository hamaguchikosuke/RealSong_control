function out = B_posi(opt,A,x_region,y_region,varargin);
% usage: B_posi(A,x_region,y_region);
%     P _____1______ Q (maxX,maxY)
%      | \ | /      |
%      2-  A  ----- 3
%      |_/_|_\__4___| <- search B on the boundary.
%     S              R
% (minX,minY)    
% 
% by KH 2005.02.20

Ax = A(1); Ay = A(2);
maxX = max(x_region);minX = min(x_region);
maxY = max(y_region);minY = min(y_region);
if Ax > maxX || Ax < minX || Ay > maxY || Ay < minY
  error('A must be within the region');
end
%---- number of grid on one vertices. ------
if nargin>=5
    space_digit = varargin{1};
else
    space_digit = 11;
end

switch opt
 case 'space'
  PQ = [linspace(minX,maxX,space_digit);maxY*ones(1,space_digit)];
  QR = [maxX*ones(1,space_digit);linspace(maxY,minY,space_digit)];
  RS = [linspace(maxX,minX,space_digit);minY*ones(1,space_digit)];
  SP = [minX*ones(1,space_digit);linspace(minY,maxY,space_digit)];
  out = [PQ,QR(:,2:end),RS(:,2:end),SP(:,2:end-1)];
  
 case 'theta'
  theta_digit = space_digit; 
  P= [minX,maxY];Q= [maxX,maxY];R= [maxX,minY];S= [minX,minY];
  Ptheta = atan((maxY-Ay)/(minX-Ax))+pi;
  Qtheta = atan((maxY-Ay)/(maxX-Ax));
  Rtheta = atan((minY-Ay)/(maxX-Ax));
  Stheta = atan((minY-Ay)/(minX-Ax))-pi;
  
  theta = linspace(-pi/2,pi/2,theta_digit); theta = theta(1:end-1);
  Bx = zeros(1,theta_digit*2);By = zeros(1,theta_digit*2);
  
  Bx(1) = Ax; Bx(theta_digit+1) = Ax;
  By(1) = maxY; By(theta_digit+1) = minY;
  for i = 2:theta_digit-1
    % search 1-border 
    Bx_tmp = Ax+(maxY-Ay)/tan(theta(i))
    if Bx_tmp< max(x_region) && Bx_tmp > min(x_region)
      Bx(i) = Bx_tmp;
      By(i) = maxY;
    else % 
      Bx(i) = maxX;
      By(i) = tan(theta(i))*(maxX-Ax)+Ay;
    end
    % opposite site on 3-border
    Bx_tmp = Ax+(minY-Ay)/tan(theta(i))
    if Bx_tmp< max(x_region) && Bx_tmp > min(x_region)
      Bx(theta_digit+i) = Bx_tmp;
      By(theta_digit+i) = minY;
    else % 
      Bx(theta_digit+i) = minX;
      By(theta_digit+i) = tan(theta(i))*(minX-Ax)+Ay;
    end
    
    % search 3-border
    Bx_tmp = Ax+(minY-Ay)/tan(theta(i))
    if Bx_tmp< max(x_region) && Bx_tmp > min(x_region)
      Bx(i) = Bx_tmp;
      By(i) = maxY;
    else % 
      Bx(i) = maxX;
      By(i) = tan(theta(i))*(maxX-Ax)+Ay;
    end
  end
 otherwise 
  error(['Unknown option']);
end

  