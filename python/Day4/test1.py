#!/usr/bin/python
#coding:utf-8

'''
序列与字典
'''

####################序列
'''
包含若干个元素，元素有序排列，可以通过下标访问到一个或者多个元素，这个的对象称为序列
包括：字符串、列表、元组
'''
#标准类型操作
'''
判等操作符   <=  >=  > < == !=
'''
#序列类型操作符
'''
in/not in：判断是否存在，返回布尔值
+：链接操作符（相同类型序列），连接操作符并不高效(新创建对象，吧原有的进行拷贝)，
    对于列表建议用extend来完成，对于字符串建议join这样的方法
*: 重复操作
元组不可变就是单层的对象id不可变，如果元组的一个对象是列表，那么列表的元素可以改变的
'''
a = [1,2,3]
b= [4,4,5]
print a+b
a.extend(b)
print a
print id(a)
print id(b)
print id(a+b)

print b*3

####序列的切片操作
#切片操作([],[:],[::]),通过下标访问某一个元素，或者谋个子序列，区间前闭后开
'''
序列下标：0~n-1,,,-n~-1
[:] :0~n-1
[::]:起始，终止，步长
注意的是：python的切片越界是没有关系的，遵循前闭后开，区间里面有多少就取多少
'''
list1 = [1,2,3,4,5,7,8,9,0]
print list1
print list1[1:8]
print list1[1:8:-1]
print list1[8:1:-1]
print list1[::-1]

#字符串反转
'''
C语言：1，首尾指针遍历交换，2，借助堆栈，3,运用库函数 std::reverse(str,str+strlen(str));
python: a = "niaho"  print a[::-1]
'''
#############序列内建函数
#len返回序列的长度
a= [0,2,"NIHAO" ,2,3,4]
print len(a)

#max返回最大值
print max(a)
#min返回最小值
print min(a)
#sorted排序（默认升序，四个参数） 会新建对象
b= sorted(a)
print b
d=sorted(a,reverse = True)
print d
#key:找到一个特殊的数，进行排序（长度）
aa = ["aaaa","sdsdsds","sadddddddddddddddd"]
print sorted(aa,key = len)
#sum 序列求和（全是数字)
aaa = [2,2,34,4]
print sum(aaa)
########enumerate 同时枚举序列的下标与值   每对映射一个(元组)
for item in enumerate(aaa):
    key,val = item
    print key,val
#eg：找出元素在列表中的下标
#丑陋：
in_list = [1,22,3,455,666,77,8]
def Find(in_list,x):
    for i in range(0,len(in_list)):
        if x == in_list[i]:
            return i
    return None
#美观
def Find1(in_list,x):
    '''
    for key val in enumerate(in_list):
        if val == x:
            return key
    return None
    '''
    for item in enumerate(in_list):
        key,val = item
        if val == x:
            return key
    return None

print Find(in_list,22)
print Find1(in_list,8)
print Find1(in_list,9999)

#zip就是矩阵的行列转换,
#首先将列表/元组转换为元组，汇总为一个列表，转换过程中行列进行转换
x = [1,2,3]
y = [4,5,6]
z = [7,8,9]
print x,y,z
print zip(x,y,z)
print id(x)
print id(y)
print id(z)
print id(zip(x,y,z))

x = (1,2,3)
y = (4,5,6)
z = (7,8,9)
print x,y,z
print zip(x,y,z)

#构造字典(键值对)
list2 = [(1,2),(2,3),(3,4)]
dict1 = dict(list2)
list3 = [[1,2],[3,4]]
dict3 = dict(list3)
print dict3
print dict1

#zip应用
key =  (1,2,3,4,5)
val = ("a","b","c","d","e")
dict3 = dict(zip(key,val))
print dict3
print zip(key,val)

######################字符串
#三种引号的区别
'''
单引号与双引号是等价的，不像有些语言，转义只在双引号中进行
python中“原始字符串”来完成这样的功能
三引号相比前两个区别就是可以跨行
'''

#理解字符串的不可变性
#字符串是不可变对象，只能创建不能修改,或者用切片进行新的创建
#a[0] = 'b'  ----->   a = 'b'+a[1:]

