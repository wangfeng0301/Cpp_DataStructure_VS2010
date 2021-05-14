#ifndef __STACK_H__
#define __STACK_H__
#include "type.h"
#include "linkedlist_single.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

/* 栈 */
template <typename T>
class Stack
{
public:
	Stack(int _size);//构造函数
	~Stack();//析构函数
	bool isEmpty();
	bool isFull();
	bool push(T dat);
	bool pop(T *dat);
	bool getTop(T *dat);
	bool clear();//清空栈
	int getSize();
private:
	int size;	//栈的大小
	int top;	//栈顶
	T *st;	//存放栈元素的数组
};


/* 链式栈类，栈空间由链表组成 */
template <typename T>
class LinkStack:public LinkNode<T>//公有继承LinkNode类
{
public:
	LinkStack();//构造函数
	~LinkStack();//析构函数
	bool isEmpty();
	bool push(T dat);
	bool pop(T *dat);
	bool getTop(T *dat);
	bool clear();
	int getSize();
private:
	LinkNode<T> *top;//栈顶
	int size;	//栈大小
};

/************************顺序栈：后进先出***********************************/
/************************************************************************
 *功能：构造函数，创建栈
 *输入：size:栈的大小
 *输出：无
 *返回：无
************************************************************************/
template <typename T>
Stack<T>::Stack(int _size)
{
	size = _size;
	top = -1;
	st = new T[size];
}
/************************************************************************
 *功能：析构函数，销毁栈
 *输入：无
 *输出：无
 *返回：无
************************************************************************/
template <typename T>
Stack<T>::~Stack()
{
	delete []st;
	st = NULL;
}

/************************************************************************
 *功能：判断栈是否空
 *输入：无
 *输出：无
 *返回：栈空返回TRUE;非空返回FALSE
************************************************************************/
template <typename T>
bool Stack<T>::isEmpty()
{
	if(top > (-1))
		return FALSE;
	//else
		//cout << "栈空" << endl;
	return TRUE;
}
/************************************************************************
 *功能：判断栈是否满
 *输入：无 
 *输出：无
 *返回：满TRUE， 未满FALSE
************************************************************************/
template <typename T>
bool Stack<T>::isFull()
{
	if(top < size-1)//栈顶小于栈的最大个数
		return FALSE;
	//else
	//	printf("栈满\r\n");
	
	return TRUE;
}
/************************************************************************
 *功能：压栈
 *输入：dat:压栈数据
 *输出：无
 *返回：TRUE or FALSE
************************************************************************/
template <typename T>
bool Stack<T>::push(T dat)
{
	if(isFull())
		return FALSE;
	top ++;//栈顶加1
	st[top] = dat;
	return TRUE;
}

/************************************************************************
 *功能：出栈
 *输入：dat:出栈数据
 *输出：无
 *返回：TRUE or FALSE
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
 *功能：获取栈顶元素值，但不弹出
 *输入：dat:出栈数据
 *输出：无
 *返回：TRUE or FALSE
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
 *功能：清空栈
 *输入：无
 *输出：无
 *返回：TRUE or FALSE
************************************************************************/
template <typename T>
bool Stack<T>::clear()
{
	top = -1;
	return TRUE;
}

/************************************************************************
 *功能：获取栈中元素个数
 *输入：无 
 *输出：无
 *返回：栈中元素个数
************************************************************************/
template <typename T>
int Stack<T>::getSize()
{
	return top + 1;
}



/***************************链式栈*************************************/
/************************************************************************
 *功能：构造函数，创建栈
 *输入：无
 *输出：无
 *返回：无
************************************************************************/
template <typename T>
LinkStack<T>::LinkStack()
{
	size = 0;
	top = NULL;
	cout << "LinkStack()" << endl;
}
/************************************************************************
 *功能：析构函数，销毁栈
 *输入：无
 *输出：无
 *返回：无
************************************************************************/
template <typename T>
LinkStack<T>::~LinkStack()
{
	clear();
	cout << "~LinkStack()" << endl;
}
/************************************************************************
 *功能：判断栈是否空
 *输入：无
 *输出：无
 *返回：空TRUE，非空FALSE
************************************************************************/
template <typename T>
bool LinkStack<T>::isEmpty()
{
	if(size > 0)
		return FALSE;
	else
		printf("栈空\r\n");
	return TRUE;
}

/************************************************************************
 *功能：压栈,向表首插入节点，作为后入节点
 *输入：dat:压栈数据
 *输出：无
 *返回：TRUE or FALSE
************************************************************************/
template <typename T>
bool LinkStack<T>::push(T dat)
{
	LinkNode<T> *temp = new LinkNode<T>(dat, top);//实例化对象并赋值
	if(temp == NULL)
	{
		cout << "申请空间失败" <<endl;
		return FALSE;
	}
	top = temp;
	size ++;
	return TRUE;
}

/************************************************************************
 *功能：出栈
 *输入：dat:出栈数据
 *输出：无
 *返回：TRUE or FALSE
************************************************************************/
template <typename T>
bool LinkStack<T>::pop(T *dat)
{
	LinkNode<T> *tempNode;					//临时节点

	if(isEmpty())
		return FALSE;
	*dat = top->data;					//提取元素
	tempNode = top;
	top = top->next;
	delete tempNode;
	tempNode = NULL;
	size --;
	return TRUE;
}

/************************************************************************
 *功能：获取栈顶元素，不出栈
 *输入：dat:出栈数据
 *输出：无
 *返回：TRUE or FALSE
************************************************************************/
template <typename T>
bool LinkStack<T>::getTop(T *dat)
{
	//LinkNode<T> *tempNode;					//临时节点

	if(isEmpty())
		return FALSE;
	*dat = top->data;					//提取元素
	return TRUE;
}

/************************************************************************
 *功能：清空栈
 *输入：无
 *输出：无
 *返回：TRUE or FALSE
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
	printf("清栈成功！\r\n");
	return TRUE;
}



void testStack(void);
void testLinkStack(void);

#endif