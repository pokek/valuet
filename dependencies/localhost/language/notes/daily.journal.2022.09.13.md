---
id: 5azwwx88jli05iu60kjaupv
title: '2022-09-13'
desc: ''
updated: 1663087058185
created: 1663069486381
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

# 2022年9月13日

## 19点45分

### 汉得笔试

1. 编程，抢车位
![](/assets/images/2022-09-13-19-45-50.png)
`概率计算`
![](/assets/images/2022-09-13-19-53-18.png)

## 22点24分

### 微众银行笔试

![](/assets/images/2022-09-13-22-24-56.png)
![](/assets/images/2022-09-13-22-25-42.png)
![](/assets/images/2022-09-13-22-25-12.png)
![](/assets/images/2022-09-13-22-25-53.png)
![](/assets/images/2022-09-13-22-25-27.png)
![](/assets/images/2022-09-13-22-26-05.png)

### Mysql死锁

1. 有一点很重要，就是使用insert.、delete、update这三个DML语句的时候，innDB引擎 会自动给涉及到的数据加上行级 排他锁，
所以加过排他锁的数据行在其他事务中是不能修改数据的，也不能通过for update和lock in share mode锁的方式查询数据

2. 只要加过排他锁就不能再进行 insert delete update了,也不能再加锁,相当于是不可重入锁，只能加一次

[死锁讲解博文](https://longcj.blog.csdn.net/article/details/122932768)

### 操作系统的阻塞与睡眠和挂起

阻塞：进行I/O操作而导致程序无法继续执行；
睡眠：多个进程使用临界资源，未获取资源的进程停止执行（睡眠）等待
挂起：一些阻塞的进程暂时用不到内存资源，就先将其换入外存
阻塞和睡眠都还在内存；挂起被搁置到了外存
阻塞进程在做I/O操作，睡眠进程只有等待
- [ ] [讲解连接](https://www.cnblogs.com/ck1020/p/6669661.html)
