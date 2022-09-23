---
id: 59lebbcuy4n12yc1glc8gfb
title: '2022-09-23'
desc: ''
updated: 1663945198613
created: 1663940172143
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

# 2022年9月23日

## 21点36分

### HashMap源码及扩容机制

明确相关属性：
capacity        底层数组长度
loader_factor   确定size阈值大小
size            HashMap元素多少

明确相关方法作用：
resize()        初始化底层数组以及扩容
tableSizeFor()  确定size阈值大小(接近2的次幂)
HashMap()       确定HashMap相关属性，确定了loader_factor
HashMap(int capacity，float loadFactor)   确定HashMap相关属性，确定了loader_factor和size阈值大小
**总结**：都是为了元素在HashMap中分布比较均匀。

#### 默认构造及扩容流程

```java
public class Test{
  public static void main(String[] args){
    HashMap map = new HashMap() ;   // 1
    map.put("a", 1);                // 2
    ...
    map.put("d", 3);                // 3   超出map size阈值
  }
}
1过程确定HashMap loader_factor属性 默认0.75;
2过程执行后->调用resize()进行底层数组初始化，确定数组长度为默认，确定size阈值为0.75*16=12;
3过程执行后->调用resize()进行扩容，数组长度扩为原有2倍，size阈值扩为原有2倍

```

#### 有参构造及扩容流程

```java
public class Test{
  public static void main(String[] args){
    HashMap map = new HashMap(100) ;   // 1
    map.put("a", 1);                   // 2
    ...
    map.put("d", 3);                   // 3  超出map size阈值
  }
}
1过程确定HashMap loader_factor属性 默认0.75，size阈值为128(接近2的次幂)
2过程执行后->调用resize()进行底层数组初始化，确定数组长度为size阈值128，确定size阈值为128*0.75=96;
3过程执行后->调用resize()进行扩容，数组长度扩为原有2倍(保证了底层数组长度为2的次幂)，size阈值扩为原有2倍
```

#### 树化过程

相关属性：
UNTREEIFY_THRESHOLD = 6           链表长度阈值
TREEIFY_THRESHOLD = 8             链表转红黑树阈值(***缓解重复来回转化***)
MIN_TREEIFY_CAPACITY = 64         树化时，最小底层数组长度
`当产生树化行为时，会判断当前底层数组长度>=MIN_TREEIFY_CAPACITY，若满足，则树化，不满足，则扩容到MIN_TREEIFY_CAPACITY，再进行树化`
