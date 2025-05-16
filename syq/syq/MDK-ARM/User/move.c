#include "main.h"
#include "tim.h"
move_t move;
Servo_t Servo;
Chassis_Motor_t Motor;
void move_init()
{
    move.speed.Speed_Vx = 0;
    move.speed.Speed_Vy = 0;
    move.distance = 0;
    move.time_acceleration = 0;
    move.time_deceleration = 0;
    move.time_constant = 0;
}

void time_calc(move_t *move_time_calc)
{
    //时间计算
    
    move_time_calc->time_acceleration = (maxVx - V0) / ACCELERATION;
    move_time_calc->time_deceleration = (maxVx - V0) / DECELERATION;
    float distance_acceleration = V0 * move_time_calc->time_acceleration + 0.5 * ACCELERATION * move_time_calc->time_acceleration * move_time_calc->time_acceleration;
    float distance_deceleration = V0 * move_time_calc->time_deceleration + 0.5 * DECELERATION * move_time_calc->time_deceleration * move_time_calc->time_deceleration;
    float distance_constant = move.distance - (distance_acceleration + distance_deceleration);
    if (distance_constant > 0)
    {
        move_time_calc->time_constant = distance_constant / maxVx;
    }
    else
    {
        move_time_calc->time_constant = 0;
    } 
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM8)
    {
        //定时器中断
        //更新pwm值
    // 判断是否有设定x轴或y轴速度，再决定是否加速
    if (move.speed.Speed_Vx != 0)
    {
        if (motor.chassisVx < move.speed.Speed_Vx)
        {
            motor.chassisVx += ACCELERATION * motor_time;
            if (motor.chassisVx > move.speed.Speed_Vx)
                {
                    motor.chassisVx = move.speed.Speed_Vx;
                }
        }
        else if (motor.chassisVx > move.speed.Speed_Vx)
        {
            motor.chassisVx -= ACCELERATION * motor_time;
            if (motor.chassisVx < move.speed.Speed_Vx)
                motor.chassisVx = move.speed.Speed_Vx;
        }
    }
    else 
    {
        motor.chassisVx = 0;
    }


    if (move.speed.Speed_Vy != 0)
    {
        if (motor.chassisVy < move.speed.Speed_Vy)
        {
            motor.chassisVy += ACCELERATION * motor_time;
            if (motor.chassisVy > move.speed.Speed_Vy)
                motor.chassisVy = move.speed.Speed_Vy;
        }
        else if (motor.chassisVy > move.speed.Speed_Vy)
        {
            motor.chassisVy -= ACCELERATION * motor_time;
            if (motor.chassisVy < move.speed.Speed_Vy)
                motor.chassisVy = move.speed.Speed_Vy;
        }
    }
    }
        else 
        {
            motor.chassisVy = 0;
        }
    
        
        if (motor.chassisVx > maxVx)
        {
            motor.chassisVx = maxVx;
        }

        if (motor.chassisVy > maxVy)
        {
            motor.chassisVy = maxVy;
        }
        Task_Chassis();
}



//定时中断更新pwm值

void move_linearAcceleration(move_t *move_linearAcceleration)
{
    //线性加速
    int n = 0;//加速段数
    n = move_linearAcceleration->time_acceleration / motor_time;
    float time = 0;
    float distance = 0;
    float speed = 0;
    for (int i = 0; i < n; i++)
    {
        time = i * motor_time;
        if(currentstate == STATE_SECTION_2)
        {
            move_linearAcceleration->speed.Speed_Vx  = V0 + ACCELERATION * time;
            move_linearAcceleration->speed.Speed_Vy  = V0;
        }
        if(currentstate == STATE_SECTION_4)
        {
            move_linearAcceleration->speed.Speed_Vy  = V0 + ACCELERATION * time;
            move_linearAcceleration->speed.Speed_Vx  = V0;
        }
        
        HAL_TIM_PeriodElapsedCallback(&htim8);
        //更新速度
    } 

}

void move_deceleration(move_t *move_deceleration)
{
    //线性减速
    int n = 0;//减速段数
    n = move_deceleration->time_deceleration / motor_time;
    float time = 0;
    float distance = 0;
    float speed = 0;
    for (int i = 0; i < n; i++)
    {
        time = i * motor_time;
        if(currentstate == STATE_SECTION_3)
        {
            move_deceleration->speed.Speed_Vx  = V0 + DECELERATION * time;
            move_deceleration->speed.Speed_Vy  = V0;
        }
        if(currentstate == STATE_SECTION_4)
        {
            move_deceleration->speed.Speed_Vy  = V0 + DECELERATION * time;
            move_deceleration->speed.Speed_Vx  = V0;
        }
        
        HAL_TIM_PeriodElapsedCallback(&htim8);
        //更新速度
    } 
}

