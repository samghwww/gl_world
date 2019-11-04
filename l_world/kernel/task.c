/*******************************************************************************
Copyright (C) 2019 Sam He(HeGuanglin)

Discription:
    Implementation of the system task here.

History:
    Date        Author          Notes
 2019/10/06     Sam He          The first version
 
*******************************************************************************/

#include "task.h"

#include "../lib/queue.h"
#include "../inc/macrodef.h"
#include "../inc/typedef.h"

#include <stdlib.h>

#define STTC    //static

STTC TaskManager_t TaskManager;


// 0B0000 0000
// 0B0000 0001
// 0B0000 0010
// 0B0000 0100
// 0B0000 1000
// 0B0001 0000
// 0B0010 0000
// 0B0100 0000
// 0B1000 0000

static inline bool task_checkPriorityValid(TaskPrio_t _prio)
{
    return (0 <= _prio && _prio < TASK_PRIO_MAX);
}

// Get the specified priority N queue.
// Return the corresponding queue pointer of priority N.
static inline Queue_t *task_getPriorityNQueue(TaskPrio_t _prio)
{
    return (Queue_t*)TaskManager.queueArray;
}

// Update the highest prority for next time task switch;
// Usually, this function would be called/invoked by scheduler.
// or another word, be called/invoked after execute/run/handle a task.
static inline void task_updateHighestPriority(void)
{
    TaskPrio_t prio = TASK_PRIO_HIGHEST;
    for ( ; prio <= TASK_PRIO_LOWEST; prio++) {
        if (!Queue_IsEmpty(task_getPriorityNQueue(prio))) {
            Task_SetReadyHighestPrio(prio);
            return;
        }
    }
    Task_SetReadyHighestPrio(TASK_PRIO_LOWEST);
}

static inline TaskPrio_t task_getHighestPriority(void)
{
    return 0;
}

// Get the highest priority task.
Task_t *Task_GetHighester(void)
{
    return (Task_t*)TaskManager.queueArray[task_getHighestPriority()].phead;
    #if 0
    
    return NULL;
    #endif
}

err_t Task_Add(Task_t* const _ptskPut)
{
    if (NULL == _ptskPut) {
        return ERR_NULL;
    }
    if (!task_checkPriorityValid(_ptskPut->prio)) {
        return ERR_INVALID_PARAM;
    }
    return Queue_Add(task_getPriorityNQueue(_ptskPut->prio), _ptskPut);
}

err_t Task_Del(Task_t const * const _ptskDel)
{
    if (NULL == _ptskDel) {
        return ERR_NULL;
    }
    return Queue_Delete(task_getPriorityNQueue(_ptskDel->prio), _ptskDel);
}
