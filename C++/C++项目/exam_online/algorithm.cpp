// algorithm.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#include "pch.h"
#include"sort.h"
#include"ListNode.h"
#include"Tree.h"
#pragma warning(disable:4996)
#include <iostream>
#include<vector>
#include <string>
#include<algorithm>
#include <map>
#include<queue>
using namespace std;

class student
{
	int num;
	char *name;
public:
	student()
	{
		name = new char(20);
		cout << "Student" << endl;
	}
	~student()
	{
		cout << "~Student " << (int)name << endl;
		delete name;
		name = NULL;
	}
	student(const student &s)
	{
		name = new char(20);
		memcpy(name, s.name, strlen(s.name));
		cout << "copy" << endl;
	}
};

int cvte_findminindex(vector<int> input, int value, int valindex)
{
	for (int i = input.size() - 1; i >= 0; i--)
	{
		if (input[i] < value&&i != valindex)
			return i;
	}
	return 0;
}

int cvteExam()
{
	vector<int> input;
	int num;
	while (cin >> num) {
		input.push_back(num);
		char ch = getchar();
		if (ch == '\n')
			break;
	}
	//确保有结果
	vector<int> left, right;
	left.push_back(input[0]);
	// 找到比第一个数小的最后一个数
	int index = cvte_findminindex(input, input[0], 0);
	//在0-index里面找出最大值，如果最大值就是in[0]，就可以退出，否则继续
	int maxpre = 0;
	int maxcur = 0;
	int maxnumber;
	while (1)
	{
		maxpre = maxcur;
		for (int i = maxpre+1; i <= index; i++)
		{
			if (input[i] > input[maxpre])
			{
				maxnumber = input[i];
				maxcur = i;
			}
		}
		if (maxcur == maxpre)
			break;
		else
		{
			index = cvte_findminindex(input, maxnumber, maxcur);
		}
	}
	cout << "left = ";
	for (int i = 0; i < index; i++)
		cout << input[i] << ' ';
	cout << input[index];
	cout << ", right = ";
	for (int i = index + 1; i < input.size(); i++)
		cout << input[i] << ' ';
	return 0;

}

int main_1()
{
	
	return 0;
}

// 字节跳动笔试题
bool dealstr1(string &str)
{
	int length = str.size();
	for (int i = 0; i < length-1; i++)
	{
		if (i <= length - 3)
		{
			if (str[i] == str[i + 1] && str[i] == str[i + 2])
			{
				str.erase(str.begin() + i + 2);
				return false;
			}
		}
	}
	return true;
}
bool dealstr2(string &str)
{
	int length = str.size();
	for (int i = 0; i < length - 1; i++)
	{
		if (i <= length - 4)
		{
			if (str[i] == str[i + 1] && str[i+2] == str[i + 3])
			{
				str.erase(str.begin() + i + 2);
				return false;
			}
		}
	}
	return true;
}
int byteExam_1()
{
	int n;
	cin >> n;
	vector<string> data;
	while (n--)
	{
		string tmp;
		cin >> tmp;
		data.push_back(tmp);
	}
	for (int i = 0; i < data.size(); i++)
	{
		while (!dealstr1(data[i]))
		{
		}
		while (!dealstr2(data[i]))
		{
		}
		cout << data[i] << endl;
	}
	return 0;
}


int calC(int num1, int num2)
{
	int sum1 = 1,sum2=1;
	if (num1 < num2)
		return 0;
	if (num1 < 2 * num2)
		num2 = num1 - num2;
	int cnum2 = num2;
	while (cnum2)
	{
		sum1 = sum1 * num1;
		num1--;
		cnum2--;
	}
		
	for (int i = num2; i >1; i--)
	{
		sum2 = sum2 * i;
	}
	return sum1 / sum2;
}

class A {
	int n1;
	int n2;
public:
	A() :n2(0), n1(n2 + 2) {

	}
	void print()
	{
		cout << n1 << ' ' << n2;
	}
};

// n个骰子的点数
void ntouzi(int number)
{
	vector<int> a, b;
	for (int i = 0; i < 6; i++)
	{
		a.push_back(1);
	}
	// 点数是number-6*number
	for (int k = 2; k <= number; k++)
	{
		// 从第二次开始计算 只是第二次的部分k=2
		for (int num = k; num <= 6 * k; num++)
		{
			int sum = 0;
			for (int dian = 1; dian <= 6; dian++)
			{
				if (num - dian >= (k-1)&& num - dian<((k-1)*6+1))
					sum = sum + a[num - dian - (k-1)];
			}
			b.push_back(sum);
			cout << sum << ' ';
		}
		a = b;
		b.clear();
		cout << endl;
	}
}


