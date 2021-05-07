/************************************************************************
 *                 ��                                 
 *������ȫ���������Ա�洢������
 *�ο����ϣ������ݽṹ���㷨�������������ԣ��Ժ����
 *wangfeng
 *E-mail:fengwang0301@163.com
 *CSDN:https://blog.csdn.net/u013073067?spm=1001.2101.3001.5343
 *GitHub:https://github.com/wangfeng0301
 *2019.11.29-2021.2.4
 *2021.2.4	�޸ģ��淶������
 *			���ӣ����Ѳ���
 *2021.2.5	�޸ģ��Ż��򻯴��룬����������������
************************************************************************/
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "heap.h"

/************************************************************************/
/*���ܣ��ж϶��Ƿ���
/*���룺heap:�ѽṹ����
/*�������
/*���أ���TRUE,δ��FALSE
/************************************************************************/
static bool Heap_IsFull(Heap_t *heap, uchar tag)
{
	if(heap->currsize >= heap->maxsize)				//���������������TRUE
		return TRUE;
	else
		return FALSE;
}
/************************************************************************/
/*���ܣ��ж϶��Ƿ��
/*���룺heap:�ѽṹ����
/*�������
/*���أ���TRUE,δ��FALSE
/************************************************************************/
static bool Heap_IsEmpty(Heap_t *heap, uchar tag)
{
	if(heap->currsize <= 0)				//������ѿգ�����TRUE
		return TRUE;
	else
		return FALSE;
}
/************************************************************************/
/*���ܣ���parentΪ�����½��е���,����С�ѣ�������������棻�����ѣ���С����������
/*���룺parent:���ڵ��ţ��Ӵ˽ڵ㿪ʼ����
/*		tag:0,��С�ѣ�1������
/*�������
/*���أ���
/************************************************************************/
static void Heap_SiftDown(Heap_t *heap, uint parent, uchar tag)
{
	uint child = 2*parent + 1;						//���ڵ�����ӽڵ���
	HeapNode_t temp = heap->array[parent];			//���游�ڵ�

	while(child < heap->currsize)					//�ڵ���С�ڵ�ǰ��С
	{
		/* ��С�ѣ��������ӽڵ㣬�����ӽڵ�С�����ӽڵ�,����������ӽڵ� */
		/* ���ѣ��������ӽڵ㣬�����ӽڵ�������ӽڵ�,����������ӽڵ� */
		//if((child < heap->currsize-1) && (heap->array[child].key > heap->array[child+1].key))
		if((child < heap->currsize-1))
		{
			if((heap->array[child].key > heap->array[child+1].key && tag == 0) || 
				(heap->array[child].key < heap->array[child+1].key && tag == 1))
			child++;
		}
		/* ��С�ѣ����ڵ�����ӽڵ�,����λ�� */
		/* ���ѣ����ڵ�С���ӽڵ�,����λ�� */
		if((temp.key > heap->array[child].key && tag == 0) ||
			(temp.key < heap->array[child].key && tag == 1))		
		{
			heap->array[parent] = heap->array[child];
			parent = child;
			child = 2*parent+1;						//���������ߣ����ӽڵ�
		}
		else
			break;									//����������ʱ�˳�
	}
	heap->array[parent] = temp;
}

/************************************************************************/
/*���ܣ���posΪ�����Ͻ��е���,����С�ѣ���С���������棻�����ѣ��������������
/*���룺pos:��ʼ����λ��
/*		tag:0,��С�ѣ�1������
/*�������
/*���أ���
/************************************************************************/
static void Heap_SiftUp(Heap_t *heap, uint pos, uchar tag)
{
	int position = pos;								//�ӵ�ǰ��Сλ�ÿ�ʼ���ϵ���
	HeapNode_t temp = heap->array[position];		//���浱ǰֵ
	/* ��̬�ѣ�leftchild = 2*parent + 1 */
	/* ��̬�ѣ�rightchild = 2*parent + 2 */
	/* ��̬�ѣ�parent = (child-1)/2 */
	/* δ���������ڵ㣬�Ҹ��ڵ�ȵ�ǰ�ڵ�� */
	while((position > 0) &&((heap->array[(position-1)/2].key > temp.key) && tag == 0) ||
							((heap->array[(position-1)/2].key < temp.key) && tag == 1))
	{
		heap->array[position] = heap->array[(position-1)/2];
		position = (position-1)/2;					//���������ڵ�λ��
	}
	heap->array[position] = temp;
}

