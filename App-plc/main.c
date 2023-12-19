#include "iec_types.h"
#include "stddef.h"

void __init_0();
void __retrieve_0();
void __publish_0();
void __run_tasks(unsigned long* tick);
void init_freertos();
IEC_TIME __CURRENT_TIME;
IEC_BOOL __DEBUG = 0;
unsigned long __tick = 0;
char *PLC_ID = NULL;


int main() 
{
    init_freertos();

    __init_0();
    while(1)
    {
        unsigned long tick = 0;
        __retrieve_0();
        __run_tasks(&tick);
        __publish_0();
    }

}