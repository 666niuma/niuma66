#include "protocol.h"

protocol::protocol( UART_HandleTypeDef *huart)
    : SerialDevice(huart)
{
    
}


void protocol::initQueue()
{
    sendQueue_ = osMessageQueueNew(MAX_QUEUE_SIZE, sizeof(Frame), NULL);
    MsgPool = osMessageQueueNew(MAX_QUEUE_SIZE, sizeof(Frame), NULL);
}

void protocol::addSubscriber(Subscriber *subscriber)
{
    if (subscriberCount_ < MAX_SUBSCRIBERS)
    {
        subscribers[subscriberCount_] = subscriber;// add the subscriber to the array
        subscriberCount_++;
    }
}

void Subscriber::addport(protocol *port_)
{
    serialport_ = port_;
    serialport_->addSubscriber(this); // give the ptr of this port
}

void protocol::handleReceiveData(void)
{
    
    if (osMessageQueueGet(ReceiveQueue_, &frame_to_process, NULL, 0)  == osOK)
    {
        for (int i = 0; i < subscriberCount_; i++)
        {
            subscribers[i]->DataReceivedCallback(frame_to_process.ID,frame_to_process.data);// notify all subscribers
        }
    }
    if (osMessageQueueGet(MsgPool, &frame_to_broadcast, NULL, 0)  == osOK)
    {
        for (int i = 0; i < subscriberCount_; i++)
        {
            subscribers[i]->DataReceivedCallback(frame_to_broadcast.ID,frame_to_broadcast.data);// notify all subscribers
        }
    }
}

__attribute__((section("dma_buffer_section"), aligned(4))) uint8_t sendBuffer_[24] = {0}; // 发送缓冲区，放到 AHB SRAM 的 DMA 段

bool protocol::processSendData(uint8_t ID,uint8_t length,const uint8_t *data)
{
    //add the byte to the queue

    tx_frame.header[0] = FRAME_HEADER_0;
    tx_frame.header[1] = FRAME_HEADER_1;
    tx_frame.length = length; // length only includes data length
    tx_frame.ID = ID;
    for (int i = 0; i < length; i++) // length only includes data length
    {
        tx_frame.data[i] = data[i];
    }
    tx_frame.trailer[0] = FRAME_TRAILER_0;
    tx_frame.trailer[1] = FRAME_TRAILER_1;
    return (osMessageQueuePut(sendQueue_, &tx_frame, 0, 0) == osOK);
}


void protocol::SendData(void)
{
    Frame frame_to_send;
    osStatus_t status = osMessageQueueGet(sendQueue_, &frame_to_send, NULL, 0);// Non-blocking get
    if (status == osOK)
    {
        // Prepare send buffer
        sendBuffer_[0] = frame_to_send.header[0];
        sendBuffer_[1] = frame_to_send.header[1];
        sendBuffer_[2] = frame_to_send.length;
        for (int i = 0; i < frame_to_send.length; i++) // length only includes data length
        {
            sendBuffer_[3 + i] = frame_to_send.data[i];
        }
        sendBuffer_[frame_to_send.length + 3] = frame_to_send.trailer[0];
        sendBuffer_[frame_to_send.length + 4] = frame_to_send.trailer[1];
        // Start DMA transmission
        HAL_UART_Transmit_DMA(huart_, sendBuffer_, frame_to_send.length + 5); // Total length = header(2) + length(1) + data + trailer(2)
    }
}

bool Subscriber::sendData(uint8_t ID,uint8_t length,const uint8_t *data)
{
    if (serialport_ != nullptr)
    {
        return serialport_->processSendData(ID,length, data);//give the data to the protocol instance 
    }
    return false;
}

bool Subscriber::transferData(uint8_t ID,uint8_t length,const uint8_t *data)
{
    if (serialport_ != nullptr)
    {
        return serialport_->TransferData(ID,length, data);//give the data to the protocol instance 
    }
    return false;
}

bool protocol::TransferData(uint8_t ID,uint8_t length,const uint8_t *data)
{
    frame_to_broadcast.header[0] = FRAME_HEADER_0;
    frame_to_broadcast.header[1] = FRAME_HEADER_1;
    frame_to_broadcast.length = length; // length only includes data length
    frame_to_broadcast.ID = ID;
    for (int i = 0; i < length; i++) // length only includes data length
    {
        frame_to_broadcast.data[i] = data[i];
    }
    frame_to_broadcast.trailer[0] = FRAME_TRAILER_0;
    frame_to_broadcast.trailer[1] = FRAME_TRAILER_1;
    if(osMessageQueuePut(MsgPool, &frame_to_broadcast, 0, 0) != osOK)
    {
        // try again
        osMessageQueueReset(MsgPool);
        (void)osMessageQueuePut(MsgPool, &frame_to_broadcast, 0, 0);
    }
    return true;
}

