#include<iostream>
#include<vector>
#include<algorithm> // find() sort()函数
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
        return m_age < that.m_age;
    }
};
ostream& operator<<(ostream& os,Student const& that){
    return os << that.m_name << ":" << that.m_age << endl;
}
void print(string const& str,vector<Student>& v){
    cout << str << endl;
    typedef vector<Student>::iterator IT;  // 迭代器是嵌套在容器里面的
    for (IT it = v.begin(); it != v.end();++it) // 起始迭代和终止迭代
        cout << *it << " "; // *it 得到一个学生对象，所以学生类必须支持<<操作符
    cout << endl << "------------------------------" << endl;
}

// 比较类
class CMP
{
private:
    /* data */
public:
    // 使得比较器支持()操作符
    bool operator()(Student const& a,Student const& b){
        return a < b;
    }
};


int main(){
    vector<Student> vs;
    vs.reserve(10);
    vs.push_back(Student("张飞", 22));
    vs.push_back(Student("赵云", 12));
    vs.push_back(Student("关羽", 52));
    vs.push_back(Student("马超", 82));
    vs.push_back(Student("黄忠", 32));
    // 利迭代器遍历输出向量vs里的内容
    print("添加节点后：", vs);

    // 利用迭代器插入节点
    vs.insert(vs.begin(), Student("刘备",56));//插入位置为起始迭代，说明换了个向量头
    print("在迭代器指向的位置添加节点后：", vs);
    
    // 利用迭代器删除节点
    vs.erase(vs.begin());
    print("在迭代器指向的位置删除节点后：", vs);

    // 改操作
    typedef vector<Student>::iterator IT;
    IT it = vs.begin();
    *it = Student("诸葛亮", 15);
    print("更改迭代器指向的位置的节点后：", vs);

    // 查操作
    IT fit = find(vs.begin(), vs.end(), Student("赵云", 12)); //find函数是个全局函数，\
    意义就在于可以让任何容器都能使用find函数，而不是某一个容器的函数
    // find在单独的头文件下
    // find()函数内部是通过==来判断的，这就意味着Student类还得支持==操作符
    if(fit!=vs.end())   // 如果没有查到会返回第二个迭代
        vs.erase(fit);
    print("找到赵云并删除后：", vs); 

    // 排序操作
    //sort(vs.begin(), vs.end()); // 内部用到了<比较操作符，所以还得重载
    // 比较器方式
    CMP cmp;
    sort(vs.begin(), vs. end(), cmp);// 比较器内部需要比较类对象即比较器支持()运算符
    print("排序后：", vs);
    return 0;
}
