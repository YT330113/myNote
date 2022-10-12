#include <iostream>
#include <set>
using namespace std;

int main(){
    // 新建多重集合容器
    multiset<int> s;    
    // 为集合容器添加节点
    s.insert(1);
    s.insert(10);
    s.insert(100);
    s.insert(1); // 由于多重集合允许重复，所以下面这几个节点可以加进去
    s.insert(10);
    s.insert(100);
    cout << "节点个数：" << s.size() << endl;
    typedef multiset<int>::iterator IT;
    for (IT it = s.begin(); it != s.end(); it++){
        cout << (*it) << ' ';
        cout << endl;
    }
}