#include "search.h"

/*二分查找
 *arr:要查找的数组,必须为有序数组
 *arr_len:数组长度
 *dat:要查找的数
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
		else//找到
		{
			return mid;
		}
	}
	return -1;
}