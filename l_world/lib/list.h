/*******************************************************************************
 Copyright (C) 2019 Sam He(HeGuanglin)

 History:
    Date        Author          Notes
 2019/10/06     Sam He          The first version

 Discription:
    Definition of the single linke node and double linke node list.
 
*******************************************************************************/

#ifndef LIST_H_
#define LIST_H_

#include "../inc/err.h"

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


extern err_t SList_Insert(SNode_t * const _pbase, SNode_t * const _pin);
extern err_t SList_Delete(SNode_t * const _pbase, SNode_t * const _pdel, ListType_t _lt);
extern err_t SList_Search(SNode_t * const _pbase, SNode_t * const _psch, ListType_t _lt);

extern err_t DList_Insert(DNode_t * const _pbase, DNode_t * const _pin);
extern err_t DList_Delete(DNode_t * const _pbase, DNode_t * const _pdel, ListType_t _lt);
extern err_t DList_Search(DNode_t * const _pbase, DNode_t * const _psch, ListType_t _lt);

#ifdef __cplusplus
}
#endif
#endif //LIST_H_
