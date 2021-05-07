#ifndef __STACK_H__
#define __STACK_H__
#include "type.h"
#include "linkedlist_single.h"

/* 栈 */
template <typename T>
class Stack
{
public:
	Stack(int _size);//构造函数
	~Stack();//析构函数
	//bool isExist(Stack_t *s);//实例化对象即存在栈
	bool isEmpty();
	bool isFull();
	//bool Create(, int size, uint datlen);//创建栈//构造函数创建栈
	bool push(T dat);
	bool pop(T *dat);
	bool getTop(T *dat);
	bool clear();//清空栈
	int getSize();
	//bool Stack_Destroy(Stack_t *s);//析构函数销毁
private:
	int size;	//栈的大小
	int top;	//栈顶
	T *st;	//存放栈元素的数组
};

/* 链式栈节点结构体 */
//typedef struct LinkStackNode
//{
//	void *data;	//节点数据类型不定
//	struct LinkStackNode *next;
//}LinkStackNode_t;

/* 链式栈类，栈空间由链表组成 */
template <typename T>
class LinkStack:public LinkNode<T>//公有继承LinkNode类
{
public:
	LinkStack();//构造函数
	~LinkStack();//析构函数
	bool isEmpty();
	//bool Create(, uint datlen);//构造函数创建
	bool push(T dat);
	bool pop(T *dat);
	bool getTop(T *dat);
	bool clear();
	int getSize();
	//bool Destroy();//析构函数销毁
private:
	LinkNode *top;//栈顶
	int size;	//栈大小
};

void testStack(void);
void testLinkStack(void);

#endif