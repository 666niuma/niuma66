#include "Screen.h"

protocol ScreenProtocol(&huart2); // 创建 protocol 实例
Screen screen; // 创建 Screen 实例

void Screen::DataReceivedCallback(uint8_t ID,const uint8_t *byte)
{
    if (ID == 0x83) // "S" symbol for screen
    {
        for (int i = 0; i < 3; i++)
        {
            page[i] = byte[i];
        }
        widget_ID = byte[3];
        data = byte[4];
		processData(page,widget_ID,data);
    }
}

void Screen::ScreenInit()
{
    screen.addport(&ScreenProtocol); // 将 Screen 实例注册到 protocol 实例
    ScreenProtocol.initReceiveQueue(); // 初始化接收队列
    ScreenProtocol.initQueue(); // 初始化发送队列
    // init the index
    screen.widget_ID = 0;
    screen.data = 0;
    for (int i = 0; i < 3; i++)
    {
        screen.page[i] = 0;
    }
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET);
    frame_to_transfer.header[0] = FRAME_HEADER_0;
    frame_to_transfer.header[1] = FRAME_HEADER_1;
    frame_to_transfer.length = 5; // length only includes data length
    // different ID for different use
    frame_to_transfer.trailer[0] = FRAME_TRAILER_0;
    frame_to_transfer.trailer[1] = FRAME_TRAILER_1;
    ScreenProtocol.startUartReceiveIT(); // 启动 UART 接收中断
}

void Screen::processData(uint8_t *page,uint8_t widget_ID,uint8_t data)
{
    if (page[0] == 0x4D && page[1] == 0x41 && page[2] == 0x4A) // "MAJ"
    {
        MAJORPAGE(widget_ID,data);
    }
    else if (page[0] == 0x4D && page[1] == 0x49 && page[2] == 0x4E) // "MIN"
    {
        MINORPAGE(widget_ID,data);
    }
    else if (page[0] == 0x53 && page[1] == 0x45 && page[2] == 0x54) // "SET"
    {
        SETTINGSPAGE(widget_ID,data);
    }
}

void Screen::MAJORPAGE(uint8_t widget_ID,uint8_t data)
{
    frame_to_transfer.data[0] = 0X4D; // 'M'
    frame_to_transfer.data[1] = 0X41; // 'A'
    frame_to_transfer.data[2] = 0X4A; // 'J'
    // Handle major page data
    if (widget_ID == 0x53) //switch
    {
        frame_to_transfer.data[3] = 0X53; // 'S'
        if (data & 0x80)
        {
            HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
            frame_to_transfer.data[4] = 0x80;
            frame_to_transfer.ID = 0x57; // W for Wireless
            transferData(frame_to_transfer.ID,frame_to_transfer.length,frame_to_transfer.data);
        }
        else if (data & 0x40)
        {
            frame_to_transfer.data[4] = 0x40;
        }
        else if (data & 0x20)
        {
            frame_to_transfer.data[4] = 0x20;
        }
        else if (data & 0x10)
        {
            frame_to_transfer.data[4] = 0x10;
        }
        else if (data & 0x08)
        {
            frame_to_transfer.data[4] = 0x08;
        }
        else if (data & 0x04)
        {  
            frame_to_transfer.data[4] = 0x04;
        }
        else if (data & 0x02)
        {
            frame_to_transfer.data[4] = 0x02;
        }
        else if (data & 0x01)
        {
            frame_to_transfer.data[4] = 0x01;
        }
    }
    if (widget_ID == 0x42)
    {
        frame_to_transfer.data[3] = 0X42; // 'B'
        if (data == 0x01)
        {
            frame_to_transfer.data[4] = 0x01;
        }
        else if (data == 0x02)
        {
            frame_to_transfer.data[4] = 0x02;
        }
        else if (data == 0x03)
        {
            frame_to_transfer.data[4] = 0x03;
        }
        else if (data == 0x04)
        {
            frame_to_transfer.data[4] = 0x04;
        }
        else if (data == 0x05)
        {}
        else if (data == 0x06)
        {}
        else if (data == 0x07)
        {}
        else if (data == 0x08)
        {}
        else if (data == 0x09)
        {}
        else if (data == 0x0A)
        {}
        else if (data == 0x0B)
        {}
        else if (data == 0x0C)
        {}
        else if (data == 0x0D)
        {}
        else if (data == 0x0E)
        {}
        else if (data == 0x0F)
        {}
        else if (data == 0x10)
        {}
    }

}


