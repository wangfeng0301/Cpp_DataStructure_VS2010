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
 *2021.5.2  
************************************************************************/
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "linkedlist_double.h"
using namespace std;

/************************************************************************
 *功能：构造函数，创建双向链表
 *输入：
 *输出：无
 *返回：
************************************************************************/
template <typename T>
DoubleLink<T>::DoubleLink()
{
	head = tail = new DoubleLinkNode<T>(NULL, NULL);
	cout << "DoubleLink()" << endl;
}
/************************************************************************
 *功能：析构函数，销毁双向链表
 *输入：
 *输出：无
 *返回：
************************************************************************/
template <typename T>
DoubleLink<T>::~DoubleLink()
{
	DoubleLinkNode<T> *temp;
	while(head != NULL)
	{
		temp = head;
		head = temp->next;
		delete temp;
	}
	cout << "~DoubleLink()" << endl;
}
/************************************************************************
 *功能：判断链表是否存在
 *输入：list:链表起始地址
 *输出：无
 *返回：TRUE or FALSE
************************************************************************/
/*bool DoubleLink_IsExist(DoubleLinkList_t *list)
{
	if(list->node == NULL)
	{
		printf("链表不存在\r\n");
		return FALSE;
	}
	return TRUE;
}*/
/************************************************************************
 *功能：判断链表是否为空
 *输入：list:链表起始地址
 *输出：无
 *返回：TRUE or FALSE
************************************************************************/
template <typename T>
bool DoubleLink<T>::isEmpty()
{
	if(head->next == NULL)
	{
		cout << "链表为空" << endl;
		return TRUE;
	}
	else
		return FALSE;
}
/************************************************************************
 *功能：创建链表
 *输入：list:链表起始地址
 *		n 链表节点个数，不包含首节点
 *		dat:要传入的数据元素指针，若n=0,改参数可传NULL
 *		datlen:数据类型的长度
 *输出：list:链表地址
 *返回：TRUE or FALSE
************************************************************************/
/*bool DoubleLink_Create(DoubleLinkList_t *list, unsigned int n, void *dat, unsigned int datlen)
{
	unsigned int i=0;
	DoubleLinkNode_t *pHead,*pTail,*pNode;							//定义首节点、尾节点、普通节点

	pHead = (DoubleLinkNode_t *)malloc(sizeof(DoubleLinkNode_t));	//为首节点开辟空间，首节点没有数据
	if(pHead == NULL)
	{
		printf("首节点空间分配失败！\r\n");
		return FALSE;
	}
	pHead->pre = NULL;												//首节点前驱指向空
	pTail = pHead;													//尾节点指向首节点
	for(i=0;i<n;i++)
	{
		pNode = (DoubleLinkNode_t*)malloc(sizeof(DoubleLinkNode_t));//新开辟空间给新节点
		pNode->data = (void *)malloc(datlen);						//为普通节点分配数据内存
		if(pNode == NULL || pNode->data == NULL)
		{
			printf("新节点%d空间分配失败！\r\n",i);
			return FALSE;
		}
		//pNode->data = dat[i];
		memcpy(pNode->data, (void *)((unsigned int)dat+i*datlen), datlen);	//赋值
		pTail->next = pNode;										//新建节点的前一个节点后继指向自己
		pNode->pre = pTail;											//新建节点前驱指向前一个节点
		pTail = pNode;												//新节点赋值给尾节点，尾节点就变成了当前新建的节点
	}
	pTail->next = NULL;												//尾节点后继指向空，创建结束
	list->datlen = datlen;											//指定数据类型长度
	list->node = pHead;												//指定首节点
	list->node->data = NULL;										//一定要初始化首节点数据区
	return TRUE;
}*/

/************************************************************************
 *功能：遍历节点
 *输入：
 *输出：无
 *返回：TRUE or FALSE
************************************************************************/
template <typename T>
bool DoubleLink<T>::traverse()
{
	DoubleLinkNode<T> *p;

	printf("遍历链表：\r\n");
	if(isEmpty())
		return FALSE;
	p = head->next;													//临时节点指向第1个普通节点
	while(p != NULL)
	{
		cout << p->data << endl;
		p = p->next;												//指向下一个节点
	}
	return TRUE;
}

