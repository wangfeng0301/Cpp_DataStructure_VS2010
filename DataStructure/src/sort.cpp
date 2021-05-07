/*********************************************************************
*常见排序算法
*wangfeng
*2019.11.28
*参考资料：《数据结构与算法》张铭，王腾蛟，赵海燕等
**********************************************************************/
#include <stdio.h>
#include <malloc.h>
#include "sort.h"

/************************************************************************/
/* 直接插入排序
/* Array[]：待排序数组
/* n：数组长度
/************************************************************************/
void InsertSort(Record Array[],int n)
{
	Record tempRecord;												//临时变量
	int i,j;
	for(i = 1;i < n;i++)											//依次插入第i个记录
	{
		tempRecord = Array[i];										//将记录Array[i]放在临时变量中
		j = i-1;													//内存循环变量j从i-1开始
		while(j>=0 && tempRecord.SortKey < Array[j].SortKey)		//往前寻找记录i的正确位置
		{
			Array[j+1] = Array[j];									//将大于记录i的记录后移
			j = j-1;												//下标j前移
		}
		Array[j+1] = tempRecord;									//此时记录j+1就是记录i的正确位置，回填
	}
}

/************************************************************************/
/* 修改的插入排序算法
/* Array[]：待排序数组
/* n：数组长度
/* delta:当前增量
/************************************************************************/
void ModInsertSort(Record Array[],int n,int delta)
{
	int i,j;
	Record temp;
	for(i = delta;i < n;i += delta)									//对子序列中第i个记录，寻找合适的插入位置
	{
		for(j = i;j>=delta;j -= delta)								//j以delta为步长向前寻找逆置对进行调整
		{
			if(Array[j].SortKey < Array[j-delta].SortKey)			//Array[j]<Array[j-delta]，则二者为逆置对
			{
				temp = Array[j];									//交换
				Array[j] = Array[j-delta];
				Array[j-delta] = temp;
			}
			else
				break;
		}
	}
}
/************************************************************************/
/* Shell排序/缩小增量排序法
/* Array[]：待排序数组
/* n：数组长度
/************************************************************************/
void ShellSort(Record Array[],int n)
{
	int i,delta;
	for(delta = n/2;delta>0;delta /=2)								//增量delta每次除以2递减
	{
		for(i = 0;i<delta;i++)										//分别对delta个子序列进行插入排序
			ModInsertSort(&Array[i],n-i,delta);						//"&"传Array[i]的地址，待处理数组长度为n-i
	}
	//ModInsertSort(Array,n,1);										//如果增量序列不能保证最后一个delta间距为1，可以安排下面这个扫尾性质的插入排序
}

/************************************************************************/
/* 直接选择排序
/* Array[]：待排序数组
/* n：数组长度
/************************************************************************/
void SelectSort(Record Array[],int n)
{
	int i,j,smallest;
	Record temp;
	for(i = 0;i<n-1;i++)											//依次选出第i小的记录，即剩余记录中最小的那个
	{
		smallest = i;												//首先假设记录i就是最小的
		for(j = i+1;j<n;j++)										//开始向后扫描所有剩余记录
		{
			if(Array[j].SortKey < Array[smallest].SortKey)			//发现更小的记录，记录他的位置
				smallest = j;
		}
		temp = Array[smallest];										//交换，第i小的记录到位
		Array[smallest] = Array[i];
		Array[i] = temp;
	}
}

/******************************************堆排序*************************************************************/

