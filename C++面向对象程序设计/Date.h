#ifndef DATE_H
#define DATE_H

class Date
{
public:
	Date();									// 默认构造函数
	Date(char strDate[]);					// 转换构造函数？
	Date(int Y,int M,int D);				// 带有三个参数的普通构造函数
	void setDate(int Y, int M, int D);		// 设置年、月、日的成员函数
	void show()const;						// 显示日期的成员函数
	int GetYear();							// 单独获取年的成员函数
	void SetYear(int Y);					// 单独设置年的成员函数
	int GetMonth();							// 单独获取月的成员函数
	void SetMonth(int M);					// 单独设置月的成员函数
	int GetDay();							// 单独获取日的成员函数
	void SetDay(int D);						// 单独设置日的成员函数
	char * toString();						// 把日期转换为字符串的函数
	int daysPerMonth(int m = -1) const;		// 计算每月多少天
	int daysPerYear(int y = -1) const;		// 计算每年多少天
	int compare(const Date &date) const;	// 比较两个日期的大小，相等返回0
	bool isLeapYear(int y = -1) const;		// 是否闰年
	int subDate(const Date &date) const;	// 减去一个日期，返回天数
	Date subDays(int days) const;			// 减少指定的天数？
	Date addDays(int days) const;			// 增加指定的天数

private:
	int year, month, day;					// 代表年月日的私有数据成员
	void addOneDay();						// 增加一天
	void subOneDay();						// 减少一天
	int subSmallDate(const Date& dat) const;// 减去一个更小的date，返回天数
};

#endif 
