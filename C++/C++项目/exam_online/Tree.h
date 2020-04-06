#pragma once
#include <iostream>
#include<vector>
#include<queue>
using namespace std;

class TreeNode {
public:
	int value;
	TreeNode *left, *right;
	TreeNode(int val) {
		this->value = val;
		this->left = this->right = NULL;
	}
};
struct TreeNode2 {
	int value;
	TreeNode2 *left;
	TreeNode2 *right;
	TreeNode2 *parent;
	TreeNode2(int x):value(x), left(nullptr), right(nullptr), parent(nullptr){}
};

// 根据前序与中序序列重建二叉树
TreeNode *rebaseTree(vector<int> pre, vector<int> mid)
{
	if (pre.size() == 0||mid.size()==0)
		return nullptr;
	TreeNode *root = new TreeNode(0);
	int rootvalue = pre[0];
	int index;
	for (int i = 0; i < mid.size(); i++)
	{
		if (mid[i] == rootvalue)
		{
			index = i;
			break;
		}
	}
	vector<int> midleft,preleft;
	midleft.assign(mid.begin(), mid.begin() + index); // 截取vector的一部分
	preleft.assign(pre.begin() + 1, pre.begin() + index + 1);
	vector<int> midright, preright;
	midright.assign(mid.begin() + index + 1, mid.end());
	preright.assign(pre.begin() + index + 1, pre.end());
	// 可以加入检查的函数，两个数组中的值是否有不一样，否则给的数据有误
	root->value = rootvalue;
	root->left = rebaseTree(preleft, midleft);
	root->right = rebaseTree(preright, midright);
	return root;
}


// 判断B是否是A的子结构


bool isEqual(TreeNode *a, TreeNode*b)
{
	if (b == nullptr)
		return true;
	if (a == nullptr)
		return false;
	if (a->value == b->value)
	{
		return isEqual(a->left, b->left) && isEqual(a->right, b->right);
	}
	else
	{
		return false;
	}
}
bool isHave(TreeNode *a, TreeNode*b)
{
	bool result = false;
	if (a == nullptr&&b == nullptr)
		return true;
	if (a != nullptr&&b != nullptr)
	{
		if (a->value == b->value)
			result = isEqual(a, b);
		if (!result)
			result = (isHave(a->left, b));
		if (!result)
			result = (isHave(a->right, b));
	}
	return result;
}


// 判断是否是二叉树的镜像
bool ismirror(TreeNode *a, TreeNode*b)
{
	if (a == nullptr&&b == nullptr)
		return true;
	else if (a == nullptr || b == nullptr)
		return false;
	else
	{
		if (a->value == b->value)
			return ismirror(a->right, b->left) && ismirror(a->left, b->right);
		else
			return false;
	}
}

// 根据叶节点，得到路径
bool getPathFromLeaf(TreeNode *root, TreeNode*leaf,vector<int> &path)
{
	path.push_back(root->value);
	if (root == leaf)
		return true;
	
	bool found = false;
	if (root->left)
		found = getPathFromLeaf(root->left, leaf, path);
	if (!found&&root->right)
		found = getPathFromLeaf(root->right, leaf, path);
	if (!found)
		path.pop_back();
	return found;
}

// 二叉树的最大深度
int deepTree(TreeNode*root)
{
	if (root == nullptr)
		return 0;
	else
	{
		int leftdeep = deepTree(root->left);
		int rightdeep = deepTree(root->right);
		return leftdeep > rightdeep ? (leftdeep + 1) : (rightdeep + 1);
	}
}
// 是否是平衡二叉树
bool isBalanceTree(TreeNode*root)
{
	if (root == nullptr)
		return 1;
	if (abs(deepTree(root->left) - deepTree(root->right)) > 1)
		return false;
	else
		return isBalanceTree(root->left) && isBalanceTree(root->right);
}

// 层序遍历
queue< TreeNode*> res;
void queneTree(TreeNode*root)
{
	if (root == nullptr)
		return;
	res.push(root);
	while (root) {
		res.pop();
		cout << root->value<<' ';
		if (root->left)
			res.push(root->left);
		if (root->right)
			res.push(root->right);
		if (res.empty())
			return;
		root = res.front();
	}
}