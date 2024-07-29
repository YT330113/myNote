# sed编辑器

**stream editor**

流编辑器，根据事先设定好的规则编辑数据流

**1.【 替换(s)命令】**

替换斜杠之间的内容

```bash
sed 's/string1/string2/'
# 用 string2 来替换 string1
```

```bash
echo "This is a test" | sed 's/test/big test/'
This is a big test
```

```bash
sed 's/dog/cat/' data1.txt
# 把文件 data.txt 里的 dog 替换为 cat 输出
```

**注意：** sed不会修改原始文件，只是将修改后的数据输出到 STDOUT

**2.【每行替换多个】**

使用 `-e` 选项，命令之间以分号分隔

```bash
sed -e 's/brown/red/; s/dog/cat/' data1.txt
# 把文件 data.txt 里的 brown 替换为 red,再把 dog 替换为 cat 输出
```

**3. 【sed脚本】**

把大量的sed命令放在一个脚本文件里，例如`script1.sed`，通过 `-f` 参数执行sed脚本文件

```bash
$ cat script1.sed
s/brown/green/
s/fox/toad/
s/dog/cat/
```

```bash
$ sed -f script1.sed datda1.txt
```

**4.【更多替换选项】**

sed默认只替换每行的第一个数据字段，那如果一行有多个可以匹配的数据字段怎么办？使用替换标志

**四种替换标志：**

- 数字：指明替换第几处出现的文本
- g ：替换每行所有
- p ：指明打印替换后的行，常与`-n`选项配合
- w *file* ：将替换后的结果写入文件

> `-n`就是对没有匹配到的行产生输出抑制，什么叫匹配到的行？就是行号匹配的或内容匹配的；如果不抑制，sed会输出所有的行内容
>
> `-n`选项会抑制sed编辑器的输出，而替换标志`p`会输出替换后的行。二者配合的结果就是只输出被替换命令修改后的行.

```bash
# 把data4.txt文件里每行第二个出现的cat替换为dog
sed 's/cat/dog/2' data4.txt

# 把文本行中所有的cat都替换为dog
sed 's/cat/dog/g' data4.txt

# 只输出文件data.txt被替换的那一行
sed -n 's/cat/dog/p' data.txt

# 将文件data.txt替换后的那一行输出到文件test.txt中
sed 's/cat/dog/w test.txt' data.txt
```

**【其他打印命令】**

- `p`:打印文本行，注意P在前面是打印命令，在后面是打印标志
- `=`:打印行号，先打印行号再打印行内容
- `l`:列出行:打印出包含转义字符在内的所有字符，即Tab会打印成`\t`而不是四个空格

```bash
# 只打印匹配到“3rd line”的那一行
sed -n '/3rd line/p' data.txt

# 打印文件的2-3行
sed -n '2,3p' data.txt
```

**【写入文件】**

```bash
# 将文件data.txt的前两行输出到文件test.txt中
sed '1,2w test.txt' data.txt
```

**【向文件插入数据流】**

`r`命令

```bash
# 把文件data.txt文件的内容插入到文件data2.txt的第3行之后
sed '3r data1.txt' data2.txt

# 把文件data.txt文件的内容插入到文件data2.txt有“number 2”的那一行之后
sed '/number 2/r data1.txt' data2.txt

# 把文件data.txt文件的内容插入到文件data2.txt的末尾
sed '$r data1.txt' data2.txt


```



**5.【其他替代分隔符】**

sed命令除了使用正斜线`/`作为替换命令的分隔符外还可以使用其他字符，如感叹号`!`:

```bash
# 把/etc/passwd文件中的/bin/bash替换为/bin/csh
sed 's!/bin/bash!/bin/csh!' /etc/passwd
```

**6.【仅替换文件中的某一行---行寻址】**

- 特定行
- 行区间
- 到行尾（`$`符号 ）

```bash
# 仅把文件data.txt第二行的cat替换为dog
sed '2s/cat/dog/' data.txt

# 把文件data.txt第二行到第三行的cat替换为dog
sed '2,3s/cat/dog/' data.txt

# 把文件data.txt第二行到最后一行的cat替换为dog
sed '2,$s/cat/dog/' data.txt
```

**7.【文本模式匹配】**

除了使用行号来指定操作那些行外，还可以使用**`文本模式过滤`**

```bash
# 把/etc/passwd文件中有rich的那一行的bash替换为csh
sed '/rich/s/bash/csh/' /etc/passwd
```



**8.【命令组】**

在单行文本中执行多次替代命令，使用花括号`{}`将命令组合在一起

```bash
$ sed '{
> s/fox/toad/
> s/cat/dog/
}' data.txt
```

