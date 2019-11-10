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

#include "../lib/queue.h"
#include "../inc/err.h"
#include "../inc/typedef.h"

//#include <limits.h>

#ifdef __cplusplus
extern "C" {
#endif

#define TASK_PRIO_MAX                       32

#define TASK_PRIO_AMOUNT_DEFAULT            6

#define BIT_CNT_OF_BYTE                     (sizeof(unsigned char)<<3)
#define BIT_CNT_OF_BYTES(bc)                (BIT_CNT_OF_BYTE * (bc))

#if (defined(CFG_TASK_PRIO_AMOUNT) && CFG_TASK_PRIO_AMOUNT)
    #define TASK_PRIO_AMOUNT        CFG_TASK_PRIO_AMOUNT
#else
    #define TASK_PRIO_AMOUNT        TASK_PRIO_AMOUNT_DEFAULT
#endif

#if (TASK_PRIO_AMOUNT >= TASK_PRIO_MAX)
    #error TASK_PRIO_AMOUNT configuration is error, please check again!
#endif

// Task entry function type.
typedef void (*TaskFnc_t)(void *parg);
// Task priority data type.
typedef enum {
    TASK_PRIO_LEVEL_BASE,
    TASK_PRIO_LEVEL_0   = TASK_PRIO_LEVEL_BASE,
    TASK_PRIO_LEVEL_1,
    TASK_PRIO_LEVEL_2,
    TASK_PRIO_LEVEL_3,
    TASK_PRIO_LEVEL_4,
    TASK_PRIO_LEVEL_5,
    TASK_PRIO_INVALID   = TASK_PRIO_AMOUNT,

    TASK_PRIO_LEVEL_MIN = TASK_PRIO_LEVEL_BASE,
    TASK_PRIO_LEVEL_MAX = TASK_PRIO_INVALID - 1,

    TASK_PRIO_LOWEST    = TASK_PRIO_LEVEL_MAX,
    TASK_PRIO_HIGHEST   = TASK_PRIO_LEVEL_MIN,

    TASK_PRIO_NUMBER    = TASK_PRIO_INVALID,
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
    TaskPrio_t   prio; // Task priority.
} Task_t;

typedef struct {
    ux_t        rdyPrioRecord;
    Queue_t     queueArray[TASK_PRIO_AMOUNT];
} TaskManager_t;

extern TaskManager_t TaskManager;

static inline ux_t Task_CZL(ux_t n)
{
    sx_t c = BIT_CNT_OF_BYTES(sizeof(n));
    while (--c >= 0) {
        if ((n>>c)&1) {
            break;
        }
    }
    return (BIT_CNT_OF_BYTES(sizeof(n)) - 1) - c;
}

// Call/Invoke task entry function.
static inline void Task_CallFunc(Task_t const * const _ptsk)
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

static inline void Task_SetRdyPrioRecord(TaskPrio_t _rdyPrio)
{
    TaskManager.rdyPrioRecord |= ((ux_t)1) << ((BIT_CNT_OF_BYTES(sizeof(ux_t)) - 1) - _rdyPrio);
}

static inline void Task_ClrRdyPrioRecord(TaskPrio_t _rdyPrio)
{
    TaskManager.rdyPrioRecord &=~ (((ux_t)1) << ((BIT_CNT_OF_BYTES(sizeof(ux_t)) - 1) - _rdyPrio));
}

static inline TaskPrio_t Task_GetReadyHighestPrio(void)
{
    return Task_CZL(TaskManager.rdyPrioRecord);
}

Task_t* Task_GetHighester(void);
err_t Task_Add(Task_t* const _ptskPut);

#ifdef __cplusplus
}
#endif
#endif //TASK_H_