/************************************************************************
 *功能：修改节点n的值
 *输入：n:第n个节点,n从0开始算。只算普通节点
 *		list:链表地址
 *		dat:修改的值
 *输出：无
 *返回：TRUE or FALSE
************************************************************************/
template <typename T>
bool DoubleLink<T>::changeNodeValue(int n, T dat)
{
	DoubleLinkNode<T> *temp;

	cout << "修改节点" << n << "的值" << endl;
	if(isEmpty())
		return FALSE;
	temp = head->next;												//临时节点指向第一个有数据节点
	while(temp != NULL && n--)
	{
		temp = temp->next;											//指向下一个节点，直到到指定节点
	}
	if(temp != NULL)
	{	
		temp->data = dat;
		return TRUE;
	}
	else
	{
		printf("节点不存在！\r\n");
		return FALSE;
	}
}
/************************************************************************
 *功能：在第n个节点前插入节点，节点从0开始算，只算普通节点
 *输入：n:第n个节点
 *		dat:插入的值
 *输出：无
 *返回：TRUE or FALSE
************************************************************************/
template <typename T>
bool DoubleLink<T>::insertNode(int n, T dat)
{
	DoubleLinkNode<T> *temp,*pNewNode;								//临时节点

	cout << "在节点" << n << "前插入新节点" << endl;
	if(isEmpty())
		return FALSE;
	temp = head;												//临时节点指向首节点
	while(temp != NULL && n--)
	{
		temp = temp->next;											//指向下一个节点，直到指向指定节点
	}
	if(temp != NULL)												//注意现在temp是指定节点的前一个节点
	{
		pNewNode = new DoubleLinkNode<T>(dat, temp, temp->next);//为新节点分配内存，并赋值
		if(pNewNode == NULL)
		{
			cout <<"新节点空间分配失败！" << endl;
			return FALSE;
		}
		if(pNewNode->next == NULL)									//新节点后继是NULL，表示新节点是尾节点
		{
			tail = pNewNode;
			pNewNode->pre->next = pNewNode;
		}
		else
		{
			pNewNode->pre->next = pNewNode;
			pNewNode->next->pre = pNewNode;
		}
		return TRUE;
	}
	else
	{
		cout << "该节点不存在！" << endl;
		return FALSE;
	}
}
/************************************************************************
 *功能：在表尾插入节点
 *输入：n:第n个节点
 *		dat:插入的值
 *输出：无
 *返回：TRUE or FALSE
************************************************************************/
template <typename T>
bool DoubleLink<T>::insertNode(T dat)
{
	DoubleLinkNode<T> *pNewNode;

	cout << "在表尾插入新节点" << endl;
	if(isEmpty())
	{
		pNewNode = new DoubleLinkNode<T>(dat, head, NULL);//为新节点分配内存，并赋值
	}
	else
	{
		pNewNode = new DoubleLinkNode<T>(dat, tail->pre, tail->next);//为新节点分配内存，并赋值

	}
	if(pNewNode == NULL)
	{
		cout <<"新节点空间分配失败！" << endl;
		return FALSE;
	}
	if(head->next == NULL)//空
		head->next = pNewNode;
	else
		tail->next = pNewNode;
	tail = pNewNode;
	return TRUE;
}
/************************************************************************
 *功能：获取第n个节点的数据，节点从0开始算，只算普通节点
 *输入：n:第n个节点
 *输出：dat:获取的数据
 *返回：TRUE or FALSE
************************************************************************/
template <typename T>
bool DoubleLink<T>::getNodeValue(int n, T *dat)
{
	DoubleLinkNode<T> *temp;											//临时节点
											
	cout << "获取节点" << n "的数据" << endl;
	if(isEmpty(list))
		return FALSE;
	temp = head->next;										//临时节点指向第一个普通节点
	while(temp != NULL && n--)
	{
		temp = temp->next;											//指向下一个节点，直到指向指定节点
	}
	if(temp != NULL)
	{
		dat = temp->data;
		return TRUE;
	}
	else
	{
		cout << "该节点不存在!" << endl;
		return FALSE;
	}
}
/************************************************************************
 *功能：删除第n个节点，n从0开始算，只算普通节点
 *输入：n:第n个节点,从0开始算
 *输出：无
 *返回：无
************************************************************************/
template <typename T>
bool DoubleLink<T>::deleteNode(int n)
{
	DoubleLinkNode<T> *temp,*pDeleteNode;							//临时节点

	cout << "删除节点" << n << endl;
	if(isEmpty())
		return FALSE;
	temp = head;												//临时节点指向首节点
	while(temp!=NULL && n--)
	{
		temp = temp->next;											//指向下一个节点，直到指向指定节点
	}
	if(temp->next != NULL)											//注意现在temp是指定节点的前一个节点,不能删除首节点
	{
		pDeleteNode = temp->next;									//temp后继是要删除的节点
		temp->next = pDeleteNode->next;								//前一个节点后继		
		if(pDeleteNode->next != NULL)								//后一个节点不是NULL，表示后一个节点不是尾节点，否则不执行下面操作
		{
			temp = pDeleteNode->next;								//临时节点赋值为要删除节点的后一个节点
			temp->pre = pDeleteNode->pre;							//后一个节点前驱
		}
		if(pDeleteNode == tail)										//要删除的节点是表尾节点
		{
			tail = pDeleteNode->pre;
			tail->next = NULL;
		}
		delete pDeleteNode;
		pDeleteNode = NULL;
		return TRUE;
	}
	else
	{
		cout << "节点不存在！" << endl;
		return FALSE;
	}
}
/************************************************************************
 *功能：删除链表尾节点
 *输入：
 *输出：无
 *返回：无
************************************************************************/
template <typename T>
bool DoubleLink<T>::deleteNode()
{
	DoubleLinkNode<T> *pDeleteNode;							//临时节点

	cout << "删除表尾节点" << endl;
	if(isEmpty())
		return FALSE;
	pDeleteNode = tail;
	tail = pDeleteNode->pre;
	tail->next = NULL;
	delete pDeleteNode;
	pDeleteNode = NULL;
	return TRUE;
}
/************************************************************************
 *功能：清除整个链表，保留链表头
 *输入：
 *输出：无
 *返回：TRUE or FALSE
************************************************************************/
template <typename T>
bool DoubleLink<T>::clear()
{
	DoubleLinkNode<T> *temp,*p;										//临时节点

	if(isEmpty())
		return FALSE;
	temp = head->next;												//临时节点指向首节点
	while(temp != NULL)
	{
		p = temp->next;												//当前节点后继赋值给p
		delete temp;												//释放当前节点内存
		temp = p;
	}
	if(temp == NULL)
	{
		head->next = NULL;											//首节点指向空指针
		tail = head;
		cout << "清除链表成功！" << endl;
		return TRUE;
	}
	return FALSE;
}

