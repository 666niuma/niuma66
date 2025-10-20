#include "joystick.h"

UART_HandleTypeDef virtual_huart_joystick;//创建一个虚拟串口句柄供协议类使用，实际不使用该串口发送数据，禁止DMA发送//仅使用广播功能

protocol joystick_protocol(&virtual_huart_joystick);//创建一个协议实例
JOYStick joystick;

void JOYStick::DataReceivedCallback(uint8_t ID,uint8_t length,const uint8_t *byte) // data callback
{

}

void JOYStick::Joystick_init()
{

}

void JOYStick::Scan()
{
    
}






































void JOYStick::Task_Joystick()
{

}