function out = rescaleImage(C,X)
%
%
%
%X = [0,1,10,100];
NewC = length(X)*ones(size(C));

for i=1:length(X)
    ind= find(C<=X(i));
    NewC(ind) = NewC(ind)-1;
end

out = NewC;