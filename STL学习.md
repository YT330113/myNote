# C++ STL

模板的意义就在于泛化数据类型，不因为数据类型的多样性而不能书写通用代码；忽略掉数据类型的影响，尽量泛化程序

## 函数模板

==函数模板并非函数！！！==

### 函数模板的定义

```cpp
template<class 类型形参1， class 类型形参2，...>
    返回值类型 函数模板名(调用形参1， 调用形参2，...){
    ...
}

template<class T>//关键字也可以用typename替代
    T Max(T x,T y){
    return x>y?x:y; 
}
```

> 小括号里的参数表叫==调用参数==表
>
> 尖括号里的叫==类型参数==表，类型参数前必须跟一个关键字class；
>
> 调用形参接收的是数据，类型参数接收的不是数据而是类型，例如int、double

### 函数模板使用

==使用函数模板必须对函数模板进行实例化==

实例化就是把真实的类型参数传给函数模板的类型形参

```cpp
形式：
函数模板名<类型实参1, 类型实参2， ...> （调用实参1， 调用实参2， ...）; 
    
例如：   
Max<int>(123, 456);
Max<double>(12.3, 45.6);
Max<string>("hello", "world");  
```

### 函数模板的本质

编译器并不是把函数模板编译成一个可以处理任何数据的单一实体，函数模板不能理解为一个函数，只能理解为一个模子用于在特定的时刻按照模子生成实体函数；

编译器一看到`Max<int>`就会依据函数模板生成一个实体函数`int Max(int x, int y){...}`，函数模板相当于人和编译器的一个约定；

函数模板只有通过实例化才能产生真正的函数，实例化话就是用具体数据类型替换函数模板类型形参的过程；

实例化是自动的不用程序员额外请求对函数模板的实例化，只要使用函数模板即一出现`Max<int>`就会自动引发实例化；

### 实例化函数模板的条件

要用一个类型实例化函数模板，这个类型必须支持函数模板要执行的操作；

例如：一个不支持">"运算符的类型是不可能实力化函数模板的

这种情况一般是自己定义的类没有对特定的运算符进行重载，要实力化类类型的函数模板就必须对该类进行相应的运算符重载；

```cpp
class Integer{
public:
    Integer(int i):m_i(i){}
private:
    int m_i;
};

Max<Integer>(ix, iy);//显然是不能实例化的，因为这个自定义类是不能做>运算的 

//要想可以实例化，就必须对Integer类进行">"的运算符重载
class Integer{
public:
    Integer(int i):m_i(i){}
    bool operator>(Integer const& that)const{//重载运算符后便可以用Integer实例化Max<Integer>(ix, iy);
        return m_i > that.m_i;
    }
private:
    int m_i;
};

```

### 二次编译

- 编译器对函数模板会进行两次编译

- 第一次编译只检查函数模板本身内部代码，看基本词法是否正确

  - 函数模板内部出现的所有标识符是否申明； 
  - 对已知类型的调用要查看是否有效：调用某类的成员函数是否存在？
  - 对于未知类型的调用编译器认为调用都合理，但是不能出现尖括号`<>`

  ```cpp
  class A{
      public:
      void func(){
          cout << "asdasdasd" << endl;
      }
  };
  
  template <class T>void foo(){
      A a;
      a.func();//已知类型调用
      a.func1()://无效调用，报错
      T t;
      t.asdhgasdjgyfaj();//未知类型调用，第一次编译不会报错
  }
  ```



- 第二次编译发生在实例化函数模板之后，结合所使用的类型实参，再次检查所有调用是否有效

==过不了第一次编译谈不上第二次编译==

### 隐式推断类型实参

> 隐式：编译器自己推断实现
>
> 显示：程序员通过写具体语句实现

- 如果函数模板的调用形参（小括号里的）和类型形参（大括号里边的）相关，编译器可以通过调用参数的类型来推出类型实参的类型

```cpp
template<class T>
    T Max(T x,T y){
    return x>y?x:y; 
}

Max<>(123, 456);//与Max<int>(123, 456)效果相同
Max(123, 456);//与Max<int>(123, 456)效果相同，<>甚至也可以去掉

//为什么可以省略掉？因为在定义模板的时候就已经说明了调用参数的类型和类型参数的类型是一样的，所有编译器看到小括号里的调用参数的类型后就会自己推断出类型参数的类型
```

- 好处：获得和调用普通函数一样的语法表现形式

```cpp
template<class T,class D>
    T Hum(T x){
    D d;
    return d; 
}

int nx;
Hum<double>(nx)；//<double>明确了D的类型
    			//虽然函数模板Hum有两个类型参数，但只要<>内只有一个类型参数仍是合法的，T的类型是由传进来的调用参数nx的类型明确的，因此只需指出D具体是什么类型就行
```

注意，上面这个函数模板有两个==类型参数==，==调用参数==只有一个，编译器可以通过传进来的调用参数推出T是什么类型，但是D具体是什么类型不知道，因此需要特别指出

### 函数模板的重载

> 函数重载：函数名相同但参数个数或类型（参数表）不同的函数之间是重载关系 

- 普通函数和可实例化出该函数的函数模板构成重载关系
  - 实例化后的函数和普通函数相同时优先选择普通函数
  - 可在函数名后加`<>`强制使用函数模板实例化的函数而不是普通函数

==<>可以看作是和编译器之间的一个君子协定，出现<>编译器就只执行函数模板实例化==

## 类模板

==类模板不是类，不能定义对象，他只是编译器用来生成类的一个依据==

