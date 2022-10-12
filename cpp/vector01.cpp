#include<iostream>
#include<vector>
//#include<stdio>
using namespace  std;
// 不往容器里存基本类型的数据，自制一个类
class Student
{
private:
    string m_name;
public:
    Student(string const& name):m_name(name){
        cout << "缺省构造了：" << m_name << "(" << this << ")" << endl;
        // this是为了打印对象的地址
    }
    Student(Student const& that):m_name(that.m_name){
       cout << "用：" << that.m_name << "(" << &that << ")" 
             << "拷贝构造了：" << m_name << "(" << this << ")" << endl;
    }
    ~Student(){
        cout << "析构了：" << m_name << "(" << this << ")" << endl;
    }
};

int main(){
    vector<Student> vs;
    vs.reserve(10);// 预先设置向量容量节省开销
    // 往容器里压入一个学生
    vs.push_back(Student("张三"));// 匿名对象，生命周期语句级
                                  // 语句结束，该对象就被析构了
    vs.push_back(Student("李四"));
    vs.push_back(Student("王五"));
    // 容器里永远存的是对象的副本，所以会有一个原对象的副本出现
    // 只要出现了用副本复制副本那就是内存不够了，在从新迁移
    getchar();// 阻塞程序，不打回车程序不会结束；

    return 0;
}
