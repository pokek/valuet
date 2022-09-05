---
id: zgt03js3tr5z823zo638ivp
title: '2022-09-04'
desc: ''
updated: 1662294791762
created: 1662252585338
traitIds:
  - journalNote
---
This template was applied using the daily journal schema. Edit the [[templates.daily]] note to change this template.
To create your own schemas to auto-apply templates when they match a hierarchy, follow the [schema tutorial](https://blog.dendron.so/notes/P1DL2uXHpKUCa7hLiFbFA/) to get started.

<!--
Based on the journaling method created by Intelligent Change:
- [Intelligent Change: Our Story](https://www.intelligentchange.com/pages/our-story)
- [The Five Minute Journal](https://www.intelligentchange.com/products/the-five-minute-journal)
-->

# 2022年9月4日

## 08点52分

### Mysql死锁处理方式

1. 死锁等待，直至等待超时后就回滚事务
2. 检测死锁，检测方式:以事务为节点，锁为边，构成一个有向图，判断图是否存在环，存在就存在死锁，之后回滚其中一个事务，让其它事务执行****

### Mysql索引

索引本身为一种数据结构存在磁盘中，好的索引结构能够减少磁盘操作io次数，提高查找效率。

#### 索引分类

1. 按照索引数据结构来看的话，有哈希索引，B+树索引(类似目录查找)等
2. 按照索引存储类型来看的话，有聚簇索引(主键索引，==叶子节点存储记录数据==)，二级索引(辅助索引，==叶子节点存储主键索引值==)
3. 按照索引字段个数来看的话，有单列索引，联合索引(==遵循最左匹配原则，索引下推优化==)
4. 按照字段特性来看的话，有主键索引，唯一索引，普通索引，前缀索引。
*[遵循最左匹配原则]: 如创建一个(a, b, c)的联合索引 where a == 1 and b == 2 and c == 3会采用联合索引，(**在a中b局部有序，b中c局部有序**)，而where b== 3 and c== 4就无法使用到联合索引。
最左匹配原则
*[索引下推优化]: 在创建后(a,b,c)联合索引后，在最左匹配原则下，若最左字段使用范围查找的话，后边的字段就用不到联合索引，如where a > 10 and b == 3中a可以使用联合索引，b就使用不了，为减少回表次数，就进行索引下推至引擎层进行后面字段判断，去除不符合条件的记录。
索引下推优化
*[二级索引]: 如果查找的为叶子节点存的值，就无需进行回表操作，也就称为覆盖索引
二级索引

> ![](/assets/images/2022-09-04-09-55-01.png)

## 20点20分

### leecode 1143

==string.charAt() stringbuilder.charAt()==
[最长公共子序列](https://leetcode.cn/problems/longest-common-subsequence/)

```java{.line-numbers}
class Solution {

    public int longestCommonSubsequence(String text1, String text2) {
    
        int m = text1.length();
        int n = text2.length();

        // dp[i][j] 表示text1[0...i],text2[0...j]的最大子序列
        /**
            1....
            2..(i-1, j-1).. (i-1, j)  
            3....(i, j -1)(i, j)  

         */
        int[][] dp = new int[m + 1][n + 1];
        for(int i = 1; i < m + 1; i++){
            for(int j = 1; j < n + 1; j++){
                // 相等转移
                if(text1.charAt(i - 1) == text2.charAt(j - 1)){
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                }else{
                  // 位于i和j的字符不相等，那就取位于i和j-1字符 & i - 1, j的最大子序列
                    dp[i][j] = Math.max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[m][n];
    }
}
```
