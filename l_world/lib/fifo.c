/*******************************************************************************
Copyright (C) 2019 Sam He(HeGuanglin)

Discription:
    Implementations about fifo.
History:
    Date        Author          Notes
 2019/10/23     Sam He          The first version
 
*******************************************************************************/

#include "fifo.h"
#include "../mm/mm.h"
#include "../inc/macrodef.h"
#include "../inc/typedef.h"

//#include <stdlib.h>
#include <stdbool.h>

bool Fifo_Fulled(Fifo_t const * const _pfifo)
{
    return _pfifo->wrIdx == _pfifo->rdIdx;
}

bool Fifo_Empty(Fifo_t const * const _pfifo)
{
    return (_pfifo->wrIdx-1) == _pfifo->rdIdx;
}

err_t Fifo_Create(Fifo_t **_ppfifo, ux_t _fifoBufLen)
{
    if (0x00 == _fifoBufLen) {
        return ERR_INVALID_PARAM;
    }
    Fifo_t *pfifo = (Fifo_t *)malloc(sizeof(*pfifo) + _fifoBufLen);
    if (NULL == pfifo) {
        return ERR_NO_MEM;
    }
    pfifo->pbuf  = (u8*)pfifo + sizeof(*pfifo);
    pfifo->wrIdx = 0;
    pfifo->rdIdx = -1;
    pfifo->capacity = _fifoBufLen;
    *_ppfifo = pfifo;
    return ERR_SUCCEED;
}

err_t Fifo_CreateStatic(Fifo_t **_ppfifo, void const * const _pfifoBuf, ux_t _fifoBufLen)
{
    if (0x00 == _fifoBufLen) {
        return ERR_INVALID_PARAM;
    }
    Fifo_t *pfifo = (Fifo_t *)_pfifoBuf;
    pfifo->pbuf = (Fifo_t *)((u8*)pfifo + sizeof(*pfifo));
    pfifo->wrIdx = 0;
    pfifo->rdIdx = -1;
    pfifo->capacity = _fifoBufLen;
    *_ppfifo = pfifo;
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
    if (Fifo_Empty(_pfifo)) {
        _pfifo->rdIdx = 0;
    }
    _pfifo->pbuf[_pfifo->wrIdx] = _byte;
    _pfifo->wrIdx = ((++_pfifo->wrIdx) < _pfifo->capacity) ? _pfifo->wrIdx : 0;
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
    if (_pfifo->rdIdx >= _pfifo->capacity) {
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

ux_t Fifo_Peeks(Fifo_t * const _pfifo, u8 * const _pbuf, ux_t _bufLen)
{
    if (NULL == _pfifo) {
        return ERR_NULL;
    }
    ux_t const len   = Fifo_GetLength(_pfifo);
    ux_t const rdLen = MIN(len, len);
    ux_t       i     = rdLen;
    ux_t const rdIdx = _pfifo->rdIdx;
    u8        *prd   = _pbuf;
    for ( ; i; i--) {
        if (ERR_SUCCEED != Fifo_Pop(_pfifo, *prd)) {
            break;
        }
        ++prd;
    }
    _pfifo->rdIdx = rdIdx;
    return rdLen - i;
}

ux_t Fifo_Write(Fifo_t * const _pfifo, u8 * const _pwrBuf, ux_t _wrBufLen)
{
    if (NULL == _pfifo) {
        return ERR_NULL;
    }
    ux_t restLen = Fifo_GetRestLength(_pfifo);
    ux_t wrLen   = MIN(restLen, _wrBufLen);
    ux_t i       = wrLen;
    u8  *pwr     = _pwrBuf;
    for ( ; i; i--) {
        if (ERR_SUCCEED != Fifo_Put(_pfifo, *pwr)) {
            break;
        }
        ++pwr;
    }
    return wrLen - i;
}

ux_t Fifo_Read(Fifo_t * const _pfifo, u8 * const _prdBuf, ux_t _rdBufLen)
{
    if (NULL == _pfifo) {
        return ERR_NULL;
    }
    ux_t len = Fifo_GetLength(_pfifo);
    ux_t rdLen = MIN(len, _rdBufLen);
    ux_t i = rdLen;
    u8* prd = _prdBuf;
    for ( ; i; i--) {
        if (ERR_SUCCEED != Fifo_Pop(_pfifo, prd)) {
            break;
        }
        ++prd;
    }
    return rdLen - i;
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

ux_t Fifo_GetLength(Fifo_t const* const _pfifo)
{
    if (NULL == _pfifo) {
        return NULL;
    }
    if (-1 == _pfifo->rdIdx) {
        return 0;
    }
    if (_pfifo->rdIdx < _pfifo->wrIdx) {
        return _pfifo->wrIdx - _pfifo->rdIdx;
    }
    else if (_pfifo->rdIdx > _pfifo->wrIdx) {
        return _pfifo->wrIdx + (_pfifo->capacity - _pfifo->rdIdx);
    }
    else { //if (_pfifo->rdIdx == _pfifo->wrIdx) {
        return _pfifo->capacity;
    }
}

ux_t Fifo_GetRestLength(Fifo_t const* const _pfifo)
{
    if (NULL == _pfifo) {
        return 0;
    }
    return _pfifo->capacity - Fifo_GetLength(_pfifo);
}
