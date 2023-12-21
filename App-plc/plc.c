
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
#include "hardware/adc.h"
#include "main.h"

extern IEC_TIME __CURRENT_TIME;
extern void RESOURCE1_run__(); // gen
extern void RESOURCE0_run__(); // gen
void task1_func(); //gen
void task2_func(); //gen
uint16_t buf16bit;
float temp;

void init_freertos() //full gen
{
    TaskHandle_t task1 = NULL;
    TaskHandle_t task2 = NULL;
    xTaskCreate(task1_func, "1", 1024, (void*)0, 7, &task1);
    xTaskCreate(task2_func, "2", 256, (void*)1, 7, &task2);
}

void __init_spi() //NOT GEN
{
    printf("task 1 started");
    stdio_init_all();
    spi_init(SPI_PORT, 500000);
    gpio_set_function(SCK, GPIO_FUNC_SPI);
    gpio_set_function(MISO, GPIO_FUNC_SPI);
    gpio_set_function(CS, GPIO_FUNC_SPI);
    gpio_init(CS);
    gpio_set_dir(CS, GPIO_OUT);
    gpio_put(CS, 1);
}
void __init_adc()
{
    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(4);
}

void __retrieve_adc()
{
    uint16_t raw = adc_read();
    const float conversion_factor = 3.3f / (1<<12);
    float result = raw * conversion_factor;
    temp = 27 - (result -0.706)/0.001721;
    printf("Temp_internal = %f C\n", temp);
    MD1_0 = temp;
    printf("_MD1_0 = %f C\n", MD1_0);

    vTaskDelay(200);
}

void __retrieve_spi() //NOT GEN
{
    gpio_put (CS, 0);
    vTaskDelay(1); 
    spi_read_blocking(SPI_PORT, 0, &buf16bit, 1);
    buf16bit <<= 8;
    spi_read_blocking(SPI_PORT, 0, &buf16bit, 1);
    gpio_put(CS, 1);

    buf16bit >>= 3;
    printf("buf = %.2f C \n", buf16bit*0.25);
    MD0_0 = (float)buf16bit;
    printf("Temp = %.2f C \n", (MD0_0)*0.25);
    vTaskDelay(200);     
}
void __init_uart()
{
    stdio_init_all();
}
void __init_0(int task_id)
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

void __retrieve_0(int task_id)
{
    for (int j = 0; j < r_task_sizes[task_id]; j++)
    {
        tasks[task_id].r_pin_reqs[j].value = (void*)gpio_get(tasks[task_id].r_pin_reqs[j].pin);
    }
}

void __publish_0(int task_id)
{
    uint8_t w_task_size = w_task_sizes[task_id];
    for (int j = 0; j < w_task_sizes[task_id]; j++)
    {
        gpio_put(tasks[task_id].w_pin_reqs[j].pin, (bool*)tasks[task_id].w_pin_reqs[j].value);
    }
}

void task1_func(int task_id) //full gen
{
    TaskStatus_t xTaskDetails;
    __init_spi();
    while (1)
    {
        TickType_t tick = xTaskGetTickCount();
        __CURRENT_TIME.tv_sec = tick/1000;
        __CURRENT_TIME.tv_nsec = (tick % 1000) * 1000000;
        __retrieve_spi();
        RESOURCE1_run__(tick);
       
        //__publish_0(task_id);
        vTaskDelay(5);
    }
}

void task2_func(int task_id) //full gen
{
    TaskStatus_t xTaskDetails;
    __init_uart();
    __init_adc();
    while (1)
    {
        TickType_t tick = xTaskGetTickCount();
        __CURRENT_TIME.tv_sec = tick/1000;
        __CURRENT_TIME.tv_nsec = (tick % 1000) * 1000000;
        __retrieve_adc();
        RESOURCE0_run__(tick);
        printf("_MD0_0 = %f F\n", *__MD0_0);
        printf("_MD1_0 = %f F\n", *__MD1_0);
        printf("_MD0_1 = %f F\n", *__MD0_1);
        printf("_MD1_1 = %f F\n", *__MD1_1);
        printf("diff %i\r\n", __MX1_1);
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