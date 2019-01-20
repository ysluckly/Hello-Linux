#!/usr/bin/python
#coding:utf-8

'''
将目录中的文件批量重命名（加上后缀(即时间戳)）
'''

import os,time

#time库中提供一系列的针对时间操作的方法
#改变linux系统的工作路径
os.chdir("./data")

#strftime 把时间戳转换为指定格式的字符串
#localtime 获取当前时间，转换为指定字符串
data = time.strftime("%Y%m%d",time.localtime())

#遍指定路径下的文件

for filename in os.listdir("./"):
    #listdir 返回一个list列表，每个元素都是文件名
    #os.rename()方法，修改文件名，第一个参数叫做源文件，第二个参数叫修改文件名
    if filename.startswith("Text"):
        os.rename(filename,filename+data)
