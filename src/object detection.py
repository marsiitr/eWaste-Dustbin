#!/usr/bin/env python
# coding: utf-8

# In[1]:


get_ipython().system('pip install torch==1.8.1+cu111 torchvision==0.9.1+cu111 torchaudio===0.8.1 -f https://download.pytorch.org/whl/lts/1.8/torch_lts.html')


# In[2]:


get_ipython().system('git clone https://github.com/ultralytics/yolov5')
    


# In[4]:


get_ipython().system('cd yolov5 & pip install -r requirements.txt')


# In[5]:


import torch
from matplotlib import pyplot as plt
import numpy as np
import cv2


# In[6]:



model = torch.hub.load('ultralytics/yolov5', 'yolov5s')


# In[7]:


model


# In[4]:


import uuid   # Unique identifier
import os
import time


# In[5]:


IMAGES_PATH = os.path.join('data', 'images') #/data/images
labels = ['phone', 'watch']
number_imgs = 23


# In[8]:


for label in labels:
    print('Collecting images for {}'.format(label))
    for img_num in range(number_imgs):
        print('Collecting images for {}, image number {}'.format(label, img_num))
        imgname = os.path.join(IMAGES_PATH, label+'.'+str(uuid.uuid1())+'.jpg')
        print(imgname)   


# In[6]:


get_ipython().system('git clone https://github.com/tzutalin/labelImg')


# In[7]:


get_ipython().system('pip install pyqt5 lxml --upgrade')
get_ipython().system('cd labelImg && pyrcc5 -o libs/resources.py resources.qrc')


# In[3]:


import os
from random import choice
import shutil

#arrays to store file names
imgs =[]
xmls =[]

#setup dir names
trainPath = r"C:\Users\latas\ewb2.0\dataset\images\train"
valPath = r"C:\Users\latas\ewb2.0\dataset\images\val"
crsPath = r"C:\Users\latas\images" #dir where images and annotations stored

#setup ratio (val ratio = rest of the files in origin dir after splitting into train and test)
train_ratio = 0.8
val_ratio = 0.2


#total count of imgs
totalImgCount = len(os.listdir(crsPath))/2

#soring files to corresponding arrays
for (dirname, dirs, files) in os.walk(crsPath):
    for filename in files:
        if filename.endswith('.txt'):
            xmls.append(filename)
        else:
            imgs.append(filename)


#counting range for cycles
countForTrain = int(len(imgs)*train_ratio)
countForVal = int(len(imgs)*val_ratio)
print("training images are : ",countForTrain)
print("Validation images are : ",countForVal)


# In[4]:


trainimagePath =  r"C:\Users\latas\ewb2.0\dataset\images\train"
trainlabelPath =  r"C:\Users\latas\ewb2.0\dataset\label\train"
valimagePath = r"C:\Users\latas\ewb2.0\dataset\images\val"
vallabelPath =  r"C:\Users\latas\ewb2.0\dataset\label\val"
#cycle for train dir
for x in range(countForTrain):

    fileJpg = choice(imgs) # get name of random image from origin dir
    fileXml = fileJpg[:-4] +'.txt' # get name of corresponding annotation file

    #move both files into train dir
    #shutil.move(os.path.join(crsPath, fileJpg), os.path.join(trainimagePath, fileJpg))
    #shutil.move(os.path.join(crsPath, fileXml), os.path.join(trainlabelPath, fileXml))
    shutil.copy(os.path.join(crsPath, fileJpg), os.path.join(trainimagePath, fileJpg))
    shutil.copy(os.path.join(crsPath, fileXml), os.path.join(trainlabelPath, fileXml))


    #remove files from arrays
    imgs.remove(fileJpg)
    xmls.remove(fileXml)



#cycle for test dir   
for x in range(countForVal):

    fileJpg = choice(imgs) # get name of random image from origin dir
    fileXml = fileJpg[:-4] +'.txt' # get name of corresponding annotation file

    #move both files into train dir
    #shutil.move(os.path.join(crsPath, fileJpg), os.path.join(valimagePath, fileJpg))
    #shutil.move(os.path.join(crsPath, fileXml), os.path.join(vallabelPath, fileXml))
    shutil.copy(os.path.join(crsPath, fileJpg), os.path.join(valimagePath, fileJpg))
    shutil.copy(os.path.join(crsPath, fileXml), os.path.join(vallabelPath, fileXml))
    
    #remove files from arrays
    imgs.remove(fileJpg)
    xmls.remove(fileXml)

#rest of files will be validation files, so rename origin dir to val dir
#os.rename(crsPath, valPath)
shutil.move(crsPath, valPath) 


# In[5]:


get_ipython().system('python train.py --img 415 --batch 16 --epochs 30 --data dataset.yaml --weights yolov5s.pt --cache')


# In[1]:


cd yolov5


# In[1]:


get_ipython().system('python train.py --img 12 --batch 16 --epochs 30 --data dataset.yml --weights yolov5s.pt --cache')


# In[2]:


cd yolov5


# In[3]:


get_ipython().system('python train.py --img 45 --batch 2 --epochs 50 --data dataset.yml --weights yolov5s.pt --workers 16')


# In[12]:



get_ipython().system('python -m pip install pefile')


# In[13]:


get_ipython().system('python fixNvPe.py --input=C:\\Users\\latas\\AppData\\Local\\Programs\\Python\\Python38\\lib\\site-packages\\torch\\lib\\*.dll')


# In[14]:


get_ipython().system('python train.py --img 415 --batch 2 --epochs 30 --data dataset.yml --weights yolov5s.pt --cache')


# In[15]:


get_ipython().system('python fixNvPe.py --input= C:\\Users\\latas\\anaconda3\\Lib\\site-packages\\torch\\lib\\*.dll')


# In[ ]:




