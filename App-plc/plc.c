
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "stack_macros.h"
#include "iec_types.h"

#include "plc.h"

#include "FreeRTOS.h"
#include "timers.h"
#include "task.h"

extern IEC_TIME     __CURRENT_TIME;     // gen
extern void         RESOURCE1_init__(); // gen
extern void         RESOURCE0_init__(); // gen

extern void         RESOURCE1_run__();  // gen
extern void         RESOURCE0_run__();  // gen

void                task1_func();       // gen
void                task2_func();       // gen

uint16_t            buf16bit;           // NOT NEEDED
float               temp;               // NOT NEEDED

void init_freertos() //full gen
{
    TaskHandle_t task1 = NULL;
    TaskHandle_t task2 = NULL;
    xTaskCreate(TASK1_RUN, "1", TASK1_STACK_SIZE, (void*)0, TASK1_PRIORITY, &task1);
    xTaskCreate(TASK2_RUN, "2", TASK2_STACK_SIZE, (void*)1, TASK2_PRIORITY, &task2);
}

void __init_spi() //NOT GEN
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
void __init_adc() //NOT GEN
{
    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(4);
}

void __retrieve_adc() //NOT GEN
{
    /*use value from st code*/
    uint16_t raw = adc_read();
    const float conversion_factor = 3.3f / (1<<12);
    float result = raw * conversion_factor;
    temp = 27 - (result -0.706)/0.001721;
    MD1_0 = temp;
    vTaskDelay(200);
}

void __retrieve_spi() //NOT GEN
{
    /*use value from st code*/
    gpio_put (CS, 0);
    vTaskDelay(1); 
    spi_read_blocking(SPI_PORT, 0, &buf16bit, 1);
    buf16bit <<= 8;
    spi_read_blocking(SPI_PORT, 0, &buf16bit, 1);
    gpio_put(CS, 1);
    buf16bit >>= 3;
    MD0_0 = (float)buf16bit * 0.25;
    vTaskDelay(200);     
}

void __init_uart() //NOT GEN
{
    stdio_init_all();
}
//gen only when needed
void __init_GPIO(int task_id)
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
//gen only when needed
void __retrieve_GPIO(int task_id)
{
    for (int j = 0; j < r_task_sizes[task_id]; j++)
    {
        tasks[task_id].r_pin_reqs[j].value = (void*)gpio_get(tasks[task_id].r_pin_reqs[j].pin);
    }
}
//gen only when needed
void __publish_GPIO(int task_id)
{
    uint8_t w_task_size = w_task_sizes[task_id];
    for (int j = 0; j < w_task_sizes[task_id]; j++)
    {
        gpio_put(tasks[task_id].w_pin_reqs[j].pin, (bool*)tasks[task_id].w_pin_reqs[j].value);
    }
}

void task1_func(int task_id) //full gen
{
    __init_spi();
    RESOURCE1_init__();
    while (1)
    {
        TickType_t tick = xTaskGetTickCount();
        __CURRENT_TIME.tv_sec = tick/1000;
        __CURRENT_TIME.tv_nsec = (tick % 1000) * 1000000;
        __retrieve_spi();
        tasks[task_id].func(tick);
        vTaskDelay(5);
    }
}

void task2_func(int task_id) //full gen
{
    __init_uart();
    RESOURCE0_init__();
    __init_adc();
    while (1)
    {
        TickType_t tick = xTaskGetTickCount();
        __CURRENT_TIME.tv_sec = tick/1000;
        __CURRENT_TIME.tv_nsec = (tick % 1000) * 1000000;
        __retrieve_adc();
        tasks[task_id].func(tick);
        printf("_MD0_0 = %f С\n", *__MD0_0);
        printf("_MD1_0 = %f С\n", *__MD1_0);
        printf("_MD0_1 = %f F\n", *__MD0_1);
        printf("_MD1_1 = %f F\n", *__MD1_1);
        printf("diff %i\r\n", *__MX1_1);
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
//gen only when needed
void __cleanup_0()
{

}