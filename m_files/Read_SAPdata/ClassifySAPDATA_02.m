function ClassifySAPDATA_02(opt)
% read SAP exported MATLAB format data of syllable database,
% check the syllable by eyes and ears, 
% by KH 20090729
% 
%% 
% addpath('Sub_SyllableAnalysis_Mcodes');
% 
% sap.pm.names={'recnum',...              % 1
%     'serial_number',...             % 2
%     'bird_ID',...                   % 3
%     'start_on',...                  % 4
%     'duration',...                  % 5
%     'mean_pitch',...                % 6
%     'mean_FM',...                   % 7
%     'mean_entropy',...              % 8
%     'mean_goodness_of_pitch',...    % 9
%     'mean_mean_frequency',...       % 10
%     'mean_am2',...                  % 11
%     'mean_amplitude',...            % 12
%     'var_pitch',...                 % 13
%     'var_FM',...                    % 14
%     'var_entropy',...               % 15
%     'var_goodness_of_pitch',...     % 16
%     'var_mean_frequency',...        % 17
%     'var_am',...                    % 18
%     'month',...                     % 19
%     'day',...                       % 20
%     'hour',...                      % 21
%     'minute',...                    % 22
%     'second',...                    % 23
%     'cluster'};                     % 24
%     'file_name'};                   % 25
%       'MahlDist'                    % 26
%     'EM_cluster',                   % 27
%     'manual_cluster',...            % 28



ClassifySAP_sub_routines_05p9('init_variables_for_figure'); % load variables needed below;
ClassifySAP_sub_routines_05p9('init_variables');
ClassifySAP_sub_routines_05p9('init_figures');


