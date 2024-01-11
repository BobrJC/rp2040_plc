#ifndef PLCH
#define PLCH

#include "structs.h"
#include "pico/stdlib.h"
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <semphr.h>
#include "hardware/spi.h"
#include "hardware/adc.h"

#define TASK_N 1 // from script (для циклов)
#define MAX_REQS_N 10

// ---------- TASK 1 ----------
#define TASK1_PRIORITY 10           // from resource_X.c
#define TASK1_RUN task1_func   // from resource_X.c
#define TASK1_STACK_SIZE 256        // from csv
//part needed only tish GPIO pins
#define TASK1_N_W_PIN 1             // from csv (нужно для циклов)
#define TASK1_N_R_PIN 0             // from csv

#define TASK1_R_PIN_1 9             // from csv
#define TASK1_R_PIN_1_STATE 0       // default

#define TASK1_W_PIN_1 0             // from csv
#define TASK1_W_PIN_1_STATE 0       // default

#define TASK1__MX0_0_2_13 0         // from csv


// ---------- TASK 2 ----------
#define TASK2_PRIORITY 2            // from csv
#define TASK2_RUN task2_func   // from resource_X.c
#define TASK2_STACK_SIZE 256        // from csv
//part needed only tish GPIO pins
#define TASK2_N_W_PIN 1             // from csv (нужно для циклов)
#define TASK2_N_R_PIN 0             // from csv

#define TASK2_R_PIN_1 9             // from csv
#define TASK2_R_PIN_1_STATE 0       // default

#define TASK2_W_PIN_1 0             // from csv
#define TASK2_W_PIN_1_STATE 0       // default

#define TASK2__MX0_0_2_0 0      // from csv

// ---------- SPI_VARS -----------
#define MISO 16
#define CS 17
#define SCK 18
#define SPI_PORT spi0

extern void TASK1_RUN(unsigned long tick); //gen

typedef struct task {
    const uint8_t priority;
    w_request_t w_pin_reqs[MAX_REQS_N]; 
    r_request_t r_pin_reqs[MAX_REQS_N]; 
    void (*func)(unsigned long); 
} task_t;

task_t tasks[TASK_N] = {
    {
        .priority = TASK1_PRIORITY, 
        .func = TASK1_RUN, 
        .w_pin_reqs = {},
        .r_pin_reqs = {},
    },
    {
        .priority = TASK2_PRIORITY, 
        .func = TASK2_RUN, 
        .w_pin_reqs = {},
        .r_pin_reqs = {},
    },
};

float MD0_1;    //GEN good names from st
float MD0_0;    //GEN good names from st
float MD1_0;    //GEN good names from st
float MD1_1;    //GEN good names from st
int MX1_1;      //GEN good names from st


/*  in st types are without IEC_

typedef uint8_t  IEC_BOOL;

typedef int8_t    IEC_SINT;
typedef int16_t   IEC_INT;
typedef int32_t   IEC_DINT;
typedef int64_t   IEC_LINT;

typedef uint8_t    IEC_USINT;
typedef uint16_t   IEC_UINT;
typedef uint32_t   IEC_UDINT;
typedef uint64_t   IEC_ULINT;

typedef uint8_t    IEC_BYTE;
typedef uint16_t   IEC_WORD;
typedef uint32_t   IEC_DWORD;
typedef uint64_t   IEC_LWORD;

typedef float    IEC_REAL;
typedef double   IEC_LREAL;
*/

float* __MD0_1 = &MD0_1;    //gen type (comment upper) from st 
float* __MD0_0 = &MD0_0;  
float* __MD1_0 = &MD1_0;
float* __MD1_1 = &MD1_1;  
int* __MX1_1 = &MX1_1;  

// from csv какой тип будет  ^ (w или r)

const uint8_t r_task_sizes[TASK_N] = {TASK1_N_R_PIN};
const uint8_t w_task_sizes[TASK_N] = {TASK1_N_W_PIN};

#endif

