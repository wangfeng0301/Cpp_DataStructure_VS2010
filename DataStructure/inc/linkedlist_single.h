#ifndef __LINK_H__
#define __LINK_H__
#include "type.h"

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
	//bool isExist();//ʵ��������������Ȼ����
	bool isEmpty();
	//bool create(int n);//ʵ���������ڹ��캯���оʹ���������
	bool changeNodeValue(int n, T dat);
	bool traverse();
	bool insertNode(int n, T dat);
	bool insertNode(T dat);//��β����
	bool getNodeValue(int n, T *dat);
	bool deleteNode(int n);
	bool deleteNode();//ɾ����β�ڵ�
	bool clear();
	//bool destroy();//����������������
	bool reverse();
private:
	LinkNode<T> *head, *tail;//�������ͷβָ��
};

void testLink(void);

#endif