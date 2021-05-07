#ifndef __BINARYTREE_H__
#define __BINARYTREE_H__
#include "type.h"

template <typename T>
class BinaryTreeNode
{	
public:
	BinaryTreeNode(T node_dat, BinaryTreeNode *left_node, BinaryTreeNode *right_node, BinaryTreeNode *parent_node)//���캯��
	{
		dat = node_dat;
		left = left_node;
		right = right_node;
		parent = parent_node;
	}
	BinaryTreeNode(BinaryTreeNode *left_node, BinaryTreeNode *right_node, BinaryTreeNode *parent_node)//���캯��
	{
		left = left_node;
		right = right_node;
		parent = parent_node;
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
	void deleteTree(BinaryTreeNode *root);
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

void testBinaryTree(void);
void testBinarySearchTree(void);

#endif