/************************************************************************/
/*���ܣ������ѽṹ 
/*���룺heap:�ѽṹ����
/*		dat:�����ݣ�����keyֵ��
/*		datlen:����Ԫ�س��ȣ�����keyֵ��
/*		key:���ݶ�Ӧ��keyֵ��һ��Ҫ��dat��Ӧ��
/*		size:���ݸ���
/*		maxsize:�����ռ��С
/*		tag:0,��С�ѣ�1������
/*�������
/*���أ�TRUE or FALSE
/************************************************************************/
static bool Heap_Create(Heap_t *heap, void *dat, uint datlen, int *key, int size, int maxsize, uchar tag)
{
	int i;
	if(maxsize <= 0)									//���������ռ�������0
		return FALSE;
	heap->array = (HeapNode_t *)malloc(maxsize*sizeof(HeapNode_t));//����maxsize���ռ��С
	if(heap->array == NULL)
		return FALSE;
	//for(i=0;i<heap->currsize;i++)						//���ݸ�ֵ
	for(i=0;i<maxsize;i++)								//�������ռ�
	{
		heap->array[i].dat = (void *)malloc(datlen);
		if(heap->array[i].dat == NULL)
			return FALSE;
		if(i < size)
		{
			memcpy(heap->array[i].dat, (void *)((uint)dat+i*datlen), datlen);
			heap->array[i].key = key[i];
		}
	}
	heap->currsize = size;								//��ǰ����Ԫ�ظ���
	heap->maxsize = maxsize;
	heap->datlen = datlen;
	for(i = heap->currsize/2-1;i>=0;i--)				//ɸѡ�����ѣ���n/2-1��ʼ
	{
		Heap_SiftDown(heap, i, tag);
	}
	return TRUE;
}

/************************************************************************/
/*���ܣ������½ڵ� 
/*���룺heap:�ѽṹ����
/*		key:����ڵ��ֵ
/*		tag:0,��С�ѣ�1������
/*�������
/*���أ�TRUE or FALSE
/************************************************************************/
static bool Heap_Insert(Heap_t *heap, uint key, void *dat, uchar tag)
{
	printf("����ڵ��ֵ��%d\r\n",key);
	if(Heap_IsFull(heap, tag))
		return FALSE;
	heap->array[heap->currsize].dat = (void *)malloc(heap->datlen);
	//if(heap->array[heap->currsize].dat == NULL)//����ʱ�Ѿ����ٿռ�
	//	return FALSE;
	memcpy(heap->array[heap->currsize].dat, dat, heap->datlen);
	heap->array[heap->currsize].key = key;
	Heap_SiftUp(heap, heap->currsize, tag);			//���ϵ���
	heap->currsize++;								//��ǰ��С��1

	return TRUE;
}

/************************************************************************/
/*���ܣ��ӶѶ�ɾ����Сֵ�����ֵ  
/*���룺heap:�ѽṹ����
/*		tag:0,��С�ѣ�1������
/*�����node:ɾ���ڵ��ֵ(HeapNode_t���ͣ�ֻ�������ݵ�ַ��û������)
/*���أ�TRUE or FALSE
/************************************************************************/
static bool Heap_RemoveMinMax(Heap_t *heap, HeapNode_t *node, uchar tag)
{
	HeapNode_t temp;
	if(MinHeap_IsEmpty(heap))						//��ǰ��СΪ0���޷�ɾ��
	{
		printf("��ǰ�Ѵ�СΪ0���޷�ɾ��\r\n");
		return FALSE;
	}
	else
	{
		heap->currsize--;							//��ǰ��С��1

		temp = heap->array[0];						//�����Ѷ��Ͷ�ĩβԪ��
		heap->array[0] = heap->array[heap->currsize];
		heap->array[heap->currsize] = temp;

		if(heap->currsize > 1)						//��ǰ��С����1���ӶѶ���ʼ����ɸѡ����
			Heap_SiftDown(heap, 0, tag);
		*node = heap->array[heap->currsize];
		//free(heap->array[heap->currsize].dat);	//����ʱ���ͷ�
		//heap->array[heap->currsize].dat = NULL;
		return TRUE;
	}
}

