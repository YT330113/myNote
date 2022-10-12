#include<iostream>
#include<list>
//#include<algorithm>
using namespace std;
class CMP  // 定义比较类，只需要实现()小括号运算符
{
public:
    bool operator()(int const &a, int const &b){
        return a > b;//降序
    }
};

void print(string const& str,list<int>& l){//如果这里写成list<int>const&,那就得用常迭代器
    cout << str << endl;
    // 利用迭代器遍历链表的每一个节点
    typedef list<int>::iterator IT; 
    for(IT it =l.begin();it!=l.end();++it)
        cout << *it << " ";
    cout << endl
         << "----------------"<< endl;
}
int main(){
    list<int> ls;
    for (int i = 0; i < 5;i++)
        ls.push_front(10 + i);// 在链表头添加5个节点
    for (int i = 0; i < 5;i++)
        ls.push_back(10 - i);
    print("添加节点后：", ls);

    // 唯一化：
    ls.unique();
    print("唯一化之后：", ls);

    // 排序，成员函数sort()
    ls.sort(); // <号，只能升序排列
    print("排序后：", ls);
    // 比较器排序
    CMP cmp;//比较器
    ls.sort(cmp);// 只要用比较器就要使用小括号运算符
    print("比较器降序排序后：", ls);

    // 拆分：
    list<int> lst;
    lst.push_back(1000);
    lst.push_back(2000);
    lst.push_back(3000);
    lst.push_back(4000);
    // 剪全部
    // 把lst列表的内容剪切到列表ls的ls.begin()迭代器的位置
    // ls.splice(ls.begin(), lst);
    // print("调用列表ls:", ls);
    // print("参数列表lst:", lst); // liat剪切后空了
    // 剪1个
    // 把lst列表的lst.begin()迭代器指向位置的内容剪切到列表ls的ls.begin()迭代器的位置
    // ls.splice(ls.begin(), lst, lst.begin());
    // print("调用列表ls:", ls);
    // print("参数列表lst:", lst);
    // 剪一部分
    // 把lst列表++lst.begin()和--lst.end()两个迭代器之间的节点剪切到ls列表
    ls.splice(ls.begin(), lst, ++lst.begin(),--lst.end());
    print("调用列表ls:", ls);
    print("参数列表lst:", lst);
    return 0;
}