### 类模板声明

形式：

```cpp
tempate<class A, class B>class CMath{
public:
    A m_a;
    B func(){...};
}
```

类的成员函数是可以定义在类外的，那么类模板的成员函数怎么在类模板外面定义呢？

1. 帽子不能丢
2. 只有类能引成员，类模板不是类不能引成员

```cpp
template<class T>
class CMath{
public:
    CMath(T const& t1, T const& t2):m_t1(t1), m_t2(t2){}//构造
    T add();//仅在类内声明但未定义的函数
private:
    T m_t1;
    T m_t2;
};
//如何在类外定义类模板函数？
template<class T>//  1. 模板的帽子不能丢
T CMath<T>::add(){// 2. 不能写成CMath::add(){},CMath<T>才是一个类，CMath只是类模板
    return m_t1 + m_t2;
}
```

### 类模板的使用

==类模板必须实例化才能使用==（产生真正的类）

- 类模板本身并不能代表一个确定的类型（即不能定义对象）

- 类模板只有通过==类型实参==实例化成真正的类之后才是一个真正的类（才可以定义对象）

例如：

```cpp
CMath math;//不能定义对象
CMath<int> math;//CMath<int>这句就是在实例化类模板，编译器看到这句后就会依据类模板自动生成一个类
			// 类名就是CMath<int>
```

- 类模板在实例化时类模板的成员函数并没有实例化，成员函数只有在被调用时才能实例化，例如

```cpp
//定义类模板
template<class T>
class CMath{
public:
    CMath(T const& t1, T const& t2):m_t1(t1), m_t2(t2){}//构造
    T add();//仅在类内声明但未定义的函数
private:
    T m_t1;
    T m_t2;
};

//对于上面的类模板，编译器在看到 CMath<int> 时会生成下面所示的代码：

class CMath<int>{
public:
private:
	int m_t1;
	int m_t2;
}
// 可以看出，只有成员变量的类型被int实例化了，成员函数并没有生成
// 那么成员函数在什么时候生成呢？
CMath math(10,20);
// 通过上面的语句便实例化了构造函数
// 定义对象的本质就是调用构造函数
math.add();
// 通过上面的调用才实例化了 add() 函数
```

- 自定义的类虽然不一定支持类模板的所有方法（成员函数），但是仍可以用来实例化类模板，要使用类模板的某个方法便只写一下那个方法的实现就可以不用实现类模板所有的方法；这也从侧面说明类模板实例化时只实例化成员变量不实例化成员函数。

### 类模板的静态成员

> 类的静态成员：只属于类，不属于任何对象，但这个类的所有对象会共享这个成员
>
> 类静态成员变量的定义和初始化一定要放在类外去写！

- 类模板的静态成员也不是每个对象拥有一份；
- 也不是类模板拥有一份；
- 应该是由类模板实例化出的每一个真正的类各有一份；
- 且为该实例化类定义的对象共享

```cpp
// 定义一个类模板
template<class T>class A{
public:
    // 定义静态成员函数
    static void print(){// 打印两个成员变量的地址  
        cout << "&m_i: " << &m_i << "&m_i: "<< &m_t  << endl;
    }
    static int m_i;// 定义两个静态成员变量
    static T m_t;
}; 

// 类模板的静态成员变量定义也要在类模板的外面
template<class T>int A<T>::m_i = 0;//类模板帽子不能丢；A<T>::而不是A::
template<class T>T A<T>::m_t;//T是个位置类型，怎么给m_t赋初值呢？

//实例化类模板并定义对象
A<int> x,y,z;
// 以下四种调用生成的地址是一样的，验证了类模板的静态成员由实例化类定义的所有对象共享
x.print();
y.print();
z.print():
A<int>::print();

```

### 类模板的递归实例化

- 由类模板实例化产生的类也可以用来实例化类模板自身，这种做法就是类模板的递归实例化
- 好处：通过这种方法可以构建空间上具有递归特性的数据结构（多维数组）

```cpp
// 定义一个类模板
template<class T>
class Array{//这个类模板用来维护一个数组
public:
    // 定义一个成员函数
    T& operator[](size_t i){  // 重载下标操作符
  		return m_arr[i];
    }
private:
    T m_arr[10];// 成员变量是一个十个元素的数组，每个元素的类型是T
}

// 实例化类模板
Array<int> a;// a是一个Array<int>类的对象，也就是a维护一个十元数组，每个元素类型是int
// 使用重载的下标运算符访问a对象维护的数组元素
a[5]//==>operator[](5)
    
// 类模板的递归实例化
Array<Array<int> >  m ;// 用Array<int>再次实例化类模板Array
    			      // 出现两个 << 连起来是中间要空一格，否则与输入流重复了
m 的每个元素类型是Array<int>型，也就是一维数组，因此 m 就是个二维数组  
```

### 全局特化（特殊化）

- 包括**全类特化**和**成员特化**

- 实现类模板对所有类型都支持

类模板对大多类型都是通用的，例如int, double, string, 但对于字符数组 char[] 通常都是不适用的，因为字符数组的首地址，是指针，指针与指针之间的运算是有限制的

- 如果`template<>`的尖括号里什么都没写那就是特化

> 指针是不能和指针做加法计算的；两个指针相加没有意义
>
> 指针可以和整数做加法计算；``*（a+1）``

