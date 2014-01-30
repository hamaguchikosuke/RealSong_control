function   xin=running_windows3(x,window_size, step_size,varargin)
% Divide a vector into a matrix where each column represents a sliding window of the vector. 
% xin=running_windows3(x,window_size, step_size);
% This function receives a vector of data and returns a matrix of
% #step x (window_size). Data is either column or row vector,
% but in the returned matrix, each column is the one continuous section.
% The step size between the windows is step_size.
% 
% To save memory, it can returns a portion of the window.
% xin=running_windows3(x,window_size, step_size, Position_of_DiviedMatrix,NumofDivision)
% Position_of_DiviedMatrix: a number from 1 to NumofDivision.
% NumofDivision:  Divide the sliding window into NumofDivision sections, 
% and returns 
% 
% ex) NumofDivision=3, Position_of_DividedWindow=2
% 
% Position of DivividedWindow         (1)    (2)   (3)
% matrix    ||||||||||||||||        |||||| |||||| ||||
%           ||||||||||||||||        |||||| |||||| ||||
%           ||||||||||||||||    ==> |||||| |||||| |||| 
%           ||||||||||||||||        |||||| |||||| ||||
%           ||||||||||||||||        |||||| |||||| ||||
%                                          ^^^^^^   
%                                          return 
%                                          this.

% It can returns the assigned columns of the window.
% xin=running_windows3(x,window_size, step_size, index)
% index: a vector of index ranges from 1 to Nsteps
% and returns 
% 
% ex) index=[6:10]
% 
% Position of DivividedWindow         (1)    (2)   (3)
% matrix    ||||||||||||||||        |||||| |||||| ||||
%           ||||||||||||||||        |||||| |||||| ||||
%           ||||||||||||||||    ==> |||||| |||||| |||| 
%           ||||||||||||||||        |||||| |||||| ||||
%           ||||||||||||||||        |||||| |||||| ||||
%                                          ^^^^^^   
%                                          return 
%                                          this.
% 
% 
%        Written by KH         20100905

if ~isvector(x)
    error('x must be a vector');
end

if nargin==5
    Position_of_DiviedMatrix=varargin{1};
    NumofDivision=varargin{2};
    return_index=0;
elseif nargin==4
    return_index=varargin{1};
%         error('xin=running_windows3(x,window_size, step_size, Position_of_DiviedMatrix,NumofDivision) must have four inputs!')
elseif nargin==3
    Position_of_DiviedMatrix=1;
    NumofDivision=1;
    return_index=0;
end
    
x=x(:); % make it a column vector.
T=length(x);

Nsteps=1+fix((T-window_size)/(step_size));


if return_index==0
    % window to be returned
    window_index=0:(Nsteps-1);
    
    % index=1:Nsteps;
    index_div=ceil(Nsteps/NumofDivision);
    index=(1:index_div)+(Position_of_DiviedMatrix-1)*index_div;
    if max(index)>Nsteps
        index=index(1):Nsteps;
    end
    
    window_index=window_index(index);
else
    window_index=return_index-1;
end

if max(window_index)>Nsteps
    errtxt=sprintf('your requested window index is larger than Nsteps=%d!',Nsteps)
    error(errtxt);
end
%
% Pre-process X
%
colindex = 1 + window_index*(step_size);
rowindex = (1:window_size)';
% xin = zeros(window_size,Nsteps);

% Put x into columns of xin with the proper offset
xin = x(rowindex(:,ones(1,length(window_index)))+colindex(ones(window_size,1),:)-1);

