#include "plc.h"
#include "task.h"

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "stack_macros.h"
#include "iec_types.h"
#include "FreeRTOS.h"
#include "timers.h"

IEC_TIME       __CURRENT_TIME;
extern void     RESOURCE0_init__();
extern void     RESOURCE1_init__();

extern void     RESOURCE0_run__();
extern void     RESOURCE1_run__();

void task0_func();  
void task1_func();  

void init_freertos()
{
    TaskHandle_t task0 = NULL;
    TaskHandle_t task1 = NULL;
    xTaskCreate(task0_func, "0", TASK0_STACK_SIZE, (void*)0, TASK0_PRIORITY, &task0);
    xTaskCreate(task1_func, "1", TASK1_STACK_SIZE, (void*)1, TASK1_PRIORITY, &task1);
}

void __init_task0_adc()
{
}

void __retrieve_task0_adc()
{
}

void __publish_task0_adc()
{
}

void __init_gpio(int task_id)
{
    for (int j = 0; j < r_task_sizes[task_id]; j++)
    {
        gpio_init(tasks[task_id].r_pin_reqs[j].pin);
        gpio_set_dir(tasks[task_id].r_pin_reqs[j].pin, false);
    }
    for (int j = 0; j < w_task_sizes[task_id]; j++) 
    {
        gpio_init(tasks[task_id].w_pin_reqs[j].pin);
        gpio_set_dir(tasks[task_id].w_pin_reqs[j].pin, true);
    }
}

void __retrieve_gpio(int task_id)
    {
        for (int j = 0; j < r_task_sizes[task_id]; j++)
        {
            tasks[task_id].r_pin_reqs[j].value = (void*)gpio_get(tasks[task_id].r_pin_reqs[j].pin);
        }
    }

void __publish_gpio(int task_id)
{
    uint8_t w_task_size = w_task_sizes[task_id];
    for (int j = 0; j < w_task_sizes[task_id]; j++)
    {
        gpio_put(tasks[task_id].w_pin_reqs[j].pin, (bool*)tasks[task_id].w_pin_reqs[j].value);
    }
}


void __init_task1_spi()
{
}

void __retrieve_task1_spi()
{
}

void __publish_task1_spi()
{
}

void task0_func(int task_id)
{
    // USER CODE HERE
    RESOURCE0_init__();
    __init_task0_adc();
    __init_gpio(task_id);
    while (1)
    {
        TickType_t tick = xTaskGetTickCount();
        __CURRENT_TIME.tv_sec = tick/1000;
        __CURRENT_TIME.tv_nsec = (tick % 1000) * 1000000;
        __retrieve_task0_adc();
        __retrieve_gpio(task_id);
        tasks[task_id].func(tick);
        __publish_task0_adc();
        __publish_gpio(task_id);
        vTaskDelay(5);
    }
}

void task1_func(int task_id)
{
    // USER CODE HERE
    RESOURCE1_init__();
    __init_task1_spi();
    while (1)
    {
        TickType_t tick = xTaskGetTickCount();
        __CURRENT_TIME.tv_sec = tick/1000;
        __CURRENT_TIME.tv_nsec = (tick % 1000) * 1000000;
        __retrieve_task1_spi();
        tasks[task_id].func(tick);
        __publish_task1_spi();
        vTaskDelay(5);
    }
}

