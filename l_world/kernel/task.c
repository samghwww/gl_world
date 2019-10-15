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

#define STTC    static

STTC Queue_t TaskQueueArry[TASK_PRIO_AMOUNT];

static inline sz_t task_getQueueSize(void)
{
	return ARRY_SIZE(TaskQueueArry); //TASK_PRIO_AMOUNT;
}

static inline Queue_t *task_getPriorityNHeader(TaskPrio_t _prio)
{
	return &TaskQueueArry[_prio];
}

Task_t *Task_GetHighester(void)
{
    for (sz_t idx = 0; idx < ARRY_SIZE(TaskQueueArry); idx++) {
        if (!Queue_IsEmpty(&TaskQueueArry[idx])) {
            return (Task_t*)Queue_GetHead(&TaskQueueArry[idx]);
        }
    }
    return NULL;
}

err_t Task_Add(Task_t* const _ptskPut)
{
	return Queue_Add(task_getPriorityNHeader(_ptskPut->prio), _ptskPut);
}

err_t Task_Del(Task_t const * const _ptskDel)
{
	return Queue_Delete(task_getPriorityNHeader(_ptskDel->prio), _ptskDel);
}
