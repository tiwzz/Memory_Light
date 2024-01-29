/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#define Key_Down  0
#define Key_up    1  
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
typedef enum
{
  AUTO = 1,
  MANUAL,
	DOWN,
}SET_MODE;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
void GetKeyOrder(void);
void LastKeyOrder_update(void);
void Get_Key_Sequence(void);
void Light_LED(void);
void Set_Mode(void);
void clear_memory(void);
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_OUT_1_Pin GPIO_PIN_1
#define LED_OUT_1_GPIO_Port GPIOA
#define LED_OUT_2_Pin GPIO_PIN_3
#define LED_OUT_2_GPIO_Port GPIOA
#define LED_OUT_3_Pin GPIO_PIN_5
#define LED_OUT_3_GPIO_Port GPIOA
#define LED_OUT_4_Pin GPIO_PIN_7
#define LED_OUT_4_GPIO_Port GPIOA
#define LED_OUT_5_Pin GPIO_PIN_1
#define LED_OUT_5_GPIO_Port GPIOB
#define LED_OUT_6_Pin GPIO_PIN_11
#define LED_OUT_6_GPIO_Port GPIOB
#define MODE_AUTO_Pin GPIO_PIN_8
#define MODE_AUTO_GPIO_Port GPIOA
#define MODE_MANUAL_Pin GPIO_PIN_9
#define MODE_MANUAL_GPIO_Port GPIOA
#define LED_IN_6_Pin GPIO_PIN_10
#define LED_IN_6_GPIO_Port GPIOA
#define LED_IN_5_Pin GPIO_PIN_11
#define LED_IN_5_GPIO_Port GPIOA
#define LED_IN_4_Pin GPIO_PIN_15
#define LED_IN_4_GPIO_Port GPIOA
#define LED_IN_3_Pin GPIO_PIN_3
#define LED_IN_3_GPIO_Port GPIOB
#define LED_IN_2_Pin GPIO_PIN_4
#define LED_IN_2_GPIO_Port GPIOB
#define LED_IN_1_Pin GPIO_PIN_5
#define LED_IN_1_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
