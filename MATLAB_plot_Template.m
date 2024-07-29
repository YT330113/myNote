%% �³ϵ��� ��׼����ͼ
%% QQ480570241 
%% �Ա����³ϵ�������
%% ���ںţ��³ϵ�������ѻ�ȡ����/Դ���룩 

% ��ȡ/���� ԭʼ����
t=R(:,1);
y1 = R(:,2);
y2 = RL(:,2);

% ���������ע
xlabel0 = 't(s)';
ylabel0 = 'I(A)';


% ���û�ͼ���ߵĿ��
lw=1.5;

% ���û�ͼ�������С
ft=12; % FontSize

% ���û�ͼ��������ʽ
fn_en='Times New Roman'; %Ӣ������������

% ����һ����figure
figure();
ax1=subplot(1,1,1);

plot(t,y1,'LineWidth',lw);
hold on
plot(t,y2,'LineWidth',lw);

% ����x�᷶Χ�ͱ�ע
xlabel(ax1,xlabel0,'FontSize',ft,'FontName',fn_en);

% ����y�᷶Χ�ͱ�ע
ylabel(ax1,ylabel0,'FontSize',ft,'FontName',fn_en);

grid(ax1,'on');
ax1.FontSize = ft;
ax1.FontName =fn_en;

% ���û�ͼ��λ��500��500����С 700�� 300��
set(gcf,'Position',[500,500,400,240]);





