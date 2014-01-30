function [a,b,varargout] = FindDiff2Next(opt,varargin)
% Draw Phase diagram of MH-synfire chain network.
% 
%
%
%
% by K.H 31,May.2003
global end_layer j0 j2  sigma_D M threshold stop_threshold
global r0_init r2_init


switch opt
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
case 'init'
 j0 = linspace(-1,1,100);
 j2 = linspace(0,4,100);
% j0 = linspace(-1,-0.6,10);
% j2 = linspace(3.0707,3.2,2);

 [J0,J2] = meshgrid(j0,j2);
%J0 = J0(1:50,:);
%J2 = J2(1:50,:);
 r0_init = 1;
 r2_init = 0;
 sigma_D = 0.25;
 
 M = 100;
 threshold = 0.25;
 stop_threshold = 1/(10^7);

 a = J0;
 b = J2;
 varargout{1} =[r0_init; r2_init];
 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 case 'rough'
[J0,J2]=  phase_diagramMH5('init');
length_j0 = size(J0,2);
length_j2 = size(J0,1);

r0 = zeros(length_j2,length_j0);
r2 = zeros(length_j2,length_j0);
end_layer =  zeros(length_j2,length_j0);
for i = 1:length_j0
  for j = 1:length_j2
    theory_MH2('init','J0',J0(j,i),'J2',J2(j,i),'sigma_D',sigma_D,...
	      'threshold',.25,'r0_init',r0_init,'r2_init',r2_init,'M',50,...
	      'stop_threshold',stop_threshold);
    
    data = theory_MH2('phase_diagram');
     r0(j,i) = data(1);r2(j,i) = data(2);end_layer(j,i)=data(3);
  end
end

data1 = [' \Delta=',num2str(sigma_D)];
data2 = [' h=',num2str(threshold)];
data3 = ['_J0',num2str(J0(1)),'_',num2str(J0(end))];
data4 = ['_J2',num2str(J2(1)),'_',num2str(J2(end))];
t = ['Phase diagram',data1,data2,data3,data4];

figure(1);title('r0')
mesh(J0,J2,r0);xlabel('J0');ylabel('J2');zlabel('r0')
title(t,'FontSize',10)

figure(2);title('r2')
mesh(J0,J2,r2);xlabel('J0');ylabel('J2');zlabel('r2')
title(t,'FontSize',10)

[y,m,d] = datevec(now); 
m = datestr(datenum(datevec(now)),3);

today = [num2str(d),m,num2str(y)];
savenameMAT = ['PhaseDiagram_Rgh_',today,'.mat']
save(savenameMAT,'r0','r2','end_layer','J0','J2','opt')
a = r0;
b = r2;
c = end_layer;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 case 'Search_Border'
[J0,J2,r]=  phase_diagramMH5('init');
dJ0 = 0.01;
dJ2 = 0.01;
J0 = [J0(1,1),J0(end,end)];
J2 = [J2(1,1),J2(end,end)];
Init_posi = [J0(1),J2(1)];
direction = [1,-1]; % Direction of grid calculation

length_r02_init = size(r,2);

r0_init_original = r(1,:); %r0_init;
r0_init = r0_init_original;
r2_init_original = r(2,:); %r2_init;
r2_init = r2_init_original;

[y,m,d] = datevec(now); 
m = datestr(datenum(datevec(now)),3);
today = [num2str(d),m,num2str(y)];

data1 = ['_D',num2str(sigma_D)];
data2 = ['_h',num2str(threshold)];
data3 = ['_r0',num2str(r0_init)]
data4 = ['_r2',num2str(r2_init)]
param = [data1,data2,data3,data4];

savenameEPS_R0 = ['SB_R0_',param,today,'.eps']
savenameEPS_R2 = ['SB_R2_',param,today,'.eps']
t = ['Search Border',param]

%%%%%%%%%%%%%%%%%%%%%%%%%
r0 = [];
r2 = [];
end_layer = [];
  now_posi = Init_posi;
  last_state = 2;% States: see fixNum function.
  
while now_posi(1) < J0(end)
    %%%%%%% k loop %%%
    for k = 1:length_r02_init
theory_MH2('init','J0',now_posi(1),'J2',now_posi(2),...
	   'sigma_D',sigma_D,'threshold',.25,'r0_init',r0_init,...
	   'r2_init',r2_init,'M',M,'stop_threshold',stop_threshold);
      
    data_tmp = theory_MH2('phase_diagram');
    r0_tmp(k) = data_tmp(1);
    r2_tmp(k) = data_tmp(2);
    end_layer_tmp(k) = data(3);
    end
    %%%%%end of k loop%%%%%
    i0 = fixNum(r0_tmp);
    i2 = fixNum(r2_tmp);
    now_state = i0;
    if now_state == 1;
      J0 = [J0,now_posi(1)];
      J0 = [J0,now_posi(2)];
      now_posi = now_posi + direction.*[dJ0,dJ2];
    end
    
