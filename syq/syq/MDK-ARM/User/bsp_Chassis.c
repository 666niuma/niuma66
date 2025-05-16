#include "main.h" 


void Motor_Init(Chassis_Motor_t *Motor_init)
{
	for (int i = 0;i < 4;i++)
	{
		Motor_init->motor[i].motor_set.speed_set = 0;
        Motor_init->motor[i].motor_set.pid_speed = 0;
        Motor_init->motor[i].motor_set.duty_set = 0;
        Motor_init->motor[i].motor_fdb.speed_fdb = 0;
        Motor_init->motor[i].motor_fdb.encoder_fdb = 0;
        
	}
    //各个电机的最大转速

    Motor_init->maxRpm_fwd[0] = 307;
    Motor_init->maxRpm_fwd[1] = 360;
    Motor_init->maxRpm_fwd[2] = 350;
    Motor_init->maxRpm_fwd[3] = 345;
    Motor_init->maxRpm_bwd[0] = 330;
    Motor_init->maxRpm_bwd[1] = 360;
    Motor_init->maxRpm_bwd[2] = 350;
    Motor_init->maxRpm_bwd[3] = 345;
    Motor_init->motor[0].tim_channel = TIM_CHANNEL_1;
    Motor_init->motor[1].tim_channel = TIM_CHANNEL_2;
    Motor_init->motor[2].tim_channel = TIM_CHANNEL_3;
    Motor_init->motor[3].tim_channel = TIM_CHANNEL_4;
    Motor_init->motor_TIM = htim8;

}


void Motor_PWM_Set(Chassis_Motor_t *Motor_pwm_set)
{
    //电机pwm设置
    for (int i = 0;i < 4;i++)
    {
        if (Motor_pwm_set->motor[i].motor_set.duty_set > 0)
        {
            __HAL_TIM_SET_COMPARE(&Motor_pwm_set->motor_TIM,  Motor_pwm_set->motor[i].tim_channel,  Motor_pwm_set->motor[i].motor_set.duty_set);
            HAL_GPIO_WritePin(Motor_pwm_set->motor[i].motor_gpio.gpio, Motor_pwm_set->motor[i].motor_gpio.in1, GPIO_PIN_SET);
            HAL_GPIO_WritePin(Motor_pwm_set->motor[i].motor_gpio.gpio, Motor_pwm_set->motor[i].motor_gpio.in2, GPIO_PIN_RESET);
        }
        else
        {
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1 + i, -Motor_pwm_set->motor[i].motor_set.duty_set);
            HAL_GPIO_WritePin(Motor_pwm_set->motor[i].motor_gpio.gpio, Motor_pwm_set->motor[i].motor_gpio.in1, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(Motor_pwm_set->motor[i].motor_gpio.gpio, Motor_pwm_set->motor[i].motor_gpio.in2, GPIO_PIN_SET);
        }
    }
}
