function all_words = FilesIntheDir(input_string)
% USAGE:  FilesIntheDir(directory,input_string)
%
%
%
%
%

remainder = input_string;
all_words = '';

while (any(remainder))
  [chopped,remainder] = strtok(remainder);
  all_words = strvcat(all_words,chopped);
end

      