function out = stackedhist(data,mu)
% Usage: stackedhist(data,sep)
% mu = [1 30;31 50];
% plot histgram of staked.
% n is the separated data.

[n m] = size(mu);
min_data = min(min(data));
max_data = max(max(data));
bin_number = 20;
data_histgram= zeros(n,bin_number);

for i = 1:n
 number =  mu(i,1):mu(i,2);
 data_tmp = data(number);
 edges = full(linspace(min_data,max_data,bin_number));
 data_histgram(i,:) =  histc(full(data_tmp),edges)
end

out = data_histgram;

sum(data_histgram,2)
bar(data_histgram',1)
legend('1','2','3')