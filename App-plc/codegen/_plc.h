#ifndef PLCH
#define PLCH

#include "pico/stdlib.h"
#include <FreeRTOS.h>
#include <queue.h>
#include "hardware/spi.h"
#include "hardware/adc.h"
#include "hardware/uart.h"
#include "stdint.h"

#define TASK_N 2
#define MAX_REQS_N 10

// ---------- TASK 0 ----------
#define TASK0_PRIORITY 7
#define TASK0_RUN  RESOURCE0_run__
#define TASK0_STACK_SIZE 256
#define TASK0_N_R_PIN 1
#define TASK0_N_W_PIN 0
#define TASK0_R_PIN_0 5

// ---------- TASK 1 ----------
#define TASK1_PRIORITY 7
#define TASK1_RUN  RESOURCE1_run__
#define TASK1_STACK_SIZE 256
#define TASK1_N_R_PIN 0
#define TASK1_N_W_PIN 0

extern void RESOURCE0_run__(unsigned long tick);
extern void RESOURCE1_run__(unsigned long tick);

typedef struct r_request {
    const uint32_t pin;
    void* value;
} r_request_t;

typedef struct w_request {
    const uint32_t pin;
    void* value;
} w_request_t;
        
typedef struct task {
    const uint8_t priority;
    void (*func)(unsigned long);
    w_request_t w_pin_reqs[MAX_REQS_N];
    r_request_t r_pin_reqs[MAX_REQS_N];
} task_t;
    
task_t tasks[TASK_N] = {
    {
        .priority = TASK0_PRIORITY,
        .func = TASK0_RUN,
        .w_pin_reqs = {},
        .r_pin_reqs = {{TASK0_R_PIN_0, 0},},
    },
    {
        .priority = TASK1_PRIORITY,
        .func = TASK1_RUN,
        .w_pin_reqs = {},
        .r_pin_reqs = {},
    },
};
    
const uint8_t r_task_sizes[TASK_N] = {TASK0_N_R_PIN,TASK1_N_R_PIN,};
const uint8_t w_task_sizes[TASK_N] = {TASK0_N_W_PIN,TASK1_N_W_PIN,};

float cel_0;
float far1;
float far_from_pair;
uint8_t res;
float cel_1;
float far;

float* __MD1_0 = &cel_0;
float* __MD1_1 = &far1;
float* __MD0_1 = &far_from_pair;
uint8_t* __MX1_1 = &res;
float* __MD0_0 = &cel_1;

#endif
