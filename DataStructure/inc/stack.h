#ifndef __STACK_H__
#define __STACK_H__
#include "type.h"
#include "linkedlist_single.h"

/* ջ */
template <typename T>
class Stack
{
public:
	Stack(int _size);//���캯��
	~Stack();//��������
	//bool isExist(Stack_t *s);//ʵ�������󼴴���ջ
	bool isEmpty();
	bool isFull();
	//bool Create(, int size, uint datlen);//����ջ//���캯������ջ
	bool push(T dat);
	bool pop(T *dat);
	bool getTop(T *dat);
	bool clear();//���ջ
	int getSize();
	//bool Stack_Destroy(Stack_t *s);//������������
private:
	int size;	//ջ�Ĵ�С
	int top;	//ջ��
	T *st;	//���ջԪ�ص�����
};

/* ��ʽջ�ڵ�ṹ�� */
//typedef struct LinkStackNode
//{
//	void *data;	//�ڵ��������Ͳ���
//	struct LinkStackNode *next;
//}LinkStackNode_t;

/* ��ʽջ�࣬ջ�ռ���������� */
template <typename T>
class LinkStack:public LinkNode<T>//���м̳�LinkNode��
{
public:
	LinkStack();//���캯��
	~LinkStack();//��������
	bool isEmpty();
	//bool Create(, uint datlen);//���캯������
	bool push(T dat);
	bool pop(T *dat);
	bool getTop(T *dat);
	bool clear();
	int getSize();
	//bool Destroy();//������������
private:
	LinkNode *top;//ջ��
	int size;	//ջ��С
};

void testStack(void);
void testLinkStack(void);

#endif