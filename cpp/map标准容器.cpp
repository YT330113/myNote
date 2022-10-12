#include <iostream>
#include <map>
//#include <list>
using namespace std;
// 候选人类
class Candidate{
public:
    Candidate(string name=""):m_name(name),m_vote(0){}
    string m_name;
    int m_vote;
};
void print(map<char,Candidate>& m){
    // 还是用迭代器遍历
    typedef map<char, Candidate>::iterator IT;
    for (IT it = m.begin(); it != m.end(); it++)
        cout << "(" << (*it).first << ")" << (*it).second.m_name << " ";
    cout << endl;
}
int main(){
    map<char, Candidate> m;//m就代表一个映射容器，m的每一个节点存的都是一个候选人对象
    // 上句的意思就是每一个候选人对应一个字母，a代表张三，b代表李四
    // 以下是三种在映射容器中添加节点的方法，第三种最简单
    m.insert(pair<char, Candidate>('A', Candidate("张飞")));
    m.insert(make_pair('B', Candidate("关羽")));
    m['C'] = Candidate("赵云");
    m['D'] = Candidate("马超");
    m['E'] = Candidate("黄忠");
    // 模拟选民,十个选民
    typedef map<char, Candidate>::iterator IT;
    for (int i = 0; i < 10;i++){
        print(m);
        char ch;
        cin >> ch;
        IT fit = m.find(ch);
        if(fit==m.end()){// 如果没找到返回终止迭代
            cout << "废票！" << endl;
            continue; //进入下一次循环
        }
        ++(*fit).second.m_vote;  // *fit拿到pair对象（键值对），(*fit).second拿到键值对的值\
                                    即候选人对象，(*fit).second.m_vote拿到候选人对象的票数
    }
    // 唱票：打印每个人多少票
    for (IT it = m.begin(); it != m.end(); ++it){
        cout << (*it).second.m_name << ": " << (*it).second.m_vote << endl;
    }
        return 0;
}