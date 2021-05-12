/************************************************************************
 *单向链表包括：创建链表、遍历链表、插入节点、修改某节点值、
 *				删除整个链表、删除某个节点
 *参考资料：《数据结构与算法》张铭，王腾蛟，赵海燕等
 *wangfeng
 *E-mail:fengwang0301@163.com
 *CSDN:https://blog.csdn.net/u013073067?spm=1001.2101.3001.5343
 *GitHub:https://github.com/wangfeng0301
 *2021.5.1 首次提交
 *2021.5.12 将类模板的实现和类定义放在一个文件中，即放在头文件中实现
 *         否则在某些时候调用时会出现错误
************************************************************************/
#include "linkedlist_single.h"


void testLink(void)
{
	int age[3] = {10,11,12};
	Link<int> student;//定义一个链表

	if(student.insertNode(age[0]))//在链尾插入新节点
		student.traverse();//遍历链表
	if(student.insertNode(age[1]))//在链尾插入新节点
		student.traverse();//遍历链表
	if(student.insertNode(age[2]))//在链尾插入新节点
		student.traverse();//遍历链表
	
	if(student.changeNodeValue(0,1))//修改第0个节点的值
		student.traverse();//遍历链表

	if(student.insertNode(3,2))//在第n个节点前插入新节点
		student.traverse();//遍历链表
	if(student.insertNode(0,3))//在第n个节点前插入新节点
		student.traverse();//遍历链表

	if(student.deleteNode(0))//删除节点
		student.traverse();//遍历链表
	if(student.deleteNode())//删除尾节点
		student.traverse();//遍历链表
	
	if(student.reverse())//翻转链表
		student.traverse();//遍历链表

	if(student.clear())//翻转链表
		student.traverse();//遍历链表
}
