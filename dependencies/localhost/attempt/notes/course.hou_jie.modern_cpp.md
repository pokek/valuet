---
id: j1lxx005wb4ryzmqvimkj0v
title: Modern_cpp
desc: ''
updated: 1668693057179
created: 1667228535999
---

## valriaric template(可变参模板)

```cpp

#include <iostream>

void PrintF() {}

template <typename T, typename... Type>
void PrintF(T const& arg1, Type const&... args) {
  std::cout << arg1 << std::endl;
  PrintF(args...);
}

int main() {
  PrintF("xiaoming", 20, 30);
}

// xiaoming
// 20
// 30

```

### test

```cpp {.line-numbers, highlight=[24, 26]}
// 移动语义
#include <functional>
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

#include <boost/type_index.hpp>

using boost::typeindex::type_id_with_cvr;

struct Student {
  std::string name_;
  int age_;
};

template <typename T>
void test(T&& t) {
  std::cout << std::is_lvalue_reference<T>() << std::endl;
  std::cout << type_id_with_cvr<decltype(t)>().pretty_name() << std::endl;
}

int main() {
  Student&& stu = Student();  // stu为泛左值
  Student s     = Student();
  test(stu);  // 自动推断为  Student&
}

```

## 别名模板和模板模板参数

```cpp
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <boost/type_index.hpp>

using boost::typeindex::type_id_with_cvr;

template <typename T>
using Vec = std::vector<T, std::allocator<T>>;

template <typename T, template <class> class Container>
void func(T t) {
  Container<T> vec;
  std::cout << type_id_with_cvr<decltype(vec)>().pretty_name() << std::endl;
}

template <typename T, template <class> class Container>
class MyVec {
 public:
  Container<T> container;
  MyVec() {
    std::cout << type_id_with_cvr<decltype(container)>().pretty_name() << std::endl;
  }
};

int main() {
  func<std::string, Vec>(std::string("avc"));
  MyVec<std::string, Vec> vec;
}

```

### test

```cpp {.line-numbers, highlight=[15]}
#include <vector>

class Student {
 public:
  Student()                              = default;
  Student(Student const& src)            = default;
  Student& operator=(Student const& src) = default;
  Student& operator=(Student&& src)      = delete;
  Student(Student&& src)                 = delete;
  ~Student()                             = default;
};

int main() {
  std::vector<Student> vec;
  vec.push_back(Student());  // vector传无移动意义临时变量，会报错
}

```

```cpp {.line-numbers, highlight=[12]}
#include <iostream>

#include <boost/type_index.hpp>

using boost::typeindex::type_id_with_cvr;

int main() {
  auto tmp = [](int a, int b) -> int {
    return a + b;
  };

  std::cout << type_id_with_cvr<decltype(tmp)>().pretty_name() << std::endl;    // main::$_0
}

```

```cpp {.line-numbers, highlight=[23]}
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

#include <__algorithm/remove_if.h>

int main() {
  auto cmp = [](int a, int b) {
    return a > b;
  };
  std::set<int, decltype(cmp)> sets({1, 2, 3, 4, 5, 6}, cmp);
  for (int num : sets) {
    std::cout << num << std::endl;
  }

  std::cout << "------------" << std::endl;

  std::vector<int> vec{10, 20, 30, 40, 50, 60, 70, 80, 90};
  int x = 30;
  int y = 80;

  // remove_if()把不在范围内的元素往前填充，返回在范围内的迭代器，vec.end()迭代器不变
  vec.erase(std::remove_if(vec.begin(), vec.end(), [x, y](int item) { return x < item && item < y; }), vec.end());
  for (int ele : vec) {
    std::cout << ele << std::endl;
  }
}

```

## 可变参数模板

