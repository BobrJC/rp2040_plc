#include "stdint.h"
#include "stdbool.h"

typedef struct r_request
{
    const uint32_t pin;
    bool value;
} r_request_t;

typedef struct w_request
{
    const uint32_t pin;
    bool value;
} w_request_t;