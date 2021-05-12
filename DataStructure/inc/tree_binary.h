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
	BinaryTreeNode(T node_dat, BinaryTreeNode<T> *left_node, BinaryTreeNode<T> *right_node, BinaryTreeNode<T> *parent_node)//构造函数
	{
		dat = node_dat;
		left = left_node;
		right = right_node;
		parent = parent_node;
	}
	BinaryTreeNode(BinaryTreeNode<T> *left_node, BinaryTreeNode<T> *right_node, BinaryTreeNode<T> *parent_node)//构造函数
	{
		left = left_node;
		right = right_node;
		parent = parent_node;
	}
	BinaryTreeNode()//必须要有空参数的默认构造函数，否则编译出错
	{
		//cout << "BinaryTreeNode()" << endl;
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
	void deleteTree(BinaryTreeNode<T> *root);
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

/************************************************************************/
/* 功能：构造函数                                                    
/* 输入：无
/* 输出：无
/* 返回：无
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
/* 功能：析构函数，销毁二叉树                                                     
/* 输入：无
/* 输出：无
/* 返回：无
/************************************************************************/
template <typename T>
BinaryTree<T>::~BinaryTree()
{
	deleteTree(root);
	//cout << "~BinaryTree()" << endl;
}
/************************************************************************/
/* 功能：判断一个二叉树是否为空树                                                     
/* 输入：空
/* 输出：无
/* 返回：空，TRUE ；非空，FALSE
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
/* 功能：创建一个二叉树
/* 输入：dat:根节点数据
/*       leftTree左子树
/*       rightTree右子树
/* 输出：无
/* 返回：TRUE or FALSE
/************************************************************************/
template <typename T>
bool BinaryTree<T>::create(const T &dat, BinaryTree<T> &leftTree, BinaryTree<T> &rightTree)
{
	root = new BinaryTreeNode<T>(dat, leftTree.root, rightTree.root, NULL);
	if(root == NULL)
	{
		cout << "分配内存失败" << endl;
		return FALSE;
	}
	leftTree.root->parent = root;//左子树的父节点指向新根节点
	rightTree.root->parent = root;//右子树的父节点指向新根节点
	leftTree = rightTree = NULL;//原来两棵树根节点置位空，防止非法访问
	return TRUE;
}
/************************************************************************/
/* 功能：删除一个二叉树，利用后序遍历删除
/* 输入：无
/* 输出：无
/* 返回：TRUE or FALSE
/************************************************************************/
template <typename T>
void BinaryTree<T>::deleteTree(BinaryTreeNode *root_node)
{
	if(root_node != NULL)
	{
		deleteTree(root->left);		//后序周游左子树
		deleteTree(root->right);		//后序周游右子树
		delete root;				//访问当前节点
		root = NULL;
	}
}
/************************************************************************/
/* 功能：在某节点插入新节点，暂时屏蔽（插入后，后续节点作为左子节点还是右子节点？）
/* 输入：parent:父节点，在此节点后插入
/*		dat:要插入节点的数据
/*		LeftRight：在左子节点插入还是右子节点插入,0左；1右
/* 输出：无
/* 返回：TRUE 成功；FALSE 失败
/************************************************************************/
template <typename  T>
bool BinaryTree<T>::insertNode(BinaryTreeNode<T> *parent, T dat, unsigned char LeftRight)
{
	/*if(isEmpty())//空树，插入节点作为树根
	{
		BinaryTreeNode<T> *currentnode = new BinaryTreeNode<T>(dat, NULL, NULL, NULL);//实例化对象并初始化
		root = currentnode;
		return TRUE;
	}
	else if(parent == NULL)
	{
		cout << "插入节点处为空，无法插入新节点！" << endl;
		return FALSE;
	}

	BinaryTreeNode<T> *currentnode = new BinaryTreeNode<T>(dat, NULL, NULL, parent);//实例化对象并初始化
	if(currentnode == NULL)
	{
		cout << "申请空间失败" << endl;
		return FALSE;
	}

	if(LeftRight)//在父节点的右面插入
	{
		parent->right->parent = currentnode;
		parent->right = currentnode;						//父节点右子节点指向当前节点
	}
	else//在父节点的左面插入
	{
		parent->left->parent = currentnode;
		parent->left = currentnode;							//父节点左子节点指向当前节点
	}*/
	return TRUE;	
}

/************************************************************************/
/* 访问当前节点内容                                                     */
/* cunrrentnode:当前节点
/* tree:二叉树地址
/************************************************************************/
template <typename T>
static void visit(BinaryTreeNode<T> *currentnode)
{
	cout << currentnode->dat << endl;
}

/************************************************************************/
/* 前序周游二叉树                                                       */
/************************************************************************/
template <typename T>
void BinaryTree<T>::preOrder(BinaryTreeNode<T> *root_node)
{
	if(root_node != NULL)
	{
		visit(root_node);				//访问当前节点
		preOrder(root_node->left);		//前序周游左子树
		preOrder(root_node->right);		//前序周游右子树
	}
}
/************************************************************************/
/* 中序周游二叉树                                                       */
/************************************************************************/
template <typename T>
void BinaryTree<T>::inOrder(BinaryTreeNode<T> *root_node)
{
	if(root_node != NULL)
	{
		inOrder(root_node->left);		//中序周游左子树
		visit(root_node);				//访问当前节点
		inOrder(root_node->right);		//中序周游右子树
	}
}
/************************************************************************/
/* 后序周游二叉树                                                       */
/************************************************************************/
template <typename T>
void BinaryTree<T>::postOrder(BinaryTreeNode<T> *root_node)
{
	if(root_node != NULL)
	{
		postOrder(root_node->left);		//后序周游左子树
		postOrder(root_node->right);		//后序周游右子树
		visit(root_node);				//访问当前节点
	}
}
/************************************************************************/
/* 前序周游二叉树,非递归方法                                            */
/************************************************************************/
template <typename T>
void BinaryTree<T>::preOrderNonRecursion(BinaryTreeNode *root)
{
	BinaryTreeNode<T> *pointer = root;
	BinaryTreeNode<T> pointertemp;
	LinkStack<BinaryTreeNode<T>> stack;					//定义栈变量

	if(isEmpty())
		return;
	while(pointer || !stack.isEmpty())					//栈非空
	{
		visit(pointer);									//访问当前节点
		if(pointer->right != NULL)						//非空右子节点入栈
			stack.push(*(pointer->right));
		if(pointer->left != NULL)						
			pointer = pointer->left;					//左路下降
		else
		{
			if(stack.pop(&pointertemp))					//栈顶元素退栈
				pointer = pointertemp.parent->right;	//被压栈的是右节点，前面有可能右节点为空，非空右节点不入栈
			else
				pointer = NULL;
		}
	}
}
/************************************************************************/
/* 中序周游二叉树,非递归方法                                            */
/************************************************************************/
template <typename T>
void BinaryTree<T>::inOrderNonRecursion(BinaryTreeNode<T> *root)
{
	BinaryTreeNode<T> *pointer = root;
	BinaryTreeNode<T> pointertemp;
	LinkStack<BinaryTreeNode<T>> stack;

	if(isEmpty())
		return;
	while(pointer || !stack.isEmpty())					//栈非空
	{
		if(pointer)
		{
			stack.push(*pointer);
			pointer = pointer->left;					//左路下降
		}
		else
		{
			if(stack.pop(&pointertemp))					//栈顶元素退栈
			{
				visit(&pointertemp);					//访问当前节点
				pointer = pointertemp.right;			//指针指向右子节点
			}
			else
				pointer = NULL;
		}
	}
}
/************************************************************************/
/* 后序周游二叉树,非递归方法                                            */
/************************************************************************/
template <typename T>
void BinaryTree<T>::postOrderNonRecursion(BinaryTreeNode<T> *root)
{
	BinaryTreeNode<T> *pointer = root;
	BinaryTreeNode<T> *q = NULL;
	BinaryTreeNode<T> pointertemp;
	LinkStack<BinaryTreeNode<T>> stack;

	if(isEmpty())										//空树则返回
		return;
	while(pointer || !stack.isEmpty())					//栈非空
	{
		while(pointer != NULL)							//如果当前指针非空，则压栈并下降到最左子节点
		{					
			stack.push(*pointer);				
			pointer = pointer->left;					//从左路下降
		}
		stack.getTop(&pointertemp);						//左路下降到底，取栈顶元素，即最后一个左子节点
		if(pointertemp.parent == NULL)					//考虑根节点父节点为空的情况
			pointer = root;
		else if(pointertemp.parent->left)				//考虑栈顶节点父节点无左节点的情况，则必然栈顶节点必然是父节点的右节点
			pointer = pointertemp.parent->left;			
		else
			pointer = pointertemp.parent->right;
		if(pointer->right == NULL || pointer->right == q)//从右子树返回
		{
			visit(pointer);
			/* 1.如果取出的节点右节点为空（对应页节点的情况） */
			/* 2.如果取出的节点右节点等于q（对应右子节点已经遍历过的情况） */
			/* 上述两种情况都需要将本节点弹出栈 */
			stack.pop(&pointertemp);				
			q = pointer;
			pointer = NULL;
		}
		else											//如果从右子树返回
		{
			pointer = pointer->right;					//从左子树返回，访问右子树
		}
	}
}
/************************************************************************/
/* 广度周游二叉树                                                       */
/************************************************************************/
template <typename T>
void BinaryTree<T>::levelOrder(BinaryTreeNode<T> *root)
{
	BinaryTreeNode<T> *pointer = root;
	BinaryTreeNode<T> pointertemp, *q = NULL;
	LinkQueue<BinaryTreeNode<T>> queue;

	if(!isEmpty())
	{
		queue.en(*pointer);								//根节点入队列
	}
	while(!queue.isEmpty())								//队列非空
	{
		queue.de(&pointertemp);
		/* 由于queue.de弹出数据不包含节点本身地址信息 */
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
		visit(pointer);									//访问当前节点
		if(pointer->left != NULL)
			queue.en(*(pointer->left));					//左子树进队列
		if(pointer->right != NULL)
			queue.en(*(pointer->right));				//右子树进队列
	}
}

/******************************************** 二叉搜索树 *******************************************************/

/*************************************************************************************/
/*功能：二叉搜索树节点插入算法，按照输入数据大小，自动选择合适的节点插入。
/*		插入后需符合二叉搜索树的特点，即左树小，右树大
/*输入：dat:待插入新节点的数据
/*输出：无
/*返回：TRUE or FALSE
/*************************************************************************************/
template <typename T>
bool BinarySearchTree<T>::insertNode(BinaryTreeNode<T> *newpointer)
{
	BinaryTreeNode<T> *pointer = NULL;
	BinaryTreeNode<T> *temp;
	T newvalue = 0,pointervalue = 0;
	uchar i = 0;

	/* 若树为空，则新节点作为树根,否则记录根节点 */
	if(isEmpty())
	{
		root = newpointer;
		return TRUE;
	}
	else
		pointer = root;
	while(pointer != NULL)
	{
		if(newpointer->value() == pointer->value())			//存在相等元素则不插入
		{
			cout << "存在与插入元素相等的值" << newpointer->dat <<endl;
			return FALSE;
		}
		else if(newpointer->value() < pointer->value())		//待插入节点小于当前节点关键码值
		{
			if(pointer->left == NULL)						//如果pointer没有左子树
			{
				temp = pointer->left;
				pointer->left = newpointer;					//newpointer作为pointer左子树
				newpointer->parent = pointer;
				newpointer->left = temp;
				return TRUE;
			}
			else
				pointer = pointer->left;					//向左下降
		}
		else if(newpointer->value() > pointer->value())
		{
			if(pointer->right == NULL)						//如果pointer没有右子树
			{
				temp = pointer->right;
				pointer->right = newpointer;				//newpointer作为pointer右子树
				newpointer->parent = pointer;
				newpointer->right = temp;
				return TRUE;
			}
			else
				pointer = pointer->right;					//向右下降
		}
	}
	return FALSE;
}

/*************************************************************************************/
/*功能：二叉搜索树查找节点算法
/*输入：dat:要查找节点的数据的指针
/*输出：
/*返回：满足数据值的节点地址
/*************************************************************************************/
template <typename T>
BinaryTreeNode<T> *BinarySearchTree<T>::searchNode(T *dat)
{
	BinaryTreeNode<T> *pointer = NULL;

	if(isEmpty())						//如果是空树
	{
		cout << "二叉树为空！" << endl;
		return NULL;
	}
	else
		pointer = root;
	while(pointer != NULL)
	{
		if(*dat == pointer->value())									
		{
			cout << "找到： " << pointervalue << endl;
			return pointer;
		}
		else if(*dat < pointer->value())				//要查找的值小于当前节点值，向左查找
		{
			if(pointer->left == NULL)										
			{
				cout << "此二叉树中不存在此值！" << endl;
				return NULL;
			}
			else
				pointer = pointer->left;				//向左下降
		}
		else if(*dat > pointer->value())				//要查找的值大于当前节点值，向右查找
		{
			if(pointer->right == NULL)					//如果pointer没有右子树
			{
				cout << "此二叉树中不存在此值！" << endl;
				return NULL;
			}
			else
				pointer = pointer->right;				//向右下降
		}
	}
	cout << "此二叉树中不存在此值！" << endl;
	return NULL;
}

/*************************************************************************************/
/*功能：二叉搜索树节点删除算法															 
/*输入：pointer:待删除节点
/*输出：无
/*返回：TRUE or FALSE
/*************************************************************************************/
template <typename T>
bool BinarySearchTree<T>::deleteNode(BinaryTreeNode<T> *pointer)
{
	BinaryTreeNode_t *temppointer;							//用于保存替换被删除节点的节点
	BinaryTreeNode_t *tempparent = NULL;					//用于保存替换节点的父节点
	if(pointer == NULL)										//待删除节点不存在
	{
		cout << "节点不存在！" << endl;
		return FALSE;
	}
	if(pointer->left == NULL)								//如果待删除节点左子树为空
		temppointer = pointer->right;						//替换节点赋值为其右子树
	else													//替换节点左子树不为空，在左子树中寻找最大节点作为替换节点
	{
		temppointer = pointer->left;						//替换节点赋值为左子树
		while(temppointer->right != NULL)					//寻找左子树中最大节点，向右路下降即可
		{
			tempparent = temppointer;						//保存替换节点的父节点
			temppointer = temppointer->right;				//向右下降
		}
		if(tempparent == NULL)								//如果替换节点就是被删除节点的左子节点，则不会进入上面的while循环
			pointer->left = temppointer->left;				//替换节点左子树挂接到被删除节点的左子树
		else
			tempparent->right = temppointer->left;			//替换节点的左子树作为其父节点的右子树
		temppointer->left = pointer->left;					//继承pointer左子树
		temppointer->right = pointer->right;				//继承pointer的右子树
		temppointer->parent = pointer->parent;				//继承pointer的父节点
	}

	//下面用替换节点代替待删除节点
	if(pointer->parent == NULL)								//被删除节点为根节点
		temppointer->parent = NULL;
	else if(pointer->parent->left == pointer)				//被删除节点挂在其父节点的左子树
		pointer->parent->left = temppointer;
	else													//被删除节点挂在其父节点的右子树
		pointer->parent->right = temppointer;				

	delete pointer;											//释放节点内存
	pointer = NULL;
	return TRUE;
}


void testBinaryTree(void);
void testBinarySearchTree(void);

#endif