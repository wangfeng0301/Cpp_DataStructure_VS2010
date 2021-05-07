#ifndef __DOUBLELINK_H__
#define __DOUBLELINK_H__
#include "type.h"

/*˫������ڵ���ģ��*/
template <typename T>
class DoubleLinkNode
{
public:
	DoubleLinkNode(const T info, DoubleLinkNode<T> *preNode = NULL, DoubleLinkNode<T> *nextNode = NULL)//3�������Ĺ��캯��
	{
		data = info;
		pre = preNode;
		next = nextNode;
	}
	DoubleLinkNode(DoubleLinkNode<T> *preNode = NULL, DoubleLinkNode<T> *nextNode = NULL)//2�������Ĺ��캯��
	{
		pre = preNode;
		next = nextNode;
	}
	~DoubleLinkNode(){};//��������
	T data;	
	DoubleLinkNode<T> *pre;//ǰ��
	DoubleLinkNode<T> *next;//���
};
/*˫��������ģ��*/
template <typename T>
class DoubleLink:public DoubleLinkNode<T>
{
public:
	DoubleLink();//���캯��
	~DoubleLink();//��������
	bool isExist();
	bool isEmpty();
	//bool create(unsigned int n, void *dat, unsigned int datlen);//��������,���캯���д���
	bool traverse();//��������
	bool changeNodeValue(int n, T dat);//�޸ĵ�n���ڵ��ֵ
	bool insertNode(int n, T dat);//�ڵ�n���ڵ�ǰ�����½ڵ�
	bool insertNode(T dat);//�ڱ�β�����½ڵ�
	bool getNodeValue(int n, T *dat);//��ȡ��n���ڵ��ֵ
	bool deleteNode(int n);//ɾ����n���ڵ�
	bool deleteNode();//ɾ����β�ڵ�
	bool clear();
	//bool Destroy();//��������,����������������

	//bool CycDoubleLink_IsExist();
	//bool CycDoubleLink_IsEmpty();
	//bool CycDoubleLink_Create(unsigned int n, void *dat, unsigned int datlen);//����˫��ѭ������
	//bool CycDoubleLink_Traverse();//����ѭ������
	//bool CycDoubleLink_ChangeNodeValue(DoubleLinkList_t * list,unsigned int n, void *dat);//�޸Ľڵ�ֵ
	//bool CycDoubleLink_InsertNode(,unsigned int n, void *dat);
	//bool CycDoubleLink_AddNode(, void *dat);
	//bool CycDoubleLink_GetNodeValue(,unsigned int n, void *dat);
	//bool CycDoubleLink_DeleteNode(,unsigned int n);//ɾ��ָ���ڵ�
	//bool CycDoubleLink_Clear();
	//bool CycDoubleLink_Destroy();
private:
	DoubleLinkNode<T> *head,*tail;//˫�����ͷβָ��
};

void testDoubleLink(void);
void testCycDoubleLink(void);
#endif