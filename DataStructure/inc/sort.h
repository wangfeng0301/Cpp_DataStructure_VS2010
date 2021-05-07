#ifndef __SORT_H__
#define __SORT_H__
#include "type.h"

/*��¼(�ڵ�)�ṹ��*/
typedef struct
{
	int SortKey;
	int next;
}Record;

/*�ѽṹ��*/
typedef struct 
{
	Record *heapArray;								//��Ŷ����ݵ�����
	int CurrentSize;								//��ǰ����Ԫ����Ŀ
	int MaxSize;									//�ѵ����Ԫ����Ŀ
}SortHeap;

/*��̬���нṹ��*/
typedef struct  
{
	int head;
	int tail;
}StaticQueue;

void testSort(void);
#endif