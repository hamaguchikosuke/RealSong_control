function [nu,nuext_grid,cv]=return_if_diffnu_less_than(dnucv,cnuext,known_nu,p,varargin)
% [nu,nuext_grid,cv]=return_if_diffnu_less_than(dnu,cnuext,known_nu,p)
% dnu is the target difference of the rate.
% nuext = [min_nuext,max_nuext] is the min and max of the input rate.
% known_nu = [NaN, NaN], or [nu1, NaN], or [NaN, nu2];
% p is the parameter of the model.
% % ex)
% dnu = 10;
% cnuext = [1,4];
% known_nu = [NaN,NaN];
% p.rinit = 100;
% p.tau=10; 
% p.tauref=2;
% p.J=.2; 
% p.Jext=p.J;
% p.Ce=1000; 
% p.g=7; 
% p.Vth=-55; 
% p.Vr=-65; 
% p.VL=-65;
% beta = 1/4;
% p.Ci = beta*p.Ce;
% p.Cnuext= [.5:.5:2];
% 
% [nu,nuext_grid,cv]=return_if_diffnu_less_than(dnu,cnuext,known_nu,p)
% by K.H. 20072120
% -----------------------------------------------------------------------
%                     Schematic procesure of this code.
% -----------------------------------------------------------------------
% Given input 
%      [nu0 nu1]  
%        :   :  (1.calculate output.)
%      [r0   r1]
%       / \     (2.if diff(r0,r1)>dnu, divide input space [nu0, (nu0+nu1)/2, nu1])
%      [r0 r0.5]
%       | (2.a if diff(r0,r0.5)>dnu, divide.)
%     /  \ 
%   [r0  r0.25] (2.b if diff(r0,r0.25)<dnu, stop and return the input&output rates.)
%   ........
%   then repeat the same process for,
%          [r 0.25 r0.5]
%          and 
%                 [r0.5   r1]
%
% 
%% 
vervose_mode = 0;
dcnuext_threshold = .005;
slfcnst_rate_func = 'slfcnstNwt_lif04_mex';
unknown_nu_ind=find(isnan(known_nu));

if prod(size(dnucv))==1
    dnu = dnucv(1);
    dcv = 2;
else
    dnu = dnucv(1);
    dcv = dnucv(2);
end

if nargin==5
    known_cv = varargin{1};
else
    known_cv = [NaN,NaN];
end
for ii=1:length(unknown_nu_ind)
   [known_nu(unknown_nu_ind(ii)),known_cv(unknown_nu_ind(ii))]= feval(slfcnst_rate_func,...
       p.rinit,... % initial input 
       p.tau,...
       p.tauref,...
       cnuext(unknown_nu_ind(ii)),...
       p.Jext,...
       p.J,...
       p.g,...
       p.Ce,...
       p.Ci,...
       p.Vth-p.VL,...
       p.Vr-p.VL,1);
end
%%
% If abs(r_left-r_right) is more than dnu, we divide the input space into
% two, and continue until two neighboring input rate have outputs closer than
% dnu, except for the case the input rate difference becomes too small
% (dnuext_threshold).
if (abs(diff(known_nu))>dnu ||...
        abs(diff(known_cv))>dcv) &&...
        (diff(cnuext)>dcnuext_threshold)
    % (divide): [r_left, r_right] ==>  [r_left, r_mid (unknown), r_right]
    if (vervose_mode), fprintf('<-- go deeper to left...[%3.3g-%3.3g]\n',cnuext(1),mean(cnuext));
    else fprintf('.');
    end;
    p.rinit = known_nu(1);
    
    % Calculate [r_left, r_mid (unknown)]
    [nutmp1,nuext_grid1,cvtmp1]=feval(mfilename,[dnu,dcv],[cnuext(1),mean(cnuext)],[known_nu(1),NaN],p,[known_cv(1),NaN]);
%     if abs(known_nu(2)-nutmp1(end))>dnu && (diff(cnuext)>dcnuext_threshold)
    if     ((abs(known_nu(2)-nutmp1(end))>dnu) || ...
            (abs(known_cv(2)-cvtmp1(end))>dcv)) && ...
            (diff(cnuext)>dcnuext_threshold)
        if (vervose_mode),fprintf('--> go deeper to right...[%3.3g-%3.3g]\n',mean(cnuext),cnuext(2));end
 % (divide): [r_mid, r_right] ==>  [r_mid, r_mid_r (unknown),r_right]
        [nutmp2,nuext_grid2,cvtmp2]=feval(mfilename,[dnu,dcv],[mean(cnuext),cnuext(2)],[nutmp1(end),known_nu(2)],p,[cvtmp1(end),known_cv(2)]);
    else
        if (vervose_mode),fprintf('! touch ground at right ...[%3.3g-%3.3g]\n',mean(cnuext),cnuext(2));end
        nutmp2 = [nutmp1(end),known_nu(2)];
        nuext_grid2 = [mean(cnuext),cnuext(2)];
        cvtmp2 = [cvtmp1(end),known_cv(2)];
    end
else
    if (vervose_mode),fprintf('! touch ground at left ...[%3.3g-%3.3g]\n',cnuext(1),cnuext(2));end
    nu = known_nu;
    nuext_grid = cnuext;
    cv = known_cv;
    return;
end
if (vervose_mode), fprintf('! reach ground...\n');end
nu = [nutmp1,nutmp2(2:end)];
nuext_grid = [nuext_grid1,nuext_grid2(2:end)];
cv = [cvtmp1,cvtmp2(2:end)];

%fprintf('\n');