#ifndef __HEAP_H__
#define __HEAP_H__
#include "type.h"
#include <iostream>
#include <string.h>
using namespace std;

template <typename T>
class HeapNode
{
public:
	HeapNode(int _key, T _dat)//���캯��
	{
		key = _key;
		dat = _dat;
	}
	HeapNode(){};
	~HeapNode(){}//��������
	int key;
	T dat;
};
template <typename T>
class Heap:public HeapNode<T>//���м̳�
{
public:
	Heap(T *dat, int *key, int size, int maxsize, uchar tag);//���캯��
	Heap();
	~Heap();//��������
	bool isFull();
	bool isEmpty();
	void siftDown(int parent, uchar tag);
	void siftUp(int pos, uchar tag);
	bool create(T *dat, int *key, int size, int maxsize, uchar tag);
	bool insert(int key, T &dat, uchar tag);
	bool remove(HeapNode<T> *node, int pos, uchar tag);
	bool removeHeapTop(HeapNode<T> *node, uchar tag);
	void traverse();
//private:
	HeapNode<T> *array; //��Ŷѽڵ������
	int currsize;		//��ǰ����Ԫ����Ŀ
	int maxsize;		//�ѵ����Ԫ����Ŀ
};
template <typename T>
class MinHeap:public Heap<T>
{
public:
	MinHeap(T *dat, int *key, int size, int maxsize);
	//bool create(T *dat, int *key, int size, int maxsize);
	bool insert(int key, T &dat);
	bool remove(HeapNode<T> *node, int pos);
	bool removeMin(HeapNode<T> *node);
};
template <typename T>
class MaxHeap:public Heap<T>
{
public:
	MaxHeap(T *dat, int *key, int size, int maxsize);
	//bool create(T *dat, int *key, int size, int maxsize);
	bool insert(int key, T &dat);
	bool remove(HeapNode<T> *node, int pos);
	bool removeMax(HeapNode<T> *node);
};
/************************************************************************/
/* ���ܣ����캯����������                                                 
/* ���룺��
/* �������
/* ���أ���
/************************************************************************/
template <typename T>
Heap<T>::Heap(T *dat, int *key, int size, int maxsize, uchar tag)
{
	this->create(dat, key, size, maxsize, tag);
}
template <typename T>
Heap<T>::Heap()
{
	
}
/************************************************************************/
/* ���ܣ���������,�ͷŶ�                                                   
/* ���룺��
/* �������
/* ���أ���
/************************************************************************/
template <typename T>
Heap<T>::~Heap()
{
	if(this->array != NULL)
	{
		delete []array;
		this->array = NULL;
	}
	this->maxsize = 0;
	this->currsize = 0;
	cout << "~Heap()" << endl;
}
/************************************************************************/
/*���ܣ��ж϶��Ƿ���
/*���룺��
/*�������
/*���أ���TRUE,δ��FALSE
/************************************************************************/
template <typename T>
bool Heap<T>::isFull()
{
	if(this->currsize >= this->maxsize)
		return TRUE;
	else
		return FALSE;
}
/************************************************************************/
/*���ܣ��ж϶��Ƿ��
/*���룺��
/*�������
/*���أ���TRUE,δ��FALSE
/************************************************************************/
template <typename T>
bool Heap<T>::isEmpty()
{
	if(this->currsize <= 0)
		return TRUE;
	else
		return FALSE;
}
/************************************************************************/
/*���ܣ���parentΪ�����½��е���,����С�ѣ�������������棻�����ѣ���С����������
/*���룺parent:���ڵ��ţ��Ӵ˽ڵ㿪ʼ����
/*		tag:0,��С�ѣ�1������
/*�������
/*���أ���
/************************************************************************/
template <typename T>
void Heap<T>::siftDown(int parent, uchar tag)
{
	int child = 2*parent + 1;						//���ڵ�����ӽڵ���
	HeapNode<T> temp = this->array[parent];			//���游�ڵ�
	/* ��̬�ѣ�leftchild = 2*parent + 1 */
	/* ��̬�ѣ�rightchild = 2*parent + 2 */
	/* ��̬�ѣ�parent = (child-1)/2 */
	while(child < this->currsize)					//�ڵ���С�ڵ�ǰ��С
	{
		/* ��С�ѣ��������ӽڵ㣬�����ӽڵ�С�����ӽڵ�,������������ӽڵ� */
		/* ���ѣ��������ӽڵ㣬�����ӽڵ�������ӽڵ�,������������ӽڵ� */
		if((child < this->currsize-1))
		{
			if((this->array[child].key > this->array[child+1].key && tag == 0) || 
				(this->array[child].key < this->array[child+1].key && tag == 1))
				child++;
		}
		/* ��С�ѣ����ڵ�����ӽڵ�,����λ�� */
		/* ���ѣ����ڵ�С���ӽڵ�,����λ�� */
		if((temp.key > this->array[child].key && tag == 0) ||
			(temp.key < this->array[child].key && tag == 1))		
		{
			this->array[parent] = this->array[child];
			parent = child;
			child = 2*parent+1;						//���������ߣ����ӽڵ�
		}
		else
			break;									//����������ʱ�˳�
	}
	this->array[parent] = temp;
}

