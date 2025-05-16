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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdint.h"
#include <stdio.h>
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "Servo.h"
#include "bsp_Chassis.h"
#include "move.h"
#include "chassis.h"
#include "math.h"
#include "pid.h"
#include "encoder.h"
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
#define Motor3IN1_Pin GPIO_PIN_0
#define Motor3IN1_GPIO_Port GPIOC
#define Motor3IN2_Pin GPIO_PIN_1
#define Motor3IN2_GPIO_Port GPIOC
#define Motor1IN1_Pin GPIO_PIN_2
#define Motor1IN1_GPIO_Port GPIOC
#define Motor1IN2_Pin GPIO_PIN_3
#define Motor1IN2_GPIO_Port GPIOC
#define Servo1_Pin GPIO_PIN_0
#define Servo1_GPIO_Port GPIOA
#define Servo2_Pin GPIO_PIN_1
#define Servo2_GPIO_Port GPIOA
#define Motor2IN1_Pin GPIO_PIN_4
#define Motor2IN1_GPIO_Port GPIOC
#define Motor2IN2_Pin GPIO_PIN_5
#define Motor2IN2_GPIO_Port GPIOC
#define Servo3_Pin GPIO_PIN_11
#define Servo3_GPIO_Port GPIOB
#define Motor1PWM_Pin GPIO_PIN_6
#define Motor1PWM_GPIO_Port GPIOC
#define Motor2PWM_Pin GPIO_PIN_7
#define Motor2PWM_GPIO_Port GPIOC
#define Motor3PWM_Pin GPIO_PIN_8
#define Motor3PWM_GPIO_Port GPIOC
#define Motor4PWM_Pin GPIO_PIN_9
#define Motor4PWM_GPIO_Port GPIOC
#define Motor1_Encoder1_Pin GPIO_PIN_8
#define Motor1_Encoder1_GPIO_Port GPIOA
#define Motor1_Encoder2_Pin GPIO_PIN_9
#define Motor1_Encoder2_GPIO_Port GPIOA
#define Motor4IN1_Pin GPIO_PIN_10
#define Motor4IN1_GPIO_Port GPIOA
#define Motor4IN2_Pin GPIO_PIN_12
#define Motor4IN2_GPIO_Port GPIOA
#define Motor2_Encoder1_Pin GPIO_PIN_15
#define Motor2_Encoder1_GPIO_Port GPIOA
#define Motor2_Encoder2_Pin GPIO_PIN_3
#define Motor2_Encoder2_GPIO_Port GPIOB
#define Motor3_Encoder1_Pin GPIO_PIN_4
#define Motor3_Encoder1_GPIO_Port GPIOB
#define Motor3_Encoder2_Pin GPIO_PIN_5
#define Motor3_Encoder2_GPIO_Port GPIOB
#define Motor4_Encoder1_Pin GPIO_PIN_6
#define Motor4_Encoder1_GPIO_Port GPIOB
#define Motor4_Encoder2_Pin GPIO_PIN_7
#define Motor4_Encoder2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
