function [Q,fcnt] = myquad(funfcn,a,b,tol,trace,varargin)
%QUAD   Numerically evaluate integral, adaptive Simpson quadrature.
%   Q = QUAD(FUN,A,B) tries to approximate the integral of function
%   FUN from A to B to within an error of 1.e-6 using recursive
%   adaptive Simpson quadrature.  The function Y = FUN(X) should
%   accept a vector argument X and return a vector result Y, the
%   integrand evaluated at each element of X.  
%
%   Q = QUAD(FUN,A,B,TOL) uses an absolute error tolerance of TOL 
%   instead of the default, which is 1.e-6.  Larger values of TOL
%   result in fewer function evaluations and faster computation,
%   but less accurate results.  The QUAD function in MATLAB 5.3 used
%   a less reliable algorithm and a default tolerance of 1.e-3.
%
%   [Q,FCNT] = QUAD(...) returns the number of function evaluations.
%
%   QUAD(FUN,A,B,TOL,TRACE) with non-zero TRACE shows the values
%   of [fcnt a b-a Q] during the recursion.
%
%   QUAD(FUN,A,B,TOL,TRACE,P1,P2,...) provides for additional 
%   arguments P1, P2, ... to be passed directly to function FUN,
%   FUN(X,P1,P2,...).  Pass empty matrices for TOL or TRACE to
%   use the default values.
%
%   Use array operators .*, ./ and .^ in the definition of FUN
%   so that it can be evaluated with a vector argument.
%
%   Function QUADL may be more efficient with high accuracies
%   and smooth integrands.
%
%   Example:
%       FUN can be specified as:
%
%       An inline object:
%          F = inline('1./(x.^3-2*x-5)');
%          Q = quad(F,0,2);
%
%       A function handle:
%          Q = quad(@myfun,0,2);
%          where myfun.m is an M-file:
%             function y = myfun(x)
%             y = 1./(x.^3-2*x-5);
%
%   See also QUADL, DBLQUAD, TRIPLEQUAD, INLINE, @.

%   Based on "adaptsim" by Walter Gander.  
%   Ref: W. Gander and W. Gautschi, "Adaptive Quadrature Revisited", 1998.
%   http://www.inf.ethz.ch/personal/gander
%   Copyright 1984-2002 The MathWorks, Inc. 
%   $Revision: 5.26 $  $Date: 2002/04/08 20:26:50 $

f = fcnchk(funfcn);
if nargin < 4 | isempty(tol), tol = 1.e-6; end;
if nargin < 5 | isempty(trace), trace = 0; end;

% Initialize with three unequal subintervals.
h = 0.13579*(b-a);
x = [a a+h a+2*h (a+b)/2 b-2*h b-h b];
y = feval(f, x, varargin{:});
fcnt = 7;

% Fudge endpoints to avoid infinities.
if ~isfinite(y(1))
   y(1) = feval(f,a+eps*(b-a),varargin{:});
   fcnt = fcnt+1;
end
if ~isfinite(y(7))
   y(7) = feval(f,b-eps*(b-a),varargin{:});
   fcnt = fcnt+1;
end

% Call the recursive core integrator.
hmin = eps/1024*abs(b-a);
[Q(1),fcnt,warn(1)] = ...
   myquadstep(f,x(1),x(3),y(1),y(2),y(3),tol,trace,fcnt,hmin,varargin{:});
[Q(2),fcnt,warn(2)] = ...
   myquadstep(f,x(3),x(5),y(3),y(4),y(5),tol,trace,fcnt,hmin,varargin{:});
[Q(3),fcnt,warn(3)] = ...
   myquadstep(f,x(5),x(7),y(5),y(6),y(7),tol,trace,fcnt,hmin,varargin{:});
Q = sum(Q);
warn = max(warn);

switch warn
   case 1
      warning('MATLAB:quad:MinStepSize', ...
          'Minimum step size reached; singularity possible.')
   case 2
      warning('MATLAB:quad:MaxFcnCount', ...
          'Maximum function count exceeded; singularity likely.')
   case 3
      warning('MATLAB:quad:ImproperFcnValue', ...
          'Infinite or Not-a-Number function value encountered.')
   otherwise
      % No warning.
end

% ------------------------------------------------------------------------

