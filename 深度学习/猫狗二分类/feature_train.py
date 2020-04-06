import argparse
import time
import os

import torch
from torch import nn
from torch.autograd import Variable
from torch import optim
from torch.utils.data import DataLoader
import torch.nn.functional as F
from dataset import h5Dataset
from net import classifier


train_list = ['./train_feature_vgg.hd5f', './train_feature_inceptionv3.hd5f', './train_feature_resnet152.hd5f']
test_list = ['./test_feature_vgg.hd5f', './test_feature_inceptionv3.hd5f', './test_feature_resnet152.hd5f']
dataset = {'train': h5Dataset(train_list), 'test': h5Dataset(test_list)}
datasize = {
    'train': dataset['train'].dataset.size(0),
    'test': dataset['test'].dataset.size(0)
}
batch_size = 100
dataloader = {'train': DataLoader(dataset['train'], batch_size=batch_size, shuffle=True,), 'test': DataLoader(
    dataset['test'], batch_size=batch_size, shuffle=False,)}
dimension = dataset['train'].dataset.size(1)

mynet = classifier(dimension, 2)
criterion = nn.CrossEntropyLoss()
optimizer = optim.SGD(mynet.parameters(), lr=1e-3)
epoches = 50


for epoch in range(epoches):
    print('第{}次训练!'.format(epoch+1))
    mynet.train()
    since = time.time()

    train_loss = 0.0
    train_acc = 0.0
    correct = 0
    for i, data in enumerate(dataloader['train'], 1):
        feature, label = data
        feature = Variable(feature)
        label = Variable(label)

        # forward
        out = mynet(feature)
        loss = criterion(out, label)
        # backward
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

        train_loss += loss.item()
        _, pred = torch.max(out, 1)
        correct += torch.sum(pred == label)
        # correct += pred.eq(label.long()).sum().item()

    train_loss /= datasize['train']
    eplise_time = time.time() - since
    print('Loss: {:.6f}, Acc: {:.2f}%, Time: {:.0f}s'.format(
        train_loss, 100*float(correct) / float(datasize['train']), eplise_time))
    print('验证')
    mynet.eval()
    correct = 0.0
    eval_loss = 0.0
    for data in dataloader['test']:
        feature, label = data
        feature = Variable(feature)
        label = Variable(label)
        # forward
        out = mynet(feature)
        loss = criterion(out, label)

        _, pred = torch.max(out, 1)
        correct += torch.sum(pred == label)
        eval_loss += loss.item()

    print('Loss: {:.6f}, Acc: {:.2f}%'.format(eval_loss / datasize['test'], 100 * float(correct) / float(datasize['test'])))
print('Finish Training!')

save_path = os.path.join('./', 'model_save')
if not os.path.exists(save_path):
    os.mkdir(save_path)

torch.save(mynet.state_dict(), save_path + '/feature_model.pth')

