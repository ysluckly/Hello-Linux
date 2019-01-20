#!/usr/bin/python
#coding:utf-8
'''
文件操作
'''
#文件操作
import os

#os.path提供了一系列的文件路径操作方法
#打印文件名
print os.path.basename("/home/ys/code/GitHub/Linux/python/Day5/test2.py")
#d打印所在目录
print os.path.dirname("/home/ys/code/GitHub/Linux/python/Day5/test2.py")
#返回路径与文件名构成的元组
print os.path.split("/home/ys/code/GitHub/Linux/python/Day5/test2.py")
#基于文件名进行,与后缀的分隔
print os.path.splitext("/home/ys/code/GitHub/Linux/python/Day5/test2.py")
