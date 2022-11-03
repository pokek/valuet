---
id: vj7gwwmpa7tyr21f8m1c7v9
title: Tools
desc: ''
updated: 1667261178997
created: 1662116582069
---


## 数组中的快慢指针使用

### Leecode 100

多题一解 [[fruit]]

```java  {.line-numbers}
    // 非常nice的题目
    '定义两个指针，慢指针指向，快指针指向'
public static void main(String[] args){
    int[] arrs = new int[20];
    int left = arrs.length;
    int right = 0;
    while(right < left){
        System.out.println("aaaa");
    }
}
```

```java {.line-numbers}
public static void main(String[] args){
    int[] arrs = new int[20];
    int left = arrs.length;
    int right = 0;
    while(right < left){
        System.out.println("aaaa");
    }
}
```

#### 随手记得一些快捷键

##### vscode

vscode ：复制一行  shift + alt + 上下箭头
选中关键字，修改其一其余全部修改  ctrl + d (适用leecode)
选取任意一个导航栏: ctrl + q
全局替换 ctrl + h
快速定位某一行: ctrl + g
放大整个界面缩小放大： ctrl + +/-
添加多个光标: ctrl + alt + 上下箭头

选中一个区块同时编辑: alt + shift + 鼠标拖拉 或者 点击鼠标 添加多个光标 / 添加多个光标后，按下左/右箭头进行文本全部选择

编辑器窗口管理：ctrl + 1/2/3 三个窗口之间切换  一个窗口有多个文件 切换文件 ctrl + tab

```java  {.line-numbers, highlight=[4-5]}
// ok it's fine

public static void main(String[] args){
    String.trime("  __wingwog__");
    System.out.print("哈哈哈");
}
```

一个文件去用多个窗口显示卧槽超好用 ctrl + tab

vscode下窗口是一个重要概念，不同窗口之间文件可以多开，一个窗口下开不同文件

代码格式调整：shift + alt + f
代码行上移动，下移动 超级好用： alt + 上下箭头
显示/隐藏侧边栏 : 不在编辑文件中使用有效 ctrl + b
超好用 显示/隐藏终端：ctrl + `;
超好用跳转行尾设置: ctrl + ;
外部设置需要跳出编辑文件: ctrl + , 打开设置
vscode ctrl + p ：按下>进入万能指令模式(即ctrl + shift + p)且可以输入不同符号表示需要的相关信息 ?为近期操作，!显示errors/warings : 跳转行, @跳转标记或变量  
怎么按下 ctrl + k m   ctrl k 按下后松开ctrl 按下m
同步git：command:public git

---

难受ing

---

##### Dendron

使用Dendron 核心思想是以笔记为中心，笔记命名为xxx.xxx.xxx，该命名方式以在其所在的tree_view中是以层级结构显示，但实际电脑上储存文件还是以xxxx.md形式进行存储，以文件名的层级为结构目录xxx.xxx  xxx.xxx.xxx.
首先先理解下该拓展下的workspace含义，其中有root workspace/在实际文件系统中即(Dendron)下有相应的工作区间设置和相关配置，然后就是自己的notes文件下的相关笔记，其中有.vscode文件，一系列笔记都记录在该文件下，并且图片存在asserts中，在这种文件结构下，可以自己进行一些代码的编写。
look up 可以查找建立的note文件和创建不存在的note文件 ctrl + l
超棒的一个功能引用其它笔记: ![[alogrithm]] 需要显示的话 加上:#*但是需用该插件自带的note preview 不支持自动滚动，但是可实时渲染。
用自带的preview黏贴图片需要 ctrl + alt + v

强大的重构功能： 重构也就重构文件名，重构标题头(重命名/移动标题到其它整个note文件中并附加到文件尾部，没有就新建)，重构继承关系 (并且重构的过程中，保持了引用的笔记名也进行了重构)  注意的是：需要引用重构笔记的笔记文件是已经保存着的，还一个注意点就是重构文件名和标题头都只能第一级的结构目录下，但是继承关系可以重新去定。

并且提供了tags标签，标签标签就是有相应的内容提示，并有颜色提示

创建vaulet相当于本机文件系统创建文件夹，在插件笔记模型中就为另一个知识库

既然有不同知识库，那么就有相应的笔记引用内容了，接下来继续笔记引用这一节(==内容太多了，之后再看，还有schema==)

笔记引用：对于一个笔记来说，视图中的backlines显示的是该note被那几个笔记引用路径，command:copy note link快速复制笔记链接
command: show note graph 展示笔记图

### Refercen to image

![](/assets/images/2022-09-02-21-03-22.png)

![](/assets/images/2022-09-02-21-13-36.png)

### Reference to Note

![[recipes.cook]]

什么鬼，你是煞笔

[[example.my-example|tags.example.my-example]]

tags常规用法

[[2022年9月2日|tags.yel]]

markdown-enhanced相匹配主题为---none.css

vscode背板颜色---#f2f8fc
