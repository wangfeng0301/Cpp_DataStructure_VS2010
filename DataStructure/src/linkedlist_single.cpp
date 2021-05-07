/************************************************************************
 *���������������������������������ڵ㡢�޸�ĳ�ڵ�ֵ��
 *				ɾ����������ɾ��ĳ���ڵ�
 *�ο����ϣ������ݽṹ���㷨�������������ԣ��Ժ����
 *wangfeng
 *E-mail:fengwang0301@163.com
 *CSDN:https://blog.csdn.net/u013073067?spm=1001.2101.3001.5343
 *GitHub:https://github.com/wangfeng0301
 *2021.5.1
************************************************************************/
#include <iostream>
#include <string.h>
#include "linkedlist_single.h"
using namespace std;

#if 0
/************************************************************************
 *����ڵ���ģ��
************************************************************************/
template <typename T>
class LinkNode
{
public:
	LinkNode(const T info, /*const*/ LinkNode<T> *nextValue = NULL)//���������Ĺ��캯��
	{
		data = info;
		next = nextValue;
	}
	LinkNode(/*const*/ LinkNode<T> *nextValue = NULL)//1�������Ĺ��캯��
	{
		next = nextValue;
	}
	~LinkNode(){};//��������
	T data;
	LinkNode<T> *next;
};
/************************************************************************
 *������ģ��
************************************************************************/
template <typename T>
class Link:public LinkNode<T>//���м̳�LinkNode��
{
public:
	Link();//���캯��
	~Link();//��������
	//bool isExist();//ʵ��������������Ȼ����
	bool isEmpty();
	//bool create(int n);//ʵ���������ڹ��캯���оʹ���������
	bool changeNodeValue(int n, T dat);
	bool traverse();
	bool insertNode(int n, T dat);
	bool insertNode(T dat);//��β����
	bool getNodeValue(int n, T *dat);
	bool deleteNode(int n);
	bool deleteNode();//ɾ����β�ڵ�
	bool clear();
	//bool destroy();//����������������
	bool reverse();
private:
	LinkNode<T> *head, *tail;//�������ͷβָ��
};
#endif
/************************************************************************
 *���ܣ����캯������ʼ������
 *���룺
 *�����
 *���أ�
************************************************************************/
template <typename T>
Link<T>::Link()
{
	head = tail = new LinkNode<T>(NULL);
	cout << "Link()" << endl;
}
/************************************************************************
 *���ܣ��������������������ͷŸ����ڵ�
 *���룺
 *�����
 *���أ�
************************************************************************/
template <typename T>
Link<T>::~Link()
{
	LinkNode<T> *temp;
	while(head != NULL)
	{
		temp = head;
		head = head->next;
		delete temp;
	}
	cout << "~Link()" << endl;
}

