#ifndef __JOYSTICK_H
#define __JOYSTICK_H



#include "protocol.h"
#ifdef __cplusplus
extern "C"
{
#endif
#include "stm32f1xx_hal.h" 
#ifdef __cplusplus
}
#endif
#include <stm32f103xb.h>



class JOYStick :public Subscriber
{
    public:
    void DataReceivedCallback(uint8_t ID,uint8_t length,const uint8_t *byte) override; // data callback
    JOYStick() = default;
    void Joystick_init();
    void Scan();
    void Task_Joystick();
    typedef struct {
    GPIO_TypeDef *port;  // GPIO端口，例如 GPIOA
    uint16_t pin;        // GPIO引脚，例如 GPIO_PIN_0
    } GPIO_Pin_t;

    enum class ButtonActionType
    {
        Toggle,    // 按键状态翻转
        Increment, // 状态递增
        Decrement, // 状态递减
        Onlyread,  // 仅读取
        Custom     // 自定义操作
    };
    typedef struct ButtonConfig
    {
        GPIO_Pin_t single;
        bool *currentState;
        bool *lastState;              // 上次按键状态
        uint8_t *toggleState;         // 状态变量
        uint8_t maxState;             // 最大状态
        ButtonActionType actionType;  // 按键行为类型
        void (*customAction)();       // 自定义操作函数指针
    }ButtonConfig;
    typedef enum {
    SWITCH_TYPE_2 = 0,
    SWITCH_TYPE_3
    } SwitchType;
    typedef struct 
    {
        SwitchType type; // 开关类型（2档或3档）
    union 
    {
        GPIO_Pin_t single;  // 按钮或两档开关使用的单个引脚
        struct {
            GPIO_Pin_t pin1;
            GPIO_Pin_t pin2;
        } triple;           // 三档开关使用的两个引脚
    } gpio;

    uint8_t *currentState;
    uint8_t *lastState;
    uint8_t maxState;
    void (*customAction)(); // 可选：自定义操作函数
    } SwitchConfig_t;

    typedef struct ControllerData_t
    {
    // 按键数据（bool类型）
    bool btnLY;
    bool btnLY_last;
    bool btnLB;
    bool btnLB_last;
    bool btnLA;
    bool btnLA_last;
    bool btnLX;
    bool btnLX_last;
    bool btnRY;
    bool btnRY_last;
    bool btnRB;
    bool btnRB_last;
    bool btnRA;
    bool btnRA_last;
    bool btnRX;
    bool btnRX_last;
    uint8_t Switch3Left;
    uint8_t Switch3Right;
    uint8_t Switch3Left_last;
    uint8_t Switch3Right_last;
    uint8_t Switch2Left;
    uint8_t Switch2Right;
    uint8_t Switch2Left_last;
    uint8_t Switch2Right_last;
    // 霍尔值（16位数值）,给出回正默认值
    uint16_t joyLHori=33333;
    uint16_t joyLVert=33333;
    uint16_t joyRHori=33333;
    uint16_t joyRVert=33333;
    uint16_t trigLT;
    uint16_t trigRT;
    float joyLHori_map;
    float joyLVert_map;
    float joyRHori_map;
    float joyRVert_map;
    float trigLT_map;
    float trigRT_map;
    } ControllerData_t;

    ControllerData_t joystick_data;

    // ===================== 按钮配置 =====================

ButtonConfig btnLYConfig = {
    .single = {GPIOA, GPIO_PIN_0},
    .currentState = &joystick_data.btnLY,
    .lastState = &joystick_data.btnLY_last,
    .toggleState = nullptr,
    .maxState = 1,
    .actionType = ButtonActionType::Onlyread,
    .customAction = nullptr
};

ButtonConfig btnLBConfig = {
    .single = {GPIOA, GPIO_PIN_1},
    .currentState = &joystick_data.btnLB,
    .lastState = &joystick_data.btnLB_last,
    .toggleState = nullptr,
    .maxState = 1,
    .actionType = ButtonActionType::Onlyread,
    .customAction = nullptr
};

ButtonConfig btnLAConfig = {
    .single = {GPIOA, GPIO_PIN_2},
    .currentState = &joystick_data.btnLA,
    .lastState = &joystick_data.btnLA_last,
    .toggleState = nullptr,
    .maxState = 1,
    .actionType = ButtonActionType::Onlyread,
    .customAction = nullptr
};

ButtonConfig btnLXConfig = {
    .single = {GPIOA, GPIO_PIN_3},
    .currentState = &joystick_data.btnLX,
    .lastState = &joystick_data.btnLX_last,
    .toggleState = nullptr,
    .maxState = 1,
    .actionType = ButtonActionType::Onlyread,
    .customAction = nullptr
};

ButtonConfig btnRYConfig = {
    .single = {GPIOA, GPIO_PIN_4},
    .currentState = &joystick_data.btnRY,
    .lastState = &joystick_data.btnRY_last,
    .toggleState = nullptr,
    .maxState = 1,
    .actionType = ButtonActionType::Onlyread,
    .customAction = nullptr
};

ButtonConfig btnRBConfig = {
    .single = {GPIOA, GPIO_PIN_5},
    .currentState = &joystick_data.btnRB,
    .lastState = &joystick_data.btnRB_last,
    .toggleState = nullptr,
    .maxState = 1,
    .actionType = ButtonActionType::Onlyread,
    .customAction = nullptr
};

ButtonConfig btnRAConfig = {
    .single = {GPIOA, GPIO_PIN_6},
    .currentState = &joystick_data.btnRA,
    .lastState = &joystick_data.btnRA_last,
    .toggleState = nullptr,
    .maxState = 1,
    .actionType = ButtonActionType::Onlyread,
    .customAction = nullptr
};

ButtonConfig btnRXConfig = {
    .single = {GPIOA, GPIO_PIN_7},
    .currentState = &joystick_data.btnRX,
    .lastState = &joystick_data.btnRX_last,
    .toggleState = nullptr,
    .maxState = 1,
    .actionType = ButtonActionType::Onlyread,
    .customAction = nullptr
};

// ===================== 开关配置 =====================

SwitchConfig_t Switch3LeftConfig = {
    .type = SWITCH_TYPE_3,
    .gpio = { .triple = { {GPIOB, GPIO_PIN_0}, {GPIOB, GPIO_PIN_1} } },
    .currentState = &joystick_data.Switch3Left,
    .lastState = &joystick_data.Switch3Left_last,
    .maxState = 2,
    .customAction = nullptr
};

SwitchConfig_t Switch3RightConfig = {
    .type = SWITCH_TYPE_3,
    .gpio = { .triple = { {GPIOB, GPIO_PIN_2}, {GPIOB, GPIO_PIN_3} } },
    .currentState = &joystick_data.Switch3Right,
    .lastState = &joystick_data.Switch3Right_last,
    .maxState = 2,
    .customAction = nullptr
};

SwitchConfig_t Switch2LeftConfig = {
    .type = SWITCH_TYPE_2,
    .gpio = { .single = {GPIOB, GPIO_PIN_4} }, 
    .currentState = &joystick_data.Switch2Left,
    .lastState = &joystick_data.Switch2Left_last,
    .maxState = 1,
    .customAction = nullptr
};

SwitchConfig_t Switch2RightConfig = {
    .type = SWITCH_TYPE_2,
    .gpio = { .single = {GPIOB, GPIO_PIN_5} }, 
    .currentState = &joystick_data.Switch2Right,
    .lastState = &joystick_data.Switch2Right_last,
    .maxState = 1,
    .customAction = nullptr
};

};

#endif 