/************************************************************************/
/*���ܣ���posΪ�����Ͻ��е���,����С�ѣ���С���������棻�����ѣ��������������
/*���룺pos:��ʼ����λ��
/*		tag:0,��С�ѣ�1������
/*�������
/*���أ���
/************************************************************************/
template <typename T>
void Heap<T>::siftUp(int pos, uchar tag)
{
	int position = pos;								//�ӵ�ǰ��Сλ�ÿ�ʼ���ϵ���
	HeapNode<T> temp = this->array[position];		//���浱ǰֵ
	/* ��̬�ѣ�leftchild = 2*parent + 1 */
	/* ��̬�ѣ�rightchild = 2*parent + 2 */
	/* ��̬�ѣ�parent = (child-1)/2 */
	/* δ���������ڵ㣬�Ҹ��ڵ�ȵ�ǰ�ڵ�� */
	while(position > 0)
	{
		if( ((this->array[(position-1)/2].key > temp.key) && tag == 0) 
		 || ((this->array[(position-1)/2].key < temp.key) && tag == 1))
		{
			this->array[position] = this->array[(position-1)/2];
			position = (position-1)/2;				//���������ڵ�λ��
		}
		else
			break;
	}
	this->array[position] = temp;
}

/************************************************************************/
/*���ܣ������ѽṹ 
/*���룺dat:�����ݣ�����keyֵ��
/*		key:���ݶ�Ӧ��keyֵ��һ��Ҫ��dat��Ӧ��
/*		size:���ݸ���
/*		maxsize:�����ռ��С
/*		tag:0,��С�ѣ�1������
/*�������
/*���أ�TRUE or FALSE
/************************************************************************/
template <typename T>
bool Heap<T>::create(T *dat, int *key, int size, int maxsize, uchar tag)
{
	int i;
	if(maxsize <= 0 || size > maxsize)					//���������ռ�������0
		return FALSE;
	if(/*dat == NULL ||*/ (key == NULL && size > 0))
		return FALSE;
	this->array = new HeapNode<T>[maxsize];				//����maxsize���ռ��С
	if(this->array == NULL)
		return FALSE;
	for(i=0;i<size;i++)
	{
		if(dat)
			this->array[i].dat = dat[i];
		else											//�����������ָ��
			this->array[i].dat = 0;
		this->array[i].key = key[i];
	}
	this->currsize = size;								//��ǰ����Ԫ�ظ���
	this->maxsize = maxsize;
	for(i = this->currsize/2-1;i>=0;i--)				//ɸѡ�����ѣ���n/2-1��ʼ
	{
		this->siftDown( i, tag);
	}
	return TRUE;
}

