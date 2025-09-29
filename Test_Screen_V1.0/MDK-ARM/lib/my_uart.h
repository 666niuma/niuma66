#ifndef __MY_UART_H
#define __MY_UART_H



#ifdef __cplusplus

#ifdef __cplusplus
extern "C"
{
#endif
#include "main.h"
#include <cmsis_os.h>
#include "stdint.h"
#include "stdbool.h"
#include "string.h"
#include "stdio.h"
#include "FreeRTOS.h"
#include "usart.h"
#include "task.h"
#include "queue.h"
#ifdef __cplusplus
}
#endif
#ifdef __cplusplus

#define MAX_INSTANCE 4 // 最多支持 4 个串口实例
#define RX_BUFFER_SIZE 27 // 接收缓冲区大小
#define Frame_Length 1
#define MAX_DATA_LENGTH 16

typedef struct Frame
{
    uint8_t header[2];
    uint8_t length;
    uint8_t ID;
    uint8_t data[MAX_DATA_LENGTH];
    uint8_t trailer[2];
}Frame;


class SerialDevice
{
    public:
    SerialDevice(UART_HandleTypeDef *huart);//构造函数，用来调用管理函数注册实例
    osMessageQueueId_t ReceiveQueue_; // to share the data received
    static  SerialDevice *obArr[MAX_INSTANCE];//保存实例
    static int Ins_Count;//用来标志有几个串口实例
    public:

    static void Instance_Register(SerialDevice *Instance);//for register all the instance
    UART_HandleTypeDef *huart_=nullptr; // 保存 UART 句柄
    uint8_t rxBuffer_[RX_BUFFER_SIZE];
    void startUartReceiveIT();
    uint8_t rxByte[1];
    uint8_t check_Byte[2];
    int rx_index;//用来指示接收到第几位
    int length_flag;
    int8_t total_length;
		Frame rxframe;
    bool check_flag = false;
    virtual void handleReceiveData(void) = 0;//for handle the data received
    virtual bool processSendData(uint8_t ID,uint8_t length,const uint8_t *data) = 0;
    virtual void SendData(void) = 0;
    void initReceiveQueue();
    protected:
    static const uint8_t MAX_QUEUE_SIZE = 5; // 最大队列大小
};


#endif
#endif
#endif

