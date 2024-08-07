## 概念

- 设计树：每一次编辑操作都会排在设计树中
- 属性等菜单中的蓝色表示当前激活的菜单
- 同时打开几个模型：窗口--平铺
- 窗口也可以查看当前打开的所有模型

## 快捷键

- 鼠标中键：旋转视图
- 鼠标滚轮：放大缩小视图
- Ctrl+鼠标中键：平移视图

- 空格：视图定向---旋转不同的观察视图
- 鼠标右键按下并移动：快速添加尺寸或绘制圆及矩形

## 草图绘制

- 草图蓝色变黑色说明完全约束住了。完全约束不仅要约束所有线条尺寸还要约束与坐标原点的位置关系
- 草图约束除了尺寸约束还有草图几何关系，如水平，垂直，与原点重合等等
- 黄色是过定义了
- 尺寸约束：智能尺寸
  - 表角度：点两条线
  - 表水平或垂直约束：点击线条后水平或竖直方向移动
- 裁剪草图线条：裁剪实体--强劲裁剪
- 除了在基准平面绘制草图外，也可以在已有几何体的表面绘制
- 几何体的变现为细实线，草图的线为粗实线
- 把现有模型表现的线段提取到正在绘制的草图中：**转换实体引用**
- 转换实体引用不仅可以转换特征上的边线，也可以转换别的草图等
- 根据已有实体（草图，几何体等）的线条生成相距一定距离的线条：**等距实体**
- 尺寸
  - 驱动尺寸：黑色
  - 从动尺寸：灰色，

## 特征之拉伸凸台

- 拉伸的几个要素：以哪个草图从哪里拉伸到哪里
- 除了直接从草图基准面拉伸外，还可以从距草图一定距离的位置开始拉伸---等距
- 除了给定拉伸距离外还可以用以下选项指定拉伸截止的位置
  - 成形到下一面：拉伸碰到下一个面后就停止
  - 成形到一顶点：指定几何上的某一点作为拉伸截止位置
  - 成形到一面：指定几何上的某一面作为拉伸截止位置
  - 成形到实体
  - 到离指定面指定的距离
  - 两侧对称：两边都拉伸一样的距离

### 拉伸薄壁

就是把草图的外轮廓给一个厚度再拉伸，这样就形成了一个薄壁结构

--- 不用先拉伸凸台再拉伸切除了

## 特征之参考几何体

除了默认的三个基准面，还可以自己创建基准面

- 基准面
- 基准轴
- 坐标系
- 点等

默认基准面默认不可见（透明色），右击基准面后点击小眼睛就会变蓝（可见）

## 解决相关问题

1. 新建零件是找不到模板

   [默认模板无效](https://www.bilibili.com/video/BV1iw411Z7HZ/?p=5&spm_id_from=pageDriver&vd_source=0ca12f825d8b78e1adfff58fc2cbac3a)

