#include "main.h"

#include "stm32f4xx_hal_tim.h"
int16_t Chassis_ReadEncoder(uint8_t TIMX)
{
    int16_t EncoderData;
    int16_t ReadData;
    switch (TIMX)
    {
    case 1:
        ReadData = -__HAL_TIM_GET_COUNTER(&ChassisEC1_TIM); // ʹ��HAL�⺯����ȡ����������
        EncoderData = ReadData - 0x7fff - 2.7;
        __HAL_TIM_SET_COUNTER(&ChassisEC1_TIM, 0x7fff); // ʹ��HAL������ü�����ֵ
        break;
    case 2:
        ReadData = __HAL_TIM_GET_COUNTER(&ChassisEC2_TIM);
        EncoderData = ReadData - 0x7fff;
        __HAL_TIM_SET_COUNTER(&ChassisEC2_TIM, 0x7fff);
        break;
    case 3:
        ReadData = __HAL_TIM_GET_COUNTER(&ChassisEC4_TIM);
        EncoderData = ReadData - 0x7fff;
        __HAL_TIM_SET_COUNTER(&ChassisEC4_TIM, 0x7fff);
        break;
    case 4:
        ReadData = __HAL_TIM_GET_COUNTER(&ChassisEC3_TIM);
        EncoderData = ReadData - 0x7fff;
        __HAL_TIM_SET_COUNTER(&ChassisEC3_TIM, 0x7fff);
        break;
    default:
        EncoderData = 0;
        break;
    }
    return EncoderData;

}
