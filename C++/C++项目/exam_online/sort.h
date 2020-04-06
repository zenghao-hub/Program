#pragma once
#include <iostream>
#include<vector>
using namespace std;
/*
打印数组
*/

void Print(vector<int> nums)
{
	int size = nums.size();
	for (int i = 0; i < size; i++)
		cout << nums[i] << ' ';
}


/*
二分查找
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
在排序数组中查找要插入的位置
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
冒泡排序
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
快速排序的划分函数,快速排序的递归函数
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
插入排序、希尔排序都是基于插入排序原理
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
	unsigned gap = len / INCRGAP + 1; // 步长初始化,注意如果当len<INCRGAP时，gap为0，所以为了保证进入循环，gap至少为1！！！
	while (gap) // while gap>=1
	{
		for (int i = gap; i < len; ++i) // 分组，在每个子序列中进行插入排序
		{
			insertNum = a[i];//将当前的元素值先存起来方便后面插入
			int j = i;
			while (j >= gap && insertNum < a[j - gap])//寻找插入位置
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
选择排序，堆排序都是基于选择排序的原理
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

// 递归方式构建大根堆(len是arr的长度，index是第一个非叶子节点的下标)
void adjust(vector<int> &arr, int len, int index)
{
	int left = 2 * index + 1; // index的左子节点
	int right = 2 * index + 2;// index的右子节点

	int maxIdx = index;
	if (left<len && arr[left] > arr[maxIdx])     maxIdx = left;
	if (right<len && arr[right] > arr[maxIdx])     maxIdx = right;

	if (maxIdx != index)
	{
		swap(arr[maxIdx], arr[index]);
		adjust(arr, len, maxIdx);
	}

}

// 堆排序
void heapSort(vector<int> &arr)
{
	int size = arr.size();
	// 构建大根堆（从最后一个非叶子节点向上）
	for (int i = size / 2 - 1; i >= 0; i--)
	{
		adjust(arr, size, i);
	}

	// 调整大根堆
	for (int i = size - 1; i >= 1; i--)
	{
		swap(arr[0], arr[i]);           // 将当前最大的放置到数组末尾
		adjust(arr, i, 0);              // 将未完成排序的部分继续进行堆排序
	}
}

/*
二路归并排序，多路归并排序都是基于归正排序
这里只写出归并排序,需要额外的空间

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
		int mid = (left + right) / 2;// 可加1
		mergeSort(nums, left, mid);
		mergeSort(nums, mid, right);
		merge(nums, left, mid, right);
	}
}

