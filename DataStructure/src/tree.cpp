#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

/*创建链式栈*/
static void CreatLinkStack(BinaryTreeStack_t *s)
{
	s->top = NULL;//初始化栈顶为空
	s->size = 0;//初始化栈大小为0
}
/*压栈*/
static void LSpush(BinaryTreeStack_t *s,BinaryTreeNode_t node)
{
	BinaryTreeLinkList_t *linklist_node = (BinaryTreeLinkList_t*)malloc(sizeof(BinaryTreeLinkList_t));//为新节点申请内存
	if(linklist_node == NULL)
	{
		printf("申请内存失败\r\n");
		return;
	}
	if(s->top == NULL)//第一个压栈的元素
	{
		s->top = linklist_node;
		s->top->next = NULL;
	}
	else
	{
		linklist_node->next = s->top;
		s->top = linklist_node;
	}
	s->size ++;//栈大小加1
	s->top->node = node;
}
/*出栈*/
static BinaryTreeNode_t LSpop(BinaryTreeStack_t *s)
{
	BinaryTreeNode_t temp;
	BinaryTreeStack_t *tempNode;
	if(s->top == NULL)
	{
		printf("栈空\r\n");
		return;
	}
	else//栈非空
	{
		temp = s->top->node;//提取节点
		tempNode = s->top;//保存当前节点
		s->top = s->top->next;//栈顶下移
		free(tempNode);//释放当前节点
		tempNode = NULL;
		s->size --;
		return temp;
	}
}
/*销毁栈*/
static void LSClear(BinaryTreeStack_t *s)
{
	BinaryTreeLinkList_t *tempNode;
	while(s->top != NULL)
	{
		tempNode = s->top->next;
		free(s->top);//释放栈顶
		s->top = tempNode;
	}
	if(s->top == NULL)
	{
		s->size = 0;
		printf("清栈成功\r\n");
	}
}

/*创建二叉树*/
void CreatBinaryTree()
{

}
/*判断二叉树是否为空*/
static bool isEmpty(struct BinaryTreeNode_t *T)
{
	if(T != NULL)
		return FALSE;
	else
		return TRUE;
}
/*操作树中的数据*/
static void visit(BinaryTreeEle_t element)
{
	printf("%d ",element.element);
}

/*深度优先周游分为三种方式：前序法、中序法、后序法。这里前中后是相对于根节点来说的*/
/*前序周游：先访问根节点，再访问左子树，最后访问右子树*/
void PreOrder(BinaryTreeNode_t *T)
{
	if(T == NULL)
		return;
	visit(T->element);
	PreOrder(T->lift);
	PreOrder(T->right);
}
/*中序周游：先访问左子树，再访问根节点，最后访问右子树*/
void InOrder(BinaryTreeNode_t *T)
{
	if(T == NULL)
		return;
	InOrder(T->lift);
	visit(T->element);
	InOrder(T->right);
}
/*后序周游：先访问左子树，再访问右子树，最后访问根节点*/
void PostOrder(BinaryTreeNode_t *T)
{
	if(T == NULL)
		return;
	PostOrder(T->lift);
	PostOrder(T->right);
	visit(T->element);
}

/*非递归前序周游*/
void PreOrderWithoutRecursion(BinaryTreeNode_t *T)
{
	BinaryTreeStack_t Stack;//定义栈
	//BinaryTreeNode_t tempNode;
	BinaryTreeNode_t *pointer = T;//二叉树节点

	CreatLinkStack(&Stack);//创建栈
	while(pointer)
	{
		visit(pointer->element);
		if(pointer->right != NULL)//右节点不为空，将右节点压栈
			LSpush(&Stack,*(pointer->right));
		if(pointer->lift != NULL)//左路下降
			pointer = pointer->lift;
		else//否则弹出栈顶元素
		{
			*pointer = LSpop(&Stack);
		}
	}

}
/*非递归中序周游*/
void InOrderWithoutRecursion(BinaryTreeNode_t *T)
{

}
/*非递归后序周游*/
void PostOrderWithoutRecursion(BinaryTreeNode_t *T)
{

}