/************************************************************************
 *功能：销毁整个链表，不保留链表头
 *输入：list:链表地址
 *输出：无
 *返回：TRUE or FALSE
************************************************************************/
/*bool DoubleLink_Destroy(DoubleLinkList_t *list)
{
	DoubleLinkNode_t *temp,*p;										//临时节点

	if(!DoubleLink_IsExist(list))
		return FALSE;
	temp = list->node;												//临时节点指向首节点
	list->datlen = 0;												//链表数据长度清零
	list->node = NULL;												//首节点指向空指针
	while(temp != NULL)
	{
		p = temp->next;												//当前节点后继赋值给p
		if(temp->data != NULL)
			free(temp->data);										//释放数据地址,注意释放的顺序不能换
		temp->data = NULL;
		free(temp);													//释放当前节点内存
		temp = p;
	}
	if(temp==NULL)
	{
		//free(p);													//释放临时变量
		//p = NULL;
		printf("销毁链表成功！\r\n");
		return TRUE;
	}
	return FALSE;
}*/



#if 0
/***************************************循环链表***********************************************************/
/************************************************************************
 *功能：判断链表是否存在
 *输入：list:链表起始地址
 *输出：无
 *返回：TRUE or FALSE
************************************************************************/
bool CycDoubleLink_IsExist(DoubleLinkList_t *list)
{
	if(list->node == NULL)
	{
		printf("链表不存在\r\n");
		return FALSE;
	}
	return TRUE;
}
/************************************************************************
 *功能：判断链表是否为空
 *输入：list:链表起始地址
 *输出：无
 *返回：TRUE or FALSE
************************************************************************/
bool CycDoubleLink_IsEmpty(DoubleLinkList_t *list)
{
	if(DoubleLink_IsExist(list))
	{
		if(list->node->next != list->node)
			return TRUE;
		else
			printf("链表为空\r\n");
	}
	return FALSE;
}
/************************************************************************
 *功能：创建链表
 *输入：list:链表地址
 *		n: 链表节点个数，不包含首节点
 *		dat:要传入的数据元素指针，若n=0,改参数可传NULL
 *输出：list:链表地址
 *返回：TRUE or FALSE
************************************************************************/
bool CycDoubleLink_Create(DoubleLinkList_t *list, unsigned int n, void *dat, unsigned int datlen)
{
	unsigned int i=0;
	DoubleLinkNode_t *pHead,*pTail,*pNode;							//定义首节点、尾节点、普通节点

	pHead = (DoubleLinkNode_t *)malloc(sizeof(DoubleLinkNode_t));	//为首节点开辟空间，首节点没有数据
	if(pHead == NULL)
	{
		printf("首节点空间分配失败！\r\n");
		return FALSE;
	}
	pTail = pHead;//尾节点指向首节点
	for(i=0;i<n;i++)
	{
		pNode = (DoubleLinkNode_t*)malloc(sizeof(DoubleLinkNode_t));//新开辟空间给新节点
		pNode->data = (void *)malloc(datlen);						//为普通节点分配数据内存
		if(pNode == NULL || pNode->data == NULL)
		{
			printf("新节点%d空间分配失败！\r\n",i);
			return FALSE;
		}
		//pNode->data = dat[i];
		memcpy(pNode->data, (void *)((unsigned int)dat+i*datlen), datlen);//赋值
		pTail->next = pNode;										//新建节点的前一个节点后继指向自己
		pNode->pre = pTail;											//新建节点前驱指向前一个节点
		pTail = pNode;												//新节点赋值给尾节点，尾节点就变成了当前新建的节点
	}
	pHead->pre = pTail;												//首节点前驱指向尾节点
	pTail->next = pHead;											//尾节点后继指向首节点，创建结束
	list->datlen = datlen;											//指定数据类型长度
	list->node = pHead;												//指定首节点
	list->node->data = NULL;										//一定要初始化首节点数据区
	return TRUE;
}

