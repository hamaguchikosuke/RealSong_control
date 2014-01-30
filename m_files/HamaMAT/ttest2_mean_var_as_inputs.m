function [h,p,ci,stats] = ttest2_mean_var_as_inputs(mean_x,n_sample_x,var_x,mean_y,n_sample_y,var_y,alpha,tail,vartype,dim)
% [h,p,ci,stats] = ttest2_mean_var_as_inputs(mean_x,n_sample_x,var_x,mean_y,n_sample_y,var_y,alpha,tail,vartype,dim)
% 
% H = ttest2_mean_var_as_inputs(Mean_X,n_sample_X,Var_X,Mean_Y,n_sample_Y,Var_Y) 
%   performs a T-test of the hypothesis that twoindependent samples, 
%   with equal means, and returns the result of the test in H.


% ttest2_mean_var_as_inputs Two-sample T-test with pooled or unpooled variance estimate.
%   H = ttest2_mean_var_as_inputs(X,Y) performs a T-test of the hypothesis that two
%   independent samples, in the vectors X and Y, come from distributions
%   with equal means, and returns the result of the test in H.  H=0
%   indicates that the null hypothesis ("means are equal") cannot be
%   rejected at the 5% significance level.  H=1 indicates that the null
%   hypothesis can be rejected at the 5% level.  The data are assumed to
%   come from normal distributions with unknown, but equal, variances.  X
%   and Y can have different lengths.
%
%   X and Y can also be matrices or N-D arrays.  For matrices, ttest2_mean_var_as_inputs
%   performs separate T-tests along each column, and returns a vector of
%   results.  X and Y must have the same number of columns.  For N-D
%   arrays, ttest2_mean_var_as_inputs works along the first non-singleton dimension.  X and Y
%   must have the same size along all the remaining dimensions.
%
%   ttest2_mean_var_as_inputs treats NaNs as missing values, and ignores them.
%
%   H = ttest2_mean_var_as_inputs(X,Y,ALPHA) performs the test at the significance level
%   (100*ALPHA)%.  ALPHA must be a scalar.
%
%   H = ttest2_mean_var_as_inputs(X,Y,ALPHA,TAIL) performs the test against the alternative
%   hypothesis specified by TAIL:
%       'both'  -- "means are not equal" (two-tailed test)
%       'right' -- "mean of X is greater than mean of Y" (right-tailed test)
%       'left'  -- "mean of X is less than mean of Y" (left-tailed test)
%   TAIL must be a single string.
%
%   H = ttest2_mean_var_as_inputs(X,Y,ALPHA,TAIL,VARTYPE) allows you to specify the type of
%   test.  When VARTYPE is 'equal', ttest2_mean_var_as_inputs performs the default test
%   assuming equal variances.  When VARTYPE is 'unequal', ttest2_mean_var_as_inputs performs
%   the test assuming that the two samples come from normal distributions
%   with unknown and unequal variances.  This is known as the Behrens-Fisher
%   problem. ttest2_mean_var_as_inputs uses Satterthwaite's approximation for the effective
%   degrees of freedom.  VARTYPE must be a single string.
%
%   [H,P] = ttest2_mean_var_as_inputs(...) returns the p-value, i.e., the probability of
%   observing the given result, or one more extreme, by chance if the null
%   hypothesis is true.  Small values of P cast doubt on the validity of
%   the null hypothesis.
%
%   [H,P,CI] = ttest2_mean_var_as_inputs(...) returns a 100*(1-ALPHA)% confidence interval for
%   the true difference of population means.
%
%   [H,P,CI,STATS] = ttest2_mean_var_as_inputs(...) returns a structure with the following fields:
%      'tstat' -- the value of the test statistic
%      'df'    -- the degrees of freedom of the test
%      'sd'    -- the pooled estimate of the population standard deviation
%                 (for the equal variance case) or a vector containing the
%                 unpooled estimates of the population standard deviations
%                 (for the unequal variance case)
%
%   [...] = ttest2_mean_var_as_inputs(X,Y,ALPHA,TAIL,VARTYPE,DIM) works along dimension DIM of
%   X and Y.  Pass in [] to use default values for ALPHA, TAIL, or VARTYPE.
%
%   See also TTEST, RANKSUM, VARTEST2, ANSARIBRADLEY.

%   References:
%      [1] E. Kreyszig, "Introductory Mathematical Statistics",
%      John Wiley, 1970, section 13.4. (Table 13.4.1 on page 210)

%   Copyright 1993-2006 The MathWorks, Inc.
%   $Revision: 2.15.4.9 $  $Date: 2006/06/20 20:51:53 $

