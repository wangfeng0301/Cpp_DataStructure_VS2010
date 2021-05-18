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
	int key;										//��ֵ������������Ƚ�
	T dat;											//����
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
///*��¼(�ڵ�)�ṹ��*/
//typedef struct
//{
//	int SortKey;
//	int next;
//}Record;
//
///*�ѽṹ��*/
//typedef struct 
//{
//	Record *heapArray;								//��Ŷ����ݵ�����
//	int CurrentSize;								//��ǰ����Ԫ����Ŀ
//	int MaxSize;									//�ѵ����Ԫ����Ŀ
//}SortHeap;
//
///*��̬���нṹ��*/
//typedef struct  
//{
//	int head;
//	int tail;
//}StaticQueue;

void testSort(void);
#endif