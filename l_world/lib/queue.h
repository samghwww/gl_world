/*******************************************************************************
Copyright (C) 2019 Sam He(HeGuanglin)

Discription:
    Definnition of queue.

History:
    Date        Author          Notes
 2019/10/06     Sam He          The first version

*******************************************************************************/

#ifndef QUEUE_H_
#define QUEUE_H_

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

typedef struct {
    SNode_t *head;
    SNode_t *tail;
} Queue_t;

err_t Queue_Init(void);
err_t Queue_ChgHead(Queue_t * const _pq, void *_p);
err_t Queue_AddTail(Queue_t * const _pq, void *_p);
err_t Queue_Insert(void *_pb, void *_pin);
err_t Queue_Search(Queue_t const * const _pq, void *_psrch);

void *Queue_PeekHead(Queue_t * const _pq);
void *Queue_PeekTail(Queue_t * const _pq);
void *Queue_GetHead(Queue_t * const _pq);
void *Queue_GetTail(Queue_t * const _pq);

#ifdef __cplusplus
}
#endif
#endif //QUEUE_H_
