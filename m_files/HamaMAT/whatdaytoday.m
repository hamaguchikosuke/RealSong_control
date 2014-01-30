function out = whatdaytoday(varargin)
%
% it returns the day in the format [DayMonthYear].
% ex) when today is 2003/08/20, then the output is 20Aug2003.
% 
% or you can specify the date 
% Usage: whatdaytoday 
%      : whatdaytoday(y,m,d)
%  by K.H. 20Aug2003.

if nargin == 3
  y = varargin{1};
  m = varargin{2};
  d = varargin{3};
else
  [y,m,d] = datevec(now);   
end

m = datestr(datenum(datevec(now)),3);
today = [num2str(d),m,num2str(y)];
out = today;