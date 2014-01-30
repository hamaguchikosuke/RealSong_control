function [out,varargout] = hist2d_r(X,Y,R,varargin)
% calculate and show the 2-dimensional histgram of value R(x(t),y(t)).
% R draws a trajectory, and we calculate the accumulated histrgam of R.
% Usage: N = hist2d( X , Y , R);
%                   1xd 1xd 1xd
% USAGE: N = hist2d(X,Y,R,dX,dY); X,Y is a vector. N is the matrix. 
% dX and dY is the edges to divide values. Usually made by dX = linspace(0,1,100+1);
% X,Y need not be within the range of dX,dY.
% dX dY can be number of grids.
% ex) X = randn(100,100); Y = randn(100,100); R = rand(100,100);
%    N1 = hist2d_r(X,Y,R);
%    N2 = hist2d_r(X,Y,R,linspace(-2,2,20),linspace(-2,2,20));
%    N3 = hist2d_r(X,Y,R,100,100);
%    [N,gridX,gridY]= hist2d(X,Y,R);
% by K.H. 2007.07.20

if nargin == 3
  xngrid = 100; yngrid = 100;
  opt ='makedxdy';
end

if nargin == 5 % dX and dY are given.
  dX = varargin{1};
  dY = varargin{2};

  if isempty(dX)
    xngrid = 100;    opt = 'makedxdy';
  elseif prod(size(dX)) == 1
    xngrid = dX;    opt = 'makedxdy';
  else
    xngrid = length(dX); opt = 'donothing';
  end
 
  if isempty(dY)
    yngrid = 100;    opt = 'makedxdy';
  elseif prod(size(dY)) == 1
    yngrid = dY;     opt = 'makedxdy';
  else
    yngrid = length(dY); opt = 'donothing';
  end
  N = zeros(xngrid+1,yngrid+1)';
end

if prod(size(X)-1)>0 % If it is Matrix 
  X = reshape(X,1,prod(size(X)));
end

if prod(size(Y)-1)>0 % If it is Matrix 
  Y = reshape(Y,1,prod(size(Y)));
end


if prod(size(R)-1)>0 % If it is Matrix 
  R = reshape(R,1,prod(size(R)));
end


switch opt
 case 'makedxdy'
  dX = linspace(min(X),max(X),xngrid+1);
  dY = linspace(min(Y),max(Y),yngrid+1);
  N = zeros(xngrid+1,yngrid+1)';  
end

if length(X) ~= length(Y)
  error(['X and Y must be the same length vector'])
end

Xtick = dX(2)-dX(1);
Ytick = dY(2)-dY(1);

X = X-dX(1); % to 
Y = Y-dY(1); %

Xdata = floor(X/Xtick)+1; % Position of the matrix.
Ydata = floor(Y/Ytick)+1;

for i = 1:length(X)
  if Xdata(i) > 0 && Ydata(i) > 0 && Xdata(i) <= xngrid+1 && Ydata(i) <= yngrid+1
    N(Ydata(i),Xdata(i)) =   N(Ydata(i),Xdata(i)) +R(i);
%  else
%    [Xdata(i),Ydata(i)]
  end
end

N(:,end-1) = N(:,end-1) + N(:,end); % sum the values on the right(X) edge
N(end-1,:) = N(end-1,:) + N(end,:); % sum the values on the upper(Y) edge
N = N([1:end-1],[1:end-1]);

out = N;

%[DX DY] = meshgrid(dX,dY);
%mesh(DX,DY,N);

varargout{1} = dX(1:end-1);
varargout{2} = dY(1:end-1);