/************************************************************************
 *���ܣ��ж������Ƿ����
 *���룺
 *�������
 *���أ�TRUE or FALSE
************************************************************************/
/*template <typename T>
bool Link<T>::isExist()
{
	if(head == NULL)
	{
		printf("��������\r\n");
		return FALSE;
	}
	return TRUE;
}*/
/************************************************************************
 *���ܣ��ж������Ƿ�Ϊ��
 *���룺
 *�������
 *���أ�TRUE or FALSE
************************************************************************/
template <typename T>
bool Link<T>::isEmpty()
{
	if(head->next == NULL)
	{
		cout << "�����" <<endl;
		return TRUE;
	}
	else
		return FALSE;
}
/************************************************************************
 *���ܣ���������ͨ�ã������������͸ı���ı�
 *���룺list:������ʼ��ַ
 *		n������ڵ�������������׽ڵ�
 *		dat:Ҫ���������Ԫ��ָ�룬��n=0,�Ĳ����ɴ�NULL
 *		datlen:�������͵ĳ���
 *�������
 *���أ�TRUE or FALSE
************************************************************************/
/*bool Link_Create(LinkList_t *list, uint n, void *dat, uint datlen)
{
	uint i;
	LinkNode_t *pHead,*pNode,*pTail;						//�����׽�㣬��ͨ�ڵ㣬β�ڵ�
	pHead = (LinkNode_t *)malloc(sizeof(LinkNode_t));		//Ϊͷ�������ڴ�ռ䣬ͷ��㲻�����ݣ�ָ���׽ڵ㣨��һ���ڵ㣩
	if(pHead == NULL)										//�ж��Ƿ�����ڴ�ɹ�
	{
		printf("�ռ����ʧ��");
		return FALSE;
	}
	pTail = pHead;											//β�ڵ��ʼָ���׽��

	for(i=0;i<n;i++)
	{
		pNode = (LinkNode_t *)malloc(sizeof(LinkNode_t));	//Ϊ��ͨ�ڵ����ڵ�ṹ���ڴ�
		pNode->data = (void *)malloc(datlen);				//Ϊ��ͨ�ڵ���������ڴ�
		if(pNode == NULL || pNode->data == NULL)			//�ж��Ƿ�����ڴ�ɹ�
		{
			printf("�½ڵ�%d�ռ����ʧ�ܣ�\r\n",i);
			return FALSE;
		}
		memcpy(pNode->data, (void *)((uint)dat+i*datlen), datlen);//��ֵ
		//pNode->data = dat[i];
		pTail->next = pNode;								//β�ڵ�ָ���µĽڵ㣬ͬʱβ�ڵ��ǰһ���ڵ�Ҳָ����pNode
		pTail = pNode;										//�½ڵ㸳ֵ��β�ڵ�,�½ڵ�ͱ����β�ڵ�
	}
	pTail->next = NULL;										//β�ڵ�ָ��NULL,��������
	list->datlen = datlen;									//ָ���������ͳ���
	list->node = pHead;										//ָ���׽ڵ�
	list->node->data = NULL;								//һ��Ҫ��ʼ���׽ڵ�������
	return TRUE;
}*/

/************************************************************************
 *���ܣ��޸Ľڵ�n��ֵ
 *���룺n:��n���ڵ�,n��0��ʼ�㡣ֻ����ͨ�ڵ�
 *		dat:�޸ĺ��ֵ
 *�������
 *���أ�TRUE or FALSE
************************************************************************/
template <typename T>
bool Link<T>::changeNodeValue(int n, T dat)
{
	LinkNode<T> *t;
	cout << "�޸Ľڵ�" << n << "��ֵ" << endl;
	if(isEmpty())
		return FALSE;
	t = head->next;
	while(t != NULL && n--)								//�ҵ���n���ڵ�
	{
		t = t->next;
	}
	if(t != NULL)
	{
		t->data = dat;
		return TRUE;
	}
	else
	{
		cout << "�ڵ㲻���ڣ�" << endl;;
		return FALSE;
	}
}

/************************************************************************
 *���ܣ������ڵ�
 *���룺��
 *�������
 *���أ�TRUE or FALSE
************************************************************************/
template <typename T>
bool Link<T>::traverse()
{
	LinkNode<T> *p;

	cout << "��������" << endl;
	if(isEmpty())
	{
		return FALSE;
	}
	p = head->next;
	while(p != NULL)
	{
		cout << p->data << endl;
		p = p->next;								//ָ����һ���ڵ�
	}
	return TRUE;
}

