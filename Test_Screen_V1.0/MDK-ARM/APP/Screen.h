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
    void DataReceivedCallback(uint8_t ID,uint8_t length,const uint8_t *byte) override; // data callback
    void processData(uint8_t ID,uint8_t *page,uint8_t widget_ID,uint8_t *data); // process the data
    void MAJORPAGE(uint8_t ID,uint8_t widget_ID,uint8_t *data); // major page
    void MINORPAGE(uint8_t ID,uint8_t Iwidget_ID,uint8_t *data); // minor page
    void SETTINGSPAGE(uint8_t ID,uint8_t widget_ID,uint8_t *data); // settings page
    void ScreenInit();
    void Task_screen();
    Frame frame_to_process;
    Frame frame_to_transfer;
    char txbuffer[20] = {0};
    void TJC_process(char *page_name,uint8_t widget_ID,uint8_t* data);
    void TJC_Send();
    char page_name[10] = {0};
    private:
    osMessageQueueId_t TJC_Queue_;
    uint8_t page[3] = {0};
    uint8_t widget_ID;
    uint8_t data[16] = {0};
};


#endif
#endif
