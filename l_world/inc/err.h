/*******************************************************************************
Copyright (C) 2019 Sam He(HeGuanglin)

Discription:
    Define warning/error code number.

History:
    Date        Author          Notes
 2019/10/06     Sam He          The first version

*******************************************************************************/

#ifndef ERR_H_
#define ERR_H_

#ifdef __cplusplus
extern "C" {
#endif


/// @Brief ERROR/Exception enumerator type define
typedef enum {
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

} err_t;


#ifdef __cplusplus
}
#endif
#endif //ERR_H_
