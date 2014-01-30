function [out,nind] = cvcalc(varargin)
% Usage: [cv,nind]=cvcalc(isi) 
% isi can be a stcuct, or object with ISIs.
% nind is the number of isis in that data.
% by K.H.

out = zeros(nargin,1);
for i=1:nargin

if isempty(varargin{i})
    out(i)=NaN;
    nind(i) = 0;
else
    mean_varargin = mean(varargin{i},2);
    var_varargin  = var(varargin{i},1,2);
    out(i) = sqrt(var_varargin)./mean_varargin;
    nind(i) = length(varargin{i});
end
end
