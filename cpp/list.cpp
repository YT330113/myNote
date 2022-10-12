#include <iostream>
#include <stdexcept> //异常类，抛出一些异常错误
using namespace std;
template<class T>class list{    // 用类模板实现节点数据类型泛化
public:
    // 缺省构造
    list():m_head(NULL),m_tail(NULL){}
    // 拷贝构造
    list(list const& that):m_head(NULL),m_tail(NULL){
        // 深拷贝
        // 遍历that链表的每一个节点
        for (node *pnode = that.m_head; pnode;pnode=pnode->m_next){
            push_back(pnode->m_data);// 把that链表的每个节点数据都压到要\
                                        新建的这个链表的末尾，这样就实现了拷贝
        }
    }
    // 析构函数
    ~list(){
        clear();
    };
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
        if(empty())
            return;
        node *pnode = m_tail->m_prev;// 备份倒数第二个节点
        delete m_tail;
        // 能不能肯定要删除的尾节点有前一个节点？
        if (pnode)
            pnode->m_next = NULL;// 如果有那删了
        else
            m_head = NULL;//如果没有那你还把尾节点删了，那链表就为空了，\
                            所以头节点应该是空的
        m_tail = pnode;
    }
    // 获取尾节点数据
    T& back(){
        if(empty())
            throw underflow_error("null node");
        return m_tail->m_data;
    }
    T const& back()const{
        // 把掉这个常函数的常对象的常属性去除掉，然后再掉上面的back()函数
        return const_cast<list *>(this)->back();
    }
    // 清空链表
    void clear(){
        // 链表不空进循环
        while (!empty())
        {
            pop_front();// 不断删除头节点
        }
        

    }
    // 获取链表大小
    size_t size(){
        size_t i = 0;// size_t 类型表示C中任何对象所能达到的最大长度，它是无符号整数。  
        for (node *pnode = m_head; pnode;pnode=pnode->m_next)
            ++i;
        return i;
    }
    // 
// 获取起始迭代器，遍历链表  // 这是定义在list<>容器里的，即是做容器 \
   的人实现的，用户只需要通过list类对象来掉就可以获得迭代器
// 


//private:
// 节点类
    class node{
    public:
        node(node *prev, T const& data,node *next):m_prev(prev),m_data(data),m_next(next){}
        node *m_prev;   // 前指针
        T m_data;       // 节点数据
        node *m_next;   // 后指针
    };
//
// 正向非常迭代类 // 他是list<>类的嵌套类  // node类也是list<>类的嵌套类
// 
    class iterator{
    public:
        // 构造
        iterator(node *start, node *cur, node *end) : m_start(start), m_cur(cur), m_end(end){}
        // 重载 * 运算符，来获取迭代器指向节点的数据
        T& operator*(){
            if(m_cur==NULL)
                throw underflow_error("null node");
            return m_cur->m_data;
        }
        // 重载 ++ 运算符，返回迭代器类型
        iterator& operator++(){
            if(m_cur==NULL)
                m_cur = m_start; // 如果m_cur指向了尾节点的后面，就让他重新指向头节点，实现循环迭代
            else
                m_cur = m_cur->m_next;// 把迭代器当前指向往后挪一个
            return *this;//返回调用这个函数的对象本身
        }
        iterator& operator--(){
            if(m_cur==NULL)
                m_cur = m_end; // 如果m_cur指向了头节点的前面，就让他重新指向尾节点，实现循环迭代
            else
                m_cur = m_cur->m_prev;// 把迭代器当前指向往qian挪一个
            return *this;//返回调用这个函数的对象本身
        }
        // 重载==,判断两个迭代器是否相等
        // ==是双目操作符，左操作数是调用的对象，右操作数是传进来的参数
        bool operator==(iterator const& that)const{
            return m_start == that.m_start && m_cur == that.m_cur && m_end == that.m_end;
        }
        // 重载!=
         bool operator!=(iterator const& that)const{
             return !(*this == that);// 又调用了==操作符
        }
    private:
        node *m_start;  // 开始指向
        node *m_cur;    // 当前指向
        node *m_end;    // 终止指向
         friend class list;//可以用list的函数访问迭代器类的三个私有成员了
    };

// 
// 获取起始迭代器，遍历链表  // 这是定义在list<>容器里的，即是做容器 \
   的人实现的，用户只需要通过list类对象来掉就可以获得迭代器
// 
    iterator begin(){
        return iterator(m_head, m_head, m_tail);//让迭代器的起始指向为链表头，\
                                        当前指向为链表头，终止指向为链表尾
    }// 用户只需要用链表对象掉一个begin函数就能返回一个起始迭代器
// 
// 获取终止迭代器，它就是个结束标志
// 
    iterator end(){
        return iterator(m_head, NULL, m_tail);//这个NULL表示尾节点的下一个位置，相当于无效节点
    }
