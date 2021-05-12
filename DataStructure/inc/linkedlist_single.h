#ifndef __LINK_H__
#define __LINK_H__
#include "type.h"
#include <iostream>
#include <string.h>
using namespace std;

/************************************************************************
 *链表节点类模板
************************************************************************/
template <typename T>
class LinkNode
{
public:
	LinkNode(const T info, /*const*/ LinkNode<T> *nextValue = NULL)//两个参数的构造函数
	{
		data = info;
		next = nextValue;
	}
	LinkNode(/*const*/ LinkNode<T> *nextValue = NULL)//1个参数的构造函数
	{
		next = nextValue;
	}
	~LinkNode(){};//析构函数
	T data;
	LinkNode<T> *next;
};
/************************************************************************
 *链表类模板
************************************************************************/
template <typename T>
class Link:public LinkNode<T>//公有继承LinkNode类
{
public:
	Link();//构造函数
	~Link();//析构函数
	bool isEmpty();
	bool changeNodeValue(int n, T dat);
	bool traverse();
	bool insertNode(int n, T dat);
	bool insertNode(T dat);//链尾插入
	bool getNodeValue(int n, T *dat);
	bool deleteNode(int n);
	bool deleteNode();//删除链尾节点
	bool clear();
	bool reverse();
private:
	LinkNode<T> *head, *tail;//单链表的头尾指针
};

/************************************************************************
 *功能：构造函数，初始化链表
 *输入：
 *输出：
 *返回：
************************************************************************/
template <typename T>
Link<T>::Link()
{
	head = tail = new LinkNode<T>(NULL);
	cout << "Link()" << endl;
}
/************************************************************************
 *功能：析构函数，销毁链表，释放各个节点
 *输入：
 *输出：
 *返回：
************************************************************************/
template <typename T>
Link<T>::~Link()
{
	LinkNode<T> *temp;
	while(head != NULL)
	{
		temp = head;
		head = head->next;
		delete temp;
	}
	cout << "~Link()" << endl;
}

/************************************************************************
 *功能：判断链表是否为空
 *输入：
 *输出：无
 *返回：TRUE or FALSE
************************************************************************/
template <typename T>
bool Link<T>::isEmpty()
{
	if(head->next == NULL)
	{
		cout << "链表空" <<endl;
		return TRUE;
	}
	else
		return FALSE;
}

/************************************************************************
 *功能：修改节点n的值
 *输入：n:第n个节点,n从0开始算。只算普通节点
 *		dat:修改后的值
 *输出：无
 *返回：TRUE or FALSE
************************************************************************/
template <typename T>
bool Link<T>::changeNodeValue(int n, T dat)
{
	LinkNode<T> *t;
	cout << "修改节点" << n << "的值" << endl;
	if(isEmpty())
		return FALSE;
	t = head->next;
	while(t != NULL && n--)								//找到第n个节点
	{
		t = t->next;
	}
	if(t != NULL)
	{
		t->data = dat;
		return TRUE;
	}
	else
	{
		cout << "节点不存在！" << endl;;
		return FALSE;
	}
}

/************************************************************************
 *功能：遍历节点
 *输入：无
 *输出：无
 *返回：TRUE or FALSE
************************************************************************/
template <typename T>
bool Link<T>::traverse()
{
	LinkNode<T> *p;

	cout << "遍历链表" << endl;
	if(isEmpty())
	{
		return FALSE;
	}
	p = head->next;
	while(p != NULL)
	{
		cout << p->data << endl;
		p = p->next;								//指向下一个节点
	}
	return TRUE;
}

/************************************************************************
 *功能：在第n个节点前插入节点，节点从0开始算，只算普通节点
 *输入：n:第n个节点
 *		dat:插入的值
 *输出：无
 *返回：TRUE or FALSE
************************************************************************/
template <typename T>
bool Link<T>::insertNode(int n, T dat)
{
	LinkNode<T> *p;
	LinkNode<T> *in;									//新插入节点

	cout << "在节点" << n << "前插入新节点" << endl;
	if(isEmpty())
		return FALSE;
	p = head;										//定义指针指向首节点
	while(p != NULL && n--)							//定位到第n个节点，在此节点前插入新节点
	{
		p = p->next;
	}
	if(p != NULL)
	{
		in = new LinkNode<T>(dat, p->next);//为新插入节点分配内存,并赋值
		if(in == NULL)
		{
			cout << "空间分配失败" << endl;
			return FALSE;
		}
		p->next = in;								//源节点指向新插入节点
		if(p == tail)								//在链尾插入
			tail = in;
		return TRUE;
	}
	else
	{
		cout << "节点不存在!" << endl;
		return FALSE;
	}
}
/************************************************************************
 *功能：在尾节点后插入节点
 *输入：dat:插入的值
 *输出：无
 *返回：TRUE or FALSE
************************************************************************/
template <typename T>
bool Link<T>::insertNode(T dat)
{
	LinkNode<T> *in;									//新插入节点

	cout << "在链尾插入新节点" << endl;
	in = new LinkNode<T>(dat, tail->next);//为新插入节点分配内存,并赋值
	if(in == NULL)
	{
		cout << "空间分配失败" << endl;
		return FALSE;
	}
	tail->next = in;								//源节点指向新插入节点
	tail = in;
	return TRUE;
}

