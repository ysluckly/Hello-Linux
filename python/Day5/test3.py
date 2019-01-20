#!/usr/bin/python
#coding:utf-8


'''
用我们的代码，生成一个py文件并且执行，输出hello pyton
'''
import os,sys

#stat 保存好多的定义好的变量
import stat

#判断文件是否存在，返回布尔值
if os.path.exists("hello.py"):
    #删除指定路径文件，任意路径（绝对与相对）
    os.remove("hello.py")

#生成一个文件
os.mknod("hello.py")

#打开指定文件
#open    r  w    a   b
#os.open  打开方式是数字
f=os.open("hello.py",os.O_RDWR)  #2 -->os. O_RDWR

os.write(f,"#!/usr/bin/python\n print 'hello python'")

#关闭
os.close(f)

#调用os方法
os.chmod("hello.py",320)
os.system("./test3.py")

