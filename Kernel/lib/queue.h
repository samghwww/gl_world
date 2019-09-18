#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdbool.h>

#include "../exception/exception.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CFG_QUEUE_CNTXT_TYPE

#ifdef CFG_QUEUE_CNTXT_TYPE
typedef struct
{
    void ( *fn )( void * );
    void *pArg;
} QueueCntxt_t;
#endif

#ifndef CFG_QUEUE_CNTXT_TYPE
typedef unsigned char QueueCntxt_t;
#endif
typedef unsigned long ElePrio_t;


typedef struct QueueEle
{
    QueueCntxt_t cntxt;    // Element context
    ElePrio_t    prio;     // Element priority
} SQueueEle_t;

typedef struct Node
{
    SQueueEle_t e;        // Element Content
    struct Node *next;  // The pointer of the next element
} SNode_t;

typedef struct Queue
{
    void    *pCntxt;    // The pointer all context
    ElePrio_t    *pPrioCnt;  // The pointer of the arry about element priority
    long     sz;        // Context buffer memery buffer size/ element count
    SNode_t *head;      // The head of the queue
    SNode_t *tail;      // The tail of the queue
} SQueue_t;


eExcpt_t Queue_Create( SQueue_t *_pQueue, SQueue_t *_pQueueMem,
    const long _queueSz );
eExcpt_t Queue_Put( SQueue_t *_pQueue, const SQueueEle_t *_pe );
SQueueEle_t Queue_Pop( SQueue_t *_pQueue );
bool Queue_IsEmpty( const SQueue_t *_pQueue );
eExcpt_t Queue_Del( SQueue_t *_pQueue, const SQueueEle_t *_pe );
SNode_t *Queue_Search( SQueue_t *_pQueue, const SQueueEle_t *_pe );


#ifdef __cplusplus
}
#endif
#endif //__QUEUE_H__
