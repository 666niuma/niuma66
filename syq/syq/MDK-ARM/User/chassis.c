#include "main.h"
pid_type_def Chassis_PID[4];
Chassis_Motor_t   Motor;


void MotorPID_Init(Chassis_Motor_t *pid_init); //PID初始化函数

//PID参数
pid_type_def Chassis_PID[4];
float Motor_Kp[5] = {2.9,  2.9,  1.5,  2,   1};
float Motor_Ki[5] = {0.15, 0.15, 0.15, 0.1, 0.2};
float Motor_Kd[5] = {0.1,  0.1,  0.1, 0.1, 0.5};

// 速度解算函数

void Chassis_Init(void)
{
    MotorPID_Init(&Motor);
    Motor_Init(&Motor);
}

void MotorPID_Init(Chassis_Motor_t *pid_init)
{
    int i;
    for(i = 0; i < 4; i++)
    {
        Chassis_PID[i].Kp = Motor_Kp[i];
        Chassis_PID[i].Kd = Motor_Kd[i];
        Chassis_PID[i].Ki = Motor_Ki[i];

        Chassis_PID[i].max_iout = 250;
        Chassis_PID[i].max_out = 300;

        Chassis_PID[i].mode = ChassisMotor.pidMode;

        pid_init->motor[i].motor_set.speed_set = 0;
    }
}


void Chassis_Speed_Calc(Chassis_Motor_t *Chassis_speed_calc)
{
    //速度解算
    Chassis_speed_calc->motor[0].motor_set.speed_set = ((sqrt(2) / 2) * Chassis_speed_calc->chassisVx - (sqrt(2) / 2) * Chassis_speed_calc->chassisVy ) * K * 60;
    Chassis_speed_calc->motor[1].motor_set.speed_set = (((-1) * sqrt(2) / 2) * Chassis_speed_calc->chassisVx - (sqrt(2) / 2) * Chassis_speed_calc->chassisVy  ) * K * 60;
    Chassis_speed_calc->motor[2].motor_set.speed_set = (-(sqrt(2) / 2) *Chassis_speed_calc->chassisVx + (sqrt(2) / 2) * Chassis_speed_calc->chassisVy ) * K * 60;
    Chassis_speed_calc->motor[3].motor_set.speed_set = ((sqrt(2) / 2) * Chassis_speed_calc->chassisVx + (sqrt(2) / 2) * Chassis_speed_calc->chassisVy ) * K * 60;
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

void Motor_fdb(Chassis_Motor_t *Motor_fdb)
{
    //电机反馈
    for(int i = 0; i < 4; i++)
    {
        Motor_fdb->motor[i].motor_fdb.encoder_fdb = Chassis_ReadEncoder(i + 1);
        Motor_fdb->motor[i].motor_fdb.speed_fdb = (Motor_fdb->motor[i].motor_fdb.encoder_fdb * motor_time / 4) * 60 / (NPN * gear_ratio);
    }
    Motor_fdb->motor[0].motor_fdb.speed_fdb = -Motor_fdb->motor[0].motor_fdb.speed_fdb;
}



void Task_Chassis(void)
{
    // Infinite loop
    Chassis_Speed_Calc(&Motor);
    Chassis_Speed_TO_Duty(&Motor);
    Motor_PWM_Set(&Motor);
}