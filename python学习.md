- 创建项目
   new->project
- 创建pytho文件 
  new->python file
- 快捷键
  - 注释 `#+空格`
  - 注释多行以及取消注释多行 `ctrl+/`
  - 注释多行还可以用三个引号包含
  - 整块缩进 `tab`
  - 取消缩进 `shift+tab`
  - 查找 `ctrl+f`
  - 全局查找 `ctrl+shift+f`

- python 单引号和双引号无区别
- python 不用定义数据类型，int、char等
- python 用 `tab` 代替大括号分块, `tab`和空格不能混用
- 变量命名
  - myAge
  - my_age
- 强制类型转换
  - int(数字字符串)  数字字符转为数字
  - str（数字） 数字转为字符
- 运行一个新打开的文件时要右击运行，不能点右上角的三角
- 黄灯泡表示该行代码可以改进，按`ALT+enter`查看建议
- 按两下`shift`：search for everywhere
- python的6种数据类型
  - 数字 number
  - 字符串 string
  - 列表 list
  - 元组 tuple
  - 集合 set
  - 字典 dictiona
- 元组与列表区别

操作|列表|元组
:-:|:-:|:-:
表达形式|方括号|圆括号
其中元素是否可变|可以|不可以
访问元素|方括号|方括号
修改元素值|可修改单个元素|不能修改单个元素，要改只能重新定义元组覆盖掉之前的

- for循环

```python

names = ['张三', '李四', 'wangwu', 'zhaoliu']

print('hello 张三')
print('hello 李四')
print('hello wangwu')
print('hello zhaoliu')
print('\n')

for name in names:              # 注意冒号和缩进
    print('hello, ', name)

for index in range(len(names)):     # 效果同上一句
    print('你好， ', names[index])

range(4)            # range(4)代表[0,4),左开右闭区间，相当于0，1，2，3，4
range(0, 100, 10)   # range(0, 100, 10)代表0，10，20，30，40，...，90

for num in range(4):
    print(num)
for num in range(0, 100, 10):
    print(num)


```

- while循环

```py
num = 0

# while (num<10):             # 死循环
#     print('num: ', num)

while (num<10):     # 括号可以去掉
    print('num: ', num)
    num += 1        # 同num=num+1
print('\n', num)

num = 0
while (num < 10):
    num += 1
    if num % 2 == 0:        # 输出单数,不等于是 ！=
        continue            # 跳出本次循环
        # break             # 跳出整个循环
    print('num: ', num)



```
- list列表

```python

import numpy as np

names = ['张三', '李四', 'wangwu', 'zhaoliu']
print(names)

# 访问列表
Grades = [30, 40, 50, 90]
print(Grades)       # 访问所有元素
print(Grades[0])        # 访问第一个元素
print(Grades[-1])        # 访问最后一个元素
print(Grades[-2])        # 访问倒数第二个元素

# 操作列表
Grades[0] = 1000        # 修改数据
print(Grades)
Grades.append(90)       # 末尾增加数据
print(Grades)
Grades.insert(0, 20)    # 插入数据
print(Grades)
Grades.pop(0)           # 删除第一个位置的数字
print(Grades)
Grades.remove(90)       # 删掉指定元素
print(Grades)
print(len(Grades))        # 输出列表长度

# 列表排序
# Grades.sort()       # 永久排序,即改变列表
print(Grades)
names.sort()
print(names)
print(sorted(Grades))       # 临时排序，不改变列表
print(Grades)
Grades.reverse()        # 反转，即倒序排列
print(Grades)


# 列表进阶
names = ['张三', '李四', 'wangwu', 'zhaoliu', '吴七']
print(names, '\n')

# 列表切片
list1 = names[0:2]      # 列表的前两个，相当于[0,2)
list2 = names[:2]       # 列表的前两个

print(list1, '\n')
print(list2, '\n')

list3 = names[-3:]      # 列表后三个
print(list3, '\n')

list4 = names[2:]      # 列表第二个到最后一个，注意：从第0个开始
print(list4, '\n')

list5 = names[2:4]      # 列表第二个到第四个，注意：[2,4)
print(list5, '\n')

# 列表遍历
for name in names[:3]:
    print('HELLO, ', name)

# 复制列表
new_list = names         # 不能这样简单赋值，原来列表改变的化新的列表也会跟着改变，两个相当于一个东西
print('new_list: ', new_list)

new_list1 = names[:]    # [:]表示从第一个到最后一个
print('new_list1: ', new_list1)

names[0] = 'zhangsan'
print('new_list: ', new_list)           # new_list随names的改变而改变
print('new_list1: ', new_list1)         # new_list1不随names的改变而改变


# 二维列表
# numpy函数,python对一维列表很好，但多维支持不是很好，多维时numpy必不可少
# 创建
ArrayList = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
print(ArrayList[0][2])      # 打印第一行第三列！

ArrayList2 = [[i for i in range(1, 7)] \
              for j in range(1, 7)]             # \+回车表示还是一行
print('ArrayList2: ', ArrayList2)

# newArrayList = ArrayList[0, :]              # 想输出数组的第一行，但这样写会报错，要导入numpy
newArray = np.array(ArrayList)
newArray2 = newArray[0, :]              # 第一行
newArray3 = newArray[:, 0]              # 第一列

print(newArray)
print(newArray2)
print(newArray3)


```

- if语句
  - `if True` 大写
  - `if False` 大写

