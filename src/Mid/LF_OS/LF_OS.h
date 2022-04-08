#pragma once

#include "stm32f4xx_hal.h"

#define UINT8  uint8_t
#define UINT16 uint16_t
#define UINT32 uint32_t

typedef void* (*l_func_t)(uint8_t*, void*);

typedef enum
{
	X_L_TSK_TASK_MODE_DISABLE = 0,
	X_L_TSK_TASK_MODE_SPTIMES,
	X_L_TSK_TASK_MODE_ENABLE,
}l_tsk_task_mode_t;

typedef struct
{
	l_func_t				p_func;
	uint16_t					period;
	uint16_t					cnt;
	l_tsk_task_mode_t		enable_mode;
	uint16_t					exec_times;
	uint16_t					remain_times;
}l_tsk_task_t;

void x_l_tsk_init(void);
void x_l_tsk_set_task(l_tsk_task_t task, uint8_t task_id);
void x_l_tsk_reset_task(uint8_t task_id, l_func_t func, l_tsk_task_mode_t mode, uint16_t total_time, uint16_t period);
void x_l_tsk_task_exec(uint8_t* argc, void* argv);



