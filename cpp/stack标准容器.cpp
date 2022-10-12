#include <iostream>
#include <stack>
#include <vector>
#include <deque>
#include <list>
using namespace std;

int main(){
    stack<int> s; // 底层容器是deque
    // stack<int,vector<int>> s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);
    s.push(6);
    while(!s.empty()){ // 栈容器不为空
        cout << s.top() << endl;
        s.pop(); // 读一个删一个
    }

    return 0;
}