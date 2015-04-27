% pwd_now=pwd;
% sql_dir='C:\mysql\data\mysql\';
% cd(sql_dir);
% %             s=sprintf('%s.MYD',[sap.SAPtablename,'_x']);
% [load_table_names, pathname] = uigetfile( ...
%     {[s,';*.MYD;*.myd']; '*.*'},...
%     'SELECT tables to load classified data',...
%     'MultiSelect', 'on');
% cd(pwd_now);
% 
load_table_names=[];
load_table_names{1}='pur820m_20100506_undir_saline_day1_x.MYD';
load_table_names{2}='pur820m_20100507_undir_10mmbmi_day2_x.MYD';
load_table_names{3}='pur820m_20100508_undir_saline_day3_x.MYD';

load_table_names=[];
load_table_names{1}='or811m_20100426_undir_saline_day5_x.MYD';
load_table_names{2}='or811m_20100427_undir_bmi10mm_day6_x.MYD';
load_table_names{3}='or811m_20100428_undir_before_day7_1_x.MYD';

% load_table_names{4}='pur820m_20100512_undir_5mmmuscimol_day7_x.MYD';
% % 
% load_table_names=[];
% load_table_names{1}='sil827m_20100516_saline_day2_x.MYD';
% load_table_names{2}='sil827m_20100517_10mMBMI_day3_x.MYD';
% load_table_names{3}='sil827m_20100518_saline_day4_x.MYD';
% bout_dur_dirnames{3}='C:\home\LabVIEW\data\or811m\20100428_UnDir_before_day7_1_feature';
% 

% 
% prompt={'which cluster to load?'};
% name='load one cluster from a database';
% numlines=1;
% defaultanswer={'1'};
% 
% which_cluster=inputdlg(prompt,name,numlines,defaultanswer);
% which_cluster=str2num(which_cluster{1});

which_cluster=[1:5];

% init parameters
hist_edges=[];
histdata=struct;
legend_h=[];
legend_h2=[];


list_of_features={'duration','mean_pitch','mean_FM','mean_entropy','mean_goodness_of_pitch','var_entropy'}
% n=listdlg('PromptString','Select features to plot (at maximum three)','ListString',list_of_features);
% n=4;
% features_to_read=list_of_features(n);
% features_to_read={'duration'};hist_edges=linspace(0,400,101);
% features_to_read={'mean_FM'};hist_edges=linspace(0,50,51);
% features_to_read={'mean_entropy','mean_amplitude'};
features_to_read={'mean_entropy'};hist_edges=linspace(-3.0,0,51);
% features_to_read={'var_entropy'};hist_edges=linspace(0,4,51);

figure(20);setPaperSize([7,7]);clf;
ColOrder={'b','r','g','c'};
list_of_feature_labels=strrep(features_to_read,'_','\_');
gph_axes(1)=mysubplot(1,1,1,1,[.8,.8]);


figure(21);setPaperSize([7,7]);clf;
gph_axes(2)=mysubplot(1,1,1,1,[.8,.8]);
savedir= 'C:\home\Platex\MyPaper\EffCopy_Project2008\Figs_ver3\'
savename=sprintf('bird=%s_%s_%d_hist',load_table_names{1}(1:7),features_to_read{1},which_cluster);



n_features_to_read=length(features_to_read);


for ss=1:length(load_table_names)
    [data,colname]=return_features_from_database(load_table_names{ss},which_cluster);
  c=[ColOrder{ss},'.'];
