#include "battery.h"


extern ADC_HandleTypeDef hadc1;
UART_HandleTypeDef virtual_huart_battery;//创建一个虚拟串口句柄供协议类使用，实际不使用该串口发送数据，禁止DMA发送//仅使用广播功能

Battery battery;
protocol BatteryProtocol(&virtual_huart_battery);

void Battery :: GetVoltage(uint32_t voltage)
{
    batteryVoltage = voltage;
}

void Battery :: ReadBatteryVoltage_Averaged(void)
{

    float voltage = Battery_fliter(batteryVoltage) * ADC_TO_BATT_CONST;
    // 可选：指数移动平均，减少突发跳变
    if (smoothedVoltage == 0.0f) smoothedVoltage = voltage;
    smoothedVoltage = EMA_ALPHA * voltage + (1.0f - EMA_ALPHA) * smoothedVoltage;
    batteryPercentage = static_cast<int>(((smoothedVoltage - minBatteryVoltage) / (maxBatteryVoltage - minBatteryVoltage)) * 100.0f);
}


void Battery::DataReceivedCallback(uint8_t ID,uint8_t length,const uint8_t *byte)
{
   
}

void Battery::Battery_init()
{
    battery.addport(&BatteryProtocol); // 将 Battery 实例注册到 protocol 实例
    BatteryProtocol.initReceiveQueue(); // 初始化接收队列
    BatteryProtocol.initQueue(); // 初始化发送队列
}

//转发电池数据给屏幕 data[0] n0控件 data[1] 电池百分比
void Battery::Task_Battery()
{
    ReadBatteryVoltage_Averaged();
    frame_to_transfer.length = 6; // length only includes data length
    frame_to_transfer.ID = 0x53; // 'S' ID for screen
    frame_to_transfer.data[0] = 0x4D;
    frame_to_transfer.data[1] = 0x41;
    frame_to_transfer.data[2] = 0x4A; // MAJ major page
    frame_to_transfer.data[3] = 0x6E; // n for number widget
    frame_to_transfer.data[4] = 0x00; //for the first n0 widget which is battery percentage
    frame_to_transfer.data[5] = batteryPercentage; // battery percentage
    transferData(frame_to_transfer.ID,frame_to_transfer.length,frame_to_transfer.data); // 'S' ID 发送给屏幕
    BatteryProtocol.handleReceiveData();
}


uint32_t Battery::Battery_fliter(uint32_t voltage)
{
    static std::array<uint32_t, 5> window = {0};
        static uint8_t index = 0;

        window[index] = voltage;
        index = (index + 1) % window.size();

        // 复制一份用于排序求中位数
        auto temp = window;
        std::sort(temp.begin(), temp.end());
        uint32_t median = temp[temp.size() / 2];

        // --- 平滑滤波（指数平均） ---
        if (!initialized_) {
            filtered_adc_value = median;
            initialized_ = true;
        } else {
            const float alpha = 0.1f;  // 越小越平滑
            filtered_adc_value = static_cast<uint32_t>(
                alpha * median + (1.0f - alpha) * filtered_adc_value);
        }

        return filtered_adc_value;
}