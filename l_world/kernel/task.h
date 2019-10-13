/*******************************************************************************
 Copyright (C) 2019 Sam He(HeGuanglin)

 History:
    Date        Author          Notes
 2019/10/07     Sam He          The first version

 Discription:
    Definition/declaratino of l system kernel handle task.
 
*******************************************************************************/

typedef unsigned char TaskPri_t;
typedef struct task {
  struct task* nxt;
  void (*fnc)(void*);
  void* arg;
  TaskPri_t pri;
} Task_t;

