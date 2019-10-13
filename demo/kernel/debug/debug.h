#ifndef __DEBUG_H__
#define __DEBUG_H__

/// @INCLUDE your custom header file here


//#include "nrf_log.h"
//#include "nrf_log_ctrl.h"

#include "../../usr/usr_cfg.h"

#if (PLATFORM == PLATFORM_NO_OS)
    #include "../../usr/RTT/SEGGER_RTT.h"
#endif

#include <stdio.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif



#ifndef DP_DEBUG
#define DP_DEBUG                    (0)
#endif

#if (defined(DP_DEBUG) && DP_DEBUG)
#define GL_DEBUG                    DP_DEBUG
#endif

#if (PLATFORM == PLATFORM_NO_OS)
#define __DBG_CUSTOM_PRINTF(...)    SEGGER_RTT_printf(0, ##__VA_ARGS__)
#else
#define __DBG_CUSTOM_PRINTF(...)    printf(__VA_ARGS__)
#endif

#if defined(GL_DEBUG) && (GL_DEBUG)
#define DBG_INIT()                                  \
        SEGGER_RTT_ConfigUpBuffer(0, NULL, NULL, 0, SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL)

//#define DBG_INIT()                                  \
//        SEGGER_RTT_ConfigUpBuffer(0, "RTTUP", NULL, 0, SEGGER_RTT_MODE_NO_BLOCK_SKIP)
#else
#define DBG_INIT(...)
#endif

#if (defined(GL_DEBUG) && (GL_DEBUG))
#define DEVELOPMENT_DEBUG               (1)
#endif

/// @CONFIGE debug print function,
/// @If your target system is not windows/Linux/BSD/Unix etc,
/// @this option must be configured,Unless you don't need
/// @debug you project code with undefined "DEVELOPMENT_DEBUG"
/// @or define "DEVELOPMENT_DEBUG" with zero(0)
#ifndef __DBG_CUSTOM_PRINTF
#define __DBG_PRINTF(...)        LOG_INTERNAL(NRF_LOG_LEVEL_DEBUG, "", __VA_ARGS__)  //printf(__VA_ARGS__)
#else
#define __DBG_PRINTF(...)        __DBG_CUSTOM_PRINTF(__VA_ARGS__)
#endif

#define SUCCEEDED                       (0U)


#if (PLATFORM == PLATFORM_NO_OS)
#if defined(__GNUC__)
#define DBG_BREAKUP() __builtin_trap()
#else
#define DBG_BREAKUP(...) __breakpoint(0) //__BKPT(0)
#endif
#else
#define DBG_BREAKUP(...)
#endif //#if (PLATFORM == PLATFORM_NO_OS)

#if ( (defined(DEVELOPMENT_DEBUG)) && (DEVELOPMENT_DEBUG) )

#define DEBUG_CODE(code)            code
#define DBG_CODE(code)              code

#if !defined(CODE_LAYER)
#define DBG_LAYER                  ""
#endif

#if !defined(CODE_MODULE)
#define DBG_MODULE                 ""
#endif

#ifdef DBG_PRINT
#undef DBG_PRINT
#endif
#define DBG_PRINT(...)                                    \
    __DBG_PRINTF(__VA_ARGS__)

#define DBG_PRINTL(...)                                   \
    DBG_PRINT(__VA_ARGS__);                           \
    DBG_PRINT("\r\n")
/// NRF_LOG_INTERNAL_FLUSH();
/// @if you add the following statement it will crash when
/// DBG_PRINT(...) excute in interrupt handler,
/// becuase it will take more time to proccess print course
/// NRF_LOG_INTERNAL_FLUSH(); /// It will always loop untill
/// print work finished
#ifdef DBG_PROCESS
#undef DBG_PROCESS
#endif
#define DBG_PROCESS()               \
    while (NRF_LOG_PROCESS())   \
    {                           \
        NRF_LOG_FLUSH();        \
    }

#ifdef DBG_PRINT_PREFIX
#undef DBG_PRINT_PREFIX
#endif
#define DBG_PRINT_PREFIX(...)                               \
    do {                                                \
        DBG_PRINT(DBG_LAYER);                           \
        DBG_PRINT(DBG_MODULE);                          \
    } while (0)