/************************************************************************/
/*���ܣ������½ڵ� 
/*���룺key:����ڵ��ֵ
/*      dat:���������
/*		tag:0,��С�ѣ�1������
/*�������
/*���أ�TRUE or FALSE
/************************************************************************/
template <typename T>
bool Heap<T>::insert(int key, T &dat, uchar tag)
{
	cout << "����ڵ��ֵ��" << key <<endl;
	if(this->isFull())
	{
		cout << "������" <<endl;
		return FALSE;
	}
	this->array[this->currsize].dat = dat;
	this->array[this->currsize].key = key;
	this->siftUp(this->currsize, tag);					//���ϵ���
	this->currsize++;									//��ǰ��С��1

	return TRUE;
}

/************************************************************************/
/*���ܣ�ɾ�������±��Ԫ�� 
/*���룺pos:ɾ���ڵ�ı��
/*		tag:0,��С�ѣ�1������
/*�����node:ɾ���ڵ��ֵ
/*���أ�TRUE or FALSE
/************************************************************************/
template <typename T>
bool Heap<T>::remove(HeapNode<T> *node, int pos, uchar tag)
{
	//cout << "ɾ���ڵ�" << pos << endl;
	if(this->isEmpty())
	{
		cout << "��ǰ�Ѵ�СΪ0���޷�ɾ��" << endl;
		return FALSE;
	}
	if((pos<0) || pos >= this->currsize)
	{
		cout << "�ڵ��±곬��Χ���޷�ɾ��" << endl;
		return FALSE;
	}
	*node = this->array[pos];							//���Ҫɾ���Ľڵ�
	this->array[pos] = this->array[--this->currsize];	//�ö�����ֵ�滻�����ֵ
	/*����ɾ���Ѷ��ڵ�*/
	if(pos == 0)
	{
		if(this->currsize > 1)
			this->siftDown(0,tag);
	}
	else if(pos > 0)
	{
		/*ɾ���ǶѶ��ڵ�ʱ��������ڵ���ڵ�ǰ�ڵ㣬�����������*/
		/*1.���ѣ���Ҫ���µ���*/
		/*2.��С�ѣ���Ҫ���ϵ���*/
		if(this->array[(pos-1)/2].key > this->array[pos].key)
		{
			if(tag == 0)
				this->siftUp(pos,tag);
			else if(tag == 1)
				this->siftDown(pos,tag);
		}
		/*ͬ����������ڵ�С�ڵ�ǰ�ڵ㣬�����������*/
		/*1.���ѣ���Ҫ���ϵ���*/
		/*2.��С�ѣ���Ҫ���µ���*/
		else
		{
			if(tag == 0)
				this->siftDown(pos, tag);
			else if(tag == 1)
				this->siftUp(pos, tag);
		}
	}
	
	return TRUE;
}

/************************************************************************/
/*���ܣ��ӶѶ�ɾ����Сֵ�����ֵ  
/*���룺tag:0,��С�ѣ�1������
/*�����node:ɾ���ڵ�
/*���أ�TRUE or FALSE
/************************************************************************/
template <typename T>
bool Heap<T>::removeHeapTop(HeapNode<T> *node, uchar tag)
{
	return this->remove(node, 0, tag);
}

/************************************************************************/
/*���ܣ�������ȱ�����  
/*���룺��
/*�������
/*���أ���
/************************************************************************/
template <typename T>
void Heap<T>::traverse()
{
	cout << "������" << endl;
	for(int i=0;i<this->currsize;i++)
	{
		cout << "key��" << this->array[i].key ;
		cout << "  ���ݣ�" << this->array[i].dat << endl;
	}
}


/*************************************************** ��С�� **************************************************/

