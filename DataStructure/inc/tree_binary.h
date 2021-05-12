#ifndef __BINARYTREE_H__
#define __BINARYTREE_H__
#include "type.h"
#include <iostream>
#include <string.h>
#include "stack.h"
#include "queue.h"
using namespace std;

template <typename T>
class BinaryTreeNode
{	
public:
	BinaryTreeNode(T node_dat, BinaryTreeNode<T> *left_node, BinaryTreeNode<T> *right_node, BinaryTreeNode<T> *parent_node)//���캯��
	{
		dat = node_dat;
		left = left_node;
		right = right_node;
		parent = parent_node;
	}
	BinaryTreeNode(BinaryTreeNode<T> *left_node, BinaryTreeNode<T> *right_node, BinaryTreeNode<T> *parent_node)//���캯��
	{
		left = left_node;
		right = right_node;
		parent = parent_node;
	}
	BinaryTreeNode()//����Ҫ�пղ�����Ĭ�Ϲ��캯��������������
	{
		//cout << "BinaryTreeNode()" << endl;
	}
	~BinaryTreeNode(){};//��������
	T vaule(){return dat};
	T dat;						//����
	BinaryTreeNode<T> *left;	//���ӽڵ�ָ��
	BinaryTreeNode<T> *right;	//���ӽڵ�ָ��
	BinaryTreeNode<T> *parent;	//ָ�򸸽ڵ�ָ��
};
template <typename T>
class BinaryTree:public BinaryTreeNode<T>//���м̳�
{
public:
	BinaryTree();//���캯��
	BinaryTree(T dat);
	~BinaryTree();//��������
	bool isEmpty();
	bool create(const T &dat, BinaryTree<T> &leftTree, BinaryTree<T> &rightTree);
	void deleteTree(BinaryTreeNode<T> *root);
	bool insertNode(BinaryTreeNode<T> *parent, T dat, unsigned char LeftRight);
	void preOrder(BinaryTreeNode<T> *root);//ǰ������
	void inOrder(BinaryTreeNode<T> *root);//��������
	void postOrder(BinaryTreeNode<T> *root);//��������
	void preOrderNonRecursion(BinaryTreeNode<T> *root);
	void inOrderNonRecursion(BinaryTreeNode<T> *root);
	void postOrderNonRecursion(BinaryTreeNode<T> *root);
	void levelOrder(BinaryTreeNode<T> *root);//������ζ�����
//private:
	BinaryTreeNode<T> *root;			//���������ڵ�
};

template <typename T>
class BinarySearchTree:public BinaryTree<T>//���м̳�
{
public:
	bool insertNode(BinaryTreeNode<T> *newpointer);
	BinaryTreeNode<T> *searchNode(T *dat);
	bool deleteNode(BinaryTreeNode<T> *pointer);
};

/************************************************************************/
/* ���ܣ����캯��                                                    
/* ���룺��
/* �������
/* ���أ���
/************************************************************************/
template <typename T>
BinaryTree<T>::BinaryTree()
{
	root = NULL;
}

template <typename T>
BinaryTree<T>::BinaryTree(T dat)
{
	root = new BinaryTreeNode<T>(dat, NULL, NULL, NULL);
}
/************************************************************************/
/* ���ܣ��������������ٶ�����                                                     
/* ���룺��
/* �������
/* ���أ���
/************************************************************************/
template <typename T>
BinaryTree<T>::~BinaryTree()
{
	deleteTree(root);
	//cout << "~BinaryTree()" << endl;
}
/************************************************************************/
/* ���ܣ��ж�һ���������Ƿ�Ϊ����                                                     
/* ���룺��
/* �������
/* ���أ��գ�TRUE ���ǿգ�FALSE
/************************************************************************/
template <typename T>
bool BinaryTree<T>::isEmpty()
{
	if(root == NULL)
		return TRUE;
	else
		return FALSE;
}