/************************************************************************
 *���ܣ��ڵ�n���ڵ�ǰ����ڵ㣬�ڵ��0��ʼ�㣬ֻ����ͨ�ڵ�
 *���룺n:��n���ڵ�
 *		dat:�����ֵ
 *�������
 *���أ�TRUE or FALSE
************************************************************************/
template <typename T>
bool Link<T>::insertNode(int n, T dat)
{
	LinkNode<T> *p;
	LinkNode<T> *in;									//�²���ڵ�

	cout << "�ڽڵ�" << n << "ǰ�����½ڵ�" << endl;
	if(isEmpty())
		return FALSE;
	p = head;										//����ָ��ָ���׽ڵ�
	while(p != NULL && n--)							//��λ����n���ڵ㣬�ڴ˽ڵ�ǰ�����½ڵ�
	{
		p = p->next;
	}
	if(p != NULL)
	{
		in = new LinkNode<T>(dat, p->next);//Ϊ�²���ڵ�����ڴ�,����ֵ
		if(in == NULL)
		{
			cout << "�ռ����ʧ��" << endl;
			return FALSE;
		}
		p->next = in;								//Դ�ڵ�ָ���²���ڵ�
		if(p == tail)								//����β����
			tail = in;
		return TRUE;
	}
	else
	{
		cout << "�ڵ㲻����!" << endl;
		return FALSE;
	}
}
/************************************************************************
 *���ܣ���β�ڵ�����ڵ�
 *���룺dat:�����ֵ
 *�������
 *���أ�TRUE or FALSE
************************************************************************/
template <typename T>
bool Link<T>::insertNode(T dat)
{
	LinkNode<T> *in;									//�²���ڵ�

	cout << "����β�����½ڵ�" << endl;
	in = new LinkNode<T>(dat, tail->next);//Ϊ�²���ڵ�����ڴ�,����ֵ
	if(in == NULL)
	{
		cout << "�ռ����ʧ��" << endl;
		return FALSE;
	}
	tail->next = in;								//Դ�ڵ�ָ���²���ڵ�
	tail = in;
	return TRUE;
}

/************************************************************************
 *���ܣ���ȡ��n���ڵ�����ݣ��ڵ��0��ʼ�㣬ֻ����ͨ�ڵ�
 *���룺n:��n���ڵ�
 *		dat:��ȡ��ֵ
 *�������
 *���أ�TRUE or FALSE
************************************************************************/
template <typename T>
bool Link<T>::getNodeValue(int n, T *dat)
{
	LinkNode<T> *p;

	if(isEmpty())
		return FALSE;
	p = head->next;									//����LinkNode_t��ָ��ָ���׽ڵ�
	while(p != NULL && n--)							//��λ����n���ڵ㣬�ڴ˽ڵ�ǰ�����½ڵ�
	{
		p = p->next;
	}
	if(p != NULL)
	{
		*dat = p->data;
		return TRUE;
	}
	else
	{
		cout << "�ڵ㲻���ڣ�" << endl;
		return FALSE;
	}
}

/************************************************************************
 *���ܣ�ɾ����n���ڵ㣬n��0��ʼ�㣬ֻ����ͨ�ڵ�
 *���룺n:��n���ڵ�,��0��ʼ��
 *�������
 *���أ���
************************************************************************/
template <typename T>
bool Link<T>::deleteNode(int n)
{
	LinkNode<T> *p, *pre;
	
	cout << "��" << n << "���ڵ㽫��ɾ��" << endl;
	if(isEmpty())
		return FALSE;
	pre = head;										//��¼Ҫɾ���ڵ��ǰһ���ڵ�
	p = head->next;									//����ָ��ָ���׽ڵ�
	while(p != NULL && n--)							//�ƶ�����n���ڵ㣬ɾ��
	{
		pre = p;
		p = p->next;
	}
	if(p != NULL)
	{
		pre->next = p->next;
		if(p == tail)
			tail = pre;
		delete p;									//�ͷŽڵ����
		p = NULL;
	}
	else
	{
		cout << "��ɾ���ڵ㲻���ڣ�" << endl;
		return FALSE;
	}
	return TRUE;
}
/************************************************************************
 *���ܣ�ɾ��β�ڵ�
 *���룺��
 *�������
 *���أ���
************************************************************************/
template <typename T>
bool Link<T>::deleteNode()
{
	LinkNode<T> *p, *pre;
	
	cout << "ɾ��β�ڵ�" << endl;
	if(isEmpty())
		return FALSE;
	pre = head;										//��¼Ҫɾ���ڵ��ǰһ���ڵ�
	p = head->next;									//����ָ��ָ���׽ڵ�
	while(p->next != NULL)								//�ƶ�����β��ɾ��
	{
		pre = p;
		p = p->next;
	}
	tail = pre;
	pre->next = p->next;
	delete p;									//�ͷŽڵ����
	p = NULL;
	return TRUE;
}

