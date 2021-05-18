/************************************************************************
 *                 堆                                 
 *利用完全二叉树线性表存储堆数据
 *参考资料：《数据结构与算法》张铭，王腾蛟，赵海燕等
 *wangfeng
 *E-mail:fengwang0301@163.com
 *CSDN:https://blog.csdn.net/u013073067?spm=1001.2101.3001.5343
 *GitHub:https://github.com/wangfeng0301
 *2021.5.15 采用静态堆
 *2021.5.17 使用构造函数创建堆；修改siftUp函数，防止在最大堆时出错；
 *          创建堆时，允许传入的数据和键值为空；
 *          remove时，删除堆顶节点的情况需要单独考虑；
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
		cout << "最小值：" << node.key << endl;
	min_heap.traverse();
	if(TRUE == min_heap.remove(&node, 3))
		cout << "被删除数据：" << node.key << endl;
	min_heap.traverse();
	while(!min_heap.isEmpty())
	{
		if(TRUE == min_heap.removeMin(&node))
			cout << "最小值：" << node.key << endl;
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
		cout << "最大值：" << node.key << endl;
	max_heap.traverse();
	if(TRUE == max_heap.remove(&node, 3))
		cout << "被删除数据：" << node.key << endl;
	max_heap.traverse();
	while(!max_heap.isEmpty())
	{
		if(TRUE == max_heap.removeMax(&node))
			cout << "最大值：" << node.key << endl;
	}
}