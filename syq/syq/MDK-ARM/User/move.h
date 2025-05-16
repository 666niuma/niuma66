#ifndef __MOVE_H
#define __MOVE_H


#include "main.h"

#define V0 0            // 初始速度，单位：毫米/秒
#define maxVx 300          // 最大速度，单位：毫米/秒
#define maxVy 300          // 最大速度，单位：毫米/秒
#define ACCELERATION 300       // 加速度，单位：毫米/平方秒
#define DECELERATION -150       // 减速度，单位：毫米/平方秒
#define START_TO_LIGHT_DISTANCE      1250//单位为毫米
#define LIGHT_TO_ENDLINE_DISTANCE    500//单位为毫米
#define ENDLINE_TO_FINAL             550//单位为毫米
#define motor_time 10//单位为ms

typedef struct 
{
    float Speed_Vx;      // 速度，单位：毫米/秒
    float Speed_Vy;      // 速度，单位：毫米/秒
    /* data */
}Speed_set;

typedef struct 
{
    Speed_set speed_set;          // 速度，单位：毫米/秒
    float distance;      // 距离，单位：毫米
    float time_acceleration; // 加速时间，单位：秒
    float time_deceleration; // 减速时间，单位：秒
    float time_constant; // 匀速时间，单位：秒
    /* data */
}move_t;








#endif