/************************************************************************
 *功能：获取第n个节点的数据，节点从0开始算，只算普通节点
 *输入：n:第n个节点
 *		dat:获取的值
 *输出：无
 *返回：TRUE or FALSE
************************************************************************/
template <typename T>
bool Link<T>::getNodeValue(int n, T *dat)
{
	LinkNode<T> *p;

	if(isEmpty())
		return FALSE;
	p = head->next;									//定义LinkNode_t型指针指向首节点
	while(p != NULL && n--)							//定位到第n个节点，在此节点前插入新节点
	{
		p = p->next;
	}
	if(p != NULL)
	{
		*dat = p->data;
		return TRUE;
	}
	else
	{
		cout << "节点不存在！" << endl;
		return FALSE;
	}
}

/************************************************************************
 *功能：删除第n个节点，n从0开始算，只算普通节点
 *输入：n:第n个节点,从0开始算
 *输出：无
 *返回：无
************************************************************************/
template <typename T>
bool Link<T>::deleteNode(int n)
{
	LinkNode<T> *p, *pre;
	
	cout << "第" << n << "个节点将被删除" << endl;
	if(isEmpty())
		return FALSE;
	pre = head;										//记录要删除节点的前一个节点
	p = head->next;									//定义指针指向首节点
	while(p != NULL && n--)							//移动到第n个节点，删除
	{
		pre = p;
		p = p->next;
	}
	if(p != NULL)
	{
		pre->next = p->next;
		if(p == tail)
			tail = pre;
		delete p;									//释放节点变量
		p = NULL;
	}
	else
	{
		cout << "被删除节点不存在！" << endl;
		return FALSE;
	}
	return TRUE;
}
/************************************************************************
 *功能：删除尾节点
 *输入：无
 *输出：无
 *返回：无
************************************************************************/
template <typename T>
bool Link<T>::deleteNode()
{
	LinkNode<T> *p, *pre;
	
	cout << "删除尾节点" << endl;
	if(isEmpty())
		return FALSE;
	pre = head;										//记录要删除节点的前一个节点
	p = head->next;									//定义指针指向首节点
	while(p->next != NULL)								//移动到链尾，删除
	{
		pre = p;
		p = p->next;
	}
	tail = pre;
	pre->next = p->next;
	delete p;									//释放节点变量
	p = NULL;
	return TRUE;
}

/************************************************************************
 *功能：清空整个链表
 *输入：
 *输出：无
 *返回：TRUE or FALSE
************************************************************************/
template <typename T>
bool Link<T>::clear()
{
	LinkNode<T> *p;
	
	if(isEmpty())
		return FALSE;
	p = head->next;									//指向第一个普通节点
	while(p != NULL)								//每个节点挨个删除
	{
		head->next = p->next;						//头节点指向下一个节点
		delete p;									//释放当前节点内存
		p = head->next;							
	}
	if(p == NULL)
	{
		cout << "清空链表成功！" << endl;
		tail = head;
		return TRUE;
	}
	return FALSE;
}

/************************************************************************
 *功能：翻转整个链表
 *输入：无
 *输出：无
 *返回：无
************************************************************************/
template <typename T>
bool Link<T>::reverse()
{
	LinkNode<T> *currNode;							//当前要插到head后面的node
	LinkNode<T> *nextNode;							//相对于当前节点的下一个节点
	LinkNode<T> *preNode;							//相对于当前节点的上一个节点
	LinkNode<T> *headNode;							//头结点

	cout << "翻转单向链表" << endl;
	if(isEmpty())
		return FALSE;
	headNode = head;
	preNode = head->next;
	currNode = preNode->next;
	while(currNode != NULL)
	{
		nextNode = currNode->next;					//保存next节点
		preNode->next = currNode->next;
		currNode->next = headNode->next;
		headNode->next = currNode;

		currNode = nextNode;
	}
	tail = preNode;
	return TRUE;
}


void testLink(void);

#endif