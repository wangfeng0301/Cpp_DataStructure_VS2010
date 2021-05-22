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
	int key;										//��ֵ������������Ƚ�
	T dat;											//����
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
/* ���ܣ����캯��                                             
/* ���룺��
/* �������
/* ���أ���
/************************************************************************/
template <typename T>
Sort<T>::Sort()
{

}
/************************************************************************/
/* ���ܣ���������                                             
/* ���룺��
/* �������
/* ���أ���
/************************************************************************/
template <typename T>
Sort<T>::~Sort()
{

}
/************************************************************************/
/* ���ܣ���������                                             
/* ���룺��
/* �������
/* ���أ���
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
/* ð������:ʱ�临�Ӷȣ�n^2,�ȶ�
/* ���룺Array������������
/*       n�����鳤��
/*       mode:0������1������
/* �����Array:�ź��������
/* ���أ���
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
				/*����ע������һ����С�ڣ�������С�ڵ��ڣ����������ȶ�*/
				if(Array[j].key < Array[j+1].key)
					swap(&Array[j], &Array[j+1]);
			}
			else
			{
				/*����ע������һ���Ǵ��ڣ������Ǵ��ڵ��ڣ����������ȶ�*/
				if(Array[j].key > Array[j+1].key)
					swap(&Array[j], &Array[j+1]);
			}
		}
	}
#else
	/*����һ��ð�����򷽷������ַ�ʽ�ǽ��ź�������ݷ���ǰ�棬*/
	/*�������ַ����ǽ��ź�������ݷ��ں���*/
	/*������Ѿ�����ð�ݷ��ˣ���Ϊû�����������Ƚϣ������֤������ʱ�临�ӶȺ��ȶ�����һ����*/
	/*2021.5.22 ����ʵ��ֱ��ѡ������*/
	for(i = 0;i<n-1;i++)
	{
		for(j = i+1;j<n;j++)
		{
			if(mode)
			{
				/*����ע������һ����С�ڣ�������С�ڵ��ڣ����������ȶ�*/
				if(Array[i].key < Array[j].key)
					swap(&Array[i], &Array[j]);
			}
			else
			{
				/*����ע������һ���Ǵ��ڣ������Ǵ��ڵ��ڣ����������ȶ�*/
				if(Array[i].key > Array[j].key)
					swap(&Array[i], &Array[j]);
			}
		}
	}
#endif
}
/*************************************************************************
 *��������:ʱ�临�Ӷȣ�nlogn�����ȶ�
 *���룺Array  Ҫ���������
 *		start ���ݿ�ʼ�±�
 *		end  ���ݽ����±�
 *���أ���
 *************************************************************************/
template <typename T>
void Sort<T>::quickSort(Record<T> *Array, int start, int end)
{
	/* ȡ��һ������Ϊ��׼�� */
	Record<T> mid = Array[start];
	int low,high;

	/* start��end��ͷ�ˣ�����������˳��ݹ� */
	if(start >= end)
		return;

	/* low��������ӻ�׼����ʼ�ұ�mid�������λ�� */
	/* high������Ҳ�end�����ұ�midС������λ�� */
	low = start;
	high = end;

	/* ����ѭ����ֻҪlow��highû����ͷ��һֱ����,��low��high���˵����ͷ�� */
	while(low < high)
	{
		/* ��high��ʼ�����ҵ���һ����midС���ߵ���mid���������λ��,�����high������mid�����Ǿ�����high��*/
		/* ��������Ҫȷ���ҵ�֮ǰ�����low��high��ͷ�ˣ�Ҳ������ */
		while(Array[high].key > mid.key && (low < high))
			high--;

		/* ��low��ʼ���ң��ҵ���һ����mid����������λ��,�����low������midС�����Ǿ�����low�� */
		/* ��������Ҫȷ���ҵ�֮ǰ�����low��high��ͷ�ˣ�Ҳ������ */
		while((Array[low].key <= mid.key) && (low < high))
			low++;

		/* �ҵ�������Ǻ󣬽��� */
		swap(&Array[low],&Array[high]);
	}
	swap(&Array[start],&Array[low]);

	quickSort(Array,start,low-1);//�ݹ����
	quickSort(Array,low+1,end);
}

