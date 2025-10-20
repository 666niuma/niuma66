#ifndef __MY_ADC_H
#define __MY_ADC_H

#include "main.h"

#ifndef __ADC_DEVICE_H__
#define __ADC_DEVICE_H__

#include "main.h"
#include "cmsis_os.h"
#include "battery.h"
#define MAX_ADC_INSTANCE   4    // 最多支持的 ADC 实例数
#define MAX_ADC_CHANNELS   6    // 每个 ADC 实例最多几个通道
#define ADC_QUEUE_SIZE     5    // 消息队列长度



class ADCDevice
{
    public:
    uint32_t raw_values_[MAX_ADC_CHANNELS]; // 存储原始 ADC 值
    uint32_t averaged_values_[MAX_ADC_CHANNELS]; // 存储平均后的 ADC 值
    void UpdateAverage();
    void ADC_init();
    ADCDevice(){};
    void Task_ADC();
};

#endif
#endif
