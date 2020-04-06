# coding=utf-8
import os
import shutil
import torch
import numpy as np
import pandas as pd     # 基于 NumPy 的一种数据处理工具
import torch.nn as nn   # nn.Module
import torch.nn.functional as F
import matplotlib.pyplot as plt
from torch.autograd import Variable  # Variable变量import内容
from torch import optim
from torch.utils.data import DataLoader
from torchvision import datasets, transforms


# cat_file = os.listdir('E:/learn/pytorch学习/kaggle/PetImages/Cat')
dog_file = os.listdir('E:/learn/pytorch学习/kaggle/PetImages/Dog')
train_cat_filepath = 'E:/learn/pytorch学习/kaggle/cat/train'
test_cat_filepath = 'E:/learn/pytorch学习/kaggle/cat/test'
train_dog_filepath = 'E:/learn/pytorch学习/kaggle/dog/train'
test_dog_filepath = 'E:/learn/pytorch学习/kaggle/dog/test'

num_train = int(len(dog_file)*0.9)
num_test = int(len(dog_file)*0.1)
# for i in range(1, num_train):
#     pic_path = 'E:/learn/pytorch学习/kaggle/PetImages/Cat/' + str(i) + '.jpg'
#     train_path = train_cat_filepath + '/' + str(i) + '.jpg'
#     shutil.move(pic_path, train_path)
for i in range(num_train):
    pic_path = 'E:/learn/pytorch学习/kaggle/PetImages/Dog/' + str(i) + '.jpg'
    train_path = train_dog_filepath + '/' + str(i) + '.jpg'
    shutil.move(pic_path, train_path)
    if i % 1000 == 0:
        print(i/num_train)
