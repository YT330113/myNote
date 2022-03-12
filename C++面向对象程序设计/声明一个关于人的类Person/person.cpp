#include<iostream>
using namespace std;
class Person
{
private:
    /* data */
    char name[20];
    char sex;
    int age;
public:
    void SetInfo()
    {
        cout << "Please enter name,sex,age:\n";
        cin >> name >> sex >> age;
    }
    void show()
    {
        cout << "name:" << name << " ";
        cout << "sex:" << sex << " ";
        cout << "age:" << age << endl;
    }
};
int main()
{
    Person person1, person2;
    person1.SetInfo();
    person2.SetInfo();
    person1.show();
    person2.show();
    return 0;
}


