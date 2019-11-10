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
    return &TaskManager.queueArray[_prio];
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

static inline bool task_prioEmpty(TaskPrio_t _prio)
{
    return (NULL == task_getPriorityNQueue(_prio)->phead) ? true : false;
}

// Get the highest priority task.
Task_t *Task_GetHighester(void)
{
    TaskPrio_t hightestPrio = Task_GetReadyHighestPrio();
    Task_t *ptsk = Queue_GetHead(task_getPriorityNQueue(hightestPrio));
    if (ptsk) {
        if (NULL == ptsk->pnxt) {
            Task_ClrRdyPrioRecord(hightestPrio);
        }
    }
    else {
        Task_ClrRdyPrioRecord(hightestPrio);
    }
    return ptsk;
}

err_t Task_Add(Task_t* const _ptskPut)
{
    err_t errCode;
    if (NULL == _ptskPut) {
        return ERR_NULL;
    }
    if (!task_checkPriorityValid(_ptskPut->prio)) {
        return ERR_INVALID_PARAM;
    }
    errCode = Queue_Add(task_getPriorityNQueue(_ptskPut->prio), _ptskPut);
    if (ERR_SUCCEED == errCode) {
        Task_SetRdyPrioRecord(_ptskPut->prio);
    }
    return errCode;
}

err_t Task_Del(Task_t const * const _ptskDel)
{
    err_t errCode;
    if (NULL == _ptskDel) {
        return ERR_NULL;
    }
    errCode = Queue_Delete(task_getPriorityNQueue(_ptskDel->prio), _ptskDel);
    if (ERR_SUCCEED == errCode) {
        if (task_prioEmpty(_ptskDel->prio)) {
            Task_ClrRdyPrioRecord(_ptskDel->prio);
        }
    }
    return errCode;
}