/************************************************************************
 *功能：遍历节点
 *输入：list:链表地址
 *输出：无
 *返回：TRUE or FALSE
************************************************************************/
bool CycDoubleLink_Traverse(DoubleLinkList_t *list)
{
	DoubleLinkNode_t *p;				
	uchar temp[32];

	printf("遍历链表：\r\n");
	if(!CycDoubleLink_IsEmpty(list))
		return FALSE;
	p = list->node->next;											//首节点没有数据，所以临时节点指向第一个普通节点
	while(p != list->node)
	{
		memcpy(temp,p->data,list->datlen);
		printf("%d\r\n",*temp);										//打印节点数据
		p = p->next;												//指向下一个节点
	}
	return TRUE;
}

/************************************************************************
 *功能：修改节点n的值
 *输入：n:第n个节点,n从0开始算。只算普通节点
 *		list:链表地址
 *		dat:改变节点的值
 *输出：无
 *返回：TRUE or FALSE
************************************************************************/
bool CycDoubleLink_ChangeNodeValue(DoubleLinkList_t * list,unsigned int n, void *dat)
{
	unsigned int i = n;
	DoubleLinkNode_t* temp;

	if(!CycDoubleLink_IsEmpty(list))
		return FALSE;
	temp = list->node->next;										//临时节点指向第一个有数据节点
	while(i--)														//循环链表，可以循环查询。如链表长度为3，输入4，指定到节点0
	{
		temp = temp->next;											//指向下一个节点，直到到指定节点
		if(temp == list->node)										//循环到表尾，从头开始计数
		{
			temp = temp->next;
		}
	}
	if(temp != list->node)
	{	
		printf("修改节点%d\r\n",n);
		//temp->data = dat;
		memcpy(temp->data,dat,list->datlen);
		return TRUE;
	} 
	else
	{
		printf("节点不存在！\r\n");
		return FALSE;
	}
}

