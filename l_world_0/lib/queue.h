/*******************************************************************************
 Copyright (C) 2019 Sam He(HeGuanglin)

 History:
    Date        Author          Notes
 2019/10/06     Sam He          The first version

 Discription:
    Definnition of queue.
 
*******************************************************************************/

#ifndef QUEUE_H_
#define QUEUE_H_

#include "list.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct queue {
    union {
        void *phead;
        SNode_t *pshead;
        DNode_t *pdhead;
    };
    union {
        void *ptail;
        SNode_t *pstail;
        DNode_t *pdtail;
    };
} Queue_t;



#ifdef __cplusplus
}
#endif
#endif //QUEUE_H_
