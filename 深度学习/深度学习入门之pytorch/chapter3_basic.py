# coding=utf-8
import torch
import numpy as np
import pandas as pd     # 基于 NumPy 的一种数据处理工具
import torch.nn as nn   # nn.Module
import torch.nn.functional as F
import matplotlib.pyplot as plt
from torch.autograd import Variable  # Variable变量import内容
from torch import optim
'''
3.1 pytorch基础
'''
# torch
'''
num = 50
# Tensor
y = torch.randn(num)
y = y.numpy()  # torch与numpy的转换
maxinum = max(y)
y = y/maxinum
x = np.arange(0, num, 1)

touch_x = torch.from_numpy(x)  # numpy与torch的转换
touch_y = torch.from_numpy(y)
pic = plt.figure()
plt.plot(x, y)
plt.show()
print(y)
'''

# Variable
# 向量或者矩阵的求导，表示分别对其中每一个元素求偏导
'''
x = Variable(torch.Tensor([1]), True)
a = Variable(torch.Tensor([100]), True)
b = Variable(torch.Tensor([1]), True)
y = a * x + b
y.backward()    # 自动求导
print(x.grad)   # 表示y相对于x的偏导
print(b.grad)   # 表示y相对于b的偏导

x = Variable(torch.Tensor([[2, 3], [1, 2]]), requires_grad=True)
a = Variable(torch.Tensor([[10, 13], [11, 12]]), requires_grad=True)
b = Variable(torch.Tensor([[20, 23], [21, 22]]), requires_grad=True)

y = a * x + b
y.backward(torch.Tensor([[1, 0.1], [1, 1]]))    # 自动求导 偏导的倍数
print(x.grad)   # 表示y相对于x的偏导
print(b.grad)   # 表示y相对于b的偏导
'''

# 数据集
'''
class myDataset(Dataset):
    def __init__(self, csv_file, txt_file, root_dir, other_file):
        self.csvdata = pd.read_csv(csv_file)
        with open(txt_file, 'r') as f:
            data_list = f.readlines()
        self.txt_data = data_list
        self.root_dir = root_dir

    def __len__(self):
        return len(self.csv_data)

    def __getitem__(self, idx):
        data = (self.csv_data[idx], self.txt_data[idx])
        return data
'''

# nn.Module 神经网络
# 所有的模型构建都是从基类nn.Module继承的
'''
class net_name(nn.Module):
    def __init__(self, other_arguments):
        super(net_name, self).__init__() # 调用父类初始化函数的方法
        self.conv1 = nn.Conv2d(in_channels, out_channels, kernel_size)
        # 别的网络层
    
    def forward(self,x):
        x = self.conv1(x)
        return x
'''

# torch.optim(优化)
# optimizer = torch.optim.SGD(model.params(),lr=0.01,momentum=0.9) # 设置学习率与动量

# 模型的保存与加载
'''
1. 保存结构与参数 torch.save(model, path)
2. 保存参数 torch.save(model.state_dict, path)

1. 加载结构与参数 load_model = torch.load(path)
2. 加载参数 model.load_state_dic(torch.load(path))
'''

# 一维线性回归
'''
x_train = np.array([[3.3],[4.4],[5.5],[6.71],[6.93],[4.168],[9.779],[6.182],[7.59],[2.167],[7.042],[10.791],[5.313],[7.997],[3.1]],dtype=np.float32)
y_train = np.array([[1.7],[2.76],[2.09],[3.19],[1.694],[1.573],[3.366],[2.596],[2.53],[1.221],[2.827],[3.465],[1.65],[2.904],[1.3]],dtype=np.float32)
# plt.figure()
# plt.scatter(x_train,y_train)
# plt.show()
x_train = torch.from_numpy(x_train)
y_train = torch.from_numpy(y_train)

class LinearRegression(nn.Module):
    def __init__(self):
        super(LinearRegression,self).__init__()
        self.linear = nn.Linear(1, 1)

    def forward(self, x):
        out = self.linear(x)
        return out

model=LinearRegression()
criterion = nn.MSELoss()
optimizer = optim.SGD(model.parameters(), lr=1e-3)

# Train
num_epochs = 55000
for epoch in range(num_epochs):
    inputs = Variable(x_train)
    target = Variable(y_train)
    out = model(inputs)
    loss = criterion(out,target)
    optimizer.zero_grad()
    loss.backward()
    optimizer.step()

    if(epoch+1)%100==0:
        print('Epoch[{}/{}],loss:{:.6f}'.format(epoch+1,num_epochs,loss.data[0]))

# Test
model.eval()
predict = model(Variable(x_train))
predict = predict.data.numpy()
plt.plot(x_train.numpy(),y_train.numpy(),'ro',label='Original data')
plt.plot(x_train.numpy(),predict,label='Fitting Line')
plt.show()
'''
