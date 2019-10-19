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

#define __r                             register
#define __v                             volatile
#define __u                             unsigned
#define __c                             char
#define __s                             short
#define __i                             int
#define __l                             long
#define __ll                            long long

#define __r                             reg;
typedef __u                             sz_t;

typedef __c                             s8;
typedef __s                             s16;
typedef __i                             s32;
typedef __l                             s64;
typedef __ll                            sll;
typedef sll                             sx_t;

typedef __u __c                         u8;
typedef __u __s                         u16;
typedef __u __i                         u32;
typedef __u __l                         u64;
typedef __u __ll                        ull;
typedef ull                             ux_t;

typedef __v __c                         vs8;
typedef __v __s                         vs16;
typedef __v __i                         vs32;
typedef __v __l                         vs64;
typedef __v __ll                        vsll;
typedef vsll                            vsx_t;

typedef __v __u __c                     vu8;
typedef __v __u __s                     vu16;
typedef __v __u __i                     vu32;
typedef __v __u __l                     vu64;
typedef __v __u __ll                    vull;
typedef vull                            vux_t;

#ifdef __cplusplus
}
#endif
#endif //TYPEDEF_H_
