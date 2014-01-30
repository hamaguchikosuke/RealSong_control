function out=mysubplot(M,N,i,varargin)
% subplot more widely. It does not care even axes are overlapped.
% subplot(M,N,i) plots  
% subplot(M,N,i,j) plots  
%  
%              j 
%            (1,2) (1,2) (1,3) 
%         i  (2,1) (2,2) (2,3)   [MxN] plot.
%              |
% ex)      mysubplot(2,3,2,1)
% ex) subplot(M,N,i,j,[w,h])
% [w,h] is the relative width and height of the axes.
% default is [w,h]=[.98,0.98]; 
% by K.H.

  
if nargin>=4,    j = varargin{1};
else [i,j] = ind2sub([M,N],i);
end

if nargin>=5
  wh= varargin{2};
  aw = wh(1); ah = wh(2);
else
  aw = 0.98; ah = 0.98;
end


if (M==1)&&(N==1)
    dw=  .1;
    dh=  .1; 
    Lw = 1-2*dw;
    Lh = 1-2*dh;
    w = aw*Lw/N;
    h = ah*Lh/M;
    aw=0.8; ah=0.8;
elseif (N==1)
    dw=  .1;
    dh=  .05;
    Lw = 1-2*dw;
    Lh = 1-2*dh;
    w = aw*Lw/N;
    h = ah*Lh/M;
else
    dw = .1;
    dh = .05;
    Lw = 1-2*dw;
    Lh = 1-2*dh;
    w = aw*Lw/N;
    h = ah*Lh/M;
end

axes('position',[dw+(j-1)*Lw/N,dh+(M-i)*Lh/M,w,h]);
out=gca;