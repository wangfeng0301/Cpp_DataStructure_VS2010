#ifndef __APPLICATION_H__
#define __APPLICATION_H__
#include "type.h"

void josephus(unsigned int n,unsigned int s,unsigned int m);

long factorial_recursion(long n);//n�Ľ׳ˣ��ݹ鷽ʽ
long factorial_iteration(long n);//n�Ľ׳ˣ�������ʽ
unsigned char RecKnap(int s,int n,int* w);//�������⣬�ݹ鷽ʽ
unsigned char nonRecKnap(int s,int n,int* w);//�������⣬�ǵݹ鷽ʽ
unsigned char nonRecknapOpt(int s,int n, int* w);//�������⣬�Ż��ǵݹ鷽ʽ
void testRecursion(void);
void testCalculator(void);
#endif