#原始字符串（raw strings）
#/se会自动替换为表情，在python就可以用原始字符串来解决，在字符串前面加上r，R，前缀，表示原始字符串,就是不存在转义

#repr函数与反引号操作符
#跟str(),作用相似,转换为字符串，精度都有限，但是repr比str精度高，打印字符串时，str出来没引号给人看，repr有引号，给解释器看

a = 1
print repr(a)

a = [1,2,3]
print repr(a)
print type(repr(a))

#将序列的字符串并成一个字符串
a = ["q","qq","aaaaa","xxxx"]
print '-'.join(a)

#按空格将字符串分割成列表
a= "  aa ss ee ff"
print a.split(" ")

#判断字符串的开头与结尾,返回布尔值
print a.startswith("aa")
print a.endswith("ff")

#strip 去掉开头，结尾空格，与制表符

print a.strip()

#左对齐、右对齐、中间对齐
a = "hello python"
print "["+a.ljust(20)+"]"
print "["+a.rjust(20)+"]"
print "["+a.center(20)+"]"

#查找子串，返回下标,不存在-1
print a.find("py")

#替换子串（新创建）
print a.replace("python","world")

#判断是数字/字母
#判断是字母或者数字
a = "adasdadi" #字母
print a.isalpha()
a="22ss2"
print a.isalnum() #字母或者数字
a = "sss"
print a.isdigit()#数字

#转换大小写
#lower，upper

#结束符
#python没有‘\0’


###################列表
#字符串只能由字符构成，而且不可变，但是列表可以任意对象，灵活
#使用切片操作访问列表元素（可以用切片操作改变元素 ）

#追加元素  a.append(3)
#删除指定下标     del a[0]
#按值删除 a.remove(val)
#列表比较 ==/!=  < >
list1 = [1,2]
list1+=[2] #+=一个元素理解为追加一个，，如果+=多个元素需要extend，+创建，，，extend不创建，表示追加元素
print list1
# in/not in/+ /extend(链接)

#列表是可变对象，有时会进行自身的修改，比如sorted新的创建，，list.sort()对自身修改
#sort默认的是归并排序的衍生算法，时间复杂度是O（N*log(n)）
#基于列表的堆栈
a= []

a.append(1)  #push
print a[-1]   #top
a.pop()  #pop  默认最后一个元素

#基于列表的队列
a.append(1)
print a[0]
a.pop(0)

#列表的深浅拷贝
#id相同浅拷贝，，，id不同深拷贝
a = b =c = d = [1,2,3,5]

print a,b,c,d
print id(a),id(b),id(c),id(d)
a = [99]

print a,b,c,d
print id(a),id(b),id(c),id(d)

#总结：列表 赋值= ，切片[:]，list工厂函数都是浅拷贝
#浅拷贝指的是：创建了新的对象，但是新对象中包含的子对象和原来的子对象是同一个对象
#深拷贝就是：创建新对象，同时这个新对象的子对象都是重新创建一份新的拷贝对象
#不想与原来的对象粘在一起，可以强制深拷贝通过 copy.deepcopy() 完成，简单，复杂对象都重新创建
#除非特殊声明，否则都为浅拷贝
#浅拷贝只有简单元素生成新的对象，复杂元素直接纳爱使用

####################################字典
#其实就是键值对，字典时基于hash表实现的，key唯一，必须能够hash(能够计算出一个固定唯一的hash值)，val就是无限制类型

#创建字典
#1,{}
#2,工厂方法 dict（），参数为键值对
#3,使用字典的内建方法 fromkeys()
a={}.fromkeys(('x','y'),0)
print a

#访问字典的元素
#[]获取到值,for遍历
#修改：在修改，不在直接添加
#in/not in/判断是否存在  if ”A“ in di1 print dict["A"]
#标准类型操作符：判等
#           即先判断长度，在判断key，在判断value
dict1 = {"in":"kkk","pp":"00000"}
print len(dict1)   #2

#item 返回一个元组（key，value）




