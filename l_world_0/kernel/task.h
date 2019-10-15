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

typedef unsigned char TaskPrio_t;
typedef struct task {
  struct task* pnxt;
  void (*pfnc)(void*);
  void* parg;
  TaskPrio_t prio;
} Task_t;


err_t Task_Add(Task_t* const _ptask);

#ifdef __cplusplus
}
#endif
#endif //TASK_H_
