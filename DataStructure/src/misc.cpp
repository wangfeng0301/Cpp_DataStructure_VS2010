/*********************************************************************
*杂乱函数，比较通用的函数
*wangfeng
*E-mail:fengwang0301@163.com
*CSDN:https://blog.csdn.net/u013073067?spm=1001.2101.3001.5343
*GitHub:https://github.com/wangfeng0301
*2021.2.3
**********************************************************************/
#include "misc.h"
/************************************************************************
 *功能：将空类型数据转换成long型
 *输入：dat:数据起始地址
 *		datlen:数据长度（字节）
 *输出：无
 *返回：空，TRUE ；非空，FALSE
************************************************************************/
long void2long(void *dat, uchar datlen)
{
	uchar i;
	long ret = 0;
	for(i = 0;i < datlen; i++)//数据类型转换
	{
#ifdef BIG_ENDIAN
		ret += (*(long *)((uint)dat+i)) << (datlen-1-i)*8;
#else
		ret += (*(long *)((uint)dat+datlen-1-i)) << (datlen-1-i)*8;
#endif
	}
	return ret;
}