#!/usr/bin/python
#coding:utf-8

'''
模块与包
'''

#模块
'''
当代码量比较大的时候，我们最好吧代码拆分为又组织的代码片段
每个代码片段里面包含了一组逻辑有关联的函数或类
每个片段放在一个独立的文件中，这样的片段称为模块
使用import可以在一个python文件中引入其他模块

'''
#对比c语言的include
'''
如果一个文件想要使用其他文件内容，通过include即可，
本质就是文本替换，因此可能导致一系列的问题（重复包含，包含顺序相关问题[部分文件依靠前面文件]）
'''

#模块也是对象
'''
python中模块避免了c语言的这些问题，import实际就是创建了一个模块对象，通过这个对象访问模块的具体方法

'''
import os,sys
print type(os)
print id(os)


#模块搜索路径
'''
尝试import时，解释器就会知道模块文件的路径
模块是库模块就不用担心路径
如果自定义模块，不在当前路径下，就需要用sys.path.append("...")引入模块路径
'''
print sys.path

#假如在当前文件引用下级目录中Add模块，//失败，，解决方案追加目录，path中即加列表元素

sys.path.append("/home/ys/code/GitHub/Linux/python/Day6/ADD")
from Add import add

print add(2,3)
#假如在当前文件引用上级目录中模块，//失败  解决方案追加目录

sys.path.append("/home/ys/code/GitHub/Linux/python/")
from Sum import sum
print sum(3,1)


#理解“理解命名空间”
'''
#命名冲突问题：如果一个项目中的代码量很大，那么很有可能函数/类/变量名字冲突，
因此C语言采用的方案是给名字加一个又丑又长的前缀
c++  namespace
python模块也相当于命名空间，例如os.path.exits(),通过这样的结构，就有效避免了命名冲突

'''



#import 可以引入一个，也可以多个
#推荐一个，美观
'''
引入顺序：按照标准库，第三方库，应用程序自定制模块的顺序来引入，提供程序可读性
模块也是一个对象，也与作用域的概念，在函数内部，import只在函数内有效
模块既然是一个对象，那么就可以给这个对象赋值就是重命名，这样也简化了敲代码
'''

#from-import语句
'''

import 直接导入一个模块
有时候我们只需要一个模块的一个或多个函数，就可以使用from-import的方法了
还可以进行协调引入私有方法，from xxx import _xxx,  from xxx  import * 忽略私有化函数

'''

#import as
'''
给模块起简短变量名
'''

#导入意味着被执行
#就是说无缩进的代码总是会被执行到，这通常包含函数的定义与全局变量的定义
#使用模块的一些函数与变量，因此往往我们在实现一个模块时，只是将函数定义/类定义到顶层代码中
#python 中main函数：if __name__  == "__main__"

#理解 "导入"与“加载”
'''
import引入一个模块时，其实有两大阶段，现将这个模块的文件加载到内存中，
并创建一个对象来表示，然后通过一个变量名将这个模块引入到当前的命名空间中
使用reload可以重新导入
'''
#reload场景  项目的config.py配置文件
#服务器如果在引用了一次，，然后中途修改了，又不能关闭服务器，所以就可以重新导入就可以

#模块的内置变量
print globals()  #全局命名空间下的内置变量
'''
__builtins__：内建函数模块：open，doc等
__name__:模块名字如果从这个模块开始，，就是__name__ == __main__
__file__:文件名字
__doc__:模块的文件字符串
__package__ :模块从属的包名
'''
'''
def add(x,y):
    return x+y
if __name__ == "__main__":
    print add(2,3)
如果name== main，执行测试代码，否则会认为add会被其他文件引用
'''

##########################包
#当代码量变大时，拆分多个文件（模块）不能满足，所以就按照一定文件目录层次化的组织这些模块，同事也可以解决模块之间的名字冲突问题
#在apple/目录中新增  __init__.py,,此时的目录就是一个包
#引入模块是import apple.add

#sys模块的方法
'''
是基础的模块，里面很多属性都是描述程序的执行环境
eg：
sys.argv:命令行参数，一个列表
sys.byteorder:返回机器的字节序
sys.builtinmodulenames:解释器内置的模块
sys.dontwritebytecode:如果为True,就不会有pyc文件，
sys.executable:解释器的绝对路径
sys.exit()  退出python
sys.getrefcount() : 获取对象的引用计数
sys.path():模块的查找路径：列表
sys.module:一个字典对象，描述当前对象加载了哪些模块
sys.stdin....stdout....stderr:三个对象标准输入，输出，错误
sys.version:python版本信息
'''
print sys.version
#os模块

'''
也是一个比较重要模块
官方称为 ：会砸的系统操作接口
不同操作系统的api可能不同，os试图将不同api封装一起共开发者使用

'''
#进程信息
'''
os.getpid()
os.getppid()
os.getuid() //用户id
os.getenv():按key获取当前的环境变量
os.uname（）：操作系统五元组


'''

#文件操作与路径操作
'''
os.abort():生成一个SIGABORT信号，（往往终止程序）
os.exec()函数族：进程替换函数族
进程等待等待
os.getloadavg():获取系统负载，获取一个三元组，返回近一分钟，三分钟，十五分钟系统负载的值
关于系统负载，其实就是描述系统 繁忙程度 的重要指标，数字越大月繁忙
os.system("")创建一个子shell，等价于C语言中的system函数
'''
print os.getloadavg()








