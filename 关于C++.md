- typedef：取别名
int Typename;
typedef int Typename; Typename=int

- <*.h>表示优先中系统目录中查找 该头文件  比如#include <stdio.h>  这是系统中的
- "*.h"表示优先从当前目录中查找  该头文件  比如#include "head.h"   这是你自己写的

- 文件布置
在 OpenFOAM 中，所有代码都以注释段开头，使用有限体积的 CFD 类型文件都包括以下头文件:

 `#include "fvCFD.H"` 在此头文件种，仅包含类或函数的定义，函数的内容会在运行时以动态形式调用。

当 fvCFD.H 文件被引用后，在对应的编译设置文件 Make/options 中还需要添加如下命令

```
EXE_INC = \ 
			-I${LIB_SRC}/finiteVolume/lnInclude

EXE_LIBS = \
			-lfiniteVolume
```
这两句话指定了在编译时寻找头文件的位置和需要链接的函数库。

在 fvCFD.H 中，为了避免被多次引用，定义了如下宏变量
```
# ifndef fvCFD_H
# define fvCFD_H
<code>
#endif
```
当头文件已经引用过后，ifndef 判断返回 0，此时文件内直到 #endif 命令之间内容全部不会被再次引用。

在 fvCFD.H 中之后包含了一系列头文件，并以如下内容结束
```
#ifndef namespaceFoam
#define namespaceFoam
    using namespace Foam;
#endif
```
此代码定义了命令空间 Foam，在包含的库中所有的函数声明都属于命令空间 Foam，因此在调用库函数时必须使用。

在 c++ 代码中，必须包含 main 函数的实例，并且程序执行时是从此函数开始。在 c++ 的 main 函数中，使用以下参数并返回一个整数

> int main(int argc, char *argv[])

---
c++ 编程基础
---
- 操作符
对于输入和输出可以使用标准库 iostream

cout << "Please type an integer!" << endl;
cin >> myInteger;
其中操作符 << 和 >> 为输出和输入操作符，endl 为换行操作符。在 OpenFOAM 中推荐使用新的输出流 info，其优点是可以在并行计算情况中使用。

变量可以相加减，相乘除，并且当自定义类型指定了转化方法时还可以转化为其他类型的变量。在 OpenFOAM 中一些变量还可以使用算术运算符，但并非所有都可以。

c++ 中一些运算符包括 +、-、*、/ 等，以及其他标准运算符，例如 %、++、--、+=、-=、/=、%=等，用户自定义类型应自己定义这些运算符计算过程。

标准数学函数定义在标准库 cmath 中，因此并不是 c++ 的一部分，例如三角函数，指数函数和对数函数等。

- 分支
判断语句形式为： if (variable1 > variable2) {...CODE...} else {...CODE...}。
比较操作符包括：<、>、<=、>=、==、!=。
循环语句形式为：for (int; condition; change) {...CODE...}。

- 函数
在 c++ 中，函数可能有或者没有返回值，对于没有参数或返回值的函数，对应位置用 void 指定。在 c++ 中允许多个函数为同一函数名，只要其参数的个数或类型不同就不会在编译时报错。

变量域由花括号指定 {}，一个在花括号内定义的变量，仅在此区域内可见。可能有多个变量为同一个名字，但是在每个域内仅代表唯一的一个变量。为了使用全局变量，可以用 :: 操作符指明变量所在的域。

函数的调用前必须进行声明，函数的声明一般放在头文件内，如 #include "file.h" 或 #include <standardfile>。在编程时，将函数的声明和定义放在不同的文件中是一种良好的习惯，在 OpenFOAM 中也是采用这种方式。

如果函数中某个参数需要改变变量值，那么参数的类型必须是引用，例如

vodi change(double& x1)
此时对应的变量 x1 将为参数的引用，而非函数内的局部变量。在 c++ 内对函数进行调用时，需要对输入参数进行复制，引用也可以避免对内存占用较多的变量进行复制。为了避免对输入参数进行错误的修改，也可以定义输入参数的类型为常量型引用，即

- >void changeWord(const string& s)  
  
定义函数时可以给定参数的默认值，在函数调用时可以减少此参数的值。

- 类型
在 c++ 中变量可以包含不同的类型，在定义时可以用 int myInteger，或用 cont int myConstantInteger = 10 来定义常数。在 c++ 中也可以自定义类型，并且在 OpenFOAM 中包含了多种自定义类型。

- 指针是指向内存空间的变量，指针变量可以从变量的定义看出

int *pint;
double *pdouble;
char *pchar;
可以用 typedef 来定义新的变量类型

typedef vector<int> integerVector;
integerVector iV;
这种方法可以简化大型程序，例如 OpenFOAM 代码的复杂度，使得代码易读性更好。

- 命名空间
当不同编程人员使用 c++ 写程序时可能会有命名重复的风险。
通过将声明的区域增加命名空间可以有效控制声明的变量是否可见，例如 OpenFOAM 中常用的

- using namespace Foam;
可以使所有定义在命名空间 Foam 内的声明可见。
定义命名空间的形式为

namespace name {
	// declarations
}
此时，新的定义就加入到了命名空间内，并且在此作用域内可以使用命名空间定义的其他代码。

- 面向对象
面向对象的思想是将关注点放在对象而非函数上。对象是类的实例，对于属于同一类的对象包含有相同的属性。面向对象的优势在于增加了代码的复用性，每个类可以为不同的目标进行设计和编写。在 c++中，类与变量类型是同一个概念，所以类也可以看做是一种新的变量类型。