/*************************************************************************
 *�������򷨣��Ż���:ʱ�临�Ӷȣ�nlogn�����ȶ�
 *���룺Array  Ҫ���������
 *		start ���ݿ�ʼ�±�
 *		end  ���ݽ����±�
 *���أ���
 *************************************************************************/
#define THRESHOLD 28
template <typename T>
void Sort<T>::modQuickSort(Record<T> *Array, int start, int end)
{
	if(end - start + 1 > THRESHOLD)
	{
		/* ȡ��һ������Ϊ��׼�� */
		Record<T> mid = Array[start];
		int low,high;

		/* start��end��ͷ�ˣ�����������˳��ݹ� */
		if(start >= end)
			return;

		/* low��������ӻ�׼����ʼ�ұ�mid�������λ�� */
		/* high������Ҳ�end�����ұ�midС������λ�� */
		low = start;
		high = end;

		/* ����ѭ����ֻҪlow��highû����ͷ��һֱ����,��low��high���˵����ͷ�� */
		while(low < high)
		{
			/* ��high��ʼ�����ҵ���һ����midС���ߵ���mid���������λ��,�����high������mid�����Ǿ�����high��*/
			/* ��������Ҫȷ���ҵ�֮ǰ�����low��high��ͷ�ˣ�Ҳ������ */
			while(Array[high].key > mid.key && (low < high))
				high--;

			/* ��low��ʼ���ң��ҵ���һ����mid����������λ��,�����low������midС�����Ǿ�����low�� */
			/* ��������Ҫȷ���ҵ�֮ǰ�����low��high��ͷ�ˣ�Ҳ������ */
			while((Array[low].key <= mid.key) && (low < high))
				low++;

			/* �ҵ�������Ǻ󣬽��� */
			swap(&Array[low],&Array[high]);
		}
		swap(&Array[start],&Array[low]);

		modQuickSort(Array,start,low-1);//�ݹ����
		modQuickSort(Array,low+1,end);
	}
}
/*************************************************************************
 *�������򷨣��Ż���:ʱ�临�Ӷȣ�nlogn�����ȶ�
 *���룺Array  Ҫ���������
 *		n ���ݳ���
 *���أ���
 *************************************************************************/
template <typename T>
void Sort<T>::quickSort(Record<T> *Array, int n)
{
	modQuickSort(Array, 0, n-1);
	insertSort(Array, n);
}
/*************************************************************************
 *ֱ�Ӳ������򷨣�ʱ�临�Ӷȣ�n^2
 *�ȶ��ԣ��ȶ�
 *˼�룺1.�ӵ�2������ʼ������ѡ����ΪҪ�Ƚϵ�ֵ��
 *		2.�Ը�ֵΪ���ң���������Ƚϣ�������ֵ����ֵ�����ƣ��ճ�λ��
 *		3.ֱ���ҵ��ȸ�ֵС���������ҵ����󣬽���
 *		4.ѡ��һ��Ҫ�Ƚϵ�ֵ���ظ�2-3����ֱ���������н���
 *���룺dat  Ҫ���������
 *		len ���ݳ���
 *���أ���
 *************************************************************************/
template <typename T>
void Sort<T>::insertSort(Record<T> *Array, int n)
{
	Record<T> temp;
	int end;
	for(int i = 1;i < n;i++)
	{
		temp = Array[i];//����ÿ��Ҫ�Ƚϵ�ֵ
		end = i-1;
		/* ��ǰ�Ƚϣ�ֱ���ҵ����Լ�С�ģ����롣һ����key<dat[end]������С�ڵ��ڣ������ȶ� */
		while(end >= 0 && temp.key < Array[end].key)
		{
			/* ����ķ���Ϊ����ǰһ��ֵ��ֵ����һ��ֵ�����keyֵ��ֵ����ǰ����ɲ��� */
			Array[end+1] = Array[end];
			end--;
		}
		Array[end+1] = temp;
	}
}

/*************************************************************************
 *ϣ�����򷨣�ֱ�Ӳ������򷨵��Ż���:ʱ�临�Ӷȣ�n^2
 *�ȶ��ԣ����ȶ�
 *˼�룺1.����
 *		2.�Է�����в�������
 *		3.��С�����࣬��С���и���
 *���룺dat  Ҫ���������
 *		len ���ݳ���
 *���أ���
 *************************************************************************/
