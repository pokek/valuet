---
id: y3riuz15bl7j8354zs61mdu
title: Blackhorse
desc: ''
updated: 1666793652315
created: 1665755934762
---
## CPlusPlus基础

### cplusplus对c语言的增强

```cpp {.line-numbers, highlight=[60, 71, 98]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//1、全局变量检测增强
//int a;
int a = 10;

//2、函数检测增强 ,参数类型增强,返回值检测增强,函数调用参数检测增强
int getRectS(int w, int h)
{
 return w*h;
}
void test02()
{
 getRectS(10, 10);
}


//3、类型转换检测增强
void test03()
{
 char * p = (char*)malloc(sizeof(64)); //malloc返回值是void*
}


//4、struct 增强
struct Person
{
 int m_Age;
 void plusAge(){ m_Age++; }; //c++中struct可以加函数
};
void test04()
{
 Person p1; //使用时候可以不加struct关键字
 p1.m_Age = 10;
 p1.plusAge();
 cout << p1.m_Age << endl;
}

//5、 bool类型增强 C语言中没有bool类型
bool flag = true; //只有真或假 true代表 真（非0）  false 代表假（0）
void test05()
{
 cout << sizeof(bool) << endl;

 flag = 100;
 //bool类型 非0的值 转为 1  ，0就转为0
 cout << flag << endl;
}

//6、三目运算符增强
void test06()
{
 int a = 10;
 int b = 20;

 cout << "ret = " << (a < b ? a : b) << endl;
 
 (a < b ? a : b) = 100; //b = 100 C++中返回的是引用，c中返回的是值，c语言中可以这样达到改效果 *(a > b ? &a : &b) = 200;
  
 cout << "a = " << a << endl;
 cout << "b = " << b << endl;
}


const int m_A = 10; //收到保护，不可以改
void test07()
{

 const int m_B = 20; //真正常量，c语言中局部const是伪常量可以通过指针修改，c++中通过符号表存储常量，编译器不分配空间，编译器是产生的一个临时变量存储该值
 //m_B = 100;

 int * p = (int *)&m_B;
 *p = 200;
 cout << "*p = " << *p << endl;
 cout << "m_B = " << m_B << endl;

 int arr[m_B]; //可以初始化数组


}


int main(){

 //test04();

 // test05();

 // test06();
 test07();

 system("pause");
 return EXIT_SUCCESS;
}

// c语言全局const默认外链，c++语言全局const默认是内部链接（extern const int a = 100，则可以设置外链，extern提高作用域）
```

![](/assets/images/2022-10-14-22-53-21.png)

### const分配内存的情况

```cpp {.line-numbers, highlight=[6, 7, 11, 15, 19, 28]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <string>
using namespace std;

//1、const分配内存 取地址会分配临时内存
//2、extern 编译器也会给const变量分配内存
void test01()
{
 const int m_A = 10;
 int * p = (int*)&m_A; //会分配临时内存

}

//3、 用普通变量初始化 const 的变量
void test02()
{
 int a = 10;
 const int b = a; //会分配内存

 int * p = (int *) &b;
 *p = 1000;

 cout << "b = " << b << endl;

}

//4、 自定义数据类型  加const也会分配内存，分配内存的都可用指针进行修改
struct Person
{
 string m_Name; //姓名
 int m_Age;
};
void test03()
{
 const Person p1;
 //p1.m_Name = "aaa";

 Person * p = (Person*)&p1;
 p->m_Name = "德玛西亚";
 (*p).m_Age = 18;

 cout << "姓名： " << p1.m_Name << " 年龄： " << p1.m_Age << endl;

}

int main(){

 //test02();
 test03();

 system("pause");
 return EXIT_SUCCESS;
}
```

### 引用的基本语法

```cpp {.line-numbers, highlight=[37, 44]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//1、引用基本语法  Type &别名 = 原名
void test01()
{
 int a = 10;
 int &b = a;

 b = 20;

 cout << "a = " << a << endl;
 cout << "b = " << b << endl;
}
//2、引用必须初始化
void test02()
{
 //int &a; 必须初始化
 int a = 10;
 int &b = a; //引用初始化后不可以修改了
 int c = 20;

 b = c; //赋值！！！
}

//3、对数组建立引用
void test03()
{
 int arr[10];
 for (int i = 0; i < 10;i++)
 {
  arr[i] = i;
 }

 //给数组起别名
 int(&pArr)[10] = arr;      // array of pointer int *p[10]  pointer to array int (*p) [10]  引用本质为 int* const b
 for (int i = 0; i < 10;i++)
 {
  cout << pArr[i] << " ";
 }
 cout << endl;

 //第二种方式 起别名

 typedef int(ARRAYREF)[10]; //一个具有10个元素的int类型的数组
 ARRAYREF & pArr2 = arr;

 for (int i = 0; i < 10; i++)
 {
  cout << pArr2[i] << " ";
 }
 cout << endl;

}


int main(){

 //test01();

 test03();

 system("pause");
 return EXIT_SUCCESS;
}
```

### 引用的注意事项

```cpp {.line-numbers, highlight=[61, 93]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

void mySwap(int a, int b)
{
 int tmp = a;
 a = b;
 b = tmp;

 cout << "mySwap::a = " << a << endl;
 cout << "mySwap::b = " << b << endl;
}

void test01()
{
 int a = 10;
 int b = 20;
 mySwap(a, b); //值传递

 cout << "a = " << a << endl;
 cout << "b = " << b << endl;
}


//地址传递
void mySwap2(int * a, int * b)
{
 int tmp = *a;
 *a = *b;
 *b = tmp;
}
void test02()
{
 int a = 10;
 int b = 20;
 mySwap2(&a, &b); 

 cout << "a = " << a << endl;
 cout << "b = " << b << endl;
}

//引用传递 类似传地址
void mySwap3(int &a, int &b)  //&a = a &b = b
{
 int tmp = a;
 a = b;
 b = tmp;
}

void test03()
{
 int a = 10;
 int b = 20;
 mySwap3(a, b); 

 cout << "a = " << a << endl;
 cout << "b = " << b << endl;
}

//引用的注意事项
//1、 引用必须引一块合法的内存空间
//2、不要返回局部变量的引用

int& doWork()
{
 int a = 10;
 return a;
}

void test04()
{
 //int &a = 10; // 引用必须引一块合法的内存空间
 int &ret = doWork();
 cout << "ret = " << ret << endl; //第一次10是编译器做了优化
 cout << "ret = " << ret << endl;
 cout << "ret = " << ret << endl;
 cout << "ret = " << ret << endl;
 cout << "ret = " << ret << endl;
}


int& doWork2()
{
 static int a = 10;
 return a;
}
void test05()
{
 
 int &ret = doWork2();
 
 //如果函数的返回值是引用，那么这个函数调用可以作为左值

 doWork2() = 1000; //相当于写了 a = 1000;

}

int main(){

 //test01();

 //test02();

 //test03();

 //test04();

 test05();

 system("pause");
 return EXIT_SUCCESS;
}
```

### 引用的本质

```cpp {.line-numbers, highlight=[1, 7, 8]}
//发现是引用，转换为 int* const ref = &a; 传参是一种初始化
void testFunc(int& ref){
 ref = 100; // ref是引用，转换为*ref = 100
}
int main(){
 int a = 10;
 int& aRef = a; //自动转换为 int* const aRef = &a;这也能说明引用为什么必须初始化
 aRef = 20; //内部发现aRef是引用，自动帮我们转换为: *aRef = 20;
 cout << "a:" << a << endl;
 cout << "aRef:" << aRef << endl;
 testFunc(a);
 return EXIT_SUCCESS;
}
```

### 指针的引用

```cpp {.line-numbers, highlight=[25]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

struct Person
{
 int m_Age;
};

void allocatMemory(Person ** p) // **p 具体的Person对象  *p 对象的指针   p 指针的指针
{
 *p = (Person *)malloc(sizeof(Person));

 (*p)->m_Age = 100;
}

void test01()
{
 Person * p = NULL;
 allocatMemory(&p);
 cout <<  "p的年龄： " <<p->m_Age << endl;
}


//利用指针引用开辟空间
void allocatMemoryByRef(Person* &p)
{
 p = (Person*)malloc(sizeof(Person));
 p->m_Age = 1000;
}

void test02()
{
 Person * p = NULL;
 allocatMemoryByRef(p);
 cout << "p的年龄：" << p->m_Age << endl;
}


int main(){

 //test01();

 test02();

 system("pause");
 return EXIT_SUCCESS;
}
```

### 常量引用

```cpp {.line-numbers, highlight=[8, 22]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

void test01()
{
 //int &ref = 10;//引用了不合法的内存，不可以
 const int &ref = 10; //加入const后 ，编译器处理方式为： int tmp = 10; const int &ref = tmp;，分配了内存，可用指针修改

 //ref = 10;

 int * p = (int*)&ref;
 *p = 1000;

 cout << "ref = " << ref << endl;

}

//常量引用使用场景 用来修饰形参
void showValue(const int &val)
{
 //val += 1000; //如果只是想显示内容，而不修改内容，那么就用const修饰这个形参，但也可以用指针修改
 cout << "val = " << val << endl;
}

void test02()
{
 int a = 10;
 showValue(a);
}


int main(){

 test01();

 system("pause");
 return EXIT_SUCCESS;
}
```

### 作业-设计圆类

```cpp
#include <iostream>

double const pa_pi = 3.14;

class Circle {
 private:
  int r;

 public:
  Circle();
  explicit Circle(int _r);
  void set_r(int _r);
  int get_r() const;
  double calculat_girth() const;
};

Circle::Circle() : r(0) {}
Circle::Circle(int _r) : r(_r) {}
void Circle::set_r(int _r) {
  r = _r;
}
int Circle::get_r() const {
  return r;
}
double Circle::calculat_girth() const {
  return 2 * pa_pi * r;
}

int main() {
  const Circle cir_one;
  std::cout << cir_one.calculat_girth() << std::endl;
  const Circle cir_two(20);
  std::cout << cir_two.calculat_girth() << std::endl;
}

```

### 作业-设计学生类

```cpp
#include <iostream>

class Student {
 private:
  std::string name;
  int id;

 public:
  explicit Student(std::string const& _name = "error", int _id = 0);
  void set_name(std::string const& _name);
  std::string get_name() const;
  void set_id(int _id);
  int get_id() const;
};

Student::Student(std::string const& _name, int _id) : name(_name), id(_id) {}
void Student::set_name(std::string const& _name) {
  name = _name;
}
std::string Student::get_name() const {
  return name;
}
void Student::set_id(int _id) {
  id = _id;
}
int Student::get_id() const {
  return id;
}

int main() {
  const Student stu_one;
  std::cout << stu_one.get_name() << "...." << stu_one.get_id() << std::endl;
  Student stu_two("xiaoming", 20);
  std::cout << stu_two.get_name() << std::endl;
  stu_two.set_name("xiaozhang");
  std::cout << stu_two.get_name() << std::endl;
}
```

### 宏函数缺陷和内联函数

```cpp {.line-numbers, highlight=[35, 43]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>

using namespace std;

//定义一个加法
#define  MyAdd(x,y) ((x)+(y))

void test01()
{
 int ret = MyAdd(10, 20) *20; //预期结果 600 ((10)+(20))*20

 cout << "ret = " << ret << endl;
}


#define MyCompare(a,b)  ((a) < (b)) ? (a) :(b)

inline void mycompare(int a, int b)
{
 int ret = a < b ? a : b;
 cout << "ret :::::  " << ret << endl;
}

//1 内联函数注意事项
// 类内部的成员函数 默认前面会加inline关键字
inline void func(); //内联函数声明
inline void func() { }; //如果函数实现时候，没有加inline关键字 ，那么这个函数依然不算内联函数

void test02()
{
 int a = 10;
 int b = 20;

 //int ret =  MyCompare(++a, b); // 预期结果 11    ((++a) < (b)) ? (++a):(b)

 //cout << "ret = " << ret << endl;

 mycompare(++a, b);

}

//3 宏函数也没有作用域，也没有类型


int main(){

 //test01();

 test02();

 system("pause");
 return EXIT_SUCCESS;
}
```

### 函数默认参数与占位参数

```cpp {.line-numbers, highlight=[29]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//函数的默认参数 参数后面 = ...
//函数参数注意事项，如果有一个位置有了默认参数，那么从这个位置开始，从左往后都必须有默认参数
// 传入参数 ，如果有参数，就用传入的参数，没有参数就用默认值

//如果函数声明里面有了 默认参数，那么函数实现时候必须没有
// 函数声明和实现里 只能有一个里有默认参数，不要同时都出现默认参数
void myFunc(int a = 10, int b = 10);
void myFunc(int a , int b ){}

void func( int a , int b = 10,int c = 1 )
{
 cout << "a + b + c = " << a + b + c << endl;
}

void test01()
{
 //func();

 func(1,2);

}


//函数 占位参数
//如果有了占位参数，函数调用时候必须要提供这个参数 ,但是用不到参数
//占位参数 没有什么大用途，只有后面重载 ++符号才有一点点用
//占位参数 可以有默认值
void func2(int a , int = 1)
{

}


void test02()
{
 func2(10);

}

int main(){

 test01();

 system("pause");
 return EXIT_SUCCESS;
}
```

### 函数重载

```cpp {.line-numbers, highlight=[66, 71]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;


//函数重载  
// C++中 函数名称可以重复
// 必须在同一个作用域,函数名称相同  
// 函数的参数 个数不同 或者 类型不同  或者 顺序不同
void func()
{
 cout << "无参数的func" << endl;
}

void func(int a )
{
 cout << "有参数的func(int a)" << endl;
}

void func(double  a)
{
 cout << "有参数的func(double a)" << endl;
}

void func(double  a , int b)
{
 cout << "有参数的func(double a ,int b)" << endl;
}

void func(int a, double b)
{
 cout << "有参数的func(int a ,double b)" << endl;
}

//返回值可以作为函数重载的条件吗？？？   不可以  因为产生二义性
//int func(int a, double b)
//{
// cout << "有参数的func(int a ,double b)" << endl;
// return 1;
//}

void test01()
{
 //func(1.1,3);
 func(1, 3.14);
}


//当函数重载 碰到了 默认参数时候，要注意避免二义性问题
void func2(int a,int b = 10)
{

}
void func2(int a)
{

}

void test02()
{
 //func2(10);

}

//引用的重载版本
void func3(int &a) //引用必须要引合法的内存空间
{
 cout << " int &a" << endl;
}

void func3(const int &a)  //const也是可以作为重载的条件  int tmp = 10; const int &a = tmp;
{
 cout << "const int &a" << endl;
}

void test03()
{
 //int a = 10;
 func3(10);
}




int main(){
 //test01();

 //test03();


 system("pause");
 return EXIT_SUCCESS;
}
```

### extern "c"作用

```cpp {.line-numbers, highlight=[12, 40]}
// test.c
#include "test.h"

void show()
{
 printf("hello world \n");
}

// test.h
#pragma  once

#ifdef __cplusplus //两个_下划线
extern "C" {
#endif // !__cplusplus



#include <stdio.h>

 void show();

 



#ifdef __cplusplus //两个_下划线
}
# endif // !__cplusplus

// test.cpp
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include "test.h"


//C++中想调用C语言方法

//extern "C" void show(); //show方法 按照C语言方式做连接
//解决的问题就是 在C++中调用C语言的函数

int main(){

 show(); //在C++中 函数是可以发生重载的，编译器会把这个函数名称偷偷改变  _showv  void

 system("pause");
 return EXIT_SUCCESS;
}
```

### c语言封装和c++语言封装

```cpp {.line-numbers, highlight=[15, 54]}
// test.c
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Person
{
 char mName[64];

 int mAge;

};

void PersonEat(struct Person *p) // 行为定义在外部
{
 printf("%s 在吃人饭 \n",p->mName);
}

void test01()
{
 struct Person p1;
 strcpy(p1.mName, "德玛西亚");

 PersonEat(&p1);
}


struct Dog
{
 char mName[64];

 int mAge;
};

void DogEat(struct Dog * dog)
{
 printf("%s 在吃狗粮 \n", dog->mName);
}

void test02()
{
 struct Dog d;
 strcpy(d.mName, "旺财");

 DogEat(&d);

 struct Person p1;
 strcpy(p1.mName, "老王");

 DogEat(&p1);

}
//C语言封装 属性和行为分开处理了 ,类型检测不够


int main(){
 //test01();

 test02();
 system("pause");
 return EXIT_SUCCESS;
}

// test.cpp
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

struct Person
{
 char mName[64];

 int mAge;

 void PersonEat()
 {
  cout <<  mName <<"吃人饭" << endl;
 }

};

struct Dog
{
 char mName[64];

 int mAge;

 void DogEat()
 {
  cout << mName << "吃狗粮" << endl;
 }

};

//C++中的封装 严格类型转换检测， 让属性和行为 绑定到一起
// 1 属性和行为作为一个整体来表示生活中的事物
// 2 控制权限 public 公有权限   protected 保护权限  private 私有权限
void test01()
{
 Person p1;
 strcpy(p1.mName, "老王");
 p1.PersonEat();
 //p1.DogEat();
}



//struct 和class是一个意思，唯一的不同  默认权限 ，struct是public，但是class默认权限是private
class Animal
{
private:
 //如果我不声明权限，默认的权限是 private
 void eat(){ mAge = 100; };

 int mAge;

public:
 int mHeight;

protected: //保护权限 类内部可以访问 ，(当前类的子类可以访问) , 类外部不可以访问

 int mWeight;

 void setWeight(){ mWeight = 100; };
};

//所谓私有权限 就是私有成员(属性、函数) 在类内部可以访问，类外部不可以方法
//公共权限 ，在类内部和类外部都可以访问
void test02()
{
 Animal an;
 //an.eat();
 //an.mAge; //私有不可以访问到

 an.mHeight = 100; //公有权限在类外部可以访问到
 //an.mWeight = 100; //保护权限 在类外不可访问到
}

// public  类内 类外 都可以访问
// protected 类内可以访问 类外 不可以访问 （子类可以方法）
// private   类内可以访问 类外 不可以访问  （子类不可以方法）


int main(){
 test01();


 system("pause");
 return EXIT_SUCCESS;
}
```

### 设计立方体类

```cpp
#include <iostream>
#include <ostream>

class Cube {
 private:
  int len;
  int height;
  int width;

 public:
  Cube();
  Cube(int _len, int _height, int _width);
  int cal_area() const;
  int cal_volume() const;
  bool is_equal(Cube const& src) const;
};

Cube::Cube() : len(0), height(0), width(0) {}
Cube::Cube(int _len, int _height, int _width) : len(_len), height(_height), width(_width) {}
int Cube::cal_area() const {
  return 2 * len * width + 2 * len * height + 2 * width * height;
}
int Cube::cal_volume() const {
  return len * height * width;
}
bool Cube::is_equal(Cube const& src) const {
  return this->cal_area() == src.cal_area() && this->cal_volume() == src.cal_volume();
}

bool cube_is_equal(Cube const& c_one, Cube const& c_two) {
  return c_one.cal_area() == c_two.cal_area() && c_one.cal_volume() == c_two.cal_volume();
}

int main() {
  Cube const c_one(20, 30, 40);
  Cube const c_two(10, 20, 30);
  std::cout << c_one.cal_area() << std::endl;
  std::cout << c_two.cal_area() << std::endl;
  std::cout << c_one.is_equal(c_two) << std::endl;
  std::cout << cube_is_equal(c_one, c_two) << std::endl;
}
```

### 设计圆类与点类并且计算圆与点的关系

```cpp
#include <cmath>
#include <iostream>

class Point {
 private:
  int x_;
  int y_;

 public:
  Point() : x_(0), y_(0) {}
  Point(int x, int y) : x_(x), y_(y) {}
  int Distance(Point const& point) const;
};
int Point::Distance(Point const& point) const {
  return pow(this->x_ - point.x_, 2) + pow(this->y_ - point.y_, 2);
}

class Circle {
 private:
  int r_;
  Point point_;

 public:
  Circle() : r_(0) {}
  Circle(int r, Point const& point) : r_(r), point_(point) {}
  void RelationCircleAndPoint(Point const& point) const;
};
void Circle::RelationCircleAndPoint(Point const& point) const {
  int const distance = this->point_.Distance(point);
  int const r_pow    = pow(r_, 2);
  if (r_pow < distance) {
    std::cout << "the point is outside the circle" << std::endl;
  } else if (r_pow == distance) {
    std::cout << "the point is on the circle" << std::endl;
  } else {
    std::cout << "the point is inside the circle" << std::endl;
  }
}

int main() {
  Point const center(10, 0);
  Circle const circle(10, center);
  Point const point(10, 9);
  circle.RelationCircleAndPoint(point);
}
```

### 构造函数分类与使用

```cpp {.line-numbers, highlight=[39, 41-50, 52, 54]}

#include <iostream>
using namespace std;

//分类
//按照参数进行分类  无参构造函数（默认构造函数）   有参构造函数
//按照类型进行分类  普通构造函数  拷贝构造函数
class Person {
 public:    //构造和析构必须写在public下才可以调用到
  Person()  //默认 、 无参构造函数
  {
    cout << "默认构造函数调用" << endl;
  }

  Person(int a) {
    cout << "有参构造函数调用" << endl;
  }

  //拷贝构造函数
  Person(Person const& p) {
    m_Age = p.m_Age;
    cout << "拷贝构造函数调用" << endl;
  }

  ~Person() {
    cout << "析构函数调用" << endl;
  }

  int m_Age;
};

void test01() {
  //构造函数调用方式
  //括号法调用
  // Person p1(1);  //有参
  //p1.m_Age = 10;
  // Person p2(p1);  //拷贝
  //cout << "p2的年龄" << p2.m_Age << endl;

  Person p3;  //默认构造函数 不要加()   Person p3(); //编译器认为这行是函数的声明

  //显示法调用
  Person p4 = Person(100);
  Person p5 = Person(p4);

  //Person(100); //叫匿名对象 ,匿名对象特点，如果编译器发现了对象是匿名的，那么在这行代码结束后就释放这个对象
  // 上面两行相当于给匿名对象起名字

  //不能用拷贝构造函数 初始化匿名对象
  Person(p5); // Redefinition of 'p5' 个人理解：此时没有有名字的this指针，因此p5看作是this，所以左值相当于Person p5，调用默认构造
  //Person p6 = Person(p5); //如果写成左值，编译器认为你写成 Person p5; 对象的声明，如果写成右值，那么可以

  Person p7 = 100;  //相当于调用了 Person p7 = Person(100) ，隐式类型转换
  // Person p8 = p7;   // 相当于  Person p8 = Person(p7);
  // 现在的编译器初始化时不产生临时变量
}

int main() {
  test01();
}
```

### 拷贝函数调用时机

