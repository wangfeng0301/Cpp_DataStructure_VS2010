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
	Record(){};
	~Record(){};
	int key;										//键值，用来做排序比较
	T dat;											//数据
};
template <typename T>
class Sort:public Record<T>
{
public:
	Sort();
	~Sort();
	void bubbleSort(Record<T> *Array,int n, bool mode);
	void insertSort(Record<T> *arr, int n);
	void modInsertSort(Record<T> *arr,int n,int delta);
	void shellSort(Record<T> *arr,int n);
	void selectSort(Record<T> *arr,int n);
	void heapSort(Record<T> *arr,int n);
	void quickSort(Record<T> *arr,int left,int right);
	void mergeSort(Record<T> *arr,Record<T> *temparr,int left,int right);
	void modMergeSort(Record<T> *arr,Record<T> *temparr,int left,int right);
	void BucketSort(Record<T> *arr,int n,int max);
private:
	void swap(Record<T> *record1, Record<T> *record2);
};
/************************************************************************/
/* 功能：构造函数                                             
/* 输入：无
/* 输出：无
/* 返回：无
/************************************************************************/
template <typename T>
Sort<T>::Sort()
{

}
/************************************************************************/
/* 功能：析构函数                                             
/* 输入：无
/* 输出：无
/* 返回：无
/************************************************************************/
template <typename T>
Sort<T>::~Sort()
{

}
/************************************************************************/
/* 功能：交换数据                                             
/* 输入：无
/* 输出：无
/* 返回：无
/************************************************************************/
template <typename T>
void Sort<T>::swap(Record<T> *record1, Record<T> *record2)
{
	Record<T> temp;
	temp = *record1;
	*record1 = *record2;
	*record2 = temp;
}
/************************************************************************/
/* 冒泡排序:时间复杂度：n^2,稳定
/* 输入：Array：待排序数组
/*       n：数组长度
/*       mode:0：升序；1：降序
/* 输出：Array:排好序的数组
/* 返回：无
/************************************************************************/
template <typename T>
void Sort<T>::bubbleSort(Record<T> *Array, int n, bool mode)
{
	int i,j;
	Record<T> temp;
#if 0
	for(i = 0;i<n-1;i++)
	{
		for(j = 0;j<n-1-i;j++)
		{
			if(mode)
			{
				/*降序，注意这里一定是小于，不能是小于等于，否则排序不稳定*/
				if(Array[j].key < Array[j+1].key)
					swap(&Array[j], &Array[j+1]);
			}
			else
			{
				/*升序，注意这里一定是大于，不能是大于等于，否则排序不稳定*/
				if(Array[j].key > Array[j+1].key)
					swap(&Array[j], &Array[j+1]);
			}
		}
	}
#else
	/*另外一种冒泡排序方法，这种方式是将排好序的数据放在前面，*/
	/*上面那种方法是将排好序的数据放在后面*/
	/*这可能已经不是冒泡法了，因为没有相邻两两比较，后面查证，不过时间复杂度和稳定性是一样的*/
	for(i = 0;i<n-1;i++)
	{
		for(j = i+1;j<n;j++)
		{
			if(mode)
			{
				/*降序，注意这里一定是小于，不能是小于等于，否则排序不稳定*/
				if(Array[i].key < Array[j].key)
					swap(&Array[i], &Array[j]);
			}
			else
			{
				/*升序，注意这里一定是大于，不能是大于等于，否则排序不稳定*/
				if(Array[i].key > Array[j].key)
					swap(&Array[i], &Array[j]);
			}
		}
	}
#endif
}

void testSort(void);
#endif