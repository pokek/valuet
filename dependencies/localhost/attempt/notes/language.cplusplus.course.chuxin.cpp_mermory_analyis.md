---
id: 3y2gpodk7ab0f7dngncg9wk
title: Cpp_mermory_analyi
desc: ''
updated: 1667003643320
created: 1667003643320
---

# C++的内存模型

## 前言：课程介绍

1. 前言：这是我的第二门课，在学习这门课前，最好先去学一下我的第一门课，C语言对应的32位汇编，我的空间里就有第一套课。懂汇编对于理解C++的运行方式还是非常重要的。当然，如果不懂也没太大关系，只是有些地方会比较迷惑，需要死记硬背。

顺带一提：这套课程讲的内容真的非常实用，是我多年的一点经验。

2. 课程目的
(1) 提升开发功底：能够理解C++的内存模型对提高C++的开发功底非常重要，很多东西理解不了，很大程度上就是基本功不够，没有完整的体系。
(2) 应付面试，理解C++的内存模型很有意义，这也是面试时一个常问的点，如果能够熟练的答出来，面试官也会高看你的，工资有时就是你自己开了。
(3) 帮助大家从编译器的角度理解C/C++，以后理解C/C++的一切都要尽量从编译期出发。
3. 环境介绍：直接在vs上演示(vs2013，vs2015，vs2017，vs2019，vs2022都可以)，有个vs就够了。

话不多说，直接开始。时间是最宝贵的，如何在有限的时间内做更多的事情是非常值得考虑的，这一点已经工作的人应该更加有体会。

## Part1：C++普通类的内存模型---第一课：C++类和C结构体的区别

首先要说的是：C++的类在堆栈内存上就是C语言的结构体，C++类的那些功能不过是编译器帮我们做了很多事而已。

我们已经知道C/C++结构体在栈上的分布方式。C++的编译器究竟帮我们额外做了什么呢？首先分两点讨论。

1. C++的类对象如何调用函数呢？
(1) 有很多人这么说的，C++的类函数在编译时额外添加了一个this指针作为形参，该指针指向函数所作用的对象。
(2) 其实，这种说法并不准确，this是一个关键字，如果用this指针作为形参。编译时语法分析根过不了。this指针如果设置为形参，用函数指针灵活调用函数也会有极大的麻烦，作用域也会有很大麻烦。
(3) This是一个关键字，既然是关键字，有什么功能就看编译器怎么解释了，无需考虑语法。this实际上是一个类内所有成员函数，成员变量都可以看见的特殊变量，该变量永远指向函数所作用的对象。

2. C++的构造函数，析构函数有什么用呢？
(1) C语言的结构体对象在创建后值是什么完全取决于这块栈内存或堆内存原来有什么值。但是C++的对象创建后有什么取决于我们构造函数，原因就是C++类对象内存分配后要调用构造函数对这块内存进行初始化。
(2) 析构函数也是同理，类对象销毁时要调用析构函数。
(3) 对C++类对象进行初始化的构造函数并不是我们写的构造函数。在调用我们写的构造函数前，编译器会帮我们干很多事情。
①父类有空参构造函数，我们的构造函数并未显示调用父类的构造函数，编译器就会帮我们调用父类的空参构造函数。
②类中有其它类类型的对象，我们对其采取默认构造，且该类对象有空参构造函数，编译器就会帮助我们调用它的空参构造函数。
③编译器会帮助我们初始化指向虚函数表的指针和指向虚继承表的指针，不懂没关系，这两个东西就是part2和part3的主要内容。
(4) 析构函数也是同理，在我们的析构函数之后，编译器也会做很多事。
①父类有析构函数，编译器会帮助我们调用父类的析构函数。
②类中有其它类类型，编译期会帮我们调用析构函数。

3. 默认构造函数，默认析构函数。
(1) C++primer中写到，当我们不写任何构造函数时，编译器会帮我们生成一个默认的构造函数。这个默认的构造函数做的事情，就是上面三条。
(2) 析构函数也一样，C++primer中写到，我们缺乏析构函数时，编译器会帮我们生成一个默认的析构函数。这个析构函数做的事情也是上面的。

## 第二课：类内的静态成员变量和静态成员函数

1. 类的静态成员变量：
(1) 类内的静态成员变量其实和C语言的静态局部变量差不多。在编译期创建，存储在.bss或.data段中。
(2) 这也是类内的静态成员变量必须在类外进行初始化的原因，当然，C++11新添加了一种写法，就是const static i = 10，但这样写的本质还是让i在编译期就在确定数值，初始化在.data区。const关键字一定不能省，有了const才能让这一行代码成为一个常量表达式。常量表达式就是指能在编译期确定值的式子，这是编译过程中语义分析的一个概念，就是在这一步已经可以确定变量的值，确保变量不会被修改，所以const改为constexpr也是完全没有问题。
(3) 静态成员变量在编译期初始化，需要在编译期就确定数值。构造函数是运行期的事情了。
(4) 类的静态成员变量作用范围和其它局部变量一样，生命周期和函数内的静态成员变量一样，都是从程序开始加载到程序运行结束。

