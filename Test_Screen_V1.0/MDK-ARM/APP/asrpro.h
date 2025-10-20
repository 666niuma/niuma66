// #ifndef __ASRPRO_H
// #define __ASRPRO_H
// #include "main.h"

// #include "protocol.h"
// #ifdef __cplusplus
// extern "C"
// {
// #endif
// #include "stm32f1xx_hal.h" 
// #ifdef __cplusplus
// }
// #endif

// class ASRPro :public Subscriber
// {
//     public:
//     ASRPro() = default;
//     void DataReceivedCallback(uint8_t ID,uint8_t length,const uint8_t *byte) override; // data callback
//     void processData(uint8_t ID,uint8_t length,const uint8_t *byte); // process the data
//     void ASRPro_init();
//     void Task_ASRPro();
//     void ASR_send(bool flag, char* data);
//     Frame frame_to_transfer;
//     Frame frame_to_send;
//     Frame frame_to_process;
//     uint8_t ASR_buffer[10] = {0};
//     bool ASR_flag = false;
//     char ASR_data[10] = {0};
//     private:
// };



























// #endif