---
id: ji977vg4t7h66afvrppwt8k
title: Karel_code
desc: ''
updated: 1668153879092
created: 1667983505401
---

## [704. 二分查找](https://leetcode.cn/problems/binary-search/)

```cpp{.line-numbers, highlight=[7]}

#include <vector>

using namespace std;

class Solution {
 public:
 // 循环不变量为区间
  int search(vector<int>& nums, int target) {
    int l_bound = 0;
    int r_bound = nums.size();
    while (l_bound < r_bound) {
      int mid = l_bound + (r_bound - l_bound) / 2;
      if (nums[mid] > target) {
        r_bound = mid;              
      } else if (nums[mid] < target) {
        l_bound = mid + 1;
      } else {
        return mid;
      }
    }
    return -1;
  }
};

```

## [27. 移除元素](https://leetcode.cn/problems/remove-element/)

```cpp {.line-numbers, highlight=[7]}

#include <vector>

using namespace std;

class Solution {
 public:
  // 快慢指针
  int removeElement(vector<int>& nums, int val) {
    int left  = 0;
    int right = 0;
    int len   = nums.size();
    while (right < len) {
      if (nums[right] != val) {
        // swap(nums[left], nums[right]);      // 影响执行效率，题意为移出即可  
        nums[left] = nums[right];
        ++left;
      }
      ++right;
    }
    return left;
  }

  void swap(int& a, int& b) {
    int temp = a;
    a        = b;
    b        = temp;
  }
};

```

## [35.搜索插入位置](https://leetcode.cn/problems/search-insert-position/)

```cpp {.line-numbers, highlight=[]}

#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
 // 二分查找
  int searchInsert(vector<int>& nums, int target) {
    int left_bound  = 0;
    int right_bound = nums.size();
    while (left_bound < right_bound) {
      int mid = left_bound + (right_bound - left_bound) / 2;
      if (nums[mid] > target) {
        right_bound = mid;
      } else if (nums[mid] < target) {
        left_bound = mid + 1;
      } else {
        return mid;
      }
    }
    return left_bound;
  }
};

```

## [34. 在排序数组中查找元素的第一个和最后一个位置](https://leetcode.cn/problems/find-first-and-last-position-of-element-in-sorted-array/)

```cpp {.line-numbers, highlight=[]}

#include <chrono>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
 // 二分查找
  vector<int> searchRange(vector<int>& nums, int target) {
    vector<int> res{-1, -1};
    if (nums.size() == 0) {
      return res;
    }
    res[0] = FindLeftBound(nums, target);
    res[1] = FindRightBound(nums, target);
    return res;
  }

  int FindLeftBound(vector<int>& nums, int target) {
    int left_bound  = 0;
    int right_bound = nums.size();
    while (left_bound < right_bound) {
      int mid = left_bound + (right_bound - left_bound) / 2;
      if (nums[mid] < target) {
        left_bound = mid + 1;
      } else {
        right_bound = mid;
      }
    }
    return (left_bound >= 0 && left_bound < nums.size() && nums[left_bound] == target) ? left_bound : -1; // 判断数组索引是否越界
  }

  int FindRightBound(vector<int>& nums, int target) {
    int left_bound  = 0;
    int right_bound = nums.size();
    while (left_bound < right_bound) {
      int mid = left_bound + (right_bound - left_bound) / 2;
      if (nums[mid] <= target) {
        left_bound = mid + 1;
      } else {
        right_bound = mid;
      }
    }
    return (left_bound - 1 >= 0 && left_bound - 1 < nums.size() && nums[left_bound - 1] == target) ? left_bound - 1
                                                                                                   : -1;
  }
};

```
