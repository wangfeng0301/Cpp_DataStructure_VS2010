#ifndef __TREE_H__
#define __TREE_H__
#include "type.h"

//���������ݽṹ��
typedef struct{
	int element;
}BinaryTreeEle_t;
//�������ڵ�ṹ��
typedef struct BinaryTreeNode_t{
	struct BinaryTreeNode_t *lift;
	struct BinaryTreeNode_t *right;
	struct BinaryTreeNode_t *parent;
	BinaryTreeEle_t element;//����
}BinaryTreeNode_t;

//����ṹ��
typedef struct BinaryTreeLinkList{
	struct BinaryTreeLinkList *next;
	//BinaryTreeEle_t element;//����������
	BinaryTreeNode_t node;//�������ڵ�
}BinaryTreeLinkList_t;
//��ʽջ�ṹ��
typedef struct{
	BinaryTreeLinkList_t *top;
	int size;//ջ��С
}BinaryTreeStack_t;


void testTree(void);
#endif