#ifdef DBG_PRINT_HEX
#undef DBG_PRINT_HEX
#endif
#define DBG_PRINT_HEX(hex_string, len)                      \
    do {                                                \
        uint32_t dataIdx = 0;                           \
        for ( ; dataIdx < (uint32_t)(len); dataIdx++)   \
        {                                               \
            DBG_PRINT("%02X ", ((unsigned char*)(hex_string))[dataIdx]);  \
        }                                               \
    } while (0)

#ifdef DBG_DATA_HEX
#undef DBG_DATA_HEX
#endif
#define DBG_DATA_HEX(hex_string, len)                      \
    do {                                                \
        uint32_t dataIdx = 0;                           \
        for ( ; dataIdx < (uint32_t)(len); dataIdx++)   \
        {                                               \
            DBG_MSG_DATA("%02X ", ((unsigned char*)(hex_string))[dataIdx]);  \
        }                                               \
        DBG_MSG_DATA("\r\n");                              \
    } while (0)
    
#ifdef DBG_PRINTL_HEX
#undef DBG_PRINTL_HEX
#endif
#define DBG_PRINTL_HEX(hex_string, len)                      \
    do {                                                \
        uint32_t dataIdx = 0;                           \
        for ( ; dataIdx < (uint32_t)(len); dataIdx++)   \
        {                                               \
            DBG_PRINT("%02X ", ((unsigned char*)(hex_string))[dataIdx]);  \
        }                                               \
        DBG_PRINT("\r\n");                              \
    } while (0)

#ifdef DBG_DATAL_HEX
#undef DBG_DATAL_HEX
#endif
#define DBG_DATAL_HEX(hex_string, len)                      \
    do {                                                \
        uint32_t dataIdx = 0;                           \
        for ( ; dataIdx < (uint32_t)(len); dataIdx++)   \
        {                                               \
            DBG_MSG_DATA("%02X ", ((unsigned char*)(hex_string))[dataIdx]);  \
        }                                               \
        DBG_MSG_DATA("\r\n");                              \
    } while (0)
    
#ifdef DBG_MSG
#undef DBG_MSG
#endif
#define DBG_MSG(...)                DBG_PRINT(__VA_ARGS__)

#ifdef DBG_MSG_DATA
#undef DBG_MSG_DATA
#endif
#define DBG_MSG_DATA(...)                DBG_PRINT(__VA_ARGS__)

#ifdef DBG_MSG_OK
#undef DBG_MSG_OK
#endif
#define DBG_MSG_OK(...)             DBG_MSG(__VA_ARGS__)

#ifdef DBG_MSG_NG
#undef DBG_MSG_NG
#endif
#define DBG_MSG_NG(...)             DBG_MSG(__VA_ARGS__)

#ifdef DBG_INFO
#undef DBG_INFO
#endif
#define DBG_INFO(...)                       \
    do {                                \
        DBG_PRINT("func: %s line: %d\r\n", __func__, __LINE__);         \
        DBG_PRINT(__VA_ARGS__); \
    } while (0)

#ifdef DBG_ENTER_FUNC
#undef DBG_ENTER_FUNC
#endif
#define DBG_ENTER_FUNC()                    \
    do {                                \
        DBG_PRINT("\r\n\r\n");          \
        DBG_PRINT("ENTER==>>\r\n");     \
        DBG_PRINT("%s: %d : %s\r\n", __FILE__, (uint32_t)__LINE__, __func__);

#ifdef DBG_EXIT_FUNC
#undef DBG_EXIT_FUNC
#endif
#define DBG_EXIT_FUNC()                     \
    DBG_PRINT("\r\n\r\n");          \
    } while (0)

#ifdef DBG_ASSERT
#undef DBG_ASSERT
#endif
#define DBG_ASSERT(p)               \
    do {                        \
        if (!(p))               \
        {                       \
            DBG_PRINT("ASSERT: %s: %d : %s\r\n",    \
                __FILE__, __LINE__, __func__);      \
            DBG_BREAKUP();      \
        }                       \
    } while (0)

