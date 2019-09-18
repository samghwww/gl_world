#ifndef __FIFO_H__
#define __FIFO_H__

//#include "../inc/typedef.h"
#include "../exception/exception.h"

#ifdef __cplusplus
extern "C" {
#endif

#if 0
typedef struct
{
    unsigned char e;
} FifoElement_t;
#else
typedef unsigned char  FifoElement_t;
#endif

typedef enum
{
    FIFO_MODE_NORMAL,
    FIFO_MODE_CIRCLAR
} eFifoMode_t;

typedef struct Fifo
{
    FifoElement_t   *pCtx;
    unsigned        sz;
    unsigned        rdPos;
    unsigned        wrPos;
    eFifoMode_t      mode;
} sFifo_t;

// Declare functions
eExcpt_t Fifo_Create( sFifo_t *const _pFifo,
    void const *const _pFifoMem,
    unsigned const _fifoSz );
eExcpt_t Fifo_Put( sFifo_t *const _pFifo,
    FifoElement_t const _e );
FifoElement_t Fifo_Pop( sFifo_t *const _pFifo );
unsigned Fifo_ReadNoSkRdPos( sFifo_t const *const _pFifo,
    FifoElement_t *const _pDst,
    unsigned const _rdSz );
eExcpt_t Fifo_Write( sFifo_t *const _pFifo,
    FifoElement_t const *const _pSrc,
    unsigned const _wrSz );
eExcpt_t Fifo_Read( sFifo_t *const _pFifo, FifoElement_t *const _pDst,
    unsigned const _rdSz );
eExcpt_t Fifo_SkipWrPos( sFifo_t *const _pFifo, unsigned const _skNum );
eExcpt_t Fifo_SkipRdPos( sFifo_t *const _pFifo, unsigned const _skNum );
eExcpt_t Fifo_Adjust( sFifo_t *const _pFifo );
static inline unsigned Fifo_Peeks(sFifo_t const *const _pFifo,
    FifoElement_t *const _pDst,
    unsigned const _peekSz)
{
    return Fifo_ReadNoSkRdPos( _pFifo, _pDst, _peekSz );
}

static inline unsigned Fifo_CurrSz( sFifo_t const *const _pFifo )
{
    return
        _pFifo->wrPos >= _pFifo->rdPos ?
        _pFifo->wrPos  - _pFifo->rdPos :
        _pFifo->wrPos  + ( _pFifo->sz - _pFifo->rdPos );
}
static inline unsigned Fifo_RestSz( sFifo_t const *const _pFifo )
{
    return _pFifo->sz - Fifo_CurrSz( _pFifo );
}

/// @Brief
///  Reset fifo vessle.
/// @Param
///  _pFifo: The pointer of the fifo handle.
/// @Return None
static inline void Fifo_Reset( sFifo_t *const _pFifo )
{
    _pFifo->wrPos = 0;
    _pFifo->rdPos = 0;
} // End Fifo_Reset()

#ifdef __cplusplus
}
#endif
#endif //__FIFO_H__
