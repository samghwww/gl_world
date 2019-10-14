/*******************************************************************************
 Copyright (C) 2019 Sam He(HeGuanglin)

 History:
    Date        Author          Notes
 2019/10/07     Sam He          The first version

 Discription:
    Definition/declaratino of l system kernel handle task.
 
*******************************************************************************/

#ifndef TASK_H_
#define TASK_H_

#ifdef __cplusplus
extern "C" {
#endif

// Task entry function type.
typedef void (*TaskFnc_t)(void *parg);
// Task priority data type.
typedef unsigned char TaskPrio_t;

// Task control block data structure.
typedef struct task {
    struct task *pnxt; // Point to the next task control block.
    TaskFnc_t   *pfnc; // Task entry function.
    void        *parg; // Task entry function parameter/argument pointer.
    TaskPrio_t   prio; // Task priority.
} Task_t;

#ifdef __cplusplus
}
#endif
#endif //TASK_H_
