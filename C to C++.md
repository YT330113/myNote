//-----------“2小时从C到C++快速入门（2018）”-------

//bilibili:https://www.bilibili.com/video/

- C++头文件不必是.h结尾，C语言中的标准库头文件如math.h,stdio.h在C++被命名为cmath,cstdio
```C++
#include <cmath>
#include <cstdio>
int main(){
double a = 1.2;
a = sin (a);
printf("%lf\n",a);
}
```
- 除了C的多行注释，C++可以使用单行注释
```C++
/*
CC的多行注释`
用于注释一块代码
*/
#include <cmath>
#include <cstdio>
int main(){ //程序执行的入口，main主函数
double a = 1.2; //定义一个变量a
a = sin (a);
printf("%lf\n",a); //用格式符%lf输出a: lf表示是double型
}
```
- 名字空间namespace.
为防止名字冲突(出现同名),C++引入了名字空间( namespace)，
通过::运算符限定某个名字属于哪个名字空间

```cpp
#include <cstdio>
namespace first
{
int a;
void f(){/*...*/}
int g(){/*...*/}
}
namespace second
{
double a;
double f(){/*...*/}
char g;
}
int main ()
{
first::a = 2;
second::a = 6.453;
first::a = first::g()+second::f();
second::a = first::g()+6.453;
printf("%d\n",first::a);
printf("%lf\n",second::a);
return 0;
}
```



- C++的新的输入输出流库(头文件iostream)将输入输出看成一个流，并用
输出运算符 << 和输入运算符 >> 对数据(变量和常量进行输入输出);
其中有cout和cin分别代表标准输出流对象(屏幕窗口)和标准输入流对象(键盘);
标准库中的名字都属于标准名字空间std.
```c++
    #include <iostream>
    #include <cmath>
    using std::cout; //使用单个名字
    int main()
    {
    double a;
    cout << "从键盘输入一个数" << std::endl; //endl表示换行符，并强制输出
    std::cin >> a; // 通过“名字限定”std::cin,
    //cin是代表键盘的输入流对象，>>等待键盘输入一个实数
    a = sin(a);
    cout << a; //cout是代表屏幕窗口的输出流对象
    return 0;
    }
    #include <iostream> //标准输入输出头文件
    #include <cmath>
    using namespace std; //引入整个名字空间std中的所有名字
    //cout cin都属于名字空间std;
    int main() {
        double a;
    cout << "从键盘输入一个数" << endl;
    cin >> a;
    a = sin(a);
    cout << a;
    return 0;
    }
```
- 变量“即用即定义”，且可用表达式初始化
```c++
#include <iostream>
using namespace std;
int main (){
double a = 12 * 3.25;
double b = a + 1.112;
cout << "a contains : " << a << endl;
cout << "b contains: " << b << endl;
a = a * 2 + b;
double c = a + b * a; //“即用即定义”，且可用表达式初始化
cout << "c contains: " << c << endl;
}
```
- 程序块`{}`内部作用域可定义域外部作用域同名的变量，在该块里就隐藏了外部变量
```CPP
#include <iostream>
using namespace std;
int main ()
{
    double a;
    cout << "Type a number: ";
    cin >> a;
    {
        int a = 1; // "int a"隐藏了外部作用域的“double a"
        a = a * 10 + 4;
        cout << "Local number: " << a << endl;
    }
    cout << "You typed: " << a << endl; //main作用域的“double a"
    return 0;
}
```
- for循环语句可以定义局部变量。
```cpp
#include <iostream>
using namespace std;
int main (){
    int i = 0;
    for (int i = 0; i < 4; i++)
    {
        cout << i << endl;
    }
    cout << "i contains: " << i << endl;
    for (i = 0; i < 4; i++)
    {
        for (int i = 0; i < 4; i++) // we're between
        { // previous for's hooks
            cout << i<< " ";
        }
        cout << endl;
    }
    return 0;
}
```
- 访问和内部作用域变量同名的全局变量，要用全局作用域限定` :: `

==::是全局作用域限定符，cout<< :: a表示输出全局变量a，全局变量指在main函数前定义的变量，通常指常量==

```cpp
#include <iostream>
using namespace std;
double a = 128;
int main (){
double a = 256;
cout << "Local a: " << a << endl;
cout << "Global a: " <<::a << endl; //::是全局作用域限定
return 0;
}
```
- C++引入了**引用类型**，即一个变量是另一个变量的别名,`&`符号

==引用是为函数传参准备的，是指针传参的升级版==

```cpp
#include <iostream>
using namespace std;
int main ()
{
double a = 3.1415927;
double &b = a; // b 是 a的别名，b就是a
b = 89; //也就是a的内存块值为89
cout << "a contains: " << a << endl; // Displays 89.
return 0;
}
```
  交换a,b值的三种程序：


```cpp
#include <iostream>
using namespace std;
void swap(int x, int y) {
cout << "swap函数内交换前：" << x << " " << y << endl;
int t = x; x = y; y = t;
cout << "swap函数内交换后：" << x << " " << y << endl;
}
int main(){
int a = 3, b = 4;
swap(a, b);
cout << a << ", " << b << endl; // Displays 100, 4.
return 0;
}
/*
x,y得到2个int型变量的指针,x,y本身没有修改
修改的是x,y 指向的那2个int型变量的内容
*/
```

```cpp

