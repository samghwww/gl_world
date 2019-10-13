/*******************************************************************************
 Copyright (C) 2019 Sam He(HeGuanglin)

 History:
    Date        Author          Notes
 2019/10/06     Sam He          The first version

 Discription:
    Implementation of the single linke node and double linke node list.
 
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


// Double link node list implementation below/following
err_t DList_Insert(DNode_t * const _pbase, DNode_t * const _pin)
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
err_t DList_Delete(DNode_t * const _pbase, DNode_t * const _pdel)
{

    return ERR_SUCCESS;
}

err_t DList_Search(DNode_t * const _pbase, DNode_t * const _psch)
{

    return ERR_SUCCESS;
}
