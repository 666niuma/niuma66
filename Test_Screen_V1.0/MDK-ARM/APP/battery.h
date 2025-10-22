#ifndef __BATTERY_H
#define __BATTERY_H
#include "protocol.h"
#include <array>
#include <cstdint>
#include <algorithm> // for std::sort
#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f1xx_hal.h"
#ifdef __cplusplus
}
#endif

// 由实测参数计算得到
#define ADC_TO_BATT_CONST  (0.00940f) // V per ADC count
#define minBatteryVoltage 11.4f // 电池最低电压
#define maxBatteryVoltage 12.6f // 电池最高电压

// 可选：用于长期平滑
static float smoothedVoltage = 0.0f;
static const float EMA_ALPHA = 0.2f; // 0..1，越小越平滑

class Battery :public Subscriber
{
    public:
    Battery() = default;
    void DataReceivedCallback(uint8_t ID,uint8_t length,const uint8_t *byte) override; // data callback
    void GetVoltage(uint32_t voltage);
    void Battery_init();
    uint32_t Battery_fliter(uint32_t voltage);
    void ReadBatteryVoltage_Averaged(void);
    void Task_Battery();
    private:
    Frame frame_to_transfer;
    float batteryVoltage = 0.0f;
    uint8_t batteryPercentage = 0;
    bool initialized_ = false;
    uint32_t filtered_adc_value = 0.0f;
};
















#endif
