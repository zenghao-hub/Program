# coding=utf-8
import torch
import numpy as np
from torch.utils.data import Dataset
import h5py


class h5Dataset(Dataset):

    def __init__(self, h5py_list):
        label_file = h5py.File(h5py_list[0], 'r')
        self.label = torch.from_numpy(label_file['label'].value)    # 提取h5py文件中label  （ndarry)
        if len(self.label) > 10000:
            cat_data = self.label[:5000]      # 时间考虑，只训练4000
            dog_data = self.label[-5000:]
            self.label = torch.cat((cat_data, dog_data), 0)
        else:
            cat_data = self.label[:1000]  # 时间考虑，只测试1000
            dog_data = self.label[-1000:]
            self.label = torch.cat((cat_data, dog_data), 0)
        self.nSamples = self.label.size(0)
        temp_dataset = torch.Tensor()
        temp_dataset = temp_dataset.float()
        for file in h5py_list:
            h5_file = h5py.File(file, 'r')
            if len(self.label) == 10000:
                cat_dataset = torch.from_numpy(h5_file['data'].value)
                dog_dataset = cat_dataset[-5000:]
                cat_dataset = cat_dataset[:5000]
                dataset = torch.cat((cat_dataset, dog_dataset), 0)    # 时间考虑，只训练4000
            else:
                cat_dataset = torch.from_numpy(h5_file['data'].value)
                dog_dataset = cat_dataset[-1000:]
                cat_dataset = cat_dataset[:1000]
                dataset = torch.cat((cat_dataset, dog_dataset), 0)    # 时间考虑，只训练4000
            temp_dataset = torch.cat((temp_dataset, dataset), 1)        # 特征向量融合

        self.dataset = temp_dataset

    def __len__(self):
        return self.nSamples

    def __getitem__(self, index):
        assert index < len(self), 'index range error'
        data = self.dataset[index]
        label = self.label[index]
        return data, label
