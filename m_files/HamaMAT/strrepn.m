function s1=strrepn(s1,s2,s3)
% replace s2 with s3 in a string s1.
% s2 can be a cell struct, such as {' ', '\', '{','}'}.
% this replaces white spaces, \, {} from s1.
%
% ex) 
% s1= 'this_is_a_{pen} and a {\} book.';
% s2 = {'_','\','{','}'};
% s3 = {''}; %to remove s2, s3 must be ''.
% s1 = strrepn(s1,s2,s3);
% % it returns, 'thisisapen and a  book.';

if ischar(s3)
   s3={s3};
end

if length(s3)==1
     s3index = ones(1,length(s2));
elseif length(s3)~=length(s2)
    error(['strrepn(s1,s2,s3): s3 must be one string, or must have same number of index as s2.'])
else
    s3index = [1:length(s2)];
end

for ii=1:length(s2)
    s1 = strrep(s1,s2{ii},s3{s3index(ii)});
end