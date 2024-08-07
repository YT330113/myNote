一、内存
===

在计算机中，每个应用程序之间的内存是相互独立的，通常情况下应用程序 A 并不能访问应用程序 B，当然一些特殊技巧可以访问，但此文并不详细进行说明。例如在计算机中，一个视频播放程序与一个浏览器程序，它们的内存并不能访问，每个程序所拥有的内存是分区进行管理的。

在计算机系统中，运行程序 A 将会在内存中开辟程序 A 的内存区域 1，运行程序 B 将会在内存中开辟程序 B 的内存区域 2，内存区域 1 与内存区域 2 之间逻辑分隔。

1.1 内存四区
---
在程序 A 开辟的内存区域 1 会被分为几个区域，这就是内存四区，内存四区分为**栈区、堆区、数据区与代码区。**

- ***栈区***  指的是存储一些<u>临时变量</u>的区域，临时变量包括了<u>局部变量、返回值、参数、返回地址</u>等，当这些变量超出了当前作用域时将会自动弹出。该栈的最大存储是有大小的，该值固定，超过该大小将会造成栈溢出。

- ***堆区***  指的是一个比较大的内存空间，主要用于<u>对动态内存的分配</u>；在程序开发中一般是开发人员进行分配与释放，若在程序结束时都未释放，系统将会自动进行回收。

- ***数据区***  指的是主要<u>存放全局变量、常量和静态变量的区域</u>，数据区又可以进行划分，分为全局区与静态区。全局变量与静态变量将会存放至该区域。

- ***代码区***  就比较好理解了，主要是<u>存储可执行代码</u>，该区域的属性是只读的。

  

## 1.2 内存四区的底层结构

---
- 栈区的数据存储结构为先进后出
- 先存储的变量地址索引将会是最大的，随后依次减少
- 同一个栈内变量的地址索引是连续的
- 静态变量的地址与一般变量的地址不存在连续，静态变量存储在静态区内
- 栈区、数据区都是使用栈结构对数据进行存储。
- 栈的容量具有固定大小，超过最大容量将会造成栈溢出。在平常开发中若需要大容量的内存，需要使用**堆**。例如

```cpp
    #include<stdio.h>
    #include<string.h>
    #include <malloc.h>
    int main()
    {
    char *p1 = (char *)malloc(1024*1000000);// malloc返回的类型不确定，通过接收的指针变量从而进行类型的转换
    strcpy(p1, "这里是堆区");
    printf("%s\n", p1);
    }
```
```
以上代码中使用了strcpy 往手动开辟的内存空间 p1 中传数据“这里是堆区”，手动开辟空间使用 malloc，传入申请开辟的空间大小 1024*1000000，在栈中那么大的空间必定会造成栈溢出，而堆本身就是大容量，则不会出现该情况。
```
- 堆并没有栈一样的结构，也没有栈一样的先进后出。需要人为的对内存进行分配使用。

二、malloc 和 free
===
在 C 语言（不是 C++)中，`malloc` 和` free` 是系统提供的函数，成对使用，用于从堆中分配和释放内存。`malloc` 的全称是 `memory allocation` 译为“**动态内存分配**”。

2.1 malloc 和 free 的使用
---
在开辟堆空间时我们使用的函数为 `malloc`，`malloc` 在 C 语言中是用于申请内存空间，`malloc` 函数的原型如下：

```c
void *malloc(size_t size);
```

在` malloc` 函数中，`size` 是表示需要申请的内存空间大小，<u>申请成功将会返回该内存空间的地址；申请失败则会返回 NULL</u>，并且申请成功也不会自动进行初始化。

细心的同学可能会发现，该函数的返回值说明为 `void *`，在这里 <u>`void * `并不指代某一种特定的类型，而是说明该类型不确定，通过接收的指针变量从而进行类型的转换</u>。

在分配内存时需要注意，即使在程序关闭时系统会自动回收该手动申请的内存 ，但也要进行手动的释放，保证内存能够在不需要时返回至堆空间，使内存能够合理的分配使用。
释放空间使用 free 函数，函数原型如下：

```c
void free(void *ptr);
```

`free` 函数的返回值为 `void`，没有返回值，接收的参数为使用 `malloc` 分配的内存空间指针。一个完整的堆内存申请与释放的例子如下：

