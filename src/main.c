/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "led.h"
#include "button.h"
#include "LF_OS.h" 
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
void led_blink_task(void);
void btn4_callback(void *btn);
void btn3_callback(void *btn);
void btn2_callback(void *btn);
void btn1_callback(void *btn);
uint8_t read_btn4_level(void);
uint8_t read_btn3_level(void);
uint8_t read_btn2_level(void);
uint8_t read_btn1_level(void);
void btn_process_task(void);
void btn_init(void);
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
Button_t btn1;
Button_t btn2;
Button_t btn3;
Button_t btn4;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM11_Init();
  btn_init();
  /* USER CODE BEGIN 2 */
  x_l_blink_set(&x_l_red_blink_init,LD4_GPIO_Port,LD4_Pin,X_L_LED_BLINK_MODE_B);
  x_l_blink_set(&x_l_yellow_blink_init,LD3_GPIO_Port,LD3_Pin,X_L_LED_BLINK_MODE_C);
  // x_l_blink_set(&x_l_blue_blink_init,LD2_GPIO_Port,LD2_Pin,X_L_LED_BLINK_MODE_B);
  // x_l_blink_set(&x_l_green_blink_init,LD1_GPIO_Port,LD1_Pin,X_L_LED_BLINK_MODE_C);

  x_l_tsk_reset_task(0, (l_func_t)led_blink_task,	X_L_TSK_TASK_MODE_ENABLE,	0,	100);
  x_l_tsk_reset_task(1, (l_func_t)btn_process_task,	X_L_TSK_TASK_MODE_ENABLE,	0,	20);

  HAL_TIM_Base_Start_IT(&htim11);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
    // Button_Process();
    // HAL_Delay(20);
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void btn_init(void)
{
  Button_Create("btn1",&btn1,read_btn1_level,0);
  Button_Create("btn2",&btn2,read_btn2_level,0);
  Button_Create("btn3",&btn3,read_btn3_level,0);
  Button_Create("btn4",&btn4,read_btn4_level,0);

  Button_Attach(&btn1,BUTTON_DOUBLE,(Button_CallBack)btn1_callback);
  Button_Attach(&btn2,BUTTON_LONG,(Button_CallBack)btn2_callback);
  // Button_Attach(&btn3,BUTTON_DOWM,(Button_CallBack)btn3_callback);
  // Button_Attach(&btn4,BUTTON_DOWM,(Button_CallBack)btn4_callback);
}
void led_blink_task(void)
{
   x_l_blink_start(&x_l_red_blink_init);
  // x_l_blink_start(&x_l_blue_blink_init);
   x_l_blink_start(&x_l_yellow_blink_init);
  // x_l_blink_start(&x_l_green_blink_init);
}

void btn1_callback(void *btn)
{
  HAL_GPIO_TogglePin(LD1_GPIO_Port,LD1_Pin);
}
void btn2_callback(void *btn)
{
  HAL_GPIO_TogglePin(LD2_GPIO_Port,LD2_Pin);
}
void btn3_callback(void *btn)
{
  HAL_GPIO_TogglePin(LD3_GPIO_Port,LD3_Pin);
}
void btn4_callback(void *btn)
{
  HAL_GPIO_TogglePin(LD4_GPIO_Port,LD4_Pin);
}

uint8_t read_btn1_level(void)
{
  return HAL_GPIO_ReadPin(K1_GPIO_Port,K1_Pin);
}
uint8_t read_btn2_level(void)
{
  return HAL_GPIO_ReadPin(K2_GPIO_Port,K2_Pin);
}
uint8_t read_btn3_level(void)
{
  return HAL_GPIO_ReadPin(K3_GPIO_Port,K3_Pin);
}
uint8_t read_btn4_level(void)
{
  return HAL_GPIO_ReadPin(K4_GPIO_Port,K4_Pin);
}

void btn_process_task(void)
{
  Button_Process();
}

void Tim11_irq_callback(void)
{
  x_l_tsk_task_exec(0,0);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == (&htim11))
    {
      Tim11_irq_callback();
    }
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

