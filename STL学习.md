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



