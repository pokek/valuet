---
id: 9tmie2g1tw7dokice7ia8g5
title: Alogrithm
desc: ''
updated: 1667726405508
created: 1667726340378
---

```cpp {.line-numbers}

#include <algorithm>
#include <array>
#include <cstddef>
#include <deque>
#include <forward_list>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

namespace test_array {
void test() {
  // 初始化对象分配在栈上，内部为默认数组，对象内存大小等于数组元素内存大小
  // 编译器默认生成 big five (空参构造，拷贝构造，移动构造，拷贝赋值，移动赋值，默认析构)，便于编译器加上自己想要加上的一些相关代码
  // 基本类型
  array<int, 20> nums{1, 20, 30};  // 先构造成员，再构造自身，因此是对内部数组先进行初始化
  array<int, 20> nums_two{10, 30, 50};
  nums = nums_two;
  for (int num : nums) {
    cout << num << endl;
  }
  cout << "---------" << endl;
  nums.fill(-1);                // 相同元素填满容器
  int* nums_ptr = nums.data();  // 获取内部数组首元素指针
  for (int i = 0; i < nums.size(); ++i) {
    cout << *(nums_ptr++) << endl;  // 简单来说就是size = max_size ，因为就是一个固定元素数量个数的常规数组
  }
  cout << "----" << endl;
  // string类型
  array<string, 10> string_array{
      "abc", "wing", "wgwg"};  // begin返回数组首元素迭代器，end返回整个数组的尾部元素时候迭代器
  cout << string_array.size() << endl;      // 10
  cout << string_array.max_size() << endl;  // 10
  for (int i = string_array.size(); i >= 0; --i) {
    cout << string_array[i] << endl;
  }
  cout << "------" << endl;
  array<string, 5> arrays_string{"abc", "cdf", "efd", "rgd", "wgww"};
  reverse_copy(arrays_string.begin(), arrays_string.end(), ostream_iterator<string>(cout, ", "));
}

}  // namespace test_array

namespace test_vector {
void test() {
  // vector对象本身有3个迭代器，在栈上，但是牵连着堆中数据
  // 基本数据类型
  vector<int> vec{10, 20, 30, 40, 50};
  cout << vec.capacity() << endl;  // 5
  cout << vec.size() << endl;      // 5
  vec.push_back(100);
  vec.push_back(200);
  vec.push_back(300);
  cout << vec.capacity() << endl;
  cout << vec.size() << endl;
}

}  // namespace test_vector

namespace test_alogrithm_ajact_find {
void test() {
  list<int> int_list;
  int_list.push_back(10);
  int_list.push_back(20);
  int_list.push_back(30);
  int_list.push_back(40);
  int_list.push_back(40);
  cout << "original ele is ";
  for (int ele : int_list) {
    cout << ele << ", ";
  }
  cout << endl;
  list<int>::iterator iter = adjacent_find(int_list.begin(), int_list.end());
  if (iter != int_list.end()) {
    cout << "find equal value is " << *iter << endl;
  } else {
    cout << "not find equal value " << endl;
  }

  iter = adjacent_find(int_list.begin(), int_list.end(), [](int ele1, int ele2) { return ele1 * 2 == ele2; });
  if (iter != int_list.end()) {
    cout << "find ele1 * 2 == ele2  ele1 is " << *(iter++) << ", ele2 is " << *iter << endl;
  } else {
    cout << "not find ele1 * 2 == ele2" << endl;
  }
}
}  // namespace test_alogrithm_ajact_find

namespace test_alogrithm_all_of {
void test() {
  list<int> int_list{10, 20, 30, 40, 50};
  cout << "orignial value is ";
  for_each(int_list.begin(), int_list.end(), [](int ele) { cout << ele << ", "; });
  cout << endl;
  auto pre = [](int item) {
    return !(item % 2);
  };
  if (all_of(int_list.begin(), int_list.end(), pre)) {
    cout << "all element is even number" << endl;
  } else {
    cout << "not all element is even number" << endl;
  }
}

}  // namespace test_alogrithm_all_of

namespace test_alogrithm_any_of {
void test() {
  list<int> int_list{11, 21, 53, 67, 30};
  cout << "origianl number is ";
  auto print = [](int ele) {
    cout << ele << ", ";
  };
  for_each(int_list.begin(), int_list.end(), print);
  cout << endl;
  auto pre = [](int item) {
    return !(item % 2);
  };
  if (any_of(int_list.begin(), int_list.end(), pre)) {
    cout << "exists even number" << endl;
  } else {
    cout << "not exists even number" << endl;
  }
}
}  // namespace test_alogrithm_any_of

namespace test_alogrithm_binary_search {
// sort 和 binary_search的谓词规则需要一致
void test() {
  auto print = [](int ele) {
    cout << ele << ", ";
  };  // 打印

  list<int> int_list{50, 10, 30, 20, 25, 5};

  cout << "orinail value is ";
  for_each(int_list.begin(), int_list.end(), print);
  cout << endl;

  int_list.sort();

  cout << "sort value is ";
  for_each(int_list.begin(), int_list.end(), print);
  cout << endl;

  if (binary_search(int_list.begin(), int_list.end(), 30)) {
    cout << "find value = 30" << endl;
  } else {
    cout << "not find value = 30" << endl;
  }  // 二分查找

  int_list.sort(greater<int>());

  cout << "in greater  sort value is ";
  for_each(int_list.begin(), int_list.end(), print);
  cout << endl;

  if (binary_search(int_list.begin(), int_list.end(), 30, greater<int>())) {
    cout << "find value = 30" << endl;
  } else {
    cout << "not find value = 30" << endl;
  }  // 二分查找

  auto custom_cmp = [](int ele1, int ele2) {
    if (ele1 < 0) {
      ele1 = -ele1;
    }
    if (ele2 < 0) {
      ele2 = -ele2;
    }
    return ele1 < ele2;
  };  // 比较绝对值

  vector<int> vec_int{-2, -1, 0, 1, 2, 3, 4};

  cout << "orinail value is ";
  for_each(vec_int.begin(), vec_int.end(), print);
  cout << endl;

  sort(vec_int.begin(), vec_int.end(), custom_cmp);

  cout << "sort value is ";
  for_each(vec_int.begin(), vec_int.end(), print);
  cout << endl;

  if (binary_search(vec_int.begin(), vec_int.end(), -1, custom_cmp)) {
    cout << "find value = -1" << endl;
  } else {
    cout << "not find value = -1 " << endl;
  }  // 二分查找
}

}  // namespace test_alogrithm_binary_search

namespace test_alogrithm_copy {
// copy存在重叠范围时，往左移不会出现丢失元素，但是往右移就会出现丢失元素
void test() {
  auto print = [](int ele) {
    cout << ele << ", ";
  };  // 打印

  vector<int> vec_one;
  for (int i = 0; i <= 5; ++i) {
    vec_one.push_back(10 * i);
  }

  cout << "vec1 orignial value is ";
  for_each(vec_one.begin(), vec_one.end(), print);
  cout << endl;

  vector<int> vec_two;
  for (int i = 0; i <= 10; ++i) {
    vec_two.push_back(3 * i);
  }

  cout << "vec2 orignial value is ";
  for_each(vec_two.begin(), vec_two.end(), print);
  cout << endl;

  copy(vec_one.begin(), vec_one.begin() + 3, vec_two.begin() + 4);

  cout << "vec2 copy value is ";
  for_each(vec_two.begin(), vec_two.end(), print);
  cout << endl;

  copy(vec_two.begin() + 4, vec_two.begin() + 7, vec_two.begin() + 2);

  cout << "vec2 shift value is ";
  for_each(vec_two.begin(), vec_two.end(), print);
  cout << endl;
}

}  // namespace test_alogrithm_copy

namespace test_alogrithm_copy_backward {
// 当存在重叠范围时，右移不会导致元素丢失，从源范围最后一个元素一个一个移动
void test() {
  auto print = [](int ele) {
    cout << ele << ", ";
  };  // 打印

  vector<int> vec_one;
  for (int i = 0; i <= 5; ++i) {
    vec_one.push_back(10 * i);
  }

  cout << "vec1 orignial value is ";
  for_each(vec_one.begin(), vec_one.end(), print);
  cout << endl;

  vector<int> vec_two;
  for (int i = 0; i <= 10; ++i) {
    vec_two.push_back(3 * i);
  }

  cout << "vec2 orignial value is ";
  for_each(vec_two.begin(), vec_two.end(), print);
  cout << endl;

  copy_backward(vec_one.begin(), vec_one.begin() + 3, vec_two.begin() + 7);

  cout << "vec2 copy value is ";
  for_each(vec_two.begin(), vec_two.end(), print);
  cout << endl;

  copy_backward(vec_two.begin() + 4, vec_two.begin() + 7, vec_two.begin() + 9);

  cout << "vec2 shift value is ";
  for_each(vec_two.begin(), vec_two.end(), print);
  cout << endl;
}

}  // namespace test_alogrithm_copy_backward

namespace test_alogrithm_copy_if {
void test() {
  auto print = [](int ele) {
    cout << ele << ", ";
  };  // 打印

  list<int> src{46, 59, 88, 72, 79, 71, 60, 5, 40, 84};
  list<int> res1(src.size());
  list<int> res2(src.size());

  cout << "src orignial value is ";
  for_each(src.begin(), src.end(), print);
  cout << endl;

  auto is_even = [](int ele) {
    return !(ele % 2);
  };

  auto is_odd = [](int ele) {
    return ele % 2;
  };

  list<int>::iterator end_one = copy_if(src.begin(), src.end(), res1.begin(), is_even);
  res1.resize(std::distance(res1.begin(), end_one));

  cout << "res1 even value is ";
  for_each(res1.begin(), res1.end(), print);
  cout << endl;

  list<int>::iterator end_two = copy_if(src.begin(), src.end(), res2.begin(), is_odd);
  res2.resize(std::distance(res2.begin(), end_two));

  cout << "res2 odd value is ";
  for_each(res2.begin(), res2.end(), print);
  cout << endl;
}
}  // namespace test_alogrithm_copy_if

namespace test_alogrithm_copy_n {
void test() {
  string s1{"dandelion"};
  string s2{"badger"};

  cout << s1 << " + " << s2 << " = ";
  copy_n(s1.begin(), 3, s2.begin());
  cout << s2 << endl;
}
}  // namespace test_alogrithm_copy_n

namespace test_alogrithm_count {
void test() {
  auto print = [](int ele) {
    cout << ele << ", ";
  };  // 打印

  vector<int> vec{10, 20, 10, 40, 10};

  cout << "vec value is ";
  for_each(vec.begin(), vec.end(), print);
  cout << endl;

  vector<int>::iterator::difference_type result = count(vec.begin(), vec.end(), 10);
  cout << "in vec value 10 nums is :" << result << endl;
}
}  // namespace test_alogrithm_count

namespace test_alogrithm_count_if {
void test() {
  auto print = [](int ele) {
    cout << ele << ", ";
  };  // 打印

  vector<int> vec{10, 20, 10, 40, 10};

  cout << "vec value is ";
  for_each(vec.begin(), vec.end(), print);
  cout << endl;

  auto greater_than = [](int item) {
    return item > 10;
  };

  vector<int>::iterator::difference_type nums = count_if(vec.begin(), vec.end(), greater_than);

  cout << "value > 10 nums " << nums << endl;
}

}  // namespace test_alogrithm_count_if

namespace test_alogrithm_equal {
void test() {
  vector<int> v1{0, 5, 10, 15, 20, 25};
  vector<int> v2{0, 5, 10, 15, 20, 25};
  vector<int> v3{0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50};

  cout << "v1 is euqual v2 " << equal(v1.begin(), v1.end(), v2.begin()) << endl;
  cout << "v1 is euqual v3 " << equal(v1.begin(), v1.end(), v3.begin()) << endl;
  // cout << "v1 is equal v3 of range " << equal(v1.begin(), v1.end(), v3.begin(), v3.end()) << endl;  // c++14起才进行重载
}

}  // namespace test_alogrithm_equal

namespace test_alogrithm_equal_range {

template <typename Type>
void DumpIterator(vector<Type> const& vec,
                  pair<typename vector<Type>::iterator, typename vector<Type>::iterator> range) {
  cout << "dump value is : ";

  for (typename vector<Type>::const_iterator iter = vec.begin(); iter != vec.end();
       ++iter) {  // const_iterator为指向内容不能变，const iterator迭代器本身不能变
    if (iter == range.first) {
      cout << " [ ";
    }
    if (iter == range.second) {
      cout << " ] ";
    }
    cout << *iter << " ";
  }

  cout << endl;
}

template <typename Type>
void EqualRangeDemo(vector<Type> const& vec, Type value) {
  auto print = [](Type ele) {
    cout << ele << ", ";
  };  // 打印

  vector<Type> tmp(vec);

  sort(tmp.begin(), tmp.end());

  cout << "use default predicate sort order is : ";
  for_each(tmp.begin(), tmp.end(), print);
  cout << endl;

  pair<typename vector<Type>::iterator, typename vector<Type>::iterator> ranges =
      equal_range(tmp.begin(), tmp.end(), value);

  DumpIterator(tmp, ranges);
}

template <typename Type, typename Pf>
void EqualRangeDemo(vector<Type> const& vec, Type value, Pf predicate, string pf_name) {
  auto print = [](Type ele) {
    cout << ele << ", ";
  };  // 打印

  vector<Type> tmp(vec);

  sort(tmp.begin(), tmp.end(), predicate);

  cout << "use " << pf_name << " predicate sort order is : ";
  for_each(tmp.begin(), tmp.end(), print);
  cout << endl;

  pair<typename vector<Type>::iterator, typename vector<Type>::iterator> pairs =
      equal_range(tmp.begin(), tmp.end(), value, predicate);

  DumpIterator(tmp, pairs);
}

void test() {
  auto abs_my = [](int ele1, int ele2) {
    return abs(ele1) < abs(ele2);
  };
  auto length_than = [](string const& s1, string const& s2) {
    return s1.length() < s2.length();
  };

  vector<int> v1{-1, 0, 1, 2, 3, 4, -3, -2, -1, 0};
  EqualRangeDemo(v1, 3);
  EqualRangeDemo(v1, 3, greater<int>(), "greather");
  EqualRangeDemo(v1, 3, abs_my, "abs_my");

  vector<string> v2{"cute", "fluffy", "kittens", "fun", "meowmeowmeow", "blah"};
  EqualRangeDemo<string>(v2, "fred");
  EqualRangeDemo<string>(v2, "fred", greater<string>(), "greater");
  EqualRangeDemo<string>(v2, "fred", length_than, "length_than");
}

}  // namespace test_alogrithm_equal_range

namespace test_alogrithm_fill {
void test() {
  auto print = [](int ele) {
    cout << ele << ", ";
  };  // 打印

  vector<int> v1;

  for (int i = 0; i <= 9; ++i) {
    v1.push_back(5 * i);
  }

  cout << "defalut value is : ";
  for_each(v1.begin(), v1.end(), print);
  cout << endl;

  fill(v1.begin() + 5, v1.end(), 2);

  cout << "filled value is : ";
  for_each(v1.begin(), v1.end(), print);
  cout << endl;
}

}  // namespace test_alogrithm_fill

namespace test_alogrithm_fill_n {
void test() {
  auto print = [](int ele) {
    cout << ele << ", ";
  };  // 打印

  vector<int> v1(9);

  cout << "defalut value is : ";
  for_each(v1.begin(), v1.end(), print);
  cout << endl;

  fill_n(v1.begin(), 3, 1);

  cout << "fill 1 value is : ";
  for_each(v1.begin(), v1.end(), print);
  cout << endl;

  fill_n(v1.begin() + 3, 3, 2);

  cout << "fill 2 value is : ";
  for_each(v1.begin(), v1.end(), print);
  cout << endl;

  fill_n(v1.end() - 3, 3, 3);

  cout << "fill 2 value is : ";
  for_each(v1.begin(), v1.end(), print);
  cout << endl;
}

}  // namespace test_alogrithm_fill_n

int main() {
  // test_array::test();
  // test_vector::test();
  // test_alogrithm_ajact_find::test();
  // test_alogrithm_all_of::test();
  // test_alogrithm_any_of::test();
  // test_alogrithm_binary_search::test();
  // test_alogrithm_copy::test();
  // test_alogrithm_copy_backward::test();
  // test_alogrithm_copy_if::test();
  // test_alogrithm_copy_n::test();
  // test_alogrithm_count::test();
  // test_alogrithm_count_if::test();
  // test_alogrithm_equal::test();
  // test_alogrithm_equal_range::test();
  // test_alogrithm_fill::test();
  // test_alogrithm_fill_n::test();
}

```
