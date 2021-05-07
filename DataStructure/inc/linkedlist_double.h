#ifndef __DOUBLELINK_H__
#define __DOUBLELINK_H__
#include "type.h"

/*双向链表节点类模板*/
template <typename T>
class DoubleLinkNode
{
public:
	DoubleLinkNode(const T info, DoubleLinkNode<T> *preNode = NULL, DoubleLinkNode<T> *nextNode = NULL)//3个参数的构造函数
	{
		data = info;
		pre = preNode;
		next = nextNode;
	}
	DoubleLinkNode(DoubleLinkNode<T> *preNode = NULL, DoubleLinkNode<T> *nextNode = NULL)//2个参数的构造函数
	{
		pre = preNode;
		next = nextNode;
	}
	~DoubleLinkNode(){};//析构函数
	T data;	
	DoubleLinkNode<T> *pre;//前驱
	DoubleLinkNode<T> *next;//后继
};
/*双向链表类模板*/
template <typename T>
class DoubleLink:public DoubleLinkNode<T>
{
public:
	DoubleLink();//构造函数
	~DoubleLink();//析构函数
	bool isExist();
	bool isEmpty();
	//bool create(unsigned int n, void *dat, unsigned int datlen);//创建链表,构造函数中创建
	bool traverse();//遍历链表
	bool changeNodeValue(int n, T dat);//修改第n个节点的值
	bool insertNode(int n, T dat);//在第n个节点前插入新节点
	bool insertNode(T dat);//在表尾插入新节点
	bool getNodeValue(int n, T *dat);//获取第n个节点的值
	bool deleteNode(int n);//删除第n个节点
	bool deleteNode();//删除表尾节点
	bool clear();
	//bool Destroy();//销毁链表,析构函数销毁链表

	//bool CycDoubleLink_IsExist();
	//bool CycDoubleLink_IsEmpty();
	//bool CycDoubleLink_Create(unsigned int n, void *dat, unsigned int datlen);//创建双向循环链表
	//bool CycDoubleLink_Traverse();//遍历循环链表
	//bool CycDoubleLink_ChangeNodeValue(DoubleLinkList_t * list,unsigned int n, void *dat);//修改节点值
	//bool CycDoubleLink_InsertNode(,unsigned int n, void *dat);
	//bool CycDoubleLink_AddNode(, void *dat);
	//bool CycDoubleLink_GetNodeValue(,unsigned int n, void *dat);
	//bool CycDoubleLink_DeleteNode(,unsigned int n);//删除指定节点
	//bool CycDoubleLink_Clear();
	//bool CycDoubleLink_Destroy();
private:
	DoubleLinkNode<T> *head,*tail;//双链表的头尾指针
};

void testDoubleLink(void);
void testCycDoubleLink(void);
#endif