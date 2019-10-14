/*******************************************************************************
Copyright (C) 2019 Sam He(HeGuanglin)

Discription:
    Implementation of queue.

History:
    Date        Author          Notes
 2019/10/06     Sam He          The first version

*******************************************************************************/

err_t Queue_Init(void)
{

}

err_t Queue_ChgHead(Queue_t * const _pq, void *_p)
{
    if (NULL == _pq || NULL == p) {
        return ERR_NULL;
    }
    ((SNode_t*)_p)->nxt = _pq->head->nxt;
    _pq->head = _p;
    return ERR_SUCCEED;
}

err_t Queue_AddTail(Queue_t * const _pq, void *_p)
{
    if (NULL == _pq || NULL == p) {
        return ERR_NULL;
    }
    _p->nxt = NULL;
    _pq->tail->nxt = _p;
    return ERR_SUCCEED;
}

err_t Queue_Insert(void *_pb, void *_pin)
{
    if (NULL == _pb || NULL == _pin) {
        return ERR_NULL;
    }
    _pin->nxt = _pb->nxt;
    _pb->nxt = _pin;
    return ERR_SUCCEED;
}

err_t Queue_Search(Queue_t const * const _pq, void const * const _psrch)
{
    if (NULL == _pb || NULL == _pin) {
        return ERR_NOT_FOUND;
    }
    SNode_t const *tmp = (SNode_t const *)_pq->head;
    while (tmp) {
        if (tmp == _psrch) {
            return ERR_SUCCEED;
        } else {
            tmp = tmp->nxt;
        }
    }
    return ERR_NOT_FOUND;
}

void *Queue_PeekHead(Queue_t * const _pq)
{
    return (void*)_pq->head;
}

// Just see/look the tail of queue
void *Queue_PeekTail(Queue_t * const _pq)
{
    return (void*)_pq->tail;
}

// Get the header of queue and remove it.
void *Queue_GetHead(Queue_t * const _pq)
{
    void *ret = (void*)_pq->head;
    _pq->head = _pq->head->nxt;
    return ret;
}

// Find/Search/Seek the del element and delete it.
err_t Queue_Del(Queue_t * const _pq, void const * const _pdel)
{
    if (NULL == _pq || NULL == _pdel) {
        return ERR_FAILED;
    }
    if (_pdel == _pq->head) {
        _pq->head = _pq->head->nxt;
        return ERR_SUCCEED;
    }
    SNode_t *prv = _pq->head;
    SNode_t *cur = prv->nxt;
    while (cur) {
        if (cur == _pdel) {
            break;
        } else {
            prv = cur;
            cur = cur->nxt;
        }
    }
    prv->nxt = cur->nxt;
    return ERR_SUCCEED;
}

// Delete the queue element that know it's previor
err_t Queue_DelN(void * const _pprv, void const * const _pdel)
{
    if (NULL == _pprv || NULL == _pdel) {
        return ERR_FAILED;
    }
    if (_pprv->nxt != _pdel) {
        return ERR_NOT_SUPPORT;
    }
    _pprv->nxt = _pdel->nxt;
    return ERR_SUCCEED;
}
