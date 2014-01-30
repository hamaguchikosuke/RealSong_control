function [a, b, c] = testneurons(t, x, task, I)
% testneurons: A number of neurons 
% whose dynamics are represented as a Hodgkin-Huxley model.
% Jan.28.2002 by kosuke hamaguchi.

% to be able to change the constant values of HH neuron
global C gna gk gl ena ek el N Graph

if isempty(task) % No task, return x dots.
  % state variables
  x = reshape(x,4,N);
  v = x(1,:); m = x(2,:); h = x(3,:); n = x(4,:);
 
  % Input current
  if size(I,1) == 2             % if the I =(t,I) table
  It = interp1(I(1,:), I(2,:),t);
  else     It = I(1);              % I is constant current.
  end
  
  It = It + v*Graph

	am = 0.1*(v+40)./(1-exp(-(v+40)/10));
	bm = 4*exp(-(v+65)/18);
	ah = 0.07*exp(-(v+65)/20);
	bh = 1/(1+exp(-(v+35)/10));
	an = 0.01*(v+55)./(1-exp(-(v+55)/10));
	bn = 0.123*exp(-(v+65)/80);
 % x dots
	a = [ (It - gna.*m.^3.*h.*(v-ena) - gk.*n.^4.*(v-ek) - gl.*(v-el))./C;
		am.*(1-m)-bm.*m;
		ah.*(1-h)-bh.*h;
                an.*(1-n)-bn.*n];
     return;
end

switch(task)

case 'init'
% membrane capacitance (uF/cm^2)
     I = repmat(1,N);
     C = 1*I;
     % maximum conductance (uS/cm^2)
     gna = 120*I;  % sodium
     gk = 36*I;    % pottasium
     gl = 0.3*I;   % leak 
     % reversal potential (mV)
     ena = 50*I;
     ek = -77*I;
     el = -54.4*I;
     % Number of cells
     N = 2  
     Graph = [0 1;
	      0 0];

     % return default value
     a = [0 100]; % default time span
     bmean = [     -65; 
		 0.052; 
		 0.596; 
		 0.317]; %default value of v,m,h,n
       bvar = [20  0    0    0; 
	       0 0.020  0    0;
	       0   0   0.2   0;
	       0   0    0  0.1]; % default variance of v,m,h,n 
     b = repmat(bmean,1,N) + bvar*randn(4,N); 
     c=  [];
case 'name'
       a = char('vol', 'm', 'h', 'n');
case 'title'
a = char('Hodzkin-Huxley equation');

otherwise 
     error( [ ' invalid task; '], task);

end

% end of hamahh.m
