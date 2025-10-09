#include "Screen.h"

protocol ScreenProtocol(&huart2); // 创建 protocol 实例
Screen screen; // 创建 Screen 实例

void Screen::DataReceivedCallback(uint8_t ID,uint8_t length,const uint8_t *byte)
{
    if (ID == 0x73 || ID == 0x53) // receive data from screen, 's' or 'S'
    {
        for (int i = 0; i < 3; i++)
        {
            page[i] = byte[i];
        }
        widget_ID = byte[3];
        if (length == 5)
            data[0] = byte[4];
        else
        {
            for (int i = 0; i < length - 4; i++)
            {
                data[i] = byte[4 + i]; // only process the last byte
            }
        }
		processData(ID,page,widget_ID,data);
    }
}

void Screen::ScreenInit()
{
    screen.addport(&ScreenProtocol); // 将 Screen 实例注册到 protocol 实例
    ScreenProtocol.initReceiveQueue(); // 初始化接收队列
    ScreenProtocol.initQueue(); // 初始化发送队列
    TJC_Queue_ = osMessageQueueNew(5, sizeof(txbuffer), NULL);
    // init the index
    screen.widget_ID = 0;
    for (int i = 0; i < 16; i++)
    {
        screen.data[i] = 0;
    }
    
    for (int i = 0; i < 3; i++)
    {
        screen.page[i] = 0;
    }
	
    frame_to_transfer.header[0] = FRAME_HEADER_0;
    frame_to_transfer.header[1] = FRAME_HEADER_1;
    // different length for different use
    // different ID for different use
    frame_to_transfer.trailer[0] = FRAME_TRAILER_0;
    frame_to_transfer.trailer[1] = FRAME_TRAILER_1;
    ScreenProtocol.startUartReceiveIT(); // 启动 UART 接收中断
}

void Screen::processData(uint8_t ID,uint8_t *page,uint8_t widget_ID,uint8_t *data)
{
    if (page[0] == 0x4D && page[1] == 0x41 && page[2] == 0x4A) // "MAJ"
    {
        MAJORPAGE(ID,widget_ID,data);
    }
    else if (page[0] == 0x4D && page[1] == 0x49 && page[2] == 0x4E) // "MIN"
    {
        MINORPAGE(ID,widget_ID,data);
    }
    else if (page[0] == 0x53 && page[1] == 0x45 && page[2] == 0x54) // "SET"
    {
        SETTINGSPAGE(ID,widget_ID,data);
    }
}

void Screen::MAJORPAGE(uint8_t ID,uint8_t widget_ID,uint8_t *data)
{
    frame_to_transfer.data[0] = 0X4D; // 'M'
    frame_to_transfer.data[1] = 0X41; // 'A'
    frame_to_transfer.data[2] = 0X4A; // 'J'
    page_name[0] = 'm';
    page_name[1] = 'a';
    page_name[2] = 'j';
    page_name[3] = 'o';
    page_name[4] = 'r';
    // Handle major page data
    if (ID == 0x53) //S for receive from internal
    {
        TJC_process(page_name,widget_ID,data);
        osMessageQueuePut(TJC_Queue_, &txbuffer, 0, 0);
    }
    if (ID == 0x73)
    {
    if (widget_ID == 0x53) //switch
    {
        frame_to_transfer.data[3] = 0X53; // 'S'
        if (data[0] & 0x80)
        {

            
            frame_to_transfer.data[4] = 0x80;
            frame_to_transfer.ID = 0x57; // W for Wireless
            transferData(frame_to_transfer.ID,frame_to_transfer.length,frame_to_transfer.data);
            
        }
        else if (data[0] & 0x40)
        {
            frame_to_transfer.data[4] = 0x40;
        }
        else if (data[0] & 0x20)
        {
            frame_to_transfer.data[4] = 0x20;
        }
        else if (data[0] & 0x10)
        {
            frame_to_transfer.data[4] = 0x10;
        }
        else if (data[0] & 0x08)
        {
            frame_to_transfer.data[4] = 0x08;
        }
        else if (data[0] & 0x04)
        {  
            frame_to_transfer.data[4] = 0x04;
        }
        else if (data[0] & 0x02)
        {
            frame_to_transfer.data[4] = 0x02;
        }
        else if (data[0] & 0x01)
        {
            frame_to_transfer.data[4] = 0x01;
        }
    }
    if (widget_ID == 0x42)
    {
        frame_to_transfer.data[3] = 0X42; // 'B'
        if (data[0] == 0x01)
        {
            frame_to_transfer.data[4] = 0x01;
        }
        else if (data[0] == 0x02)
        {
            frame_to_transfer.data[4] = 0x02;
        }
        else if (data[0] == 0x03)
        {
            frame_to_transfer.data[4] = 0x03;
        }
        else if (data[0] == 0x04)
        {
            frame_to_transfer.data[4] = 0x04;
        }
        else if (data[0] == 0x05)
        {}
        else if (data[0] == 0x06)
        {}
        else if (data[0] == 0x07)
        {}
        else if (data[0] == 0x08)
        {}
        else if (data[0] == 0x09)
        {}
        else if (data[0] == 0x0A)
        {}
        else if (data[0] == 0x0B)
        {}
        else if (data[0] == 0x0C)
        {}
        else if (data[0] == 0x0D)
        {}
        else if (data[0] == 0x0E)
        {}
        else if (data[0] == 0x0F)
        {}
        else if (data[0] == 0x10)
        {}
    }
    }
}


