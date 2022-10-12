# Linux学习

## The Shell

**bash : Bourne Again Shell***

```yantao@yantao-virtual-machine:~$ ``` 冒号前面是主机名，当前所在的位置是 `~` (表示 “home”);`$`符号表示您现在的身份不是 root 用户.

类似于 Python 或 Ruby，shell 是一个编程环境，所以它具备变量、条件、循环和函数。当你在 shell 中执行命令时，您实际上是在执行一段 shell 可以解释执行的简短代码。如果你要求 shell 执行某个指令，但是该指令并不是 shell 所了解的编程关键字，那么它会去咨询 环境变量 `$PATH`,`echo $PATH`命令可显示当 shell 接到某条指令时，进行程序搜索的路径。当我们执行 `echo` 命令时，shell 了解到需要执行 `echo` 这个程序，随后它便会在 `$PATH` 中搜索由 `:` 所分割的一系列目录，基于名字搜索该程序。当找到该程序时便执行（假定该文件是 **可执行程序**)。

确定某个程序名代表的是哪个具体的程序，可以使用 `which` 程序。
```bash
yantao@yantao-virtual-machine:~$ which echo 
/bin/echo
```

也可以绕过 `$PATH`，通过直接指定需要执行的程序的路径来执行该程序。
```bash
yantao@yantao-virtual-machine:~$ echo hello
hello

yantao@yantao-virtual-machine:~$ /bin/echo hello
hello
```
shell 中的路径是一组被分割的目录，在 Linux 和 macOS 上使用 `/` 分割，而在Windows上是 `\`。

路径 `/` 代表的是**系统的根目录**，所有的文件夹都包括在这个路径之下，在Windows上每个盘都有一个根目录（例如： C:\）。

如果某个路径以 / 开头，那么它是一个 ==**绝对路径**==，其他的都是 ==**相对路径**== 。相对路径是指相对于当前工作目录的路径
```bash
yantao@yantao-virtual-machine:~$ ls
core  examples.desktop  MTO  OpenFOAM  openmpi  OpenMPI  PETSc  snap  swak4Foam  公共的  模板  视频  图片  文档  下载  音乐  桌面
yantao@yantao-virtual-machine:~$ cd /
yantao@yantao-virtual-machine:/$ ls
bin   cdrom  etc   initrd.img      lib    lost+found  mnt  proc  run   snap  swapfile  tmp  var      vmlinuz.old
boot  dev    home  initrd.img.old  lib64  media       opt  root  sbin  srv   sys       usr  vmlinuz
```

当前工作目录可以使用 `pwd` 命令来获取。此外，切换目录需要使用 `cd `命令。在路径中，`.` 表示的是当前目录，而 `..` 表示上级目录：
```bash
yantao@yantao-virtual-machine:~$ pwd
/home/yantao
```

shell 会实时显示当前的路径信息。一般来说，当我们运行一个程序时，如果我们没有指定路径，则该程序会在当前目录下执行。

大多数的命令接受标记和选项（带有值的标记），它们以 - 开头，并可以改变程序的行为。通常，在执行程序时使用 -h 或 --help 标记可以打印帮助信息，以便了解有哪些可用的标记或选项。

如果您想要知道关于程序参数、输入输出的信息，亦或是想要了解它们的工作方式，请试试 man 这个程序。它会接受一个程序名作为参数，然后将它的文档（用户手册）展现给您。注意，使用 q 可以退出该程序。
```bash
yantao@yantao-virtual-machine:~$ man ls

```

在 shell 中，程序有两个主要的“流”：它们的输入流和输出流。 当程序尝试读取信息时，它们会从输入流中进行读取，当程序打印信息时，它们会将信息输出到输出流中。 通常，一个程序的输入输出流都是您的终端。也就是，您的键盘作为输入，显示器作为输出。 但是，我们也可以==重定向==这些流！
最简单的重定向是 `< file` 和 `> file`。这两个命令可以将程序的输入输出流分别重定向到文件：

```bash
yantao@yantao-virtual-machine:~$ echo hello >hello.txt
yantao@yantao-virtual-machine:~$ cat hello.txt 
hello
yantao@yantao-virtual-machine:~$ cat <hello.txt 
hello
yantao@yantao-virtual-machine:~$ cat <hello.txt >hello2.txt
yantao@yantao-virtual-machine:~$ cat hello2.txt 
hello
```

`#` 在Bash中表示注释

## 常用命令

- cat 相当于vi，但是不能编辑

  - cat -n ：由 1 开始对所有输出的行数编号。

- 左键选中，中间粘贴

- 命令后加&表示后台运行

- pwd 查看当前操作文件路径

- ls 列出当前文件下所有的文件

  - 蓝色的是文件夹，白色的是文件

  - ls *.XXX：列出所有XXX类型的文件
  - ls X*：列出以X开头的文件

  - ？也有与 * 类似的作用，但是==*可代表多个字符，？只代表一个字符==

- `cd`：打开文件夹/切换路径

- `cd..`：打开上一级路劲

  . 代表当前目录
  .. 代表上一级目录
  ~ 代表home目录

- tab：自动补全

  - 按两次会显示所有开头相同的文件或文件夹

- 方向键上：可以复制之前的命令

- 方向键左右：移动光标

- clear ：清屏

- cd~ ：直接回到home目录

- 以 . 开头的文件是隐藏文件

  - ls - a 打开隐藏文件


- touch ：创建文件
- mkdir ：创建目录
- rm：移除文件
- rm -d ：移除目录


