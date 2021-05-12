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
	Queue(int _size);//���캯��
	~Queue();//��������
	bool isEmpty();
	bool isFull();
	bool en(T dat);
	bool de(T *dat);
	void clear();
private:
	int size;//���д�С
	int front;//��ͷ
	int rear;//��β
	T *qu;//����������
};
/* ��ʽ������ */
template <typename T>
class LinkQueue:public LinkNode<T>
{
public:
	LinkQueue();//���캯��
	~LinkQueue();//��������
	bool isEmpty();
	bool en(T dat);
	bool de(T *dat);
	void clear();
private:
	int size;			//���д�С
	LinkNode<T> *front;	//��ͷ
	LinkNode<T> *rear;	//��β
};

/************************ ˳��ѭ������ ***********************************/
/************************************************************************
 *���ܣ����캯������������
 *���룺��
 *�������
 *���أ���
************************************************************************/
template <typename T>
Queue<T>::Queue(int _size)
{
	size = _size + 1;//���1��Ϊ����ͷ
	qu = new T[size];
	front = rear = 0;
}
/************************************************************************
 *���ܣ��������������ٶ���
 *���룺��
 *�������
 *���أ���
************************************************************************/
template <typename T>
Queue<T>::~Queue()
{
	delete []qu;
	qu = NULL;
}
/************************************************************************
 *���ܣ������Ƿ�Ϊ��
 *���룺��
 *�������
 *���أ��շ���TRUE;�ǿշ���FALSE
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
 *���ܣ������Ƿ�Ϊ��
 *���룺��
 *�������
 *���أ�������TRUE;δ������FALSE
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
 *���ܣ�������
 *���룺dat:�����е�����
 *�������
 *���أ�TRUE or FLASE
************************************************************************/
template <typename T>
bool Queue<T>::en(T dat)
{
	if(isFull())
	{
		printf("��������\r\n");
		return FALSE;
	}
	else
	{
		qu[rear] = dat;//��β��������
		rear = (rear+1)%size;//ѭ�����
		return TRUE;
	}
}

/************************************************************************
 *���ܣ�������
 *���룺��
 *�����dat:�����е�����
 *���أ�TRUE or FLASE
************************************************************************/
template <typename T>
bool Queue<T>::de(T *dat)
{
	if(isEmpty())
	{
		printf("����Ϊ��\r\n");
		return FALSE;
	}
	else
	{
		*dat = qu[front];
		front = (front+1)%(size);//ѭ�����
		return TRUE;
	}
}

/************************************************************************
 *���ܣ���ն���
 *���룺��	
 *�������
 *���أ���
************************************************************************/
template <typename T>
void Queue<T>::clear()
{
	front = rear = 0;
}


/************************ ��ʽ���� ***********************************/
/************************************************************************
 *���ܣ����캯����������ʽ����
 *���룺��
 *�������
 *���أ���
************************************************************************/
template <typename T>
LinkQueue<T>::LinkQueue()
{
	size = 0;
	front = rear = NULL;
}
/************************************************************************
 *���ܣ�����������������ʽ����
 *���룺��
 *�������
 *���أ���
************************************************************************/
template <typename T>
LinkQueue<T>::~LinkQueue()
{
	clear();
}
/************************************************************************
 *���ܣ������Ƿ�Ϊ��
 *���룺��
 *�������
 *���أ��շ���TRUE;�ǿշ���FALSE
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
 *���ܣ�������
 *���룺dat:�����е�����
 *�������
 *���أ�TRUE or FLASE
************************************************************************/
template <typename T>
bool LinkQueue<T>::en(T dat)
{
	LinkNode<T> *temp;

	temp = new LinkNode<T>(dat, NULL);//�����½ڵ�,����ֵ
	if(temp == NULL)
	{
		printf("�����ڴ�ʧ��r\n");
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
 *���ܣ�������
 *���룺��
 *�����dat:�����е�����
 *���أ�TRUE or FLASE
************************************************************************/
template <typename T>
bool LinkQueue<T>::de(T *dat)
{
	LinkNode<T> *temp;

	if(isEmpty())
	{
		printf("����Ϊ��\r\n");
		return FALSE;
	}
	*dat = front->data;//ȡ����
	temp = front;
	front = front->next;
	delete temp;								//�ͷ�ȡ���Ľڵ�
	temp = NULL;
	if(front == NULL)
		rear = NULL;
	size --;
	return TRUE;
}
/************************************************************************
 *���ܣ���ն���
 *���룺��
 *�������
 *���أ���
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
	printf("��ն��гɹ�\r\n");
}


void testQueue(void);
void testLinkQueue(void);

#endif