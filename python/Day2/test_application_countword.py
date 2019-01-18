#!/usr/bin/python
#coding:utf-8

'''
统计词频
'''

f = open("text_count.txt","r")

data = f.readline()  #list
#字符串-次数 ----》字典
Words = {}
#循环遍历每一行
for item in data:
    #in/not in  在与不在
    #因为字符串后面追加换行符，运用切片的操作干掉
    word = item[:-1]
    #判断是否保存
    if word in Words:
        #这个字符出现过
        Words[word] +=1
    else:
        #没有出现过
        Words[word] = 1
#统计完毕
print Words

f.close()
