function xind=find_NOTnan_region(x)
% find index of not NaN region within input x.
% usage: xind = find_NOTnan_region(x);
% xind{:} are a cell, xind{1} are the first continuous not NaN region.  
% ex) 
% x = [1:100]; x(1:10)=NaN; x(30:40)=NaN; x(50:55)=NaN; %x(90:100)=NaN;
% y = randn(1,length(x));
% xind = find_NOTnan_region(x);
% for ii=1:length(xind)
%  plot(x(xind{ii}),y(xind{ii}));hold on;
% end

ii = 1;
x_now = 1;
x_end=1;

% remove nan region 
xind = [];
 while x_end<length(x)
    x_start= find(~isnan(x(x_now:end)),1,'first');
    if isempty(x_start), break;end
    x_start = x_now+x_start-1;
    x_end =  find(isnan(x(x_start:end)),1,'first')-1;
   
    if isempty(x_end) % Reaching end of x.
        xind{ii} = [x_start:length(x)];
    else
        xind{ii} = [x_start:x_start+x_end-1];
    end
    x_now = xind{ii}(end)+1;
        ii=ii+1;
 end