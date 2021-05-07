/*********************************************************************
*���Һ������Ƚ�ͨ�õĺ���
*wangfeng
*E-mail:fengwang0301@163.com
*CSDN:https://blog.csdn.net/u013073067?spm=1001.2101.3001.5343
*GitHub:https://github.com/wangfeng0301
*2021.2.3
**********************************************************************/
#include "misc.h"
/************************************************************************
 *���ܣ�������������ת����long��
 *���룺dat:������ʼ��ַ
 *		datlen:���ݳ��ȣ��ֽڣ�
 *�������
 *���أ��գ�TRUE ���ǿգ�FALSE
************************************************************************/
long void2long(void *dat, uchar datlen)
{
	uchar i;
	long ret = 0;
	for(i = 0;i < datlen; i++)//��������ת��
	{
#ifdef BIG_ENDIAN
		ret += (*(long *)((uint)dat+i)) << (datlen-1-i)*8;
#else
		ret += (*(long *)((uint)dat+datlen-1-i)) << (datlen-1-i)*8;
#endif
	}
	return ret;
}