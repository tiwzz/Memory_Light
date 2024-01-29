/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
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
#include "gpio.h"

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
// 本项目所用到的所有全局变量
int8_t LED_1, LED_2, LED_3, LED_4, LED_5, LED_6, mode_auto, mode_manual = 0;
int8_t Last_LED_1, Last_LED_2, Last_LED_3, Last_LED_4, Last_LED_5, Last_LED_6, Last_mode_auto, Last_mode_manual = 0;
int8_t count = 0;
int8_t memory_LED[50] = {0}; // 用来记录按键顺序
int8_t sequence_num = 0;
int8_t Mode = DOWN;
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
  /* USER CODE BEGIN 2 */
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    Set_Mode();
    LastKeyOrder_update();
    GetKeyOrder();
    if (Mode == MANUAL)
    {
      Get_Key_Sequence();
    }
    else if (Mode == AUTO)
    {
      Light_LED();
      Mode = DOWN;
    }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    HAL_Delay(5);
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

  /** Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
// 获取按键信息
void GetKeyOrder(void)
{
  LED_1 = HAL_GPIO_ReadPin(LED_IN_1_GPIO_Port, LED_IN_1_Pin);
  LED_2 = HAL_GPIO_ReadPin(LED_IN_2_GPIO_Port, LED_IN_2_Pin);
  LED_3 = HAL_GPIO_ReadPin(LED_IN_3_GPIO_Port, LED_IN_3_Pin);
  LED_4 = HAL_GPIO_ReadPin(LED_IN_4_GPIO_Port, LED_IN_4_Pin);
  LED_5 = HAL_GPIO_ReadPin(LED_IN_5_GPIO_Port, LED_IN_5_Pin);
  LED_6 = HAL_GPIO_ReadPin(LED_IN_6_GPIO_Port, LED_IN_6_Pin);
  mode_manual = HAL_GPIO_ReadPin(MODE_MANUAL_GPIO_Port, MODE_MANUAL_Pin);
  mode_auto = HAL_GPIO_ReadPin(MODE_AUTO_GPIO_Port, MODE_AUTO_Pin);
}

// 更新上一次的按键信息
void LastKeyOrder_update(void)
{
  Last_LED_1 = LED_1;
  Last_LED_2 = LED_2;
  Last_LED_3 = LED_3;
  Last_LED_4 = LED_4;
  Last_LED_5 = LED_5;
  Last_LED_6 = LED_6;
  Last_mode_manual = mode_manual;
  Last_mode_auto = mode_auto;
}

// 记录按键顺序
void Get_Key_Sequence(void)
{
  if (LED_1 == Key_up && Last_LED_1 == Key_Down)
  {
    memory_LED[sequence_num] = 1;
    sequence_num++;
  }
  else if (LED_2 == Key_up && Last_LED_2 == Key_Down)
  {
    memory_LED[sequence_num] = 2;
    sequence_num++;
  }
  else if (LED_3 == Key_up && Last_LED_3 == Key_Down)
  {
    memory_LED[sequence_num] = 3;
    sequence_num++;
  }
  else if (LED_4 == Key_up && Last_LED_4 == Key_Down)
  {
    memory_LED[sequence_num] = 4;
    sequence_num++;
  }
  else if (LED_5 == Key_up && Last_LED_5 == Key_Down)
  {
    memory_LED[sequence_num] = 5;
    sequence_num++;
  }
  else if (LED_6 == Key_up && Last_LED_6 == Key_Down)
  {
    memory_LED[sequence_num] = 6;
    sequence_num++;
  }
  else
  {
    sequence_num = sequence_num;
  }
}

// 按照记录的顺序点亮led
void Light_LED(void)
{
  int i;
  for (i = 0; i < 51; i++)
  {
    switch (memory_LED[i])
    {
    case 1:
    {
      HAL_GPIO_WritePin(LED_OUT_1_GPIO_Port, LED_OUT_1_Pin, GPIO_PIN_SET);
      HAL_Delay(500);
      HAL_GPIO_WritePin(LED_OUT_1_GPIO_Port, LED_OUT_1_Pin, GPIO_PIN_RESET);
    }
    break;
    case 2:
    {
      HAL_GPIO_WritePin(LED_OUT_2_GPIO_Port, LED_OUT_2_Pin, GPIO_PIN_SET);
      HAL_Delay(500);
      HAL_GPIO_WritePin(LED_OUT_2_GPIO_Port, LED_OUT_2_Pin, GPIO_PIN_RESET);
    }
    break;
    case 3:
    {
      HAL_GPIO_WritePin(LED_OUT_3_GPIO_Port, LED_OUT_3_Pin, GPIO_PIN_SET);
      HAL_Delay(500);
      HAL_GPIO_WritePin(LED_OUT_3_GPIO_Port, LED_OUT_3_Pin, GPIO_PIN_RESET);
    }
    break;
    case 4:
    {
      HAL_GPIO_WritePin(LED_OUT_4_GPIO_Port, LED_OUT_4_Pin, GPIO_PIN_SET);
      HAL_Delay(500);
      HAL_GPIO_WritePin(LED_OUT_4_GPIO_Port, LED_OUT_4_Pin, GPIO_PIN_RESET);
    }
    break;
    case 5:
    {
      HAL_GPIO_WritePin(LED_OUT_5_GPIO_Port, LED_OUT_5_Pin, GPIO_PIN_SET);
      HAL_Delay(500);
      HAL_GPIO_WritePin(LED_OUT_5_GPIO_Port, LED_OUT_5_Pin, GPIO_PIN_RESET);
    }
    break;
    case 6:
    {
      HAL_GPIO_WritePin(LED_OUT_6_GPIO_Port, LED_OUT_6_Pin, GPIO_PIN_SET);
      HAL_Delay(500);
      HAL_GPIO_WritePin(LED_OUT_6_GPIO_Port, LED_OUT_6_Pin, GPIO_PIN_RESET);
    }
    break;
    default:
    {
      HAL_GPIO_WritePin(LED_OUT_1_GPIO_Port, LED_OUT_1_Pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(LED_OUT_2_GPIO_Port, LED_OUT_2_Pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(LED_OUT_3_GPIO_Port, LED_OUT_3_Pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(LED_OUT_4_GPIO_Port, LED_OUT_4_Pin, GPIO_PIN_RESET);
    }
    break;
    }
  }
}

void Set_Mode(void)
{
  if (mode_manual == Key_up && Last_mode_manual == Key_Down)
  {
    sequence_num = 0;
    clear_memory();
    Mode = MANUAL;
  }
  else if (mode_auto == Key_up && Last_mode_auto == Key_Down)
  {
    Mode = AUTO;
  }
}

void clear_memory(void)
{
  int j;
  for (j = 0; j < 51; j++)
  {
    memory_LED[j] = 0;
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

#ifdef USE_FULL_ASSERT
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
