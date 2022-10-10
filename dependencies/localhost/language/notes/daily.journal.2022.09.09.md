---
id: bjw2gf434xujtw695v3i2yk
title: '2022-09-09'
desc: ''
updated: 1665396354013
created: 1662704487491
traitIds:
  - journalNote
---
**This** template was applied using the daily journal schema. Edit the [[templates.daily]] note to change this template.
To create your own schemas to auto-apply templates when they match a hierarchy, follow the [schema tutorial](https://blog.dendron.so/notes/P1DL2uXHpKUCa7hLiFbFA/) to get started.

<!--
Based on the journaling method created by Intelligent Change:
- [Intelligent Change: Our Story](https://www.intelligentchange.com/pages/our-story)
- [The Five Minute Journal](https://www.intelligentchange.com/products/the-five-minute-journal)
-->

# 日期

## 14点21分

### 深拷贝与浅拷贝和System.arrayCopy(),Arrays.copyOf()

1. 深拷贝后堆内存有两份完全一样的对象，浅拷贝后堆内存还是只有一份对象
2. System.arrayCopy()和Array.copyOf()元素类型为基本类型和包装类型时是进行深拷贝，其它对象对象类型则为浅拷贝
