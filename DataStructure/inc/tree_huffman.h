#ifndef __HUFFMANTREE_H__
#define __HUFFMANTREE_H__
#include "type.h"
#include "tree_binary.h"
#include "heap.h"
#include <iostream>
using namespace std;

template <typename T>
class HuffmanTree:public BinaryTree<T>
{
public:
	HuffmanTree(T *dat, int *weight, int n);
	~HuffmanTree();
//private:
	//BinaryTreeNode *root;
};

/************************************************************************/
/*功能：构造函数，创建Huffman树
/*输入：dat:数据
/*      weight:节点权值
/*		n:节点数量
/*返回：无
/*注意：dat和权值必须一一对应
/************************************************************************/
template <typename T>
HuffmanTree<T>::HuffmanTree(T *dat, int *weight, int n)
{
	BinaryTreeNode<T> *parentnode;						//父节点，合并时使用，新开辟的空间就是父节点
	BinaryTreeNode<T> *leftnode,*rightnode;				//左右子节点，用于归并
	BinaryTreeNode<T> *huffman_tree_node_list = new BinaryTreeNode<T>[n];
	/*注意插入堆的数据是BinaryTreeNode*/
	/*remove堆时，返回的是HeapNode类型数据，该类型节点包括数据和权值*/
	HeapNode<BinaryTreeNode<T>> firstchild,secondchild;	//存放从堆中弹出的包含最小值的节点的所有值
	MinHeap<BinaryTreeNode<T>> min_heap(NULL,NULL,0,n);	//定义一个堆结构变量

	/*数据保存到BinaryTreeNode的数据区中，并将数据和权值插入最小堆*/
	/*注意数据和权值是一一对应的*/
	for(int i = 0;i<n;i++)
	{
		huffman_tree_node_list[i].dat = dat[i];
		huffman_tree_node_list[i].parent = NULL;
		huffman_tree_node_list[i].left = NULL;
		huffman_tree_node_list[i].right = NULL;
		if(FALSE == min_heap.insert( weight[i], huffman_tree_node_list[i]))
			exit (-1);
	}
	for(int i = 0;i<n-1;i++)
	{
		parentnode = new BinaryTreeNode<T>;
		if(FALSE == min_heap.removeMin(&firstchild))
			exit (-1);
		if(FALSE == min_heap.removeMin(&secondchild))
			exit (-1);

		/*将两个最小的连接成一个树*/
		leftnode = new BinaryTreeNode<T>;
		rightnode = new BinaryTreeNode<T>;
		*leftnode = firstchild.dat;
		*rightnode = secondchild.dat;
		parentnode->left = leftnode;
		parentnode->right = rightnode;
		leftnode->parent = rightnode->parent = parentnode;
		/*父节点再次插入堆*/
		min_heap.insert(firstchild.key + secondchild.key, *parentnode);
		//this->root = parentnode;
		BinaryTree::root = parentnode;
	}
	BinaryTree::root->parent = NULL;
	delete []huffman_tree_node_list;
	huffman_tree_node_list = NULL;
}
/************************************************************************/
/*功能：析构函数，销毁Huffman树
/*输入：无
/*输出：无
/*返回：TRUE or FALSE
/************************************************************************/
template <typename T>
HuffmanTree<T>::~HuffmanTree()
{
	//this->deleteTree(this->root);
	this->deleteTree(BinaryTree::root);
	cout << "~HuffmanTree()" <<endl;
}

/************************************************************************/
/*功能：计算权值与路径乘积,输出路径(未完成3)
/*输入：huffmantree:树地址
/*		n:叶节点，即权值个数
/************************************************************************/
/*void HuffmanTree_Path(HuffmanTree_t *huffmantree, int n)
{
	HuffmanTreeNode_t *temp;
	printf("\r\n");
	while(n--)
	{
		temp = huffmantree->root;								//定位到根节点
		while(temp != NULL)								//未遇到叶节点之前一直循环
		{
			printf("%d ",temp->weight);				//输出当前节点
			temp = temp->left;
		}
		printf("\r\n");
	}

}*/

void testHuffmanTree(void);

#endif