void Screen::MINORPAGE(uint8_t Iwidget_IDD,uint8_t data)
{
    // Handle minor page data
        if (widget_ID == 0x53) //switch
    {
        if (data & 0x80)
        {}
        else if (data & 0x40)
        {}
        else if (data & 0x20)
        {}
        else if (data & 0x10)
        {}
        else if (data & 0x08)
        {}
        else if (data & 0x04)
        {}
        else if (data & 0x02)
        {}
        else if (data & 0x01)
        {}
    }
    if (widget_ID == 0x42)
    {
        if (data == 0x01)
        {}
        else if (data == 0x02)
        {}
        else if (data == 0x03)
        {}
        else if (data == 0x04)
        {}
        else if (data == 0x05)
        {}
        else if (data == 0x06)
        {}
        else if (data == 0x07)
        {}
        else if (data == 0x08)
        {}
        else if (data == 0x09)
        {}
        else if (data == 0x0A)
        {}
        else if (data == 0x0B)
        {}
        else if (data == 0x0C)
        {}
        else if (data == 0x0D)
        {}
        else if (data == 0x0E)
        {}
        else if (data == 0x0F)
        {}
        else if (data == 0x10)
        {}
    }
    
}

void Screen::SETTINGSPAGE(uint8_t widget_ID,uint8_t data)
{
    // Handle settings page data
        if (widget_ID == 0x53) //switch
    {
        if (data & 0x80)
        {}
        else if (data & 0x40)
        {}
        else if (data & 0x20)
        {}
        else if (data & 0x10)
        {}
        else if (data & 0x08)
        {}
        else if (data & 0x04)
        {}
        else if (data & 0x02)
        {}
        else if (data & 0x01)
        {}
    }
    if (widget_ID == 0x42)
    {
        if (data == 0x01)
        {}
        else if (data == 0x02)
        {}
        else if (data == 0x03)
        {}
        else if (data == 0x04)
        {}
        else if (data == 0x05)
        {}
        else if (data == 0x06)
        {}
        else if (data == 0x07)
        {}
        else if (data == 0x08)
        {}
        else if (data == 0x09)
        {}
        else if (data == 0x0A)
        {}
        else if (data == 0x0B)
        {}
        else if (data == 0x0C)
        {}
        else if (data == 0x0D)
        {}
        else if (data == 0x0E)
        {}
        else if (data == 0x0F)
        {}
        else if (data == 0x10)
        {}
    }
}



void Screen::Task_screen()
{
    ScreenProtocol.handleReceiveData(); // 处理接收的数据
    ScreenProtocol.SendData(); // 发送数据
}
char txData[] = "Hello World\r\n";
extern "C" void Task_screen(void *argument)
{

    screen.ScreenInit(); // 初始化 Screen
    //ScreenProtocol.startUartReceiveIT(); // 启动 UART 接收中断
	
    for(;;)
    {
			//Tx[0] = 0x5A;
      //screen.Task_screen();
			//ScreenProtocol.startUartReceiveIT();
			//HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
			HAL_UART_Transmit_DMA(&huart2, (uint8_t*)txData, strlen(txData));
			//HAL_UART_Receive_IT(&huart2, Rx, 1);
			osDelay(300);
    }
}

//extern "C" void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//    
//    
//        if (Rx[0] == 0x5A)
//        {
//            HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);//test
//						Rx[0] = 0x00;
//        }
//    
//		HAL_UART_Receive_IT(&huart2, Rx, 1);
//}