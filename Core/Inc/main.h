/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "sys.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define TestKey_Pin GPIO_PIN_0
#define TestKey_GPIO_Port GPIOA
#define TestLED_Pin GPIO_PIN_2
#define TestLED_GPIO_Port GPIOD
#define FDC2214_CLK_Pin GPIO_PIN_6
#define FDC2214_CLK_GPIO_Port GPIOB
#define FDC2214_SDA_Pin GPIO_PIN_7
#define FDC2214_SDA_GPIO_Port GPIOB
#define OledClk_Pin GPIO_PIN_8
#define OledClk_GPIO_Port GPIOB
#define OledData_Pin GPIO_PIN_9
#define OledData_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
//nus为要延时的us数.		    								   
#define CPU_FREQUENCY_MHZ    72		// STM32时钟主频   72MHz
void delay_us(__IO unsigned int delay);
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