/************************************************************************/
/* ���ܣ�����һ��������
/* ���룺dat:���ڵ�����
/*       leftTree������
/*       rightTree������
/* �������
/* ���أ�TRUE or FALSE
/************************************************************************/
template <typename T>
bool BinaryTree<T>::create(const T &dat, BinaryTree<T> &leftTree, BinaryTree<T> &rightTree)
{
	root = new BinaryTreeNode<T>(dat, leftTree.root, rightTree.root, NULL);
	if(root == NULL)
	{
		cout << "�����ڴ�ʧ��" << endl;
		return FALSE;
	}
	leftTree.root->parent = root;//�������ĸ��ڵ�ָ���¸��ڵ�
	rightTree.root->parent = root;//�������ĸ��ڵ�ָ���¸��ڵ�
	leftTree = rightTree = NULL;//ԭ�����������ڵ���λ�գ���ֹ�Ƿ�����
	return TRUE;
}
/************************************************************************/
/* ���ܣ�ɾ��һ�������������ú������ɾ��
/* ���룺��
/* �������
/* ���أ�TRUE or FALSE
/************************************************************************/
template <typename T>
void BinaryTree<T>::deleteTree(BinaryTreeNode *root_node)
{
	if(root_node != NULL)
	{
		deleteTree(root->left);		//��������������
		deleteTree(root->right);		//��������������
		delete root;				//���ʵ�ǰ�ڵ�
		root = NULL;
	}
}
/************************************************************************/
/* ���ܣ���ĳ�ڵ�����½ڵ㣬��ʱ���Σ�����󣬺����ڵ���Ϊ���ӽڵ㻹�����ӽڵ㣿��
/* ���룺parent:���ڵ㣬�ڴ˽ڵ�����
/*		dat:Ҫ����ڵ������
/*		LeftRight�������ӽڵ���뻹�����ӽڵ����,0��1��
/* �������
/* ���أ�TRUE �ɹ���FALSE ʧ��
/************************************************************************/
template <typename  T>
bool BinaryTree<T>::insertNode(BinaryTreeNode<T> *parent, T dat, unsigned char LeftRight)
{
	/*if(isEmpty())//����������ڵ���Ϊ����
	{
		BinaryTreeNode<T> *currentnode = new BinaryTreeNode<T>(dat, NULL, NULL, NULL);//ʵ�������󲢳�ʼ��
		root = currentnode;
		return TRUE;
	}
	else if(parent == NULL)
	{
		cout << "����ڵ㴦Ϊ�գ��޷������½ڵ㣡" << endl;
		return FALSE;
	}

	BinaryTreeNode<T> *currentnode = new BinaryTreeNode<T>(dat, NULL, NULL, parent);//ʵ�������󲢳�ʼ��
	if(currentnode == NULL)
	{
		cout << "����ռ�ʧ��" << endl;
		return FALSE;
	}

	if(LeftRight)//�ڸ��ڵ���������
	{
		parent->right->parent = currentnode;
		parent->right = currentnode;						//���ڵ����ӽڵ�ָ��ǰ�ڵ�
	}
	else//�ڸ��ڵ���������
	{
		parent->left->parent = currentnode;
		parent->left = currentnode;							//���ڵ����ӽڵ�ָ��ǰ�ڵ�
	}*/
	return TRUE;	
}

/************************************************************************/
/* ���ʵ�ǰ�ڵ�����                                                     */
/* cunrrentnode:��ǰ�ڵ�
/* tree:��������ַ
/************************************************************************/
template <typename T>
static void visit(BinaryTreeNode<T> *currentnode)
{
	cout << currentnode->dat << endl;
}

