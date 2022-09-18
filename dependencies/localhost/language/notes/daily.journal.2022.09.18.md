---
id: 9ig0jlgusawgjksyhqmvpl7
title: '2022-09-18'
desc: ''
updated: 1663475526173
created: 1663472930509
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

# 2022年9月18日

## 11点49分

### Questions

- [ ] 快表的删除，插入，查找等操作理解

### Redis删除策略和淘汰策略与持久化方式

1. 删除策略有定期删除，惰性删除(系统使用key的时候，若key过期则进行删除)两种策略方式
2. 淘汰策略，超过限制内存直接报错，所有key进行随机删除，所有key进行lru，设置过期时间的key集合进行随机删除/或者进行lru
3. 持久化方式：AOF(追加文件，实时性好，恢复慢，策略：key修改就写入，1s后写入，系统决定什么时候写入),RDP(实时性差，恢复快，(save minutes, 几条指令修改))
