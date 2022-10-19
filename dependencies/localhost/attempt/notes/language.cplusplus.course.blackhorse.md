---
id: y3riuz15bl7j8354zs61mdu
title: Blackhorse
desc: ''
updated: 1666170900120
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
