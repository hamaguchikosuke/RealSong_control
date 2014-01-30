function varargout = PrmSps(opt,varargin)
%
% Parameter Space: This m-file sets retains, and provides global parameters. 
% Since it is better not to use global variable, we use this function.
% Usage:
% PrmSps('set','variable_name1',value1,'variable_name2',value2);
% PrmSps('get','variable_name1','variable_name2');
% by K.H. 2004.4.16


persistent A B C
switch(opt)
 case 'init'
  
  A = 1;
  B = 2;
  
  feval(mfilename,'init_dependVal')
 
 case 'init_dependVal'
  
  assignin('caller','C',ones(2)*B);
  
%  C = A*ones(2)*B;
  
 case 'set'
  
  for i = 1:(nargin-1)/2
    a = varargin{2*i-1};
    b = varargin{2*i};
    eval([a,'=',num2str(b)])
  end
  
  % Here, you should re-set variables which depends on other
  % variables %%
  C = A*ones(2)*B;
   
 case 'get'
  if nargin >=2
    for i =1:nargin-1
    varargout{i} = eval(varargin{i});
    end
  else
  error(['you should specity the parameter name'])    
  end
  

 otherwise
  error(['unknown option:',opt])
end
