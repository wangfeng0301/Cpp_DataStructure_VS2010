#include "search.h"

/*���ֲ���
 *arr:Ҫ���ҵ�����,����Ϊ��������
 *arr_len:���鳤��
 *dat:Ҫ���ҵ���
 */
int Search_Binary(int *arr,int arr_len,int dat)
{
	int low = 0;
	int high = arr_len-1;
	int mid;
	int i;
	
	while(low<=high)
	{
		mid = (low + high)/2;
		if(arr[mid]<dat)
		{
			low = mid+1;
		}
		else if(arr[mid]>dat)
		{
			high = mid-1;
		}
		else//�ҵ�
		{
			return mid;
		}
	}
	return -1;
}