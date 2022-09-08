---
id: n66uz7vh7rjkqrsetuo0a05
title: '2022-09-08'
desc: ''
updated: 1662623486264
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

### 一些sql优化手段和什么时候用索引，什么时候不用索引

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