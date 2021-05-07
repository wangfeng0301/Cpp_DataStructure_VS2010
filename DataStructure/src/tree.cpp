#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

/*������ʽջ*/
static void CreatLinkStack(BinaryTreeStack_t *s)
{
	s->top = NULL;//��ʼ��ջ��Ϊ��
	s->size = 0;//��ʼ��ջ��СΪ0
}
/*ѹջ*/
static void LSpush(BinaryTreeStack_t *s,BinaryTreeNode_t node)
{
	BinaryTreeLinkList_t *linklist_node = (BinaryTreeLinkList_t*)malloc(sizeof(BinaryTreeLinkList_t));//Ϊ�½ڵ������ڴ�
	if(linklist_node == NULL)
	{
		printf("�����ڴ�ʧ��\r\n");
		return;
	}
	if(s->top == NULL)//��һ��ѹջ��Ԫ��
	{
		s->top = linklist_node;
		s->top->next = NULL;
	}
	else
	{
		linklist_node->next = s->top;
		s->top = linklist_node;
	}
	s->size ++;//ջ��С��1
	s->top->node = node;
}
/*��ջ*/
static BinaryTreeNode_t LSpop(BinaryTreeStack_t *s)
{
	BinaryTreeNode_t temp;
	BinaryTreeStack_t *tempNode;
	if(s->top == NULL)
	{
		printf("ջ��\r\n");
		return;
	}
	else//ջ�ǿ�
	{
		temp = s->top->node;//��ȡ�ڵ�
		tempNode = s->top;//���浱ǰ�ڵ�
		s->top = s->top->next;//ջ������
		free(tempNode);//�ͷŵ�ǰ�ڵ�
		tempNode = NULL;
		s->size --;
		return temp;
	}
}
/*����ջ*/
static void LSClear(BinaryTreeStack_t *s)
{
	BinaryTreeLinkList_t *tempNode;
	while(s->top != NULL)
	{
		tempNode = s->top->next;
		free(s->top);//�ͷ�ջ��
		s->top = tempNode;
	}
	if(s->top == NULL)
	{
		s->size = 0;
		printf("��ջ�ɹ�\r\n");
	}
}

/*����������*/
void CreatBinaryTree()
{

}
/*�ж϶������Ƿ�Ϊ��*/
static bool isEmpty(struct BinaryTreeNode_t *T)
{
	if(T != NULL)
		return FALSE;
	else
		return TRUE;
}
/*�������е�����*/
static void visit(BinaryTreeEle_t element)
{
	printf("%d ",element.element);
}

/*����������η�Ϊ���ַ�ʽ��ǰ�򷨡����򷨡����򷨡�����ǰ�к�������ڸ��ڵ���˵��*/
/*ǰ�����Σ��ȷ��ʸ��ڵ㣬�ٷ�����������������������*/
void PreOrder(BinaryTreeNode_t *T)
{
	if(T == NULL)
		return;
	visit(T->element);
	PreOrder(T->lift);
	PreOrder(T->right);
}
/*�������Σ��ȷ������������ٷ��ʸ��ڵ㣬������������*/
void InOrder(BinaryTreeNode_t *T)
{
	if(T == NULL)
		return;
	InOrder(T->lift);
	visit(T->element);
	InOrder(T->right);
}
/*�������Σ��ȷ������������ٷ����������������ʸ��ڵ�*/
void PostOrder(BinaryTreeNode_t *T)
{
	if(T == NULL)
		return;
	PostOrder(T->lift);
	PostOrder(T->right);
	visit(T->element);
}

/*�ǵݹ�ǰ������*/
void PreOrderWithoutRecursion(BinaryTreeNode_t *T)
{
	BinaryTreeStack_t Stack;//����ջ
	//BinaryTreeNode_t tempNode;
	BinaryTreeNode_t *pointer = T;//�������ڵ�

	CreatLinkStack(&Stack);//����ջ
	while(pointer)
	{
		visit(pointer->element);
		if(pointer->right != NULL)//�ҽڵ㲻Ϊ�գ����ҽڵ�ѹջ
			LSpush(&Stack,*(pointer->right));
		if(pointer->lift != NULL)//��·�½�
			pointer = pointer->lift;
		else//���򵯳�ջ��Ԫ��
		{
			*pointer = LSpop(&Stack);
		}
	}

}
/*�ǵݹ���������*/
void InOrderWithoutRecursion(BinaryTreeNode_t *T)
{

}
/*�ǵݹ��������*/
void PostOrderWithoutRecursion(BinaryTreeNode_t *T)
{

}