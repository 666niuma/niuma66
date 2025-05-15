#include "main.h"

Chassis_Motor_t   Motor;

void Chassis_Speed_Calc(Chassis_Motor_t *Chassis_speed_calc)
{
    //速度解算
    Chassis_speed_calc->motor[0].motor_set.speed_set = ((sqrt(2) / 2) * Chassis_speed_calc->chassisVx - (sqrt(2) / 2) * Chassis_speed_calc->chassisVy + 60 * Chassis_speed_calc->anglespeed_set * r) * K;
    Chassis_speed_calc->motor[1].motor_set.speed_set = (((-1) * sqrt(2) / 2) * Chassis_speed_calc->chassisVx - (sqrt(2) / 2) * Chassis_speed_calc->chassisVy + 60 * Chassis_speed_calc->anglespeed_set * r) * K;
    Chassis_speed_calc->motor[2].motor_set.speed_set = (-(sqrt(2) / 2) *Chassis_speed_calc->chassisVx + (sqrt(2) / 2) * Chassis_speed_calc->chassisVy + 60 * Chassis_speed_calc->anglespeed_set * r) * K;
    Chassis_speed_calc->motor[3].motor_set.speed_set = ((sqrt(2) / 2) * Chassis_speed_calc->chassisVx + (sqrt(2) / 2) * Chassis_speed_calc->chassisVy + 60 * Chassis_speed_calc->anglespeed_set * r) * K;
    //速度限制
    for(int i = 0; i < 4; i++)
    {
        if(Chassis_speed_calc->motor[i].motor_set.speed_set > Chassis_speed_calc->maxRpm_fwd[i])
        {
            Chassis_speed_calc->motor[i].motor_set.speed_set = Chassis_speed_calc->maxRpm_fwd[i];
        }
        else if(Chassis_speed_calc->motor[i].motor_set.speed_set < -Chassis_speed_calc->maxRpm_bwd[i])
        {
            Chassis_speed_calc->motor[i].motor_set.speed_set = -Chassis_speed_calc->maxRpm_bwd[i];
        }

    }
}

void Chassis_Speed_TO_Duty(Chassis_Motor_t *ChassisMotor_speed_to_duty)
{
    //速度转化为电机转速
    for(int i = 0; i < 4; i++)
    {
        if(ChassisMotor_speed_to_duty->motor[i].motor_set.speed_set > 0)
        {
            ChassisMotor_speed_to_duty->motor[i].motor_set.duty_set = (ChassisMotor_speed_to_duty->motor[i].motor_set.speed_set / ChassisMotor_speed_to_duty->maxRpm_fwd[i]) * 1000;
        }
        else
        {
            ChassisMotor_speed_to_duty->motor[i].motor_set.duty_set = (ChassisMotor_speed_to_duty->motor[i].motor_set.speed_set / ChassisMotor_speed_to_duty->maxRpm_bwd[i]) * 1000;
        }
    }
}
// 将move.c中的速度值传入底盘电机设置值的函数
void Chassis_Set_Speed_From_Move(Chassis_Motor_t *chassis, float vx, float vy)
{
    chassis->chassisVx = vx;
    chassis->chassisVy = vy;

}

