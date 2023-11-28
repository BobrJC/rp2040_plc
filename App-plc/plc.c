
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "plc.h"

void init_freertos()
{
    TaskHandle_t gpio_task_handle = NULL;
    TaskHandle_t pico_task_handle = NULL;
    xMutex = xQueueCreateMutex(queueQUEUE_TYPE_MUTEX);
}

void __init_0()
{
    xSemaphoreTake(xMutex, portMAX_DELAY);
    for (int i = 0; i < TASK_N; i++)
    {
        for (int j = 0; j < R_REQ_N; j++)
        {
            gpio_init(tasks[i].r_pin_reqs[j].pin);
            gpio_set_dir(tasks[i].r_pin_reqs[j].pin, tasks[i].r_pin_reqs[j].dir);
        }
        for (int j = 0; j < W_REQ_N; j++)
        {
            gpio_init(tasks[i].r_pin_reqs[j].pin);
            gpio_set_dir(tasks[i].w_pin_reqs[j].pin, tasks[i].w_pin_reqs[j].dir);
        }
    }
}

void __retrieve_0()
{
    for (int i = 0; i < TASK_N; i++)
    {
        for (int j = 0; j < R_REQ_N; j++)
        {
            tasks[i].r_pin_reqs[j].state = gpio_get(tasks[i].r_pin_reqs[j].pin);
        }
    }
}

void __run_tasks(unsigned long *tick)
{
    for (int i = 0; i < TASK_N; i++)
    {
        tasks[i].func(*tick++);
    } 
}

void __publish_0()
{
    for (int i = 0; i < TASK_N; i++)
    {
        for (int j = 0; j < W_REQ_N; j++)
        {
            gpio_put(tasks[i].w_pin_reqs[j].pin, tasks[i].w_pin_reqs[j].state);
        }
    }
    xSemaphoreGive(xMutex);
}

void __cleanup_0()
{
    
}