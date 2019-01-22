#!/usr/bin/python
#coding:utf-8

'''
Flask框架搭建web网站
'''
#pip install flask
from flask import Flask
#引入flask框架为我们提供的调用模板函数，建立规定的templates目录：flask规定模板存放目录,就可以直接调用.html
from flask import render_template,request
#flask规定的static目录，存放静态资源
#资源可以随时被静态（提供目录即可）获取

#用flask方法建立app对象，一般默认为吧文本文件设置成app对象
app= Flask(__name__)
#因为有中文，需要进行转换
import sys
reload(sys)
sys.setdefaultencoding("utf8")


#web网站初尝试值hello world
#route路由  将指定的url与函数进行一对一映射，访问指定url时，就会被路由转发到指定函数进行响应
@app.route("/hello/")
def Hello():
    #return "<h1>Hello World</h1>"
    #return render_template("index.html") #参数可变
    data = [
            ("111","cdcd","班主任")
            ("122","cdcd","班主任")
            ("144","cdcd","班主任")
            ]
    return render_template("main.html",job = data)
#route一个标识作用
@app.route("/main/")
def Mian():
    return "main  page"
'''
GET方法通过URL后面追加的键值对 key-value
request.args.get(key)
POST方法通过from表单提交数据
request.from.get(name) name是标签的属性
'''


#登陆,默认get
@app.route("/log/",methods = ["POST","GET"])
def Log():
    if request.method == "POST":
        GetName = request.from.get("username")
        GetPsw = request.from.get("userpsw")
        return GetName+GetPsw
    return render_template("log.html")
if __name__ == "main":
    app.run(host = "0.0.0.0",port = 30000)  #0.0.0.0允许公网所有用户访问