%   c2=[ColOrder{ss}];
    if n_features_to_read==1
        axes(gph_axes(1));
        ind1=strmatch(features_to_read{1},colname);
        %         plot(ss+rand(length(data(ind1,:)),1)/2-0.75,data(ind1,:),c); hold on;
        legend_h(ss)=plot(ss+linspace(-0.5,0.5,length(data(ind1,:)))-0.5,data(ind1,:),c); hold on;
        ylabel(list_of_feature_labels(1));
        errorbar(ss-0.5,mean(data(ind1,:)),std(data(ind1,:))/sqrt(length(data(ind1,:))),'Color','k')
        %             plot(1:length(data(ind1,:)),data(ind1,:),'k.');
        
        axes(gph_axes(2));
        histdata(ss).histN=histc(data(ind1,:),hist_edges);
        
        legend_h2(ss)=stairs(hist_edges,histdata(ss).histN/sum(histdata(ss).histN),c(1));hold on;
        
    elseif  n_features_to_read==2
        ind1=strmatch(features_to_read{1},colname);
        ind2=strmatch(features_to_read{2},colname);
        plot(data(ind1,:),data(ind2,:),c);hold on;
        xlabel(list_of_feature_labels(1));
        ylabel(list_of_feature_labels(2));
    elseif  n_features_to_read==3
        ind1=strmatch(features_to_read{1},colname);
        ind2=strmatch(features_to_read{2},colname);
        ind3=strmatch(features_to_read{3},colname);
     
        plot3(data(ind1,:),data(ind2,:),data(ind3,:),c); hold on;
        xlabel(list_of_feature_labels(1));
        ylabel(list_of_feature_labels(2));
        zlabel(list_of_feature_labels(3));
    else
        error('max variables to plot is three!');
    end
    
end

figure(20);
savedir= 'C:\home\Platex\MyPaper\EffCopy_Project2008\Figs_ver3\'
savename=sprintf('bird=%s_%s_syllable=%d',load_table_names{1}(1:7),features_to_read{1},which_cluster);

axes(gph_axes(1));
title(strrep(savename,'_','\_'));
legend(legend_h,'Before','BMI','Recovery','Muscimol')
print(gcf,'-dill',fullfile(savedir,[savename,'.ai']));
print(gcf,'-dpng',fullfile(savedir,[savename,'.png']));

figure(21);
axes(gph_axes(2));
title(strrep(savename,'_','\_'));

legend(legend_h2,'Before','BMI','Recovery','Muscimol')
print(gcf,'-dill',fullfile(savedir,[savename,'.ai']));
print(gcf,'-dpng',fullfile(savedir,[savename,'.png']));

%%
figure(22);setPaperSize([7,7]);clf;
bout_dur_name='Song_Motif_hist_ISIthresh=200';
bout_dur_dirnames=[];
n=0;
ColOrder={'b','r','g','c'};
% 
n=n+1;
bout_dur_dirnames{n,1}='C:\home\LabVIEW\data\pur820m\pur820m_20100506_saline_day1_feature';
bout_dur_dirnames{n,2}='C:\home\LabVIEW\data\pur820m\pur820m_20100507_10mMBMI_day2_feature';
bout_dur_dirnames{n,3}='C:\home\LabVIEW\data\pur820m\pur820m_20100508_saline_day3_feature';
% bout_dur_dirnames{n,4}='C:\home\LabVIEW\data\pur820m\pur820m_20100512_Undir_5mMMuscimol_day7_feature';
birdname{1}='pur820m';


n=n+1;
bout_dur_dirnames{n,1}='C:\home\LabVIEW\data\or811m\20100426_UnDir_Saline_day5_feature';
bout_dur_dirnames{n,2}='C:\home\LabVIEW\data\or811m\20100427_UnDir_BMI10mM_day6_feature';
bout_dur_dirnames{n,3}='C:\home\LabVIEW\data\or811m\20100428_UnDir_before_day7_1_feature';
birdname{2}='or811m';


n=n+1;
bout_dur_dirnames{n,1}='C:\home\LabVIEW\data\sil827m\sil827m_20100516_saline_day2_feature';
bout_dur_dirnames{n,2}='C:\home\LabVIEW\data\sil827m\sil827m_20100517_10mMBMI_day3_feature';
bout_dur_dirnames{n,3}='C:\home\LabVIEW\data\sil827m\sil827m_20100518_saline_day4_feature';
birdname{3}='sil827m';

% % bout_dur_dirnames{3}='pur820m_20100508_undir_saline_day3_x.MYD';
    data_bouttmp=struct;