/************************************************************************/
/*���ܣ�ɾ�������±��Ԫ�� 
/*���룺heap:�ѽṹ����
/*		pos:ɾ���ڵ�ı��
/*		tag:0,��С�ѣ�1������
/*�����node:ɾ���ڵ��ֵ
/*���أ�TRUE or FALSE
/************************************************************************/
static bool Heap_Remove(Heap_t *heap, HeapNode_t *node, uint pos, uchar tag)
{
	printf("ɾ���ڵ�%d\r\n",pos);
	if(Heap_IsEmpty(heap, tag))
	{
		printf("��ǰ�Ѵ�СΪ0���޷�ɾ��\r\n");
		return FALSE;
	}
	if((pos<0) || pos >= heap->currsize)
	{
		printf("�ڵ��±곬��Χ���޷�ɾ��\r\n");
		return FALSE;
	}
	*node = heap->array[pos];						//���Ҫɾ���Ľڵ�
	heap->array[pos] = heap->array[--heap->currsize];//�ö�����ֵ�滻�����ֵ
	if(heap->array[(pos-1)/2].key > heap->array[pos].key)//������ڵ�ֵ���ڵ�ǰֵ
	{
		if(tag == 0)
			Heap_SiftUp(heap,pos,tag);				//�ӵ�ǰ�ڵ㿪ʼ����ɸѡ
		else if(tag == 1)
			Heap_SiftDown(heap,pos,tag);
	}
	else
	{
		if(tag == 0)
			Heap_SiftDown(heap, pos, tag);			//����Ӵ˽ڵ㿪ʼ���µ���
		else if(tag == 1)
			Heap_SiftUp(heap, pos, tag);
	}
	//free(heap->array[heap->currsize].dat);		//����ʱ���ͷ�
	//heap->array[heap->currsize].dat = NULL;
	return TRUE;
}
/************************************************************************/
/*���ܣ�������ȱ�����  
/*���룺heap:�ѽṹ����
/*�������
/*���أ���
/************************************************************************/
static void Heap_Traverse(Heap_t *heap, uchar tag)
{
	uint i;
	printf("������");
	for(i=0;i<heap->currsize;i++)
	{
		printf("keyֵ��%d ",heap->array[i].key);
		printf("���ݣ�%d \r\n",*(int *)heap->array[i].dat);
	}
	printf("\r\n");
}
/************************************************************************/
/*���ܣ����ٶ�
/*���룺heap:�ѽṹ����
/*�������
/*���أ���
/************************************************************************/
static void Heap_Destroy(Heap_t *heap, uchar tag)
{
	while(heap->maxsize)
	{
		heap->maxsize --;
		free(heap->array[heap->currsize].dat);		//�ͷ�ɾ���ڵ��������
		heap->array[heap->currsize].dat = NULL;
		heap->array[heap->currsize].key = 0;
	}
	heap->currsize = 0;
	free(heap->array);
	heap->array = NULL;
}


