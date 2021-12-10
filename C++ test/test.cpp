#define _CRT_SECURE_NO_WARNINGS      //windows系统,可防止报错
#include <iostream>
#include <cstring>

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

  virtual ~student(){         // 析构函数
    delete name;              // 不能用free!
    cout << "析构函数，释放了100个char元素的动态空间" << endl;
  }
};

int main() {
  cout << "Hello!" << endl << endl;
  student a;
  cout << a.name << ", age " << a.age << endl << endl;
  student b("John");
  cout << b.name << ", age " << b.age << endl << endl;

  b.age = 21;
  cout << b.name << ", age " << b.age << endl << endl;
  student c("Miki", 45);
  cout << c.name << ", age " << c.age << endl << endl;
  cout << "Bye!" << endl << endl;

  return 0;
}