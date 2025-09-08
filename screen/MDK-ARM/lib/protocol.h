#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#pragma once
#include "main.h"

#ifdef __cplusplus


class uart_msg{
    public:
    uint8_t rx_msg_pos_ptr; //此变量用来指示解析到一帧的第几个字节
    uint8_t rx_msg[20]; //使用此数组来存放接收到的字节
    virtual void frame_receive() = 0;
    virtual void frame_send() = 0;
    protected:
    uint8_t state_ptr;//解析到帧头为1，解析到帧尾为2，如果收完一帧该指示器未变成2则重置接收状态
    virtual bool fsm_judge() = 0;
    uint8_t msg_length;

};


class TJC_RX_MSG : private uart_rx_msg
{
    public:
    
    //TJC_RX();
    //TjC_send();
    private:
    bool fsm_judge(TJC_RX_MSG *TJC_JUDGE);

    //TJC_Frame_process();
    //TJC_Prase();
};



#endif
#endif
