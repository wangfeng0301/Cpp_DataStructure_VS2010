/*********************************************************************
*hufman����
*�ο����ϣ������ݽṹ���㷨�������������ԣ��Ժ����
*wangfeng
*E-mail:fengwang0301@163.com
*CSDN:https://blog.csdn.net/u013073067?spm=1001.2101.3001.5343
*GitHub:https://github.com/wangfeng0301
*2019.11.28-2021.2.5
*2021.5.17	����Huffman��
**********************************************************************/
#include <iostream>

#include "queue.h"
#include "tree_huffman.h"
using namespace std;

void testHuffmanTree(void)
{
	//int weight[10]={10,20,30,40,50,45,35,25,15,5};//Ȩֵ
	int weight[4]={10,20,30,40};//Ȩֵ
	HuffmanTree<int> huffmantree(weight, weight, sizeof(weight)/sizeof(weight[0]));
	cout << "ǰ�������" << endl;
	huffmantree.preOrder(huffmantree.root);
	cout << "������ȱ�����" << endl;
	huffmantree.levelOrder(huffmantree.root);

}