/*************************************************** ��С�� **************************************************/
/************************************************************************/
/*���ܣ��ж������Ƿ���
/*���룺heap:�ѽṹ����
/*�������
/*���أ���TRUE,δ��FALSE
/************************************************************************/
bool MinHeap_IsFull(Heap_t *heap)
{
	return Heap_IsFull(heap, 0);
}
/************************************************************************/
/*���ܣ��ж������Ƿ��
/*���룺heap:�ѽṹ����
/*�������
/*���أ���TRUE,δ��FALSE
/************************************************************************/
bool MinHeap_IsEmpty(Heap_t *heap)
{
	return Heap_IsEmpty(heap, 0);
}
/************************************************************************/
/*���ܣ���parentΪ�����½��е���,��������������
/*���룺parent:���ڵ��ţ��Ӵ˽ڵ㿪ʼ����
/*�������
/*���أ���
/************************************************************************/
void MinHeap_SiftDown(Heap_t *heap, uint parent)
{
	Heap_SiftDown(heap, parent, 0);
}
/************************************************************************/
/*���ܣ���posΪ�����Ͻ��е���,��С����������
/*���룺pos:��ʼ����λ��
/*�������
/*���أ���
/************************************************************************/
void MinHeap_SiftUp(Heap_t *heap, uint pos)
{
	Heap_SiftUp(heap, pos, 0);
}
/************************************************************************/
/*���ܣ�������С�ѽṹ 
/*���룺heap:�ѽṹ����
/*		dat:�����ݣ�����keyֵ��
/*		datlen:����Ԫ�س��ȣ�����keyֵ��
/*		key:���ݶ�Ӧ��keyֵ��һ��Ҫ��dat��Ӧ��
/*		size:���ݸ���
/*		maxsize:�����ռ��С
/*�������
/*���أ�TRUE or FALSE
/************************************************************************/
bool MinHeap_Create(Heap_t *heap, void *dat, uint datlen, int *key, int size, int maxsize)
{
	return Heap_Create(heap, dat, datlen, key, size, maxsize, 0);
}
/************************************************************************/
/*���ܣ������½ڵ� 
/*���룺heap:�ѽṹ����
/*		key:�ڵ��ֵ
/*		dat:�ڵ�����
/*�������
/*���أ�TRUE or FALSE
/************************************************************************/
bool MinHeap_Insert(Heap_t *heap,uint key, void *dat)
{
	return Heap_Insert(heap, key, dat, 0);
}
/************************************************************************/
/*���ܣ��ӶѶ�ɾ����Сֵ 
/*���룺heap:�ѽṹ����
/*�����node:ɾ���ڵ��ֵ
/*���أ�TRUE or FALSE
/************************************************************************/
bool MinHeap_RemoveMin(Heap_t *heap, HeapNode_t *node)
{
	return Heap_RemoveMinMax(heap, node, 0);
}
/************************************************************************/
/*���ܣ�ɾ�������±��Ԫ�� 
/*���룺heap:�ѽṹ����
/*		pos:ɾ���ڵ�ı��
/*		tag:0,��С�ѣ�1������
/*�����node:ɾ���ڵ��ֵ
/*���أ�TRUE or FALSE
/************************************************************************/
bool MinHeap_Remove(Heap_t *heap, HeapNode_t *node, uint pos)
{
	return Heap_Remove(heap, node, pos, 0);
}
/************************************************************************/
/*���ܣ�������ȱ�����С��  
/*���룺heap:�ѽṹ����
/*�������
/*���أ���
/************************************************************************/
void MinHeap_Traverse(Heap_t *heap)
{
	Heap_Traverse(heap, 0);
}
/************************************************************************/
/*���ܣ����ٶ�
/*���룺heap:�ѽṹ����
/*�������
/*���أ���
/************************************************************************/
void MinHeap_Destroy(Heap_t *heap)
{
	Heap_Destroy(heap, 0);
}





/*************************************************** ���� **************************************************/
/************************************************************************/
/*���ܣ��ж������Ƿ���
/*���룺heap:�ѽṹ����
/*�������
/*���أ���TRUE,δ��FALSE
/************************************************************************/
bool MaxHeap_IsFull(Heap_t *heap)
{
	return Heap_IsFull(heap, 1);
}
/************************************************************************/
/*���ܣ��ж������Ƿ��
/*���룺heap:�ѽṹ����
/*�������
/*���أ���TRUE,δ��FALSE
/************************************************************************/
bool MaxHeap_IsEmpty(Heap_t *heap)
{
	return Heap_IsEmpty(heap, 1);
}
/************************************************************************/
/*���ܣ���parentΪ�����½��е���,��С����������
/*���룺parent:���ڵ��ţ��Ӵ˽ڵ㿪ʼ����
/*�������
/*���أ���
/************************************************************************/
void MaxHeap_SiftDown(Heap_t *heap, uint parent)
{
	Heap_SiftDown(heap, parent, 1);
}

/************************************************************************/
/*���ܣ���posΪ�����Ͻ��е���,��������������
/*���룺pos:��ʼ����λ��
/*�������
/*���أ���
/************************************************************************/
void MaxHeap_SiftUp(Heap_t *heap, uint pos)
{
	Heap_SiftUp(heap, pos, 1);
}

