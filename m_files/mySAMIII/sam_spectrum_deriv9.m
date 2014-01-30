function [mm_spec_deriv ,...
          mm_AM, ...
          mm_FM ,...
          mm_Entropy , ...
          mm_amplitude ,...
          mm_frequency, ...
          mm_PitchGoodness, ...
          mm_Pitch , ...
          mm_Pitch_chose ,...
          mm_Pitch_weight,...
          f ,t,param]=sam_spectrum_deriv9(TS,fs,varargin)


% [m_spec_deriv , m_AM, m_FM ,m_Entropy , m_amplitude ,m_frequency, m_PitchGoodness , m_Pitch , Pitch_chose , Pitch_weight ]=sam_spectrum_deriv9(TS,fs);
%	 uses the derivative estimates to calculate the spectrum's frequency
%	 and time derivatives
% 
%        S: estimated spectrum; S_f: estimated frequency derivative; 
%        S_t: estimated time derivative
%        NW: time bandwidth parameter (e.g. 3)
%        K : number of tapers kept, approx. 2*NW-1
%        pad: length to which data will be padded (preferably power of 2
%        window: time window size
%        winstep: distance between centers of adjacent time windows

%        Written by Sigal Saar August 08 2005
%        Modified by Kosuke Hamaguchi 04 2010
%        Further modified by Kosuke Hamaguchi 08 2012 to generate similar
%        output for different sampling frequency. 
% % 
% frange=[600 11024];
% frange=[600 22049];
% 
% To use a specific set of parameters to analyze sound,
% [m_spec_deriv]=sam_spectrum_deriv3(TS,fs,param_file,fs_for_paramfile);
% "param_file"s are in private direcotry.
% fs_for_paramfile is just fs.
% 
% For trouble shooting, you can plot whatever at a specific time point by
%[m_spec_deriv]=sam_spectrum_deriv3(TS,fs,param_file,fs_for_paramfile,t_check);
% where t_check is the time point where you want to analyze. time is
% counted from the beginning of the file (t=0 is at the beginning of the
% file);
 


[b,a] = ellip(4,.1,50,[400/(fs/2) 0.99]);

TS=filtfilt(b,a,TS);
if nargin==2
    load('Parameters');
elseif nargin==3
    param_file=varargin{1};
    param=feval(param_file);
elseif nargin>=4
    param_file=varargin{1};
    param=feval(param_file,varargin{2});
    %     load(param_file);
end

if nargin>=5
    test_plot_time=varargin{3};
else
    test_plot_time=[];
end


T=length(TS);

nBlockSize=2500;


Nsteps=1+fix((T-param.window)/(param.winstep));
time_index_fft=param.window/2+[0:Nsteps-1]*param.winstep;
t=time_index_fft/fs;

test_plot_time_in_Nstep_index=ceil(test_plot_time*fs/param.winstep)+1;


% TSM=zeros(Nsteps,param.window);
% size(TSM);
WinBlockSize=10000;
nWinBlockSize=ceil(Nsteps/WinBlockSize);
% fprintf('Total:%dsteps, divide it into %d \n',Nsteps,nWinBlockSize);

% 
% for ii=1:nWinBlockSize
%     index=[1:WinBlockSize]+(ii-1)*WinBlockSize;
%     if index(end)>Nsteps, index=index(1):Nsteps;end
% %     tmp=running_windows3(TS,param.window, param.winstep,index)'; 
%     TSM(index,:)=running_windows3(TS,param.window, param.winstep,index)';
% end

% size(TSM)
% Nsteps=size(TSM,1);


fgrid = psdfreqvec('npts',param.pad,'Fs',fs,'Range','half')';

freq_winer_ampl_index=[param.min_freq_ampl:param.max_freq_ampl];
freq_entropy_index   =[param.min_freq_entropy:param.max_freq_entropy];

% select=3:255;%(length(fgrid)-3);
select=freq_entropy_index;
f = fgrid(select);

cepst_nfft=2048;         % nfft size for cepstrum;
quefrency = [0:cepst_nfft]'*(param.pad)/(fs*cepst_nfft); % quefrency. in [sec].
quefrency_select=(1./quefrency<8000 & 1./quefrency > 600); % select quefrency in 400 to 8000 Hz range.

qt=quefrency(quefrency_select);

% initialize output variables to allocate memory
mm_spec_deriv   =zeros(Nsteps,length(select));
mm_AM           =zeros(Nsteps,1);
mm_FM           =zeros(Nsteps,1);
mm_Entropy      =zeros(Nsteps,1); 
mm_amplitude    =zeros(Nsteps,1);
mm_frequency    =zeros(Nsteps,1);
mm_PitchGoodness=zeros(Nsteps,1);
mm_Pitch        =zeros(Nsteps,1); 
mm_Pitch_chose  =zeros(Nsteps,1); 
mm_Pitch_weight =zeros(Nsteps,1);

[E2,V] = dpss(param.window,4,3);
Ec=E2(:,1)';
Es=E2(:,2)';


% calculate in block to avoid memory error
nBlockSteps=ceil(Nsteps/nBlockSize);
%%
for ii=1:nBlockSteps
  
    index=[1:nBlockSize]+(ii-1)*nBlockSize;
    if max(index)>Nsteps,        index=index(1):Nsteps; end

    TSM=running_windows3(TS,param.window, param.winstep,index)';
    J1=fft(TSM.*Ec(ones(length(index),1),:),param.pad,2);
    J2=fft(TSM.*Es(ones(length(index),1),:),param.pad,2);
  

    %==============Power spectrum=============
    m_powSpec=(J1.*conj(J1))+(J2.*conj(J2));
%         m_time_deriv=-1*(real(J1).*real(J2)+imag(J1).*imag(J2));
%         m_freq_deriv=((imag(J1).*real(J2)-real(J1).*imag(J2)));
    m_time_deriv=-real(J1.*conj(J2));
    m_freq_deriv=-real(conj(J1*i).*J2);

m_time_deriv_max=max(m_time_deriv.^2,[],2);
m_freq_deriv_max=max(m_freq_deriv.^2,[],2);

%===


m_amplitude=sum(m_powSpec(:,freq_winer_ampl_index),2);
log_power=m_time_deriv(:,freq_winer_ampl_index).^2+m_freq_deriv(:,freq_winer_ampl_index).^2; 

gc_base=sum(log_power,2);
m_AM=sum(m_time_deriv(:,freq_winer_ampl_index),2);

m_frequency=sum((ones(size(log_power,1),1)*fgrid(freq_winer_ampl_index)).*log_power,2);
m_frequency=m_frequency./(gc_base+eps);

m_AM=m_AM./(m_amplitude+eps);
m_amplitude=log10(m_amplitude*1024/param.pad+1)*10-70; %units in Db


%===========Wiener entropy==================


m_SumLog=sum(log(m_powSpec(:,freq_entropy_index)+eps),2);
m_LogSum=(sum(m_powSpec(:,freq_entropy_index),2)); 

m_LogSum(find(m_LogSum==0))=length(freq_entropy_index); 
m_LogSum=log(m_LogSum/length(freq_entropy_index)); %divide by the number of frequencies
m_Entropy=(m_SumLog/length(freq_entropy_index))-m_LogSum;
m_Entropy(find(m_LogSum==0))=0; 


%============FM===================

m_FM=atan(m_time_deriv_max./(m_freq_deriv_max+eps));
%m_FM(find(m_freq_deriv_max==0))=0;

%%%%%%%%%%%%%%%%%%%%%%%%

%==========Directional Spectral derivatives=================


cFM=cos(m_FM);
sFM=sin(m_FM);

%==The image==

m_spec_deriv=m_time_deriv(:,select).*(sFM*ones(1,length(select)))+m_freq_deriv(:,select).*(cFM*ones(1,length(select)));
% Cepstrum=(fft(m_spec_deriv./(m_powSpec(:,select)+eps),512,2))*( 1/2);
bias=3;
% hanning_matrix=repmat(hanning(length(select)-bias+1)',size(m_spec_deriv,1),1);

% Cepstrum=(fft(hanning_matrix.*m_spec_deriv(:,bias:end)./(m_powSpec(:,select(bias:end))+eps),cepst_nfft,2))*( 1/2);
Cepstrum=(fft(m_spec_deriv(:,bias:end)./(m_powSpec(:,select(bias:end))+eps),cepst_nfft,2))*( 1/2);

x=abs(Cepstrum(:,quefrency_select)).^2;
% x=abs(fft(abs(m_spec_deriv),512,2)).^2;
bias=3;
[m_PitchGoodness,m_Pitch]=max(x(:,bias:end),[],2);
% m_PitchGoodness=m_PitchGoodness(:,end);
m_Pitch=m_Pitch+bias-1;

ismember_index=find(ismember(test_plot_time_in_Nstep_index,index));
for kk=1:length(ismember_index)
     
    test_index=rem(test_plot_time_in_Nstep_index(kk),nBlockSize);
    fprintf('Generate test plot at t=%f (index=%d, %d)\n',...
        test_plot_time(kk),test_plot_time_in_Nstep_index(kk),test_index);
    txt=sprintf('t=%f (index=%d, %d)',...
        test_plot_time(kk),test_plot_time_in_Nstep_index(kk),test_index);
    
    
    figure(33);clf;
%       sound(TSM(test_index,:)/std(TSM(test_index,:))/10);
    subplot(3,1,1);
    plot(TSM(test_index,:));
    title(txt);
    
    subplot(3,1,2);
    %     size(m_spec_deriv);
%     norm_m_spec_deriv=m_spec_deriv./(m_powSpec(:,select)+eps);
%     plotyy(f,m_spec_deriv(test_index,:),f,norm_m_spec_deriv(test_index,:));hold on;
plotyy(f,m_spec_deriv(test_index,:),f,m_powSpec(test_index,select));hold on;
    plot(1/quefrency(m_Pitch(test_index))*[1:5;1:5], [ylim],'k--');
    %         plot(f,m_powSpec(test_index,select),'b');
    subplot(3,1,3);
    %     plot(abs(Cepstrum(test_index,:)).^2);hold on;
    
    plot(qt*1000,x(test_index,:),'r');xlabel('ms');
    hold on;
    plot(qt(m_Pitch(test_index))*1000,m_PitchGoodness(test_index),'ro');
    pause;
end

m_Pitch(find(m_PitchGoodness<1))=1;
Pitch_chose= 1./qt(m_Pitch);
m_Pitch= 1./qt(m_Pitch);


index_m_freq=find(Pitch_chose>param.pitch_HoP | (m_PitchGoodness<param.gdn_HoP & m_Entropy>param.up_wiener));
Pitch_chose(index_m_freq)=m_frequency(index_m_freq);
Pitch_weight=Pitch_chose.*m_PitchGoodness./sum(m_PitchGoodness);
% subplot(3,1,3);plot(Pitch_chose,'g-');hold on;axis tight;

m_FM=m_FM*180/pi;

% size(m_spec_deriv)
% size(index)
mm_spec_deriv(index,:) =m_spec_deriv;
mm_AM(index)         =m_AM;
mm_FM(index)         =m_FM;
mm_Entropy(index)    =m_Entropy; 
mm_amplitude(index)  =m_amplitude;
mm_frequency(index)  =m_frequency;
mm_PitchGoodness(index)=m_PitchGoodness;
mm_Pitch(index)       =m_Pitch; 
mm_Pitch_chose(index) =Pitch_chose; 
mm_Pitch_weight(index) =Pitch_weight;

end
