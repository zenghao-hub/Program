# coding=utf-8
import torch
import numpy as np
import pandas as pd     # 基于 NumPy 的一种数据处理工具
import torch.nn as nn   # nn.Module
import torch.nn.functional as F
import matplotlib.pyplot as plt
from torch.autograd import Variable  # Variable变量import内容
from torch import optim


def make_features(x):
    x = x.unsqueeze(1)
    return torch.cat([x**i for i in range(1,4)],1)  # 0表示行扩充，1表示列扩充
W_target = torch.Tensor([0.5, 3, 2.4]).unsqueeze(1)
b_target = torch.Tensor([0.9])

def f(x):
    return x.mm(W_target) + b_target[0]

def get_batch(batch_size = 32):
    random = torch.randn(batch_size)
    x = make_features(random)
    y = f(x)
    return random, Variable(x),Variable(y)

class poly_model(nn.Module):
    def __init__(self):
        super(poly_model, self).__init__()
        self.poly = nn.Linear(3, 1)

    def forward(self, x):
        out = self.poly(x)
        return out

model=poly_model()
criterion = nn.MSELoss()
optimizer = optim.SGD(model.parameters(), lr=1e-3)

epoch = 0
while True:
    x, batch_x, batch_y = get_batch()
    out = model(batch_x)
    loss = criterion(out, batch_y)
    optimizer.zero_grad()
    loss.backward()
    optimizer.step()
    if(epoch+1)%100==0:
        print('Epoch[{}/{}],loss:{:.6f}'.format(epoch+1,num_epochs,loss.data[0]))
    if(loss.data[0]<1e-3):
        break


#关联数组排序
def combine_sort_np(x, y):
    Z = zip(x,y)
    Z = sorted(Z,reverse=False)
    sorted_x, sorted_y = zip(*Z)
    return sorted_x, sorted_y
# Test
model.eval()

x, batch_x, batch_y = get_batch()
predict = model(Variable(batch_x))
predict = predict.data.numpy()
sorted_x, sorted_y = combine_sort_np(batch_x[:,0].numpy(), batch_y.numpy())
# plt.plot(batch_x.numpy(),batch_y.numpy(),label='Original data')
plt.figure()
plt.plot(sorted_x,sorted_y,label='Original data')
plt.scatter(batch_x[:,0].numpy(),predict,label='Fitting Line')
plt.show()

