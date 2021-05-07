/*********************************************************************
*���������㷨
*wangfeng
*2019.11.28
*�ο����ϣ������ݽṹ���㷨�������������ԣ��Ժ����
**********************************************************************/
#include <stdio.h>
#include <malloc.h>
#include "sort.h"

/************************************************************************/
/* ֱ�Ӳ�������
/* Array[]������������
/* n�����鳤��
/************************************************************************/
void InsertSort(Record Array[],int n)
{
	Record tempRecord;												//��ʱ����
	int i,j;
	for(i = 1;i < n;i++)											//���β����i����¼
	{
		tempRecord = Array[i];										//����¼Array[i]������ʱ������
		j = i-1;													//�ڴ�ѭ������j��i-1��ʼ
		while(j>=0 && tempRecord.SortKey < Array[j].SortKey)		//��ǰѰ�Ҽ�¼i����ȷλ��
		{
			Array[j+1] = Array[j];									//�����ڼ�¼i�ļ�¼����
			j = j-1;												//�±�jǰ��
		}
		Array[j+1] = tempRecord;									//��ʱ��¼j+1���Ǽ�¼i����ȷλ�ã�����
	}
}

/************************************************************************/
/* �޸ĵĲ��������㷨
/* Array[]������������
/* n�����鳤��
/* delta:��ǰ����
/************************************************************************/
void ModInsertSort(Record Array[],int n,int delta)
{
	int i,j;
	Record temp;
	for(i = delta;i < n;i += delta)									//���������е�i����¼��Ѱ�Һ��ʵĲ���λ��
	{
		for(j = i;j>=delta;j -= delta)								//j��deltaΪ������ǰѰ�����öԽ��е���
		{
			if(Array[j].SortKey < Array[j-delta].SortKey)			//Array[j]<Array[j-delta]�������Ϊ���ö�
			{
				temp = Array[j];									//����
				Array[j] = Array[j-delta];
				Array[j-delta] = temp;
			}
			else
				break;
		}
	}
}
/************************************************************************/
/* Shell����/��С��������
/* Array[]������������
/* n�����鳤��
/************************************************************************/
void ShellSort(Record Array[],int n)
{
	int i,delta;
	for(delta = n/2;delta>0;delta /=2)								//����deltaÿ�γ���2�ݼ�
	{
		for(i = 0;i<delta;i++)										//�ֱ��delta�������н��в�������
			ModInsertSort(&Array[i],n-i,delta);						//"&"��Array[i]�ĵ�ַ�����������鳤��Ϊn-i
	}
	//ModInsertSort(Array,n,1);										//����������в��ܱ�֤���һ��delta���Ϊ1�����԰����������ɨβ���ʵĲ�������
}

/************************************************************************/
/* ֱ��ѡ������
/* Array[]������������
/* n�����鳤��
/************************************************************************/
void SelectSort(Record Array[],int n)
{
	int i,j,smallest;
	Record temp;
	for(i = 0;i<n-1;i++)											//����ѡ����iС�ļ�¼����ʣ���¼����С���Ǹ�
	{
		smallest = i;												//���ȼ����¼i������С��
		for(j = i+1;j<n;j++)										//��ʼ���ɨ������ʣ���¼
		{
			if(Array[j].SortKey < Array[smallest].SortKey)			//���ָ�С�ļ�¼����¼����λ��
				smallest = j;
		}
		temp = Array[smallest];										//��������iС�ļ�¼��λ
		Array[smallest] = Array[i];
		Array[i] = temp;
	}
}

/******************************************������*************************************************************/

