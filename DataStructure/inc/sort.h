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
	void quickSort(Record<T> *Array, int start, int end);
	void quickSort(Record<T> *Array, int n);
	void insertSort(Record<T> *Array, int n);
	void shellSort(Record<T> *Array, int n);
	void selectSort(Record<T> *arr,int n);
	void heapSort(Record<T> *arr,int n);
	void mergeSort(Record<T> *arr,Record<T> *temparr,int left,int right);
	void modMergeSort(Record<T> *arr,Record<T> *temparr,int left,int right);
	void BucketSort(Record<T> *arr,int n,int max);
private:
	void swap(Record<T> *record1, Record<T> *record2);
	void modQuickSort(Record<T> *arr,int start, int end);
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
/*************************************************************************
 *快速排序法:时间复杂度：nlogn，不稳定
 *输入：Array  要排序的数据
 *		start 数据开始下标
 *		end  数据结束下标
 *返回：无
 *************************************************************************/
template <typename T>
void Sort<T>::quickSort(Record<T> *Array, int start, int end)
{
	/* 取第一个数作为基准数 */
	Record<T> mid = Array[start];
	int low,high;

	/* start和end碰头了，排序结束，退出递归 */
	if(start >= end)
		return;

	/* low来标记左侧从基准数开始找比mid大的数的位置 */
	/* high来标记右侧end向左找比mid小的数的位置 */
	low = start;
	high = end;

	/* 进行循环，只要low和high没有碰头就一直进行,当low和high相等说明碰头了 */
	while(low < high)
	{
		/* 从high开始向左，找到第一个比mid小或者等于mid的数，标记位置,（如果high的数比mid大，我们就左移high）*/
		/* 并且我们要确定找到之前，如果low和high碰头了，也不找了 */
		while(Array[high].key > mid.key && (low < high))
			high--;

		/* 从low开始向右，找到第一个比mid大的数，标记位置,（如果low的数比mid小，我们就右移low） */
		/* 并且我们要确定找到之前，如果low和high碰头了，也不找了 */
		while((Array[low].key <= mid.key) && (low < high))
			low++;

		/* 找到两个标记后，交换 */
		swap(&Array[low],&Array[high]);
	}
	swap(&Array[start],&Array[low]);

	quickSort(Array,start,low-1);//递归调用
	quickSort(Array,low+1,end);
}

/*************************************************************************
 *快速排序法（优化）:时间复杂度：nlogn，不稳定
 *输入：Array  要排序的数据
 *		start 数据开始下标
 *		end  数据结束下标
 *返回：无
 *************************************************************************/
#define THRESHOLD 28
template <typename T>
void Sort<T>::modQuickSort(Record<T> *Array, int start, int end)
{
	if(end - start + 1 > THRESHOLD)
	{
		/* 取第一个数作为基准数 */
		Record<T> mid = Array[start];
		int low,high;

		/* start和end碰头了，排序结束，退出递归 */
		if(start >= end)
			return;

		/* low来标记左侧从基准数开始找比mid大的数的位置 */
		/* high来标记右侧end向左找比mid小的数的位置 */
		low = start;
		high = end;

		/* 进行循环，只要low和high没有碰头就一直进行,当low和high相等说明碰头了 */
		while(low < high)
		{
			/* 从high开始向左，找到第一个比mid小或者等于mid的数，标记位置,（如果high的数比mid大，我们就左移high）*/
			/* 并且我们要确定找到之前，如果low和high碰头了，也不找了 */
			while(Array[high].key > mid.key && (low < high))
				high--;

			/* 从low开始向右，找到第一个比mid大的数，标记位置,（如果low的数比mid小，我们就右移low） */
			/* 并且我们要确定找到之前，如果low和high碰头了，也不找了 */
			while((Array[low].key <= mid.key) && (low < high))
				low++;

			/* 找到两个标记后，交换 */
			swap(&Array[low],&Array[high]);
		}
		swap(&Array[start],&Array[low]);

		modQuickSort(Array,start,low-1);//递归调用
		modQuickSort(Array,low+1,end);
	}
}
/*************************************************************************
 *快速排序法（优化）:时间复杂度：nlogn，不稳定
 *输入：Array  要排序的数据
 *		n 数据长度
 *返回：无
 *************************************************************************/
template <typename T>
void Sort<T>::quickSort(Record<T> *Array, int n)
{
	modQuickSort(Array, 0, n-1);
	insertSort(Array, n);
}
/*************************************************************************
 *直接插入排序法：时间复杂度：n^2
 *稳定性：稳定
 *思想：1.从第2个数开始，依次选中作为要比较的值；
 *		2.以该值为最右，从右向左比较，如果左边值大，左值向右移，空出位置
 *		3.直到找到比该值小的数，或找到最左，结束
 *		4.选下一个要比较的值，重复2-3步，直到整个序列结束
 *输入：dat  要排序的数据
 *		len 数据长度
 *返回：无
 *************************************************************************/
template <typename T>
void Sort<T>::insertSort(Record<T> *Array, int n)
{
	Record<T> temp;
	int end;
	for(int i = 1;i < n;i++)
	{
		temp = Array[i];//保存每次要比较的值
		end = i-1;
		/* 向前比较，直到找到比自己小的，插入。一定是key<dat[end]，不能小于等于，否则不稳定 */
		while(end >= 0 && temp.key < Array[end].key)
		{
			/* 插入的方法为：将前一个值赋值到后一个值，最后将key值赋值到当前。完成插入 */
			Array[end+1] = Array[end];
			end--;
		}
		Array[end+1] = temp;
	}
}

/*************************************************************************
 *希尔排序法（直接插入排序法的优化）:时间复杂度：n^2
 *稳定性：不稳定
 *思想：1.分组
 *		2.对分组进行插入排序
 *		3.减小分组间距，减小序列个数
 *输入：dat  要排序的数据
 *		len 数据长度
 *返回：无
 *************************************************************************/
template <typename T>
void Sort<T>::shellSort(Record<T> *Array, int n)
{
	int gap = n/2;
	Record<T> temp;
	int end,i=0;

	for(gap;gap>0;gap/=2)//增量也可以取其他值
	{
		for(i = gap;i<n;i++)
		{
			temp = Array[i];
			end = i-gap;
			while(end >=0 && temp.key < Array[end].key)
			{
				Array[end+gap] = Array[end];
				end -= gap;
			}
			Array[end+gap] = temp;
		}	
	}
}
void testSort(void);
#endif