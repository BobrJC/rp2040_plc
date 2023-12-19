#include "iec_types.h"
#include "stddef.h"
#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

extern void __init_0();
extern void __retrieve_0();
extern void __publish_0();
extern void __run(unsigned long* tick);
void init_freertos();
IEC_TIME __CURRENT_TIME;
IEC_BOOL __DEBUG = 0;
unsigned long __tick = 0;
char *PLC_ID = NULL;


int main() 
{
    stdio_init_all();
    sleep_ms(10000);
    init_freertos();
    vTaskStartScheduler();
    sleep_ms(23000);
    unsigned long tick = 0;

}