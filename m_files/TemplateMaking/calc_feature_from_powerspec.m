function  [m_amplitude,m_frequency,m_Entropy,Pitch_chose] =...
    calc_feature_from_powerspec(p,winsize,nFFT,F)
% a copy of feature calculation code in my_dsppitchtime_svm_5
% 


Nyq=F/2;
f=F*((1:nFFT)-1)/nFFT;
frange=[400,8000];
findex=find(f>=frange(1)&f<=frange(2)); % [400Hz to 8kHz] range.
Tlen=size(p,2);


y=p;
m_powSpec=y(findex,:);
m_amplitude=sum(m_powSpec);
m_frequency=sum(repmat(f(findex)',1,Tlen).*m_powSpec)./m_amplitude;
% convert into Db unit.
m_amplitude=log10(m_amplitude+1)*10-70; 

m_SumLog=sum(log(m_powSpec+eps),1);
m_LogSum=sum(m_powSpec,1); 

%=========== log of Wiener entropy ==================

m_LogSum=log(m_LogSum/length(findex));
m_Entropy=(m_SumLog/length(findex))-m_LogSum;
ind =find(m_LogSum==0);
m_Entropy(ind)=0;

%========== Pitch =================


%==The image==
up_pitch=3;% index fs/up_pitch hz??
low_pitch=64;%index fs/low_pitch hz??
pitch_HoP=1800;%hz
gdn_HoP=100;
up_wiener=-2;

select=up_pitch:floor(nFFT/2);

Cepstrum=fft(y(select,:)+eps,nFFT,1);
x=abs(Cepstrum(up_pitch:low_pitch,:));
[m_PitchGoodness,m_Pitch]=max(x,[],1);
% m_Pitch=m_Pitch;
Pitch_chose= F./m_Pitch;
% 
% if (Pitch_chose>pitch_HoP | ...
%     (m_PitchGoodness<gdn_HoP &...
%     m_Entropy>up_wiener))



if (Pitch_chose>pitch_HoP)|(m_PitchGoodness<gdn_HoP & m_Entropy>up_wiener)
Pitch_chose=m_frequency;
end
               
                
                
                
