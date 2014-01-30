function [out,varargout]=TemplateMaker_subroutine_0p1(opt,varargin)
%  Template maker for KinkaChronic
%
%
%  by KH
global tmkr



switch opt
   case 'init'
        
       if nargin>=2
           tmkr=varargin{1};
           tmkr.template.amp_thresh=tmkr.pm.MotifThreshold;
       else
           tmkr.template.amp_thresh=0.1;
       end
     
       
       tmkr.template.feature_names={'amplitude_bias','entropy','pitch','m_FM','meanfreq'};
      
        
%         s{1}='amplitude_bias';
%         s{2}='entropy';
%         s{3}='pitch';
%         s{4}='m_FM';
%         s{5}='meanfreq';
        
        
        
        tmkr.template.TargetCode{1,1}=[1 0 0];
        tmkr.template.TargetCode{1,2}='o';
        tmkr.template.TargetCode{1,3}='target';

        tmkr.template.TargetCode{2,1}=[0 1 0];
        tmkr.template.TargetCode{2,2}='?';
        tmkr.template.TargetCode{2,3}='unknown';
        
        tmkr.template.TargetCode{3,1}=[0 0 1];
        tmkr.template.TargetCode{3,2}='x';
        tmkr.template.TargetCode{3,3}='Non-target';
        
        gph.template_figure_panel=feval(mfilename,'init_fig');
        out=gph.template_figure_panel;
       feval(mfilename,'reset_template');
        
       
    case 'init_fig'
        
        tmkr.gph.template_feature_fig=figure(17);clf;
        pos=get(0,'ScreenSize');
        pos=[pos(3)/4,pos(4)/8,pos(3)*0.7,pos(4)*0.8];
        set(tmkr.gph.template_feature_fig,'Name',mfilename,'Position',pos)
        
        tmkr.gph.template_figure_panel = uipanel('Position',[0 0  .9 1]);
       out=tmkr.gph.template_figure_panel;
       
        for ii=1:length(tmkr.template.feature_names)+1
            tmkr.gph.template_features_subfig_axes(ii)=mysubplot(length(tmkr.template.feature_names)+1,1,ii,1);
        set(tmkr.gph.template_features_subfig_axes(ii),'Parent',tmkr.gph.template_figure_panel);
        end
        
        postmp=get(tmkr.gph.template_features_subfig_axes(1),'Position');
        pos=[postmp(1)+postmp(3),postmp(2),postmp(1)/20,postmp(4)];
        tmkr.gph.amp_slider=uicontrol('Style', 'slider',...
            'Parent',tmkr.gph.template_figure_panel,...
            'Unit','Normalized',...
            'value', tmkr.template.amp_thresh,...
            'Max',  1,...
            'Min',  0,...
            'Position',pos,...
            'Callback', 'TemplateMaker_subroutine_0p1(''set_amp_slider'');');
        
        postmp=pos;
        tmkr.gph.amp_edit=uicontrol('Style', 'edit',...
            'Parent',tmkr.gph.template_figure_panel,...
            'Unit','Normalized',...
            'String', num2str(tmkr.template.amp_thresh),...
            'Position',pos+[pos(3), 0, pos(3)*10,-pos(4)*0.75],...
            'Callback', 'TemplateMaker_subroutine_0p1(''set_amp_edit'');');
    
        
        tmkr.gph.template_ui_panel     = uipanel('Position',[.9 0 .1 1]);
        origin=[0 1 0 0]; dy=0.05; dh=0.04; dx=0.01;
      
        pos=origin+[dx -dy 1-2*dx, dh]; 
        uicontrol('Style', 'pushbutton','Parent',tmkr.gph.template_ui_panel,'String', 'play',...
            'Unit','Normalized','Position', pos,'Callback', 'TemplateMaker_subroutine_0p1(''play'');');
    
        pos=origin+[dx -2*dy 1-2*dx, dh]; 
        uicontrol('Style', 'pushbutton','Parent',tmkr.gph.template_ui_panel,'String', 'train template',...
            'Unit','Normalized','Position', pos,'Callback', 'TemplateMaker_subroutine_0p1(''train_template'');');
    
        pos=origin+[dx -3*dy 1-2*dx, dh]; 
        uicontrol('Style', 'pushbutton','Parent',tmkr.gph.template_ui_panel,'String', 'predict template',...
            'Unit','Normalized','Position', pos,'Callback', 'TemplateMaker_subroutine_0p1(''predict_template'');');
    
         pos=origin+[dx -4*dy 1-2*dx, dh]; 
        uicontrol('Style', 'pushbutton','Parent',tmkr.gph.template_ui_panel,'String', 'reset template',...
            'Unit','Normalized','Position', pos,'Callback', 'TemplateMaker_subroutine_0p1(''reset_template'');');
        
        pos=origin+[dx -5*dy 1-2*dx, dh]; 
        uicontrol('Style', 'pushbutton','Parent',tmkr.gph.template_ui_panel,'String', 'save template',...
            'Unit','Normalized','Position', pos,'Callback', 'TemplateMaker_subroutine_0p1(''save_template'');');
    
            pos=origin+[dx -6*dy 1-2*dx, dh]; 
        uicontrol('Style', 'pushbutton','Parent',tmkr.gph.template_ui_panel,'String', 'load template',...
            'Unit','Normalized','Position', pos,'Callback', 'TemplateMaker_subroutine_0p1(''load_template'');');
        
               pos=origin+[dx -8*dy 1-2*dx, dh]; 
        uicontrol('Style', 'pushbutton','Parent',tmkr.gph.template_ui_panel,'String', 'load song',...
            'Unit','Normalized','Position', pos,'Callback', 'TemplateMaker_subroutine_0p1(''load_song'');');
    
    case 'load_song'  
        
        if nargin>=3
            tmkr.pm.song = varargin{1};
            tmkr.pm.Fsong= varargin{2};
            tmkr.pm.filename=varargin{3};
        else
            
            
            try
                [tmkr.pm.filename,tmkr.pm.sound_dir] = uigetfile({'*.wav';fullfile(tmkr.pm.sound_dir,tmkr.pm.filename)}, 'Pick a song (.wav) file');
            catch % In case no wave file is chosen.
                [tmkr.pm.filename,tmkr.pm.sound_dir] = uigetfile('*.wav', 'Pick a song (.wav) file');
                %             error([mfilename, ': Please chose a .wav file.']);
            end
            
            
            [tmkr.pm.song,Fsong]=wavread(fullfile(tmkr.pm.sound_dir,tmkr.pm.filename));
            if round(tmkr.pm.Fsong)~=round(Fsong)
                fprintf('Resampling from %d to %d\n',Fsong,tmkr.pm.Fsong);
                tmkr.pm.song=resample(tmkr.pm.song,tmkr.pm.Fsong,Fsong);
            end
            
            [tmkr.pm.feature.m_spec_deriv , ...
                tmkr.pm.feature2.m_AM,...
                tmkr.pm.feature2.m_FM ,...
                tmkr.pm.feature2.entropy ,...
                tmkr.pm.feature2.amplitude ,...
                tmkr.pm.feature2.meanfreq, ...
                tmkr.pm.feature2.pgood , ...
                tmkr.pm.feature2.pitch ,...
                tmkr.pm.feature2.Pitch_chose ,...
                tmkr.pm.feature2.Pitch_weight ]=sam_spectrum_deriv5(tmkr.pm.song,tmkr.pm.Fsong,'parameters_for_buffer_rec_mode_01p2');
            
            tmkr.pm.feature2.t=linspace(0,length(tmkr.pm.song)/tmkr.pm.Fsong,size(tmkr.pm.feature.m_spec_deriv,1)+1);
            tmkr.pm.feature2.t=tmkr.pm.feature2.t(1:end-1);
            tmkr.pm.feature2.f=tmkr.pm.Fsong*(1:size(tmkr.pm.feature.m_spec_deriv ,2))/1024;
        end
        
         feval(mfilename,'draw_sonogram_features',tmkr.template.amp_thresh);
    case 'train_template'
        feval(mfilename,'update_target_vector');
        train_label=[ones(length(tmkr.template.target_data),1);-ones(length(tmkr.template.nontarget_data),1)];
         tmkr.template.model.param = svmtrain(2*train_label-1,...
                [tmkr.template.target_data,tmkr.template.nontarget_data]', '-c 400 -g 0.01');
    
    case 'predict_template'
        
        tmkr.template.template_scaling_factor=std(tmkr.data(tmkr.pm.template_classify_dim_index,:),[],2);
        x=tmkr.template.tmp_feature([1:5,7:10],:)./repmat(tmkr.template.template_scaling_factor,1,length(tmkr.template.tmp_feature));
  
        [tmkr.template.predict_label, accuracy, dec_values] = svmpredict(randn(size(x,2),1),  ...
            x', tmkr.template.model.param); % test the training data
    
%         axes(tmkr.gph.template_features_subfig_axes(1));
        predicted_index=(tmkr.template.predict_label>0);
%         plot(tmkr.pm.feature2.t,predicted_index*max(ylim),'g');
        set(tmkr.gph.predicted_lines,'XData',tmkr.pm.feature2.t,...
            'YData',predicted_index*max(ylim));
        
    case 'reset_template'
        tmkr.template.target_data=[];
        tmkr.template.nontarget_data=[];
        tmkr.template.template_scaling_factor=std(tmkr.data(tmkr.pm.template_classify_dim_index,:),[],2);
        tmkr.template.use_filenames=cell(1);
        tmkr.template.model.param=[];
    case 'save_template'
         [savename, pathname] = uiputfile( ...
                    {'*.mat', 'MAT-file (*.mat)'},...
                    'SELECT a file to save a template model');
                model=tmkr.template.model;
                scaling_factor=tmkr.template.template_scaling_factor;
%                 tmkr.template.SamplingFreq=
                template_loaded=tmkr.template;
                save(fullfile(pathname,savename),'model','scaling_factor','template_loaded');
    case 'load_template'
            [loadname, pathname] = uigetfile( ...
                    {'*.mat', 'MAT-file (*.mat)'},...
                    'SELECT a file to load a template model');
                
                load(fullfile(pathname,loadname),'model','scaling_factor');
                tmkr.template.model=model;
                tmkr.template.template_scaling_factor=scaling_factor;
                
    case 'play'
        tt=get(tmkr.gph.template_features_subfig_axes(1),'XLim');
        tti=ceil(tt*tmkr.pm.Fsong)+1;
        
        tti(1)=max(1,tti(1));  % start index > 1.
        tti(2)=min(length(tmkr.pm.song),tti(2)); % end index < length(song)
        
        % sound(ss.song(tti(1):tti(2)),ss.F);
        
        sound(tmkr.pm.song(tti(1):tti(2))/(8*std(tmkr.pm.song)),tmkr.pm.Fsong);
        
    case 'draw_sonogram_features'
        
        if nargin>=2
            tmkr.template.amp_thresh=varargin{1};
        else
            tmkr.template.amp_thresh=0.1;
        end
       
        [tmkr.pm.feature2.m_spec_deriv , ...
            tmkr.pm.feature2.m_AM,...
            tmkr.pm.feature2.m_FM ,...
            tmkr.pm.feature2.entropy ,...
            tmkr.pm.feature2.amplitude ,...
            tmkr.pm.feature2.meanfreq, ...
            tmkr.pm.feature2.pgood , ...
            tmkr.pm.feature2.pitch ,...
            tmkr.pm.feature2.Pitch_chose ,...
            tmkr.pm.feature2.Pitch_weight ]=sam_spectrum_deriv5(tmkr.pm.song,tmkr.pm.Fsong,'parameters_for_buffer_rec_mode_01p2');
        
        tmkr.pm.feature2.t=linspace(0,length(tmkr.pm.song)/tmkr.pm.Fsong,size(tmkr.pm.feature2.m_spec_deriv,1)+1);
        tmkr.pm.feature2.t=tmkr.pm.feature2.t(1:end-1);
        tmkr.pm.feature2.f=tmkr.pm.Fsong*(1:size(tmkr.pm.feature2.m_spec_deriv ,2))/1024;
        amp_bias=70;
        tmkr.pm.feature2.amplitude_bias=tmkr.pm.feature2.amplitude+amp_bias;
        
        max_spec=max(tmkr.pm.feature2.m_spec_deriv(:));
        min_spec=min(tmkr.pm.feature2.m_spec_deriv(:));
        cutoff=0.001;
        
        axes(tmkr.gph.template_features_subfig_axes(1));cla;
        imagesc(tmkr.pm.feature2.t,tmkr.pm.feature2.f,tmkr.pm.feature2.m_spec_deriv');
        caxis(tmkr.gph.template_features_subfig_axes(1),cutoff*[-max_spec, max_spec]);
        colormap bone;
        set(tmkr.gph.template_features_subfig_axes(1),'YDir','Normal');
        
        [tmkr.template.tmp_feature,counter,tmkr.pm.feature2.start_ind,tmkr.pm.feature2.end_ind]=...
            feval(mfilename,'running_mean_var_of_features',tmkr.pm.feature2);
         tmkr.template.current_target_id=-ones(length(tmkr.pm.feature2.start_ind),1);
        feval(mfilename,'draw_sonogram_and_features',tmkr.template.tmp_feature,counter);
        feval(mfilename,'detect_motif',tmkr.pm.feature2.amplitude_bias,1);
        
    case 'running_mean_var_of_features'
        
        if nargin==2
            features=varargin{1};    
        else
            features=tmkr.pm.feature2;           
        end
        minbase=min(features.amplitude_bias);
        maxbase=max(features.amplitude_bias);
        
        tmkr.template.aboveind=(features.amplitude_bias>tmkr.template.amp_thresh);
        %
        counter=zeros(length(features.t),1);
        % init mean and the variance variables
        
        
        x=zeros(length(tmkr.template.feature_names),1);
        iterative_mean_var(x,'init');
        out=zeros(2*length(tmkr.template.feature_names),length(counter));
        up_ind=[];
        down_ind=[];
        for ii=1:length(counter)
            if tmkr.template.aboveind(ii)==0 % above threshold
                out(:,ii)=iterative_mean_var(0);
                counter(ii+1)=0;
                if counter(ii)~=0
                    down_ind=[down_ind,ii];
                end
            else            % above threshold
                counter(ii+1)=counter(ii)+1;
                if counter(ii)==0;
                    out(:,ii)=iterative_mean_var(0);
                    up_ind=[up_ind,ii];
                else
                    
                    for jj=1:length(tmkr.template.feature_names)
                        x(jj)=features.(tmkr.template.feature_names{jj})(ii);
                    end
                    out(:,ii)=iterative_mean_var(x);
                end
            end
            
        end
        
            
        counter=counter(1:end-1);

        
        if isempty(up_ind) || isempty(down_ind)
            px=[];
            py=[];
            duration=[];
            fprintf('No motif or syllable detected! (min amp=%g, max amp=%g, thresh=%g)\n',...
                min(features.amplitude_bias),...
                max(features.amplitude_bias),...
                tmkr.template.amp_thresh);        
                return;
        elseif length(up_ind)==1 && length(down_ind)==1
            fprintf('Single call detected, or syllable threshold is too small. \n')
            tmkr.pm.syllable=[];
            if up_ind(1)>down_ind(1)
                fprintf('Detected: up_ind(1)>down_ind(1)\n')   
                    return;
            end
        end
        
        % data start from above the threshold. This part is neglected.
        if up_ind(1)>down_ind(1)
            down_ind = down_ind(2:end);
        end
        
        % data end above threshold. This part is neglected.
        if up_ind(end)>down_ind(end)
            up_ind= up_ind(1:end-1);
        end
        
       
        varargout{1}=counter;
        varargout{2}=up_ind;
        varargout{3}=down_ind
   
        
        
    case 'draw_sonogram_and_features'
        
        out=varargin{1};
        counter=varargin{2};
        
        for jj=1:length(tmkr.template.feature_names)
            tmp_feature.(['m_' (tmkr.template.feature_names{jj})])= out(jj,:);
            tmp_feature.(['v_' (tmkr.template.feature_names{jj})])= out(length(tmkr.template.feature_names)+jj,:);
        end
        
        
        
%         tmkr.gph.template_features_subfig_axes=zeros(length(tmkr.template.feature_names)+1,1);
%         tmkr.gph.template_features_subfig_axes(1)=mysubplot(length(tmkr.template.feature_names)+1,1,1);
        max_spec=max(tmkr.pm.feature2.m_spec_deriv(:));
        min_spec=min(tmkr.pm.feature2.m_spec_deriv(:));
        cutoff=0.001;
        
        axes(tmkr.gph.template_features_subfig_axes(1));cla;
        imagesc(tmkr.pm.feature2.t,tmkr.pm.feature2.f,tmkr.pm.feature2.m_spec_deriv');
        caxis(tmkr.gph.template_features_subfig_axes(1),cutoff*[-max_spec, max_spec]);
        colormap bone;
        set(tmkr.gph.template_features_subfig_axes(1),'YDir','Normal');
        
        try delete(tmkr.gph.template_feature.mtf_Strt);end
        try delete(tmkr.gph.template_feature.mtf_End);end
        try delete(tmkr.gph.template_feature.mtf_Strt);end
        try delete(tmkr.gph.motifpatch_for_template_label);end
        
        tmkr.gph.template_mtf_axes=axes('Parent',tmkr.gph.template_figure_panel,'Position',get(tmkr.gph.template_features_subfig_axes(1),'Position'));
        tmkr.gph.template_feature.mtf_Strt    =plot(1,1,'Color',[1 0 0]);hold on;
        tmkr.gph.template_feature.mtf_End     =plot(1,1,'Color',[1 0 0]);
        tmkr.gph.predicted_lines              =plot(NaN,NaN,'Color',[0 1 0],'LineWidth',2);
        tmkr.gph.template_feature.mtf_region  = patch(0,0,'r');
        tmkr.gph.template_feature.amp          =plot(tmkr.pm.feature2.t,tmkr.pm.feature2.amplitude_bias,'Color',[0 1 0]);hold on;
        tmkr.gph.template_feature.amp_thresh   =plot([tmkr.pm.feature2.t(1),tmkr.pm.feature2.t(end)],...
            tmkr.template.amp_thresh(ones(1,2)),'Color',[0 1 0],'LineStyle','--');hold on;
        set(tmkr.gph.template_mtf_axes,'Visible','off');
        
        for ii=1:length(tmkr.template.feature_names)
            
            axes(tmkr.gph.template_features_subfig_axes(ii+1));cla;
%             tmkr.gph.template_features_subfig_axes(ii+1)=mysubplot(length(tmkr.template.feature_names)+1,1,ii+1,1);
               if ii==1,
                tmp=zeros(length(tmkr.pm.feature2.t),1);
                h(2)=stairs(tmkr.pm.feature2.t,counter,'g-'); hold on;
             else
                tmp=zeros(length(tmkr.pm.feature2.t),1);
                if ii==length(tmkr.template.feature_names),
                    xlabel('sec');
                else
                    set(tmkr.gph.template_features_subfig_axes(ii),'XTickLabel','');
                end
               end
            
            tmp(tmkr.template.aboveind)=tmkr.pm.feature2.(tmkr.template.feature_names{ii})(tmkr.template.aboveind);
                     
            h(2)=plot(tmkr.pm.feature2.t,tmp,'r.');hold on;grid on;
            h(4)=plot(tmkr.pm.feature2.t,tmp_feature.(['m_' tmkr.template.feature_names{ii}]),'r-');hold on;grid on;
            h(5)=plot_mean_conflimt(tmkr.pm.feature2.t,tmp_feature.(['m_' tmkr.template.feature_names{ii}]),sqrt(tmp_feature.(['v_' tmkr.template.feature_names{ii}])),'r');
            
            ylabel(tmkr.template.feature_names{ii});
            
        end
        
        
        
        linkaxes([tmkr.gph.template_features_subfig_axes(:);tmkr.gph.template_mtf_axes],'x');
        h=zoom;
        set(h,'Motion','horizontal','ButtonDownFilter',@myzoomcallback,'Enable','on');
   


    case 'detect_motif'
        
%         if nargin~=3
%             error('%s(%s,vector,threshold) requires 2 optional inputs!',mfilename,opt);
%         elseif nargin==3
%             x=varargin{1};
%             thresh=varargin{2};
%         end
% %         MinNoteLength=1; % ms
% %         MinPauseLength=0; % ms
%         LongestNoteLength=500; %ms
%         StimConductDelay = 40; %ms
% 
%         
%         sampF_spec=length(tmkr.pm.feature2.t)/(tmkr.pm.feature2.t(end)-tmkr.pm.feature2.t(1));
       
%         [up_ind,down_ind]=detect_thresholded_regions(...
%             x,...
%             thresh,...
%             MinNoteLength*sampF_spec/1000,...
%             LongestNoteLength*sampF_spec/1000,...
%             MinPauseLength*sampF_spec/1000);

            %         tmkr.pm.feature2.start_ind=up_ind;
            %         tmkr.pm.feature2.end_ind  =down_ind;
            up_ind=tmkr.pm.feature2.start_ind;
            down_ind=tmkr.pm.feature2.end_ind;
            
            if length(up_ind)>1
                tmkr.pm.MotifDetected=1;
            else % there is only one pause in the song, which is very likely to be noise.
                % fprintf('No motif or syllable detected!\n')
                tmkr.pm.MotifDetected=0;
            end
        
       
        
        axes(tmkr.gph.template_mtf_axes);
        ylim_tmp=get(tmkr.gph.template_mtf_axes,'YLim');
        maxy = max(ylim_tmp);
        miny=  min(ylim_tmp);
        px = [repmat(tmkr.pm.feature2.t(up_ind),2,1); NaN*ones(1,length(up_ind))];
        px = reshape(px,1,prod(size(px)));
        py = [repmat(ylim_tmp',1,length(up_ind)); NaN*ones(1,length(up_ind))];
        py = reshape(py,1,numel(py));
        
       
        
        set(tmkr.gph.template_feature.mtf_Strt,'XData',px,'YData',py);
        
        
        px = [repmat(tmkr.pm.feature2.t(down_ind),2,1); NaN*ones(1,length(down_ind))];
        px = reshape(px,1,numel(px));
        py = [repmat(ylim_tmp',1,length(down_ind)); NaN*ones(1,length(down_ind))];
        py = reshape(py,1,prod(size(py))); 
        
        set(tmkr.gph.template_feature.mtf_End,'XData',px,'YData',py);
          
        px = [tmkr.pm.feature2.t(up_ind); tmkr.pm.feature2.t(down_ind); tmkr.pm.feature2.t(down_ind);tmkr.pm.feature2.t(up_ind)];
        
       
        py = [maxy-0.2*diff(ylim_tmp)*ones(1,2), maxy,maxy]';
        py = repmat(py,1,size(px,2));
%         set(tmkr.gph.template_feature.mtf_region,'XData',px,'YData',py);

        
        show_target_label   =1;
        t_offset            =0.005;
        label_num_offset    =maxy-0.1*diff(ylim_tmp);
        font_size           =9;
       
        
        for ii=1:length(tmkr.pm.feature2.start_ind)
            userdata=[tmkr.pm.feature2.start_ind(ii), tmkr.pm.feature2.end_ind(ii)];
            tmkr.gph.motifpatch_for_template(ii)=patch(px(:,ii),py(:,ii),'b',...
                'FaceAlpha',0.5,...
                'ButtonDownFcn','TemplateMaker_subroutine_0p1(''Toggle_Target_or_Not'')',...
                'Tag','DoNotIgnore','UserData',[userdata,ii]);
            
            if (show_target_label)
                tmkr.gph.motifpatch_for_template_label(ii)=text(mean(px(:,ii))-t_offset,label_num_offset,'x',...
                    'FontSize',font_size);
                set(tmkr.gph.motifpatch_for_template_label(ii),...
                    'ButtonDownFcn','TemplateMaker_subroutine_0p1(''Toggle_Target_or_Not'')',...
                    'Tag','DoNotIgnore','UserData',[userdata,ii]);
            end
 
        end
    case 'Toggle_Target_or_Not'
        
        
        
        % [1 0 0]; RED,  target.
        % [0 1 0]; GREEN, not clear.
        % [0 0 1]; BLUE, Non-target.
        userdata    =get(gcbo,'UserData');
        id=userdata(3);
        LR=get(gcf,'SelectionType');
        switch LR
            case 'normal'
                d=1;
            case 'alt'
                d=-1;
            otherwise
                error;
        end
        color_target=get(tmkr.gph.motifpatch_for_template(id),'FaceColor');
        set(tmkr.gph.motifpatch_for_template(id),'FaceColor',circshift(color_target,[0,d]));
        color_target_now=get(tmkr.gph.motifpatch_for_template(id),'FaceColor');
        
        set(tmkr.gph.motifpatch_for_template_label(userdata(3)),'String',tmkr.template.TargetCode{find(color_target_now),2});
        % 1: target, 0; not defined, -1: non-target syllable.
        tmkr.template.current_target_id(id)=round(2-find(color_target_now));
        
    case 'update_target_vector'
        
        if isempty(strmatch(tmkr.pm.filename,strvcat(tmkr.template.use_filenames{:}),'exact'))
            tmkr.template.use_filenames={tmkr.template.use_filenames{:},tmkr.pm.filename};
        else
            disp('this file has already used')
            return;
        end
        tmp=feval(mfilename,'get_target_vector');
        tmkr.template.target_data= ...
            [tmkr.template.target_data,tmp];
        
         tmp=feval(mfilename,'get_nontarget_vector');
         tmkr.template.nontarget_data= ...
            [tmkr.template.nontarget_data,tmp];
        
          
    case 'get_target_vector'
        start_ind=tmkr.pm.feature2.start_ind(find(tmkr.template.current_target_id>0));
        end_ind=tmkr.pm.feature2.end_ind(find(tmkr.template.current_target_id>0));
        
        index=[];
        for ii=1:length(start_ind)
            tmpindex=start_ind(ii):end_ind(ii);
            index=[index,tmpindex(2:end-1)];
        end
        % number 6 is var_amplitude which is not used in classifytmkr.
    out=tmkr.template.tmp_feature([1:5,7:10],index)./repmat(tmkr.template.template_scaling_factor,1,length(index));
      
     case 'get_nontarget_vector'
        start_ind=tmkr.pm.feature2.start_ind(find(tmkr.template.current_target_id<0));
        end_ind=tmkr.pm.feature2.end_ind(find(tmkr.template.current_target_id<0));
        
        index=[];
        for ii=1:length(start_ind)
            tmpindex=start_ind(ii):end_ind(ii);
            index=[index,tmpindex(2:end-1)];
        end
        
        out=tmkr.template.tmp_feature([1:5,7:10],index)./repmat(tmkr.template.template_scaling_factor,1,length(index));
    
    case 'set_amp_slider'
        value=get(tmkr.gph.amp_slider,'Value');
        set(tmkr.gph.amp_edit,'String',num2str(value));
        tmkr.template.amp_thresh=value;
        feval(mfilename,'draw_sonogram_features',tmkr.template.amp_thresh);
    case 'set_amp_edit'
        
        value=str2double(get(tmkr.gph.amp_edit,'String'));
        set(tmkr.gph.amp_slider,'Value',value);
        tmkr.template.amp_thresh=value;
        feval(mfilename,'draw_sonogram_features',tmkr.template.amp_thresh);
        
         
    otherwise
        error('Unknown option (%s)!',opt);
end

   
     

function [flag] = myzoomcallback(obj,event_obj)
% If the tag of the object is 'DoNotIgnore', then return true.
objTag = get(obj,'Tag');
if strcmpi(objTag,'DoNotIgnore')
   flag = true;
else
   flag = false;
end
