---
id: k3wsf2016m2fc0o33oe6ae3
title: '2022-09-24'
desc: ''
updated: 1664016534486
created: 1664016397833
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

# 2022年9月24日

## 18点46分

### 刷题

1. 判断回文数

```java {.line-numbers, highlight=[7]}
    // 判断回文数
    public static boolean isPalindromeNumber(int num) {
        int sum = 0;
        int val = num;

        while(val != 0){
          // += 和 = 分清楚 +=在原有基础上加值并赋值
            sum = sum * 10 + val % 10;     // 求余取个位
            val /= 10;                     // 除法去除个位

        }

        if(sum == num){
            return true;
        }

        return false;
    }
```
