#ifndef __TYPE_H__
#define __TYPE_H__

//重定义数据类型
#ifndef FALSE
#define FALSE			0
#endif
#ifndef TRUE
#define TRUE			1
#endif

/* 定义大端，若不是大端则屏蔽 */
//#define BIG_ENDIAN

//typedef unsigned char	bool;

typedef unsigned char	uchar;
typedef unsigned short	ushort;
typedef unsigned int	uint;
typedef unsigned long	ulong;

typedef unsigned char	uint8_t;
typedef unsigned short	uint16_t;
typedef unsigned int	uint32_t;
typedef unsigned long	uint64_t;

typedef char			int8_t;
typedef short			int16_t;
typedef int				int32_t;
typedef long			int64_t;

#endif