/*******************************************************************************
Copyright (C) 2019 Sam He(HeGuanglin)

Discription:
    Definition of the l system kernel debug infomation.
History:
    Date        Author          Notes
 2019/10/07     Sam He          The first version
 
*******************************************************************************/

#ifndef DEBUG_H_
#define DEBUG_H_

#include <stdio.h>
#include <conio.h>

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



#define DBG_BREAKPOINT(...)                         \
    do {                                            \
        DBG_CUST_PRINT("@@@__break_point__:\n");    \
        DBG_CUST_PRINT("FILE: %s\n", __FILE__);     \
        DBG_CUST_PRINT("FUNC: %s\n", __func__);     \
        DBG_CUST_PRINT("LINE: %d\n", __LINE__);     \
        _getch();                                   \
    } while (0)

#if (DEBUG_ENABLED)
    #define DBG_CODE(...)           __VA_ARGS__

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

    #define dbg_assert(con)             \
        do {                            \
            if (false == (con)) {       \
                DBG_BREAKPOINT();       \
            }                           \
        } while (0)

    // Assert the pointer "p" is not NULL
    #define dbg_assert_ptr(p)           dbg_assert(NULL != (p))
    // Assert the number "n" is not zero
    #define dbg_assert_nzr(n)           dbg_assert(0 != (n))

    #define dbg_msg(...)            dbg_print(__VA_ARGS__)
    #define dbg_msg(...)            dbg_print(__VA_ARGS__)
    #define dbg_info(...)           dbg_print(__VA_ARGS__)
    #define dbg_err(...)            dbg_print(__VA_ARGS__)
    #define dbg_warn(...)           dbg_print(__VA_ARGS__)
    #define dbg_ok(...)             dbg_print(__VA_ARGS__)
    #define dbg_ng(...)             dbg_print(__VA_ARGS__)

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
#else //DEBUG_ENABLED
    #define DBG_CODE(...)

    // Debug initializatiion function.
    #define dbg_init(...)

    #define dbg_print(...)
    #define dbg_printl(...)
    #define dbg_hex(...)
    #define dbg_hexl(...)
    #define dbg_msg(...)
    #define dbg_msg(...)
    #define dbg_info(...)
    #define dbg_err(...)
    #define dbg_warn(...)
    #define dbg_ok(...)
    #define dbg_ng(...)

    #define dbg_msgl(...)
    #define dbg_infol(...)
    #define dbg_errl(...)
    #define dbg_warnl(...)
    #define dbg_okl(...)
    #define dbg_ngl(...)

    // Log initialization function
    #define log_init(...)
    #define log_hex(h, l)
    #define log_hexl(h, l)

    #define log_msg(...)
    #define log_info(...)
    #define log_err(...)
    #define log_warn(...)
    #define log_ok(...)
    #define log_ng(...)

    #define log_msgl(...)
    #define log_infol(...)
    #define log_errl(...)
    #define log_warnl(...)
    #define log_okl(...)
    #define log_ngl(...)
#endif //#else DEBUG_ENABLED
#ifdef __cplusplus
}
#endif
#endif //DEBUG_H_
