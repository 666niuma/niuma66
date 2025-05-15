#include "main.h"
#define Servo_MAX 90
#define Servo_MIN 0
#define Servo_open 0
#define Servo_close 1
#define Duty_MIN 50
#define Duty_MAX 250

Servo_t Servo;


void Servo_angle_to_duty(Servo_t *Servo_calc)
{
	for (int i = 0;i < 3;i++)
	{
		if(Servo_calc->Servo_angle[i] > Servo_MAX)
	{
		Servo_calc->Servo_angle[i] = Servo_MAX;
	}
	Servo_calc->Servo_Duty[i] = ((Servo_calc->Servo_angle[i] - Servo_MIN) * (Duty_MAX - Duty_MIN)) / (Servo_MAX - Servo_MIN) + Duty_MIN;
	}
}

void Servo_Init()
{
	//��ʼ�����Ϊ0�ȹر�״̬
	__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_1, 50);
	__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_2, 50);
	//����ͷ�����ʼ��
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 250);//������ͷ�����ʼλ�������м�λ��
}

void Servo_Set(Servo_t *Servo_set)
{
	//��־λΪ0ʱ���ӹرգ�Ϊ1ʱ���ӿ���
	
	if (Servo.Servo_Flag[0] == 0 && Servo_set->Servo_Flag[1] == 0)
	{
		for (int i = 0;i < 2;i++)
		{
		Servo_set->Servo_angle[i] = 0;
		Servo_angle_to_duty(&Servo);
		__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_1 , Servo.Servo_Duty[i]);
		__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_2 , Servo.Servo_Duty[i]);
		}
		
	}

	if (Servo.Servo_Flag[0] == 1)
	{
		Servo.Servo_angle[0] = 90;
		Servo_angle_to_duty(&Servo);
		__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_1 , Servo.Servo_Duty[0]);
	}
	if (Servo.Servo_Flag[1] == 1)
	{
		Servo.Servo_angle[1] = 90;
		Servo_angle_to_duty(&Servo);
		__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_2 , Servo.Servo_Duty[1]);
	}

}
