#ifndef __QUEUE_H__
#define __QUEUE_H__
#include "type.h"
#include "linkedlist_single.h"

template <typename T>
class Queue
{
public:
	Queue(int _size);//���캯��
	~Queue();//��������
	bool isEmpty();
	bool isFull();
	//bool Create(, int size, uint datlen);
	bool en(T dat);
	bool de(T *dat);
	void clear();
	//void Destroy();
private:
	int size;//���д�С
	int front;//��ͷ
	int rear;//��β
	T *qu;//����������
};

/*��ʽ���нڵ�ṹ��*/
/*typedef struct LinkQueueNode
{
	void *data;
	struct LinkQueueNode* next;
}LinkQueueNode_t;*/
/* ��ʽ������ */
template <typename T>
class LinkQueue:public LinkNode<T>
{
public:
	LinkQueue();//���캯��
	~LinkQueue();//��������
	bool isEmpty();
	//void Create(int datlen);//���캯������
	bool en(T dat);
	bool de(T *dat);
	void clear();
	//void Destroy();//�����������ٶ���
private:
	int size;			//���д�С
	LinkNode<T> *front;	//��ͷ
	LinkNode<T> *rear;	//��β
};


void testQueue(void);
void testLinkQueue(void);

#endif