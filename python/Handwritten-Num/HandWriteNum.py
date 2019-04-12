# -*- coding: utf-8 -*-
<<<<<<< HEAD

'''

Title: 手写数字识别
Date ：2019.4.8
Autor：YS （1640701****）
School：XUST 
个人博客与GitHub名称：Mr-Hunter 
=======
'''

Title: 手写数字识别
Date ：2019.4.8
Autor：YS （1640701****） 
个人博客与GitHub名称：Mr-Hunter 
项目源码：https://github.com/Mr-Hunter/Linux/tree/master/python/Handwritten-Num
>>>>>>> ec0cd06325010017cfe49d3c702afed2cc34f47d
''' 

import os
from skimage import io
import numpy as np

N = 2500

#读取训练图片
def readPicture(files):
    Picture = np.zeros([len(files), N+1])
    for i, item in enumerate(files):
        img = io.imread('./num/'+item, as_grey = True).reshape(N)
        Picture[i, 0:N] = img
        Picture[i, N] = float(item[0])
    return Picture

#读取识别图像
def readTestPicture(files):
    Picture = np.zeros([len(files), N])
    for i, item in enumerate(files):
        img = io.imread(item, as_grey = True).reshape(N)
        Picture[i, 0:N] = img
    return Picture

#计算测试向量与其他向量之间的距离
def calDis(pic, testPic):
    dis = np.zeros([2, len(pic)])
    for i, item in enumerate(pic):
        Item = item[0:N]
        dis[0, i] = np.sqrt(abs(np.sum(Item**2-testPic**2)))
        dis[1, i] = item[N]
    return dis

#对测试向量进行分类
def chooseClass(dis):
    disMin = np.sort(dis[0,:])
    DisPoint = []
    for item in disMin[0:1]:
        point = list(dis[0,:]).index(item)
        DisPoint.append(dis[1, point])
    return DisPoint

filenames = os.listdir(r"./num/")
pic = readPicture(filenames)
testPic = readTestPicture(['test.png'])
distance = calDis(pic, testPic)
picClass = chooseClass(distance)
print('The number may is', picClass)
