- Header头文件的正规写法 **（防卫式声明）**
  - 告诉编译器，如果不曾定义过这个名词的话就把它定义出来，同一个程序第二次引入时因为已经定义过了所以就不会再定义一次。

  - 例如：complex.h
```cpp
//头文件正规写法

#ifndef _COMPLEX_
#define _COMPLEX_

...

#endif
```
- 构造函数
```cpp

class complex
{
public:
    complex (double r=0,double i=0)     //默认参数
                                        //构造函数
        : re (r),im (i)                 //初始列，在声明阶段初始化，相当于在函数体内赋值，但更快
    { }
private:
    double re, im;
}
```