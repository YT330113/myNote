// 图书馆图书借阅管理系统.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "Date.h"
#include <ctime>
#include <iostream>

using namespace std;

int main()
{
    /*获取计算机系统时间*/
    time_t nowtime;
    time(&nowtime);                     // 获取日历时间
    struct tm local;
    localtime_s(&local, &nowtime);      // 获取当前系统时间
    int year = local.tm_year + 1900;
    int month = local.tm_mon + 1;
    int day = local.tm_mday;
    /*测试Date类*/
    Date date1(year, month, day);
    date1.show();
    char* p = date1.toString();
    cout << p << endl;
    Date date2(p);
    date2.show();
    cout << "十天前：";
    Date date3 = date2.subDays(10);
    date3.show();
    cout << "十天后：";
    Date date4 = date2.addDays(10);
    date4.show();
    Date date5;
    cout << "Date date5 is: ";
    date5.show();
    date5.setDate(2015, 2, 2);
    cout << "After modify,Date date5 is: ";
    date5.show();
    cout << date5.GetYear() << ":";
    cout << date5.GetMonth() << ":";
    cout << date5.GetDay() << endl;
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
