#include <iostream>
#include <queue> // 优先队列也是这个头文件
#include <vector>
#include <deque>
//#include <list>
using namespace std;
class CMP{
public:
    bool operator()(int const &a, int const &b){
        return a > b; // 降序排列
    }
};
int main()
{
    //priority_queue<int> pq;  // 压入一个数字就排下序
    // 小者先出
    priority_queue<int,deque<int>,CMP> pq;
    pq.push(3);
    pq.push(8);
    pq.push(4);
    pq.push(9);
    pq.push(5);
    pq.push(7);
    while (!pq.empty())
    {
        cout << pq.top() << endl; // 读首元素
        pq.pop();// 删首元素
    }
    return 0;
}