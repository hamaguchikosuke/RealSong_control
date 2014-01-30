function h=draw_rectangles(X,Y,dX,dY,varargin)
% Draw rectangles like below;
%            __
%           |  |
%    dX     |__|
%    __   (X(i+1),Y(i+1))
%   |  | }dY
%   |__|
%   (X(i),Y(i))
% ex)
% X = [1,4]; Y = [1,3];
% dX = 1;    dY = 1;
% draw_rectangles(X,Y,dX,dY)
% >> you can also specify the color of the lines.
% draw_rectangles(X,Y,dX,dY,'FaceColor','r')
% draw_rectangles(X,Y,dX,dY,'FaceAlpha',0,'LineStyle','-','EdgeColor','r');
% by KH. 20070720;


X=X(:)';
Y=Y(:)';
dX=dX(:)';
dY=dY(:)';

% sanity check
if length(X)~=length(Y) || length(X)~=length(dX) || length(X)~=length(dY) 
    error('Size of input X,Y,dX,dY must be the same');
end
Xg=[X;X+dX;X+dX;X];
Yg=[Y;Y;Y+dY;Y+dY];

% varargin{:}
    
h=patch(Xg,Yg,ones(size(Xg)),'r');
% get(h)
set(h,'FaceAlpha',1);
if nargin<5
set(h,'LineStyle','-','EdgeColor','r');
% plot3(X+dX/2,Y+dY/2,-ones(1,length(X)),'ko')
else
set(h,varargin{:});
end
