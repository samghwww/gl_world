/*******************************************************************************
Copyright (C) 2019 Sam He(HeGuanglin)

Discription:
    Definition/declaratino of l system kernel handle task.
History:
    Date        Author          Notes
 2019/10/07     Sam He          The first version
 
*******************************************************************************/

#ifndef TASK_H_
#define TASK_H_

#include "../inc/err.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TASK_INNER_PRIORITY_ENABLED			1

// Task entry function type.
typedef void (*TaskFnc_t)(void *parg);
// Task priority data type.
typedef enum {
	TASK_PRIO_LEVEL_BASE,
	TASK_PRIO_LEVEL_0	= TASK_PRIO_LEVEL_BASE,
	TASK_PRIO_LEVEL_1,
	TASK_PRIO_LEVEL_2,
	TASK_PRIO_LEVEL_3,
	TASK_PRIO_LEVEL_4,
	TASK_PRIO_LEVEL_5,
	TASK_PRIO_INVALID,

	TASK_PRIO_LEVEL_MIN = TASK_PRIO_LEVEL_BASE,
	TASK_PRIO_LEVEL_MAX = TASK_PRIO_INVALID - 1,

    TASK_PRIO_LOWEST	= TASK_PRIO_LEVEL_MAX,
	TASK_PRIO_HIGHEST	= TASK_PRIO_LEVEL_MIN,
	
    TASK_PRIO_NUMBER	= TASK_PRIO_INVALID,
    TASK_PRIO_AMOUNT	= TASK_PRIO_NUMBER,
} TaskPrio_t;
// Task state/status type define.
typedef enum {
    TASK_STA_IDLE,
    TASK_STA_READY,
    TASK_STA_RUNNING,
    TASK_STA_INVALID,
} TaskSta_t;

// Task control block data structure.
typedef struct task {
    struct task *pnxt; // Point to the next task control block.
    TaskFnc_t    pfnc; // Task entry function.
    void        *parg; // Task entry function parameter/argument pointer.
    TaskSta_t    sta;  // Task state/status.
#if TASK_INNER_PRIORITY_ENABLED
	TaskPrio_t   prio; // Task priority.
#endif // TASK_INNER_PRIORITY_ENABLED
} Task_t;

static inline void Task_EntryFuncCaller(Task_t const * const _ptsk)
{
    if (_ptsk->pfnc) {
        _ptsk->pfnc(_ptsk->parg);
    }
}

static inline void Task_SetSta(Task_t * const _ptsk, TaskSta_t const _tskSta)
{
    _ptsk->sta = _tskSta;
}

static inline TaskSta_t Task_GetSta(Task_t const * const _ptsk)
{
    return _ptsk->sta;
}


Task_t* Task_GetHighester(void);
err_t Task_Add(Task_t* const _ptskPut);

#ifdef __cplusplus
}
#endif
#endif //TASK_H_
