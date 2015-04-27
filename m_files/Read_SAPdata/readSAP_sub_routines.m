function readSAP_sub_routines(opt,varargin)
% global data datatmp gph pm
global data gph pm

switch lower(opt)
    case 'update_datatmp'
       
        for ii=[1:9]
            evaltxt = sprintf('pm.cluster_val(%d)=get(gph.ui_cluster%d,''Value'');',ii,mod(ii,9));
            eval(evaltxt);
        end
        pm.cluster_val;
        pm.show_index=zeros(1,size(data,2));
        for ii=1:9
            if (pm.cluster_val(ii))
                 pm.show_index =pm.show_index|(data(pm.cluster_index,:)==mod(ii,9));
            end
        end
        datatmp = data(:,pm.show_index);
        feval(mfilename,'redraw_clusters');
        feval(mfilename,'init_cov_matrix');
        
    case {'show_syllable','show_transit_syllable'}
         try delete(gph.syllable_label);end
         try delete(gph.wavefile_text);end
         
         switch lower(opt)
             case 'show_syllable'
                 axes(gph.ax(1));
                 [xposi,yposi]=ginput(1);
                 datatmp=data(:,pm.show_index);
                 distance=(datatmp(pm.xind,:)-xposi).^2/var(datatmp(pm.xind,:))+...
                     (datatmp(pm.yind,:)-yposi).^2/var(datatmp(pm.yind,:));
                 
                 
                 
                 [mindistnace,pm.minind]=min(distance);
                 pm.show_sonogram_index=pm.show_index(pm.minind);
                 
                 pm.serial=datatmp(pm.serial_index,pm.minind);
                  pm.filename=return_filename(datatmp(:,pm.minind));
             case 'show_transit_syllable'
                 axes(gph.trans_mat_axes);
                 figure(2);
                 [xposi,yposi]=ginput(1);
                 xposi=round(xposi);                 yposi=round(yposi);
                 fprintf('Look for transition from syllable %d to %d',yposi,xposi);
                 pm.show_sonogram_index=pm.trans_matrix_serials{yposi,xposi};
                 pm.filename=return_filename(data(:,pm.show_sonogram_index(1)));
                  pm.serial=data(pm.serial_index,pm.show_sonogram_index(1));
             otherwise
                 error('Unknown option!')
                  
         end
         
      
        
       
        
%         axes(gph.sonogramAxes); cla(gph.sonogramAxes,'reset');    
        txt=strrep(sprintf('wavfile: %s',pm.filename),'_','\_');
        try
            [pm.song,pm.Fsong]=wavread([pm.filename,'.wav']);
        catch
            pm.filename;
            s=strsplit(pm.filename,'_');
            pm.filename=ls(sprintf('*%s*',s{2})); % just look for the ID number.
            pm.filename=pm.filename(1:end-4);
            txt=strrep(sprintf('wavfile: %s',pm.filename),'_','\_');
            if isvector(pm.filename)
                [pm.song,pm.Fsong]=wavread([pm.filename,'.wav']);
            else
                error('try reading %s, but failed!',[pm.filename,'.wav']);
            end
        end
        
        nfft = 1012;
        fftwindow=nfft;
        numoverlap=ceil(nfft/1.2);
