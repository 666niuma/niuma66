#ifndef __DFPLAYER_H__
#define __DFPLAYER_H__


#include "main.h"
#include "protocol.h"





class DFPlayer : public Subscriber
{
    public:
    void DataReceivedCallback(uint8_t ID, uint8_t length, const uint8_t *byte) override;
    void DFPlayer_init();
    void Task_DFPlayer();
    void process_data(uint8_t ID, uint8_t length, const uint8_t *byte);
    void DF_send();
    void DF_play();
    void DF_pack(uint8_t cmd, uint8_t param1, uint8_t param2);
    private:
    uint8_t rx_msg[10] = {0};
    uint8_t tx_msg[10] = {0};
    uint8_t tx_buffer[10] = {0};
    osMessageQueueId_t DFplayer_queue_;
};












#endif