/************************************************************************/
/*以根i为根向下进行调整                                                 */
/*left:从left开始向下筛选
/*返回：无
/************************************************************************/
static void SiftDown(SortHeap *heap,int left)
{
	int i = left;													//从left开始向下筛选
	int j = 2*i+1;													//i的左子节点
	Record temp = heap->heapArray[i];								//保存父节点

	while(j < heap->CurrentSize)									//节点编号小于当前大小
	{
		if((j < heap->CurrentSize-1) && (heap->heapArray[j].SortKey < heap->heapArray[j+1].SortKey))//若有右子节点，且右子节点大于左子节点
			j++;													//j指向右子节点
		if(temp.SortKey < heap->heapArray[j].SortKey)				//父节点小于子节点,交换位置
		{
			heap->heapArray[i] = heap->heapArray[j];
			i = j;
			j = 2*i+1;												//继续向下走，左子节点
		}
		else
			break;													//堆序性满足时退出
	}
	heap->heapArray[i] = temp;
}
/************************************************************************/
/*向上进行调整                                                 */
/*heap:堆结构体
/*返回：无
/************************************************************************/
static void SiftUp(SortHeap *heap,int pos)
{
	int position = pos;								//从当前大小位置开始向上调整
	Record temp = heap->heapArray[position];		//保存当前值
	while((position > 0) && (heap->heapArray[(position-1)/2].SortKey < temp.SortKey))//未调整到根节点，且父节点比当前节点小
	{
		heap->heapArray[position] = heap->heapArray[(position-1)/2];
		position = (position-1)/2;					//调整到父节点位置
	}
	heap->heapArray[position] = temp;
}
/************************************************************************/
/*建立最大堆结构                                                        */
/*data:连续空间，Record类型
/*heap:堆结构变量
/*size:数据大小
/*返回：无
/************************************************************************/
void BuildMaxHeap(SortHeap *heap,Record *data,int maxsize)
{
	int i;
	//if(heap->MaxSize<=0)										//堆数据最大空间必须大于0
	//	return;
	heap->MaxSize = maxsize;									//设置最大值
	//heap->heapArray = (int *)malloc(heap->MaxSize*sizeof(int));	//开辟maxsize个空间大小
	heap->CurrentSize = maxsize;									//当前堆中元素个数
	heap->heapArray = data;										//赋值
	//for(i=0;i<heap->CurrentSize;i++)							//数据赋值
	//	heap->heapArray[i] = data[i];

	for(i = heap->CurrentSize/2-1;i>=0;i--)						//筛选法建堆，从n/2-1开始
	{
		SiftDown(heap,i);
	}
	//printf("\r\n遍历堆");
	//for(i = 0;i<heap->CurrentSize;i++)
	//	printf("%d ",heap->heapArray[i].SortKey);
	//printf("\r\n");
}
/************************************************************************/
/*从堆顶删除最大值                                                       */
/*heap:堆结构变量
/*返回：堆中最大值节点
/************************************************************************/
static Record MaxHeapRemoveMax(SortHeap *heap)
{
//	int i;
	Record temp;
	if(0 == heap->CurrentSize)										//当前大小为0，无法删除
	{
		printf("当前堆大小为0，无法删除\r\n");
		return;
	}
	else
	{
		heap->CurrentSize--;										//当前大小减1

		temp = heap->heapArray[0];									//交换堆顶和堆末尾节点（记录）
		heap->heapArray[0] = heap->heapArray[heap->CurrentSize];
		heap->heapArray[heap->CurrentSize] = temp;

		if(heap->CurrentSize > 1)									//当前大小大于1，从堆顶开始向下筛选排序
			SiftDown(heap,0);

		//printf("\r\n遍历堆");
		//for(i = 0;i<heap->CurrentSize;i++)
		//	printf("%d ",heap->heapArray[i].SortKey);
		//printf("\r\n");

		return heap->heapArray[heap->CurrentSize];
	}
}
/************************************************************************/
/* 堆排序
/* Array[]：待排序数组
/* n：数组长度
/************************************************************************/
void HeapSort(Record Array[],int n)
{
	int i;
	SortHeap heap;													//定义变量
	BuildMaxHeap(&heap,Array,n);									//构建最大堆
	for(i = 0;i<n-1;i++)
	{
		MaxHeapRemoveMax(&heap);
	}
}
/******************************************堆排序结束*********************************************************/

/************************************************************************/
/* 冒泡排序
/* Array[]：待排序数组
/* n：数组长度
/************************************************************************/
void BubbleSort(Record Array[],int n)
{
	int i,j;
	Record temp;													//定义变量
	for(i = 0;i<n-1;i++)											//外循环
	{
		for(j = i+1;j<n;j++)
		{
			if(Array[i].SortKey>Array[j].SortKey)
			{
				temp = Array[i];
				Array[i] = Array[j];
				Array[j] = temp;
			}
		}
	}
		
}

