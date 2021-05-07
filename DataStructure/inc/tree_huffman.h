#ifndef __HUFFMANTREE_H__
#define __HUFFMANTREE_H__
#include "type.h"

typedef struct HuffmanTreeNode
{
	int weight;						//�ڵ�Ȩ��
	void *dat;						//�ڵ���������
	struct HuffmanTreeNode *left;	//���ӽڵ�ָ��
	struct HuffmanTreeNode *right;	//���ӽڵ�ָ��
	struct HuffmanTreeNode *parent;	//ָ�򸸽ڵ�ָ��
}HuffmanTreeNode_t;
typedef struct 
{
	HuffmanTreeNode_t *root;
	uint datlen;					//�ڵ��������ͳ���
}HuffmanTree_t;

bool HuffmanTree_Create(HuffmanTree_t *tree, uint datlen, void *dat, int *weight, uint n);
void HuffmanTree_PreOrder(HuffmanTree_t *tree, HuffmanTreeNode_t *node);
void HuffmanTree_LevelOrder(HuffmanTree_t *tree, HuffmanTreeNode_t *root);

void testHuffmanTree(void);

#endif