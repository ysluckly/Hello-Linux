#!/usr/bin/python
#coding:utf-8

'''
Python爬虫项目：从小说网站获取一本小说内容
'''
#默认中国汉字编码字符：GB2312/GBK ，需要进行解码重新编码

#Python库，提供一系列针对url的操作方法
import urllib2
#Re正则表达式 提供一系列针对正则表达式的方法
import re
#BeautifulSoup库
from bs4 import BeautifulSoup
#系统库
import sys
#获取页面内容
def OpenPage(url):
    MyHeader = {}
    #urllib2.Request 填写两参数，1，url，2，请求头headers
    request = urllib2.Request(url,headers = MyHeader)
    #类文件对象
    #urlopen发送指定请求
    f = urllib2.urlopen(request)
    #读取响应对象的内容
    data = f.read()
    #return data
    #此时data是一种乱码，需要进行编码解码方法 encode/ decode
    #ignore replase  //防止出错  ,一个忽略，一个换成 ？
    return data.decode("GBK",errors = "ignore").encode("utf-8") #error可以省略
#测试访问页面内容
def Test1():
    print OpenPage("http://www.shengxu6.com/book/2967.html")

#解析主页内容，获取url列表
def ParseMainPage(page):
    #解析页面,使原来的乱序变得规整
    soup = BeautifulSoup(page,"html.parser")
    #测试
    #return soup
    #find_all方法查找所有内容，包含read字符串 的href链接，通过正则表达式
    list_charts = soup.find_all(href = re.compile("read"))
    #print list_charts
    #列表生成式
    url_list = ["http://www.shengxu6.com"+item["href"] for item in list_charts]
    #上一语句可以写成下面语句
    '''
    url_list = []
    for item in list_charts:
        #print type(item) //标签
        #每一个item是一个tag标签类的实例化对象
        #通过没有一个标签item["href"]可以获取href值
        print item["href"]
        url_list.append("http://www.shengxu6.com"+item["href"])
    '''
    return url_list
def Test2():
    page = OpenPage("http://www.shengxu6.com/book/2967.html")
    print  ParseMainPage(page)
#解析详情内容，获取小说内容（一章内容）
def ParsePageCatchContent(page):
    soup = BeautifulSoup(page,"html.parser")
    title = soup.find_all(class_="panel-heading")[0].get_text()  #列表第一个元素，即章节名
    content = soup.find_all(class_ = "content-body")[0].get_text()

    return title,content
def Test3():
    page = OpenPage("http://www.shengxu6.com/read/2967_2008734.html")
    title,content = ParsePageCatchContent(page)
    print title
    print content[:-12]

#把获取的内容写入文件
def WriteDateToFile(file_path,data):
    f= open(file_path,"a+")  #追加
    f.write(data)
    f.close()
    #以上代码可以替换下（上下文管理器）
    '''
    with open(file_path,"a+") as f:
        f.write(data)
    '''
#测试
def Test4():
    WriteDateToFile("CatchContent.txt","jj")

if __name__ == "__main__":
    #Test1()
    #Test2()
    #Test3()
    #Test4()
    #构建爬虫项目
    #小说主页
    #url = "http://www.shengxu6.com/book/2967.html"
    url = raw_input("请输入要爬取的小说网址：")
    #获取主页内容
    main_page = OpenPage(url)
    #获取主页内容各章节url
    url_list = ParseMainPage(main_page)
    for url in url_list:
        print "Clone_url=" +url
        detail_page = OpenPage(url)

        title,content = ParsePageCatchContent(detail_page)
        data = "\n\n\n"+title+"\n\n\n"+content
        data = data.encode("utf-8")
        #可能存在的问题：直接写入，编码不对，需要进行重新编码
        WriteDateToFile("PythonCatchContent.txt",data)
    print "爬取完毕"