end

for i = 1:length_j0
  %%%%%%%%j loop %%%%%%%%%%%%
  for j = 1:length_j2
    r0_tmp = zeros(3,k);
    r2_tmp = zeros(3,k);
    end_layer_tmp = zeros(3,k);
    %%%%%%% k loop %%%
    for k = 1:length_r02_init
    [J0(j2_n(j),j0_n(i)),J2(j2_n(j),j0_n(i))]
    if i >= 2 & j >= 2
      r0_init = r0(j2_n(j-1),j0_n(i-1));
      r2_init = r2(j2_n(j-1),j0_n(i-1));
    elseif i == 1 & j >= 2
      r0_init = r0(j2_n(j-1),j0_n(1));
      r2_init = r2(j2_n(j-1),j0_n(1));
    elseif i >=2  & j == 1
      r0_init = r0(j2_n(1),j0_n(i-1));
      r2_init = r2(j2_n(1),j0_n(i-1));
    elseif i == 1 & j == 1
      r0_init = r0_init_original(k);
      r2_init = r2_init_original(k);
    end

    data_tmp = theory_MH2('phase_diagram');
    r0_tmp(k) = data_tmp(1);
    r2_tmp(k) = data_tmp(2);
    end_layer_tmp(k) = data(3);
    end
    %%%%%end of k loop%%%%%
    
    r0(j2_n(j),j0_n(i)) = data(1);
    r2(j2_n(j),j0_n(i)) = data(2);
    end_layer(j2_n(j),j0_n(i))=data(3);    
  end %%%%%%%%%end of j loop %%%%%%%%%%%%%%%
end

figure(1);title('r0')
mesh(J0,J2,r0);xlabel('J0');ylabel('J2');zlabel('r0')
title(t,'FontSize',10); colorbar;
print(gcf,'-deps2',savenameEPS_R0); 

figure(2);title('r2')
mesh(J0,J2,r2);xlabel('J0');ylabel('J2');zlabel('r2')
title(t,'FontSize',10);colorbar;
print(gcf,'-deps2',savenameEPS_R2); 


savenameMAT = ['PhaseDiagram_lc',today,param,'.mat']
save(savenameMAT,'r0','r2','end_layer','J0','J2','r0_init_original',...
     'r2_init_original','opt')

a = r0;
b = r2;
c = end_layer;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 case '2p_Bifurcation'
figure(1); clf; figure(2);clf;
[J0,J2,r]=  phase_diagramMH5('init');
length_j0 = size(J0,2);
length_j2 = size(J2,1);

% 1/pi*sin(L*pi/N); Based on the result from 4/5 (4.4.12)
i0 = zeros(length_j2,length_j0);
i2 = zeros(length_j2,length_j0);
end_layer =zeros(length_j2,length_j0); ;
[y,m,d] = datevec(now); 
m = datestr(datenum(datevec(now)),3);
today = [num2str(d),m,num2str(y)];

data1 = ['_D',num2str(sigma_D)];
data2 = ['_h',num2str(threshold)];
data3 = ['_J0',num2str(J0(1)),'_',num2str(J0(end))];
data4 = ['_J2',num2str(J2(1)),'_',num2str(J2(end))];
param = [data1,data2,data3,data4];

savenameEPS_R0 = ['2p_bif_r0',param,today,'.eps']
savenameEPS_R2 = ['2p_bif_r2',param,today,'.eps']
savenameMAT = ['2p_bif_sirius',today,param]
t = [savenameMAT,param]


 [i0,i2,r0,r2,end_layer]= num_of_fixedPoint(J0,J2);

figure(1);hold on;
surf(J0,J2,i0);shading flat;view(0,90)
xlabel('J0');ylabel('J2');zlabel('r0')
title(['r0 ',t],'FontSize',10); 
print(gcf,'-depsc2',savenameEPS_R0); 

figure(2);hold on;
surf(J0,J2,i2);shading flat;view(0,90)
xlabel('J0');ylabel('J2');zlabel('r2')
title(['r2',t],'FontSize',10);
print(gcf,'-depsc2',savenameEPS_R2); 

save([savenameMAT,'.mat'],'i0','i2','end_layer','J0','J2','r0','r2')

a = i0;
b = i2;
c = end_layer;  

 case 'fixedpoints_analysis'
  
  
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 otherwise
  error(['Unknown option'])
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%% End %%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function [i0,i2,r0,r2,end_layer]= num_of_fixedPoint(J0,J2)
global sigma_D M threshold stop_threshold
%%%%% calculation as varing j0.

init_grid = 10;
grid_j0 = size(J0,2);
grid_j2 = size(J2,1);
L = linspace(0,1,init_grid); 

