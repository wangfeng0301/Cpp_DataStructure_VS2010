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
/*���ܣ����캯��������Huffman��
/*���룺dat:����
/*      weight:�ڵ�Ȩֵ
/*		n:�ڵ�����
/*���أ���
/*ע�⣺dat��Ȩֵ����һһ��Ӧ
/************************************************************************/
template <typename T>
HuffmanTree<T>::HuffmanTree(T *dat, int *weight, int n)
{
	BinaryTreeNode<T> *parentnode;						//���ڵ㣬�ϲ�ʱʹ�ã��¿��ٵĿռ���Ǹ��ڵ�
	BinaryTreeNode<T> *leftnode,*rightnode;				//�����ӽڵ㣬���ڹ鲢
	BinaryTreeNode<T> *huffman_tree_node_list = new BinaryTreeNode<T>[n];
	/*ע�����ѵ�������BinaryTreeNode*/
	/*remove��ʱ�����ص���HeapNode�������ݣ������ͽڵ�������ݺ�Ȩֵ*/
	HeapNode<BinaryTreeNode<T>> firstchild,secondchild;	//��ŴӶ��е����İ�����Сֵ�Ľڵ������ֵ
	MinHeap<BinaryTreeNode<T>> min_heap(NULL,NULL,0,n);	//����һ���ѽṹ����

	/*���ݱ��浽BinaryTreeNode���������У��������ݺ�Ȩֵ������С��*/
	/*ע�����ݺ�Ȩֵ��һһ��Ӧ��*/
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

		/*��������С�����ӳ�һ����*/
		leftnode = new BinaryTreeNode<T>;
		rightnode = new BinaryTreeNode<T>;
		*leftnode = firstchild.dat;
		*rightnode = secondchild.dat;
		parentnode->left = leftnode;
		parentnode->right = rightnode;
		leftnode->parent = rightnode->parent = parentnode;
		/*���ڵ��ٴβ����*/
		min_heap.insert(firstchild.key + secondchild.key, *parentnode);
		//this->root = parentnode;
		BinaryTree::root = parentnode;
	}
	BinaryTree::root->parent = NULL;
	delete []huffman_tree_node_list;
	huffman_tree_node_list = NULL;
}
/************************************************************************/
/*���ܣ���������������Huffman��
/*���룺��
/*�������
/*���أ�TRUE or FALSE
/************************************************************************/
template <typename T>
HuffmanTree<T>::~HuffmanTree()
{
	//this->deleteTree(this->root);
	this->deleteTree(BinaryTree::root);
	cout << "~HuffmanTree()" <<endl;
}

/************************************************************************/
/*���ܣ�����Ȩֵ��·���˻�,���·��(δ���3)
/*���룺huffmantree:����ַ
/*		n:Ҷ�ڵ㣬��Ȩֵ����
/************************************************************************/
/*void HuffmanTree_Path(HuffmanTree_t *huffmantree, int n)
{
	HuffmanTreeNode_t *temp;
	printf("\r\n");
	while(n--)
	{
		temp = huffmantree->root;								//��λ�����ڵ�
		while(temp != NULL)								//δ����Ҷ�ڵ�֮ǰһֱѭ��
		{
			printf("%d ",temp->weight);				//�����ǰ�ڵ�
			temp = temp->left;
		}
		printf("\r\n");
	}

}*/

void testHuffmanTree(void);

#endif