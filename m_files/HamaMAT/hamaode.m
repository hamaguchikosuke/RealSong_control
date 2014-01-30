function hamaode(opt)
% run ode
% % ex)
% hamaode('init');
% hamaode('run')
% by KH 20080805


warning off;

global pm od ui gph
figure(1);clf;
gph.g1 = [0.1,0.35,0.28,0.28];   
gph.g2_1 = [0.1, 0.8,0.4,0.1];
gph.g2_2 = [0.1, 0.67,0.4,0.1];
gph.g2 = [0.1,0.3,0.3,0.3]; 
gph.g3 = [0.6,0.1,0.3,0.8];
pm.usesameNoiseMat = 1;
%%%%%% Map or Ordinary Equation 
pm.map = 0;
pm.ode = 1-pm.map; 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
ui.quitflag = 0;
ui.pauseflag = -1;

pm.epsilon = 1;
pm.b = 1;
pm.d = 2;
% pm.J0 = -1;
% pm.J1 = 5;
% pm.Noise = 0;
% pm.beta =2;
% pm.h = .25;
% 
pm.N = 2;
% od.Theta = linspace(-pi,pi,pm.N+1); od.Theta = od.Theta(1:end-1);
% od.Cos = cos(od.Theta); od.Sin = sin(od.Theta);
% od.NoiseMatrix =  make_sym_randmat(pm.N)/sqrt(pm.N);
%%%%%%%%%%% Range of x1 x2 %%%%%%%%%%%%%%%%%%%
gph.x1 = [-10:.1:10];
gph.x2 = [-10:.1:10];

od.x = ones(2,1);zeros(pm.N,1);
od.x0x1 = [od.x];
%od.ODEfunc = 'p13_eq1_3_4';
%od.ODEfunc = 'p15_eq1_3_2_a';
%  od.ODEfunc = 'p15_eq1_3_2_b';
% od.ODEfunc = 'p15_eq1_3_2_c';
od.ODEfunc = 'p17_eq1_4_1';



od.T = 0;
dt = 0.1;
pm.drawTimeSize = 50;
od.time = 0;
% 
% %----- Connection Plot ---------%a
% subplot('position',gph.g1);
% gph.connection = plot(od.Theta,pm.J0+pm.J1*od.Cos+pm.J*od.NoiseMatrix(ceil(pm.N/2),:));
% xlabel('\Delta \theta'); ylabel('J_{\theta \theta}');
% axis([-pi pi -10 15]); line([-pi pi], [0 0]);
% %------ Position plot ---------%
% subplot('position',gph.g2_1);
% gph.od.x0x1 = plot(T,[0;0]);set(gca,'XtickLabel',[]);ylabel('x0(t),x1(t)');
% gph.od.x0x1P = get(gph.od.x0x1,'Parent');
% subplot('position',gph.g2_2);
% gph.pos_phi = plot(T,0);ylabel('\phi(t)')
% gph.pos_phiP = get(gph.pos_phi,'Parent');

%----- Activity plot
subplot('position',gph.g3);
gph.activity = plot(od.x(1),od.x(2),'ro');
gph.activity_title = title('Activity'); hold on;
if (pm.ode)
    gph.od.x0x1 = plot(od.x(1),od.x(2),'b-');
elseif (pm.map)
    gph.od.x0x1 = plot(od.x(1),od.x(2),'b.','MarkerSize',3);
end

xlabel('x1'); ylabel('x2');
feval(od.ODEfunc,[],'init');

axis([-2*pi 2*pi -3 3]);
%axis([-.5 .5 -.5 .5]);
%axis([-1 1 -1 1])
%axis([-3 3 -3 3])
%==== UI Control =====
   
uicontrol('Style','pushbutton', 'Units','normalized', ...
          'Position',[0.6  0.03 0.1 0.05],...
          'String','clf','Callback','global od; od.time = 0;od.T = 0;od.x0x1 = [];');
  
uicontrol('Style','pushbutton', 'Units','normalized', ...
          'Position',[0.7  0.03 0.1 0.05],...
          'String','initial point','Callback','global od; ic = ginput(1); od.x=[ic(1);ic(2)]; od.time = 0; od.T = 0;');
 
uicontrol('Style','pushbutton', 'Units','normalized', ...
          'Position',[0.8  0.03 0.1 0.05],...
          'String','pause','tag','pause','Callback','global ui; ui.pauseflag=-ui.pauseflag;');
      
uicontrol('Style','pushbutton', 'Units','normalized', ...
    'Position',[0.9  0.03 0.1 0.05],...
    'String','quit','Callback','global ui; ui.quitflag=1;');

 