```cpp {.line-numbers, highlight=[22, 30, 40, 49-53, 59]}
#include <iostream>
using namespace std;

class Person {
 public:
  Person() {
    cout << "默认构造函数调用" << endl;
  }
  Person(int a) {
    cout << "有参函数调用" << endl;
  }
  Person(Person const& p) {
    cout << "拷贝构造函数调用" << endl;
  }
  ~Person() {
    cout << "析构函数调用" << endl;
  }
  int m_age;
};

// 拷贝构造函数的调用时机
// 1. 用已经创建好的对象来初始化对象
void test01() {
  Person p1;
  p1.m_age = 10;

  Person p2(p1);
}

// 2. 以值传递的方式给函数参数传值
void doWork(Person p1) {  // Person p1 = Person(p2);
}

void test02() {
  Person p1;
  p1.m_age = 20;
  doWork(p1);
}

// 3. 以值方式返回局部变量
Person doWork2() {
  Person p1;
  return p1;
}

void test03() {
  Person p = doWork2();
}
// Release下优化成什么样？  c++11下clang编译器已经优化了3，只调用一次默认构造和析构
/*Person p; 不调用默认构造   ??????????不是很懂
  doWork2(p);
  void doWork2(Person& p){
    Person p1; 调用默认构造
  }
*/

void test04() {
  Person p1;
  Person& p2      = Person(p1); // Non-const lvalue reference to type 'Person' cannot bind to a temporary of type
  Person const& p = Person(p1);
  // std::string& str = "abc";
  cout << "--------------" << endl;
}

int main() {
  // test01();
  // test02();
  test03();
}
```

### 构造函数调用规则

```cpp
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class MyClass
{
public:
 //MyClass()
 //{
 // cout << "默认构造函数" << endl;
 //}

 MyClass(int a)
 {
  cout << "有参构造函数" << endl;
 }

 //MyClass(const MyClass& m)
 //{
 //}
 int m_A;
 
 
};

//系统默认给一个类提供 3个函数  默认构造 、 拷贝构造 、 析构函数

//1 当我们提供了有参构造函数，那么系统就不会在给我们提供默认构造函数了
//但是 系统还会提供默认拷贝构造函数 , 进行简单的值拷贝

void test01()
{
 MyClass c1(1);
 c1.m_A = 10;
 MyClass c2(c1);
 cout << c2.m_A << endl;
}

//2 当我们提供了 拷贝构造，那么系统就不会提供其他构造了

class MyClass2
{
public:
 MyClass2()
 {
  cout << "默认构造函数" << endl;
 }

 //MyClass2(int a)
 //{
 // cout << "有参构造函数" << endl;
 //}

 MyClass2(const MyClass& m)
 {
 }
 int m_A;

};

void test02()
{
 MyClass2 c1;
}


int main(){
 test01();


 system("pause");
 return EXIT_SUCCESS;
}
```

### 深拷贝与浅拷贝

```cpp {.line-numbers, highlight=[26]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;


class Person
{
public:

 Person()
 {}
 //初始化属性
 Person(char * name,int age)
 {
  m_Name = (char*)malloc(strlen(name) + 1);
  strcpy(m_Name, name);

  m_age = age;
 }
 //拷贝构造 系统会提供默认拷贝构造，而且是简单的值拷贝
 //自己提供拷贝构造，原因简单的浅拷贝会释放堆区空间两次，导致挂掉
 //深拷贝
 Person(const Person&p)
 {
  m_age = p.m_age;
  m_Name = (char*)malloc(strlen(p.m_Name) + 1); // strlen根据传入字符指针，计算字符串长度，不包括'\0', char chr[] = "abc"，sizeof(chr)计算字节数，包括'\0'
  strcpy(m_Name, p.m_Name);
 }

 ~Person()
 {
  cout << "析构函数调用" << endl;
  if (m_Name!=NULL)
  {
   free(m_Name);
   m_Name = NULL;
  }
 }


 //姓名
 char * m_Name;
 //年龄
 int m_age;
};


void test01()
{
 Person p1("敌法",10);
 Person p2(p1); //调用拷贝构造

 
}


int main(){

 test01();

 system("pause");
 return EXIT_SUCCESS;
}
```

### 类对象作为成员

```cpp {.line-numbers, highlight=[78]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <string>
using namespace std;

class Phone
{
public:
 Phone()
 {
  cout << "手机的默认构造函数调用" << endl;
 }
 Phone(string name)
 {
  cout << "手机的有参构造调用" << endl;
  m_PhoneName = name;
 }
 
 ~Phone()
 {
  cout << "手机的析构函数调用" << endl;
 }

 string m_PhoneName;

};

class Game
{
public:
 Game()
 {
  cout << "Game的默认构造函数调用" << endl;
 }
 Game(string name)
 {
  cout << "Game的有参构造调用" << endl;
  m_GameName = name;
 }
 ~Game()
 {
  cout << "Game的析构函数调用" << endl;
 }

 string m_GameName;

};

class Person
{
public:
 Person()
 {
  cout << "Person的默认构造函数调用" << endl;
 }

 Person(string name, string phoneName, string gameName) : m_Name(name), m_Phone(phoneName), m_Game(gameName)
 {
  cout << "Person的有参构造调用" << endl;
  //m_Name = name;
 }

 void playGame()
 {
  cout << m_Name << " 拿着《" << m_Phone.m_PhoneName << "》牌手机 ，玩着《" << m_Game.m_GameName << "》游戏" << endl;
 }

 ~Person()
 {
  cout << "Person的析构函数调用" << endl;
 }

 string m_Name; //姓名
 Phone m_Phone; //手机
 Game m_Game; //游戏
};

//类对象作为类成员时候，构造顺序先将类对象一一构造，然后构造自己， 析构的顺序是相反的
void test01()
{
 Person p("狗蛋","苹果","切水果");
 p.playGame();
}

int main(){

 test01();

 system("pause");
 return EXIT_SUCCESS;
}
```

### new运算符使用

```cpp {.line-numbers, highlight=[31-36, 44]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Person
{
public:
 Person()
 {
  cout << "默认构造调用" << endl;
 }

 Person(int a)
 {
  cout << "有参构造调用" << endl;
 }

 ~Person()
 {
  cout << "析构函数调用" << endl;
 }

};

void test01()
{
 //Person p1;  栈区开辟

 Person * p2 = new Person; //堆区开辟

 //所有new出来的对象 都会返回该类型的指针
 //malloc 返回 void* 还要强转，并且可能分配失败需要判断是否分配成功
 // malloc需要自己确定内存字节大小，new 知道对应类型即可
 //malloc会调用构造吗？ 不会  new会调用构造
 // new 运算符  malloc 函数
 //释放 堆区空间
 // delete也是运算符 配合 new用  malloc 配合 free用
 delete p2;

}

void test02()
{
 void *p = new Person(10); 
 //当用void* 接受new出来的指针 ，会出现释放的问题
 delete p;
 //无法释放p ，所以避免这种写法
}

void test03()
{
 //通过new开辟数组 一定会调用默认构造函数,所以一定要提供默认构造
 Person * pArray = new Person[10];
 //Person pArray2[2] = { Person(1), Person(2) }; //在栈上开辟数组，可以指定有参构造


 //释放数组 delete []
 delete [] pArray;
}

int main(){

 //test01();

 //test02();

 test03();

 system("pause");
 return EXIT_SUCCESS;
}
```

### 单例模式-主席案例

```cpp {.line-numbers, highlight=[30, 55]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//创建主席类
//需求 单例模式  为了创建类中的对象，并且保证只有一个对象实例
class ChairMan
{
 //1构造函数 进行私有化
private:
 ChairMan()
 {
  //cout << "创建国家主席" << endl;
 }
 //拷贝构造 私有化
 ChairMan(const ChairMan&c)
 {}

public:
 //提供 get方法 访问 主席
 static ChairMan* getInstance()
 {
  return singleMan;
 }

private:
 static ChairMan * singleMan;

};
ChairMan * ChairMan::singleMan = new ChairMan;  // 运行时初始化

void test01()
{
 /*ChairMan c1;
 ChairMan * c2 = new ChairMan;
 ChairMan * c3 = new ChairMan;*/

 /*ChairMan * cm = ChairMan::singleMan;
 ChairMan * cm2 = ChairMan::singleMan;
*/
 //ChairMan::singleMan = NULL;


 ChairMan * cm1 = ChairMan::getInstance();
 ChairMan * cm2 = ChairMan::getInstance();
 if (cm1 == cm2)
 {
  cout << "cm1 与 cm2相同" << endl;
 }
 else
 {
  cout << "cm1 与 cm2不相同" << endl;
 }

 /*ChairMan * cm3 = new ChairMan(*cm2); // 调用拷贝构造
 if (cm3 == cm2)
 {
 cout << "cm3 与 cm2相同" << endl;
 }
 else
 {
 cout << "cm3 与 cm2不相同" << endl;
 }*/


}

int main(){

 //cout << "main调用" << endl; 主席创建先于main调用
 test01();

 system("pause");
 return EXIT_SUCCESS;
}
```

```cpp {.line-numbers, highlight=[1, 25, 30]}
// 自写单例 ????????????????????????????线程是否安全
#include <iostream>
#include <ostream>

class Person {
 private:
  int age;
  static Person singleton;
  Person();
  // 屏蔽拷贝构造
  Person(Person const& Person) {}

 public:
  Person(int _age) : age(_age) {}
  static Person const& get();
  int GetAge() const;
};
Person::Person() : age(0) {}
int Person::GetAge() const {
  return age;
}
Person const& Person::get() {
  return singleton;
}
Person Person::singleton;  // 运行时初始化

int main() {
  Person const& per = Person::get();
  std::cout << per.GetAge() << std::endl;
  Person* ptr = new Person[2]{10, 20};  // c++11运行时初始化，调用默认构造，c++2b调用有参构造
  std::cout << ptr[0].GetAge() << std::endl;
}
```