/************************************************************************/
/*���ܣ��������ѽṹ 
/*���룺heap:�ѽṹ����
/*		dat:�����ݣ�����keyֵ��
/*		datlen:����Ԫ�س��ȣ�����keyֵ��
/*		key:���ݶ�Ӧ��keyֵ��һ��Ҫ��dat��Ӧ��
/*		size:���ݸ���
/*		maxsize:�����ռ��С
/*�������
/*���أ�TRUE or FALSE
/************************************************************************/
bool MaxHeap_Create(Heap_t *heap, void *dat, uint datlen, int *key, uint size, uint maxsize)
{
	return Heap_Create(heap, dat, datlen, key, size, maxsize, 1);
}
/************************************************************************/
/*���ܣ������½ڵ� 
/*���룺heap:�ѽṹ����
/*		key:�ڵ��ֵ
/*		dat:�ڵ�����
/*�������
/*���أ�TRUE or FALSE
/************************************************************************/
bool MaxHeap_Insert(Heap_t *heap,uint key, void *dat)
{
	return Heap_Insert(heap, key, dat, 1);
}
/************************************************************************/
/*���ܣ��ӶѶ�ɾ�����ֵ  
/*���룺heap:�ѽṹ����
/*�����node:ɾ���ڵ��ֵ
/*���أ�TRUE or FALSE
/************************************************************************/
bool MaxHeap_RemoveMax(Heap_t *heap, HeapNode_t *node)
{
	return Heap_RemoveMinMax(heap, node, 1);
}
/************************************************************************/
/*���ܣ�ɾ�������±��Ԫ�� 
/*���룺heap:�ѽṹ����
/*		node:�ڵ�ֵ
/*		pos:ɾ���ڵ�ı��
/*�����ɾ���ڵ��ֵ
/*���أ�TRUE or FALSE
/************************************************************************/
bool MaxHeap_Remove(Heap_t *heap, HeapNode_t *node, uint pos)
{
	return Heap_Remove(heap, node, pos, 1);
}
/************************************************************************/
/*���ܣ�������ȱ�����С��  
/*���룺heap:�ѽṹ����
/*�������
/*���أ���
/************************************************************************/
void MaxHeap_Traverse(Heap_t *heap)
{
	Heap_Traverse(heap, 1);
}
/************************************************************************/
/*���ܣ����ٶ�
/*���룺heap:�ѽṹ����
/*�������
/*���أ���
/************************************************************************/
void MaxHeap_Destroy(Heap_t *heap)
{
	Heap_Destroy(heap, 1);
}



void testHeap(void)
{
	int HeapVal[9] = {9,9,7,6,20,4,33,2,1};
	uint key[9] = {9,9,7,6,20,4,33,2,1};
	int temp = 11111;
	Heap_t heap;									//����һ���ѽṹ����
	HeapNode_t node;
	
	MinHeap_Create(&heap, HeapVal, sizeof(HeapVal[0]), key, sizeof(HeapVal)/sizeof(HeapVal[0]), 10);
	MinHeap_Traverse(&heap);
	if(TRUE == MinHeap_Insert(&heap,10, &temp))
		MinHeap_Traverse(&heap);

	if(MinHeap_RemoveMin(&heap, &node))
		printf("��Сֵ��%d\r\n",node.key);
	MinHeap_Traverse(&heap);

	if(MinHeap_Remove(&heap, &node, 3))
		printf("��ɾ�����ݣ�%d\r\n", node.key);
	MinHeap_Traverse(&heap);
	while(!MinHeap_IsEmpty(&heap))
	{
		if(MinHeap_RemoveMin(&heap, &node))
			printf("��Сֵ��%d\r\n",node.key);
	}
	MinHeap_Destroy(&heap);

	printf("\r\n\r\n");
	//MaxHeap_Create(&heap, HeapVal, sizeof(HeapVal)/sizeof(HeapVal[0]), 10);
	MaxHeap_Create(&heap, HeapVal, sizeof(HeapVal[0]), key, sizeof(HeapVal)/sizeof(HeapVal[0]), 10);
	MaxHeap_Traverse(&heap);
	if(TRUE == MaxHeap_Insert(&heap, 10, &temp))
		MaxHeap_Traverse(&heap);

	if(MaxHeap_RemoveMax(&heap, &node))
		printf("���ֵ��%d\r\n", node.key);
	MaxHeap_Traverse(&heap);

	if(MaxHeap_Remove(&heap, &node, 3))
		printf("��ɾ�����ݣ�%d\r\n", node.key);
	MaxHeap_Traverse(&heap);
	while(!MaxHeap_IsEmpty(&heap))
	{
		if(MaxHeap_RemoveMax(&heap, &node))
			printf("���ֵ��%d\r\n",node.key);
	}
	MaxHeap_Destroy(&heap);
}