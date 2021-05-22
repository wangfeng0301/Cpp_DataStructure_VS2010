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
	void mergeSort(Record<T> *Array,int n);
	void mergeSort_Nor(Record<T> *Array,int n);
	void modMergeSort(Record<T> *Array,int n);
	void BucketSort(Record<T> *arr,int n,int max);
private:
	void swap(Record<T> *record1, Record<T> *record2);
	void modQuickSort(Record<T> *arr,int start, int end);
	void _mergeSort(Record<T> *Array,int left,int right,Record<T> *temp);
	void mergeData(Record<T> *Array,int left,int mid,int right,Record<T> *temp);
	void _modMergeSort(Record<T> *Array,Record<T> *TempArray,int left,int right);
	void modMergeData(Record<T> *Array,Record<T> *TempArray,int left,int right,int middle);
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
#if 1
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
	/*2021.5.22 这其实是直接选择排序*/
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

/*************************************************************************
 *直接选择排序：时间复杂度：n^2
 *思想：1.找出第i小的值，放到第i个位置
 *稳定性：不稳定
 *输入：dat  要排序的数据
 *		len 数据长度
 *返回：无
 *************************************************************************/
template <typename T>
void Sort<T>::selectSort(Record<T>* Array,int n)
{
#if 0
	/* 普通的直接选择排序 */
	int i,j,smallest;
	/* 外循环最后1次不用比较 */
	for(i = 0;i<n - 1;i++)
	{
		smallest = i;
		/* 内循环需要从选中的后一个开始比较到最后一个 */
		for(j = i+1;j<n;j++)
		{
			if(Array[j].key < Array[smallest].key)
				smallest = j;
		}
		/* 最小值的索引发生了变化才交换 */
		if(smallest != i)
			swap(&Array[smallest], &Array[i]);
	}
#else
	/* 改进的直接选择排序 */
	int i;
	int minIndex,maxIndex;
	int left=0,right=n-1;//左右索引号
	
	while(left < right)
	{
		minIndex = left;
		maxIndex = right;
		for(i = left;i<=right;i++)//找到最大最小值索引号
		{
			if(Array[minIndex].key > Array[i].key)
				minIndex = i;
			if(Array[maxIndex].key < Array[i].key)
				maxIndex = i;
		}
		/* 索引发生了变化才交换 */
		if(minIndex != left)
		{
			this->swap(&Array[minIndex], &Array[left]);
			if(maxIndex == left)
				maxIndex = minIndex;
		}
		if(maxIndex != right)
			this->swap(&Array[maxIndex], &Array[right]);

		left ++;
		right --;
	}
#endif
}

/*************************************************************************
 *堆排序(降序排列)：时间复杂度：nlogn
 *思想：1.对所有数据建立最大堆
 *		2.取出堆顶最大值与末端交换
 *		3.调整为最大堆，重复2-3
 *稳定性：不稳定
 *输入：arr:输入的数据；
 *		len:输入数据的数量；
 *输出：arr：重新排列的数据
 *返回：无
 *************************************************************************/
template <typename T>
void Sort<T>::heapSort(Record<T> *Array,int n)
{
	/* 构造最大堆 */
	MaxHeap<Record<T>> maxheap(n);
	for(int i = 0;i<n;i++)
		maxheap.insert(Array[i].key, Array[i]);
	
	/* 依次取出堆顶 */
	HeapNode<Record<T>> temp_node;
	for(int i = 0;i<n;i++)
	{
		maxheap.removeMax(&temp_node);
		Array[i] = temp_node.dat;
	}
}

/*************************************************************************
 *二路归并
 *输入：Array:输入的数据；
 *		left:Array中要归并的两组数据的最左索引
 *		right:Array中要归并的两组数据的最右索引
 *		mid:Array中要归并的两组数据的第1组数据的最后索引
 *输出：temp:归并后的数据
 *返回：无
 *************************************************************************/
template <typename T>
void Sort<T>::mergeData(Record<T> *Array,int left,int mid,int right,Record<T> *temp)
{
	int index1 = left;//第1组数据的下角标
	int index2 = mid+1;//第2组数据的下角标
	int i = 0;
	while(index1 <= mid && index2 <= right)
	{
		if(Array[index1].key <= Array[index2].key)//为保证稳定性，相等时优先选左边的
			temp[i++] = Array[index1++];
		else
			temp[i++] = Array[index2++];
	}
	/* 接收剩下的数据 */
	while(index1 <= mid)
		temp[i++] = Array[index1++];
	while(index2 <= right)
		temp[i++] = Array[index2++];
}
/*************************************************************************
 *归并排序的分组
 *输入：Array:输入的数据；
 *		left:Array中要归并的两组数据的最左索引
 *		right:Array中要归并的两组数据的最右索引
 *输出：temp:归并后的数据
 *返回：无
 *************************************************************************/