% %UI interface
% uicontrol('Style','pushbutton', 'Units','normalized', ...
%     'Position',[0.4  0.4 0.1 0.05],...
%     'String','local pulse','Callback','od.x=od.x+.1*transpose(od.Cos);');
% 
% uicontrol('Style','pushbutton', 'Units','normalized', ...
%     'Position',[0.4  0.3 0.1 0.05],...
%     'String','init','Callback','od.x=zeros(pm.N,1);x0=0;rc=0;rs=0;');

%----- J,J0,J1 UI -----------------
uicontrol('Style','text', 'Units','normalized', ...
    'Position',[0.4  0.25 0.03 0.03],'string','b=');
uicontrol('Style','edit', 'Units','normalized', ...
    'Position',[0.43  0.25 0.05 0.03],...
    'string',num2str(pm.b),'tag','b','Callback','loc_changepars;');
uicontrol('Style','text', 'Units','normalized', ...
    'Position',[0.4  0.2 0.03 0.03],'string','d=');
uicontrol('Style','edit', 'Units','normalized', ...
    'Position',[0.43  0.2 0.05 0.03],...
    'string',num2str(pm.d),'tag','d','Callback','loc_changepars;');
uicontrol('Style','text', 'Units','normalized', ...
    'Position',[0.4  0.15 0.03 0.03],'string','e=');
uicontrol('Style','edit', 'Units','normalized', ...
    'Position',[0.43  0.15 0.05 0.03],...
    'string',num2str(pm.epsilon),'tag','epsilon','Callback','loc_changepars;');
% 
% uicontrol('Style','text', 'Units','normalized', ...
%     'Position',[0.4  0.15 0.03 0.03],'string','J0=');
% uicontrol('Style','edit', 'Units','normalized', ...
%     'Position',[0.43  0.15 0.05 0.03],...
%     'string',num2str(pm.J0),'tag','J0','Callback','loc_changepars;');
% 
% uicontrol('Style','text', 'Units','normalized', ...
%     'Position',[0.4  0.1 0.03 0.03],'string','J1=');
% uicontrol('Style','edit', 'Units','normalized', ...
%     'Position',[0.43  0.1 0.05 0.03],...
%     'string',num2str(pm.J1),'tag','J1','Callback','loc_changepars;');
% 
% %----- beta, Noise UI -----------------
% uicontrol('Style','text', 'Units','normalized', ...
%     'Position',[0.49  0.2 0.03 0.03],'string','\beta=');
% uicontrol('Style','edit', 'Units','normalized', ...
%     'Position',[0.52  0.2 0.05 0.03],...
%     'string',num2str(pm.beta),'tag','beta','Callback','loc_changepars;');
% 
% uicontrol('Style','text', 'Units','normalized', ...
%     'Position',[0.49  0.15 0.03 0.03],'string','Noise=');
% uicontrol('Style','edit', 'Units','normalized', ...
%     'Position',[0.52  0.15 0.05 0.03],...
%     'string',num2str(pm.Noise),'tag','Noise','Callback','loc_changepars;');
% 
% uicontrol('Style','text', 'Units','normalized', ...
%     'Position',[0.49  0.1 0.03 0.03],'string','h=');
% uicontrol('Style','edit', 'Units','normalized', ...
%     'Position',[0.52  0.1 0.05 0.03],...
%     'string',num2str(pm.h),'tag','h','Callback','loc_changepars;');
%    
% uicontrol('Style','frame', 'Units','normalized', ...
%           'Position',[0.1  0.08 0.25 0.22]);
% uicontrol('Style','text', 'Units','normalized', 'HorizontalAlignment','left',...
%           'Position',[0.11  0.085 0.23 0.21],'string',{'model:';'';'x_i'' = -x_i + \sum_j J_{ij} r_j + Noise';'';'r_i=(1+tanh(beta*(x_i-h)))/2';'';'J_{ij} = J_0/N + J_1cos(\theta-\theta'')/N+\xi_{ij}';'';'\xi \sim N(0,J^2/N)'});

ui.button_pauseflag =findobj('tag','pause');
while ui.quitflag==0
    while ui.pauseflag>0
        %set(ui.button_pauseflag,'string','resume');
        pause(.5);drawnow; %needed to overcome MATLAB7 bug (found by Gerardo Lafferriere)     
    end;
    od.T = od.T+dt;
   