```cpp
// 全类特化
template<> // 帽子，<>里面不写东西
		  // 如果template<>的尖括号里什么都没写那就是特化
class CMath<char* const>{  // 看形式这就是写了一个类
public:
    CMath<char* const>(char*const& t1, char*const& t2):m_t1(t1), m_t2(t2){}
    char* const add(){
        return strcat(m_t1, m_t2);// 不是add，而是拼接字符
    }
private:
    char* const m_t1;
    char* const m_t2;
};

// 以上实现了对char* const类型的支持
// 全类特化相当于自己写出对某类模板的实例化

// 成员特化
template<>
char* const CMath<char*const>::add(){
    return strcat(m_t1, m_t2);// 仅仅对成员函数add()做特化，这样代价比较小且实现了类模板 CMath的全局特化
}
```

### 局部特化

- 全局特化指的是把类模板的所有类型参数都特化
- 局部特化是指类模板的类型参数没有全部特化
- 除非必要，不要使用类模板的局部特化，防止引发编译器的匹配企业

```cpp
// 定义两个类型参数的类模板
template<class T, class D>
class CMath{
public:
private:
}

// 全局特化:所有的类型参数都具体化了
template<>
class CMath<long, short>{
    ...
}
// 局部特化：部分类型参数具体化
template<class T> // 仅对D类型做特化为short，T没有特化
class CMath<T, short>{
    ...
}
```

### 类型形参的缺省值

> 函数的调用形参可以有缺省值

- 类模板的类型形参可以带缺省值
- 类模板类型形参的缺省值是类型而不是数据

```cpp
// 定义带缺省类型参数的类模板
template<class T=short, class D=int>class CMath{// T默认为short，D默认为int
public:
private:
}
```

- 和函数一样，默认类型形参也遵守靠右原则

### 数值形式的类型参数

- 类模板的模板形参（尖括号里的）并不限于类型参数，普通数值也可作为模板的参数
- 只能是整形的

```cpp
// 例如
template<class T, size_t S> //T是类型参数，S是数值型参数
class Array{
public:
    T& operator[](size_t i){  
  		return m_arr[i];
    }
private:
    T m_arr[10];
}

// 参数也可以有默认值
template<class T=double, size_t S=15> //T是类型参数，S是数值型参数
class Array{
public:
    T& operator[](size_t i){  
  		return m_arr[i];
    }
private:
    T m_arr[S];//S由模板参数引入，这样可以方便自由定义数组的长度
}
```

### 模板型成员变量

- 是成员变量
- 类型是有一个类模板实例化的未知类

 ```cpp
 //先定义一个模板
 template<class T>class Array{
     public:
     private:
 };
 // 另一个模板
 template<class D>class Sum{
     public:
     private:
     Array<D> m_s; // 模板型成员变量
     Array<int> m_s; // ！不是模板型成员变量
 };
 ```

### 模板型成员函数

- 又叫类模板的==成员函数模板==

 ```cpp
 template<class T>class CMath{
 public:
     template<class D>void foo();//成员 函数模板
 }
 // 类外定义成员函数模板
 template<class T>
 template<class D>void CMath<T>::foo(){
     cout << ...
 }
 ```

### 模板型成员类型

- 类模板中嵌套的类模板

```cpp
template<class X>class A{
public:
    template<class Y>class B{
    public:
        template<class Z>class C;
    };
};

// 类外定义类C
template<class X>
template<class Y>
template<class Z>class A<X>::B<Y>::C{
public:
    template<class T>void foo(){ // 又折腾一个成员函数模板
        cout << ...;
    };
};   
```

如何调用成员函数模板foo()?

1. foo()是成员，要拿对象调；
2. 要对象必须得有类；
3. 类由类模板实例化来

```cpp
// 实例化类模板并定义对象
A<int>::B<double>::C<float> c;
// 用c对象调用成员函数foo()
c.foo<string>(); //foo()是个函数模板，因此也必须实例化
```

### 模板型模板参数

>尖括号里的模板形参可是是类型，也可以是数值

- 尖括号里也可以是类模板，也可以带缺省值
- 尖括号里只能出现上述三种形式

```cpp
template<class D, template<class M>class C>class Sum{};
// 模板类Sum有两个类型参数，一个是D接收一个类型，一个是C但C接收的不是类型而是类模板
template<class D, template<class M>class C=int>class Sum{};//err;C只能接收类模板
template<class D, template<class M>class C=Array>class Sum{};// 没有问题，因为Array是个类模板
```

有什么用？

- 使类模板更泛化，可以传进来类模板型类型参数下的任何类；

---

## 类模板使用常见错误

### 嵌套依赖

```cpp
// 定义一个嵌套类
class A{
public:
    class B{
    public:
        void foo(){};
    }
};
// 定义一个函数模板
// 我们想给T传进来A类型
template<class T>void Func(){
    T::B b;//嵌套依赖
    		// T是一个未知类，编译器允许未知类定义对象，但T::B编译器会认为B是T对象的一个静态成员，而不是我们理解的T类下的嵌套类B
    b.foo();
}

// 解决方法
// 告诉编译器B是T的嵌套类型
template<class T>void Func(){
    typename T::B b;//这样编译器会认为B是T的嵌套类型
```



## 链表容器

### 基本链表容器

