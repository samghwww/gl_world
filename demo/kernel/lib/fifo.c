
#include <stdlib.h>
#include <string.h>

#include "../inc/typedef.h"
#include "../exception/exception.h"

#include "fifo.h"


/// @Brief
///  Create fifo vessle.
/// @Param
///  _pFifo: The pointer of the fifo handle.
///  _lstSz: The size of the fifo memery.
/// @Return
///  Exception code, contain Error code and warn code.
///  @Ref eExcpt_t
eExcpt_t Fifo_Create( sFifo_t *const _pFifo,
    void const *const _pFifoMem,
    unsigned const _fifoSz )
{
    if ( NULL == _pFifo || NULL == _pFifoMem || 0x00 == _fifoSz )
    {
        return ERR_INVALID_PARAM;
    }

    _pFifo->pCtx = ( unsigned char * )_pFifoMem;
    _pFifo->sz     = _fifoSz;
    _pFifo->rdPos  = 0;
    _pFifo->wrPos  = 0;

    return ERR_SUCCESS;
} //End Fifo_Create()

/// @Brief
///  Put a fifo element to fifo vessle.
/// @Param
///  _pFifo: The pointer of the fifo handle.
///  _e: The element want to add to fifo vessle.
/// @Return
///  Exception code, contain Error code and warn code.
///  @Ref eExcpt_t
eExcpt_t Fifo_Put( sFifo_t *const _pFifo, FifoElement_t const _e )
{
    if ( NULL == _pFifo )
    {
        return ERR_NULL;
    }
    else
    {
        // go on
    }

    if ( FIFO_MODE_NORMAL == _pFifo->mode )
    {
        if ( _pFifo->wrPos < _pFifo->sz )
        {
            _pFifo->pCtx[_pFifo->wrPos] = _e;
            ++_pFifo->wrPos;
        }
        else
        {
            return ERR_NO_MEM;
        }
    }
    else if ( FIFO_MODE_CIRCLAR == _pFifo->mode )
    {
        _pFifo->wrPos = _pFifo->wrPos >= _pFifo->sz ? 0 : _pFifo->wrPos;
        _pFifo->pCtx[_pFifo->wrPos] = _e;
        ++_pFifo->wrPos;
    }
    else
    {
        return ERR_NOT_SUPPORT;
    }

    return ERR_SUCCESS;
} // End Fifo_Put()

/// @Brief
///  Pop a fifo element from fifo vessle.
/// @Param
///  _pFifo: The pointer of the fifo handle.
///  _e: Pop an element from fifo memery.
/// @Return
///  The first element in fifo vessle.
///  @Ref FifoElement_t
FifoElement_t Fifo_Pop( sFifo_t *const _pFifo )
{
    FifoElement_t ret;

    if ( NULL == _pFifo )
    {
        return ERR_NULL;
    }
    else
    {
        // go on
    }

    if ( _pFifo->rdPos == _pFifo->wrPos )
    {
        return ERR_NOT_FOUND;
    }
    else
    {
        // go on
    }

    ret = _pFifo->pCtx[_pFifo->rdPos];
    ++_pFifo->rdPos;

    if ( _pFifo->rdPos == _pFifo->wrPos )
    {
        Fifo_Reset( _pFifo );
    }
    else if ( _pFifo->rdPos > _pFifo->sz )
    {
        if ( _pFifo->wrPos >= _pFifo->sz )
        {
            Fifo_Reset( _pFifo );
        }
        else
        {
            _pFifo->rdPos = 0;
        }
    }

    return ret;
} // End Fifo_Pop()

