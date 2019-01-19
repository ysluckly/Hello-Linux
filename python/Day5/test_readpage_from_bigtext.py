#!/usr/bin/python
#!coding:utf_8

'''
python实现less命令，从文件中一次读取一页内容
'''

import sys,os
#构造一个内容读取函数

def PrintScreen(path):
    #行计数器
    line_count = 0
    for line in f:
        print line
        #遍历文件对象，打印每一行
        if line_count >25:
            break
        line_count+=1

path = sys.argv[1]
f = open(path,"r")
while True:
    os.system("clear")
    PrintScreen(f)
    command = raw_input(":")
    if command == 'q':
        break
f.close()