```cpp
// cpp/list.cpp
#include <iostream>
#include <stdexcept> //异常类，抛出一些异常错误
using namespace std;
template<class T>class list{    // 用类模板实现节点数据类型泛化
public:
    // 缺省构造
    list():m_head(NULL),m_tail(NULL){}
    // 拷贝构造
    list(list const& that):m_head(NULL),m_tail(NULL){
        // 深拷贝
        // 遍历that链表的每一个节点
        for (node *pnode = that.m_head; pnode;pnode=pnode->m_next){
            push_back(pnode->m_data);// 把that链表的每个节点数据都压到要\
                                        新建的这个链表的末尾，这样就实现了拷贝
        }
    }
    // 析构函数
    ~list(){
        clear();
    };
    // 链表判空
    bool empty(){
        return m_head == NULL && m_tail == NULL;
    }

    // 添加头结点
    void push_front(T const& data){
        m_head = new node(NULL, data, m_head);// 新建一个节点，前指针为空，\
                                        后节点指向之前的头节点
        // 让之前的头节点的前指针指向新建的节点
        // 如果有下一个节点那正常执行
        if (m_head->m_next)
            m_head->m_next->m_prev = m_head;
        // 如果没有下一个节点那就表示尾节点就是头节点
        else
            m_tail = m_head;
    }

    // 删除链表头结点
    void pop_front(){
        // 如果是空的直接返回
        if(empty())
            return;
        node *pnode = m_head->m_next;// 先备份下链表的第二个节点
        delete m_head;
        // 是否能确定头节点的下一个节点存在？得判断一下
        if (pnode)
            pnode->m_prev = NULL;
        // 如果头节点的下一个节点不存在，\
           那把头节点删了下一个节点就是空节点，那新头都是空那尾肯定也是空
        else
            m_tail = NULL;
        m_head = pnode;
    }

    // 获取头结点数据
    T& front(){    // 返回头结点数据的引用，好处：可以用它更改链表数据
        if(empty())
            // return 0;
            // 不能return0，虽然这里返回0是指出错，但万一要返回的数据就是0就说不清了
            // 抛出异常
            throw underflow_error("null node");
        return m_head->m_data;
    }
    // 有常属性的链表掉这个函数，因此不会修改，别的调用front函数只会调用上面的那个
    T const& front()const{// 第一个const表示常引用，第二个表示常函数
                          // 只有常对象才能调用常函数
        // 方法1 完全复制上面的
        if(empty())
            // return 0;
            // 不能return0，虽然这里返回0是指出错，但万一要返回的数据就是0就说不清了
            // 抛出异常
            throw underflow_error("null node");
        return m_head->m_data;
        // 方法2
        return const_cast<list *>(this)->front();
    }
    // 添加尾节点
    void push_back(T const& data){
        // 把新new的节点当做尾节点
        m_tail = new node(m_tail, data, NULL);
        // 新尾节点的前一个节点的后指针应该指向新的尾节点
        if (m_tail->m_prev)
            m_tail->m_prev->m_next = m_tail;
        else//new的这个节点的链表只有一个节点
            m_head = m_tail;
    }
    // 删除尾节点
    void pop_back(){
        if(empty())
            return;
        node *pnode = m_tail->m_prev;// 备份倒数第二个节点
        delete m_tail;
        // 能不能肯定要删除的尾节点有前一个节点？
        if (pnode)
            pnode->m_next = NULL;// 如果有那删了
        else
            m_head = NULL;//如果没有那你还把尾节点删了，那链表就为空了，\
                            所以头节点应该是空的
        m_tail = pnode;
    }
    // 获取尾节点数据
    T& back(){
        if(empty())
            throw underflow_error("null node");
        return m_tail->m_data;
    }
    T const& back()const{
        // 把掉这个常函数的常对象的常属性去除掉，然后再掉上面的back()函数
        return const_cast<list *>(this)->back();
    }
    // 清空链表
    void clear(){
        // 链表不空进循环
        while (!empty())
        {
            pop_front();// 不断删除头节点
        }
        

    }
    // 获取链表大小
    size_t size(){
        size_t i = 0;// size_t 类型表示C中任何对象所能达到的最大长度，它是无符号整数。  
        for (node *pnode = m_head; pnode;pnode=pnode->m_next)
            ++i;
        return i;
    }

private:
// 节点类
    class node{
    public:
        node(node *prev, T const& data,node *next):m_prev(prev),m_data(data),m_next(next){}
        node *m_prev;// 前指针
        T m_data;// 节点数据
        node *m_next;// 后指针
    };
    node *m_head;// 头节点
    node *m_tail;// 尾节点
    friend ostream &operator<<(ostream &os, list<int> &l);//输出流操作函数\
            因为这个函数在类外使用了list类的私有成员node和m_data，所以声明为友元
};
// 以上代码模拟容器
// -----------------------------------
// 以下代码模拟普通用户

// 重载输出流操作符，这是用户层面重载的，不是容器提供的
ostream& operator<<(ostream& os,list<int>& l) {
    for (list<int>::node *pnode = l.m_head; pnode; pnode = pnode->m_next){
        os << pnode->m_data << ' ';
    }
    return os;
}
int main() {
    list<int> ls;
    // 给链表对象添加5个节点
    for (int i = 0; i < 5; i++)
        ls.push_front(10 + i);
    for (int i = 0; i < 5;i++)
        ls.push_back(100 + i);
    cout << ls << endl;// 还没有重载输出流操作符
    return 0;
}
```

## 迭代器

### 迭代器概念

- 迭代器就是一个类（迭代类）对象，==什么什么器都是指类对象==（比较器）
- 迭代就是遍历的意思
- 链表容器也可以通过for循环的形式实现遍历，但这需要用户对链表内部结构非常熟悉
- 迭代类结构：起始指向、当前指向、终止指向
- 通过对迭代类对象进行++或--操作可以对链表容器进行全部或局部遍历
- 这样可以可以使普通用户不必关系链表容器的内部结构