```C++
#include<stdio.h>
#include<string.h>
#include <malloc.h>

int main() {
    int n, *p, i;
    printf("请输入一个任意长度的数字来分配空间:");
    scanf("%d", &n);
    
    p = (int *)malloc(n * sizeof(int));
     if(p==NULL){
      printf("申请失败\n");
      return 0;
     }
    else{
  printf("申请成功\n");
 } 
 
 memset(p, 0, n * sizeof(int));//填充0 
 
 //查看 
    for (i = 0; i < n; i++)
        printf("%d ", p[i]);
    printf("\n");

    free(p);
    p = NULL;
    return 0;
}
```
以上代码中使用了 `malloc` 创建了一个由用户输入创建指定大小的内存，判断了内存地址是否创建成功，且使用了 `memset 函数`对该内存空间进行了填充值，随后使用` for `循环进行了查看。最后使用了 `free` 释放了内存，并且将` p` 赋值 `NULL`，这点需要主要，**不能使指针指向未知的地址，要置于 NULL**。**否则在之后的开发者会误以为是个正常的指针，就有可能再通过指针去访问一些操作，但是在这时该指针已经无用，指向的内存也不知此时被如何使用，这时若出现意外将会造成无法预估的后果，甚至导致系统崩溃。**

2.2 内存泄漏
---
**内存泄漏是指在动态分配的内存中，并没有释放内存或者一些原因造成了内存无法释放，轻度则造成系统的内存资源浪费，严重的导致整个系统崩溃等情况的发生。**

内存泄漏通常比较隐蔽，且少量的内存泄漏发生不一定会发生无法承受的后果，但由于该错误的积累将会造成整体系统的性能下降或系统崩溃。特别是在较为大型的系统中，如何有效的防止内存泄漏等问题的出现变得尤为重要。例如一些长时间的程序，若在运行之初有少量的内存泄漏的问题产生可能并未呈现，但随着运行时间的增长、系统业务处理的增加将会累积出现内存泄漏这种情况；这时极大的会造成不可预知的后果，如整个系统的崩溃，造成的损失将会难以承受。由此防止内存泄漏对于底层开发人员来说尤为重要。

C 程序员在开发过程中，不可避免的面对内存操作的问题，特别是频繁的申请动态内存时会及其容易造成内存泄漏事故的发生。如申请了一块内存空间后，未初始化便读其中的内容、间接申请动态内存但并没有进行释放、释放完一块动态申请的内存后继续引用该内存内容；如上所述这种问题都是出现内存泄漏的原因，往往这些原因由于过于隐蔽在测试时不一定会完全清楚，将会导致在项目上线后的长时间运行下，导致灾难性的后果发生。

三、 new 和 delete
===
C++ 中使用 `new` 和 `delete` 从堆中分配和释放内存，==**new 和 delete 是运算符，不是函数**==，两者成对使用(后面说明为什么成对使用)。

`new/delete `除了分配内存和释放内存（与 malloc/free），还做更多的事情，所有在 C++ 中不再使用 malloc/free 而使用 new/delete。

3.1 new 和 delete 使用
---
new 一般使用格式如下：

```cpp
指针变量名 = new 类型标识符;
指针变量名 = new 类型标识符(初始值);
指针变量名 = new 类型标识符[内存单元个数];
```



在C++中new的三种用法包括：plain new， nothrow new 和 placement new。

**使用 new 生成一个类对象时系统会调用该类的构造函数，使用 delete 删除一个类对象时，系统会调用该类的析构函数。**可以调用构造函数/析构函数就意味着 <u>`new` 和 `delete` 具备针对堆所分配的内存进行初始化和释放的能力，而 `malloc` 和` free` 不具备。</u>

3.2 delete 与 delete[] 的区别
---
- delete 释放 new 分配的**单个对象**指针指向的内存
- delete[] 释放 new 分配的**对象数组**指针指向的内存

```C++
delete a;        //方式1
delete[] a;     //方式2
```
1. 针对简单类型 使用 new 分配后的不管是数组还是非数组形式内存空间用两种方式均可 如：
```C++
int *a = new int[10];
delete a;
delete[] a;
```
此种情况中的释放效果相同，原因在于：分配简单类型内存时，内存大小已经确定，系统可以记忆并且进行管理，在析构时，系统并不会调用析构函数。它直接通过指针可以获取实际分配的内存空间，哪怕是一个数组内存空间(在分配过程中 系统会记录分配内存的大小等信息，此信息保存在结构体` _CrtMemBlockHeader` 中，具体情况可参看 `VC` 安装目录下 `CRTSRCDBGDEL.cpp`)。

