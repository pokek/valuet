#include<iostream>
#include<vector>
#include<string>

using namespace std;

class Student{
public:
    string name;
    int age;

    Student(){}

    Student(string name, int age){
        this->name = name;
        this->age = age;
    }

    void add(int age, int amount);
};

void Student::add(int age, int amount){
    this->age = age + amount;
}

int main(){
    // Student* stu = new Student("xiaoming", 20);
    Student stu("xiaoming", 20);
    cout << stu.name << endl;
    cout << stu.age << endl;

    stu.add(stu.age, 30);
    cout << stu.age << endl;
    return 0;
}