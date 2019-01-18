#!/usr/bin/python2
#coding:utf-8

#复习
print "hello world"
a=1.2
b=1.555555555555555555
print type(a)
print type (b)

#新内容
#break continue
count = 0
while True:
    if count  == 2:
        count+=1
        continue
    if count > 5:
        break
    print count
    count+=1

# pass 占位符，防止if不干事，
if 1<2:
    pass #do nothing
else:
    print "test"


# 列表解析，又叫列表生成式，灵活生成生成各种列表
list1 = [x for x in range(1,10,2)] #前面表示操作，后面表示哪来的
print list1

list1 = ["第"+str(x)+"个" for x in range(1,10,2)]  #花式生成
print list1

list2 = [x ** 2 for x in range(1,10,2)]  #花式操作
print list2

list3 = [x **2 for x in range(50) if x%2 == 0]  #加条件
print list3

#函数  参数无敌，任何形式都可以,即一切对象为参，
#参数可以有默认值，，调用时可以指定赋值
#python 无函数重载
def Sum(x = 10,y = 20):
    Num = x+y
    return Num
print "函数结束"
print Sum(1,2)
print Sum(1)   #默认值
print Sum()
print Sum(y = 3)  #只给y赋值


#声明一个函数，多个返回值
def Test():
    return 1,2,3,4

#多个接收，全返回逐个赋值
a,b,c,d = Test()
print a,b,c,d
#一个接收，，即返回元组
f = Test()
print f
#否则可以同占位符
a,_,_,d = Test()
print a,d

#函数类型与id
print type(Test) #函数类型：function
print id(Test)   #有空间就是有id，有id就是对象

#文件
'''
f = open("Text.txt","r")
#读时，会将全部内容放进缓冲区，
#一部分被读走后，下一次读取这部分就不在了

#读取全部内容,返回的是一个列表，列表的每一个元素都是一行
data3 = f.readlines()
#读取指定长度内容
data1 = f.read(5)
#读取一行
data2 = f.readline()

print data3
print data1
print data2
'''

'''
f=open("Text.txt","w")
f.write("niasnlasnc\ndscscs\nscsc\n")
f.writelines(["123\n","2434334553\n"])
f.close()
'''