### 迭代类分类

- 一共分为四种
- ***正向非常迭代类***    ==iterator==
- ***正向常迭代类***     ==const_iterator==
- ***反向非常迭代类***    ==reverse_iterator==
- ***反向常迭代类***     ==const_reverse_iterator==

#### 非常迭代器

可以通过迭代器修改链表

```cpp
// 实现正向非常迭代类
// 这个类和节点类一样是嵌套在链表类里面的
class iterator{
public:
    iterator(node *start, node *cur, node *end) : m_start(start), m_cur(cur), m_end(end){}
    // 重载*运算符，来获取迭代器指向节点的数据
    T& operator*(){
        if(m_cur==NULL)
            throw underflow_error("null node");
        return m_cur->m_data;
    }
    // 重载++运算符，返回迭代器类型
    iterator& operator++(){
        if(m_cur==NULL)
            m_cur = m_start; // 如果m_cur指向了尾节点的后面，就让他重新指向头节点，实现循环迭代
        else
            m_cur = m_cur->m_next;// 把迭代器当前指向往后挪一个
        return *this;//返回调用这个函数的对象本身
    }
    iterator& operator--(){
        if(m_cur==NULL)
            m_cur = m_end; // 如果m_cur指向了头节点的前面，就让他重新指向尾节点，实现循环迭代
        else
            m_cur = m_cur->m_prev;// 把迭代器当前指向往qian挪一个
        return *this;//返回调用这个函数的对象本身
    }
    // 重载==,判断两个迭代器是否相等
    // ==是双目操作符，左操作数是调用的对象，右操作数是传进来的参数
    bool operator==(iterator const& that)const{
        return m_start == that.m_start && m_cur == that.m_cur && m_end == that.m_end;
    }
    // 重载!=
     bool operator!=(iterator const& that)const{
         return !(*this == that);// 又调用了==操作符
    }
private:
    node *m_start; // 开始指向
    node *m_cur;// 当前指向
    node *m_end;// 终止指向
};
```

完整的链表容器和迭代器程序：

