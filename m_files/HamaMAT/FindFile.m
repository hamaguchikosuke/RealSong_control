function out = FindFile(keyword,varargin)
%
% returns the file names in the current directory which contains keywords.
% USAGE: FindFile(Keyword1,Keyword2,...)
% by K.H. 2003.Aug.31.

c = ['ls ',keyword];

if nargin >=2
  for i =1:nargin-1
    keyword2 = varargin{i};
    c = [c,'*',keyword2];
  end
  if ~strcmp(c(end-3:end),'.mat') 
    c = [c,'*'] % If the last word is ".mat", You don't need to add "*" at the end.
  end
end

eval(c);
%filenames =words(ans);
%filenames = ans
filenames = chopword(ans,keyword,varargin{nargin-1});

%if nargin >= 2
%  if strcmp(c(end-3:end),'.mat')% if use 'ls OOO*OO*O.mat'
%  filenames = chopword(filenames,keyword,varargin{nargin-1});
%  end
%end
out = filenames;
%a = ans;
%if any(isspace(a)) % That means it contains more than two lines in ans
%  out = words(ans);
%else
%  out = deblank(ans);
%end



function all_words = words(input_string)
remainder = input_string;
size(input_string);
all_words = '';

while (any(remainder))
  [chopped,remainder] = strtok(remainder)
  size(chopped)
  all_words = strvcat(all_words,chopped);
end

