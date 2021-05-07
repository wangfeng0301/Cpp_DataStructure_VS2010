/*********************************************************************
*hufman树：
*参考资料：《数据结构与算法》张铭，王腾蛟，赵海燕等
*wangfeng
*E-mail:fengwang0301@163.com
*CSDN:https://blog.csdn.net/u013073067?spm=1001.2101.3001.5343
*GitHub:https://github.com/wangfeng0301
*2019.11.28-2021.2.5
*2021.2.5	创建Huffman树
**********************************************************************/
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "heap.h"
#include "queue.h"
#include "misc.h"
#include "tree_huffman.h"

/************************************************************************/
/*功能：创建Huffman树
/*输入：tree:huffman树地址
/*		datlen:节点数据类型长度
/*		dat:节点其他数据
/*		weight:节点权值（一个权值对应一个dat）
/*		n:节点数量
/*返回：TRUE or FALSE
/*由于哈夫曼树中没有度为1的结点，则一棵有n个叶子的哈夫曼树共有2×n-1个结点，
/*可以用一个大小为2×n-1 的一维数组存放哈夫曼树的各个结点。 由于每个结点同时
/*还包含其双亲信息和孩子结点的信息，所以构成一个静态三叉链表。
/*注意：外部传入的dat在函数内不做拷贝，直接使用原始数据地址
/************************************************************************/
bool HuffmanTree_Create(HuffmanTree_t *tree, uint datlen, void *dat, int *weight, uint n)
{
	uint i=0;
	uint totalnode = 2 * n - 1;					//Huffman树中节点数量
	HuffmanTreeNode_t *parentnode;				//父节点，合并时使用，新开辟的空间就是父节点
	HuffmanTreeNode_t firstchild,secondchild;	//存放从堆中弹出的包含最小值的节点的所有值
	HuffmanTreeNode_t *huffmantreenode;
	Heap_t heap;								//定义一个堆结构变量
	HeapNode_t heapnode;

	/* 先开辟n个HuffmanTreeNode结构体大小连续空间，作为叶节点 */
	huffmantreenode = (HuffmanTreeNode_t *)malloc(n * sizeof(HuffmanTreeNode_t));
	/* 建立一个空的最小堆，方便取最小值 */
	MinHeap_Create(&heap, NULL, sizeof(HuffmanTreeNode_t), weight, 0, n);
	/* 初始化n个节点互相独立，都是根节点 */
	for(i = 0;i < n;i++)
	{
		huffmantreenode[i].left = NULL;
		huffmantreenode[i].right = NULL;
		huffmantreenode[i].parent = NULL;
		huffmantreenode[i].dat = (void *)((uint)dat + i * datlen);//注意这里直接使用外部数据地址，不必开辟新地址赋值，节省时间
		huffmantreenode[i].weight = weight[i];	//权值初始化
		if(!MinHeap_Insert(&heap, huffmantreenode[i].weight, &huffmantreenode[i]))
			return FALSE;
	}
	MinHeap_Traverse(&heap);

	/* 通过n-1次合并得到Huffman树，n是叶节点个数 */
	for(i = 0;i < n-1;i ++)												
	{
		/* 前面已经开辟了n个空间,加上这n-1个，所以一共是2*n-1个节点 */
		parentnode = (HuffmanTreeNode_t *)malloc(sizeof(HuffmanTreeNode_t));

		/* 取两个最小权值的节点,firstchild节点中值<=secondchild节点中的值 */
		if(!MinHeap_RemoveMin(&heap, &heapnode))
			return FALSE;
		memcpy((void *)&firstchild, heapnode.dat, heap.datlen);
		if(!MinHeap_RemoveMin(&heap, &heapnode))
			return FALSE;
		memcpy((void *)&secondchild, heapnode.dat, heap.datlen);

		/*下面两个if语句是为了判断读出的两个节点是不是叶节点，如果是叶节点则放在连续空间huffmantree中*/
		if(firstchild.left == NULL && firstchild.right == NULL)		//左右子节点都是空，说明其是叶节点
		{
			/* 因为firstchild是实体节点，所以要将其值赋值给地址huffmantreenode */
			//huffmantree->left = firstchild.left;					//左右子节点不用赋值了，前面初始化的时候赋值过了，都指向NULL
			//huffmantree->right = firstchild.right;
			huffmantreenode->parent = parentnode;
			parentnode->left = huffmantreenode;						//父节点的左子节点指向当前
			huffmantreenode->weight = firstchild.weight;
			huffmantreenode->dat = firstchild.dat;					//对firstchild数据地址拷贝
			huffmantreenode ++;										//指向下一个叶节点
		}
		else														//如果子节点不是空，说明其不是叶节点,且其是别的叶节点的父节点
		{
			firstchild.left->parent->parent = parentnode;			//firstchild.left->parent就是其本身地址.
			parentnode->left = firstchild.left->parent;				//父节点的左子节点指向自己.
		}
		if(secondchild.left == NULL && secondchild.right == NULL)	//左右子节点都是空，说明其是叶节点
		{
			//huffmantree->left = secondchild.left;					//左右子节点不用赋值了，前面初始化的时候赋值过了，都指向NULL
			//huffmantree->right = secondchild.right;
			huffmantreenode->parent = parentnode;
			parentnode->right = huffmantreenode;					//父节点的右子节点指向当前
			huffmantreenode->weight = secondchild.weight;
			huffmantreenode->dat = firstchild.dat;					//对firstchild数据地址拷贝
			huffmantreenode ++;										//指向下一个叶节点
		}
		else
		{
			secondchild.right->parent->parent = parentnode;			//firstchild.left->parent就是其本身地址
			parentnode->right = secondchild.right->parent;			//父节点的左子节点指向自己
		}

		parentnode->parent = NULL;									//父节点的父节点指向空
		parentnode->weight = firstchild.weight+secondchild.weight;
		parentnode->dat = NULL;
		if(!MinHeap_Insert(&heap, parentnode->weight, parentnode))	//将父节点再放入堆中排序
			return FALSE;
	}
	MinHeap_Destroy(&heap);											//销毁最小堆，释放内存
	tree->root = parentnode;										//返回最后的父节点，就是Huffman树的根节点
	tree->datlen = datlen;
	return TRUE;														
}
/************************************************************************/
/*功能：销毁Huffman树（未完成）
/*输入：tree:huffman树地址
/*输出：无
/*返回：TRUE or FALSE
/************************************************************************/
bool HuffmanTree_Destroy(HuffmanTree_t *tree)
{

}
/************************************************************************/
/* 打印值 
/************************************************************************/
static void visit(HuffmanTree_t *tree, HuffmanTreeNode_t *node)
{
	printf("weight:%d \r\n",node->weight);
}
/************************************************************************/
/* 前序周游二叉树                                                       */
/************************************************************************/
void HuffmanTree_PreOrder(HuffmanTree_t *tree, HuffmanTreeNode_t *node)
{
	if(node != NULL)
	{
		visit(tree, node);							//访问当前节点
		HuffmanTree_PreOrder(tree, node->left);		//前序周游左子树
		HuffmanTree_PreOrder(tree, node->right);	//前序周游右子树
	}
}
/************************************************************************/
/* 广度周游二叉树                                                       */
/************************************************************************/
void HuffmanTree_LevelOrder(HuffmanTree_t *tree, HuffmanTreeNode_t *root)
{
	HuffmanTreeNode_t *pointer = root;
	HuffmanTreeNode_t pointertemp, *q = NULL;
	LinkQueue_t queue;
	LinkQueue_Create(&queue, sizeof(HuffmanTreeNode_t));	//创建队列
	if(pointer != NULL)
	{
		LinkQueue_En(&queue, pointer);					//根节点入队列
	}
	while(!LinkQueue_IsEmpty(&queue))					//队列非空
	{
		LinkQueue_De(&queue, &pointertemp);
		/* 由于LinkQueue_De弹出数据不包含节点本身地址信息 */
		/* 所以要判断出弹出节点的地址，以便后续循环 */
		if(pointertemp.parent == NULL)					//考虑出队列节点是根节点的情况
			pointer = root;
		/* q保存左子节点 */
		/* 还要考虑节点没有左节点的情况 */
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
		visit(tree, pointer);							//访问当前节点
		if(pointer->left != NULL)
			LinkQueue_En(&queue,pointer->left);			//左子树进队列
		if(pointer->right != NULL)
			LinkQueue_En(&queue,pointer->right);		//右子树进队列
	}
	LinkQueue_Destroy(&queue);
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

void testHuffmanTree(void)
{
	//int weight[10]={10,20,30,40,50,45,35,25,15,5};//权值
	int weight[4]={10,20,30,40};//权值
	HuffmanTree_t tree;								//定义

	if(HuffmanTree_Create(&tree, 0, NULL, weight,sizeof(weight)/sizeof(weight[0])))//构造hufffman树
	{
		printf("前序遍历：\r\n");
		HuffmanTree_PreOrder(&tree, tree.root);
		printf("广度优先遍历：\r\n");
		HuffmanTree_LevelOrder(&tree, tree.root);
	}
}