#ifndef __CHASSIS_H#define __CHASSIS_H

#include "main.h"

#define timeHz          100          //10ms, 采样频率
#define NULL            0
#define Wheel_R         30.0f       //轮子半径
#define PI              3.1415926f  //PI
#define gear_ratio         30.0f       //减速比
#define NPN             13.0f       //转一圈的脉冲数
#define T               100         //编码器arr
#define r               188.14      //底盘半径
#define MotorMAXspeed   56520       //线速度
#define MAX_AngleSpeed  2.00f       //单位为 rad/s
#define K               1 / (2 * PI * Wheel_R)          //底盘解算转速系数 188.4
#define maxVx 300          // 最大速度，单位：毫米/秒
#define maxVy 300          // 最大速度，单位：毫米/秒




void Chassis_Speed_Calc(Chassis_Motor_t *Chassis_speed_calc);
void Chassis_Speed_TO_Duty(Chassis_Motor_t *ChassisMotor_speed_to_duty);
void Chassis_Set_Speed_From_Move(Chassis_Motor_t *chassis, float vx, float vy);

#endif
