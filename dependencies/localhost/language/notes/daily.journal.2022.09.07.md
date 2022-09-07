---
id: a2ix85rnhq20pjllm3i9s05
title: '2022-09-07'
desc: ''
updated: 1662565910627
created: 1662516924640
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

# 2022年9月7日

## 10点51分

### M阶B树

1. B树中的子节点最多有M个
2. 根节点最少有两个节点，除根节点和叶子节点的其它节点最少有m/2个子节点

- [ ] 3....

#### B树B+树

两者不同之处在于：B树中间节点存相关数据信息，B+树只有叶子节点存储数据信息，其它节点作为索引使用，因此在==同一磁盘分页大小相同的情况下==B+树比B树==存储更多的节点信息==，在磁盘查找的工作原理下，(局部性原理),能够比B树减少IO次数，更适合作为磁盘数据存储的数据结构。
*[在磁盘查找的工作原理下]: 磁盘找数据有一个预读功能(根据操作系统的局部性原理)，每次都磁盘都从同一个位置开始，根据所需的数据大小往后去读。
*[局部性原理]: 操作系统在一段时间内，只处理一段程序资源(占用一段硬件资源)，B+树每一次就读取磁盘中的一页。

#### 二叉搜索树和AVL树和红黑树

1. 二叉搜索树，AVL树，红黑树都不适合做磁盘数据存储索引，节点之间逻辑上可能相对较近，但实际存储过程中物理空间之上就可能很远，io操作次数就会很多(O(logN))
2. 二叉搜索树==最好时间复杂度O(logN)，最坏O(N)==,因此引入AVL和红黑树这==两个自平衡树(红黑树并不是高度平衡)平均查找时间复杂度O(logN)==
3. AVL树和红黑树插入和删除都需要进行旋转自平衡，==AVL树插入最多旋转一次(O(logN)),删除最多旋转log(N)次，每次O(2log(N)),红黑树插入最多旋转2次，删除最多旋转3次，变色操作需要O(log(N))的时间复杂度==

## 13点57分

### 云和恩墨（北京）信息技术有限公司笔试

1. ER图为实体-关系模型，为数据库管理数据的数据模型
2. sql四大语言：DDL(数据定义语言，对表结构进行更改，创建数据库等)，DML(数据管理语言，表中增加记录等，删除表等)，DCL(数据控制语言，修改用户，密码等)，DQL(数据查询语言)
3. 数据库系统如何保持与应用程序的独立性：数据库提供了内模式(映像)(==保持数据库数据硬件存储方式不对数据库软件产生联系，即数据的物理独立性==)，外模式(映像)(==保持数据库软件与应用程序之间不产生任意关系，各自保持独立，即数据的逻辑独立性==)，保持与应用程序的独立性。
4. radi5(一种多块磁盘阵列算法，类似redis集群)至少需要三块磁盘
5. 数据库数据冗余，一种是列中数据重复，把该列数据抽取出来单独作为一张表，供主表引用，减少数据占用空间，另一种在大量数据情况下，对数据进行水平拆分(产生partition key)，==为减少partition key带来的其它字段查询会产生查找多个库的现象，设置常查询的字段为partition key冗余一份相同数据的数据库==。
6. mkdir -p 创建多级目录
7. icmp,telnet(远程登录)都属于TCP/IP
8. arp(四层模型属于网络层，七层模型属于链路层)地址解析协议，由ip地址解析成mac地址
9. 局域网访问外网过程

![](/assets/images/2022-09-07-16-19-19.png)

## 21点20分

### 东软笔试

1. 内部类==权限修饰符==比外部类==多了private,protected==，外部类有public,defalut；内部类修饰符比外部类==多了static==，外部类有abstract,final。
2. 十六进制0x16f,==八进制018==(0开头);
3. float o = 12.0(==编译出错，12.0默认为double型==)
4. ==switch()条件不能为double==，可以为int,char,short,byte
5. 自动装拆箱.valueOf(),intValue()
6. 包装类型缓存机制：valueOf()和initCache类，其中四种整型包装类(-128-127)和Character(0-127)和Boolean(TRUE,FALSE)有包装类，浮点型没有
7. 八种基本类型：byte,short,long,int, float,double, boolean, character
8. 变长参数 String... args
9. 重写遵循两同两小一大
10. 基本数据类型做为局部变量存储在栈上，成员变量(非static)存储在堆中。大多数对象分配在堆上(JIT的逃逸分析，标量匹配分配对象到栈上)。
11. 重写时父类private，final，static重写不了，但static可以声明
12. default可在接口中定义默认实现方法，但在类中方法加default会编译异常