void swap(int *x, int *y) {
cout << "swap函数内交换前：" << *x << " " << *y << endl;
int t = *x; *x = *y; *y = t;
cout << "swap函数内交换后：" << *x << " " << *y << endl;
}
int main() {
int a = 3, b = 4;
swap(&a, &b); // &a赋值给x,&b赋值给y,
//x,y分别是int*指针，指向a,b
//*x, *y就是a和b
cout << a << ", " << b << endl; // Displays 100, 4.
return 0;
}
```
```cpp
//x,y是实参的引用
void swap(int &x, int &y) {
cout << "swap函数内交换前：" << x << " " << y << endl;
int t = x; x = y; y = t;
cout << "swap函数内交换后：" << x << " " << y << endl;
}
int main(){
int a = 3, b = 4;
swap(a, b); //x,y将分别是a,b的引用，即x就是a,y就是b
cout << a << ", " << b << endl; // Displays 100, 4.
return 0;
}
```
**比指针好用**

**效率高** 
当实参占据内存大时，用引用代替传值（需要复制）可提高效率

**不希望形参改变实参的值时**
如果不希望因此无意中修改实参，可以在形参前面加一个==const修改符==，const表示不可修改、常数

```cpp
#include <iostream>
using namespace std;
void change (double &x, const double &y,double z){
x = 100;
y = 200; //错！ y不可修改，是const double &
z = 300;
}
int main (){
double a,b,c;//内在类型变量未提供初始化式，默认初始化为0
change(a, b, c);
cout << a << ", " << b << ", " << c << endl; // Displays 100, 4.
return 0;
} 
```
- 内联函数
  

对于不包含循环的简单函数，建议用`inline`关键字声明 为**inline内联函数**，编译器将内联函数调用用其代码展开，称为“内联展开”，避免函数调用开销，提高程序执行效率
```cpp
#include <iostream>
#include <cmath>
using namespace std;
inline double distance(double a, double b) {
return sqrt(a * a + b * b);
}
int main() {
double k = 6, m = 9;
// 下面2行将产生同样的代码:
cout << distance(k, m) << endl;//这句语句不当作函数调用，相当于下一行的效果，没有函数调用参数传递的额外过程
cout << sqrt(k * k + m * m) << endl;
return 0;
}
```
- 通过 `try-catch`处理==异常==情况

正常代码放在try函数块，catch函数快中捕获try块抛出的异常

```cpp
#include <iostream>
#include <cmath>
using namespace std;
int main (){
int a, b;
cout << "Type a number: ";
cin >> a;
cout << endl;
try {
if (a > 100) throw 100;
if (a < 10) throw 10;
throw "hello";
}
catch (int result) {
cout << "Result is: " << result << endl;
b = result + 1;
}
catch (char * s) {
cout << "haha " << s << endl;
}
cout << "b contains: " << b << endl;
cout << endl;



// another example of exception use:
char zero[] = "zero";
char pair[] = "pair";
char notprime[] = "not prime";
char prime[] = "prime";
try {
if (a == 0) throw zero;
if ((a / 2) * 2 == a) throw pair;
for (int i = 3; i <= sqrt (a); i++){
if ((a / i) * i == a) throw notprime;
}
throw prime;
}
catch (char *conclusion) {
cout << "异常结果是： " << conclusion << endl;
}
catch (...) {
cout << "其他异常情况都在这里捕获 " << endl;
}
cout << endl;
return 0;
}
```
- 默认形参
  
  函数的形参可带有默认值，但**必须一律在最右边**
```cpp
#include <iostream>
using namespace std;
double test(double a, double b = 7) {//参数b默认是7
return a - b;
}
int main() {
cout << test(14, 5) << endl;
cout << test(14) << endl;
return 0;
}
/*错： 默认参数一律靠右*/
double test(double a, double b = 7, int c) {//默认参数b=7没在最右边
return a - b;
}
```

- 函数重载
  
  C++允许函数同名**函数名相同**，只要它们的形参不一样(参数个数或对应参数类型任一不同均可)
  
  调用函数时将根据实参和形参的匹配选择最佳函数，看参数类型和参数个数
  
  如果有多个难以区分的最佳函数，则变化一起报错！
  
  注意：不能根据返回值类型区分同名函数 `void fun（int a,int b）`和`int fun（int a,int b）`不可以！
```cpp
#include <iostream>
using namespace std;
double add(double a, double b) {
return a + b;
}
int add(int a, int b) {
return a + b;
}

