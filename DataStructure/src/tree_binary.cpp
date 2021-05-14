/*********************************************************************
*��������
*���������������������нڵ�С�ڸýڵ㣬���������нڵ���ڸýڵ�
*			�������������нڵ�ֵ����Ψһ���������οɵõ���С��������
*�ο����ϣ������ݽṹ���㷨�������������ԣ��Ժ����
*wangfeng
*E-mail:fengwang0301@163.com
*CSDN:https://blog.csdn.net/u013073067?spm=1001.2101.3001.5343
*GitHub:https://github.com/wangfeng0301
*2021.5.3 �״��ύ
*2021.5.12 ����ģ���ʵ�ֺ��ඨ�����һ���ļ��У�������ͷ�ļ���ʵ��
*         ������ĳЩʱ�����ʱ����ִ���
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

	if(!binary_tree.create(12, binary_tree_left, binary_tree_right))//����������
	{
		cout << "����������ʧ��" << endl;
		return;
	}

	//for(int i = 0;i<3;i++)//����10���ڵ㣬���ն�������������ʽ���д�С
	//{
	//	binary_tree.insertNode(binary_tree.root, i, 0);
	//}
	cout << "���������" << endl;
	binary_tree.inOrder(binary_tree.root);
	cout << endl;
	binary_tree.inOrderNonRecursion(binary_tree.root);

	cout << "ǰ�������" << endl;
	binary_tree.preOrder(binary_tree.root);
	cout << endl;
	binary_tree.preOrderNonRecursion(binary_tree.root);

	cout << "����������" << endl;
	binary_tree.postOrder(binary_tree.root);
	cout << endl;
	binary_tree.postOrderNonRecursion(binary_tree.root);

	cout << "������Σ�" <<endl;
	binary_tree.levelOrder(binary_tree.root);
	cout << endl;

	/*cout << "ɾ��������" <<endl;
	binary_tree.deleteTree(binary_tree.root);

	cout << "������Σ�" <<endl;
	binary_tree.levelOrder(binary_tree.root);
	cout << endl;*/
}

void testBinarySearchTree(void)
{
	BinarySearchTree<int> binary_tree;
	BinarySearchTree<int> binary_tree_left(10);
	BinarySearchTree<int> binary_tree_right(11);
	//BinaryTreeNode<int> temp[5] = {10,11,12,13,14};//��ʱ�ڵ�
	int val;

	if(!binary_tree.create(12, binary_tree_left, binary_tree_right))//����������
	{
		cout << "����������ʧ��" << endl;
		return;
	}

	for(int i = 0;i<3;i++)//����10���ڵ㣬���ն�������������ʽ���д�С
	{
		BinaryTreeNode<int> temp(i);
		binary_tree.insertNode(&temp);
	}
	cout << "���������" << endl;
	binary_tree.inOrder(binary_tree.root);
	cout << endl;
	binary_tree.inOrderNonRecursion(binary_tree.root);

	cout << "ǰ�������" << endl;
	binary_tree.preOrder(binary_tree.root);
	cout << endl;
	binary_tree.preOrderNonRecursion(binary_tree.root);

	cout << "����������" << endl;
	binary_tree.postOrder(binary_tree.root);
	cout << endl;
	binary_tree.postOrderNonRecursion(binary_tree.root);

	cout << "������Σ�" <<endl;
	binary_tree.levelOrder(binary_tree.root);
	cout << endl;

	if(NULL != (temp = binary_tree.searchNode(&val)))
		binary_tree.deleteNode(temp);//ɾ���ڵ�
	cout << "���������" << endl;
	binary_tree.inOrder(binary_tree.root);
	cout << endl;
	binary_tree.inOrderNonRecursion(binary_tree.root);
}