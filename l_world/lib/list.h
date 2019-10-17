/*******************************************************************************
Copyright (C) 2019 Sam He(HeGuanglin)

Discription:
    Definition of the single linke node and double linke node list.
History:
    Date        Author          Notes
 2019/10/06     Sam He          The first version

*******************************************************************************/

#ifndef LIST_H_
#define LIST_H_


#include "../inc/err.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    LIST_TYPE_NORMAL,
    LIST_TYPE_CIRCLE,
    LIST_TYPE_INVALID,
} ListType_t;

// Single link node data type
typedef struct snode {
    struct snode *pnxt;
} SNode_t;

// Double link node data type
typedef struct dnode {
    struct dnode *pprv;
    struct dnode *pnxt;
} DNode_t;

typedef struct {
    SNode_t *pshead;
    SNode_t *pstail;
} SList_t;

typedef struct {
    DNode_t *pdhead;
    DNode_t *pdtail;
} DList_t;

extern err_t SList_RingInsert(SNode_t * const _pbase, SNode_t * const _pin);
extern err_t SList_RingAdd(SList_t * const _pslst, SNode_t * const _padd);
extern err_t SList_RingDelete(SList_t * const _pslst, SNode_t * const _pdel);
extern err_t SList_RingSearch(SList_t * const _pslst, SNode_t * const _psch);

extern err_t SList_UnRingInsert(SList_t * const _pslst, SNode_t * const _pin);
extern err_t SList_UnRingAdd(SList_t * const _pslst, SNode_t * const _padd);
extern err_t SList_UnRingDelete(SList_t * const _pslst, SNode_t * const _pdel);
extern err_t SList_UnRingSearch(SList_t * const _pslst, SNode_t * const _psch);

extern err_t DList_RingInsert(DList_t * const _pbase, DNode_t * const _pin);
extern err_t DList_RingDelete(DList_t * const _pbase, DNode_t * const _pdel);
extern err_t DList_RingSearch(DList_t * const _pbase, DNode_t * const _psch);

extern err_t DList_UnRingReplaceNode(DList_t* const _pdlst, DNode_t* const _preplace);
extern err_t DList_UnRingInsert(DList_t * const _pdlst, DNode_t * const _pin);
extern err_t DList_UnRingAdd(DList_t * const _pdlst, DNode_t * const _padd);
extern err_t DList_UnRingRemove(DList_t * const _pdlst, DNode_t * const _prmv);
extern err_t DList_UnRingDelete(DList_t * const _pdlst, DNode_t * const _pdel);
extern void* DList_UnRingPop(DList_t * const _pdlst, DNode_t * const _ppop);
extern err_t DList_UnRingSearch(DList_t * const _pdlst, DNode_t * const _psch);
extern bool DList_IsEmpty(DList_t const * const _pdlst);

#ifdef __cplusplus
}
#endif
#endif //LIST_H_