/************************************************************************/
/*�Ը�iΪ�����½��е���                                                 */
/*left:��left��ʼ����ɸѡ
/*���أ���
/************************************************************************/
static void SiftDown(SortHeap *heap,int left)
{
	int i = left;													//��left��ʼ����ɸѡ
	int j = 2*i+1;													//i�����ӽڵ�
	Record temp = heap->heapArray[i];								//���游�ڵ�

	while(j < heap->CurrentSize)									//�ڵ���С�ڵ�ǰ��С
	{
		if((j < heap->CurrentSize-1) && (heap->heapArray[j].SortKey < heap->heapArray[j+1].SortKey))//�������ӽڵ㣬�����ӽڵ�������ӽڵ�
			j++;													//jָ�����ӽڵ�
		if(temp.SortKey < heap->heapArray[j].SortKey)				//���ڵ�С���ӽڵ�,����λ��
		{
			heap->heapArray[i] = heap->heapArray[j];
			i = j;
			j = 2*i+1;												//���������ߣ����ӽڵ�
		}
		else
			break;													//����������ʱ�˳�
	}
	heap->heapArray[i] = temp;
}
/************************************************************************/
/*���Ͻ��е���                                                 */
/*heap:�ѽṹ��
/*���أ���
/************************************************************************/
static void SiftUp(SortHeap *heap,int pos)
{
	int position = pos;								//�ӵ�ǰ��Сλ�ÿ�ʼ���ϵ���
	Record temp = heap->heapArray[position];		//���浱ǰֵ
	while((position > 0) && (heap->heapArray[(position-1)/2].SortKey < temp.SortKey))//δ���������ڵ㣬�Ҹ��ڵ�ȵ�ǰ�ڵ�С
	{
		heap->heapArray[position] = heap->heapArray[(position-1)/2];
		position = (position-1)/2;					//���������ڵ�λ��
	}
	heap->heapArray[position] = temp;
}
/************************************************************************/
/*�������ѽṹ                                                        */
/*data:�����ռ䣬Record����
/*heap:�ѽṹ����
/*size:���ݴ�С
/*���أ���
/************************************************************************/
void BuildMaxHeap(SortHeap *heap,Record *data,int maxsize)
{
	int i;
	//if(heap->MaxSize<=0)										//���������ռ�������0
	//	return;
	heap->MaxSize = maxsize;									//�������ֵ
	//heap->heapArray = (int *)malloc(heap->MaxSize*sizeof(int));	//����maxsize���ռ��С
	heap->CurrentSize = maxsize;									//��ǰ����Ԫ�ظ���
	heap->heapArray = data;										//��ֵ
	//for(i=0;i<heap->CurrentSize;i++)							//���ݸ�ֵ
	//	heap->heapArray[i] = data[i];

	for(i = heap->CurrentSize/2-1;i>=0;i--)						//ɸѡ�����ѣ���n/2-1��ʼ
	{
		SiftDown(heap,i);
	}
	//printf("\r\n������");
	//for(i = 0;i<heap->CurrentSize;i++)
	//	printf("%d ",heap->heapArray[i].SortKey);
	//printf("\r\n");
}
/************************************************************************/
/*�ӶѶ�ɾ�����ֵ                                                       */
/*heap:�ѽṹ����
/*���أ��������ֵ�ڵ�
/************************************************************************/
static Record MaxHeapRemoveMax(SortHeap *heap)
{
//	int i;
	Record temp;
	if(0 == heap->CurrentSize)										//��ǰ��СΪ0���޷�ɾ��
	{
		printf("��ǰ�Ѵ�СΪ0���޷�ɾ��\r\n");
		return;
	}
	else
	{
		heap->CurrentSize--;										//��ǰ��С��1

		temp = heap->heapArray[0];									//�����Ѷ��Ͷ�ĩβ�ڵ㣨��¼��
		heap->heapArray[0] = heap->heapArray[heap->CurrentSize];
		heap->heapArray[heap->CurrentSize] = temp;

		if(heap->CurrentSize > 1)									//��ǰ��С����1���ӶѶ���ʼ����ɸѡ����
			SiftDown(heap,0);

		//printf("\r\n������");
		//for(i = 0;i<heap->CurrentSize;i++)
		//	printf("%d ",heap->heapArray[i].SortKey);
		//printf("\r\n");

		return heap->heapArray[heap->CurrentSize];
	}
}
/************************************************************************/
/* ������
/* Array[]������������
/* n�����鳤��
/************************************************************************/
void HeapSort(Record Array[],int n)
{
	int i;
	SortHeap heap;													//�������
	BuildMaxHeap(&heap,Array,n);									//��������
	for(i = 0;i<n-1;i++)
	{
		MaxHeapRemoveMax(&heap);
	}
}
/******************************************���������*********************************************************/