```cpp
#include <iostream>
#include <stdexcept> //异常类，抛出一些异常错误
using namespace std;
template<class T>class list{    // 用类模板实现节点数据类型泛化
public:
    // 缺省构造
    list():m_head(NULL),m_tail(NULL){}
    // 拷贝构造
    list(list const& that):m_head(NULL),m_tail(NULL){
        // 深拷贝
        // 遍历that链表的每一个节点
        for (node *pnode = that.m_head; pnode;pnode=pnode->m_next){
            push_back(pnode->m_data);// 把that链表的每个节点数据都压到要\
                                        新建的这个链表的末尾，这样就实现了拷贝
        }
    }
    // 析构函数
    ~list(){
        clear();
    };
    // 链表判空
    bool empty(){
        return m_head == NULL && m_tail == NULL;
    }

    // 添加头结点
    void push_front(T const& data){
        m_head = new node(NULL, data, m_head);// 新建一个节点，前指针为空，\
                                        后节点指向之前的头节点
        // 让之前的头节点的前指针指向新建的节点
        // 如果有下一个节点那正常执行
        if (m_head->m_next)
            m_head->m_next->m_prev = m_head;
        // 如果没有下一个节点那就表示尾节点就是头节点
        else
            m_tail = m_head;
    }

    // 删除链表头结点
    void pop_front(){
        // 如果是空的直接返回
        if(empty())
            return;
        node *pnode = m_head->m_next;// 先备份下链表的第二个节点
        delete m_head;
        // 是否能确定头节点的下一个节点存在？得判断一下
        if (pnode)
            pnode->m_prev = NULL;
        // 如果头节点的下一个节点不存在，\
           那把头节点删了下一个节点就是空节点，那新头都是空那尾肯定也是空
        else
            m_tail = NULL;
        m_head = pnode;
    }

    // 获取头结点数据
    T& front(){    // 返回头结点数据的引用，好处：可以用它更改链表数据
        if(empty())
            // return 0;
            // 不能return0，虽然这里返回0是指出错，但万一要返回的数据就是0就说不清了
            // 抛出异常
            throw underflow_error("null node");
        return m_head->m_data;
    }
    // 有常属性的链表掉这个函数，因此不会修改，别的调用front函数只会调用上面的那个
    T const& front()const{// 第一个const表示常引用，第二个表示常函数
                          // 只有常对象才能调用常函数
        // 方法1 完全复制上面的
        if(empty())
            // return 0;
            // 不能return0，虽然这里返回0是指出错，但万一要返回的数据就是0就说不清了
            // 抛出异常
            throw underflow_error("null node");
        return m_head->m_data;
        // 方法2
        return const_cast<list *>(this)->front();
    }
    // 添加尾节点
    void push_back(T const& data){
        // 把新new的节点当做尾节点
        m_tail = new node(m_tail, data, NULL);
        // 新尾节点的前一个节点的后指针应该指向新的尾节点
        if (m_tail->m_prev)
            m_tail->m_prev->m_next = m_tail;
        else//new的这个节点的链表只有一个节点
            m_head = m_tail;
    }
    // 删除尾节点
    void pop_back(){
        if(empty())
            return;
        node *pnode = m_tail->m_prev;// 备份倒数第二个节点
        delete m_tail;
        // 能不能肯定要删除的尾节点有前一个节点？
        if (pnode)
            pnode->m_next = NULL;// 如果有那删了
        else
            m_head = NULL;//如果没有那你还把尾节点删了，那链表就为空了，\
                            所以头节点应该是空的
        m_tail = pnode;
    }
    // 获取尾节点数据
    T& back(){
        if(empty())
            throw underflow_error("null node");
        return m_tail->m_data;
    }
    T const& back()const{
        // 把掉这个常函数的常对象的常属性去除掉，然后再掉上面的back()函数
        return const_cast<list *>(this)->back();
    }
    // 清空链表
    void clear(){
        // 链表不空进循环
        while (!empty())
        {
            pop_front();// 不断删除头节点
        }
        

    }
    // 获取链表大小
    size_t size(){
        size_t i = 0;// size_t 类型表示C中任何对象所能达到的最大长度，它是无符号整数。  
        for (node *pnode = m_head; pnode;pnode=pnode->m_next)
            ++i;
        return i;
    }

private:
// 节点类
    class node{
    public:
        node(node *prev, T const& data,node *next):m_prev(prev),m_data(data),m_next(next){}
        node *m_prev;// 前指针
        T m_data;// 节点数据
        node *m_next;// 后指针
    };
//
// 正向非常迭代类
// 
    class iterator{
    public:
        iterator(node *start, node *cur, node *end) : m_start(start), m_cur(cur), m_end(end){}
        // 重载*运算符，来获取迭代器指向节点的数据
        T& operator*(){
            if(m_cur==NULL)
                throw underflow_error("null node");
            return m_cur->m_data;
        }
        // 重载++运算符，返回迭代器类型
        iterator& operator++(){
            if(m_cur==NULL)
                m_cur = m_start; // 如果m_cur指向了尾节点的后面，就让他重新指向头节点，实现循环迭代
            else
                m_cur = m_cur->m_next;// 把迭代器当前指向往后挪一个
            return *this;//返回调用这个函数的对象本身
        }
        iterator& operator--(){
            if(m_cur==NULL)
                m_cur = m_end; // 如果m_cur指向了头节点的前面，就让他重新指向尾节点，实现循环迭代
            else
                m_cur = m_cur->m_prev;// 把迭代器当前指向往qian挪一个
            return *this;//返回调用这个函数的对象本身
        }
        // 重载==,判断两个迭代器是否相等
        // ==是双目操作符，左操作数是调用的对象，右操作数是传进来的参数
        bool operator==(iterator const& that)const{
            return m_start == that.m_start && m_cur == that.m_cur && m_end == that.m_end;
        }
        // 重载!=
         bool operator!=(iterator const& that)const{
             return !(*this == that);// 又调用了==操作符
        }
    private:
        node *m_start; // 开始指向
        node *m_cur;// 当前指向
        node *m_end;// 终止指向
    };
    // 
    // 获取其实迭代器，遍历链表
    // 
    iterator begin(){
        return iterator(m_head, m_head, m_tail);//让迭代器的起始指向为链表头，\
                                        当前指向为链表头，终止指向为链表尾
    }// 用户只需要用链表对象掉一个begin函数就能返回一个起始迭代器
    // 
    // 获取终止迭代器，结束标志
    // 
    iterator end(){
        return iterator(m_head, NULL, m_tail);
    }
    node *m_head;// 头节点
    node *m_tail;// 尾节点
    // 有了迭代器就不用这个了友元了
    friend ostream &operator<<(ostream &os, list<int> &l);//输出流操作函数\
            因为这个函数在类外使用了list类的私有成员node和m_data，所以声明为友元
};
// 以上代码模拟容器
// -----------------------------------
// 以下代码模拟普通用户

// 重载输出流操作符，这是用户层面重载的，不是容器提供的
// 有了迭代器就不用这个了
ostream& operator<<(ostream& os,list<int>& l) {
    for (list<int>::node *pnode = l.m_head; pnode; pnode = pnode->m_next){
        os << pnode->m_data << ' ';
    }
    return os;
}

// 定义一个打印链表内容的函数
void print(string const &str, list<int> &l){
    cout << str << endl;
    typedef list<int>::iterator IT;//迭代器类是嵌套在list<>类下面的，用它定义对象很麻烦，这里简洁定义下
    for (IT it = l.begin(); /*获得一个起始迭代器*/ it != l.end(); ++it){
        cout << *it /*调用*函数取得迭代器的当前值*/ << ' ';
    }
    cont << endl << "---------------------------------" << endl;
}
int main() {
    list<int> ls;
    // 给链表对象添加5个节点
    for (int i = 0; i < 5; i++)
        ls.push_front(10 + i);
    for (int i = 0; i < 5;i++)
        ls.push_back(100 + i);
    // cout << ls << endl;// 还没有重载输出流操作符
    // 通过使用迭代器来遍历输出链表
    print("添加节点后： ", ls);
    ls.pop_front();
    ls.pop_back();
    print("删除头尾节点后： ", ls);
    return 0;
}
```

- 迭代器指向的中间某个位置添加/删除节点

#### 常迭代器

不是说迭代器具有常属性，而是指迭代器操作的链表具有常属性，即链表是不能修改的