// 和为s的连续正整数序列
void function57(int s)
{
	int small = 1;
	int big = 2;
	while (big < s)
	{
		int sum = (small + big)*(big - small + 1) / 2;
		if (s == sum)
		{
			cout << '[' << small << ',' << big << ']'<<endl;
			small++;
		}
		else if (s > sum)
			big++;
		else
			small++;
	}
}

// 只有两个数字出现一次，其余数字均出现了两次
void function58(vector<unsigned> s)
{
	unsigned size = s.size();
	unsigned res = 0;
	for (unsigned i = 0; i < size; i++)
	{
		res = res ^ s[i];
	}
	// getBit
	unsigned bit = 0;
	while ((res & 1) == 0 && (bit < 8 * sizeof(unsigned))) // 与运算必须打括号
	{
		res = res >> 1;//右移
		bit++;
	}
	vector<unsigned> s1, s0;
	for (unsigned i = 0; i < size; i++)
	{
		unsigned tmp = s[i];
		tmp = tmp >> bit;
		if ((tmp & 1)==1)
		{
			s1.push_back(s[i]);
		}
		else
			s0.push_back(s[i]);
	}
	unsigned res1=0, res0=0;
	for (unsigned i = 0; i < s1.size(); i++)
		res1 = res1 ^ s1[i];
	for (unsigned i = 0; i < s0.size(); i++)
		res0 = res0 ^ s0[i];
	cout << res1<<' '<<res0;
}

void function50(string s)
{
	map<char, int> data; // m.count(key)，m.find(key)
	for (int i = 0; i < s.size(); i++)
	{
		int count = data.count(s[i]);
		if (count == 0)
			data.insert(pair<char, int>(s[i], 1));
		else
			data[s[i]] = count + 1;
	}
	// 遍历map
	map<char, int>::iterator iter;
	iter = data.begin();
	while (iter != data.end()) {
		if (iter->second == 1)
			cout << iter->first<<iter->second;
		iter++;
	}
}


int GetUglyNumber_Solution(int index) {
	if (index == 0)
		return 0;
	int *a = new int[index];
	a[0] = 1;
	int p2 = 0, p3 = 0, p5 = 0;
	for (int i = 1; i < index; i++)
	{
		int tmp = min(min(a[p2] * 2, a[p3] * 3), a[p5] * 5);
		a[i] = tmp;
		if (a[p2] * 2 <= tmp)
			p2++;
		if (a[p3] * 3 <= tmp)
			p3++;
		if (a[p5] * 5 <= tmp)
			p5++;
	}
	return a[index - 1];
}



int main_t()
{
	vector<unsigned> arr = { 2,2,4,5,5,4,1,9 };
	//heapSort(arr);
	//Print(arr);
	//function58(arr);
	//function50("aabbccddeeffghhrrqqwee");

	TreeNode * a1 = new TreeNode(8);
	TreeNode * a2 = new TreeNode(6);
	TreeNode * a3 = new TreeNode(10);
	TreeNode * a4 = new TreeNode(5);
	TreeNode * a5 = new TreeNode(7);
	TreeNode * a6 = new TreeNode(9);
	TreeNode * a7 = new TreeNode(11);
	a1->left = a2;
	a1->right = a3;
	a2->left = a4;
	a2->right = a5;
	a3->left = a6;
	a3->right = a7;
	//cout << deepTree(a1);
	//queneTree(a1);
	TreeNode * b1 = new TreeNode(8);
	TreeNode * b2 = new TreeNode(10);
	TreeNode * b3 = new TreeNode(6);
	TreeNode * b4 = new TreeNode(11);
	TreeNode * b5 = new TreeNode(9);
	TreeNode * b6 = new TreeNode(7);
	TreeNode * b7 = new TreeNode(5);
	b1->left = b2;
	b1->right = b3;
	b2->left = b4;
	b2->right = b5;
	b3->left = b6;
	b3->right = b7;
	vector<int> path;
	//getPathFromLeaf(a1, a7,path);
	return 0;
}

long long getsum(int *a, int n, int left, int right)
{
	if (right <= -1 || left > n - 1)
		return 0;
	long long x = 0;
	for (int i = left; i <= right; i++)
		x = x + a[i];
	return x;
}
int disifanshi1()
{
	int n;
	cin >> n;
	long long res = 0;
	int a = n;
	int *data = new int[n];
	while (a--)
	{
		int tmp;
		cin >> tmp;
		data[n - a - 1] = tmp;
	}
	int q = 0;
	cin >> q;
	int aq = q;
	long long allsum = getsum(data, n, 0, n - 1);
	while (aq--)
	{
		int a1, a2;
		cin >> a1 >> a2;
		res = res + allsum - getsum(data, n, 0, a1 - 1) - getsum(data, n, a2+1, n - 1);
	}
	cout << res % 1000000007;
	return 0;
}


