function [out,nind] = cv2calc(varargin)
% Usage: [cv2,nind]=cv2calc(isi) 
% isi can be a stcuct, or object with ISIs.
% ISI_n = T_{n+1}-T{n}, where T_n is the n-th spike timing.
% cv2(n) = 2*|ISI_n+1-ISI_n|/(ISI_n+1 + ISI_n).
% nind is the number of isis in that data.
%     <==== CV2_{n} ====>
%       ISI_n    ISI_{n+1}
%     <-------> <------->
%  ___|________|_________|___
% T_{n}     T_{n+1}   T_{n+2}
% 
% by K.H. 2007.05.09

out = cell(nargin,1);
nind = zeros(nargin,1);
for i=1:nargin

if isempty(varargin{i})
    out{i}=NaN;
    nind(i) = 0;
else
    nind(i) = length(varargin{i});
    if nind(i)>=2
        dcv2 = abs(diff(varargin{i}));
        mcv2 = (varargin{i}(1:end-1)+varargin{i}(2:end))/2;
        out{i} = dcv2./mcv2;
    else
        out{i} = NaN;
    end
end
end

    