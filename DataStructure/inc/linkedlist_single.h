#ifndef __LINK_H__
#define __LINK_H__
#include "type.h"
#include <iostream>
#include <string.h>
using namespace std;

/************************************************************************
 *����ڵ���ģ��
************************************************************************/
template <typename T>
class LinkNode
{
public:
	LinkNode(const T info, /*const*/ LinkNode<T> *nextValue = NULL)//���������Ĺ��캯��
	{
		data = info;
		next = nextValue;
	}
	LinkNode(/*const*/ LinkNode<T> *nextValue = NULL)//1�������Ĺ��캯��
	{
		next = nextValue;
	}
	~LinkNode(){};//��������
	T data;
	LinkNode<T> *next;
};
/************************************************************************
 *������ģ��
************************************************************************/
template <typename T>
class Link:public LinkNode<T>//���м̳�LinkNode��
{
public:
	Link();//���캯��
	~Link();//��������
	bool isEmpty();
	bool changeNodeValue(int n, T dat);
	bool traverse();
	bool insertNode(int n, T dat);
	bool insertNode(T dat);//��β����
	bool getNodeValue(int n, T *dat);
	bool deleteNode(int n);
	bool deleteNode();//ɾ����β�ڵ�
	bool clear();
	bool reverse();
private:
	LinkNode<T> *head, *tail;//�������ͷβָ��
};

/************************************************************************
 *���ܣ����캯������ʼ������
 *���룺
 *�����
 *���أ�
************************************************************************/
template <typename T>
Link<T>::Link()
{
	head = tail = new LinkNode<T>(NULL);
	cout << "Link()" << endl;
}
/************************************************************************
 *���ܣ��������������������ͷŸ����ڵ�
 *���룺
 *�����
 *���أ�
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
 *���ܣ��ж������Ƿ�Ϊ��
 *���룺
 *�������
 *���أ�TRUE or FALSE
************************************************************************/
template <typename T>
bool Link<T>::isEmpty()
{
	if(head->next == NULL)
	{
		cout << "�����" <<endl;
		return TRUE;
	}
	else
		return FALSE;
}

/************************************************************************
 *���ܣ��޸Ľڵ�n��ֵ
 *���룺n:��n���ڵ�,n��0��ʼ�㡣ֻ����ͨ�ڵ�
 *		dat:�޸ĺ��ֵ
 *�������
 *���أ�TRUE or FALSE
************************************************************************/
template <typename T>
bool Link<T>::changeNodeValue(int n, T dat)
{
	LinkNode<T> *t;
	cout << "�޸Ľڵ�" << n << "��ֵ" << endl;
	if(isEmpty())
		return FALSE;
	t = head->next;
	while(t != NULL && n--)								//�ҵ���n���ڵ�
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
		cout << "�ڵ㲻���ڣ�" << endl;;
		return FALSE;
	}
}

/************************************************************************
 *���ܣ������ڵ�
 *���룺��
 *�������
 *���أ�TRUE or FALSE
************************************************************************/
template <typename T>
bool Link<T>::traverse()
{
	LinkNode<T> *p;

	cout << "��������" << endl;
	if(isEmpty())
	{
		return FALSE;
	}
	p = head->next;
	while(p != NULL)
	{
		cout << p->data << endl;
		p = p->next;								//ָ����һ���ڵ�
	}
	return TRUE;
}

/************************************************************************
 *���ܣ��ڵ�n���ڵ�ǰ����ڵ㣬�ڵ��0��ʼ�㣬ֻ����ͨ�ڵ�
 *���룺n:��n���ڵ�
 *		dat:�����ֵ
 *�������
 *���أ�TRUE or FALSE
************************************************************************/
template <typename T>
bool Link<T>::insertNode(int n, T dat)
{
	LinkNode<T> *p;
	LinkNode<T> *in;									//�²���ڵ�

	cout << "�ڽڵ�" << n << "ǰ�����½ڵ�" << endl;
	if(isEmpty())
		return FALSE;
	p = head;										//����ָ��ָ���׽ڵ�
	while(p != NULL && n--)							//��λ����n���ڵ㣬�ڴ˽ڵ�ǰ�����½ڵ�
	{
		p = p->next;
	}
	if(p != NULL)
	{
		in = new LinkNode<T>(dat, p->next);//Ϊ�²���ڵ�����ڴ�,����ֵ
		if(in == NULL)
		{
			cout << "�ռ����ʧ��" << endl;
			return FALSE;
		}
		p->next = in;								//Դ�ڵ�ָ���²���ڵ�
		if(p == tail)								//����β����
			tail = in;
		return TRUE;
	}
	else
	{
		cout << "�ڵ㲻����!" << endl;
		return FALSE;
	}
}
/************************************************************************
 *���ܣ���β�ڵ�����ڵ�
 *���룺dat:�����ֵ
 *�������
 *���أ�TRUE or FALSE
************************************************************************/
template <typename T>
bool Link<T>::insertNode(T dat)
{
	LinkNode<T> *in;									//�²���ڵ�

	cout << "����β�����½ڵ�" << endl;
	in = new LinkNode<T>(dat, tail->next);//Ϊ�²���ڵ�����ڴ�,����ֵ
	if(in == NULL)
	{
		cout << "�ռ����ʧ��" << endl;
		return FALSE;
	}
	tail->next = in;								//Դ�ڵ�ָ���²���ڵ�
	tail = in;
	return TRUE;
}

