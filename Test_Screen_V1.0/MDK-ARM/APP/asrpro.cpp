// #include "asrpro.h"

// protocol ASRProProtocol(&huart3); // create protocol instance
// ASRPro asrpro; // create ASRPro instance


// void ASRPro::ASRPro_init()
// {

//     asrpro.addport(&ASRProProtocol);
//     ASRProProtocol.initQueue();
//     ASRProProtocol.initReceiveQueue(); // initialize the receive queue
//     ASRProProtocol.startUartReceiveIT(); // start UART receive interrupt
//     // Register the ASRPro instance to the protocol instance
//     ASR_buffer[0] = 0;
//     ASR_buffer[1] = 0;
//     ASR_buffer[2] = 0;
//     ASR_buffer[3] = 0;
//     ASR_buffer[4] = 0;
//     ASR_buffer[5] = 0;
//     ASR_buffer[6] = 0;
//     ASR_buffer[7] = 0;
//     ASR_buffer[8] = 0;
//     ASR_buffer[9] = 0;

//     frame_to_transfer.header[0] = FRAME_HEADER_0;
//     frame_to_transfer.header[1] = FRAME_HEADER_1;
//     // different ID for different use
//     // different length for different use
//     frame_to_transfer.trailer[0] = FRAME_TRAILER_0;
//     frame_to_transfer.trailer[1] = FRAME_TRAILER_1;

//     frame_to_send.header[0] = FRAME_HEADER_0;
//     frame_to_send.header[1] = FRAME_HEADER_1;
//     frame_to_send.trailer[0] = FRAME_TRAILER_0;
//     frame_to_send.trailer[1] = FRAME_TRAILER_1;

// }

// void ASRPro::DataReceivedCallback(uint8_t ID,uint8_t length,const uint8_t *byte) // data callback
// {
//     if (ID  == 0x41 || ID == 0x61) // different A or a for external of internal
//     {
//         processData(ID,length,byte); // process the data
//     }
// }

// void ASRPro::processData(uint8_t ID,uint8_t length,const uint8_t *byte) // process the data
// {
//     if (ID == 0x41) 
//     {
        
//         if (byte[0] & 0x01)
//         {
//             ASR_flag = true;
//             strcpy(ASR_data, "one");
//             ASR_send (ASR_flag, ASR_data);
//         }
//         if (byte[0] & 0x02)
//         {
//             ASR_flag = true;
//             strcpy(ASR_data, "two");
//             ASR_send (ASR_flag, ASR_data);
//         }
//     }
//     if (ID == 0x61){}
// }


// void ASRPro::ASR_send(bool flag,char *data)
// {
//     if (flag)
//     {
//         HAL_UART_Transmit_DMA(&huart1, (uint8_t*)data, strlen(data));// If there is a special function to get the huart_ handle for ASRPro at a higher level, it is not elegant to call the terminal directly here
//     }
//     ASR_flag = false;
    
// }

// void ASRPro::Task_ASRPro()
// {
//     ASRProProtocol.handleReceiveData(); // handle the received data
//     memset(ASR_data, 0, sizeof(ASR_data));
// }

// extern "C" void Task_asrpro(void *argument)
// {
//     asrpro.ASRPro_init(); // initialize ASRPro
//     for(;;)
//     {
//       asrpro.Task_ASRPro();
//             osDelay(10);
//     }
// }