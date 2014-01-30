function phi = SortPhi(phi,varargin)
% sorted_phi = SortPhi(phi,opt) 
% opt: '1d'
% sort phi which is confined in a range[-pi pi] space into
% continuous like [-inf inf].
% opt: 'circ2pi'
% remove jump line by changing phi->NaN after jump.
% default is '1d'.
% phi can be a vector or matrix which row is one trial.
% by K.H. 
if nargin>=2
    opt = varargin{1};
else
    opt = '1d';
end

%--- Sanity Check 
%4D version
if length(size(phi))==4
  [Phi_size_1,Phi_size_3,Phi_size_3,Phi_size_4] = size(phi);
  phi_tmp = zeros(size(phi));
  for i = 1:Phi_size_3
    for j = 1:Phi_size_4
      phi_tmp(:,:,i,j) = SortPhi_InternalFunc(phi(:,:,i,j),opt);
    end
  end  
elseif  length(size(phi))==3
  [Phi_size_1,Phi_size_3,Phi_size_3] = size(phi);
  phi_tmp = zeros(size(phi));
  for i = 1:Phi_size_3
    phi_tmp(:,:,i) = SortPhi_InternalFunc(phi(:,:,i),opt);
  end  
elseif  length(size(phi))==2
    phi_tmp = SortPhi_InternalFunc(phi,opt);
end

phi=phi_tmp;

%---- function to sort phi for 1D or 2D ---
function phi = SortPhi_InternalFunc(phi,opt)
if length(size(phi))>=3
  error(['Please use a vector or 2D-matrix in phi.'])
end


Dphi = diff(phi,1,2);
[UpJ_x,UpJ_y] = find(Dphi>pi);
[DownJ_x,DownJ_y] = find(Dphi<-pi);

switch lower(opt)
    case '1d' % map on [-inf inf] 1d space.
        for i = 1:length(UpJ_x)
            phi(UpJ_x(i),[UpJ_y(i)+1:end]) = phi(UpJ_x(i),[UpJ_y(i)+1:end]) - 2*pi;
        end
        for i = 1:length(DownJ_x)
            phi(DownJ_x(i),[DownJ_y(i)+1:end]) = phi(DownJ_x(i),[DownJ_y(i)+1:end]) + 2*pi;
        end
    case 'circ2pi' % map on [-pi pi] space.
        for i = 1:length(UpJ_x)
            phi(UpJ_x(i),UpJ_y(i)+1) = NaN;
        end
        for i = 1:length(DownJ_x)
            phi(DownJ_x(i),DownJ_y(i)+1) = NaN;
        end
end