---

**9.【删除行】**

sed 除了替换功能，还具有删除功能 `d命令`

```bash
# 删除文件流data.txt的所有行
sed 'd' data.txt

# 删除文件流data.txt的第二行
sed '2d' data.txt

# 删除文件流data.txt的2-4行
sed '2,4d' data.txt

# 删除文件流data.txt的第二行到行尾
sed '2,$d' data.txt

# 删除文件流data.txt有dog存在的那一行
sed '/dog/d' data.txt
```

**10.【insert和add】**

- i，某一行前
- a，某一行后

```bash
# 在文件data.txt的第三行前插入一行This is an insert line.
$ sed '3i\
> This is an insert line.
> ' data.txt

# 在文件data.txt的第三行后附加一行This is an append line.
$ sed '3a\
> This is an append line.
> ' data.txt

# 在文件data.txt的末尾附加一行This is an append line.
$ sed '$a\
> This is an append line.
> ' data.txt

# 要插入多行时需要在新文本的末尾使用反斜线
$ sed '2i\
> This is an insert line1.\
> This is an insert line2.\
> This is an insert line3.
> ' data.txt
```

**【修改行】**

修改命令：`c`

```bash
# 把文件data.txt第二行修改为This is a changed line.
$ sed '2c\
> This is a changed line.
> ' data.txt

# 把文件data.txt含有dog的所有行修改为This is a changed line.
$ sed '/dog/c\
> This is a changed line.
> ' data.txt

# 使用地址区间时会把区间内所有行替换为指定的那一行
$ sed '2,4c\
> This is a changed line.
> ' data.txt
# 2-4行被一行This is a changed line.替换
```

**【转换命令】**

`y` :处理单个字符，把第一个`//`之间的单个字符替换为第二个`//`之间的单个字符

```bash
sed 'y/123/789/' data.txt
# 把data.txt文件中出现的每个1替换为7、每个2替换为8、每个3替换为9
```



# gawk编辑器

**1. 【数据字段变量】**

- \$0 代表整个文本行
- \$1 代表文本行中的第一个**数据子段**
- \$2 代表文本行中的第二个**数据子段**
- \$n 代表文本行中的第 n 个**数据子段**

```bash
$ cat data2.txt
one lines of test text.
two lines of test text.
three lines of test text.
```

```bash
$ gawk '{print $1}' data2,txt	# 显式每行的第一个数据字段
one
two
three
```

**2. 【-F参数制定别的字段分隔符】**

默认字段分隔符为空格

```bash
$ gawk -F: '{print $1}' /etc/passwd
# 指定冒号 ：为分隔符
```

**3.【多条命令】**

分号分隔

```bash
$ echo "My name is YT" | gawk '{$4="YanTao"; print $0}'
My name is YanTao
# 第一条命令为第四个字段赋新值，第二个命令打印整行
```

**4.【gawk脚本】**

```bash
$ cat script3.gawk
{
text = "'s home directory is " # 定义脚本变量保存文本字符串
print $1 text $6	# 打印第一个数据段、text 和第六个数据段
}
```

```bash
$ gawk -F: -f script3.gawk /tec/passwd
# -F指定分隔符为冒号
# -f指定执行脚本
```

**5.【在处理数据前后运行脚本】**

默认gawk会先从输入中读取一行，然后对这一行执行脚本。但有时希望在处理数据前先运行脚本，比如为报告创建一个标题。有时也希望在处理完数据后再执行脚本

```bash
BEGIN 关键字
END 关键字
```

```bash
$ gawk 'BEGIN {print "Title"}; {print $0};END {print "the end"}' data3.txt

# 再输出data3.txt文件前先输出一个Title,输出完文件内容后再输出一个the end
```

**6.【使用gawk脚本对文件创建一份漂亮的报告】**

```bash
yt@Ubuntu:~$ cat script4.gawk 
BEGIN {
print "The latest list of users and shells"
print "UserID    \t  Shell"
print "-------   \t  -------"
FS=":"
}

{
print $1 "	\t " $7
}

END {
print "This concludes the listing"
}
```

```bash
yt@Ubuntu:~$ gawk -f script4.gawk /etc/passwd
The latest list of users and shells
UserID    	  Shell
-------   	  -------
root		 /bin/bash
daemon		 /usr/sbin/nologin
bin		 /usr/sbin/nologin
sys		 /usr/sbin/nologin
sync		 /bin/sync
games		 /usr/sbin/nologin
man		 /usr/sbin/nologin
lp		 /usr/sbin/nologin
mail		 /usr/sbin/nologin
news		 /usr/sbin/nologin
...
```

