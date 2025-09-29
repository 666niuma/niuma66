#ifndef __APP_SCREEN_H
#define __APP_SCREEN_H
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

typedef void (*FuncPtr)();

class Screen :public Subscriber
{
    public:
    Screen() = default;
    void DataReceivedCallback(uint8_t ID,const uint8_t *byte) override; // data callback
    void processData(uint8_t *page,uint8_t widget_ID,uint8_t data); // process the data
    void MAJORPAGE(uint8_t widget_ID,uint8_t data); // major page
    void MINORPAGE(uint8_t Iwidget_ID,uint8_t data); // minor page
    void SETTINGSPAGE(uint8_t widget_ID,uint8_t data); // settings page
    void ScreenInit();
    void Task_screen();
    Frame frame_to_transfer;
    private:
    uint8_t page[3] = {0};
    uint8_t widget_ID;
    uint8_t data;
};


#endif
#endif
