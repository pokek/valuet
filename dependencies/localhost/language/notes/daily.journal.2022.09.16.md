---
id: cs4922y0e8y7teg8qbxn7m5
title: '2022-09-16'
desc: ''
updated: 1663340475025
created: 1663297354678
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

# 2022年9月16日

## 11点02分

### java反射

获取私有方法和属性，field = class.getDeclared(),field.setAccessible()。

new 对象经过两个过程，类加载，初始化对象。
反射newInstance()，就只有初始化对象过程，类加载过程在Class.forName()中进行加载。

获取类对象有三种方法，但是Student.class, new Student().getClass,需要在语言层面确定数据对象类型，而Class.forName()则在语言层面上无需指定特定类型，仅需通过语言层面上的字符串确定类型。

### java的静态代理和动态代理

1. 静态代理在编译时期就生成目标对象，接口，代理对象的class文件，灵活性差，扩展性差，每一个接口增加方法，目标对象和代理对象都得实现对应的方法，并且每一个目标类都需要生成一个代理类。
2. 动态代理在jvm运行时期，生成相应代理对象的字节码文件，并在运行时期加载进jvm中，灵活高，扩展性好，解决静态代理的三大缺陷
3. jdk动态代理核心Proxy.newProxy(类加载器，接口类数组，invocationHandler实现类)和InvocationHandler接口，只能生成实现接口实现类的代理对象，
4. Cglib动态代理通过继承实现代理模式，解决jdk动态代理缺陷，因为需要继承，所以不能生成final修饰的类的代理对象，核心为Enhancer类和MethodInterceptor
5. 可通过工厂模式生成代理对象

### java中的BigDecimal类

该类能进行精度计算，因为引入精度描述来计算相应浮点数

### 函数声明

函数声明也就是声明了调用方和被调用方之间的一种调用方式，声明了调用方应该传入哪些类型参数，被调用方应该返回什么类型结果

### JAVA中的Unsafe对象

该对象是java提供给程序员直接访问系统内存资源和管理系统内存资源能力，是单例的，一般并不建议使用，是不安全的，java自带的并发类和io相关的类使用的更多，需要由bootstrap加载的类，才能进行使用该类，可以由反射机制拿到该类的私有的单例对象字段进行使用，对内存的操作都是操作系统的内存即堆外内存，(减少数据从系统内存到堆内存的拷贝)。

DirectBuffer是典型的应用之一，由于分配的是堆外内存，不受jvm垃圾回收机制的管理，因此需要自己释放，但是该类利用一个Cleaner对象监测DirectBuffer的垃圾回收行为，当其被垃圾回收后，就自动释放该内存，new Cleaner(this, new Deallocator());
