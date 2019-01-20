#!/usr/bin/python
#coding:utf-8

'''
面向对象编程
'''
'''
面向过程就是编年史：按照时间先后顺序，一条一条的记录发生的事情
面向对象就是记传史：按照每个王侯将相的维度，记录这个人是谁，有哪些特点，做过哪些事情
所以史记就是中国古代非常成功的一个 应用oop思想的著作
oop思想就是指解决一类问题时，使用一定的方法手段，一套组合拳，

'''

#这套拳的招式：
#抽象：
'''
抽象就是对现实世界问题和实体的本质行为，表现，特征进行建模
抽象的反义词就是具体
抽象的本质就是抓住重点关注的实体，忽略一些不需要关心的细节
写程序也四一样，我们不可能吧一个现实事物所有的信息都用程序表现出来，而只是表示我们需要用到的一些信息
'''

#类与实例
'''
类就是施工图纸，里面有房子重要的信心（户型，面积，层数）
实例即是建好的房子，房子改好了，才能住进去，
通过一张图纸能检出N个相同格局的房子，那么这N个实例都是属于同一个类  type（）
通过一张图纸建造N房子，每个房子都有房号，，id()
每个房子住的人也不一样，就是值不一样      val()

'''
class Animal(object):
    #静态变量
    x= 0
    #非静态成员方法,1,self参数,
    def Print(self):
        print "这是非静态成员方法"
    def run(self):
        print "animal  runging"
    #非静态变量
    #python类的初始化
    def __init__(self):  #变量名加__变私有，外部不能直接访问，但python没有真正的私有
        self.Name = "Hunter"
        self.Age = 11
    #静态方法的声明
    #1,接受一个参数，返回静态方法
    #2,函数前加静态装饰器   @staticmethod
    #Print = staticmethod(Print)
A= Animal()
A.Print()

print A.Age
print Animal.x

#继承
class Dog(Animal):
    def run(self):
        print "Dog runing"

class Cat(Animal):
    def run(self):
        print "Cat is runing"

d = Dog()
d.Print()
d.run()  #子类有就在子类中找，没有上基类
print d.Name
print d.x

c = Cat()
c.run()

def WhoisRun(Animal):
    Animal.run()
WhoisRun(Animal())
WhoisRun(Dog())
WhoisRun(Cat())

#开闭原则，
#开放扩展，子类可以进行自由的扩展
#对调用封闭
print type(A)
print type(d)
print type(c)
#只能认祖归宗，不能与下一代比较
print isinstance(A,Animal)
print isinstance(d,Animal)
print isinstance(c,Animal)

'''
对象就是类的实例，是一个客观事物的抽象
吧多个对象按照一定的规则归一类，就成为了类
python中对象包含三个部分：类型，id，值
'''

#封装与接口
'''
封装描述了对数据/信息的隐藏的观念，对象的使用者只能通过接口来访问/修改对象的数据
封装的好处就是减轻调用者的使用负担，调用者只需要知道接口如何使用就好，而不需要知道对象的具体实现
封装这个概念当然不是只存在于面向对象思想中，回忆计算机网络协议栈的分层结构，也是为了达到封装的效果

'''

#组合/包含
'''
多个小的类组合成一个大的类，来解决一个大的问题
组合表示 has-a的语义
例如：一个学校类：包含了教师类，学生类
组合的目的就是代码复用
'''
#通讯录
#联系人类
class Person(object):
    def __init__(self,x,y):
        #私有变量用方法获即可
        self.Name = x
        self.Phone = y
    def Get(self):
        return self.Name,self.Phone
    def Set(self,x,y):
        if len(y)<11:
            print "错误Phone"
        else:
            self.Name = x
            self.Phone = y

c= Person("Hunter","10000")
print c.Name,c.Phone
a = c.Get()
print a
c.Set("hahah","88888")
a= c.Get()
print a
#电话本类
class Book(object):
    def __init__(self):
        self.Data = []
        self.Number= 0
    def Add(self,Person):
        self.Data.append(Person)
        self.Number+=1
    def Printc(self):
        print "共有折磨多人："+str(self.Number)+"人"
        for item in self.Data:
            print item.Name,item.Phone

b = Book()
p1 = Person("1","22222222222222222222222222222222")
p2 = Person("2","3333333333333333333333333333333")
b.Add(p1)
b.Add(p2)

b.Printc()

class Per(object):
    x = 19
    #@staticmethod
    #def Print():
    #    print x   #静态方法，但与静态成员很大区别，与类其他都没有关联，不能访问其他成员
    #类内的静态成员方法
    @classmethod
    def Printt(cls):
        print cls.x

class Child(Per):
    def __init__(self):
        #子类的构造器需要在执行一下父类构造
        Per.__init__(self)
        self.Sex = "Man"
        self.Drade = "222"

#子类的构造器需要在执行一下父类构造,否则无法调用父类成员变量，也可以使用super方法，找到父类，不需要指定父类名，super(Child,self).__init__()
cc = Child()
print cc.Sex,cc.x

pp = Per()
Per.Printt()
pp.Printt()

#判断一个类是不是一个类子类
print issubclass(Child,Per)
#判断一个对象是不是一个类的实例
print isinstance(pp,Per)
print isinstance(pp,Child)

#对一个类或对象的属性进行操作和判定
class C(object):
    x = 111
print hasattr(C,"x")
print getattr(C,"x")
setattr(C,"x",22)
print C.x
delattr(C,"x")
print hasattr(C,"x")

#dir：查看类与对象的属性
print dir(C)
#vars  与dir相似，dir只是返回属性，但没有返回值，vars返回值与属性
print vars(C)

#super 获取到当前类的父类，本质是工厂函数，创建一个父类

#特殊方法
'''
__init__:初始化构造器
__str__:给类一个返回值（解释类作用）（优先执行）
'''
