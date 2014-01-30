%
% Let's consider this Leaky Integrate-and-Fire Neuron.
% CdV=-L(V-Vre) + I
% output the theoritical Freqency of this eq. as a function of I. 
%
%

L = 1;
C = 1;
Vre = 0;
Vth = 20;
tau = C/L;
I_vth  = L*(Vth-Vre);

I=0:0.01:100;

freq = 1./(tau*log(1+(Vth*L)./(I-I_vth)));

plot(I(2001:end),freq(2001:end));

set(gca, 'FontSize', 18);
axis([0,max(I),0,max(freq)]);
xlabel('I');
ylabel('\omega');
title('Leaky Integrate-and-Fire \omega-I ');

