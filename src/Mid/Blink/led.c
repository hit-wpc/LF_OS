#include "led.h"

__IO const uint32_t x_l_blink_mode_a = 0x55555555;
__IO const uint32_t x_l_blink_mode_b = 0x50505050;
__IO const uint32_t x_l_blink_mode_c = 0x0A0A0A0A;

x_l_blink_init_t x_l_red_blink_init;
x_l_blink_init_t x_l_yellow_blink_init;
x_l_blink_init_t x_l_blue_blink_init;
x_l_blink_init_t x_l_green_blink_init;

uint8_t x_l_blink_set(x_l_blink_init_t* x_l_blink_init, GPIO_TypeDef* led_port, uint32_t led_pin, x_l_blink_mode_t x_l_blink_mode)
{
	if (x_l_blink_init->x_l_blink_mode != x_l_blink_mode)
	{
		
		x_l_blink_init->led_pin        = led_pin;
		x_l_blink_init->led_port       = led_port;
		x_l_blink_init->x_l_blink_mode = x_l_blink_mode;
		return 0;
	}
}

uint8_t x_l_blink_start(x_l_blink_init_t* x_l_blink_init)
{
	if (x_l_blink_init->x_l_blink_mode == X_L_LED_BLINK_MODE_A)
	{
		uint8_t mode_a_status = 0;
		mode_a_status = (((x_l_blink_mode_a >> (x_l_blink_init->blink_ticks)) & 0x00000001) == 1) ? 1 : 0;
		x_l_blink_init->blink_ticks++;
		if (x_l_blink_init->blink_ticks >= 31)
		{
			x_l_blink_init->blink_ticks = 0;
		}
		if (mode_a_status == 1)
		{
			//WPC_LED_SET_L;
			HAL_GPIO_WritePin(x_l_blink_init->led_port,x_l_blink_init->led_pin,GPIO_PIN_SET);
		}
		else
		{
			//WPC_LED_SET_H;
			HAL_GPIO_WritePin(x_l_blink_init->led_port,x_l_blink_init->led_pin,GPIO_PIN_RESET);
		}
	}
	else if (x_l_blink_init->x_l_blink_mode == X_L_LED_BLINK_MODE_B)
	{
		uint8_t mode_b_status = 0;
		mode_b_status = (((x_l_blink_mode_b >> (x_l_blink_init->blink_ticks)) & 0x00000001) == 1) ? 1 : 0;
		x_l_blink_init->blink_ticks++;
		if (x_l_blink_init->blink_ticks >= 31)
		{
			x_l_blink_init->blink_ticks = 0;
		}
		if (mode_b_status == 1)
		{
			//WPC_LED_SET_L;
			HAL_GPIO_WritePin(x_l_blink_init->led_port,x_l_blink_init->led_pin,GPIO_PIN_SET);
		}
		else
		{
			//WPC_LED_SET_H;
			HAL_GPIO_WritePin(x_l_blink_init->led_port,x_l_blink_init->led_pin,GPIO_PIN_RESET);
		}
	}
	else if (x_l_blink_init->x_l_blink_mode == X_L_LED_BLINK_MODE_C)
	{
		uint8_t mode_c_status = 0;
		mode_c_status = (((x_l_blink_mode_c >> (x_l_blink_init->blink_ticks)) & 0x00000001) == 1) ? 1 : 0;
		x_l_blink_init->blink_ticks++;
		if (x_l_blink_init->blink_ticks >= 31)
		{
			x_l_blink_init->blink_ticks = 0;
		}
		if (mode_c_status == 1)
		{
			//WPC_LED_SET_L;
			HAL_GPIO_WritePin(x_l_blink_init->led_port,x_l_blink_init->led_pin,GPIO_PIN_SET);
		}
		else
		{
			//WPC_LED_SET_H;
			HAL_GPIO_WritePin(x_l_blink_init->led_port,x_l_blink_init->led_pin,GPIO_PIN_RESET);
		}
	}
	else if (x_l_blink_init->x_l_blink_mode == X_L_LED_ON)
	{
		HAL_GPIO_WritePin(x_l_blink_init->led_port,x_l_blink_init->led_pin,GPIO_PIN_SET);	
	}
	else if (x_l_blink_init->x_l_blink_mode == X_L_LED_OFF)
	{
		HAL_GPIO_WritePin(x_l_blink_init->led_port,x_l_blink_init->led_pin,GPIO_PIN_RESET);
	}
}