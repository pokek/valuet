---
id: okmxs20qy0gljkf7roui691
title: '2022-09-03'
desc: ''
updated: 1662269465666
created: 1662163327638
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

# 2022年9月3日

## 09点08分

### star准则

    s: situlation 情景
    t: target 目标
    a: action 行动
    r: result 结果

### Mysql三大日志和MVCC机制

    三大日志分别是:1.undolog(回滚日志，负责事务失败回滚和MVCC机制)，
                  2.redolog(重做日志，当数据库发生故障时候，进行数据恢复)
                  3.binlog(归档日志，用于数据备份和主从复制)
    MVCC(多版本控制)：situation: 在大量并发数据库操作的情境下，只有读读并发，系统整
    体性能还是弱的一批，不满足实际需求
                      target   : 为了提高整体数据库系统并发量，(使得不仅读读之间可
    以并发，而且读写，写读之间也可以并发，写写操作之间还是阻塞的)。
                      action   : 因此引入了MVCC版本控制进行以上目标实现。
                      实现原理  : 首先只有在读提交和可重复读的事务隔离级别下才有相关
                      实现，基本思想就是每条记录(聚簇索引中)都引入一个事务id，和一个版本指针(指
                      向上次事务的修改，存入undolog)，从而形成一个操作版本链，只要判定当前事务id
                      能够操作该条记录即可，从而维护了一个活跃事务id的列表READVIEW
                      (由开头说的两种不同隔离级别下，维护的时机不同，read commited
                      在每一次select操作后进行维护，reapeat read则是第一次select操
                      作后进行维护，其它时机就不维护)
                      result    : 提高了系统整体并发度

### JVM一些参数

-xms 初始堆大小
-xmx 最大堆大小
-xmn 新生代大小

### locadClass和Class.forName()

loadClass由**类加载器对象**执行，默认**不进行解析**
Class.forName()**默认进行类初始化**

## 11点55分

### 秒杀项目中的异步下单减库存

整个创建订单(下单)过程中有以下操作：

- redis减缓存库存
- 异步消息发送同步数据库库存
- 数据库创建新的订单
虽然redis，异步消息同步数据库与创建新的订单在同一事务中，但redis和同步数据库库存失败都不会引起回滚操作，因此在下单过程以以上操作从上往下执行可见redis失败，同步数据库库存失败都不会引起回滚，但创建订单回归，造成货物少了，但没有新的订单生成。
解决一：调整执行顺序(仍存在问题，如消费消息失败就会造成库存没少，订单增加--超卖)
解决二：利用mq的事务

## 14点07分

### 刷题

- ==String.join()==
把字符用同一分隔符进行串联，如[list]("2", "3", "4") String.join(list, "->")变成字符串"2->3->4"。

#### Leecode

