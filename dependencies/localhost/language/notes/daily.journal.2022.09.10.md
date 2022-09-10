---
id: 2hk9so3u6ari7xipw6yxxvw
title: '2022-09-10'
desc: ''
updated: 1662812337410
created: 1662779852525
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

# 2022年9月10日

## 11点17分

### SQL注入

1. 逻辑运算符优先级，逻辑与(&&)大于逻辑或(||)
2.

```java
// 未做参数检查，导致sql注入
// userName和 password 设置为 “1' or '1'='1”绕过用户名/密码的检查直接进入系统了
 SELECT COUNT(userId) FROM t_user WHERE userName='"+userName+"' AND password ='"+password+"'; 

 ```

3. 经典案例

> ![](/assets/images/2022-09-10-11-20-08.png)
![](/assets/images/2022-09-10-11-23-48.png)

## 15点16分

### SQL语句执行流程

1. 客户端与Mysql服务建立TCP连接，Mysql进行权限验证，并分配相关资源给客户端
2. 然后根据语句分发器判断SQL语句是否为select语句，若为select语句并且具有查询权限，则进行缓存查找，若缓存中有相关数据则进行返回，没有就执行下一步
3. Mysql分析器对SQL语句进行句子分析判断句子是否合法，非法则抛出异常，否则进行下一步
4. 预处理器对语句进行相关表名，字段名等处理，判断是否是合法表名，字段名等，合法进行下一步
5. 优化器会根据句子字段索引，选择最优语句执行计划，生成相应语句执行计划后，进入下一步
6. 执行器查询是否具有查询权限，有则进行SQL语句执行，并把语句结果集存入缓存并且返回给客户端

### SQL语句优化以及索引优化以及内外连接以及group by关键字以及in与exist区别

#### SQL语句优化(避免全表扫描)

1. where中不用or，用union all
2. 避免使用in，not in，而使用between and
3. 复合索引符合最左匹配原则
4. 不要进行非null判断
5. 不用使用以通配符开头like的字符串匹配
6. 类型转换会使索引失效
7. 不在where子句中进行字段表达式操作和函数操作

#### 索引优化

1. 联合索引，把排序分组出现频率较高的字段放在最左边
2. 利用前缀索引
3. 模糊查询使用==全文索引==

>![](/assets/images/2022-09-10-16-43-28.png)

#### 内外连接(Mysql)

1. inner join内连接，找出符合连接条件的全部记录
2. left join 左外连接, 找出符合连接条件的全部记录，并且左表记录全部保留
3. right join 右外连接，找出符合连接条件的全部记录，并且右表记录全部保留
4. full join(Mysql暂不支持) 完全外连接，找出符合连接条件的全部记录，并且左右表记录全部保留

>![](/assets/images/2022-09-10-19-51-15.png)

#### group by关键字

group by关键字用于分组情景，可与having进行组内聚合结果筛选，一个分组只允许一条可用记录
>![](/assets/images/2022-09-10-19-56-45.png)

#### in与exist区别

in进行查询相当于查询多次表，A exist B先遍历A表然后看是否在B表中
,如果两张表A(大表),B(小表)，in适用于外查询为大表，子查询为小表，exist适用于外查询为小表，子查询为大表

#### 数据量大的情况下

1. 加上查询条件
2. 读写分离，主写从读
3. 垂直拆分，水平拆分

### SQL语句执行顺序

select ..distinct.. from ..join..on.. where..group by..having..union...order by...limit
执行顺序如下:

1. from
2. on
3. join
4. where
5. group by
6. having(筛选聚合字段结果)
7. distinct
8. union
9. order by
10. limit
