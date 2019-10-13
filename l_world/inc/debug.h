/*******************************************************************************
 Copyright (C) 2019 Sam He(HeGuanglin)

 History:
    Date        Author          Notes
 2019/10/07     Sam He          The first version

 Discription:
    Definition of the l system kernel debug infomation.
 
*******************************************************************************/

#ifndef __LDEBUG_H__
#define __LDEBUG_H__

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
#define LDEBUG              1
#define LDEBUG_ENABLED      LDEBUG


#define __DBG_PRINT(...)    printf(__VA_ARGS__)

#if (LDEBUG_ENABLED)
  #define dbg_print(...)     __DBG_PRINT(__VA_ARGS__)
#define dbg_msg(...)
#else //LDEBUG_ENABLED
  #define dbg_print(...)
#define dbg_printl(...)
#define dbg_msg(...)
#define dbg_msgl(...)
#define dbg_info(...)
#define dbg_infol(...)
#define dbg_ok(...)
#define dbg_ng(...)
#endif //#else LDEBUG_ENABLED
#ifdef __cplusplus
}
#endif
#endif //__LDEBUG_H__
