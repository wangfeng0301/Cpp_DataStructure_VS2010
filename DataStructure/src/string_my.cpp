/*********************************************************************
*字符串：实现C标准库<string.h>
*参考资料：《数据结构与算法》张铭，王腾蛟，赵海燕等
*wangfeng
*2019.11.28-2021.1.27
**********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "string_my.h"

/************************************************************************
 *功能：在参数 str 所指向的存储空间的前 n 个字节中搜索第一次出现字符 c（一个无符号字符）的位置。
 *输入：str:要执行的内存块
 *		c:以 int 形式传递的值，但是函数在每次字节搜索时是使用该值的无符号字符形式。
 *		n:要被分析的字节数
 *输出：无
 *返回：返回一个指向匹配字节的指针，如果在给定的内存区域未出现字符，则返回 NULL。
************************************************************************/
void *Mymemchr(const void *str, int c, size_t n)
{
	char *temp;
	if(str == NULL)
	{
		printf("字符串为空\r\n");
		exit(-1);
	}
	temp = (char*)str;
	while(n > 0)
	{
		if(*temp == c)
			return (void *)temp;
		n --;
		temp ++;
	}
	return NULL;
}
/************************************************************************
 *功能：把存储区 str1 和存储区 str2 的前 n 个字节进行比较
 *输入：str1:要比较的字符串
 *		str2:要比较的字符串
 *		n:要比较的字节数
 *输出：无
 *返回：str<str2,<0;str1=str2,=0;str1>str2,>0
************************************************************************/
int Mymemcmp(const void *str1, const void *str2, size_t n)
{
	char *temp1,*temp2;
	if(str1 == NULL || str2 == NULL)
	{
		printf("字符串不能为空！\r\n");
		exit(-1);
	}
	temp1 = (char *)str1;
	temp2 = (char *)str2;
	while(n --)
	{
		if(*temp1 > *temp2)
			return 1;
		else if(*temp1 < *temp2)
			return -1;
		temp1 ++;
		temp2 ++;
	}
	return 0;
}
/************************************************************************
 *功能：从存储区 str2 复制 n 个字节到存储区 str1
 *输入：str1:目标数组
 *		str2:原数组
 *		n:字节数
 *输出：无
 *返回：指向目标区str1的指针
************************************************************************/
void *Mymemcpy(void *str1, const void *str2, size_t n) 
{
	char *temp1,*temp2;
	if(str1 == NULL || str2 == NULL)
	{
		printf("字符串不能为空！\r\n");
		exit(-1);
	}
	temp1 = (char *)str1;
	temp2 = (char *)str2;
	while(n --)
	{
		*temp1++ = *temp2++;
	}
	return str1;
}
/************************************************************************
 *功能：从存储区 str2 复制 n 个字节到存储区 str1
 *		与Mymemcpy不同的是，该函数在目标区域和源区域重叠时依然有效。
 *		如果出现覆区域重叠的情况，函数执行后会改变源目标的值
 *输入：str1:目标数组
 *		str2:原数组
 *		n:字节数
 *输出：无
 *返回：指向目标区str1的指针
************************************************************************/
void *Mymemmove(void *str1, const void *str2, size_t n)
{
	char *dst = (char *)str1;
	char *src = (char *)str2;

	if(dst > src && src + n > dst)//目标区域在源区域之后，且有覆盖，此时需要从后向前赋值
	{
		dst += n - 1;
		src += n - 1;
		while(n --)
			*dst-- = *src--;
	}
	else
	{
		while(n --)
			*dst++ = *src++;
	}
	return dst;
}
/************************************************************************
 *功能：复制字符 c（一个无符号字符）到参数 str 所指向的字符串的前 n 个字符
 *输入：str:要填充的内存块
 *		c:被设置的值
 *		n:字节数
 *输出：无
 *返回：返回一个指向存储区 str 的指针
************************************************************************/
void *Mymemset(void *str, int c, size_t n)
{
	char *temp = str;
	while(n --)
		*temp++ = (char)c;
	return str;
}
/************************************************************************
 *功能：src 所指向的字符串追加到 dest 所指向的字符串的结尾
 *输入：src:指向要追加的字符串，该字符串不会覆盖目标字符串。
 *		dest:指向目标数组，该数组包含了一个 C 字符串，且足够容纳追加后的字符串。
 *输出：无
 *返回：返回一个指向最终的目标字符串 dest 的指针。
************************************************************************/
char *Mystrcat(char *dest, const char *src)
{
	char *temp = (char *)src;
	char *temp2 = dest;
	int len = strlen(dest);//目标串大小
	while(*temp != 0)
		temp2[len++] = *temp++;
	temp2[len] = 0;//加结束符
	return dest;
}
/************************************************************************
 *功能：把 src 所指向的字符串追加到 dest 所指向的字符串的结尾，直到 n 字符长度为止。
 *输入：src:要追加的字符串。
 *		dest:指向目标数组，该数组包含了一个 C 字符串，且足够容纳追加后的字符串，包括额外的空字符。
 *		n:要追加的最大字符数。
 *输出：无
 *返回：返回一个指向最终的目标字符串 dest 的指针。
************************************************************************/
char *Mystrncat(char *dest, const char *src, size_t n)
{
	char *temp = (char *)src;
	char *temp2 = dest;
	int len = strlen(dest);//目标串大小
	while(n --)
		temp2[len++] = *temp++;
	temp2[len] = 0;//加结束符
	return dest;
}
/************************************************************************
 *功能：在参数 str 所指向的字符串中搜索第一次出现字符 c（一个无符号字符）的位置。
 *输入：src:要被检索的 C 字符串。
 *		c:在 str 中要搜索的字符。
 *输出：无
 *返回：返回在字符串 str 中第一次出现字符 c 的位置，如果未找到该字符则返回 NULL。
************************************************************************/
char *Mystrchr(const char *str, int c)
{
	char *temp;
	if(str == NULL)
	{
		printf("字符串为空\r\n");
		exit(-1);
	}
	temp = (char *)str;
	while(*temp != 0)
	{
		if(*temp == c)
			return temp;
		temp ++;
	}
	return NULL;
}
/************************************************************************
 *功能：在参数 str 所指向的字符串中搜索最后一次出现字符 c（一个无符号字符）的位置。
 *输入：src:要被检索的 C 字符串。
 *		c:在 str 中要搜索的字符。
 *输出：无
 *返回：返回 str 中最后一次出现字符 c 的位置。如果未找到该值，则函数返回一个空指针。
************************************************************************/
char *Mystrrchr(const char *str, int c)
{
	char *temp,*ret;
	if(str == NULL)
	{
		printf("字符串为空\r\n");
		exit(-1);
	}
	temp = (char *)str;
	ret = NULL;
	while(*temp != 0)
	{
		if(*temp == c)
			ret = temp;
		temp ++;
	}
	return ret;
}
/************************************************************************
 *功能：把 str1 所指向的字符串和 str2 所指向的字符串进行比较
 *输入：str1:要进行比较的第一个字符串。
 *		str2:要进行比较的第二个字符串。
 *输出：无
 *返回：返回值小于 0，则表示 str1 小于 str2。
 *		返回值大于 0，则表示 str1 大于 str2。
 *		返回值等于 0，则表示 str1 等于 str2。
************************************************************************/
int Mystrcmp(const char *str1, const char *str2)
{
	char *temp1,*temp2;
	if(str1 == NULL || str2 == NULL)
	{
		printf("字符串不能为空！\r\n");
		exit(-1);
	}
	temp1 = (char *)str1;
	temp2 = (char *)str2;
	while(*temp1 != 0 || *temp2 != 0)
	{
		if(*temp1 > *temp2)
			return 1;
		else if(*temp1 < *temp2)
			return -1;
		temp1 ++;
		temp2 ++;
	}
	return 0;
}
/************************************************************************
 *功能：把 str1 和 str2 进行比较，最多比较前 n 个字节
 *输入：str1:要进行比较的第一个字符串。
 *		str2:要进行比较的第二个字符串。
 *		n:要比较的最大字符数
 *输出：无
 *返回：返回值小于 0，则表示 str1 小于 str2。
 *		返回值大于 0，则表示 str1 大于 str2。
 *		返回值等于 0，则表示 str1 等于 str2。
************************************************************************/
int Mystrncmp(const char *str1, const char *str2, size_t n)
{
	char *temp1,*temp2;
	if(str1 == NULL || str2 == NULL)
	{
		printf("字符串不能为空！\r\n");
		exit(-1);
	}
	temp1 = (char *)str1;
	temp2 = (char *)str2;
	while((*temp1 != 0 && *temp2 != 0) && n--)
	{
		if(*temp1 > *temp2)
			return 1;
		else if(*temp1 < *temp2)
			return -1;
		temp1 ++;
		temp2 ++;
	}
	if(n)//由于字符串结束而提前结束
	{
		if(*temp1 == 0 && *temp2 != 0)//str1比str2短
			return -1;
		else if(*temp1 != 0 && *temp2 == 0)//str1比str2长
			return 1;
		else
			return 0;
	}
	return 0;
}
/************************************************************************
 *功能：把 str1 和 str2 进行比较，结果取决于 LC_COLLATE 的位置设置
 *输入：str1:要进行比较的第一个字符串。
 *		str2:要进行比较的第二个字符串。
 *输出：无
 *返回：返回值小于 0，则表示 str1 小于 str2。
 *		返回值大于 0，则表示 str1 大于 str2。
 *		返回值等于 0，则表示 str1 等于 str2。
************************************************************************/
int Mystrcoll(const char *str1, const char *str2)
{

}
/************************************************************************
 *功能：把 src 所指向的字符串复制到 dest
 *输入：dest:指向用于存储复制内容的目标数组。
 *		src:要复制的字符串。
 *输出：无
 *返回：返回一个指向最终的目标字符串 dest 的指针。
************************************************************************/
char *Mystrcpy(char *dest, const char *src)
{
	char *temp = dest;
	while((*dest++ = *src++)!='\0');

	return temp;
}
/************************************************************************
 *功能：把 src 所指向的字符串复制到 dest，最多复制 n 个字符。当 src 的长度小于 n 时，dest 的剩余部分将用空字节填充。
 *输入：dest:指向用于存储复制内容的目标数组。
 *		src:要复制的字符串。
 *		n:要从源中复制的字符数。
 *输出：无
 *返回：返回最终复制的字符串
************************************************************************/
char *Mystrncpy(char *dest, const char *src, size_t n)
{
	char *temp = dest;
	while((*dest++ = *src++)!='\0' && n)
		n--;
	while(n)//src长度<n
	{
		*dest++ = 0;
		n--;
	}

	return temp;
}
/************************************************************************
 *功能：检索字符串 str1 开头连续有几个字符都不含字符串 str2 中的字符
 *输入：str1:要被检索的 C 字符串。
 *		str2:该字符串包含了要在 str1 中进行匹配的字符列表。
 *输出：无
 *返回：返回 str1 开头连续都不含字符串 str2 中字符的字符数。
************************************************************************/
size_t Mystrcspn(const char *str1, const char *str2)
{
	// map有32个字节的大小，也就是256个bit，可把map看做一个2维数组[32][8]
    unsigned char map[32] = {0};
	int count = 0;

    // 每个ASCII码(设为c)有7bit，共128个。
    // map数组作为位图记录每个ASCII码是否出现过。map一个字节可以记录8个ASCII码
	// 如“0”的ASCII码是48，那么map[48/8]就是“0”在位图中的第几个字节
	// 而48 & 7（换成二进制就是0011 0000 & 0000 0111,一个字节8bit，所以&7）可以定位到这个字节的第几个bit
    while(*str2)
    {
        map[*str2 >> 3] |= (1 << (*str2 & 7));
        str2++;
    }

    map[0] |= 1;//0在ascii中表示空，所以前面*str退出时一定是空，所以置位
    while(!(map[*str1 >> 3] & (1 << (*str1 & 7))))
    {
        count++;
        str1++;
    }

    return count;
}
/************************************************************************
 *功能：检索字符串 str1 中第一个不在字符串 str2 中出现的字符下标
 *输入：str1:要被检索的 C 字符串。
 *		str2:该字符串包含了要在 str1 中进行匹配的字符列表。
 *输出：无
 *返回：返回 str1 中第一个不在字符串 str2 中出现的字符下标。
************************************************************************/
size_t Mystrspn(const char *str1, const char *str2)
{
	// map有32个字节的大小，也就是256个bit，可把map看做一个2维数组[32][8]
    unsigned char map[32] = {0};
	int count = 0;

    // 每个ASCII码(设为c)有7bit，共128个。
    // map数组作为位图记录每个ASCII码是否出现过。map一个字节可以记录8个ASCII码
	// 如“0”的ASCII码是48，那么map[48/8]就是“0”在位图中的第几个字节
	// 而48 & 7（换成二进制就是0011 0000 & 0000 0111,一个字节8bit，所以&7）可以定位到这个字节的第几个bit
    while(*str2)
    {
        map[*str2 >> 3] |= (1 << (*str2 & 7));
        str2++;
    }

    //map[0] |= 1;//0在ascii中表示空，所以前面*str退出时一定是空，所以置位
    while((map[*str1 >> 3] & (1 << (*str1 & 7))))
    {
        count++;
        str1++;
    }

    return count;
}
/************************************************************************
 *功能：检索字符串 str1 中第一个匹配字符串 str2 中字符的字符，不包含空结束字符。
 *		也就是说，依次检验字符串 str1 中的字符，当被检验字符在字符串 str2 中也包含时，则停止检验，并返回该字符位置。
 *输入：str1:要被检索的 C 字符串。
 *		str2:该字符串包含了要在 str1 中进行匹配的字符列表。
 *输出：无
 *返回：返回 str1 中第一个匹配字符串 str2 中字符的字符，如果未找到字符则返回 NULL。
************************************************************************/
char *Mystrpbrk(const char *str1, const char *str2)
{
	// map有32个字节的大小，也就是256个bit，可把map看做一个2维数组[32][8]
    /*unsigned char map[32] = {0};
	char *ret;

    // 每个ASCII码(设为c)有7bit，共128个。
    // map数组作为位图记录每个ASCII码是否出现过。map一个字节可以记录8个ASCII码
	// 如“0”的ASCII码是48，那么map[48/8]就是“0”在位图中的第几个字节
	// 而48 & 7（换成二进制就是0011 0000 & 0000 0111,一个字节8bit，所以&7）可以定位到这个字节的第几个bit
    while(*str2)
    {
        map[*str2 >> 3] |= (1 << (*str2 & 7));
        str2++;
    }

    map[0] |= 1;//0在ascii中表示空，所以前面*str退出时一定是空，所以置位
	ret = NULL;
    while(!(map[*str1 >> 3] & (1 << (*str1 & 7))))
    {
        str1++;
    }
	return (char *)str1;*/

	return (char *)str1 + Mystrcspn(str1,str2);
}
/************************************************************************
 *功能：计算字符串 str 的长度，直到空结束字符，但不包括空结束字符。
 *输入：str:要计算长度的字符串。
 *输出：无
 *返回：返回字符串的长度。
************************************************************************/
size_t Mystrlen(const char *str)
{
	int lenth=0;
	while(*str++ != '\0')
		lenth++;
	return lenth;
}
/************************************************************************
 *功能：在字符串 haystack 中查找第一次出现字符串 needle 的位置，不包含终止符 '\0'。
 *输入：haystack:要被检索的 C 字符串。
 *		needle:在 haystack 字符串内要搜索的小字符串。
 *输出：无
 *返回：返回在 haystack 中第一次出现 needle 字符串的位置，如果未找到则返回 null。
************************************************************************/
char *Mystrstr(const char *haystack, const char *needle)
{
	int len,len2;
	if(!(len=strlen(needle)))//needle长度为0，表示needle字符串为空
		return(char*)haystack;
	len2 = strlen(haystack);//取字符串haystack长度
	for(;*haystack;++haystack)
	{
		if(len2 >= len)//若haystack剩余长度小于needle长度，则needle必然不是haystack子串
		{
			if(*haystack==*needle && strncmp(haystack,needle,len)==0)
				return(char*)haystack;
			len2 --;
		}
		else
			break;
	}
	return NULL;
}
/************************************************************************
 *功能：分解字符串 str 为一组字符串，delim 为分隔符。
 *输入：str:要被分解成一组小字符串的字符串。
 *		delim:包含分隔符的 C 字符串。
 *输出：无
 *返回：返回被分解的第一个子字符串，如果没有可检索的字符串，则返回一个空指针。
 *详解：
************************************************************************/
char *Mystrtok(char *str, const char *delim)
{
	// map有32个字节的大小，也就是256个bit，可把map看做一个2维数组[32][8]
	unsigned char map[32] = {0};
	static char *laststr;
	char *string_org;

	if(str == NULL)
		str = laststr;
	// 每个ASCII码(设为c)有7bit，共128个。
	// map数组作为位图记录每个ASCII码是否出现过。map一个字节可以记录8个ASCII码
	// 如“0”的ASCII码是48，那么map[48/8]就是“0”在位图中的第几个字节
	// 而48 & 7（换成二进制就是0011 0000 & 0000 0111,一个字节8bit，所以&7）可以定位到这个字节的第几个bit
	while(*delim)
	{
		map[*delim >> 3] |= (1 << (*delim & 7));
		delim ++;
	}
	//map[0] |= 1;//0在ascii中表示空，所以前面*str退出时一定是空，所以置位

	while((map[*str >> 3] & (1 << (*str & 7))) && *str)//找到第一个与分隔符不相等的位置
		str ++;
	string_org = str;
	for(;*str;str++)//循环直到找到分隔符或字符串结束,注意这里不能用while(*str++)判断
	{
		if((map[*str >> 3] & (1 << (*str & 7))))
		{
			*str++ = 0;//找到分隔符的位置清零
			break;
		}
	}
	laststr = str;//记录本次指针，下次使用
	if(string_org == str)//这种情况是字符串中不包含分隔符
		return NULL;
	else
		return string_org;
}
//atoi函数，实现字符串转换为整数
int Myatoi(char *str)
{
	int temp = 0;
	int i=0;
	int length = Mystrlen(str);//字符串长度
	if(str[0] == '-' || str[0] == '+')//判断首字符是不是正负号		
		i++;
	while(i<length)
	{
		if(str[i]>'0'&&str[i]<'9')
		{
			temp = temp*10+(str[i]-'0');
			i++;
		}
		else
		{
			printf("字符%d不合法！\r\n",i);
			return 0;
		}

	}
	if(str[0]=='-')
		temp = -temp;
	return temp;
}

