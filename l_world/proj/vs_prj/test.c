

#include "../../kernel/task.h"
#include "../../inc/err.h"
#include "../../inc/debug.h"

#include <stdlib.h>

void taskFnc(void* _parg)
{
	dbg_msgl("%s", __func__);
}

Task_t task = {
	NULL,
	taskFnc,
	NULL,
	TASK_STA_IDLE,
	TASK_PRIO_LOWEST,
};

err_t test_main(void)
{
	Task_Add(&task);

	return ERR_SUCCEED;
}
