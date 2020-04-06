#pragma once
#include <iostream>
#include<vector>
using namespace std;

struct ListNode
{
	int value;
	ListNode* Next;
};
// 定义一个链表
ListNode * getListNode(int len)
{
	if (len <= 0)
		return nullptr;
	vector<ListNode*> data;
	for (int i = 0; i < len; i++)
	{
		ListNode* tmp = new ListNode();
		tmp->value = i;
		tmp->Next = nullptr;
		data.push_back(tmp);
	}
	ListNode* tmp1 = new ListNode();
	ListNode* tmp2 = new ListNode();
	tmp1 = data[0];
	tmp2 = data[0];
	for (int i = 0; i < len-1; i++)
	{
		tmp1->Next = data[i + 1];
		tmp1 = tmp1->Next;
	}
	return tmp2;
}

// 打印链表
void printListNode(ListNode *pHead)
{
	if (pHead == nullptr)
	{
		cout << "链表为空!" << endl;
		return;
	}
	else
	{
		while (pHead)
		{
			cout << pHead->value;
			if (pHead->Next != nullptr)
				cout << "->";
			pHead = pHead->Next;
		}
	}
}

// 插入链表
// 算法思想：首先判断是否是空节点，这是在尾部插入一个链表
ListNode * addListNode(ListNode *pHead, int value)
{
	ListNode * pNew = new ListNode();
	pNew->Next = nullptr;
	pNew->value = value;
	if (pHead == nullptr)
	{
		return pNew;
	}
	ListNode * pNode = pHead;
	while (pHead->Next!=nullptr)
	{
		pHead = pHead->Next;
	}
	pHead->Next = pNew;
	return pNode;
}

// 删除链表的节点
// 算法思想：找到节点，如果是头结点与不是头结点
ListNode * RemoveListNode(ListNode *pHead, int value)
{
	ListNode * pDel = new ListNode();
	pDel = nullptr;
	if (pHead == nullptr)
	{
		return nullptr;
	}
	if (pHead->value == value)
	{
		pDel = pHead->Next;
		return pDel;
	}
	ListNode * pNode= new ListNode();
	pNode = pHead;
	while (pHead->Next->value != value && pHead->Next != nullptr)
	{
		pHead = pHead->Next;
	}
	if (pHead->Next == nullptr)
		return pNode;
	pDel = pHead->Next;
	pHead->Next = pHead->Next->Next;
	delete pDel;
	return pNode;
}


// 从尾到头打印链表 递归与栈
void TailPrint(ListNode *pHead)
{
	if (pHead != nullptr)
	{
		if (pHead->Next != nullptr)
			TailPrint(pHead->Next);
		cout << pHead->value << "<-";
	}

}

// 链表的倒数第k个节点
// 算法思想,第一个指针首先走k-1步，然后第二个指针开始走，直到第一个指针走到底，那么第二个指针就是倒数第k个节点
// 注意安全性
ListNode * LastK(ListNode *pHead, int k)
{
	if (k <= 0)
		return nullptr;
	ListNode * head1 = pHead;
	ListNode * head2 = pHead;
	for (int i = 0; i < k-1; i++)
	{
		if (head1->Next)
			head1 = head1->Next;
		else
			return nullptr;
	}
	while (head1->Next)
	{
		head1 = head1->Next;
		head2 = head2->Next;
	}
	return head2;
}

/*
链表环的入口节点
算法思想：首先根据一快一慢指针找到环的节点个数
然后指针3首先走n步，指针4与指针3一起单步向前走
*/

/*
反转链表
算法思想：首先定义pre = nullptr 然后遍历pNode，一定先记录下一节点，再去反转。
*/

ListNode * reverseListNode(ListNode *pHead)
{
	if (pHead == nullptr)
		return nullptr;
	if (pHead->Next == nullptr)
		return pHead;
	ListNode *pNode = pHead;
	ListNode *pre = nullptr;
	while (pNode)
	{
		ListNode *next = pNode->Next;
		pNode->Next = pre;
		pre = pNode;
		pNode = next;
	}
	return pre;
}


/*
合并两个排序的链表
判断两个头结点大小，作为新链表头结点，下一节点就用递归.很巧妙
*/

ListNode * Merge(ListNode *pHead1, ListNode *pHead2)
{
	if (pHead1 == nullptr)
		return pHead2;
	if (pHead2 == nullptr)
		return pHead1;
	ListNode * newList = new ListNode();
	if (pHead1->value < pHead2->value)
	{
		newList->value = pHead1->value;
		newList->Next = Merge(pHead1->Next, pHead2);
	}
	else
	{
		newList->value = pHead2->value;
		newList->Next = Merge(pHead1, pHead2->Next);
	}
	return newList;
}