#ifndef __SERVO_H
#define __SERVO_H
#include "main.h"




#define SERVO_MIN  400    
#define SERVO_MAX  1700   

typedef struct 
{
    int code[3];
}MorseCode_T;

/*      函数声明        */



// 设置舵机角度
// servo_num: 1-舵机1(PA0), 2-舵机2(PA1)
// angle: 0-180度

// 舵机开关控制
// state: 0-关闭(0°), 1-打开(180°)



void MorCode_Read(MorseCode_T * read);

#endif
