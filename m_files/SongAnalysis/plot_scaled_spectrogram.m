function out = plot_scaled_spectrogram(opt,varargin)
% Print spectrogram
% by KH
% 2013/10/21

global specplot

if nargin==0
    opt= 'plot';
end

switch opt
    case 'plot'
        %% Load a file
        try
            [specplot.filename, specplot.pathname] = uigetfile( ...
                fullfile(specplot.pathname,specplot.filename), ...
                'Pick a file');
        catch
            
            [specplot.filename, specplot.pathname] = uigetfile( ...
                {'*.wav';'*.mat';'*.*'}, ...
                'Pick a file');
        end
        %%
        
        if strncmpi(specplot.filename(end-3:end),'.wav',4)
            [mic,Fs]=wavread(fullfile(specplot.pathname,specplot.filename));
        elseif strncmpi(filename(end-4:end),'.mat',4)
            rsd = realsong_dataclass(fullfile(specplot.pathname,specplot.filename));
            mic=rsd.mic;
            Fs = rsd.Fs;
        end
        
        %
        [B,A]=ellip(4,.1,50,[800 22000]/44100);
        mic=filtfilt(B,A,mic');
        
        myfigure('Specgrogram');clf;
        [S,f_spec,t_spec,P] = spectrogram(mic,1024,1024-32,4096,Fs);
        m_spec_deriv=10*log10(abs(S));
        
        color_mapping='jet';
        cutoff=[0.8 0.2; 0 .99];
        
        max_spec=max(max(m_spec_deriv));
        min_spec=min(min(m_spec_deriv));
        median_spec=median(median(m_spec_deriv))
        
        
        
        imagesc(t_spec,f_spec,m_spec_deriv);hold on;
        specplot.spectrogram=gca;
        set(specplot.spectrogram,'CLim',cutoff*[median_spec,max_spec]','YDir','Normal');
        colormap(color_mapping);
        axis([xlim,[0 10000]]);
        
        pos=get(gca,'Position');
        clim = get(gca,'CLim');
        
        dx=0.01; dy = 0.01; dw = 0.05; dh =0.05;
        pos_slider1=[pos(1)+pos(3),pos(2), dx,pos(4)];
        Callbacktxt=sprintf('feval(''%s'',''slider_caxis_change'');',mfilename);
        
        specplot.slider_caxis_min= uicontrol('Style','slider',...
            'Unit','normalized',...
            'Position',pos_slider1,'Callback',Callbacktxt,...
            'Min', max(min_spec,-50),...
            'Max',min(max_spec,50),...
            'Value',clim(1));
        
        
        pos_slider1=pos_slider1+[dx 0 0 0];
        Callbacktxt=sprintf('feval(''%s'',''slider_caxis_change'');',mfilename);
         specplot.slider_caxis_max= uicontrol('Style','slider',...
            'Unit','normalized',...
            'Position',pos_slider1,'Callback',Callbacktxt,...
            'Min', max(min_spec,-50),...
            'Max',min(max_spec,50),'Value',clim(2));
        
        pos_print=[pos(1),pos(2)+pos(4),dw,dh ];
        Callbacktxt=sprintf('feval(''%s'',''scaled_print'');',mfilename);
         specplot.spec_print= uicontrol('Style','pushbutton',...
             'String','Print',...
            'Unit','normalized',...
            'Position',pos_print,'Callback',Callbacktxt);
        
    case 'scaled_print'
        
%         set(specplot.spectrogram,'XTickLabel',[],'YTickLabel',[]);
        
        XTickLabel=get(specplot.spectrogram,'XTickLabel');
        YTickLabel=get(specplot.spectrogram,'YTickLabel');
%         set(specplot.spectrogram,'XTickLabel',[],'YTickLabel',[]);
       
        savename =fullfile( specplot.pathname, specplot.filename);
        savename = [savename(1:end-4),sprintf('t=[%2.2f_%2.2f]',min(xlim),max(xlim))];
           
         [savename, pathname] = uiputfile( ...
         [savename,'.png'], ...
        'Print as PNG and EPS');
        
         savename = fullfile(pathname,savename(1:end-4));
       
        fprintf('Print in %s.\n',savename);
        scaled_print2(gcf,xlim,'-dpng','-noui',[savename,'.png']);
        scaled_print2(gcf,xlim,'-depsc2','-noui',[savename,'.eps']);
        
        set(specplot.spectrogram,'XTickLabel',XTickLabel,'YTickLabel',YTickLabel);
    
    
    case 'slider_caxis_change'
        
        
%         clim=get(specplot.spectrogram,'CLim');
        cmin=get(specplot.slider_caxis_min,'Value');
        cmax=get(specplot.slider_caxis_max,'Value');
        crange=[cmin,cmax];
        set(specplot.spectrogram,...
            'CLim',crange);
%         
    otherwise
        error('Unknown optiont %s!',opt)
end