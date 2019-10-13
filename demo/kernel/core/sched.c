
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "sched.h"
#include "../debug/debug.h"


#define STTC_k  //static

const unsigned char FisrtBit0Table[] =
{
    //  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
    0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 4
};
#if 0
const unsigned char FisrtBit0Table[] =
{
    //  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
    1, 2, 1, 3, 1, 2, 1, 4
};
#endif

typedef struct
{
    sEvent_t *pFstEvt;
    sEvent_t *pLstEvt;
} sPrioEvtFstLst_t;

typedef struct
{
    unsigned      idx;
    unsigned char bit;
} sBit0MapCoord_t;

STTC_k sPrioEvtFstLst_t lPrioEvtFstLst[PRIO_AMOUNT] = {0};
STTC_k unsigned  lEventIndexMap[EVENT_MAX_NUMBER / ( sizeof(
                             unsigned ) << 3 )] = {0};
STTC_k sEvent_t    eventQueue[EVENT_MAX_NUMBER];
STTC_k sEventMgr_t eventManager;

STTC_k unsigned   lTaskIndexMap[TASK_MAX_NUMBER / ( sizeof(
                            unsigned ) << 3 )] = {0};
STTC_k sTask_t    taskQueue[TASK_MAX_NUMBER];
STTC_k sTaskMgr_t taskManager;

STTC_k sThread_t  lThreadList[THREAD_MAX_NUMBER];
STTC_k sThread_t *lpThreadCurr;
STTC_k sThreadMgr_t lThreadManager;

eExcpt_t Sched_Init( void )
{
    taskManager.pTskQueue = &taskQueue[0];
    taskManager.pTskCurr  = NULL;

    eventManager.pEvtQueue = &eventQueue[0];
    eventManager.pEvtCurr  = NULL;

    lThreadManager.pThreadList = &lThreadList[0];
    lThreadManager.pThreadCurr = NULL;

    memset( taskQueue, 0x00, sizeof( taskQueue ) );
    memset( eventQueue, 0x00, sizeof( eventQueue ) );
    memset( lThreadList, 0x00, sizeof( lThreadList ) );

    return ERR_SUCCESS;
}

static sBit0MapCoord_t *GetFstBit0Coord( unsigned *const _pMap,
    unsigned const _len, sBit0MapCoord_t *_pCoord )
{
    unsigned tmpIdx = 0;

    _pCoord->idx = 0;
    _pCoord->bit = 0;

    // Check the parameter/argument
    if ( NULL == _pCoord )
    {
        return NULL;
    }
    else
    {
        // go on
    }

    // Find the first bite 0
    for ( tmpIdx = 0; tmpIdx < _len; tmpIdx++ )
    {
        if ( ( unsigned )( ~0 ) == _pMap[tmpIdx] )
        {
            ++_pCoord->idx;
        }
        else
        {
            goto BIT0_HANDLER;
        }
    }
    return _pCoord;

BIT0_HANDLER:
    for ( unsigned i = 0; i < sizeof( unsigned ) << 1; i++ )
    {
        if ( 0x0F == ( ( _pMap[tmpIdx] >> ( i << 2 ) ) & 0x0F ) )
        {
            _pCoord->bit += 4;
        }
        else
        {
            _pCoord->bit += FisrtBit0Table[( _pMap[tmpIdx] >> ( i << 2 ) ) & 0x0F];
            break;
        }
    }
    return _pCoord;
}

static inline void taskPut2Tween( sTask_t *_pLftTsk, sTask_t *const _pTsk )
{
    _pTsk->pNext = _pLftTsk->pNext;
    _pLftTsk->pNext = _pTsk;
}

static inline void taskPut2Trail( sTask_t *_pLftTsk, sTask_t *const _pTsk )
{
    _pTsk->pNext = NULL;
    _pLftTsk->pNext = _pTsk;
}

