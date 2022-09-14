---
id: rkrd2aeu51atw6k0evyr3t2
title: '2022-09-14'
desc: ''
updated: 1663145999284
created: 1663123903496
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

# 2022年9月14日

## 10点42分

### 进程状态相关的一些疑惑

1. 进程阻塞和睡眠，进程如何进行并发，两个进程，一个cpu，其中一个进程阻塞，如何进行调度的(java两个线程，一个线程堵塞，该线程是会一直堵塞着，另一个线程还是正常调度)
阻塞：遇到阻塞程序事件(如等待io，等待其它事件等)，进入阻塞状态，释放cpu时间片，cpu不再调度，(就绪态才被cpu调度)
睡眠：多个进程使用临界资源，未获取资源的进程停止执行（睡眠）等待
2. 进程更多不进行并发(更多是父子进程之间)，而是通信，线程之间更处于并发
3. java中有相关线程状态需要与进程状态分开，java线程睡眠不释放释放时间片(不处于阻塞态，可以认为在运行态，照常cpu调度处理)，java线程join(调用join方法线程处于阻塞态，释放cpu时间片，等待其它线程结束后，再进行转为就绪态，等待cpu调度)---不一定对

- [ ] 4. java中的线程模型定义：（是java为线程之间调度提供了一层抽象模型，个人）

- [ ] 5. 进程的调度策略，是为当多个大型任务执行的时候，提供的一种调度策略，并且抽象出一层进程状态模型

6. cpu实际的调度还是根据线程调度的，进程只是分配资源，线程才是调度单元

7. 进程更多相当于充当任务拆分功能(父子进程)，如nginx的实现就是利用父子进程，线程更多是实现某一任务的具体步骤，其中存在并发，线程可以看作是一种特殊的进程

8. socket套接字有监听套接字，和已连接套接字

9. 进程和进程组(只要有一个线程就仍是进程组，无关有没有组长)，作业相当于一个进程组，前台只有一个作业，后台可有多个作业，会话有一个或多个进程组，shell的实现就是一套运用以上概念的案例.

10. 操作系统提供了基于进程的API和基于线程的API。

11. 操作系统的内存管理，文件管理，还有c++的内存模型

## 14点42分

### java的线程6种状态

1. new
2. runing
3. redy
4. waiting
5. time_waiting
6. blocking

特别注意的一点：给线程标记这些状态都是为了充分利用cpu，如thread.sleep(1000l)，线程处于time_wating状态，底层实现将其加入等待队列中，等待cpu调度，但不会释放锁

yield()方法与sleep()类似，只是不能由用户指定暂停多长时间，并且yield（）方法只能让同优先级的线程有执行的机会，sleep()方法让其它线程有执行的机会

![](/assets/images/2022-09-14-14-51-44.png)

个人猜测，操作系统对进度的调度设计架构，也是根据相应的状态信息，放入相应队列进行调度，如已经准备好的队列就分配cpu时间片，其它状态就放入其它队列中，觉得有点类似AQS实现，学习的时候可作为一种类比s方向。
(学习课程：哈工大操作系统课程)
