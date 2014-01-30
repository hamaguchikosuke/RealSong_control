function out=max2D(X,varargin)
%  MAX  �ő�v�f
%  
%     �x�N�g���ɑ΂��āAMAX(X) �́AX �̍ő�v�f�ł��B�s��ɑ΂��āAMAX(X) �́A
%     �e��̍ő�v�f���܂ލs�x�N�g���ł��BN �����z��ɑ΂��āAMAX(X) �͍ŏ���
%     ��V���O���g�������ɉ����ď������܂��B
%  
%     [Y,I] = MAX(X) �́A�x�N�g�� I �ɍő�l�̃C���f�b�N�X��Ԃ��܂��B�ŏ���
%     ��V���O���g�������ɉ������l�������̍ő�v�f���܂ޏꍇ�A�ŏ��̍ő�v�f��
%     �C���f�b�N�X���Ԃ���܂��B
%  
%     MAX(X,Y) �́AX,Y �̑Ή�����v�f�̓��A�ł��傫���v�f�𓾂āAX,Y �Ɠ���
%     �T�C�Y�̔z���Ԃ��܂��BX,Y �̂ǂ��炩���X�J���ł��\���܂���B
%  
%     [Y,I] = MAX(X,[],DIM) �́A���� DIM �ɉ����ď������܂��B
%  
%     X �����f���̏ꍇ�A�ő�l�́A�U�� MAX(ABS(X)) ���g���Čv�Z����܂��B
%     �������U���v�f������ꍇ�A�ʑ��p MAX(ANGLE(X)) ���g���܂��B
%  
%     �ő�v�f�̌v�Z�ł́ANaN �𖳎����܂��BX �̂��ׂĂ̗v�f�� NaN �̏ꍇ�A
%     �ő�l�Ƃ��čŏ��� 1 ���Ԃ���܂��B
%  
%     ��F X = [2 8 4   �̏ꍇ�Amax(X,[],1) �� [7 8 9] �ł��B
%               7 3 9]
%  
%         max(X,[],2) �� [8    �ŁAmax(X,5) �� [5 8 5  �ł��B
%                         9]                    7 5 9]

[max_x,max_ind]=max(X,varargin{:});

if nargin>=3
    DIM=varargin{2};
end

out=cat(DIM,max_x,max_ind);