//错：编译器无法区分int add (int a, int b),void add (int a, int b )
void add(int a, int b) {
return a - b;
}
int main() {
double m = 7, n = 4;
int k = 5, p = 3;
cout << add(m, n) << " , " << add(k, p) << endl;
return 0;
}
```

- 运算符重载

```cpp
#include <iostream>
using namespace std;
struct Vector2{
double x;
double y;
};
Vector2 operator*(double a, Vector2 b){       //相当于定义了一个数乘以一个向量
Vector2 r;
r.x = a * b.x;
r.y = a * b.y;
return r;
}
Vector2 operator+(Vector2 a, Vector2 b) {      //相当于定义了两向量相加
Vector2 r;
r.x = a.x + b.x;
r.y = a.y + b.y;
return r;
}
int main (){
Vector2 k, m;       // C++定义的struct类型前不需要再加关键字struct:"struct vector"
k.x = 2;        //用成员访问运算符.访问成员
k.y = -1;
m = 3.1415927 * k;      // Magic!

cout << "(" << m.x << ", " << m.y << ")" << endl;
Vector2 n = m + k;
cout << "(" << n.x << ", " << n.y << ")" << endl;
return 0;
}


#include <iostream>
using namespace std;
struct Vector2 {
double x;
double y;
};
ostream& operator << (ostream& o, Vector2 a){       //重新定义输出运算符，相当于一次直接输出一个向量
o << "(" << a.x << ", " << a.y << ")";
return o;
}
int main (){
Vector2 a;
a.x = 35;
a.y = 23;
cout << a << endl; // 相当于执行 operator <<(cout,a);
return 0;
}
```
- 模板函数 template

  当用同一套函数流程而数据类型却不同要定义很很多相似的函数时，可以用函数模板

  厌倦了对每种类型求最小值

```cpp
#include <iostream>
using namespace std;

int minValue(int a, int b) {//return a<b?a:b
if (a < b) return a;
else return b;
}

double minValue(double a, double b) {//return a<b?a:b
if (a < b) return a;
else return b;
}

int main() {
int i = 3, j = 4;
cout << "min of " << i << " and " << j << " is " << minValue(i, j) << endl;
double x = 3.5, y = 10;
cout << "min of " << x << " and " << y << " is " << minValue(x, y) << endl;
}



//可以转化成： 模板函数
#include <iostream>
using namespace std;
//可以对任何能比较大小(<)的类型使用该模板让编译器
//自动生成一个针对该数据类型的具体函数
template<class TT>      //定义一个模板类函数
TT minValue(TT a, TT b) {//return a<b?a:b
if (a < b) return a;
else return b;
}
int main() {
int i = 3, j = 4;
cout << "min of " << i << " and " << j << " is " << minValue(i, j) << endl;
double x = 3.5, y = 10;
cout << "min of " << x << " and " << y << " is " << minValue(x, y) << endl;



//但是,不同类型的怎么办？
cout << "min of " << i << " and " << y << " is " << minValue(i, y) <<
endl;
}       //出错


//可以对任何能比较大小(<)的类型使用该模板让编译器
//自动生成一个针对该数据类型的具体函数
#include <iostream>
using namespace std;
template<class T1, class T2>
T1 minValue(T1 a, T2 b) {//return a<b?a:b
if (a < b) return a;
else return (T2)b; //强制转化为T1类型
}
int main() {
int i = 3, j = 4;
cout << "min of " << i << " and " << j << " is " << minValue(i, j) <<
endl;
double x = 3.5, y = 10;
cout << "min of " << x << " and " << y << " is " << minValue(x, y) <<
endl;
//但是,不同类型的怎么办？
cout << "min of " << i << " and " << y << " is " << minValue(i, y) <<
endl;
}
```

- `new`和`delete`
  动态内存分配： 关键字` new `和` delete `比C语言的`malloc/alloc/realloc`和`free`更好，可以对类对象调用初始化构造函数或销毁析构函数

```cpp

