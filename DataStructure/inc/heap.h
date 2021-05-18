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
	HeapNode(int _key, T _dat)//构造函数
	{
		key = _key;
		dat = _dat;
	}
	HeapNode(){};
	~HeapNode(){}//析构函数
	int key;
	T dat;
};
template <typename T>
class Heap:public HeapNode<T>//公有继承
{
public:
	Heap(T *dat, int *key, int size, int maxsize, uchar tag);//构造函数
	Heap();
	~Heap();//析构函数
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
	HeapNode<T> *array; //存放堆节点的数组
	int currsize;		//当前堆中元素数目
	int maxsize;		//堆的最大元素数目
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
/* 功能：构造函数，创建堆                                                 
/* 输入：无
/* 输出：无
/* 返回：无
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
/* 功能：析构函数,释放堆                                                   
/* 输入：无
/* 输出：无
/* 返回：无
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
/*功能：判断堆是否满
/*输入：无
/*输出：无
/*返回：满TRUE,未满FALSE
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
/*功能：判断堆是否空
/*输入：无
/*输出：无
/*返回：空TRUE,未空FALSE
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
/*功能：以parent为根向下进行调整,若最小堆，则大数放在下面；若最大堆，则小数放在下面
/*输入：parent:父节点编号，从此节点开始调整
/*		tag:0,最小堆；1，最大堆
/*输出：无
/*返回：无
/************************************************************************/
template <typename T>
void Heap<T>::siftDown(int parent, uchar tag)
{
	int child = 2*parent + 1;						//父节点的左子节点编号
	HeapNode<T> temp = this->array[parent];			//保存父节点
	/* 静态堆，leftchild = 2*parent + 1 */
	/* 静态堆，rightchild = 2*parent + 2 */
	/* 静态堆，parent = (child-1)/2 */
	while(child < this->currsize)					//节点编号小于当前大小
	{
		/* 最小堆，若有右子节点，且右子节点小于左子节点,则需调整到右子节点 */
		/* 最大堆，若有右子节点，且右子节点大于左子节点,则需调整到右子节点 */
		if((child < this->currsize-1))
		{
			if((this->array[child].key > this->array[child+1].key && tag == 0) || 
				(this->array[child].key < this->array[child+1].key && tag == 1))
				child++;
		}
		/* 最小堆，父节点大于子节点,交换位置 */
		/* 最大堆，父节点小于子节点,交换位置 */
		if((temp.key > this->array[child].key && tag == 0) ||
			(temp.key < this->array[child].key && tag == 1))		
		{
			this->array[parent] = this->array[child];
			parent = child;
			child = 2*parent+1;						//继续向下走，左子节点
		}
		else
			break;									//堆序性满足时退出
	}
	this->array[parent] = temp;
}

/************************************************************************/
/*功能：以pos为根向上进行调整,若最小堆，则小数放在上面；若最大堆，则大数放在上面
/*输入：pos:开始调整位置
/*		tag:0,最小堆；1，最大堆
/*输出：无
/*返回：无
/************************************************************************/
template <typename T>
void Heap<T>::siftUp(int pos, uchar tag)
{
	int position = pos;								//从当前大小位置开始向上调整
	HeapNode<T> temp = this->array[position];		//保存当前值
	/* 静态堆，leftchild = 2*parent + 1 */
	/* 静态堆，rightchild = 2*parent + 2 */
	/* 静态堆，parent = (child-1)/2 */
	/* 未调整到根节点，且父节点比当前节点大 */
	while(position > 0)
	{
		if( ((this->array[(position-1)/2].key > temp.key) && tag == 0) 
		 || ((this->array[(position-1)/2].key < temp.key) && tag == 1))
		{
			this->array[position] = this->array[(position-1)/2];
			position = (position-1)/2;				//调整到父节点位置
		}
		else
			break;
	}
	this->array[position] = temp;
}

/************************************************************************/
/*功能：建立堆结构 
/*输入：dat:堆数据（不含key值）
/*		key:数据对应的key值（一定要和dat对应）
/*		size:数据个数
/*		maxsize:堆最大空间大小
/*		tag:0,最小堆；1，最大堆
/*输出：无
/*返回：TRUE or FALSE
/************************************************************************/
template <typename T>
bool Heap<T>::create(T *dat, int *key, int size, int maxsize, uchar tag)
{
	int i;
	if(maxsize <= 0 || size > maxsize)					//堆数据最大空间必须大于0
		return FALSE;
	if(/*dat == NULL ||*/ (key == NULL && size > 0))
		return FALSE;
	this->array = new HeapNode<T>[maxsize];				//开辟maxsize个空间大小
	if(this->array == NULL)
		return FALSE;
	for(i=0;i<size;i++)
	{
		if(dat)
			this->array[i].dat = dat[i];
		else											//允许传入空数据指针
			this->array[i].dat = 0;
		this->array[i].key = key[i];
	}
	this->currsize = size;								//当前堆中元素个数
	this->maxsize = maxsize;
	for(i = this->currsize/2-1;i>=0;i--)				//筛选法建堆，从n/2-1开始
	{
		this->siftDown( i, tag);
	}
	return TRUE;
}

/************************************************************************/
/*功能：插入新节点 
/*输入：key:插入节点键值
/*      dat:插入的数据
/*		tag:0,最小堆；1，最大堆
/*输出：无
/*返回：TRUE or FALSE
/************************************************************************/
template <typename T>
bool Heap<T>::insert(int key, T &dat, uchar tag)
{
	cout << "插入节点键值：" << key <<endl;
	if(this->isFull())
	{
		cout << "堆已满" <<endl;
		return FALSE;
	}
	this->array[this->currsize].dat = dat;
	this->array[this->currsize].key = key;
	this->siftUp(this->currsize, tag);					//向上调整
	this->currsize++;									//当前大小加1

	return TRUE;
}

/************************************************************************/
/*功能：删除给定下标的元素 
/*输入：pos:删除节点的标号
/*		tag:0,最小堆；1，最大堆
/*输出：node:删除节点的值
/*返回：TRUE or FALSE
/************************************************************************/
template <typename T>
bool Heap<T>::remove(HeapNode<T> *node, int pos, uchar tag)
{
	//cout << "删除节点" << pos << endl;
	if(this->isEmpty())
	{
		cout << "当前堆大小为0，无法删除" << endl;
		return FALSE;
	}
	if((pos<0) || pos >= this->currsize)
	{
		cout << "节点下标超范围，无法删除" << endl;
		return FALSE;
	}
	*node = this->array[pos];							//输出要删除的节点
	this->array[pos] = this->array[--this->currsize];	//用堆最后的值替换这里的值
	/*考虑删除堆顶节点*/
	if(pos == 0)
	{
		if(this->currsize > 1)
			this->siftDown(0,tag);
	}
	else if(pos > 0)
	{
		/*删除非堆顶节点时，如果父节点大于当前节点，分两种情况：*/
		/*1.最大堆，需要向下调整*/
		/*2.最小堆，需要向上调整*/
		if(this->array[(pos-1)/2].key > this->array[pos].key)
		{
			if(tag == 0)
				this->siftUp(pos,tag);
			else if(tag == 1)
				this->siftDown(pos,tag);
		}
		/*同样，如果父节点小于当前节点，分两种情况：*/
		/*1.最大堆，需要向上调整*/
		/*2.最小堆，需要向下调整*/
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
/*功能：从堆顶删除最小值或最大值  
/*输入：tag:0,最小堆；1，最大堆
/*输出：node:删除节点
/*返回：TRUE or FALSE
/************************************************************************/
template <typename T>
bool Heap<T>::removeHeapTop(HeapNode<T> *node, uchar tag)
{
	return this->remove(node, 0, tag);
}

/************************************************************************/
/*功能：广度优先遍历堆  
/*输入：无
/*输出：无
/*返回：无
/************************************************************************/
template <typename T>
void Heap<T>::traverse()
{
	cout << "遍历：" << endl;
	for(int i=0;i<this->currsize;i++)
	{
		cout << "key：" << this->array[i].key ;
		cout << "  内容：" << this->array[i].dat << endl;
	}
}


/*************************************************** 最小堆 **************************************************/

/************************************************************************/
/* 功能：构造函数，创建堆                                                 
/* 输入：无
/* 输出：无
/* 返回：无
/************************************************************************/
template <typename T>
MinHeap<T>::MinHeap(T *dat, int *key, int size, int maxsize)
{
	Heap::create(dat, key, size, maxsize, 0);
}
/************************************************************************/
/*功能：建立最小堆结构 
/*输入：dat:堆数据（不含key值）
/*		key:数据对应的key值（一定要和dat对应）
/*		size:数据个数
/*		maxsize:堆最大空间大小
/*输出：无
/*返回：TRUE or FALSE
/************************************************************************/
/*template <typename T>
bool MinHeap<T>::create(T *dat, int *key, int size, int maxsize)
{
	return Heap::create(dat, key, size, maxsize, 0);
}*/

/************************************************************************/
/*功能：插入新节点 
/*输入：key:节点键值
/*		dat:节点数据
/*输出：无
/*返回：TRUE or FALSE
/************************************************************************/
template <typename T>
bool MinHeap<T>::insert(int key, T &dat)
{
	return Heap::insert(key, dat, 0);
}

/************************************************************************/
/*功能：删除给定下标的元素 
/*输入：pos:删除节点的标号
/*输出：node:删除节点的值
/*返回：TRUE or FALSE
/************************************************************************/
template <typename T>
bool MinHeap<T>::remove(HeapNode<T> *node, int pos)
{
	return Heap::remove(node, pos, 0);
}

/************************************************************************/
/*功能：从堆顶删除最小值 
/*输入：无
/*输出：node:删除节点的值
/*返回：TRUE or FALSE
/************************************************************************/
template <typename T>
bool MinHeap<T>::removeMin(HeapNode<T> *node)
{
	return Heap::removeHeapTop(node, 0);
}

/*************************************************** 最大堆 **************************************************/

/************************************************************************/
/* 功能：构造函数，创建堆                                                 
/* 输入：无
/* 输出：无
/* 返回：无
/************************************************************************/
template <typename T>
MaxHeap<T>::MaxHeap(T *dat, int *key, int size, int maxsize)
{
	Heap::create(dat, key, size, maxsize, 1);
}
/************************************************************************/
/*功能：建立最大堆结构 
/*输入：dat:堆数据（不含key值）
/*		key:数据对应的key值（一定要和dat对应）
/*		size:数据个数
/*		maxsize:堆最大空间大小
/*输出：无
/*返回：TRUE or FALSE
/************************************************************************/
/*template <typename T>
bool MaxHeap<T>::create(T *dat, int *key, int size, int maxsize)
{
	return Heap::create(dat, key, size, maxsize, 1);
}*/
/************************************************************************/
/*功能：插入新节点 
/*输入：key:节点键值
/*		dat:节点数据
/*输出：无
/*返回：TRUE or FALSE
/************************************************************************/
template <typename T>
bool MaxHeap<T>::insert(int key, T &dat)
{
	return Heap::insert(key, dat, 1);
}

/************************************************************************/
/*功能：删除给定下标的元素 
/*输入：node:节点值
/*		pos:删除节点的标号
/*输出：删除节点的值
/*返回：TRUE or FALSE
/************************************************************************/
template <typename T>
bool MaxHeap<T>::remove(HeapNode<T> *node, int pos)
{
	return Heap::remove(node, pos, 1);
}

/************************************************************************/
/*功能：从堆顶删除最大值  
/*输入：无
/*输出：node:删除节点的值
/*返回：TRUE or FALSE
/************************************************************************/
template <typename T>
bool MaxHeap<T>::removeMax(HeapNode<T> *node)
{
	return Heap::removeHeapTop(node, 1);
}

void testHeap(void);

#endif