for jj=1:size(bout_dur_dirnames,1)
    h=[];
    dur_t=[0:.1:8];
    data_bout=struct;
    for ii=1:size(bout_dur_dirnames,2)
        if isempty(bout_dur_dirnames{jj,ii}), continue;end
        loadname=fullfile(bout_dur_dirnames{jj,ii},bout_dur_name);
        load(loadname,'bout_duration');
        
        N=histc(bout_duration/1000,dur_t); N=N/sum(N);
        Ncdf=cumsum(N);
        h(ii)=plot(dur_t,Ncdf,ColOrder{ii}); hold on;
        data_bouttmp(jj,ii).bout_dur=bout_duration;
        data_bout(ii).bout_dur=bout_duration;
        % pause
    end
    axis([0 7 0 1]);
    [is_significant,p_ks]=kstest2(data_bouttmp(jj,1).bout_dur,data_bouttmp(jj,2).bout_dur);
    xlabel('[sec]');ylabel('Cumulative distribution of bout duration')
    legend(h,'pre','BMI','recovery','Muscimol')
    % text(max(xlim)-0.5*diff(xlim),min(ylim)+0.1*diff(ylim),...
    %     sprintf('pre VS BMI, KS-test (P=%g)',p_ks));
    title(sprintf('pre VS BMI, KS-test (p=%g)',p_ks));
    fprintf('%s: pre VS BMI, KS-test (p=%g)\n',birdname{jj},p_ks);
    
    [is_significant,p_ks2]=kstest2(data_bouttmp(jj,1).bout_dur,data_bouttmp(jj,3).bout_dur);
    fprintf('%s: pre VS post, KS-test (p=%g)\n',birdname{jj},p_ks2);
     [mann_whit_p,h]=ranksum([data_bouttmp(jj,1).bout_dur,data_bouttmp(jj,3).bout_dur],data_bouttmp(jj,2).bout_dur);
    fprintf('%s: saline VS BMI, Mann_Whitney_U test (p=%g)\n',birdname{jj},mann_whit_p);
    
    savename=sprintf('birdname=%s_bout_durations',birdname{jj});
    savename=fullfile(bout_dur_dirnames{jj,1},savename);
    print(gcf,'-dill',[savename,'.ai']);
    print(gcf,'-dpng',[savename,'.png']);
    save(savename,'data_bout');
    clf;
    
end
%%
figure(2);setpapersize([20,5],9);clf;
loadname{1}='C:\home\LabVIEW\data\pur820m\pur820m_20100506_Saline_day1\pur820m_20100506_undir_saline_day1_x_transMatrix.mat';
loadname{2}='C:\home\LabVIEW\data\pur820m\pur820m_20100507_10mMBMI_day2\pur820m_20100506_undir_10mmbmi_day2_x_transMatrix.mat';
loadname{3}='C:\home\LabVIEW\data\pur820m\pur820m_20100508_saline_day3\pur820m_20100508_undir_saline_day3_x_transMatrix.mat';

for ii=1:length(loadname)
    load(loadname{ii});
    mysubplot(1,4,1,ii,[.8,.8]);
      tmp=sap.pm.converting_matrix;
        labels=[tmp(2:end-1),'N','End'];
            show_index_x=unique([show_index,9,10]);
        show_index_y=show_index;
        
        labels_X=labels(show_index_x);
        labels_Y=labels(show_index_y);
        
        sap.gph.trans_mat_IMG=imagesc(Ntrans_matrix(show_index_y,show_index_x)); x=.5:1:10.5;
%         sap.gph.trans_mat_IMG=surf(sap.pm.Ntrans_matrix(show_index_y,show_index_x));  x=0:1:10;view(0,90);
%         axis([0 show_index_x(end)+1 0 show_index_y(end)+1])
   
        x=.5:1:10.5;
        [X,Y]=meshgrid(x,x);
        line(X,Y,ones(size(X)),'Color',[1 1 1]);
        line(X',Y',ones(size(X')),'Color',[1 1 1])
       set(get(sap.gph.trans_mat_IMG,'Parent'),'XAxisLocation','top','XTick',1:length(labels_X),'YTick',1:length(labels_Y));
        set(get(sap.gph.trans_mat_IMG,'Parent'),'XTickLabel',labels_X,'YTickLabel',labels_Y);
        set(gca,'YDir','Reverse','FontSize',10)
        if ii==1,
              ylabel('Preceding syllable')
        end
end
mysubplot(1,4,1,4,[.9,.8]); 
colorbar;caxis([0 .9])
     xlabel('Following syllable');
      
load('coldfire2');
colormap(coldfire2);

savedir= 'C:\home\Platex\MyPaper\EffCopy_Project2008\Figs_ver3\';
savename= fullfile(savedir,'pur820m_transMatrix');
print(gcf,'-dpng',[savename,'.png'])
print(gcf,'-dtiff',[savename,'.tiff'])     
 
