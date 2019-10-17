

#include "task.h"
#include "sched/sched.h"

#include "../mm/mm.h"
#include "../inc/debug.h"
#include "../inc/err.h"


#include <stdbool.h>
#include <conio.h>

#define PLATFORM_BARE               0
#define PLATFORM_WINDOWS            1
#define PLATFORM_LINUX              2
#define PLATFORM_UNIX               3
#define PLATFORM_VXWORKS            4
#define PLATFORM_FREERTOS           5
#define PLATFORM_RTTHREAD           6
#define PLATFORM_LISTOS             7
#define PLATFORM_UCOS               8

#define PLATFORM                    PLATFORM_WINDOWS

#if (PLATFORM == PLATFORM_WINDOWS)
#if 0
static inline int getch(void) {
    return _getch();
}
#else
#define getch(...)  _getch()
static inline void pause(void) {
    dbg_info("Please press any ENTER key to exit......");
    (void)_getch();
}
#endif
#else

#endif

void task0_func(void* _parg)
{
	dbg_msgl("The first task reached.");
}

void task1_func(void* _parg)
{
	dbg_msgl("The second task reached.");
}

void task2_func(void* _parg)
{
	dbg_msgl("The third task reached.");
}

Task_t task0 = {
	.pnxt = NULL,
	.pfnc = task0_func,
	.parg = NULL,
	.sta  = TASK_STA_READY,
	.prio = TASK_PRIO_LOWEST,
};

Task_t task1 = {
	.pnxt = NULL,
	.pfnc = task1_func,
	.parg = NULL,
	.sta = TASK_STA_READY,
	.prio = TASK_PRIO_LOWEST,
};

Task_t task2 = {
	.pnxt = NULL,
	.pfnc = task2_func,
	.parg = NULL,
	.sta = TASK_STA_READY,
	.prio = TASK_PRIO_HIGHEST,
};


int main(int argc, char const** const args)
{
    dbg_msgl("Welcome to L System Kernel WORLD!");

    // Initialization function here.
    MM_INIT_DEF();

	Task_Add(&task0);
	Task_Add(&task1);
	Task_Add(&task2);

	while (true) {
		// Wakeup form sleep(deep/light) handle here.
		
		Scheduler();
		// Goto sleep/halt/stop here, and when system core wakeup,
		// code will execute from here.
	}
	// System should never reach here.
}
