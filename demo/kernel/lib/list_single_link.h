#ifndef __LIST_SINGLE_LINK_H__
#define __LIST_SINGLE_LINK_H__

#include <stdio.h>
#include "../exception/exception.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SLinkNode
{
    struct SLinkNode *pNext;
} SLinkNode_t;

typedef struct
{
    SLinkNode_t *pHead;
    SLinkNode_t *pTail;
} SLinkMgr_t;

#pragma push
#pragma diag_suppress 815
eExcpt_t SList_Put( SLinkMgr_t *const _pSLstMgr, SLinkNode_t *const _pe );
SLinkNode_t * SList_Pop( SLinkMgr_t *const _pSLstMgr );
eExcpt_t SList_Delete( SLinkMgr_t *const _pSLstMgr, SLinkNode_t *const _pe );
static inline SLinkNode_t const *const SList_Peek( SLinkMgr_t const * const _pSLstMgr )
{
    if ( NULL == _pSLstMgr ) {
        return (SLinkNode_t*)NULL;
    }
    return _pSLstMgr->pHead ? _pSLstMgr->pHead : (SLinkNode_t*)NULL;
}
#pragma pop

static inline void SList_Reset( SLinkMgr_t * const _pSLstMgr )
{
    if ( NULL != _pSLstMgr ) {
        _pSLstMgr->pHead = NULL;
        _pSLstMgr->pTail = NULL;
    }
}
#ifdef __cplusplus
}
#endif
#endif //__LIST_SINGLE_LINK_H__
