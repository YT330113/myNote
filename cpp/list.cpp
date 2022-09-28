#include <iostream>
#include <stdexcept> //异常类，抛出一些异常错误
using namespace std;
template<class T>class list{    // 用类模板实现节点数据类型泛化
public:
    // 缺省构造
    list():m_head(NULL),m_tail(NULL){}
    // 拷贝构造
    list(list const that):m_head(NULL),m_tail(NULL){

    }
    // 析构函数
    ~list(){};
    // 链表判空
    bool empty(){
        return m_head == NULL && m_tail == NULL;
    }

    // 添加头结点
    void push_front(T const& data){
        m_head = new node(NULL, data, m_head);// 新建一个节点，前指针为空，\
                                        后节点指向之前的头节点
        // 让之前的头节点的前指针指向新建的节点
        // 如果有下一个节点那正常执行
        if (m_head->m_next)
            m_head->m_next->m_prev = m_head;
        // 如果没有下一个节点那就表示尾节点就是头节点
        else
            m_tail = m_head;
    }

    // 删除链表头结点
    void pop_front(){
        // 如果是空的直接返回
        if(empty())
            return;
        node *pnode = m_head->m_next;// 先备份下链表的第二个节点
        delete m_head;
        // 是否能确定头节点的下一个节点存在？得判断一下
        if (pnode)
            pnode->m_prev = NULL;
        // 如果头节点的下一个节点不存在，\
           那把头节点删了下一个节点就是空节点，那新头都是空那尾肯定也是空
        else
            m_tail = NULL;
        m_head = pnode;
    }

    // 获取头结点数据
    T& front(){    // 返回头结点数据的引用，好处：可以用它更改链表数据
        if(empty())
            // return 0;
            // 不能return0，虽然这里返回0是指出错，但万一要返回的数据就是0就说不清了
            // 抛出异常
            throw underflow_error("null node");
        return m_head->m_data;
    }
    // 有常属性的链表掉这个函数，因此不会修改，别的调用front函数只会调用上面的那个
    T const& front()const{// 第一个const表示常引用，第二个表示常函数
                          // 只有常对象才能调用常函数
        // 方法1 完全复制上面的
        if(empty())
            // return 0;
            // 不能return0，虽然这里返回0是指出错，但万一要返回的数据就是0就说不清了
            // 抛出异常
            throw underflow_error("null node");
        return m_head->m_data;
        // 方法2
        return const_cast<list *>(this)->front();
    }
    // 添加尾节点
    void push_back(T const& data){
        // 把新new的节点当做尾节点
        m_tail = new node(m_tail, data, NULL);
        // 新尾节点的前一个节点的后指针应该指向新的尾节点
        if (m_tail->m_prev)
            m_tail->m_prev->m_next = m_tail;
        else//new的这个节点的链表只有一个节点
            m_head = m_tail;
    }
    // 删除尾节点
    void pop_back(){

    }
    // 获取尾节点数据
    T& back(){

    }
    T const& back()const{

    }
    // 清空链表
    void clear(){

    }
    // 获取链表大小
    size_t size(){

    }

private:
// 节点类
    class node{
    public:
        node(node *prev, T const& data,node *next):m_prev(prev),m_data(data),m_next(next){}
        node *m_prev;// 前指针
        T m_data;// 节点数据
        node *m_next;// 后指针
    };
    node *m_head;// 头节点
    node *m_tail;// 尾节点
}
int main() {

    return 0;
}