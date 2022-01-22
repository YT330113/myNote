// implementation of the Date class
#include "Date.h"
#include<string>
#include<iostream>
using namespace std;

/******Date类的公用成员函数的类外定义******/
Date::Date()
{
	year = 2015; month = 1;	day = 1;
}
Date::Date(char strDate[])		// 要求实参日期字符串中年月日之间的分隔符为冒号：
{	
	// 从日期字符串中提取年份信息
	char y[5];
	int i = 0;
	while (strDate[i] != '\0' && strDate[i] != ':')
	{
		y[i] = strDate[i];
		i++;
	}
	y[i] = '\0';
	year = atoi(y);				// atoi()函数表示 ascii to integer，把字符串转换成整型
	// 从日期字符串中提取月份信息
	if (strDate[i] != '\0')		i++;
	char m[3];
	int j = i, k = 0;
	while (strDate[i] != '\0' && strDate[i] != ':')	
	{
		m[i - j] = strDate[i];	i++;	k++;
	}
	m[k] = '\0';
	month = atoi(m);
	// 从日期字符串中提取日信息
	if (strDate[i] != '\0')		i++;
	char d[3];
	j = i, k = 0;
	while (strDate[i] != '\0' && strDate[i] != ':')
	{
		d[i - j] = strDate[i];	i++;	k++;
	}
	d[k] = '\0';
	day = atoi(m);
}
Date::Date(int Y,int M,int D):year(Y),month(M),day(D){}		// 构造函数参数初始化表，比函数体内赋值方便
void Date::setDate(int Y, int M, int D)		// 设置年、月、日的成员函数
{
	year = Y;	month = M;	day = D;
}
void Date::show()const					    // 显示日期的成员函数
{
	cout << year << "年（";
	if (isLeapYear())
		cout << "闰";
	else cout << "平";
	cout << "年）" << month << "月" << day << "日";
}
int Date::GetYear() { return year; }		// 单独获取年的成员函数
void Date::SetYear(int Y) { year = Y; }		// 单独设置年的成员函数
int Date::GetMonth() { return month; }		// 单独获取月的成员函数
void Date::SetMonth(int M) { month = M; }	// 单独设置月的成员函数
int Date::GetDay() { return day; }			// 单独获取日的成员函数
void Date::SetDay(int D) { day = D; }		// 单独设置日的成员函数
char* Date::toString()						// 把日期转换为字符串的函数
{
	char* arr = new char[20];
	char* IntToString(int);					// 将整数转换为字符串函数的原型声明
	strcpy(arr, IntToString(year));
	strcat(arr, ":");
	strcpy(arr, IntToString(month));
	strcat(arr, ":");
	strcat(arr, IntToString(day));
	return arr;
}
int Date::daysPerMonth(int m) const		// 计算每月多少天
{
	m = (m < 0) ? month : m;
	switch (m)
	{
	case 1:return 31;
	case 2:return isLeapYear(year) ? 29 : 28;
	case 3:return 31;
	case 4:return 30;
	case 5:return 31;
	case 6:return 30;
	case 7:return 31;
	case 8:return 31;
	case 9:return 30;
	case 10:return 31;
	case 11:return 30;
	case 12:return 31;
	default:return -1;
	}
}
int Date::daysPerYear(int y) const		// 计算每年多少天
{
	y = (y < 0) ? year : y;
	if (isLeapYear(y))	return 366;
	return 365;
}
int Date::compare(const Date& date) const	// 比较两个日期的大小，相等返回0
{
	if (year > date.year)	return 1;
	else if (year < date.year)	return -1;
	else
	{
		if (month > date.month)	return 1;
		else if (month < date.month)	return -1;
		else
		{
			if (day > date.day)	return 1;
			else if (day < date.day)	return -1;
			else return 0;
		}
	}	
}
bool Date::isLeapYear(int y) const		// 是否闰年
{
	y = (y < 0) ? year : y;
	if (0 == y % 400 || (0 == y % 4 && 0 != y % 100))	return true;
	return false;
}
int Date::subDate(const Date& date) const	// 减去一个日期，返回天数
{
	if (compare(date) > 0)
		return subSmallDate(date);
	else if (compare(date) < 0)
		return -(date.subSmallDate(*this));//this指针
	else return 0;
}
Date Date::addDays(int days) const			// 增加指定的天数？
{
	Date newDate(year,month,day);
	if (days>0)
	{	for (int i = 0;i < days;i++)	newDate.addOneDay();	}
	else if (days<0)
	{	for (int i = 0;i < (- days);i++)	newDate.subOneDay(); }
	return newDate;
}
Date Date::subDays(int days) const			// 减少指定的天数
{	return addDays(-days);	}

/******Date类的私有成员函数的类外定义******/
void Date::addOneDay()						// 增加一天
{
	if (++day > daysPerMonth()) { day = 1;month++; }
	if (month > 12) { month = 1;year++; }
}
void Date::subOneDay()						// 减少一天
{
	if (--day < 1)
	{
		if (--month < 1) { month = 12;year--; }
		day = daysPerMonth();
	}
}
int Date::subSmallDate(const Date& dat) const // 减去一个更小的date，返回天数
{
	int days = 0;
	Date date(dat);
	while (year>(date.year+1))	
	{
		days += date.daysPerYear();
		date.year++;
	}
	while (month > (date.month + 1))
	{
		days += date.daysPerMonth();
		date.month++;
	}
	while (day > (date.day + 1))
	{
		days++;
		date.day++;
	}
	while (compare(date)>0)
	{
		days++;
		date.addOneDay();
	}
	return days;
}
const char* IntToChar(int n)					// 将整数0-9抓换成字符串,我加的const
{
	switch (n)
	{
	case 0:return "0";
	case 1:return "1";
	case 2:return "2";
	case 3:return "3";
	case 4:return "4";
	case 5:return "5";
	case 6:return "6";
	case 7:return "7";
	case 8:return "8";
	case 9:return "9";
	}
}
char* IntToString(int n)				// 将整数n转换为字符串
{
	char* ptr = new char[20];
	if (n<10)
	{
		strcpy(ptr, IntToChar(n));	
		return ptr;
	}
	else
	{
		strcpy(ptr, IntToString(n / 10));	//递归?
		strcat(ptr, IntToChar(n % 10));
		return ptr;
	}
}
