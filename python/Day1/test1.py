#!/usr/bin/python
#coding:utf-8
#from __future__ import division   #除法方法
print "hello python"  #输出hello

#第一种执行：python+文件
#第二种执行：
#chmod +x 文件名
#./文件名

#python是动态强类型
#解释时检查类型，不支持隐士类型转换
#变量与赋值
#直接赋值
a=1
b=0.5
#链式赋值
a=b=c=1
#增量赋值
a= 10*2
a=208*b
#多元赋值
x,y = 1,2
#给同一变量赋值，最后一次为准
a=0.5
a=2
a="123"
#################遵守变量命名规范:<代码大全> 10,11章
#1，person_name
#2, PersonName  //大驼峰
#3，personName  //小驼峰

#对数字没限制，把数字放内存中

#type(变量名)
type(a)
print type(a)


#复数类型
print 2+3j

#字符串
#声明 ‘’、“”、‘’‘ ’‘’三种
#互不干扰,三引号在最外面即可
#eg：
print '''niha，"haha",'wozaizhe' '''
print "abc"+"def"
print "yao "*4
print type("nihao")

#字符串象数组存储，可以用指定位置取元素
str1= "abcdefg"

print str1[0]
#字符串元素是不可改变对象
#错误：str1[0] = 'e'

#没有字符类型char

#切片操作法

str2 = "ssssssssssssccccccccccccccdcaaca"
print str2
#冒号前后两个数字构成前闭后开区间[1,5)
print str2[1:5]
#区间前默认0，后面默认字符串长度，即最后
print str2[:5]
#填写负数，；len-n
print str2[2:-2]

#计算对象长度，返回整数
str3 = "Hunter"
print len(str3)

#字符串格式化
str4 = "Number is %d" % 10
str5 = "Number is %d/%d" % (11,12)
print str4
print str5
#布尔类型
#True/False   1/0
print False-1
print type(True)

#获取用户输入函数，返回值字符串  raw_input()
#对非字符串操作：年龄
#str1 = raw_input("请输入您的学号：")
#print str1

str2 = raw_input("年龄")
#由于返回值是字符串，
#如果字符串与整数相加，就需要强制类型转换，不支持隐士类型转换
print int(str2)+1

#乘法
print 2 * 3 # 6
#乘方
print 2 ** 3  # 8

#除
#传统除法
a=1
b=2
print a/b   # 取整 0
#精确除法
#from __future__ import division
print a/b  #精确  0.5
#地板除  向下取整 //
print a/b

#关系运算符相同 ,返回布尔值

#赋值运算符  但是不支持自增自减

#逻辑运算    and   or  not   #& | !   [存在短路情况]
print 1<2 and 3 != 4

#3 > 4>5  没有错，，但可读性太差，不建议

#字符串判等
str1 = "123"
str2 = "adasd"
print str1 > str2

################三剑客 :列表、元祖、字典
########################列表 list [] 可变对象

list1 = [1,0.5,[1,2]]
#下标取值
print list1[1]
print list1[2][1]

print type(list1) # list类型

#列表切片 [:]
print list1[:2]

################################元祖 tuple()
#【一点与list不同，，对象不可修改,（）括号声明】
tuple1 = (1,2,3,4)
print tuple1[2]

print type(tuple1)
############################字典  dict{  }  键值对

dict1 = { "Ip":"127.33.45.5","Host":"www.baidu.com" }
print dict1["Ip"]
print dict1["Host"]

#赋值
dict1["Ip"] = "222.22.22.223" #存在key，直接修改
dict1["name"] = "Hunter"    #不存在，直接添加
dict2 = {1:"test"}

print dict1
print dict2[1]
print type(dict1)

#c/c++中四份1，python只是存储一份1
a=b=c=d=1
#三要素：定义一个值就会有一块拥有三要素：
#id标识符、type类型、value值，的空间，相同值得变量会贴在此处，
#该空间引用计数加一，是因为python的垃圾回收机制gc（引用计数原则）
#改变变量的值计数减一

#id()
print id(a)
print id(b)

b = 3
print id(b)

#缩进，过于纷争格式，索性不要括号，只要缩进

#if else
#for
#while

#1
if 1<2:
    print "这句在if里面"
    if 3 != 4:
        print "嵌套if的语句"
elif 3 != 4:
    print "这是if外的语句"
else:
    print "这是最后一个else"
print "这是if外的语句"

#2
count = 0
while count<5:
    print count
    count+=1

#3 list tuple 通用，，，遍历字典时是遍历key，
list2 = [1,2,3,4,5,6,8]
for item in list2:
    print item
print "循环结束"

#range(),计数作用，，，
#三参数，，start/默认起始  stop/默认结束  step/默认1
#起始，结束，前闭后开，，构成list
Test = range(10)   # 0~9 list
print Test

for item in range(1,6,2):
    print item

#无switch。，用表驱动代替，

