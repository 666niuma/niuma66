#ifndef __SERVO_H
#define __SERVO_H
#include "main.h"


typedef struct
{	
	//����1������2������ͷ
	int Servo_angle[3];
	int Servo_Duty[3];
	int Servo_Flag[3];//�����־λ����1������2������ͷ
}Servo_t;


void Servo_angle_to_duty(Servo_t *Servo_calc);

void Servo_Init();

void Servo_Set(Servo_t *Servo_set);




#endif
