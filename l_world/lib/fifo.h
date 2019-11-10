/*******************************************************************************
Copyright (C) 2019 Sam He(HeGuanglin)

Discription:
    Definition/declaratino of fifo.
History:
    Date        Author          Notes
 2019/10/23     Sam He          The first version
 
*******************************************************************************/

#ifndef FIFO_H_
#define FIFO_H_

#include "../inc/err.h"
#include "../inc/typedef.h"

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    FIFO_MODE_NORMAL,
    FIFO_MODE_CIRCLE_OVERRIDE,
    FIFO_MODE_CIRCLE_NORMAL,
} FifoMode_t;

typedef struct {
    union {
        void *pvbuf;
        u8   *pbuf;
    };
    union {
        ux_t capacity;
        ux_t length;
    };
    ux_t rdIdx;
    ux_t wrIdx;
} Fifo_t;


err_t Fifo_Create(Fifo_t** _ppfifo, ux_t _fifoBufLen);
err_t Fifo_CreateStatic(Fifo_t** _ppfifo, void const* const _pfifoBuf, ux_t _fifoBufLen);
err_t Fifo_Put(Fifo_t * const _pfifo, u8 _byte);
err_t Fifo_Pop(Fifo_t * const _pfifo, u8 * const _pbyte);
err_t Fifo_Peek(Fifo_t * const _pfifo, u8 * const _pbyte);
ux_t  Fifo_Peeks(Fifo_t * const _pfifo, u8 * const _prxBuf, ux_t _rxBufLen);
ux_t  Fifo_Write(Fifo_t * const _pfifo, u8 * const _pwrBuf, ux_t _wrBufLen);
ux_t  Fifo_Read(Fifo_t * const _pfifo, u8 * const _prdBuf, ux_t _rdBufLen);
err_t Fifo_Reset(Fifo_t * const _pfifo);
ux_t  Fifo_GetLength(Fifo_t const* const _pfifo);
ux_t  Fifo_GetRestLength(Fifo_t const* const _pfifo);
bool  Fifo_Empty(Fifo_t const* const _pfifo);

#ifdef __cplusplus
}
#endif
#endif //FIFO_H_
