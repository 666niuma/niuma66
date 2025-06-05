#include "main.h"
#include <Legacy/stm32_hal_legacy.h>
// 定义舵机控制的电码结构体
// 设置舵机角度
// servo_num: 1-舵机1(PF8), 2-舵机2(PF9)
// angle: 0-180度

void MorCode_Read(MorseCode_T * read)
{
    if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9) == GPIO_PIN_SET)
    {
        read->code[0] = 1;
    }
    else
    {
        read->code[0] = 0;
    }

    if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10) == GPIO_PIN_SET)
    {
        read->code[1] = 1;
    }
    else
    {
        read->code[1] = 0;
    }

    if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11) == GPIO_PIN_SET)
    {
        read->code[2] = 1;
    }
    else
    {
        read->code[2] = 0;
    }
}
