/*********************************************************************
*Ӧ�ó��򣺰���������ջ�����е����ݽṹ��Ӧ��
*�ο����ϣ������ݽṹ���㷨�������������ԣ��Ժ����
*wangfeng
*E-mail:fengwang0301@163.com
*CSDN:https://blog.csdn.net/u013073067?spm=1001.2101.3001.5343
*GitHub:https://github.com/wangfeng0301
*2019.11.28-2021.2.4
*2021.2.3   �޸ģ�ʹ��ͨ��ѭ��˫������Լ˹������
*			���ӣ�ʹ��ͨ��ջʵ����������
*			�޸ģ�ʹ��ͨ��ջ����׳˺ͱ�������
*2021.2.4   �޸ģ������޸�ջ�пպ�����״̬������Ӧ�õ��˺����ı�
**********************************************************************/
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include "application.h"
#include "linkedlist_single.h"
#include "linkedlist_double.h"
#include "stack.h"
#include "string.h"

/************************************************************************
 *����������Josephus���⣨Լɪ�򻷣���n��Χһ�����ӵ�s�˿�ʼ������������m�˳���
 *			�ӳ�����һ�������¿�ʼ������������m�˳��У��Դ����ƣ������г����е���
 *ʹ��˼·��ѭ��˫������/ѭ����������
 *���룺n:������
 *		s:�ӵ�s�˿�ʼ����
 *		m:������m�˳���
 *�������
 *���أ���
************************************************************************/
void josephus(unsigned int n, unsigned int s, unsigned int m)
{
	unsigned int i=0;
	DoubleLinkList_t person;
	unsigned int num;

	if(!CycDoubleLink_Create(&person, 0, NULL, sizeof(unsigned int)))//����һ��ѭ������0����Ч�ڵ�
		return;
	if(n < 1)
	{		
		printf("�������������1��\r\n");
		return;
	}
	if(s > n || s < 1)
	{
		printf("��ʼ��������С�ڵ����������Ҵ���0��\r\n");
		return;
	}
	if(m < 1)
	{
		printf("������m�������0��\r\n");
		return;
	}
	
	for(i=0;i<n;i++)							//��β���n���ڵ㣬��ʾn����
	{
		num = i+1;
		CycDoubleLink_AddNode(&person, &num);
	}
	CycDoubleLink_Traverse(&person);			//����������ÿ�˱��

	for(i = 0;i < n;i++)						//��n�ˣ�ÿ�����1�����
	{
		/* ȡ��s+m���ڵ�����ݣ�s����ʼλ�ã�m��������m������ */
		/* (s-1+m)%(n-i)ȡ���ݵ�λ�� */
		s = (s - 1 + m)%(n - i);				//��ʼλ��
		if(!CycDoubleLink_GetNodeValue(&person, s, &num))
		{
			printf("����\r\n");
			return;
		}
		else
			printf("��̭��%d�˱��:%d\r\n",i + 1,num);//�����ǰ�ڵ���
		if(!CycDoubleLink_DeleteNode(&person, s))
			return;
	}
	CycDoubleLink_Destroy(&person);				//��������
}


