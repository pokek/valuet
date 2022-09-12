---
id: dm7ngq2hebdlyc2ny1u17f9
title: '2022-09-12'
desc: ''
updated: 1662950160303
created: 1662949086650
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

# 2022年9月12日

## 10点18分

### Mysql的主从复制架构

1. 主从复制架构应用场景：(1)读写分离，提高mysql系统性能和并发能力
(2) 提高系统容灾能力
2. 会出现的问题：(1) 主库宕机之后，会出现数据丢失情况；(2) 当主库写压力较大压力时，会出现从库复制延迟情况;
3. 针对上述问题，数据丢失情况可以采用**半同步模式**进行解决，从库复制延迟可以**从库并行复制方法**。
*[半同步模式]: 主库等待任意一个从库发送返回数据后，才进行commit，Mysql默认采用异步模式
*[从库并行复制方法]: 不再是单个sql线程进行relay-log(中继日志)语句执行或相关操作
4. 读写分离的情况下会导致引发读过期数据现象(主库数据没有及时更新到从库中)，解决方法就是(1) 按请求类型进行分类，若为需要最新数据，强制去读主库数据；(2) 当主库更新之后，从库读操作就sleep,类似select sleep(1)

- [ ] 主从复制流程
