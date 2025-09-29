#ifndef __PROTOCOL_H
#define __PROTOCOL_H


#ifdef __cplusplus
extern "C"
{
#endif
#include "main.h"
#include "my_uart.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <cmsis_os.h>
#include "stdint.h"
#include "stdbool.h"
#include "string.h"
#include "stdio.h"
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

#define FRAME_HEADER_0 0x21
#define FRAME_HEADER_1 0x40
#define FRAME_TRAILER_0 0x26
#define FRAME_TRAILER_1 0x2A

#define MAX_SUBSCRIBERS 4



class protocol;

class Subscriber
{
public:
    virtual void DataReceivedCallback(uint8_t ID,const uint8_t *byte) {}; // 数据回调函数
    // 用户调用此函数发送字节数据
    bool sendData(uint8_t ID,uint8_t length,const uint8_t *data);
    bool transferData(uint8_t ID,uint8_t length,const uint8_t *data);
    void addport(protocol *port_);
private:
    protocol *serialport_ = nullptr;
};

class protocol : public SerialDevice
{
    public:
    void addSubscriber(Subscriber *subscriber);
    Frame tx_frame;
    public:
    protocol(UART_HandleTypeDef *huart = nullptr);
    virtual void handleReceiveData(void) override;
    virtual bool processSendData(uint8_t ID,uint8_t length,const uint8_t *data) override;
    virtual void SendData(void) override;
	Frame frame_to_process;
    Frame frame_to_broadcast;
    void initQueue();
    bool TransferData(uint8_t ID,uint8_t length,const uint8_t *data);
    private:
    osMessageQueueId_t sendQueue_;
    osMessageQueueId_t MsgPool;
    Subscriber *subscribers[MAX_SUBSCRIBERS]; // 订阅者数组
    uint8_t subscriberCount_ = 0;             // 订阅者数量
};

#endif
#endif


