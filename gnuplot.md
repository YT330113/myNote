# gnuplot

[摘自链接](https://blog.csdn.net/weixin_38468077/article/details/101069365?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522166921339016782388090867%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=166921339016782388090867&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-2-101069365-null-null.142^v66^control,201^v3^add_ask,213^v2^t3_esquery_v3&utm_term=gnuplot%E8%AF%BB%E5%8F%96txt%E6%96%87%E4%BB%B6%E7%94%BB%E5%9B%BE&spm=1018.2226.3001.4187)

## 1. 基础

### 1.1 参数

| 命令       | 缩写 | 意义                                                         |
| ---------- | ---- | ------------------------------------------------------------ |
| With       | w    | with后边跟需要指定的样式                                     |
| Line       | l    | 用线l显示                                                    |
| Point      | p    | 用点显示                                                     |
| LinePoints | lp   | 用线和点画，对数据绘图时有用                                 |
| LineType   | lt   | 线的样式（0代表虚线，1-7代表实线,颜色分别为紫、蓝、绿、橙、黄、靛、红。超过7以后颜色依次循环） |
| LineWidth  | lw   | 线的宽度（level从0开始，默认为1）                            |
| PointType  | pt   | 点的样式（level从0开始，默认为1）                            |
| PointSize  | ps   | 点的宽度（level从0开始，默认为1）                            |

### 1.2 图例

1. 没有任何格式`plot sin(x)`

2. with points `plot sin(x) w p`

3. with line `plot sin(x) w l`
4. with linePoints `plot sin(x) w lp`

5. with linePoints lineType is 0 `plot sin(x) w lp lt 0`

6. with line lineType=1 and lineWidth=4 `plot sin(x) w l lt 1 lw 4`

7. with point pointType=4 `plot sin(x) w p pt 4`

8. with point pointType=4 and pointSize=4`plot sin(x) w p pt 4 ps 2`

## 1.3 高阶参数



### 1.3.1 约束画图范围

```cpp
plot [-5:5] [-1.2:1.2] sin(x)
//表示x取值范围为[-5,5],y的取值范围为[-1.2,1.2]
```

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190920164811487.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl8zODQ2ODA3Nw==,size_16,color_FFFFFF,t_70#pic_center)

### 1.3.2 坐标轴设定

在对于坐标轴的设定，要注意的一点就是，在画图之前执行命令。

| 命令                     | 含义                                                         |
| ------------------------ | ------------------------------------------------------------ |
| set xlabel ‘x’           | x轴标为‘x’                                                   |
| set ylabel ‘y’           | y轴标为’y’                                                   |
| set ylabel ‘DOS’ tc lt 3 | ‘DOS’的颜色用第三种颜色                                      |
| set xtics 1.0            | x轴的主刻度的宽度为1.0，同样可以为y轴定义ytics               |
| set mxtics 3             | x轴上每个主刻度中画3个分刻度，同样可以为y轴定义mytics        |
| set border 3             | 设为第三种边界，同样可以为上边的x轴（称为x2）和右边y（称为y2）轴进行设置，即x2tics，mx2tics，y2tics，my2tics。 |
| set xtics nomirror       | 去掉上边x的刻度，同样可以为ytics设置                         |
| unset x2tics             | 去掉上边x的标度，同样可以为y2tics设置                        |

```cpp
gnuplot> set title 'kmust team'
gnuplot> set xlabel 'x'
gnuplot> set ylabel 'y'
gnuplot> set xtics 1.0
gnuplot> set mxtics 3
gnuplot> set border 3
gnuplot> plot sin(x)
```

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190920170828421.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl8zODQ2ODA3Nw==,size_16,color_FFFFFF,t_70#pic_center)

### 1.3.3 图名关键字位置

| 命令                | 含义                                 |      |
| ------------------- | ------------------------------------ | ---- |
| set key left        | 放在左边，有left 和right两个选项     |      |
| set key bottom      | 放在下边，只有这一个选项；默认在上边 |      |
| set key outside     | 放在外边，但只能在右面的外边         |      |
| set key left bottom | 表示放在左下边                       |      |

```cpp
set key right bottom
gnuplot> set title "kmust"
gnuplot> plot sin(x)
//将图例放在右下角
//设置标题为“kmust”
```

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190920194230103.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl8zODQ2ODA3Nw==,size_16,color_FFFFFF,t_70#pic_center)

### 1.3.4 在图中任意位置插入文字

```cpp
gnuplot> set label 'I Love Kmust!' at 2.5,0.5
gnuplot> plot sin(x)
//在坐标（2.5，0.5）处插入文字
//如果想要删除文字就使用 unset label 1(此处数字代表要删除label的序号)
```

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190920203757755.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl8zODQ2ODA3Nw==,size_16,color_FFFFFF,t_70#pic_center)

## 1.4 同时画出多条曲线

```cpp
plot sin(x),cos(x)
//注意连个函数之间要使用逗号分隔开
```

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190920171358263.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl8zODQ2ODA3Nw==,size_16,color_FFFFFF,t_70#pic_center)

当然两个函数之间也可以单独约束

```c
plot sin(x) title 'sin(x)' w l lt 0 lw 2, cos(x) title 'cos(x)' w l lt 2 lw 2
//注意连个函数之间要使用逗号分隔开，每个函数的绘画要求紧跟着对应的函数
```

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190920171518832.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl8zODQ2ODA3Nw==,size_16,color_FFFFFF,t_70#pic_center)

## 1.7 读取dat、txt文件进行画图

在用c语言进行程序设计的时候，有时就需要画图任务，这时gnuplot可以读取dat、txt文件内的内容，并再进行绘画。

```c
gnuplot> set arrow from -0.3,0.0 to 1.0,0.0
gnuplot> plot [-16:16] [-0.3:1] "sinc.bat"  u 1:2 w l lt 1 lw 1
//从（-16，0）到（16，0）画一条直线
//从（-0.3，0）到（1.0，0）画一条带箭头射线
//读取“sinc.bat”文件内的数据，并用其内的第一列和第二列作图，，并且设置线条颜色和粗细。
```

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190920202433729.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl8zODQ2ODA3Nw==,size_16,color_FFFFFF,t_70#pic_center)

## 1.8 设定图的大小和位置

```c
gnuplot> set size 0.5,0.5
gnuplot> plot sin(x)
//长宽均为默认宽度的一半
```

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190920204413633.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl8zODQ2ODA3Nw==,size_16,color_FFFFFF,t_70#pic_center)

```c
gnuplot> set origin 0.0,0.5
gnuplot> plot sin(x)
//设定图的最左下角的那一点在图形面板中的位置。这里图将出现在左上角。
```

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190920204545846.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl8zODQ2ODA3Nw==,size_16,color_FFFFFF,t_70#pic_center)



## 1.9 画多个图

```c
gnuplot> set multiplot//设置为多图模式
multiplot> set origin 0.0,0.5//设置第一个图的原点的位置
multiplot> set size 0.5,0.5//设置第一个图的大小，长和宽均为整个图的一半
multiplot> plot tan(x)//开始绘制第一个图
multiplot> set origin 0.5,0.5//设置第2个图的原点的位置
multiplot> set size 0.5,0.5//设置第2个图的大小，长和宽均为整个图的一半
multiplot> plot  cos(x)//开始绘制第2个图
multiplot> set origin 0.0,0.0//设置第3个图的原点的位置
multiplot> set size 0.5,0.5//设置第3个图的大小，长和宽均为整个图的一半
multiplot> plot  sin(x)//开始绘制第3个图
multiplot> set origin 0.5,0.0//设置第4个图的原点的位置
multiplot> set size 0.5,0.5//设置第4个图的大小，长和宽均为整个图的一半
multiplot> plot 1/x//开始绘制第4个图
```

绘制完成之后就会出现这个四合一的图，当然我们还可以 为每个图设置自己的特有属性，比如颜色、标题等。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190920212747179.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl8zODQ2ODA3Nw==,size_16,color_FFFFFF,t_70#pic_center)

## 2.gnuplot进阶

### 2.1 设置坐标轴范围

```c
gnuplot>  set size square//设置形状为方形
gnuplot> set size 0.5,0.5//设置图形的大小各为一半
gnuplot> set xrange[-10:10]
gnuplot> set yrange[-10:10]//设置x,y的范围相同
gnuplot> plot x+2
```

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190920220255315.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl8zODQ2ODA3Nw==,size_16,color_FFFFFF,t_70#pic_center)

### 2.2 在同一张图里利用左右两边的y轴分别画图
```cpp
gnuplot> set xtics nomirror
//去掉上边坐标轴x2的刻度
gnuplot> set ytics nomirror
//去掉上边坐标轴y2的刻度
gnuplot> set x2tics
//让上面坐标轴x2刻度自动产生
gnuplot> set y2tics
//让上面坐标轴y2刻度自动产生
gnuplot> plot sin(x),cos(x) axes x1y2
//用x1y2坐标，axes x1y2表示用x1y2坐标轴
```

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190920220659444.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl8zODQ2ODA3Nw==,size_16,color_FFFFFF,t_70#pic_center)

### 2.5 gnuplot脚本文件

我在文件夹下创建了一个 try.plt文件，其内容如下所示

```c
reset
//重置画图属性
set pm3d
//设置为pm3d模式
unset ztics
//取消z轴标题
set isosamples 200,200
//设置网格属性为200x200
splot x**2+y**2 w pm3d
//开始画图并且设置为pm3d模式
```


然后只需在gnuplot命令界面输入

```c
load 'try.plt
//加载plt文件，执行画图任务
```

其结果如下所示：![img](https://img-blog.csdnimg.cn/20190921165002556.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl8zODQ2ODA3Nw==,size_16,color_FFFFFF,t_70#pic_center)

## 3 使用实例

**例 1：**

```bash
plot sin(x)
```

假设我们只想看到一个正弦曲线周期。我们通过限制图的默认 x 范围来完成此操作。使用表示法 [min:max] 来指定范围。要仅指定最小值，使用 [min:]；要仅指定最大值，使用 [:max]。数学上称此为所谓的“闭”区间表示法。

**例 2：**从 -pi 到 +pi 的 sin(x) 和 cos(x)

```bash
set xrange [-pi:pi]
replot cos(x) with points pointtype 2
```

或者：

```bash
plot [-pi:pi] sin(x), cos(x) with points pointtype 2
```

我们刚才使用了 replot 命令，它执行先前的 plot 命令。当您绘制曲线图且需要不断对该图进行修改以添加想要的特征时，此命令会非常有用。另外，replot 使您可以添加更多的图。尝试输入 replot cos(x)。依照语法，该命令等同于 plot sin(x), cos(x)。replot 就是获取先前的绘图字符串，添加必要的逗号，然后附加输入给它的其余部分。

**例 5: 将数据文件中的数据画出**

```bash
plot sin(x), ‘1.dat’
```

其中1.dat 为一数据文件，每一行描述一点坐标位置。 内容如下，其中 # 后面的内容为注释：

```bash
# $Id: 1.dat,v 1.1.1.1 1998/04/15 19:16:40 lhecking Exp $
-20.000000 -3.041676
-19.000000 -3.036427
-18.000000 -3.030596
-17.000000 -3.024081
-16.000000 -3.016755
-15.000000 -3.008456
……
```

![image-20221123233054833](/home/yt/.config/Typora/typora-user-images/image-20221123233054833.png)

**例 6命名图和坐标轴：**

```bash
set title 'My first graph'
set xlabel 'Angle, in degrees'
set ylabel 'sin(angle)'
plot sin(x)
```

![image-20221123233244200](/home/yt/.config/Typora/typora-user-images/image-20221123233244200.png)

现在，我们注意到 x 轴实际没有标记为度数，看起来不是很好。要修改此问题，可以通过调整 x 轴上的 tic 标记。

**例 7 改变轴上 tic 并设置网格：**

```bash
set title "My first graph"
set xrange [-pi:pi]　　# we want only one cycle
set xtics ('0' 0, '90' pi/2, '-90' -pi/2, '45' pi/4,'-45' -pi/4,'135' 3*pi/4,'-135' -3*pi/4)
set grid
set xlabel 'Angle, in degrees'
set ylabel 'sin(angle)'
plot sin(x) 
```

![image-20221123233348442](/home/yt/.config/Typora/typora-user-images/image-20221123233348442.png) 

gnuplot 还允许您指定绘图的样式，以便获得进一步的控制。

**例 8 多条曲线**

```bash
plot sin(x) with linespoints pointtype 5, cos(x) w boxes lt 4 
```

![image-20221123233452587](/home/yt/.config/Typora/typora-user-images/image-20221123233452587.png)

with 子句使您可以详细而精确地指定线的样式。在本例中，我们说明两种有用的样式。第一种样式 linespoints 通常在对数据绘图时非常有用，它在涉及的每个示例或数据点处标记一个点，并使用线性插值法连接连续的点。这里我们另外指定点类型为 5，它选择终端允许的第五种点。第二种样式 boxes 更适合绘制直方图数据。注意我们如何在 cos(x) 曲线中将 with 缩写成 w。类似地，lt 是 linetype 的缩写，是另一个特定于终端的设置，它选择终端可以绘制的四种线。不必说，您可以使用 pt 代替冗长的 pointtype。如果想在多条线中使用相同的绘图样式（在一个 plot 命令中或在多个 plot 命令中），可以使用 set 命令设置绘图样式：set style function linespoints。要更改用于绘制与函数相对的数据集合的样式，使用 set style data linespoints。

当绘制两条或多条曲线时，我们需要关键字或图例来对它们进行区分。默认情况下，关键字在右上角；但是如果它妨碍了图，可以将关键字放到其他位置 。如果愿意，甚至可以放到图外。

**例 9 定制图的关键字或图例**

```bash
set key top left
set key box
plot [-pi:pi] sin(x) title 'sinusoid' with linespoints pointtype 5, cos(x) t 'cosine' w boxes lt 4
```

![image-20221123233708256](/home/yt/.config/Typora/typora-user-images/image-20221123233708256.png)

上面，我们在同一图中绘制了正弦和余弦曲线。gnuplot 使您还可以绘制多个图，这样它们可以并排显示在同一输出屏幕或文件中。在某些排版系统中，以一个文件的形式包含两个图形比分别包含两个图形要更容易。

**例 10 Multiplot 示例：**

```bash
set xrange [-pi:pi]
# gnuplot recommends setting the size and origin before going to multiplot mode
# This sets up bounding boxes and may be required on some terminals
set size 1,1
set origin 0,0

# Done interactively, this takes gnuplot into multiplot mode
set multiplot

# plot the first graph so that it takes a quarter of the screen
set size 0.5,0.5
set origin 0,0.5
plot sin(x)

# plot the second graph so that it takes a quarter of the screen
set size 0.5,0.5
set origin 0,0
plot 1/sin(x)

# plot the third graph so that it takes a quarter of the screen
set size 0.5,0.5
set origin 0.5,0.5
plot cos(x)

# plot the fourth graph so that it takes a quarter of the screen
set size 0.5,0.5
set origin 0.5,0
plot 1/cos(x)

# On some terminals, nothing gets plotted until this command is issued
unset multiplot
# remove all customization
reset
```

![image-20221123233819136](/home/yt/.config/Typora/typora-user-images/image-20221123233819136.png)

## 3 GNU技巧

`gnuplot> plot ‘a.dat’ u 2:3 w l lt 3 lw 2` %利用数据文件a.dat中的第二和第三列作图


顺便提一下，如这里最前面的两个例子所示，在gnuplot中，如果某两个词，按字母先后顺序，前面某几个字母相同，后面的不同，那么只要写到第一个不同的字母就可以了。如with，由于没有其它以w开头的词，因此可以用 w 代替，line也可以用 l 代替。

2、同时画多条曲线

`gnuplot> plot sin(x) title ‘sin(x)’ w l lt 1 lw 2, cos(x) title ‘cos(x)’ w l lt 2 lw 2` ％两条曲线是用逗号隔开的。画多条曲线时，各曲线间均用逗号隔开就可以了。

以上例子中是对函数作图，如**果对数据文件作图，将函数名称换为数据文件名即可，但要用单引号引起来。**

 

3、关于图例的位置

默认位置在右上方。

> gnuplot> set key left %放在左边，有left 和right两个选项
>
> gnuplot> set key bottom %放在下边，只有这一个选项；默认在上边
>
> gnuplot> set key outside %放在外边，但只能在右面的外边

以上三个选项可以进行组合。如：

gnuplot> set key left bottom %表示左下边


还可以直接用坐标精确表示图例的位置，如

gnuplot> set key 0.5,0.6 %将图例放在0.5,0.6的位置处

4、关于坐标轴

gnuplot> set xlabel ‘x’   %x轴标为‘x’

gnuplot> set ylabel ‘y’   %y轴标为’y’

gnuplot> set ylabel ‘DOS’ tc lt 3 %其中的tc lt 3表示’DOS’的颜色用第三种颜色。

gnuplot> set xtics 1.0    %x轴的主刻度的宽度为1.0，同样可以为y轴定义ytics

gnuplot> set mxtics 3    %x轴上每个主刻度中画3个分刻度，同样可以为y轴定义mytics

gnuplot> set border 3 lt 3 lw 2 %设为第三种边界，颜色类型为3，线宽为2

同样可以为上边的x轴（称为x2）和右边y（称为y2）轴进行设置，即x2tics，mx2tics，y2tics，my2tics。

gnuplot> set xtics nomirror

gnuplot> unset x2tics     %以上两条命令去掉上边x2轴的刻度


gnuplot> set ytics nomirror

gnuplot> unset y2tics     %以上两条命令去掉右边y轴的刻度


5、在图中插入文字

gnuplot> set label ‘sin(x)’ at 0.5,0.5 %在坐标（0.5,0.5）处加入字符串’sin(x)’。

在输出为.ps或.eps文件时，如果在set term 的语句中加入了enhanced选现，则可以插入上下标、希腊字母和特殊符号。上下标的插入和latex中的方法是一样的。

6、在图中添加直线和箭头

gnuplot> set arrow from 0.0,0.0 to 0.6,0.8    %从（0.0,0.0）到（0.6,0.8）画一个箭头

gnuplot> set arrow from 0.0,0.0 to 0.6,0.8 lt 3 lw 2   %这个箭头颜色类型为3，线宽类型为2

gnuplot> set arrow from 0.0,0.0 to 0.6,0.8 nohead lt 3 lw 2 %利用nohead可以去掉箭头的头部，这就是添加直线的方法。

注意，在gnuplot中，对于插入多个的label和arrow等等，系统会默认按先后顺序分别对各个label或arrow进行编号，从1开始。如果以后要去掉某个label或arrow，那么只要用unset命令将相应的去掉即可。如：

gnuplot> unset arrow 2

将去掉第二个箭头。

7、图的大小和位置

gnuplot>set size 0.5,0.5 %长宽均为默认宽度的一半，建议用这个取值，尤其是画成ps或eps图形的时候

gnuplot>set origin 0.0,0.5   %设定图的最左下角的那一点在图形面板中的位置。这里图将出现在左上角。

8、画三维图

gnuplot>splot ‘文件名’ u 2:4:5 %以第二和第四列作为x和y坐标，第五列为z坐标。

9．将图形输出到文件

在gnuplot中，输出文件的格式是由terminal来控制的。默认的情况下，都是输出到屏幕，即终端模式为X11。如果想输出到文件，则必须对terminal进行设置。要了解有那些终端类型，可以输入 set terminal后回车，所有支持的终端模式（或文件格式）都列出来了。就我来说，输出文件的格式用得最多的是ps和eps文件。这在运行画图命令plot或splot前必须先运行如下两条命令：

gnuplot>set term post eps color solid enh

gnuplot>set output ‘a.eps’

其中第一条命令为设置终端模式，post即为postscript模式，这是输出到ps或eps文件必须有的。后面的eps，color，solid以及enh选项均可以有或没有，根据你的需要。eps表示输出为eps文件，没有就输出为ps文件；color表示输出图形为彩色，不用就会保存为黑白的；solid表示输出图中的所有线都用实线，不用则除了第一条线为实线外，其它的均用不同的虚线；使用enh(enhanced)选项可以在图中插入上下标、希腊字母和特殊符号，不用则不能实现这些功能。后面的选项可以根据自己的需要选择一个或几个。

第二条命令对output的设置表示要输出的文件的名字。但是请注意，运行完这条命令后，还仅仅是定义了输出文件的名字，实际上，图还没画到这个文件里去。因此运行这两条命令还只是进行了必须的设置。然后运行如下命令

gnuplot>plot sin(x) w l

或

gnuplot>replot（假如前面已经运行过plot或replot命令的话）

这时，图形就在上面指定的文件中了。

要输出为其它格式，同样要进行这样的设置，比如要输出为jpg格式，则在运行画图命令前先运行如下命令：

gnuplot>set term jpeg

gnuplot>set output ‘a.jpg’

如果要由其它模式再返回到输出到屏幕，则运行如下命令：

gnuplot>set term X11

二、提高篇：

1、如何在同一张图里同时画多个图

gnuplot>set multiplot   %设置为多图模式

gnuplot>set origin 0.0,0.5   %设置第一个图的原点的位置

gnuplot>set size 0.5,0.5 %设置第一个图的大小

gnuplot>plot “a1.dat”

gnuplot>set origin 0.5,0.5   %设置第二个图的原点的位置

gnuplot>set size 0.5,0.5 %设置第二个图的大小

gnuplot>plot “a2.dat”

gnuplot>set origin 0.0,0.0   %设置第三个图的原点的位置

gnuplot>set size 0.5,0.5 %设置第三个图的大小

gnuplot>plot “a3.dat”

gnuplot>set origin 0.5,0.0   %设置第四个图的原点的位置

gnuplot>set size 0.5,0.5 %设置第四个图的大小

gnuplot>plot “a4.dat”

当然，如果后一个图中的某个量的设置和前一个的相同，那么后一个中的这个量的设置可以省略。例如上面对第二、第三和第四个图的大小的设置。前一个图中对某个量的设置也会在后一个图中起作用。如果要取消在后面图中的作用，必须用如下命令，如取消label，用

gnuplot>unset label

 

 

2、作二维图时，如何使两边坐标轴的单位长度等长

gnuplot> set size square    %使图形是方的
gnuplot> set size 0.5,0.5    %使图形是你要的大小
gnuplot> set xrange[-a:a]
gnuplot> set yrange[-a:a]    %两坐标轴刻度范围一样
gnuplot> plot ‘a.dat’

 

3、如何在同一张图里利用左右两边的y轴分别画图

gnuplot> set xtics nomirror   %去掉上面坐标轴x2的刻度
gnuplot> set ytics nomirror   %去掉右边坐标轴y2的刻度
gnuplot> set x2tics       %让上面坐标轴x2刻度自动产生
gnuplot> set y2tics     %让右边坐标轴y2的刻度自动产生
gnuplot> plot sin(x),cos(x) axes x1y2    %cos(x)用x1y2坐标，axes x1y2表示用x1y2坐标轴
gnuplot> plot sin(x),cos(x) axes x2y2     %cos(x)用x2y2坐标，axes x2y2表示用x2y2坐标轴
gnuplot> set x2range[-20:20]   %设定x2坐标的范围
gnuplot> replot
gnuplot> set xrange[-5:5] %设定x坐标的范围
gnuplot> replot
gnuplot> set xlabel 'x'
gnuplot> set x2label 't'
gnuplot> set ylabel 'y'
gnuplot> set y2label 's'
gnuplot> replot
gnuplot> set title 'The figure'
gnuplot> replot
gnuplot> set x2label 't' textcolor lt 3    %textcolor lt 3或tc lt 3设置坐标轴名称的颜色

 

4、如何插入希腊字母和特殊符号

一般只能在ps和eps图中，且必须指定enhanced选项。在X11终端（即显示器）中无法显示。

gnuplot> set terminal postscript enhanced

然后希腊字母就可以通过{/Symbol a}输入。例如

gnuplot> set label ‘{/Symbol a}’

各种希腊字母与特殊符号的输入方法请见安装包中gnuplot-4.0.0/docs/psdoc目录下的ps_guide.ps文件。


另外还可参见：
http://t16web.lanl.gov/Kawano/gnuplot/label-e.html#4.3

 

- 如何设置坐标轴字体大小

```cpp
//设置刻度文本远离坐标轴
set xtics offset -3.5,0 font 'Times,19,Bold'
//设置刻度文本靠近坐标轴
set xtics offset 2.5,0  font 'Times,19,Bold'
//设置刻度文本加粗
set xtics font 'Bold'
```

- 设置绘图界面窗口

 指定显示格式，及窗口或者图片的大小、在屏幕中显示位置的命令为：

```cpp
set terminal <terminal_type> {size <width>, <height>} {position <x>, <y>}
```

`terminal_type`是上面terminal 显式样式，默认的就是`wxt`，是以交互式窗口的形式弹出来的；

width和height分别表示宽和高，单位是像素；

x和y一起表示在屏幕上的位置，单位同样是像素，0,0表示屏幕左上角，100,50表示窗口左上角以屏幕左上角为原点向右偏移100像素、向下偏移50像素。可以参考示例（我的屏幕分辨率为1920×1080）：

> gnuplot>set terminal wxt size 1000, 600 position 100, 50
>
> gnuplot>plot sin(x)