/// @Brief
///  Put a fifo element to fifo vessle.
/// @Param
///  _pFifo: The pointer of the fifo handle.
///  _pEleArr: The pointer of element arry want to add to fifo vessle.
///  _wrSz: Write size
/// @Return
///  Exception code, contain Error code and warn code.
///  @Ref eExcpt_t
eExcpt_t Fifo_Write( sFifo_t *const _pFifo, FifoElement_t const *const _pSrc,
    unsigned const _wrSz )
{
    if ( NULL == _pFifo || NULL == _pSrc )
    {
        return ERR_NULL;
    }
    else
    {
        // go on
    }

    if ( 0x00 == _wrSz || _wrSz > _pFifo->sz )
    {
        return ERR_NOT_SUPPORT;
    }
    else
    {
        // go on
    }

    if ( _pFifo->wrPos >= _pFifo->sz )
    {
        _pFifo->wrPos = 0;
    }
    else
    {
        // go on
    }

    unsigned register upSz = _pFifo->sz - _pFifo->wrPos;


    if ( _wrSz <= upSz )
    {
        memcpy( ( void * )&_pFifo->pCtx[_pFifo->wrPos],
            ( void * )_pSrc, _wrSz );
    }
    else
    {
        memcpy( ( void * )&_pFifo->pCtx[_pFifo->wrPos],
            ( void * )_pSrc, upSz );
        if ( FIFO_MODE_CIRCLAR == _pFifo->mode )
        {
            memcpy( ( void * )&_pFifo->pCtx[0],
                ( void * )&_pSrc[upSz], _wrSz - upSz );
        }
        else
        {
            Fifo_SkipWrPos( _pFifo, upSz );
            return ERR_SUCCESS;
        }

    }

    Fifo_SkipWrPos( _pFifo, _wrSz );

    return ERR_SUCCESS;
} // End Fifo_Write()

/// @Brief
///  Read a block of fifo element to fifo vessle but not skip read position.
/// @Param
///  _pFifo: The pointer of the fifo handle.
///  _pEleArr: The pointer of element arry want to add to fifo vessle.
///  _rdSz: Read size
/// @Return
///  Writen number of data
unsigned Fifo_ReadNoSkRdPos( sFifo_t const *const _pFifo,
    FifoElement_t *const _pDst,
    unsigned const _rdSz )
{
    if ( NULL == _pFifo || NULL == _pDst )
    {
        return 0;
    }

    if ( 0x00 == _rdSz || _rdSz > _pFifo->sz )
    {
        return 0;
    }

    if ( _rdSz > Fifo_CurrSz( _pFifo ) )
    {
        return 0;
    }

    if ( _rdSz <= _pFifo->sz - _pFifo->rdPos )
    {
        memcpy( _pDst, &_pFifo->pCtx[_pFifo->rdPos],
            _rdSz * sizeof( FifoElement_t ) );
    }
    else
    {
        memcpy( _pDst, &_pFifo->pCtx[_pFifo->rdPos],
            ( _pFifo->sz - _pFifo->rdPos ) * sizeof( FifoElement_t ) );
        memcpy( &_pDst[_pFifo->sz - _pFifo->rdPos], &_pFifo->pCtx[0],
            ( _rdSz - ( _pFifo->sz - _pFifo->rdPos ) ) * sizeof( FifoElement_t ) );
    }

    return _rdSz;
} // End Fifo_ReadNoSkRdPos()

/// @Brief
///  Put a fifo element to fifo vessle.
/// @Param
///  _pFifo: The pointer of the fifo handle.
///  _pEleArr: The pointer of element arry want to add to fifo vessle.
///  _rdSz: Read size
/// @Return
///  Exception code, contain Error code and warn code.
///  @Ref eExcpt_t
eExcpt_t Fifo_Read( sFifo_t *const _pFifo, FifoElement_t *const _pDst,
    unsigned const _rdSz )
{
#if 0
    if ( NULL == _pFifo || NULL == _pDst )
    {
        return ERR_NULL;
    }

    if ( 0x00 == _rdSz || _rdSz > _pFifo->sz )
    {
        return ERR_NOT_SUPPORT;
    }

    if ( _rdSz > Fifo_CurrSz( _pFifo ) )
    {
        return ERR_INVALID_PARAM;
    }

    if ( _rdSz <= _pFifo->sz - _pFifo->rdPos )
    {
        memcpy( _pDst, &_pFifo->pCtx[_pFifo->rdPos],
            _rdSz * sizeof( FifoElement_t ) );
    }
    else
    {
        memcpy( _pDst, &_pFifo->pCtx[_pFifo->rdPos],
            ( _pFifo->sz - _pFifo->rdPos ) * sizeof( FifoElement_t ) );
        memcpy( &_pDst[_pFifo->sz - _pFifo->rdPos], &_pFifo->pCtx[0],
            ( _rdSz - ( _pFifo->sz - _pFifo->rdPos ) ) * sizeof( FifoElement_t ) );
    }
#endif
    if ( 0x00 != Fifo_ReadNoSkRdPos( _pFifo, _pDst, _rdSz ) )
    {
        Fifo_SkipRdPos( _pFifo, _rdSz );
    }
    else
    {
        return ERR_INVALID_PARAM;
    }

    return ERR_SUCCESS;
} // End Fifo_Read()

