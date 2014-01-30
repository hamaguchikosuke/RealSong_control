function [  m_spec_deriv,...
            m_amplitude,...
            m_Entropy,...
            m_FM,...
            m_AM,...
            m_frequency,...
            m_Pitch,...
            m_PitchGoodness,...
            varargout] = multitaper_feature_RTSAC3(J1,J2,...
            Ts,nFFT,param,varargin)
% J1: taper1 windowed FFT signal, column vector.
% J2: taper2 windowed FFT signal, column vector.
% Ts: sample time 
% frange: frequency range to take into consider
% erange: frequency range for entropy calculation. 
% It is better to cut off low frequency <1000Hz.
% [  m_spec_deriv,...
%             m_amplitude,...
%             m_Entropy,...
%             m_FM,...
%             m_AM,...
%             m_frequency,...
%             m_Pitch,...
%             m_PitchGoodness] = multitaper_feature_RTSAC(J1,J2,Ts,nFFT)


if nargin>=6
    calc_precise_pitch=varargin{1};
else
    calc_precise_pitch=0;
end


if nargin>=7
    test_plot=varargin{2};
else
    test_plot=0;
end

fs=1/Ts;
Nyq=fs/2;

% f=fs*((1:nFFT)-1)/nFFT; % not exactly correct, but I chose f-range less than Nyquist freq. 


% 
% up_pitch= 8000;% 
% low_pitch=400;%
% 
% param.cepst_nfft=2048;         % nfft size for cepstrum;
% quefrency = [0:param.cepst_nfft]*nFFT/(fs*param.cepst_nfft); % quefrency in [sec].
% param.quefrency_select=(1./quefrency<up_pitch & 1./quefrency > low_pitch); % select quefrency in 400 to 8000 Hz range.
% qt=quefrency(param.quefrency_select);
% 

%==============Power spectrum=============
Axx=J1.*conj(J1);
m_powSpec=real(Axx+(J2.*conj(J2)));
m_time_deriv=-real(J1.*conj(J2));
m_freq_deriv=-real(conj(J1*1i).*J2);
Axx=ifft(Axx); % calculate auto-correlation for pitch detection.

m_time_deriv_max=max(m_time_deriv(param.findex).^2,[],1);
m_freq_deriv_max=max(m_freq_deriv(param.findex).^2,[],1);

%===

m_amplitude=real(sum(m_powSpec(param.findex)));

log_power=m_time_deriv(param.findex).^2+m_freq_deriv(param.findex).^2;
m_SumLog=sum(log(m_powSpec(param.efindex)));
m_LogSum=mean(m_powSpec(param.efindex));

m_frequency=(param.f(param.findex)*log_power)/(sum(log_power)+eps);
gc_base=sum(log_power);
m_AM=sum(m_time_deriv(param.findex));


% m_frequency=m_frequency./max(gc_base,1)*fs/pad;
% m_frequency=Nyq*m_frequency./(gc_base+eps)/length(param.findex);
m_AM=m_AM./(m_amplitude+eps);
m_amplitude=log10(m_amplitude+1)*10; %units in Db


%===========Wiener entropy==================
if m_LogSum==0
    m_LogSum=0;
    m_Entropy=0;
else
    m_LogSum=log(m_LogSum); %divide by the number of frequencies
    m_Entropy=(m_SumLog/length(param.efindex))-m_LogSum;
end




%============FM===================

m_FM=real(atan(m_time_deriv_max/(m_freq_deriv_max+eps)));
%m_FM(find(m_freq_deriv_max==0))=0;

%%%%%%%%%%%%%%%%%%%%%%%%

%==========Directional Spectral derivatives=================

% 
cFM=cos(m_FM);
sFM=sin(m_FM);

%==The image==
m_spec_deriv=sFM*m_time_deriv(param.findex)+cFM*m_freq_deriv(param.findex);
% Cepstrum=(fft(m_spec_deriv./(m_powSpec(3:255)+eps),512,2))*( 1/2);
% % Cepstrum=fft(abs(m_spec_deriv),512,2);
% m_spec_deriv=m_powSpec(param.findex);

pitch_HoP=1800;%hz
gdn_HoP=10;
up_wiener=-1;

% size(m_spec_deriv)
Cepstrum=fft(m_spec_deriv(3:end)./(m_powSpec(param.findex(3:end))+eps),param.cepst_nfft,1)*( 1/2);
% size(Cepstrum)
% Cepstrum=fft(m_spec_deriv(3:end)./(m_powSpec(param.findex(3:end))+eps),length(m_spec_deriv(3:end)))*( 1/2);

x=abs(Cepstrum(param.quefrency_select)).^2;
bias_m=find(param.quefrency_select,1,'first')-1;

[m_PitchGoodness,m]=max(x);
m_Pitch=m+bias_m;
m_Pitch= 1./(m_Pitch*nFFT/(fs*param.cepst_nfft)); 


if (calc_precise_pitch)
df=1;
if m==1 
    parabolic_estimate_m = 1;
elseif m==length(x)
    parabolic_estimate_m = 1;
else   
    dy1 = x(m-1)-x(m);
    dy2 = x(m)-x(m+1);
    
    a = -(dy1-dy2)/(2*df^2);
    b = dy1/df - 2 * a * (m-0.5);
    parabolic_estimate_m = -b/(2*a)+bias_m;
end
% fprintf('Parabolic estimated of auto-correlation peak is %3.5gsec (freq=%3.5g)\n',...
%     cubic_estime_t,1/cubic_estime_t);
varargout{1}=1./(parabolic_estimate_m*nFFT/(fs*param.cepst_nfft));

end

% size(m_Pitch)
% size(m_PitchGoodness)
% size(m_Entropy)
% if pitch is too high or goodness of pitch is too low, and entropy is too
% high (noisy), just use frequency as pitch value.
if ((m_Pitch>pitch_HoP) || (m_PitchGoodness<gdn_HoP)) &&( m_Entropy>up_wiener)
    m_Pitch=m_frequency;
end

m_FM=m_FM*180/pi;

if (test_plot)
    figure(1);clf;
    subplot(3,1,1);
        plot(m_spec_deriv./(m_powSpec(param.findex)+eps));
%     plot(log(m_powSpec));
    subplot(3,1,2);
    aC=abs(Cepstrum);aC(256:end)=0;
    plot(aC,'-');  hold on;
    plot(find(param.quefrency_select),aC(find(param.quefrency_select)),'r.');
    [maxC,maxCind]=max(aC(param.quefrency_select))
    plot(maxCind,maxC,'r*')
    text(maxCind,maxC,sprintf('f_0=%5.5g pitchgoodness=%3.3g, precise pitch=%5.5g',...
        m_Pitch, m_PitchGoodness,varargout{1}));
   
%     plot(aC(1:128)+aC(1:2:256)+aC(1:4:end),'r.-'); 
    
     subplot(3,1,3);
    plot([1:length(Axx)]*Ts*1000,Axx,'b.-'); 
end


if nargout>=11
    varargout{2}=m_time_deriv_max;
    varargout{3}=m_freq_deriv_max;
    varargout{4}=m_powSpec(param.findex);
end

%%
