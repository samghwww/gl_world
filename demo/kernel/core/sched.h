
#ifndef __SCHED_H__
#define __SCHED_H__

#include <stdbool.h>
#include "../debug/debug.h"
#include "../exception/exception.h"
#ifndef __API
#define __API
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define SCHED_DBG_EABLED        (0)

#if (defined(SCHED_DBG_EABLED) && SCHED_DBG_EABLED)
#define SCHED_DBG_PRINT(...)    DBG_PRINT(__VA_ARGS__)
#else
#define SCHED_DBG_PRINT(...)
#endif

#define TASK_MAX_NUMBER          ((sizeof(unsigned)<<3) * 8)
#define EVENT_MAX_NUMBER         ((sizeof(unsigned)<<3) * 8)
#define THREAD_MAX_NUMBER        (4)

#define PRIO_HIGHEST            0
#define PRIO_LOWEST             5
#define PRIO_AMOUNT             (PRIO_LOWEST - PRIO_HIGHEST + 1)

typedef void( *Hndlr_t )( void * );
typedef void( *TaskFnc_t )( void * );
typedef void( *TreadFnc_t )( void * );

typedef enum
{
    TSK_TYPE_NULL,
    TSK_TYPE_RT,      //Real time event
    TSK_TYPE_RGLR,    // Regular event
} eTskType_t;

typedef enum
{
    TSK_STA_RUNNING,
    TSK_STA_READY,
    TSK_STA_WAITING,
    TSK_STA_DEAD,
} eTskSta_t;

typedef struct task
{
    struct task *pNext;
    TaskFnc_t fn;
    eTskType_t type;
    eTskSta_t sta;
    void *pArg;
    unsigned tmStamp;
    unsigned char prio;
} sTask_t;

typedef enum
{
    EVT_TYPE_NULL,
    EVT_TYPE_RT,      //Real time event
    EVT_TYPE_RGLR,    // Regular event
    EVT_TYPE_INVALID = EVT_TYPE_NULL
} eEventType_t;

typedef enum
{
    EVT_STA_IVALID,
    EVT_STA_IDLE,
    EVT_STA_HANDLING,
    EVT_STA_QUEUED
} eEventSta_t;

typedef struct event
{
    Hndlr_t        hndlr;
    eEventType_t     type;
    eEventSta_t      sta;
    struct event  *pNext;
    unsigned char  prio;

} sEvent_t;

typedef struct
{
    sTask_t *pTskQueue;
    sTask_t *pTskCurr;
} sTaskMgr_t;

typedef struct
{
    sEvent_t *pEvtQueue;
    sEvent_t *pEvtCurr;
} sEventMgr_t;

typedef struct thread
{
    TreadFnc_t fn;
} sThread_t;

typedef struct
{
    sThread_t *pThreadList;
    sThread_t *pThreadCurr;
    unsigned   threadCnt;
} sThreadMgr_t;


__API eExcpt_t Sched_Init( void );
__API void Sched_Exec( void );

__API eExcpt_t Sched_PutEvent( sEvent_t const *const _pEvt );
__API eExcpt_t Sched_PutTask( sTask_t *const _pTsk );
__API eExcpt_t Sched_PutThread( sThread_t *const _pThrd );


__API sEvent_t const *Sched_GetQueuedEvent( sEvent_t const *const _pEvt );
__API bool Sched_TaskIsQueued( sTask_t const *const _pTsk );
__API bool Sched_EventIsQueued( sEvent_t const *const _pEvt );


DEBUG_CODE(
    void Sched_PrintEventQueue( void );
    void Sched_PrintTaskQueue( void );
);

#ifdef __cplusplus
}
#endif
#endif //__SCHED_H__