template <typename T>
void Sort<T>::shellSort(Record<T> *Array, int n)
{
	int gap = n/2;
	Record<T> temp;
	int end,i=0;

	for(gap;gap>0;gap/=2)//����Ҳ����ȡ����ֵ
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
 *ֱ��ѡ������ʱ�临�Ӷȣ�n^2
 *˼�룺1.�ҳ���iС��ֵ���ŵ���i��λ��
 *�ȶ��ԣ����ȶ�
 *���룺dat  Ҫ���������
 *		len ���ݳ���
 *���أ���
 *************************************************************************/
template <typename T>
void Sort<T>::selectSort(Record<T>* Array,int n)
{
#if 0
	/* ��ͨ��ֱ��ѡ������ */
	int i,j,smallest;
	/* ��ѭ�����1�β��ñȽ� */
	for(i = 0;i<n - 1;i++)
	{
		smallest = i;
		/* ��ѭ����Ҫ��ѡ�еĺ�һ����ʼ�Ƚϵ����һ�� */
		for(j = i+1;j<n;j++)
		{
			if(Array[j].key < Array[smallest].key)
				smallest = j;
		}
		/* ��Сֵ�����������˱仯�Ž��� */
		if(smallest != i)
			swap(&Array[smallest], &Array[i]);
	}
#else
	/* �Ľ���ֱ��ѡ������ */
	int i;
	int minIndex,maxIndex;
	int left=0,right=n-1;//����������
	
	while(left < right)
	{
		minIndex = left;
		maxIndex = right;
		for(i = left;i<=right;i++)//�ҵ������Сֵ������
		{
			if(Array[minIndex].key > Array[i].key)
				minIndex = i;
			if(Array[maxIndex].key < Array[i].key)
				maxIndex = i;
		}
		/* ���������˱仯�Ž��� */
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
 *������(��������)��ʱ�临�Ӷȣ�nlogn
 *˼�룺1.���������ݽ�������
 *		2.ȡ���Ѷ����ֵ��ĩ�˽���
 *		3.����Ϊ���ѣ��ظ�2-3
 *�ȶ��ԣ����ȶ�
 *���룺arr:��������ݣ�
 *		len:�������ݵ�������
 *�����arr���������е�����
 *���أ���
 *************************************************************************/
template <typename T>
void Sort<T>::heapSort(Record<T> *Array,int n)
{
	/* �������� */
	MaxHeap<Record<T>> maxheap(n);
	for(int i = 0;i<n;i++)
		maxheap.insert(Array[i].key, Array[i]);
	
	/* ����ȡ���Ѷ� */
	HeapNode<Record<T>> temp_node;
	for(int i = 0;i<n;i++)
	{
		maxheap.removeMax(&temp_node);
		Array[i] = temp_node.dat;
	}
}

/*************************************************************************
 *��·�鲢
 *���룺Array:��������ݣ�
 *		left:Array��Ҫ�鲢���������ݵ���������
 *		right:Array��Ҫ�鲢���������ݵ���������
 *		mid:Array��Ҫ�鲢���������ݵĵ�1�����ݵ��������
 *�����temp:�鲢�������
 *���أ���
 *************************************************************************/
template <typename T>
void Sort<T>::mergeData(Record<T> *Array,int left,int mid,int right,Record<T> *temp)
{
	int index1 = left;//��1�����ݵ��½Ǳ�
	int index2 = mid+1;//��2�����ݵ��½Ǳ�
	int i = 0;
	while(index1 <= mid && index2 <= right)
	{
		if(Array[index1].key <= Array[index2].key)//Ϊ��֤�ȶ��ԣ����ʱ����ѡ��ߵ�
			temp[i++] = Array[index1++];
		else
			temp[i++] = Array[index2++];
	}
	/* ����ʣ�µ����� */
	while(index1 <= mid)
		temp[i++] = Array[index1++];
	while(index2 <= right)
		temp[i++] = Array[index2++];
}
/*************************************************************************
 *�鲢����ķ���
 *���룺Array:��������ݣ�
 *		left:Array��Ҫ�鲢���������ݵ���������
 *		right:Array��Ҫ�鲢���������ݵ���������
 *�����temp:�鲢�������
 *���أ���
 *************************************************************************/
template <typename T>
void Sort<T>::_mergeSort(Record<T> *Array,int left,int right,Record<T> *temp)
{
	int mid;
	if(right <= left)//�˳��ݹ������
		return;
	mid = left+(right - left)/2;//ȡ�м�����������1�����ݵ����һ������
	_mergeSort(Array, left, mid, temp);
	_mergeSort(Array, mid+1, right, temp);
	mergeData(Array, left, mid, right, temp);
	memcpy(Array + left, temp, sizeof(Array[0])*(right - left + 1));
}
/*************************************************************************
 *�鲢���򣺽��������Ԫ�����з�Ϊ����������ȵ�������,��ÿ�������н�������,
 *			Ȼ�����Ǻϲ���һ������,�ϲ����������еĹ��̳�Ϊ��·�鲢.
 *ʱ�临�Ӷȣ�nlogn
 *�ȶ��ԣ��ȶ�
 *���룺Array:��������ݣ�
 *		size:�������ݴ�С
 *�����Array:�����������
 *���أ���
 *************************************************************************/
template <typename T>
void Sort<T>::mergeSort(Record<T> *Array,int n)
{
	Record<T> *temp = new Record<T>[n];
	if(NULL == temp)
	{
		cout << "�����ڴ�ʧ��" << endl;
		return;
	}
	_mergeSort(Array,0,n-1,temp);
	delete []temp;
	temp = NULL;
}
/*************************************************************************
 *�鲢���򣺷ǵݹ鷽ʽ
 *ʱ�临�Ӷȣ�nlogn
 *�ȶ��ԣ��ȶ�
 *���룺Array:��������ݣ�
 *		size:�������ݴ�С
 *�����Array:�����������
 *���أ���
 *************************************************************************/
template <typename T>
void Sort<T>::mergeSort_Nor(Record<T> *Array,int n)
{
	int gap,i;
	int left,right,mid;
	Record<T> *temp = new Record<T>[n];
	if(NULL == temp)
	{
		cout << "�����ڴ�ʧ��" << endl;
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
			if(mid >= n)//ȷ���������ݶ��ܷ���
				mid = n - 1;
			if(right >= n)//ȷ���������ݶ��ܷ���
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
 *�Ż���Sedgwick�������������й鲢���������������ˣ������������м�ɨ�裬�鲢��������
 *************************************************************************/
template <typename T>
void Sort<T>::modMergeData(Record<T> *Array,Record<T> *TempArray,int left,int right,int middle)
{
	int i,j,k,index1,index2;									
	for(i = left;i<=middle;i++)								//������ߵ�������
		TempArray[i] = Array[i];
	for(j = 1;j<right-middle;j++)							//�����ұߵ������У���˳��ߵ�����
		TempArray[right-j+1] = Array[j+middle];
	for(index1 = left,index2 = right,k = left;k<=right;k++)	//��ʼ�鲢��ȡ��С�߲���ϲ�������
	{
		if(TempArray[index1].key <= TempArray[index2].key)//Ϊ��֤�ȶ��ԣ����ʱ�������
			Array[k] = TempArray[index1++];
		else
			Array[k] = TempArray[index2--];
	}
}
/*************************************************************************
 * �Ż��Ĺ鲢����
 * Array[]������������
 * left:��������±�
 * right:�����Ҷ��±�
 ************************************************************************/
#define	THRESHOLD 28
template <typename T>
void Sort<T>::_modMergeSort(Record<T> *Array,Record<T> *TempArray,int left,int right)
{
	int middle;											
	if(right-left+1 > THRESHOLD)							//���������ֻ��0��1����¼���Ͳ�������
	{
		middle = (left+right)/2;							//���м仮��Ϊ����������
		_modMergeSort(Array,TempArray,left,middle);			//�����һ����еݹ�
		_modMergeSort(Array,TempArray,middle+1,right);		//���ұ�һ����еݹ�
		modMergeData(Array,TempArray,left,right,middle);		//���й鲢
	}
	else
		insertSort(&Array[left],right-left+1);				//С���������н��в�������
}
/*************************************************************************
 * �Ż��Ĺ鲢����
 * Array[]������������
 * n:��������
 ************************************************************************/
template <typename T>
void Sort<T>::modMergeSort(Record<T> *Array,int n)
{
	Record<T> *temp = new Record<T>[n];
	if(NULL == temp)
	{
		cout << "�����ڴ�ʧ��" << endl;
		return;
	}
	_modMergeSort(Array, temp, 0, n-1);
	delete []temp;
	temp = NULL;
}
void testSort(void);
#endif