#define _CRT_SECURE_NO_WARNINGS //windows
#include <iostream>
#include <cstring>
using namespace std;
int main() {
    double d = 3.14;      // 变量d是一块存放double值的内存块
    double * dp;           // 指针变量dp：保存double类型的地址的变量
                          // dp的值得类型是double *
                          // dp是存放double *类型值 的内存块
    dp = &d;              //取地址运算符&用于获得一个变量的地址，(指针dp指向double型变量d)
                          // 将double变量d的地址(指针)保存到double*指针变量dp中
                          // dp和&d的类型都是double *
    *dp = 4.14;           //解引用运算符*用于获得指针变量指向的那个变量(C++中也称为对象)
                          //*dp就是dp指向的那个d
    cout << "*dp= " << *dp << " d=:" << d << endl;



    cout << "Type a number: ";
    cin >> *dp;           //输出dp指向的double内存块的值
    cout << "*dp= " << *dp << " d=:" << d << endl;


    dp = new double;      // new 分配正好容纳double值的内存块（如4或8个字节）
                          // 并返回这个内存块的地址，而且地址的类型是double *
                          //这个地址被保存在dp中，dp指向这个新内存块，不再是原来d那个内存块了
                          // 但目前这个内存块的值是未知的
                          // 注意：
                          // new 分配的是堆存储空间，即所有程序共同拥有的自由内存空间
                          //而d,dp等局部变量是这个程序自身的静态存储空间
                          // new会对这个double元素调用double类型的构造函数做初始化，比如初始化为0
    *dp = 45.3;           //*dp指向的double内存块的值变成45.3


    cout << "Type a number: ";
    cin >> *dp;           //输出dp指向的double内存块的值
    cout << "*dp= " << *dp << endl;

    *dp = *dp + 5;        //修改dp指向的double内存块的值45.3+5
    cout << "*dp= " << *dp << endl;
    delete dp;            // delete 释放dp指向的动态分配的double内存块




    dp = new double[5];    //new 分配了可以存放15个double值的内存块，
                            //返回这块连续内存的起始地址，而且指针类型是
                            //double *， 实际是第一个double元素的地址
                            // new会对每个double元素调用double类型的构造函数做初始化，比如初始化为0

    dp[0] = 4456;           // dp[0]等价于 *(dp+0)即*dp，也即是第1个double元素的内存块
    dp[1] = dp[0] + 567;    // dp[1]等价于 *(dp+1)，也即是第2个double元素的内存块
    cout << "d[0]=: " << dp[0] << " d[1]=: " << dp[1] << endl;

    delete[] dp;            // 释放dp指向的多个double元素占据的内存块，
                            // 对每个double元素调用析构函数以释放资源
                            // 缺少[]，只释放第一个double元素的内存块，这叫“内存泄漏”


    int n = 8;

    dp = new double[n];     // new 可以分配随机大小的double元素，
                            // 而静态数组则必须是编译期固定大小，即大小为常量
                            // 如 double arr[20];
                            //通过下标访问每个元素
    for (int i = 0; i < n; i++) {
        dp[i] = i;
    }                       //通过指针访问每个元素

    double *p = dp;
    for (int i = 0; i < n; i++) {
        cout << *(p + i) << endl;   //p[i]或dp[i]
    }
    cout << endl;

    for (double *p = dp, *q = dp + n; p < q; p++) {
        cout << *p << endl;
    }
    cout << endl;

    delete[] dp;


    char *s;
    s = new char[100];
    strcpy(s, "Hello!");      //将字符串常量拷贝到s指向的字符数组内存块中
    cout << s << endl;
    delete[] s;               //用完以后，记得释放内存块，否则会“内存泄漏”！

    return 0;
}

```
2021 12 10

---
- 类：是在C的struct类型上，增加了“成员函数”。
- C的strcut可将一个概念或实体的所有属性组合在一起，描述同一类对象的共同属性，
- C++使得struct不但包含数据，还包含函数(方法)用于访问或修改类变量(对象)的这些属性。

```cpp
#include <iostream>
using namespace std;
struct Date {
    int d, m, y;
    void init(int dd, int mm, int yy) {
        d = dd; m = mm; y = yy;
    }

    void print() {
        cout << y << "-" << m << "-" << d << endl;
    }
};

int main (){
    Date day; 
    day.print();          //通过类Date对象day调用类Date的print方法
    day.init(4, 6, 1999); //通过类Date对象day调用类Date的init方法
    day.print();          //通过类Date对象day调用类Date的print方法

    return 0;
}

```
```cpp
// 成员函数 返回 “自引用” （*this）


#include <iostream>
using namespace std;
struct Date {
  int d, m, y;

  void init(int dd, int mm, int yy) {
    d = dd; m = mm; y = yy;
  }

  void print() {
    cout << y << "-" << m << "-" << d << endl;
  }

 Date& add(int dd) {
    d = d + dd;
    return *this; //this是指向调用这个函数的类型对象指针，
                  // *this就是调用这个函数的那个对象
                  //这个成员函数返回的是“自引用”，即调用这个函数的对象本身
                  //通过返回自引用，可以连续调用这个函数
                  // day.add(3);
                  // day.add(3).add(7);
  }
};

int main() {
  Date day;
  day.print(); //通过类Date对象day调用类Date的print方法
  day.init(4, 6, 1999); //通过类Date对象day调用类Date的init方法
  day.print(); //通过类Date对象day调用类Date的print方法
  day.add(3);
  day.add(5).add(7);
  day.print();

  return 0;
}

```


```cpp
//成员函数重载“运算符函数”


#include <iostream>
using namespace std;
struct Date {
  int d, m, y;

  void init(int dd, int mm, int yy) {
    d = dd; m = mm; y = yy;
  }