#ifdef DBG_WARN
#undef DBG_WARN
#endif
#define DBG_WARN(...)               \
    do {                        \
        DBG_PRINT_PREFIX(...)       \
        DBG_PRINT("WARN: %s: %d : %s\r\n      ", __FILE__, (uint32_t)__LINE__, __func__); \
        DBG_PRINT(__VA_ARGS__)
#ifdef DBG_ERROR
#undef DBG_ERROR
#endif
#define DBG_ERROR(errCode)          \
    do {                            \
        DBG_BREAKUP();              \
        DBG_PRINT("ERROR: %s: %d ", __func__, __LINE__); \
        DBG_PRINT("%X", errCode);   \
        DBG_PRINT("\r\n");          \
    } while (0)

#ifdef GL_ASSERT
#undef GL_ASSERT
#endif
#define GL_ASSERT(assertCode)       \
    do {                        \
        if (SUCCEEDED != (assertCode))       \
        {                       \
            DBG_ASSERT("ASSERT: %s: %d  CODE: 0x%02X/%d  FUNC: %s\r\n", __FILE__, __LINE__, assertCode, assertCode); \
            DBG_BREAKUP();      \
        }                       \
        else                    \
        {                       \
            \
        }                       \
    } while (0U)

#ifdef ASSERT_WARN
#undef ASSERT_WARN
#endif
#define ASSERT_WARN(warnCode)       \
    do {                        \
        if (SUCCEEDED != (warnCode))         \
        {                       \
            DBG_ASSERT("WARN: %s: %d  CODE: 0x%02X/%d  FUNC: %s\r\n", __FILE__, __LINE__, warnCode, warnCode);;  \
            DBG_BREAKUP();      \
        }                       \
        else                    \
        {                       \
            \
        }                       \
    } while (0U)

#ifdef ASSERT_ERROR
#undef ASSERT_ERROR
#endif
#define ASSERT_ERROR(errorCode)     \
    do {                        \
        if (SUCCEEDED != (errorCode))        \
        {                       \
            DBG_ASSERT("ERROR: %s: %d : %s: 0x%02X\r\n", __FILE__, (uint32_t)__LINE__, __func__, errorCode); \
            DBG_BREAKUP();      \
        }                       \
        else                    \
        {                       \
            \
        }                       \
    } while (0U)

#else //#if ((defined(DEVELOPMENT_DEBUG)) && (DEVELOPMENT_DEBUG))

#define DEBUG_CODE(...)
#define DBG_CODE(...)

#ifdef DBG_PRINT
#undef DBG_PRINT
#endif
#define DBG_PRINT(...)

#ifdef DBG_PROCESS
#undef DBG_PROCESS
#endif
#define DBG_PROCESS(...)

#ifdef DBG_PRINT_HEX
#undef DBG_PRINT_HEX
#endif
#define DBG_PRINT_HEX(...)

#ifdef DBG_PRINTL_HEX
#undef DBG_PRINTL_HEX
#endif
#define DBG_PRINTL_HEX(...)

#ifdef DBG_DATA_HEX
#undef DBG_DATA_HEX
#endif
#define DBG_DATA_HEX(...)

#ifdef DBG_DATAL_HEX
#undef DBG_DATAL_HEX
#endif
#define DBG_DATAL_HEX(...)

#ifdef DBG_MSG
#undef DBG_MSG
#endif
#define DBG_MSG(...)

#ifdef DBG_MSG_DATA
#undef DBG_MSG_DATA
#endif
#define DBG_MSG_DATA(...)

#ifdef DBG_MSG_OK
#undef DBG_MSG_OK
#endif
#define DBG_MSG_OK(...)

#ifdef DBG_MSG_NG
#undef DBG_MSG_NG
#endif
#define DBG_MSG_NG(...)

#ifdef DBG_INFO
#undef DBG_INFO
#endif
#define DBG_INFO(...)

#ifdef DBG_ASSERT
#undef DBG_ASSERT
#endif
#define DBG_ASSERT(...)

#ifdef DBG_WARN
#undef DBG_WARN
#endif
#define DBG_WARN(...)

#ifdef DBG_ERROR
#undef DBG_ERROR
#endif
#define DBG_ERROR(...)

    //    #ifdef ASSERT
    //    #undef ASSERT
    //    #endif
    //    #define ASSERT(x)               (void)x

#ifdef ASSERT_WARN
#undef ASSERT_WARN
#endif
#define ASSERT_WARN(...)

#ifdef ASSERT_ERROR
#undef ASSERT_ERROR
#endif
#define ASSERT_ERROR(...)

#endif //#else ((defined(DEVELOPMENT_DEBUG)) && (DEVELOPMENT_DEBUG))

#ifdef __cplusplus
}
#endif
#endif //__DEBUG_H__