2. 类的静态成员函数：
(1) 类的静态成员函数和c语言的静态函数区别就比较大了。
(2) c语言的静态函数唯一作用就是让编译器在链接时将不同文件的同名函数当做不同的符号处理，所以可以在不同文件中定义同名的静态函数。
(3) 类的静态成员函数就是专门为类的静态成员变量设置的，类的静态成员变量可以用类名直接调用，但是这样会破坏分装性，于是推出了静态成员函数。

## 第三课：继承的本质

1. 在编译器看来，创建一个类对象就是在堆或栈上分配对应大小的内存，再调用构造函数，子类也是如此。编译器读取子类对应的代码段，分配出可以容纳父类全部对象和子类新增对象的内存空间。
2. 然后调用子类的构造函数。一般来说子类首先都是调用父类的构造函数，注意，在子类构造函数调用后，父类的构造函数不管是不是第一个调用，都会首先被执行。
3. 如果子类未调用父类的构造函数，且父类有空参构造函数，编译器会在调用子类的构造函数之前自动调用父类的构造函数。这一点其实第一课就讲过了。
4. 在子类对象创建完毕后，从内存的角度讲，子类对象和普通类的对象并没有区别。

## Part2：C++的虚函数---第四课：C++虚函数的工作原理

1. C++的虚函数被引入的目的就是为了实现多态，多态是面向对象的重要一环，可以说一个语言不支持多态，就是不支持面向对象。因为很多学生对多态的重要性认识不够，所以这里强调一下。
2. 多态就是父类指针指向子类对象时可以调用子类对象的函数，要讲它的实现原理，就要提一下静态联编和动态联编的概念了。
(1) 静态联编：程序在编译期就已经确定类对象要调用的函数地址，这就是静态联编。c语言，c++非多态都处于这种情况。
(2) 动态联编：程序在编译期只是明确了寻找函数地址的方式，只有在程序运行时，编译器才真正明白了函数的地址。C++的多态就是动态联编。

3. 静态联编很好理解，那么动态联编是如何实现的呢。这就首先要讲一下虚函数表和虚函数指针的概念。每个有虚函数的类都会有且仅有一个虚函数表，父类和子类不会共用虚函数表。对于父类，每一个有虚函数的父类都会有一个指向虚函数表的指针，虽然C++标准并未规定这个指针应该放在哪里，但所有的主流编译器都将这个指针当成类的第一个成员变量，这个指针的赋值工作由编译器负责。虚函数表里面存放的是所有虚函数的地址。
4. 对于单继承，子类的虚函数表会复杂一些。

![](/assets/images/2022-10-29-09-50-46.png)

额外说一点，每个虚函数表下面都会有一个空指针，用来将虚函数和其它内存隔离。
5. 对于多继承，子类的虚函数表会再复杂一些

![](/assets/images/2022-10-29-09-51-09.png)

当然这样画是方便大家理解，但其实，这两个表是连接在一起的。比如B::g是vptr[4]，则vptr[7]就是B::d。那么vptr[5]和vptr[6]是什么呢，vptr[5]是一个空指针。vptr[6]是一个type_info，这也就是马上要讲的RTTI的实现原理。
所以一个类只有一个虚函数表，不会出现两个。
每个虚函数表，vptr[-1]就是type_info，用来存储类的真实信息。我们讲虚函数表都是从vptr[0]开始，但其实vptr[-1]也是有东西的。

6. 动态联编的实现原理：当C++用指针寻找函数时，编译期只会给出类对象寻找地址的方式，也就是去对应虚函数表中寻找对应名称的函数。这个寻址的过程只有程序在运行时才会真正执行。而其它的方式，程序在编译时地址就已经确定。

## 第五课：RTTI（run time type identification）

首先讲一下RTTI有什么用，RTTI，也就是运行时类型检查，我相信很多人根本就没用过，知道有这么个东西，但压根不知道能干什么。

实际上，这个功能还是有用的，它的作用的主要有以下几点。

1. 向下类型转化：将父类指针转化为子类指针，那向下类型转化有什么用呢，主要就下面两个。
2. 异常处理：这一点不少人应该用过。
3. 数据存储：这个用过的人相对就少很多了，但有应用场景。

综上所述，RTTI还是有用的，应该掌握。

RTTI运算符：
typeid：返回type_info结构体的对象，type_info实际上是什么，看代码。
dynamic：成功返回子类指针，失败返回nullptr
这两个运算符的实际使用方式看代码。