  void print() {
    cout << y << "-" << m << "-" << d << endl;
  }

  Date& operator+=(int dd) {
    d = d + dd;
    return *this; //this是指向调用这个函数的类型对象指针，
                  // *this就是调用这个函数的那个对象
                  //这个成员函数返回的是“自引用”，即调用这个函数的对象本身
                  //通过返回自引用，可以连续调用这个函数
                  // day.add(3);
                  // day.add(3).add(7);
  }
};

int main() {
  Date day;
  day.print(); //通过类Date对象day调用类Date的print方法
  day.init(4, 6, 1999); //通过类Date对象day调用类Date的init方法
  day.print(); //通过类Date对象day调用类Date的print方法
  day += 3; // day.add(3);
  (day += 5) += 7; //day.add(5).add(7);
  day.print();

return 0;
}
```
- 构造函数和析构函数
  - 构造函数是**和类名同名**且**没有返回类型**的函数，**在定义对象时会自动被调用**，而不需要在单独调用专门的初始化函数如init，
  - 构造函数**用于初始化类对象成员**，包括申请一些资源，如分配内存、打开某文件等
  - 析构函数是在类对象销毁时被自动调用，用于释放该对象占用的资源，如释放占用的内存、关闭打开的文件

```cpp
#include <iostream>
using namespace std;
struct Date {
  int d, m, y;

  Date(int dd, int mm, int yy) {  //Date函数与类同名，且没有返回值，是构造函数；构造函数在定义一个该类对象的时候会被自动调用
    d = dd; m = mm; y = yy;
    cout << "构造函数" << endl;
  }

  void print() {
    cout << y << "-" << m << "-" << d << endl;
  }

  ～Date() {        //析构函数名是~和类名，且不带参数，没有返回类型
                    //目前不需要做任何释放工作，因为构造函数没申请资源
    cout << "析构函数" << endl;
  }
};
int main(){
  Date day;         //错：会自动调用构造函数，但没提供3个参数
                    //即时不定义构造函数，C++也会自动生成一个默认构造函数，默认构造函数不包含参数 

  Date(4, 6, 1999); //会自动调用构造函数Date(int dd, int mm, int yy)
                    // day.init(4, 6, 1999); //通过类Date对象day调用类Date的init方法
  day.print();      //通过类Date对象day调用类Date的print方法

  return 0;
}

```

执行上述代码，看看构造函数和析构函数执行了吗？

假如想如下调用构造函数构造对象，是不是要定义多个同名的构造函数（即重载构造函数）?

```cpp
Date day;
Date day1（2）;
Date day2(23, 10);
Date day3(2,3,1999);
```
当然可以的

```cpp
struct Date {
  int d, m, y;

  Date() {
    d = m = 1; y = 2000;
    cout << "构造函数" << endl;
  }

  Date(int dd) {
    d = dd; m = 1; y = 2000;
    cout << "构造函数" << endl;
  }

  Date(int dd, int mm) {
    d = dd; m = mm; y = 2000;
    cout << "构造函数" << endl;
  }

  Date(int dd, int mm, int yy) {
    d = dd; m = mm; y = yy;
    cout << "构造函数" << endl;
  }

  void print() {
  cout << y << "-" << m << "-" << d << endl;
}

  ~Date() {             //析构函数名是~和类名，且不带参数，没有返回类型
                        //目前不需要做任何释放工作，因为构造函数没申请资源
    cout << "析构函数" << endl;
  }
};

```

为什么不用默认参数呢？也可以使用c++特有的默认参数功能，即定义的时候就初始化

```cpp
#include <iostream>
using namespace std;
using namespace std;

struct Date {
  int d, m, y;

  Date(int dd = 1, int mm = 1, int yy = 1999) {
    d = dd; m = mm; y = yy;
    cout << "构造函数" << endl;
  }

  void print() {
    cout << y << "-" << m << "-" << d << endl;
    }

  ~Date() {                 //析构函数名是~和类名，且不带参数，没有返回类型
                            //目前不需要做任何释放工作，因为构造函数没申请资源
    cout << "析构函数" << endl;
  }
};

int main(){
  Date day;
  Date day1(2);
  Date day2(23, 10);
  Date day3(2, 3, 1999);
  day.print();
  day1.print();
  day2.print();
  day3.print();

  return 0;
}

```

```cpp
//析构函数示例


#define _CRT_SECURE_NO_WARNINGS      //windows系统,可防止报错
#include <iostream>
#include <cstring>

using namespace std;

struct student {

  char *name;
  int age;

  student(char *n = "no name", int a = 0) {
    name = new char[100]; // 比malloc好!
    strcpy(name, n);      //指针不能赋值给指针变量，所以对于字符串类型变量要用字符拷贝strcpy函数来赋值
    age = a;
    cout << "构造函数，申请了100个char元素的动态空间" << endl;
}