- 对象声明
下面代码定义了 name 类及其公有或私有的方法和数据
```
class name{
public:
	// public member functions and data members
private:
	// hidden member functions and data members
}
```
- 类的公有属性（方法和数据）在类外部是可见的，而私有属性则不可见。
对于没有指定 public 或 private 的属性，其默认是 private。
类中方法和数据的声明与普通函数与变量相同。

- 类的使用
定义类的对象方法为

- name nameObject;
一个类可以有多个对象，并且每个对象包含的属性都是相互独立的。可以声明对象的指针或引用，但是其调用类包含的方法时需要用 -> 符号，例如

>p1 = &nameObject; // reference
>p2 = new name;    // pointer
p1->write();
p2->write();

类中方法的定义可以在类的定义里，也可以在其外部。

>inline void name::write()
{
	// Contents of the member function.
}

例如上述代码定义了 name 类中的 write() 方法。在函数定义时，name:: 指出了方法 write 属于 name 类，而 inline 关键字则指出方法会在调用处进行展开，而非像普通函数那样在内存空间中跳转。对于直接定义在类中的方法，会自动使用 inline 关键字进行展开。

在类的方法中可以自由方法类的所有数据和方法，而不受任何限制。

和普通函数一样，类的声明和定义也应该分开，放在不同的文件内。在 OpenFOAM 中，大部分类都是使用此种模式。对于 inline 类型函数，需要将函数的定义放在对应的头文件内。

- 构造函数
构造函数是类的对象在调用时使用的特定的初始化函数。当没有使用特定的构造函数时，即使用 null 构造函数，对象的所有属性都是未定义的。
在初始化时，根据给定的参数不同调用对应的构造函数。下面给出了 Vector 类的构造函数的几个示例

>// Constructors
	// Construct null
	inline Vector();
	// Construct given VectorSpace
	inline Vector(const VectorSpace<Vector<Cmpt>, Cmpt, 3>&);
	// Construct given three components
	inline Vector(const Cmpt& vx, const Cmpt& vy, const Cmpt& vz);
	// Construct from Istream
	inline Vector(Istream&;)

- 析构函数
当对内存空间申请后，在类的析构函数中必须对内存进行释放。为保证所有内容都得到释放，最好显式的对析构函数进行定义。
在析构函数中不需要任何参数，并且函数名与类名相同，但是函数名前增加了 ~ 符号。
定义的对象在离开作用域时应该释放其空间，特别是使用 new 关键字申请对象应手动使用 delete 进行删除。

- 常数成员函数
常数关键字 constant 可以用于修饰成员函数。对于常数类型成员函数，其含义是函数内对象不会进行修改。常数的成员函数定义方法为在参数后添加 const 修饰符，例如

> template <class Cmpt>
inline const Cmpt& Vector<Cmpt>::x() const
{
	return this->v_[X];
}

- 友元
友元 friend 代表一个函数或类可以访问某个类的私有属性。一个类可以声明哪些类型为自己的友元，但是无法声明自己为哪些类型的友元。

- 操作符
操作符定义了如何对特定的类型进行操作。标准操作符包括以下几种



操作符应当被定义为成员函数或友元函数，函数名为 operatorX，其中 X 用对应的操作符号代替。

在 OpenFOAM 中为所有的类型都定义了对应的操作符，包括 iostream 符 << 和 >>。

- 静态成员
静态成员在类之中具有单独的实例，即所有对象中都一样。静态成员使用关键字 static，可以应用在数据成员或成员函数中。由于静态成员不属于任何一个特定的对象，因此调用时必须用类名进行调用，如

className::staticFunction(parameters);
- 继承
一个类可以继承另一个已有类的属性，并扩展包含其他属性。继承的定义方法为

class newClass : public oldClass { ...members... }
在 OpenFOAM 中，类的继承形式为

template <class Cmpt>
class Vector
:
	public VectorSpace<Vector<Cmpt>, Cmpt, 3>
这里，Vector 是 VectorSpace 的一个子类。

子类的名字可以与父类相同，此时父类中所有同名成员会被隐藏，即使父类与子类成员函数的变量个数不同。

隐藏的父类成员可以通过 oldClass::member 方式访问。在类中的定义的不同访问属性中，private 成员无法在子类中访问，而 public 和 protected 属性成员可以。子类可以有多个父类，从而合并各个类的特性。

- 虚函数
虚成员函数主要用于动态绑定，即根据运行时调用的方式来确定具体函数。
虚函数使用 virtual 关键字，通过使用指针指向父类的对象来实现动态绑定 p = new subClass (...parameters...)，指针可以指向任何子类，从而使用 p->memberFunction 来调用具体函数。

具有至少一个虚函数的类为虚类，虚类无法实例化对象，主要作用是规定子类的定义方式。

- 模板
大部分类的定义都是针对特性数据类型，但是有些操作是与数据类型无关的，此时与其将相同的算法针对不同的类型定义许多遍，更常用的方法是定义模板使之适用于任意类型。
模板类在定义时在类前添加如下代码

template<class T>
其中 T 是一般参数，代表任意类型，关键字 class 定义了 T 为类型变量。一般参数随后在类的定义中使用指定的类型进行定义，模板类在构造对象时的形式为

templateClass<type> templateClassObject;
OpenFOAM 广泛使用模板，为了使代码易读性更好，通常将模板类名字用 typedef 重新定义，例如

typedef List<vector> vectorList;
上面代码将 vectorList 定义为 vector 数据类型的模板 List 类的别名。