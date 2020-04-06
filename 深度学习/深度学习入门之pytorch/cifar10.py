# coding=utf-8
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
from datetime import datetime

train_transform = transforms.Compose([
    transforms.Resize(40),       # 缩放
    transforms.RandomHorizontalFlip(),
    transforms.RandomCrop(32),
    transforms.ToTensor(),
    transforms.Normalize([0.5, 0.5, 0.5], [0.5, 0.5, 0.5])  # RGB三维通道的均值0.5，方差也为0.5
    ]
)

test_transform = transforms.Compose([
    transforms.ToTensor(),
    transforms.Normalize([0.5, 0.5, 0.5], [0.5, 0.5, 0.5])  # RGB三维通道的均值0.5，方差也为0.5
    ]
)


def conv3x3(in_channels, out_channels, stride=1):
    return nn.Conv2d(in_channels, out_channels, kernel_size=3, stride=stride, padding=1, bias=False)


# 定义残差模块
class residual_block(nn.Module):
    def __init__(self, in_channel, out_channel, same_shape=True):
        super(residual_block, self).__init__()
        self.same_shape = same_shape
        stride = 1 if self.same_shape else 2

        self.conv1 = conv3x3(in_channel, out_channel, stride=stride)
        self.bn1 = nn.BatchNorm2d(out_channel)

        self.conv2 = conv3x3(out_channel, out_channel)
        self.bn2 = nn.BatchNorm2d(out_channel)
        if not self.same_shape:
            self.conv3 = nn.Conv2d(in_channel, out_channel, 1, stride=stride)

    def forward(self, x):
        out = self.conv1(x)
        out = F.relu(self.bn1(out), True)
        out = self.conv2(out)
        out = F.relu(self.bn2(out), True)

        if not self.same_shape:
            x = self.conv3(x)
        return F.relu(x + out, True)


class resnet(nn.Module):
    def __init__(self, in_channel, num_classes, verbose=False):
        super(resnet, self).__init__()
        self.verbose = verbose
        self.block1 = nn.Conv2d(in_channel, 64, 7, 2)
        self.block2 = nn.Sequential(
            nn.MaxPool2d(3, 2), residual_block(64, 64), residual_block(64, 64))

        self.block3 = nn.Sequential(
            residual_block(64, 128, False), residual_block(128, 128))

        self.block4 = nn.Sequential(
            residual_block(128, 256, False), residual_block(256, 256))

        self.block5 = nn.Sequential(
            residual_block(256, 512, False),
            residual_block(512, 512), nn.AvgPool2d(3))

        self.classifier = nn.Linear(512, num_classes)

    def forward(self, x):
        x = self.block1(x)
        if self.verbose:
            print('block 1 output: {}'.format(x.shape))
        x = self.block2(x)
        if self.verbose:
            print('block 2 output: {}'.format(x.shape))
        x = self.block3(x)
        if self.verbose:
            print('block 3 output: {}'.format(x.shape))
        x = self.block4(x)
        if self.verbose:
            print('block 4 output: {}'.format(x.shape))
        x = self.block5(x)
        if self.verbose:
            print('block 5 output: {}'.format(x.shape))
        x = x.view(x.shape[0], -1)
        x = self.classifier(x)
        return x


trainset = datasets.CIFAR10(root='./data_cifar10', train=True, download=True, transform=train_transform)
trainloader = torch.utils.data.DataLoader(trainset, batch_size=4, shuffle=True, num_workers=0)
testset = datasets.CIFAR10(root='./data_cifar10', train=False, download=True, transform=test_transform)
testloader = torch.utils.data.DataLoader(testset, batch_size=4, shuffle=False, num_workers=0)
classes = ('plane', 'car', 'bird', 'cat', 'deer', 'dog', 'frog', 'horse', 'ship', 'truck')


def get_acc(output, label):
    total = output.shape[0]
    _, pred_label = output.max(1)
    num_correct = (pred_label == label).sum().data[0]
    return num_correct / total


num_epochs = 20
prev_time = datetime.now()
model = resnet(3, 10)           # 输入维度3，输出10
criterion = nn.CrossEntropyLoss()
optimizer = optim.SGD(model.parameters(), lr=1e-2)
for epoch in range(num_epochs):
    train_loss = 0
    train_acc = 0
    model.train()
    for im, label in trainloader:           # 读取数据存在问题
        im = Variable(im)
        label = Variable(label)
        # forward
        output = model(im)
        loss = criterion(output, label)
        # backward
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

        train_loss += loss.data[0]
        train_acc += get_acc(output, label)

    cur_time = datetime.now()
    h, remainder = divmod((cur_time - prev_time).seconds, 3600)
    m, s = divmod(remainder, 60)
    time_str = "Time %02d:%02d:%02d" % (h, m, s)
    if testloader is not None:
        test_loss = 0
        test_acc = 0
        model.eval()
        for im, label in testloader:
            im = Variable(im, volatile=True)
            label = Variable(label, volatile=True)
            output = model(im)
            loss = criterion(output, label)
            test_loss += loss.data[0]
            test_acc += get_acc(output, label)
        epoch_str = (
            "Epoch %d. Train Loss: %f, Train Acc: %f, Valid Loss: %f, Valid Acc: %f, "
            % (epoch, train_loss / len(trainloader),
               train_acc / len(trainloader), test_loss / len(testloader),
               test_acc / len(testloader)))
    else:
        epoch_str = ("Epoch %d. Train Loss: %f, Train Acc: %f, " %
                     (epoch, train_loss / len(trainloader),
                      train_acc / len(trainloader)))
    prev_time = cur_time
    print(epoch_str + time_str)