if nargin < 6
    error('stats:ttest2_mean_var_as_inputs:TooFewInputs','Requires at least two input arguments');
end

if nargin < 7 || isempty(alpha)
    alpha = 0.05;
elseif ~isscalar(alpha) || alpha <= 0 || alpha >= 1
    error('stats:ttest2_mean_var_as_inputs:BadAlpha','ALPHA must be a scalar between 0 and 1.');
end

if nargin < 8 || isempty(tail)
    tail = 0;
elseif ischar(tail) && (size(tail,1)==1)
    tail = find(strncmpi(tail,{'left','both','right'},length(tail))) - 2;
end
if ~isscalar(tail) || ~isnumeric(tail)
    error('stats:ttest2_mean_var_as_inputs:BadTail', ...
          'TAIL must be one of the strings ''both'', ''right'', or ''left''.');
end

if nargin < 9 || isempty(vartype)
    vartype = 1;
elseif ischar(vartype) && (size(vartype,1)==1)
    vartype = find(strncmpi(vartype,{'equal','unequal'},length(vartype)));
end
if ~isscalar(vartype) || ~isnumeric(vartype)
    error('stats:ttest2_mean_var_as_inputs:BadVarType', ...
          'VARTYPE must be one of the strings ''equal'' or ''unequal''.');
end


nx=sum(n_samples_x);
ny=sum(n_samples_y);

s2x = sum(var_x.*n_samples_x)/nx
s2y = sum(var_y.*n_samples_y)/ny;
difference = sum(mean_x.*samples_x)/nx -sum(mean_y.*samples_y)/ny;



if vartype == 1 % equal variances
    dfe = nx + ny - 2;
    sPooled = sqrt(((nx-1) .* s2x + (ny-1) .* s2y) ./ dfe);
    se = sPooled .* sqrt(1./nx + 1./ny);
    ratio = difference ./ se;

    if (nargout>3)
        stats = struct('tstat', ratio, 'df', cast(dfe,class(ratio)), ...
                       'sd', sPooled);
        if isscalar(dfe) && ~isscalar(ratio)
            stats.df = repmat(stats.df,size(ratio));
        end
    end
elseif vartype == 2 % unequal variances
    s2xbar = s2x ./ nx;
    s2ybar = s2y ./ ny;
    dfe = (s2xbar + s2ybar) .^2 ./ (s2xbar.^2 ./ (nx-1) + s2ybar.^2 ./ (ny-1));
    se = sqrt(s2xbar + s2ybar);
    ratio = difference ./ se;

    if (nargout>3)
        stats = struct('tstat', ratio, 'df', cast(dfe,class(ratio)), ...
                       'sd', sqrt(cat(dim, s2x, s2y)));
        if isscalar(dfe) && ~isscalar(ratio)
            stats.df = repmat(stats.df,size(ratio));
        end
    end
    
    % Satterthwaite's approximation breaks down when both samples have zero
    % variance, so we may have gotten a NaN dfe.  But if the difference in
    % means is non-zero, the hypothesis test can still reasonable results,
    % that don't depend on the dfe, so give dfe a dummy value.  If difference
    % in means is zero, the hypothesis test returns NaN.  The CI can be
    % computed ok in either case.
    if se == 0, dfe = 1; end
else
    error('stats:ttest2_mean_var_as_inputs:BadVarType',...
          'VARTYPE must be ''equal'' or ''unequal'', or 1 or 2.');
end

% Compute the correct p-value for the test, and confidence intervals
% if requested.
if tail == 0 % two-tailed test
    p = 2 * tcdf(-abs(ratio),dfe);
    if nargout > 2
        spread = tinv(1 - alpha ./ 2, dfe) .* se;
        ci = cat(dim, difference-spread, difference+spread);
    end
elseif tail == 1 % right one-tailed test
    p = tcdf(-ratio,dfe);
    if nargout > 2
        spread = tinv(1 - alpha, dfe) .* se;
        ci = cat(dim, difference-spread, Inf(size(p)));
    end
elseif tail == -1 % left one-tailed test
    p = tcdf(ratio,dfe);
    if nargout > 2
        spread = tinv(1 - alpha, dfe) .* se;
        ci = cat(dim, -Inf(size(p)), difference+spread);
    end
else
    error('stats:ttest2_mean_var_as_inputs:BadTail',...
          'TAIL must be ''both'', ''right'', or ''left'', or 0, 1, or -1.');
end

% Determine if the actual significance exceeds the desired significance
h = cast(p <= alpha, class(p));
h(isnan(p)) = NaN; % p==NaN => neither <= alpha nor > alpha
