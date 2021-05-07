/*********************************************************************
*应用程序：包含对链表、栈、队列等数据结构的应用
*参考资料：《数据结构与算法》张铭，王腾蛟，赵海燕等
*wangfeng
*E-mail:fengwang0301@163.com
*CSDN:https://blog.csdn.net/u013073067?spm=1001.2101.3001.5343
*GitHub:https://github.com/wangfeng0301
*2019.11.28-2021.2.4
*2021.2.3   修改，使用通用循环双链表解决约斯夫环问题
*			增加，使用通用栈实现四则运算
*			修改，使用通用栈解决阶乘和背包问题
*2021.2.4   修改，由于修改栈判空和判满状态，故相应用到此函数改变
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
 *问题描述：Josephus问题（约瑟夫环）：n人围一桌，从第s人开始报数，数到第m人出列
 *			从出列下一个人重新开始报数，数到第m人出列，以此类推，依次列出出列的人
 *使用思路：循环双向链表/循环单向链表
 *输入：n:总人数
 *		s:从第s人开始报数
 *		m:数到第m人出列
 *输出：无
 *返回：无
************************************************************************/
void josephus(unsigned int n, unsigned int s, unsigned int m)
{
	unsigned int i=0;
	DoubleLinkList_t person;
	unsigned int num;

	if(!CycDoubleLink_Create(&person, 0, NULL, sizeof(unsigned int)))//定义一个循环链表，0个有效节点
		return;
	if(n < 1)
	{		
		printf("总人数必须大于1！\r\n");
		return;
	}
	if(s > n || s < 1)
	{
		printf("开始人数必须小于等于总人数且大于0！\r\n");
		return;
	}
	if(m < 1)
	{
		printf("所报数m必须大于0！\r\n");
		return;
	}
	
	for(i=0;i<n;i++)							//表尾添加n个节点，表示n个人
	{
		num = i+1;
		CycDoubleLink_AddNode(&person, &num);
	}
	CycDoubleLink_Traverse(&person);			//遍历人数及每人编号

	for(i = 0;i < n;i++)						//共n人，每轮输出1个编号
	{
		/* 取第s+m个节点的数据，s是起始位置，m是数到第m个出列 */
		/* (s-1+m)%(n-i)取数据的位置 */
		s = (s - 1 + m)%(n - i);				//开始位置
		if(!CycDoubleLink_GetNodeValue(&person, s, &num))
		{
			printf("出错\r\n");
			return;
		}
		else
			printf("淘汰第%d人编号:%d\r\n",i + 1,num);//输出当前节点编号
		if(!CycDoubleLink_DeleteNode(&person, s))
			return;
	}
	CycDoubleLink_Destroy(&person);				//销毁链表
}


typedef struct 
{
	uchar flag;			//元素的类型：操作符或数字
#define OPERATOR	0x01
#define NUMBER		0x02
	int element;		//元素内容
}Postfix_t;
/*运算符优先级*/
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
 *问题描述：中缀表达式转后缀表达式
 *使用思路：利用栈，将中缀表达式转成后缀表达式
 *输入：infix:中缀表达式字符串
 *输出：postfix:后缀表达式
 *返回：TRUE or FALSE
