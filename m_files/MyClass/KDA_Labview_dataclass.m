classdef KDA_Labview_dataclass < KinkaDataAnalysis_Defalut_dataclass
    % KinkaDataAnalysis Labview Data class.
    % obj=KDA_Labview_dataclass(filename);
    %
    % ex)
    % analysis  --gpm   (global parameters)
    %           --data  (data structure)
    %           --pmR   (parameter set from the first trial)
    %           --pmRAll(parameter set from all the trial)
    %
    
    %
    % by KH 20121111
    
    %     properties (SetAccess = private)
    %         gpm
    %         data
    %         pmR
    %         pmRAll
    %
    %     end
    %
    %     properties (Dependent)
    %
    %     end
    %
    
    methods
        function obj = KDA_Labview_dataclass(filename)
            
            obj=obj@KinkaDataAnalysis_Defalut_dataclass(filename);
                        
            s=strsplit(filename,filesep);
            obj.gpm.pathname =sprintf('%s\\',s{1:end-1});
            obj.gpm.filename=s{end};
            
            fid = fopen(filename, 'r','b'); % Read-Only, Big-endian
            
            % % get header size and parameters.
            header_size = fread(fid, 1, 'uint32')';
            header_size=header_size+4;
            
            
            % Determine whether recording program was "SongPres" or
            % "SongPresDual" or higher.
            
            try
                [fid,obj.pmR]=ReadHeader_SongPresSingleLabView(fid);
                obj.pmR.AOChannel; % test that parameters are correctly read.
                %             % The AO channel parameter must be char, and usually, less 64
                %             because most of the electrophysiology uses less than 64 channel.
                if ~ischar(obj.pmR.AOChannel)|| (length(obj.pmR.AOChannel)>100)
                    error;
                end
                obj.gpm.flag_songpresdual_or_more=0;
            catch
                fseek(fid,4,-1);
                [fid,obj.pmR]=ReadHeader_SongPresLabView(fid);
                obj.gpm.flag_songpresdual_or_more=1;
            end
            
            
            obj.pmR.AIChannel = str2num(obj.pmR.AIChannel);
            obj.pmR.ChannelForPlot=obj.pmR.AIChannel;
            obj.pmR.AOChannel = str2num(obj.pmR.AOChannel);
            num_channel=length(obj.pmR.AIChannel);
            fclose(fid);
            
            % UPdate obj.gpm.channel_name
            kk=1;
            for ii=1:length(obj.pmR.AIChannel)
                for jj=1:length(obj.gpm.channel_name)
                    if ~isempty(strfind(obj.gpm.channel_name{jj},['E' num2str(obj.pmR.AIChannel(ii))]))
                        tmp{kk}=obj.gpm.channel_name{jj};
                        tmp2{kk}=obj.gpm.current_name{jj};
                        kk=ceil(kk+1);
                    end
                end
            end
            
            obj.gpm.channel_name=tmp;
            obj.gpm.current_name=tmp2;
            obj.gpm.spike_analysis_bool=true(1,length(obj.pmR.AIChannel));
            
            if obj.gpm.flag_songpresdual_or_more==0
                [obj.data.v,pmRtmp,obj.data.songID,obj.pmRAll]=Read_SongPresData3(fullfile(obj.gpm.pathname,obj.gpm.filename),'songpres_single');
            else
                [obj.data.v,pmRtmp,obj.data.songID,obj.pmRAll]=Read_SongPresData3(fullfile(obj.gpm.pathname,obj.gpm.filename),num_channel);
            end
            % Search for the longest sequence and set it as obj.data.T
            % This is necessary because v.v1 is padded NaN if some sequence is shorter than the other t
            % to make a same size matrix.
            obj.gpm.max_TotalScanLen=0;
            %         for ii=1:size(obj.data.v.v1,1)
            %         obj.gpm.max_TotalScanLen =max(obj.gpm.max_TotalScanLen,obj.pmRAll{ii}.TotalScanLen);
            %         end
            obj.gpm.max_TotalScanLen=size(obj.data.v.v1(1,:),2);
            obj.data.T=linspace(0,(obj.gpm.max_TotalScanLen-1)/(obj.pmR.scanrate/2),obj.gpm.max_TotalScanLen);
            
            obj.pmR.Fcell          = obj.pmR.scanrate/2;
            %         if obj.pmR.Fcell==11025,
            %             obj.pmR.Fcell=10000;
            %         end
            obj.gpm.curr_trial     =1;
            obj.gpm.loaded_trials  =1:size(obj.data.v.v1,1);          
            
        end     
        
    end

end