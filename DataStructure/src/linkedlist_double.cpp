/************************************************************************
 *˫�������������������������������ڵ㡢�޸�ĳ�ڵ�ֵ��
 *				ɾ����������ɾ��ĳ���ڵ�
 *˫��ѭ�������������������������������ڵ㡢�޸�ĳ�ڵ�ֵ��
 *				ɾ����������ɾ��ĳ���ڵ�
 *�ο����ϣ������ݽṹ���㷨�������������ԣ��Ժ����
 *wangfeng
 *E-mail:fengwang0301@163.com
 *CSDN:https://blog.csdn.net/u013073067?spm=1001.2101.3001.5343
 *GitHub:https://github.com/wangfeng0301
 *2021.5.2  �״��ύ
 *2021.5.12 ����ģ���ʵ�ֺ��ඨ�����һ���ļ��У�������ͷ�ļ���ʵ��
 *         ������ĳЩʱ�����ʱ����ִ���
************************************************************************/
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "linkedlist_double.h"
using namespace std;

void testDoubleLink(void)
{
	int age[4] = {10,11,12,13};
	DoubleLink<int> teacher;//����һ������

	if(teacher.insertNode(age[0]))		//�ڱ�β�����½ڵ�
		teacher.traverse();		//��������
	if(teacher.insertNode(age[1]))		//�ڱ�β�����½ڵ�
		teacher.traverse();		//��������
	if(teacher.insertNode(age[2]))		//�ڱ�β�����½ڵ�
		teacher.traverse();		//��������
	if(teacher.insertNode(age[3]))		//�ڱ�β�����½ڵ�
		teacher.traverse();		//��������

	if(teacher.insertNode(4,14))		//�ڵ�n���ڵ�ǰ�����½ڵ�
		teacher.traverse();		//��������
	
	if(teacher.changeNodeValue(0, 1))	//�޸ĵ�3���ڵ��ֵ
		teacher.traverse();		//��������
	
	if(teacher.deleteNode(2))		//ɾ���ڵ�
		teacher.traverse();		//��������
	if(teacher.deleteNode())		//ɾ���ڵ�
		teacher.traverse();		//��������
	
	if(teacher.clear())		//�������
		teacher.traverse();		//��������

	
}

#if 0
void testCycDoubleLink(void)
{
	int age[4] = {10,11,12,13};
	int dat;
	DoubleLinkList_t people;

	if(CycDoubleLink_Create(&people, sizeof(age)/sizeof(age[0]), age, sizeof(age[0])))
		CycDoubleLink_Traverse(&people);		//��������

	dat = 1;
	if(CycDoubleLink_InsertNode(&people, 4, &dat))		//�ڵ�n���ڵ�ǰ�����½ڵ�
		CycDoubleLink_Traverse(&people);		//��������
	
	dat = 2;
	if(CycDoubleLink_ChangeNodeValue(&people, 3, &dat))//�޸ĵ�3���ڵ��ֵ
		CycDoubleLink_Traverse(&people);		//��������
	
	dat = 3;
	if(CycDoubleLink_AddNode(&people, &dat))		//����β�����½ڵ�
		CycDoubleLink_Traverse(&people);		//��������
	if(CycDoubleLink_AddNode(&people, &dat))		//����β�����½ڵ�
		CycDoubleLink_Traverse(&people);		//��������

	if(CycDoubleLink_DeleteNode(&people,12))	//ɾ���ڵ�
		CycDoubleLink_Traverse(&people);		//��������

	if(CycDoubleLink_DeleteNode(&people,0))	//ɾ���ڵ�
		CycDoubleLink_Traverse(&people);		//��������
	
	if(CycDoubleLink_Clear(&people))	//ɾ������
		CycDoubleLink_Traverse(&people);		//��������
	
	if(CycDoubleLink_Destroy(&people))	//ɾ������
		CycDoubleLink_Traverse(&people);		//��������
}
#endif