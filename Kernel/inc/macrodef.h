#ifndef __MACRODEF_H__
#define __MACRODEF_H__

#include <stdio.h>

#ifndef MIN
#define MIN(a, b)       ( ( (a)<(b) ) ? (a) : (b) )
#endif
#ifndef MAX
#define MAX(a, b)       ( ( (a)>(b) ) ? (a) : (b) )
#endif

#define IS_NULL(p)      (NULL == (p))

#ifndef ARR_SZ
#define ARR_SZ(arr)     ( sizeof(arr) / sizeof(arr[0]) )
#endif

#define SWPU16(n)       ( (((n)<<8)&0xFF00) | (((n)>>8)&0xFF) )
#define SWPU32(n)       ( (((n)<<16)&0xFFFF0000) | (((n)>>16)&0xFFFF) )

#define ARR2U8(arr)                                                 \
    (unsigned char)                                             \
    (((unsigned char)*(unsigned char *)(arr)) << 0)

#define ARR2U16(arr)                                                \
    (unsigned short)                                            \
    ( (((unsigned short)*(unsigned char *)(arr)) << 0) +        \
        (((unsigned short)*((unsigned char *)(arr) + 1)) << 8) )

#define ARR2U32(arr)                                                \
    (unsigned int)                                              \
    ( (((unsigned int)*((unsigned char *)(arr) + 0)) <<  0) +   \
        (((unsigned int)*((unsigned char *)(arr) + 1)) <<  8) +   \
        (((unsigned int)*((unsigned char *)(arr) + 2)) << 16) +   \
        (((unsigned int)*((unsigned char *)(arr) + 3)) << 24) )

#define ARR2ADDR(arr)       ((void *)ARR2U32((arr)))

#define MSB8(addr)		ARR2U8((addr))
#define MSB16(addr)		ARR2U16((addr))
#define MSB32(addr)		ARR2U32((addr))
#define MSB64(addr)		ARR2U64((addr))

#define LSB8(addr)		ARR2U8((addr))
#define LSB16(addr)		ARR2U16((addr))
#define LSB32(addr)		ARR2U32((addr))
#define LSB64(addr)		ARR2U64((addr))


#define STT_FIELD_SZ(stt)


#endif //__MACRODEF_H__
