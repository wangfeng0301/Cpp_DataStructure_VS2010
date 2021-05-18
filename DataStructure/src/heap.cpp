/************************************************************************
 *                 ��                                 
 *������ȫ���������Ա�洢������
 *�ο����ϣ������ݽṹ���㷨�������������ԣ��Ժ����
 *wangfeng
 *E-mail:fengwang0301@163.com
 *CSDN:https://blog.csdn.net/u013073067?spm=1001.2101.3001.5343
 *GitHub:https://github.com/wangfeng0301
 *2021.5.15 ���þ�̬��
 *2021.5.17 ʹ�ù��캯�������ѣ��޸�siftUp��������ֹ������ʱ����
 *          ������ʱ������������ݺͼ�ֵΪ�գ�
 *          removeʱ��ɾ���Ѷ��ڵ�������Ҫ�������ǣ�
************************************************************************/
#include <iostream>
#include <string.h>
#include "heap.h"
using namespace std;

void testHeap(void)
{
	//int HeapVal[9] = {9,9,7,6,20,4,33,2,1};
	//int key[9] =     {9,9,7,6,20,4,33,2,1};
	int HeapVal[4] = {9,90,7,6};
	int key[4] =     {9,9,7,6};
	int temp;
	int maxsize = 10;
	
	
	HeapNode<int> node;
	
	cout << "*************MinHeap*****************" << endl;
	//if(TRUE == min_heap.create(HeapVal, key, sizeof(HeapVal)/sizeof(HeapVal[0]), 10))
	//	min_heap.traverse();
	MinHeap<int> min_heap(HeapVal, key, sizeof(HeapVal)/sizeof(HeapVal[0]), 5);
	min_heap.traverse();
	for(int i = sizeof(HeapVal)/sizeof(HeapVal[0]); i < maxsize + 1; i++)
	{
		temp = i*10;
		if(TRUE == min_heap.insert(i, temp))
			min_heap.traverse();
		else
			break;
	}
	if(TRUE == min_heap.removeMin(&node))
		cout << "��Сֵ��" << node.key << endl;
	min_heap.traverse();
	if(TRUE == min_heap.remove(&node, 3))
		cout << "��ɾ�����ݣ�" << node.key << endl;
	min_heap.traverse();
	while(!min_heap.isEmpty())
	{
		if(TRUE == min_heap.removeMin(&node))
			cout << "��Сֵ��" << node.key << endl;
	}

	cout << "*************MaxHeap*****************" << endl;
	//if(TRUE == max_heap.create(HeapVal, key, sizeof(HeapVal)/sizeof(HeapVal[0]), 10))
	//	max_heap.traverse();
	MaxHeap<int> max_heap(HeapVal, key, sizeof(HeapVal)/sizeof(HeapVal[0]), 5);
	max_heap.traverse();
	for(int i = sizeof(HeapVal)/sizeof(HeapVal[0]); i < maxsize + 1; i++)
	{
		temp = i*10;
		if(TRUE == max_heap.insert(i, temp))
			max_heap.traverse();
		else
			break;
	}
	if(TRUE == max_heap.removeMax(&node))
		cout << "���ֵ��" << node.key << endl;
	max_heap.traverse();
	if(TRUE == max_heap.remove(&node, 3))
		cout << "��ɾ�����ݣ�" << node.key << endl;
	max_heap.traverse();
	while(!max_heap.isEmpty())
	{
		if(TRUE == max_heap.removeMax(&node))
			cout << "���ֵ��" << node.key << endl;
	}
}