classdef AxonBinaryFile_dataclass < handle
% Axon Binary File (ABF) data class.
% define abf=AxonBinaryFile_dataclass(filename);
% 
% ex)
% abf=AxonBinaryFile_dataclass('your_realsong_data_here.mat');
% abf.vm;          % voltage (either input/output)
% abf.Im;          % current (either input/output)
% abf.t;           % time vector.
% abf.h;           % Axon Binary File, Header information.
% abf.Fs;          % Sampling Rate [Hz].
% 
%  
% by KH 20131120

    properties (SetAccess = private)
        vm
        Im
        t
        pm
        Fs
        filename
        ClampMode
    end
    
    
    
    properties (Dependent)
        
    end
    
    
    methods
        function obj = AxonBinaryFile_dataclass(filename,varargin)
            
           
            if nargin==0
                [filename,pathname]=uigetfile();
                filename=fullfile(pathname,filename);
            end
            
            
            [d,si,h]=abfload(filename);
            pm.SampRate = 1/(si*1.e-6);     
            pm.ScalingFactor =  h.fInstrumentScaleFactor;
            pm.ABF_h = h;
            
            [dataN,channelN,SweepN] = size(d);
            
            if h.dataPtsPerChan ~= dataN 
                error('Data length does not match');
            end
            
        
                
            % Because pClamp software add 1/64th of data at the beginning
            % and end.
            t_vec = linspace(0,(dataN-1)/pm.SampRate,dataN)-dataN/64/pm.SampRate;
            
            obj.filename=filename;
          	obj.t= t_vec;
           
            obj.Fs = pm.SampRate;
            
          name_conversion_matrix = ...
                {'I_MTest 0',               'Vm0'; ...
                'I_MTest 1',                'Vm1';...
                'Ch2_VmCmd',                'Im0';...
                'I_MTest 3',                'Im1';...
                'Im1_VC',                   'Im0';...
                'Vm1_VC',                   'Vm0';...
                'Im2_VC',                   'Im1';...
                'Vm2_VC',                   'Vm1';...
                '_Ipatch',                  'Vm0'};
            
            %---- sort out parameters ----%
            
            % rename the channel identifier so that we can analyze them in unified
            % manner.
            pm.AIChannel        =   regexprep(h.recChNames,{name_conversion_matrix{:,1}},{name_conversion_matrix{:,2}});
        
            pm.AI_ChUnits       =   h.recChUnits;
            Vindex              =  find(strncmpi(h.recChUnits,'mV',2));
            Iindex              =  find(strncmpi(h.recChUnits,'pA',2));
 
            if any(Iindex==1) % If current recorded first,
                obj.ClampMode = 'VoltageClamp';
            elseif any(Vindex==1) % If voltage recorded first,
                obj.ClampMode = 'CurrentClamp';
            else
                obj.ClampMode = 'Unknown';
            end
            
            pm.V_Channel        =   pm.AIChannel(Vindex);
            pm.I_Channel        =   pm.AIChannel(Iindex);
                
            
            obj.vm = d(:,Vindex,:);
            obj.Im = d(:,[Iindex],:);
            
            switch obj.ClampMode
                case 'VoltageClamp'
                    % Input channel is current.
                     pm.AIChannel        =   pm.I_Channel  ;
                     % Output channel is voltage.
                     pm.AOChannel        =   pm.V_Channel  ;
                case 'CurrentClamp'
                    % Input channel is voltage.
                    pm.AIChannel        =   pm.V_Channel  ;
                    % Output channel is current.
                    pm.AOChannel        =   pm.I_Channel  ;
                otherwise
                    error;
            end
            obj.pm = pm;
            
        end
    end
 
    %-----------------------------------------------------
 
end