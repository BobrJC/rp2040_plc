#include "stdint.h"
#include "stdbool.h"

typedef enum req_types
{
    GPIO,
    UART,
    SPI
} req_types_t;

typedef struct r_request
{
    const uint32_t pin;
    void* value;
    req_types_t type;
} r_request_t;

typedef struct w_request
{
    const uint32_t pin;
    void* value;
    req_types_t type;
} w_request_t;