#!/usr/bin/python
#coding:utf-8

'''
实现ls命令
'''

import os,sys

path = sys.argv[1]
#os.walk遍历指定目录，然后返回目录，包含目录，包含文件名
for root,dirname,filenames in os.walk(path):
    for filename in filenames:
        print os.path.join(root,filename)
