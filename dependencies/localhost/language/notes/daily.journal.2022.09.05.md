---
id: o741uuuqsc4zxem44667d04
title: '2022-09-05'
desc: ''
updated: 1662373582906
created: 1662340323240
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

# 2022年9月5日

## 09点12分

### UNIX中的io模型和JAVA中的BIO，NIO，AIO

io:读写事件

1个端口建立多个socket连接，1个socket连接发送多个请求。
建立socket --->socket拷贝内核空间--->拷贝用户空间
同步/异步：两个角度(真正的io操作(recvfrom))/(调用者角度)

>![](/assets/images/2022-09-05-12-41-08.png)

阻塞/非阻塞：消息处理机制(二次拷贝操作中，第一次拷贝是否阻塞)

#### UNIX中的网络IO模型

1. 阻塞io模型
2. 非阻塞io模型
3. 多路复用技术
4. 信号驱动模型(通知何时进行io操作)
5. 异步io模型(事件驱动，通知何时io操作完成)

编程范式：线程驱动，事件驱动(事件处理的时候是会阻塞)，单线程同步
> ![](/assets/images/2022-09-05-12-53-22.png)

1,2,3,4都是同步模型
5是异步模型

#### JAVA中的BIO,NIO,AIO

利用java语言使用操作系统提供的io能力，完成相应的几个io模型

1. BIO(阻塞式io)

>![](/assets/images/2022-09-05-13-27-07.png)

>![](/assets/images/2022-09-05-13-31-53.png)

2. NIO(提供阻塞式也提供非阻塞式，channel是为全双工模型可以双向同时读写，selector实现多路复用技术)由一个selectot线程监听成千上万个socketChannel

>![](/assets/images/2022-09-05-13-46-43.png)
[[Nioserver|technology.netty.nioserver]]
[[Nioclient|technology.netty.nioclient]]

- [ ] 3. AIO(真正的异步非阻塞io，一个AsynchronousServerSocketChannel可以监听成千上万个socket请求)
