

#include "sched/sched.h"
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

//#define _print(...) printf(__VA_ARGS__)

err_t test_main(void);

int main(int argc, char const** const args)
{
    dbg_msgl("Welcome to L KERNEL WORLD!");

	test_main();
    
	while (true) {
		// Wakeup handle here.
		

		Scheduler();
		// Goto sleep/halt/stop here.

	}
    return 0;
}