%     I = feval(od.ODEfunc,od.x);
    if (pm.map)
      od.x =   feval(od.ODEfunc,od.x);
    elseif (pm.ode)
        Kn1 = feval(od.ODEfunc,od.x);
        Kn2 = feval(od.ODEfunc,od.x+dt*Kn1);
        od.x = od.x + dt*(Kn1+Kn2)/2;
    end
    %--------PLOT ------------%
    set(gph.activity,'XData',od.x(1),'YData',od.x(2)); 
    set(gph.activity_title,'String',[num2str(od.T),'ms']);

    if od.T < pm.drawTimeSize
        od.x0x1 = [od.x0x1, od.x];
        %phiphi= [phiphi,atan2(rs,rc)];
        od.time = [od.time, od.T];
    else
        od.x0x1 = [od.x0x1(:,2:end), od.x];
        %phiphi = [phiphi(2:end),atan2(rs,rc)];
        od.time = [max(0,od.T-pm.drawTimeSize+dt):dt:max(od.T,pm.drawTimeSize)];
    end
    %set(gph.pos_phi,'XData',od.time,'YData',phiphi);
%     set(gph.pos_phiP,'XLim',[od.time(1),od.time(end)],'YLim',[-pi pi]);
%      for i=1:size(gph.od.x0x1,1)
         set(gph.od.x0x1, 'XData',od.x0x1(1,:),'YData', od.x0x1(2,:));
%         set(gph.od.x0x1P{i},'XLim',[od.time(1),od.time(end)],'YLim',[0 1]);
%      end


%     if (od.T>1000)
%         return;
%     end
    if mod(ceil(od.T/dt),10)==0
       drawnow;
    end 
end

%%%%%%%%%%%%%%%Guckenheimer and Holmes, p13, eq1_3_4 %%%%%%%%%%%%%%%%%%%%
function [out,varargout] = p13_eq1_3_4(x,opt,varargin)
global od pm ui gph
pm.NredNC = 1;
if nargin>=2
    switch opt
        case 'init'
            gph.nulca = line([-10 10],[0 0]); hold on; % x2 = 0; 
            gph.nulcb = line([0 0], [-10 10]);
            gph.nulc1 = plot(gph.x1,-1./(pm.epsilon*gph.x1));
        case 'nulc'
             if pm.epsilon == 0;
                out = repmat(NaN,size(gph.x1));
                varargout{1} =repmat(NaN,size(gph.x1));
            else
            out = x;
            varargout{1} =-1./(pm.epsilon*x);
            end
        otherwise
            error(['Unknown option'])
    end
else
 out = [0 1; -1 0]*x  - pm.epsilon*[0; x(1)^2*x(2)];
end


%%%%%%%%%%%%%%%Guckenheimer and Holmes, p15, ex1_3_2 (1) %%%%%%%%%%%%%%%%%%%%
function [out,varargout] = p15_eq1_3_2_a(x,opt,varargin)
global od pm ui gph
pm.NredNC = 1;
if nargin>=2
    switch opt
        case 'init'
            gph.nulca = line([-10 10],[0 0]); hold on; % x2 = 0; 
            %gph.nulcb = line([0 0], [-10 10]); hold on; % x1 = 0; 
            gph.nulc1 = plot(gph.x1,(gph.x1-gph.x1.^3)/pm.epsilon); hold on;
        case 'nulc'
             if varargin{1}==1
                 if pm.epsilon == 0
                     out = x;
                     varargout{1} =repmat(NaN,size(x));
                 else
                     out = x;
                     varargout{1} =(x-x.^3)/pm.epsilon;
                 end
             else
                 error(['Not so many null-clines.'])
             end
        otherwise
            error(['Unknown option'])
    end
else
 out = [0 1; 1 pm.epsilon]*x  + [0; -x(1)^3];
end

%%%%%%%%%%%%%%%Guckenheimer and Holmes, p15, ex1_3_2 (b) %%%%%%%%%%%%%%%%%%%%
function [out,varargout] = p15_eq1_3_2_b(x,opt,varargin)
global od pm ui gph
pm.NredNC = 1;
if nargin>=2
    switch opt
        case 'init'
            gph.nulca = line([-10 10],[0 0]); hold on; % x2 = 0; 
            %gph.nulcb = line([0 0], [-10 10]); hold on; % x1 = 0; 
            gph.nulc1 = plot(gph.x1,cos(gph.x1)); hold on;
        case 'nulc'
             if varargin{1}==1
             out = x;
             varargout{1} =cos(gph.x1);
             else
                 error(['Not so many null-clines.'])
             end    
        otherwise
            error(['Unknown option'])
    end
else
 out = [x(2);sin(x(1))];
end