// 
// 迭代器指向的位置添加节点
// 
    // 添加位置在指向节点之前，标准模板库是这样的
    void insert(iterator const& loc,T const& data){
        //loc迭代器等于终止迭代器说明loc迭代器指向的是尾节点的下一个位置,\
          相当于无效节点
        if(loc==end())
        // 那就给链表添一个尾节点
            push_back(data);
        else{
            // 新建一个节点，这个新节点的前指针指向迭代器当前指点的上一个节点 \
            新节点数据为传进来的data，新节点的后指针指向迭代器当前指向的节点
            node *pnode = new node(loc.m_cur->m_prev, data, loc.m_cur);
            // 此外还要让新节点前后节点的后指针和前指针都指向自己
            if (pnode->m_prev)// 不能保证新new的节点有前一个节点
                pnode->m_prev->m_next = pnode;
            else
                m_head = pnode;//如果新节点没有前节点，那新节点就应该是头节点
            // 能保证新new的节点有后一个节点吗？\
               可以，因为后一个节点就是迭代器当前指向的这个节点
            pnode->m_next->m_prev = pnode;
        }
    }
// 
// 删除迭代器指向位置的节点
//
    void erase(iterator const &loc) {
        // 删之前还要考虑删除节点前后节点的指向问题，否则直接删除链表就断了
        if(loc==end())//迭代器指向了尾节点的下一个位置，那就不用删了
            return;
        node *pdel = loc.m_cur;//先备份下要删除的节点
        // 能保证要删除的节点有前一个节点吗？
        if(pdel->m_prev)
            // 如果要删除的节点有前一个节点，那删除
            pdel->m_prev->m_next = pdel->m_next;
        else
            // 如果要删除的节点没有前节点那说明要删除头节点
            m_head = pdel->m_next;//那就让要删除节点的下一个节点为头节点
        // 能保证要删除的节点有下一个节点吗？
        if(pdel->m_next)
            pdel->m_next->m_prev = pdel->m_prev;
        else
            // 如果没有那就要删除节点的前一个节点作为新的尾节点
            m_tail = pdel->m_prev;
        delete pdel;
    }
// 
// 正向 常 迭代类  //还是定义在链表类list里
//
    class const_iterator{
    public:
        const_iterator(iterator const& it):m_it(it){}
        // 定义*运算符
        T const& operator*(){//const&是为了不能通过引用来改目标，把路堵上了
            return *m_it;
        }
        // 定义++运算符，实现遍历
        const_iterator& operator++(){
            ++m_it;
            return *this;
        }
        // 定义--运算符，实现遍历
        const_iterator& operator--(){
            --m_it;
            return *this;
        }
        // 定义==运算符
        bool operator==(const_iterator const& that)const{// 常对象才能掉常函数
            return m_it==that.m_it;
        }
        // 定义!=运算符
        bool operator!=(const_iterator const& that)const{// 常对象才能掉常函数
            return !(*this==that);
        }
    private:
        iterator m_it;//利用前面的功能实现新的功能
    };

//
// 获取起始常迭代器，以下函数定义在const_iterator类外面，是list<>类的成员
// 
    const_iterator begin()const{//和之前的begin函数是重载关系，只有常链表才能掉这个begin函数
        return iterator(m_head, m_head, m_tail);
    }
//
// 获取终止常迭代器
//
    const_iterator end()const{
        return iterator(m_head, NULL, m_tail);
    }
    node *m_head;// 链表头节点
    node *m_tail;// 链表尾节点
    // 有了迭代器就不用这个了友元了
    // friend ostream &operator<<(ostream &os, list<int> &l);//输出流操作函数\
            因为这个函数在类外使用了list类的私有成员node和m_data，所以声明为友元
};
// 
// 查找，不在list类里面，是全局函数，但仍是做容器的人干的；\
   STL也是把查找函数放在容器外面的；
// 
// 查找函数是个函数模板
// 调用参数a和b就是传进来的两个迭代器，用来卡范围的，
// 查找就是在a和b圈定的范围内找数据和data相等的节点
// 返回值也是个迭代器
template<class IT, class T>IT find(IT const& a, IT const& b, T const& data){
    // 比较查找，利用 == 实现
    for (IT it = a; it != b; ++it) { // 遍历a和b之间的节点，b不动a动
        if (*it == data)
            return it;
        // 如果for循环结束了还没找到
        }
        return b; 
        // 用户在main程序通过判断返回值是不是b来确定是否找到
    
}
// 
// 快速排序（利用<号排序）
// 
template<class IT>void sort(IT const& begin,IT const& end){//begin和end也是卡范围的
    IT p = begin;
    IT last = end;
    --last;// 这样last就指向尾节点了
    for (IT i = begin, j = last; i != j; ){
        while (i != p && *i < *p)
            ++i;
        if (i != p){
            swap(*i, *p);
            p = i;
        }
        while (j != p && *p < *j)
            --j;
        if (j != p){
            swap(*p, *j);
            p = j;
        }
    } // for循环结束说明已经有一个数字的位置确定了
    // 接下来要使用递归来对确定位置左右两侧的数字排序
    // 排之前要确定那个位置左侧和右侧是否至少有两个熟悉
    IT it = begin;
    ++it;
    if (p != begin && p != it)
        sort(begin, p);// 如果p前面有至少两个数，那对链表开始和p这段排序 \
                          注意p不参与排序，sort函数只排到p的前一个位置
    it = p;
    ++it;
    if (it != end && it != last)
        sort(it, end);// p后面至少有两个数字时递归
}
// 
// 快速排序（利用 比较器 排序）
// 
template<class IT,class CMP>// CMP接受一个比较类型的类型参数
void sort(IT const& begin,IT const& end,CMP cmp){//begin和end也是卡范围的
    IT p = begin;
    IT last = end;
    --last;// 这样last就指向尾节点了
    for (IT i = begin, j = last; i != j; ){
        while (i != p && cmp(*i,*p))//*i < *p)   // 对象跟括号触发括号操作符，不是调构造 \
                                                    括号操作符是用户在main中定义的
            ++i;
        if (i != p){
            swap(*i, *p);
            p = i;
        }
        while (j != p && cmp(*p,*i))//*p < *j)
            --j;
        if (j != p){
            swap(*p, *j);
            p = j;
        }
    } // for循环结束说明已经有一个数字的位置确定了
    // 接下来要使用递归来对确定位置左右两侧的数字排序
    // 排之前要确定那个位置左侧和右侧是否至少有两个熟悉
    IT it = begin;
    ++it;
    if (p != begin && p != it)
        sort(begin, p, cmp);// 如果p前面有至少两个数，那对链表开始和p这段排序 \
                          注意p不参与排序，sort函数只排到p的前一个位置
    it = p;
    ++it;
    if (it != end && it != last)
        sort(it, end, cmp);// p后面至少有两个数字时递归
}
// 以上代码模拟容器
// -----------------------------------
// 以下代码模拟普通用户

