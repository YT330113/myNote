%% 陈诚电气 标准化绘图
%% QQ480570241 
%% 淘宝：陈诚电气辅导
%% 公众号：陈诚电气（免费获取资料/源代码） 

% 获取/生产 原始数据
t=R(:,1);
y1 = R(:,2);
y2 = RL(:,2);

% 横纵坐标标注
xlabel0 = 't(s)';
ylabel0 = 'I(A)';


% 设置绘图曲线的宽度
lw=1.5;

% 设置绘图的字体大小
ft=12; % FontSize

% 设置绘图的字体样式
fn_en='Times New Roman'; %英文字体新罗马

% 声明一个新figure
figure();
ax1=subplot(1,1,1);

plot(t,y1,'LineWidth',lw);
hold on
plot(t,y2,'LineWidth',lw);

% 设置x轴范围和标注
xlabel(ax1,xlabel0,'FontSize',ft,'FontName',fn_en);

% 设置y轴范围和标注
ylabel(ax1,ylabel0,'FontSize',ft,'FontName',fn_en);

grid(ax1,'on');
ax1.FontSize = ft;
ax1.FontName =fn_en;

% 设置绘图的位置500，500，大小 700宽 300高
set(gcf,'Position',[500,500,400,240]);





