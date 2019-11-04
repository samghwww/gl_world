/*******************************************************************************
Copyright (C) 2019 Sam He(HeGuanglin)

Discription:
    Implementation of queue.

History:
    Date        Author          Notes
 2019/10/06     Sam He          The first version

*******************************************************************************/


#include "queue.h"
#include "../inc/err.h"


#include <stdlib.h>

// Pointer(any) convert to single node pointer
#define POINTER2PSNODE(p)       ((SNode_t*)p)

// Pointer(any) convert to double/dual node pointer
#define POINTER2PDNODE(p)       ((DNode_t*)p)

err_t Queue_Init(void)
{

}

static inline err_t queue_AddFisrtElement(Queue_t * const _pq, void * const _pfirst)
{
    POINTER2PSNODE(_pfirst)->pnxt = NULL;
    _pq->phead = _pfirst;
    _pq->ptail = _pfirst;
    return ERR_SUCCEED;
}

err_t Queue_ChgHead(Queue_t * const _pq, void *_p)
{
    if (NULL == _pq || NULL == _p) {
        return ERR_NULL;
    }
    if (_pq->phead) {
        POINTER2PSNODE(_p)->pnxt = POINTER2PSNODE(_pq->phead)->pnxt;
    }
    _pq->phead = _p;
    return ERR_SUCCEED;
}

err_t Queue_AddHead(Queue_t* const _pq, void* _p)
{

    return ERR_SUCCEED;
}

err_t Queue_AddTail(Queue_t * const _pq, void *_p)
{
    if (NULL == _pq || NULL == _p) {
        return ERR_NULL;
    }
    POINTER2PSNODE(_p)->pnxt = NULL;
    _pq->pstail->pnxt = _p;
    _pq->pstail = _p;
    return ERR_SUCCEED;
}

// Insert queue element to queue.
// _pb: The queue basic element pointer.
// _pin: The insert element pointer.
err_t Queue_Insert(void *_pb, void *_pin)
{
    if (NULL == _pb || NULL == _pin) {
        return ERR_NULL;
    }
    POINTER2PSNODE(_pin)->pnxt = POINTER2PSNODE(_pb)->pnxt;
    POINTER2PSNODE(_pb)->pnxt = _pin;
    return ERR_SUCCEED;
}

err_t Queue_Add(Queue_t* const _pq, void* const _padd)
{
    if (Queue_IsEmpty(_pq)) {
        queue_AddFisrtElement(_pq, _padd);
    } else {
        Queue_AddTail(_pq, _padd);
    }
    return ERR_SUCCEED;
}

err_t Queue_Search(Queue_t const * const _pq, void const * const _psrch)
{
    if (NULL == _pq || NULL == _psrch) {
        return ERR_NOT_FOUND;
    }
    SNode_t const *ptmp = POINTER2PSNODE(_pq->phead);
    while (ptmp) {
        if (ptmp == _psrch) {
            return ERR_SUCCEED;
        } else {
            ptmp = ptmp->pnxt;
        }
    }
    return ERR_NOT_FOUND;
}

// Find/Search/Seek the del element and delete it.
err_t Queue_Delete(Queue_t * const _pq, void const * const _pdel)
{
    if (NULL == _pq || NULL == _pq->phead || NULL == _pdel) {
        return ERR_NOT_FOUND;
    }
    if (_pdel == _pq->phead) {
        _pq->phead = POINTER2PSNODE(_pq->phead)->pnxt;
        return ERR_SUCCEED;
    }
    SNode_t *prv = POINTER2PSNODE(_pq->phead);
    SNode_t *cur = prv->pnxt;
    while (cur) {
        if (cur == _pdel) {
            break;
        } else {
            prv = cur;
            cur = cur->pnxt;
        }
    }
    prv->pnxt = cur ? cur->pnxt : cur;
    return ERR_SUCCEED;
}

// Delete the queue element that know it's previor
err_t Queue_DelNode(void * const _pb, void const * const _pdel)
{
    if (NULL == _pb || NULL == _pdel) {
        return ERR_NOT_FOUND;
    }
    if (POINTER2PSNODE(_pb)->pnxt != _pdel) {
        return ERR_NOT_FOUND;
    }
    POINTER2PSNODE(_pb)->pnxt = POINTER2PSNODE(_pdel)->pnxt;
    return ERR_SUCCEED;
}

void *Queue_PeekHead(Queue_t const * const _pq)
{
    return _pq->phead;
}

// Just see/look the tail of queue
void *Queue_PeekTail(Queue_t const * const _pq)
{
    return _pq->ptail;
}

// Get the header of queue and remove it.
void *Queue_GetHead(Queue_t * const _pq)
{
    void *ret = _pq->phead;
	_pq->phead = POINTER2PSNODE(_pq->phead)->pnxt;
    return ret;
}

bool Queue_IsEmpty(Queue_t const * const _pq)
{
    return (NULL == _pq->phead) ? true : false;
}
