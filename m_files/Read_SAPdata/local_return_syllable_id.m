function ind=local_return_syllable_id(s)

switch s
    case 'i'
        ind=1;
    case 'a'
        ind=2;
    case 'b'
        ind=3;
    case 'c'
        ind=4;
    case 'd'
        ind=5;
    case 'e'
        ind=6;
    case 'f'
        ind=7;
    case 'g'
        ind=8;
    case {'x','N'}
        ind=9;
    case '\n'
        ind=10;
%     case 'x'
%         ind=0;
    otherwise
        error('Unknown syllable label! (%s)',s);
end