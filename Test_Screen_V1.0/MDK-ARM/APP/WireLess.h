#ifndef __WIRELESS_H
#define __WIRELESS_H
#include "main.h"
#pragma once
#include "protocol.h"
#ifdef __cplusplus
extern "C"
{
#endif
#include "stm32f1xx_hal.h" 
#ifdef __cplusplus
}
#endif

class WireLess :public Subscriber
{
    public:
    WireLess() = default;
    void DataReceivedCallback(uint8_t ID,const uint8_t *byte) override; // data callback
    void processData_Screen(const uint8_t *byte); // process the data for screen
    void processData_Joystick(); // process the data for joystick
    void WireLess_init();
    void Task_WireLess();
    Frame frame_to_transfer;
    Frame frame_to_send;
    uint8_t Screen_buffer[10] = {0};
    uint8_t Joystick_buffer[10] = {0};
    private:

};












#endif