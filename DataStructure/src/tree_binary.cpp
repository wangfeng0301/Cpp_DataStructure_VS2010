/*********************************************************************
*二叉树：
*二叉搜索树：左子树所有节点小于该节点，右子树所有节点大于该节点
*			二叉搜索树所有节点值必须唯一；中序周游可得到由小到大序列
*参考资料：《数据结构与算法》张铭，王腾蛟，赵海燕等
*wangfeng
*E-mail:fengwang0301@163.com
*CSDN:https://blog.csdn.net/u013073067?spm=1001.2101.3001.5343
*GitHub:https://github.com/wangfeng0301
*2021.5.3 首次提交
*2021.5.12 将类模板的实现和类定义放在一个文件中，即放在头文件中实现
*         否则在某些时候调用时会出现错误
**********************************************************************/
#include <iostream>
#include <string.h>
#include "tree_binary.h"
using namespace std;


void testBinaryTree(void)
{
	BinaryTree<int> binary_tree;
	BinaryTree<int> binary_tree_left(10);
	BinaryTree<int> binary_tree_right(11);

	if(!binary_tree.create(12, binary_tree_left, binary_tree_right))//创建二叉树
	{
		cout << "创建二叉树失败" << endl;
		return;
	}

	//for(int i = 0;i<3;i++)//插入10个节点，按照二叉搜索树的形式排列大小
	//{
	//	binary_tree.insertNode(binary_tree.root, i, 0);
	//}
	cout << "中序遍历：" << endl;
	binary_tree.inOrder(binary_tree.root);
	cout << endl;
	binary_tree.inOrderNonRecursion(binary_tree.root);

	cout << "前序遍历：" << endl;
	binary_tree.preOrder(binary_tree.root);
	cout << endl;
	binary_tree.preOrderNonRecursion(binary_tree.root);

	cout << "后续遍历：" << endl;
	binary_tree.postOrder(binary_tree.root);
	cout << endl;
	binary_tree.postOrderNonRecursion(binary_tree.root);

	cout << "广度周游：" <<endl;
	binary_tree.levelOrder(binary_tree.root);
	cout << endl;

	/*cout << "删除二叉树" <<endl;
	binary_tree.deleteTree(binary_tree.root);

	cout << "广度周游：" <<endl;
	binary_tree.levelOrder(binary_tree.root);
	cout << endl;*/
}

void testBinarySearchTree(void)
{
	BinarySearchTree<int> binary_tree;
	BinarySearchTree<int> binary_tree_left(10);
	BinarySearchTree<int> binary_tree_right(11);
	//BinaryTreeNode<int> temp[5] = {10,11,12,13,14};//临时节点
	int val;

	if(!binary_tree.create(12, binary_tree_left, binary_tree_right))//创建二叉树
	{
		cout << "创建二叉树失败" << endl;
		return;
	}

	for(int i = 0;i<3;i++)//插入10个节点，按照二叉搜索树的形式排列大小
	{
		BinaryTreeNode<int> temp(i);
		binary_tree.insertNode(&temp);
	}
	cout << "中序遍历：" << endl;
	binary_tree.inOrder(binary_tree.root);
	cout << endl;
	binary_tree.inOrderNonRecursion(binary_tree.root);

	cout << "前序遍历：" << endl;
	binary_tree.preOrder(binary_tree.root);
	cout << endl;
	binary_tree.preOrderNonRecursion(binary_tree.root);

	cout << "后续遍历：" << endl;
	binary_tree.postOrder(binary_tree.root);
	cout << endl;
	binary_tree.postOrderNonRecursion(binary_tree.root);

	cout << "广度周游：" <<endl;
	binary_tree.levelOrder(binary_tree.root);
	cout << endl;

	if(NULL != (temp = binary_tree.searchNode(&val)))
		binary_tree.deleteNode(temp);//删除节点
	cout << "中序遍历：" << endl;
	binary_tree.inOrder(binary_tree.root);
	cout << endl;
	binary_tree.inOrderNonRecursion(binary_tree.root);
}