%N =1
r0_init = L; %L/N; % Based on the result from 4/5 (4.4.11)
r2_init = 1/pi*sin(L*pi);

r0 = zeros(grid_j0,grid_j2,init_grid);
r2 = zeros(grid_j0,grid_j2,init_grid);
i0 = zeros(grid_j0,grid_j2);
i2 = zeros(grid_j0,grid_j2);
end_layer =  zeros(grid_j0,grid_j2);

for dj0 = 1:grid_j0
  for dj2 = 1:grid_j2
  [J0(dj0,dj2),J2(dj0,dj2)]
    for j = 1:init_grid
theory_MH2('init','J0',J0(dj0,dj2),'J2',J2(dj0,dj2),...
	   'sigma_D',sigma_D,'threshold',.25,'r0_init',r0_init(j),...
	   'r2_init',r2_init(j),'M',M,'stop_threshold',stop_threshold);
    
    data = theory_MH2('phase_diagram');
  r0(dj0,dj2,j) = data(1);
  r2(dj0,dj2,j) = data(2);
   end
  end_layer(dj0,dj2)=data(3);  
  i0(dj0,dj2)= fixNum(r0(dj0,dj2,:));
  i2(dj0,dj2)= fixNum(r2(dj0,dj2,:));   
  end
end
end_layer = max(end_layer);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function out = fixNum(r)
r_max = max(r);

rate = 10^(-3);

if r_max <= rate
  out = 0;
elseif any(((r_max-rate)>r).*(r>rate))
  out = 2;
else
  out = 1;
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function out =Border(r,J0,J2)
global   sigma_D M threshold stop_threshold

J02_Start_r = [];%
J02_Next_r = [];%
K = 5; % Iteration of dichotomy.
length_j0 = size(J0,2);
J02_Border_r = zeros(2,length_j0); 
 
 for i = 1:length_j0 % Preparation
   j = ChkZeroPnt(r(:,i));
   if isempty(j)
     pnt = [NaN; NaN];
   else
     pnt = [J0(j,i);J2(j,i)];
   end
   J02_Start_r = [J02_Start_r,pnt];
   J02_Next_r =[J02_Next_r, WhichWay(r,i,j,J0,J2)]; 
 end

 
 for i = 1:length_j0 % Calculation 
 J02_zero_r = J02_Start_r(:,i);
 J02_real_r = J02_Next_r(:,i);
 
 
  %%%%%%%%%%%%%%%%%**********%%%%%%%%%%%%%%%%%%%%%%%
  for k = 1:K
    J02_tmp_r = (J02_zero_r + J02_real_r)./2;
    
    if isnan(J02_tmp_r)
      J02_zero_r = NaN;
      break
    end
    
    theory_MH2('init','J0',J02_tmp_r(1),'J2',J02_tmp_r(2),'sigma_D',sigma_D,...
	      'threshold',.25,'r0_init',r0_init,'r2_init',r2_init,'M',50,...
	      'stop_threshold',stop_threshold);
    
    data = theory_MH2('phase_diagram');
    r0_check = data(1); r2_check = data(2); end_layer_check=data(3);
    
    if r0_check > 0
      J02_real_r = J02_tmp_r;
    elseif r0_check == 0
      J02_zero_r = J02_tmp_r;
    end
  end
  %%%%%%%%%%%%%%%%%**********%%%%%%%%%%%%%%%%%%%%%%%
  J02_Border_r(:,i) = J02_zero_r;
 end

 out = J02_Border_r;
 
 
 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function out = ChkZeroPnt(r)
%Return the position of r =0 that is located at the farest point. 
 I = find(r==0)
% r(I(end));
if isempty(I) 
  out = [];
else
  out = I(end)
end

 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 function out = WhichWay(r,i,j,J0,J2)
 % it returns the position of positive r which is next to r = 0.
 %  out = [J0,J2]
 %
 
 length_j2 = size(J0,1);
 
 if isempty(j)
   out = [NaN; NaN];
   break;
 end
 
   
 if j ~=1 & j~=length_j2 % Decide which way to go. UP or DOWN?
   next_r_UP = r(j+1,i);
   next_r_DOWN = r(j-1,i);
   
   if next_r_UP >0 & next_r_DOWN ==0
     next_r =  next_r_UP;
     real_J0 =  J0(j+1,i);
     real_J2 =  J2(j+1,i);
   elseif next_r_UP == 0 & next_r_DOWN >0
     next_r =  next_r_DOWN; 
     real_J0 =  J0(j-1,i);
     real_J2 =  J2(j+1,i);
   else 
     error('Both side of 0 is 0. Strange !')
   end
 else
   warning(['Please make the mesh more smaller: r0/2 is on the boundary.'])   
   real_J0 = NaN;
   real_J2 = NaN;
 end
 
 out = [real_J0; real_J2];
 
 
 