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
>#include <cstdio>
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
  >#include <iostream>
using namespace std;
int main ()
{
double a = 3.1415927;
double &b = a; // b 是 a的别名，b就是a
b = 89; //也就是a的内存块值为89
cout << "a contains: " << a << endl; // Displays 89.
return 0;
}

  交换a,b值的三种程序：

  - >#include <iostream>
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
  - >void swap(int *x, int *y) {
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
  - >//x,y是实参的引用
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

**比指针好用**

**效率高** 
当实参占据内存大时，用引用代替传值（需要复制）可提高效率

**不希望形参改变实参的值时**
如果不希望因此无意中修改实参，可以在形参前面加一个const修改符，const表示不可修改、常数

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
- 通过 `try-catch`处理异常情况

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
Vector2 operator * (double a, Vector2 b){       //相当于定义了一个数乘以一个向量
Vector2 r;
r.x = a * b.x;
r.y = a * b.y;
return r;
}
Vector2 operator+ (Vector2 a, Vector2 b) {      //相当于定义了两向量相加
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


