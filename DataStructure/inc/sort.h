#ifndef __SORT_H__
#define __SORT_H__
#include "type.h"
#include <iostream>
#include "heap.h"
using namespace std;

template <typename T>
class Record
{
public:
	Record();
	~Record();
	int key;										//键值，用来做排序比较
	T dat;											//数据
};
template <typename T>
class Sort:public Record<T>
{
public:
	Sort();
	~Sort();
	void insertSort(Record<T> *arr, int n);
	void modInsertSort(Record<T> *arr,int n,int delta);
	void shellSort(Record<T> *arr,int n);
	void selectSort(Record<T> *arr,int n);
	void heapSort(Record<T> *arr,int n);
	void bubbleSort(Record<T> *arr,int n);
	void quickSort(Record<T> *arr,int left,int right);
	void mergeSort(Record<T> *arr,Record<T> *temparr,int left,int right);
	void modMergeSort(Record<T> *arr,Record<T> *temparr,int left,int right);
	void BucketSort(Record<T> *arr,int n,int max);
};
///*记录(节点)结构体*/
//typedef struct
//{
//	int SortKey;
//	int next;
//}Record;
//
///*堆结构体*/
//typedef struct 
//{
//	Record *heapArray;								//存放堆数据的数组
//	int CurrentSize;								//当前堆中元素数目
//	int MaxSize;									//堆的最大元素数目
//}SortHeap;
//
///*静态队列结构体*/
//typedef struct  
//{
//	int head;
//	int tail;
//}StaticQueue;

void testSort(void);
#endif