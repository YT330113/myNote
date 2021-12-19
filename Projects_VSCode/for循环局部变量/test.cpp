
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