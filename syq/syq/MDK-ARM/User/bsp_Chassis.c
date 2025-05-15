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
}