%         [y,f,t,p]=spectrogram(pm.song,fftwindow,numoverlap,nfft,pm.Fsong);
%         logp=10*log10(abs(p));
%         set(gph.sonogramImg,'XData',t,'YData',f,'CData',logp);colormap(jet);
             
        m_spec_deriv=sam_spectrum_deriv(pm.song,pm.Fsong);
        max_spec=max(max(m_spec_deriv));
        min_spec=min(min(m_spec_deriv));
        cutoff=0.001;
        t=linspace(0,length(pm.song)/pm.Fsong,size(m_spec_deriv,1));
        f=pm.Fsong*(1:size(m_spec_deriv,2))*1000/1024;
         set(gph.sonogramImg,'XData',t,'YData',f,'CData',m_spec_deriv');colormap(bone);
         set(gph.sonogramAxes,'CLim',cutoff*[-max_spec, max_spec]);
          
        
        set(gph.sonogramAxes,'XLim',[min(t) max(t)],'YLim',[0 max(f)]);
%         imagesc(t,f,logp); set(gca,'YDir','Normal'); hold on;
        axes(gph.sonogramAxes);
        gph.wavefile_text=text(min(xlim)+0.01*diff(xlim),max(ylim)-0.1*diff(ylim),txt);
        axis tight;
       
        try delete([gph.syllable_start,gph.syllable_end]);end
        gph.syllable_start=line([data(pm.start_on_index,pm.show_sonogram_index(1)),...
            data(pm.start_on_index,pm.show_sonogram_index(1))]/1000,...
            ylim,[10 10],'Color','r','LineWidth',2);
        gph.syllable_end  =line(([data(pm.start_on_index,pm.show_sonogram_index(1)),...
            data(pm.start_on_index,pm.show_sonogram_index(1))]+...
            data(pm.duration_index,pm.show_sonogram_index(1)))/1000,ylim,'Color','r','LineWidth',2);
        
        ind = ceil(pm.Fsong*data(pm.start_on_index,pm.show_sonogram_index(1))/1000)+[0:ceil(pm.Fsong*data(pm.duration_index,pm.show_sonogram_index(1))/1000)];
        sound(pm.song(ind),pm.Fsong);
        feval(mfilename,'init_feature_button');
        feval(mfilename,'show_classification');
        
    case 'play_wholesong'
        Cs=get(gph.syllable_start,'Color');
        Ce=get(gph.syllable_end,'Color');
        
        tt=get(gph.sonogramAxes,'XLim');
        tti=ceil(tt*pm.Fsong)+1;
        
        tti(1)=max(1,tti(1));  % start index > 1.
        tti(2)=min(length(pm.song),tti(2)); % end index < length(song)
        
        % sound(ss.song(tti(1):tti(2)),ss.F);
        
        sound(pm.song(tti(1):tti(2)),pm.Fsong);
        
%         sound(pm.song,pm.Fsong);
        
        pause(data(pm.start_on_index,pm.show_sonogram_index)/1000-tti(1)/pm.Fsong);
        set(gph.syllable_start,'Color','k');
        set(gph.syllable_end,'Color','k');
        pause(data(pm.duration_index,pm.show_sonogram_index)/1000);
        set(gph.syllable_start,'Color',Cs);
        set(gph.syllable_end,'Color',Ce);
        
    case 'play_syllable'
        ind = ceil(pm.Fsong*data(pm.start_on_index,pm.show_sonogram_index)/1000)+[0:ceil(pm.Fsong*data(pm.duration_index,pm.show_sonogram_index)/1000)];
        sound(pm.song(ind),pm.Fsong);
        
    case 'show_classification'
        axes(gph.sonogramAxes);
        %         pm.serial=datatmp(pm.serial_index,pm.minind);
%         datatmp=data(:,pm.show_index);
        pm.same_serial_index = find(data(pm.serial_index,:)==pm.serial);
        try delete(gph.syllable_label);end
        try delete(gph.syllable_line);end
        gph.syllable_label=zeros(1,length(pm.same_serial_index));
        gph.syllable_line =zeros(1,length(pm.same_serial_index));
        
        for ii=1:length(pm.same_serial_index)
          x = [data(pm.start_on_index,pm.same_serial_index(ii)),...
              data(pm.start_on_index,...
              pm.same_serial_index(ii))+data(pm.duration_index,pm.same_serial_index(ii))]/1000;
          gph.syllable_line(ii)=line(x,[0 0],'Color','c','LineWidth',3,...
                 'ButtonDownFcn','readSAP_sub_routines(''return_feature_2D_posi'')',...
                    'UserData',pm.same_serial_index(ii));
          cluster=data(pm.cluster_index,pm.same_serial_index(ii));
          if (cluster>0)
              c = pm.CS(cluster,:);
          else
              c=[0 0 0];
          end
          gph.syllable_label(ii)=text(mean(x),-0.15*diff(ylim),num2str(cluster),'Color',c);
        end
    case 'chk_xaxis_button'  
        pm.xname=get(get(gph.ui_xbuttonG,'selectedobject'),'String');
        feval(mfilename,'redraw_clusters');
    case 'chk_yaxis_button'  
        pm.yname=get(get(gph.ui_ybuttonG,'selectedobject'),'String');
        feval(mfilename,'redraw_clusters');
    case 'redraw_clusters'
        xlim_now=xlim;
        ylim_now=ylim;
        pm.xind = strmatch(pm.xname,pm.names);
        pm.yind = strmatch(pm.yname,pm.names);
        cla(gph.ax(1),'reset');        axes(gph.ax(1));
%         gph.ax(1)=axes('Position',[.1 .6 .7 .3]);
        pm.show_index=zeros(1,size(data,2));
        
        for ii=1:9
            if (pm.cluster_val(ii))
                pm.show_index =pm.show_index|(data(pm.cluster_index,:)==mod(ii,9));
            end
        end
        
        pm.show_index=find(pm.show_index);
        
        for ii=9:-1:1
            if (pm.cluster_val(ii))
                show_index=data(pm.cluster_index,:)==mod(ii,9);
                datatmp=data(:,show_index);
                h=plot(datatmp(pm.xind,:),datatmp(pm.yind,:),'ko','MarkerSize',2);hold on;
                  if (mod(ii,9)==0)
                      CSnow=[0 0 0];
                  else
                      CSnow = pm.CS(ii,:);
                  end
                  set(h,'MarkerFaceColor',CSnow,'MarkerEdgeColor','none');
            end
            
%             pm.plotind = find(datatmp(pm.cluster_index,:)==cluster_ID(ii));
%             if (cluster_ID(ii)==0)
%                 CSnow=[0 0 0];
%             else
%                 CSnow = pm.CS(cluster_ID(ii),:);
%             end
%             h=plot(datatmp(pm.xind,pm.plotind),datatmp(pm.yind,pm.plotind),'ko','MarkerSize',2);hold on;
%             %              h=plot(data(pm.xind,pm.plotind),data(pm.yind,pm.plotind),'k.');hold on;
%             set(h,'MarkerFaceColor',CSnow,'MarkerEdgeColor','none');
        end
%         axis([xlim_now ylim_now]);
        xlabel(strrep(pm.xname,'_','\_'));ylabel(strrep(pm.yname,'_','\_'));
        
      try
        gph.selected_note_posi=plot(data(pm.xind,gph.selected_note_index),...
            data(pm.yind,gph.selected_note_index),'ro','MarkerSize',5);
      catch
          disp('!')
      end
      
     case 'redraw'
         axis tight;
    case 'load_feature'
        
       
        pm.feature_loadname=pm.filename;
        bindata=fopen(fullfile(pm.feature_dir,[pm.feature_loadname,'.dat']));
        
        if (bindata<0)
            error('%s does not exist!',loadname);
        end
        
        % read the feature file. Get the meaturements of the amplitude, mean
        % frequency, pitch, entropy, goodness of pitch of the wave file.
        u=1;
        pm.feature=[];
        
        while(~feof(bindata))
            
            tmp=fread(bindata,1,'int16=>int',2);
            if (length(tmp))
                pm.feature.amplitude(u)=double(tmp);
            end
            
            tmp=fread(bindata,1,'int8=>int');
            if (length(tmp))
                pm.feature.meanfreq(u)=43*(double(tmp)+120);
            end
            
            tmp=fread(bindata,1,'int8=>int');
            if (length(tmp))
                pm.feature.pitch(u)=43*(double(tmp)+120);
            end
            
            tmp=fread(bindata,1,'int16=>int',2);
            if (length(tmp))
                pm.feature.entropy(u)=double(tmp)/100;
            end
            
            tmp=fread(bindata,1,'int16=>int');
            if (length(tmp))
                pm.feature.pgood(u)=double(tmp)/10;
            end
            
            if (length(tmp)&((pm.feature.pgood(u)<100 & pm.feature.entropy(u)<-2)| pm.feature.pitch(u)>1800))
                pm.feature.pitch(u)=pm.feature.meanfreq(u);
            end
            
            u=u+1;
        end
        fclose(bindata);
     % The default FFT window size is 9.27ms, so the start point of the
     % feature time is 9.27/2ms.  The last time point is also true T in
     % song amplitude minus 9.27/2.
     dt=9.27/2/1000;
        pm.feature.t=linspace(dt,length(pm.song)/44100-dt,length(pm.feature.amplitude));
    case 'init_feature_button'
         
        lf=length(pm.feature_names);
         for ii=1:lf
            s=['ui_featurebutton',num2str(ii)];
            set(gph.(s),'Value',0);
         end
        feval(mfilename,'chk_feature_button');
        
    case 'chk_feature_button'
        
    
        if isempty(strmatch(pm.filename,pm.feature_loadname))
            feval(mfilename,'load_feature');
        end
     
        lf=length(pm.feature_names);
        val=zeros(lf,1);
        for ii=1:lf
            s=['ui_featurebutton',num2str(ii)];
            val(ii)=get(gph.(s),'Value');
        end
        ymax=max(get(gph.sonogramAxes,'YLim'));
        for ii=1:lf
            if val(ii)
                tmp=pm.feature.(pm.feature_names{ii});
                tmpmax=max(tmp);
                tmpmin=min(tmp);
                tmp=(tmp-tmpmin)/(tmpmax-tmpmin); % now [0,1];
                tmp=tmp*ymax;
                set(gph.sonogram_feature_plots(ii),'XData',pm.feature.t,'YData',tmp);
            else
               set(gph.sonogram_feature_plots(ii),'XData',NaN,'YData',NaN);
 
            end
        end
    case 'init_cov_matrix'
        % for the syllable detection, we use only
        % duration, mean_pitch, mean_FM,mean_entropy,mean_gpitch.
        
        pm.covM=zeros(length(pm.mahl_index));
        
        mean_val=mean(data(pm.mahl_index,pm.show_index),2);
        for ii=1:length(pm.show_index)
            tmp=data(pm.mahl_index,pm.show_index(ii))-mean_val;
            pm.covM=pm.covM+(tmp)*(tmp)';
        end
        pm.covM=pm.covM/length(pm.show_index);
        pm.invcovM=inv(pm.covM);
    case 'init_feature_vector'
        % calculate the mean feature vector of each syllables.
        % duration, mean_pitch, mean_FM,mean_entropy,mean_gpitch.
     
      pm.feature_vector=zeros(length(pm.mean_feature_index),9);
        for ii=1:9
                 index = (data(pm.cluster_index,:)==mod(ii,9));
                 tmp=data(pm.mean_feature_index,index);
                 pm.feature_vector(:,ii)=mean(tmp,2);
        end
        
    case 'auto_classify'
        
        if nargin>=2
            mode=varargin{1};
        else
            mode='show_gui';
        end
        
        if strmatch(mode,'nogui_mode')
            no_gui=1;
        else
            no_gui=0;
        end
%         fprintf('Calculating Mahalanobis distance...\n');
        
        for ii=1:length(pm.same_serial_index)
            feature = data(pm.mahl_index,pm.same_serial_index(ii));
            cluster=data(pm.cluster_index,pm.same_serial_index(ii));
            
            MahalDist=zeros(length(pm.show_index),1);
            
            if (cluster==0)
                %             dx=(repmat(feature,1,length(pm.show_index))-data(pm.mean_feature_index,pm.show_index));
                for jj=1:length(pm.show_index)
                    dx=feature-data(pm.mahl_index,pm.show_index(jj));
                    MahalDist(jj)=dx'*pm.invcovM*dx;
%                     MahalDist(jj,2)=data(pm.cluster_index,pm.show_index(jj));
                end
                MahalDist;
                [MahalDist,I] = sort(MahalDist,1,'ascend');
                % take the 10% of the data and its index.
                c=floor(.01*length(pm.show_index));
                nb_clust=data(pm.cluster_index,pm.show_index(I(1:c))); % nearby clusters.
                nb_clust=nb_clust(nb_clust~=0); % pick up classified ones.
                N_nb_clust=hist(nb_clust,[1:8]);
                [max_N_nb_clust,max_nb_clust]=sort(N_nb_clust,'descend');
                
                %                 max_nb_clust
                if ~(no_gui)
                    set(gph.syllable_label(ii),'String',num2str(max_nb_clust(1)),...
                        'ButtonDownFcn','readSAP_sub_routines(''manual_change_cluster'')',...
                        'UserData',[pm.same_serial_index(ii),ii,max_nb_clust]);
                end
                data(26,pm.same_serial_index(ii))=max_nb_clust(1);
            else
                data(26,pm.same_serial_index(ii))=data(pm.cluster_index,pm.same_serial_index(ii));
            end
            
        end
      case 'auto_classify_all'
          unique_serials=unique(data(2,:));
          
          data(26,:)=zeros(1,size(data,2));
          try
              h = waitbar(0,'Classifying notes...');
              
              for ii=1:length(unique_serials)
                  pm.same_serial_index = find(data(pm.serial_index,:)==unique_serials(ii));
                  feval(mfilename,'auto_classify','nogui_mode');
                  waitbar(ii/length(unique_serials),h);
              end
              
              close(h)
          catch
              close(h)
          end

    case 'parse_autoclassified_notes'
         unique_serials=unique(data(2,:));
         
         pm.trans_matrix=zeros(10);
         pm.trans_matrix_serials=cell(10);
         
         for ii=1:length(unique_serials)
             pm.same_serial_index = find(data(pm.serial_index,:)==unique_serials(ii));
             tmp=data(26,pm.same_serial_index);
             
             for jj=1:length(pm.same_serial_index)-1
                 ISI=data(pm.start_on_index,pm.same_serial_index(jj+1))-data(pm.start_on_index,pm.same_serial_index(jj))-...
                     data(pm.duration_index,pm.same_serial_index(jj));
                 if ISI<200 % if note-note interval is more than 200ms, define the end of the song.
                     pm.trans_matrix(tmp(jj),tmp(jj+1))=ceil(pm.trans_matrix(tmp(jj),tmp(jj+1))+1);
                     pm.trans_matrix_serials{tmp(jj),tmp(jj+1)}=[pm.trans_matrix_serials{tmp(jj),tmp(jj+1)},...
                         pm.same_serial_index(jj)];
                 else
                     pm.trans_matrix(tmp(jj),10)=ceil(pm.trans_matrix(tmp(jj),10)+1);
                     pm.trans_matrix_serials{tmp(jj),10}=[pm.trans_matrix_serials{tmp(jj),10}, ...
                         pm.same_serial_index(jj)];

                 end
                              end
             pm.trans_matrix(tmp(end),10)=ceil(pm.trans_matrix(tmp(end),10)+1);
             pm.trans_matrix_serials{tmp(end),10}=[pm.trans_matrix_serials{tmp(end),10}, pm.same_serial_index(end)];
             
         end
              
         sumP=sum( pm.trans_matrix,2);
         pm.Ntrans_matrix=pm.trans_matrix./repmat(sumP,1,size(pm.trans_matrix,2));
         pm.Nrepeat_prob=diag(pm.Ntrans_matrix);
         
        for ii=1:size(pm.Ntrans_matrix)
            pm.Ntrans_matrix(ii,ii)=0;
        end
        
    case 'show_trans_matrix'
        figure(2);clf;
        
        gph.ui_Transmat_panel = uipanel('visible','on','Position',[0.1 .1 .8 .8]);
        gph.trans_mat_axes=axes('Position',[0 0 .98 .98],'Parent',gph.ui_Transmat_panel);
        gph.trans_mat_IMG=imagesc(pm.Ntrans_matrix);
        uicontrol('Style', 'pushbutton','String', 'show syllable','Parent',gph.ui_Transmat_panel,...
            'Unit','Normalized','Position', [0 1 .15 .1],...
            'Callback', 'readSAP_sub_routines(''show_transit_syllable'');');

        
        
        
        
        
     case 'return_feature_2d_posi'
         try delete(gph.selected_note_posi); end;
         gph.selected_note_index=get(gcbo,'UserData');
         axes(gph.ax(1));
        gph.selected_note_posi=plot(data(pm.xind,gph.selected_note_index),...
            data(pm.yind,gph.selected_note_index),'ro','MarkerSize',5);
        
    case 'manual_change_cluster'
        tmp=get(gcbo,'UserData');
        fprintf('This cluster (%dth note) has neighbors:',tmp(2));
        fprintf('%d ',tmp(3:end));fprintf('\n');
        
        gph.change_note_index=tmp(1);
        gph.syllable_label_tag=tmp(2);
        
        Units = get(gcbo,'Units'); set(gcbo,'Units','Normalized');
        posi=get(gcbo,'Extent');  set(gcbo,'Units',Units);
        parent_posi=get(get(gcbo,'Parent'),'Position');
        o=parent_posi([1:2]); dx=parent_posi(3);dy=parent_posi(4);
        posi= o+[posi(1)*dx,posi(2)*dy];
        posi=[posi .03 .03];
        gph.uieditnow=uicontrol('Style', 'edit','String', get(gcbo,'String'),...
    'Unit','Normalized','Position',posi,'Callback', 'readSAP_sub_routines(''enter_cluster_number'');');
    waitfor(gph.uieditnow);
    case 'enter_cluster_number'
        
        str=get(gph.uieditnow,'String');
        set(gph.syllable_label(gph.syllable_label_tag),'String',str);
        delete(gph.uieditnow);
        
    case ''
        
        str=get(gph.uieditnow,'String');
        set(gph.syllable_label(gph.syllable_label_tag),'String',str);
        delete(gph.uieditnow);
        
        
    otherwise
        error('Unknown option')
end