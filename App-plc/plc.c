
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "plc.h"
#include "stack_macros.h"

void init_freertos()
{
    TaskHandle_t gpio_task_handle = NULL;
    TaskHandle_t pico_task_handle = NULL;
    gpio_init(0);
    gpio_set_dir(0, GPIO_OUT);
    gpio_put(0, 1);
    sleep_ms(1000);

    //xMutex = xQueueCreateMutex(queueQUEUE_TYPE_MUTEX);
}

void __init_0()
{
    //xSemaphoreTake(xMutex, portMAX_DELAY);
    for (int i = 0; i < TASK_N; i++)
    {
        for (int j = 0; j < r_task_sizes[i]; j++)
        {
            switch (tasks[i].r_pin_reqs[j].type)
            {
            case GPIO:
                gpio_init(tasks[i].r_pin_reqs[j].pin);
                gpio_set_dir(tasks[i].r_pin_reqs[j].pin, false);
                break;
            case UART:
                break;
            case SPI:
                break;
            default:
                break;
            }
            
        }
        for (int j = 0; j < w_task_sizes[i]; j++)
        {
            switch (tasks[i].w_pin_reqs[j].type)
            {
            case GPIO:
                gpio_init(tasks[i].r_pin_reqs[j].pin);
                gpio_set_dir(tasks[i].r_pin_reqs[j].pin, false);
                break;
            case UART:
                break;
            case SPI:
                break;
            default:
                break;
            }
        }
    }
}

void __retrieve_0()
{
    for (int i = 0; i < TASK_N; i++)
    {
        for (int j = 0; j < r_task_sizes[i]; j++)
        switch (tasks[i].w_pin_reqs[j].type)
        {
        case GPIO:
            tasks[i].r_pin_reqs[j].state = gpio_get(tasks[i].r_pin_reqs[j].pin);
            break;
        case UART:
            break;
        case SPI:
            break;
        default:
            break;
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
        uint8_t w_task_size = w_task_sizes[i];
        for (int j = 0; j < w_task_sizes[i]; j++)
        {
            switch (tasks[i].w_pin_reqs[j].type)
            {
            case GPIO:
                tasks[i].r_pin_reqs[j].state = gpio_get(tasks[i].r_pin_reqs[j].pin);
                break;
            case UART:
                break;
            case SPI:
                break;
            default:
                break;
            }
            gpio_put(tasks[i].w_pin_reqs[j].pin, tasks[i].w_pin_reqs[j].state);
        }
    }
    //xSemaphoreGive(xMutex);
}

void __cleanup_0()
{

}