************************************************************************/
static bool InfixExp2PostfixExp(char *infix, Postfix_t *postfix)
{
	uchar infix_len;//字符串长度
	uchar i = 0, j = 0, k = 0;
	char ch[20];
	Stack_t s;

	infix_len = strlen(infix);
	Stack_Create(&s, infix_len, sizeof(char));			//创建栈空间，该栈只存放运算符
	while(i < infix_len)
	{
		/* 1.将数字字符串转换成整数，如“123”转成123,操作数直接输出到postfix中 */
		j = 0;
		if(infix[i] <= '9' && infix[i] >= '0')
		{
			while(infix[i] <= '9' && infix[i] >= '0' && i < infix_len)
				ch[j++] = infix[i++];
			ch[j] = 0;									//字符串末尾填充0，表示结束
			postfix[k].element = atoi(ch);				//字符串转换成整数
			postfix[k].flag = NUMBER;					//标志记录为数字
			k ++;
		}
		/* 2.遇到开括号，将其入栈 */
		else if(infix[i] == '(')
		{
			Stack_Push(&s, &infix[i]);
			i ++;
		}
		/* 3.遇到闭括号 */
		else if(infix[i] == ')')
		{
			/* 3.1 栈若为空，括号不匹配 */
			if(Stack_IsEmpty(&s))
			{
				Stack_Destroy(&s);
				printf("括号不匹配\r\n");
				return FALSE;
			}
			/* 3.2 栈若非空，依次弹出栈中元素，直到遇到第一个开括号 */
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
				/* 3.2.1 栈空了还没有遇到开括号，则括号不匹配 */
				if(Stack_IsEmpty(&s) && ch[0] != 0)
				{
					Stack_Destroy(&s);
					printf("括号不匹配\r\n");
					return FALSE;
				}
			}
			i ++;
		}
		/* 4.遇到运算符 */
		else if(infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/')
		{
			/* 4.1 当栈非空 && 栈顶不是开括号 && 栈顶运算符优先级不低于输入的运算符优先级，弹出栈顶放到后缀表达式中 */
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
			/* 4.2 将输入的运算符入栈 */
			if(!Stack_Push(&s, &infix[i]))
			{
				Stack_Destroy(&s);
				return FALSE;
			}
			i ++;
		}
		else
		{
			printf("表达式出现非法字符\r\n");
			return FALSE;
		}
	}
	/* 5. 扫描完，出栈所有元素 */
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
			printf("括号不匹配\r\n");
			return FALSE;
		}
	}
	postfix[k].flag = 0;						//标志位清零，用作结束标志
	Stack_Destroy(&s);							//销毁栈
	return TRUE;
}
/************************************************************************
 *问题描述：四则运算
 *使用思路：利用栈，将中缀表达式转成后缀表达式
 *输入：postfix:后缀表达式
 *输出：result:输出结果
 *返回：TRUE or FALSE
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
						printf("除数不能为0\r\n");
						goto err;
					}
					operand2 /= operand1;
					break;
				default:
					printf("非法运算符\r\n");
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
	if(!Stack_Pop(&s, result))//最终结果出栈
		goto err;
	if(!Stack_IsEmpty(&s))
	{
		printf("出错,运算后栈非空\r\n");
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

	printf("请输入表达式：\r\n");
	scanf("%s",experssion);
	if(InfixExp2PostfixExp(experssion, postfix))
	{
		printf("输出后缀表达式：\r\n");
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
			printf("运算结果为：%d\r\n",result);
		else
			printf("计算出错\r\n");
	}
}

/***************************递归算法*************************************/
/*n的阶乘：递归方式*/
long factorial_recursion(long n)
{
	if(n<=1)
		return 1;
	else
		return n*factorial_recursion(n-1);
}
/*n的阶乘：迭代方式*/
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
		printf("输入参数应该大于等于0！\r\n");
		return 0;
	}
	return m;
}

