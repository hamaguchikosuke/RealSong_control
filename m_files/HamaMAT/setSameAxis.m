function out = setSameAxis(cgcf,opt,varargin)
% set all the axis same in all the figures in the current figure.
% Usage: setSameAxis(gcf,opt)
% opt: 'ZLim' set the z-axis of all the figures same.
%    : 'CLim' set the color range of all the figures same.
%
% ex) setSameAxis(figure(2),'CLim')
% By default, the span of an axis is 
% defined as (min,max).
% by K.H. 2004.Feb.16.



Children = get(cgcf,'Children');
Lims = cell2mat(get(Children,opt));
MinLim = min(Lims(:,1));
MaxLim = max(Lims(:,2));
if nargin >=3
  for i = 1:(nargin-2)/2
    a = varargin{2*i-1};
    b = varargin{2*i};
    eval([a,'=',num2str(b)])
  end
end


set(Children,opt,[MinLim, MaxLim]);
