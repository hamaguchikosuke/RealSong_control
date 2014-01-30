function x = sv_pol(sig, a, b, c, d)
%SV_DOT Basic template for the Dot Product 
%
%	X = SV_MULT(D, X1, X2, Y1, Y2) returns the scalar product of X1 and X2 
%	multiplied componentwise with the polarities of Y1 and Y2, which
%	is a vector (for five input arguments) 
%	or of X1'*X1 with Y1 componentwise (for three input arguments)
%	where D is the type of dot product used
%
%	exp(-sigma * |x - y|^2)
%
%	see also DISPLAY, SV_DOT, SV_MULT, SV_POL

% File:        @rbf_dot/sv_pol.m
%
% Author:      Alex J. Smola
% Created:     01/12/98
% Updated:     05/08/00
%
% This code is released under the GNU Public License
% Copyright by GMD FIRST and The Australian National University

if (nargin ~= 3) & (nargin ~= 5)
  error('wrong number of arguments');
elseif nargin == 3
  dot_a = sum(a.*a,1);
  unitvec = ones(size(a,2),1);
  x = a' * a;
  for i=1:size(a,2)
    x(:,i) = b(i) * (exp(sig * (2 * x(:,i) - dot_a' - dot_a(i) * ...
				    unitvec)) .* b);
  end
else
  dot_a = sum(a.*a,1);
  dot_b = sum(b.*b,1);
  unitvec = ones(size(a,2),1);
  x = a' * b;
  
  for i=1:size(b,2)
    x(:,i) = d(i) * (exp(sig * (2 * x(:,i) - dot_a' - dot_b(i) * ...
				    unitvec)) .* c);
  end
end;


 