/******************************************快速排序*********************************************************/
/************************************************************************/
/* 选择轴值
/* left:数组左端
/* right:数组右端
/************************************************************************/
int SelectPivot(int left, int right)
{
	return (left+right)/2;									//选择中间值作为轴值
}
/************************************************************************/
/* 分割函数,分割后轴值到达正确位置
/* Array[]：待排序数组
/* left:数组左端
/* right:数组右端
/************************************************************************/
int Partition(Record Array[],int left,int right)
{
	Record temp = Array[right];								//将轴值放在临时变量中
	while(left != right)									//开始分割，left/right不断向中间移动，直到相遇
	{
		while(Array[left].SortKey <= Array[right].SortKey && right>left)//left指针向右移动，越过那些小于等于轴值的记录，直到找到一个大于轴值的记录
			left++;
		if(left<right)										//若left/right尚未相遇，将逆置元素换到右边的空位
		{
			Array[right] = Array[left];
			right--;										//right指针左移
		}
		while(Array[right].SortKey >= temp.SortKey && right>left)//right指针向左移动，越过那些大于等于轴值的记录，直到找到一个小于轴值的记录
			right--;
		if(left<right)										//若left/right尚未相遇，将逆置元素换到左边的空位
		{
			Array[left] = Array[right];
			left++;
		}
	}
	Array[left] = temp;										//把轴值回填到分界位置上
	return left;											//返回分界位置left
}

/************************************************************************/
/* 快速排序
/* Array[]：待排序数组
/* left:数组左端
/* right:数组右端
/************************************************************************/
void QuickSort(Record Array[],int left,int right)
{
	int pivot;												//轴值
	Record temp;
	if(right<=left)											//如果子序列中只有0或1个记录，就不需要排序
		return;
	pivot = SelectPivot(left,right);						//选择轴值
	temp = Array[left];										//分割前将轴值放到数组末端
	Array[left] = Array[right];
	Array[right] = temp;
	pivot = Partition(Array,left,right);					//分割后轴值到达正确位置
	QuickSort(Array,left,pivot-1);							//对轴值左边的子序列进行递归快速排序
	QuickSort(Array,pivot+1,right);							//对轴值右边的子序列进行递归快速排序
}
/******************************************快速排序结束*********************************************************/

/*两个子序列都从左到右扫描，归并到新数组*/
void Merge(Record Array[],Record TempArray[],int left,int right,int middle)
{
	int i,j,index1,index2;									
	for(j = left;j<=right;j++)								//将数组暂时存放在临时数组
		TempArray[j] = Array[j];
	index1 = left;											//左边子序列起始位置
	index2 = middle+1;										//右边子序列起始位置
	i = left;												//从左开始归并
	while(index1 <= middle && index2 <= right)				//取较小者插入合并数组中
	{
		if(TempArray[index1].SortKey <= TempArray[index2].SortKey)//为保证稳定性，相等时左边优先
			Array[i++] = TempArray[index1++];
		else
			Array[i++] = TempArray[index2++];
	}
	while(index1 <= middle)									//只剩做序列，可以直接复制
		Array[i++] = TempArray[index1++];
	while(index2 <= right)									//与上个循环互斥，直接复制剩余的右序列
		Array[i++] = TempArray[index2++];
}
/************************************************************************/
/* 归并排序
/* Array[]：待排序数组
/* left:数组左端下标
/* right:数组右端下标
/************************************************************************/
void MergeSort(Record Array[],Record TempArray[],int left,int right)
{
	int middle;												//
	if(left<right)											//如果序列中只有0或1个记录，就不用排序
	{
		middle = (left+right)/2;							//从中间划分为两个子序列
		MergeSort(Array,TempArray,left,middle);				//对左边一般进行递归
		MergeSort(Array,TempArray,middle+1,right);			//对右边一半进行递归
		Merge(Array,TempArray,left,right,middle);			//进行归并
	}
}