/************************************************************************
 *���ܣ���ȡ��n���ڵ�����ݣ��ڵ��0��ʼ�㣬ֻ����ͨ�ڵ�
 *���룺n:��n���ڵ�
 *		dat:��ȡ��ֵ
 *�������
 *���أ�TRUE or FALSE
************************************************************************/
template <typename T>
bool Link<T>::getNodeValue(int n, T *dat)
{
	LinkNode<T> *p;

	if(isEmpty())
		return FALSE;
	p = head->next;									//����LinkNode_t��ָ��ָ���׽ڵ�
	while(p != NULL && n--)							//��λ����n���ڵ㣬�ڴ˽ڵ�ǰ�����½ڵ�
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
		cout << "�ڵ㲻���ڣ�" << endl;
		return FALSE;
	}
}

/************************************************************************
 *���ܣ�ɾ����n���ڵ㣬n��0��ʼ�㣬ֻ����ͨ�ڵ�
 *���룺n:��n���ڵ�,��0��ʼ��
 *�������
 *���أ���
************************************************************************/
template <typename T>
bool Link<T>::deleteNode(int n)
{
	LinkNode<T> *p, *pre;
	
	cout << "��" << n << "���ڵ㽫��ɾ��" << endl;
	if(isEmpty())
		return FALSE;
	pre = head;										//��¼Ҫɾ���ڵ��ǰһ���ڵ�
	p = head->next;									//����ָ��ָ���׽ڵ�
	while(p != NULL && n--)							//�ƶ�����n���ڵ㣬ɾ��
	{
		pre = p;
		p = p->next;
	}
	if(p != NULL)
	{
		pre->next = p->next;
		if(p == tail)
			tail = pre;
		delete p;									//�ͷŽڵ����
		p = NULL;
	}
	else
	{
		cout << "��ɾ���ڵ㲻���ڣ�" << endl;
		return FALSE;
	}
	return TRUE;
}
/************************************************************************
 *���ܣ�ɾ��β�ڵ�
 *���룺��
 *�������
 *���أ���
************************************************************************/
template <typename T>
bool Link<T>::deleteNode()
{
	LinkNode<T> *p, *pre;
	
	cout << "ɾ��β�ڵ�" << endl;
	if(isEmpty())
		return FALSE;
	pre = head;										//��¼Ҫɾ���ڵ��ǰһ���ڵ�
	p = head->next;									//����ָ��ָ���׽ڵ�
	while(p->next != NULL)								//�ƶ�����β��ɾ��
	{
		pre = p;
		p = p->next;
	}
	tail = pre;
	pre->next = p->next;
	delete p;									//�ͷŽڵ����
	p = NULL;
	return TRUE;
}

/************************************************************************
 *���ܣ������������
 *���룺
 *�������
 *���أ�TRUE or FALSE
************************************************************************/
template <typename T>
bool Link<T>::clear()
{
	LinkNode<T> *p;
	
	if(isEmpty())
		return FALSE;
	p = head->next;									//ָ���һ����ͨ�ڵ�
	while(p != NULL)								//ÿ���ڵ㰤��ɾ��
	{
		head->next = p->next;						//ͷ�ڵ�ָ����һ���ڵ�
		delete p;									//�ͷŵ�ǰ�ڵ��ڴ�
		p = head->next;							
	}
	if(p == NULL)
	{
		cout << "�������ɹ���" << endl;
		tail = head;
		return TRUE;
	}
	return FALSE;
}

/************************************************************************
 *���ܣ���ת��������
 *���룺��
 *�������
 *���أ���
************************************************************************/
template <typename T>
bool Link<T>::reverse()
{
	LinkNode<T> *currNode;							//��ǰҪ�嵽head�����node
	LinkNode<T> *nextNode;							//����ڵ�ǰ�ڵ����һ���ڵ�
	LinkNode<T> *preNode;							//����ڵ�ǰ�ڵ����һ���ڵ�
	LinkNode<T> *headNode;							//ͷ���

	cout << "��ת��������" << endl;
	if(isEmpty())
		return FALSE;
	headNode = head;
	preNode = head->next;
	currNode = preNode->next;
	while(currNode != NULL)
	{
		nextNode = currNode->next;					//����next�ڵ�
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