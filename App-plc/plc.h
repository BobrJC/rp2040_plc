// #ifndef PLCH
// #define PLCH
#pragma once

#define R_REQ_N 0 //gen
#define W_REQ_N 1 //gen
#define TASK_N 1 //gen
#include "stdbool.h"
#include "stdint.h"
#include "pico/stdlib.h"
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <semphr.h>

SemaphoreHandle_t xMutex;

extern void RESOURCE1_run__(unsigned long tick); //gen

typedef struct r_request
{
    uint32_t pin;
    bool dir;
    bool state;
} r_request_t;

typedef struct w_request
{
    uint32_t pin;
    bool dir;
    bool state;
} w_request_t;


typedef struct task {
    uint8_t priority;
    w_request_t w_pin_reqs[W_REQ_N]; 
    r_request_t r_pin_reqs[R_REQ_N]; 
    void (*func)(unsigned long); 
} task_t;

task_t tasks[TASK_N] = {{.priority = 10, .func = RESOURCE1_run__, .w_pin_reqs = {{.pin = 0, .dir = 1, .state = 0}}}}; //gen

bool *__MX0_0_2_13 = &tasks[0].w_pin_reqs[0].state; //gen

// #endif