  virtual ~student(){         // 析构函数
    delete name;              // 不能用free!
    cout << "析构函数，释放了100个char元素的动态空间" << endl;
  }
};

int main() {
  cout << "Hello!" << endl << endl;
  student a;      //student类有默认值初始化，所以对象a为默认值
                  //在定义student类对象a时会默认自动调用一次构造函数即student函数
  cout << a.name << ", age " << a.age << endl << endl;
  student b("John");
  cout << b.name << ", age " << b.age << endl << endl;

  b.age = 21;
  cout << b.name << ", age " << b.age << endl << endl;
  student c("Miki", 45);
  cout << c.name << ", age " << c.age << endl << endl;
  cout << "Bye!" << endl << endl;

  return 0;              //程序执行完毕后会执行三次析构函数来释放掉申请的动态内存空间
}

```
- 访问控制、类接口
  将关键字struct换成class
  struct 默认public，class默认private

```cpp

#include <iostream>
#include <cstring>

using namespace std;

class student {
  char *name;
  int age;

  student(char *n = "no name", int a = 0) {
    name = new char[100]; // 比malloc好!
    strcpy(name, n);
    age = a;
    cout << "构造函数，申请了100个char元素的动态空间" << endl;
  }

  virtual ~student() { // 析构函数
    delete name; // 不能用free!
    cout << "析构函数，释放了100个char元素的动态空间" << endl;
  }
};

int main() {
  cout << "Hello!" << endl << endl;
  student a;                                           //编译出错:无法访问 private 成员(在“student”类中声明)
  cout << a.name << ", age " << a.age << endl << endl; //编译出错
  student b("John");                                   //编译出错
  cout << b.name << ", age " << b.age << endl << endl;                                //编译出错
  b.age = 21;                                           //编译出错
  cout << b.name << ", age " << b.age << endl << endl;  //编译出错
  
  return 0;
}

```
class定义的类的成员默认都是私有的private，外部函数无法通过类对象成员或类成员函数访问

```cpp
#include <iostream>
#include <cstring>

using namespace std;

class student {
                    //默认私有的，等价于 private:
    char *name;
    int age;
public: //公开的
    student(char *n = "no name", int a = 0) {
        name = new char[100]; // 比malloc好!
        strcpy(name, n);
        age = a;
        cout << "构造函数，申请了100个char元素的动态空间" << endl;
    }
    virtual ~student() { // 析构函数

        delete name; // 不能用free!
       cout << "析构函数，释放了100个char元素的动态空间" << endl;
    }
};
int main() {
    cout << "Hello!" << endl << endl;
    student a; //OK
    cout << a.name << ", age " << a.age << endl ; //编译出错: 无法访问private 成员(在“student”类中声明)
    student b("John");
    cout << b.name << ", age " << b.age << endl ;//编译出错
    b.age = 21;
    cout << b.name << ", age " << b.age << endl l;//编译出错
    return 0;
}



a.name，a.age仍然不能访问， 如何进一步修改呢？


#include <iostream>
#include <cstring>

using namespace std;

class student {
//默认私有的，等价于 private:
    char *name;
    int age;
public: //公开的
    char *get_name() { return name; }
    int get_age() { return age; }
    void set_age(int ag) { age = ag; }
    student(char *n = "no name", int a = 0) {
        name = new char[100]; // 比malloc好!
        strcpy(name, n);
        age = a;
        cout << "构造函数，申请了100个char元素的动态空间" << endl;
    }
    virtual ~student() { // 析构函数
        delete name; // 不能用free!
        cout << "析构函数，释放了100个char元素的动态空间" << endl;
    }
};

int main() {
    cout << "Hello!" << endl << endl;

    student a;
    cout << a.get_name() << ", age " << a.get_age() << endl ; //编译出错

    student b("John");
    cout << b.get_name() << ", age " << b.get_age() << endl l; //编译出错

    b.set_age(21);
    cout << b.get_name() << ", age " << b.get_age() << endl ; //编译出错

    return 0;
}

```

- 接口：public的公开成员（一般是成员函数）称为这个类的对外接口，外部函数只能通过这些接口访问类对象，
- private等非public的包含内部内部细节，不对外公开，从而可以封装保护类对象！

```cpp
定义一个数组类array

#include <iostream>
#include <cstdlib>

using namespace std;

class Array {
    int size;
    double *data;
public:
    Array(int s) {
    size = s;
    data = new double[s];
    }

    virtual ~Array() {
        delete[] data;
    }

    double &operator [] (int i) {
        if (i < 0 || i >= size){
            cerr << endl << "Out of bounds" << endl;
            throw "Out of bounds";
        }
        else return data[i];
    }
};

int main() {
    Array t(5);

    t[0] = 45; // OK
    t[4] = t[0] + 6; // OK
    cout << t[4] << endl; // OK
    t[10] = 7; // error!

    return 0;
}