void Fifo_WrPos( sFifo_t *const _pFifo, unsigned const _wrPos )
{
    _pFifo->wrPos = _wrPos;
}

void Fifo_RdPos( sFifo_t *const _pFifo, unsigned const _rdPos )
{
    _pFifo->rdPos = _rdPos;
}

/// @Brief
///  Skip fifo write position.
/// @Param
///  _pFifo: The pointer of the fifo handle.
///  _skNum: Skip number.
/// @Return
///  Exception code, contain Error code and warn code.
///  @Ref eExcpt_t
eExcpt_t Fifo_SkipWrPos( sFifo_t *const _pFifo, unsigned const _skNum )
{
    if ( NULL == _pFifo )
    {
        return ERR_NULL;
    }

    if ( 0x00 == _skNum || _skNum >= _pFifo->sz )
    {
        return ERR_NOT_SUPPORT;
    }

    _pFifo->wrPos += _skNum;

    _pFifo->wrPos = ( _pFifo->wrPos > _pFifo->sz ) ?
        ( _pFifo->wrPos - _pFifo->sz ) :
        ( _pFifo->wrPos );

    return ERR_SUCCESS;
} // End Fifo_SkipWrPos()

/// @Brief
///  Skip fifo read position.
/// @Param
///  _pFifo: The pointer of the fifo handle.
///  _skNum: Skip number.
/// @Return
///  Exception code, contain Error code and warn code.
///  @Ref eExcpt_t
eExcpt_t Fifo_SkipRdPos( sFifo_t *const _pFifo, unsigned const _skNum )
{
    if ( NULL == _pFifo )
    {
        return ERR_NULL;
    }

    if ( 0x00 == _skNum || _skNum >= _pFifo->sz )
    {
        return ERR_NOT_SUPPORT;
    }

    _pFifo->rdPos += _skNum;

    if ( _pFifo->rdPos >= _pFifo->sz )
    {
        if ( _pFifo->wrPos >= _pFifo->sz )
        {
            Fifo_Reset( _pFifo );
        }
        else
        {
            _pFifo->rdPos -= _pFifo->sz;
            if ( _pFifo->rdPos > _pFifo->wrPos )
            {
                _pFifo->rdPos = _pFifo->wrPos;
            }
            else
            {
                // go on
            }
        }
    }
    else
    {
        // Some else case.
    }

    return ERR_SUCCESS;
} // End Fifo_SkipRdPos()

/// @Brief
///  Adjust fifo vessle.
///  If have something invovle asynchronous process such as
///   thread, task, intrrupt, @NOTE: NEED THINK ABOUT MORE BEFORE CALL
///   THIS FUNCTION.
/// @Param
///  _pFifo: The pointer of the fifo handle.
/// @Return
///  Exception code, contain Error code and warn code.
///  @Ref eExcpt_t
eExcpt_t Fifo_Adjust( sFifo_t *const _pFifo )
{
    if ( FIFO_MODE_NORMAL == _pFifo->mode )
    {
        if ( 0x00 != _pFifo->rdPos )
        {
            memcpy( &_pFifo->pCtx[0], &_pFifo->pCtx[_pFifo->rdPos],
                Fifo_CurrSz( _pFifo ) );
        }
        else
        {
            // go on
            // Don't need adjust
            // It's on the right way.
        }
    }
    else
    {
        // Don't need adjust
        // FIFO_MODE_CIRCLAR mode is not support adjust.
        return ERR_NOT_SUPPORT;
    }

    return ERR_SUCCESS;
} // End Fifo_Reset()