/************************************************************************/
/* ǰ�����ζ�����                                                       */
/************************************************************************/
template <typename T>
void BinaryTree<T>::preOrder(BinaryTreeNode<T> *root_node)
{
	if(root_node != NULL)
	{
		visit(root_node);				//���ʵ�ǰ�ڵ�
		preOrder(root_node->left);		//ǰ������������
		preOrder(root_node->right);		//ǰ������������
	}
}
/************************************************************************/
/* �������ζ�����                                                       */
/************************************************************************/
template <typename T>
void BinaryTree<T>::inOrder(BinaryTreeNode<T> *root_node)
{
	if(root_node != NULL)
	{
		inOrder(root_node->left);		//��������������
		visit(root_node);				//���ʵ�ǰ�ڵ�
		inOrder(root_node->right);		//��������������
	}
}
/************************************************************************/
/* �������ζ�����                                                       */
/************************************************************************/
template <typename T>
void BinaryTree<T>::postOrder(BinaryTreeNode<T> *root_node)
{
	if(root_node != NULL)
	{
		postOrder(root_node->left);		//��������������
		postOrder(root_node->right);		//��������������
		visit(root_node);				//���ʵ�ǰ�ڵ�
	}
}
/************************************************************************/
/* ǰ�����ζ�����,�ǵݹ鷽��                                            */
/************************************************************************/
template <typename T>
void BinaryTree<T>::preOrderNonRecursion(BinaryTreeNode *root)
{
	BinaryTreeNode<T> *pointer = root;
	BinaryTreeNode<T> pointertemp;
	LinkStack<BinaryTreeNode<T>> stack;					//����ջ����

	if(isEmpty())
		return;
	while(pointer || !stack.isEmpty())					//ջ�ǿ�
	{
		visit(pointer);									//���ʵ�ǰ�ڵ�
		if(pointer->right != NULL)						//�ǿ����ӽڵ���ջ
			stack.push(*(pointer->right));
		if(pointer->left != NULL)						
			pointer = pointer->left;					//��·�½�
		else
		{
			if(stack.pop(&pointertemp))					//ջ��Ԫ����ջ
				pointer = pointertemp.parent->right;	//��ѹջ�����ҽڵ㣬ǰ���п����ҽڵ�Ϊ�գ��ǿ��ҽڵ㲻��ջ
			else
				pointer = NULL;
		}
	}
}
/************************************************************************/
/* �������ζ�����,�ǵݹ鷽��                                            */
/************************************************************************/
template <typename T>
void BinaryTree<T>::inOrderNonRecursion(BinaryTreeNode<T> *root)
{
	BinaryTreeNode<T> *pointer = root;
	BinaryTreeNode<T> pointertemp;
	LinkStack<BinaryTreeNode<T>> stack;

	if(isEmpty())
		return;
	while(pointer || !stack.isEmpty())					//ջ�ǿ�
	{
		if(pointer)
		{
			stack.push(*pointer);
			pointer = pointer->left;					//��·�½�
		}
		else
		{
			if(stack.pop(&pointertemp))					//ջ��Ԫ����ջ
			{
				visit(&pointertemp);					//���ʵ�ǰ�ڵ�
				pointer = pointertemp.right;			//ָ��ָ�����ӽڵ�
			}
			else
				pointer = NULL;
		}
	}
}
/************************************************************************/
/* �������ζ�����,�ǵݹ鷽��                                            */
/************************************************************************/
template <typename T>
void BinaryTree<T>::postOrderNonRecursion(BinaryTreeNode<T> *root)
{
	BinaryTreeNode<T> *pointer = root;
	BinaryTreeNode<T> *q = NULL;
	BinaryTreeNode<T> pointertemp;
	LinkStack<BinaryTreeNode<T>> stack;

	if(isEmpty())										//�����򷵻�
		return;
	while(pointer || !stack.isEmpty())					//ջ�ǿ�
	{
		while(pointer != NULL)							//�����ǰָ��ǿգ���ѹջ���½��������ӽڵ�
		{					
			stack.push(*pointer);				
			pointer = pointer->left;					//����·�½�
		}
		stack.getTop(&pointertemp);						//��·�½����ף�ȡջ��Ԫ�أ������һ�����ӽڵ�
		if(pointertemp.parent == NULL)					//���Ǹ��ڵ㸸�ڵ�Ϊ�յ����
			pointer = root;
		else if(pointertemp.parent->left)				//����ջ���ڵ㸸�ڵ�����ڵ����������Ȼջ���ڵ��Ȼ�Ǹ��ڵ���ҽڵ�
			pointer = pointertemp.parent->left;			
		else
			pointer = pointertemp.parent->right;
		if(pointer->right == NULL || pointer->right == q)//������������
		{
			visit(pointer);
			/* 1.���ȡ���Ľڵ��ҽڵ�Ϊ�գ���Ӧҳ�ڵ������� */
			/* 2.���ȡ���Ľڵ��ҽڵ����q����Ӧ���ӽڵ��Ѿ�������������� */
			/* ���������������Ҫ�����ڵ㵯��ջ */
			stack.pop(&pointertemp);				
			q = pointer;
			pointer = NULL;
		}
		else											//���������������
		{
			pointer = pointer->right;					//�����������أ�����������
		}
	}
}
/************************************************************************/
/* ������ζ�����                                                       */
/************************************************************************/
template <typename T>
void BinaryTree<T>::levelOrder(BinaryTreeNode<T> *root)
{
	BinaryTreeNode<T> *pointer = root;
	BinaryTreeNode<T> pointertemp, *q = NULL;
	LinkQueue<BinaryTreeNode<T>> queue;

	if(!isEmpty())
	{
		queue.en(*pointer);								//���ڵ������
	}
	while(!queue.isEmpty())								//���зǿ�
	{
		queue.de(&pointertemp);
		/* ����queue.de�������ݲ������ڵ㱾���ַ��Ϣ */
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
		visit(pointer);									//���ʵ�ǰ�ڵ�
		if(pointer->left != NULL)
			queue.en(*(pointer->left));					//������������
		if(pointer->right != NULL)
			queue.en(*(pointer->right));				//������������
	}
}