/*优化的Sedgwick两个有序子序列归并，右子序列逆置了，都从两端向中间扫描，归并到新数组*/
void ModMerge(Record Array[],Record TempArray[],int left,int right,int middle)
{
	int i,j,k,index1,index2;									
	for(i = left;i<=middle;i++)								//复制左边的子序列
		TempArray[i] = Array[i];
	for(j = 1;j<right-middle;j++)							//复制右边的子序列，但顺序颠倒过来
		TempArray[right-j+1] = Array[j+middle];
	for(index1 = left,index2 = right,k = left;k<=right;k++)	//开始归并，取较小者插入合并数组中
	{
		if(TempArray[index1].SortKey<=TempArray[index2].SortKey)//为保证稳定性，相等时左边优先
			Array[k] = TempArray[index1++];
		else
			Array[k] = TempArray[index2--];
	}
}
/************************************************************************/
/* 优化的归并排序
/* Array[]：待排序数组
/* left:数组左端下标
/* right:数组右端下标
/************************************************************************/
#define	THRESHOLD 28
void ModMergeSort(Record Array[],Record TempArray[],int left,int right)
{
	int middle;												//
	if(right-left+1 > THRESHOLD)							//如果序列中只有0或1个记录，就不用排序
	{
		middle = (left+right)/2;							//从中间划分为两个子序列
		ModMergeSort(Array,TempArray,left,middle);			//对左边一般进行递归
		ModMergeSort(Array,TempArray,middle+1,right);		//对右边一半进行递归
		ModMerge(Array,TempArray,left,right,middle);		//进行归并
	}
	else
		InsertSort(&Array[left],right-left+1);				//小长度子序列进行插入排序
}

/************************************************************************/
/* 桶式排序
/* Array[]：待排序数组
/* n:数组长度
/* max:区间最大值
/************************************************************************/
void BucketSort(Record Array[],int n,int max)
{
	Record *TempArray = (Record*)malloc(n*sizeof(Record));		//临时数组
	int *count = (int *)malloc(max*sizeof(int));				//桶容量计数器，count[i]存储了第i个桶中的记录数
	int i;

	for(i = 0;i<n;i++)											//将序列复制到临时数组
		TempArray[i] = Array[i];
	for(i = 0;i<max;i++)										//所有计数器初始为0
		count[i] = 0;
	for(i = 0;i<n;i++)											//统计每个取值出现的次数
		count[Array[i].SortKey]++;
	for(i = 1;i<max;i++)										//统计小于等于i的元素个数
		count[i] = count[i-1] + count[i];						//count[i]记录了i+1的开始位置
	for(i = n-1;i>=0;i--)										//从尾部开始顺序输出，保证排序的稳定性
		Array[--count[TempArray[i].SortKey]] = TempArray[i];

	free(count);
	count = NULL;
	free(TempArray);
	TempArray = NULL;
}

/************************************************************************/
/* 顺序基数排序,d次桶式排序
/* Array[]：待排序数组
/* n:数组长度
/* d:排序码个数
/* r:基，比如十进制数就是0-9，r=10；字母就是a-z，r=26
/************************************************************************/
void SequenceRadixSort(Record Array[],int n,int d,int r)
{
	Record *TempArray = (Record*)malloc(n*sizeof(Record));		//临时数组
	int *count = (int *)malloc(r*sizeof(int));					//桶容量计数器，count[i]存储了第i个桶中的记录数
	int i,j,k;
	int Radix = 1;												//模保持进位，用来取Array[j]的第i位排序码

	for(i = 1;i<=d;i++)											//分别对第i个排序码进行分配
	{
		for(j = 0;j<r;j++)										//所有计数器初始为0
			count[j] = 0;
		for(j = 0;j<n;j++)										//统计每个桶中的记录数
		{
			k = (Array[j].SortKey/Radix)%r;						//取Array[j]的第i位排序码
			count[k]++;											//相应计数器加1
		}
		for(j = 1;j<r;j++)										//将TempArray中的位置依次分配给r个桶
			count[j] = count[j-1]+count[j];						
		//count[i]记录了i+1的开始位置，元素i应该从Array[count[i]-1]往前追溯，存放count[i]-count[i-1]个
		for(j = n-1;j>=0;j--)									//从数组尾部，将记录收集到相应桶中
		{
			k = (Array[j].SortKey/Radix)%r;						//取Array[j]的第i位排序码，Array[j]应该放到count[k]-1处
			count[k]--;											//使用了第k个桶的一个位置，桶剩余量的计数器减1
			TempArray[count[k]] = Array[j];						//Array[j]放到TempArray中，下标位置在上面已经被减1
		}
		for(j = 0;j<n;j++)										//将临时数组中的内容复制到Array中
			Array[j] = TempArray[j];
		Radix *=r;												//向左进一位，修改模Radix
	}
	free(count);
	count = NULL;
	free(TempArray);
	TempArray = NULL;
}

