/*******************************************************************************
 Copyright (C) 2019 Sam He(HeGuanglin).

 History:
    Date        Author          Notes
 2019/10/07     Sam He          The first version

 Discription:
    Definition of the l system kernel debug infomation.
 
*******************************************************************************/

#ifndef DEBUG_H_
#define DEBUG_H_

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#define DEBUG_ENABLE_DEFAULT        1

#ifdef DEBUG
  #define DEBUG_ENABLED             DEBUG
#else
  #define DEBUG_ENABLED             DEBUG_ENABLE_DEFAULT
#endif


#define DBG_CUST_INIT(...)
#define DBG_CUST_PRINT(...)         printf(__VA_ARGS__)

#if (DEBUG_ENABLED)
    // Debug initializatiion function.
    #define dbg_init(...)           DBG_CUST_INIT(__VA_ARGS__)
    
    #define dbg_print(...)          DBG_CUST_PRINT(__VA_ARGS__)
    #define dbg_printl(...)             \
        do {                            \
            dbg_print(__VA_ARGS__);     \
            dbg_print("\n");            \
        } while (0)
    #define dbg_hex(h, l)               \
        do {                            \
            unsigned char const* pbyte = (unsigned char const *)h;  \
            unsigned long long hStrSz  = l;     \
            while (--hStrSz) {                  \
                dbg_print("%0X ", pbyte++);     \
            }                           \
            dbg_print("%0X", pbyte);    \
        } while (0)
    #define dbg_hexl(h, l)              \
        do {                            \
            dbg_hex((h), (l));          \
            dbg_print("\n");            \
        } while (0)

    #define dbg_msg(...)            dbg_print(__VA_ARGS__)
    #define dbg_msg(...)            dbg_print(__VA_ARGS__)
    #define dbg_info(...)           dbg_print(__VA_ARGS__)
    #define dbg_err(...)            dbg_print(__VA_ARGS__)
    #define dbg_warn(...)           dbg_print(__VA_ARGS__)
    #define dbg_ok(...)             dbg_print(__VA_ARGS__)
    #define dbg_ng(...)             dbg_print(__VA_ARGS__)

    #define dbg_msgl(...)           dbg_printl(__VA_ARGS__)
    #define dbg_msgl(...)           dbg_printl(__VA_ARGS__)
    #define dbg_infol(...)          dbg_printl(__VA_ARGS__)
    #define dbg_errl(...)           dbg_printl(__VA_ARGS__)
    #define dbg_warnl(...)          dbg_printl(__VA_ARGS__)
    #define dbg_okl(...)            dbg_printl(__VA_ARGS__)
    #define dbg_ngl(...)            dbg_printl(__VA_ARGS__)

    // Log initialization function
    #define log_init(...)           dbg_init(__VA_ARGS__)
    #define log_hex(h, l)           dbg_hex((h), (l))
    #define log_hexl(h, l)          dbg_hexl((h), (l))

    #define log_msg(...)            dbg_print(__VA_ARGS__)
    #define log_info(...)           dbg_print(__VA_ARGS__)
    #define log_err(...)            dbg_print(__VA_ARGS__)
    #define log_warn(...)           dbg_print(__VA_ARGS__)
    #define log_ok(...)             dbg_print(__VA_ARGS__)
    #define log_ng(...)             dbg_print(__VA_ARGS__)

    #define log_msgl(...)           dbg_printl(__VA_ARGS__)
    #define log_infol(...)          dbg_printl(__VA_ARGS__)
    #define log_errl(...)           dbg_printl(__VA_ARGS__)
    #define log_warnl(...)          dbg_printl(__VA_ARGS__)
    #define log_okl(...)            dbg_printl(__VA_ARGS__)
    #define log_ngl(...)            dbg_printl(__VA_ARGS__)
#else //#if DEBUG_ENABLED
    #define dbg_print(...)
    #define dbg_printl(...)
    #define dbg_msg(...)
    #define dbg_msgl(...)
    #define dbg_info(...)
    #define dbg_infol(...)
    #define dbg_ok(...)
    #define dbg_ng(...)
#endif //#else DEBUG_ENABLED
#ifdef __cplusplus
}
#endif
#endif //DEBUG_H_