// 计算几何距离
bool getanswer(vector<vector<int>> dataset, int a1, int a2, int a3, int a4)
{
	vector<double> disall;
	double mindis = 10000.0;
	int minindex = -1;
	for (int i = 0; i < dataset.size(); i++)
	{
		double dis = 0.0;
		dis = (dataset[i][0] - a1)*(dataset[i][0] - a1) +
			(dataset[i][1] - a2)*(dataset[i][1] - a2) +
			(dataset[i][2] - a3)*(dataset[i][2] - a3) + 
			(dataset[i][3] - a4)*(dataset[i][3] - a4);
		if (mindis > dis)
		{
			mindis = dis;
			minindex = i;
		}
	}
	return dataset[minindex][4];

}
int disifanshi2()
{
	vector<int> data;
	vector<vector<int>> dataset;
	int num = 0;
	cin >> num;
	while (num--)
	{
		int a1, a2, a3, a4, a5;
		cin >> a1 >> a2 >> a3 >> a4 >> a5;
		dataset.push_back({ a1,a2,a3,a4,a5 });
	}
	int devnum;
	cin >> devnum;
	vector<bool> ans;
	while (devnum--)
	{
		int a1, a2, a3, a4;
		cin >> a1 >> a2 >> a3 >> a4;
		ans.push_back(getanswer(dataset, a1, a2, a3, a4));
	}
	for (int i = 0; i < ans.size(); i++)
	{
		cout << ans[i];
	}
	return 0;
}

/*
14
1 1 1 0 1
1 1 1 1 1
2 1 1 0 0
3 2 1 0 0
3 3 0 0 0
3 3 0 1 1
2 3 0 1 0
1 2 1 0 1
1 3 0 0 0
3 2 0 0 0
1 2 0 0 0
2 2 1 1 0
2 1 0 0 0
3 2 1 1 1
*/

int baidu1()
{
	int n, m;
	cin >> n >> m;
	int cntn = n;
	int cnm = m;
	vector<vector<int>> data;
	int *test = new int[m];
	while (cntn--)
	{
		int a, b;
		cin >> a >> b;
		data.push_back({ a,b,0 });
	}
	while (cnm--)
	{
		int tmp;
		cin >> tmp;
		test[m - cnm - 1] = tmp;
	}
	int score = 0;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < data.size(); j++)
		{
			if (test[i] >= data[j][0] && test[i] <= data[j][1]&& data[j][2]==0)
			{
				score++;
				data[j][2] = 1;
				break;
			}
		}
	}
	cout << score;
	return 0;
}

int baidu2()
{
	unsigned long long a1, a2, a3, a4;
	unsigned long long n;
	cin >> a1 >> a2 >> a3 >> a4 >> n;
	unsigned long long pren1 = a4;
	unsigned long long pren3 = a2;
	unsigned long long pren2 = a3;
	unsigned long long pren4 = a1;
	unsigned long long answer;
	unsigned long long cnt = n;
	if (n <= 5)
	{
		switch (n)
		{
		case 1:return a1;
		case 2:return a2;
		case 3:return a3;
		case 4:return a4;
		default:
			break;
		}
	}
	while (cnt != 4)
	{
		answer = pren1 + pren3 + pren4;
		cnt--;
		pren4 = pren3;
		pren3 = pren2;
		pren2 = pren1;
		pren1 = answer;

	}
	cnt = answer % 1000000007;
	cout << cnt;
	return 0;
}

int xunfei1()
{
	int n;
	cin >> n;
	int *a = new int[n];
	a[0] = 3, a[1] = 3;
	for (int i = 2; i < n; i++)
	{
		a[i] = a[i - 1] + a[i - 2];
	}
	int sum = a[n-1];
	for (int i = 0; i < n-1; i++)
	{
		sum = 2 * sum + a[n - i - 2];
	}
	cout << sum*2;
	return 0;
}
int xunfei2()
{
	string s;
	cin >> s;
	vector<string> data;
	int begin = 0, end = 0;
	int res = 0;
	s = s + ";";
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == ';')
		{
			bool flag = true;
			string tmp = s.substr(begin, i-begin);
			begin = i + 1;
			if (tmp != "")
			{
				data.push_back(tmp);
				for (int j = 0; j < tmp.size(); j++)
				{
					int a = int(tmp[j]);
					if ((a >= int('A') && a <= int('Z')) || (a >= int('a') && a <= int('z')))
					{

					}
					else
					{
						flag = false;
					}
				}
				if (flag)
					res = res + int(tmp[tmp.size() - 1]) - int(tmp[0]);
			}
				
		}
	}
	cout << res;
	return 0;
}