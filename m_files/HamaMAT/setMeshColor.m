function out = setMeshColor(cgcf,MeshColor,varargin)
% set all the axis same in all the figures in the current figure.
% Usage: setSameAxis(gcf,opt)
% opt: 'ZLim' set the z-axis of all the figures same.
%    : 'CLim' set the color range of all the figures same.
%
% ex) setSameAxis(figure(2),'CLim')
% By default, the span of an axis is 
% defined as (min,max).
% by K.H. 2004.Feb.16.

Children = get(cgcf,'Children');
GChildren = get(Children,'Children');
NumSubFig = size(GChildren,1);
NumMesh = size(cell2mat(GChildren(1)),1);
GChildrenM = reshape(cell2mat(GChildren),NumSubFig,NumMesh);
GChildrenM = GChildrenM(end:-1:1,:);

for i = 1:NumMesh
  set(GChildrenM(i,:),'EdgeColor',MeshColor(i,:));
end
