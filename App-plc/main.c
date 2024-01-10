#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>


void init_freertos();

int main() 
{
    init_freertos();
    vTaskStartScheduler();
}