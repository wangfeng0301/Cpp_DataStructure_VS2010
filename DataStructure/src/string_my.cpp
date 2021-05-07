/*********************************************************************
*�ַ�����ʵ��C��׼��<string.h>
*�ο����ϣ������ݽṹ���㷨�������������ԣ��Ժ����
*wangfeng
*2019.11.28-2021.1.27
**********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "string_my.h"

/************************************************************************
 *���ܣ��ڲ��� str ��ָ��Ĵ洢�ռ��ǰ n ���ֽ���������һ�γ����ַ� c��һ���޷����ַ�����λ�á�
 *���룺str:Ҫִ�е��ڴ��
 *		c:�� int ��ʽ���ݵ�ֵ�����Ǻ�����ÿ���ֽ�����ʱ��ʹ�ø�ֵ���޷����ַ���ʽ��
 *		n:Ҫ���������ֽ���
 *�������
 *���أ�����һ��ָ��ƥ���ֽڵ�ָ�룬����ڸ������ڴ�����δ�����ַ����򷵻� NULL��
************************************************************************/
void *Mymemchr(const void *str, int c, size_t n)
{
	char *temp;
	if(str == NULL)
	{
		printf("�ַ���Ϊ��\r\n");
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
 *���ܣ��Ѵ洢�� str1 �ʹ洢�� str2 ��ǰ n ���ֽڽ��бȽ�
 *���룺str1:Ҫ�Ƚϵ��ַ���
 *		str2:Ҫ�Ƚϵ��ַ���
 *		n:Ҫ�Ƚϵ��ֽ���
 *�������
 *���أ�str<str2,<0;str1=str2,=0;str1>str2,>0
************************************************************************/
int Mymemcmp(const void *str1, const void *str2, size_t n)
{
	char *temp1,*temp2;
	if(str1 == NULL || str2 == NULL)
	{
		printf("�ַ�������Ϊ�գ�\r\n");
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
 *���ܣ��Ӵ洢�� str2 ���� n ���ֽڵ��洢�� str1
 *���룺str1:Ŀ������
 *		str2:ԭ����
 *		n:�ֽ���
 *�������
 *���أ�ָ��Ŀ����str1��ָ��
************************************************************************/
void *Mymemcpy(void *str1, const void *str2, size_t n) 
{
	char *temp1,*temp2;
	if(str1 == NULL || str2 == NULL)
	{
		printf("�ַ�������Ϊ�գ�\r\n");
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
 *���ܣ��Ӵ洢�� str2 ���� n ���ֽڵ��洢�� str1
 *		��Mymemcpy��ͬ���ǣ��ú�����Ŀ�������Դ�����ص�ʱ��Ȼ��Ч��
 *		������ָ������ص������������ִ�к��ı�ԴĿ���ֵ
 *���룺str1:Ŀ������
 *		str2:ԭ����
 *		n:�ֽ���
 *�������
 *���أ�ָ��Ŀ����str1��ָ��
************************************************************************/
void *Mymemmove(void *str1, const void *str2, size_t n)
{
	char *dst = (char *)str1;
	char *src = (char *)str2;

	if(dst > src && src + n > dst)//Ŀ��������Դ����֮�����и��ǣ���ʱ��Ҫ�Ӻ���ǰ��ֵ
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
 *���ܣ������ַ� c��һ���޷����ַ��������� str ��ָ����ַ�����ǰ n ���ַ�
 *���룺str:Ҫ�����ڴ��
 *		c:�����õ�ֵ
 *		n:�ֽ���
 *�������
 *���أ�����һ��ָ��洢�� str ��ָ��
************************************************************************/
void *Mymemset(void *str, int c, size_t n)
{
	char *temp = str;
	while(n --)
		*temp++ = (char)c;
	return str;
}
/************************************************************************
 *���ܣ�src ��ָ����ַ���׷�ӵ� dest ��ָ����ַ����Ľ�β
 *���룺src:ָ��Ҫ׷�ӵ��ַ��������ַ������Ḳ��Ŀ���ַ�����
 *		dest:ָ��Ŀ�����飬�����������һ�� C �ַ��������㹻����׷�Ӻ���ַ�����
 *�������
 *���أ�����һ��ָ�����յ�Ŀ���ַ��� dest ��ָ�롣
************************************************************************/
char *Mystrcat(char *dest, const char *src)
{
	char *temp = (char *)src;
	char *temp2 = dest;
	int len = strlen(dest);//Ŀ�괮��С
	while(*temp != 0)
		temp2[len++] = *temp++;
	temp2[len] = 0;//�ӽ�����
	return dest;
}
/************************************************************************
 *���ܣ��� src ��ָ����ַ���׷�ӵ� dest ��ָ����ַ����Ľ�β��ֱ�� n �ַ�����Ϊֹ��
 *���룺src:Ҫ׷�ӵ��ַ�����
 *		dest:ָ��Ŀ�����飬�����������һ�� C �ַ��������㹻����׷�Ӻ���ַ�������������Ŀ��ַ���
 *		n:Ҫ׷�ӵ�����ַ�����
 *�������
 *���أ�����һ��ָ�����յ�Ŀ���ַ��� dest ��ָ�롣
************************************************************************/
char *Mystrncat(char *dest, const char *src, size_t n)
{
	char *temp = (char *)src;
	char *temp2 = dest;
	int len = strlen(dest);//Ŀ�괮��С
	while(n --)
		temp2[len++] = *temp++;
	temp2[len] = 0;//�ӽ�����
	return dest;
}
/************************************************************************
 *���ܣ��ڲ��� str ��ָ����ַ�����������һ�γ����ַ� c��һ���޷����ַ�����λ�á�
 *���룺src:Ҫ�������� C �ַ�����
 *		c:�� str ��Ҫ�������ַ���
 *�������
 *���أ��������ַ��� str �е�һ�γ����ַ� c ��λ�ã����δ�ҵ����ַ��򷵻� NULL��
************************************************************************/
char *Mystrchr(const char *str, int c)
{
	char *temp;
	if(str == NULL)
	{
		printf("�ַ���Ϊ��\r\n");
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
 *���ܣ��ڲ��� str ��ָ����ַ������������һ�γ����ַ� c��һ���޷����ַ�����λ�á�
 *���룺src:Ҫ�������� C �ַ�����
 *		c:�� str ��Ҫ�������ַ���
 *�������
 *���أ����� str �����һ�γ����ַ� c ��λ�á����δ�ҵ���ֵ����������һ����ָ�롣
************************************************************************/
char *Mystrrchr(const char *str, int c)
{
	char *temp,*ret;
	if(str == NULL)
	{
		printf("�ַ���Ϊ��\r\n");
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
 *���ܣ��� str1 ��ָ����ַ����� str2 ��ָ����ַ������бȽ�
 *���룺str1:Ҫ���бȽϵĵ�һ���ַ�����
 *		str2:Ҫ���бȽϵĵڶ����ַ�����
 *�������
 *���أ�����ֵС�� 0�����ʾ str1 С�� str2��
 *		����ֵ���� 0�����ʾ str1 ���� str2��
 *		����ֵ���� 0�����ʾ str1 ���� str2��
************************************************************************/
int Mystrcmp(const char *str1, const char *str2)
{
	char *temp1,*temp2;
	if(str1 == NULL || str2 == NULL)
	{
		printf("�ַ�������Ϊ�գ�\r\n");
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
 *���ܣ��� str1 �� str2 ���бȽϣ����Ƚ�ǰ n ���ֽ�
 *���룺str1:Ҫ���бȽϵĵ�һ���ַ�����
 *		str2:Ҫ���бȽϵĵڶ����ַ�����
 *		n:Ҫ�Ƚϵ�����ַ���
 *�������
 *���أ�����ֵС�� 0�����ʾ str1 С�� str2��
 *		����ֵ���� 0�����ʾ str1 ���� str2��
 *		����ֵ���� 0�����ʾ str1 ���� str2��
************************************************************************/
int Mystrncmp(const char *str1, const char *str2, size_t n)
{
	char *temp1,*temp2;
	if(str1 == NULL || str2 == NULL)
	{
		printf("�ַ�������Ϊ�գ�\r\n");
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
	if(n)//�����ַ�����������ǰ����
	{
		if(*temp1 == 0 && *temp2 != 0)//str1��str2��
			return -1;
		else if(*temp1 != 0 && *temp2 == 0)//str1��str2��
			return 1;
		else
			return 0;
	}
	return 0;
}
/************************************************************************
 *���ܣ��� str1 �� str2 ���бȽϣ����ȡ���� LC_COLLATE ��λ������
 *���룺str1:Ҫ���бȽϵĵ�һ���ַ�����
 *		str2:Ҫ���бȽϵĵڶ����ַ�����
 *�������
 *���أ�����ֵС�� 0�����ʾ str1 С�� str2��
 *		����ֵ���� 0�����ʾ str1 ���� str2��
 *		����ֵ���� 0�����ʾ str1 ���� str2��
************************************************************************/
int Mystrcoll(const char *str1, const char *str2)
{

}
/************************************************************************
 *���ܣ��� src ��ָ����ַ������Ƶ� dest
 *���룺dest:ָ�����ڴ洢�������ݵ�Ŀ�����顣
 *		src:Ҫ���Ƶ��ַ�����
 *�������
 *���أ�����һ��ָ�����յ�Ŀ���ַ��� dest ��ָ�롣
************************************************************************/
char *Mystrcpy(char *dest, const char *src)
{
	char *temp = dest;
	while((*dest++ = *src++)!='\0');

	return temp;
}
/************************************************************************
 *���ܣ��� src ��ָ����ַ������Ƶ� dest����ิ�� n ���ַ����� src �ĳ���С�� n ʱ��dest ��ʣ�ಿ�ֽ��ÿ��ֽ���䡣
 *���룺dest:ָ�����ڴ洢�������ݵ�Ŀ�����顣
 *		src:Ҫ���Ƶ��ַ�����
 *		n:Ҫ��Դ�и��Ƶ��ַ�����
 *�������
 *���أ��������ո��Ƶ��ַ���
************************************************************************/
char *Mystrncpy(char *dest, const char *src, size_t n)
{
	char *temp = dest;
	while((*dest++ = *src++)!='\0' && n)
		n--;
	while(n)//src����<n
	{
		*dest++ = 0;
		n--;
	}

	return temp;
}
/************************************************************************
 *���ܣ������ַ��� str1 ��ͷ�����м����ַ��������ַ��� str2 �е��ַ�
 *���룺str1:Ҫ�������� C �ַ�����
 *		str2:���ַ���������Ҫ�� str1 �н���ƥ����ַ��б�
 *�������
 *���أ����� str1 ��ͷ�����������ַ��� str2 ���ַ����ַ�����
************************************************************************/
size_t Mystrcspn(const char *str1, const char *str2)
{
	// map��32���ֽڵĴ�С��Ҳ����256��bit���ɰ�map����һ��2ά����[32][8]
    unsigned char map[32] = {0};
	int count = 0;

    // ÿ��ASCII��(��Ϊc)��7bit����128����
    // map������Ϊλͼ��¼ÿ��ASCII���Ƿ���ֹ���mapһ���ֽڿ��Լ�¼8��ASCII��
	// �硰0����ASCII����48����ômap[48/8]���ǡ�0����λͼ�еĵڼ����ֽ�
	// ��48 & 7�����ɶ����ƾ���0011 0000 & 0000 0111,һ���ֽ�8bit������&7�����Զ�λ������ֽڵĵڼ���bit
    while(*str2)
    {
        map[*str2 >> 3] |= (1 << (*str2 & 7));
        str2++;
    }

    map[0] |= 1;//0��ascii�б�ʾ�գ�����ǰ��*str�˳�ʱһ���ǿգ�������λ
    while(!(map[*str1 >> 3] & (1 << (*str1 & 7))))
    {
        count++;
        str1++;
    }

    return count;
}
/************************************************************************
 *���ܣ������ַ��� str1 �е�һ�������ַ��� str2 �г��ֵ��ַ��±�
 *���룺str1:Ҫ�������� C �ַ�����
 *		str2:���ַ���������Ҫ�� str1 �н���ƥ����ַ��б�
 *�������
 *���أ����� str1 �е�һ�������ַ��� str2 �г��ֵ��ַ��±ꡣ
************************************************************************/
size_t Mystrspn(const char *str1, const char *str2)
{
	// map��32���ֽڵĴ�С��Ҳ����256��bit���ɰ�map����һ��2ά����[32][8]
    unsigned char map[32] = {0};
	int count = 0;

    // ÿ��ASCII��(��Ϊc)��7bit����128����
    // map������Ϊλͼ��¼ÿ��ASCII���Ƿ���ֹ���mapһ���ֽڿ��Լ�¼8��ASCII��
	// �硰0����ASCII����48����ômap[48/8]���ǡ�0����λͼ�еĵڼ����ֽ�
	// ��48 & 7�����ɶ����ƾ���0011 0000 & 0000 0111,һ���ֽ�8bit������&7�����Զ�λ������ֽڵĵڼ���bit
    while(*str2)
    {
        map[*str2 >> 3] |= (1 << (*str2 & 7));
        str2++;
    }

    //map[0] |= 1;//0��ascii�б�ʾ�գ�����ǰ��*str�˳�ʱһ���ǿգ�������λ
    while((map[*str1 >> 3] & (1 << (*str1 & 7))))
    {
        count++;
        str1++;
    }

    return count;
}
/************************************************************************
 *���ܣ������ַ��� str1 �е�һ��ƥ���ַ��� str2 ���ַ����ַ����������ս����ַ���
 *		Ҳ����˵�����μ����ַ��� str1 �е��ַ������������ַ����ַ��� str2 ��Ҳ����ʱ����ֹͣ���飬�����ظ��ַ�λ�á�
 *���룺str1:Ҫ�������� C �ַ�����
 *		str2:���ַ���������Ҫ�� str1 �н���ƥ����ַ��б�
 *�������
 *���أ����� str1 �е�һ��ƥ���ַ��� str2 ���ַ����ַ������δ�ҵ��ַ��򷵻� NULL��
************************************************************************/
char *Mystrpbrk(const char *str1, const char *str2)
{
	// map��32���ֽڵĴ�С��Ҳ����256��bit���ɰ�map����һ��2ά����[32][8]
    /*unsigned char map[32] = {0};
	char *ret;

    // ÿ��ASCII��(��Ϊc)��7bit����128����
    // map������Ϊλͼ��¼ÿ��ASCII���Ƿ���ֹ���mapһ���ֽڿ��Լ�¼8��ASCII��
	// �硰0����ASCII����48����ômap[48/8]���ǡ�0����λͼ�еĵڼ����ֽ�
	// ��48 & 7�����ɶ����ƾ���0011 0000 & 0000 0111,һ���ֽ�8bit������&7�����Զ�λ������ֽڵĵڼ���bit
    while(*str2)
    {
        map[*str2 >> 3] |= (1 << (*str2 & 7));
        str2++;
    }

    map[0] |= 1;//0��ascii�б�ʾ�գ�����ǰ��*str�˳�ʱһ���ǿգ�������λ
	ret = NULL;
    while(!(map[*str1 >> 3] & (1 << (*str1 & 7))))
    {
        str1++;
    }
	return (char *)str1;*/

	return (char *)str1 + Mystrcspn(str1,str2);
}
/************************************************************************
 *���ܣ������ַ��� str �ĳ��ȣ�ֱ���ս����ַ������������ս����ַ���
 *���룺str:Ҫ���㳤�ȵ��ַ�����
 *�������
 *���أ������ַ����ĳ��ȡ�
************************************************************************/
size_t Mystrlen(const char *str)
{
	int lenth=0;
	while(*str++ != '\0')
		lenth++;
	return lenth;
}
/************************************************************************
 *���ܣ����ַ��� haystack �в��ҵ�һ�γ����ַ��� needle ��λ�ã���������ֹ�� '\0'��
 *���룺haystack:Ҫ�������� C �ַ�����
 *		needle:�� haystack �ַ�����Ҫ������С�ַ�����
 *�������
 *���أ������� haystack �е�һ�γ��� needle �ַ�����λ�ã����δ�ҵ��򷵻� null��
************************************************************************/
char *Mystrstr(const char *haystack, const char *needle)
{
	int len,len2;
	if(!(len=strlen(needle)))//needle����Ϊ0����ʾneedle�ַ���Ϊ��
		return(char*)haystack;
	len2 = strlen(haystack);//ȡ�ַ���haystack����
	for(;*haystack;++haystack)
	{
		if(len2 >= len)//��haystackʣ�೤��С��needle���ȣ���needle��Ȼ����haystack�Ӵ�
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
 *���ܣ��ֽ��ַ��� str Ϊһ���ַ�����delim Ϊ�ָ�����
 *���룺str:Ҫ���ֽ��һ��С�ַ������ַ�����
 *		delim:�����ָ����� C �ַ�����
 *�������
 *���أ����ر��ֽ�ĵ�һ�����ַ��������û�пɼ������ַ������򷵻�һ����ָ�롣
 *��⣺
************************************************************************/
char *Mystrtok(char *str, const char *delim)
{
	// map��32���ֽڵĴ�С��Ҳ����256��bit���ɰ�map����һ��2ά����[32][8]
	unsigned char map[32] = {0};
	static char *laststr;
	char *string_org;

	if(str == NULL)
		str = laststr;
	// ÿ��ASCII��(��Ϊc)��7bit����128����
	// map������Ϊλͼ��¼ÿ��ASCII���Ƿ���ֹ���mapһ���ֽڿ��Լ�¼8��ASCII��
	// �硰0����ASCII����48����ômap[48/8]���ǡ�0����λͼ�еĵڼ����ֽ�
	// ��48 & 7�����ɶ����ƾ���0011 0000 & 0000 0111,һ���ֽ�8bit������&7�����Զ�λ������ֽڵĵڼ���bit
	while(*delim)
	{
		map[*delim >> 3] |= (1 << (*delim & 7));
		delim ++;
	}
	//map[0] |= 1;//0��ascii�б�ʾ�գ�����ǰ��*str�˳�ʱһ���ǿգ�������λ

	while((map[*str >> 3] & (1 << (*str & 7))) && *str)//�ҵ���һ����ָ�������ȵ�λ��
		str ++;
	string_org = str;
	for(;*str;str++)//ѭ��ֱ���ҵ��ָ������ַ�������,ע�����ﲻ����while(*str++)�ж�
	{
		if((map[*str >> 3] & (1 << (*str & 7))))
		{
			*str++ = 0;//�ҵ��ָ�����λ������
			break;
		}
	}
	laststr = str;//��¼����ָ�룬�´�ʹ��
	if(string_org == str)//����������ַ����в������ָ���
		return NULL;
	else
		return string_org;
}
//atoi������ʵ���ַ���ת��Ϊ����
int Myatoi(char *str)
{
	int temp = 0;
	int i=0;
	int length = Mystrlen(str);//�ַ�������
	if(str[0] == '-' || str[0] == '+')//�ж����ַ��ǲ���������		
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
			printf("�ַ�%d���Ϸ���\r\n",i);
			return 0;
		}

	}
	if(str[0]=='-')
		temp = -temp;
	return temp;
}

/************************************************************************
 *���ܣ�����ƥ���ַ���
 *���룺T:������
 *		P:�Ӵ�
 *�������
 *���أ��Ӵ��������е���ʼλ�á��������ڣ�����-1
************************************************************************/
int ViolentMatch(char* T, char* P)
{
	int tLen = strlen(T);
	int pLen = strlen(P);
	int i = 0;//��������
	int j = 0;//�Ӵ�����

	while(i < tLen && j < pLen)
	{
		if(T[i] == P[j])
		{
			/*1.�����ǰ�ַ�ƥ��ɹ�����T[i] == P[j]������i++��j++ */
			/*�����Ƚ���һ���ַ���ֱ���Ӵ�����*/
			i++;
			j++;
		}
		else
		{
			/*2.���ʧ�䣨��T[i]! = P[j]������j = 0,���Ӵ����ݵ��ʼ */
			/*��i = i - (j - 1)�������������ƶ�1λ */
			i = i - j + 1;
			j = 0;
		}
	}
	/*ƥ��ɹ��������Ӵ�P������T�е�λ�ã����򷵻�-1 */
	if(j == pLen)
		return i - j;
	else
		return -1;
}
/************************************************************************
 *���ܣ�ʹ��KMP�㷨ʱ�������ַ�����������
 *���룺P:Ҫ��������ַ�����
 *�������
 *���أ�nextָ��
 *��⣺
************************************************************************/
static int *findNext(char *P)
{
	int i=0;
	int k=-1;
	int m=strlen(P);//�ַ���P����
	int *next = (int *)malloc(m*sizeof(int));//����m��int��С�ռ�
	if(m==0)//�ַ�����Ϊ0���˳�
		return 0;
	if(next == NULL)//���ٿռ�ʧ��
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
 *���ܣ�KMP�㷨���Ӵ��������е�λ��
 *���룺s:����
 *		p:�Ӵ�
 *�������
 *���أ��Ӵ��������е���ʼλ�á��������ڣ�����-1
 *��⣺
************************************************************************/
int KmpSearch(char *s,char *p)
{
	int i = 0;
	int j = 0;
	int sLen = strlen(s);
	int pLen = strlen(p);
	int *next = findNext(p);
	if(sLen < pLen)//��������С���Ӵ���ƥ���޷��ɹ�
		return -1;
	while (i < sLen && j < pLen)
	{
		//�����j = -1�����ߵ�ǰ�ַ�ƥ��ɹ�����S[i] == P[j]��������i++��j++    
		if (j == -1 || s[i] == p[j])
		{
			i++;
			j++;
		}
		else
		{
			//�����j != -1���ҵ�ǰ�ַ�ƥ��ʧ�ܣ���S[i] != P[j]�������� i ���䣬j = next[j]    
			//next[j]��Ϊj����Ӧ��nextֵ
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
	printf("[%c] ֮����ַ����� - [%s]\n", ch, retchar);

	printf("\r\nMymemcmp test\r\n");
	ret = Mymemcmp(str1, str2, 5);
	if(ret > 0)
		printf("str2 С�� str1\r\n");
	else if(ret < 0) 
		printf("str1 С�� str2\r\n");
	else 
		printf("str1 ���� str2\r\n");

	printf("\r\nMymemcpy test\r\n");
	printf("ʹ�� memcpy ǰ: %s\n", str1);
	Mymemcpy(str1, str2, strlen(str2));
	printf("ʹ�� memcpy ��: %s\n", str1);

	printf("\r\nMymemmove test\r\n");
	dst = &src[5];
	printf("Դ�ַ���:%s\r\n",src);
	printf("Ŀ���ַ���:%s\r\n",dst);
	Mymemcpy(dst, src, 6);
	printf("ʹ�� Mymemcpy ��,Դ�ַ���: %s\n", src);
	printf("ʹ�� Mymemcpy ��,Ŀ���ַ���: %s\n", dst);
	dst2 = &src2[5];
	printf("Դ�ַ���:%s\r\n",src2);
	printf("Ŀ���ַ���:%s\r\n",dst2);
	Mymemmove(dst, src2, 6);
	printf("ʹ�� Mymemmove ��,Դ�ַ���: %s\n", src2);
	printf("ʹ�� Mymemmove ��,Ŀ���ַ���: %s\n", dst2);
	printf("ʹ�� Mymemcpy ����\n");
	printf("ʹ�� Mymemmove ��ȷ��\n");

	printf("\r\nMymemset test\r\n");
	Mymemset(src2,'A',sizeof(src2)-1);
	printf("src2:%s\r\n",src2);

	printf("\r\nMystrcat test\r\n");
	printf("str5:%s\r\n",str5);
	printf("str1:%s\r\n",str1);
	retchar = Mystrcat(str5,str1);
	printf("����str5��str1��%s\r\n",retchar);

	printf("\r\nMystrncat test\r\n");
	printf("str5:%s\r\n",str5);
	printf("str1:%s\r\n",str1);
	retchar = Mystrncat(str5,str1,5);
	printf("����str5��str1��%s\r\n",retchar);

	printf("\r\nMystrchr/Mystrrchr test\r\n");
	printf("str5:%s\r\n",str5);
	ch = 'T';
	retchar = (char*)Mystrchr(str5, ch);
	printf("Mystrchr:[%s]��[%c] ֮����ַ����� - [%s]\n", str5, ch, retchar);
	retchar = (char*)Mystrrchr(str5, ch);
	printf("Mystrrchr:[%s]��[%c] ֮����ַ����� - [%s]\n", str5, ch, retchar);

	printf("\r\nMystrcmp test\r\n");
	printf("str1:%s\r\n",str1);
	printf("str2:%s\r\n",str2);
	ret = Mystrcmp(str1, str2);
	if(ret > 0)
		printf("str2 С�� str1\r\n");
	else if(ret < 0) 
		printf("str1 С�� str2\r\n");
	else 
		printf("str1 ���� str2\r\n");

	printf("\r\nMystrncmp test\r\n");
	printf("str1:%s\r\n",str1);
	printf("str2:%s\r\n",str2);
	ret = Mystrncmp(str1, str2,5);
	if(ret > 0)
		printf("str2 С�� str1\r\n");
	else if(ret < 0) 
		printf("str1 С�� str2\r\n");
	else 
		printf("str1 ���� str2\r\n");

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
	printf("��һ��ƥ����ַ����� %d\n", strcspn(str1,str2) + 1);
	printf("��һ��ƥ����ַ����� %d\n", Mystrcspn(str1,str2) + 1);

	printf("\r\nMystrspn test\r\n");
	printf("str1:%s\r\n",str1);
	printf("str2:%s\r\n",str2);
	printf("��һ����ƥ����ַ����� %d\n", strspn(str1,str2) + 1);
	printf("��һ����ƥ����ַ����� %d\n", Mystrspn(str1,str2) + 1);

	printf("\r\nMystrpbrk test\r\n");
	strcpy(str2,"123");
	printf("str1:%s\r\n",str1);
	printf("str2:%s\r\n",str2);
	retchar = strpbrk(str1,str2);
	if(retchar)
		printf("��һ��ƥ����ַ��� %c\n", *retchar);
	else
		printf("δ�ҵ�ƥ���ַ�\n");
	retchar = Mystrpbrk(str1,str2);
	if(retchar)
		printf("��һ��ƥ����ַ��� %c\n", *retchar);
	else
		printf("δ�ҵ�ƥ���ַ�\n");
	
	

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
	printf("str1���״γ���str2���ַ���:%s\r\n",retchar);
	retchar = Mystrstr(str1,str2);
	printf("str1���״γ���str2���ַ���:%s\r\n",retchar);

	printf("\r\nMystrtok test\r\n");
	strcpy(str1,"hello World test");
	strcpy(str2," ");
	printf("str1:%s\r\n",str1);
	printf("str2:%s\r\n",str2);
	retchar = Mystrtok(str1,str2);
	printf("str1��str2�ָ��:%s\r\n",retchar);
	//printf("str1:%s\r\n",str1);
	//printf("str2:%s\r\n",str2);
	for(i = 0;i<sizeof(str1);i++)
		printf("%d ",str1[i]);
	//strcpy(str1,"hello Worldtest");
	//printf("\r\n��;�ı�str1��ֵstr1:%s\r\n",str1);
	retchar = Mystrtok(NULL,str2);
	printf("\r\nretchar:%s\r\n",retchar);
	for(i = 0;i<sizeof(str1);i++)
		printf("%d ",str1[i]);
	retchar = Mystrtok(NULL,str2);
	printf("\r\nretchar:%s\r\n",retchar);
	for(i = 0;i<sizeof(str1);i++)
		printf("%d ",str1[i]);

	printf("�ַ���%sת��Ϊ������%d\r\n",str4,Myatoi(str4));
	printf("�ַ���ת��Ϊ������%d\r\n",Myatoi(str4));

	printf("\r\nKmpSearch test\r\n");
	strcpy(str1,"hello World test");
	strcpy(str2,"hello");
	printf("str1:%s\r\n",str1);
	printf("str2:%s\r\n",str2);
	//ret = KmpSearch(str1,str2);
	ret = ViolentMatch(str1,str2);
	printf("str2��str1�е�λ�ã�%d\r\n",ret);
	for(i = 0;i<strlen(str2);i++)
		printf("%c",*(str1+ret+i));
	printf("\r\n");
}