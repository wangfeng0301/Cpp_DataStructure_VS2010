#ifndef __SORT_H__
#define __SORT_H__
#include "type.h"

/*记录(节点)结构体*/
typedef struct
{
	int SortKey;
	int next;
}Record;

/*堆结构体*/
typedef struct 
{
	Record *heapArray;								//存放堆数据的数组
	int CurrentSize;								//当前堆中元素数目
	int MaxSize;									//堆的最大元素数目
}SortHeap;

/*静态队列结构体*/
typedef struct  
{
	int head;
	int tail;
}StaticQueue;

void testSort(void);
#endif