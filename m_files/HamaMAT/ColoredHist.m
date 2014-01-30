function out = ColoredHist(data,mu,varargin)
% Usage: stackedhist(data,sep)
% mu = [1 30;31 50];
% plot histgram of staked.
% n is the separated data.

if nargin>=3
  range = varargin{1};
else
  min_data = min(min(data));
  max_data = max(max(data));
  range = [min_data, max_data];
end
[n m] = size(mu);
bin_number = 20;  
data_histgram= zeros(n,bin_number);
hist(data(1,:),bin_number);
%xtick = get(gca,'Xtick');
%xticklabel = get(gca,'XtickLabel');

for i = 1:n
 number =  mu(i,1):mu(i,2);
 data_tmp = data(number);
 edges = full(linspace(range(1),range(2),bin_number));
 data_histgram(i,:) =  histc(full(data_tmp),edges);
end

out = data_histgram;
sum(data_histgram,2);
bar(data_histgram',1);
legend('sin','-sin')

xtick = linspace(0,bin_number,3);
%xticklabel = strvcat('0','1/2gmax','gmax');
xticklabel = linspace(range(1),range(2),3);
set(gca,'Xtick',xtick);
set(gca,'XtickLabel',xticklabel);
  