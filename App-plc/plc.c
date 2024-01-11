#include "plc.h"
#include "task.h"

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "stack_macros.h"
#include "iec_types.h"
#include "FreeRTOS.h"
#include "timers.h"

IEC_TIME        __CURRENT_TIME;
extern void     RESOURCE0_init__();
extern void     RESOURCE1_init__();

extern void     RESOURCE0_run__();
extern void     RESOURCE1_run__();

void task0_func();  
void task1_func();  

uint16_t        buf16bit;        


void init_freertos()
{
    TaskHandle_t task0 = NULL;
    TaskHandle_t task1 = NULL;
    xTaskCreate(task0_func, "0", TASK0_STACK_SIZE, (void*)0, TASK0_PRIORITY, &task0);
    xTaskCreate(task1_func, "1", TASK1_STACK_SIZE, (void*)1, TASK1_PRIORITY, &task1);
}

void __init_task0_adc()
{
    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(4);
}

void __retrieve_task0_adc()
{
    uint16_t raw = adc_read();
    const float conversion_factor = 3.3f / (1<<12);
    float result = raw * conversion_factor;
    cel_0 = 27 - (result -0.706)/0.001721;
    vTaskDelay(200);
}

void __publish_task0_adc()
{
}

void __init_task1_spi()
{
    stdio_init_all();
    spi_init(SPI_PORT, 500000);
    gpio_set_function(SCK, GPIO_FUNC_SPI);
    gpio_set_function(MISO, GPIO_FUNC_SPI);
    gpio_set_function(CS, GPIO_FUNC_SPI);
    gpio_init(CS);
    gpio_set_dir(CS, GPIO_OUT);
    gpio_put(CS, 1);
}

void __retrieve_task1_spi()
{
    gpio_put (CS, 0);
    vTaskDelay(1); 
    spi_read_blocking(SPI_PORT, 0, &buf16bit, 1);
    buf16bit <<= 8;
    spi_read_blocking(SPI_PORT, 0, &buf16bit, 1);
    gpio_put(CS, 1);
    buf16bit >>= 3;
    cel_1 = (float)buf16bit * 0.25;
    vTaskDelay(200);   
}

void __publish_task1_spi()
{
}

void task0_func(int task_id)
{
    // USER CODE HERE
    RESOURCE0_init__();
    __init_task0_adc();
    while (1)
    {
        TickType_t tick = xTaskGetTickCount();
        __CURRENT_TIME.tv_sec = tick/1000;
        __CURRENT_TIME.tv_nsec = (tick % 1000) * 1000000;
        __retrieve_task0_adc();
        tasks[task_id].func(tick);
        __publish_task0_adc();
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
        printf("_MD0_0 = %f С\n", *__MD0_0);
        printf("_MD1_0 = %f С\n", *__MD1_0);
        printf("_MD0_1 = %f F\n", *__MD0_1);
        printf("_MD1_1 = %f F\n", *__MD1_1);
        printf("diff %i\r\n", *__MX1_1);
        vTaskDelay(5);
    }
}

