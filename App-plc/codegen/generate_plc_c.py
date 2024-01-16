def generate_plc_c(tasks):
    num_tasks = len(tasks)

    with open("_plc.c", "w") as file:
        file.write("#include \"plc.h\"\n")
        file.write("#include \"task.h\"\n\n")
        file.write("#include <stdio.h>\n")
        file.write("#include <unistd.h>\n")
        file.write("#include <errno.h>\n")
        file.write("#include \"stack_macros.h\"\n")
        file.write("#include \"iec_types.h\"\n")
        file.write("#include \"FreeRTOS.h\"\n")
        file.write("#include \"timers.h\"\n\n")

        file.write("IEC_TIME       __CURRENT_TIME;\n")
        
        for i in range(num_tasks):
            file.write(
                "extern void     RESOURCE{}_init__();\n".format(i))
        file.write("\n")
        for i in range(num_tasks):
            file.write(
                "extern void     RESOURCE{}_run__();\n".format(i))
        file.write("\n")

        for i in range(num_tasks):
            file.write("void task{}_func();  \n".format(i))
        file.write("\n")

        file.write("void init_freertos()\n")
        file.write("{\n")
        for i in range(num_tasks):
            file.write("    TaskHandle_t task{} = NULL;\n".format(i))
        for i in range(num_tasks):
            file.write(
                "    xTaskCreate(task{}_func, \"{}\", TASK{}_STACK_SIZE, (void*){}, TASK{}_PRIORITY, &task{});\n".format(i, i, i, i, i, i))
        file.write("}\n")
        file.write("\n")
        use_gpio = 0
        for task in tasks:
            used_types = []
            for var in task.vars:
                type = var[2].lower()
                if type not in used_types and type != 'default':
                    if type == 'gpio':
                        if not use_gpio:
                            use_gpio = 1
                            file.write("void __init_gpio(int task_id)\n{\n")
                            file.write("""    for (int j = 0; j < r_task_sizes[task_id]; j++)
    {
        gpio_init(tasks[task_id].r_pin_reqs[j].pin);
        gpio_set_dir(tasks[task_id].r_pin_reqs[j].pin, false);
    }
    for (int j = 0; j < w_task_sizes[task_id]; j++) 
    {
        gpio_init(tasks[task_id].w_pin_reqs[j].pin);
        gpio_set_dir(tasks[task_id].w_pin_reqs[j].pin, true);
    }
}\n""")
                            file.write('''\nvoid __retrieve_gpio(int task_id)
    {
        for (int j = 0; j < r_task_sizes[task_id]; j++)
        {
            tasks[task_id].r_pin_reqs[j].value = (void*)gpio_get(tasks[task_id].r_pin_reqs[j].pin);
        }
    }

void __publish_gpio(int task_id)
{
    uint8_t w_task_size = w_task_sizes[task_id];
    for (int j = 0; j < w_task_sizes[task_id]; j++)
    {
        gpio_put(tasks[task_id].w_pin_reqs[j].pin, (bool*)tasks[task_id].w_pin_reqs[j].value);
    }
}\n\n\n''')
                    else:
                        file.write(f"void __init_task{task.task_id}_{type}()\n{{\n}}\n\n")
                        file.write(f"void __retrieve_task{task.task_id}_{type}()\n{{\n}}\n\n")
                        file.write(f"void __publish_task{task.task_id}_{type}()\n{{\n}}\n\n")
                        
                used_types.append(type)
            
        for i in range(num_tasks):
            
            file.write("void task{}_func(int task_id)\n".format(i))
            file.write("{\n")
            file.write("    // USER CODE HERE\n")
            file.write("    RESOURCE{}_init__();\n".format(i))
            used_types = []
            for var in tasks[i].vars:    
                type = var[2]
                if type not in used_types and type != 'DEFAULT':
                    if type == 'gpio':
                        file.write(f"    __init_gpio(task_id);\n")
                    else:
                        file.write(f"    __init_task{tasks[i].task_id}_{var[2]}();\n")

                used_types.append(type)
            file.write("    while (1)\n")
            file.write("    {\n")
            file.write("        TickType_t tick = xTaskGetTickCount();\n")
            file.write("        __CURRENT_TIME.tv_sec = tick/1000;\n")
            file.write("        __CURRENT_TIME.tv_nsec = (tick % 1000) * 1000000;\n")
            used_types = []
            for var in tasks[i].vars:
                type = var[2]
                if type not in used_types and type != 'DEFAULT':
                    if type == 'gpio':
                        file.write(f"        __retrieve_gpio(task_id);\n")
                    else:
                        file.write(f"        __retrieve_task{tasks[i].task_id}_{var[2]}();\n")
                used_types.append(type)
                
            file.write("        tasks[task_id].func(tick);\n")
            used_types = []
            for var in tasks[i].vars:
                type = var[2]
                if type not in used_types and type != 'DEFAULT':
                    if type == 'gpio':
                        file.write(f"        __publish_gpio(task_id);\n")
                    else:
                        file.write(f"        __publish_task{tasks[i].task_id}_{var[2]}();\n")
                used_types.append(type)
                
                        
           
            file.write("        vTaskDelay(5);\n    }\n}\n\n")

    
        print("_plc.c file created successfully.")
