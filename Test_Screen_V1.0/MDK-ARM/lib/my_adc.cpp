#include "my_adc.h"

ADCDevice adcDevice;

extern ADC_HandleTypeDef hadc1;
extern Battery battery;


void ADCDevice::ADC_init()
{
    HAL_ADC_Start_DMA(&hadc1, (uint32_t*)raw_values_, MAX_ADC_CHANNELS);
}

void ADCDevice::UpdateAverage(void)
{
    uint32_t sum[MAX_ADC_CHANNELS] = {0};

    for (int i = 0; i < 20; i++)
    {
        // 重新启动 DMA 一次采样
        HAL_ADC_Stop_DMA(&hadc1);
        HAL_ADC_Start_DMA(&hadc1, (uint32_t*)raw_values_, MAX_ADC_CHANNELS);

        // 等待 DMA 完成（简易延时，若要求高可用信号量通知）
        osDelay(2);

        // 累加每个通道的值
        for (int ch = 0; ch < MAX_ADC_CHANNELS; ch++)
        {
            sum[ch] += raw_values_[ch];
        }
    }

    // 求平均并保存
    for (int ch = 0; ch < MAX_ADC_CHANNELS; ch++)
    {
        averaged_values_[ch] = sum[ch] / 20;
    }
}

void ADCDevice::Task_ADC()
{
    UpdateAverage();
    // 将电池电压传递给 Battery 类
    battery.GetVoltage(averaged_values_[1]);
}

extern "C" void Task_adc(void *argument)
{
    adcDevice.ADC_init();
		battery.Battery_init();
    for(;;)
    {
    adcDevice.Task_ADC();
    battery.Task_Battery();
    osDelay(100);
    }
}
