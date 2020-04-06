# coding=utf-8
import torch
import numpy as np
import pandas as pd     # 基于 NumPy 的一种数据处理工具
import torch.nn as nn   # nn.Module
import torch.nn.functional as F
import matplotlib.pyplot as plt
from torch.autograd import Variable  # Variable变量import内容
from torch import optim

with open('data3.txt', 'r') as f:
    data_list = f.readlines()
    data_list = [i.split('\n')[0] for i in data_list]
    data_list = [i.split(',') for i in data_list]
    data = [(float(i[0]),float(i[1]),float(i[2])) for i in data_list]
    y_data = [(float(i[2])) for i in data_list]


x0 = list(filter(lambda x:x[-1]==0.0, data))
x1 = list(filter(lambda x:x[-1]==1.0, data))

class LogisticRegression(nn.Module):
    def __init__(self):
        super(LogisticRegression,self).__init__()
        self.linear = nn.Linear(2, 1)
        self.sigmod = nn.Sigmoid()

    def forward(self, x):
        x = self.linear(x)
        out = self.sigmod(x)
        return out

# list 转 numpy
# np.array(a)
# ndarray 转 list
# a.tolist()
np_data = np.array(data, dtype='float32')
x_data = torch.from_numpy(np_data[:,0:2])
y_data = torch.from_numpy(np_data[:,-1]).unsqueeze(1)
logistic_model=LogisticRegression()
criterion = nn.BCELoss()
optimizer = optim.SGD(logistic_model.parameters(), lr=1e-3, momentum=0.9)
num_epoch = 200000
for epoch in range(num_epoch):
    x = Variable(x_data)
    y = Variable(y_data)
    out = logistic_model(x)
    loss = criterion(out, y)
    mask = out.ge(0.5).float()  # 大于0.5等于1，小于0.5等于0
    correct = (mask==y).sum().float()
    acc = correct/x.size(0)

    optimizer.zero_grad()
    loss.backward()
    optimizer.step()
    if (epoch + 1) % 1000 == 0:
        print('Epoch[{}/{}],loss:{:.6f},acc:{}'.format(epoch + 1, num_epoch, loss.item(),acc))

w0, w1 = logistic_model.linear.weight.data.numpy()[0]
w0 = w0.item()
w1 = w1.item()
b = logistic_model.linear.bias.data.numpy()[0]
plot_x = np.arange(30, 100, 0.1)
plot_y = (-w0*plot_x-b)/w1   # 基于logistic回归方程中w1*x + w2*y + b = 0
plot_x0_0 = [i[0] for i in x0]
plot_x0_1 = [i[1] for i in x0]
plot_x1_0 = [i[0] for i in x1]
plot_x1_1 = [i[1] for i in x1]
plt.plot(plot_x0_0, plot_x0_1, 'ro',label = 'x_0')
plt.plot(plot_x1_0, plot_x1_1, 'bo',label = 'x_1')
plt.plot(plot_x,plot_y)
plt.show()