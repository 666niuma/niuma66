/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdint.h"
#include "stdbool.h"
#include <stdio.h>
#include "chassis.h"
#include "pid.h"
#include "Servo.h"
#include "tim.h"
#include "math.h"
#include "bsp_Chassis.h"
#include <stdarg.h>
#include <string.h>
#include "usart.h"
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
#define CIN2_Pin GPIO_PIN_4
#define CIN2_GPIO_Port GPIOE
#define PWMC_Pin GPIO_PIN_5
#define PWMC_GPIO_Port GPIOE
#define PWMD_Pin GPIO_PIN_6
#define PWMD_GPIO_Port GPIOE
#define CIN1_Pin GPIO_PIN_13
#define CIN1_GPIO_Port GPIOC
#define PWMB_Pin GPIO_PIN_15
#define PWMB_GPIO_Port GPIOB
#define AIN1_Pin GPIO_PIN_8
#define AIN1_GPIO_Port GPIOD
#define BIN2_Pin GPIO_PIN_9
#define BIN2_GPIO_Port GPIOD
#define AIN2_Pin GPIO_PIN_10
#define AIN2_GPIO_Port GPIOD
#define BIN1_Pin GPIO_PIN_11
#define BIN1_GPIO_Port GPIOD
#define DIN2_Pin GPIO_PIN_14
#define DIN2_GPIO_Port GPIOD
#define DIN1_Pin GPIO_PIN_15
#define DIN1_GPIO_Port GPIOD

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
