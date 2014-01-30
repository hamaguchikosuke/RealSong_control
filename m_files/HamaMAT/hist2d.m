function [out,varargout] = hist2d(X,Y,varargin)
% calculate and show the 2-dimensional histgram.
% Usage: N = hist2d( X , Y );
%                   1xd 1xd
% USAGE: N = hist2d(X,Y,dX,dY); X,Y is a vector. N is the matrix. 
% dX and dY is the edges to divide values. Usually made by dX = linspace(0,1,100+1);
% X,Y need not be within the range of dX,dY.
% dX dY can be number of grids.
% ex) X = randn(100,100); Y = randn(100,100);
%    N1 = hist2d(X,Y);
%    N2 = hist2d(X,Y,linspace(-2,2,20),linspace(-2,2,20));
%    N3 = hist2d(X,Y,100,100);
%    [N,gridX,gridY]= hist2d(X,Y);
% by K.H. 2006

if nargin == 2
  xngrid = 100; yngrid = 100;
  opt ='makedxdy';
end

if nargin == 4 % dX and dY are given.
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
    N(Ydata(i),Xdata(i)) =   N(Ydata(i),Xdata(i)) +1;
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
