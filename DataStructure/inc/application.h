#ifndef __APPLICATION_H__
#define __APPLICATION_H__
#include "type.h"

void josephus(unsigned int n,unsigned int s,unsigned int m);

long factorial_recursion(long n);//n的阶乘，递归方式
long factorial_iteration(long n);//n的阶乘，迭代方式
unsigned char RecKnap(int s,int n,int* w);//背包问题，递归方式
unsigned char nonRecKnap(int s,int n,int* w);//背包问题，非递归方式
unsigned char nonRecknapOpt(int s,int n, int* w);//背包问题，优化非递归方式
void testRecursion(void);
void testCalculator(void);
#endif