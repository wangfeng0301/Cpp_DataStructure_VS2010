#ifndef __MYSTRING_H__
#define __MYSTRING_H__

void *Mymemchr(const void *str, int c, size_t n);
int Mymemcmp(const void *str1, const void *str2, size_t n);
void *Mymemcpy(void *str1, const void *str2, size_t n);
void *Mymemmove(void *str1, const void *str2, size_t n);
void *Mymemset(void *str, int c, size_t n);
char *Mystrcat(char *dest, const char *src);
char *Mystrncat(char *dest, const char *src, size_t n);
char *Mystrchr(const char *str, int c);
char *Mystrrchr(const char *str, int c);
int Mystrcmp(const char *str1, const char *str2);
int Mystrncmp(const char *str1, const char *str2, size_t n);
char *Mystrcpy(char *dest, const char *src);
char *Mystrncpy(char *dest, const char *src, size_t n);
size_t Mystrcspn(const char *str1, const char *str2);
size_t Mystrspn(const char *str1, const char *str2);
size_t Mystrlen(const char *str);
char *Mystrpbrk(const char *str1, const char *str2);
char *Mystrstr(const char *haystack, const char *needle);
char *Mystrtok(char *str, const char *delim);

int Myatoi(char *str);//字符串转换为整数
int ViolentMatch(char* T, char* P);
int *findNext(char *P);
int KmpSearch(char *s,char *p);

void testString(void);

#endif
