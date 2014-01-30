function [out1,out2] = OptionCheck(name,varargin)
%
%
%
%

if nargin>=2
  NAME = strmatch(char(name),varargin)
end

%strvcat(varargin)

if ~isempty(NAME)
  try
    out1 =varargin{NAME};
    out2 = varargin{NAME+1};
  catch 
    error(['no arguments in ',varargin{NAME}]) 
  end
  
end
	 

  