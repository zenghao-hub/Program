// shudu.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include<time.h>
#include<random>
#include<set>
#include<iterator>
#include<vector>
using namespace std;

// 定义容器删除一些元素
void del(set<int> &ans, int* a, int i, int j) {
	for (int k = i; k <= j; k++)
		ans.erase(a[k]);
}
void print(int *a) {
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cout << a[i * 9 + j] << ' ';
		}
		cout << endl;
	}
}
// 根据剔除条件，随机选择n个数
void getnum(set<int> &ans, int n, int *a, int begin) {
	int k = begin;
	while (n--)
	{
		
		int r = rand() % ans.size();
		set<int>::iterator i = ans.begin();
		while (r--)
		{
			++i;
		}
		a[k++] = (*i);
		ans.erase(*i);
	}
}
// 得出随机9数
void get9num(vector<int> &num, set<int> &ans) {
	int n = 9;
	while (n--)
	{
		int r = rand() % ans.size();
		set<int>::iterator i = ans.begin();
		while (r--)
		{
			++i;
		}
		num.push_back(*i);
		ans.erase(*i);
	}
}
int main()
{
	// 初始定义
	int randnum[81] = {9,7,8,3,1,2,6,4,5,
		3,1,2,6,4,5,9,7,8,
		6,4,5,9,7,8,3,1,2,
		7,8,9,1,2,3,4,5,6,
		1,2,3,4,5,6,7,8,9,
		4,5,6,7,8,9,1,2,3,
		8,9,7,2,3,1,5,6,4,
		2,3,1,5,6,4,8,9,7,
		5,6,4,8,9,7,2,3,1};
	set<int> num = { 1,2,3,4,5,6,7,8,9 };
	srand(unsigned(time(0)));

	vector<int> r;
	get9num(r, num);

	for (int k = 0; k < 9; k++)
	{
		int swapnum1 = randnum[k];
		int swapnum2 = r[k];
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++) {
				if (randnum[i * 9 + j] == swapnum1) {
					randnum[i * 9 + j] = swapnum2;
				}
				else if (randnum[i * 9 + j] == swapnum2) {
					randnum[i * 9 + j] = swapnum1;
				}
			}
		}
	}
	print(randnum);

}


