// # pragma once
// #ifndef __TASKMANAGER_H__
// #define __TASKMANAGER_H__


// #ifdef __cplusplus
// extern "C" {
// #include <cmsis_os2.h>
// #endif
// #ifdef __cplusplus
// }

// #define MAX_TASKS 10
// #define MAX_CLASSES_PER_TASK 20

// class TaskEntry
// {
//     public:
//     virtual void Function_Entry() = 0;
//     virtual ~TaskEntry() = default;
//     char name[16];

// };

// struct TaskInfo
// {
//     osThreadId_t Handle = nullptr;
//     char name[16];
//     osPriority_t priority = osPriorityNormal;
//     TaskEntry *taskObj[MAX_CLASSES_PER_TASK] = {nullptr};
//     int class_index = 0;
//     uint32_t stack_size = 8 * 128;
// };

// class TaskManager
// {
//     public:
//     void Task_prepare(int Task_ID,osPriority_t priority ,uint32_t stack_size=2*128);
//     void Task_register(int Task_ID, TaskEntry *obj);
//     private:
//     static TaskInfo taskList[MAX_TASKS];
//     static void TaskFunction(void *argument);
// };





// #endif
// #endif
