#ifndef __BSP_CHASSIS_H
#define __BSP_CHASSIS_H
#include "main.h"



typedef struct
{ 
    float speed_set;
    float pid_speed;
    uint16_t duty_set;
}MOTOR_SET;

typedef struct 
{
    float speed_fdb;
    int16_t encoder_fdb;
    float last_Vx;
    float last_Vy;
}MOTOR_FDB;

typedef struct 
{
    GPIO_TypeDef *gpio;
    uint16_t in1;
    uint16_t in2;
}MOTOR_GPIO;


typedef struct
{
    MOTOR_SET   motor_set;
    MOTOR_FDB   motor_fdb;
    MOTOR_GPIO  motor_gpio;
    unsigned int  tim_channel;
}MOTOR_T;

typedef struct
{
    MOTOR_T motor[4];
    float chassisVx;
    float chassisVy;
    float maxRpm_fwd[4];
    float maxRpm_bwd[4];
    float maxVx;
    float maxVy;
    float pidMode;
	float anglespeed_set;
    float pid_anglespeed;
	float anglespeed_fdb;
    unsigned int motor_TIM;
}Chassis_Motor_t;




void Motor_Init(Chassis_Motor_t *Motor_init);




#endif
