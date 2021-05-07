/*********************************************************************
*hufman����
*�ο����ϣ������ݽṹ���㷨�������������ԣ��Ժ����
*wangfeng
*E-mail:fengwang0301@163.com
*CSDN:https://blog.csdn.net/u013073067?spm=1001.2101.3001.5343
*GitHub:https://github.com/wangfeng0301
*2019.11.28-2021.2.5
*2021.2.5	����Huffman��
**********************************************************************/
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "heap.h"
#include "queue.h"
#include "misc.h"
#include "tree_huffman.h"

/************************************************************************/
/*���ܣ�����Huffman��
/*���룺tree:huffman����ַ
/*		datlen:�ڵ��������ͳ���
/*		dat:�ڵ���������
/*		weight:�ڵ�Ȩֵ��һ��Ȩֵ��Ӧһ��dat��
/*		n:�ڵ�����
/*���أ�TRUE or FALSE
/*���ڹ���������û�ж�Ϊ1�Ľ�㣬��һ����n��Ҷ�ӵĹ�����������2��n-1����㣬
/*������һ����СΪ2��n-1 ��һά�����Ź��������ĸ�����㡣 ����ÿ�����ͬʱ
/*��������˫����Ϣ�ͺ��ӽ�����Ϣ�����Թ���һ����̬��������
/*ע�⣺�ⲿ�����dat�ں����ڲ���������ֱ��ʹ��ԭʼ���ݵ�ַ
/************************************************************************/
bool HuffmanTree_Create(HuffmanTree_t *tree, uint datlen, void *dat, int *weight, uint n)
{
	uint i=0;
	uint totalnode = 2 * n - 1;					//Huffman���нڵ�����
	HuffmanTreeNode_t *parentnode;				//���ڵ㣬�ϲ�ʱʹ�ã��¿��ٵĿռ���Ǹ��ڵ�
	HuffmanTreeNode_t firstchild,secondchild;	//��ŴӶ��е����İ�����Сֵ�Ľڵ������ֵ
	HuffmanTreeNode_t *huffmantreenode;
	Heap_t heap;								//����һ���ѽṹ����
	HeapNode_t heapnode;

	/* �ȿ���n��HuffmanTreeNode�ṹ���С�����ռ䣬��ΪҶ�ڵ� */
	huffmantreenode = (HuffmanTreeNode_t *)malloc(n * sizeof(HuffmanTreeNode_t));
	/* ����һ���յ���С�ѣ�����ȡ��Сֵ */
	MinHeap_Create(&heap, NULL, sizeof(HuffmanTreeNode_t), weight, 0, n);
	/* ��ʼ��n���ڵ㻥����������Ǹ��ڵ� */
	for(i = 0;i < n;i++)
	{
		huffmantreenode[i].left = NULL;
		huffmantreenode[i].right = NULL;
		huffmantreenode[i].parent = NULL;
		huffmantreenode[i].dat = (void *)((uint)dat + i * datlen);//ע������ֱ��ʹ���ⲿ���ݵ�ַ�����ؿ����µ�ַ��ֵ����ʡʱ��
		huffmantreenode[i].weight = weight[i];	//Ȩֵ��ʼ��
		if(!MinHeap_Insert(&heap, huffmantreenode[i].weight, &huffmantreenode[i]))
			return FALSE;
	}
	MinHeap_Traverse(&heap);

	/* ͨ��n-1�κϲ��õ�Huffman����n��Ҷ�ڵ���� */
	for(i = 0;i < n-1;i ++)												
	{
		/* ǰ���Ѿ�������n���ռ�,������n-1��������һ����2*n-1���ڵ� */
		parentnode = (HuffmanTreeNode_t *)malloc(sizeof(HuffmanTreeNode_t));

		/* ȡ������СȨֵ�Ľڵ�,firstchild�ڵ���ֵ<=secondchild�ڵ��е�ֵ */
		if(!MinHeap_RemoveMin(&heap, &heapnode))
			return FALSE;
		memcpy((void *)&firstchild, heapnode.dat, heap.datlen);
		if(!MinHeap_RemoveMin(&heap, &heapnode))
			return FALSE;
		memcpy((void *)&secondchild, heapnode.dat, heap.datlen);

		/*��������if�����Ϊ���ж϶����������ڵ��ǲ���Ҷ�ڵ㣬�����Ҷ�ڵ�����������ռ�huffmantree��*/
		if(firstchild.left == NULL && firstchild.right == NULL)		//�����ӽڵ㶼�ǿգ�˵������Ҷ�ڵ�
		{
			/* ��Ϊfirstchild��ʵ��ڵ㣬����Ҫ����ֵ��ֵ����ַhuffmantreenode */
			//huffmantree->left = firstchild.left;					//�����ӽڵ㲻�ø�ֵ�ˣ�ǰ���ʼ����ʱ��ֵ���ˣ���ָ��NULL
			//huffmantree->right = firstchild.right;
			huffmantreenode->parent = parentnode;
			parentnode->left = huffmantreenode;						//���ڵ�����ӽڵ�ָ��ǰ
			huffmantreenode->weight = firstchild.weight;
			huffmantreenode->dat = firstchild.dat;					//��firstchild���ݵ�ַ����
			huffmantreenode ++;										//ָ����һ��Ҷ�ڵ�
		}
		else														//����ӽڵ㲻�ǿգ�˵���䲻��Ҷ�ڵ�,�����Ǳ��Ҷ�ڵ�ĸ��ڵ�
		{
			firstchild.left->parent->parent = parentnode;			//firstchild.left->parent�����䱾���ַ.
			parentnode->left = firstchild.left->parent;				//���ڵ�����ӽڵ�ָ���Լ�.
		}
		if(secondchild.left == NULL && secondchild.right == NULL)	//�����ӽڵ㶼�ǿգ�˵������Ҷ�ڵ�
		{
			//huffmantree->left = secondchild.left;					//�����ӽڵ㲻�ø�ֵ�ˣ�ǰ���ʼ����ʱ��ֵ���ˣ���ָ��NULL
			//huffmantree->right = secondchild.right;
			huffmantreenode->parent = parentnode;
			parentnode->right = huffmantreenode;					//���ڵ�����ӽڵ�ָ��ǰ
			huffmantreenode->weight = secondchild.weight;
			huffmantreenode->dat = firstchild.dat;					//��firstchild���ݵ�ַ����
			huffmantreenode ++;										//ָ����һ��Ҷ�ڵ�
		}
		else
		{
			secondchild.right->parent->parent = parentnode;			//firstchild.left->parent�����䱾���ַ
			parentnode->right = secondchild.right->parent;			//���ڵ�����ӽڵ�ָ���Լ�
		}

		parentnode->parent = NULL;									//���ڵ�ĸ��ڵ�ָ���
		parentnode->weight = firstchild.weight+secondchild.weight;
		parentnode->dat = NULL;
		if(!MinHeap_Insert(&heap, parentnode->weight, parentnode))	//�����ڵ��ٷ����������
			return FALSE;
	}
	MinHeap_Destroy(&heap);											//������С�ѣ��ͷ��ڴ�
	tree->root = parentnode;										//�������ĸ��ڵ㣬����Huffman���ĸ��ڵ�
	tree->datlen = datlen;
	return TRUE;														
}
/************************************************************************/
/*���ܣ�����Huffman����δ��ɣ�
/*���룺tree:huffman����ַ
/*�������
/*���أ�TRUE or FALSE
/************************************************************************/
bool HuffmanTree_Destroy(HuffmanTree_t *tree)
{

}
/************************************************************************/
/* ��ӡֵ 
/************************************************************************/
static void visit(HuffmanTree_t *tree, HuffmanTreeNode_t *node)
{
	printf("weight:%d \r\n",node->weight);
}
/************************************************************************/
/* ǰ�����ζ�����                                                       */
/************************************************************************/
void HuffmanTree_PreOrder(HuffmanTree_t *tree, HuffmanTreeNode_t *node)
{
	if(node != NULL)
	{
		visit(tree, node);							//���ʵ�ǰ�ڵ�
		HuffmanTree_PreOrder(tree, node->left);		//ǰ������������
		HuffmanTree_PreOrder(tree, node->right);	//ǰ������������
	}
}
/************************************************************************/
/* ������ζ�����                                                       */
/************************************************************************/
void HuffmanTree_LevelOrder(HuffmanTree_t *tree, HuffmanTreeNode_t *root)
{
	HuffmanTreeNode_t *pointer = root;
	HuffmanTreeNode_t pointertemp, *q = NULL;
	LinkQueue_t queue;
	LinkQueue_Create(&queue, sizeof(HuffmanTreeNode_t));	//��������
	if(pointer != NULL)
	{
		LinkQueue_En(&queue, pointer);					//���ڵ������
	}
	while(!LinkQueue_IsEmpty(&queue))					//���зǿ�
	{
		LinkQueue_De(&queue, &pointertemp);
		/* ����LinkQueue_De�������ݲ������ڵ㱾���ַ��Ϣ */
		/* ����Ҫ�жϳ������ڵ�ĵ�ַ���Ա����ѭ�� */
		if(pointertemp.parent == NULL)					//���ǳ����нڵ��Ǹ��ڵ�����
			pointer = root;
		/* q�������ӽڵ� */
		/* ��Ҫ���ǽڵ�û����ڵ����� */
		else if(pointertemp.parent->left == q || pointertemp.parent->left == NULL)
		{
			pointer = pointertemp.parent->right;
			q = NULL;
		}
		else
		{
			pointer = pointertemp.parent->left;
			q = pointer;
		}
		visit(tree, pointer);							//���ʵ�ǰ�ڵ�
		if(pointer->left != NULL)
			LinkQueue_En(&queue,pointer->left);			//������������
		if(pointer->right != NULL)
			LinkQueue_En(&queue,pointer->right);		//������������
	}
	LinkQueue_Destroy(&queue);
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

void testHuffmanTree(void)
{
	//int weight[10]={10,20,30,40,50,45,35,25,15,5};//Ȩֵ
	int weight[4]={10,20,30,40};//Ȩֵ
	HuffmanTree_t tree;								//����

	if(HuffmanTree_Create(&tree, 0, NULL, weight,sizeof(weight)/sizeof(weight[0])))//����hufffman��
	{
		printf("ǰ�������\r\n");
		HuffmanTree_PreOrder(&tree, tree.root);
		printf("������ȱ�����\r\n");
		HuffmanTree_LevelOrder(&tree, tree.root);
	}
}