- 22 [==有效括号==](https://leetcode.cn/problems/generate-parentheses/)
- 95 [==不同二叉搜素树II==](https://leetcode.cn/problems/unique-binary-search-trees-ii/)
- 100 [相同的树](https://leetcode.cn/problems/same-tree/)
- 96 [不同的二叉搜索树](https://leetcode.cn/problems/unique-binary-search-trees/)
- 104 [二叉树的最大深度](https://leetcode.cn/problems/maximum-depth-of-binary-tree/)
- 124 [==二叉树的最大路径和==](https://leetcode.cn/problems/binary-tree-maximum-path-sum/)
- 105 [从前序与中序遍历序列构造二叉树](https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/)
- 235 [二叉搜索树的最近公共祖先](https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-search-tree/)

## 22点17分

### 笔试题目

#### 广联达笔试题

1. 子弹题:key:

```java {.line-numbers}
// 一些粒子一个一个发到另一边，每个粒子拥有独一无二的编号，
// 有些粒子速度很快会提前到达，找出有几个粒子提前到达了。
// 输入n代表n个粒子，下面两行各n个数代表发送和接收时的编号。
// 样例：
// 输入：
// 5
// 1 2 3 4 5
// 2 3 4 1 5
// 输出：
// 3
// 解释：1在2 3 4前发射，但是2 3 4比1先到达

// 核心思路: map+队列

// 作者：YuYoung32
// 链接：https://www.nowcoder.com/discuss/1035240?type=post&order=create&pos=&page=1&ncTraceId=&channel=-1&source_id=search_post_nctrack&gio_id=C2839843699ED144FAA92BBF8B85F1EF-1662214983134
// 来源：牛客网

// 思路: 发送队列和接收队列, map存储发送队列中是否有提前到达的.

// 如果发送队列和接收队列首个相同，那两个队列直接到下一个就好了。
// 如果发送队列和接收队列首个不同，接收队列跳转到下一个，发送队列不变，计数器+1，标记map[revc[0]]=false，以便下次再遇到时直接跳过。
// 重复1 2直到发送队列为空。

package main

import "fmt"

func main() {
    var n int
    fmt.Scan(&n)
    start := make([]int, n)
    end := make([]int, n)
    //sm==true表示出发队列的这个是未到达的
    sm := make(map[int]bool)
    for i := 0; i < n; i++ {
        fmt.Scan(&start[i])
    }
    for i := 0; i < n; i++ {
        fmt.Scan(&end[i])
    }

    var res int
    for len(start) > 0 {
        if sm[start[0]] {
            if start[0] == end[0] {
                start = start[1:]
                end = end[1:]
            } else {
                res++
                //标记start中的，为已到达，以后直接跳过
                sm[end[0]] = false
                end = end[1:]
            }
        } else {
            start = start[1:]
        }
    }

    fmt.Println(res)
}

```

2. 模拟题:key:

```java
// 一排座位编号1..n，有m条规则，
// 每条规则是这样的座位区间[l,r]内最多有x个人坐，
// 问符合所有规则情况下，最多有多少人坐。
// 输入第一行两个数n m代表座位数和规则数，
// 下面m行每行有3个数分别代表l r x。
// 样例：
// 输入：
// 10 3
// 1 4 2
// 3 6 2
// 10 10 1
// 输出：
// 8
// 解释：3 4号座位是空的，其他坐满了

// 作者：YuYoung32
// 链接：https://www.nowcoder.com/discuss/1035240?type=post&order=create&pos=&page=1&ncTraceId=&channel=-1&source_id=search_post_nctrack&gio_id=C2839843699ED144FAA92BBF8B85F1EF-1662214983134
// 来源：牛客网

// 思路：寻求最多的座位使用，相当于寻求最少的座位未使用，即寻求最少的空白座位，我们当然希望一个空白座位属于多个区间内的，这样就可以复用空白座位，以达到最少空白座位的目的。

// 创建记录所有规则的数据结构，这里使用数组+结构体。
// 创建记录座位有哪些规则的数据结构，这里使用二维数组记录，第一维下标代表座位编号，每一维的数组代表遵顼的规则的下标（此下标是第一步记录规则的数组的下标）。
// 找到座位中规则数量最多的座位（可以根据数组第二维的长度比较），访问其遵循的每个规则，让规则需要的空白座位减去1，若减去1后小于等于0，说明此规则已经完全满足，在第1步创建的规则数组中消去他（设为空）,并且结果+1.若规则需要的空白座位减去1后仍大于0，说明此规则还未满足，计数器+1以得知未满足的规则数。
// 重复步骤3，每次更新未满足的规则数，直到未满足的规则数为0
// 拿到了结果（最少需要的空白座位数），打印总座位数减去结果就是最多坐的人。

package main

import "fmt"

type Interval struct {
    start int
    end   int
    blank int //至少的空座位数量
}

func main() {
    //n个座位 m个规则
    var n, m int
    var x int
    fmt.Scan(&n, &m)
    //seats[i]表示这个座位属于哪几个规则区间，区间以下标存储
    seats := make([][]int, n+1)
    intervals := make([]Interval, m)
    for i := 0; i < m; i++ {
        fmt.Scan(&intervals[i].start)
        fmt.Scan(&intervals[i].end)
        fmt.Scan(&x)
        intervals[i].blank = intervals[i].end - intervals[i].start + 1 - x
        //对这个区间的座位加上规则
        for j := intervals[i].start; j <= intervals[i].end; j++ {
            seats[j] = append(seats[j], i)
        }
    }
    //每次取规则数最多的座位，视作空位，对应的规则空座数量减去1，当某个区间所需空格为0,去除掉他，所有区间都为0，结束
    var minTotalBlanks int
    leftRules := len(intervals)
    for leftRules > 0 {
        //找到规则最多的座位
        maxRules := 0
        maxRulesIdx := -1
        for i := 1; i < len(seats); i++ {
            if len(seats[i]) > maxRules {
                maxRules = len(seats[i])
                maxRulesIdx = i
            }
        }
        //对应的规则空座数量减去1
        leftRules = subBlank(seats[maxRulesIdx], intervals)
        seats[maxRulesIdx] = nil
        minTotalBlanks++
    }
    fmt.Println(n - minTotalBlanks)
}

func subBlank(idxs []int, intervals []Interval) int {
    var leftNums int
    for _, i := range idxs {
        intervals[i].blank--
        if intervals[i].blank > 0 {
            leftNums++
        }
    }
    return leftNums
}

/*

10 3
1 4 2
3 6 2
10 10 1

*/
```

[参考链接](https://www.nowcoder.com/discuss/1035240?type=post&order=create&pos=&page=1&ncTraceId=&channel=-1&source_id=search_post_nctrack&gio_id=C2839843699ED144FAA92BBF8B85F1EF-1662214983134)

#### 搜狐畅游笔试

1. 内存屏障 JVM的JMM内存模型的操作如以下进行，其中**local/storage形成内存屏障**

![](/assets/images/2022-09-04-00-03-36.png)

2. G1垃圾收集器流程如下：初始标记---->并发标记---->**最终标记**----->垃圾筛选回收(region回收)
3. loadClass加载没有的类名时候，会**抛出异常**
4. notify()使得其它位于wait中的线程进入**就绪态**
5. yield()使得与该**线程优先级相同的线程**有机会争夺时间片
6. 同一优先级线程调度必然是分时吗？**多cpu情况下，可同时调度**
7. ==八大排序比较次数/时间复杂度与数据初始状态无关的????? ==简单选择排序
8. finalize()是在**对象引用释放之前**，进行对象的一次finalize()的调用，main()方法执行完后里面创建的强引用变量就随着栈销毁一起销毁了