void move_constant(move_t *move_constant)
{
    //匀速
    int n = 0;//匀速段数
    n = move_constant->time_constant / motor_time;
    float time = 0;
    float distance = 0;
    float speed = 0;
    for (int i = 0; i < n; i++)
    {
        time = i * motor_time;
        if(currentstate == STATE_SECTION_2)
        {
            move_constant->speed.Speed_Vx  = maxVx;
            move_constant->speed.Speed_Vy  = V0;
        }
        if(currentstate == STATE_SECTION_3)
        {
            move_constant->speed.Speed_Vx  = V0;
            move_constant->speed.Speed_Vy  = maxVy;
        }
        
        HAL_TIM_PeriodElapsedCallback(&htim8);
        //更新速度
    } 
}



void move_stop(move_t *move_stop)
{
    //停止
    move_stop->speed.SetSpeed_Vx  = 0;
    move_stop->speed.SetSpeed_Vy  = 0;
    HAL_TIM_PeriodElapsedCallback(&htim8);
    //更新速度
}

void Chassis_Set_Speed_From_Move(Chassis_Motor_t *chassis, move_t *move)
{
    float vx = move->speed.Speed_Vx;
    float vy = move->speed.Speed_Vy;
    chassis->chassisVx = vx;
    chassis->chassisVy = vy;
}

void Task_move()
{
    // Infinite loop
    if (currentstate == STATE_SECTION_1)
    {
        move_init();
        move.distance = START_TO_LIGHT_DISTANCE;
        time_calc(&move);
        move_linearAcceleration(&move);
        move_constant(&move);
        move_deceleration(&move);
        move_stop(&move);
    }
    else if (currentstate == STATE_SECTION_2)
    {
        move_init();
        move.distance = LIGHT_TO_ENDLINE_DISTANCE;
        time_calc(&move);
        move_linearAcceleration(&move);
        move_constant(&move);
        move_deceleration(&move);
        move_stop(&move);
    }
    else if (currentstate == STATE_SECTION_3)
    {
        move_init();
        move.distance = ENDLINE_TO_FINAL;
        time_calc(&move);
        move_linearAcceleration(&move);
        move_constant(&move);
        move_deceleration(&move);
        move_stop(&move);
    }
    else if (currentstate == STATE_SECTION_4)
    {
        move_init();
        move.distance = ENDLINE_TO_FINAL;
        time_calc(&move);
        move_linearAcceleration(&move);
        move_constant(&move);
        move_deceleration(&move);
        move_stop(&move);
    }
    else if (currentstate == STATE_DONE)
    {
        // Do nothing
        move_stop(&move);
    }
}

void Task()
{
    Motor_Init(&Motor);
    Servo_Init();
    state_machine_init();
    move_init();


}

typedef enum
{
    STATE_SECTION_1,
    STATE_SECTION_2,
    STATE_SECTION_3,
    STATE_SECTION_4,
    STATE_DONE
}VehicleState;

VehicleState currentstate = STATE_SECTION_1;

void state_machine_init(VehicleState *currentstate)
{
    // Initialize the state machine
    currentstate = STATE_SECTION_1;
}

void state_machine_update()
{
    switch (currentstate)
    {
        case STATE_SECTION_1:
            // Perform actions for section 1
            Servo_Init();
            HAL_Delay(100-1);
            currentstate = STATE_SECTION_2;
            
            break;

        case STATE_SECTION_2:
            // Perform actions for section 2
		
            Servo_Set(&Servo);
            
            move.distance = START_TO_LIGHT_DISTANCE;
            if (condition_met)
            {
                currentstate = STATE_SECTION_3;
            }
            break;

        case STATE_SECTION_3:
            // Perform actions for section 3
           move.distance = LIGHT_TO_ENDLINE_DISTANCE;
            if (condition_met)
            {
                currentstate = STATE_DONE;
            }
            break;
        case STATE_SECTION_4:
            // Perform actions for section 4

            move.distance = ENDLINE_TO_FINAL;
            if (condition_met)
            {
                currentstate = STATE_DONE;
            }
            break;

        case STATE_DONE:
            // Perform actions when done
             move.distance = ENDLINE_TO_FINAL;
            break;
    }
}