```cpp
// 
// 正向常迭代类
//
//还是定义在链表类list里
class const_iterator{
public:
    const_iterator(iterator const& it):m_it(it){}
    // 定义*运算符
    T const& operator*(){//const&是为了不能通过引用来改目标
        return *m_it;
    }
    // 定义++运算符，实现遍历
    const_iterator& operator++(){
        ++m_it;
        return *this;
    }
    // 定义--运算符，实现遍历
    const_iterator& operator++(){
        --m_it;
        return *this;
    }
    // 定义==运算符
    bool operator==(const_operator const& that)const{// 常对象才能掉常函数
        return m_it==that.m_it;
    }
    // 定义!=运算符
    bool operator==(const_operator const& that)const{// 常对象才能掉常函数
        return !(*this==that);
    }
private:
    iterator m_it;//利用前面的功能实现新的功能
};

//
// 获取起始常迭代器，以下函数定义在const_iterator类外面，是list<>类的成员
// 
const_iterator begin()const{//和之前的begin函数是重载关系，只有常链表才能掉这个begin函数
    return iterator(m_head, m_head, m_tail);
}
//
// 获取终止常迭代器
//
const_iterator end()const{
    return iterator(m_head, NULL, m_tail);
}

// main函数中实现常迭代器功能
const list<int> cls=cls(ls);//const的变量在定义后就不让改了，因此这里要给常迭代器赋初值，用之前的非常迭代器ls拷贝构造一个常迭代器
// 遍历下cls的各节点
typedef list<int>::const_iterator CIT;
for(CIT cit=cls.begin();vit!=cls.end();++cit){//通过++cit可以看出迭代器本身没有常属性，而是指迭代器指的数据没有常属性
    cout << *cit <<' ';
}
cout << endl <<"----------------------------------"
```

#### 反向迭代器

仅和正向迭代器方向不同。

正向迭代器++是从链表头往链表尾移动；

反向迭代器++是从链表尾往链表头移动；

#### 查找/排序功能

定义在list类外的全局函数

```cpp
// 
// 查找
// 
template<class IT, class T>IT find(IT const& a, IT const& b, T const& data){
    
}
```

> 详细内容见list.cpp

---



## STL

#### STL概念和作用

- 全称：Standard Template Library

- 作用：

STL 并不是C++语言的一部分（但模板肯定是C++语言的东西），他就是一个工具库，封装了十几种容器；没有这个工具库时程序员要实现容器或数据结构只能自己制作，如制作链表，制作栈等

STL内部使用模板使操作更加泛化，STL内部三大部分组成：==容器 ，泛型 ， 算法==（数据整理排序等）

#### 数组结构和链表结构

不是指数组或链表，而是一种泛化；

只要是连续存储的数据结构就叫数组结构等，而链式就是指不连续的结构；

这两种数据结构是计算机最基本的数据结构，别的数据结构都是在他们的基础上建立的；

这两种数据结构都不完美，各有优缺点；

- 数组结构：
  - 优点：随机访问（即指下标访问）方便，速度快效率高。
  - 缺点：中间位置插入删除不方便，效率低（内存空间分布的限制）
- 链表结构：
  - 优点：插入删除操作方便，效率高。
  - 缺点：随机访问效率低，往往只能通过遍历过程对给定的条件进行检测
- 总结：STL标准模板库所提供的容器类，结合了数组和链表的优点，使用户从内存管理的细节中得以解脱（对数组和链表的功能进行了封装）

### 十大容器

##### 基本容器（线性容器）：

元素按照线性顺序排列（线性指能从一个找到下一个）

- 向量（vector）：类似数组（内部是连续存储），支持下表访问，在尾部添加和删除元素效率高，但中间效率低
- 双端队列（deque)：支持下标访问（头尾两段都可添加/删除操作）

> 队列的特点是先进先出，因此要实现一个队列，存数据只能从最后存，取数据只能从最前面取；

- 列表（list）:就指的是==链表==，在任何位置添加或删除操作都很方便，==不支持下标访问。==

---

##### 适配器容器（裁剪容器）：

对线性容器的某些功能加以屏蔽

以上三种为基本容器，以下三种容器是上述三种基本容器部分功能裁剪的产物

- 堆栈/栈（stack）：支持在一端存储和提取元素
- 队列（queue）：支持从前端提取，后端压入元素
- 优先队列（priority_queue）：类似队列，优先级最高（默认最大的）的先出

---

##### 关联容器：

根据一个元素相关联的key来存储或提取数据，以key-value形式存储

- ***映射（map）***：***数据结构的重中之重***，以==键值对（key-value）==的形式存储数据，以key的升序排列，key唯一，映射的内部结构是红黑树

- 多重映射（multimap）：允许key重复出现的映射
- 集合（set）:没有value的映射（那就只有key了）
- 多重集合（multiset）：没有value的多重映射

#### 十大容器的共同特点

所有的容器都支持<u>拷贝构造和拷贝复制</u>（指的是<u>同类型之间</u>）；

相同类型的两个容器之间可以通过 == 进行相等性判断；

==容器存储的为数据的<u>副本</u>==，这就意味着存入容器的对象应支持拷贝构造和拷贝赋值；*（你要往容器中存一个东西必须得先有这个东西，所以是副本）*

通常情况下被存放到容器中的对象应支持<u>无参构造</u>

#### 迭代器

顺序迭代器：一次只能向前或向后迭代一步，即只支持++和--运算；

随机迭代器：能移动多步，即除了支持++和--外还支持对整数的加减运算；

*除了<u>向量和双端列表以及优先队列</u>支持随机迭代器意外，其余容器只支持顺序迭代器*

---

正向迭代器：从前到后

反向迭代器：从后到前

每个容器都有四个迭代类：

- iterator
- const_iterator
- reverse_iterator
- const_reverse_iterator

每个容器都有八个迭代器对象：起始迭代和终止迭代

- begin() / end()
- begin()const / end()const
- rbegin() / rend()
- rbegin()const / rend()const

