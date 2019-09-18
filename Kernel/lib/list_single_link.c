
#include "../inc/typedef.h"
#include "../exception/exception.h"

#include <stdio.h>
#include "list_single_link.h"



/// @Brief
///  Create single linked list memery vessle.
/// @Param
///  _pSLstMem: The pointer of the list memery.
///  _lstSz: The size of the specified memery.
/// @Return
///  Exception code, contain Error code and warn code.
///  @Ref eExcpt_t
eExcpt_t SList_Create( SLinkNode_t *_pSLstMem, const long _lstSz )
{

    return ERR_SUCCESS;
} // End SList_Create()

/// @Brief
///  Insert one element into the empty node of the specified list.
/// @Param
///  _pSLst: The pointer of the list will be inserted.
///  _e: The element want to insert into list.
/// @Return
///  Exception code, contain Error code and warn code.
///  @Ref eExcpt_t
eExcpt_t SList_Put( SLinkMgr_t *const _pSLstMgr, SLinkNode_t *const _pe )
{
    if ( NULL == _pSLstMgr || NULL == _pe ) {
        return ERR_NULL;
    }
    if ( NULL == _pSLstMgr->pHead ) {
        _pSLstMgr->pHead = _pe;
        _pSLstMgr->pTail = _pSLstMgr->pHead;
    }
    else {
        _pSLstMgr->pTail->pNext = _pe;
        _pSLstMgr->pTail = _pSLstMgr->pTail->pNext;
    }
    _pSLstMgr->pTail->pNext = NULL;
    return ERR_SUCCESS;
} // End SList_Add()

SLinkNode_t * SList_Pop( SLinkMgr_t *const _pSLstMgr )
{
    if ( NULL == _pSLstMgr ) {
        return NULL;
    }

    if ( NULL != _pSLstMgr->pHead ) {
        SLinkNode_t *pRet = _pSLstMgr->pHead;
        _pSLstMgr->pHead = _pSLstMgr->pHead->pNext;
        return pRet;
    }
    else {
        return NULL;
    }
}


/// @Brief
///  Delete one element from the specified list.
/// @Param
///  _pSLst: The pointer of the list will be deleted.
///  _e: The element want to delete in the specified list.
/// @Return
///  Exception code, contain Error code and warn code.
///  @Ref eExcpt_t
eExcpt_t SList_Delete( SLinkMgr_t *const _pSLstMgr, SLinkNode_t *const _pe )
{
    if ( NULL == _pSLstMgr || NULL == _pe ) {
        return ERR_NULL;
    }

    if ( NULL == _pSLstMgr->pHead ) {
        return ERR_NOT_SUPPORT;
    }

    if ( _pSLstMgr->pHead == _pe ) {
        _pSLstMgr->pHead = _pSLstMgr->pHead->pNext;
        return ERR_SUCCESS;
    }

    SLinkNode_t *tmp = _pSLstMgr->pHead;

    while ( tmp->pNext ) {
        if ( tmp->pNext == _pe ) {
            tmp->pNext = tmp->pNext->pNext;
            return ERR_SUCCESS;
        }
        else {
            tmp = tmp->pNext;
        }
    }

    return ERR_NOT_SUPPORT;
} // End SList_Delete()

