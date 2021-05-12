/************************************************************************
 *���У��Ƚ��ȳ���һ�����ݽṹ
 *�ο����ϣ������ݽṹ���㷨�������������ԣ��Ժ����
 *wangfeng
 *E-mail:fengwang0301@163.com
 *CSDN:https://blog.csdn.net/u013073067?spm=1001.2101.3001.5343
 *GitHub:https://github.com/wangfeng0301
 *2021.5.3 �״��ύ
 *2021.5.12 ����ģ���ʵ�ֺ��ඨ�����һ���ļ��У�������ͷ�ļ���ʵ��
 *         ������ĳЩʱ�����ʱ����ִ���
************************************************************************/
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
using namespace std;


void testQueue(void)
{
	Queue<int> q(5);
	int dat;

	q.en(10);
	q.en(11);
	q.en(12);
	q.en(13);
	q.en(14);
	q.en(15);
	for(int i = 0;i<5;i++)
	{
		if(q.de(&dat))
			cout << dat << endl;
	}
	q.clear();
	if(q.de(&dat))
		cout << dat << endl;	
}

void testLinkQueue(void)
{
	LinkQueue<int> q;
	int dat;

	q.en(10);
	q.en(11);
	q.en(12);
	q.en(13);
	q.en(14);
	q.en(15);
	for(int i = 0;i<5;i++)
	{
		if(q.de(&dat))
			cout << dat << endl;
	}
	q.clear();
	if(q.de(&dat))
		cout << dat << endl;
	
}