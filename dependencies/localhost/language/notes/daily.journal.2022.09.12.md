---
id: dm7ngq2hebdlyc2ny1u17f9
title: '2022-09-12'
desc: ''
updated: 1662977759750
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
*[半同步模式]: 主库等待任意一个从库发送返回数据后，才进行commit(主从库之间建立稳定通信可以看成一个事务)，Mysql默认采用异步模式
*[从库并行复制方法]: 不再是单个sql线程进行relay-log(中继日志)语句执行或相关操作
4. 读写分离的情况下会导致引发读过期数据现象(主库数据没有及时更新到从库中)，解决方法就是(1) 按请求类型进行分类，若为需要最新数据，强制去读主库数据；(2) 当主库更新之后，从库读操作就sleep,类似select sleep(1)

- [ ] 主从复制流程: 主库从库都是通过3306默认端口进行通信，主从复制就为进程中的一个线程操作

### java的equals和hashcode方法

1. 如果重写equals没有重写hashcode(==object 的hashcode默认返回对象地址==)会出现两个相同的对象出现hashcode值不相等
2. 在需要类的散列表情况下(如hashset，hashmap等)equals和hashcode方法有相关联系的，在不需要类的散列表情况下(如hashset，hashmap等）equals和hashcode方法没有什么联系的。

### String的getChars()和String

1. str.getChars()把str拼到dst字符串后面，采用System.arrayCopy()
2. string不可变是线程安全的
3. `new String("abc")`创建1个或者2个字符串对象，ldc会判断字符串常量池中是否有字符串"abc"的引用，有就返回，无就创建并把引用放入字符串常量池中
4. `String str = new String("a") + new String("b")`执行后，字符串常量池中并没有字符串"ab"的引用
5. string.intern()判断是否可以从字符串常量池中找到该字符串引用，有则直接返回，无则(1.6和1.8不同)把自身对象引用放入字符串常量池中

```java {.line-numbers, highlight=[4, 10]}
// 1.6
String ab = new String("a")　＋　new String("b");  //在堆中创建"a","b","ab";

String ab2 = ab.intern();//先判断StringTable的中是否有"ab"，如果有直接返回StringTable中的地址，如果没有则拷贝一份ab对象放入StringTable。

String ab3 = "ab";//因为StringTable中有"ab",此时直接返回StringTable中地址。

System.out.println( ab2 == ab3 );//true        

System.out.println( ab == ab3 );//false       此时ab还是返回堆中的地址
```

```java {.line-numbers, highlight=[4, 10]}
// 1.8
String ab = new String("a")　＋　new String("b");  //在堆中创建"a","b","ab";

String ab2 = ab.intern();//先判断StringTable中是否有"ab"，如果有直接返回StringTable中的地址，如果没有则将该对象放入StringTable中。

String ab3 = "ab";//因为StringTable中有"ab",此时直接返回StringTable中地址。

System.out.println( ab2 == ab3 );//true        

System.out.println( ab == ab3 );//true       此时ab已经被放入StringTable中，所以地址相同
```

>![](/assets/images/2022-09-12-16-43-39.png)

```java
      char[] chr1 = new char[20];
      char[] chr2 = new char[20];
      chr1[0] = 'a';
      chr1[1] = 'b';
      chr2[0] = 'c';
      chr2[1] = 'd';

      System.arraycopy(chr2, 0, chr1, 2, 2);

      System.out.println(Arrays.toString(chr1));  // [a, b, c, d,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ]
```

```java {.line-numbers, highlight=[11]}
    public void getChars(int srcBegin, int srcEnd, char dst[], int dstBegin) {
        if (srcBegin < 0) {
            throw new StringIndexOutOfBoundsException(srcBegin);
        }
        if (srcEnd > value.length) {
            throw new StringIndexOutOfBoundsException(srcEnd);
        }
        if (srcBegin > srcEnd) {
            throw new StringIndexOutOfBoundsException(srcEnd - srcBegin);
        }
        System.arraycopy(value, srcBegin, dst, dstBegin, srcEnd - srcBegin);
    }
  ```

  ```java {.line-numbers, highlight=[2, 4-5]}
      public static void main(String[] args) {
        char[] chr1 = new char[20];
        char[] chr2 = new char[20];
        // chr1数组的长度为3，引用变量chr1不再指向new char[20]对象
        chr1 = "abc".toCharArray(); 

    }
```

>![](/assets/images/2022-09-12-15-39-00.png)

### JVM运行时常量池和字符串常量池

1. 程序文件编译后的字节码文件有==常量池表==这一概念，它是存着编译时期的字面量和符号引用，在JVM进行类加载的时候，会将其==加载进运行时常量池中的==，运行时常量池在jdk1.8是存在于元空间中的。
2. 字符串常量池(==底层==实现stringtable.cpp，==采用hashset-string-数据结构==)和静态变量在jdk1.8存于堆中，其中==字符串常量池存的是字符串引用==，字符串本体对象存于堆中的。

### javac编译器

1. javac仅有少数的优化之一：常量折叠
*[常量折叠]: 唯有在编译阶段，能够由javac编译器事先知道的结果才能常量折叠，运行时才知道的话就没有该优化。
```java
// 例1
public final String str1 = "abc";  // final修饰的字符串变量(字符串常量)
public final String str2 = "edf";
String st = "abcedf";
String str = str1 + str2;
System.out.println(st == str) // true


// 例2
public final String str1 = "abc";  
public final String str2 = getStr(); // 运行时才知晓
String st = "abcedf";
String str = str1 + str2;
System.out.println(st == str) // false

public String getStr(){
  return "edf";
}



