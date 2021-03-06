function [tpp, tppsig] = phillips (se2, t2, resid, rss, sigma, obs)
%PHILLIPS Phillips-Perron test of the unit-root hypothesis in a Dickey-Fuller regression
%
% [TPP, TPPSIG] = PHILLIPS (SE2, T2, RESID, RSS, SIGMA, OBS)
%
%    - computes the Phillips-Perron (Phillips, 1987, Phillips & Perron, 1988)
%      autocorrelation/heteroskedasticity corrected t-ratio TPP on the unit-root
%      coefficient in a Dickey-Fuller or an Augmented Dickey-Fuller (1979) regression, and
%
%    - evaluates its significance level TPPSIG,
%
%    using the following arguments from (A)DF the regression (which can be taken from the
%    output of the author's ADFREG m-function):
%
%    SE2   = the estimated standard errors of the unit-root coefficient
%    T2    = the corresponding t-ratio
%    RESID = the (row vector) of residuals
%    RSS   = the residual sum of squares
%    SIGMA = the estimated standard error of the residuals
%    OBS   = the number of observations of the regression
%
%    Usage: reject the null of a unit root, even in the presence of serial correlation
%           and/or heteroskedasticity, if tpp is statistically significant.
%
%    REQUIRES the author's DFCRIT m-function to compute TPPSIG.
%
% The author assumes no responsibility for errors or damage resulting from usage. All
% rights reserved. Usage of the programme in applications and alterations of the code
% should be referenced. This script may be redistributed if nothing has been added or
% removed and nothing is charged. Positive or negative feedback would be appreciated.

%                     Copyright (c) 6 April 1998  by Ludwig Kanzler
%                     Department of Economics, University of Oxford
%                     Postal: Christ Church,  Oxford OX1 1DP,  U.K.
%                     E-mail: ludwig.kanzler@economics.oxford.ac.uk
%                     Homepage:      http://users.ox.ac.uk/~econlrk
%                     $ Revision: 1.03 $$ Date: 15 September 1998 $

% First determine the number of autocovariances of the residuals to be used, using the
% "rule of thumb" proposed by Schwert, 1987 (see also Diebold & Nerlove, 1990):
covs = fix(4*(obs/100)^0.25);

% Then compute the Newey & West (1987) estimator accordingly:
nw = rss;
for j = 1 : covs
   nw = nw + 2*(1-j/(covs+1))*(resid(1:end-j)'*resid(j+1:end));
end
nw = nw/obs;

% Finally, "apply" the NW estimator and some of the above regression output to the
% original t-ratio, thus obtaining the Phillips-Perron statistic, which follows the
% tabulated Dickey-Fuller distribution, and obtain its statistical significance:
tpp = sqrt(rss/obs / nw) * t2 - 1/2* (nw - rss/obs)/sqrt(nw) * obs*se2/sigma;
if nargout == 2
   tppsig = dfcrit (tpp, obs);
end

% End of function.


% REFERENCES:
%
% Dickey, David & Wayne Fuller (1979), "Distribution of the Estimators for Autoregressive
%    Time Series With a Unit Root", Journal of the American Statistical Association, vol.
%    74, no. 366 (June), pp. 427-431
%
% Diebold, Francis & Marc Nerlove (1990), "Unit Roots in Economic Time Series: A
%    Selective Survey", in George Rhodes Jr. & Thomas Fomby, eds., "Advances in
%    Econometrics: A Research Annual", vol. 8 ("Co-integration, Spurious Regressions, and
%    Unit Roots"), JAI Press, Greenwich, Connecticut, pp. 3-69
%
% Newey, Whitney & Kenneth West (1987), "A Simple, Positive Semi-definite,
%    Heteroskedasticity and Autocorrelation Consistent Covariance Matrix", Econometrica,
%    vol. 55, no. 3 (May), pp. 703-708
%
% Phillips, Peter (1987), "Time Series Regression with a Unit Root", Econometrica, vol.
%    55, no. 2 (March), pp. 277-301
%
% Phillips, Peter & Pierre Perron (1988), "Testing for a Unit Root in Time Series
%    Regression", Biometrika, vol. 75, no. 2 (June), pp. 335-346
%
% Schwert, William (1989), "Tests for Unit Roots: A Monte Carlo Investigation”, Journal of
%    Business and Economic Statistics, vol. 7, no. 2 (April), pp. 147-159

% This implementation of the test follows the theoretical exposition in Hamilton, 1994,
% pp. 506-515, and Mills, 1993, pp. 54-55:
%
% Hamilton, James (1994), "Time Series Analysis", Princeton University Press, Princeton,
%    New Jersey
%
% Mills, Terence (1993), "The Econometric Modelling of Financial Time Series", Cambridge
%    University Press, Cambridge

% End of file.