- [ ] [单例模式线程安全](https://zhuanlan.zhihu.com/p/83539039)

```cpp {.line-numbers, highlight=[21]}
////////////////////////// 饿汉实现 /////////////////////
class Singleton
{
public:
    // 获取单实例
    static Singleton* GetInstance();

    // 释放单实例，进程退出时调用
    static void deleteInstance();
    
    // 打印实例地址
    void Print();

private:
    // 将其构造和析构成为私有的, 禁止外部构造和析构
    Singleton();
    ~Singleton();

    // 将其拷贝构造和赋值构造成为私有函数, 禁止外部拷贝和赋值
    Singleton(const Singleton &signal);
    Singleton &operator=(const Singleton &signal); // 为什么禁止赋值操作符?????????????????????????????????????

private:
    // 唯一单实例对象指针
    static Singleton *g_pSingleton;
};

// 代码一运行就初始化创建实例 ，本身就线程安全
Singleton* Singleton::g_pSingleton = new (std::nothrow) Singleton;

Singleton* Singleton::GetInstance()
{
    return g_pSingleton;
}

void Singleton::deleteInstance()
{
    if (g_pSingleton)
    {
        delete g_pSingleton;
        g_pSingleton = NULL;
    }
}

void Singleton::Print()
{
    std::cout << "我的实例内存地址是:" << this << std::endl;
}

Singleton::Singleton()
{
    std::cout << "构造函数" << std::endl;
}

Singleton::~Singleton()
{
    std::cout << "析构函数" << std::endl;
}
////////////////////////// 饿汉实现 /////////////////////
```

### 单例模式-打印机

```cpp
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <string>
using namespace std;

class Printer
{
private:
 Printer(){ m_Count = 0; };
 Printer(const Printer& p);

public:
 static Printer* getInstance()
 {
  return singlePrinter;
 }

 void printText(string text)
 {
  cout << text << endl;
  m_Count++;
  cout << "打印机使用了次数为： " << m_Count << endl;
 }




private:
 static Printer* singlePrinter;
 int m_Count;
};
Printer* Printer::singlePrinter = new Printer;

void test01()
{
 //拿到打印机
 Printer * printer =  Printer::getInstance();

 printer->printText("离职报告");
 printer->printText("入职报告");
 printer->printText("加薪申请");
 printer->printText("升级申请");
 printer->printText("退休申请");
}

int main(){

 test01();

 system("pause");
 return EXIT_SUCCESS;
}
```

### 成员变量和成员函数是分开的

```cpp {.line-numbers, highlight=[4, 7-11, 19]}

#include <iostream>
using namespace std;

// #pragma pack(1)  // 关闭内存对齐
class Person {
 public:
  int m_A;                //非静态成员变量，属于对象身上
  void func(){};          //非静态成员函数 不属于对象身上
  static int m_B;         //静态成员变量 ，不属于对象身上
  static void func2(){};  //静态成员函数 ，不属于对象身上
  double m_C;             // 12 错误  16正确（内存对齐）
};

//结论 ： 非静态成员变量 ，才属于对象身上

void test01() {
  // 6 、 0 、 4 、 1
  cout << "sizo of (Person) = " << sizeof(Person) << endl;
  //空类的大小为 1  每个实例的对象 都有独一无二的地址，char维护这个地址，不是很理解，非空类难道就能不用char成为独一无二的吗??????????????s
  // Person p[10]  p[0] p[1]
}

void test02() {
  //this指针指向被调用的成员函数所属的对象

  Person p1;
  p1.func();  //编译器会偷偷 加入一个 this指针  Person * this

  Person p2;
  p2.func();
}

int main() {
  test01();
}
```

### this指针使用

```cpp
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

// this可以解决命名冲突
class Person
{
public:
 Person(  int age)
 {
  this->age = age;
 }

 //对比年龄
 void compareAge( Person & p)
 {
  if (this->age == p.age )
  {
   cout << "年龄相等" << endl;;
  }
  else
  {
   cout << "年龄不相等" << endl;;
  }
 }

 //年龄相加
  Person& PlusAge(Person & p)
 {
   this->age += p.age;
   return *this; //*this指向对象本体
 }

 int age;
};

void test01()
{
 Person p1(10);
 
 cout << "p1的年龄" << p1.age << endl;

 Person p2(10);

 p1.compareAge(p2);

 p1.PlusAge(p2).PlusAge(p2).PlusAge(p2); //链式编程

 cout << "p1的年龄" << p1.age << endl;
}

int main(){

 test01();

 system("pause");
 return EXIT_SUCCESS;
}
```

### 空指针访问成员函数

```cpp {.line-numbers, highlight=[15]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Person
{
public:

 void show(  )
 {
  cout << "Person show" << endl;  
 }
 void showAge()
 {
  if (this == NULL)   // 增加代码鲁棒性，防止代码宕机
  {
   return;
  }
  cout << this->m_Age << endl; // NULL -> m_Age
 }

 int m_Age; // 
};

void test01()
{
 Person * p = NULL;
 p->show();
 p->showAge();

}

int main(){
 test01();


 system("pause");
 return EXIT_SUCCESS;
}

```

### const修饰成员函数

```cpp {.line-numbers, highlight=[32]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Person
{
public :
 Person()
 {
  //构造中修改属性
  //this 永远执行本体  
  
  this->m_A = 0;
  this->m_B = 0;
 }

 void showInfo() const //常函数 不允许修改指针指向的值
 {
  //this->m_A = 1000;
  this->m_B = 1000;
  // const Person * const this
  cout << "m_A = " << this->m_A << endl;
  cout << "m_B = " << this->m_B << endl;
 }

 void show2() const
 {
  //m_A = 100;
 }

 int m_A;
 mutable int m_B; //就算是常函数 我还是执意要修改

};

void test01()
{

 Person p1;
 p1.showInfo();

 //常对象 不允许修改属性
 const  Person p2;
 //cout << p2.m_A << endl;
 p2.show2();
 //常对象 不可以调用普通成员函数
 //常对象 可以调用常函数
}

int main(){

 test01();

 system("pause");
 return EXIT_SUCCESS;
}

```

### 全局函数做友元函数

```cpp
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <string>
using namespace std;

class Building
{
 //让全局的好基友函数 变为我的好朋友  友元函数
 friend void  goodGay(Building * building);
public:
 Building()
 {
  this->m_SittingRoom = "客厅";
  this->m_BedRoom = "卧室";
 }

 //客厅  卧室
public:
 string m_SittingRoom; //客厅

private:
 string m_BedRoom; //卧室
};

//全局函数  好基友
void  goodGay( Building * building )
{
 cout << "好基友正在访问 " << building->m_SittingRoom << endl;
 cout << "好基友正在访问 " << building->m_BedRoom << endl;
}
//友元函数 目的访问类中的私有成员属性
void test01()
{
 Building * building = new Building;
 goodGay(building);
}

int main(){

 test01();

 system("pause");
 return EXIT_SUCCESS;
}

```

### 类作为友元类

```cpp {.line-numbers, highlight=[6, 59]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <string>
using namespace std;

class Building; // 为让后面类定义知晓该类名存在，类声明和定义提供大量信息给编译器
class goodGay
{
public:
 goodGay();

 void visit();
private:
 Building * building;
};

class Building
{
 //让好基友类 作为 Building的好朋友
 friend class goodGay;
public:
 Building();
public:
 string m_SittingRoom; //客厅
private:
 string m_BedRoom; //卧室
};

goodGay::goodGay()
{
 building = new Building;
}

void goodGay::visit()
{
 cout << "好基友正在访问： " << this->building->m_SittingRoom << endl;
 cout << "好基友正在访问： " << this->building->m_BedRoom << endl;
}

Building::Building()
{
 this->m_SittingRoom = "客厅";
 this->m_BedRoom = "卧室";
}

void test01()
{
 goodGay gg;
 gg.visit();
}

int main(){

 test01();

 system("pause");
 return EXIT_SUCCESS;
}
// 友元类是单向的，友元类的友元关系不可传递
```

### 成员函数做友元函数

```cpp
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <string>

//只让 visit可以作Building的好朋友  visit2 不可以访问私有属性
class Building;
class goodGay
{
public:
 goodGay();

 void visit();
 void visit2();
private:
 Building * building;
};

class Building
{
 //让成员函数 visit作为友元函数
 friend void goodGay::visit();
 
public:
 Building();
public:
 string m_SittingRoom; //客厅
private:
 string m_BedRoom; //卧室
};

goodGay::goodGay()
{
 building = new Building;
}

void goodGay::visit()
{
 cout << "好基友正在访问： " << this->building->m_SittingRoom << endl;
 cout << "好基友正在访问： " << this->building->m_BedRoom << endl;
}

void goodGay::visit2()
{
 cout << "好基友正在访问： " << this->building->m_SittingRoom << endl;
 //cout << "好基友正在访问： " << this->building->m_BedRoom << endl;
}

Building::Building()
{
 this->m_SittingRoom = "客厅";
 this->m_BedRoom = "卧室";
}

void test01()
{
 goodGay gg;
 gg.visit();
 gg.visit2();
}

int main(){

 test01();

 system("pause");
 return EXIT_SUCCESS;
}

```

### 前置后置递增递减运算符重载

```cpp {.line-numbers, highlight=[23]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class MyInteger
{
 friend ostream& operator<<(ostream& cout, MyInteger & myInt);

public:
 MyInteger()
 {
  m_Num = 0;
 };

 //前置++重载
 MyInteger& operator++()
 {
  this->m_Num++;
  return *this;
 }

 //后置++ 重载
 MyInteger operator++(int)    // 编译器根据占位符区别前置，后置
 {
  //先保存目前数据
  MyInteger tmp = *this;
  m_Num++;
  return tmp;
 }
 int m_Num;
};

ostream& operator<<( ostream& cout ,MyInteger & myInt)
{
 cout << myInt.m_Num;
 return cout;
}

void test01()
{
 MyInteger myInt;
 // 前置++
 
 cout << ++(++myInt) << endl;
 cout << myInt << endl;

 //cout << myInt++ << endl; // 后置++ 

 //cout << myInt << endl;
}

int main(){

 test01();

 /*int a = 10;
 cout << ++(++a) << endl;
 cout << a << endl;*/

 system("pause");
 return EXIT_SUCCESS;
}

```

### 指针运算符重载-智能指针

```cpp {.line-numbers, highlight=[26, 72-73]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Person
{
public:
 Person(int age)
 {
  this->m_Age = age;
 }

 void showAge()
 {
  cout << "年龄为：" << this->m_Age << endl;
 }
 ~Person()
 {
  cout << "Person的析构调用" << endl;
 }

 int m_Age;
};


//智能指针
//用来托管自定义类型的对象，让对象进行自动的释放
class smartPointer
{
public:
 smartPointer(Person * person)
 {
  this->person = person;
 }

 //重载->让智能指针对象 想Person *p一样去使用
 Person * operator->()
 {
  return this->person;
 }

 //重载 * 
 Person& operator*()
 {
  
  return *this->person;
 }

 ~smartPointer()
 {
  cout << "智能指针析构了" << endl;
  if (this->person !=NULL)
  {
   delete this->person;
   this->person = NULL;
  }
 }

private:
 Person * person;
};

void test01()
{
 //Person p1(10); //自动析构

 //Person * p1 = new Person(10);
 //p1->showAge();
// delete p1;


 smartPointer sp(new Person(10)); //sp开辟到了栈上，自动释放
 sp->showAge(); // sp->->showAge(); 编译器优化了 写法

 (*sp).showAge();
}


int main(){

 test01();

 system("pause");
 return EXIT_SUCCESS;
}

```

### 赋值运算符重载

```cpp
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//一个类默认创建 默认构造、析构、拷贝构造 operator=赋值运算符 进行简单的值传递
class Person
{
public:

 Person(int a)
 {
  this->m_A = a;
 }


 int m_A;
};

void test01()
{
 Person p1(10);

 Person p2(0);

 p2 = p1; //赋值

 cout << "p2 的m_A" << p2.m_A <<endl;
}


class Person2
{
public:
 Person2(char * name)
 {
  this->pName = new char[strlen(name) + 1];
  strcpy(this->pName, name);
 }

 //重载 = 赋值运算符
 Person2& operator= ( const Person2 & p)
 {
  //判断如果原来已经堆区有内容，先释放
  if (this->pName != NULL)
  {
   delete[] this->pName;
   this->pName = NULL;
  }

  this->pName = new char[strlen(p.pName) + 1];
  strcpy(this->pName, p.pName);

  return *this;
 }

 ~Person2()
 {
  if (this->pName != NULL)
  {
   delete[] this->pName;
   this->pName = NULL;
  }
 }

 char * pName; 
};

void test02()
{
 Person2 p1("狗蛋");

 Person2 p2("狗剩");

 Person2 p3("");
 p3 = p2 = p1;

 cout << p2.pName << endl;
 cout << p3.pName << endl;

 //int a = 10;
 //int b = 20;
 //int c;
 //c = a = b; //都是20
 //cout << a << " " << b << " " << c << endl;

}

int main(){

 //test01();

 test02();

 system("pause");
 return EXIT_SUCCESS;
}

```

### 设计数组类

```cpp {.line-numbers, highlight=[63, 89]}
// 自写数组类

#include <iostream>
#include <ostream>
using namespace std;

class MyArray {
 private:
  int* array_;
  int capacity_;
  int size_;

 public:
  MyArray();
  MyArray(int capacity);
  MyArray(MyArray const& array);
  void add(int value);
  void add(int index, int value);
  int get(int index);
  int length();
  int GetCapacity();
  int& operator[](int index);
  ~MyArray();
};

MyArray::MyArray() {
  capacity_ = 100;
  size_     = 0;
  array_    = new int[100]{0};
}
MyArray::MyArray(int capacity) {
  capacity_ = capacity;
  size_     = 0;
  array_    = new int[capacity_]{0};
}
MyArray::MyArray(MyArray const& array) {
  capacity_ = array.capacity_;
  size_     = array.size_;
  array_    = new int[capacity_]{0};
  for (int i = 0; i < size_; ++i) {
    array_[i] = array.array_[i];
  }
}
MyArray::~MyArray() {
  delete[] array_;
}
void MyArray::add(int value) {
  array_[size_++] = value;
}
void MyArray::add(int index, int value) {
  array_[index] = value;
  ++size_;
}
int MyArray::length() {
  return size_;
}
int MyArray::GetCapacity() {
  return capacity_;
}
int MyArray::get(int index) {
  return array_[index];
}
int& MyArray::operator[](int index) {
  return array_[index];
}

int main() {
  MyArray array;
  array.add(20);
  array.add(30);
  array.add(10, 100);
  cout << array.length() << endl;
  for (int i = 0; i < 11; ++i) {
    cout << array.get(i) << endl;
  }
  cout << array.GetCapacity() << endl;
  cout << "------------------" << endl;
  MyArray nums(30);
  nums.add(20);
  nums.add(30);
  nums.add(25, 100);
  for (int i = 0; i < 30; ++i) {
    cout << nums.get(i) << endl;
  }
  cout << nums.GetCapacity() << endl;

  cout << "-----------" << endl;
  cout << nums[0] << endl;
  int temp = nums[0];  // int a = 10; int& b = a; int c = b;(拷贝构造)
  cout << temp << endl;
  nums[0] = 30;
  cout << nums[0] << endl;
}

```

### 函数调用运算符重载

```cpp {.line-numbers, highlight=[20, 53-55, 62, 65]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <string>
using namespace std;

// ()重载

class MyPrint
{
public:
 void operator()( string text)
 {
  cout << text << endl;
 }
};

void test01()
{
 MyPrint myPrint;
 myPrint("hello world1111"); // 仿函数
}

class MyAdd
{
public:
 int operator()(int v1,int v2)
 {
  return v1 + v2;
 }

};
void test02()
{
 //MyAdd myAdd;
 //cout << myAdd(1, 1) << endl;

 cout << MyAdd()(1, 1) << endl; //匿名对象
}




int main(){

 //test01();

 test02();

 system("pause");
 return EXIT_SUCCESS;
}

// 不要重载&& || 会导致短路特性失效
// Compare cm1(0);Compare cm2(2);
// cm1 && (cm1 += cm2)  先执行cm1+=cm2,cm1的值变化，再执行重载&&操作

#include <iostream>
using namespace std;
int main() {
  int a = 0;
  int b = 1;
  if (a && (a += b)) {  // 短路特性
    cout << "error" << endl;
  }
  cout << a << endl;      // 输出为0
}

```

### 设计字符串类

```cpp {.line-numbers, highlight=[75-76]}
// 自写字符串
#include <cstring>
#include <iostream>
#include <istream>
#include <ostream>

using namespace std;

class MyString {
 private:
  int length_;
  char* chr_ptr_;

 public:
  MyString(char const* ptr);
  MyString(MyString const& src);
  friend ostream& operator<<(ostream& c_out, MyString const& src);
  friend istream& operator>>(istream& c_in, MyString& src);
  MyString& operator=(char const* ptr);
  MyString& operator=(MyString const& src);
  MyString operator+(char const* ptr);
  MyString operator+(MyString const& src);
  bool operator==(MyString const& src);
  ~MyString();
};

MyString::MyString(char const* ptr) {
  this->length_  = strlen(ptr);
  this->chr_ptr_ = new char[this->length_ + 1];
  strcpy(this->chr_ptr_, ptr);
}
MyString::MyString(MyString const& src) {
  this->length_  = src.length_;
  this->chr_ptr_ = new char[length_ + 1];
  strcpy(chr_ptr_, src.chr_ptr_);
}
MyString::~MyString() {
  delete[] chr_ptr_;
}
ostream& operator<<(ostream& c_out, MyString const& src) {
  c_out << src.chr_ptr_;
  return c_out;
}
istream& operator>>(istream& c_in, MyString& src) {
  if (src.chr_ptr_ != nullptr) {
    delete[] src.chr_ptr_;
  }
  char tmp[1024] = {0};
  c_in >> tmp;
  src.length_  = strlen(tmp);
  src.chr_ptr_ = new char[src.length_ + 1];
  strcpy(src.chr_ptr_, tmp);
  return c_in;
}
MyString& MyString::operator=(char const* ptr) {
  if (this->chr_ptr_ != nullptr) {
    delete[] chr_ptr_;
  }
  length_  = strlen(ptr);
  chr_ptr_ = new char[length_ + 1];
  strcpy(chr_ptr_, ptr);
  return *this;
}
MyString& MyString::operator=(MyString const& src) {
  if (this->chr_ptr_ != nullptr) {
    delete[] chr_ptr_;
  }
  length_  = src.length_;
  chr_ptr_ = new char[length_ + 1];
  strcpy(chr_ptr_, src.chr_ptr_);
  return *this;
}
MyString MyString::operator+(char const* ptr) {
  int new_size = length_ + strlen(ptr) + 1;
  char* tmp    = new char[new_size]; // 新开一片拼接字符串后大小的内存，防止内存溢出
  // strcat(des, src)函数返回des的指针（在des的内存大小基础上进行拼接字符串），当des指针被释放时，后面拼接的字符串释放不了，导致内存泄漏
  strcat(tmp, this->chr_ptr_);
  strcat(tmp, ptr);
  MyString res(tmp);
  delete[] tmp;
  return res;
}
MyString MyString::operator+(MyString const& src) {
  int new_size = length_ + strlen(src.chr_ptr_) + 1;
  char* tmp    = new char[new_size];
  strcat(tmp, this->chr_ptr_);
  strcat(tmp, src.chr_ptr_);
  MyString res(tmp);
  delete[] tmp;
  return res;
}
bool MyString::operator==(MyString const& src) {
  return this->length_ == src.length_ && strcmp(this->chr_ptr_, src.chr_ptr_) == 0;
}

int main() {
  MyString str1("abc");
  cout << str1 << endl;
  // cin >> str1;
  // cout << str1 << endl;
  cout << (str1 == "abc" ? "两者相等" : "两者不等") << endl;
}

```

```cpp {.line-numbers, highlight=[5-6, 8-9]}
#include <iostream>
// const pointer and pointer to const写法
int main() {
  int a        = 20;
  int* const c = &a;  // const pointer
  int const* f = &a;  // pointer to const
  int d        = 40;
  c            = &d;  // Cannot assign to variable 'c' with const-qualified type 'int *const'
  *f           = 40;  // Read-only variable is not assignable
}

```

```cpp {.line-numbers, highlight=[1, 7]}
// 开辟内置类型堆空间时记得初始化零值
#include <cstring>
#include <iostream>

using namespace std;
int main() {
  char* chrs = new char[10]{0};
  chrs[0]    = 'a';
  chrs[1]    = 'b';
  for (int i = 0; i < int(strlen(chrs)); ++i) {
    cout << chrs[i] << endl;
  }
}

```

### 继承方式

```cpp {.line-numbers, highlight=[1-2, 108-110]}
// 继承模式（以何种方式继承父类继承过来的成员）：public, protected, private
// protected和private对外部访问来说是起一样的作用的，但是对派生类来说还是不一样的，在公有继承模式下，protected成员能被派生类访问，private不能；
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Base1
{
public:
 int m_A;
protected:
 int m_B;
private:
 int m_C;
};

//公有继承
class Son1 : public Base1
{
public:
 void func()
 {
  //cout << m_C << endl; //基类中私有的属性 不可继承
  cout << m_A << endl; //基类中公有的属性 可继承，还是public
  cout << m_B << endl;//基类中保护的属性 可继承，还是protected 类外访问不到
 }

};
void myFunc()
{
 Son1 s1;
 s1.m_A;
 //s1.m_B;
}

////////////////////////////////////////保护继承////////////////////////////////////////

class Base2
{
public:
 int m_A;
protected:
 int m_B;
private:
 int m_C;
};
class Son2 :protected Base2
{
public:
 void func()
 {
  //cout << m_C << endl; //基类中私有的属性 不可继承
  cout << m_A << endl;//基类中公有的属性 可继承，还是protected
  cout << m_B << endl;//基类中保护的属性 可继承，还是protected
 }

};
void myFunc2()
{
 Son2 s;
 //s.m_A; 不能访问
}


////////////////////////////////////////私有继承////////////////////////////////////////
class Base3
{
public:
 int m_A;
protected:
 int m_B;
private:
 int m_C;

};

class Son3 :private Base3
{
public:
 void func()
 {
  //cout << m_C << endl; //基类中私有的属性 不可继承
  cout << m_A << endl; //基类中公有的属性 可继承，还是private
  cout << m_B << endl;//基类中保护的属性 可继承，还是private
 }

};

class GrandSon3 :public Son3
{
public:
 void myFunc()
 {
  //cout << m_A << endl; //孙子类中 访问不到 m_A，因为在Son3中m_A已经是私有属性了
 }

};



int main(){



 system("pause");
 return EXIT_SUCCESS;
}
// ？？？？？？？待证明--继承关系中：先构造父类，在构造子类（有父才有子），继承模式决定了，该块内存中，父类成员是否能够被子类访问；
// ？？？？？？？待证明--继承减少程序文本（非可执行程序）中的代码量，还有如适配器设计模式，也是为了减少程序文本中的代码量----可执行程序的大小在于是否用了该类型，没有用该类型，无论定义了多少类型，都不会影响可执行程序大小
// 类中成员为对象时候的构建时，先构建成员对象，再构建本体对象（洋葱从底层构建），析构时先析构本体对象，再析构成员对象（洋葱从外向内剥皮）

```

![](/assets/images/2022-10-17-22-52-07.png)

### 继承中的对象模型

```cpp {.line-numbers, highlight=[16, 25]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Base
{
public:
 int m_A;
protected: 
 int m_B;
private:
 int m_C;

};

//子类中 会继承父类的私有成员，只是被编译给隐藏起来，访问不到私有成员
class Son :public Base
{
public:
 int m_D;
};

void test01()
{
 cout << sizeof(Son) << endl; // 16

}

int main(){

 test01();

 system("pause");
 return EXIT_SUCCESS;
}


```

### 继承中的构造和析构函数

```cpp {.line-numbers, highlight=[80-85, 104, 107-108]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Base
{
public:
 Base()
 {
  m_A = 10;
  cout << "Base默认构造函数调用" << endl;
 }
 ~Base()
 {
  cout << "Base的析构函数调用" << endl;
 }

 int m_A;
};
// 子类会继承父类的成员属性，成员函数
//但是 子类 不会继承 父类 构造函数 和 析构函数
//只有父类自己知道如果构造和析构自己的属性，而子类不知道


class Son :public Base
{
public:
 Son()
 {
  cout << "Son默认构造函数调用" << endl;
 }
 ~Son()
 {
  cout << "Son的析构函数调用" << endl;
 }
};

void test01()
{
 //Base b1;

 Son s1;
}



class Base2
{
public:
 Base2(int a)
 {
  this->m_A = a;
  cout << "有参构造函数调用" << endl;
 }
 int m_A;
};

class Son2:public Base2
{
public:
 Son2(int a ) : Base2(a)//利用初始化列表方式 显示调用 有参构造
 {
 }
};

void test02()
{
 Son2 s2(1000);
}


int main(){

 test01();

 system("pause");
 return EXIT_SUCCESS;
}

// 在继承中，派生类的拷贝构造是否自动调用基类的拷贝构造???????????
// 在继承中，派生类赋值运算符是否继承基类赋值运算符----答：派生类不继承基类赋值运算符
// 在继承中，派生类的默认构造自动调用基类的默认构造
// 继承，虚函数，多态关系？？？？？？？？？？？？？？？？？
// 待验证？？？？通过下表可知赋值运算符不可以继承，但可以是虚函数，不可继承可以这样理解，当赋值时候每个对象都是得把自己内存的东西赋值给相应类型对象，就好像人自己把东西需要赋给与自己同样的一类人。
// 待验证？？？？？？而虚函数是在实现多态作用，使得运行时候能够确定真正的类型对象所要进行的赋值运算，继承和虚函数并没有联系，但两者共同使得能够实现多态机制


#include <iostream>

class Student {};

class Home : public Student {};

void test01(Student& stu) {
  std::cout << "a is on" << std::endl;
}

void test01(Home& home) {
  std::cout << "a" << std::endl;
}

auto main() -> int {
  Home home;
  test01(home); // 重载更加具体化的函数
}

// 待验证？？？？？？----对于java中类型判定和强转的一些理解，java中的isInstanceOf相当于是运行时先进行查一个对象信息表然后判定确切类型，判定通过，就查虚函数表进行函数调用
// 其中强转可以自由从Objec转任意子类，有点类似子类有个显示转换构造函数，如Object ob = new Object(); ArrayList nums = (ArrayList) ob;
```

![](/assets/images/2022-10-18-13-51-44.png)

![](/assets/images/2022-10-18-14-33-26.png)

![](/assets/images/2022-10-18-14-33-02.png)

### 继承中同名函数处理

```cpp {.line-numbers, highlight=[53, 57-59]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Base
{
public:
 Base()
 {
  m_A = 100;
 }

 void fun()
 {
  cout << "Base func调用" << endl;
 }
 void fun(int a)
 {
  cout << "Base func (int a)调用" << endl;
 }


 int m_A;
};

class Son :public Base
{
public:
 Son()
 {
  m_A = 200;
 }

 void fun()
 {
  cout << "Son func调用" << endl;
 }

 int m_A;
};

void test01()
{
 Son s1;
 cout << s1.m_A << endl;
 //想调用 父类中 的m_A

 cout << s1.Base::m_A << endl;

 s1.fun();

 //调用父类的func
 s1.Base::fun(10);

}

//如果子类和父类拥有同名的函数 属性 ，子类会覆盖父类的成员吗？ 不会
//如果子类与父类的成员函数名称相同，子类会把父类的所有的同名版本都隐藏掉
//想调用父类的方法，必须加作用域


int main(){

 test01();

 system("pause");
 return EXIT_SUCCESS;
}

```

### 继承中静态成员处理

```cpp {.line-numbers, highlight=[45]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Base
{
public:

 static void func()
 {
  cout << "base fun()" << endl;
 }
 static void func(int a)
 {
  cout << "base fun(int)" << endl;
 }


 static int m_A;
};
int Base::m_A = 10;

class Son :public Base
{
public:

 static void func()
 {
  cout << "son fun()" << endl;
 }

 static int m_A;
};
int Son::m_A = 20;

//静态成员属性 子类可以继承下来
void test01()
{
 cout << Son::m_A << endl;
 //访问父类的m_A
 cout << Base::m_A << endl;

 Son::func();
 //访问 父类中同名的函数
 Son::Base::func(10);   // 由子便可以访问父

}


int main(){

 test01();

 system("pause");
 return EXIT_SUCCESS;
}

```

### 多继承的概念和问题

```cpp {.line-numbers, highlight=[36]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Base1
{
public:
 Base1()
 {
  m_A = 10;
 }
public:
 int m_A;
};

class Base2
{
public:
 Base2()
 {
  m_A = 20;
 }
public:
 int m_A;
};

//多继承
class Son :public Base1, public Base2
{
public:

 int m_C;
 int m_D;
};

//多继承中很容易引发二义性
void test01()
{
 cout << sizeof(Son) << endl;

 Son s1;
 //s1.m_A; //二义性

 cout << s1.Base1::m_A << endl; 
 cout << s1.Base2::m_A << endl;
}

int main(){

 test01();

 system("pause");
 return EXIT_SUCCESS;
}

```

### 菱形继承的概念和问题

```cpp {.line-numbers, highlight=[11, 25-26, 39-40]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Animal
{
public:
 int m_Age;
};

//虚基类 Sheep
class Sheep :virtual public Animal
{
};
//虚基类 Tuo
class Tuo :virtual public Animal
{
};

class SheepTuo :public Sheep, public Tuo
{

};

// 菱形继承的问题，产生多份空间，产生资源浪费
//菱形继承的解决方案 利用虚继承 之后操作的是共享的一份数据

void test01()
{
 SheepTuo st;
 st.Sheep::m_Age = 10;
 st.Tuo::m_Age = 20;

 cout << st.Sheep::m_Age << endl;
 cout << st.Tuo::m_Age << endl;
 cout << st.m_Age << endl; //可以直接访问，原因已经没有二义性的可能了，只有一份m_Age
}

//通过地址 找到 偏移量
//内部工作原理
void test02()
{
 SheepTuo st;
 st.m_Age = 100;

 //找到Sheep的偏移量操作
 //cout<< *(int *)((int *)*(int *)&st + 1) << endl;

 cout << *(int*)((int*)*(int *)&st + 1) << endl;

 //找到Tuo的偏移量
 cout << *((int *)((int *)*((int *)&st + 1) + 1)) << endl;
 
 //输出Age
 cout << ((Animal*)((char *)&st + *(int*)((int*)*(int *)&st + 1)))->m_Age << endl;

}

int main(){

 //test01();
 test02();

 system("pause");
 return EXIT_SUCCESS;
}

```

![](/assets/images/2022-10-18-16-27-44.png)

### 静态联编和动态联编

```cpp {.line-numbers, highlight=[1, 35-36, 60]}
// 多态为实现和定义之间提供了隔离性，便于代码阅读和拓展
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Animal
{
public:
 virtual void speak()
 {
  cout << "动物在说话" << endl;
 }

 virtual void eat()
 {
  cout << "动物在吃饭" << endl;
 }

};

class Cat :public Animal
{
public:
 void speak()
 {
  cout << "小猫在说话" << endl;
 }

 virtual void eat()
 {
  cout << "小猫在吃鱼" << endl;
 }
};

//调用doSpeak ，speak函数的地址早就绑定好了，早绑定，静态联编，编译阶段就确定好了地址
//如果想调用猫的speak，不能提前绑定好函数的地址了，所以需要在运行时候再去确定函数地址
//动态联编，写法 doSpeak方法改为虚函数,在父类上声明虚函数，发生了多态
// 父类的引用或者指针 指向 子类对象
void doSpeak(Animal & animal) //Animal & animal = cat
{
 animal.speak();
}
//如果发生了继承的关系，编译器允许进行类型转换

void test01()
{
 Cat cat;
 doSpeak(cat);

}


void test02()
{
 //cout << sizeof(Animal) << endl;
 //父类指针指向子类对象 多态
 Animal * animal = new Cat;

 //animal->speak();
 // *(int*)*(int*)animal 函数地址  编译器生成
 ((void(*)()) (*(int*)*(int*)animal))();

 //  *((int*)*(int*)animal+1)猫吃鱼的地址

 ((void(*)()) (*((int*)*(int*)animal + 1)))();
}

int main(){

 //test01();

 test02();

 system("pause");
 return EXIT_SUCCESS;
}

```

![](/assets/images/2022-10-19-15-16-49.png)

### 多态案例-计算器案例

```cpp {.line-numbers, highlight=[1-2]}
// 继承和虚函数就是为了实现多态，方便设计开闭原则的代码，对外扩展，不修改源代码
// 抽象基类与纯虚函数有关，抽象基类也有一个虚函数表指针，进行占位，但不提供实现函数地址
```

### 虚析构与纯虚析构

```cpp {.line-numbers, highlight=[14-15, 21-25]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Animal
{
public:

 virtual void speak()
 {
  cout << "动物在说话" << endl;
 }

 //普通析构 是不会调用子类的析构的，所以可能会导致释放不干净
 //利用虚析构来解决这个问题
 //virtual ~Animal()
 //{
 // cout << "Animal的析构调用" << endl;
 //}

 //纯虚析构 写法如下 
 //纯虚析构 ，需要声明 还需要实现 类内声明，类外实现
 virtual ~Animal() = 0;
 //如果函数中出现了 纯虚析构函数，那么这个类也算抽象类
 //抽象类 不可实例化对象

};
Animal::~Animal()
{
 //纯虚析构函数实现
 cout << "Animal的纯虚析构调用" << endl;
}
// 如果出现纯虚析构，类也算抽象类，不能实例化对象
//void func()
//{
// Animal an;
// Animal * animal = new Animal;
//}

class Cat:public Animal
{
public:
 Cat(const char * name)
 {
  this->m_Name = new char[strlen(name) + 1];
  strcpy(this->m_Name, name);
 }

 virtual void speak()
 {
  cout << "小猫在说话" << endl;
 }

 ~Cat()
 {
  cout << "Cat的析构调用" << endl;
  if (this->m_Name !=NULL)
  {
   delete[] this->m_Name;
   this->m_Name = NULL;
  }
 }

 char * m_Name;

};


void test01()
{
 Animal * animal = new Cat("TOM");
 animal->speak();

 delete animal;

}


int main(){

 test01();

 system("pause");
 return EXIT_SUCCESS;
}

```

![](/assets/images/2022-10-19-17-14-57.png)

```cpp {.line-numbers, highlight=[30, 33-40]}
#include <iostream>
class A {
 private:
  short val1;

 public:
  int val2;
  double d;
  static char ch;
  virtual void funcA1() = 0;
  ~A() {
    std::cout << "A" << std::endl;
  }
};

class B : public A {
 public:
  virtual void funcA1() {}
  ~B() {
    std::cout << "B" << std::endl;
  }
};

int main() {
  __attribute__((unused)) int k = sizeof(A);
  __attribute__((unused)) int v = sizeof(B);
  // __attribute__((unused)) A a;
  // B b;
  A* ptr = new B;
  delete ptr;  // 输出 A
}

// 结论：基类成员函数为虚函数需要实现，派生类可实现也可不实现
// 析构函数要为虚函数的原因由于，堆上创建创建子类对象后由父类指针指向后，编译器生成delete的时候，查找子类虚函数表中是否有对应析构，没有就调用父类析构；
// 抽象基类的析构也要为虚函数，不然也保证不了堆上内存释放时的释放顺序
// 虚表中内容动态绑定，其它静态绑定，函数绑定，变量分配地址

// 查看对象内存模型 clang -Xclang -fdump-record-layouts    main函数中需要sizeof
// 查看虚函数表clang -Xclang -fdump-vtable-layouts    main函数中需初始化
// windows中 > 为命令行打印输出到文件，类似于unix中的 |

```

![](/assets/images/2022-10-20-12-05-41.png)

### PK小游戏设计

```cpp {.line-numbers, highlight=[1, 9, 26, 67]}
// 头文件与头文件中互相包含时，可以在其中一个头文件中先进行声明，以使得可以过编译
#pragma once 
#include <iostream>
#include "Weapon.h"
#include <string>
#include "Monster.h"
using namespace std;

class Monster;

class Hero
{
public:
 Hero();

 string m_Name; //人名

 int m_Atk; //攻击力

 int m_Def; // 防御力

 int m_Hp; //血量

 Weapon * weapon; //武器

 void EquipWeapon(Weapon * weapon); // hero类型维护的只是一个外面传来的指针，无需自己delete，由外面使用者自己释放

 void Attack( Monster * monster );
};

// ----------------------------------------------
#pragma once 
#include <iostream>
#include "Weapon.h"
#include <string>
#include "Hero.h"
using namespace std;

class Hero;

class Monster
{
public:
 Monster();

 string m_Name;

 int m_Hp;

 int m_Atk;

 int m_Def;

 bool m_Hold;

 void Attack(Hero * hero);

};

// ---------------------------------------------------
#pragma once

#include "Weapon.h"

class DragonSword : public Weapon {
 public:
  DragonSword();  // 实现构造函数时不能直接使用父类成员初始化列表初始化父类成员，要用父类构造函数初始化父类成员
  virtual int GetBaseDamage(); 
  virtual int GetSuckBlood();
  virtual bool GetHold();
  virtual bool GetCrit();

  int stuck_rate_;
  int hold_rate_;
  int crit_rate_;

  bool IsTrigger(int rate);
};

```

### 指向成员变量和成员函数的指针

```cpp {.line-numbers, highlight=[23, 27]}
#include <iostream>

class Person {
 public:
  Person() : age_(20) {}
  static int height;
  int age_;
  static void show();
  int set();
};

int Person::height = 200;
void Person::show() {
  std::cout << "out" << std::endl;
}
int Person::set() {
  std::cout << "set" << std::endl;
}

int main() {
  Person p1;
  // 指针指向静态成员变量和静态函数
  int* ptr = &Person::height;  // 指向静态成员变量的指针，与普通变量一样，其不独自属于哪个对象
  void (*ptr_function)() = &Person::show;
  std::cout << *ptr << std::endl;
  ptr_function();
  // 指针指向非静态成员变量和非静态成员函数 ????????????????????
  int Person::*p_tr = &Person::age_;
  std::cout << p1.*p_tr << std::endl;
  int (Person::*p_function)() = &Person::set;
  (p1.*p_function)();
}

```

### 函数模板的基本用法

```cpp {.line-numbers, highlight=[22, 42, 46, 49]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//交换int类型两个数字
void mySwapInt( int & a, int & b)
{
 int tmp = a;
 a = b;
 b = tmp;
}

//交换double数据
void mySwapDouble(double &a, double &b)
{
 double tmp = a;
 a = b;
 b = tmp;
}

//类型，逻辑又非常相似
//类型参数化  泛型编程 -- 模板技术
template<class T> // 告诉编译器 下面如果出现T不要报错，T是一个通用的类型
void mySwap(T &a, T &b)
{
 T tmp = a;
 a = b; 
 b = tmp;
}


// template<typename T>  等价于 template<class T>
template<typename T>
void mySwap2(){}

void test01()
{
 int a = 10;
 int b = 20;
 char c1 = 'c';
// mySwapInt(a, b);
 //1 自动类型推导,必须有参数类型才可以推导
 //mySwap(a, c1); 推导不出来T，所以不能运行
 mySwap(a, b);

 //2 显示指定类型
 mySwap<int>(a, b);

 //模板必须要指定出T才可以使用
 mySwap2<double>();

 cout << "a = " << a << endl;
 cout << "b = " << b << endl;

 double c = 3.14;
 double d = 1.1;
 //mySwapDouble(c, d);
 mySwap(c, d);


}

int main(){

 test01();

 system("pause");
 return EXIT_SUCCESS;
}

```

### 利用模板实现任意类型数组排序

```cpp
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//对char和int数组进行排序  排序规则 从大到小  利用选择排序

template <class T>
void mySwap( T &a, T &b)
{
 T tmp = a;
 a = b;
 b = tmp;
}


template<class T>
void mySort( T arr[], int len )
{
 for (int i = 0; i < len;i++)
 {
  int max = i;
  for (int j = i + 1; j < len;j++)
  {
   if (arr[max] < arr[j])
   {
    //交换 下标
    max = j;
   }
  }
  if (max != i)
  {
   //交换数据
   mySwap(arr[max], arr[i]);
  }
 }
}

//输出数组元素的模板
template<class T>
void printArray( T arr[], int len)
{
 for (int i = 0; i < len;i++)
 {

  cout << arr[i] << " ";
 }
 cout << endl;
}

void test01()
{
 char charArr[] = "helloworld";
 int num = sizeof(charArr) / sizeof(char);
 mySort(charArr, num);
 printArray(charArr, num);


 int intArr[] = { 1, 4, 100, 34, 55 };
 int num2 = sizeof(intArr) / sizeof (int);
 mySort(intArr, num2);
 printArray(intArr, num2);

}


int main(){

 test01();

 system("pause");
 return EXIT_SUCCESS;
}

```

### 函数模板与普通函数的区别与调用规则

```cpp {.line-numbers, highlight=[23 , 39]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;


//1 普通函数与函数模板区别
template<class T>
T myPlus(T a, T b)
{
 return a + b;
}

int myPlus2(int a, int b)
{
 return a + b;
}

void test01()
{
 int a = 10;
 int b = 20;
 char c = 'c'; // a = 97 
// myPlus(a, c); //类型推导不出来 ,函数模板不可以进行隐式类型转换
 cout << myPlus2(a, c) <<endl; // 10 + 99  普通函数 可以进行隐式类型转换
}

//2 、普通函数和函数模板的调用规则
template<class T>
void myPrint(T a ,T b)
{
 cout << "模板调用的myPrint" << endl;
}

template<class T>
void myPrint(T a, T b ,T c)
{
 cout << "模板调用的myPrint(a,b,c)" << endl;
}
////通过模板生成的函数  叫模板函数 function of template   template of function 模板是有二次编译
//void myPrint(int a, int b, int c)
//{
//
//}

void myPrint(int a, int  b)
{
 cout << "普通函数调用 myPrint" << endl;
}

void test02()
{
 int a = 10;
 int b = 20;

 //1 、如果出现重载  优先使用普通函数调用,如果没有实现，出现错误
 //myPrint(a, b);

 //2、 如果想强制调用模板 ，那么可以使用空参数列表
 myPrint<>(a, b);

 //3、 函数模板可以发生重载
 int c = 30;
 myPrint(a, b, c);

 //4、 如果函数模板可以产生更好的匹配，那么优先调用函数模板
 char c1 = 'c';
 char d = 'd';
 myPrint(c1, d);

}



int main(){

 //test01();

 test02();

 system("pause");
 return EXIT_SUCCESS;
}

```

### 模板局限性以及解决

```cpp {.line-numbers, highlight=[31]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <string>
using namespace std;

class Person
{
public:
 Person(string name, int age)
 {
  this->m_Name = name;
  this->m_Age = age;
 }
 string m_Name;
 int m_Age;
};



template<class T>
bool myCompare( T &a , T &b )
{
 if ( a == b)
 {
  return true;
 }
 return false;
}

// 通过第三代具体化自定义数据类型，解决上述问题
// 如果具体化能够优先匹配，那么就选择具体化
// 语法  template<> 返回值  函数名<具体类型>(参数) 
template<> bool myCompare<Person>(Person &a, Person &b)
{
 if ( a.m_Age  == b.m_Age)
 {
  return true;
 }

 return false;
}

void test01()
{
 int a = 10;
 int b = 20;

 int ret = myCompare(a, b);

 cout << "ret = " << ret << endl;

 Person p1("Tom", 10);
 Person p2("Jerry", 10);

 int ret2 = myCompare(p1, p2);

 cout << "ret2 = " << ret2 << endl;

}


int main(){

 test01();

 system("pause");
 return EXIT_SUCCESS;
}

```

### 类模板的基本使用

```cpp {.line-numbers, highlight=[8, 28, 67]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <string>
using namespace std;


//类模板
template <class NameType, class AgeType = int> //类模板可以有默认类型
class Person
{
public:
 Person(NameType name, AgeType age)
 {
  this->m_Name = name;
  this->m_Age = age;
 }

 void showPerson()
 {
  cout << "姓名：" << this->m_Name << " 年龄： " << this->m_Age << endl;
 }

 NameType m_Name;
 AgeType m_Age;
};
void test01()
{
 //自动类型推导 ，类模板 不支持
 //Person p("孙悟空", 100);

 //显示指定类型
 Person<string, int> p("孙悟空", 100);
 p.showPerson();
}
class Person1
{
public:
 void showPerson1()
 {
  cout << "Person1的调用" << endl;
 }
};

class Person2
{
public:
 void showPerson2()
 {
  cout << "Person2的调用" << endl;
 }
};

template<class T>
class myClass
{
public:
 T obj;
 void func1()
 {
  obj.showPerson1();
 }
 void func2()
 {
  obj.showPerson2();
 }
};
//类模板中成员函数 一开始不会创建出来，而是在运行时才去创建?????????是否静态绑定

void test02()
{
 myClass<Person1>m;

 m.func1();

 //m.func2();
}

int main(){

// test01();

 test02();

 system("pause");
 return EXIT_SUCCESS;
}

```

### 类模板作为函数参数

```cpp {.line-numbers, highlight=[26, 38, 42, 55]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <string>
using namespace std;

//类模板
template <class NameType, class AgeType = int> //类模板可以有默认类型
class Person
{
public:
 Person(NameType name, AgeType age)
 {
  this->m_Name = name;
  this->m_Age = age;
 }

 void showPerson()
 {
  cout << "姓名：" << this->m_Name << " 年龄： " << this->m_Age << endl;
 }

 NameType m_Name;
 AgeType m_Age;
};

//1  指定传入类型
void doWork( Person<string ,int> & p ) 
{
 p.showPerson();
}

void test01()
{
 Person <string, int> p("MT",10);
 doWork(p);
}

//2 参数模板化 利用函数模板自动推断类型
template<class T1 ,class T2>
void doWork2(Person<T1, T2> & p)
{
 //如何查看类型
 cout << typeid(T1).name() << endl;
 cout << typeid(T2).name() << endl;
 p.showPerson();
}
void test02()
{
 Person <string, int> p("呆贼", 18);

 doWork2(p);
}


//3 整体模板化 利用函数模板自动推断类型
template<class T>
void doWork3(T&p)
{
 cout << typeid(T).name() << endl;
 p.showPerson();
}

void test03()
{
 Person <string, int> p("劣人", 18);

 doWork3(p);
}



int main(){

// test01();

 test02();
 
 test03();

 system("pause");
 return EXIT_SUCCESS;
}

```

### 类模板碰到继承的问题

```cpp {.line-numbers, highlight=[12, 18]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

template <class T>
class Base
{
public:
 T m_A; //double类型
};

//child继承与 base必须告诉base中的T的类型，否则T无法分配内存
class Child :public Base<int>
{

};

//child2 也是模板类
template<class T1, class T2>
class Child2 :public Base<T2>
{
public:
 Child2()
 {
  cout << typeid(T1).name() << endl;
  cout << typeid(T2).name() << endl;
 }
public:
 T1 m_B; //int类型
};

void test01()
{
 Child2<int, double>child;//由用户指定类型

}


int main(){

 test01();

 system("pause");
 return EXIT_SUCCESS;
}

```

### 类模板外实现成员函数

```cpp {.line-numbers, highlight=[26-27]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <string>

template<class T1 ,class T2>
class Person
{
public:
 Person(T1 name, T2  age);
 //{
 // this->m_Name = name;
 // this->m_Age = age;
 //}

 void showPerson();
 //{
 // cout << "姓名：" << this->m_Name << "  年龄：  " << this->m_Age << endl;
 //}

 T1 m_Name;
 T2 m_Age;
};

//类外实现成员函数
template <class T1, class T2>
Person<T1, T2>::Person(T1 name, T2 age)
{
 this->m_Name = name;
 this->m_Age = age;
}

template <class T1, class T2>
void Person<T1, T2>::showPerson()
{
 cout << "姓名：" << this->m_Name << "  年龄：  " << this->m_Age << endl;
}

void test01()
{
 Person <string ,int> p1("Mt", 100);
 p1.showPerson();

}



int main(){

 test01();
 
 system("pause");
 return EXIT_SUCCESS;
}

```

### 类模板的分文件编写问题和解决办法

```cpp {.line-numbers, highlight=[7]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <string>
using namespace std;
#include "Person.hpp"

//建议 模板不要做分文件编写,写到一个类中即可,类内进行声明和实现，最后把后缀名改为.hpp 约定俗成 

int main(){

 Person<string, int>p("猪八戒", 10);
 p.showPerson();


 system("pause");
 return EXIT_SUCCESS;
}

```

### 类模板友元函数-类内实现

```cpp {.line-numbers, highlight=[9]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <string>
using namespace std;

template<class T1 ,class T2>
class Person
{
 //友元函数类内实现 编译器认为其为全局函数
 friend void printPerson( Person<T1 ,T2> & p )
 {
  cout << "姓名：" << p.m_Name << "  年龄： " << p.m_Age << endl;
 }
public: 
 Person(T1 name, T2 age)
 {
  this->m_Name = name;
  this->m_Age = age;
 }

private:
 T1 m_Name;
 T2 m_Age;
};

void test01()
{
 Person<string, int> p("Tom", 10);
 printPerson(p);
}


int main(){
 test01();


 system("pause");
 return EXIT_SUCCESS;
}

```

### 类模板友元函数-类外实现

```cpp {.line-numbers, highlight=[5-7, 16-17]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <string>
using namespace std;
// 如何去理解这种声明方式???????????????????????
//让编译器提前看到printPerson声明

//让编译器看到Person类声明
template<class T1, class T2> class Person;
template<class T1, class T2>void printPerson(Person<T1, T2> & p);


template<class T1, class T2>
class Person
{
 //友元函数类内实现  利用空参数列表 告诉编译器 模板函数的声明
 friend void printPerson<>(Person<T1, T2> & p); //普通函数 声明 friend void printPerson(Person<T1, T2> & p)
 /*{
  cout << "姓名：" << p.m_Name << "  年龄： " << p.m_Age << endl;
 }*/
public:
 Person(T1 name, T2 age)
 {
  this->m_Name = name;
  this->m_Age = age;
 }

private:
 T1 m_Name;
 T2 m_Age;
};

//类外实现
template<class T1 ,class T2>
void printPerson(Person<T1, T2> & p)
{
 cout << "姓名：" << p.m_Name << "  年龄： " << p.m_Age << endl;
}

void test01()
{
 Person<string, int> p("Tom", 10);
 printPerson(p);
}


int main(){

 test01();

 system("pause");
 return EXIT_SUCCESS;
}

```

![](/assets/images/2022-10-23-09-00-42.png)

### 利用模板设计数组类

```cpp
#pragma  once 
#include <iostream>
using namespace std;

template< class T>
class MyArray
{
public:


 //构造
 explicit MyArray(int capacity)  //防止隐式类型转换 防止MyArray arr = 10; 写法
 {
  this->m_Capacity = capacity;
  this->m_Size = 0;
  this->pAddress = new T[this->m_Capacity];
 }

 MyArray(const MyArray & array)
 {
  this->m_Capacity = array.m_Capacity;
  this->m_Size = array.m_Size;
  this->pAddress = new T[this->m_Capacity];
  for (int i = 0; i < m_Size;i++)
  {
   this->pAddress[i] = array[i];
  }
 }

 ~MyArray()
 {
  if (this->pAddress != NULL)
  {
   delete[] this->pAddress;
   this->pAddress = NULL;
  }
 }

 //赋值操作符重载
 MyArray& operator=(MyArray & array)
 {
  //先判断原始数据，有就清空
  if (this->pAddress != NULL)
  {
   delete[] this->pAddress;
   this->pAddress = NULL;
  }
  
  this->m_Capacity = array.m_Capacity;
  this->m_Size = array.m_Size;
  this->pAddress = new T[this->m_Capacity];
  for (int i = 0; i < m_Size; i++)
  {
   this->pAddress[i] = array[i];
  }
 }

 //[]重载
 //MyArray arr(10);
 //arr[0] = 100;
 T & operator[]( int index)
 {
  return this->pAddress[index];
 }

 //尾插法
 void push_Back( T  val)
 {
  this->pAddress[this->m_Size] = val;
  this->m_Size++;
 }


 //获取大小
 int getSize()
 {
  return m_Size;
 }
 //获取容量
 int getCapacity()
 {
  return  this->m_Capacity;
 }
 

private:
 T * pAddress; //指向堆区指针
 int m_Capacity; //容量
 int m_Size;

};

```

```cpp
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include "MyArray.hpp"
#include <string>

//输出int类型数组
void printIntArray(  MyArray<int>& array)
{
 for (int i = 0; i < array.getSize();i++)
 {
  cout << array[i] << endl;
 }
}

class Person
{
public:
 Person(){};

 Person(string name, int age)
 {
  this->m_Name = name;
  this->m_Age = age;
 }
 string m_Name;
 int m_Age;
};



//输出Person类型数组
void printPersonArray( MyArray<Person> & array )
{
 for (int  i = 0; i < array.getSize(); i++)
 {
  cout << "姓名： " << array[i].m_Name << " 年龄： " << array[i].m_Age << endl;
 }
}



int main(){

 MyArray <int >arr(10);
 for (int i = 0; i < 10;i++)
 {
  arr.push_Back(i + 100);
 }

 printIntArray(arr);


 Person p1("MT", 10);
 Person p2("呆贼", 12);
 Person p3("傻馒", 14);
 Person p4("劣人", 15);

 MyArray<Person>arr2(10);
 arr2.push_Back(p1);
 arr2.push_Back(p2);
 arr2.push_Back(p3);
 arr2.push_Back(p4);

 printPersonArray(arr2);
 



 system("pause");
 return EXIT_SUCCESS;
}

```

#### test

```cpp {.line-numbers, highlight=[17, 38]}
#include <cwchar>
#include <ios>
#include <iostream>

class Person {
 public:
  std::string name_;
  int age_;
  Person(std::string name, int age) : name_(name), age_(age) {
    std::cout << "call parameters constructor" << std::endl;
  }
  Person Merge(Person const& src) {
    std::string name = name_ + src.name_;
    int age          = age_ + src.age_;
    Person tmp       = Person(name, age);
    std::cout << std::hex;
    std::cout << &tmp << std::endl;  // 0000002714EFFC80
    return tmp;
  }
  Person(Person const& src) {
    name_ = src.name_;
    age_  = src.age_;
    std::cout << "copy constructor" << std::endl;
  }
  Person& operator=(Person const& src) {
    name_ = src.name_;
    age_  = src.age_;
    std::cout << "assignment operator" << std::endl;
    return *this;
  }
};

int main() {
  Person p1("xiaoming", 20);
  Person p2("xiaozhang", 30);
  Person p3 = p2.Merge(p1);
  std::cout << std::hex;
  std::cout << &p3 << std::endl;  // 0000002714EFFC80    由两者输出可知  clang编译器在对象值传递返回时做了右值优化
  std::cout << p3.name_ << std::endl;
  std::cout << p3.age_ << std::endl;
}

```

### 类型转换

```cpp {.line-numbers, highlight=[5, 44, 78, 100]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//静态转换
//基础类型

void test01()
{
 char a = 'a';

 double d = static_cast<double>(a);

 cout << "d = " << d <<endl;
}

//父子之间转换
class Base{};
class Child :public Base{};
class Other{};
void test02()
{
 Base * base = NULL;
 Child * child = NULL;

 //把base转为 Child*类型 向下  不安全
 Child * child2 = static_cast<Child*>(base);

 //把child 转为 Base*  向上  安全
 Base * base2 = static_cast<Base*>(child);

 //转other类型 转换无效
 //Other * other = static_cast<Other*>(base);
}

//static_cast使用   static_cast<目标类型>(原始对象)

// 动态转换

void test03()
{
 //基础类型不可以转换
 char c = 'a';
 //dynamic_cast非常严格，失去精度 或者不安全都不可以转换
 //double d = dynamic_cast<double>(c);

}

class Base2
{
 virtual void func(){};
};
class Child2 :public Base2
{
 virtual void func(){};
};
class Other2{};

void test04()
{
 Base2 * base = NULL;
 Child2 * child = NULL;

 //child转Base2 *  安全
 Base2 * base2 = dynamic_cast<Base2*>(child);


 //base 转Child2 * 不安全
 //Child2 * child2 = dynamic_cast<Child2*>(base);

 //dynamic_cast 如果发生了多态，那么可以让基类转为派生类 ，向下转换
 Base2 * base3 = new Child2;
 Child2 * child3 = dynamic_cast<Child2*>(base3);

}


// 常量转换(const_cast)
void test05()
{
 const int * p = NULL;
 //取出const
 int * newp = const_cast<int *>(p);

 int * p2 = NULL;
 const int * newP2 = const_cast<const int *>(p2);


 //不能对非指针 或 非引用的 变量进行转换
 //const int a = 10;
 //int b = const_cast<int>(a);

 //引用
 int num = 10;
 int &numRef = num;

 const int &numRef2 = static_cast<const int &>(numRef);
}

//重新解释转换(reinterpret_cast)
void test06()
{
 int a = 10;
 int * p = reinterpret_cast<int *>(a);


 Base * base = NULL;
 Other * other = reinterpret_cast<Other*>(base);

 //最不安全 ，不推荐

}






int main(){

 test01();

 system("pause");
 return EXIT_SUCCESS;
}

```

### 异常的基本处理

```cpp {.line-numbers, highlight=[5, 35, 41, 47, 68, 82, 109]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class myException //自定义异常类
{
public:
 void printError()
 {
  cout << "自定义的异常" << endl;
 }
};

class Person
{
public:
 Person()
 {
  cout << "Person构造" << endl;
 }
 ~Person()
 {
  cout << "Person析构" << endl;
 }

};

int myDevide(int a ,int b)
{
 if (b == 0)
 {
  //如果b是异常 抛出异常
  //return -1;

  //throw 1; 抛出int类型异常
  //throw 3.14; //抛出double类型异常  异常必须处理，如果不处理 就挂掉

  //throw 'a';
  
  //栈解旋
  //从try开始  到 throw 抛出异常之前  所有栈上的对象 都会被释放 这个过程称为栈解旋
  //构造和析构顺序相反
  Person p1;
  Person p2;


  throw myException(); //匿名对象

 }
 return a / b;
}



void test01()
{
 int a = 10;
 int b = 0;

 //int ret = myDevide(a, b); //早期如果返回-1 无法区分到底是结果还是异常

 //C++中异常处理

 try //试一试
 {
  myDevide(a, b);
 }
 catch (int) //捕获异常
 {
  cout << "int类型异常捕获" << endl;
 }
 catch (double)
 {
  //如果不想处理这个异常 ，可以继续向上抛出
  throw;
  cout << "double类型异常捕获" << endl;
 }
 catch (myException e)
 {
  e.printError();
 }
 catch (...)
 {
  cout << "其他类型异常捕获" << endl;
 }

}


int main(){

 try
 {
  test01();
 }
 catch (char ) //如果异常都没有处理，那么成员terminate函数，使程序中断
 {
  cout << "main 函数中 double类型异常捕获" << endl;
 }
 catch (...)
 {
  cout << "main函数中 其他类型异常捕获" << endl;
 }
 

 system("pause");
 return EXIT_SUCCESS;
}
// 若没有处理异常的代码，则执行terminate函数，其调用aborb()函数进行程序报错

```

### 异常接口声明

```cpp {.line-numbers, highlight=[4]}
#include <exception>
#include <iostream>

void func() throw(char, int) {    // 异常接口声明，方便调用者捕获异常
  std::cout << "start" << std::endl;
  throw 1;
}

int main() {
  try {
    func();
  } catch (int) {
    std::cout << "catch" << std::endl;
  }
}

```

### 异常的生命周期

```cpp {.line-numbers, highlight=[43, 48, 52]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class MyException
{
public:
 MyException()
 {
  cout << "MyException的默认构造" << endl;
 }
 MyException(const MyException & e)
 {
  cout << "MyException的拷贝构造" << endl;
 }

 ~MyException()
 {
  cout << "MyException的析构调用" << endl;
 }

 void printError()
 {
  this->m_A = 100;
  cout << "error"  << m_A<< endl;
 }

 int m_A;

};

void doWork()
{
 throw  &MyException();
}

void test01()
{
 try
 {
  doWork();
 }
 catch (MyException *e) //MyException e，会多开销一份数据，会调用拷贝构造; MyException& e,推荐使用
 {
  
  //e->printError();
  //e->printError();
  //e->printError(); //指向非法内存空间，不应该这么做  此时throw &MyException()，可以认为此时栈上异常临时对象内存销毁，所以指向了非法内存空间

  cout << "捕获异常" << endl;

  //delete e; //靠自觉 释放对象  若throw new MyExcption()  需手动delete
 }

}


int main(){


 test01();

 system("pause");
 return EXIT_SUCCESS;
}

```

### 异常的多态使用

```cpp
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//异常基类
class BaseException
{
public:
 virtual void printError()
 {
 }
};

class  NullPointerException:public BaseException
{
public:
 virtual void printError()
 {
  cout << "空指针异常" << endl;
 }
};

class OutofRangeException:public BaseException
{
public:
 virtual void printError()
 {
  cout << "越界异常" << endl;
 }

};


void doWork()
{
 //throw NullPointerException();

 throw OutofRangeException();
}


void test01()
{
 try
 {
  doWork();
 }
 catch (BaseException & e)
 {
  e.printError();
 }

}


int main(){

 test01();

 system("pause");
 return EXIT_SUCCESS;
}

```

### 使用系统提供的标准异常

```cpp
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <string>
using namespace std;
//系统提供标准异常 要包含头文件
#include <stdexcept>


class Person
{
public:
 Person(string name, int age)
 {
  this->m_Name = name;
  //年龄做检测

  if (age < 0 || age > 200)
  {
   //抛出越界异常
   //throw  out_of_range("年龄越界了！");

   throw length_error("长度越界");
  }

 }


 string m_Name;
 int m_Age;
};

void test01()
{
 try
 {
  Person p("张三",300);
 }
 catch (out_of_range & e)
 {
  cout << e.what() << endl;
 }
 catch (length_error & e)
 {
  cout << e.what() << endl;
 }

}


int main(){

 test01();

 system("pause");
 return EXIT_SUCCESS;
}

```

### 自己编写异常类

```cpp {.line-numbers, highlight=[23]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <string>

class MyOutOfRangeException:public exception
{

public:

 MyOutOfRangeException(string errorInfo)
 {
  this->m_ErrorInfo = errorInfo;
 }

 virtual  ~MyOutOfRangeException( )
 {

 }
 virtual const char *  what() const
 {
  //返回 错误信息
  //string 转 char *     .c_str()
  return this->m_ErrorInfo.c_str();
 }
 string m_ErrorInfo;
};
class Person
{
public:
 Person(string name, int age)
 {
  this->m_Name = name;
  //年龄做检测

  if (age < 0 || age > 200)
  {
   throw MyOutOfRangeException( string("我自己的年龄越界异常"));
  }
 }
 string m_Name;
 int m_Age;
};

void test01()
{
 try
 {
  Person p("张三", 300);
 }
 catch ( MyOutOfRangeException & e  )
 {
  cout << e.what() << endl;
 }
}

int main(){

 test01();

 system("pause");
 return EXIT_SUCCESS;
}

```

### 标准输入流

```cpp {.line-numbers, highlight=[6-12, 17, 51, 70, 77, 89, 101, 155, 160, 163]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

/*
cin.get() //一次只能读取一个字符
cin.get(一个参数) //读一个字符
cin.get(两个参数) //可以读字符串
cin.getline()
cin.ignore()
cin.peek()
cin.putback()
*/

void test01()
{
 // 输入as   缓冲区中  a  s  换行    第一个拿  a  第二个 拿 s  第三次拿换行 第四次等待下次输入
 char c = cin.get();
 cout << "c = " << c << endl;

 c = cin.get();
 cout << "c = " << c << endl;

 c = cin.get();
 cout << "c = " << c << endl;

 c = cin.get();
 cout << "c = " << c << endl;

}

void test02()
{
 //cin.get(两个参数) //可以读字符串
 char buf[1024];
 cin.get(buf, 1024);

 char c = cin.get();

 if (c == '\n')
 {
  cout << "换行还在缓冲区" << endl;
 }
 else
 {
  cout << "换行不在缓冲区" << endl;
 }

 cout << buf << endl;
}
//cin.get(两个参数)读取字符串时，不会把换行符拿走，遗留在缓冲区中


//cin.getline()
void test03()
{
 char buf[1024];
 cin.getline(buf, 1024);

 char c = cin.get();
 if (c == '\n')
 {
  cout << "换行还在缓冲区" << endl;
 }
 else
 {
  cout << "换行不在缓冲区" << endl;
 }

 //cin.getline 把换行符读取，并且扔掉
}


// cin.ignore() 忽略
void test04()
{
 cin.ignore(2); //没有参数 代表忽略一个字符 ，带参数N，代表忽略N个字符

 char c =  cin.get();

 cout << "c = " << c << endl;

}


// cin.peek() 偷窥
void test05()
{
 //输入as  偷看一眼 a，然后再放回缓冲区 缓冲区中还是as
 char c = cin.peek();

 cout << "c = " << c << endl;

 c = cin.get();

 cout << "c = " << c << endl;

}


//cin.putback() 放回 放回到cin的缓冲区中
void test06()
{
 char c = cin.get();
 cin.putback(c);

 char buf[1024];

 cin.getline(buf,1024);
 cout << buf << endl;
}


//案例1  判断用户的是字符串 还是数字？
void test07()
{
 cout << "请输入一串数字或者字符串" << endl;

 //偷窥
 char c = cin.peek();

 if (c >= '0' && c <= '9')
 {
  int num;
  cin >> num;

  cout << "您输入是数字 ：数字为" << num << endl;
 }
 else
 { 
  char buf[1024];
  cin >> buf;

  cout << "您输入是字符串 ：字符串为" << buf << endl;
 }
}


//案例2 让用户输入 1 到 10 的数字 ，如果输入有误 重新输入 
void test08()
{
 int num;

 cout << "请输入一个1到10的数字：" << endl;

 while (true)
 {
  cin >> num;
  if (num > 0 && num <= 10)
  {
   cout << "输入的数字为" << num << endl;
   break;
  }
  //cout << "对不起，请重新输入" << endl;
  //重置标志位，标志位标志字符读取是否正确
  cin.clear();

  // 2015 版本的vs 下 用ignore 处理 cin.ignore(N);

  cin.sync(); //清空缓冲区


  //cout << "标志位: " << cin.fail() << endl; //标志位 0 正常的  1 不正常
 }


}



int main(){

 //test01();

 //test02();

 //test03();

 //test04();

 //test05();

 //test06();

 //test07();

 test08();

 system("pause");
 return EXIT_SUCCESS;
}

```

### 标准输出流

```cpp {.line-numbers, highlight=[3, 7-8, 26-35, 42-49]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <iomanip> //使用控制符的头文件
using namespace std;

/*
cout.put() //向缓冲区写字符
cout.write() //从buffer中写num个字节到当前输出流中。
*/

void test01()
{
// cout.put('a').put('b');


 char buf[1024] = "hellowrold";

 cout.write(buf, strlen(buf));

}

void test02()
{
 //通过流成员函数

 int number = 99;
 cout.width(20);
 cout.fill('*');
 cout.setf(ios::left); //设置格式  输入内容做对齐
 cout.unsetf(ios::dec); //卸载十进制
 cout.setf(ios::hex); //安装16进制
 cout.setf(ios::showbase); // 强制输出整数基数  0  0x
 cout.unsetf(ios::hex);
 cout.setf(ios::oct);
 cout << number << endl;

}

//控制符的方式显示
void test03(){

 int number = 99;
 cout << setw(20)
  << setfill('~')
  << setiosflags(ios::showbase) //基数
  << setiosflags(ios::left) //左对齐
  << hex // 十六进制
  << number
  << endl;
}


int main(){

 //test01();

 //test02();

 test03();

 system("pause");
 return EXIT_SUCCESS;
}

```

### 文件的读写操作

```cpp {.line-numbers, highlight=[7, 31]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
//文件读写头文件
#include <fstream>

//写文件
void test01()
{
 //以输出的方式打开文件
 //ofstream ofs("./test.txt", ios::out | ios::trunc);
 //后期指定打开方式
 
 ofstream ofs;
 ofs.open("./test.txt", ios::out | ios::trunc);
 //判断是否打开成功
 if ( !ofs.is_open())
 {
  cout << "打开失败" << endl;
 }

 ofs << "姓名：abc" << endl;
 ofs << "年龄：100" << endl;
 ofs << "性别：男" << endl;


 ofs.close();

}

//读文件
void test02()
{
 ifstream ifs;
 ifs.open("./test.txt", ios::in);

 //判断是否打开成功
 if (!ifs.is_open())
 {
  cout << "打开失败" << endl;
 }

 //第一种方式
 //char buf[1024];

 //while (ifs >>buf) //按行读取
 //{
 // cout << buf << endl;
 //}

 //第二种方式
 //char buf2[1024];

 //while (!ifs.eof()) //eof读到文件尾
 //{
 // ifs.getline(buf2, sizeof(buf2));
 // cout << buf2 << endl;
 //}

 //第三种 不推荐 按单个字符读取
 char c;
 while (  (c = ifs.get() ) != EOF) // EOF文件尾
 {
  cout << c;
 }

 ifs.close();

}



int main(){
 //test01();
 test02();

 system("pause");
 return EXIT_SUCCESS;
}

```

### STL基本概念

```cpp {.line-numbers, highlight=[1-5]}
// 六大组件：容器（class template），算法（function template），迭代器，仿函数，适配器，分配器，容器存储内容，算法通过迭代器进行容器内容操纵，仿函数根据不同策略使用算法，适配器可以修改仿函数，分配器分配容器存储空间，迭代器是容器和算法之间的桥梁
// STL让数据结构和算法分离，通过迭代器进行算法和数据结构的胶合
// 容器分为序列式容器（放进去和取出来顺序一致），关联式容器（放进去和取出来，不一定顺序相同，有key，value）
// 算法有质变算法（删除，移动等影响容器存储等），非质变算法（查找，遍历等不影响容器存储等算法）
// 迭代器设计是一种设计模式：为了能够依序访问容器元素，无需知道容器内部情况，可以看作是一种智能指针，提供有关的指针操作

```

![](/assets/images/2022-10-24-08-38-06.png)

### 容器算法迭代器初识

```cpp {.line-numbers, highlight=[42]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <vector> //vector容器的头文件
#include <algorithm> //系统标准算法头文件
#include <string>

//普通指针也是属于一种迭代器
void test01()
{
 int arr[5] = { 1, 5, 2, 7, 3 };
 int * p = arr;
 for (int i = 0; i < 5; i++)
 {
  //cout << arr[i] << endl;

  cout << *(p++) << endl;
 }
}

void myPrint(int val)
{
 cout << val << endl;
}

//内置属性类型
void test02()
{
 
 vector<int>v; //声明一个vector的容器 

 //想容器中添加数据
 v.push_back(10);
 v.push_back(20);
 v.push_back(30);
 v.push_back(40);

 //通过迭代器可以 遍历容器
 //每个容器都有自己专属的迭代器
 //vector<int>::iterator itBegin = v.begin(); //起始迭代器

 //vector<int>::iterator itEnd = v.end(); //结束迭代器 指向最后一个元素的下一个地址

 //第一种遍历方式
 //while (itBegin != itEnd)
 //{
 // cout << *itBegin << endl;
 // itBegin++;
 //}

 //第二种遍历方式
 //for (vector<int>::iterator it = v.begin(); it != v.end();it++)
 //{
 // cout << *it << endl;
 //}

 //第三种遍历方式  利用系统提供算法
 for_each(v.begin(), v.end(), myPrint);

}

//自定义数据类型
class Person
{
public:
 Person(string name, int age)
 {
  this->m_Name = name;
  this->m_Age = age;
 }
 string m_Name;
 int m_Age;
};
void test03()
{
 vector<Person> v;

 Person p1("aaa", 10);
 Person p2("bbb", 20);
 Person p3("ccc", 30);
 Person p4("ddd", 40);

 v.push_back(p1);
 v.push_back(p2);
 v.push_back(p3);
 v.push_back(p4);

 //遍历
 for (vector<Person>::iterator it = v.begin(); it != v.end();it++)
 {
  // *it --- Person类型    it  --- 指针
  cout << "姓名： " << (*it).m_Name << " 年龄： " << it->m_Age << endl;
 }
}

//存放自定义数据类型的指针
void test04()
{
 vector<Person*> v;

 Person p1("aaa", 10);
 Person p2("bbb", 20);
 Person p3("ccc", 30);
 Person p4("ddd", 40);

 v.push_back(&p1);
 v.push_back(&p2);
 v.push_back(&p3);
 v.push_back(&p4);

 for (vector<Person*>::iterator it = v.begin(); it != v.end(); it++)
 {
  //*it   ---  Person *
  cout << "姓名： " << (*it)->m_Name << " 年龄： " << (*it)->m_Age << endl;
 }
}

//容器嵌套容器
void test05()
{
 vector< vector<int> > v ;//类似二维数组

 vector<int>v1;
 vector<int>v2;
 vector<int>v3;

 for (int i = 0; i < 10;i++)
 {
  v1.push_back(i);
  v2.push_back(i + 10);
  v3.push_back(i + 100);
 }

 //将小容器 插入到大容器中
 v.push_back(v1);
 v.push_back(v2);
 v.push_back(v3);


 for (vector<vector<int>>::iterator it = v.begin(); it != v.end();it++)
 {
  //*it --- vector<int>
  for (vector<int>::iterator vit = (*it).begin(); vit != (*it).end();vit++)
  {
   //*vit  --- int
   cout << *vit << " ";
  }
  cout << endl;
 }
}

int main(){
 //test01();
 //test02();
 //test03();
 //test04();
 test05();
 system("pause");
 return EXIT_SUCCESS;
}

```

### String容器

```cpp {.line-numbers, highlight=[73]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <string>
#include <stdexcept>
#include <vector>
/*
3.1.2.1 string 构造函数
string();//创建一个空的字符串 例如: string str;
string(const string& str);//使用一个string对象初始化另一个string对象
string(const char* s);//使用字符串s初始化
string(int n, char c);//使用n个字符c初始化

3.1.2.2 string基本赋值操作
string& operator=(const char* s);//char*类型字符串 赋值给当前的字符串
string& operator=(const string &s);//把字符串s赋给当前的字符串
string& operator=(char c);//字符赋值给当前的字符串
string& assign(const char *s);//把字符串s赋给当前的字符串
string& assign(const char *s, int n);//把字符串s的前n个字符赋给当前的字符串
string& assign(const string &s);//把字符串s赋给当前字符串
string& assign(int n, char c);//用n个字符c赋给当前字符串
string& assign(const string &s, int start, int n);//将s从start开始n个字符赋值给字符串
*/

void test01()
{
 //构造
 string s1;
 string s2(s1); //拷贝构造
 string s3("aaa"); //有参构造
 string s4(10, 'c'); //两个参数 有参构造

 cout << s3 << endl;
 cout << s4 << endl;


 //赋值
 string s5;
 s5 = s4;
 //string& assign(const char *s, int n);//把字符串s的前n个字符赋给当前的字符串
 s5.assign("abcdefg", 3);
 cout << "s5 = " << s5 << endl;


 //string& assign(const string &s, int start, int n);//将s从start开始n个字符赋值给字符串
 // 从0开始计算
 string s6 = "abcdefg";
 string s7;
 s7.assign(s6, 3, 3);
 cout << "s7 =" << s7 << endl;


}



/*
3.1.2.3 string存取字符操作
char& operator[](int n);//通过[]方式取字符
char& at(int n);//通过at方法获取字符
*/

void test02()
{
 string s = "hello world";

 //for (int i = 0; i < s.size();i++)
 //{
 // //cout << s[i] << endl;
 // cout << s.at(i) << endl;
 //}
  
 //at 和 [] 区别   []访问越界 直接挂掉  而  at访问越界 会抛出一个 异常 out_of_range

 try
 {
  //s[100];
  s.at(100);
 }
 catch (exception &e)
 {
  cout << e.what() << endl;
 }

}


/*
3.1.2.4 string拼接操作
string& operator+=(const string& str);//重载+=操作符
string& operator+=(const char* str);//重载+=操作符
string& operator+=(const char c);//重载+=操作符
string& append(const char *s);//把字符串s连接到当前字符串结尾
string& append(const char *s, int n);//把字符串s的前n个字符连接到当前字符串结尾
string& append(const string &s);//同operator+=()
string& append(const string &s, int pos, int n);//把字符串s中从pos开始的n个字符连接到当前字符串结尾
string& append(int n, char c);//在当前字符串结尾添加n个字符c

3.1.2.5 string查找和替换
int find(const string& str, int pos = 0) const; //查找str第一次出现位置,从pos开始查找
int find(const char* s, int pos = 0) const;  //查找s第一次出现位置,从pos开始查找
int find(const char* s, int pos, int n) const;  //从pos位置查找s的前n个字符第一次位置
int find(const char c, int pos = 0) const;  //查找字符c第一次出现位置
int rfind(const string& str, int pos = npos) const;//查找str最后一次位置,从pos开始查找
int rfind(const char* s, int pos = npos) const;//查找s最后一次出现位置,从pos开始查找
int rfind(const char* s, int pos, int n) const;//从pos查找s的前n个字符最后一次位置
int rfind(const char c, int pos = 0) const; //查找字符c最后一次出现位置
string& replace(int pos, int n, const string& str); //替换从pos开始n个字符为字符串str
string& replace(int pos, int n, const char* s); //替换从pos开始的n个字符为字符串s
*/

void test03()
{
 //字符串拼接
 string  str1 = "我";
 string str2 = "爱北京";

 str1 += str2;

 cout << str1 << endl;


 string str3 = "天安门";

 str1.append(str3);

 cout << str1 << endl;


 //字符串查找
 string str4 = "abcdefghide";
 int pos = str4.find("de"); //如果找不到子串 返回 -1 ，找到返回第一次出现的位置
 //rfind从右往左查找
 //第二个参数 是默认起始查找的位置  默认是0
 cout << "pos = " << pos << endl;

 //string& replace(int pos, int n, const string& str); //替换从pos开始n个字符为字符串str
 str4.replace(1, 3, "111111"); // a111111efg..
 cout << "str4 " << str4 << endl;
 
}


/*
3.1.2.6 string比较操作
compare函数在>时返回 1，<时返回 -1，==时返回 0。
比较区分大小写，比较时参考字典顺序，排越前面的越小。
大写的A比小写的a小。
int compare(const string &s) const;//与字符串s比较
int compare(const char *s) const;//与字符串s比较
*/

void test04()
{

 string str1 = "bbcde";
 string str2 = "abcdeff";

 if (str1.compare(str2) == 0)
 {
  cout << "str1 == str2 " << endl;
 }
 else if (str1.compare(str2) > 0)
 {
  cout << "str1 > str2 " << endl;
 }
 else
 {
  cout << "str1 < str2 " << endl;
 }
}

/*
3.1.2.7 string子串
string substr(int pos = 0, int n = npos) const;//返回由pos开始的n个字符组成的字符串
*/
void test05()
{
 //string str = "abcde";
 //string subStr = str.substr(1, 3);
 //cout << subStr << endl; // bcd


 string email = "zhangtao@sina.com";
 int pos = email.find("@"); // 8
 string userName = email.substr(0, pos);

 cout << userName << endl;
}

void test06()
{
 string str = "www.itcast.com.cn";

 //需求：  将 网址中的每个单词 都截取到 vector容器中
 vector<string>v;

 // www   itcast   com  cn

 int start = 0;

 while (true)
 {
  //www.itcast.com.cn
  int pos = str.find(".",start);

  if (pos == -1)
  {
   //将最后一个单词截取
   string tmp = str.substr(start, str.size() - start);
   v.push_back(tmp);
   break;
  }

  string tmp = str.substr(start, pos- start);

  v.push_back(tmp);

  start = pos + 1;
 }

 
 for (vector<string>::iterator it = v.begin(); it != v.end();it++)
 {
  cout << *it << endl;
 }
}

/*
3.1.2.8 string插入和删除操作
string& insert(int pos, const char* s); //插入字符串
string& insert(int pos, const string& str); //插入字符串
string& insert(int pos, int n, char c);//在指定位置插入n个字符c
string& erase(int pos, int n = npos);//删除从Pos开始的n个字符
*/
void test07()
{
 string str = "hello";
 str.insert(1, "111");

 cout << "str = " << str << endl; // h111ello


 //利用erase  删除掉 111
 str.erase(1, 3);
 cout << "str = " << str << endl;
}

/*
string和c-style字符串转换
*/

void doWork(string s)
{
}

void doWork2(const char * s)
{
}

void test08()
{
 //char *  ->string
 char * str = "hello";
 string s(str);


 // string -> char *
 const char * str2 =  s.c_str();

 doWork(str2); //编译器将  const char*  可以隐式类型转换为  string

 //doWork2(s); //编译器 不会 将 string 隐式类型转换为 const char *
}


void test09()
{
 string s = "abcdefg";
 char& a = s[2];
 char& b = s[3];

 a = '1';
 b = '2';

 cout << s << endl;
 cout << (int*)s.c_str() << endl;

 s = "pppppppppppppppppppppppp";

 //a = '1'; //原来a和b的指向就失效了
 //b = '2';

 cout << s << endl;
 cout << (int*)s.c_str() << endl;

}

/*
写一个函数，函数内部将string字符串中的所有小写字母都变为大写字母。
*/
void test10()
{
 string str = "abCDeFg";

 for (int i = 0; i < str.size();i++)
 {
  //小写转大写
  //str[i] = toupper(str[i]);

  //大写转小写
  str[i] = tolower(str[i]);

 }
 cout << str << endl;
}

int main(){
 //test01();
 //test02();
 //test03();
 //test04();
 //test05();
 //test06();
 //test07();
 //test09();
 test10();

 system("pause");
 return EXIT_SUCCESS;
}

```

### Vector容器

```cpp {.line-numbers, highlight=[1, 167, 217, 232]}
// vector容量不够时，会开辟新空间（因为不能保证原始空间的后面不被使用），并把数据拷贝到新空间，所以原有迭代器就失效了

#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <vector>
#include <list>


void test01()
{
 vector<int> v;
 for (int i = 0; i < 10; i++){
  v.push_back(i);
  cout << v.capacity() << endl;  // v.capacity()容器的容量
 }
}



/*
3.2.4.1 vector构造函数
vector<T> v; //采用模板实现类实现，默认构造函数
vector(v.begin(), v.end());//将v[begin(), end())区间中的元素拷贝给本身。
vector(n, elem);//构造函数将n个elem拷贝给本身。
vector(const vector &vec);//拷贝构造函数。

//例子 使用第二个构造函数 我们可以...
int arr[] = {2,3,4,1,9};
vector<int> v1(arr, arr + sizeof(arr) / sizeof(int));

3.2.4.2 vector常用赋值操作
assign(beg, end);//将[beg, end)区间中的数据拷贝赋值给本身。
assign(n, elem);//将n个elem拷贝赋值给本身。
vector& operator=(const vector  &vec);//重载等号操作符
swap(vec);// 将vec与本身的元素互换。
*/
void printVector(vector<int>&v)
{
 for (vector<int>::iterator it = v.begin(); it != v.end();it++)
 {
  cout << *it << " ";
 }
 cout << endl;
}

void test02()
{
 //构造
 vector<int>v1;

 vector<int>v2(10, 100);
 printVector(v2);

 vector<int>v3(v2.begin(), v2.end());
 printVector(v3);


 //赋值
 vector<int>v4;
 //v4.assign(v3.begin(), v3.end());
 v4 = v3;
 printVector(v4);

 int arr[] = { 2, 3, 4, 1, 9 };
 vector<int> v5(arr, arr + sizeof(arr) / sizeof(int));


 //swap交换
 v4.swap(v5);
 printVector(v4);

}


/*
3.2.4.3 vector大小操作
size();//返回容器中元素的个数
empty();//判断容器是否为空
resize(int num);//重新指定容器的长度为num，若容器变长，则以默认值填充新位置。如果容器变短，则末尾超出容器长度的元素被删除。
resize(int num, elem);//重新指定容器的长度为num，若容器变长，则以elem值填充新位置。如果容器变短，则末尾超出容器长>度的元素被删除。
capacity();//容器的容量
reserve(int len);//容器预留len个元素长度，预留位置不初始化，元素不可访问。

3.2.4.4 vector数据存取操作
at(int idx); //返回索引idx所指的数据，如果idx越界，抛出out_of_range异常。
operator[];//返回索引idx所指的数据，越界时，运行直接报错
front();//返回容器中第一个数据元素
back();//返回容器中最后一个数据元素

3.2.4.5 vector插入和删除操作
insert(const_iterator pos, int count,ele);//迭代器指向位置pos插入count个元素ele.
push_back(ele); //尾部插入元素ele
pop_back();//删除最后一个元素
erase(const_iterator start, const_iterator end);//删除迭代器从start到end之间的元素
erase(const_iterator pos);//删除迭代器指向的元素
clear();//删除容器中所有元素
*/

void test03()
{
 vector<int>v1;
 v1.push_back(10);
 v1.push_back(40);
 v1.push_back(20);
 v1.push_back(30);

 cout << "size = " << v1.size() << endl;

 if (v1.empty())
 {
  cout << "v1为空" << endl;
 }
 else
 {
  cout << "v1不为空" << endl;
 }

 //重新指定容器长度  resize
 v1.resize(10,1000); //第二个参数是默认填充的值，如果不写默认值为0

 printVector(v1);

 v1.resize(3);

 printVector(v1);


 cout << "v1的第一个元素： " << v1.front() << endl;

 cout << "v1的最后一个元素： " << v1.back() << endl;

 v1.insert(v1.begin(), 2,1000); //参数1 是迭代器
 //  1000  1000  10  40  20
 printVector(v1);

 v1.pop_back(); //尾删
 //  1000  1000  10  40  
 printVector(v1);

 //删除
 //v1.erase(v1.begin() , v1.end());
 //清空
 v1.clear();
 printVector(v1);

}


//巧用swap收缩内存
void test04()
{
 vector<int>v;
 for (int i = 0; i < 100000;i++)
 {
  v.push_back(i);
 }
 cout << "v的容量： " << v.capacity() << endl;
 cout << "v的大小： " << v.size() << endl;

 v.resize(3);

 cout << "v的容量： " << v.capacity() << endl;
 cout << "v的大小： " << v.size() << endl;

 //收缩内存
 vector<int>(v).swap(v);      // 初始化匿名对象时，根据size初始化，swap是交换指针
 cout << "v的容量： " << v.capacity() << endl;
 cout << "v的大小： " << v.size() << endl;

}


//巧用reverse预留空间
void test05()
{
 vector<int>v;

 v.reserve(100000);

 int num = 0;
 int * p = NULL;

 for (int i = 0; i < 100000; i++)
 {
  v.push_back(i);
  if (p != &v[0])
  {
   p = &v[0];
   num++;
  }
 }

 cout << "num = " << num << endl;
}


void test06()
{
 //逆序遍历
 vector<int>v1;
 v1.push_back(10);
 v1.push_back(40);
 v1.push_back(20);
 v1.push_back(30);
 cout << "正序遍历结果： " << endl;
 printVector(v1);

 cout << "逆序遍历结果： " << endl;

 for (vector<int>::reverse_iterator it = v1.rbegin(); it != v1.rend();it++)
 {
  cout << *it << endl;
 }


 // vector容器的迭代器  随机访问迭代器
 //如何判断一个容器的迭代器是否支持随机访问

 vector<int>::iterator itBegin = v1.begin();

 itBegin = itBegin + 2; //如果语法通过 支持随机访问



 list<int>L;
 L.push_back(10);
 L.push_back(20);
 L.push_back(30);

 list<int>::iterator it2 = L.begin();
 //it2 = it2+1; //list容器的迭代器不支持随机访问
}


int main(){

 //test01();
 //test02();
 //test03();
 //test04();
 //test05();
 test06();

 system("pause");
 return EXIT_SUCCESS;
}

```

![](/assets/images/2022-10-24-13-28-39.png)

![](/assets/images/2022-10-24-13-57-42.png)

#### test

```cpp {.line-numbers, highlight=[6, 10, 18]}
#include <iostream>
#include <stdexcept>
#include <vector>

int main() {
  std::vector<int> vec(10);  // 指定容量后，vector对象被初始化0值，所以size和capacity都为10；
  std::cout << vec.size() << std::endl;
  std::cout << vec.capacity() << std::endl;
  std::cout << "-------------------" << std::endl;
  std::vector<int> vec1;  // 默认构造，vector对象size和capacity都为0，之后加入元素后进行capacity扩容和size随着元素增加
  vec1.push_back(20);
  vec1.push_back(20);
  vec1.push_back(20);
  vec1.push_back(20);
  vec1.push_back(20);
  std::cout << vec1.size() << std::endl;
  std::cout << vec1.capacity() << std::endl;
  std::vector<int>::reverse_iterator iter = vec1.rbegin();  // 返回反向迭代器，<---- 为正方向 *(iter+1)
  std::cout << *iter << std::endl;
  std::cout << *(iter - 1) << std::endl;
}

```

### Deque容器

```cpp {.line-numbers, highlight=[158]}
// 双端容器，头插元素只需常数时间复杂度，实现原理是有有一个中控器，所以无需拷贝旧值
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <deque>
#include <algorithm>

/*
3.3.3.1 deque构造函数
deque<T> deqT;//默认构造形式
deque(beg, end);//构造函数将[beg, end)区间中的元素拷贝给本身。
deque(n, elem);//构造函数将n个elem拷贝给本身。
deque(const deque &deq);//拷贝构造函数。

3.3.3.2 deque赋值操作
assign(beg, end);//将[beg, end)区间中的数据拷贝赋值给本身。
assign(n, elem);//将n个elem拷贝赋值给本身。
deque& operator=(const deque &deq); //重载等号操作符
swap(deq);// 将deq与本身的元素互换

3.3.3.3 deque大小操作
deque.size();//返回容器中元素的个数
deque.empty();//判断容器是否为空
deque.resize(num);//重新指定容器的长度为num,若容器变长，则以默认值填充新位置。如果容器变短，则末尾超出容器长度的元素被删除。
deque.resize(num, elem); //重新指定容器的长度为num,若容器变长，则以elem值填充新位置,如果容器变短，则末尾超出容器长度的元素被删除。
*/

void printDeque(const deque<int>&d)
{

 // iterator 普通迭代器
 // reverse_iterator 反转迭代器
 // const_iterator   只读迭代器
 for (deque<int>::const_iterator it = d.begin(); it != d.end();it++)
 {
  //*it = 10000;
  cout << *it << " ";
 }
 cout << endl;
}

void test01()
{
 deque<int>d;
 d.push_back(10);
 d.push_back(30);
 d.push_back(20);
 d.push_back(40);

 printDeque(d);

 deque<int>d2(10, 10);

 d.swap(d2);

 printDeque(d);

 if (d.empty())
 {
  cout << "d为空" << endl;
 }
 else
 {
  cout << "d不为空--size = " << d.size() << endl;
 }

}

/*
3.3.3.4 deque双端插入和删除操作
push_back(elem);//在容器尾部添加一个数据
push_front(elem);//在容器头部插入一个数据
pop_back();//删除容器最后一个数据
pop_front();//删除容器第一个数据

3.3.3.5 deque数据存取
at(idx);//返回索引idx所指的数据，如果idx越界，抛出out_of_range。
operator[];//返回索引idx所指的数据，如果idx越界，不抛出异常，直接出错。
front();//返回第一个数据。
back();//返回最后一个数据
3.3.3.6 deque插入操作
insert(pos,elem);//在pos位置插入一个elem元素的拷贝，返回新数据的位置。
insert(pos,n,elem);//在pos位置插入n个elem数据，无返回值。
insert(pos,beg,end);//在pos位置插入[beg,end)区间的数据，无返回值。
3.3.3.7 deque删除操作
clear();//移除容器的所有数据
erase(beg,end);//删除[beg,end)区间的数据，返回下一个数据的位置。
erase(pos);//删除pos位置的数据，返回下一个数据的位置。
*/

void test02()
{
 deque<int>d;
 d.push_back(10);
 d.push_back(20);
 d.push_back(30);
 d.push_back(40);
 d.push_front(100);
 d.push_front(200);
 d.push_front(300);
 d.push_front(400);

 printDeque(d); //   400 300 200 100 10 20 30 40

 d.pop_back(); //删除  40
 d.pop_front(); // 删除 400

 printDeque(d); //    300 200 100 10 20 30 


 cout << "第一个元素： " << d.front() << endl;


 cout << "最后一个元素： " << d.back() << endl;

 //插入 

 d.insert(++d.begin(), 10000);

 cout << "d.begin()" << &(d.begin()) << endl;
 cout << "++d.begin()" << &(++d.begin())<< endl;
 //cout << "1+d.begin()" << &(1+d.begin()) << endl;
 //cout << "4+d.begin()" << &(4 + d.begin()) << endl;
 cout << "++d.begin() - d.begin()" << &(1 + d.begin())  - &(d.begin()) << endl;

 printDeque(d);  //    300  10000 200 100 10 20 30 


 //删除 
 d.erase(++d.begin(),--d.end()); //删除区间  10000 到 20的区间都删除掉

 printDeque(d);


}

bool myCompare(int v1 ,int v2)
{
 return v1 > v2; //降序
}

void test03()
{
 //利用sort排序
 deque<int>d;
 d.push_back(10);
 d.push_back(20);
 d.push_back(30);
 d.push_back(40);
 d.push_front(100);
 d.push_front(200);
 d.push_front(300);
 d.push_front(400);

 //默认排序规则从小到大
 sort(d.begin(), d.end());

 //从大到小排序
 sort(d.begin(), d.end(), myCompare);   // 传入回调函数或者仿函数，进行自定义比较规则，确定了仿函数可以改变算法规则

 printDeque(d);
}

int main(){
 //test01();
 //test02();
 test03();

 system("pause");
 return EXIT_SUCCESS;
}

```

![](/assets/images/2022-10-24-15-46-53.png)

![](/assets/images/2022-10-24-15-49-20.png)

![](/assets/images/2022-10-24-16-43-21.png)

#### test

```cpp {.line-numbers, highlight=[33, 48-49]}
#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>

class Person {
 public:
  int score_;
  Person(int score = 0) : score_(score) {
    std::cout << "construct" << std::endl;
  }
  Person(Person const& src) {
    score_ = src.score_;
    std::cout << "copy construct" << std::endl;
  }
  ~Person() {
    std::cout << "xiaohui" << std::endl;
  }
};

template <typename T>
void PrintVector(T& src) {
  for (auto it = src.begin(); it != src.end(); ++it) {
    std::cout << (*it).score_ << std::endl;
  }
}

int main() {
  std::vector<Person> vec;
  for (int i = 0; i < 5; ++i) {
    Person p1(i);
    vec.push_back(
        p1);  // 为什么多次析构不报错，而且析构完后操作系统标记这块内存被重新分配??????????????????????????????
    std::cout << vec.capacity() << std::endl;
  }
  std::cout << vec.size() << std::endl;
  PrintVector(vec);
  std::cout << "-------------------" << std::endl;
}

// construct
// copy construct
// xiaohui
// construct
// copy construct
// copy construct
// xiaohui
// xiaohui          // 在于扩容后是直接进行拷贝，并且把原有的析构掉，for循环中的定义的变量，脱离for循环就行销毁
// construct        // 扩容  0 1 2 4 8
// copy construct
// copy construct
// copy construct
// xiaohui
// xiaohui
// xiaohui
// construct
// copy construct
// xiaohui
// construct
// copy construct
// copy construct
// copy construct
// copy construct
// copy construct
// xiaohui
// xiaohui
// xiaohui
// xiaohui
// xiaohui
// 5
// 0
// 1
// 2
// 3
// 4
// -------------------
// xiaohui
// xiaohui
// xiaohui
// xiaohui
// xiaohui

```

### 评委打分设计

```cpp

/*
 create by zhangtao 
 date : 2018 3 16
 createPerson( vector<Person>&v )  创建5名选手，参数1：...
*/

#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <vector>
#include <string>
#include <deque>
#include <algorithm>
#include <ctime>

/*
有5名选手：选手ABCDE，10个评委分别对每一名选手打分，去除最高分，去除评委中最低分，取平均分。
//1. 创建五名选手，放到vector中
//2. 遍历vector容器，取出来每一个选手，执行for循环，可以把10个评分打分存到deque容器中
//3. sort算法对deque容器中分数排序，pop_back pop_front去除最高和最低分
//4. deque容器遍历一遍，累加分数，累加分数/d.size()
//5. person.score = 平均分
*/


class Person
{
public:
 
 Person(string name, int score)
 {
  this->m_Name = name;
  this->m_Score = score;
 }

 string m_Name; //姓名
 int m_Score;   //平均分
};

void createPerson(vector<Person>&v)
{
 string nameSeed = "ABCDE";
 for (int i = 0; i < 5; i++)
 {
  string name = "选手";
  name += nameSeed[i];

  int score = 0;

  Person p(name, score);
  v.push_back(p);
 }
}

void setScore(vector<Person>&v)
{
 for (vector<Person>::iterator it = v.begin(); it != v.end();it++)
 {
  //有10个评委给每个人打分
  deque<int>d; //存放评委打分容器
  for (int i = 0; i < 10;i++)
  {
   int score = rand() % 41 + 60;  // 60 ~ 100
   d.push_back(score);
  }

  //cout << "选手： " << it->m_Name << "的打分情况： " << endl;
  //for (deque<int>::iterator dit = d.begin(); dit != d.end(); dit++)
  //{
  // cout << *dit << " ";
  //}
  //cout << endl;


  //排序  从小到大排序
  sort(d.begin(), d.end());

  //去除 最高分 和 最低分
  d.pop_back(); // 最高
  d.pop_front(); //最低

  //获取总分
  int sum = 0;
  for (deque<int>::iterator dit = d.begin(); dit != d.end(); dit++)
  {
   sum += *dit;
  }

  //获取平均分
  int avg = sum / d.size();

  it->m_Score = avg;
 }


}


void showScore(vector<Person>&v)
{
 for (vector<Person>::iterator it = v.begin(); it != v.end(); it++)
 {
  cout << "姓名： " << it->m_Name << " 平均分数： " << it->m_Score << endl;
 }
}

int main(){

 //设置随机数种子
 srand((unsigned int)time(NULL));

 //1、存放选手容器
 vector<Person> v; 
 //2、创建五名选手
 createPerson(v);
 //3、打分
 setScore(v);
 //4、显示得分
 showScore(v);


 ////测试
 //for (vector<Person>::iterator it = v.begin(); it != v.end(); it++)
 //{
 // cout << "姓名： " << it->m_Name << " 分数： " << it->m_Score << endl;
 //}

 system("pause");
 return EXIT_SUCCESS;
}

```

### Stack容器

```cpp {.line-numbers, highlight=[1]}
// 栈容器没有迭代器，也就是没有遍历行为
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <stack>

/*
3.4.3.1 stack构造函数
stack<T> stkT;//stack采用模板类实现， stack对象的默认构造形式：
stack(const stack &stk);//拷贝构造函数
3.4.3.2 stack赋值操作
stack& operator=(const stack &stk);//重载等号操作符
3.4.3.3 stack数据存取操作
push(elem);//向栈顶添加元素
pop();//从栈顶移除第一个元素
top();//返回栈顶元素
3.4.3.4 stack大小操作
empty();//判断堆栈是否为空
size();//返回堆栈的大小
*/

void test01()
{
 stack<int> s;

 //入栈 
 s.push(10);
 s.push(20);
 s.push(30);
 s.push(40);

 while (!s.empty())
 {
  //输出栈顶元素
  cout << s.top() << endl;

  //弹出栈顶元素
  s.pop();
 }
 cout << "栈的大小： " << s.size() << endl;

}


int main() {

 test01();

 system("pause");
 return EXIT_SUCCESS;
}

```

### Queue容器

```cpp {.line-numbers, highlight=[1]}
// queue容器没有迭代器，也就没有遍历行为
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <queue>
#include <string>
/*
3.5.3.1 queue构造函数
queue<T> queT;//queue采用模板类实现，queue对象的默认构造形式：
queue(const queue &que);//拷贝构造函数
3.5.3.2 queue存取、插入和删除操作
push(elem);//往队尾添加元素
pop();//从队头移除第一个元素
back();//返回最后一个元素
front();//返回第一个元素

3.5.3.3 queue赋值操作
queue& operator=(const queue &que);//重载等号操作符
3.5.3.4 queue大小操作
empty();//判断队列是否为空
size();//返回队列的大小
*/

class Person
{
public:
 Person(string name, int age) :m_Name(name), m_Age(age)
 {}

 string m_Name;
 int m_Age;
};

void test01()
{
 queue<Person>Q;

 Person p1("aaa",10);
 Person p2("bbb", 20);
 Person p3("ccc", 30);
 Person p4("ddd", 40);

 //入队
 Q.push(p1);
 Q.push(p2);
 Q.push(p3);
 Q.push(p4);

 while ( !Q.empty())
 {
  //获取队头元素
  Person pFront =  Q.front();
  cout << "队头元素 姓名： " << pFront.m_Name << " 年龄： " << pFront.m_Age << endl;

  //获取队尾元素
  Person pBack = Q.back();
  cout << "队尾元素 姓名： " << pBack.m_Name << " 年龄： " << pBack.m_Age << endl;

  //出队
  Q.pop();
 }

 cout << "队列的大小为： " << Q.size() << endl;

}

int main(){

 test01();

 system("pause");
 return EXIT_SUCCESS;
}

```

### List容器

```cpp {.line-numbers, highlight=[1, 176-177, 250]}
// 链表容器，底层不仅仅是双向链表还是循环的，插入，删除除迭代器之外的元素，并不会影响迭代器本身，不为随机访问迭代器
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <algorithm>
#include<list>
/*
list是一个双向循环链表
*/
/**/
//void test01()
//{
// list<int> myList;
// for (int i = 0; i < 10; i++){
//  myList.push_back(i);
// }
// list<int>::_Nodeptr node = myList._Myhead->_Next;    // 头节点不存入数据
// for (int i = 0; i < myList._Mysize * 2; i++){
//  cout << "Node:" << node->_Myval << endl;
//  node = node->_Next;
//  //node->_Prev 
//  if (node == myList._Myhead){
//   node = node->_Next;
//  }
// }
//}

/*
3.6.4.1 list构造函数
list<T> lstT;//list采用采用模板类实现,对象的默认构造形式：
list(beg,end);//构造函数将[beg, end)区间中的元素拷贝给本身。
list(n,elem);//构造函数将n个elem拷贝给本身。
list(const list &lst);//拷贝构造函数。
3.6.4.2 list数据元素插入和删除操作
push_back(elem);//在容器尾部加入一个元素
pop_back();//删除容器中最后一个元素
push_front(elem);//在容器开头插入一个元素
pop_front();//从容器开头移除第一个元素
insert(pos,elem);//在pos位置插elem元素的拷贝，返回新数据的位置。
insert(pos,n,elem);//在pos位置插入n个elem数据，无返回值。
insert(pos,beg,end);//在pos位置插入[beg,end)区间的数据，无返回值。
clear();//移除容器的所有数据
erase(beg,end);//删除[beg,end)区间的数据，返回下一个数据的位置。
erase(pos);//删除pos位置的数据，返回下一个数据的位置。
remove(elem);//删除容器中所有与elem值匹配的元素。
*/

void printList(const list<int>&L)
{
 for (list<int>::const_iterator it = L.begin(); it != L.end(); it++)
 {
  cout << *it << " ";
 }
 cout << endl;
}

//void test02()
//{
// list<int>L;
// list<int>L2(10, 10);
// list<int>L3(L2.begin(), L2.end());
//
//
// list <int>L4;
// L4.push_back(10);
// L4.push_back(20);
// L4.push_back(30);
// L4.push_front(100);
// L4.push_front(200);
// L4.push_front(300);
// //  300 200 100 10 20 30
// for (list<int>::iterator it = L4.begin(); it != L4.end();it++)
// {
//  cout << *it << " ";
// }
// cout << endl;
//
// //逆序打印
// for (list<int>::reverse_iterator it = L4.rbegin(); it != L4.rend();it++)
// {
//  cout << *it << " ";
// }
// cout << endl;
//
// L4.insert(L4.begin(), 1000); //插入参数是迭代器
//
//
// // 1000 300 200 100 10 20 30 
// printList(L4);
// L4.push_back(300);
// // 1000 300 200 100 10 20 30 300
//
// //remove(elem);//删除容器中所有与elem值匹配的元素。
// L4.remove(300);
// printList(L4);
//
//
//}

/*
3.6.4.3 list大小操作
size();//返回容器中元素的个数
empty();//判断容器是否为空
resize(num);//重新指定容器的长度为num，
若容器变长，则以默认值填充新位置。
如果容器变短，则末尾超出容器长度的元素被删除。
resize(num, elem);//重新指定容器的长度为num，
若容器变长，则以elem值填充新位置。
如果容器变短，则末尾超出容器长度的元素被删除。

3.6.4.4 list赋值操作
assign(beg, end);//将[beg, end)区间中的数据拷贝赋值给本身。
assign(n, elem);//将n个elem拷贝赋值给本身。
list& operator=(const list &lst);//重载等号操作符
swap(lst);//将lst与本身的元素互换。
3.6.4.5 list数据的存取
front();//返回第一个元素。
back();//返回最后一个元素。
*/

/*
void test03()
{
 list <int>L;
 L.push_back(10);
 L.push_back(20);
 L.push_back(30);
 L.push_front(100);
 L.push_front(200);
 L.push_front(300);



 list <int>L2;
 L2.assign(10, 100);
 printList(L2);


 L2.assign(L.begin(), L.end());
 printList(L2);


 cout << "L2 front = " << L2.front() << endl;
 cout << "L2 back = " << L2.back() << endl;

}


/*
3.6.4.6 list反转排序
reverse();//反转链表，比如lst包含1,3,5元素，运行此方法后，lst就包含5,3,1元素。
sort(); //list排序
*/
/*
bool myCompare(int v1, int v2)
{
 return v1 > v2;
}

void test04()
{
 list <int>L;
 L.push_back(10);
 L.push_back(20);
 L.push_back(30);
 L.push_front(100);
 L.push_front(200);
 L.push_front(300);

 //反转  质变算法
 L.reverse();

 printList(L);

 //排序  
 // 所有系统提供标准算法  使用的容器提供的迭代器必须支持随机访问
 // 不支持随机访问的迭代器的容器 ，内部会对应提供相应的算法的接口
 //sort(L.begin(), L.end());
 L.sort(); //默认排序规则  从小到大

 //修改排序规则 为 从大到小
 L.sort(myCompare);

 printList(L);
}
*/
class Person
{
public:
 Person(string name, int age ,int height)
 {
  this->m_Name = name;
  this->m_Age = age;
  this->m_Height = height;
 }

 bool operator==(const Person &p)
 {
  if (this->m_Name == p.m_Name && this->m_Age == p.m_Age && this->m_Height == p.m_Height)
  {
   return true;
  }
  return false;
 
 }

 string m_Name;
 int m_Age;
 int m_Height; //身高
};

bool myComparePerson(Person & p1, Person &p2)
{
 //按照年龄  升序
 // 如果年龄相同 按照身高 进行降序

 if (p1.m_Age == p2.m_Age)
 {
  return p1.m_Height > p2.m_Height;
 }

 return p1.m_Age < p2.m_Age;
}

void test05()
{
 list<Person> L;

 Person p1("大娃", 30 , 170);
 Person p2("二娃", 28 , 160);
 Person p3("三娃", 24 , 150);
 Person p4("四娃", 24 , 166);
 Person p5("五娃", 24 , 158);
 Person p6("爷爷", 90 , 200);
 Person p7("蛇精", 999 , 999);

 L.push_back(p1);
 L.push_back(p2);
 L.push_back(p3);
 L.push_back(p4);
 L.push_back(p5);
 L.push_back(p6);
 L.push_back(p7);

 for (list<Person>::iterator it = L.begin(); it != L.end();it++)
 {
  cout << " 姓名： " << it->m_Name << " 年龄： " << it->m_Age <<" 身高： "<< it->m_Height <<  endl;
 }
 cout << "排序后的结果为： " << endl;
 L.sort(myComparePerson); //自定义的数据类型 必须指定排序规则
 for (list<Person>::iterator it = L.begin(); it != L.end(); it++)
 {
  cout << " 姓名： " << it->m_Name << " 年龄： " << it->m_Age << " 身高： " << it->m_Height << endl;
 }

 //L.remove(p1);

 cout << "删除大娃后的结果为： " << endl;
 for (list<Person>::iterator it = L.begin(); it != L.end(); it++)
 {
  cout << " 姓名： " << it->m_Name << " 年龄： " << it->m_Age << " 身高： " << it->m_Height << endl;
 }
}

int main(){

 //test01();
 //test02();
 //test03();
 //test04();
 test05();

 system("pause");
 return EXIT_SUCCESS;
}

```

![](/assets/images/2022-10-24-21-04-37.png)

#### test

```cpp {.line-numbers, highlight=[1-2]}
// 排序算法稳定性，怎么用的？？？？？？？？？？？？？？？？？？？？？  理解：商品筛选，商品价格从低到高（假设没有重复值），然后质量从高到低排序---未验证：需要两次稳定排序？？？？
// 还有一种指定排序规则，一次排序就可完成

```

### Set容器

```cpp {.line-numbers, highlight=[1, 55, 57-59, 115, 137, 142, 151, 234, 244]}
// set的迭代器为只读迭代器，即不能通过迭代器修改key值，且删除或增加除指定迭代器的元素的位置的其它位置，其不会影响先前获得的迭代器
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <set> //set、 multiset  的头文件 
#include <string>
/*
3.7.2.1 set构造函数
set<T> st;//set默认构造函数：
mulitset<T> mst; //multiset默认构造函数:
set(const set &st);//拷贝构造函数
3.7.2.2 set赋值操作
set& operator=(const set &st);//重载等号操作符
swap(st);//交换两个集合容器
3.7.2.3 set大小操作
size();//返回容器中元素的数目
empty();//判断容器是否为空

3.7.2.4 set插入和删除操作
insert(elem);//在容器中插入元素。
clear();//清除所有元素
erase(pos);//删除pos迭代器所指的元素，返回下一个元素的迭代器。
erase(beg, end);//删除区间[beg,end)的所有元素 ，返回下一个元素的迭代器。
erase(elem);//删除容器中值为elem的元素。
*/

void printSet(set<int>&s)
{
 for (set<int>::iterator it = s.begin(); it != s.end();it++)
 {
  cout << *it << " ";
 }
 cout << endl;
}

void test01()
{
 set<int>s;
 s.insert(10);
 s.insert(30);
 s.insert(20);
 s.insert(50);
 s.insert(40);

 printSet(s);

 s.erase(10);

 printSet(s);
}


/*
3.7.2.5 set查找操作
find(key);//查找键key是否存在,若存在，返回该键的元素的迭代器；若不存在，返回set.end();
count(key);//查找键key的元素个数
lower_bound(keyElem);//返回第一个key>=keyElem元素的迭代器。
upper_bound(keyElem);//返回第一个key>keyElem元素的迭代器。
equal_range(keyElem);//返回容器中key与keyElem相等的上下限的两个迭代器。，返回的就为lower_boud，upper_bound的迭代器
*/

void test02()
{
 set<int>s;
 s.insert(10);
 s.insert(30);
 s.insert(20);
 s.insert(50);
 s.insert(40);

 set<int>::iterator pos = s.find(30);
 if (pos != s.end())
 {
  cout << "找到了元素：" << *pos << endl;
 }
 else
 {
  cout << "未找到" << endl;
 }


 //统计  对于set而言 结果要么是0  要么是1
 int num = s.count(10);
 cout << "10的个数为： " << num << endl;


 //lower_bound(keyElem);//返回第一个key>=keyElem元素的迭代器。

 set<int>::iterator res = s.lower_bound(30);
 
 if (res != s.end())
 {
  cout << "找到lower_bound的值为： " << *res << endl;
 }
 else
 {
  cout << "未找到" << endl;
 }

 //upper_bound(keyElem);//返回第一个key>keyElem元素的迭代器。
 res = s.upper_bound(30);
 if (res != s.end())
 {
  cout << "找到upper_bound的值为： " << *res << endl;
 }
 else
 {
  cout << "未找到" << endl;
 }


 //equal_range(keyElem);//返回容器中key与keyElem相等的上下限的两个迭代器。
 pair< set<int>::iterator, set<int>::iterator> it = s.equal_range(30);

 if (it.first != s.end())
 {
  cout << "找到equal_range中的 lower_bound的值为： " << *(it.first) << endl;
 }
 else
 {
  cout << "未找到" << endl;
 }

 if ( it.second != s.end() )
 {
  cout << "找到equal_range中的 upper_bound的值为： " << *(it.second) << endl;
 }
 else
 {
  cout << "未找到" << endl;
 }
}

//对组是声明
void test03()
{
 //第一种声明
 pair<string, int> p(string("Tom"), 18);

 cout << "姓名： " << p.first << " 年龄： " << p.second << endl;

 //第二种声明
 pair<string, int> p2 = make_pair("Jerry", 20);
 cout << "姓名： " << p2.first << " 年龄： " << p2.second << endl;
}

void test04()//setr容器不允许插入重复的键值
{
 set<int>s;

 pair<set<int>::iterator , bool> ret = s.insert(10);

 if (ret.second)
 {
  cout << "第一个插入成功" << endl;
 }
 else
 {
  cout << "第一个插入未成功" << endl;
 }

 ret = s.insert(10);

 if (ret.second)
 {
  cout << "第二个插入成功" << endl;
 }
 else
 {
  cout << "第二个插入未成功" << endl;
 }

 //printSet(s);

 multiset <int>ms;

 ms.insert(10);
 ms.insert(10);

 for (multiset<int>::iterator it = ms.begin(); it != ms.end();it++)
 {
  cout << *it << endl;
 }

}

//利用仿函数 指定set容器的排序规则
class MyCompare
{
public:
 bool operator()(int v1 ,int v2)
 {
  return v1 > v2;
 }
};

void test05()
{
 set<int, MyCompare> s;

 s.insert(10);
 s.insert(30);
 s.insert(20);
 s.insert(50);
 s.insert(40);

 //默认排序是从小到大
 //printSet(s);

 //插入之前 指定排序规则
 for (set<int, MyCompare>::iterator it = s.begin(); it != s.end();it++)
 {
  cout << *it << endl;
 }
}


class Person
{
public:
 Person(string name,int age)
 {
  this->m_Name = name;
  this->m_Age = age;
 }

 string m_Name;
 int m_Age;
};

class MyComparePerson
{
public:
 bool operator()(const  Person & p1 , const Person & p2)  // 仿函数
 {
  //年龄 升序
  return p1.m_Age < p2.m_Age;
 }

};

void test06()
{
 set<Person, MyComparePerson> s;  // 仿函数指定排序规则

 Person p1("aaa", 10);
 Person p2("bbb", 30);
 Person p3("ccc", 20);
 Person p4("ddd", 50);
 Person p5("eee", 40);

 s.insert(p1);
 s.insert(p2);
 s.insert(p3);
 s.insert(p4);
 s.insert(p5);

 //对于自定义数据类型，必须指定排序规则
 for (set<Person,MyComparePerson>::iterator it = s.begin(); it != s.end(); it++)
 {
  cout << "姓名： " << (*it).m_Name << " 年龄： " << it->m_Age << endl;
 }

}

int main(){
 test01();
 //test02();
 //test03();
 //test04();
 //test05();
 //test06();

 system("pause");
 return EXIT_SUCCESS;
}

```

#### test

```cpp {.line-numbers, highlight=[8]}
#include <array>
#include <iostream>

#define My_Size 5000

int main() {
  std::cout << "----------" << std::endl;
  std::array<int, My_Size> nums;  // 模板的非类型参数，在实例化模板时由编译器直接绑定常量值，绑定值必须为常量表达式
  nums[0] = 20;
  std::cout << nums.size() << std::endl;
  std::cout << nums[0] << std::endl;
}

```

#### test

```cpp {.line-numbers, highlight=[10-12]}
#include <iostream>
#include <string>
#include <vector>
int main() {
  std::string s1 = "abc";
  std::cout << sizeof(s1) << std::endl;
  std::vector<std::string> vec;
  std::string s2 = "awfgw";
  vec.push_back(s1);
  std::cout << &s1 << std::endl;      // 分配栈上
  std::cout << vec.data() << std::endl;   // 分配堆上
  std::cout << &vec[0] << std::endl;      // 分配堆上
  
}

// 24
// 00000023CF4FFA18
// 000001735CC5D190
// 000001735CC5D190

```

### Map容器

```cpp
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

#include <map> //map和 multimap 的头文件

/*
3.8.2.1 map构造函数
map<T1, T2> mapTT;//map默认构造函数:
map(const map &mp);//拷贝构造函数
3.8.2.2 map赋值操作
map& operator=(const map &mp);//重载等号操作符
swap(mp);//交换两个集合容器
3.8.2.3 map大小操作
size();//返回容器中元素的数目
empty();//判断容器是否为空
3.8.2.4 map插入数据元素操作
map.insert(...); //往容器插入元素，返回pair<iterator,bool>
map<int, string> mapStu;
// 第一种 通过pair的方式插入对象
mapStu.insert(pair<int, string>(3, "小张"));
// 第二种 通过pair的方式插入对象
mapStu.inset(make_pair(-1, "校长"));
// 第三种 通过value_type的方式插入对象
mapStu.insert(map<int, string>::value_type(1, "小李"));
// 第四种 通过数组的方式插入值
mapStu[3] = "小刘";
mapStu[5] = "小王";
*/

void test01()
{
 map<int, int> m;

 //插入方式
 //第一种
 m.insert(pair<int, int>(1, 10));

 //第二种
 m.insert(make_pair(2, 20));

 //第三种
 m.insert(map<int, int>::value_type(3, 30));

 //第四种
 m[4] = 40;

 for (map<int, int>::iterator it = m.begin(); it != m.end();it++)
 {
  cout << " key =  " << it->first << " value = " << (*it).second << endl;
 }


 //cout << m[4] << endl;
 //for (map<int, int>::iterator it = m.begin(); it != m.end(); it++)
 //{
 // cout << " key =  " << it->first << " value = " << (*it).second << endl;
 //}
}

/*
3.8.2.5 map删除操作
clear();//删除所有元素
erase(pos);//删除pos迭代器所指的元素，返回下一个元素的迭代器。
erase(beg,end);//删除区间[beg,end)的所有元素 ，返回下一个元素的迭代器。
erase(keyElem);//删除容器中key为keyElem的对组。
3.8.2.6 map查找操作
find(key);//查找键key是否存在,若存在，返回该键的元素的迭代器；/若不存在，返回map.end();
count(keyElem);//返回容器中key为keyElem的对组个数。对map来说，要么是0，要么是1。对multimap来说，值可能大于1。
lower_bound(keyElem);//返回第一个key>=keyElem元素的迭代器。
upper_bound(keyElem);//返回第一个key>keyElem元素的迭代器。
equal_range(keyElem);//返回容器中key与keyElem相等的上下限的两个迭代器。
*/
void test02()
{
 map<int, int> m;
 m.insert(pair<int, int>(1, 10));
 m.insert(make_pair(2, 20));
 m.insert(map<int, int>::value_type(3, 30));
 m[4] = 40;

 //m.erase(3); //按照key进行删除元素
 for (map<int, int>::iterator it = m.begin(); it != m.end(); it++)
 {
  cout << " key =  " << it->first << " value = " << (*it).second << endl;
 }

 //查找
 map<int,int>::iterator pos =  m.find(3);
 if (pos != m.end())
 {
  cout << "找到了 key为： " << (*pos).first << " value 为： " << pos->second << endl;
 }

 int num  = m.count(4);
 cout << "key为4的对组个数为： " << num << endl;

 //lower_bound(keyElem);//返回第一个key>=keyElem元素的迭代器。
 map<int,int>::iterator ret =  m.lower_bound(3);
 if (ret != m.end())
 {
  cout << "找到了lower_bound的key为：  " << ret->first << " value =  " << ret->second << endl;
 }
 else
 {
  cout << "未找到" << endl;
 }
 //upper_bound(keyElem);//返回第一个key>keyElem元素的迭代器。
 ret=  m.upper_bound(3);
 if (ret != m.end())
 {
  cout << "找到了upper_bound的key为：  " << ret->first << " value =  " << ret->second << endl;
 }
 else
 {
  cout << "未找到" << endl;
 }

 //equal_range(keyElem);//返回容器中key与keyElem相等的上下限的两个迭代器。

 pair< map<int, int>::iterator, map<int, int>::iterator> it2 = m.equal_range(3);

 if ( it2.first != m.end())
 {
  cout << "找到了equal_range中的 lower_bound的key为：  " << it2.first->first << " value =  " << it2.first->second << endl;
 }
 else
 {
  cout << "未找到" << endl;
 }

 if (it2.second != m.end())
 {
  cout << "找到了equal_range中的 upper_bound的key为：  " << it2.second->first << " value =  " << it2.second->second << endl;
 }
 else
 {
  cout << "未找到" << endl;
 }
}

class MyCompare
{
public:
 bool operator()(int v1,int v2)
 {
  return v1 > v2;
 }

};

//指定map容器的排序规则
void test03()
{
 map<int, int, MyCompare> m;
 m.insert(pair<int, int>(1, 10));
 m.insert(make_pair(2, 20));
 m.insert(map<int, int>::value_type(3, 30));
 m[4] = 40;

 for (map<int, int, MyCompare>::iterator it = m.begin(); it != m.end(); it++)
 {
  cout << " key =  " << it->first << " value = " << (*it).second << endl;
 }

}


int main(){
 //test01();
 //test02();
 test03();

 system("pause");
 return EXIT_SUCCESS;
}

```

### 员工分组案例

```cpp
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <vector>
#include <string>
#include <map>
#include <ctime>

//公司今天招聘了5个员工，5名员工进入公司之后，需要指派员工在那个部门工作
//人员信息有: 姓名 年龄 电话 工资等组成
//通过Multimap进行信息的插入 保存 显示
//分部门显示员工信息 显示全部员工信息

enum
{
 CAIWU,RENLI,MEISHU
};

class Worker
{
public:
 string m_Name;//姓名
 int m_Money; //工资
};

void createWorker(vector<Worker>&v)
{
 string nameSeed = "ABCDE";
 for (int i = 0; i < 5;i++)
 {
  Worker worker;
  worker.m_Name = "员工";
  worker.m_Name += nameSeed[i];

  worker.m_Money = rand() % 10000 + 10000; // 10000 ~ 19999
  
  v.push_back(worker);
 }

}

void setGroup(vector<Worker>&v, multimap<int, Worker>&m)
{
 for (vector<Worker>::iterator it = v.begin(); it != v.end();it++)
 {
  //随机产生部门编号  0 1 2 
  int id = rand() % 3;

  //将员工插入到分组的容器中
  m.insert(make_pair(id, *it));
 }

}

void showWorker(multimap<int,Worker>&m)
{
 // 0 A   0  B   1  C   2  D  2 E
 cout << "财务部门人员如下： " << endl;
 multimap<int,Worker>::iterator pos = m.find(CAIWU);
 int count = m.count(CAIWU);
 int index = 0;

 for (; pos != m.end(), index < count; pos++, index++)
 {
  cout << "姓名： " << pos->second.m_Name << " 工资： " << pos->second.m_Money << endl;
 }

 cout << "人力资源部门人员如下： " << endl;
 pos = m.find(RENLI);
 count = m.count(RENLI);
 index = 0;

 for (; pos != m.end(), index < count; pos++, index++)
 {
  cout << "姓名： " << pos->second.m_Name << " 工资： " << pos->second.m_Money << endl;
 }



 cout << "美术部门人员如下： " << endl;
 pos = m.find(MEISHU);
 count = m.count(MEISHU);
 index = 0;

 for (; pos != m.end(), index < count; pos++, index++)
 {
  cout << "姓名： " << pos->second.m_Name << " 工资： " << pos->second.m_Money << endl;
 }

}

int main(){

 //随机数种子
 srand((unsigned int)time(NULL));

 vector<Worker>v; //存放员工的容器
 //员工的创建
 createWorker(v);

 //员工分组
 multimap<int, Worker>m;
 setGroup(v,m);

 //分部门显示员工
 showWorker(m);


 //for (vector<Worker>::iterator it = v.begin(); it != v.end();it++)
 //{
 // cout << "姓名： " << it->m_Name << " 工资： " << it->m_Money << endl;
 //}


 system("pause");
 return EXIT_SUCCESS;
}

```

### 函数对象

```cpp {.line-numbers, highlight=[32]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//1、函数对象 很像函数调用方式 ，因此也称为 仿函数
class MyPrint
{
public:

 void operator()(int num)
 {
  cout << num << endl;
  m_Count++;
 }
 int m_Count = 0;
};

void myPrint(int num)
{
 cout << num << endl;
}

void test01()
{
 MyPrint mp;
 mp(100); //类似函数的调用

 myPrint(100);
}


//2、函数对象 超出普通函数的概念，内部可以拥有自己的状态；并且可以内联，运行效率快，函数指针并不能内联，必须进行调用
void test02()
{
 MyPrint mp;
 mp(100);
 mp(100);
 mp(100);
 mp(100);

 cout << "count = " << mp.m_Count << endl;

}

//3、函数对象可以作为函数的参数传递
void doWork(MyPrint mp , int num)
{
 mp(num);
}
void test03()
{
 doWork(MyPrint(), 1000);
}

int main(){


 //test01();
 //test02();
 test03();
 system("pause");
 return EXIT_SUCCESS;
}

```

### 谓词

```cpp {.line-numbers, highlight=[7, 63]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <vector>
#include <algorithm>

//谓词  普通函数 或者仿函数 返回值 是 bool类型，这样的函数或者仿函数称为谓词
//一元谓词
class GreaterThen20
{
public:
 bool operator()( int val)
 {
  return val > 20;
 }
};

void test01()
{
 vector<int>v;
 v.push_back(10);
 v.push_back(20);
 v.push_back(30);
 v.push_back(40);

 //找到第一个大于20的数字
 vector<int>::iterator pos = find_if(v.begin(), v.end(), GreaterThen20());

 if (pos != v.end())
 {
  cout << "找到大于20的数字为： "<< *pos << endl;
 }
 else
 {
  cout << "未找到" << endl;
 }
}


//二元谓词
class MyCompare
{
public:
 bool operator()(int v1 ,int v2)
 {
  return v1 > v2;
 }

};


void test02()
{
 vector<int>v;
 v.push_back(10);
 v.push_back(30);
 v.push_back(20);
 v.push_back(40);

 //从大到小 排序
 sort(v.begin(), v.end(), MyCompare());

 //[](){} 匿名函数  lambda  完整形式：[]()-> rt{} []为标识符，rt为返回类型  
 for_each(v.begin(), v.end(), [](int val){ cout << val << endl; });
}

int main(){

 //test01();
 test02();


 system("pause");
 return EXIT_SUCCESS;
}

```

### 内建函数对象

```cpp {.line-numbers, highlight=[4, 39]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <functional>
#include <vector>
#include <algorithm>

//template<class T> T negate<T>//取反仿函数
void test01()
{
 negate<int>n;
 cout << n(10) << endl;
}

//template<class T> T plus<T>//加法仿函数
void test02()
{
 plus<int> p;

 cout << p(1, 1) << endl;
}

//template<class T> bool greater<T>//大于
void test03()
{
 vector<int>v;
 v.push_back(10);
 v.push_back(30);
 v.push_back(50);
 v.push_back(20);
 v.push_back(70);
 v.push_back(60);

 sort(v.begin(), v.end(), greater<int>());

 for_each(v.begin(), v.end(), [](int val){ cout << val << endl; });

}
// 内建函数对象分为：算术运算，关系运算，逻辑运算，其中取反和not为一元内建函数对象，二元内建函数对象
int main(){

// test01();
// test02();
 test03();

 system("pause");
 return EXIT_SUCCESS;
}

```

### 适配器

```cpp {.line-numbers, highlight=[9, 38-40, 43, 88, 109]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <functional>
#include <string>

//1、函数对象适配器
class myPrint : public binary_function<int,int,void>
{
public:
 void operator()(int val ,int start) const
 {
  cout << "val = " << val << " start = " << start << " sum = " <<  val + start << endl;
 }

};

void test01()
{
 vector<int>v;
 for (int i = 0; i < 10;i++)
 {
  v.push_back(i);
 }
 cout << "请输入起始累加值： " << endl;
 int num;
 cin >> num;
 for_each(v.begin(), v.end(), bind2nd(myPrint(), num));


 //bind1st的参数绑定是相反的
 //for_each(v.begin(), v.end(), bind1st(myPrint(), num));

}

//1、将参数进行绑定  bind2nd
//2、做继承   binary_function<类型1，类型2，返回值类型>
//3、加const


//取反适配器
class GreaterThenFive :public unary_function<int,bool>
{
public:
 bool operator()(int val) const
 {
  return val > 5;
 }
};
void test02()
{
 vector<int>v;
 for (int i = 0; i < 10;i++)
 {
  v.push_back(i);
 }
 //取反适配器
 //vector<int>::iterator pos = find_if(v.begin(), v.end(), not1( GreaterThenFive()));

 vector<int>::iterator pos = find_if(v.begin(), v.end(),  not1( bind2nd( greater<int>(),5 )) );

 if (pos != v.end())
 {
  cout << "小于5的数字为：" << *pos << endl;
 }
 else
 {
  cout << "未找到" << endl;
 }

 vector<int>v1;
 for (int i = 0; i < 10; i++)
 {
  v1.push_back(i);
 }
 sort(v1.begin(), v1.end(), not2( less<int>()));
 for_each(v1.begin(), v1.end(), [](int val){ cout << val << endl; });

}
//取反适配器使用
// 1、一元取反   not1 
// 2、继承  unary_function<类型1 ，返回值类型>
// 3、加const


//函数指针适配器
void myPrint3(int val ,int start) 
{
 cout << val + start << endl;
}
void test03()
{
 vector<int>v;
 for (int i = 0; i < 10; i++)
 {
  v.push_back(i);
 }
 cout << "请输入起始累加值： " << endl;
 int num;
 cin >> num;
 //函数指针适配器 ，将函数指针  适配成  函数对象
 // ptr_fun
 for_each(v.begin(), v.end(), bind2nd( ptr_fun( myPrint3) ,num)  );
}


//成员函数适配器
class Person
{
public:
 Person(string name,int age)
 {
  this->m_Name = name;
  this->m_Age = age;
 }

 void showPerson()
 {
  cout << "成员函数---- 姓名：　" << m_Name << " 年龄： " << m_Age << endl;
 }

 void plusAge()
 {
  m_Age++;
 }

 string m_Name;
 int m_Age;
};

//void printPerson( Person &p)
//{
// cout << "姓名：　" << p.m_Name << " 年龄： " << p.m_Age << endl;
//}

void test04()
{
 vector<Person>v;
 Person p1("aaa", 10);
 Person p2("bbb", 20);
 Person p3("ccc", 30);
 Person p4("ddd", 40);
 Person p5("eee", 50);
 v.push_back(p1);
 v.push_back(p2);
 v.push_back(p3);
 v.push_back(p4);
 v.push_back(p5);

 //for_each(v.begin(), v.end(), printPerson);

 for_each(v.begin(), v.end(),  mem_fun_ref( &Person::showPerson));
 for_each(v.begin(), v.end(), mem_fun_ref(&Person::plusAge));
 for_each(v.begin(), v.end(), mem_fun_ref(&Person::showPerson));
}

int main(){

 //test01();
 test02();
 //test03();
 //test04();

 system("pause");
 return EXIT_SUCCESS;
}

```

#### test

```cpp {.line-numbers, highlight=[31]}
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

#include <__functional/binary_function.h>
#include <__functional/bind.h>
#include <__functional/binder2nd.h>

class PrintVector : public std::__binary_function<int, int, void> {
 public:
  void operator()(int value, int offset) const {
    std::cout << value + offset << std::endl;
    std::cout << value << std::endl;
    std::cout << offset << std::endl;
    std::cout << "---------------" << std::endl;
  }
};

int main() {
  std::vector<int> vec;
  for (int i = 0; i < 10; ++i) {
    vec.push_back(i);
  }

  int offset = 100;

  std::for_each(
      vec.begin(),
      vec.end(),
      std::bind(PrintVector(), offset, std::placeholders::_1));  // _1占位符表示使用传递函数参数列表的第一个参数 ?????????????????怎么确定绑定的，如何实现的
}

```

#### test

```cpp {.line-numbers, highlight=[1]}
#include <chrono>     // 时间库
#include <iostream>

#include <__chrono/duration.h>

int main() {
  std::chrono::seconds secs =
      std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock().now().time_since_epoch());

  std::cout << std::chrono::milliseconds(secs).count() << std::endl;
}

```

#### test

```cpp {.line-numbers, highlight=[7, 14]}
#include <iostream>

class Person {
 public:
  int age_;
  void PrintSize() {
    std::cout << sizeof(this) << std::endl;   // this指针8字节
  }
};

int main() {
  Person p1;
  p1.PrintSize();
  std::cout << sizeof(p1) << std::endl;   // 对象4字节
}

```

### 常用的遍历算法

```cpp {.line-numbers, highlight=[59, 85]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <functional>
/*
遍历算法 遍历容器元素
@param beg 开始迭代器
@param end 结束迭代器
@param _callback  函数回调或者函数对象
@return 函数对象
*/

void myPrint(int val)
{
 cout << val << endl;
}

class MyPrint
{
public:
 void operator()(int val)
 {
  cout << val << endl;
  m_count++;
 }

 int m_count = 0;
};

void test01()
{
 vector<int>v;
 for (int i = 0; i < 10;i++)
 {
  v.push_back(i);
 }
 
 //for_each(v.begin(), v.end(), myPrint);

 for_each(v.begin(), v.end(), MyPrint());
}
// for_each有返回值
void test02()
{

 vector<int>v;
 for (int i = 0; i < 10; i++)
 {
  v.push_back(i);
 }
 MyPrint mp = for_each(v.begin(), v.end(), MyPrint());

 cout <<"count = " <<  mp.m_count << endl;

}

// for_each可以绑定参数 进行输出
class MyPrint3:public binary_function<int ,int , void >
{
public:
 void operator()(int val ,int start) const
 {
  cout << val + start << endl;
  
 }
};

void test03()
{
 vector<int>v;
 for (int i = 0; i < 10; i++)
 {
  v.push_back(i);
 }

 for_each(v.begin(), v.end(), bind2nd(MyPrint3(), 1000));

}



/*
transform算法 将指定容器区间元素搬运到另一容器中
注意 : transform 不会给目标容器分配内存，所以需要我们提前分配好内存
@param beg1 源容器开始迭代器
@param end1 源容器结束迭代器
@param beg2 目标容器开始迭代器
@param _cakkback 回调函数或者函数对象
@return 返回目标容器迭代器
*/
class MyTransform
{
public:
 int operator()(int val)
 {
  return val ;
 }
};

void test04()
{
 vector<int>v1;
 for (int i = 0; i < 10;i++)
 {
  v1.push_back(i);
 }

 vector<int>vTarget;
 //重新指定 vTarget大小
 vTarget.resize(v1.size());

 transform(v1.begin(), v1.end(), vTarget.begin(), MyTransform());

 for_each(vTarget.begin(), vTarget.end(), [](int val){cout << val << endl; });
}



int main(){

 //test01();
 //test02();
 //test03();
 test04();
 system("pause");
 return EXIT_SUCCESS;
}

```

### 常用的查找算法

```cpp {.line-numbers, highlight=[9, 102, 117, 152, 183, 189]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
/*
find算法 查找元素
@param beg 容器开始迭代器
@param end 容器结束迭代器
@param value 查找的元素
@return 返回查找元素的位置
*/

void test01()
{
 vector<int>v1;
 for (int i = 0; i < 10;i++)
 {
  v1.push_back(i);
 }

 //查找有没有5这个元素
 vector<int>::iterator it = find(v1.begin(), v1.end(), 5);
 if (it != v1.end())
 {
  cout << "找到了元素： " << *it << endl;
 }
 else
 {
  cout << "未找到" << endl;
 }

}

class Person
{
public:
 Person(string name, int age)
 {
  this->m_Name = name;
  this->m_Age = age;
 }

 bool operator==(const Person & p)
 {
  return this->m_Name == p.m_Name && this->m_Age == p.m_Age;
 }

 string m_Name;
 int m_Age;
};
void test02()
{
 vector<Person>v;
 Person p1("aaa", 10);
 Person p2("bbb", 40);
 Person p3("ccc", 20);
 Person p4("ddd", 30);

 v.push_back(p1);
 v.push_back(p2);
 v.push_back(p3);
 v.push_back(p4);

 vector<Person>::iterator it = find(v.begin(), v.end(), p3);
 if (it != v.end())
 {
  cout << "找到了元素---姓名：  " << (*it).m_Name  << " 年龄： "<< it->m_Age << endl;
 }
 else
 {
  cout << "未找到" << endl;
 }
}

class MyComparePerson :public binary_function<Person*,Person*,bool>
{
public:
 bool operator()(Person * p1 ,Person * p2) const
 {
  return (p1->m_Name == p2->m_Name && p1->m_Age == p2->m_Age);
 }
};

void test03()
{
 vector<Person*>v;
 Person p1("aaa", 10);
 Person p2("bbb", 40);
 Person p3("ccc", 20);
 Person p4("ddd", 30);

 v.push_back(&p1);
 v.push_back(&p2);
 v.push_back(&p3);
 v.push_back(&p4);

 Person * p = new Person("bbb", 40);

 vector<Person*>::iterator it= find_if(v.begin(), v.end(), bind2nd( MyComparePerson() ,p ));
 if (it != v.end())
 {
  cout << "找到了数据 姓名： " << (*it)->m_Name << " 年龄： " << (*it)->m_Age << endl;
 }
 else
 {
  cout << "未找到" << endl;
 }


}


/*
adjacent_find算法 查找相邻重复元素
@param beg 容器开始迭代器
@param end 容器结束迭代器
@param  _callback 回调函数或者谓词(返回bool类型的函数对象)
@return 返回相邻元素的第一个位置的迭代器
*/
void test04()
{
 vector<int>v1;
 v1.push_back(1);
 v1.push_back(4);
 v1.push_back(2);
 v1.push_back(3);
 v1.push_back(4);
 v1.push_back(6);
 v1.push_back(6);
 v1.push_back(17);

 vector<int>::iterator it = adjacent_find(v1.begin(), v1.end());

 if (it != v1.end())
 {
  cout << "相邻的重复元素为：" << *it << endl;
 }
 else
 {
  cout << "未找到" << endl;
 }


}



/*
binary_search算法 二分查找法
注意: 在无序序列中不可用
@param beg 容器开始迭代器
@param end 容器结束迭代器
@param value 查找的元素
@return bool 查找返回true 否则false
*/

void test05()
{
 vector<int>v;
 for (int i = 0; i < 10;i++)
 {
  v.push_back(i);
 }
 //v.push_back(3);

 bool ret = binary_search(v.begin(), v.end(), 9);

 if (ret)
 {
  cout << "找到了" << endl;
 }
 else
 {
  cout << "未找到" << endl;
 }
}


/*
count算法 统计元素出现次数
@param beg 容器开始迭代器
@param end 容器结束迭代器
@param  value回调函数或者谓词(返回bool类型的函数对象)
@return int返回元素个数

count_if算法 统计元素出现次数
@param beg 容器开始迭代器
@param end 容器结束迭代器
@param  callback 回调函数或者谓词(返回bool类型的函数对象)
@return int返回元素个数
*/
class MyCompare6
{
public:
 bool operator()(int val)
 {
  return val > 4;
 }
};
void test06()
{
 vector<int>v;
 for (int i = 0; i < 10; i++)
 {
  v.push_back(i);
 }
 v.push_back(4);
 v.push_back(4);
 v.push_back(4);
 v.push_back(4);

 int num = count(v.begin(), v.end(), 4);
 cout << "4的个数为： " << num << endl;


 //按条件进行统计
 num = count_if(v.begin(), v.end(), MyCompare6());
 cout << "大于4的个数为： " << num << endl;
}



int main(){
 //test01();
 //test02();
 //test03();
 //test04();
 //test05();
 test06();
 system("pause");
 return EXIT_SUCCESS;
}

```

### 常用排序算法

```cpp {.line-numbers, highlight=[10, 37, 59, 84]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <functional>
#include <ctime>

/*
merge算法 容器元素合并，并存储到另一容器中
注意:两个容器必须是有序的
@param beg1 容器1开始迭代器
@param end1 容器1结束迭代器
@param beg2 容器2开始迭代器
@param end2 容器2结束迭代器
@param dest  目标容器开始迭代器
*/

void test01()
{
 vector<int>v1;
 vector<int>v2;

 for (int i = 0; i < 10;i++)
 {
  v1.push_back(i);
  v2.push_back(i + 1);
 }

 vector<int>vTarget;//目标容器
 vTarget.resize(v1.size() + v2.size());
 merge(v1.begin(), v1.end(), v2.begin(), v2.end(), vTarget.begin());
 for_each(vTarget.begin(), vTarget.end(), [](int val){cout << val << endl; });
}

/*
sort算法 容器元素排序
@param beg 容器1开始迭代器
@param end 容器1结束迭代器
@param _callback 回调函数或者谓词(返回bool类型的函数对象)
*/
void test02()
{
 vector<int>v1;

 for (int i = 0; i < 10; i++)
 {
  v1.push_back(i);
 }

 //从大到小
 sort(v1.begin(), v1.end(), greater<int>());

 for_each(v1.begin(), v1.end(), [](int val){cout << val << endl; });

}

/*
random_shuffle算法 对指定范围内的元素随机调整次序
@param beg 容器开始迭代器
@param end 容器结束迭代器
*/

void test03()
{
 vector<int>v1;

 for (int i = 0; i < 10; i++)
 {
  v1.push_back(i);
 }

 random_shuffle(v1.begin(), v1.end());


 for_each(v1.begin(), v1.end(), [](int val){cout << val << " "; });

 cout << endl;

}


/*
reverse算法 反转指定范围的元素
@param beg 容器开始迭代器
@param end 容器结束迭代器
*/
void test04()
{
 vector<int>v1;

 for (int i = 0; i < 10; i++)
 {
  v1.push_back(i);
 }
 v1.push_back(3);

 reverse(v1.begin(), v1.end());
 for_each(v1.begin(), v1.end(), [](int val){cout << val << " "; });

 cout << endl;
}


int main(){
 srand((unsigned int)time(NULL));

 //test01();
 //test02();
 //test03();
 test04();


 system("pause");
 return EXIT_SUCCESS;
}

```

### 常用的拷贝和替换算法

```cpp {.line-numbers, highlight=[8, 29, 36, 42, 80]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <iterator>
/*
copy算法 将容器内指定范围的元素拷贝到另一容器中
@param beg 容器开始迭代器
@param end 容器结束迭代器
@param dest 目标起始迭代器
*/
void test01()
{
 vector<int>v1;

 for (int i = 0; i < 10;i++)
 {
  v1.push_back(i);
 }

 vector<int>vTarget;
 vTarget.resize(v1.size());

 copy(v1.begin(), v1.end(), vTarget.begin());

 //for_each(vTarget.begin(), vTarget.end(), [](int val){ cout << val << " "; });

 copy(vTarget.begin(), vTarget.end(), ostream_iterator<int>(cout, " ")); // 拷贝到流迭代器中输出

 cout << endl;

}

/*
replace算法 将容器内指定范围的旧元素修改为新元素
@param beg 容器开始迭代器
@param end 容器结束迭代器
@param oldvalue 旧元素
@param oldvalue 新元素

replace_if算法 将容器内指定范围满足条件的元素替换为新元素
@param beg 容器开始迭代器
@param end 容器结束迭代器
@param callback函数回调或者谓词(返回Bool类型的函数对象)
@param oldvalue 新元素
*/

class MyCompare2
{
public:
 bool operator()(int val)
 {
  return val > 3;
 }
};
void test02()
{
 vector<int>v1;

 for (int i = 0; i < 10; i++)
 {
  v1.push_back(i);
 }

 replace(v1.begin(), v1.end(), 3, 300);

 copy(v1.begin(), v1.end(), ostream_iterator<int>(cout, " "));
 cout << endl;

 //按条件 进行替换   将所有大于3  替换为 3000
 replace_if(v1.begin(), v1.end(), MyCompare2(), 3000);

 copy(v1.begin(), v1.end(), ostream_iterator<int>(cout, " "));

}


/*
swap算法 互换两个容器的元素
@param c1容器1
@param c2容器2
*/

void test03()
{
 vector<int>v1;

 for (int i = 0; i < 10; i++)
 {
  v1.push_back(i);
 }


 vector<int>v2(10, 100);

 swap(v1, v2);

 copy(v1.begin(), v1.end(), ostream_iterator<int>(cout, " "));
 cout << endl;


}

int main(){
 //test01();
 //test02();
 test03();
 system("pause");
 return EXIT_SUCCESS;
}

```

### 常用算数生成算法

```cpp {.line-numbers, highlight=[5, 9, 28]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <vector>
#include <numeric> //accumulate头文件
#include <iterator>

/*
accumulate算法 计算容器元素累计总和
@param beg 容器开始迭代器
@param end 容器结束迭代器
@param value累加值
*/

void test01()
{
 vector<int>v;
 for (int i = 1; i <= 100;i++)
 {
  v.push_back(i);
 }

 int sum = accumulate(v.begin(), v.end(), 0); //第三个参数 是起始累加的值
 cout << "sum = " << sum << endl;
}

/*
fill算法 向容器中添加元素
@param beg 容器开始迭代器
@param end 容器结束迭代器
@param value t填充元素
*/

void test02()
{
 vector<int>v;
 v.resize(10);

 fill(v.begin(), v.end(), 500);

 copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
}


int main(){
 //test01();
 test02();

 system("pause");
 return EXIT_SUCCESS;
}

```

### 常用集合算法

```cpp {.line-numbers, highlight=[9, 42, 73]}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>
/*
set_intersection算法 求两个set集合的交集
注意:两个集合必须是有序序列
@param beg1 容器1开始迭代器
@param end1 容器1结束迭代器
@param beg2 容器2开始迭代器
@param end2 容器2结束迭代器
@param dest  目标容器开始迭代器
@return 目标容器的最后一个元素的迭代器地址
*/


void test01()
{
 vector<int>v1;
 vector<int>v2;

 for (int i = 0; i < 10; i++)
 {
  v1.push_back(i);
  v2.push_back(i + 5);
 }

 vector<int>vTarget; //目标容器
 vTarget.resize( min(v1.size(),v2.size()) );//两个容器中取小的开辟size

 vector<int>::iterator itEnd = set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), vTarget.begin());


 copy(vTarget.begin(), itEnd, ostream_iterator<int>(cout, " "));
 cout << endl;
}

/*
set_union算法 求两个set集合的并集
注意:两个集合必须是有序序列
@param beg1 容器1开始迭代器
@param end1 容器1结束迭代器
@param beg2 容器2开始迭代器
@param end2 容器2结束迭代器
@param dest  目标容器开始迭代器
@return 目标容器的最后一个元素的迭代器地址
*/
void test02()
{
 vector<int>v1;
 vector<int>v2;

 for (int i = 0; i < 10; i++)
 {
  v1.push_back(i);
  v2.push_back(i + 5);
 }

 vector<int>vTarget;

 vTarget.resize(v1.size() + v2.size());

 vector<int>::iterator itEnd = set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), vTarget.begin());

 copy(vTarget.begin(), itEnd, ostream_iterator<int>(cout, " "));
 cout << endl;
}

/*
set_difference算法 求两个set集合的差集
注意:两个集合必须是有序序列
@param beg1 容器1开始迭代器
@param end1 容器1结束迭代器
@param beg2 容器2开始迭代器
@param end2 容器2结束迭代器
@param dest  目标容器开始迭代器
@return 目标容器的最后一个元素的迭代器地址
*/


void test03()
{
 vector<int>v1;
 vector<int>v2;

 for (int i = 0; i < 10; i++)
 {
  v1.push_back(i);
  v2.push_back(i + 5);
 }

 vector<int>vTarget;

 vTarget.resize( max(v1.size(),v2.size()) );

 //v1 与 v2 差集
 //vector<int>::iterator itEnd = set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), vTarget.begin());

 //v2 与 v1 差集
 vector<int>::iterator itEnd = set_difference(v2.begin(), v2.end(), v1.begin(), v1.end(), vTarget.begin());
 copy(vTarget.begin(), itEnd, ostream_iterator<int>(cout, " "));
 cout << endl;
}



int main(){


 //test01();
 //test02();
 test03();
 system("pause");
 return EXIT_SUCCESS;
}

```