2. 针对类 Class，两种方式体现出具体差异
```C++
class A
   {
    private:
      char *m_cBuffer;
      int m_nLen;

   `` public:
      A(){ m_cBuffer = new char[m_nLen]; }
      ~A() { delete [] m_cBuffer; }
   };

   A *a = new A[10];
   delete a;         //仅释放了a指针指向的内存空间 但是只调用了a[0]对象的析构函数 剩下的从a[1]到a[9]这9个用户自行分配的m_cBuffer对应内存空间将不能释放 从而造成内存泄漏
   delete[] a;      //调用使用类对象的析构函数释放用户自己分配内存空间并且释放了a指针指向的全部内存空间
```
   所以总结下就是，如果 `ptr` 代表一个用`new`申请的内存返回的内存空间地址，即所谓的指针，那么：

`delete ptr`  代表用来释放内存，且只用来释放 `ptr` 指向的内存。`delete[]   ptr`用来释放`ptr`指向的一片内存，！！还逐一调用数组中每个对象的`destructor`！！

对于像 `int/char/long/int*/struct` 等等简单数据类型，由于对象没有 `destructor` ，所以用 `delete` 和 `delete []`是一样的！但是如果是 C++ 对象数组就不同了！

关于 `new[]` 和 `delete[]`，也分为两种情况：

(1) 为基本数据类型分配和回收空间；
(2) 为自定义类型分配和回收空间；

对于 (1)，上面提供的程序已经证明了 delete[] 和 delete 是等同的。但是对于 (2)，情况就发生了变化。

我们来看下面的例子，通过例子的学习了解 C++ 中的 delete 和 delete[] 的使用方法
```C++
#include <iostream>
using namespace std;

class Babe
{
public:
    Babe()
    {
        cout << \"Create a Babe to talk with me\" << endl;
    }

    ~Babe()
    {
        cout << \"Babe don\'t Go away,listen to me\" << endl;
    }
};

int main()
{
    Babe* pbabe = new Babe[3];
    delete pbabe;
    pbabe = new Babe[3];
    delete[] pbabe;
    return 0;
}
```
结果是
```C++
Create a babe to talk with me
Create a babe to talk with me
Create a babe to talk with me
Babe don\'t go away,listen to me
Create a babe to talk with me
Create a babe to talk with me
Create a babe to talk with me
Babe don\'t go away,listen to me
Babe don\'t go away,listen to me
Babe don\'t go away,listen to me
```

只使用 delete 的时候只出现一个 `Babe don’t go away`,`listen to me，`而使用 delete[] 的时候出现 3 个 `Babe don’t go away,listen to me。`不过不管使用 delete 还是 delete[] 那三个对象的在内存中都被删除，==既存储位置都标记为可写==，但是使用 delete 的时候只调用了 pbabe[0] 的析构函数，而使用了 delete[] 则调用了 3 个 Babe 对象的析构函数。

你一定会问，反正不管怎样都是把存储空间释放了，有什么区别。

关键在于调用析构函数上。此程序的类没有使用操作系统的系统资源（比如：`Socket`、`File`、`Thread`等），所以不会造成明显恶果。如果你的类使用了操作系统资源，单纯把类的对象从内存中删除是不妥当的，因为**没有调用对象的析构函数会导致系统资源不被释放，这些资源的释放必须依靠这些类的析构函数**。所以，在用这些类生成对象数组的时候，用 `delete[] `来释放它们才是王道。而用 `delete` 来释放也许不会出问题，也许后果很严重，具体要看类的代码了。

---



[小飞有点东西的主页 - 抖音 (douyin.com)](https://www.douyin.com/user/MS4wLjABAAAArWzY2yAKXPc64dT-6ycMJ1hbIFY4-kr-kdzLNUJZyIM?modal_id=7037056151455862029&vid=7217009310734290233)

# 小飞有点东西 

## 内存管理机制 – 垃圾回收机制

**垃圾：**通过变量名可以找到定义的变量时这块内存不是垃圾，此时这个变量值是可以顺着变量名引用到的；一旦某块内存没有捆绑任何变量名时就无法找到这个变量了，既然找不到他了他还占着空间就不合适了，这就是垃圾。

**垃圾回收机制**就是用来回收这种没有关联任何变量名的值，此时涉及到一个概念叫 **引用计数** ，就是统计引用的个数。引用计数指的是这个值身上，也就是这块内存空间的身上捆绑了几个变量名。捆绑了几个他的引用计数就为几。

```python
# 引用计数的增加
a=10
b=a
c=a
```

以上代码在内存中的形式：

<img src="image/引用计数.png" alt="引用计数" style="zoom:50%;" />