typedef struct 
{
	uchar flag;			//Ԫ�ص����ͣ�������������
#define OPERATOR	0x01
#define NUMBER		0x02
	int element;		//Ԫ������
}Postfix_t;
/*��������ȼ�*/
static int OperatorPriority(char c)
{
	int priority = -1;
	switch(c)
	{
		case '+':
		case '-':
			priority = 0;
			break;
		case '*':
		case '/':
			priority = 1;
			break;
		default:
			break;
	}
	return priority;
}
/************************************************************************
 *������������׺���ʽת��׺���ʽ
 *ʹ��˼·������ջ������׺���ʽת�ɺ�׺���ʽ
 *���룺infix:��׺���ʽ�ַ���
 *�����postfix:��׺���ʽ
 *���أ�TRUE or FALSE
************************************************************************/
static bool InfixExp2PostfixExp(char *infix, Postfix_t *postfix)
{
	uchar infix_len;//�ַ�������
	uchar i = 0, j = 0, k = 0;
	char ch[20];
	Stack_t s;

	infix_len = strlen(infix);
	Stack_Create(&s, infix_len, sizeof(char));			//����ջ�ռ䣬��ջֻ��������
	while(i < infix_len)
	{
		/* 1.�������ַ���ת�����������硰123��ת��123,������ֱ�������postfix�� */
		j = 0;
		if(infix[i] <= '9' && infix[i] >= '0')
		{
			while(infix[i] <= '9' && infix[i] >= '0' && i < infix_len)
				ch[j++] = infix[i++];
			ch[j] = 0;									//�ַ���ĩβ���0����ʾ����
			postfix[k].element = atoi(ch);				//�ַ���ת��������
			postfix[k].flag = NUMBER;					//��־��¼Ϊ����
			k ++;
		}
		/* 2.���������ţ�������ջ */
		else if(infix[i] == '(')
		{
			Stack_Push(&s, &infix[i]);
			i ++;
		}
		/* 3.���������� */
		else if(infix[i] == ')')
		{
			/* 3.1 ջ��Ϊ�գ����Ų�ƥ�� */
			if(Stack_IsEmpty(&s))
			{
				Stack_Destroy(&s);
				printf("���Ų�ƥ��\r\n");
				return FALSE;
			}
			/* 3.2 ջ���ǿգ����ε���ջ��Ԫ�أ�ֱ��������һ�������� */
			else
			{
				while(!Stack_IsEmpty(&s))
				{
					if(!Stack_Pop(&s, &ch[0]))
						break;
					if(ch[0] == '(')
					{
						ch[0] = 0;
						break;
					}
					else
					{
						postfix[k].element = ch[0];
						postfix[k].flag = OPERATOR;
						k ++;
					}
				}
				/* 3.2.1 ջ���˻�û�����������ţ������Ų�ƥ�� */
				if(Stack_IsEmpty(&s) && ch[0] != 0)
				{
					Stack_Destroy(&s);
					printf("���Ų�ƥ��\r\n");
					return FALSE;
				}
			}
			i ++;
		}
		/* 4.��������� */
		else if(infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/')
		{
			/* 4.1 ��ջ�ǿ� && ջ�����ǿ����� && ջ����������ȼ��������������������ȼ�������ջ���ŵ���׺���ʽ�� */
			while(!Stack_IsEmpty(&s))
			{
				Stack_GetTop(&s, &ch[0]);
				if(ch[0] != '(' && OperatorPriority(ch[0]) >= OperatorPriority(infix[i]))
				{
					Stack_Pop(&s, &ch[0]);
					postfix[k].element = ch[0];		
					postfix[k].flag = OPERATOR;
					k ++;
				}
				else
					break;
			}
			/* 4.2 ��������������ջ */
			if(!Stack_Push(&s, &infix[i]))
			{
				Stack_Destroy(&s);
				return FALSE;
			}
			i ++;
		}
		else
		{
			printf("���ʽ���ַǷ��ַ�\r\n");
			return FALSE;
		}
	}
	/* 5. ɨ���꣬��ջ����Ԫ�� */
	while(!Stack_IsEmpty(&s))
	{
		Stack_Pop(&s, &ch[0]);
		if(ch[0] != '(')
		{
			postfix[k].element = ch[0];		
			postfix[k].flag = OPERATOR;
			k ++;
		}
		else
		{
			Stack_Destroy(&s);
			printf("���Ų�ƥ��\r\n");
			return FALSE;
		}
	}
	postfix[k].flag = 0;						//��־λ���㣬����������־
	Stack_Destroy(&s);							//����ջ
	return TRUE;
}
/************************************************************************
 *������������������
 *ʹ��˼·������ջ������׺���ʽת�ɺ�׺���ʽ
 *���룺postfix:��׺���ʽ
 *�����result:������
 *���أ�TRUE or FALSE
************************************************************************/
bool Calculator(Postfix_t *postfix, int *result)
{
	Stack_t s;
	uint i = 0;
	int operand1,operand2;

	if(!Stack_Create(&s, 20, sizeof(int)))
		return FALSE;
	while(postfix[i].flag != 0)
	{
		if(postfix[i].flag == OPERATOR)
		{
			if(!Stack_Pop(&s, &operand1))
				goto err;
			if(!Stack_Pop(&s, &operand2))
				goto err;
			switch(postfix[i].element)
			{
				case '+':
					operand2 += operand1;
					break;
				case '-':
					operand2 -= operand1;
					break;
				case '*':
					operand2 *= operand1;
					break;
				case '/':
					if(operand1 == 0)
					{
						printf("��������Ϊ0\r\n");
						goto err;
					}
					operand2 /= operand1;
					break;
				default:
					printf("�Ƿ������\r\n");
					goto err;
			}
			if(!Stack_Push(&s, &operand2))
				goto err;
		}
		else if(postfix[i].flag == NUMBER)
		{
			if(!Stack_Push(&s, &(postfix[i].element)))
				goto err;
		}
		i ++;
	}
	if(!Stack_Pop(&s, result))//���ս����ջ
		goto err;
	if(!Stack_IsEmpty(&s))
	{
		printf("����,�����ջ�ǿ�\r\n");
		goto err;
	}
	Stack_Destroy(&s);
	return TRUE;
err:
	Stack_Destroy(&s);
	return FALSE;
}
void testCalculator(void)
{
	uint i = 0;
	char experssion[512] = {0};
	Postfix_t postfix[100];
	int result;

	printf("��������ʽ��\r\n");
	scanf("%s",experssion);
	if(InfixExp2PostfixExp(experssion, postfix))
	{
		printf("�����׺���ʽ��\r\n");
		while(postfix[i].flag != 0)
		{
			if(postfix[i].flag == OPERATOR)
				printf("%c ",postfix[i].element);
			else if(postfix[i].flag == NUMBER)
				printf("%d ",postfix[i].element);
			i ++;
		}
		printf("\r\n");
		if(Calculator(postfix, &result))
			printf("������Ϊ��%d\r\n",result);
		else
			printf("�������\r\n");
	}
}

/***************************�ݹ��㷨*************************************/
/*n�Ľ׳ˣ��ݹ鷽ʽ*/
long factorial_recursion(long n)
{
	if(n<=1)
		return 1;
	else
		return n*factorial_recursion(n-1);
}
/*n�Ľ׳ˣ�������ʽ*/
long factorial_iteration(long n)
{
	long m=1;
	long i;
	if(n>=0)
	{
		for(i=1;i<=n;i++)
			m = m*i;
	}
	else
	{
		printf("�������Ӧ�ô��ڵ���0��\r\n");
		return 0;
	}
	return m;
}

/************************************************************************
 *�����������򻯵ı�������,����һ�������ɷ�������Ϊs������n����Ʒ�������ֱ�Ϊw0,w1,...wn-1
 *			���ܷ����n����Ʒ��ѡ�����ɷ��뱳����������֮������Ϊs��
 *ʹ��˼·���ݹ鷽ʽ				/	true,   ��s=0
			knap_recursion(s,n)=   |	false,  ��s<0��s>0��n<1��
									\	knap_recursion(s-wn-1,n-1,w)||knap_recursion(s,n-1,w),��s>0��n>=1
 *���룺s:�����ɷ�������
 *		n:n����Ʒ
 *		w:����Ʒ����
 *�������
 *���أ�TRUE or FALSE
************************************************************************/
bool RecKnap(int s, int n, int *w)
{
	if(0 == s)
		return TRUE;
	if(s<0 || (s>0 && n<1))
		return FALSE;
	if(s>0 && n>=1)
	{
		if(RecKnap(s-w[n-1],n-1,w))
		{
			printf("%d ",w[n-1]);
			return TRUE;
		}
		else
			return RecKnap(s,n-1,w);
	}
}


typedef enum //���ص�ַ����
{
	rd1=0,			//��һ�����������knap(s,n)��Ϸ��ص����ñ���������������
	rd2,			//�ڶ������������knap(s-w[n-1],n-1)��ϣ����ص������ú�����������
	rd3				//���������������knap(s,n-1)��ϣ����ص������ú�����������
}rdType_t;
typedef struct  
{
	int s,n;		//�����ĳ���������Ʒ����Ŀ
	rdType_t rd;	//���ص�ַ
	unsigned char k;//�����Ԫ
}KnapNode_t;
/************************************************************************
 *�����������򻯵ı�������,����һ�������ɷ�������Ϊs������n����Ʒ�������ֱ�Ϊw0,w1,...wn-1
 *			���ܷ����n����Ʒ��ѡ�����ɷ��뱳����������֮������Ϊs��
 *ʹ��˼·���ǵݹ鷽����ʹ��ջ
 *			����1����w[n-1]�����ڽ��У����knap(s-w[n-1],n-1)
 *			����2����w[n-1]�������ڽ��У����knap(s,n-1)
 *���룺s:�����ɷ�������
 *		n:n����Ʒ
 *		w:����Ʒ����
 *�������
 *���أ�TRUE or FALSE
************************************************************************/
unsigned char nonRecKnap(int s,int n,int* w)
{
	KnapNode_t tmp,x;
	LinkStack_t knap;										//��ʽջ����

	LinkStack_Create(&knap, sizeof(KnapNode_t));			//������ʽջ

	tmp.s = s;												//�ǵݹ麯�����,��ʼ��
	tmp.n = n;
	tmp.rd = rd1;
	LinkStack_Push(&knap, &tmp);							//����ʼ���Ľڵ��ַѹ��ջ

label0:
	LinkStack_Pop(&knap, &tmp);								//��ջ���鿴ջ��Ԫ�ط��������
	if(tmp.s == 0)											//������ݹ��������
	{
		tmp.k = 1;											//�޸�ջ�������Ԫk,=1��ʾ�н�
		LinkStack_Push(&knap, &tmp);						//�ٴ�ѹջ
		goto label3;										//ת��ݹ���ڴ���
	}
	if(tmp.s<0 || (tmp.s>0 && tmp.n<1))
	{
		tmp.k = 0;											//�޸�ջ�������Ԫk,=0��ʾ�޽�
		LinkStack_Push(&knap, &tmp);						//ѹջ
		goto label3;
	}
	LinkStack_Push(&knap, &tmp);							//��δ����ݹ����

	x.s = tmp.s - w[tmp.n-1];								//���չ���1���д���
	x.n = tmp.n - 1;
	x.rd = rd2;												//����knap(s-w[n-1],n-1)��ϣ����ص������ú�����������
	LinkStack_Push(&knap, &x);								//ѹջ

	goto label0;
label1:														//����1��Ӧ�ķ��ش���
	LinkStack_Pop(&knap, &x);								//��ջ���鿴ջ��Ԫ�ط��������LSpop_knap����int�ͣ���ǿ��ת���ɵ�ַ��Ȼ��ȡֵ��
	if(tmp.k == 1)											//��ĳ��Ľ����ԪΪ��
	{
		x.k = 1;											//�������ϴ������÷�
		LinkStack_Push(&knap, &x);							//ѹջ
		printf("%d ",w[(x.n)-1]);							//�����Ӧ��Ʒ
		goto label3;
	}
	LinkStack_Push(&knap, &x);								//ѹջ,��ĳ��Ľ����ԪΪ��
	
	tmp.s = x.s;											//��ǰ��Ʒ��ѡ�񲻺��ʣ����ݣ����ù���2
	tmp.n = x.n-1;											//���չ���2����ѹջ����
	tmp.rd = rd3;					
	LinkStack_Push(&knap, &tmp);							//ѹջ

	goto label0;
label2:														//����2��Ӧ�ķ��ش���
	LinkStack_Pop(&knap, &x);								//��ջ���鿴ջ��Ԫ�ط��������LSpop_knap����int�ͣ���ǿ��ת���ɵ�ַ��Ȼ��ȡֵ��
	x.k = tmp.k;											//�����Ԫk�������ϴ������÷�
	LinkStack_Push(&knap, &x);								//ѹջ
label3:														//�ݹ���ڴ���
	LinkStack_Pop(&knap, &tmp);								//��ջ���鿴ջ��Ԫ�ط��������LSpop_knap����int�ͣ���ǿ��ת���ɵ�ַ��Ȼ��ȡֵ��
	switch(tmp.rd)
	{
		case rd1:
			LinkStack_Destroy(&knap);
			return tmp.k;									//�㷨���������ؽ��
		case rd2:goto label1;								//ת�����1�ķ��ش���
		case rd3:goto label2;								//ת�����2�ķ��ش���
	}
}
/************************************************************************
 *�����������򻯵ı�������,����һ�������ɷ�������Ϊs������n����Ʒ�������ֱ�Ϊw0,w1,...wn-1
 *			���ܷ����n����Ʒ��ѡ�����ɷ��뱳����������֮������Ϊs��
 *ʹ��˼·���Ż��ǵݹ鷽����ʹ��ջ
 *			����1����w[n-1]�����ڽ��У����knap(s-w[n-1],n-1)
 *			����2����w[n-1]�������ڽ��У����knap(s,n-1)
 *���룺s:�����ɷ�������
 *		n:n����Ʒ
 *		w:����Ʒ����
 *�������
 *���أ�TRUE or FALSE
************************************************************************/
unsigned char nonRecknapOpt(int s,int n, int* w)
{
	int t,n0 = n;
	unsigned char k = 0;									//�������ʼ��Ϊ0����ʾ����
	KnapNode_t tmp,x;										//��ʱ����

	LinkStack_t knap;										//��ʽջ����
	LinkStack_Create(&knap, sizeof(KnapNode_t));			//������ʽջ
	tmp.s = s;
	tmp.rd = rd1;
	LinkStack_Push(&knap, &tmp);							//����ʼ���Ľڵ��ַѹ��ջ

	while(!LinkStack_IsEmpty(&knap))
	{
		t = knap.size;										//��ȡջ�Ĵ�С
		LinkStack_GetTop(&knap,&tmp);						//��ȡջ��Ԫ�أ���������
		
		while(tmp.s>=0 && (tmp.s<=0 || n0>=t))				//����ȡջ��Ԫ�سɹ����ж��Ƿ���ϳ�������
		{
			if(tmp.s == 0)									//�ﵽ��������
			{
				k = 1;									
				break;
			}
			else											//δ�ﵽ��������
			{
				x.s = tmp.s - w[n0-t];
				x.rd = rd2;
				LinkStack_Push(&knap, &x);					
			}
			t = knap.size;
			LinkStack_GetTop(&knap, &tmp);
		}
		
		while(!LinkStack_IsEmpty(&knap))					//���ش���
		{
			LinkStack_Pop(&knap, &tmp);						//����ջ��Ԫ��
			t = knap.size;
			if(tmp.rd == rd1)								//�㷨����
			{
				LinkStack_Destroy(&knap);
				return k;
			}
			if(tmp.rd == rd2)								//�ӹ���1����
			{
				if(1 == k)									//���Ϊ�棬��ӡ��Ӧ��Ʒ
					printf("%d ",w[n0-t]);
				else										//������ݣ����ù���2��ջ
				{
					LinkStack_GetTop(&knap, &x);
					tmp.s = x.s;
					tmp.rd = rd3;
					LinkStack_Push(&knap, &tmp);
					break;
				}
			}
		}
	}
}
void testRecursion(void)
{
	long n=6;//��׳���
	int w[4] = {8,7,1,9};//�󱳰�������
	printf("%ld�Ľ׳ˣ�%ld\r\n",n,factorial_recursion(n));
	printf("%ld�Ľ׳ˣ�%ld\r\n",n,factorial_iteration(n));

	printf("�ݹ鷽���� ");
	if(RecKnap(15,4,w))
		printf("�˱��������н�\r\n");
	else
		printf("�˱��������޽�\r\n");

	printf("�ǵݹ鷽����");
	if(nonRecKnap(15,4,w))
		printf("�˱��������н�\r\n");
	else
		printf("�˱��������޽�\r\n");

	printf("�Ż��ķǵݹ鷽����");
	if(nonRecknapOpt(15,4,w))
		printf("�˱��������н�\r\n");
	else
		printf("�˱��������޽�\r\n");
}