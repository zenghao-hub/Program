#pragma once
#include <iostream>
#include<vector>
using namespace std;

struct ListNode
{
	int value;
	ListNode* Next;
};
// ����һ������
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

// ��ӡ����
void printListNode(ListNode *pHead)
{
	if (pHead == nullptr)
	{
		cout << "����Ϊ��!" << endl;
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

// ��������
// �㷨˼�룺�����ж��Ƿ��ǿսڵ㣬������β������һ������
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

// ɾ������Ľڵ�
// �㷨˼�룺�ҵ��ڵ㣬�����ͷ����벻��ͷ���
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


// ��β��ͷ��ӡ���� �ݹ���ջ
void TailPrint(ListNode *pHead)
{
	if (pHead != nullptr)
	{
		if (pHead->Next != nullptr)
			TailPrint(pHead->Next);
		cout << pHead->value << "<-";
	}

}

// ����ĵ�����k���ڵ�
// �㷨˼��,��һ��ָ��������k-1����Ȼ��ڶ���ָ�뿪ʼ�ߣ�ֱ����һ��ָ���ߵ��ף���ô�ڶ���ָ����ǵ�����k���ڵ�
// ע�ⰲȫ��
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
��������ڽڵ�
�㷨˼�룺���ȸ���һ��һ��ָ���ҵ����Ľڵ����
Ȼ��ָ��3������n����ָ��4��ָ��3һ�𵥲���ǰ��
*/

/*
��ת����
�㷨˼�룺���ȶ���pre = nullptr Ȼ�����pNode��һ���ȼ�¼��һ�ڵ㣬��ȥ��ת��
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
�ϲ��������������
�ж�����ͷ����С����Ϊ������ͷ��㣬��һ�ڵ���õݹ�.������
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