/************************************************************************
 *���������������������������������ڵ㡢�޸�ĳ�ڵ�ֵ��
 *				ɾ����������ɾ��ĳ���ڵ�
 *�ο����ϣ������ݽṹ���㷨�������������ԣ��Ժ����
 *wangfeng
 *E-mail:fengwang0301@163.com
 *CSDN:https://blog.csdn.net/u013073067?spm=1001.2101.3001.5343
 *GitHub:https://github.com/wangfeng0301
 *2021.5.1 �״��ύ
 *2021.5.12 ����ģ���ʵ�ֺ��ඨ�����һ���ļ��У�������ͷ�ļ���ʵ��
 *         ������ĳЩʱ�����ʱ����ִ���
************************************************************************/
#include "linkedlist_single.h"


void testLink(void)
{
	int age[3] = {10,11,12};
	Link<int> student;//����һ������

	if(student.insertNode(age[0]))//����β�����½ڵ�
		student.traverse();//��������
	if(student.insertNode(age[1]))//����β�����½ڵ�
		student.traverse();//��������
	if(student.insertNode(age[2]))//����β�����½ڵ�
		student.traverse();//��������
	
	if(student.changeNodeValue(0,1))//�޸ĵ�0���ڵ��ֵ
		student.traverse();//��������

	if(student.insertNode(3,2))//�ڵ�n���ڵ�ǰ�����½ڵ�
		student.traverse();//��������
	if(student.insertNode(0,3))//�ڵ�n���ڵ�ǰ�����½ڵ�
		student.traverse();//��������

	if(student.deleteNode(0))//ɾ���ڵ�
		student.traverse();//��������
	if(student.deleteNode())//ɾ��β�ڵ�
		student.traverse();//��������
	
	if(student.reverse())//��ת����
		student.traverse();//��������

	if(student.clear())//��ת����
		student.traverse();//��������
}
