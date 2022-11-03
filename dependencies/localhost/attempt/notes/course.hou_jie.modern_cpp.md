---
id: j1lxx005wb4ryzmqvimkj0v
title: Modern_cpp
desc: ''
updated: 1667229825814
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
