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

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    void * pbuf;
    ux_t bufLen;
    ux_t rdIdx;
    ux_t wrIdx;
} Fifo_t;


extern err_t Fifo_Create(ux_t _fifoBufLen);
extern err_t Fifo_Put(Fifo_t * const _pfifo, u8 _byte);
extern err_t Fifo_Pop(Fifo_t * const _pfifo, u8 * const _pbyte);
extern err_t Fifo_Peek(Fifo_t * const _pfifo, u8 * const _pbyte);
extern err_t Fifo_Peeks(Fifo_t * const _pfifo, u8 * const _prxBuf, ux_t _rxBufLen);
extern err_t Fifo_Write(Fifo_t * const _pfifo, u8 * const _pwrBuf, ux_t _wrBufLen);
extern err_t Fifo_Read(Fifo_t * const _pfifo, u8 * const _prdBuf, ux_t _rdBufLen);
extern err_t Fifo_Reset(Fifo_t * const _pfifo);
extern err_t Fifo_IsEmpty(Fifo_t const* const _pfifo);
extern err_t Fifo_GetLenght(Fifo_t const* const _pfifo);
#ifdef __cplusplus
}
#endif
#endif //FIFO_H_
