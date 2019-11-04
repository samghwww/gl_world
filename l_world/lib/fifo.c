/*******************************************************************************
Copyright (C) 2019 Sam He(HeGuanglin)

Discription:
    Implementations about fifo.
History:
    Date        Author          Notes
 2019/10/23     Sam He          The first version
 
*******************************************************************************/

#include "fifo.h"

bool Fifo_Fulled(Fifo_t const * const _pfifo)
{
    return _pfifo->wrIdx == _pfifo->rdIdx;
}

bool Fifo_Empty(Fifo_t const * const _pfifo)
{
    return (_pfifo->wrIdx-1) == _pfifo->rdIdx;
}

err_t Fifo_Create(ux_t _fifoBufLen)
{
    return ERR_SUCCEED;
}

err_t Fifo_CreateStatic(void const * const _pfifoBuf, ux_t _fifoBufLen)
{
    return ERR_SUCCEED;
}

err_t Fifo_Put(Fifo_t * const _pfifo, u8 _byte)
{
    if (NULL == _pfifo) {
        return ERR_NULL;
    }
    if (Fifo_Fulled(_pfifo)) {
        return ERR_NO_MEM;
    }
    _pfifo->pbuf[_pfifo->wrIdx] = _byte;
    _pfifo->wrIdx = (++_pfifo->wrIdx) < _pfifo->sz ? _pfifo->wrIdx : 0;
    return ERR_SUCCEED;
}

err_t Fifo_Pop(Fifo_t * const _pfifo, u8 * const _pbyte)
{
    if (NULL == _pfifo) {
        return ERR_NULL;
    }
    if (Fifo_Empty(_pfifo)) {
        return ERR_NOT_FOUND;
    }
    if (-1 == _pfifo->rdIdx) {
        *_pbyte = _pfifo->pbuf[0];
        _pfifo->rdIdx = 1;
        goto DONE;
    } else {
        *_pbyte = _pfifo->pbuf[_pfifo->rdIdx];
    }
    ++_pfifo->rdIdx;
    if (_pfifo->rdIdx >= _pfifo->sz) {
        _pfifo->rdIdx = 0 == _pfifo->wrIdx ? -1 : 0;
    }
DONE:
    return ERR_SUCCEED;
}

err_t Fifo_Peek(Fifo_t * const _pfifo, u8 * const _pbyte)
{
    if (NULL == _pfifo) {
        return ERR_NULL;
    }
    if (Fifo_Empty(_pfifo)) {
        return ERR_NOT_FOUND;
    }
    if (-1 == _pfifo->rdIdx) {
        *_pbyte = _pfifo->pbuf[0];
    } else {
        *_pbyte = _pfifo->pbuf[_pfifo->rdIdx];
    }
    return ERR_SUCCEED;
}

err_t Fifo_Peeks(Fifo_t * const _pfifo, u8 * const _pbuf, ux_t _bufLen)
{
    if (NULL == _pfifo) {
        return ERR_NULL;
    }

}

err_t Fifo_Write(Fifo_t * const _pfifo, u8 * const _pwrBuf, ux_t _wrBufLen)
{
    if (NULL == _pfifo) {
        return ERR_NULL;
    }
}

err_t Fifo_Read(Fifo_t * const _pfifo, u8 * const _prdBuf, ux_t _rdBufLen)
{
    if (NULL == _pfifo) {
        return ERR_NULL;
    }
}

err_t Fifo_Reset(Fifo_t * const _pfifo)
{
    if (NULL == _pfifo) {
        return ERR_NULL;
    }
    _pfifo->wrIdx = 0;
    _pfifo->rdIdx = -1;
    return ERR_SUCCEED;
}

err_t Fifo_IsEmpty(Fifo_t const* const _pfifo)
{
    if (NULL == _pfifo) {
        return ERR_NULL;
    }
    if (0 == _pfifo->wrIdx && _pfifo->bufLen == _pfifo->rdIdx) {
        return ERR_YES;
    }
    else {
        return ERR_NO;
    }
}
err_t Fifo_GetLenght(Fifo_t const* const _pfifo)
{

}
