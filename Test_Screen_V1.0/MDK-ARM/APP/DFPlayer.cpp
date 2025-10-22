#include "DFPlayer.h"

protocol DFPlayerProtocol(&huart1); // 创建 protocol 实例 这个不需要接受所以不用初始化接收队列
DFPlayer dfplayer; // 创建 DFPlayer 实例


void DFPlayer::DFPlayer_init()
{
    dfplayer.addport(&DFPlayerProtocol); // 将 DFPlayer 实例注册到 protocol 实例
    DFplayer_queue_ = osMessageQueueNew(5, sizeof(uint8_t[10]), NULL); // 创建消息队列
    DFPlayerProtocol.startUartReceiveIT(); // 启动 UART 接收中断
    memset(dfplayer.rx_msg, 0, sizeof(dfplayer.rx_msg));
    memset(dfplayer.tx_msg, 0, sizeof(dfplayer.tx_msg));
    memset(dfplayer.tx_buffer, 0, sizeof(dfplayer.tx_buffer));
    get_uart(); // 获取 UART 句柄
		osDelay(1000);
    DF_pack(0x03,0x00,0x01); // 播放上电初始音乐
    DF_play();
}

void DFPlayer::DataReceivedCallback(uint8_t ID, uint8_t length, const uint8_t *byte)
{
    if(ID == 0x44) 
    {
        process_data(ID,length,byte);
    }
}

void DFPlayer::process_data(uint8_t ID, uint8_t length, const uint8_t *byte)
{
    if (byte[0] == 0x01)
    {
        DF_pack(0x03,0x00,0x01); // play
        DF_play();
    }
}


void DFPlayer::DF_pack(uint8_t cmd, uint8_t param1, uint8_t param2)
{
    tx_msg[0] = 0x7E;
    tx_msg[1] = 0xFF;
    tx_msg[2] = 0x06;
    tx_msg[3] = cmd;
    tx_msg[4] = 0x00;//no feedback
    tx_msg[5] = param1;
    tx_msg[6] = param2;
    uint16_t checksum = 0 - (tx_msg[1] + tx_msg[2] + tx_msg[3] + tx_msg[4] + tx_msg[5] + tx_msg[6]);//checksum = 0xFFFF - sum( from version to param2 ) + 1
    tx_msg[7] = (checksum >> 8) & 0xFF;
    tx_msg[8] = checksum & 0xFF;
    tx_msg[9] = 0xEF;
}

void DFPlayer::DF_play()
{
    if (osMessageQueuePut(DFplayer_queue_, tx_msg, 0, 0) != osOK)
    {
        osMessageQueueReset(DFplayer_queue_); // 重置队列
        osMessageQueuePut(DFplayer_queue_, tx_msg, 0, 0);
    }
}

void DFPlayer::DF_send()
{
    if (osMessageQueueGet(DFplayer_queue_, tx_buffer, NULL, 0) == osOK)
    {
        HAL_UART_Transmit_DMA(uart_, tx_buffer, 10);
    }
}

void DFPlayer::Task_DFPlayer()
{
    DF_send();

}

extern "C" void Task_dfplayer(void *argument)
{
    dfplayer.DFPlayer_init(); // 初始化 DFPlayer
    for(;;)
    {
      dfplayer.Task_DFPlayer();
            osDelay(10);
    }
}
