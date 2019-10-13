/*******************************************************************************
 Copyright (C) 2019 Sam He(HeGuanglin)

 History:
    Date        Author          Notes
 2019/10/06     Sam He          The first version

 Discription:
    Definnition of queue.
 
*******************************************************************************/

#ifndef __LQUEUE_H__
#define __LQUEUE_H__

#include "list.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef queue {
    enum {
        void *phead;
        SNode_t *pshead;
        DNode_t *pdhead;
    };
    enum {
        void *ptail;
        SNode_t *pstail;
        DNode_t *pdtail;
    };
} Queue_t;

#ifdef __cplusplus
}
#endif
#endif //__LQUEUE_H__
