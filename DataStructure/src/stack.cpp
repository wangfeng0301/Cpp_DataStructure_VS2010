/*********************************************************************
*ջ����������ջ����ջ��ѹջ�����ջ
*��ʽջ����������ջ����ջ��ѹջ�����ջ��
*�ο����ϣ������ݽṹ���㷨�������������ԣ��Ժ����
*wangfeng
*E-mail:fengwang0301@163.com
*CSDN:https://blog.csdn.net/u013073067?spm=1001.2101.3001.5343
*GitHub:https://github.com/wangfeng0301
*2021.5.3 �״��ύ
*2021.5.12 ����ģ���ʵ�ֺ��ඨ�����һ���ļ��У�������ͷ�ļ���ʵ��
*         ������ĳЩʱ�����ʱ����ִ���
**********************************************************************/
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
using namespace std;

void testStack(void)
{
	Stack<int> s(10);
	int dat;

	if(!s.push(10))
		printf("Stack_Create Error\r\n");
	if(!s.push(11))
		printf("Stack_Create Error\r\n");
	if(!s.push(12))
		printf("Stack_Create Error\r\n");
	if(!s.push(13))
		printf("Stack_Create Error\r\n");
	if(!s.push(14))
		printf("Stack_Create Error\r\n");
	for(int i = 0;i<3;i++)
	{
		if(s.pop(&dat))
		{
			cout <<  dat << endl;	
			cout << "ջ��ʣ��ڵ�������" << s.getSize() << endl;
		}
	}
	s.clear();
	s.isEmpty();
}

void testLinkStack(void)
{
	LinkStack<int> linkstack;
	int dat;

	//LinkStack_Create(&linkstack, sizeof(int));
	linkstack.push(10);
	linkstack.push(11);
	linkstack.push(12);
	linkstack.push(13);

	cout << "��ջ��" << endl;
	for(int i = 0;i<2;i++)
	{
		linkstack.pop(&dat);
		cout << "data->[] = " << dat << endl;	
	}
	linkstack.clear();
	if(linkstack.pop(&dat))
		cout << dat << endl;
}