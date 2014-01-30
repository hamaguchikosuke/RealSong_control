function out = CirculationMat(v,varargin)
%
% output circulation matrix from vector v.
% ex) [a b c d e f]=>
%
%     [a b c d e f;
%      f a b c d e;
%      e f a b c d;
%      d e f a b c;
%      c d e f a b;
%      b c d e f a]
% You can specify the row number, or the direction of circulation.
% Usage:  CirculationMat(v,varargin) or   CirculationMat(v,n,'right')  
% n: the number of row; 'right' is the direction of circulation. 
% default and upper example is 'right';
% by K.H. 11.Nov.2002

if nargin>=2
  n = varargin{1};
else
  n = length(v)
end

if nargin>=3
  direction = varargin{2};
else
  direction = 'right';
end



switch  direction 
 case  'right'
  rev_number = [1,[length(v):-1:length(v)-n+2]]
  row_vec = v(rev_number);
  out = toeplitz(row_vec,v);
 case 'left'
  v = v(end:-1:1);
  rev_number = [1,[length(v):-1:length(v)-n+2]]
  row_vec = v(rev_number);
  out = toeplitz(row_vec,v);
  out = out(:,end:-1:1);
end




