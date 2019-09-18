
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../inc/typedef.h"
#include "../exception/exception.h"

#include "queue.h"


/// @Brief
///  Create queue.
/// @Param
///  _pSLstMem: The pointer of the list memery.
///  _lstSz: The size of the specified memery.
/// @Return
///  Exception code, contain Error code and warn code.
///  @Ref eExcpt_t
eExcpt_t Queue_Create( SQueue_t *_pQueue, SQueue_t *_pQueueMem,
    const long _queueSz )
{
    if ( NULL == _pQueue || NULL == _pQueueMem )
    {
        return ERR_NULL;
    }

    if ( 0x00 == _queueSz )
    {
        return ERR_NOT_SUPPORT;
    }

    memset( _pQueueMem, 0x00, sizeof( *_pQueueMem )*_queueSz );
    _pQueue->pCntxt = _pQueueMem;
    _pQueue->sz     = _queueSz;
    _pQueue->head   = _pQueue->tail = NULL;

    return ERR_SUCCESS;
} // End Queue_Create()


/// @Brief
///  Put a element to queue.
/// @Param
///  _pQueue: The pointer of the queue memery.
///  _e: The element gonna to add to queue.
/// @Return
///  Exception code, contain Error code and warn code.
///  @Ref eExcpt_t
eExcpt_t Queue_Put( SQueue_t *_pQueue, const SQueueEle_t *_pe )
{
    long eIdx;
    SNode_t *pTmpQueue;

    if ( NULL == _pQueue )
    {
        return ERR_NULL;
    }

    pTmpQueue = ( SNode_t * )_pQueue->pCntxt;

    for ( eIdx = 0; eIdx < _pQueue->sz; eIdx++ )
    {
        if ( NULL == pTmpQueue[eIdx].e.cntxt.fn )
        {
            memcpy( &pTmpQueue[eIdx].e, _pe, sizeof( pTmpQueue[eIdx].e ) );
            _pQueue->pPrioCnt[_pe->prio]++;
            break;
        }
        else
        {
            // go on
        }
    } // End for (eIdx = 0; eIdx < _pQueue->sz; eIdx++)

    if ( eIdx == _pQueue->sz )
    {
        // Have no enough memery save new element
        return ERR_NO_MEM;
    }
    else
    {
        // go on
    }

    _pQueue->tail = _pQueue->tail->next;

    return ERR_SUCCESS;
} // End Queue_Put()

/// @Brief
///  Pop a element from queue.
/// @Param
///  _pQueue: The pointer of the queue memery.
/// @Return
///  The element of the head of the queue
SQueueEle_t Queue_Pop( SQueue_t *_pQueue )
{
    SQueueEle_t ret;

    ret              = _pQueue->head->e;
    _pQueue->pPrioCnt[ret.prio]--;
    memset( &_pQueue->head->e, 0x00, sizeof( _pQueue->head->e ) );
    _pQueue->head    = _pQueue->head->next;

    return ret;
} // End Queue_Pop

/// @Brief
///  Judge a queue is if empty.
/// @Param
///  _pQueue: The pointer of the queue memery.
/// @Return
///  true:  Queue is empty.
///  false: Queue is not empty.
bool Queue_IsEmpty( const SQueue_t *_pQueue )
{
    return ( bool )( ( NULL != _pQueue ) && ( _pQueue->head == _pQueue->tail ) );
} // End Queue_IsEmpty

/// @Brief
///  Judge a queue is if empty.
/// @Param
///  _pQueue: The pointer of the queue memery.
/// @Return
///  true:  Queue is empty.
///  false: Queue is not empty.
eExcpt_t Queue_Del( SQueue_t *_pQueue, const SQueueEle_t *_pe )
{
    if ( NULL == _pQueue )
    {
        return ERR_NULL;
    }


    return ERR_SUCCESS;
} // End Queue_Del()

/// @Brief
///  Search an element is if in the specified queue.
/// @Param
///  _pQueue: The pointer of the queue memery.
/// @Return
///  NULL:  Not fund.
///  other: The pointer of the node contain the search element.
SNode_t *Queue_Search( SQueue_t *_pQueue,
    const SQueueEle_t *_pe ) /// @NOT Completed
{
    SNode_t *ret = NULL;

    if ( NULL == _pQueue )
    {
        return NULL;
    }

    ret              = _pQueue->head;
    _pQueue->pPrioCnt[ret->e.prio]--;
    memcpy( &_pQueue->head->e, _pe, sizeof( _pe[0] ) );
    _pQueue->head    = _pQueue->head->next;

    return ret;
} // End Queue_Search()
