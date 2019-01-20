#!/usr/bin/python
#coding:utf-8

'''
根据文件名删除三天前的文件(前提是以时间戳结尾的文件)
'''

import os,datetime
#from datetime import datetime
def CheckRemove(filename):
    #today = datetime.now()
    today = datetime.datetime.now()

    #将文件名与后缀分开
    _,Getstr = os.path.splitext(filename)
    GetTime = Getstr[4:]
    #如何吧字符串转换为时间戳
    Time = datetime.datetime.strftime(GetTime,"%Y%m%d")
    if (today - Time).days >3:
        os.remove(filename)
#跳转工作路径
os.chdir("./data")
for filename in os.listdir("./"):
    CheckRemove(filename)
