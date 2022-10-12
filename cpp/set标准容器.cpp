#include <iostream>
#include <set>
using namespace std;

int main(){
    // 新建集合容器,集合只要值没有键，所以就一个类型参数
    set<int> s;    
    // 为集合容器添加节点
    s.insert(1);
    s.insert(10);
    s.insert(100);
    s.insert(1); // 由于集合天然排重，所以下面这几个节点肯定是加不进去的
    s.insert(10);
    s.insert(100);
    cout << "节点个数：" << s.size() << endl;
    typedef set<int>::iterator IT;
    for (IT it = s.begin(); it != s.end(); it++){
        cout << (*it) << ' ';
        cout << endl;
    }
}