```

---
2021 12 11

- 拷贝构造函数：定义一个类对象时用同类型的另外对象初始化
- 赋值运算符：一个对象赋值给另外一个对象

```cpp
#define _CRT_SECURE_NO_WARNINGS //windows系统
#include <iostream>
#include <cstdlib>
using namespace std;
struct student {
char *name;
int age;
student(char *n = "no name", int a = 0) {
name = new char[100]; // 比malloc好!
strcpy(name, n);
age = a;
cout << "构造函数，申请了100个char元素的动态空间" << endl;
}
virtual ~student() { // 析构函数
delete[] name; // 不能用free!
cout << "析构函数，释放了100个char元素的动态空间" << endl;
}
};
int main() {
student s;
student k("John", 56);
cout << k.name << ", age " << k.age << endl;
student m(s); //拷贝构造函数
s = k; //赋值运算符
cout << s.name << ", age " << s.age << endl;
return 0;
}
默认的“拷贝构造函数”是“硬拷贝”或“逐成员拷贝”，name指针同一块动态字符数组，当多次释
放同一块内存就不错了！
指应该增加“拷贝构造函数”，保证各自有单独的动态数组空间。
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
using namespace std;
struct student {
char *name;
int age;
student(char *n = "no name", int a = 0) {
name = new char[100]; // 比malloc好!
strcpy(name, n);
age = a;
cout << "构造函数，申请了100个char元素的动态空间" << endl;
}
student(const student &s) { // 拷贝构造函数 Copy
constructor
name = new char[100];
strcpy(name, s.name);
age = s.age;
cout << "拷贝构造函数，保证name指向的是自己单独的内存块" << endl;
}
student & operator=(const student &s) { // 拷贝构造函数
Copy constructor
strcpy(name, s.name);
age = s.age;
cout << "拷贝构造函数，保证name指向的是自己单独的内存块" << endl;
return *this; //返回 “自引用”
}
virtual ~student(){ // 析构函数
delete[] name; // 不能用free!
cout << "析构函数，释放了100个char元素的动态空间" << endl;
}
};
int main() {
student s;
student k("John", 56);
cout << k.name << ", age " << k.age << endl ;
student m(k);
s = k;
cout << s.name << ", age " << s.age << endl ;
return 0;
}

```

- 类体外定义方法（成员函数），必须在类定义中声明，类体外要有类作用域，否则就是全局外部函数了！

```cpp

#include <iostream>
using namespace std;

class Date {
    int d, m, y;
public:
    void print();         //类申明代码，先提前申明一个函数，但不但不定义方法
    Date(int dd = 1, int mm = 1, int yy = 1999) {
        d = dd; m = mm; y = yy;
        cout << "构造函数" << endl;
    }

    virtual ~Date() {       //析构函数名是~和类名，且不带参数，没有返回类型
                            //目前不需要做任何释放工作，因为构造函数没申请资源
        cout << "析构函数" << endl;
    }
};

void Date::print() {    //类实现方法代码，在类外部定义如何实现类函数
    cout << y << "-" << m << "-" << d << endl;
}

int main() {
    Date day;
    day.print();
}

```
- 所有类成员函数都可以在外部定义，但要在类内部申明，在外部定义类成员函数时要加类作用域限定符`::`。
  
- 类模板：我们可以将一个类变成“类模板”或“模板类”，正如一个模板函数一样。

```cpp
//将原来的所有double换成模板类型T，并加上模板头 template<class T>

#include <iostream>
#include <cstdlib>
using namespace std;
template<class T>
class Array {
T size;
T *data;
public:
Array(int s) {
size = s;
data = new T[s];
}
virtual ~Array() {
delete[] data;
}
T &operator [] (int i) {
if (i < 0 || i >= size) {
cerr << endl << "Out of bounds" << endl;
throw "index out of range";
}
else return data[i];
}
};
int main() {
Array<int> t(5);
t[0] = 45; // OK
t[4] = t[0] + 6; // OK
cout << t[4] << endl; // OK
t[10] = 7; // error!
Array<double> a(5);
a[0] = 45.5; // OK
a[4] = a[0] + 6.5; // OK
cout << a[4] << endl; // OK
a[10] = 7.5; // error!
return 0;
}

```

- typedef 类型别名

```cpp
#include <iostream>
using namespace std;
typedef int INT;
int main() {
INT i = 3; //等价于int i = 3;
cout << i << endl;
return 0;
}

```
- string
- string就是个**类** 类型，是c++标准库提供的标准类函数！


```cpp

//string对象的初始化

//string是c++标准库提供的标准类函数！

#include <iostream>
#include <string>        //typedef std::basic_string<char> string;

using namespace std;

typedef string String;

