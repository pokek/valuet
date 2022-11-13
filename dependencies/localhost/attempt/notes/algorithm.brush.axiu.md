---
id: tpzqmazd4ztfsnwl1en0x1q
title: Axiu
desc: ''
updated: 1666015467788
created: 1666014869640
---
# 阿秀的刷题规划

## 快速刷完67道剑指offer

### [剑指 Offer 04. 二维数组中的查找](https://leetcode.cn/problems/er-wei-shu-zu-zhong-de-cha-zhao-lcof/)

```c
/*
 * 输入 **matrix 是长度为 matrixSize 的数组指针的数组，其中每个元素（也是一个数组）
 * 的长度组成 *matrixColSize 数组作为另一输入，*matrixColSize 数组的长度也为 matrixSize
 */
bool findNumberIn2DArray(int** matrix, int matrixSize, int* matrixColSize, int target){
    // 方法一：暴力
    // int i, j;
    // for(i = 0; i < matrixSize; ++i){
    //     for(j = 0; j < matrixColSize[i]; ++j){
    //         if(matrix[i][j] == target){
    //             return true;
    //         }
    //     }
    // }
    // return false;

}
```

```cpp
class Solution {
 public:
  bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
    // 方法一：暴力
    // for(int i = 0; i < matrix.size(); ++i) {
    //   for (int j = 0; j < matrix[i].size(); ++j) {
    //     if (matrix[i][j] == target) {
    //       return true;
    //     }
    //   }
    // }
    // return false;
  }
};

```
