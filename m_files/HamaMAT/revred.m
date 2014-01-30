function g = revred(m)
%revblue   Linear blue-scale color map from white to blue.
%   revblue(M) returns an M-by-3 matrix containing a gray-scale colormap.
%   revblue, by itself, is the same length as the current figure's
%   colormap. If no figure exists, MATLAB creates one.
%
%   For example, to reset the colormap of the current figure:
%
%             colormap(revblue)
%
%   See also HSV, HOT, COOL, BONE, COPPER, PINK, FLAG, 
%   COLORMAP, RGBPLOT.
%   Modified from gray.m by KH
% 
%   Copyright 1984-2004 The MathWorks, Inc.
%   $Revision: 5.7.4.2 $  $Date: 2005/06/21 19:30:29 $

if nargin < 1, m = size(get(gcf,'colormap'),1); end
g = (m-1:-1:0)'/max(m-1,1);
g=g.^(1/2);
g = [ones(m,1),g,g];
