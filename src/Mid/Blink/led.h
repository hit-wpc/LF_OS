#pragma once

#include "stm32f4xx_hal.h"
#include "gpio.h"

#define WPC_LED_SET_H  	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13,GPIO_PIN_SET);
#define WPC_LED_SET_L  	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13,GPIO_PIN_RESET);


typedef enum
{
	X_L_LED_ON           = 0,
	X_L_LED_OFF,
	X_L_LED_BLINK_MODE_A,
	X_L_LED_BLINK_MODE_B,
	X_L_LED_BLINK_MODE_C,
}x_l_blink_mode_t;

typedef struct
{
	GPIO_TypeDef* led_port;
	uint32_t led_pin;
	uint8_t blink_ticks;
	x_l_blink_mode_t x_l_blink_mode;	
}x_l_blink_init_t;

extern x_l_blink_init_t x_l_red_blink_init;
extern x_l_blink_init_t x_l_yellow_blink_init;
extern x_l_blink_init_t x_l_blue_blink_init;
extern x_l_blink_init_t x_l_green_blink_init;

uint8_t x_l_blink_set(x_l_blink_init_t* x_l_blink_init, GPIO_TypeDef* led_port, uint32_t led_pin, x_l_blink_mode_t x_l_blink_mode);
uint8_t x_l_blink_start(x_l_blink_init_t* x_l_blink_init);