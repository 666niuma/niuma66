#ifndef __BSP_CHASSISENCODER_H
#define __BSP_CHASSISENCODER_H

#include "main.h"
#include "stm32f4xx_hal_tim.h"
#include "tim.h"


#define ChassisEC1_TIM htim4 
#define ChassisEC2_TIM htim1 
#define ChassisEC3_TIM htim3
#define ChassisEC4_TIM htim8



int16_t Chassis_ReadEncoder(uint8_t TIMX);



#include "main.h"
#include "stm32f4xx_hal_tim.h"
#include "tim.h"



























#endif





















