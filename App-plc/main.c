#include "iec_types.h"
#include "stddef.h"

extern void __init_0();
extern void __retrieve_0();
extern void __publish_0();
extern void __run(unsigned long* tick);
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