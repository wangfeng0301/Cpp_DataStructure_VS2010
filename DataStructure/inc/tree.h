#ifndef __TREE_H__
#define __TREE_H__
#include "type.h"

//二叉树数据结构体
typedef struct{
	int element;
}BinaryTreeEle_t;
//二叉树节点结构体
typedef struct BinaryTreeNode_t{
	struct BinaryTreeNode_t *lift;
	struct BinaryTreeNode_t *right;
	struct BinaryTreeNode_t *parent;
	BinaryTreeEle_t element;//数据
}BinaryTreeNode_t;

//链表结构体
typedef struct BinaryTreeLinkList{
	struct BinaryTreeLinkList *next;
	//BinaryTreeEle_t element;//二叉树数据
	BinaryTreeNode_t node;//二叉树节点
}BinaryTreeLinkList_t;
//链式栈结构体
typedef struct{
	BinaryTreeLinkList_t *top;
	int size;//栈大小
}BinaryTreeStack_t;


void testTree(void);
#endif