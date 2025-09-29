#include "my_uart.h"

SerialDevice *SerialDevice::obArr[MAX_INSTANCE] = {nullptr};

int SerialDevice::Ins_Count = 0;

void SerialDevice::initReceiveQueue()
{
    ReceiveQueue_ = osMessageQueueNew(MAX_QUEUE_SIZE, sizeof(Frame), NULL);
}

SerialDevice::SerialDevice(UART_HandleTypeDef *huart)
    : huart_(huart)
{
        // 注册当前实例到全局数组
        if (Ins_Count < MAX_INSTANCE)
        {
            Instance_Register(this);//注册传入的串口实例
        }
}

void SerialDevice::Instance_Register(SerialDevice *instance)
{

    obArr[Ins_Count++] = instance;//注册实例
}

void SerialDevice::startUartReceiveIT()
{
    if (huart_ != nullptr)
    {
        total_length = 0;
        length_flag = 0;
        rx_index =0;// reset
        check_Byte[0] = 0;
        check_Byte[1] = 0;
        for (int i = 0; i < sizeof(rxBuffer_); i++)
        {
            rxBuffer_[i] = 0;
        }
        HAL_UART_Receive_IT(huart_, rxByte, 1);

    }
}

// 全局回调函数：HAL 库调用该函数
 extern "C" void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
 {
     for (int i = 0; i < SerialDevice::Ins_Count; i++)
     {
         if (SerialDevice::obArr[i]->huart_ == huart)
         {
            
             // for overflow check
             if (SerialDevice::obArr[i]->rx_index < sizeof(SerialDevice::obArr[i]->rxBuffer_))
             {
                 SerialDevice::obArr[i]->rxBuffer_[SerialDevice::obArr[i]->rx_index] = SerialDevice::obArr[i]->rxByte[0];
                 SerialDevice::obArr[i]->check_Byte[0] = SerialDevice::obArr[i]->check_Byte[1];
                 SerialDevice::obArr[i]->check_Byte[1] = SerialDevice::obArr[i]->rxByte[0];
                 SerialDevice::obArr[i]->rx_index++;
             }
             else
             {
                 SerialDevice::obArr[i]->startUartReceiveIT();
             }
            
             if (SerialDevice::obArr[i]->rx_index == 2 && SerialDevice::obArr[i]->check_Byte[0] == 0x21 && SerialDevice::obArr[i]->check_Byte[1] == 0x40)
             {
                 SerialDevice::obArr[i]->length_flag = SerialDevice::obArr[i]->rxBuffer_[SerialDevice::obArr[i]->rx_index - 1]; // the length byte
                 SerialDevice::obArr[i]->total_length = SerialDevice::obArr[i]->length_flag + 6; // 头2 + 长度1 + ID1 + 数据 + 尾2
             }

            
             // check if the frame is complete
             if ((SerialDevice::obArr[i]->check_Byte[0] == 0x26 && SerialDevice::obArr[i]->check_Byte[1] == 0x2A))
             {
                 // for queue put
                 if (SerialDevice::obArr[i]->rx_index > 0)
                 {
                     Frame rx_frame;
                     rx_frame.header[0] = SerialDevice::obArr[i]->rxBuffer_[0];
                     rx_frame.header[1] = SerialDevice::obArr[i]->rxBuffer_[1];
                     rx_frame.length = SerialDevice::obArr[i]->rxBuffer_[2];
                     rx_frame.ID = SerialDevice::obArr[i]->rxBuffer_[3];
                     for (int j = 0; j < rx_frame.length;j++)//length only includes data length
                     {
                         rx_frame.data[j] = SerialDevice::obArr[i]->rxBuffer_[4 + j];// header 2 + length 1 + ID 1 = 4
                     }
                     rx_frame.trailer[0] = SerialDevice::obArr[i]->rxBuffer_[SerialDevice::obArr[i]->rx_index - 2];
                     rx_frame.trailer[1] = SerialDevice::obArr[i]->rxBuffer_[SerialDevice::obArr[i]->rx_index - 1];
                     // put to queue
                     osStatus_t status = osMessageQueuePut(SerialDevice::obArr[i]->ReceiveQueue_, &rx_frame, 0, 0);
                     if (status != osOK)
                     {
                         // try again
                         osMessageQueueReset(SerialDevice::obArr[i]->ReceiveQueue_);
                         (void)osMessageQueuePut(SerialDevice::obArr[i]->ReceiveQueue_, &rx_frame, 0, 0);
                     }
                 }
                 // restart receive
                 SerialDevice::obArr[i]->startUartReceiveIT();
             }
             else
             {
                 // for next byte
                 HAL_UART_Receive_IT(huart, SerialDevice::obArr[i]->rxByte, 1);
             }
             break; 
         }
     }
 }