%%%%%%%%%%%%%%%Guckenheimer and Holmes, p15, ex1_3_2 (c) %%%%%%%%%%%%%%%%%%%%
function [out,varargout] = p15_eq1_3_2_c(x,opt,varargin)
global od pm ui gph
pm.NredNC = 2;
if nargin>=2
    if strfind(opt,'init')
            gph.nulca = line([-10 10],[0 0]); hold on; % x2 = 0; 
            gph.nulcb = line([0 0], [-10 10]); hold on; % x1 = 0; 
            gph.nulc1 = plot(gph.x1,sqrt(-sin(gph.x1/pm.epsilon))); hold on;
            gph.nulc2 = plot(gph.x1,-sqrt(-sin(gph.x1/pm.epsilon))); hold on;
    elseif strfind(opt,'nulc')
            if varargin{1}==1
             out = x;
             varargout{1} =sqrt(-sin(gph.x1/pm.epsilon));
            elseif varargin{1}==2
             out=x;
             varargout{1} =-sqrt(-sin(gph.x1/pm.epsilon));
            end
    else
        error(['Unknown option.']);
    end
else
 out = [x(2);-sin(x(1))-pm.epsilon*x(2).^2];
end
%%%%%%%%%%%%%%%Guckenheimer and Holmes, p17, ex1_4_1 %%%%%%%%%%%%%%%%%%%%
function [out,varargout] = p17_eq1_4_1(x,opt,varargin)
global od pm ui gph
pm.map = 1; pm.ode = 0;
pm.NredNC = 2;
if nargin>=2
    if strfind(opt,'init')
         set(gph.od.x0x1,'LineStyle','none','Marker','.','MarkerSize',3);
        gph.nulca = line([-10 10],[0 0]); hold on; % x2 = 0;
        gph.nulcb = line([0 0], [-10 10]); hold on; % x1 = 0;
        gph.nulc1 = plot(gph.x1,gph.x1); hold on;
        gph.nulc2 = plot((gph.x2.^3+(1-pm.d)*gph.x2)/pm.b,gph.x2); hold on;
    elseif strfind(opt,'nulc')
        if varargin{1}==1
            out = x;
            varargout{1} = gph.x2;
        elseif varargin{1}==2
            out= x;
            if pm.b == 0
                out = repmat(NaN,size(x),1);
                varargout{1} = repmat(NaN,size(x),1);
            else
                out = (x.^3+(1-pm.d)*x)/pm.b;
                varargout{1} = gph.x2;
            end
        end

    else
        error(['Unknown option.']);
    end
else
    out = [x(2);pm.b*x(1)+pm.d*x(2)-x(2)^3];
end

%% %%%%%%%%%%%%% Gardiner PRL,  %%%%%%%%%%%%%%%%%%%%
function [out,varargout] = PRL_Gardiner2001(x,opt,varargin)

% x' = y;
% y' = -pm.epsilon*x + pm.b*y.^3;

global od pm ui gph
pm.map = 1; pm.ode = 0;
pm.NredNC = 2;
if nargin>=2
    if strfind(opt,'init')
         set(gph.od.x0x1,'LineStyle','none','Marker','.','MarkerSize',3);
        gph.nulca = line([-10 10],[0 0]); hold on; % x2 = 0;
        gph.nulcb = line([0 0], [-10 10]); hold on; % x1 = 0;
        gph.nulc1 = plot(gph.x1,gph.x1); hold on;
        gph.nulc2 = plot((gph.x2.^3+(1-pm.d)*gph.x2)/pm.b,gph.x2); hold on;
    elseif strfind(opt,'nulc')
        if varargin{1}==1
            out = x;
            varargout{1} = gph.x2;
        elseif varargin{1}==2
            out= x;
            if pm.b == 0
                out = repmat(NaN,size(x),1);
                varargout{1} = repmat(NaN,size(x),1);
            else
                out = (x.^3+(1-pm.d)*x)/pm.b;
                varargout{1} = gph.x2;
            end
        end

    else
        error(['Unknown option.']);
    end
else
    out = [x(2);pm.b*x(1)+pm.d*x(2)-x(2)^3];
end

%%
function []=loc_changepars(inpcur)
global od pm gph ui

pm.b = str2double(get(findobj('tag','b'),'string'));
set(findobj('tag','b'),'string',num2str(pm.b));

pm.d = str2double(get(findobj('tag','d'),'string'));
set(findobj('tag','d'),'string',num2str(pm.d));

pm.epsilon = str2double(get(findobj('tag','epsilon'),'string'));
set(findobj('tag','epsilon'),'string',num2str(pm.epsilon));


for i = 1:pm.NredNC
     [xdata,ydata] = feval(od.ODEfunc,gph.x1,'nulc',i);
%      set(gph.nulc',num2str(i),'YData',ydata));
f = ['set(gph.nulc',num2str(i),',''XData'',xdata,''YData'',ydata)'];
     eval(f);
end