/************************************************************************
 *���ܣ������������
 *���룺
 *�������
 *���أ�TRUE or FALSE
************************************************************************/
template <typename T>
bool Link<T>::clear()
{
	LinkNode<T> *p;
	
	if(isEmpty())
		return FALSE;
	p = head->next;									//ָ���һ����ͨ�ڵ�
	while(p != NULL)								//ÿ���ڵ㰤��ɾ��
	{
		head->next = p->next;						//ͷ�ڵ�ָ����һ���ڵ�
		delete p;									//�ͷŵ�ǰ�ڵ��ڴ�
		p = head->next;							
	}
	if(p == NULL)
	{
		cout << "�������ɹ���" << endl;
		tail = head;
		return TRUE;
	}
	return FALSE;
}

/************************************************************************
 *���ܣ�������������
 *���룺list:�����ַ
 *�������
 *���أ���
************************************************************************/
#if 0
bool Link_Destroy(LinkList_t *list)
{
	LinkNode_t *p;
	LinkNode_t *temp;								//��ʱ�ڵ����
	
	if(!Link_IsExist(list))
		return FALSE;
	p = list->node;									//ָ���׽ڵ�
	list->node = NULL;								//�׽ڵ�ָ���ָ��
	list->datlen = 0;								//�������ݳ�������
	while(p != NULL)								//ÿ���ڵ㰤��ɾ��
	{
		temp = p->next;								//��ʱ����ָ����һ���ڵ�
		if(p->data != NULL)
			free(p->data);							//�ͷ����ݵ�ַ,ע���ͷŵ�˳���ܻ�
		p->data = NULL;
		free(p);									//�ͷŵ�ǰ�ڵ��ڴ�
		p = temp;
	}
	if(p == NULL)
	{
		/*if(p->data != NULL)
			free(p->data);							//�ͷ����ݵ�ַ,ע���ͷŵ�˳���ܻ�
		p->data = NULL;
		free(temp);									//�ͷ���ʱ�����ڴ�
		temp = NULL;*/
		printf("��������ɹ���\r\n");
		return TRUE;
	}
	return FALSE;
}
#endif
/************************************************************************
 *���ܣ���ת��������
 *���룺��
 *�������
 *���أ���
************************************************************************/
template <typename T>
bool Link<T>::reverse()
{
	LinkNode<T> *currNode;							//��ǰҪ�嵽head�����node
	LinkNode<T> *nextNode;							//����ڵ�ǰ�ڵ����һ���ڵ�
	LinkNode<T> *preNode;							//����ڵ�ǰ�ڵ����һ���ڵ�
	LinkNode<T> *headNode;							//ͷ���

	cout << "��ת��������" << endl;
	if(isEmpty())
		return FALSE;
	headNode = head;
	preNode = head->next;
	currNode = preNode->next;
	while(currNode != NULL)
	{
		nextNode = currNode->next;					//����next�ڵ�
		preNode->next = currNode->next;
		currNode->next = headNode->next;
		headNode->next = currNode;

		currNode = nextNode;
	}
	tail = preNode;
	return TRUE;
}

void testLink(void)
{
	int age[3] = {10,11,12};
	Link<int> student;//����һ������

	if(student.insertNode(age[0]))//����β�����½ڵ�
		student.traverse();//��������
	if(student.insertNode(age[1]))//����β�����½ڵ�
		student.traverse();//��������
	if(student.insertNode(age[2]))//����β�����½ڵ�
		student.traverse();//��������
	
	if(student.changeNodeValue(0,1))//�޸ĵ�0���ڵ��ֵ
		student.traverse();//��������

	if(student.insertNode(3,2))//�ڵ�n���ڵ�ǰ�����½ڵ�
		student.traverse();//��������
	if(student.insertNode(0,3))//�ڵ�n���ڵ�ǰ�����½ڵ�
		student.traverse();//��������

	if(student.deleteNode(0))//ɾ���ڵ�
		student.traverse();//��������
	if(student.deleteNode())//ɾ��β�ڵ�
		student.traverse();//��������
	
	if(student.reverse())//��ת����
		student.traverse();//��������

	if(student.clear())//��ת����
		student.traverse();//��������
}
