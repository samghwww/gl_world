#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__


#ifdef __cplusplus
extern "C" {
#endif

/// @Brief Exception enumerator type define
typedef enum
{
    // Error code value define
    ERR_SUCCESS = 0,    // Execute result ok.
    ERR_NULL,           // Empty pointer
    ERR_NO_MEM,         // No enough memory
    ERR_BUSY,           // Busy for something else
    ERR_DOING,
    ERR_TIMEOUT,        // Handle timeout
    ERR_UNKNOW,
    ERR_NOT_SUPPORT,
    ERR_NOT_FOUND,
    ERR_INVALID_PARAM,
    ERR_INVALID_STATE,
    ERR_INVALID_DATA,
    ERR_INVALID_LENGTH,
    ERR_INVALID_FLAG,
    ERR_INVALID_ADDR,
    ERR_INVALID_CODE,
    ERR_DEBUG_CODE,
    ERR_CODE_MAX_NR,

    // Warning code value define
    // Sorry, If you're not right,
    // you must be wrong(only wrong, no warning).
    //WARN_UNKNOW = ERR_END,
} eExcpt_t;

#ifdef __cplusplus
}
#endif
#endif //__EXCEPTION_H__
