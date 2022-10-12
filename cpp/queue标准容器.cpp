// 与栈一致
#include <iostream>
#include <queue>
#include <vector>
#include <deque>
#include <list>
using namespace std;

int main(){
    queue<int> s; // 底层容器是deque
    // stack<int,vector<int>> s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);
    s.push(6);
    while(!s.empty()){ // 栈容器不为空
        cout << s.front() << endl; // 取队列的首元素是front()函数
        s.pop(); // 读一个删一个
    }

    return 0;
}