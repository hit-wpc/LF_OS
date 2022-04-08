#include "LF_OS.h"

#define L_TSK_TASK_NUM			8
static __IO l_tsk_task_t		x_l_cb_task[L_TSK_TASK_NUM];

void x_l_tsk_init(void)
{
	//  fill x_l_cb_task with 0x00
	for (UINT16 i = 0; i < sizeof(x_l_cb_task); i++)
	{
		*(UINT8*)((UINT32)x_l_cb_task + i) = 0;
	}
}

void x_l_tsk_set_task(l_tsk_task_t task, UINT8 task_id)
{
	x_l_cb_task[task_id] = task;
}

void x_l_tsk_reset_task(UINT8 task_id, l_func_t func, l_tsk_task_mode_t mode, UINT16 total_time, UINT16 period)
{
	x_l_cb_task[task_id].enable_mode = mode;
	x_l_cb_task[task_id].p_func = func;
	
	//  reset SPTIME parameters
	x_l_cb_task[task_id].remain_times = total_time;
	x_l_cb_task[task_id].exec_times = 0;
	
	//	reset PERIOD parameters
	x_l_cb_task[task_id].period = period;
	x_l_cb_task[task_id].cnt = 0;
}

void x_l_tsk_task_exec(UINT8* argc, void* argv)
{
	for (UINT16 i = 0; i < L_TSK_TASK_NUM; i++)
	{
		//  null pointer or disabled task
		if ((!x_l_cb_task[i].p_func) || (x_l_cb_task[i].enable_mode == X_L_TSK_TASK_MODE_DISABLE)) 
		{
			continue;
		}
		
		//  SPTIMES mode
		if (x_l_cb_task[i].enable_mode == X_L_TSK_TASK_MODE_SPTIMES)
		{
			//  check if period is met
			if (x_l_cb_task[i].cnt == x_l_cb_task[i].period)
			{
				//  task has dead, execute one JB
				if (x_l_cb_task[i].remain_times == 0)
				{
					continue;
				}
				else
				{
					x_l_cb_task[i].cnt = 0;
					x_l_cb_task[i].exec_times   ++;				//  record executed time
					x_l_cb_task[i].remain_times --;				//  update remaining time
					x_l_cb_task[i].p_func(argc, argv);			//  call function
				}
			}
			else
			{
				x_l_cb_task[i].cnt ++;
			}
		}
		
		//  ENABLE mode
		else if (x_l_cb_task[i].enable_mode == X_L_TSK_TASK_MODE_ENABLE)
		{
			//  check if period is met
			if (x_l_cb_task[i].cnt == x_l_cb_task[i].period)
			{
				x_l_cb_task[i].cnt = 0;
				x_l_cb_task[i].exec_times++; 				//  record executed time
//				x_l_cb_task[i].remain_times--; 				//  update remaining time
				x_l_cb_task[i].p_func(argc, argv); 			//  call function
			}
			else
			{
				x_l_cb_task[i].cnt++;
			}
		}
		else
		{
			
		}
	}
}

