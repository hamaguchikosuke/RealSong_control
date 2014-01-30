function finish_sound(N)
% usage: finish_sound(N);% -> beep N times.
%      : finish_sound;   % -> beep twice  
% by KH.

if isempty(N)
    N = 2;
end
beep_sound = repmat([sin([0:800]),zeros(1,800)],1,N);
sound(beep_sound);