/******************************************链式基数排序*********************************************************/
static void distribute(Record *Array,int first,int i,int r,StaticQueue *queue);
static int collect(Record *Array,int first, int r,StaticQueue *queue);
static void AddrSort(Record *Array,int n, int first);
/************************************************************************/
/* 链式基数排序
/* Array[]：待排序数组
/* n:数组长度
/* d:排序码个数
/* r:基，比如十进制数就是0-9，r=10；字母就是a-z，r=26
/************************************************************************/
void LinkRadixSort(Record Array[],int n,int d,int r)
{
	int i ,first=0;														//first指向静态链中的第一个记录
	StaticQueue *queue = (StaticQueue*)malloc(r*sizeof(StaticQueue));	//存放r个桶的静态队列
	for(i = 0;i<n-1;i++)												//初始化建链，相邻记录的静态指针链接为单链表
		Array[i].next = i+1;											//第i个记录的静态指针域设为i+1，即下一个元素的下标
	Array[n-1].next = -1;												//链尾next为空

	for(i = 0;i<d;i++)													//分别对第i个排序码进行分配和收集，一共d趟
	{
		distribute(Array,first,i,r,queue);								//分配
		first = collect(Array,first,r,queue);							//收集,函数返回收集后首个元素所在数组下标
	}
	free(queue);
	queue = NULL;
	AddrSort(Array,n,first);											//线性时间整理静态链表，使得数组按下标有序
}
/************************************************************************/
/*分配过程，
/*Array中存放待排序记录，
/*first：为静态链中的第一个记录，
/*i：第i个排序码
/*r:基数
/************************************************************************/
static void distribute(Record *Array,int first,int i,int r,StaticQueue *queue)
{
	int j,k,a,curr = first;												//curr表示数组Array的下标
	for(j = 0;j<r;j++)													//初始化r个队列
		queue[j].head = -1;
	while(curr != -1)													//对整个静态链进行分配，curr != -1即没到链尾
	{
		k = Array[curr].SortKey;										//取第i位排序码数字k
		for(j = 0;j<i;j++)												//以下两行代码取k的某一位，如个位十位百位。。。
			k = k/r;
		k = k%r;
		//把Array[curr]分配到第k个桶中
		if(-1 == queue[k].head)											//如果桶为空，Array[curr]就是第一个记录
			queue[k].head = curr;										//curr表示数组Array的下标，再次是将数组下标放在桶首
		else
			Array[queue[k].tail].next = curr;							//否则加到桶的尾部
		queue[k].tail = curr;											//当前记录的下标curr被标记为该桶的尾部
		curr = Array[curr].next;										//静态指针curr移动1位，继续分配下一个记录
	}
}
/************************************************************************/
/*收集过程，
/*Array中存放待排序记录，
/*first：为静态链中的第一个记录，
/*r:基数
/************************************************************************/
static int collect(Record *Array,int first, int r,StaticQueue *queue)
{
	int last,k = 0;														//已收集到的最后一个记录
	while(-1 == queue[k].head)											//找到第一个非空队列
		k++;
	first = queue[k].head;												//开始数组的下标,first需要返回，故这里用指针取地址
	last = queue[k].tail;												//结束数组的下标
	while(k < r-1)														//继续收集下一个非空队列，r-1是最后一个
	{
		k++;
		while(k<r-1 && queue[k].head == -1)								//当前队列k为空，而且还不是最后
			k++;														//试探下一个队列
		if(queue[k].head != -1)											//将这个非空序列与上一个非空序列连接起来
		{
			Array[last].next = queue[k].head;							//Array[].next相当于中间过度，这里收集就是将队列的收尾相连
			last = queue[k].tail;										//此时最后一个记录为这个序列的尾部记录
		}
	}
	Array[last].next = -1;												//收集完毕
	return first;
}
/************************************************************************/
/*线性时间整理静态链表，使得数组下标有序
/*Array中存放待排序记录，
/*first：为静态链中的第一个记录，
/************************************************************************/
static void AddrSort(Record *Array,int n, int first)
{
	int i,j = first;													//j待处理数据下标，第一次为first
	Record TempRec;
	for(i = 0;i<n-1;i++)												//循环n-1次，每次处理第i大记录
	{
		TempRec = Array[j];												//暂存第i大记录Array[j],Array[i]和Array[j]互换
		Array[j] = Array[i];											//当前下标i的数据存放到j位置
		Array[i] = TempRec;

		Array[i].next = j;												//第i大的记录的next链要保留调换轨迹j
		j = TempRec.next;												//j移动到下一位
		while(j<=i)														//j比i小，则是轨迹，顺链找到数据
			j = Array[j].next;
	}
}
/******************************************链式基数排序结束*********************************************************/

