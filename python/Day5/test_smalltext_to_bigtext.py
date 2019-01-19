#!/usr/bin/python
#coding:utf_8

'''
基于内容输入文件，构造一个大文本
input.txt   output.txt
'''
#vim输入读取文件在内存，读取很慢

import sys

#从命令行参数获取
#获取到内容输入文件的路径
input_file_path = sys.argv[1]
#输出文件路径
output_file_path = sys.argv[2]

#获取构造文本大小
output_size = int(sys.argv[3])*1024*100
#打开内容输入文件
input_file = open(input_file_path,"r")
#读取内容
input_data = input_file.readlines()
#打开内容输出文件
output_file = open(output_file_path,"a+")

#行计数器
count = 0

#当前文件大小
total =  0

while True:
    if total > output_size:
        break
    output_file.write(input_data[count%len(input_data)])
    total += len(input_data[count%len(input_data)])
    count+=1


input_file_path.close()
output_file_path.close()


