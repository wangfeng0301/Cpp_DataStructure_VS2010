#ifndef __HEAP_H__
#define __HEAP_H__
#include "type.h"

/*堆节点结构体*/
typedef struct  
{
	int key;			//节点键值
	void *dat;			//节点其他数据
}HeapNode_t;
/*堆结构体*/
typedef struct 
{
	HeapNode_t *array;	//存放堆节点的数组
	uint currsize;		//当前堆中元素数目
	uint maxsize;		//堆的最大元素数目
	uint datlen;		//HeapNode_t中数据的长度
}Heap_t;

bool MinHeap_IsFull(Heap_t *heap);
bool MinHeap_IsEmpty(Heap_t *heap);
void MinHeap_SiftDown(Heap_t *heap, uint parent);
void MinHeap_SiftUp(Heap_t *heap, uint pos);
//bool MinHeap_Create(Heap_t *heap, int *data, int size, int maxsize);
bool MinHeap_Create(Heap_t *heap, void *dat, uint datlen, int *key, int size, int maxsize);
//bool MinHeap_Insert(Heap_t *heap,int node);
bool MinHeap_Insert(Heap_t *heap, uint key, void *dat);
//bool MinHeap_RemoveMin(Heap_t *heap, int *node);
bool MinHeap_RemoveMin(Heap_t *heap, HeapNode_t *node);
//bool MinHeap_Remove(Heap_t *heap, int *node, int pos);
bool MinHeap_Remove(Heap_t *heap, HeapNode_t *node, uint pos);
void MinHeap_Traverse(Heap_t *heap);
void MinHeap_Destroy(Heap_t *heap);

bool MaxHeap_IsFull(Heap_t *heap);
bool MaxHeap_IsEmpty(Heap_t *heap);
void MaxHeap_SiftDown(Heap_t *heap, uint parent);
void MaxHeap_SiftUp(Heap_t *heap, uint pos);
//bool MaxHeap_Create(Heap_t *heap, int *data, int size, int maxsize);
bool MaxHeap_Create(Heap_t *heap, void *dat, uint datlen, uint *key, int size, uint maxsize);
//bool MaxHeap_Insert(Heap_t *heap,int node);
bool MaxHeap_Insert(Heap_t *heap,uint key, void *dat);
//bool MaxHeap_RemoveMax(Heap_t *heap, int *node);
bool MaxHeap_RemoveMax(Heap_t *heap, HeapNode_t *node);
//bool MaxHeap_Remove(Heap_t *heap, int *node, int pos);
bool MaxHeap_Remove(Heap_t *heap, HeapNode_t *node, uint pos);
void MaxHeap_Traverse(Heap_t *heap);
void MaxHeap_Destroy(Heap_t *heap);


void testHeap(void);

#endif