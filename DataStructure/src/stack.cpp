/*********************************************************************
*ջ����������ջ����ջ��ѹջ�����ջ
*��ʽջ����������ջ����ջ��ѹջ�����ջ��
*�ο����ϣ������ݽṹ���㷨�������������ԣ��Ժ����
*wangfeng
*E-mail:fengwang0301@163.com
*CSDN:https://blog.csdn.net/u013073067?spm=1001.2101.3001.5343
*GitHub:https://github.com/wangfeng0301
*2021.5.3
**********************************************************************/
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
using namespace std;

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
 *���ܣ�����ջ
 *���룺s��ջָ�� 
 *		size:ջ�Ĵ�С
 *		datlen:ջԪ���������ʹ�С
 *�������
 *���أ�TRUE or FALSE
************************************************************************/
/*bool Stack_Create(Stack_t *s, int size, uint datlen)
{
	 s->size = size;
	 s->top = -1;							//ջ����Ҳ��ʾ��ǰջ��Ԫ�صĸ�����1
	 s->st = (void *)malloc(size*datlen);	//����size���ֽڿռ�
	 s->stlen = datlen;
	 return TRUE;
}*/
/************************************************************************
 *���ܣ��ж�ջ�Ƿ����
 *���룺s��ջָ�� 
 *�������
 *���أ�TRUE or FALSE
************************************************************************/
/*bool Stack_IsExist(Stack_t *s)
{
	if(s->st == NULL)
	{
		printf("ջ������\r\n");
		return FALSE;
	}
	return TRUE;
}*/
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
	else
		cout << "ջ��" << endl;
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
	else
		printf("ջ��\r\n");
	
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

/************************************************************************
 *���ܣ�����ջ
 *���룺s��ջָ�� 
 *�������
 *���أ�TRUE or FALSE
************************************************************************/
/*bool Stack_Destroy(Stack_t *s)
{
	if(!Stack_IsExist(s))
		return FALSE;
	s->size = 0;
	s->stlen = 0;
	s->top = 0;
	free(s->st);
	s->st = NULL;
	return TRUE;
}*/


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
 *���ܣ�����ջ,��ʽջ������ǰ���ٴ�С��������ѹջʱ��̬���ٿռ�
 *���룺s��ջָ�� 
 *�������
 *���أ���
************************************************************************/
/*bool LinkStack_Create(LinkStack_t *s, uint datlen)
{
	s->size = 0;//��ʼ��Ϊ��ջ
	s->top = NULL;//ָ���
	s->datlen = datlen;
	return TRUE;
}*/
/************************************************************************
 *���ܣ�ѹջ,����ײ���ڵ㣬��Ϊ����ڵ�
 *���룺dat:ѹջ����
 *�������
 *���أ�TRUE or FALSE
************************************************************************/
template <typename T>
bool LinkStack<T>::push(T dat)
{
	LinkNode *temp = new LinkNode<T>(dat, top);//ʵ�������󲢸�ֵ
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
	LinkNode *tempNode;					//��ʱ�ڵ�

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
	LinkNode *tempNode;					//��ʱ�ڵ�

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
	LinkNode *temp;

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
/*bool LinkStack_Destroy(LinkStack_t *s)
{
	return LinkStack_Clear(s);
}*/


void testStack(void)
{
	Stack<int> s(10);
	int dat;

	if(!s.push(10))
		printf("Stack_Create Error\r\n");
	if(!s.push(11))
		printf("Stack_Create Error\r\n");
	if(!s.push(12))
		printf("Stack_Create Error\r\n");
	if(!s.push(13))
		printf("Stack_Create Error\r\n");
	if(!s.push(14))
		printf("Stack_Create Error\r\n");
	for(int i = 0;i<3;i++)
	{
		if(s.pop(&dat))
		{
			cout <<  dat << endl;	
			cout << "ջ��ʣ��ڵ�������" << s.getSize() << endl;
		}
	}
	s.clear();
	s.isEmpty();
}

void testLinkStack(void)
{
	LinkStack<int> linkstack;
	int dat;

	//LinkStack_Create(&linkstack, sizeof(int));
	linkstack.push(10);
	linkstack.push(11);
	linkstack.push(12);
	linkstack.push(13);

	cout << "��ջ��" << endl;
	for(int i = 0;i<2;i++)
	{
		linkstack.pop(&dat);
		cout << "data->[] = " << dat << endl;	
	}
	linkstack.clear();
	if(linkstack.pop(&dat))
		cout << dat << endl;
}