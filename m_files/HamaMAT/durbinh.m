function [dh, dhsig] = durbinh (dw, se2, n, h1)
%DURBINH Durbin h statistic and significance of the hypothesis of no serial correlation
%
% [DH, DHSIG] = DURBINH (DW, SE2, N, H1)
%
%  - computes the Durbin h statistic DH (a statistic of autocorrelation which is robust to
%    the inclusion of lagged dependent variables in the regression, see Durbin, 1970), and
%
%  - evaluates the associated null hypothesis of no serial correlation
%    * against the alternative of EITHER positive OR negative autocorrelation
%      if flag H1 is 1 (one-sided test), or
%    * against the alternative of ANY autocorrelation
%      if flag H1 is 2 (two-sided test, default),
%    and returns the level of significance DHSIG at which H0 is rejected.
%
% Required input arguments are
%
%  - the Durbin-Watson statistic DW, computed from the residuals of the associated
%    regression, using, for example, the author's DWATSON m-function,
%  - the est. standard error SE2 of the coefficient of the 1st lag in the regression, and
%  - the number of residuals N (= OBS - DLAGS - 1).
%
% If the MATLAB Statistics Toolbox is not installed, DHSIG assumes NaN. If N*SE2^2 >= 1,
% the Durbin h statistic cannot be calculated, and so both DH and DHSIG assume NaN.
%
%    The author assumes no responsibility for errors or damage resulting from usage. All
%    rights reserved. Usage of the programme in applications and alterations of the code
%    should be referenced. This script may be redistributed if nothing has been added or
%    removed and nothing is charged. Positive or negative feedback would be appreciated.

%                     Copyright (c) 17 March 1998 by Ludwig Kanzler
%                     Department of Economics, University of Oxford
%                     Postal: Christ Church,  Oxford OX1 1DP,  U.K.
%                     E-mail: ludwig.kanzler@economics.oxford.ac.uk
%                     Homepage:      http://users.ox.ac.uk/~econlrk
%                     $ Revision: 1.11 $$ Date: 15 September 1998 $

if nargin == 3
   h1 = 2;
end

dh = (1-dw/2) * sqrt(n/(1-n*se2^2));

if isreal(dh)
   if h1 == 1 & exist('normcdf.m','file')
      dhsig = 1-normcdf(dh,0,1);
   elseif exist('normcdf.m','file') & nargout == 2
      dhsig = min(normcdf(dh,0,1), 1-normcdf(dh,0,1))*2;
   elseif nargout == 2
      dhsig = NaN;
   end
else
   dh       = NaN;
   dhsig    = NaN;
end

% End of function.

% REFERENCE:
%
% Durbin, James (1970), "Testing for Serial Correlation in Least-Squares Regression When
%    Some of the Regressors are Lagged Dependent Variables", Econometrica, vol. 38, no. 3
%    (May), pp. 410-421
%
% SEE ALSO:
%
% Harvey, Andrew (1990), "The Econometric Analysis of Time Series", 2nd edition, MIT
%    Press, Cambridge, Massachusetts, pp. 275-277
%
% Judge, George, Carter Hill, William Griffiths, Helmut L�tkepohl & Tsoung-Chao Lee
%    (1988), "Introduction to the Theory and Practice of Econometrics", 2nd edition, John
%    Wiley & Sons, New York, p. 401

% End of file.