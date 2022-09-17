---
id: 27p0dl1lvq46sqwy3ccln45
title: '2022-09-17'
desc: ''
updated: 1663388218065
created: 1663379868132
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

# 2022年9月17日

## 09点58分

### TCP三次握手，四次挥手状态

握手
客户端：send->establish
服务端：listening->recv->establish

挥手：
客户端：fin_wait_1->fin_wait_2->time_wait->close
服务端：close_wait->last_atack->close

### Questions

- [ ] 1. redis和Mysql返回的数据是位于堆外内存中，还是堆内内存中，如果在堆外内存，如何实现java语言操纵这些数据的呢

### 跳表数据结构

在原有序链表的基础之上，通过建立索引层优化查询效率，当数据量大的时候可通过多增加索引层数，来提高查询效率。
![](/assets/images/2022-09-17-12-16-48.png)
