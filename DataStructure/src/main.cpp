#include <iostream>
#include <string.h>
#include "linkedlist_single.h"
#include "linkedlist_double.h"
#include "stack.h"
#include "queue.h"
//#include "string_my.h"
#include "tree_binary.h"
//#include "heap.h"
//#include "tree.h"
//#include "sort.h"
//#include "application.h"
using namespace std;

int main()
{
	cout <<"\r\n**************************���������**************************\r\n" << endl;
	//testLink();

	cout <<"\r\n**************************˫�������**************************\r\n" << endl;
	//testDoubleLink();

	cout <<"\r\n************************ѭ��˫�������************************\r\n" << endl;
	//testCycDoubleLink();

	cout <<"\r\n****************************ջ����****************************\r\n" << endl;
	//testStack();

	cout <<"\r\n*************************��ʽջ����***************************\r\n" << endl;
	//testLinkStack();
	
	cout <<"\r\n***************************���в���***************************\r\n" << endl;
	//testQueue();

	cout <<"\r\n************************��ʽ���в���**************************\r\n" << endl;
	//testLinkQueue();

	cout <<"\r\n*************************����������***************************\r\n" << endl;
	//testBinaryTree();

	cout <<"\r\n**********************��������������**************************\r\n" << endl;
	testBinarySearchTree();

	cout <<"\r\n****************************�Ѳ���****************************\r\n" << endl;
	//testHeap();

	cout <<"\r\n*********************** Huffman������ ************************\r\n" << endl;
	//testHuffmanTree();

	cout <<"\r\n***************************������*****************************\r\n" << endl;
	//testTree();

	cout <<"\r\n**************************�������****************************\r\n" << endl;
	//testSort();

	cout <<"\r\n******************** josephus������� ************************\r\n" << endl;
	//josephus(5,2,2);

	cout <<"\r\n******************** ��������������� ************************\r\n" << endl;
	//testCalculator();

	cout <<"\r\n**************************�ݹ����****************************\r\n" << endl;
	//testRecursion();
	system("pause");
	return 0;
}