/************************************************************************/
/* ð������
/* Array[]������������
/* n�����鳤��
/************************************************************************/
void BubbleSort(Record Array[],int n)
{
	int i,j;
	Record temp;													//�������
	for(i = 0;i<n-1;i++)											//��ѭ��
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

/******************************************��������*********************************************************/
/************************************************************************/
/* ѡ����ֵ
/* left:�������
/* right:�����Ҷ�
/************************************************************************/
int SelectPivot(int left, int right)
{
	return (left+right)/2;									//ѡ���м�ֵ��Ϊ��ֵ
}
/************************************************************************/
/* �ָ��,�ָ����ֵ������ȷλ��
/* Array[]������������
/* left:�������
/* right:�����Ҷ�
/************************************************************************/
int Partition(Record Array[],int left,int right)
{
	Record temp = Array[right];								//����ֵ������ʱ������
	while(left != right)									//��ʼ�ָleft/right�������м��ƶ���ֱ������
	{
		while(Array[left].SortKey <= Array[right].SortKey && right>left)//leftָ�������ƶ���Խ����ЩС�ڵ�����ֵ�ļ�¼��ֱ���ҵ�һ��������ֵ�ļ�¼
			left++;
		if(left<right)										//��left/right��δ������������Ԫ�ػ����ұߵĿ�λ
		{
			Array[right] = Array[left];
			right--;										//rightָ������
		}
		while(Array[right].SortKey >= temp.SortKey && right>left)//rightָ�������ƶ���Խ����Щ���ڵ�����ֵ�ļ�¼��ֱ���ҵ�һ��С����ֵ�ļ�¼
			right--;
		if(left<right)										//��left/right��δ������������Ԫ�ػ�����ߵĿ�λ
		{
			Array[left] = Array[right];
			left++;
		}
	}
	Array[left] = temp;										//����ֵ����ֽ�λ����
	return left;											//���طֽ�λ��left
}

/************************************************************************/
/* ��������
/* Array[]������������
/* left:�������
/* right:�����Ҷ�
/************************************************************************/
void QuickSort(Record Array[],int left,int right)
{
	int pivot;												//��ֵ
	Record temp;
	if(right<=left)											//�����������ֻ��0��1����¼���Ͳ���Ҫ����
		return;
	pivot = SelectPivot(left,right);						//ѡ����ֵ
	temp = Array[left];										//�ָ�ǰ����ֵ�ŵ�����ĩ��
	Array[left] = Array[right];
	Array[right] = temp;
	pivot = Partition(Array,left,right);					//�ָ����ֵ������ȷλ��
	QuickSort(Array,left,pivot-1);							//����ֵ��ߵ������н��еݹ��������
	QuickSort(Array,pivot+1,right);							//����ֵ�ұߵ������н��еݹ��������
}
/******************************************�����������*********************************************************/

/*���������ж�������ɨ�裬�鲢��������*/
void Merge(Record Array[],Record TempArray[],int left,int right,int middle)
{
	int i,j,index1,index2;									
	for(j = left;j<=right;j++)								//��������ʱ�������ʱ����
		TempArray[j] = Array[j];
	index1 = left;											//�����������ʼλ��
	index2 = middle+1;										//�ұ���������ʼλ��
	i = left;												//����ʼ�鲢
	while(index1 <= middle && index2 <= right)				//ȡ��С�߲���ϲ�������
	{
		if(TempArray[index1].SortKey <= TempArray[index2].SortKey)//Ϊ��֤�ȶ��ԣ����ʱ�������
			Array[i++] = TempArray[index1++];
		else
			Array[i++] = TempArray[index2++];
	}
	while(index1 <= middle)									//ֻʣ�����У�����ֱ�Ӹ���
		Array[i++] = TempArray[index1++];
	while(index2 <= right)									//���ϸ�ѭ�����⣬ֱ�Ӹ���ʣ���������
		Array[i++] = TempArray[index2++];
}
/************************************************************************/
/* �鲢����
/* Array[]������������
/* left:��������±�
/* right:�����Ҷ��±�
/************************************************************************/
void MergeSort(Record Array[],Record TempArray[],int left,int right)
{
	int middle;												//
	if(left<right)											//���������ֻ��0��1����¼���Ͳ�������
	{
		middle = (left+right)/2;							//���м仮��Ϊ����������
		MergeSort(Array,TempArray,left,middle);				//�����һ����еݹ�
		MergeSort(Array,TempArray,middle+1,right);			//���ұ�һ����еݹ�
		Merge(Array,TempArray,left,right,middle);			//���й鲢
	}
}

/*�Ż���Sedgwick�������������й鲢���������������ˣ������������м�ɨ�裬�鲢��������*/
void ModMerge(Record Array[],Record TempArray[],int left,int right,int middle)
{
	int i,j,k,index1,index2;									
	for(i = left;i<=middle;i++)								//������ߵ�������
		TempArray[i] = Array[i];
	for(j = 1;j<right-middle;j++)							//�����ұߵ������У���˳��ߵ�����
		TempArray[right-j+1] = Array[j+middle];
	for(index1 = left,index2 = right,k = left;k<=right;k++)	//��ʼ�鲢��ȡ��С�߲���ϲ�������
	{
		if(TempArray[index1].SortKey<=TempArray[index2].SortKey)//Ϊ��֤�ȶ��ԣ����ʱ�������
			Array[k] = TempArray[index1++];
		else
			Array[k] = TempArray[index2--];
	}
}
/************************************************************************/
/* �Ż��Ĺ鲢����
/* Array[]������������
/* left:��������±�
/* right:�����Ҷ��±�
/************************************************************************/
#define	THRESHOLD 28
void ModMergeSort(Record Array[],Record TempArray[],int left,int right)
{
	int middle;												//
	if(right-left+1 > THRESHOLD)							//���������ֻ��0��1����¼���Ͳ�������
	{
		middle = (left+right)/2;							//���м仮��Ϊ����������
		ModMergeSort(Array,TempArray,left,middle);			//�����һ����еݹ�
		ModMergeSort(Array,TempArray,middle+1,right);		//���ұ�һ����еݹ�
		ModMerge(Array,TempArray,left,right,middle);		//���й鲢
	}
	else
		InsertSort(&Array[left],right-left+1);				//С���������н��в�������
}

/************************************************************************/
/* Ͱʽ����
/* Array[]������������
/* n:���鳤��
/* max:�������ֵ
/************************************************************************/
void BucketSort(Record Array[],int n,int max)
{
	Record *TempArray = (Record*)malloc(n*sizeof(Record));		//��ʱ����
	int *count = (int *)malloc(max*sizeof(int));				//Ͱ������������count[i]�洢�˵�i��Ͱ�еļ�¼��
	int i;

	for(i = 0;i<n;i++)											//�����и��Ƶ���ʱ����
		TempArray[i] = Array[i];
	for(i = 0;i<max;i++)										//���м�������ʼΪ0
		count[i] = 0;
	for(i = 0;i<n;i++)											//ͳ��ÿ��ȡֵ���ֵĴ���
		count[Array[i].SortKey]++;
	for(i = 1;i<max;i++)										//ͳ��С�ڵ���i��Ԫ�ظ���
		count[i] = count[i-1] + count[i];						//count[i]��¼��i+1�Ŀ�ʼλ��
	for(i = n-1;i>=0;i--)										//��β����ʼ˳���������֤������ȶ���
		Array[--count[TempArray[i].SortKey]] = TempArray[i];

	free(count);
	count = NULL;
	free(TempArray);
	TempArray = NULL;
}

/************************************************************************/
/* ˳���������,d��Ͱʽ����
/* Array[]������������
/* n:���鳤��
/* d:���������
/* r:��������ʮ����������0-9��r=10����ĸ����a-z��r=26
/************************************************************************/
void SequenceRadixSort(Record Array[],int n,int d,int r)
{
	Record *TempArray = (Record*)malloc(n*sizeof(Record));		//��ʱ����
	int *count = (int *)malloc(r*sizeof(int));					//Ͱ������������count[i]�洢�˵�i��Ͱ�еļ�¼��
	int i,j,k;
	int Radix = 1;												//ģ���ֽ�λ������ȡArray[j]�ĵ�iλ������

	for(i = 1;i<=d;i++)											//�ֱ�Ե�i����������з���
	{
		for(j = 0;j<r;j++)										//���м�������ʼΪ0
			count[j] = 0;
		for(j = 0;j<n;j++)										//ͳ��ÿ��Ͱ�еļ�¼��
		{
			k = (Array[j].SortKey/Radix)%r;						//ȡArray[j]�ĵ�iλ������
			count[k]++;											//��Ӧ��������1
		}
		for(j = 1;j<r;j++)										//��TempArray�е�λ�����η����r��Ͱ
			count[j] = count[j-1]+count[j];						
		//count[i]��¼��i+1�Ŀ�ʼλ�ã�Ԫ��iӦ�ô�Array[count[i]-1]��ǰ׷�ݣ����count[i]-count[i-1]��
		for(j = n-1;j>=0;j--)									//������β��������¼�ռ�����ӦͰ��
		{
			k = (Array[j].SortKey/Radix)%r;						//ȡArray[j]�ĵ�iλ�����룬Array[j]Ӧ�÷ŵ�count[k]-1��
			count[k]--;											//ʹ���˵�k��Ͱ��һ��λ�ã�Ͱʣ�����ļ�������1
			TempArray[count[k]] = Array[j];						//Array[j]�ŵ�TempArray�У��±�λ���������Ѿ�����1
		}
		for(j = 0;j<n;j++)										//����ʱ�����е����ݸ��Ƶ�Array��
			Array[j] = TempArray[j];
		Radix *=r;												//�����һλ���޸�ģRadix
	}
	free(count);
	count = NULL;
	free(TempArray);
	TempArray = NULL;
}

/******************************************��ʽ��������*********************************************************/
static void distribute(Record *Array,int first,int i,int r,StaticQueue *queue);
static int collect(Record *Array,int first, int r,StaticQueue *queue);
static void AddrSort(Record *Array,int n, int first);
/************************************************************************/
/* ��ʽ��������
/* Array[]������������
/* n:���鳤��
/* d:���������
/* r:��������ʮ����������0-9��r=10����ĸ����a-z��r=26
/************************************************************************/
void LinkRadixSort(Record Array[],int n,int d,int r)
{
	int i ,first=0;														//firstָ��̬���еĵ�һ����¼
	StaticQueue *queue = (StaticQueue*)malloc(r*sizeof(StaticQueue));	//���r��Ͱ�ľ�̬����
	for(i = 0;i<n-1;i++)												//��ʼ�����������ڼ�¼�ľ�ָ̬������Ϊ������
		Array[i].next = i+1;											//��i����¼�ľ�ָ̬������Ϊi+1������һ��Ԫ�ص��±�
	Array[n-1].next = -1;												//��βnextΪ��

	for(i = 0;i<d;i++)													//�ֱ�Ե�i����������з�����ռ���һ��d��
	{
		distribute(Array,first,i,r,queue);								//����
		first = collect(Array,first,r,queue);							//�ռ�,���������ռ����׸�Ԫ�����������±�
	}
	free(queue);
	queue = NULL;
	AddrSort(Array,n,first);											//����ʱ������̬����ʹ�����鰴�±�����
}
/************************************************************************/
/*������̣�
/*Array�д�Ŵ������¼��
/*first��Ϊ��̬���еĵ�һ����¼��
/*i����i��������
/*r:����
/************************************************************************/
static void distribute(Record *Array,int first,int i,int r,StaticQueue *queue)
{
	int j,k,a,curr = first;												//curr��ʾ����Array���±�
	for(j = 0;j<r;j++)													//��ʼ��r������
		queue[j].head = -1;
	while(curr != -1)													//��������̬�����з��䣬curr != -1��û����β
	{
		k = Array[curr].SortKey;										//ȡ��iλ����������k
		for(j = 0;j<i;j++)												//�������д���ȡk��ĳһλ�����λʮλ��λ������
			k = k/r;
		k = k%r;
		//��Array[curr]���䵽��k��Ͱ��
		if(-1 == queue[k].head)											//���ͰΪ�գ�Array[curr]���ǵ�һ����¼
			queue[k].head = curr;										//curr��ʾ����Array���±꣬�ٴ��ǽ������±����Ͱ��
		else
			Array[queue[k].tail].next = curr;							//����ӵ�Ͱ��β��
		queue[k].tail = curr;											//��ǰ��¼���±�curr�����Ϊ��Ͱ��β��
		curr = Array[curr].next;										//��ָ̬��curr�ƶ�1λ������������һ����¼
	}
}
/************************************************************************/
/*�ռ����̣�
/*Array�д�Ŵ������¼��
/*first��Ϊ��̬���еĵ�һ����¼��
/*r:����
/************************************************************************/
static int collect(Record *Array,int first, int r,StaticQueue *queue)
{
	int last,k = 0;														//���ռ��������һ����¼
	while(-1 == queue[k].head)											//�ҵ���һ���ǿն���
		k++;
	first = queue[k].head;												//��ʼ������±�,first��Ҫ���أ���������ָ��ȡ��ַ
	last = queue[k].tail;												//����������±�
	while(k < r-1)														//�����ռ���һ���ǿն��У�r-1�����һ��
	{
		k++;
		while(k<r-1 && queue[k].head == -1)								//��ǰ����kΪ�գ����һ��������
			k++;														//��̽��һ������
		if(queue[k].head != -1)											//������ǿ���������һ���ǿ�������������
		{
			Array[last].next = queue[k].head;							//Array[].next�൱���м���ȣ������ռ����ǽ����е���β����
			last = queue[k].tail;										//��ʱ���һ����¼Ϊ������е�β����¼
		}
	}
	Array[last].next = -1;												//�ռ����
	return first;
}
/************************************************************************/
/*����ʱ������̬����ʹ�������±�����
/*Array�д�Ŵ������¼��
/*first��Ϊ��̬���еĵ�һ����¼��
/************************************************************************/
static void AddrSort(Record *Array,int n, int first)
{
	int i,j = first;													//j�����������±꣬��һ��Ϊfirst
	Record TempRec;
	for(i = 0;i<n-1;i++)												//ѭ��n-1�Σ�ÿ�δ����i���¼
	{
		TempRec = Array[j];												//�ݴ��i���¼Array[j],Array[i]��Array[j]����
		Array[j] = Array[i];											//��ǰ�±�i�����ݴ�ŵ�jλ��
		Array[i] = TempRec;

		Array[i].next = j;												//��i��ļ�¼��next��Ҫ���������켣j
		j = TempRec.next;												//j�ƶ�����һλ
		while(j<=i)														//j��iС�����ǹ켣��˳���ҵ�����
			j = Array[j].next;
	}
}
/******************************************��ʽ�����������*********************************************************/

/*********************************************��������**************************************************************/
void AdjustRecord(Record *Array,int* IndexArray,int n);
/************************************************************************/
/*���ü򵥲������������
/*Array�д�Ŵ������¼��
/*indexArray[]:��������
/*n:���鳤��
/************************************************************************/
void IndexSort(Record *Array,int IndexArray[],int n)
{
	int i,j;
	Record temp;
	for(i = 0;i<n;i++)
		IndexArray[i] = i;												//��ʼ�������±�
	//�򵥲�������ĵ�ַ�������
	for(i = 1;i<n;i++)													//���β����i����¼
	{
		for(j = i;j>0;j--)												//���αȽϣ��������þͽ���
		{
			if(Array[IndexArray[j]].SortKey < Array[IndexArray[j-1]].SortKey)
			{
				temp = Array[IndexArray[j]];
				Array[IndexArray[j]] = Array[IndexArray[j-1]];
				Array[IndexArray[j-1]] = temp;
			}
			else														//��ʱiǰ���¼������
				break;
		}
	}
	AdjustRecord(Array,IndexArray,n);
}
/************************************************************************/
/*����indexArray����Array
/*Array�д�Ŵ������¼��
/*indexArray[]:��������
/*n:���鳤��
/************************************************************************/
void AdjustRecord(Record *Array,int* IndexArray,int n)
{
	Record TempRec;														//ֻ��Ҫһ����ʱ�洢�ռ�
	int i,j,k;
	for(i = 0;i<n;i++)													//ѭ��n-1�Σ�ÿ�δ��������е�i����¼
	{
		j = i;															//jΪ��ʱ��������ѭ�����еĵ�ǰ��¼
		TempRec = Array[i];												//�ݴ�i�±���Ŀǰ�ļ�¼
		while(IndexArray[j] != i)										//���ѭ�����������±껹����i����˳��ѭ������
		{
			k = IndexArray[j];											//kΪ����jָ����±�
			Array[j] = Array[k];										//��k�±��е�ֵ���Ƶ�jλ����j��Ԫ����ȷ��λ
			IndexArray[j] = j;											//��Ϊ����ȷ��λ������j��������
			j = k;														//j����ѭ�����е���һ������������
		}
		Array[j] = TempRec;												//����ҵ���j���������±�Ϊi����˵�i��Ԫ����ȷ��λ
		IndexArray[j] = j;												//��Ϊ����ȷ��λ������j��������
	}
}
/**********************************************�����������*********************************************************/




void testSort(void)
{
	int i;
	Record testArray[] = {{97},{53},{88},{59},{26},{41},{88},{31},{22}};
	Record tempArray[] = {{97},{53},{88},{59},{26},{41},{88},{31},{22}};//��������ֵ
	int ArraySize = sizeof(testArray)/sizeof(Record);
	Record TempArray[9];							//�鲢������
	int IndexArray[9];							//����������

	printf("ԭʼ���У�  ");
	for(i = 0;i<ArraySize;i++)
		printf("%d ",testArray[i].SortKey);
	printf("\r\n");

	printf("ֱ�Ӳ�������:");
	InsertSort(testArray,ArraySize);
	for(i = 0;i<ArraySize;i++)
		printf("%d ",testArray[i].SortKey);
	printf("\r\n");

	for(i = 0;i<ArraySize;i++)		//���¸�ֵ
		testArray[i] = tempArray[i];
	printf("Shell����:   ");
	ShellSort(testArray,ArraySize);
	for(i = 0;i<ArraySize;i++)
		printf("%d ",testArray[i].SortKey);
	printf("\r\n");

	for(i = 0;i<ArraySize;i++)		//���¸�ֵ
		testArray[i] = tempArray[i];
	printf("ֱ��ѡ������:");
	SelectSort(testArray,ArraySize);
	for(i = 0;i<ArraySize;i++)
		printf("%d ",testArray[i].SortKey);
	printf("\r\n");

	for(i = 0;i<ArraySize;i++)		//���¸�ֵ
		testArray[i] = tempArray[i];
	printf("������:      ");
	HeapSort(testArray,ArraySize);
	for(i = 0;i<ArraySize;i++)
		printf("%d ",testArray[i].SortKey);
	printf("\r\n");

	for(i = 0;i<ArraySize;i++)		//���¸�ֵ
		testArray[i] = tempArray[i];
	printf("ð������:    ");
	BubbleSort(testArray,ArraySize);
	for(i = 0;i<ArraySize;i++)
		printf("%d ",testArray[i].SortKey);
	printf("\r\n");

	for(i = 0;i<ArraySize;i++)		//���¸�ֵ
		testArray[i] = tempArray[i];
	printf("��������:    ");
	QuickSort(testArray,0,ArraySize-1);
	for(i = 0;i<ArraySize;i++)
		printf("%d ",testArray[i].SortKey);
	printf("\r\n");

	for(i = 0;i<ArraySize;i++)		//���¸�ֵ
		testArray[i] = tempArray[i];
	printf("�鲢����:    ");
	MergeSort(testArray,TempArray,0,ArraySize-1);
	for(i = 0;i<ArraySize;i++)
		printf("%d ",testArray[i].SortKey);
	printf("\r\n");

	for(i = 0;i<ArraySize;i++)		//���¸�ֵ
		testArray[i] = tempArray[i];
	printf("�Ż��鲢����:");
	ModMergeSort(testArray,TempArray,0,ArraySize-1);
	for(i = 0;i<ArraySize;i++)
		printf("%d ",testArray[i].SortKey);
	printf("\r\n");

	for(i = 0;i<ArraySize;i++)		//���¸�ֵ
		testArray[i] = tempArray[i];
	printf("Ͱʽ����:    ");
	BucketSort(testArray,ArraySize,97+1);
	for(i = 0;i<ArraySize;i++)
		printf("%d ",testArray[i].SortKey);
	printf("\r\n");

	for(i = 0;i<ArraySize;i++)		//���¸�ֵ
		testArray[i] = tempArray[i];
	printf("˳���������:");
	SequenceRadixSort(testArray,ArraySize,2,10);
	for(i = 0;i<ArraySize;i++)
		printf("%d ",testArray[i].SortKey);
	printf("\r\n");

	for(i = 0;i<ArraySize;i++)		//���¸�ֵ
		testArray[i] = tempArray[i];
	printf("��ʽ��������:");
	LinkRadixSort(testArray,ArraySize,2,10);
	for(i = 0;i<ArraySize;i++)
		printf("%d ",testArray[i].SortKey);
	printf("\r\n");

	for(i = 0;i<ArraySize;i++)		//���¸�ֵ
		testArray[i] = tempArray[i];
	printf("��������:    ");
	IndexSort(testArray,IndexArray,ArraySize);
	for(i = 0;i<ArraySize;i++)
		printf("%d ",testArray[i].SortKey);
	printf("\r\n");
}