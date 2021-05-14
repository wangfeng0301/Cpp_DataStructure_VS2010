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
	cout <<"\r\n**************************µ¥Á´±í²âÊÔ**************************\r\n" << endl;
	//testLink();

	cout <<"\r\n**************************Ë«Á´±í²âÊÔ**************************\r\n" << endl;
	//testDoubleLink();

	cout <<"\r\n************************Ñ­»·Ë«Á´±í²âÊÔ************************\r\n" << endl;
	//testCycDoubleLink();

	cout <<"\r\n****************************Õ»²âÊÔ****************************\r\n" << endl;
	//testStack();

	cout <<"\r\n*************************Á´Ê½Õ»²âÊÔ***************************\r\n" << endl;
	//testLinkStack();
	
	cout <<"\r\n***************************¶ÓÁÐ²âÊÔ***************************\r\n" << endl;
	//testQueue();

	cout <<"\r\n************************Á´Ê½¶ÓÁÐ²âÊÔ**************************\r\n" << endl;
	//testLinkQueue();

	cout <<"\r\n*************************¶þ²æÊ÷²âÊÔ***************************\r\n" << endl;
	//testBinaryTree();

	cout <<"\r\n**********************¶þ²æËÑË÷Ê÷²âÊÔ**************************\r\n" << endl;
	testBinarySearchTree();

	cout <<"\r\n****************************¶Ñ²âÊÔ****************************\r\n" << endl;
	//testHeap();

	cout <<"\r\n*********************** HuffmanÊ÷²âÊÔ ************************\r\n" << endl;
	//testHuffmanTree();

	cout <<"\r\n***************************Ê÷²âÊÔ*****************************\r\n" << endl;
	//testTree();

	cout <<"\r\n**************************ÅÅÐò²âÊÔ****************************\r\n" << endl;
	//testSort();

	cout <<"\r\n******************** josephusÎÊÌâ²âÊÔ ************************\r\n" << endl;
	//josephus(5,2,2);

	cout <<"\r\n******************** ËÄÔòÔËËãÎÊÌâ²âÊÔ ************************\r\n" << endl;
	//testCalculator();

	cout <<"\r\n**************************µÝ¹é²âÊÔ****************************\r\n" << endl;
	//testRecursion();
	system("pause");
	return 0;
}



