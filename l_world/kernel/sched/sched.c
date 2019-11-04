/*******************************************************************************
Copyright (C) 2019 Sam He(HeGuanglin)

Discription:
    Implementation of the l system kernel scheduler.

History:
    Date        Author          Notes
 2019/10/07     Sam He          The first version
 
*******************************************************************************/

#include "../../inc/debug.h"
#include "../../inc/err.h"

#include "../event.h"
#include "../task.h"
#include "../../lib/queue.h"

// L operate system kernel scheduler.
// All task and event should be handled here.
void Scheduler(void)
{
    Task_t *ptsk;
    while (ptsk = Task_GetHighester()) {
        if (!Event_IsEmpty()) {
            Event_Handler(); // Handle event here.
        }
        Task_SetSta(ptsk, TASK_STA_RUNNING);
        Task_CallFunc(ptsk);
        Task_SetSta(ptsk, TASK_STA_IDLE);
    }
}