/*********************************************索引排序**************************************************************/
void AdjustRecord(Record *Array,int* IndexArray,int n);
/************************************************************************/
/*采用简单插入的索引排序
/*Array中存放待排序记录，
/*indexArray[]:索引数组
/*n:数组长度
/************************************************************************/
void IndexSort(Record *Array,int IndexArray[],int n)
{
	int i,j;
	Record temp;
	for(i = 0;i<n;i++)
		IndexArray[i] = i;												//初始化索引下标
	//简单插入排序的地址排序过程
	for(i = 1;i<n;i++)													//依次插入第i个记录
	{
		for(j = i;j>0;j--)												//依次比较，发现逆置就交换
		{
			if(Array[IndexArray[j]].SortKey < Array[IndexArray[j-1]].SortKey)
			{
				temp = Array[IndexArray[j]];
				Array[IndexArray[j]] = Array[IndexArray[j-1]];
				Array[IndexArray[j-1]] = temp;
			}
			else														//此时i前面记录已排序
				break;
		}
	}
	AdjustRecord(Array,IndexArray,n);
}
/************************************************************************/
/*根据indexArray整理Array
/*Array中存放待排序记录，
/*indexArray[]:索引数组
/*n:数组长度
/************************************************************************/
void AdjustRecord(Record *Array,int* IndexArray,int n)
{
	Record TempRec;														//只需要一个临时存储空间
	int i,j,k;
	for(i = 0;i<n;i++)													//循环n-1次，每次处理数组中第i个记录
	{
		j = i;															//j为临时变量，是循环链中的当前记录
		TempRec = Array[i];												//暂存i下标中目前的记录
		while(IndexArray[j] != i)										//如果循环链中索引下标还不是i，则顺链循环调整
		{
			k = IndexArray[j];											//k为连接j指向的下标
			Array[j] = Array[k];										//把k下标中的值复制到j位，第j大元素正确归位
			IndexArray[j] = j;											//因为是正确归位，索引j就是自身
			j = k;														//j换到循环链中的下一个，继续处理
		}
		Array[j] = TempRec;												//最后找到的j，其索引下标为i，因此第i大元素正确入位
		IndexArray[j] = j;												//因为是正确归位，索引j就是自身
	}
}
/**********************************************索引排序结束*********************************************************/




