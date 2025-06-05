#include "main.h"
#include <Legacy/stm32_hal_legacy.h>


// 设置舵机角度
// servo_num: 1-舵机1(PF8), 2-舵机2(PF9)
// angle: 0-180度
void Set_Servo_Angle(uint8_t servo_num, uint8_t angle)
{
    uint16_t pulse_width;
    
    // 限制角度范围
    if(angle > 180) angle = 180;
    
    // 计算脉宽(线性映射)
    pulse_width = SERVO_MIN + (SERVO_MAX - SERVO_MIN) * angle / 180;
    
    // 设置对应通道的CCR值
    if(servo_num == 1) {
        __HAL_TIM_SetCompare(&htim13, TIM_CHANNEL_1, pulse_width);
    } 
    else if(servo_num == 2) {
        __HAL_TIM_SetCompare(&htim14, TIM_CHANNEL_1, pulse_width);
    }
}

// 舵机开关控制
// state: 0-关闭(0°), 1-打开(180°)
void Servo_Switch(uint8_t servo_num, uint8_t state)
{
    Set_Servo_Angle(servo_num, state ? 180 : 0);
}




void MorCode_Read(MorseCode_T * read)
{
    if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10) == GPIO_PIN_SET)
    {
        read->code[0] = 1;
    }
    else
    {
        read->code[0] = 0;
    }

    if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11) == GPIO_PIN_SET)
    {
        read->code[1] = 1;
    }
    else
    {
        read->code[1] = 0;
    }

    if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9) == GPIO_PIN_SET)
    {
        read->code[2] = 1;
    }
    else
    {
        read->code[2] = 0;
    }
}
