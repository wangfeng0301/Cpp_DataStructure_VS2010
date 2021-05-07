/*********************************************************************
*栈：包括创建栈、出栈、压栈、清空栈
*链式栈：包括创建栈、出栈、压栈、清空栈等
*参考资料：《数据结构与算法》张铭，王腾蛟，赵海燕等
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
 *功能：创建栈
 *输入：s：栈指针 
 *		size:栈的大小
 *		datlen:栈元素数据类型大小
 *输出：无
 *返回：TRUE or FALSE
************************************************************************/
/*bool Stack_Create(Stack_t *s, int size, uint datlen)
{
	 s->size = size;
	 s->top = -1;							//栈顶，也表示当前栈中元素的个数减1
	 s->st = (void *)malloc(size*datlen);	//开辟size个字节空间
	 s->stlen = datlen;
	 return TRUE;
}*/
/************************************************************************
 *功能：判断栈是否存在
 *输入：s：栈指针 
 *输出：无
 *返回：TRUE or FALSE
************************************************************************/
/*bool Stack_IsExist(Stack_t *s)
{
	if(s->st == NULL)
	{
		printf("栈不存在\r\n");
		return FALSE;
	}
	return TRUE;
}*/
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
	else
		cout << "栈空" << endl;
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
	else
		printf("栈满\r\n");
	
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

/************************************************************************
 *功能：销毁栈
 *输入：s：栈指针 
 *输出：无
 *返回：TRUE or FALSE
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
 *功能：创建栈,链式栈不用提前开辟大小，可以在压栈时动态开辟空间
 *输入：s：栈指针 
 *输出：无
 *返回：无
************************************************************************/
/*bool LinkStack_Create(LinkStack_t *s, uint datlen)
{
	s->size = 0;//初始化为空栈
	s->top = NULL;//指向空
	s->datlen = datlen;
	return TRUE;
}*/
/************************************************************************
 *功能：压栈,向表首插入节点，作为后入节点
 *输入：dat:压栈数据
 *输出：无
 *返回：TRUE or FALSE
************************************************************************/
template <typename T>
bool LinkStack<T>::push(T dat)
{
	LinkNode *temp = new LinkNode<T>(dat, top);//实例化对象并赋值
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
	LinkNode *tempNode;					//临时节点

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
	LinkNode *tempNode;					//临时节点

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
	printf("清栈成功！\r\n");
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
			cout << "栈中剩余节点数量：" << s.getSize() << endl;
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

	cout << "出栈：" << endl;
	for(int i = 0;i<2;i++)
	{
		linkstack.pop(&dat);
		cout << "data->[] = " << dat << endl;	
	}
	linkstack.clear();
	if(linkstack.pop(&dat))
		cout << dat << endl;
}