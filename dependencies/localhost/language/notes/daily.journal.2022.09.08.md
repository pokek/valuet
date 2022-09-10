---
id: n66uz7vh7rjkqrsetuo0a05
title: '2022-09-08'
desc: ''
updated: 1662798040712
created: 1662601618132
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

# 2022年9月8日

## 15点25分

### Explain语句结果解析

1. select type表示select语句的类型(有外部select语句，和子语句),table type表示查找表中记录的方式(all-全表查找，index-索引查找，range-范围查找等);
2. possible_keys(查找该记录可能需要的键)，keys(查找该记录真正用到的键),keys一定出现在possible_keys中；
3. xtra: -using where -using temporary(一般group by,order by出现较多，有一个中间缓存存储中间结果) -using filesort(order by如果没用到索引，就采用此方法)

### 一些sql优化手段和什么时候用索引，什么时候不用索引以及union关键字

#### sql优化手段

1. 不要进行类型强制转换，如varchar = 123456，就不会用到索引
2. 利用前缀索引(减少比较)，覆盖索引(减少回表)
3. 选择条件中有等号和范围，等号放最前面(最左匹配原则)，利用联合索引

#### 什么时候用索引

1. 经常出现where或order by中的字段就可以用索引
2. 高并发下一般用联合索引
3. 聚合函数的列也可以用索引，如max(item_id),count(item_id)等
4. 做为外键连接的键用索引

#### 什么时候不用索引

1. 经常增删改的字段就不用
2. 字段重复值多就不用
3. 表记录太少无需建索引，少于200条记录，mysql直接把全部记录加载进内存查找，查找速度已经很快

#### union关键字

union关键字可以把不同表的不同字段的记录(但列数必须相等)合并起来成为一张新表，且字句去除重复记录(==把两者结果集放入一块内存进行去重==)，union all不去除字句重复记录
> ![](/assets/images/2022-09-08-16-04-35.png)
> ![](/assets/images/2022-09-08-16-05-06.png)

## 23点09分

### 刷题

Leecode 93. [复原 IP 地址](https://leetcode.cn/problems/restore-ip-addresses/)

```java
class Solution {
    List<String> res = new ArrayList<>();
    int[] segements = new int[4];
    public List<String> restoreIpAddresses(String s) {
        dfs(s, 0, 0);
        return res;

    }
    
    // 从start开始搜索满足条件的sectId位置
    public void dfs(String s, int sectId, int start){
        if(sectId == 4){
            if(start == s.length()){
                StringBuilder sb = new StringBuilder();
                for(int i = 0; i < segements.length; i++){
                    sb.append(segements[i]);
                    if(i < 3){
                        sb.append(".");
                    }
                }
                res.add(sb.toString());
            }
            return;
        }

        if(start == s.length()){
            return;
        }

        if(s.charAt(start) == '0'){
            segements[sectId] = 0;
            dfs(s, sectId + 1, start + 1);
            return;

        }
        // 每一个搜索初始值为0
        int temp = 0;
        for(int end = start; end < s.length(); end++){
            temp = temp * 10 + (s.charAt(end) - '0');
            if(temp > 0 && temp <= 0xFF){
                segements[sectId] = temp;
                dfs(s, sectId + 1, end + 1);
            }else{
                break;
            }
        }               
    }
}
```