static void task2Chain( sTask_t *const _pTsk )
{
    sTask_t *pTmpTsk;

    // Event queue is empty.
    if ( NULL == taskManager.pTskCurr )
    {
        // Add firsst event to the event queue
        taskManager.pTskCurr = _pTsk;
        taskManager.pTskCurr->pNext = NULL;
        return;
    }
    else
    {
        // go on
    }

    if ( _pTsk->prio < taskManager.pTskCurr->prio )
    {
        _pTsk->pNext = taskManager.pTskCurr;
        taskManager.pTskCurr = _pTsk;
        return;
    }
    else
    {
        // go no.
    }

    // else
    pTmpTsk = taskManager.pTskCurr;
    // Find the fit/right position.
    // Find the next empty element or the lower than
    // add/insert task.
    while ( pTmpTsk )
    {
        // The next element is not existed.
        if ( NULL == pTmpTsk->pNext )
        {
            taskPut2Trail( pTmpTsk, _pTsk );
            return;
        }
        else // The next element is existed.
        {
            if ( _pTsk->prio >= pTmpTsk->prio &&
                _pTsk->prio < pTmpTsk->pNext->prio )
            {
                taskPut2Tween( pTmpTsk, _pTsk );
                return;
            }
            else // if (_pTsk->prio < pTmpTsk->prio)
            {
                // go on
            }
        }

        pTmpTsk = pTmpTsk->pNext;
    } // while (pTmpTsk)
}


__API eExcpt_t Sched_PutTask( sTask_t *const _pTsk )
{
    if ( NULL == _pTsk )
    {
        return ERR_NULL;
    }
    else
    {
        // go on
    }
    
    if (TSK_TYPE_RT == _pTsk->type)
    {
        if (Sched_TaskIsQueued(_pTsk))
        {
            return ERR_SUCCESS;
        }
        else
        {
            
        }
    }
    else
    {
        
    }

    unsigned tmp;
    sBit0MapCoord_t coord;

    //    static unsigned enterCnt = 0;
    //    SCHED_DBG_PRINT( "TaskPut: %d\r\n", ++enterCnt );

    GetFstBit0Coord( &lTaskIndexMap[0],
        sizeof( lTaskIndexMap ) / sizeof( lTaskIndexMap[0] ), &coord );

    if ( coord.idx < sizeof( lTaskIndexMap ) / sizeof( lTaskIndexMap[0] ) )
    {
        tmp = ( coord.idx * ( sizeof( unsigned ) << 3 ) ) + coord.bit;
        //SCHED_DBG_PRINT("T:%d\r\n", tmp);
        memcpy( &taskManager.pTskQueue[tmp], _pTsk, sizeof( *_pTsk ) );
        // Update/Upgrade the Map table
        lTaskIndexMap[coord.idx] |= 1 << coord.bit;

        //        static unsigned cpyCnt = 0;
        //        SCHED_DBG_PRINT( "TaskCpyCnt: %d, %d\r\n", ++cpyCnt, tmp );

        task2Chain( &taskManager.pTskQueue[tmp] );
    }
    else
    {
        return ERR_NO_MEM;
    }

    return ERR_SUCCESS;
}

static inline void prioEvtFstLstUpdate( sEvent_t *const _pEvt )
{
    lPrioEvtFstLst[_pEvt->prio].pFstEvt =
        !lPrioEvtFstLst[_pEvt->prio].pFstEvt ?
        _pEvt : lPrioEvtFstLst[_pEvt->prio].pFstEvt;

    lPrioEvtFstLst[_pEvt->prio].pLstEvt = _pEvt;
}

static inline void eventPut2Tween( sEvent_t *_pLftEvt, sEvent_t *const _pEvt )
{
    _pEvt->pNext = _pLftEvt->pNext;
    _pLftEvt->pNext = _pEvt;
}

static inline void eventPut2Trail( sEvent_t *_pLftEvt, sEvent_t *const _pEvt )
{
    _pEvt->pNext = NULL;
    _pLftEvt->pNext = _pEvt;
}