// 重载输出流操作符，这是用户层面重载的，不是容器提供的
// 有了迭代器就不用这个了
// ostream& operator<<(ostream& os,list<int>& l) {
//     for (list<int>::node *pnode = l.m_head; pnode; pnode = pnode->m_next){
//         os << pnode->m_data << ' ';
//     }
//     return os;
// }

// 定义一个打印链表内容的函数  // 全局函数
void print(string const &str, list<int> &l){
    cout << str << endl;
    typedef list<int>::iterator IT;//迭代器类是嵌套在list<>类下面的，用它定义对象很麻烦，这里简洁定义下
    for (IT it = l.begin(); /*获得一个起始迭代器*/ it != l.end(); ++it){
        cout << *it /*调用*函数取得迭代器的当前值*/ << ' ';
    }
    cout << endl << "---------------------------------" << endl;
}

//
// 比较类,这是用户自定义的类，要升序排列就return a < b;要降序就return a > b
//
class CMP{
public:
    bool operator()(int const &a, int const &b){
        // return a > b;     // 降序排列
        return a < b;  // 升序排列
    }
};
int main() {
    list<int> ls;
    // 在链表头压入5个节点
    for (int i = 0; i < 5; i++)
        ls.push_front(10 + i);
    // 在链表尾压入5个节点
    for (int i = 0; i < 5;i++)
        ls.push_back(100 + i);
    // 通过重载输出流操作符实现输出---一种对用户不友好的方法
    // cout << ls << endl;
    // 通过使用迭代器来遍历输出链表
    print("添加节点后： ", ls);
    // 删除一个头节点和一个尾节点
    ls.pop_front();
    ls.pop_back();
    // cout << ls << endl;
    print("删除头尾节点后： ", ls);

    // 模拟使用 迭代器 新建/删除节点
    //用迭代器实现增操作
    ls.insert(ls.begin() /*拿到起始迭代器，相当于在链表头插入数字*/, 1000);
    print("在迭代器指向的位置添加节点后： ", ls);
    //用迭代器实现删操作
    ls.erase(ls.begin());
    print("删除迭代器指向的节点后：", ls);
    // 用迭代器实现改操作
    typedef list<int>::iterator IT;
    IT it = ls.begin();//起始迭代器
    *it = 800;// *迭代器就是得到迭代器指向数据的引用，引用就可以来更改原始数据
    print("更改迭代器指向的节点后：", ls);
    // 用迭代器实现查操作 // 查属于读数据，前面三个是写数据

    // 测试查找功能
    IT fit = find(ls.begin(), ls.end(), 100);
    if(fit!=ls.end()){
        ls.erase(fit);// 如果找到了这个数那就删除了它
        print("找到100并删除后:", ls);
    }

    //测试排序功能(<号排序)
    // sort(ls.begin(), ls.end());

    //测试排序功能(比较器排序)
    // 先定义个比较累
    CMP cmp;//比较器
    sort(ls.begin(), ls.end(),cmp);
    print("排序后：", ls);

    // 模拟使用 常迭代器 功能
    // 常迭代器不常用
    const list<int> cls(ls);//const的变量在定义后就不让改了，因此这里要给常迭代器赋初值，用之前的非常迭代器ls拷贝构造一个常迭代器
    // 通过常迭代器遍历链表
    typedef list<int>::const_iterator CIT;
    for(CIT cit=cls.begin();cit!=cls.end();++cit){//通过++cit可以看出迭代器本身没有常属性，而是指迭代器指的数据没有常属性
        cout << *cit <<' ';
    }
    cout << endl << "----------------------------------" << endl;
    return 0;

}