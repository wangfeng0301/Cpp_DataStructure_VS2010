#ifndef __STACK_H__
#define __STACK_H__
#include "type.h"
#include "linkedlist_single.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

/* ջ */
template <typename T>
class Stack
{
public:
	Stack(int _size);//���캯��
	~Stack();//��������
	bool isEmpty();
	bool isFull();
	bool push(T dat);
	bool pop(T *dat);
	bool getTop(T *dat);
	bool clear();//���ջ
	int getSize();
private:
	int size;	//ջ�Ĵ�С
	int top;	//ջ��
	T *st;	//���ջԪ�ص�����
};


/* ��ʽջ�࣬ջ�ռ���������� */
template <typename T>
class LinkStack:public LinkNode<T>//���м̳�LinkNode��
{
public:
	LinkStack();//���캯��
	~LinkStack();//��������
	bool isEmpty();
	bool push(T dat);
	bool pop(T *dat);
	bool getTop(T *dat);
	bool clear();
	int getSize();
private:
	LinkNode<T> *top;//ջ��
	int size;	//ջ��С
};

/************************˳��ջ������ȳ�***********************************/
/************************************************************************
 *���ܣ����캯��������ջ
 *���룺size:ջ�Ĵ�С
 *�������
 *���أ���
************************************************************************/
template <typename T>
Stack<T>::Stack(int _size)
{
	size = _size;
	top = -1;
	st = new T[size];
}
/************************************************************************
 *���ܣ���������������ջ
 *���룺��
 *�������
 *���أ���
************************************************************************/
template <typename T>
Stack<T>::~Stack()
{
	delete []st;
	st = NULL;
}

/************************************************************************
 *���ܣ��ж�ջ�Ƿ��
 *���룺��
 *�������
 *���أ�ջ�շ���TRUE;�ǿշ���FALSE
************************************************************************/
template <typename T>
bool Stack<T>::isEmpty()
{
	if(top > (-1))
		return FALSE;
	//else
		//cout << "ջ��" << endl;
	return TRUE;
}
/************************************************************************
 *���ܣ��ж�ջ�Ƿ���
 *���룺�� 
 *�������
 *���أ���TRUE�� δ��FALSE
************************************************************************/
template <typename T>
bool Stack<T>::isFull()
{
	if(top < size-1)//ջ��С��ջ��������
		return FALSE;
	//else
	//	printf("ջ��\r\n");
	
	return TRUE;
}
/************************************************************************
 *���ܣ�ѹջ
 *���룺dat:ѹջ����
 *�������
 *���أ�TRUE or FALSE
************************************************************************/
template <typename T>
bool Stack<T>::push(T dat)
{
	if(isFull())
		return FALSE;
	top ++;//ջ����1
	st[top] = dat;
	return TRUE;
}

/************************************************************************
 *���ܣ���ջ
 *���룺dat:��ջ����
 *�������
 *���أ�TRUE or FALSE
************************************************************************/
template <typename T>
bool Stack<T>::pop(T *dat)
{
	if(isEmpty())
		return FALSE;
	*dat = st[top];
	top --;
	return TRUE;
}

/************************************************************************
 *���ܣ���ȡջ��Ԫ��ֵ����������
 *���룺dat:��ջ����
 *�������
 *���أ�TRUE or FALSE
************************************************************************/
template <typename T>
bool Stack<T>::getTop(T *dat)
{
	if(isEmpty())
		return FALSE;
	*dat = st[top];
	return TRUE;
}
/************************************************************************
 *���ܣ����ջ
 *���룺��
 *�������
 *���أ�TRUE or FALSE
************************************************************************/
template <typename T>
bool Stack<T>::clear()
{
	top = -1;
	return TRUE;
}

/************************************************************************
 *���ܣ���ȡջ��Ԫ�ظ���
 *���룺�� 
 *�������
 *���أ�ջ��Ԫ�ظ���
************************************************************************/
template <typename T>
int Stack<T>::getSize()
{
	return top + 1;
}



/***************************��ʽջ*************************************/
/************************************************************************
 *���ܣ����캯��������ջ
 *���룺��
 *�������
 *���أ���
************************************************************************/
template <typename T>
LinkStack<T>::LinkStack()
{
	size = 0;
	top = NULL;
	cout << "LinkStack()" << endl;
}
/************************************************************************
 *���ܣ���������������ջ
 *���룺��
 *�������
 *���أ���
************************************************************************/
template <typename T>
LinkStack<T>::~LinkStack()
{
	clear();
	cout << "~LinkStack()" << endl;
}
/************************************************************************
 *���ܣ��ж�ջ�Ƿ��
 *���룺��
 *�������
 *���أ���TRUE���ǿ�FALSE
************************************************************************/
template <typename T>
bool LinkStack<T>::isEmpty()
{
	if(size > 0)
		return FALSE;
	else
		printf("ջ��\r\n");
	return TRUE;
}

/************************************************************************
 *���ܣ�ѹջ,����ײ���ڵ㣬��Ϊ����ڵ�
 *���룺dat:ѹջ����
 *�������
 *���أ�TRUE or FALSE
************************************************************************/
template <typename T>
bool LinkStack<T>::push(T dat)
{
	LinkNode<T> *temp = new LinkNode<T>(dat, top);//ʵ�������󲢸�ֵ
	if(temp == NULL)
	{
		cout << "����ռ�ʧ��" <<endl;
		return FALSE;
	}
	top = temp;
	size ++;
	return TRUE;
}

/************************************************************************
 *���ܣ���ջ
 *���룺dat:��ջ����
 *�������
 *���أ�TRUE or FALSE
************************************************************************/
template <typename T>
bool LinkStack<T>::pop(T *dat)
{
	LinkNode<T> *tempNode;					//��ʱ�ڵ�

	if(isEmpty())
		return FALSE;
	*dat = top->data;					//��ȡԪ��
	tempNode = top;
	top = top->next;
	delete tempNode;
	tempNode = NULL;
	size --;
	return TRUE;
}

/************************************************************************
 *���ܣ���ȡջ��Ԫ�أ�����ջ
 *���룺dat:��ջ����
 *�������
 *���أ�TRUE or FALSE
************************************************************************/
template <typename T>
bool LinkStack<T>::getTop(T *dat)
{
	//LinkNode<T> *tempNode;					//��ʱ�ڵ�

	if(isEmpty())
		return FALSE;
	*dat = top->data;					//��ȡԪ��
	return TRUE;
}

/************************************************************************
 *���ܣ����ջ
 *���룺��
 *�������
 *���أ�TRUE or FALSE
************************************************************************/
template <typename T>
bool LinkStack<T>::clear()
{
	LinkNode<T> *temp;

	if(isEmpty())
		return FALSE;
	while(top != NULL)
	{
		temp = top->next;
		delete top;
		top = temp;
	}
	size = 0;
	printf("��ջ�ɹ���\r\n");
	return TRUE;
}



void testStack(void);
void testLinkStack(void);

#endif