---
id: 8yqto0kg7m9l1epwka4wmrc
title: thread
desc: ''
updated: 1667983423777
created: 1667878715955
---

### 对象中带互斥量

```cpp {.line-numbers}
#include <chrono>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>

#include <_mingw_stat64.h>

using namespace std;

class SharedObject {
 public:
  int shared_num = 0;

 private:
  mutex mux;

 public:
  void AddOne() {
    lock_guard<mutex> l1(mux);
    for (int i = 1; i <= 200000; ++i) {
      ++shared_num;
    }
  }

  void AddTwo() {
    lock_guard<mutex> l2(mux);
    for (int i = 1; i <= 200000; ++i) {
      ++shared_num;
    }
  }
};

int main() {
  SharedObject thread_object;
  void (SharedObject::*f1)() = &SharedObject::AddOne;
  void (SharedObject::*f2)() = &SharedObject::AddTwo;

  thread t1(f1, &thread_object);  // 非静态成员函数指针，需要传入对象指针参数
  thread t2(f2, &thread_object);

  this_thread::sleep_for(chrono::seconds(20));
  cout << thread_object.shared_num << endl;
}


```

### 实现生产者和消费者模式

- [ ] 实现生产者和消费者模式

```cpp {.line-numbers}

#include <algorithm>
#include <array>
#include <condition_variable>
#include <cstdio>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <type_traits>
using namespace std;

class Factory {
 public:
  queue<int> que;

 private:
  condition_variable s1;
  mutex mux;

 public:
  void Producer() {
    unique_lock<mutex> l1(mux);
    while (true) {
      if (que.empty()) {
        cout << "producer -> 1" << endl;
        que.push(1);
        s1.notify_all();
      } else {
        s1.wait(l1);
      }
    }
  }

  void Consumer() {
    unique_lock<mutex> l2(mux);
    while (true) {
      if (!que.empty()) {
        cout << "cosumer <- 1" << endl;
        que.pop();
        s1.notify_all();
      } else {
        s1.wait(l2);
      }
    }
  }
};

int main() {
  Factory factory;
  thread t1(&Factory::Producer, &factory);
  thread t2(&Factory::Consumer, &factory);
  t1.join();
  t2.join();
}


```
