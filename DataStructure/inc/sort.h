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
	void mergeSort(Record<T> *arr,Record<T> *temparr,int left,int right);
	void modMergeSort(Record<T> *arr,Record<T> *temparr,int left,int right);
	void BucketSort(Record<T> *arr,int n,int max);
private:
	void swap(Record<T> *record1, Record<T> *record2);
	void modQuickSort(Record<T> *arr,int start, int end);
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
#if 0
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
void testSort(void);
#endif