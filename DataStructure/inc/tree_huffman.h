#ifndef __HUFFMANTREE_H__
#define __HUFFMANTREE_H__
#include "type.h"

typedef struct HuffmanTreeNode
{
	int weight;						//节点权重
	void *dat;						//节点其他数据
	struct HuffmanTreeNode *left;	//左子节点指针
	struct HuffmanTreeNode *right;	//右子节点指针
	struct HuffmanTreeNode *parent;	//指向父节点指针
}HuffmanTreeNode_t;
typedef struct 
{
	HuffmanTreeNode_t *root;
	uint datlen;					//节点数据类型长度
}HuffmanTree_t;

bool HuffmanTree_Create(HuffmanTree_t *tree, uint datlen, void *dat, int *weight, uint n);
void HuffmanTree_PreOrder(HuffmanTree_t *tree, HuffmanTreeNode_t *node);
void HuffmanTree_LevelOrder(HuffmanTree_t *tree, HuffmanTreeNode_t *root);

void testHuffmanTree(void);

#endif