RTTI的实现原理：上一课已经说过vptr[-1]是type_info结构体，dynamic也要依据type_info运行，所以使用typeid和dynamic_cast都要有虚函数表，也就是虚函数。

## Part3：C++的虚继承----第六课：虚继承的用法与实现原理

虚继承就是为了解决菱形继承的问题，比如：

![](/assets/images/2022-10-29-10-41-43.png)

假设这是一个游戏的各种类的继承情况：类A有模型，大小的属性。那么类B和类C自然也会有同样的属性。
对于类D，麻烦来了，普通的继承只是简单的把对象复制下来，虚函数表指针更改一下。所以类D会出现两个模型，大小的变量。这当然是不符合，于是虚继承便诞生了。

代码演示：

接下来就是虚继承的实现原理了，懂了原理，一切都是理所当然的了。

有了虚函数，虚继承就简单了，虚继承和虚函数类似。虚函数有虚函数表（vtable），虚函数表指针（vptr）。
虚继承有虚继承表（vbtable）,虚继承表指针（vbptr）。

虚函数表在编译时初始化在代码区，虚继承表同样在编译时初始化在代码区。

虚函数表指针的赋值由操作系统在调用构造函数前负责初始化。
虚继承表指针的赋值同样由操作系统在调用构造函数前负责初始化。

虚继承表的实现原理：有了虚继承，子类就会有虚函数表，虚继承表里面记录的是每个父类成员变量相对于父类地址的偏移值。B1类和B2类都有这个表，C类继承B1和B2后，同时继承了这两个表，所以C类在继承每个变量时就会和虚继承表比对，发现size这个变量在两个虚继承表的偏移量相同，所以只继承了一个size。

## Part4：C++的模板用途与实现原理----第七课：模板的用法与原理

类模板和函数模板可以极大的提高程序的灵活度

很多萌新对模板的使用非常困惑，不明白为什么么这们用，而且模板的坑有很多，而且这些坑不懂原理的人会经常碰到。

其实，只要明白了模板的实现原理，这些坑都是理所应当的，甚至本就如此。

模板的实现原理：
编译器会对模板进行两次编译：
1.在声明的地方对模板代码本身进行编译，注意：这次的编译无法对类型进行检查。
2.在调用的地方对参数进行替换后的代码进行编译，这次会进行类型检查。
其实就是C++编译器帮程序员根据函数模板生成了需要参数类型的函数原型。

这种编译方式确实可以让我们只写一个模板，就可以使用多个类或函数。

看代码：
额外说一点，C++类模板的成员函数在外面实现时必须把模板头带上，否则无法编译。

这种的编译方式也带来一个缺点，就是类模板的声明和实现部分不能再分文件编写，因为在编译期，模板的第二次编译必须要完整的看到类模板的全部实现部分，而分离式编译只有到了链接阶段才可以看到类的实现部分。

同时，任何使用模板的地方都要给模板类型，有些可以自动推导（比如类内部的各种操作），但有些不行（比如继承），还是用刚才的代码举例。

## Part5：C++的内存管理方式----第八课：malloc，free，new，delete的工作原理

首先讲一下栈内存和堆内存的概念：

1. 栈内存比较小，32位程序一般不超过4M，在程序加载时就已经分配，可以用各种方式寻址（汇编那里已经讲过了）
2. 堆内存是比较大的，可以说2g（32位windows程序用户区）或3g（32位linux程序用户区）的用户区大部分都是堆内存，所以在程序加载时堆内存是没有经过mmu分配物理内存的，堆内存一旦越界直接报错。此外，堆内存唯一的寻址方式就是指针。

所以程序的主要数据其实在堆内存。栈更加灵活，高效，但是空间小。堆内存空间大，需要时通过mmu分配在物理内存上，这样的设计方式极大的提高了物理内存的使用效率。

接下来讲一下malloc和free的工作原理，如代码所示。
再接下来讲一下new和delete的工作原理，也如代码所示。

## 第九课：内存碎片化和内存池介绍

内存碎片化原理简单来说就是我们在堆内存上反复的申请，释放内存。导致内存之间存在太多的碎片，会浪费大量的堆内存资源。
如图所示：

当然了，实际上内存的分配方式要远远比这张图复杂，但仍然会出现这种问题。
程序运行到后面，可能看上去还有1个G的内存，但实际上连100M都拿不出来。

内存碎片化是个比较严重的问题，几乎所有的服务器都会采取办法解决问题，解决方法，就是内存池。

内存池的设计思路：

1. 对new和delete进行重载（在C++中，new和delete都是运算符，所以是可以重载的）
2. 让new和delete使用我们的内存池提供的内存分配方法。

内存池如图所示。

![](/assets/images/2022-10-29-11-45-48.png)