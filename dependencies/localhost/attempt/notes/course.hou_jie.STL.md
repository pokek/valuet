---
id: o46ig0lyxsz48sznetemns4
title: STL
desc: ''
updated: 1667447484732
created: 1667441065802
---

## STL

```cpp {.line-numbers, highlight=[29,50,59,73,90,94,125,127,131-134]}
#include <__hash_table>
#include <__tree>
#include <__tuple>
#include <algorithm>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <iterator>  // istream_iterator, ostream_iterator
#include <map>
#include <memory>
#include <set>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

#include <__functional/bind.h>
#include <__functional/unary_negate.h>
#include <boost/container_hash/hash.hpp>  // hash_combine hash_value      其中hash_value利用shared_ptr获得地址进行哈希
#include <boost/type_index.hpp>
#include <boost/type_traits/has_trivial_destructor.hpp>

using boost::typeindex::type_id_with_cvr;
template <typename T>
void test(T t) {
  std::cout << type_id_with_cvr<decltype(t)>().pretty_name()
            << std::endl;  // int const 函数模板实例化什么类型就是什么类型
}

class Student {
 public:
  std::string name_;
  int age_;
  Student() {
    std::cout << "default construct" << std::endl;
  }
  Student(std::string const& name, int age) : name_(name), age_(age) {}

  ~Student() {
    std::cout << "call desconstruct student" << std::endl;
  }
};

struct MyHash {
  size_t operator()(Student& s1) {
    int seed = 0;
    std::shared_ptr<Student> s_ptr(new Student("xiaoming", 20));
    // boost::hash_combine(seed, s_ptr);  //   ???????????? no mathcing boost::hash_combine
  }
};

template <class T>
struct MyTypeTraits {
  typedef T my_type;
  MyTypeTraits(T a) {
    std::cout << type_id_with_cvr<decltype(a)>().pretty_name()
              << std::endl;  // Student const 类模板实例化什么类型就是类型
  }
};

void TestVector(std::vector<int> vec) {
  std::cout << "one" << std::endl;
}

Student TestStudent() {
  Student stu;
  return stu;
}

extern Student
    global_stu;  // 全局声明，不会分配内存，那cout分配内存并初始化的代码是在哪个文件中？？？？？？？？？？？？？？？？？？？？  ostream，string 为类模板

int main() {
  using namespace std;

  // std::map<std::string, int> maps;
  // auto pairs = maps.insert(std::make_pair(std::string("abc"), 20));
  // std::cout << (pairs.first)->first << std::endl;

  // std::cout << maps["abc"] << std::endl;

  // map<string, int> maps;
  // maps.insert(make_pair(string("a"), 10));
  // maps.insert(make_pair(string("b"), 20));
  // maps.insert(make_pair(string("c"), 30));
  // maps.insert(make_pair(string("d"), 40));

  // for (pair<const string, int>& get_pair : maps) {  // map迭代器返回的pair key类型为const 类型要一致，避免产生临时对象
  //   cout << "key is: " << get_pair.first << "value is: " << get_pair.second << endl;
  // }

  // istream_iterator<int> eos;       // 蛮好用的输入操作，就是没有错误提示信息
  // istream_iterator<int> in_stream(cin);
  // while (in_stream != eos) {
  //   int value = *in_stream;
  //   cout << "----" << endl;
  //   ++in_stream;
  // }

  auto tuple_s = make_tuple(100, 200, "abcdf");
  std::cout << type_id_with_cvr<decltype(tuple_s)>().pretty_name()
            << std::endl;  // std::__1::tuple<int, int, char const*>

  tuple<int, double, char, float, string> nums(20, 30.0, 'c', 20.5, string("xiaozhu"));
  tuple<int, double, char, float, string> nums_one(20, 30.0, 'c', 20.5, string("xiaozhu"));
  cout << (nums_one == nums ? "true" : "false") << endl;
  cout << get<0>(nums) << endl;

  cout << boost::has_trivial_destructor<Student>::value << endl;
  cout << is_destructible<Student>::value << endl;

  typename MyTypeTraits<Student const>::my_type stu("xiaozhuzhu", 20);
  cout << type_id_with_cvr<decltype(stu)>().pretty_name() << endl;  // Student const 不愧为类型萃取....

  const Student stu_2("xiaoxing", 30);
  MyTypeTraits<Student const> my_traits(stu_2);

  int const const_int = 20;
  test<int const>(const_int);

  Student holder_stu;
  Student& ref_stu =
      holder_stu;  // 左值引用绑定，不产生任何函数调用    函数传参也是如此  Student stu = ref_stu  产生拷贝构造
  Student&& right_ref_stu =
      Student();  // 右值引用绑定，不产生任何函数调用，函数传参也是如此    Student stu = right_ref_stu  产生移动构造

  // vector<int> vecs = vector<int>{1, 2, 3, 4, 5, 6};    // use move construct
  TestVector(vector<int>{1, 2, 3, 4, 5, 6});  // use move construct
  // make_shared<vector<int>>()      // 运用了new 定位符
  // func(vector<int> vecs) : 当利用以下调用方式   func(vector<int>{1, 2, 3, 4, 5, 6}); 传参调用移动构造后，并且全表达式结束后才销毁临时对象
  // func(vector<int>&& vecs) : 当利用以下调用方式 func(vector<int>{1, 2, 3, 4, 5, 6});    传参并不调用任何函数，引用了临时对象，当分号之前的全表达式执行完，才销毁临时对象
  // 传参调用移动构造后，临时对象销毁;
  {
    Student const& stu_ref = TestStudent();  //调用一次析构
    std::cout << "eeeee" << std::endl;
  }
}

```

```cpp {.line-numbers, highlight=[6]}

#include <cstddef>
#include <functional>
#include <iostream>
int main() {
  char* str        = new char[20];
  size_t hash_code = std::hash<char*>()(str);  // 模板特化，根据泛化再特化
  std::cout << hash_code << std::endl;
}

```
