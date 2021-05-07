#ifndef __QUEUE_H__
#define __QUEUE_H__
#include "type.h"
#include "linkedlist_single.h"

template <typename T>
class Queue
{
public:
	Queue(int _size);//构造函数
	~Queue();//析构函数
	bool isEmpty();
	bool isFull();
	//bool Create(, int size, uint datlen);
	bool en(T dat);
	bool de(T *dat);
	void clear();
	//void Destroy();
private:
	int size;//队列大小
	int front;//队头
	int rear;//队尾
	T *qu;//数组存放数据
};

/*链式队列节点结构体*/
/*typedef struct LinkQueueNode
{
	void *data;
	struct LinkQueueNode* next;
}LinkQueueNode_t;*/
/* 链式队列类 */
template <typename T>
class LinkQueue:public LinkNode<T>
{
public:
	LinkQueue();//构造函数
	~LinkQueue();//析构函数
	bool isEmpty();
	//void Create(int datlen);//构造函数创建
	bool en(T dat);
	bool de(T *dat);
	void clear();
	//void Destroy();//析构函数销毁队列
private:
	int size;			//队列大小
	LinkNode<T> *front;	//队头
	LinkNode<T> *rear;	//队尾
};


void testQueue(void);
void testLinkQueue(void);

#endif