/************************************************************************
 *功能：暴力匹配字符串
 *输入：T:主串。
 *		P:子串
 *输出：无
 *返回：子串在主串中的起始位置。若不存在，返回-1
************************************************************************/
int ViolentMatch(char* T, char* P)
{
	int tLen = strlen(T);
	int pLen = strlen(P);
	int i = 0;//主串索引
	int j = 0;//子串索引

	while(i < tLen && j < pLen)
	{
		if(T[i] == P[j])
		{
			/*1.如果当前字符匹配成功（即T[i] == P[j]），则i++，j++ */
			/*继续比较下一个字符，直到子串结束*/
			i++;
			j++;
		}
		else
		{
			/*2.如果失配（即T[i]! = P[j]），令j = 0,即子串回溯到最开始 */
			/*令i = i - (j - 1)，即主串向右移动1位 */
			i = i - j + 1;
			j = 0;
		}
	}
	/*匹配成功，返回子串P在主串T中的位置，否则返回-1 */
	if(j == pLen)
		return i - j;
	else
		return -1;
}
/************************************************************************
 *功能：使用KMP算法时，计算字符串特征向量
 *输入：P:要被计算的字符串。
 *输出：无
 *返回：next指针
 *详解：
************************************************************************/
static int *findNext(char *P)
{
	int i=0;
	int k=-1;
	int m=strlen(P);//字符串P长度
	int *next = (int *)malloc(m*sizeof(int));//开辟m个int大小空间
	if(m==0)//字符长度为0，退出
		return 0;
	if(next == NULL)//开辟空间失败
		return -1;
	next[0] = -1;
	while(i<m)
	{
		while(k>=0 && P[i]!=P[k])
			k=next[k];
		i++;
		k++;
		if(i==m) break;
		if(P[i] == P[k])
			next[i] = next[k];
		else
			next[i] = k;
	}
	return next;
}
/**************************************************************************
 *功能：KMP算法求子串在主串中的位置
 *输入：s:主串
 *		p:子串
 *输出：无
 *返回：子串在主串中的起始位置。若不存在，返回-1
 *详解：
************************************************************************/
int KmpSearch(char *s,char *p)
{
	int i = 0;
	int j = 0;
	int sLen = strlen(s);
	int pLen = strlen(p);
	int *next = findNext(p);
	if(sLen < pLen)//主串长度小于子串，匹配无法成功
		return -1;
	while (i < sLen && j < pLen)
	{
		//①如果j = -1，或者当前字符匹配成功（即S[i] == P[j]），都令i++，j++    
		if (j == -1 || s[i] == p[j])
		{
			i++;
			j++;
		}
		else
		{
			//②如果j != -1，且当前字符匹配失败（即S[i] != P[j]），则令 i 不变，j = next[j]    
			//next[j]即为j所对应的next值
			j = next[j];
		}
	}
	free(next);
	if (j == pLen)
		return i - j;
	else
		return -1;
}
void testString(void)
{

	char str1[30]="Hello World";
	char str2[]="Thanks";
	char str3[]="abcdaabcab";
	int *next = findNext(str3);
	char str4[]="-123456";
	char ch = 'c';
	int ret,i;
	char *retchar;
	char src[]="Hello World";
	char src2[]="Hello World";
	char * dst,*dst2;
	char str5[50] = {"12345"};
	
	printf("Mymemchr test\r\n");
	retchar = (char*)Mymemchr(str1, ch, strlen(str1));
	printf("[%c] 之后的字符串是 - [%s]\n", ch, retchar);

	printf("\r\nMymemcmp test\r\n");
	ret = Mymemcmp(str1, str2, 5);
	if(ret > 0)
		printf("str2 小于 str1\r\n");
	else if(ret < 0) 
		printf("str1 小于 str2\r\n");
	else 
		printf("str1 等于 str2\r\n");

	printf("\r\nMymemcpy test\r\n");
	printf("使用 memcpy 前: %s\n", str1);
	Mymemcpy(str1, str2, strlen(str2));
	printf("使用 memcpy 后: %s\n", str1);

	printf("\r\nMymemmove test\r\n");
	dst = &src[5];
	printf("源字符串:%s\r\n",src);
	printf("目标字符串:%s\r\n",dst);
	Mymemcpy(dst, src, 6);
	printf("使用 Mymemcpy 后,源字符串: %s\n", src);
	printf("使用 Mymemcpy 后,目标字符串: %s\n", dst);
	dst2 = &src2[5];
	printf("源字符串:%s\r\n",src2);
	printf("目标字符串:%s\r\n",dst2);
	Mymemmove(dst, src2, 6);
	printf("使用 Mymemmove 后,源字符串: %s\n", src2);
	printf("使用 Mymemmove 后,目标字符串: %s\n", dst2);
	printf("使用 Mymemcpy 错误！\n");
	printf("使用 Mymemmove 正确！\n");

	printf("\r\nMymemset test\r\n");
	Mymemset(src2,'A',sizeof(src2)-1);
	printf("src2:%s\r\n",src2);

	printf("\r\nMystrcat test\r\n");
	printf("str5:%s\r\n",str5);
	printf("str1:%s\r\n",str1);
	retchar = Mystrcat(str5,str1);
	printf("链接str5和str1：%s\r\n",retchar);

	printf("\r\nMystrncat test\r\n");
	printf("str5:%s\r\n",str5);
	printf("str1:%s\r\n",str1);
	retchar = Mystrncat(str5,str1,5);
	printf("链接str5和str1：%s\r\n",retchar);

	printf("\r\nMystrchr/Mystrrchr test\r\n");
	printf("str5:%s\r\n",str5);
	ch = 'T';
	retchar = (char*)Mystrchr(str5, ch);
	printf("Mystrchr:[%s]中[%c] 之后的字符串是 - [%s]\n", str5, ch, retchar);
	retchar = (char*)Mystrrchr(str5, ch);
	printf("Mystrrchr:[%s]中[%c] 之后的字符串是 - [%s]\n", str5, ch, retchar);

	printf("\r\nMystrcmp test\r\n");
	printf("str1:%s\r\n",str1);
	printf("str2:%s\r\n",str2);
	ret = Mystrcmp(str1, str2);
	if(ret > 0)
		printf("str2 小于 str1\r\n");
	else if(ret < 0) 
		printf("str1 小于 str2\r\n");
	else 
		printf("str1 等于 str2\r\n");

	printf("\r\nMystrncmp test\r\n");
	printf("str1:%s\r\n",str1);
	printf("str2:%s\r\n",str2);
	ret = Mystrncmp(str1, str2,5);
	if(ret > 0)
		printf("str2 小于 str1\r\n");
	else if(ret < 0) 
		printf("str1 小于 str2\r\n");
	else 
		printf("str1 等于 str2\r\n");

	printf("\r\nMystrcpy test\r\n");
	printf("str1:%s\r\n",str1);
	printf("str2:%s\r\n",str2);
	Mystrcpy(str1,str2);
	//strcpy(str1,str2);
	printf("str1:%s\r\n",str1);
	printf("str1-str2= %d\r\n",Mystrcmp(str1,str2));

	printf("\r\nMystrncpy test\r\n");
	memset(str1,0,sizeof(str1));
	printf("str1:%s\r\n",str1);
	printf("str2:%s\r\n",str2);
	//Mystrncpy(str1,str2,10);
	Mystrncpy(str1,str2,3);
	//strncpy(str1,str2,1);
	printf("str1:%s\r\n",str1);
	printf("str2:%s\r\n",str2);

	printf("\r\nMystrcspn test\r\n");
	printf("str1:%s\r\n",str1);
	printf("str2:%s\r\n",str2);
	printf("第一个匹配的字符是在 %d\n", strcspn(str1,str2) + 1);
	printf("第一个匹配的字符是在 %d\n", Mystrcspn(str1,str2) + 1);

	printf("\r\nMystrspn test\r\n");
	printf("str1:%s\r\n",str1);
	printf("str2:%s\r\n",str2);
	printf("第一个不匹配的字符是在 %d\n", strspn(str1,str2) + 1);
	printf("第一个不匹配的字符是在 %d\n", Mystrspn(str1,str2) + 1);

	printf("\r\nMystrpbrk test\r\n");
	strcpy(str2,"123");
	printf("str1:%s\r\n",str1);
	printf("str2:%s\r\n",str2);
	retchar = strpbrk(str1,str2);
	if(retchar)
		printf("第一个匹配的字符是 %c\n", *retchar);
	else
		printf("未找到匹配字符\n");
	retchar = Mystrpbrk(str1,str2);
	if(retchar)
		printf("第一个匹配的字符是 %c\n", *retchar);
	else
		printf("未找到匹配字符\n");
	
	

	printf("\r\nMystrlen test\r\n");
	printf("str1:%s\r\n",str1);
	printf("str2:%s\r\n",str2);
	printf("Mystrlen(str1):%d\r\n",Mystrlen(str1));
	printf("Mystrlen(str2):%d\r\n",Mystrlen(str2));
	
	printf("\r\nMystrstr test\r\n");
	strcpy(str1,"helloWorld");
	strcpy(str2,"Worl");
	printf("str1:%s\r\n",str1);
	printf("str2:%s\r\n",str2);
	retchar = strstr(str1,str2);
	printf("str1中首次出现str2的字符串:%s\r\n",retchar);
	retchar = Mystrstr(str1,str2);
	printf("str1中首次出现str2的字符串:%s\r\n",retchar);

	printf("\r\nMystrtok test\r\n");
	strcpy(str1,"hello World test");
	strcpy(str2," ");
	printf("str1:%s\r\n",str1);
	printf("str2:%s\r\n",str2);
	retchar = Mystrtok(str1,str2);
	printf("str1被str2分割后:%s\r\n",retchar);
	//printf("str1:%s\r\n",str1);
	//printf("str2:%s\r\n",str2);
	for(i = 0;i<sizeof(str1);i++)
		printf("%d ",str1[i]);
	//strcpy(str1,"hello Worldtest");
	//printf("\r\n中途改变str1的值str1:%s\r\n",str1);
	retchar = Mystrtok(NULL,str2);
	printf("\r\nretchar:%s\r\n",retchar);
	for(i = 0;i<sizeof(str1);i++)
		printf("%d ",str1[i]);
	retchar = Mystrtok(NULL,str2);
	printf("\r\nretchar:%s\r\n",retchar);
	for(i = 0;i<sizeof(str1);i++)
		printf("%d ",str1[i]);

	printf("字符串%s转化为整数：%d\r\n",str4,Myatoi(str4));
	printf("字符串转化为整数：%d\r\n",Myatoi(str4));

	printf("\r\nKmpSearch test\r\n");
	strcpy(str1,"hello World test");
	strcpy(str2,"hello");
	printf("str1:%s\r\n",str1);
	printf("str2:%s\r\n",str2);
	//ret = KmpSearch(str1,str2);
	ret = ViolentMatch(str1,str2);
	printf("str2在str1中的位置：%d\r\n",ret);
	for(i = 0;i<strlen(str2);i++)
		printf("%c",*(str1+ret+i));
	printf("\r\n");
}