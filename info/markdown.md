# Markdown 使用样例 #
# 标题示例 #
# 一级标题 #
## 二级子标题 ##
### 三级子标题 ###
#### 四级子标题 ####
##### 五级子标题 #####
###### 六级子标题 ######
高级标题
===
低级标题
---
## 区块引用示例 ##
正文
>区块
>>子区块  
>>空两格以换行
>
>空一行以回到原来区块  
>区块内支持其他Markdown语法  
>## 比如标题 ##
>+ 无序列表项1
>- 无序列表项2
>* 无序列表项3
>1. 有序列表项1
>2. 有序列表项2
>3. 有序列表项3
## 列表项示例 ##
+ 无序列表项1
- 无序列表项2
* 无序列表项3
1. 有序列表项1
    1. 次级有序列表项1
    2. 次级有序列表项2
2. 有序列表项2
3. 有序列表项3
* 同一列表项下的多个段落  
    段落二  

    >列表项下的区块  
    >段落三  

2016\. 记得空一行以退出区块或者列表项  
2017\. 必要时使用转义字符'\\'以避免不必要的意外的  
2018\. 列表项  
2019\. 或者区块  
## 表格示例 ##
| 1 | 2 | 3 | 4 |  
|---|---|---|---|  
| 2 | 3 | 4 | 5 |  
| 3 | 4 | 5 | 6 |  
| 4 | 5 | 6 | 7 |
## 代码示例 ##
欲打入代码，制表符缩进即可
记得和上面空一行

    #include<iostream>
    #include<cstdio>
    using namespace std;
    int main(){
        printf("Hello World!\n");
        return 0;
    }
## 分割线示例 ##
星号或者减号均可
* * *
所在行内至少有三个
***
是否相连无所谓
*****
但不能存在其他字符
- - -
空格除外
---------------------------------------
## 链接示例 ##
行内式  
[百度](https://www.baidu.com "这是百度")

参考式  
[京东][ID1]
[bilibili][ID2]
[知乎][ID3]
[CCF][]

[ID1]:https://www.jd.com "这是京东"
[ID2]:https://www.bilibili.com '这是bilibili'
[ID3]:https://www.zhihu.com (这是知乎)
[CCF]:http://www.noi.cn (隐式链接)

有些特别的情况下，单引号包裹的文本无法被识别
## 强调示例 ##
*星号强调*  
**星号大强调**  
_下划线强调_  
__下划线大强调__  
在句子 __内部__ 的强调，注意 *前后* 要有空格
## 行内代码示例 ##
在 `行` 中插入 ```代码``` 需要 ``反`` 引号  
比如 `<html>` 什么的  
并不一定要打括号
## 图片插入示例 ##
行内式  
![LYD](https://pic3.zhimg.com/5c90d0e342c310859b2662a216c8d312_xl.jpg "这是LYD")

参考式  
![QY][ID4]  
![SHY][ID5]  
![ZRT][ID6]  
![MHR][]

[ID4]:https://pic3.zhimg.com/v2-89b4a507781787197bccd22f0eedebca_xl.jpg "这是QY"
[ID5]:https://pic1.zhimg.com/v2-8e26731da30da0b0de03ecf43d7ac064_xl.jpg '这是SHY'
[ID6]:https://pic4.zhimg.com/v2-1ad84a65d460027a333dc7393ed94e57_xl.jpg (这是ZRT)
[MHR]:https://pic3.zhimg.com/v2-61ebd983a778cad08002560af42715c6_xl.jpg (这是MHR)

就目前而言，Markdown尚且不支持图片的自定义大小、位置，需要使用HTML\CSS的辅助  
例如使图片居中：
而且，`<center>`和`</center>`并不被Github所支持

<center>  
    <img src=http://uoj.ac/pictures/UOJ.png>  
</center>

## 转义字符 ##
使用‘\\’来将特殊的符号文本化
## 自动链接 ##
<https://github.com/seoi2017/OICode>
## 数学公式 ##
使用MathJax引擎(本质是脚本生成的文本，使用LaTeX公式)

    //加载MathJax引擎
    <script type="text/javascript" src="http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=default"></script>
    //行间公式
    $$x=\frac{-b\pm\sqrt{b^2-4ac}}{2a}$$
    //行内公式
    \\(x=\frac{-b\pm\sqrt{b^2-4ac}}{2a}\\)

<script type="text/javascript" src="http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=default"></script>

行间公式测试  
$$x=\frac{-b\pm\sqrt{b^2-4ac}}{2a}$$  
行内公式\\(x=\frac{-b\pm\sqrt{b^2-4ac}}{2a}\\)测试

# Github Markdown 扩展样例 #
## 带选择框的列表 ##
- [ ] 列表项1
    - [ ] 嵌套列表项1
    - [x] 嵌套列表项2
- [x] 列表项2
- [ ] 列表项3
## GFM代码高亮 ##
```cpp
    #include<iostream>
    #include<cstdio>
    using namespace std;
    int main(){
        printf("Hello World!\n");
        return 0;
    }
```
## 表格文字的对齐方式 ##
对于第一行下面的短线

| 什么也不加 | 左侧加引号 | 右边加引号 | 两边都加引号 |  
|---|:---|---:|:---:|  
| 是 | 还是 | 是 | 就是 |  
| 左对齐 | 左对齐 | 右对齐 | 居中对齐 |
## 定义式脚注 ##
这是一个脚注[^1]

[^1]:脚注文本
## 删除线 ##
~~删除线效果~~  
## Emoji表情 ##
:+1:
# 一些不被Github支持的Markdown的扩展语法 #
## 加亮突出 ##
==高亮线效果==
## 目录(通常在全文最开头使用) ##
[TOC]
## 定义列表 ##
列表1
: 定义1
列表2
: 定义2
列表3