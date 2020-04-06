__author__ = 'zenghao'

import os
from tqdm import tqdm
import h5py
import numpy as np
import argparse

import torch
from torchvision import datasets, models, transforms
from torch import optim, nn
from torch.autograd import Variable
from torchvision.datasets import ImageFolder
from torch.utils.data import DataLoader
from net import feature_net, classifier

import warnings
warnings.filterwarnings('ignore')  # 忽略图片信息错误警告

#
parse = argparse.ArgumentParser()
# parse.add_argument('--model', required=True, help='vgg,inception3,resnet152')
# parse.add_argument('--batch_size', type=int, default=32)
# parse.add_argument('--phase', required=True, help='train, test')
# opt = parse.parse_args()  # 解析输入参数
# print(opt)
img_transform = transforms.Compose([
    transforms.Scale(320),
    transforms.CenterCrop(299),
    transforms.ToTensor(),
    transforms.Normalize((0.5, 0.5, 0.5), (0.5, 0.5, 0.5))
])
batch_size = 10
# 读取数据
dataset_train = datasets.ImageFolder('../kaggle/train', img_transform)
dataset_test = datasets.ImageFolder('../kaggle/test', img_transform)

# 导入数据 猫狗各2000训练，500测试集
train_loader = DataLoader(dataset_train, batch_size=batch_size, shuffle=False)      # 不能随机打乱数据
test_loader = DataLoader(dataset_test, batch_size=batch_size, shuffle=False)
data_loader = {'train': train_loader, 'test': test_loader}
data_size = {
    'train': len(train_loader.dataset),
    'val': len(test_loader.dataset)
}

# get numbers of classes
img_classes = len(train_loader.dataset.classes)


def CreateFeature(model, phase, outputPath='.'):
    """
    Create h5py dataset for feature extraction.
    ARGS:
        outputPath    : h5py output path
        model         : used model
        labelList     : list of corresponding groundtruth texts
    """
    featurenet = feature_net(model)
    feature_map = torch.Tensor()
    label_map = torch.Tensor()
    label_map = label_map.long()
    for data in tqdm(data_loader[phase]):
        img, label = data
        img = Variable(img, volatile=True)
        label = Variable(label)
        out = featurenet(img)
        feature_map = torch.cat((feature_map, out.cpu().data), 0)
        label_map = torch.cat((label_map, label), 0)
    feature_map = feature_map.numpy()
    label_map = label_map.numpy()
    file_name = '_feature_{}.hd5f'.format(model)
    h5_path = os.path.join(outputPath, phase) + file_name
    with h5py.File(h5_path, 'w') as h:
        h.create_dataset('data', data=feature_map)
        h.create_dataset('label', data=label_map)


CreateFeature('resnet152', 'test', './')