
#include <stdio.h>
//#include <strinig.h>
#include <math.h>

#include "task.h"
#include "sched/sched.h"

#include "../lib/fifo.h"
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
#define MM_TEST_ALLOC(sz)                       \
    char* const m##sz = (char*)malloc(sz);      \
    if (NULL != m##sz) {                        \
        dbg_msgl("m%d Memory allocate successful!", sz);\
        memset(m##sz, sz, sz);                  \
    } else {                                    \
        dbg_msgl("m%d Memory allocate failure???", sz); \
    }

#define MM(sz)              m##sz
    //char* const ptmp = (char*)malloc(100);

    MM_TEST_ALLOC(500);
    MM_TEST_ALLOC(100);
    free(MM(500));
}

void task1_func(void* _parg)
{
	dbg_msgl("The second task reached.");
}

void task2_func(void* _parg)
{
	dbg_msgl("The third task reached.");
    Fifo_t* pfifo;
    if (ERR_SUCCEED == Fifo_Create(&pfifo, 1024)) {
        char buf[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        Fifo_Write(pfifo, buf, sizeof(buf));

    }
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
