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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
void setNumberOnClock(int);
void clearNumberOnClock(int);
void clearAllClock();

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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  int hour = 0;
  int minute = 0;
  int second = 0;
  while(1)
    {
	  if (second >= 60) {
	 		second = 0;
	 		minute++;
	 	  }
	 if (minute >= 60) {
	 		minute = 0;
	 		hour++;
	 	  }
	 if (hour >= 12) {
	 		hour = 0;
	 	  }
	  clearAllClock();
	  setNumberOnClock(hour%12);
	  setNumberOnClock((minute - minute%5)/5);
	  setNumberOnClock((second - second%5)/5);

      HAL_Delay(1000);
      second++;
	  }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void setNumberOnClock(int num){
	if(num == 0) HAL_GPIO_WritePin(led_1_GPIO_Port, led_1_Pin, GPIO_PIN_RESET);
	if(num == 1) HAL_GPIO_WritePin(led_2_GPIO_Port, led_2_Pin, GPIO_PIN_RESET);
	if(num == 2) HAL_GPIO_WritePin(led_3_GPIO_Port, led_3_Pin, GPIO_PIN_RESET);
	if(num == 3) HAL_GPIO_WritePin(led_4_GPIO_Port, led_4_Pin, GPIO_PIN_RESET);
	if(num == 4) HAL_GPIO_WritePin(led_5_GPIO_Port, led_5_Pin, GPIO_PIN_RESET);
	if(num == 5) HAL_GPIO_WritePin(led_6_GPIO_Port, led_6_Pin, GPIO_PIN_RESET);
	if(num == 6) HAL_GPIO_WritePin(led_7_GPIO_Port, led_7_Pin, GPIO_PIN_RESET);
	if(num == 7) HAL_GPIO_WritePin(led_8_GPIO_Port, led_8_Pin, GPIO_PIN_RESET);
	if(num == 8) HAL_GPIO_WritePin(led_9_GPIO_Port, led_9_Pin, GPIO_PIN_RESET);
	if(num == 9) HAL_GPIO_WritePin(led_10_GPIO_Port, led_10_Pin, GPIO_PIN_RESET);
	if(num == 10) HAL_GPIO_WritePin(led_11_GPIO_Port, led_11_Pin, GPIO_PIN_RESET);
	if(num == 11) HAL_GPIO_WritePin(led_12_GPIO_Port, led_12_Pin, GPIO_PIN_RESET);
}
void clearNumberOnClock(int num){
	if(num == 0) HAL_GPIO_WritePin(led_1_GPIO_Port, led_1_Pin, GPIO_PIN_SET);
	if(num == 1) HAL_GPIO_WritePin(led_2_GPIO_Port, led_2_Pin, GPIO_PIN_SET);
	if(num == 2) HAL_GPIO_WritePin(led_3_GPIO_Port, led_3_Pin, GPIO_PIN_SET);
	if(num == 3) HAL_GPIO_WritePin(led_4_GPIO_Port, led_4_Pin, GPIO_PIN_SET);
	if(num == 4) HAL_GPIO_WritePin(led_5_GPIO_Port, led_5_Pin, GPIO_PIN_SET);
	if(num == 5) HAL_GPIO_WritePin(led_6_GPIO_Port, led_6_Pin, GPIO_PIN_SET);
	if(num == 6) HAL_GPIO_WritePin(led_7_GPIO_Port, led_7_Pin, GPIO_PIN_SET);
	if(num == 7) HAL_GPIO_WritePin(led_8_GPIO_Port, led_8_Pin, GPIO_PIN_SET);
	if(num == 8) HAL_GPIO_WritePin(led_9_GPIO_Port, led_9_Pin, GPIO_PIN_SET);
	if(num == 9) HAL_GPIO_WritePin(led_10_GPIO_Port, led_10_Pin, GPIO_PIN_SET);
	if(num == 10) HAL_GPIO_WritePin(led_11_GPIO_Port, led_11_Pin, GPIO_PIN_SET);
	if(num == 11) HAL_GPIO_WritePin(led_12_GPIO_Port, led_12_Pin, GPIO_PIN_SET);
}

void clearAllClock(){
	for(int i =0; i <=11; i++){
		clearNumberOnClock(i);
	}
}
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, led_1_Pin|led_2_Pin|led_3_Pin|led_4_Pin
                          |led_5_Pin|led_6_Pin|led_7_Pin|led_8_Pin
                          |led_9_Pin|led_10_Pin|led_11_Pin|led_12_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : led_1_Pin led_2_Pin led_3_Pin led_4_Pin
                           led_5_Pin led_6_Pin led_7_Pin led_8_Pin
                           led_9_Pin led_10_Pin led_11_Pin led_12_Pin */
  GPIO_InitStruct.Pin = led_1_Pin|led_2_Pin|led_3_Pin|led_4_Pin
                          |led_5_Pin|led_6_Pin|led_7_Pin|led_8_Pin
                          |led_9_Pin|led_10_Pin|led_11_Pin|led_12_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

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
