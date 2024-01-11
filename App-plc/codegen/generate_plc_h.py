IEC_TYPES_TO_C_MAP = {
    "BOOL": "uint8_t",
    "SINT": "int8_t",
    "INT": "int16_t",
    "DINT": "int32_t",
    "LINT": "int64_t",
    "USINT": "uint8_t",
    "UINT": "uint16_t",
    "UDINT": "uint32_t",
    "ULINT": "uint64_t",
    "BYTE": "uint8_t",
    "WORD": "uint16_t",
    "DWORD": "uint32_t",
    "LWORD": "uint64_t",
    "REAL": "float",
    "LREAL": "double",
}

def generate_plc_h(tasks, vars_types):
    task_n = len(tasks)
    vars_tasks = []
    for task in tasks:
        vars_tasks += task.vars
    header = '''#ifndef PLCH
#define PLCH

#include "pico/stdlib.h"
#include <FreeRTOS.h>
#include <queue.h>
#include "hardware/spi.h"
#include "hardware/adc.h"
#include "hardware/uart.h"
#include "stdint.h"
'''
    
    str_gpio ='''#define TASK2_PRIORITY 2 // from resource_X.c
#define TASK2_RUN RESOURCE2_run__ // from resource_X.c
#define TASK2_N_W_PIN 1 // from csv (нужно для циклов)
#define TASK2_N_R_PIN 0 // from csv

#define TASK2_R_PIN_1 9 // from csv
#define TASK2_R_PIN_1_STATE 0 // default

#define TASK2_W_PIN_1 0 // from csv
#define TASK2_W_PIN_1_STATE 0 // default

#define TASK2__MX0_0_2_0 0 // from csv
'''


    task_define = f"\n#define TASK_N {task_n}\n#define MAX_REQS_N 10\n"
    gpio_enable = 0
    w_pin_reqs = []
    r_pin_reqs = []
    n_r_pins = ''
    n_w_pins = ''
    for i, task in enumerate(tasks):
        gpio_ins = []
        gpio_outs = []
        w_pin_reqs.append([])
        r_pin_reqs.append([])
        task_define += f"\n// ---------- TASK {task.task_id} ----------\n"
        task_define += f"#define TASK{i}_PRIORITY {task.priority}\n"           
        task_define += f"#define TASK{i}_RUN  RESOURCE{i}_run__\n"  
        task_define += f"#define TASK{i}_STACK_SIZE 256\n"
        for var in task.vars:
            if var[2] == 'gpio':
                gpio_enable = 1
                if var[4] == 'in':
                    gpio_ins.append(var[3])
                elif var[4] == 'out':
                    gpio_outs.append(var[3])
        len_gpio_ins = len(gpio_ins)
        len_gpio_outs = len(gpio_outs)
        
        n_r_pins += f'TASK{i}_N_R_PIN,'
        task_define += f"#define TASK{i}_N_R_PIN {len_gpio_ins}\n"
        
        n_w_pins += f'TASK{i}_N_W_PIN,'
        task_define += f"#define TASK{i}_N_W_PIN {len_gpio_outs}\n"
        
        for j, define in enumerate(gpio_ins):
            task_define += f"#define TASK{i}_R_PIN_{j} {define}\n"
            r_pin_reqs[i].append(f"{{TASK{i}_R_PIN_{j}, 0}},")
        for j, define in enumerate(gpio_outs):
            task_define += f"#define TASK{i}_W_PIN_{j} {define}\n"
            w_pin_reqs[i].append(f"{{TASK{i}_W_PIN_{j}, 0}},")


    task_define += '\n'
    for i, task in enumerate(tasks):
        task_define += f"extern void RESOURCE{i}_run__(unsigned long tick);\n"   
    gpio_typedef = ''
    if gpio_enable:
        gpio_typedef += '''typedef struct r_request {
    const uint32_t pin;
    void* value;
} r_request_t;

typedef struct w_request {
    const uint32_t pin;
    void* value;
} w_request_t;
        '''

    task_declarations = '''typedef struct task {
    const uint8_t priority;
    void (*func)(unsigned long);'''
    if gpio_enable:
        task_declarations += '''
    w_request_t w_pin_reqs[MAX_REQS_N];
    r_request_t r_pin_reqs[MAX_REQS_N];
} task_t;
    '''
    else:
        task_declarations +='\n} task_t;\n'

    task_definitions = '''task_t tasks[TASK_N] = {
'''

    for i, task in enumerate(tasks):
        task_definition = f'''    {{
        .priority = TASK{i}_PRIORITY,
        .func = TASK{task.task_id}_RUN,'''
        if gpio_enable:
            task_definition +=f'''
        .w_pin_reqs = {{{"".join(w_pin_reqs[i]) if len(w_pin_reqs[i]) else ""}}},
        .r_pin_reqs = {{{"".join(r_pin_reqs[i]) if len(r_pin_reqs[i]) else ""}}},
    }},
'''
        else:
            task_definition += '\n    },\n'
        task_definitions += task_definition

    task_definitions += '''};
    
'''
    len_defenitions = f'const uint8_t r_task_sizes[TASK_N] = {{{n_r_pins}}};\n'
    len_defenitions += f'const uint8_t w_task_sizes[TASK_N] = {{{n_w_pins}}};\n\n'
    var_declarations = ''
    var_pointers = ''

    used_vars = set()
    used_addresses = set()

    for var in vars_tasks:
        if var[0] not in used_vars:
            var_declarations += f"{IEC_TYPES_TO_C_MAP[vars_types[var[1]]]} {var[0]};\n"
            used_vars.add(var[0])

    for var in vars_tasks:
        if var[1] not in used_addresses:
            var_pointers += f"{IEC_TYPES_TO_C_MAP[vars_types[var[1]]]}* __{var[1]} = &{var[0]};\n"
            used_addresses.add(var[1])

    footer = '''\n#endif\n'''

    plc_h_content = header + task_define + '\n' + gpio_typedef + '\n' + task_declarations + '\n' + \
        task_definitions + len_defenitions + var_declarations + '\n' + var_pointers + footer

    with open("_plc.h", "w") as file:
        file.write(plc_h_content)

    print("_plc.h file created successfully.")