static inline void event2Chain( sEvent_t *const _pEvt )
{
    sEvent_t *pTmpEvt;

    if ( _pEvt->prio > PRIO_LOWEST )
    {
        return;
    }
    else
    {
        // go on
    }

    // Event queue is empty.
    if ( NULL == eventManager.pEvtCurr )
    {
        // Add firsst event to the event queue
        _pEvt->pNext = NULL;
        eventManager.pEvtCurr = _pEvt;
        prioEvtFstLstUpdate( _pEvt );
        return;
    }
    else
    {
        // go on
    }

    if ( _pEvt->prio < eventManager.pEvtCurr->prio )
    {
        _pEvt->pNext = eventManager.pEvtCurr;
        eventManager.pEvtCurr = _pEvt;
        prioEvtFstLstUpdate( _pEvt );
        return;
    }
    else
    {
        // go no.
    }

    // else
    pTmpEvt = eventManager.pEvtCurr;
    // Find the fit/right position.
    while ( pTmpEvt )
    {
        // If The next element is not existed.
        if ( NULL == lPrioEvtFstLst[pTmpEvt->prio].pLstEvt->pNext )
        {
            eventPut2Trail( lPrioEvtFstLst[pTmpEvt->prio].pLstEvt, _pEvt );
            prioEvtFstLstUpdate( _pEvt );
            return;
        }
        else // If The next element is existed.
        {
            if ( _pEvt->prio >= lPrioEvtFstLst[pTmpEvt->prio].pLstEvt->prio &&
                _pEvt->prio < lPrioEvtFstLst[pTmpEvt->prio].pLstEvt->pNext->prio )
            {
                eventPut2Tween( lPrioEvtFstLst[pTmpEvt->prio].pLstEvt, _pEvt );
                prioEvtFstLstUpdate( _pEvt );
                return;
            }
            else // Other case(Lower the next event)
            {
                // Continue find/search
            }
        }

        pTmpEvt = lPrioEvtFstLst[pTmpEvt->prio].pLstEvt->pNext;
    } // while (pTmpTsk)
}

__API eExcpt_t Sched_PutEvent( sEvent_t const *const _pEvt )
{
    sBit0MapCoord_t coord;
    unsigned tmp;

    //    static unsigned evtCnt = 0;
    //    SCHED_DBG_PRINT( "enter evtCnt: %d\r\n", ++evtCnt );

    GetFstBit0Coord( &lEventIndexMap[0],
        sizeof( lEventIndexMap ) / sizeof( lEventIndexMap[0] ), &coord );

    if ( coord.idx < sizeof( lEventIndexMap ) / sizeof( lEventIndexMap[0] ) )
    {
        //        static unsigned cpyCnt = 0;
        //        SCHED_DBG_PRINT( "cpyCnt: %d\r\n", ++cpyCnt );

        tmp = ( coord.idx * ( sizeof( unsigned ) << 3 ) ) + coord.bit;
        memcpy( &eventManager.pEvtQueue[tmp], _pEvt, sizeof( *_pEvt ) );

        // Update/Upgrade the Map table
        lEventIndexMap[coord.idx] |= 1 << coord.bit;

        event2Chain( &eventManager.pEvtQueue[tmp] );
    }
    else
    {
        return ERR_NO_MEM;
    }

    return ERR_SUCCESS;
}

__API eExcpt_t Sched_PutThread( sThread_t *const _pThrd )
{
    for ( unsigned i = 0; i < sizeof( lThreadList ) / sizeof( lThreadList[0] );
        i++ )
    {
        if ( NULL == lThreadList[i].fn )
        {
            memcpy( &lThreadList[i], _pThrd, sizeof( *_pThrd ) );
            if ( NULL == lpThreadCurr )
            {
                lpThreadCurr = &lThreadList[i];
            }
            else
            {
                // go on
            }

            ++lThreadManager.threadCnt;
            return ERR_SUCCESS;
        }
        else
        {
            // Continue
        }
    }

    return ERR_NO_MEM;
}

__API eEventSta_t Sched_EventSta( sEvent_t const *const _pEvt )
{
    sEvent_t *pEvt = eventManager.pEvtCurr;

    while ( pEvt->hndlr )
    {
        if ( pEvt->hndlr == _pEvt->hndlr )
        {
            return pEvt->sta;
        }
        else
        {
            // Continue search
        }
    }
    return EVT_STA_IVALID;
}

__API eEventType_t Sched_EventType( sEvent_t const *const _pEvt )
{
    sEvent_t *pEvt = eventManager.pEvtCurr;

    while ( pEvt->hndlr )
    {
        if ( pEvt->hndlr == _pEvt->hndlr )
        {
            return pEvt->type;
        }
        else
        {
            // Continue search
        }
    }
    return EVT_TYPE_INVALID;
}

__API sEvent_t const *Sched_GetQueuedEvent( sEvent_t const *const _pEvt )
{
    sEvent_t *pEvt = eventManager.pEvtCurr;

    while ( pEvt->hndlr )
    {
        if ( pEvt->hndlr == _pEvt->hndlr )
        {
            return pEvt;
        }
        else
        {
            // Continue search
        }
    }
    return ( sEvent_t * )NULL;
}

