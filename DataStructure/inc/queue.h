#ifndef __QUEUE_H__
#define __QUEUE_H__
#include "type.h"
#include "linkedlist_single.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

template <typename T>
class Queue
{
public:
	Queue(int _size);//构造函数
	~Queue();//析构函数
	bool isEmpty();
	bool isFull();
	bool en(T dat);
	bool de(T *dat);
	void clear();
private:
	int size;//队列大小
	int front;//队头
	int rear;//队尾
	T *qu;//数组存放数据
};
/* 链式队列类 */
template <typename T>
class LinkQueue:public LinkNode<T>
{
public:
	LinkQueue();//构造函数
	~LinkQueue();//析构函数
	bool isEmpty();
	bool en(T dat);
	bool de(T *dat);
	void clear();
private:
	int size;			//队列大小
	LinkNode<T> *front;	//队头
	LinkNode<T> *rear;	//队尾
};

/************************ 顺序循环队列 ***********************************/
/************************************************************************
 *功能：构造函数，创建队列
 *输入：无
 *输出：无
 *返回：无
************************************************************************/
template <typename T>
Queue<T>::Queue(int _size)
{
	size = _size + 1;//多出1个为队列头
	qu = new T[size];
	front = rear = 0;
}
/************************************************************************
 *功能：析构函数，销毁队列
 *输入：无
 *输出：无
 *返回：无
************************************************************************/
template <typename T>
Queue<T>::~Queue()
{
	delete []qu;
	qu = NULL;
}
/************************************************************************
 *功能：队列是否为空
 *输入：无
 *输出：无
 *返回：空返回TRUE;非空返回FALSE
************************************************************************/
template <typename T>
bool Queue<T>::isEmpty()
{
	if(front == rear)
		return TRUE;
	else
		return FALSE;
}
/************************************************************************
 *功能：队列是否为满
 *输入：无
 *输出：无
 *返回：满返回TRUE;未满返回FALSE
************************************************************************/
template <typename T>
bool Queue<T>::isFull()
{
	if((rear+1)%size == front)
		return TRUE;
	else
		return FALSE;
}

/************************************************************************
 *功能：进队列
 *输入：dat:进队列的数据
 *输出：无
 *返回：TRUE or FLASE
************************************************************************/
template <typename T>
bool Queue<T>::en(T dat)
{
	if(isFull())
	{
		printf("队列已满\r\n");
		return FALSE;
	}
	else
	{
		qu[rear] = dat;//队尾存入数据
		rear = (rear+1)%size;//循环后继
		return TRUE;
	}
}

/************************************************************************
 *功能：出队列
 *输入：无
 *输出：dat:出队列的数据
 *返回：TRUE or FLASE
************************************************************************/
template <typename T>
bool Queue<T>::de(T *dat)
{
	if(isEmpty())
	{
		printf("队列为空\r\n");
		return FALSE;
	}
	else
	{
		*dat = qu[front];
		front = (front+1)%(size);//循环后继
		return TRUE;
	}
}

/************************************************************************
 *功能：清空队列
 *输入：无	
 *输出：无
 *返回：无
************************************************************************/
template <typename T>
void Queue<T>::clear()
{
	front = rear = 0;
}


/************************ 链式队列 ***********************************/
/************************************************************************
 *功能：构造函数，创建链式队列
 *输入：无
 *输出：无
 *返回：无
************************************************************************/
template <typename T>
LinkQueue<T>::LinkQueue()
{
	size = 0;
	front = rear = NULL;
}
/************************************************************************
 *功能：析构函数，销毁链式队列
 *输入：无
 *输出：无
 *返回：无
************************************************************************/
template <typename T>
LinkQueue<T>::~LinkQueue()
{
	clear();
}
/************************************************************************
 *功能：队列是否为空
 *输入：无
 *输出：无
 *返回：空返回TRUE;非空返回FALSE
************************************************************************/
template <typename T>
bool LinkQueue<T>::isEmpty()
{
	if(size == 0)
		return TRUE;
	else
		return FALSE;
}

/************************************************************************
 *功能：进队列
 *输入：dat:进队列的数据
 *输出：无
 *返回：TRUE or FLASE
************************************************************************/
template <typename T>
bool LinkQueue<T>::en(T dat)
{
	LinkNode<T> *temp;

	temp = new LinkNode<T>(dat, NULL);//申请新节点,并赋值
	if(temp == NULL)
	{
		printf("申请内存失败r\n");
		return FALSE;
	}
	if(isEmpty())
	{
		front = rear = temp;
		front->next = NULL;
		rear->next = NULL;
	}
	else
	{
		rear->next = temp;
		rear = temp;
	}
	size ++;
	return TRUE;
}
/************************************************************************
 *功能：出队列
 *输入：无
 *输出：dat:出队列的数据
 *返回：TRUE or FLASE
************************************************************************/
template <typename T>
bool LinkQueue<T>::de(T *dat)
{
	LinkNode<T> *temp;

	if(isEmpty())
	{
		printf("队列为空\r\n");
		return FALSE;
	}
	*dat = front->data;//取数据
	temp = front;
	front = front->next;
	delete temp;								//释放取出的节点
	temp = NULL;
	if(front == NULL)
		rear = NULL;
	size --;
	return TRUE;
}
/************************************************************************
 *功能：清空队列
 *输入：无
 *输出：无
 *返回：无
************************************************************************/
template <typename T>
void LinkQueue<T>::clear()
{
	LinkNode<T> *temp;
	while(front != NULL)
	{
		temp = front;
		front = front->next;
		delete temp;
	}
	temp = NULL;
	rear = NULL;
	size = 0;
	printf("清空队列成功\r\n");
}


void testQueue(void);
void testLinkQueue(void);

#endif