/************************************************************************
 *问题描述：简化的背包问题,假设一个背包可放入重量为s，现有n件物品，重量分别为w0,w1,...wn-1
 *			问能否从这n件物品中选择若干放入背包，是重量之和正好为s？
 *使用思路：递归方式				/	true,   当s=0
			knap_recursion(s,n)=   |	false,  当s<0或（s>0且n<1）
									\	knap_recursion(s-wn-1,n-1,w)||knap_recursion(s,n-1,w),当s>0且n>=1
 *输入：s:背包可放入重量
 *		n:n件物品
 *		w:各物品重量
 *输出：无
 *返回：TRUE or FALSE
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


typedef enum //返回地址类型
{
	rd1=0,			//第一种情况，计算knap(s,n)完毕返回到调用本函数的其他函数
	rd2,			//第二种情况，计算knap(s-w[n-1],n-1)完毕，返回到本调用函数继续计算
	rd3				//第三种情况，计算knap(s,n-1)完毕，返回到本调用函数继续计算
}rdType_t;
typedef struct  
{
	int s,n;		//背包的承重亮和物品的数目
	rdType_t rd;	//返回地址
	unsigned char k;//结果单元
}KnapNode_t;
/************************************************************************
 *问题描述：简化的背包问题,假设一个背包可放入重量为s，现有n件物品，重量分别为w0,w1,...wn-1
 *			问能否从这n件物品中选择若干放入背包，是重量之和正好为s？
 *使用思路：非递归方法，使用栈
 *			规则1：若w[n-1]包含在解中，求解knap(s-w[n-1],n-1)
 *			规则2：若w[n-1]不包含在解中，求解knap(s,n-1)
 *输入：s:背包可放入重量
 *		n:n件物品
 *		w:各物品重量
 *输出：无
 *返回：TRUE or FALSE
************************************************************************/
unsigned char nonRecKnap(int s,int n,int* w)
{
	KnapNode_t tmp,x;
	LinkStack_t knap;										//链式栈变量

	LinkStack_Create(&knap, sizeof(KnapNode_t));			//创建链式栈

	tmp.s = s;												//非递归函数入口,初始化
	tmp.n = n;
	tmp.rd = rd1;
	LinkStack_Push(&knap, &tmp);							//将初始化的节点地址压入栈

label0:
	LinkStack_Pop(&knap, &tmp);								//出栈，查看栈顶元素分情况处理
	if(tmp.s == 0)											//若满足递归出口条件
	{
		tmp.k = 1;											//修改栈顶结果单元k,=1表示有解
		LinkStack_Push(&knap, &tmp);						//再次压栈
		goto label3;										//转向递归出口处理
	}
	if(tmp.s<0 || (tmp.s>0 && tmp.n<1))
	{
		tmp.k = 0;											//修改栈顶结果单元k,=0表示无解
		LinkStack_Push(&knap, &tmp);						//压栈
		goto label3;
	}
	LinkStack_Push(&knap, &tmp);							//尚未满足递归出口

	x.s = tmp.s - w[tmp.n-1];								//按照规则1进行处理
	x.n = tmp.n - 1;
	x.rd = rd2;												//计算knap(s-w[n-1],n-1)完毕，返回到本调用函数继续计算
	LinkStack_Push(&knap, &x);								//压栈

	goto label0;
label1:														//规则1对应的返回处理
	LinkStack_Pop(&knap, &x);								//出栈，查看栈顶元素分情况处理。LSpop_knap返回int型，需强制转换成地址，然后取值。
	if(tmp.k == 1)											//若某层的结果单元为真
	{
		x.k = 1;											//把真结果上传给调用方
		LinkStack_Push(&knap, &x);							//压栈
		printf("%d ",w[(x.n)-1]);							//输出对应物品
		goto label3;
	}
	LinkStack_Push(&knap, &x);								//压栈,若某层的结果单元为假
	
	tmp.s = x.s;											//当前物品的选择不合适，回溯，调用规则2
	tmp.n = x.n-1;											//按照规则2进行压栈处理
	tmp.rd = rd3;					
	LinkStack_Push(&knap, &tmp);							//压栈

	goto label0;
label2:														//规则2对应的返回处理
	LinkStack_Pop(&knap, &x);								//出栈，查看栈顶元素分情况处理。LSpop_knap返回int型，需强制转换成地址，然后取值。
	x.k = tmp.k;											//结果单元k的内容上传给调用方
	LinkStack_Push(&knap, &x);								//压栈
label3:														//递归出口处理
	LinkStack_Pop(&knap, &tmp);								//出栈，查看栈顶元素分情况处理。LSpop_knap返回int型，需强制转换成地址，然后取值。
	switch(tmp.rd)
	{
		case rd1:
			LinkStack_Destroy(&knap);
			return tmp.k;									//算法结束并返回结果
		case rd2:goto label1;								//转向规则1的返回处理处
		case rd3:goto label2;								//转向规则2的返回处理处
	}
}
/************************************************************************
 *问题描述：简化的背包问题,假设一个背包可放入重量为s，现有n件物品，重量分别为w0,w1,...wn-1
 *			问能否从这n件物品中选择若干放入背包，是重量之和正好为s？
 *使用思路：优化非递归方法，使用栈
 *			规则1：若w[n-1]包含在解中，求解knap(s-w[n-1],n-1)
 *			规则2：若w[n-1]不包含在解中，求解knap(s,n-1)
 *输入：s:背包可放入重量
 *		n:n件物品
 *		w:各物品重量
 *输出：无
 *返回：TRUE or FALSE
************************************************************************/
unsigned char nonRecknapOpt(int s,int n, int* w)
{
	int t,n0 = n;
	unsigned char k = 0;									//结果，初始化为0，表示错误
	KnapNode_t tmp,x;										//临时变量

	LinkStack_t knap;										//链式栈变量
	LinkStack_Create(&knap, sizeof(KnapNode_t));			//创建链式栈
	tmp.s = s;
	tmp.rd = rd1;
	LinkStack_Push(&knap, &tmp);							//将初始化的节点地址压入栈

	while(!LinkStack_IsEmpty(&knap))
	{
		t = knap.size;										//获取栈的大小
		LinkStack_GetTop(&knap,&tmp);						//获取栈顶元素，但不弹出
		
		while(tmp.s>=0 && (tmp.s<=0 || n0>=t))				//若获取栈顶元素成功，判断是否符合出口条件
		{
			if(tmp.s == 0)									//达到出口条件
			{
				k = 1;									
				break;
			}
			else											//未达到出口条件
			{
				x.s = tmp.s - w[n0-t];
				x.rd = rd2;
				LinkStack_Push(&knap, &x);					
			}
			t = knap.size;
			LinkStack_GetTop(&knap, &tmp);
		}
		
		while(!LinkStack_IsEmpty(&knap))					//返回处理
		{
			LinkStack_Pop(&knap, &tmp);						//读出栈顶元素
			t = knap.size;
			if(tmp.rd == rd1)								//算法结束
			{
				LinkStack_Destroy(&knap);
				return k;
			}
			if(tmp.rd == rd2)								//从规则1返回
			{
				if(1 == k)									//结果为真，打印对应物品
					printf("%d ",w[n0-t]);
				else										//否则回溯，采用规则2进栈
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
	long n=6;//求阶乘用
	int w[4] = {8,7,1,9};//求背包问题用
	printf("%ld的阶乘：%ld\r\n",n,factorial_recursion(n));
	printf("%ld的阶乘：%ld\r\n",n,factorial_iteration(n));

	printf("递归方法： ");
	if(RecKnap(15,4,w))
		printf("此背包问题有解\r\n");
	else
		printf("此背包问题无解\r\n");

	printf("非递归方法：");
	if(nonRecKnap(15,4,w))
		printf("此背包问题有解\r\n");
	else
		printf("此背包问题无解\r\n");

	printf("优化的非递归方法：");
	if(nonRecknapOpt(15,4,w))
		printf("此背包问题有解\r\n");
	else
		printf("此背包问题无解\r\n");
}