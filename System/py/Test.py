
#-*- coding=utf-8 -*-
 
import urllib2
import codecs
import re
 
csdn_url = "https://blog.csdn.net/qq_41035588"
blog_url = ["https://blog.csdn.net/qq_41035588/article/details/81953424",
"https://blog.csdn.net/m0_38032942/article/details/81915870","https://blog.csdn.net/qq_41035588/article/details/81839289",
"https://blog.csdn.net/qq_41035588/article/details/81912659","https://blog.csdn.net/qq_41035588/article/details/81833880",
"https://blog.csdn.net/qq_41035588/article/details/80551373",
"https://blog.csdn.net/qq_41035588/article/details/80551296","https://blog.csdn.net/qq_41035588/article/details/81980914",
"https://blog.csdn.net/qq_41035588/article/details/81952836","https://blog.csdn.net/qq_41035588/article/details/81842849",
"https://blog.csdn.net/qq_41035588/article/details/81879472","https://blog.csdn.net/qq_41035588/article/details/81916725",
"https://blog.csdn.net/qq_41035588/article/details/81842994","https://blog.csdn.net/qq_41035588/article/details/81839289",
"https://blog.csdn.net/qq_41035588/article/details/81878321","https://blog.csdn.net/qq_41035588/article/details/81838553",
"https://blog.csdn.net/qq_41035588/article/details/81784981","https://blog.csdn.net/qq_41035588/article/details/80665836",
"https://blog.csdn.net/qq_41035588/article/details/80574928","https://blog.csdn.net/qq_41035588/article/details/80304097",
"https://blog.csdn.net/qq_41035588/article/details/81878646","https://blog.csdn.net/qq_41035588/article/details/81950190",
"https://blog.csdn.net/qq_41035588/article/details/81979313","https://blog.csdn.net/qq_41035588/article/details/81833880",
"https://blog.csdn.net/qq_41035588/article/details/81990472","https://blog.csdn.net/qq_41035588/article/details/81913070",
"https://blog.csdn.net/qq_41035588/article/details/81842481","https://blog.csdn.net/qq_41035588/article/details/81843401",
"https://blog.csdn.net/qq_41035588/article/details/81842018","https://blog.csdn.net/qq_41035588/article/details/81838664",
"https://blog.csdn.net/qq_41035588/article/details/82534344","https://blog.csdn.net/qq_41035588/article/details/82428772",
"https://blog.csdn.net/qq_41035588/article/details/82428362","https://blog.csdn.net/qq_41035588/article/details/82427597",
"https://blog.csdn.net/qq_41035588/article/details/82391839","https://blog.csdn.net/qq_41035588/article/details/82356908",
"https://blog.csdn.net/qq_41035588/article/details/81840326","https://blog.csdn.net/qq_41035588/article/details/81988053",
"https://blog.csdn.net/qq_41035588/article/details/81953011", ]
 
class CSDN(object):
	def __init__(self):
		self.csdn_url = csdn_url
		self.blog_url = blog_url
		self.headers =  {'User-Agent':'Mozilla/5.0 (Windows; U; Windows NT 6.1; en-US; rv:1.9.1.6) Gecko/20091201 Firefox/3.5.6',}  
 
	def openCsdn(self):
		req = urllib2.Request(self.csdn_url, headers = self.headers)
		response = urllib2.urlopen(req)
		thePage = response.read()
		response.close()
		pattern = "访问：<span>(\d+)次</span>"
		number = ''.join(re.findall(pattern, thePage))
		print number
 
	def openBlog(self):
		for i in range(len(self.blog_url)):
			req = urllib2.Request(self.blog_url[i], headers = self.headers)
			response = urllib2.urlopen(req)
			response.close()
 
	
for i in range(500):
	print i
	csdn = CSDN()
	csdn.openCsdn()
	csdn.openBlog()
	csdn.openCsdn()