```python
# 体味 python 解释性语言的特点

list = [12, 13, 14, 15]
if 13 in list:
    print('yes')
if 16 not in list:
    print('no')

```
- 读写文件
  - w:写入，会清空之前的再写入 `with open(filename,'w') as file:`
    - 如果文件名不存在，会自动创建文件
  - r:只读 `with open(filename,'r') as file:`，只读时 r 可以省略
  - a:附加内容,相当于不清空内容的写入

```python
import matplotlib.pyplot as plt
with open('test.txt', encoding='utf-8') as file:      # 注意冒号,encoding='utf-8'表示可以读中文编码
    # 读取文件
    # contents = file.read()
    # print(contents)           # 输出整个文件

    # 通过for循环访问各行          # 逐行输出
    # for line in file:
    #     print('line: ', line)

    # 用readlines()函数读取，返回一个列表   #逐行输出
    # contents = file.readlines()
    # print(contents)

    # 对文件进行处理，得到每个月的营业额
    contents = file.readlines()         # contents得到一个列表，但是每行都有一个\n
    print(contents)
    # 删掉\n，即去掉字符串中的某个字符
new_list = []
for content in contents:
    newContent = content.replace('\n', '')      # replace函数，替换字符
    new_list.append(newContent)                 # 赋值后输出新列表
print(new_list)
# 提取每行中的数字
# 字符分割函数split（）
new_list = []
for content in contents:
    newContent = content.replace('\n', '')   # replace函数，替换字符
    money = newContent.split('：', )[-1]   # split函数，将字符串分割为冒号前后两部分,-1表示取后面一部分
    new_list.append(int(money))            # 将读取出的字符串数字转换为整形
print(new_list)

# 画图
y = new_list
x = [1, 2, 3, 5, 6]
plot = plt.plot(x, y, '^r')
plot = plt.plot(x, y, '-r')
plt.xlabel('month')
plt.ylabel('money')
plt.savefig('销售额.png')
plt.legend()
plt.show()

# 求平均值
average = sum(new_list) / len(new_list)
print('average: ', average)


```

- python 函数
  - 有颜色的是系统函数
  - 自己写的函数无颜色

```py

def f(x):           # def定义函数，f（x）函数名
    y = k*x + b
    return y        # 返回值
y=f(3)

# 位置参数和关键字参数
def f(x1，x2):           
    y = k*x1 + x2
    return y

y1 = f(3,4)                 # 位置参数，按照顺序对应
y2 = f(x1 = 3,x2 = 4)       # 关键字参数，按照名称对应，顺序可不对应

# 关于返回值：意义对应
def f(x1，x2):           
    y1 = k*x1 + b
    y2 = k*x2 + b
    return y1,y2

y1,y2 = f(x1 = 1，x2 = 2)   # 会分别对应上
y = f(x1 = 1，x2 = 2)       # 会输出一个元组，(y1,y2)


```

- 类：用来描述具有相同属性和方法的对象的集合；
  - 它定义了集合中每个对象所共有的属性和方法（函数）
  - 对象是类的实例
  - 类中的函数被称为方法
  - 一个类会包含很多函数
  - 类的输入参数写在类的构造函数的括号里，而不是类名的括号里 
  - 构造函数：`__init__()`,当创建了类的实例时会直接调用构造函数进行初始化
  - 子类可添加方法，也可重新定义父类中的方法
- 导入类和函数：一般一个文件中只定义一个类
  - 从Animal.py文件中导入Animal类
    - `from Animal import Animal`
  - 从dog_fun.py导入所有
    - `from dog_fun import *`
  - `import numpy as np`

```py
# 定义类
class Dog():
    def __init__(self, name, age):          # 初始化函数，构造函数
        self.name = name                    # self表示这个变量的作用域是整个类，self.name在整个类的所有函数中都可用
        self.age = age

    def sit(self):                  # 这里的self表示定义的这个函数的作用域是整个类
        print(self.name + " is sitting now.")

    def eat(self, food):
        '''                     # 函数注释，输入三个引号’‘’回车自动生成
        这里写函数实现的功能
        :param food: 这里解释参数food的含义
        :return: 这里解释返回值指的是什么
        '''
        print(self.name + " is now eatting " + food)

dog = Dog("beibei", 3)              # 类实例化

dog.sit()
dog.eat('apple')



```
```py
# 类继承
# 父类
class Animal():
    def __init__(self, name, age):          # 初始化函数，构造函数
        self.name = name                    # self表示这个变量的作用域是整个类，self.name在整个类的所有函数中都可用
        self.age = age

    def eat(self, food):                  # 这里的self表示定义的这个函数的作用域是整个类
        print(self.name + " is now eatting "+food)

# 子类
class Dog(Animal):          # 定义类Dog，括号里边表示它继承的Animal类
    def __init__(self, name, age, type):     # 子类的构造函数
        super().__init__(name, age)            # 表示继承的父类的构造函数，相当于借用父类已经定义好的name和age
        self.type = type
    def get_character(self):
        if self.type == '狮子狗':
            print(self.name+' is a '+self.type)

my_dog = Dog('beibei', 12, '狮子狗')
my_dog.eat('apple')
my_dog.get_character()


```

- 字典
  - 就像查字典一样，一系列“键值对”组成了字典，通过键（key）可以查到值（value）
  - 大括号{}
  - 数据含义信息多样且复杂时使用字典更方便
  - key一般是字符串和数字，建议用英文
  - value可以是任何类型
  - key值不能重复
