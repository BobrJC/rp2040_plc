
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "plc.h"
#include "stack_macros.h"
#include "iec_types.h"
#include "FreeRTOS.h"
#include "timers.h"
#include "task.h"
#include "hardware/spi.h"
#include "main.h"

extern IEC_TIME __CURRENT_TIME;
void RESOURCE1_run__(); // gen
void task1_func(); //gen
void task2_func(); //gen
void init_freertos() //full gen
{
    TaskHandle_t task1 = NULL;
    TaskHandle_t task2 = NULL;
    xTaskCreate(task1_func, "1", 256, (void*)0, 7, &task1);
    xTaskCreate(task2_func, "2", 256, (void*)1, 7, &task2);
}

void __init_spi() //NOT GEN
{
    spi_init(SPI_PORT, 500000);
    gpio_set_function(SCK, GPIO_FUNC_SPI);
    gpio_set_function(MISO, GPIO_FUNC_SPI);
    gpio_set_function(CS, GPIO_FUNC_SPI);
    gpio_init(CS);
    gpio_set_dir(CS, GPIO_OUT);
    gpio_put(CS, 1);
}

void __retrieve_spi() //NOT GEN
{
    uint16_t buf16bit;
    gpio_put (CS, 0);
    vTaskDelay(1); 
    spi_read_blocking(SPI_PORT, 0, &buf16bit, 1);
    buf16bit <<= 8;
    spi_read_blocking(SPI_PORT, 0, &buf16bit, 1);
}

void __init_0(int task_id)
{
    printf("INIT\r\n");

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

void __retrieve_0(int task_id)
{
    for (int j = 0; j < r_task_sizes[task_id]; j++)
    {
        tasks[task_id].r_pin_reqs[j].state = gpio_get(tasks[task_id].r_pin_reqs[j].pin);
    }
}

void __publish_0(int task_id)
{
    uint8_t w_task_size = w_task_sizes[task_id];
    for (int j = 0; j < w_task_sizes[task_id]; j++)
    {
        gpio_put(tasks[task_id].w_pin_reqs[j].pin, tasks[task_id].w_pin_reqs[j].state);
    }
}

void task1_func(int task_id) //full gen
{
    TaskStatus_t xTaskDetails;
    __init_0(task_id);
    while (1)
    {
        TickType_t tick = xTaskGetTickCount();
        printf("tick1 %i", tick);
        __CURRENT_TIME.tv_sec = tick/1000;
        __CURRENT_TIME.tv_nsec = (tick % 1000) * 1000000;
        __retrieve_0(task_id);
        RESOURCE1_run__(tick);
        __publish_0(task_id);
        vTaskDelay(5);
    }
}

void task2_func(int task_id) //full gen
{
    TaskStatus_t xTaskDetails;
    while (1)
    {
        TickType_t tick = xTaskGetTickCount();
        printf("tick2 %i", tick);
        __CURRENT_TIME.tv_sec = tick/1000;
        __CURRENT_TIME.tv_nsec = (tick % 1000) * 1000000;
        __retrieve_0(task_id);
        RESOURCE1_run__(tick);
        __publish_0(task_id);
        vTaskDelay(5);
    }
}

void __run_task1(unsigned long tick)
{
    __CURRENT_TIME.tv_sec = tick/1000;
    __CURRENT_TIME.tv_nsec = (tick % 1000) * 1000000;

    for (int i = 0; i < TASK_N; i++)
    {
        tasks[i].func(tick);
    } 
}




void __cleanup_0()
{

}