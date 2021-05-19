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

void testSort(void);
#endif