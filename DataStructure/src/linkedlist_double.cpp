/************************************************************************
 *双向链表包括：创建链表、遍历链表、插入节点、修改某节点值、
 *				删除整个链表、删除某个节点
 *双向循环链表包括：创建链表、遍历链表、插入节点、修改某节点值、
 *				删除整个链表、删除某个节点
 *参考资料：《数据结构与算法》张铭，王腾蛟，赵海燕等
 *wangfeng
 *E-mail:fengwang0301@163.com
 *CSDN:https://blog.csdn.net/u013073067?spm=1001.2101.3001.5343
 *GitHub:https://github.com/wangfeng0301
 *2021.5.2  首次提交
 *2021.5.12 将类模板的实现和类定义放在一个文件中，即放在头文件中实现
 *         否则在某些时候调用时会出现错误
************************************************************************/
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "linkedlist_double.h"
using namespace std;

void testDoubleLink(void)
{
	int age[4] = {10,11,12,13};
	DoubleLink<int> teacher;//定义一个链表

	if(teacher.insertNode(age[0]))		//在表尾插入新节点
		teacher.traverse();		//遍历链表
	if(teacher.insertNode(age[1]))		//在表尾插入新节点
		teacher.traverse();		//遍历链表
	if(teacher.insertNode(age[2]))		//在表尾插入新节点
		teacher.traverse();		//遍历链表
	if(teacher.insertNode(age[3]))		//在表尾插入新节点
		teacher.traverse();		//遍历链表

	if(teacher.insertNode(4,14))		//在第n个节点前插入新节点
		teacher.traverse();		//遍历链表
	
	if(teacher.changeNodeValue(0, 1))	//修改第3个节点的值
		teacher.traverse();		//遍历链表
	
	if(teacher.deleteNode(2))		//删除节点
		teacher.traverse();		//遍历链表
	if(teacher.deleteNode())		//删除节点
		teacher.traverse();		//遍历链表
	
	if(teacher.clear())		//清除链表
		teacher.traverse();		//遍历链表

	
}

#if 0
void testCycDoubleLink(void)
{
	int age[4] = {10,11,12,13};
	int dat;
	DoubleLinkList_t people;

	if(CycDoubleLink_Create(&people, sizeof(age)/sizeof(age[0]), age, sizeof(age[0])))
		CycDoubleLink_Traverse(&people);		//遍历链表

	dat = 1;
	if(CycDoubleLink_InsertNode(&people, 4, &dat))		//在第n个节点前插入新节点
		CycDoubleLink_Traverse(&people);		//遍历链表
	
	dat = 2;
	if(CycDoubleLink_ChangeNodeValue(&people, 3, &dat))//修改第3个节点的值
		CycDoubleLink_Traverse(&people);		//遍历链表
	
	dat = 3;
	if(CycDoubleLink_AddNode(&people, &dat))		//在链尾插入新节点
		CycDoubleLink_Traverse(&people);		//遍历链表
	if(CycDoubleLink_AddNode(&people, &dat))		//在链尾插入新节点
		CycDoubleLink_Traverse(&people);		//遍历链表

	if(CycDoubleLink_DeleteNode(&people,12))	//删除节点
		CycDoubleLink_Traverse(&people);		//遍历链表

	if(CycDoubleLink_DeleteNode(&people,0))	//删除节点
		CycDoubleLink_Traverse(&people);		//遍历链表
	
	if(CycDoubleLink_Clear(&people))	//删除链表
		CycDoubleLink_Traverse(&people);		//遍历链表
	
	if(CycDoubleLink_Destroy(&people))	//删除链表
		CycDoubleLink_Traverse(&people);		//遍历链表
}
#endif