#ifndef __BINARYTREE_H__
#define __BINARYTREE_H__
#include "type.h"

template <typename T>
class BinaryTreeNode
{	
public:
	BinaryTreeNode(T node_dat, BinaryTreeNode *left_node, BinaryTreeNode *right_node, BinaryTreeNode *parent_node)//构造函数
	{
		dat = node_dat;
		left = left_node;
		right = right_node;
		parent = parent_node;
	}
	BinaryTreeNode(BinaryTreeNode *left_node, BinaryTreeNode *right_node, BinaryTreeNode *parent_node)//构造函数
	{
		left = left_node;
		right = right_node;
		parent = parent_node;
	}
	~BinaryTreeNode(){};//析构函数
	T vaule(){return dat};
	T dat;						//数据
	BinaryTreeNode<T> *left;	//左子节点指针
	BinaryTreeNode<T> *right;	//右子节点指针
	BinaryTreeNode<T> *parent;	//指向父节点指针
};
template <typename T>
class BinaryTree:public BinaryTreeNode<T>//公有继承
{
public:
	BinaryTree();//构造函数
	BinaryTree(T dat);
	~BinaryTree();//析构函数
	bool isEmpty();
	bool create(const T &dat, BinaryTree<T> &leftTree, BinaryTree<T> &rightTree);
	void deleteTree(BinaryTreeNode *root);
	bool insertNode(BinaryTreeNode<T> *parent, T dat, unsigned char LeftRight);
	void preOrder(BinaryTreeNode<T> *root);//前序周游
	void inOrder(BinaryTreeNode<T> *root);//中序周游
	void postOrder(BinaryTreeNode<T> *root);//后续周游
	void preOrderNonRecursion(BinaryTreeNode<T> *root);
	void inOrderNonRecursion(BinaryTreeNode<T> *root);
	void postOrderNonRecursion(BinaryTreeNode<T> *root);
	void levelOrder(BinaryTreeNode<T> *root);//广度周游二叉树
//private:
	BinaryTreeNode<T> *root;			//二叉树根节点
};

template <typename T>
class BinarySearchTree:public BinaryTree<T>//公有继承
{
public:
	bool insertNode(BinaryTreeNode<T> *newpointer);
	BinaryTreeNode<T> *searchNode(T *dat);
	bool deleteNode(BinaryTreeNode<T> *pointer);
};

void testBinaryTree(void);
void testBinarySearchTree(void);

#endif