### 向量容器

#### 成员函数

size()      -向量维护元素个数
resize()  -设置向量元素个数

capacity() -获取向量容量

reserve() - 设置向量容量

<u>***大小指已经存了多少，容量指最大可以存多少***</u>

#### 初始化

向量中的元素被存储在一段连续空间中；

向量维护的内存空间会随着新元素的增加自动增长；

如果内存空间无法满足新元素的增加，向量会开辟新的足够的连续空间，并把原内存空间的数据复制到新的内存空间，释放掉原内存空间

向量的增加伴随着内存空间的分配和释放、元素复制和销毁等额外开销，效率并不高

如果能在创建向量时，合理分配一些空间将很大程度上缓解这些额外开销。

> vector01.cpp

#### 向量迭代器使用

增：insert()

删：Erase()

改：

查：find()

排序：sort()

> vector02.cpp

### 双端队列

#### 双端队列和向量的差别

几乎无差别

- 向量只支持在尾部插入节点，双端队列首尾两端都是可以增删元素的
- 没有提供设置和获取容量的函数，但有设置和获取容器大小的函数

> deque标准容器.cpp

==要把自己定义的类的对象放进容器，容器要什么操作你的类就得支持什么操作==，例如`==`，`!=` ,`<<`等

### 列表

就是链表

- 唯一化：将<u>连续重复出现</u>的元素唯一化
- 排序：链表的排序和向量与队列同，链表排序只需改下指针指向的位置即可
  - 在链表类里有个sort()函数成员，专门对链表排序，与全局额sort()不同
  - 成员函数sort()没有卡范围，是对链表的所有节点进行排序
- 拆分：将<u>参数列表</u>中的元素剪切到<u>调用列表</u>中

> list标准容器.cpp

---

### 栈

==往栈里存数据其实就是往底层容器里存==

- 定义形式

​		stack<元素类型，[底层容器类型]> 堆栈对象（构造实参表）

- 底层容器

​		vector / <u>deque(默认)</u> / list / 甚至自己实现的容器作为栈的底层容器

- 成员函数

| 栈提供的成员 | 底层容器对应的成员函数 |
| :----------: | :--------------------: |
| push（存栈） |       push_back        |
| pop（删栈）  |        pop_back        |
|  top (读栈)  |          back          |
|     size     |          size          |
|    empty     |         empty          |
|    clear     |         clear          |

- 栈的底层实现

​		==往栈里存数据其实就是往底层容器里存==

> stack标准容器.cpp

### 队列

- 定义形式

​		queue<元素类型，[底层容器]> 队列对象（构造实参表）

- 底层容器：deque(默认)/ list / <u>vector不可以</u>

​		因为vector是不能在头部添和删的

- 成员函数

​		push -> push_back

​		pop -> push_front

​		.....

> queue标准容器.cpp

### 优先队列

与队列区别：不是先进先出而是==优者先出==

- 定义形式：

​		priority_queue<元素类型，【底层容器类型】，【比较器类型】> 优先队列对象（构造实参表）

- 底层容器：deque(默认)/vector  <u>不能是list</u>
- 注意事项：

​		默认大者为优，也可以通过比较类定制

​		如果没有比较器，默认内部使用<运算符

​		并不是出队列时排序，而是进队列时就保证有序，出的时候直接拿最外面的那个就是

- 成员函数：同上

> priority_queue标准容器.cpp

---

### 映射

映射容器是关联容器中最重要的！

映射容器每个节点存的是键值对 

映射就是个平衡有序二叉树！

- 定义形式：map<键类型，值类型> 映射对象；
- 逻辑模型：键（信息索引）值（信息内容）对，主要用于信息检索，找东西快！类似二分法
- 物理模型：<u>平衡</u>有序二叉树又名红黑树（从任何一个节点看下去左右子树的层级不超过一层）
- 键必须唯一
- 对映射容器遍历过程实际上是做的关于键的中序遍历，键的升序
- 存储单位是由键和值组成的pair（==映射的每一个节点保存的数据为一个pair对象==），一个pair对象就是一个键值对
- ==<u>映射的迭代器的相当于指向pair对象的指针</u>==
- 映射中的键是只读的
- 映射的检索性能很好，但是构建和修改性能较差（每次存入都要排序，适用于结构稳定但需要频繁检索的操作
- 映射容器支持下标运算（中括号[]运算），用键作为下标得到对应的值的应用（可以更改值了）；如果给出的键不存在则会增加一个节点，并返回节点值的引用
- 成员函数
  - insert(pair<First,SECONF>(键，值)) // pair<First,SECONF>(键，值)相当于在掉pair的构造，这是用pair的构造来造pair对象
  - insert(make_pair(键，值)) // make_pair(键，值)也会造一个对象
  - 综上，insert()函数的参数是个pair对象
  - find(键)函数，这不是全局函数而是pair的成员函数，如果找到键存在的节点就返回迭代器对象，如果没找到返回终止迭代 

> map标准容器.cpp

### 多重映射

- 就是一种映射，只是键可以重复，表示一对多的逻辑关系；例如小明有语文数学英语三门课的成绩
- 内部仍是红黑树
- 由于键可以重复，不支持下标运算

> multiMap标准容器.cpp

### 集合

- 没有值只有键的映射
- 内部仍是红黑树
- 与向量等基本容器相比最大的优势就是**排重**

> set标准容器.cpp

### 多重集合

- 没有值只有键的多重映射
- 没有排重优势了
- 内部仍是红黑树

> multiset标准容器.cpp