template <typename T>
void Sort<T>::_mergeSort(Record<T> *Array,int left,int right,Record<T> *temp)
{
	int mid;
	if(right <= left)//退出递归的条件
		return;
	mid = left+(right - left)/2;//取中间索引，即第1组数据的最后一个索引
	_mergeSort(Array, left, mid, temp);
	_mergeSort(Array, mid+1, right, temp);
	mergeData(Array, left, mid, right, temp);
	memcpy(Array + left, temp, sizeof(Array[0])*(right - left + 1));
}
/*************************************************************************
 *归并排序：将待排序的元素序列分为两个长度相等的子序列,对每个子序列进行排序,
 *			然后将他们合并成一个序列,合并两个子序列的过程称为二路归并.
 *时间复杂度：nlogn
 *稳定性：稳定
 *输入：Array:输入的数据；
 *		size:排序数据大小
 *输出：Array:排序完的数据
 *返回：无
 *************************************************************************/
template <typename T>
void Sort<T>::mergeSort(Record<T> *Array,int n)
{
	Record<T> *temp = new Record<T>[n];
	if(NULL == temp)
	{
		cout << "申请内存失败" << endl;
		return;
	}
	_mergeSort(Array,0,n-1,temp);
	delete []temp;
	temp = NULL;
}
/*************************************************************************
 *归并排序：非递归方式
 *时间复杂度：nlogn
 *稳定性：稳定
 *输入：Array:输入的数据；
 *		size:排序数据大小
 *输出：Array:排序完的数据
 *返回：无
 *************************************************************************/
template <typename T>
void Sort<T>::mergeSort_Nor(Record<T> *Array,int n)
{
	int gap,i;
	int left,right,mid;
	Record<T> *temp = new Record<T>[n];
	if(NULL == temp)
	{
		cout << "申请内存失败" << endl;
		return;
	}
	gap = 1;
	while(gap < n)
	{
		for(i = 0;i<n;i += 2*gap)
		{
			left = i;
			mid = left + gap -1;
			right = mid + gap;
			if(mid >= n)//确保所有数据都能分组
				mid = n - 1;
			if(right >= n)//确保所有数据都能分组
				right = n-1;
			mergeData(Array,left,mid,right,temp+i);
		}
		memcpy(Array,temp,sizeof(Array[0])*n);
		gap *= 2;
	}
	delete []temp;
	temp = NULL;
}

/*************************************************************************
 *优化的Sedgwick两个有序子序列归并，右子序列逆置了，都从两端向中间扫描，归并到新数组
 *************************************************************************/
template <typename T>
void Sort<T>::modMergeData(Record<T> *Array,Record<T> *TempArray,int left,int right,int middle)
{
	int i,j,k,index1,index2;									
	for(i = left;i<=middle;i++)								//复制左边的子序列
		TempArray[i] = Array[i];
	for(j = 1;j<right-middle;j++)							//复制右边的子序列，但顺序颠倒过来
		TempArray[right-j+1] = Array[j+middle];
	for(index1 = left,index2 = right,k = left;k<=right;k++)	//开始归并，取较小者插入合并数组中
	{
		if(TempArray[index1].key <= TempArray[index2].key)//为保证稳定性，相等时左边优先
			Array[k] = TempArray[index1++];
		else
			Array[k] = TempArray[index2--];
	}
}
/*************************************************************************
 * 优化的归并排序
 * Array[]：待排序数组
 * left:数组左端下标
 * right:数组右端下标
 ************************************************************************/
#define	THRESHOLD 28
template <typename T>
void Sort<T>::_modMergeSort(Record<T> *Array,Record<T> *TempArray,int left,int right)
{
	int middle;											
	if(right-left+1 > THRESHOLD)							//如果序列中只有0或1个记录，就不用排序
	{
		middle = (left+right)/2;							//从中间划分为两个子序列
		_modMergeSort(Array,TempArray,left,middle);			//对左边一般进行递归
		_modMergeSort(Array,TempArray,middle+1,right);		//对右边一半进行递归
		modMergeData(Array,TempArray,left,right,middle);		//进行归并
	}
	else
		insertSort(&Array[left],right-left+1);				//小长度子序列进行插入排序
}
/*************************************************************************
 * 优化的归并排序
 * Array[]：待排序数组
 * n:数据数量
 ************************************************************************/
template <typename T>
void Sort<T>::modMergeSort(Record<T> *Array,int n)
{
	Record<T> *temp = new Record<T>[n];
	if(NULL == temp)
	{
		cout << "申请内存失败" << endl;
		return;
	}
	_modMergeSort(Array, temp, 0, n-1);
	delete []temp;
	temp = NULL;
}
void testSort(void);
#endif