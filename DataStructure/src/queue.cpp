/************************************************************************
 *队列：先进先出的一种数据结构
 *参考资料：《数据结构与算法》张铭，王腾蛟，赵海燕等
 *wangfeng
 *E-mail:fengwang0301@163.com
 *CSDN:https://blog.csdn.net/u013073067?spm=1001.2101.3001.5343
 *GitHub:https://github.com/wangfeng0301
 *2021.5.3
************************************************************************/
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
using namespace std;

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
 *功能：创建队列
 *输入：q:队列指针
 *		size:队列大小
 *		datlen:队列元素数据类型大小（字节）
 *输出：无
 *返回：无
************************************************************************/
/*bool Queue_Create(Queue_t *q, int size, uint datlen)
{
	q->qu = (void *)malloc((size + 1) * datlen);//开辟size+1个数据类型空间
	if(q->qu == NULL)
		return FALSE;
	q->front = q->rear = 0;
	q->size = size+1;
	q->qulen = datlen;
	return TRUE;
}*/

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
/************************************************************************
 *功能：销毁队列
 *输入：q:队列指针	
 *输出：无
 *返回：无
************************************************************************/
/*void Queue_Destroy(Queue_t *q)
{
	Queue_Clear(q);
	free(q->qu);
	q->qu = NULL;
}*/

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
#if 0
/************************************************************************
 *功能：创建队列,链式队列不用提前开辟大小，可以在入队列时动态开辟空间
 *输入：q:队列指针
 *		size:队列大小
 *输出：q:队列指针
 *返回：无
************************************************************************/
void LinkQueue_Create(LinkQueue_t *q, uint datlen)
{
	/* 为减少访问队首节点的时间代价，不使用专用表头虚节点 */
	q->size = 0;
	q->front = q->rear = NULL;
	q->datlen = datlen;
}
#endif
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
/************************************************************************
 *功能：销毁队列
 *输入：q:队列指针	
 *输出：无
 *返回：无
************************************************************************/
/*void LinkQueue_Destroy(LinkQueue_t *q)
{
	LinkQueue_Clear(q);
}*/


void testQueue(void)
{
	Queue<int> q(5);
	int dat;

	q.en(10);
	q.en(11);
	q.en(12);
	q.en(13);
	q.en(14);
	q.en(15);
	for(int i = 0;i<5;i++)
	{
		if(q.de(&dat))
			cout << dat << endl;
	}
	q.clear();
	if(q.de(&dat))
		cout << dat << endl;	
}

void testLinkQueue(void)
{
	LinkQueue<int> q;
	int dat;

	q.en(10);
	q.en(11);
	q.en(12);
	q.en(13);
	q.en(14);
	q.en(15);
	for(int i = 0;i<5;i++)
	{
		if(q.de(&dat))
			cout << dat << endl;
	}
	q.clear();
	if(q.de(&dat))
		cout << dat << endl;
	
}