/******************************************** ���������� *******************************************************/

/*************************************************************************************/
/*���ܣ������������ڵ�����㷨�������������ݴ�С���Զ�ѡ����ʵĽڵ���롣
/*		���������϶������������ص㣬������С��������
/*���룺dat:�������½ڵ������
/*�������
/*���أ�TRUE or FALSE
/*************************************************************************************/
template <typename T>
bool BinarySearchTree<T>::insertNode(BinaryTreeNode<T> *newpointer)
{
	BinaryTreeNode<T> *pointer = NULL;
	BinaryTreeNode<T> *temp;
	T newvalue = 0,pointervalue = 0;
	uchar i = 0;

	/* ����Ϊ�գ����½ڵ���Ϊ����,�����¼���ڵ� */
	if(isEmpty())
	{
		root = newpointer;
		return TRUE;
	}
	else
		pointer = root;
	while(pointer != NULL)
	{
		if(newpointer->value() == pointer->value())			//�������Ԫ���򲻲���
		{
			cout << "���������Ԫ����ȵ�ֵ" << newpointer->dat <<endl;
			return FALSE;
		}
		else if(newpointer->value() < pointer->value())		//������ڵ�С�ڵ�ǰ�ڵ�ؼ���ֵ
		{
			if(pointer->left == NULL)						//���pointerû��������
			{
				temp = pointer->left;
				pointer->left = newpointer;					//newpointer��Ϊpointer������
				newpointer->parent = pointer;
				newpointer->left = temp;
				return TRUE;
			}
			else
				pointer = pointer->left;					//�����½�
		}
		else if(newpointer->value() > pointer->value())
		{
			if(pointer->right == NULL)						//���pointerû��������
			{
				temp = pointer->right;
				pointer->right = newpointer;				//newpointer��Ϊpointer������
				newpointer->parent = pointer;
				newpointer->right = temp;
				return TRUE;
			}
			else
				pointer = pointer->right;					//�����½�
		}
	}
	return FALSE;
}

