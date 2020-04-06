#pragma once
#include <iostream>
#include<vector>
using namespace std;
/*
��ӡ����
*/

void Print(vector<int> nums)
{
	int size = nums.size();
	for (int i = 0; i < size; i++)
		cout << nums[i] << ' ';
}


/*
���ֲ���
*/
int binarySearch(vector<int> nums, int num)
{
	int left = 0;
	int right = nums.size();
	while (left < right)
	{
		int mid = (left + right) / 2;
		if (nums[mid] < num)
			left = mid;
		else if (nums[mid] > num)
			right = mid;
		else
		{
			while (nums[mid] == num)
			{
				mid--;
			}
			return mid;
		}
	}
	return -1;
}

/*
�����������в���Ҫ�����λ��
*/

int insertSearch(vector<int> nums, int num, int left, int right)
{
	if (nums[left] > num)
		return left;
	if (nums[right] < num)
		return right + 1;
	while (left <= right)
	{
		int mid = (left + right) / 2;
		if (nums[mid] < num)
			left = mid;
		else if (nums[mid] > num)
			right = mid;
		if (mid == 0)
			mid++;
		if (nums[mid - 1]<=num&&nums[mid]>=num)
			return mid;
		
	}
}
/*
ð������
*/
void BubbleSort(vector<int> &nums)
{
	int size = nums.size();
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (nums[i] > nums[j])
				swap(nums[i], nums[j]);
		}
	}
}

/*
��������Ļ��ֺ���,��������ĵݹ麯��
*/
int partition(vector<int> &nums, int left, int right)
{
	int small = left;
	for (int index = left + 1; index <= right; index++)
	{
		if (nums[index] < nums[left])
		{
			small++;
			if (index != small)
				swap(nums[index], nums[small]);
		}
	}
	swap(nums[small], nums[left]);
	return small;
}
void quick_sort(vector<int> &nums, int left, int right)
{
	if (left == right)
		return;
	int j = partition(nums, left, right);
	if (left < j)
		quick_sort(nums, left, j - 1);
	if (j < right)
		quick_sort(nums, j + 1, right);
}


/*
��������ϣ�������ǻ��ڲ�������ԭ��
*/
void insertSort(vector<int> &nums)
{
	int size = nums.size();
	for (int i = 0; i < size-1; i++)
	{
		int j = i;
		int tmp = nums[i + 1];
		while (j >= 0 && tmp < nums[j])
		{
			nums[j + 1] = nums[j];
			j--;
		}
		nums[j + 1] = tmp;
	}
}
const int INCRGAP = 2;
void shellSort(vector<int> &a)
{
	int len = a.size();
	int insertNum = 0;
	unsigned gap = len / INCRGAP + 1; // ������ʼ��,ע�������len<INCRGAPʱ��gapΪ0������Ϊ�˱�֤����ѭ����gap����Ϊ1������
	while (gap) // while gap>=1
	{
		for (int i = gap; i < len; ++i) // ���飬��ÿ���������н��в�������
		{
			insertNum = a[i];//����ǰ��Ԫ��ֵ�ȴ���������������
			int j = i;
			while (j >= gap && insertNum < a[j - gap])//Ѱ�Ҳ���λ��
			{
				//a[j] = a[j - gap];
				swap(a[j], a[j - gap]);
				j -= gap;
			}
			//a[j] = insertNum;
		}
		gap = gap / INCRGAP;
	}
}

/*
ѡ�����򣬶������ǻ���ѡ�������ԭ��
*/
void selectSort(vector<int> &nums)
{
	int size = nums.size();
	for (int i = 0; i < size-1; i++)
	{
		int key = nums[i];
		int minindex = i;
		for (int j = i + 1; j < size; j++)
		{
			if (nums[j] < key)
			{
				key = nums[j];
				minindex = j;
			}
		}
		if (minindex != i)
		{
			swap(nums[i], nums[minindex]);
		}
	}
}

// �ݹ鷽ʽ���������(len��arr�ĳ��ȣ�index�ǵ�һ����Ҷ�ӽڵ���±�)
void adjust(vector<int> &arr, int len, int index)
{
	int left = 2 * index + 1; // index�����ӽڵ�
	int right = 2 * index + 2;// index�����ӽڵ�

	int maxIdx = index;
	if (left<len && arr[left] > arr[maxIdx])     maxIdx = left;
	if (right<len && arr[right] > arr[maxIdx])     maxIdx = right;

	if (maxIdx != index)
	{
		swap(arr[maxIdx], arr[index]);
		adjust(arr, len, maxIdx);
	}

}

// ������
void heapSort(vector<int> &arr)
{
	int size = arr.size();
	// ��������ѣ������һ����Ҷ�ӽڵ����ϣ�
	for (int i = size / 2 - 1; i >= 0; i--)
	{
		adjust(arr, size, i);
	}

	// ���������
	for (int i = size - 1; i >= 1; i--)
	{
		swap(arr[0], arr[i]);           // ����ǰ���ķ��õ�����ĩβ
		adjust(arr, i, 0);              // ��δ�������Ĳ��ּ������ж�����
	}
}

/*
��·�鲢���򣬶�·�鲢�����ǻ��ڹ�������
����ֻд���鲢����,��Ҫ����Ŀռ�

*/
void merge(vector<int> &nums, int left, int mid, int right)
{
	vector<int> res;
	int l = left, m = mid;
	while (l <= mid - 1 && m <= right)
	{
		if (nums[l] <= nums[m])
			res.push_back(nums[l++]);
		else
			res.push_back(nums[m++]);
	}
	while (l <= mid - 1) {
		res.push_back(nums[l++]);
	}
	while (m <= right)
		res.push_back(nums[m++]);
	for (int i = 0; i < res.size(); i++)
	{
		nums[left++] = res[i];
	}

}
void mergeSort(vector<int> &nums, int left, int right)
{
	if (left + 1 < right)
	{
		int mid = (left + right) / 2;// �ɼ�1
		mergeSort(nums, left, mid);
		mergeSort(nums, mid, right);
		merge(nums, left, mid, right);
	}
}

