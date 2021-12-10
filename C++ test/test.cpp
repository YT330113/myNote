#include <iostream>
using namespace std;
struct Date {
    int d, m, y;
    void init(int dd, int mm, int yy) {
        d = dd; m = mm; y = yy;
    }

    void print() {
        cout << y << "-" << m << "-" << d << endl;
    }
};

int main (){
    Date day; 
    day.print();          //通过类Date对象day调用类Date的print方法
    day.init(4, 6, 1999); //通过类Date对象day调用类Date的init方法
    day.print();          //通过类Date对象day调用类Date的print方法

    return 0;
}