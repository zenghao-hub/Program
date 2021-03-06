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


class Batch_Net(nn.Module):
    def __init__(self, in_dim, n_hidden_1, n_hidden_2, out_dim):
        super(Batch_Net, self).__init__()
        self.layer1 = nn.Sequential(nn.Linear(in_dim, n_hidden_1),
                                    nn.BatchNorm1d(n_hidden_1),
                                    nn.ReLU(True))
        self.layer2 = nn.Sequential(nn.Linear(n_hidden_1, n_hidden_2),
                                    nn.BatchNorm1d(n_hidden_2),
                                    nn.ReLU(True))
        self.layer3 = nn.Sequential(nn.Linear(n_hidden_2, out_dim))

    def forward(self, x):
        x = self.layer1(x)
        x = self.layer2(x)
        out = self.layer3(x)
        return out


class Simple_Net(nn.Module):
    def __init__(self, in_dim, n_hidden_1, n_hidden_2, out_dim):
        super(Simple_Net, self).__init__()
        self.layer1 = nn.Linear(in_dim, n_hidden_1)
        self.layer2 = nn.Linear(n_hidden_1, n_hidden_2)
        self.layer3 = nn.Sequential(nn.Linear(n_hidden_2, out_dim))

    def forward(self, x):
        x = self.layer1(x)
        x = self.layer2(x)
        out = self.layer3(x)
        return out


class Activation_Net(nn.Module):
    def __init__(self, in_dim, n_hidden_1, n_hidden_2, out_dim):
        super(Activation_Net, self).__init__()
        self.layer1 = nn.Sequential(nn.Linear(in_dim, n_hidden_1),
                                    nn.ReLU(True))
        self.layer2 = nn.Sequential(nn.Linear(n_hidden_1, n_hidden_2),
                                    nn.ReLU(True))
        self.layer3 = nn.Sequential(nn.Linear(n_hidden_2, out_dim))

    def forward(self, x):
        x = self.layer1(x)
        x = self.layer2(x)
        out = self.layer3(x)
        return out


batch_size = 64
learning_rate = 1e-2
num_epoches = 20

# 将totensor与标准化两个预处理组合，toTensor自动标准化，范围0~1，Normalize参数是均值与方法，对于3通道使用[0.5,0.5,0.5],[0.5,0.5,0.5]
data_tf = transforms.Compose([transforms.ToTensor(), transforms.Normalize([0.5], [0.5])])
train_dataset = datasets.MNIST(root='./data', train=True, transform=data_tf, download=False)
test_dataset = datasets.MNIST(root='./data', train=False, transform=data_tf)
train_loader = DataLoader(train_dataset, batch_size=batch_size, shuffle=True)  # shuffle数据是否打乱
test_loader = DataLoader(test_dataset, batch_size=batch_size, shuffle=False)

model = Batch_Net(28*28, 300, 100, 10)     # 在此修改网络
criterion = nn.CrossEntropyLoss()
optimizer = optim.SGD(model.parameters(), lr=learning_rate)

for epoch in range(20):
    model.train()
    train_loss = 0
    train_acc = 0
    losses = []
    acces = []
    train_loadercnt = 0
    for im, label in train_loader:  # 938*64幅28*28图片训练数据
        im = im.view(-1, 28*28)
        im = Variable(im)
        label = Variable(label)
        out = model(im)
        loss = criterion(out, label)

        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

        train_loss += loss.item()   # 20个训练的loss累加
        _, pred = out.max(1)        # 选择10中的最大值，得出预测值数字
        num_correct = (pred == label).sum().item()      # 计数
        acc = num_correct/im.shape[0]                   # 计算准确率
        train_acc += acc
        train_loadercnt = train_loadercnt + 1
    losses.append(train_loss/len(train_loader))
    acces.append(train_acc/len(train_loader))

    eval_loss = 0
    eval_acc = 0
    model.eval()
    eval_losses = []
    eval_acces = []
    for im, label in test_loader:
        im = im.view(-1, 28 * 28)
        im = Variable(im)
        label = Variable(label)
        out = model(im)
        loss = criterion(out, label)

        eval_loss += loss.item()
        _, pred = out.max(1)
        num_correct = (pred == label).sum().item()
        acc = num_correct / im.shape[0]
        eval_acc += acc
    eval_losses.append(eval_loss / len(test_loader))
    eval_acces.append(eval_acc / len(test_loader))
    print('epoch: {}, Train Loss: {:.6f}, Train Acc: {:.6f}, Eval Loss: {:.6f}, Eval Acc: {:.6f}'.format(epoch,
                train_loss / len(train_loader), train_acc / len(train_loader),
                eval_loss / len(test_loader), eval_acc / len(test_loader)))
