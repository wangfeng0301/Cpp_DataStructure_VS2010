/************************************************************************
 *                 堆                                 
 *利用完全二叉树线性表存储堆数据
 *参考资料：《数据结构与算法》张铭，王腾蛟，赵海燕等
 *wangfeng
 *E-mail:fengwang0301@163.com
 *CSDN:https://blog.csdn.net/u013073067?spm=1001.2101.3001.5343
 *GitHub:https://github.com/wangfeng0301
 *2019.11.29-2021.2.4
 *2021.2.4	修改，规范函数名
 *			增加，最大堆操作
 *2021.2.5	修改，优化简化代码，不受数据类型限制
************************************************************************/
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "heap.h"

/************************************************************************/
/*功能：判断堆是否满
/*输入：heap:堆结构变量
/*输出：无
/*返回：满TRUE,未满FALSE
/************************************************************************/
static bool Heap_IsFull(Heap_t *heap, uchar tag)
{
	if(heap->currsize >= heap->maxsize)				//如果堆已满，返回TRUE
		return TRUE;
	else
		return FALSE;
}
/************************************************************************/
/*功能：判断堆是否空
/*输入：heap:堆结构变量
/*输出：无
/*返回：空TRUE,未空FALSE
/************************************************************************/
static bool Heap_IsEmpty(Heap_t *heap, uchar tag)
{
	if(heap->currsize <= 0)				//如果堆已空，返回TRUE
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
static void Heap_SiftDown(Heap_t *heap, uint parent, uchar tag)
{
	uint child = 2*parent + 1;						//父节点的左子节点编号
	HeapNode_t temp = heap->array[parent];			//保存父节点

	while(child < heap->currsize)					//节点编号小于当前大小
	{
		/* 最小堆，若有右子节点，且右子节点小于左子节点,则需调整右子节点 */
		/* 最大堆，若有右子节点，且右子节点大于左子节点,则需调整右子节点 */
		//if((child < heap->currsize-1) && (heap->array[child].key > heap->array[child+1].key))
		if((child < heap->currsize-1))
		{
			if((heap->array[child].key > heap->array[child+1].key && tag == 0) || 
				(heap->array[child].key < heap->array[child+1].key && tag == 1))
			child++;
		}
		/* 最小堆，父节点大于子节点,交换位置 */
		/* 最大堆，父节点小于子节点,交换位置 */
		if((temp.key > heap->array[child].key && tag == 0) ||
			(temp.key < heap->array[child].key && tag == 1))		
		{
			heap->array[parent] = heap->array[child];
			parent = child;
			child = 2*parent+1;						//继续向下走，左子节点
		}
		else
			break;									//堆序性满足时退出
	}
	heap->array[parent] = temp;
}

/************************************************************************/
/*功能：以pos为根向上进行调整,若最小堆，则小数放在上面；若最大堆，则大数放在上面
/*输入：pos:开始调整位置
/*		tag:0,最小堆；1，最大堆
/*输出：无
/*返回：无
/************************************************************************/
static void Heap_SiftUp(Heap_t *heap, uint pos, uchar tag)
{
	int position = pos;								//从当前大小位置开始向上调整
	HeapNode_t temp = heap->array[position];		//保存当前值
	/* 静态堆，leftchild = 2*parent + 1 */
	/* 静态堆，rightchild = 2*parent + 2 */
	/* 静态堆，parent = (child-1)/2 */
	/* 未调整到根节点，且父节点比当前节点大 */
	while((position > 0) &&((heap->array[(position-1)/2].key > temp.key) && tag == 0) ||
							((heap->array[(position-1)/2].key < temp.key) && tag == 1))
	{
		heap->array[position] = heap->array[(position-1)/2];
		position = (position-1)/2;					//调整到父节点位置
	}
	heap->array[position] = temp;
}

/************************************************************************/
/*功能：建立堆结构 
/*输入：heap:堆结构变量
/*		dat:堆数据（不含key值）
/*		datlen:数据元素长度（不含key值）
/*		key:数据对应的key值（一定要和dat对应）
/*		size:数据个数
/*		maxsize:堆最大空间大小
/*		tag:0,最小堆；1，最大堆
/*输出：无
/*返回：TRUE or FALSE
/************************************************************************/
static bool Heap_Create(Heap_t *heap, void *dat, uint datlen, int *key, int size, int maxsize, uchar tag)
{
	int i;
	if(maxsize <= 0)									//堆数据最大空间必须大于0
		return FALSE;
	heap->array = (HeapNode_t *)malloc(maxsize*sizeof(HeapNode_t));//开辟maxsize个空间大小
	if(heap->array == NULL)
		return FALSE;
	//for(i=0;i<heap->currsize;i++)						//数据赋值
	for(i=0;i<maxsize;i++)								//开辟最大空间
	{
		heap->array[i].dat = (void *)malloc(datlen);
		if(heap->array[i].dat == NULL)
			return FALSE;
		if(i < size)
		{
			memcpy(heap->array[i].dat, (void *)((uint)dat+i*datlen), datlen);
			heap->array[i].key = key[i];
		}
	}
	heap->currsize = size;								//当前堆中元素个数
	heap->maxsize = maxsize;
	heap->datlen = datlen;
	for(i = heap->currsize/2-1;i>=0;i--)				//筛选法建堆，从n/2-1开始
	{
		Heap_SiftDown(heap, i, tag);
	}
	return TRUE;
}

/************************************************************************/
/*功能：插入新节点 
/*输入：heap:堆结构变量
/*		key:插入节点键值
/*		tag:0,最小堆；1，最大堆
/*输出：无
/*返回：TRUE or FALSE
/************************************************************************/
static bool Heap_Insert(Heap_t *heap, uint key, void *dat, uchar tag)
{
	printf("插入节点键值：%d\r\n",key);
	if(Heap_IsFull(heap, tag))
		return FALSE;
	heap->array[heap->currsize].dat = (void *)malloc(heap->datlen);
	//if(heap->array[heap->currsize].dat == NULL)//创建时已经开辟空间
	//	return FALSE;
	memcpy(heap->array[heap->currsize].dat, dat, heap->datlen);
	heap->array[heap->currsize].key = key;
	Heap_SiftUp(heap, heap->currsize, tag);			//向上调整
	heap->currsize++;								//当前大小加1

	return TRUE;
}

/************************************************************************/
/*功能：从堆顶删除最小值或最大值  
/*输入：heap:堆结构变量
/*		tag:0,最小堆；1，最大堆
/*输出：node:删除节点的值(HeapNode_t类型，只包含数据地址，没有数据)
/*返回：TRUE or FALSE
/************************************************************************/
static bool Heap_RemoveMinMax(Heap_t *heap, HeapNode_t *node, uchar tag)
{
	HeapNode_t temp;
	if(MinHeap_IsEmpty(heap))						//当前大小为0，无法删除
	{
		printf("当前堆大小为0，无法删除\r\n");
		return FALSE;
	}
	else
	{
		heap->currsize--;							//当前大小减1

		temp = heap->array[0];						//交换堆顶和堆末尾元素
		heap->array[0] = heap->array[heap->currsize];
		heap->array[heap->currsize] = temp;

		if(heap->currsize > 1)						//当前大小大于1，从堆顶开始向下筛选排序
			Heap_SiftDown(heap, 0, tag);
		*node = heap->array[heap->currsize];
		//free(heap->array[heap->currsize].dat);	//销毁时再释放
		//heap->array[heap->currsize].dat = NULL;
		return TRUE;
	}
}

/************************************************************************/
/*功能：删除给定下标的元素 
/*输入：heap:堆结构变量
/*		pos:删除节点的标号
/*		tag:0,最小堆；1，最大堆
/*输出：node:删除节点的值
/*返回：TRUE or FALSE
/************************************************************************/
static bool Heap_Remove(Heap_t *heap, HeapNode_t *node, uint pos, uchar tag)
{
	printf("删除节点%d\r\n",pos);
	if(Heap_IsEmpty(heap, tag))
	{
		printf("当前堆大小为0，无法删除\r\n");
		return FALSE;
	}
	if((pos<0) || pos >= heap->currsize)
	{
		printf("节点下标超范围，无法删除\r\n");
		return FALSE;
	}
	*node = heap->array[pos];						//输出要删除的节点
	heap->array[pos] = heap->array[--heap->currsize];//用堆最后的值替换这里的值
	if(heap->array[(pos-1)/2].key > heap->array[pos].key)//如果父节点值大于当前值
	{
		if(tag == 0)
			Heap_SiftUp(heap,pos,tag);				//从当前节点开始向上筛选
		else if(tag == 1)
			Heap_SiftDown(heap,pos,tag);
	}
	else
	{
		if(tag == 0)
			Heap_SiftDown(heap, pos, tag);			//否则从此节点开始向下调整
		else if(tag == 1)
			Heap_SiftUp(heap, pos, tag);
	}
	//free(heap->array[heap->currsize].dat);		//销毁时再释放
	//heap->array[heap->currsize].dat = NULL;
	return TRUE;
}
/************************************************************************/
/*功能：广度优先遍历堆  
/*输入：heap:堆结构变量
/*输出：无
/*返回：无
/************************************************************************/
static void Heap_Traverse(Heap_t *heap, uchar tag)
{
	uint i;
	printf("遍历：");
	for(i=0;i<heap->currsize;i++)
	{
		printf("key值：%d ",heap->array[i].key);
		printf("内容：%d \r\n",*(int *)heap->array[i].dat);
	}
	printf("\r\n");
}
/************************************************************************/
/*功能：销毁堆
/*输入：heap:堆结构变量
/*输出：无
/*返回：无
/************************************************************************/
static void Heap_Destroy(Heap_t *heap, uchar tag)
{
	while(heap->maxsize)
	{
		heap->maxsize --;
		free(heap->array[heap->currsize].dat);		//释放删除节点的数据域
		heap->array[heap->currsize].dat = NULL;
		heap->array[heap->currsize].key = 0;
	}
	heap->currsize = 0;
	free(heap->array);
	heap->array = NULL;
}


/*************************************************** 最小堆 **************************************************/
/************************************************************************/
/*功能：判断最大堆是否满
/*输入：heap:堆结构变量
/*输出：无
/*返回：满TRUE,未满FALSE
/************************************************************************/
bool MinHeap_IsFull(Heap_t *heap)
{
	return Heap_IsFull(heap, 0);
}
/************************************************************************/
/*功能：判断最大堆是否空
/*输入：heap:堆结构变量
/*输出：无
/*返回：空TRUE,未空FALSE
/************************************************************************/
bool MinHeap_IsEmpty(Heap_t *heap)
{
	return Heap_IsEmpty(heap, 0);
}
/************************************************************************/
/*功能：以parent为根向下进行调整,即大数放在下面
/*输入：parent:父节点编号，从此节点开始调整
/*输出：无
/*返回：无
/************************************************************************/
void MinHeap_SiftDown(Heap_t *heap, uint parent)
{
	Heap_SiftDown(heap, parent, 0);
}
/************************************************************************/
/*功能：以pos为根向上进行调整,即小数放在上面
/*输入：pos:开始调整位置
/*输出：无
/*返回：无
/************************************************************************/
void MinHeap_SiftUp(Heap_t *heap, uint pos)
{
	Heap_SiftUp(heap, pos, 0);
}
/************************************************************************/
/*功能：建立最小堆结构 
/*输入：heap:堆结构变量
/*		dat:堆数据（不含key值）
/*		datlen:数据元素长度（不含key值）
/*		key:数据对应的key值（一定要和dat对应）
/*		size:数据个数
/*		maxsize:堆最大空间大小
/*输出：无
/*返回：TRUE or FALSE
/************************************************************************/
bool MinHeap_Create(Heap_t *heap, void *dat, uint datlen, int *key, int size, int maxsize)
{
	return Heap_Create(heap, dat, datlen, key, size, maxsize, 0);
}
/************************************************************************/
/*功能：插入新节点 
/*输入：heap:堆结构变量
/*		key:节点键值
/*		dat:节点数据
/*输出：无
/*返回：TRUE or FALSE
/************************************************************************/
bool MinHeap_Insert(Heap_t *heap,uint key, void *dat)
{
	return Heap_Insert(heap, key, dat, 0);
}
/************************************************************************/
/*功能：从堆顶删除最小值 
/*输入：heap:堆结构变量
/*输出：node:删除节点的值
/*返回：TRUE or FALSE
/************************************************************************/
bool MinHeap_RemoveMin(Heap_t *heap, HeapNode_t *node)
{
	return Heap_RemoveMinMax(heap, node, 0);
}
/************************************************************************/
/*功能：删除给定下标的元素 
/*输入：heap:堆结构变量
/*		pos:删除节点的标号
/*		tag:0,最小堆；1，最大堆
/*输出：node:删除节点的值
/*返回：TRUE or FALSE
/************************************************************************/
bool MinHeap_Remove(Heap_t *heap, HeapNode_t *node, uint pos)
{
	return Heap_Remove(heap, node, pos, 0);
}
/************************************************************************/
/*功能：广度优先遍历最小堆  
/*输入：heap:堆结构变量
/*输出：无
/*返回：无
/************************************************************************/
void MinHeap_Traverse(Heap_t *heap)
{
	Heap_Traverse(heap, 0);
}
/************************************************************************/
/*功能：销毁堆
/*输入：heap:堆结构变量
/*输出：无
/*返回：无
/************************************************************************/
void MinHeap_Destroy(Heap_t *heap)
{
	Heap_Destroy(heap, 0);
}





/*************************************************** 最大堆 **************************************************/
/************************************************************************/
/*功能：判断最大堆是否满
/*输入：heap:堆结构变量
/*输出：无
/*返回：满TRUE,未满FALSE
/************************************************************************/
bool MaxHeap_IsFull(Heap_t *heap)
{
	return Heap_IsFull(heap, 1);
}
/************************************************************************/
/*功能：判断最大堆是否空
/*输入：heap:堆结构变量
/*输出：无
/*返回：空TRUE,未空FALSE
/************************************************************************/
bool MaxHeap_IsEmpty(Heap_t *heap)
{
	return Heap_IsEmpty(heap, 1);
}
/************************************************************************/
/*功能：以parent为根向下进行调整,即小数放在下面
/*输入：parent:父节点编号，从此节点开始调整
/*输出：无
/*返回：无
/************************************************************************/
void MaxHeap_SiftDown(Heap_t *heap, uint parent)
{
	Heap_SiftDown(heap, parent, 1);
}

/************************************************************************/
/*功能：以pos为根向上进行调整,即大数放在上面
/*输入：pos:开始调整位置
/*输出：无
/*返回：无
/************************************************************************/
void MaxHeap_SiftUp(Heap_t *heap, uint pos)
{
	Heap_SiftUp(heap, pos, 1);
}

/************************************************************************/
/*功能：建立最大堆结构 
/*输入：heap:堆结构变量
/*		dat:堆数据（不含key值）
/*		datlen:数据元素长度（不含key值）
/*		key:数据对应的key值（一定要和dat对应）
/*		size:数据个数
/*		maxsize:堆最大空间大小
/*输出：无
/*返回：TRUE or FALSE
/************************************************************************/
bool MaxHeap_Create(Heap_t *heap, void *dat, uint datlen, int *key, uint size, uint maxsize)
{
	return Heap_Create(heap, dat, datlen, key, size, maxsize, 1);
}
/************************************************************************/
/*功能：插入新节点 
/*输入：heap:堆结构变量
/*		key:节点键值
/*		dat:节点数据
/*输出：无
/*返回：TRUE or FALSE
/************************************************************************/
bool MaxHeap_Insert(Heap_t *heap,uint key, void *dat)
{
	return Heap_Insert(heap, key, dat, 1);
}
/************************************************************************/
/*功能：从堆顶删除最大值  
/*输入：heap:堆结构变量
/*输出：node:删除节点的值
/*返回：TRUE or FALSE
/************************************************************************/
bool MaxHeap_RemoveMax(Heap_t *heap, HeapNode_t *node)
{
	return Heap_RemoveMinMax(heap, node, 1);
}
/************************************************************************/
/*功能：删除给定下标的元素 
/*输入：heap:堆结构变量
/*		node:节点值
/*		pos:删除节点的标号
/*输出：删除节点的值
/*返回：TRUE or FALSE
/************************************************************************/
bool MaxHeap_Remove(Heap_t *heap, HeapNode_t *node, uint pos)
{
	return Heap_Remove(heap, node, pos, 1);
}
/************************************************************************/
/*功能：广度优先遍历最小堆  
/*输入：heap:堆结构变量
/*输出：无
/*返回：无
/************************************************************************/
void MaxHeap_Traverse(Heap_t *heap)
{
	Heap_Traverse(heap, 1);
}
/************************************************************************/
/*功能：销毁堆
/*输入：heap:堆结构变量
/*输出：无
/*返回：无
/************************************************************************/
void MaxHeap_Destroy(Heap_t *heap)
{
	Heap_Destroy(heap, 1);
}



void testHeap(void)
{
	int HeapVal[9] = {9,9,7,6,20,4,33,2,1};
	uint key[9] = {9,9,7,6,20,4,33,2,1};
	int temp = 11111;
	Heap_t heap;									//定义一个堆结构变量
	HeapNode_t node;
	
	MinHeap_Create(&heap, HeapVal, sizeof(HeapVal[0]), key, sizeof(HeapVal)/sizeof(HeapVal[0]), 10);
	MinHeap_Traverse(&heap);
	if(TRUE == MinHeap_Insert(&heap,10, &temp))
		MinHeap_Traverse(&heap);

	if(MinHeap_RemoveMin(&heap, &node))
		printf("最小值：%d\r\n",node.key);
	MinHeap_Traverse(&heap);

	if(MinHeap_Remove(&heap, &node, 3))
		printf("被删除数据：%d\r\n", node.key);
	MinHeap_Traverse(&heap);
	while(!MinHeap_IsEmpty(&heap))
	{
		if(MinHeap_RemoveMin(&heap, &node))
			printf("最小值：%d\r\n",node.key);
	}
	MinHeap_Destroy(&heap);

	printf("\r\n\r\n");
	//MaxHeap_Create(&heap, HeapVal, sizeof(HeapVal)/sizeof(HeapVal[0]), 10);
	MaxHeap_Create(&heap, HeapVal, sizeof(HeapVal[0]), key, sizeof(HeapVal)/sizeof(HeapVal[0]), 10);
	MaxHeap_Traverse(&heap);
	if(TRUE == MaxHeap_Insert(&heap, 10, &temp))
		MaxHeap_Traverse(&heap);

	if(MaxHeap_RemoveMax(&heap, &node))
		printf("最大值：%d\r\n", node.key);
	MaxHeap_Traverse(&heap);

	if(MaxHeap_Remove(&heap, &node, 3))
		printf("被删除数据：%d\r\n", node.key);
	MaxHeap_Traverse(&heap);
	while(!MaxHeap_IsEmpty(&heap))
	{
		if(MaxHeap_RemoveMax(&heap, &node))
			printf("最大值：%d\r\n",node.key);
	}
	MaxHeap_Destroy(&heap);
}