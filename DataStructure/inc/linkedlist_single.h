#ifndef __LINK_H__
#define __LINK_H__
#include "type.h"

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
	//bool isExist();//实例化对象后，链表必然存在
	bool isEmpty();
	//bool create(int n);//实例化对象在构造函数中就创建了链表
	bool changeNodeValue(int n, T dat);
	bool traverse();
	bool insertNode(int n, T dat);
	bool insertNode(T dat);//链尾插入
	bool getNodeValue(int n, T *dat);
	bool deleteNode(int n);
	bool deleteNode();//删除链尾节点
	bool clear();
	//bool destroy();//析构函数销毁链表
	bool reverse();
private:
	LinkNode<T> *head, *tail;//单链表的头尾指针
};

void testLink(void);

#endif