---
id: 9ig0jlgusawgjksyhqmvpl7
title: '2022-09-18'
desc: ''
updated: 1663504833571
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

### unsafe类的内存屏障

1. 内存屏障：由于编译器和cpu硬件会对程序代码进行重排序，就可能导致编译器重排和cpu硬件重排(如频繁访问的变量放入高速缓存)出现矛盾，发生程序问题，因此引入了内存屏障(由cpu提供指令，操作系统提供对应命令)解决相应问题，可以认为就是设置一个共同点(在该点时候，load操作/store操作都完成了，才进行下步步骤)

- [ ] ==不够理解==

```java
@Getter
class ChangeThread implements Runnable{
    /**volatile**/ boolean flag=false;
    @Override
    public void run() {
        try {
            Thread.sleep(3000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("subThread change flag to:" + flag);
        flag = true;
    }
}

public static void main(String[] args){
    ChangeThread changeThread = new ChangeThread();
    new Thread(changeThread).start();
    while (true) {
        boolean flag = changeThread.isFlag();
        unsafe.loadFence(); //加入读内存屏障
        if (flag){
            System.out.println("detected flag changed");
            break;
        }
    }
    System.out.println("main thread end");
}
```

![](/assets/images/2022-09-18-16-06-32.png)

### javaSPI机制

1. SPI机制调用者提供接口，服务者是提供服务，API调用接口和实现都由服务者提供。
2. SPI机制核心一套接口，以及给调用者的Service类和ServiceLoader，以及服务者提供的接口实现类，ServiceLoader默认加载meta/info目录的文件内容,==调用者调用Service.getService()的时候该方法就加载实现类==。
3. ServiceLoader利用了线程上下文加载器，这是由于服务提供者体提供的实现类可以看作是==第三方类==，若添加jar包进项目中，根据一般类加载机制是需要用==应用类加载器==进行加载的，但由于ServiceLoader类属于java==自带类==，加载该类的==类加载器为bootStrap类加载器==，==其不能进行加载第三方类==，为了解决该问题，就用==线程上下文类加载器==，打破双亲委派机制(==不调用原始的load方法==)，直接加载该类，使得其可用。
4. 如若需要加载自定义路径的类文件，或者两个同名类(tomcat中两个同名应用)就可以自己自定义类加载器进行加载。
![](/assets/images/2022-09-18-17-45-48.png)

### Questions

- [ ] jdk中的动态代理，当调用代理对象的方法时，会调用invocationHandler.invoke()，该情况怎么实现的
