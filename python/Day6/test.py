#!/usr/bin/python
#coding:utf-8

'''
异常处理
'''
#认识异常
'''
程序运行出现错误，就是异常，python对于异常会报出相关错误，就是解释器已经定义好了各种异常的错误类型
有内置异常类，其实就是继承Exception类
所谓异常就是一个对象，出错抛出异常就是构造了一个异常对象，对象类型就是Exception(Python异常的基类)
比如ptint出错，报SyntaxError异常
下标越界。解释器抛出一个IndexError异常
打开一个不存在的文件，抛出IoError的异常
'''
#总结
'''
1，异常就是程序执行出错，根据不同类型，抛出不同的异常
2，如果一个程序抛出了异常，如果不对这个异常做任何处理，默认行为就是终止程序
3，这里的异常与c++中的异常左一个区分，python解释执行，所以语法错误与执行逻辑出现问题导致的错误都被解释器统一一个异常
    而c++/java都是预先对代码进行编译，如果语法出错，在编译期间就能检查出来，因此，c++/java异常只涵盖了运行时错误
'''

#异常机制的意义
'''
轻松捕获和处理异常
归根结底就是想办法帮我们简化代码的错误处理逻辑
通过异常，将做到错误逻辑与正确逻辑的分离，使得代码可读性更好
'''


###############处理异常
#不知道问题是啥
try:
    print "123"+11
except:
    print "出现异常"

#不仅知道有问题还能分析问题
try:
    print "22"+2
#捕获某种异常，e就是异常对象名字，包含了异常所有信息
except TypeError,e:
    print e
    print type(e)
#捕获所有异常
except Exception,e:
    print e
    print type(e)  #L类型具体信息

#查看所有异常类型
'''
1，解释器，dir(__builtins__):前半部分都是异常类型
2，百度
'''
#程序一旦出错，就不会执行try后续代码,但finally的代码块总会被执行
try:
    print "11"+11
    print "nihao"  #不会被执行
except:
    print "异常"
    print "pytohn"
finally:  #与except搭配使用
    print "总会被执行"

#异常也可以自己在程序中通过 raise Exception("异常")抛出，，通过except进行捕捉
try:
    raise Exception("哈哈，出现异常")
    print "nihao"  #不会被执行
except Exception,e:
    print e
    print "pytohn"
finally:  #与except搭配使用
    print "总会被执行"