__API bool Sched_TaskIsQueued( sTask_t const *const _pTsk )
{
    sTask_t *pTsk = taskManager.pTskCurr;

    while ( pTsk )
    {
        if ( pTsk->fn == _pTsk->fn )
        {
            return true;
        }
        else
        {
            // Continue search
            pTsk = pTsk->pNext;
        }
    }
    return false;
}

__API bool Sched_EventIsQueued( sEvent_t const *const _pEvt )
{
    sEvent_t *pEvt = eventManager.pEvtCurr;

    while ( pEvt->hndlr )
    {
        if ( pEvt->hndlr == _pEvt->hndlr )
        {
            return true;
        }
        else
        {
            // Continue search
        }
    }
    return false;
}

static void eventSched( void )
{
    while ( eventManager.pEvtCurr )
    {
        eventManager.pEvtCurr->sta   = EVT_STA_HANDLING;
        eventManager.pEvtCurr->hndlr( NULL );

        unsigned register tmp;
        tmp = eventManager.pEvtCurr - &eventManager.pEvtQueue[0];

        lEventIndexMap[ tmp / ( sizeof( unsigned ) << 3 ) +
                tmp % ( sizeof( unsigned ) << 3 ) ? 1 : 0 ]  &= ~
                ( 1 << ( tmp % ( sizeof( unsigned ) << 3 ) ) );

        eventManager.pEvtCurr = eventManager.pEvtCurr->pNext;
    }
}

static void taskSched( void )
{
    while ( taskManager.pTskCurr )
    {
        eventSched();
        taskManager.pTskCurr->sta = TSK_STA_RUNNING;
        taskManager.pTskCurr->fn( taskManager.pTskCurr->pArg );

        unsigned register tmp;
        tmp = taskManager.pTskCurr - &taskManager.pTskQueue[0];

        lTaskIndexMap[ tmp / ( sizeof( unsigned ) << 3 ) +
                tmp % ( sizeof( unsigned ) << 3 ) ? 1 : 0 ]  &= ~
                ( 1 << ( tmp % ( sizeof( unsigned ) << 3 ) ) );
        taskManager.pTskCurr = taskManager.pTskCurr->pNext;
    }
}

static void threadSched( void )
{
    unsigned static thrdIdx = 0;
    if ( lpThreadCurr ) {
        lpThreadCurr->fn( NULL );
        thrdIdx = ++thrdIdx < lThreadManager.threadCnt ? thrdIdx : 0;
        lpThreadCurr = &lThreadList[thrdIdx];
    }
    else {
        // go on
    }
}

DEBUG_CODE(
    void Sched_PrintEventQueue( void )
{
    static unsigned cnt = 0;
    sEvent_t *pTmpEvt = eventManager.pEvtCurr;
    if ( pTmpEvt ) {
        DBG_PRINT( "Event:\r\n" );
        DBG_PRINT( "Index: Prio\r\n" );
    }

    while ( pTmpEvt ) {
        DBG_PRINT( "%04d: %d\r\n", cnt++, pTmpEvt->prio );
        pTmpEvt = pTmpEvt->pNext;
    }
}
);

DEBUG_CODE(
    void Sched_PrintTaskQueue( void )
{
    static unsigned cnt = 0;
    sTask_t *pTmpTsk = taskManager.pTskCurr;

    if ( pTmpTsk ) {
        DBG_PRINT( "Task:\r\n" );
        DBG_PRINT( "Index: Prio\r\n" );
    }

    while ( pTmpTsk ) {
        DBG_PRINT( "%04d: %d\r\n", cnt++, pTmpTsk->prio );
        pTmpTsk = pTmpTsk->pNext;
    }
}
);

DEBUG_CODE(
    void Sched_PrintPrioEvtFstLst( void )
{
    DBG_PRINT( "PrioEvtFstLst:\r\n" );
    for ( unsigned i = 0;
        i < sizeof( lPrioEvtFstLst ) / sizeof( lPrioEvtFstLst[0] ); i++ ) {
        DBG_PRINT( "%04d:%08X,%08X\r\n", i, lPrioEvtFstLst[i].pFstEvt,
            lPrioEvtFstLst[i].pLstEvt );
    }
}
);

__API void Sched_Exec( void )
{
    eventSched();
    taskSched();
    threadSched();
}
