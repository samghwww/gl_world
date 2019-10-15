/*******************************************************************************
Copyright (C) 2019 Sam He(HeGuanglin)

Discription:
    Definition/declaratino of l system kernel basic data type.
History:
    Date        Author          Notes
 2019/10/07     Sam He          The first version
 
*******************************************************************************/

#ifndef TYPEDEF_H_
#define TYPEDEF_H_


#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned                            sz_t;

typedef char                                s8;
typedef short                               s16;
typedef int                                 s32;
typedef long                                s64;
typedef long long                           sll;
typedef sll                                 sx_t;

typedef unsigned char                       u8;
typedef unsigned short                      u16;
typedef unsigned int                        u32;
typedef unsigned long                       u64;
typedef unsigned long long                  ull;
typedef ull                                 ux_t;

typedef volatile char                       vs8;
typedef volatile short                      vs16;
typedef volatile int                        vs32;
typedef volatile long                       vs64;
typedef volatile long long                  vsll;
typedef vsll                                vsx_t;

typedef volatile unsigned char              vu8;
typedef volatile unsigned short             vu16;
typedef volatile unsigned int               vu32;
typedef volatile unsigned long              vu64;
typedef volatile unsigned long long         vull;
typedef vull                                vux_t;

#ifdef __cplusplus
}
#endif
#endif //TYPEDEF_H_
