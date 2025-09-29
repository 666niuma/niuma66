#include "WireLess.h"

protocol WireLessProtocol(&huart3); // create protocol instance
WireLess wireless; // create WireLess instance

void WireLess::DataReceivedCallback(uint8_t ID,const uint8_t *byte) //
{
    if (ID  == 0x57 ) // W for Wireless
    {
        processData_Screen(byte); // process the data
    }
    if (ID == 0x58) // X for Joystick
    {
        processData_Joystick(); // process the data for joystick
    }
}

void WireLess::processData_Screen(const uint8_t *byte) // process the data for screen
{
    for (int i = 0; i < 5; i++)//screen data length is 5
    {
        frame_to_send.data[i] = byte[i];
    }
    frame_to_send.length = 5; 
    frame_to_send.ID = 0x77; // Lowercase 'w' is used as the external ID for wireless data
    sendData(frame_to_send.ID,frame_to_send.length,frame_to_send.data);
}

void WireLess::processData_Joystick() // process the data for joystick
{
    // to do
}

void WireLess::WireLess_init()
{
    wireless.addport(&WireLessProtocol); // register the WireLess instance to the protocol instance
    WireLessProtocol.initReceiveQueue(); // initialize the receive queue
    WireLessProtocol.initQueue(); // initialize the send queue
    frame_to_transfer.header[0] = FRAME_HEADER_0;
    frame_to_transfer.header[1] = FRAME_HEADER_1;
    // different ID for different use
    // different length for different use
    frame_to_transfer.trailer[0] = FRAME_TRAILER_0;
    frame_to_transfer.trailer[1] = FRAME_TRAILER_1;
    WireLessProtocol.startUartReceiveIT(); // start UART receive interrupt
}

void WireLess::Task_WireLess()
{
    WireLessProtocol.handleReceiveData(); // handle the received data
    WireLessProtocol.SendData(); // send data
}

extern "C" void Task_WireLess(void *argument)
{
    wireless.WireLess_init(); // initialize WireLess
    for(;;)
    {
        wireless.Task_WireLess();
        osDelay(10);
    }
}