/*******************************************************************************
 Copyright (C) 2019 Sam He(HeGuanglin)

 History:
    Date        Author          Notes
 2019/10/06     Sam He          The first version

 Discription:
    Implementation of the system task here.
 
*******************************************************************************/

#include "task.h"

#include "../lib/queue.h"
#include "../inc/err.h"

#define STTC    static

// Task queue that temperaryly save the task want to add to
// the task queue ready. these task will be sorted and put/take in
// the ready task queue(TaskQueueReady).
STTC Queue_t TaskQueueAdded;

// Task queue have sort for call/executable/schedule
// When scheduler system schedule tas, it will get task
// from this task queue to run.
STTC Queue_t TaskQueueReady;

err_t Task_SetPriority(Task_t * const _ptask, TaskPrio_t const _newTaskPrio)
{
    _ptask->prio = _newTaskPrio;
}

TaskPrio_t Task_GetPriority(Task_t * const _ptask)
{
    return _ptask->prio;
}

err_t Task_SetArgument(Task_t * const _ptask, void const * const _parg)
{
    _ptask->parg = _parg;
    return ERR_SUCCEED;
}


err_t Task_Add(Task_t * const _ptask)
{
    Queue_Add(&TaskQueueAdded, _ptask);
}

err_t Task_Remove(Task_t * const _ptask)
{
    Queue_Delete(&TaskQueueAdded, _ptask);
}

