/*******************************************************************************
Copyright (C) 2019 Sam He(HeGuanglin)

Discription:
    Implementation of the single linke node and double linke node list.

History:
    Date        Author          Notes
 2019/10/06     Sam He          The first version

*******************************************************************************/

#include "list.h"
#include "../inc/err.h"

#include <stdlib.h>

// true The pointer of link node is not NULL
// false The pointer of link node is NULL
#define CHK_NODE_VALID(pnode)   (NULL != (pnode))

err_t SList_Insert(SNode_t * const _pbase, SNode_t * const _pin)
{
    if (!CHK_NODE_VALID(_pbase) || !CHK_NODE_VALID(_pin)) {
        return ERR_NULL;
    }

    _pin->pnxt = _pbase->pnxt;
    _pbase->pnxt = _pin->pnxt;

    return ERR_SUCCESS;
}

err_t SList_Delete(SNode_t ** const _pbase, SNode_t * const _pdel, ListType_t _lt)
{
    if (!CHK_NODE_VALID(_pbase) || !CHK_NODE_VALID(_pdel)) {
        return ERR_NULL;
    }
    SNode_t * curr = *_pbase;
    // Handle the first node
    if (*_pbase == _pdel) {
        if (LIST_TYPE_CIRCLE == _lt) {
            while (curr->pnxt != *_pbase) {
                curr = curr->pnxt;
            }
            curr->pnxt = (*_pbase)->pnxt;
        }
        *_pbase = (*_pbase)->pnxt;
        return ERR_SUCCESS;
    }


    while (curr->pnxt) {
        if (curr->pnxt == _pdel) {
            curr->pnxt = curr->pnxt->pnxt;
        }
        curr = curr->pnxt;
    }

    return ERR_SUCCESS;
}

err_t SList_Search(SNode_t * const _pbase, SNode_t * const _psch, ListType_t _lt)
{
    if (!CHK_NODE_VALID(_pbase) || !CHK_NODE_VALID(_psch)) {
        return ERR_NULL;
    }

    SNode_t *psrch = _pbase;

    do{
        if (psrch == _psch) {
            break;
        }
        else {
            psrch = psrch->pnxt;
        }
    } while (psrch && psrch != _pbase);

    return ERR_SUCCESS;
}


extern err_t DualList_UnRingReplace(DList_t * const _pdlst,
    DNode_t const * const _preplaced, DNode_t* const _preplacer)
{
    if (DList_Empty(_pdlst)    ||
        NULL == _preplaced          ||
        NULL == _preplacer) {
        return ERR_NULL;
    }
    if (_preplaced == _pdlst->pdhead) {
        _preplacer->pprv = NULL;
        _preplacer->pnxt = _preplaced->pnxt;
        _preplaced->pnxt->pprv = _preplacer;
        _pdlst->pdhead   = _preplacer;
    }
    else if (_preplaced == _pdlst->pdtail) {
        _preplacer->pprv = _preplaced->pprv;
        _preplacer->pnxt = NULL;
        _preplaced->pprv->pnxt = _preplacer;
        _pdlst->pdtail   = _preplacer;
    }
    else {
        _preplacer->pprv = _preplaced->pprv;
        _preplacer->pnxt = _preplaced->pnxt;
        _preplacer->pprv->pnxt = _preplacer;
        _preplacer->pnxt->pprv = _preplacer;
    }
}

// Double link node list implementation below/following
err_t DList_UnRingInsert(DNode_t * const _pbase, DNode_t * const _pin)
{
    if (!CHK_NODE_VALID(_pbase) || !CHK_NODE_VALID(_pin)) {
        return ERR_NULL;
    }

    _pin->pprv = _pbase;
    _pin->pnxt = _pbase->pnxt;

    // What if next pointer is not exist?
    _pbase->pnxt->pprv = _pin;
    _pbase->pnxt       = _pin;

    return ERR_SUCCESS;
}

err_t DList_UnRingAdd(DList_t* const _pdlst, DNode_t* const _padd)
{
    if (NULL == _pdlst || NULL == _padd) {
        return ERR_NULL;
    }
    if (DList_Empty(_pdlst)) {
        _padd->pprv     = NULL;
        _padd->pnxt     = NULL;
        _pdlst->pdhead  = _padd;
        _pdlst->pdtail  = _padd;
    }
    else {
        _padd->pprv = _pdlst->pdtail;
        _pdlst->pdtail->pnxt = _padd;
        _pdlst->pdtail = _padd;
    }
    return ERR_SUCCEED;
}

err_t DList_UnRingDelete(DList_t* const _pdlst, DNode_t * const _pdel)
{
    if (NULL == _pdlst || NULL == _pdel) {
        return ERR_NULL;
    }
    if (DList_Empty(_pdlst)) {
        return ERR_NULL;
    }
    if (_pdel == _pdlst->pdhead) {
        _pdlst->pdhead = _pdlst->pdhead->pnxt;
        if (_pdlst->pdhead) {
            _pdlst->pdhead->pprv = NULL;
        }
    }
    else if (_pdel == _pdlst->pdtail) {
        _pdlst->pdtail->pprv->pnxt = NULL;
        _pdlst->pdtail = _pdlst->pdtail->pprv;
    }
    else {
        _pdel->pprv->pnxt = _pdel->pnxt;
        _pdel->pnxt->pprv = _pdel->pprv;
    }
    return ERR_SUCCESS;
}

err_t DList_UnRingSearch(DList_t* const _pdlst, DNode_t * const _psrch)
{
    if (DList_Empty(_pdlst) || NULL == _psrch) {
        return ERR_NULL;
    }
    DNode_t* pforward = _pdlst->pdhead;
    DNode_t* pbackward = _pdlst->pdtail;
    while (pforward != pbackward) {
        if (_psrch == pforward) {
            return ERR_SUCCESS;
        }
        if (_psrch == pbackward) {
            return ERR_SUCCESS;
        }
        pforward  = pforward->pnxt;
        pbackward = pbackward->pprv;
    }
    return ERR_NOT_FOUND;
}

bool DList_Empty(DList_t const * const _pdlst)
{
    return (NULL == _pdlst->pdhead);
}
