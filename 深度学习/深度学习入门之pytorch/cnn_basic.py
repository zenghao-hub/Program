# coding=utf-8
import torch
import numpy as np
import pandas as pd     # 基于 NumPy 的一种数据处理工具
import torch.nn as nn   # nn.Module
import torch.nn.functional as F
import matplotlib.pyplot as plt
from torch.autograd import Variable  # Variable变量import内容
from torch import optim


class SimpleCNN(nn.Module):
    def __init__(self):
        super(SimpleCNN, self).__init__()       # input 3*32*32
        layer1 = nn.Sequential()
        layer1.add_module('conv1', nn.Conv2d(3, 32, 3, 1, padding=1))       # (32-3+2*1)/1+1=32 32*32*32
        layer1.add_module('relu1', nn.ReLU(True))
        layer1.add_module('pool1', nn.MaxPool2d(2, 2))                      # (32-2)/2+1=16 32*16*16
        self.layer1 = layer1

        layer2 = nn.Sequential()
        layer2.add_module('conv2', nn.Conv2d(32, 64, 3, 1, padding=1))  # 64*16*16
        layer2.add_module('relu2', nn.ReLU(True))
        layer2.add_module('pool2', nn.MaxPool2d(2, 2))  # 64*8*8
        self.layer2 = layer2

        layer3 = nn.Sequential()
        layer3.add_module('conv3', nn.Conv2d(64, 128, 3, 1, padding=1))  # 128*8*8
        layer3.add_module('relu3', nn.ReLU(True))
        layer3.add_module('pool3', nn.MaxPool2d(2, 2))  # 128*4*4
        self.layer3 = layer3

        layer4 = nn.Sequential()
        layer4.add_module('fc1', nn.Linear(2048, 512))
        layer4.add_module('fc_relu1', nn.ReLU(True))
        layer4.add_module('fc2', nn.Linear(512, 64))
        layer4.add_module('fc_relu2', nn.ReLU(True))
        layer4.add_module('fc3', nn.Linear(64, 10))
        self.layer4 = layer4

    def forward(self, x):
        conv1 = self.layer1(x)
        conv2 = self.layer2(conv1)
        conv3 = self.layer3(conv2)
        fc_input = conv3.view(conv3.size(0), -1)
        fc_out = self.layer4(fc_input)
        return fc_out

class LeNet(nn.Module):
    def __init__(self):
        super(LeNet, self).__init__()      # 32*32
        layer1 = nn.Sequential()
        layer1.add_module('conv1', nn.Conv2d(1, 6, 3, padding=1))       # 6*28*28  ?????
        layer1.add_module('pool1', nn.MaxPool2d(2, 2))                  # 6*14*14
        self.layer1 = layer1

        layer2 = nn.Sequential()
        layer2.add_module('conv2', nn.Conv2d(6, 16, 5))                 # 16*10*10
        layer2.add_module('pool2', nn.MaxPool2d(2, 2))                  # 16*5*5
        self.layer2 = layer2

        layer3 = nn.Sequential()
        layer3.add_module('fc1', nn.Linear(400, 120))
        layer3.add_module('fc2', nn.Linear(512, 84))
        layer3.add_module('fc3', nn.Linear(84, 10))
        self.layer3 = layer3

    def forward(self, x):
        x = self.layer1(x)
        x = self.layer2(x)
        x = x.view(x.size(0), -1)
        fc_out = self.layer3(x)
        return fc_out


class AlexNet(nn.Module):
    def __init__(self):
        super(AlexNet, self).__init__()      # 3*224*224
        self.features = nn.Sequential(
            nn.Conv2d(3, 64, kernel_size=11, stride=4, padding=2),
            nn.ReLU(True),
            nn.MaxPool2d(kernel_size=2, stride=2),
            nn.Conv2d(64, 192, kernel_size=5, padding=2),
            nn.ReLU(True),
            nn.MaxPool2d(kernel_size=3, stride=2),
            nn.Conv2d(192, 384, kernel_size=3, padding=1),
            nn.ReLU(True),
            nn.Conv2d(384, 256, kernel_size=3, padding=1),
            nn.ReLU(True),
            nn.Conv2d(256, 256, kernel_size=3, padding=1),
            nn.ReLU(True),
            nn.MaxPool2d(kernel_size=3, stride=2),
        )
        self.classifier = nn.Sequential(
            nn.Dropout(),
            nn.Linear(256*6*6, 4096),
            nn.ReLU(True),
            nn.Dropout(),
            nn.Linear(4096, 4096),
            nn.ReLU(True),
            nn.Linear(4096, num_classes),
        )
    def forward(self, x):
        x = self.features(x)
        x = x.view(x.size(0), 256*6*6)
        fc_out = self.classifier(x)
        return fc_out

# VGGNet 使用更小滤波器，更深结构
# GoogleNet 更深的网络结构共22层，参数却比AlexNet少了12倍，有效的Inception模块
# ResNet 创新在与引入残差


model = SimpleCNN()
# print(model)        # 打印模型
# new_model = nn.Sequential(*list(model.children())[:2])      # 提取前两层模型
# print(new_model)

# 模型参数提取 model.named_parameters()  model.parameters()
for para in model.named_parameters():
    print(para[0])

# 权重初始化
# for m in model.modules():
#     if isinstance(m, nn.Conv2d):
#         init.normal(m.weight.data)
#         init.xavier_normal(m.weight.data)
#         init.kaiming_normal(m.weight.data)
#         m.bias.data.fill_(0)
#     else: isinstance(m, nn.Linear)
#         m.weight.data.normal_()