#!/usr/bin/python
#coding:utf-8

'''
爬取西安工业大学就业网招聘信息
'''

#数据格式
import json
import MySQLdb
import base64
import urllib2
from bs4 import BeautifulSoup

#根据url获取服务器响应的内容
def OpenPage(url):
    MyHeader = {}
    request = urllib2.Request(url,headers = MyHeader)
    f = urllib2.urlopen(request)
    data = f.read()
    return data

def Test1():
    url = "http://jy.51uns.com:8022/Frame/Data/jdp.ashx?rnd=1548055466011&fn=GetZhaopinList&StartDate=2000-01-01&SearchKey=&InfoType=-1&CompanyAttr=&CompanyType=&Area=&City=&CompanyProvice=&Post=&Zhuanye=&XLkey=&Age=&start=0&limit=15&DateType=999&InfoState=1&WorkType=0&CompanyKey="
    print OpenPage(url)

#根据主页上获取的招聘信息内容，获取招聘信息id
def ParseMainPage(page):
    #一般都是json格式（带中文）”u“一般表示默认unicode码
    #Jsondata = OpenPage("http://jy.51uns.com:8022/Frame/Data/jdp.ashx?rnd=1548055466011&fn=GetZhaopinList&StartDate=2000-01-01&SearchKey=&InfoType=-1&CompanyAttr=&CompanyType=&Area=&City=&CompanyProvice=&Post=&Zhuanye=&XLkey=&Age=&start=0&limit=15&DateType=999&InfoState=1&WorkType=0&CompanyKey=")
    #我们为了获取id，将其json格式进行转换成python格式就好,即json解压
    #data = json.loads(Jsondata)
    data = json.loads(page)
    #网站xch中的id集合；是一个列表，每个元素是一个字典，字典中包含多个键值对，此时获取这个列表
    GetInfo = data["rows"]
    IdList = []
    for item in GetInfo:
        IdList.append(item["Id"])

    #return data
    return IdList
#获取招聘信息的详情页的响应数据
def ParseDatailePage(page):
    #url = "http://jy.51uns.com:8022/Frame/Data/jdp.ashx?rnd=1548058860915&fn=GetOneZhaopin&StartDate=2000-01-01&JobId=713985b4e091453b9481269fa9fc593b"
    #解压的出的大字典
    #data = json.loads(OpenPage(url))
    data = json.loads(page)
    #小的数据字典
    Info = data["Data"]
    Id = Info["Id"]
    #公司名称
    Title = Info["CompanyTitle"]
    #工资
    Price = Info["WorkPrice"]
    #岗位
    Position = Info["WorkPositon"]
    #招聘信息
    Content = Info["EmployContent"]
    soup = BeautifulSoup(Content,"html.parser")
    #查询所有的p标签，返回一个list
    Getlist = soup.find_all("p")
    GetData = [item.get_text() for item in Getlist]
    #对content的归整
    Con = "\n".join(GetData)

    return Id,Title,Price,Position,Con
#def Test2():
    #print ParseMainPage()
    #print " 完毕"
    #q,w,e,r,t =  ParseDatailePage()
    #print q,w,e,r,t

#创建一个数据库，一个table
#Id Title Price Position Con text
#create table  a(
#    "Id" text,
#    "company" text ,
#    "price" text,
#    "position",text,
#    "content" text
#
#)ENGINE = InnoDB DEFAULT CHARSET = utf8

def WriteDataToMySQL(data):
    #构造mysql链接
    #主机，用户名，密码，数据库名，
    db = MySQLdb.connect(host = "127.0.0.1",user = "root",passwd = "",db="",charset = "utf8")
    #mysql 构造python可以操作数据库游标
    cursor = db.cursor()
    con = base64.b64encode(data[4]) #把特殊字符强制转换成支持mysql的内容
    sql = "insert into table(%s,%s,%s,%s,%s)"%(data[0],data[1],data[2],data[3],con)

    try:
        #执行sql语句
        cursor.execute(sql)
        #提交
        db.commit()
    except Exception,e:
        db.rollback()  #回滚操作，用于提交失败，保证提交不对数据产生影响
        print e
    db.close()
def WriteToFile(data):
    f = open("project2.txt","a+")
    data = "\n".join(data).encode("utf-8")
    f.write(data)
    f.close()
if __name__ == "__main__":
    #Test1()
    #Test2()
    url = "http://jy.51uns.com:8022/Frame/Data/jdp.ashx?rnd=1548055466011&fn=GetZhaopinList&StartDate=2000-01-01&SearchKey=&InfoType=-1&CompanyAttr=&CompanyType=&Area=&City=&CompanyProvice=&Post=&Zhuanye=&XLkey=&Age=&start=0&limit=15&DateType=999&InfoState=1&WorkType=0&CompanyKey="
    #获取主页响应内容
    HomePage = OpenPage(url)
    #获取主页招聘信息列表
    GetList = ParseMainPage(HomePage)
    for item in GetList:
        #公共前缀构造url
        url = "http://jy.51uns.com:8022/Frame/Data/jdp.ashx?rnd=1548058860915&fn=GetOneZhaopin&StartDate=2000-01-01&JobId="+item
        #访问url的服务器响应
        DetailePage = OpenPage(url)
        #解析数据，得到信息
        data = ParseDatailePage(DetailePage)
        #存入文件
        WriteToFile(data)
        #存到数据库，
        #WriteDataToMySQL(data)
