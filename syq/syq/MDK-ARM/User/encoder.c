#include "main.h"



void Encoder_Init(void)
{
    HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);
}

int16_t Chassis_ReadEncoder(uint8_t TIMX) 
{
    int16_t EncoderData;
    int16_t ReadData;
    switch(TIMX)
    {
        case 1:
            ReadData = __HAL_TIM_GET_COUNTER(&htim1);
            EncoderData = ReadData - 0x7fff;
            __HAL_TIM_SET_COUNTER(&htim1,0x7fff);
            break;
        case 2:
            ReadData = __HAL_TIM_GET_COUNTER(&htim2);
            EncoderData = ReadData - 0x7fff;
            __HAL_TIM_SET_COUNTER(&htim2,0x7fff);
            break;
        case 3:
            ReadData = __HAL_TIM_GET_COUNTER(&htim3);
            EncoderData = ReadData - 0x7fff;
            __HAL_TIM_SET_COUNTER(&htim3,0x7fff);
            break;
        case 4:
            ReadData = __HAL_TIM_GET_COUNTER(&htim4);
            EncoderData = ReadData - 0x7fff;
            __HAL_TIM_SET_COUNTER(&htim4,0x7fff);
            break;
        default:
            EncoderData = 0;
            break;
    }
    return EncoderData;
}