/*************************************************************************************/
/*���ܣ��������������ҽڵ��㷨
/*���룺dat:Ҫ���ҽڵ�����ݵ�ָ��
/*�����
/*���أ���������ֵ�Ľڵ��ַ
/*************************************************************************************/
template <typename T>
BinaryTreeNode<T> *BinarySearchTree<T>::searchNode(T *dat)
{
	BinaryTreeNode<T> *pointer = NULL;

	if(isEmpty())						//����ǿ���
	{
		cout << "������Ϊ�գ�" << endl;
		return NULL;
	}
	else
		pointer = root;
	while(pointer != NULL)
	{
		if(*dat == pointer->value())									
		{
			cout << "�ҵ��� " << pointervalue << endl;
			return pointer;
		}
		else if(*dat < pointer->value())				//Ҫ���ҵ�ֵС�ڵ�ǰ�ڵ�ֵ���������
		{
			if(pointer->left == NULL)										
			{
				cout << "�˶������в����ڴ�ֵ��" << endl;
				return NULL;
			}
			else
				pointer = pointer->left;				//�����½�
		}
		else if(*dat > pointer->value())				//Ҫ���ҵ�ֵ���ڵ�ǰ�ڵ�ֵ�����Ҳ���
		{
			if(pointer->right == NULL)					//���pointerû��������
			{
				cout << "�˶������в����ڴ�ֵ��" << endl;
				return NULL;
			}
			else
				pointer = pointer->right;				//�����½�
		}
	}
	cout << "�˶������в����ڴ�ֵ��" << endl;
	return NULL;
}

/*************************************************************************************/
/*���ܣ������������ڵ�ɾ���㷨															 
/*���룺pointer:��ɾ���ڵ�
/*�������
/*���أ�TRUE or FALSE
/*************************************************************************************/
template <typename T>
bool BinarySearchTree<T>::deleteNode(BinaryTreeNode<T> *pointer)
{
	BinaryTreeNode_t *temppointer;							//���ڱ����滻��ɾ���ڵ�Ľڵ�
	BinaryTreeNode_t *tempparent = NULL;					//���ڱ����滻�ڵ�ĸ��ڵ�
	if(pointer == NULL)										//��ɾ���ڵ㲻����
	{
		cout << "�ڵ㲻���ڣ�" << endl;
		return FALSE;
	}
	if(pointer->left == NULL)								//�����ɾ���ڵ�������Ϊ��
		temppointer = pointer->right;						//�滻�ڵ㸳ֵΪ��������
	else													//�滻�ڵ���������Ϊ�գ�����������Ѱ�����ڵ���Ϊ�滻�ڵ�
	{
		temppointer = pointer->left;						//�滻�ڵ㸳ֵΪ������
		while(temppointer->right != NULL)					//Ѱ�������������ڵ㣬����·�½�����
		{
			tempparent = temppointer;						//�����滻�ڵ�ĸ��ڵ�
			temppointer = temppointer->right;				//�����½�
		}
		if(tempparent == NULL)								//����滻�ڵ���Ǳ�ɾ���ڵ�����ӽڵ㣬�򲻻���������whileѭ��
			pointer->left = temppointer->left;				//�滻�ڵ��������ҽӵ���ɾ���ڵ��������
		else
			tempparent->right = temppointer->left;			//�滻�ڵ����������Ϊ�丸�ڵ��������
		temppointer->left = pointer->left;					//�̳�pointer������
		temppointer->right = pointer->right;				//�̳�pointer��������
		temppointer->parent = pointer->parent;				//�̳�pointer�ĸ��ڵ�
	}

	//�������滻�ڵ�����ɾ���ڵ�
	if(pointer->parent == NULL)								//��ɾ���ڵ�Ϊ���ڵ�
		temppointer->parent = NULL;
	else if(pointer->parent->left == pointer)				//��ɾ���ڵ�����丸�ڵ��������
		pointer->parent->left = temppointer;
	else													//��ɾ���ڵ�����丸�ڵ��������
		pointer->parent->right = temppointer;				

	delete pointer;											//�ͷŽڵ��ڴ�
	pointer = NULL;
	return TRUE;
}


void testBinaryTree(void);
void testBinarySearchTree(void);

#endif