/*********************************************************************
*hufman树：
*参考资料：《数据结构与算法》张铭，王腾蛟，赵海燕等
*wangfeng
*E-mail:fengwang0301@163.com
*CSDN:https://blog.csdn.net/u013073067?spm=1001.2101.3001.5343
*GitHub:https://github.com/wangfeng0301
*2019.11.28-2021.2.5
*2021.5.17	创建Huffman树
**********************************************************************/
#include <iostream>

#include "queue.h"
#include "tree_huffman.h"
using namespace std;

void testHuffmanTree(void)
{
	//int weight[10]={10,20,30,40,50,45,35,25,15,5};//权值
	int weight[4]={10,20,30,40};//权值
	HuffmanTree<int> huffmantree(weight, weight, sizeof(weight)/sizeof(weight[0]));
	cout << "前序遍历：" << endl;
	huffmantree.preOrder(huffmantree.root);
	cout << "广度优先遍历：" << endl;
	huffmantree.levelOrder(huffmantree.root);

}