void testSort(void)
{
	int i;
	Record testArray[] = {{97},{53},{88},{59},{26},{41},{88},{31},{22}};
	Record tempArray[] = {{97},{53},{88},{59},{26},{41},{88},{31},{22}};//保存数组值
	int ArraySize = sizeof(testArray)/sizeof(Record);
	Record TempArray[9];							//归并排序用
	int IndexArray[9];							//索引排序用

	printf("原始序列：  ");
	for(i = 0;i<ArraySize;i++)
		printf("%d ",testArray[i].SortKey);
	printf("\r\n");

	printf("直接插入排序:");
	InsertSort(testArray,ArraySize);
	for(i = 0;i<ArraySize;i++)
		printf("%d ",testArray[i].SortKey);
	printf("\r\n");

	for(i = 0;i<ArraySize;i++)		//重新赋值
		testArray[i] = tempArray[i];
	printf("Shell排序:   ");
	ShellSort(testArray,ArraySize);
	for(i = 0;i<ArraySize;i++)
		printf("%d ",testArray[i].SortKey);
	printf("\r\n");

	for(i = 0;i<ArraySize;i++)		//重新赋值
		testArray[i] = tempArray[i];
	printf("直接选择排序:");
	SelectSort(testArray,ArraySize);
	for(i = 0;i<ArraySize;i++)
		printf("%d ",testArray[i].SortKey);
	printf("\r\n");

	for(i = 0;i<ArraySize;i++)		//重新赋值
		testArray[i] = tempArray[i];
	printf("堆排序:      ");
	HeapSort(testArray,ArraySize);
	for(i = 0;i<ArraySize;i++)
		printf("%d ",testArray[i].SortKey);
	printf("\r\n");

	for(i = 0;i<ArraySize;i++)		//重新赋值
		testArray[i] = tempArray[i];
	printf("冒泡排序:    ");
	BubbleSort(testArray,ArraySize);
	for(i = 0;i<ArraySize;i++)
		printf("%d ",testArray[i].SortKey);
	printf("\r\n");

	for(i = 0;i<ArraySize;i++)		//重新赋值
		testArray[i] = tempArray[i];
	printf("快速排序:    ");
	QuickSort(testArray,0,ArraySize-1);
	for(i = 0;i<ArraySize;i++)
		printf("%d ",testArray[i].SortKey);
	printf("\r\n");

	for(i = 0;i<ArraySize;i++)		//重新赋值
		testArray[i] = tempArray[i];
	printf("归并排序:    ");
	MergeSort(testArray,TempArray,0,ArraySize-1);
	for(i = 0;i<ArraySize;i++)
		printf("%d ",testArray[i].SortKey);
	printf("\r\n");

	for(i = 0;i<ArraySize;i++)		//重新赋值
		testArray[i] = tempArray[i];
	printf("优化归并排序:");
	ModMergeSort(testArray,TempArray,0,ArraySize-1);
	for(i = 0;i<ArraySize;i++)
		printf("%d ",testArray[i].SortKey);
	printf("\r\n");

	for(i = 0;i<ArraySize;i++)		//重新赋值
		testArray[i] = tempArray[i];
	printf("桶式排序:    ");
	BucketSort(testArray,ArraySize,97+1);
	for(i = 0;i<ArraySize;i++)
		printf("%d ",testArray[i].SortKey);
	printf("\r\n");

	for(i = 0;i<ArraySize;i++)		//重新赋值
		testArray[i] = tempArray[i];
	printf("顺序基数排序:");
	SequenceRadixSort(testArray,ArraySize,2,10);
	for(i = 0;i<ArraySize;i++)
		printf("%d ",testArray[i].SortKey);
	printf("\r\n");

	for(i = 0;i<ArraySize;i++)		//重新赋值
		testArray[i] = tempArray[i];
	printf("链式基数排序:");
	LinkRadixSort(testArray,ArraySize,2,10);
	for(i = 0;i<ArraySize;i++)
		printf("%d ",testArray[i].SortKey);
	printf("\r\n");

	for(i = 0;i<ArraySize;i++)		//重新赋值
		testArray[i] = tempArray[i];
	printf("索引排序:    ");
	IndexSort(testArray,IndexArray,ArraySize);
	for(i = 0;i<ArraySize;i++)
		printf("%d ",testArray[i].SortKey);
	printf("\r\n");
}