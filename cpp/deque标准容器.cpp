#include<iostream>
#include<deque>
#include<algorithm>
using namespace std;
class Student
{
private:
    string m_name;
    int m_age;
    friend ostream &operator<<(ostream &os, Student const &that);

public:
    Student(string const& name="",int age=0):m_name(name),m_age(age){}
    bool operator==(Student const& that)const{
        return m_name == that.m_name && m_age == that.m_age;
    }
    bool operator<(Student const& that)const{
        return m_age < that.m_age; // <是升序排列，>就是降序排列了
    }
};
// 在全局域中定义学生类<<重载函数
ostream& operator<<(ostream& os,Student const& that){
    return os << that.m_name << ":" << that.m_age;
}
void print(string const& str,deque<Student>& d){
    cout << str << endl;
    typedef deque<Student>::iterator IT;
    for (IT it = d.begin(); it != d.end();++it){
        cout << *it << " ";
    }
    cout << endl
         << "-----------------------" << endl;
}

int main(){
    deque<Student> di;
    // 模拟添加节点
    di.push_front(Student("张飞", 22)); // 向量是不支持在头部添加节点的，双端队列可以
    di.push_front(Student("赵云", 42));
    di.push_front(Student("马超", 29));
    di.push_back(Student("关羽", 58));
    di.push_back(Student("黄忠", 31));
    print("添加节点后：", di);
    // 模拟增删改查排序操作
    typedef deque<Student>::iterator IT;
    di.insert(di.begin(), Student("刘备", 50)); // insert()函数是封装在双端队列这个类里面的
                                                // 插入位置是节点头，插入一个Student对象
    print("在迭代器指向位置添加节点后：", di);
    di.erase(di.begin());
    print("删除迭代器指向的节点后：", di);

    IT it = di.begin();//定义一个迭代器指向双端队列容器的头结点，作起始迭代
    *it = Student("吕布", 36);
    print("更改迭代器指向的节点后：", di);

    // find()查找成功后返回一个迭代器，就是查找到那个节点的迭代器；查找失败返回第二个参数
    // find函数是通用函数，他的前两个参数说明了对哪个容器的哪个范围进行查号
    // find()内部是通过==判断的，因此学生类要支持==运算符
    IT fit = find(di.begin(), di.end(), Student("黄忠", 31)); 
    if(fit!=di.end())
        di.erase(fit);
    print("找到黄忠并删除后：", di);

    // 这是小于号版本的sort(),不是比较器版本的sort();
    sort(di.begin(), di.end()); // 排序需要支持<号操作符
    print("排序后：", di);
    return 0;
}