int main() {
// with no arguments
    string s1;          //调用默认构造函数：没有参数或参数有默认值，默认参数是“Anatoliy”
    String s2("hello"); //调用普通构造函数，用户提供参数 String就是string
    s1 = "Anatoliy";    //调用赋值运算符，"Anatoliy"是字符串类型，s1是string类型，通过赋值将字符串复制给s1
    String s3(s1);      //这是拷贝构造函数 相当于 string s3 =s1;

    cout << "s1 is: " << s1 << endl;
    cout << "s2 is: " << s2 << endl;
    cout << "s3 is: " << s2 << endl;


    string s4("this is a C_sting", 10);   //s4是拷贝"this is a C_sting"的前10个字符
    cout << "s4 is: " << s4 << endl;

    // 1 - C++ string
    // 2 - start position
    // 3 - number of characters
    string s5(s4, 6, 4);              // 从s4的第6个字符开始复制4个字符
    cout << "s5 is: " << s5 << endl;

    // 1 - number characters
    // 2 - character itself
    string s6(15, '*');               //复制15个*号
    cout << "s6 is: " << s6 << endl;

    // 1 - start iterator
    // 2 - end iterator
    string s7(s4.begin(), s4.end() - 5);//从s4的开始复制到结尾向前5个
    cout << "s7 is: " << s7 << endl;

    // you can instantiate string with assignment（赋值）
    string s8 = "Anatoliy";
    cout << "s8 is: " << s8 << endl;

    string s9 = s1 + "hello"+ s2; //s1 + "hello"+ s2的结果是string类型的对象(变量)
    cout << "s9 is: " << s9 << endl;

    return 0;
}

```
```cpp

//访问其中元素、遍历
//循环输出string类对象中的每个字符

#include <iostream>
#include <string>

using namespace std;

int main() {
    string s = "hell";
    string w = "worl!";
    s = s + w; //s +=w;

    //第一种，通过for循环，即通过下标访问
    for (int ii = 0; ii != s.size(); ii++)
        cout << ii << " " << s[ii] << endl;
    cout << endl;

    //第二种，通过迭代器变量
    string::const_iterator cii;   //const迭代器只能访问不能修改，别的也可以修改
    int ii = 0;   
    for (cii = s.begin(); cii != s.end(); cii++)    //cii相当于指针
        cout << ii++ << " " << *cii << endl;
}

```

- vector
  - 也是用来表示一组数据
  - 但其中的每个元素不一定是字符了
  - vector本身不是一个类，是个类模板

```cpp


#include <vector>
#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

int main() {
    vector<double> student_marks;
    int num_students;   //学生人数
    cout << "Number of students: " << endl;
    cin >> num_students;
    student_marks.resize(num_students);   //student_marks默认是0，现在重新设置为num_students

    //循环录入每个学生的mark
    for (vector<double>::size_type i = 0; i < num_students; i++) {    size_type是vector内部定义的一个类型，相当于整形，说是比较安全
        cout << "Enter marks for student #" << i + 1 << ": " << endl;
        cin >> student_marks[i];
    }

    cout << endl;
    //输出每个成绩
    for (vector<double>::iterator it = student_marks.begin();  
        it != student_marks.end(); it ++) { //iterator是类内部的一个迭代器类，it是一个迭代器类型的变量 ，it指向student_marks的起始位置
        cout << *it << endl;
    }
  
    return 0;
}


```

- 继承 Inheritance 
- 派生 Derivation
- 一个派生类(derived class)从1个或多个父类(parent class) / 基类(base class)继承，即继承父类的属性和行为，但也有自己的特有属性和行为

```c++

#include <iostream>
#include <string>
using namespace std;

class Employee{           //定义一个公司的雇员类
    string name;          //定义雇员姓名属性
public:   
    Employee(string n);   //构造函数，可以构造一个雇员
                          //在类体内先声明一个函数，函数实现定义在类体外
    void print();         //雇员有一个print的行为
};

class Manager: public Employee{ //雇员可以派生出一个经理，经理与雇员有相似属性，但也有特有属性
                                //继承格式，public表示完全继承，还有private等方式
    int level;                  //定义级别属性
public:
    Manager(string n, int l = 1); 
    //void print();        //不用再定义print行为，其父类已经有了这个行为，它已经继承过了
};

Employee::Employee(string n) :name(n)//定义在类体内声明过的函数
//初始化成员列表
{
//上一句相当于name = n;
}

void Employee::print() {
    cout << name << endl;
}

Manager::Manager(string n, int l) :Employee(n), level(l) {
}

//派生类的构造函数只能描述它自己的成员和其直接基类的初始式，不能去初始化基类的成员。
Manager::Manager(string n, int l) : name(n), level(l) {
}

int main() {
    Manager m("Zhang",2);
    Employee e("Li");
    m.print();
    e.print();
}

class Manager : public Employee
{
int level;
public:
Manager(string n, int l = 1);
void print();
};
Manager::Manager(string n, int l) :Employee(n), level(l) {
}
void Manager::print() {
cout << level << "\t";
Employee::print();
}
int main() {
Manager m("Zhang");
Employee e("Li");
m.print();
e.print();
}
```
