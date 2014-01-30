function [outs,cnts]=iterative_mean_var_2(x,opt)
% estimate mean and variance from the continuously flowing-in data,
% by using the iterative relationship.
%
% ex1)
% --- init---
% iterative_mean_var([],'init')
% --- estimate ---
% out=iterative_mean_var(x);
% where x is Nx1 vector;
% out is the 2Nx1 vector with
% first N are mean of x, next N are var of x.
% 
% ex2)
% --- init---
% iterative_mean_var(x,threshold_pattern)
% x: NxT vector, 
% threshold_pattern: MxT threshold patterns 
% --- estimate ---
% out=iterative_mean_var(x);
% where x is NxT vector;
% out is the (M*2N)xT vector.
% where M is the number of rows in threshold pattern
% first N are mean of x, next N are var of x.
%
% if no data available, put zero vector with the same size,
% or iterative_mean_var([],'reset').
%
% 'init':  initiallize and construct internal variables
% 'reset': just reset internal variables without constructing it
%
%
% --- iterative method to calculate mean and variance ---
% E(x_n)  =(N-1)/N*E(x_{n-1})+1/N*x_n;
% E(x_n^2)=(N-1)/N*E(x_{n-1}^2)+1/N*x_n^2;
% V(x_n)  =E(x_n^2) - E(x_n)^2;
%
% 
% ex) 
% x=zeros(4,1);
% iterative_mean_var(x,'init');
% out=zeros(8,100);
% for ii=1:100
% if mod(ii,20)==0, x=0; else x=[-70,0.5,10,50]'+randn(4,1);end
% out(:,ii)=iterative_mean_var(x);
% end
% plot(out')
% by KH 20101027

persistent cnt tmp tmp2 out

if nargin==2
    
    switch opt
        case 'init'
          
            tmp=zeros(length(x),1);
            tmp2=zeros(length(x),1);
            out=zeros(2*length(x),1);
            cnt=0;
        case 'reset'
        otherwise
            error('Unknown option!');
    end
   
elseif nargin==1
    if all(x==0)
        cnt=0;
        tmp=zeros(length(tmp),1);
        tmp2=zeros(length(tmp2),1);
        out=zeros(length(out),1);
    else
        cnt=cnt+1;
        if cnt>0     
            tmp=(cnt-1)/cnt*tmp     +x/cnt;
            tmp2=(cnt-1)/cnt*tmp2   +(x.^2)/cnt;
            out(1:length(x))= tmp;
            out((length(x)+1):end)=tmp2-tmp.^2;           
        end
    end

end

 
    outs=out;
    cnts=cnt;