void Screen::MINORPAGE(uint8_t ID,uint8_t widget_ID,uint8_t *data)
{
    // Handle minor page data
    frame_to_transfer.data[0] = 0X4D; // 'M'
    frame_to_transfer.data[1] = 0X49; // 'I'
    frame_to_transfer.data[2] = 0X4E; // 'N'
    page_name[0] = 'm';
    page_name[1] = 'i';
    page_name[2] = 'n';
    page_name[3] = 'o';
    page_name[4] = 'r';
     if (ID == 0x73)
    {
        if (widget_ID == 0x53) //switch
    {
        if (data[0] & 0x80)
        {}
        else if (data[0] & 0x40)
        {}
        else if (data[0] & 0x20)
        {}
        else if (data[0] & 0x10)
        {}
        else if (data[0] & 0x08)
        {}
        else if (data[0] & 0x04)
        {}
        else if (data[0] & 0x02)
        {}
        else if (data[0] & 0x01)
        {}
    }
    if (widget_ID == 0x42)
    {
        if (data[0] == 0x01)
        {}
        else if (data[0] == 0x02)
        {}
        else if (data[0] == 0x03)
        {}
        else if (data[0] == 0x04)
        {}
        else if (data[0] == 0x05)
        {}
        else if (data[0] == 0x06)
        {}
        else if (data[0] == 0x07)
        {}
        else if (data[0] == 0x08)
        {}
        else if (data[0] == 0x09)
        {}
        else if (data[0] == 0x0A)
        {}
        else if (data[0] == 0x0B)
        {}
        else if (data[0] == 0x0C)
        {}
        else if (data[0] == 0x0D)
        {}
        else if (data[0] == 0x0E)
        {}
        else if (data[0] == 0x0F)
        {}
        else if (data[0] == 0x10)
        {}
    }
    }
}

void Screen::SETTINGSPAGE(uint8_t ID,uint8_t widget_ID,uint8_t* data)
{
    // Handle settings page data
    frame_to_transfer.data[0] = 0X53; // 'S'
    frame_to_transfer.data[1] = 0X45; // 'E'
    frame_to_transfer.data[2] = 0X54; // 'T'
    page_name[0] = 's';
    page_name[1] = 'e';
    page_name[2] = 't';
    page_name[3] = 't';
    page_name[4] = 'i';
    page_name[5] = 'n';
    page_name[6] = 'g';
     if (ID == 0x73)
    {
        if (widget_ID == 0x53) //switch
    {
        if (data[0] & 0x80)
        {}
        else if (data[0] & 0x40)
        {}
        else if (data[0] & 0x20)
        {}
        else if (data[0] & 0x10)
        {}
        else if (data[0] & 0x08)
        {}
        else if (data[0] & 0x04)
        {}
        else if (data[0] & 0x02)
        {}
        else if (data[0] & 0x01)
        {}
    }
    if (widget_ID == 0x42)
    {
        if (data[0] == 0x01)
        {}
        else if (data[0] == 0x02)
        {}
        else if (data[0] == 0x03)
        {}
        else if (data[0] == 0x04)
        {}
        else if (data[0] == 0x05)
        {}
        else if (data[0] == 0x06)
        {}
        else if (data[0] == 0x07)
        {}
        else if (data[0] == 0x08)
        {}
        else if (data[0] == 0x09)
        {}
        else if (data[0] == 0x0A)
        {}
        else if (data[0] == 0x0B)
        {}
        else if (data[0] == 0x0C)
        {}
        else if (data[0] == 0x0D)
        {}
        else if (data[0] == 0x0E)
        {}
        else if (data[0] == 0x0F)
        {}
        else if (data[0] == 0x10)
        {}
    }
}
}



void Screen::TJC_process(char *page_name,uint8_t widget_ID,uint8_t *data)//拼接控件位号和数据
{
    if (widget_ID == 0x6E) // n for number
    { 
        if (data[0] & 0x01)
        {
            sprintf(txbuffer, "%s.n%d.val=%d", page_name,data[0],data[1]);
        }
    }
    if (widget_ID == 0x6A) //j  可以用作进度条
    {
    sprintf(txbuffer, "%s.j%d.val=%d", page_name,data[0],data[1]);
    }
}    

void Screen::TJC_Send()
{
    osMessageQueueGet(TJC_Queue_, &txbuffer, NULL, 0);
    HAL_UART_Transmit_DMA(&huart2, (uint8_t *)txbuffer, strlen(txbuffer));// 如果在上层专门写个函数取得huart_句柄不够优雅，在这里直接调用终端了
}

void Screen::Task_screen()
{
    ScreenProtocol.handleReceiveData(); // 处理接收的数据
    //ScreenProtocol.SendData(); // 发送数据
    TJC_Send();
}

extern "C" void Task_screen(void *argument)
{
    screen.ScreenInit(); // 初始化 Screen
    for(;;)
    {
      screen.Task_screen();
			osDelay(10);
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