```cpp {.line-numbers, highlight=[25]}

#include <bitset>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>

void PrintfFuc() {}

template <typename T, typename... Types>
void PrintfFuc(T const& t, Types... t_types) {
  std::cout << t << std::endl;
  PrintfFuc(t_types...);
}

class Student {
 public:
  static int age_;
};

int Student::age_ = 20;

int main() {
  PrintfFuc(20, std::string("abc"), std::bitset<60>(2000));
  std::cout << sizeof(std::bitset<60>)
            << std::endl;  // unsigned long long 8个字节  利用unsigned long long数组 元素的二进制位数代表所需要的位
  std::cout << sizeof(size_t) << std::endl;              // 8
  std::cout << sizeof(unsigned long long) << std::endl;  // 8
  uint64_t nums[80];
  std::cout << sizeof(nums) << std::endl;  // 640

  std::cout << sizeof(Student) << std::endl;  // 静态变量存在全局区
}

```

```cpp
// 可变参数模板实现printf功能
#include <exception>
#include <iostream>
#include <stdexcept>

void Printf(char const* chrs) {
  while (*chrs) {
    if (*chrs == '%' && *(++chrs) != '%') {
      throw std::runtime_error("format is not legal");
    }
    std::cout << *(chrs++);
  }
}

template <typename T, typename... Types>
void Printf(char const* chrs, T const& t, Types... types) {
  while (*chrs) {
    if (*chrs == '%' && *(++chrs) != '%') {
      std::cout << t;
      Printf(++chrs, types...);
      return;
    }
    std::cout << *(chrs++);
  }
  throw std::runtime_error("aruguments is not leagal");
}

int main() {
  Printf("aaa wingo  wojgw %d, wjgow, %c", 20, 'd');
}

```

```cpp
#include <algorithm>
#include <iostream>

int MaxMinum(int n) {
  return n;
}

template <typename... Types>
int MaxMinum(int n, Types... nums) {
  return std::max(n, MaxMinum(nums...));
}

int main() {
  std::cout << MaxMinum(10, 20, 30, 50, 90, 20, 23, 100) << std::endl;
}


```

```cpp
// 打印元组 tuple
#include <__tuple>
#include <iostream>
#include <ostream>
#include <string>
#include <tuple>

template <int IDX, int MAX, typename... Types>
class Printf {
 public:
  static void TuplePrintf(std::ostream& out, std::tuple<Types...> tuples) {
    out << std::get<IDX>(tuples) << (IDX + 1 == MAX ? "" : ", ");
    Printf<IDX + 1, MAX, Types...>::TuplePrintf(out, tuples);
  }
};

template <int MAX, typename... Types>
class Printf<MAX, MAX, Types...> {
 public:
  static void TuplePrintf(std::ostream& out, std::tuple<Types...> tuples) {}
};

template <typename... Types>
void PrintfTuple(std::tuple<Types...> tuples) {
  std::cout << "[";
  Printf<0, sizeof...(Types), Types...>::TuplePrintf(std::cout, tuples);
  std::cout << "]";
}

int main() {
  PrintfTuple(std::make_tuple(20, 30, 40, std::string("abc")));
}

```

## 右值和右值引用

```cpp {.line-numbers, highlight=[23]}

#include <iostream>
#include <utility>
#include <vector>

#include <boost/type_index.hpp>

using boost::typeindex::type_id_with_cvr;

class Student {
 public:
  Student() {}
  Student(Student const& src) {
    std::cout << "copy" << std::endl;
  }
  Student(Student&& src) noexcept {
    std::cout << "move" << std::endl;
  }
};

template <typename T>
void PushBack(T&& src) {
  // std::cout << type_id_with_cvr<decltype(src)>().pretty_name() << std::endl;
  Student stu(std::forward<T>(src));  // 完美转发  需函数模板实例化
}

int main() {
  PushBack(Student());
}


```

### test

```cpp {.line-numbers, highlight=[20-22]}

#include <__tuple>
#include <iostream>
#include <string>
#include <tuple>

class Student {
 public:
  Student() {
    std::cout << "default construct" << std::endl;
  }
  Student(Student const& src) {
    std::cout << "copy" << std::endl;
  }
  Student(Student&& src) {
    std::cout << "move" << std::endl;
  }
};

int main() {
  Student stu = Student();  // default contruct，move
  Student&& r_ref = Student();  // default construct
  Student l_value = r_ref;      // copy
}

```

- [ ] ### [返回值类型为右值引用](https://www.zhihu.com/question/22941176)