/************************************************************************
 *功能：在第n个节点前插入节点，节点从0开始算，只算普通节点
 *输入：list:链表地址
 *		n:第n个节点
 *		dat:插入节点的值
 *输出：无
 *返回：TRUE or FALSE
************************************************************************/
bool CycDoubleLink_InsertNode(DoubleLinkList_t *list,unsigned int n, void *dat)
{
	unsigned int i = n;
	DoubleLinkNode_t *temp, *pNewNode;								//临时节点

	printf("在节点%d之前插入新节点\r\n",n);
	if(!CycDoubleLink_IsEmpty(list))
		return FALSE;
	temp = list->node;												//临时节点指向首节点
	while(i--)														//循环链表，可以循环查询。如链表长度为3，输入4，指定到节点0
	{
		temp = temp->next;											//指向下一个节点，直到指向指定节点
		if(temp == list->node)										//循环到表尾，从头开始计数
		{
			temp = temp->next;
		}
	}
	if(temp != list->node)											//注意现在temp是指定节点的前一个节点
	{
		pNewNode = (DoubleLinkNode_t*)malloc(sizeof(DoubleLinkNode_t));//为新节点分配内存
		pNewNode->data = (void *)malloc(list->datlen);				//为普通节点分配数据内存
		if(pNewNode == NULL)
		{
			printf("新节点空间分配失败！\r\n");
			return FALSE;
		}
		//pNewNode->data = dat;
		memcpy(pNewNode->data,dat,list->datlen);
		pNewNode->next = temp->next;								//新节点后继
		temp->next = pNewNode;										//前一个节点后继为新节点
		pNewNode->pre = temp;										//新节点前驱为前一个节点
		temp = pNewNode->next;										//临时节点指向新节点的后继
		temp->pre = pNewNode;										//后一个节点前驱指向新节点
		return TRUE;
	}
	else
	{
		printf("该节点不存在！\r\n");
		return FALSE;
	}
}

/************************************************************************
 *功能：在表尾增加节点
 *输入：list:链表地址
 *		dat:插入节点的值
 *输出：无
 *返回：TRUE or FALSE
************************************************************************/
bool CycDoubleLink_AddNode(DoubleLinkList_t *list, void *dat)
{
	DoubleLinkNode_t *temp,*pNewNode;								//临时节点

	printf("在表尾插入新节点\r\n");
	if(!CycDoubleLink_IsExist(list))
		return FALSE;
	temp = list->node;												//临时节点指向首节点	
	pNewNode = (DoubleLinkNode_t*)malloc(sizeof(DoubleLinkNode_t));	//为新节点分配内存
	pNewNode->data = (void *)malloc(list->datlen);					//为普通节点分配数据内存
	if(pNewNode == NULL)
	{
		printf("新节点空间分配失败！\r\n");
		return FALSE;
	}
	//pNewNode->data = dat;
	memcpy(pNewNode->data,dat,list->datlen);
	pNewNode->next = temp;											//新节点后继指向首节点
	pNewNode->pre = temp->pre;										//新节点前驱指向上一个尾节点
	temp->pre = pNewNode;											//首节点前驱指向新节点
	pNewNode->pre->next = pNewNode;									//新节点作为尾节点，其前驱的后继就是新节点本身
	return TRUE;
}

/************************************************************************
 *功能：获取第n个节点的数据，节点从0开始算，只算普通节点
 *输入：lsit:链表地址
 *		n:第n个节点
 *输出：dat:获取的数据
 *返回：TRUE or FALSE
************************************************************************/
bool CycDoubleLink_GetNodeValue(DoubleLinkList_t *list, unsigned int n, void *dat)
{
	unsigned int i=n;
	DoubleLinkNode_t *temp;											//临时节点
											
	printf("获取节点%d的数据\r\n",n);
	if(!CycDoubleLink_IsEmpty(list))
		return FALSE;
	temp = list->node->next;										//临时节点指向第一个普通节点
	while(temp != NULL && i--)
	{
		temp = temp->next;											//指向下一个节点，直到指向指定节点
	}
	if(temp != NULL)
	{
		memcpy(dat, temp->data,list->datlen);
		return TRUE;
	}
	else
	{
		printf("该节点不存在！\r\n");
		return FALSE;
	}
}

