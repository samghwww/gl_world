/*******************************************************************************
Copyright (C) 2019 Sam He(HeGuanglin)

Discription:
    Definition/declaratino of l system kernel scheduler.
    
History:
    Date        Author          Notes
 2019/10/07     Sam He          The first version

*******************************************************************************/

#ifndef SCHED_H_
#define SCHED_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tcb {
    struct tcb *prv;
    struct tcb *nxt;

} TCB_t;

#ifdef __cplusplus
}
#endif
#endif //SCHED_H_