/************************************************************************/
/* ���ܣ����캯����������                                                 
/* ���룺��
/* �������
/* ���أ���
/************************************************************************/
template <typename T>
MinHeap<T>::MinHeap(T *dat, int *key, int size, int maxsize)
{
	Heap::create(dat, key, size, maxsize, 0);
}
/************************************************************************/
/*���ܣ�������С�ѽṹ 
/*���룺dat:�����ݣ�����keyֵ��
/*		key:���ݶ�Ӧ��keyֵ��һ��Ҫ��dat��Ӧ��
/*		size:���ݸ���
/*		maxsize:�����ռ��С
/*�������
/*���أ�TRUE or FALSE
/************************************************************************/
/*template <typename T>
bool MinHeap<T>::create(T *dat, int *key, int size, int maxsize)
{
	return Heap::create(dat, key, size, maxsize, 0);
}*/

/************************************************************************/
/*���ܣ������½ڵ� 
/*���룺key:�ڵ��ֵ
/*		dat:�ڵ�����
/*�������
/*���أ�TRUE or FALSE
/************************************************************************/
template <typename T>
bool MinHeap<T>::insert(int key, T &dat)
{
	return Heap::insert(key, dat, 0);
}

/************************************************************************/
/*���ܣ�ɾ�������±��Ԫ�� 
/*���룺pos:ɾ���ڵ�ı��
/*�����node:ɾ���ڵ��ֵ
/*���أ�TRUE or FALSE
/************************************************************************/
template <typename T>
bool MinHeap<T>::remove(HeapNode<T> *node, int pos)
{
	return Heap::remove(node, pos, 0);
}

/************************************************************************/
/*���ܣ��ӶѶ�ɾ����Сֵ 
/*���룺��
/*�����node:ɾ���ڵ��ֵ
/*���أ�TRUE or FALSE
/************************************************************************/
template <typename T>
bool MinHeap<T>::removeMin(HeapNode<T> *node)
{
	return Heap::removeHeapTop(node, 0);
}

/*************************************************** ���� **************************************************/

/************************************************************************/
/* ���ܣ����캯����������                                                 
/* ���룺��
/* �������
/* ���أ���
/************************************************************************/
template <typename T>
MaxHeap<T>::MaxHeap(T *dat, int *key, int size, int maxsize)
{
	Heap::create(dat, key, size, maxsize, 1);
}
/************************************************************************/
/*���ܣ��������ѽṹ 
/*���룺dat:�����ݣ�����keyֵ��
/*		key:���ݶ�Ӧ��keyֵ��һ��Ҫ��dat��Ӧ��
/*		size:���ݸ���
/*		maxsize:�����ռ��С
/*�������
/*���أ�TRUE or FALSE
/************************************************************************/
/*template <typename T>
bool MaxHeap<T>::create(T *dat, int *key, int size, int maxsize)
{
	return Heap::create(dat, key, size, maxsize, 1);
}*/
/************************************************************************/
/*���ܣ������½ڵ� 
/*���룺key:�ڵ��ֵ
/*		dat:�ڵ�����
/*�������
/*���أ�TRUE or FALSE
/************************************************************************/
template <typename T>
bool MaxHeap<T>::insert(int key, T &dat)
{
	return Heap::insert(key, dat, 1);
}

/************************************************************************/
/*���ܣ�ɾ�������±��Ԫ�� 
/*���룺node:�ڵ�ֵ
/*		pos:ɾ���ڵ�ı��
/*�����ɾ���ڵ��ֵ
/*���أ�TRUE or FALSE
/************************************************************************/
template <typename T>
bool MaxHeap<T>::remove(HeapNode<T> *node, int pos)
{
	return Heap::remove(node, pos, 1);
}

/************************************************************************/
/*���ܣ��ӶѶ�ɾ�����ֵ  
/*���룺��
/*�����node:ɾ���ڵ��ֵ
/*���أ�TRUE or FALSE
/************************************************************************/
template <typename T>
bool MaxHeap<T>::removeMax(HeapNode<T> *node)
{
	return Heap::removeHeapTop(node, 1);
}

void testHeap(void);

#endif