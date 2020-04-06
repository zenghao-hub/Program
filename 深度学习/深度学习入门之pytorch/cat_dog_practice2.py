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
from torchvision import datasets, transforms, models

import warnings
warnings.filterwarnings('ignore')  # 忽略图片信息错误警告


# 设置超参数
batch_size = 100
epochs = 20

# 数据预处理
transform = transforms.Compose(
    [
        transforms.CenterCrop(224),  # 裁剪固定大小  vgg深层网络要求
        transforms.ToTensor(),
        transforms.Normalize([0.5, 0.5, 0.5], [0.5, 0.5, 0.5])
    ]
)
# 读取数据
dataset_train = datasets.ImageFolder('../kaggle/train', transform)
dataset_test = datasets.ImageFolder('../kaggle/test', transform)

# 导入数据 猫狗各2000训练，500测试集
train_loader = DataLoader(dataset_train, batch_size=batch_size, shuffle=True)
test_loader = DataLoader(dataset_test, batch_size=batch_size, shuffle=True)


# 定义网络
class ConvNet(nn.Module):
    def __init__(self):
        super(ConvNet, self).__init__()
        self.layer1 = nn.Sequential(
            nn.Conv2d(3, 16, kernel_size=3, stride=1, padding=1),
            nn.BatchNorm2d(16),
            nn.ReLU(True),
            nn.MaxPool2d(2, 2),  # stride默认值是kernel size
        )
        self.layer2 = nn.Sequential(
            nn.Conv2d(16, 32, kernel_size=3, stride=1, padding=1),
            nn.BatchNorm2d(32),
            nn.ReLU(True),
            nn.MaxPool2d(2, 2),
        )
        self.layer3 = nn.Sequential(
            nn.Conv2d(32, 64, kernel_size=3, stride=1, padding=1),
            nn.BatchNorm2d(64),
            nn.ReLU(True),
            nn.MaxPool2d(2, 2),
        )
        self.layer4 = nn.Sequential(
            nn.Conv2d(64, 128, kernel_size=3, stride=1, padding=1),
            nn.BatchNorm2d(128),
            nn.ReLU(True),
            nn.AvgPool2d(2, 2),
        )
        self.layer5 = nn.Sequential(
            nn.Linear(6272, 512),
            nn.Linear(512, 1),
            nn.Sigmoid(),
        )

    def forward(self, x):
        x = self.layer1(x)
        x = self.layer2(x)
        x = self.layer3(x)
        x = self.layer4(x)
        x = x.view(batch_size, -1)
        x = self.layer5(x)
        return x


# model = ConvNet()
model = models.vgg16(pretrained=True)
for parma in model.parameters():
    parma.requires_grad = False

model.classifier = nn.Sequential(
    nn.Linear(25088, 4096),
    nn.ReLU(),
    nn.Linear(4096, 4096),
    nn.ReLU(),
    nn.Dropout(0.5),
    nn.Linear(4096, 1),
    nn.Sigmoid(),
)
print(model)
criterion = nn.CrossEntropyLoss()
optimizer = optim.Adam(model.classifier.parameters(), lr=1e-4)  # 只更新全连接层参数


# 训练
def train():
    model.train()
    for batch_idx, [data, label] in enumerate(train_loader):
        data = Variable(data)
        label = label.unsqueeze(1)
        label = Variable(label)
        label = label.float()
        out = model(data)
        # loss = criterion(out, label)    # 报错
        loss = F.binary_cross_entropy(out, label)
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()
        if (batch_idx + 1) % 10 == 0:
            print('cat_train {}%'.format(100*(batch_idx+1)/len(train_loader)))  # train_loader的长度是文件数除以batch_size


# 测试
def test():
    eval_loss = 0
    eval_acc = 0
    model.eval()
    correct = 0
    for batch_idx, [data, label] in enumerate(test_loader):
        data = Variable(data)
        label = label.unsqueeze(1)
        label = Variable(label)
        label = label.float()
        out = model(data)
        # loss = criterion(out, label)
        loss = F.binary_cross_entropy(out, label)  # 数据类型应一致
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

        eval_loss += loss.item()
        pred = torch.Tensor([[1] if num[0] >= 0.5 else [0] for num in out])
        pred = pred.long()
        correct += pred.eq(label.long()).sum().item()
    print('cat_test_loss{}, acc{}%'.format(eval_loss, correct/len(test_loader)))   # len长度为10 1000总数据 百分号表示


for epoch in range(1, epochs+1):
    train()
    test()
    print('训练次数为{}'.format(epoch))