/************************************************************************
 *功能：删除第n个节点，n从0开始算，只算普通节点
 *输入：list:链表地址
		n:第n个节点,从0开始算
 *输出：无
 *返回：TRUE or FALSE
************************************************************************/
bool CycDoubleLink_DeleteNode(DoubleLinkList_t *list,unsigned int n)
{
	unsigned int i=n;
	DoubleLinkNode_t* temp,*pDeleteNode;							//临时节点

	printf("删除节点%d\r\n",n);
	if(!CycDoubleLink_IsEmpty(list))
		return FALSE;
	temp = list->node;												//临时节点指向首节点
	while(temp->next != list->node && i--)
	{
		temp = temp->next;											//指向下一个节点，直到指向指定节点
	}
	if(temp->next != list->node)									//注意现在temp是指定节点的前一个节点,不能删除首节点
	{
		pDeleteNode = temp->next;									//temp后继是要删除的节点
		temp->next = pDeleteNode->next;								//前一个节点后继
		temp = pDeleteNode->next;									//临时节点赋值为要删除节点的后一个节点
		temp->pre = pDeleteNode->pre;								//后一个节点前驱
		free(pDeleteNode->data);									//释放数据地址,注意释放的顺序不能换
		pDeleteNode->data = NULL;
		free(pDeleteNode);											//释放内存
		pDeleteNode = NULL;
		return TRUE;
	}
	else
	{
		printf("节点不存在！\r\n");
		return FALSE;
	}
}

/************************************************************************
 *功能：清除整个链表
 *输入：list:链表地址
 *输出：无
 *返回：TRUE or FALSE
************************************************************************/
bool CycDoubleLink_Clear(DoubleLinkList_t *list)
{
	DoubleLinkNode_t *temp,*p;										//临时节点

	if(!CycDoubleLink_IsEmpty(list))
		return FALSE;
	temp = list->node->next;										//临时节点指向第一个普通节点
	while(temp != list->node)
	{
		p = temp->next;												//当前节点后继赋值给p
		if(temp->data != NULL)
			free(temp->data);										//释放数据地址,注意释放的顺序不能换
		temp->data = NULL;
		free(temp);													//释放当前节点内存
		temp = p;
	}
	/*保留头指针则屏蔽此段代码,特别注意这里的释放内存！需要销毁整个链表时，启动此代码，并屏蔽掉最后两行代码
	 *且销毁整个代码后，不能再遍历链表，否则会出现内存错误。注意这里与非循环双链表的区别，非循环双链表中首节点指向NULL，
	 *判断为 temp==NULL ,所以后续释放p内存并不是释放首节点的内存，首节点还是保留的，在内存中有一席之地；
	 *但是这里的判断为 temp==list ，即释放p就是释放首节点的内存，首节点就不存在了，故后续如果用遍历函数就会出现内存错误。
	 */
	if(temp == list->node)
	{
	//	free(p);//
	//	p = NULL;
		list->node->next = list->node;//首节点后继指向自身
		list->node->pre = list->node;//首节点前驱指向自身
		printf("清除链表成功！\r\n");
		return TRUE;
	}
	return FALSE;
}

/************************************************************************
 *功能：销毁整个链表
 *输入：list:链表地址
 *输出：无
 *返回：TRUE or FALSE
************************************************************************/
bool CycDoubleLink_Destroy(DoubleLinkList_t *list)
{
	DoubleLinkNode_t *temp,*p;										//临时节点

	if(!CycDoubleLink_IsExist(list))
		return FALSE;
	temp = list->node;												//临时节点指向首节点
	while(temp != list->node)
	{
		p = temp->next;												//当前节点后继赋值给p
		if(temp->data != NULL)
			free(temp->data);										//释放数据地址,注意释放的顺序不能换
		temp->data = NULL;
		free(temp);													//释放当前节点内存
		temp = p;
	}
	if(temp == list->node)
	{
		if(temp->data != NULL)
			free(temp->data);										//释放数据地址,注意释放的顺序不能换
		temp->data = NULL;
		free(temp);													//释放首节点空间
		temp = NULL;
		list->node = NULL;
		list->datlen = 0;											//链表数据长度清零
		printf("销毁链表成功！\r\n");
		return TRUE;
	}
	return FALSE;
}
#endif
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