- mv：移动文件/剪切
- ==cp：复制文件==
  - cp [options] source dest
  - -a：此选项通常在复制目录时使用，它保留链接、文件属性，并复制目录下的所有内容。其作用等于dpR参数组合。
  - -d：复制时保留链接。这里所说的链接相当于 Windows 系统中的快捷方式。
  - -f：覆盖已经存在的目标文件而不给出提示。
  - -i：与 -f 选项相反，在覆盖目标文件之前给出提示，要求用户确认是否覆盖，回答 y 时目标文件将被覆盖。
  - -p：除复制文件的内容外，还把修改时间和访问权限也复制到新文件中。
  - ==-r==：若给出的源文件是一个目录文件，此时将复制该目录下所有的子目录和文件。
  - -l：不复制文件，只是生成链接文件。


- 打开文件

  - 命令：vi 文件名
   - 示例：打开当前目录下的aa.txt文件     vi aa.txt 或者 vim aa.txt

   - 注意：***使用vi编辑器打开文件后，并不能编辑，因为此时处于命令模式，点击键盘i/a/o进入编辑模式。***

## vi编辑器

***vi编辑器的3种模式***

基本上vi可以分为三种状态，分别是==命令模式==（command mode）、==插入模式==（Insert mode）和==底行模式==（last line mode），各模式的功能区分如下：

- 命令行模式command mode）

  控制屏幕光标的移动，字符、字或行的删除，查找，移动复制某区段及进入Insert mode下，或者到 last line mode。
  命令行模式下的常用命令：

  1. 控制光标移动：↑，↓，j
  2. 删除当前行
  3. 查找：/字符
  4. ***进入编辑模式：i o a***
  5. 进入底行模式：:

 - 编辑模式（Insert mode）

   只有在Insert mode下，才可以做文字输入，==按「ESC」键可回到命令行模式。==

   -  ESC 退出编辑模式到命令行模式；

 - 底行模式（last line mode）
   将文件保存或退出vi，也可以设置编辑环境，如寻找字符串、列出行号……等。
   底行模式下常用命令：

   - 退出编辑：   :`q`
   - 强制退出：   :`q!`
   - 保存并退出：  :`wq`

---

- 打开文件
  - 命令：vi 文件名
   - 示例：打开当前目录下的aa.txt文件     vi aa.txt 或者 vim aa.txt

   - 注意：使用vi编辑器打开文件后，并不能编辑，因为此时处于命令模式，点击键盘i/a/o进入编辑模式。

- 编辑文件

  - 使用vi编辑器打开文件后点击按键：
    - i:在光标所在字符前开始插入
    - a:在光标所在字符后开始插入
    - o:在光标所在行的下面另起一新行插入


- 保存文件：

  - 第一步：ESC  进入命令行模式
  - 第二步：:     进入底行模式
  - 第三步：wq     保存并退出编辑

- 取消编辑：

  - 第一步：ESC  进入命令行模式
  - 第二步：`:`    进入底行模式
  - 第三步：`q!`     撤销本次修改并退出编辑

---

## vim使用

终端输入`vimtutor`即有教程

**01**

 1. **光标在屏幕文本中的移动**既可以用箭头键，也可以使用 hjkl 字母键。
       h (左移)       j (下行)       k (上行)     l (右移)

  2. 欲进入 Vim 编辑器(从命令行提示符)，请输入：`vim 文件名 <回车>`

  3. 欲退出 Vim 编辑器，请输入 `<ESC> `  `:q! `  `<回车>` 放弃所有改动。
       或者输入` <ESC>   :wq   <回车>` 保存改动。

  4. 在正常模式下**删除光标所在位置的字符**，请按：` x`

  5. 欲插入或添加文本，请输入：

       `i`   输入欲**插入**文本   `<ESC>`             在光标前插入文本

      `A`     输入欲**添加**文本   `<ESC>`            在一行后添加文本

特别提示：按下 `<ESC>` 键会带您回到正常模式或者撤消一个不想输入或部分完整的命令。

**02**

  1. 欲从当前光标**删除至下一个单词**，请输入：`dw`
   2. 欲从当前光标**删除至当前行末尾**，请输入：`d$`
   3. 欲**删除整行**，请输入：`dd`

   4. 欲重复一个动作，请在它前面加上一个数字：2w
   5. 在正常模式下修改命令的格式是：
        operator   [number]   motion
      其中：
        operator - 操作符，代表要做的事情，比如 d 代表删除
        [number] - 可以附加的数字，代表动作重复的次数
        motion   - 动作，代表在所操作的文本上的移动，例如 w 代表单词(word)，
                   $ 代表行末等等。
   6. 欲**移动光标到行首**，请按数字0键：`0`
   7. 欲**撤消**以前的操作，请输入：`u `(小写的u)
      **欲撤消在一行中所做的改动**，请输入：`U `(大写的U)
      欲**撤消以前的撤消命令**，恢复以前的操作结果，请输入：`CTRL-R`

## GDB调试器

使用GDB必须要有可调式信息，通过为gcc编译器加上-g或-ggdb参数来生成带调试信息的可执行程序

```bash
gcc 123.c -g
```

- 启动可调式程序

```bash
gdb 可执行文件的名字
```

- gdb调试命令	
  - l	list,显示多行源代码
  - b    break,设置断点
  - r    run，开始执行程序
  - s    step，执行下一条，会进入子函数
  - n    next，执行下一句，不进入函数
  - c    continue，继续运行程序直到新断点
  - q    quit，退出GDB调试环境
  - p    print，打印变量值

- 实际使用流程

  ```bash
  gcc xxx.c -g
  gdb xxx.out
  l #列出程序的内容
  b 函数名字/行号 #设置断点，例如 b main 在main那行停下来
  r # 运行程序，会在断点处停下
  n # 下一步（不进入子函数），按第一n会先显示下一句要执行的命令，再按n才会执行那句
  p 变量名 # 打印当前变量的值
  s # 下一步（进入子函数）
  q # 退出GDB环境
  
  ```

  

