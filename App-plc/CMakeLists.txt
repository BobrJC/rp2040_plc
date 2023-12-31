cmake_minimum_required(VERSION 3.14)

# Make project data accessible to compiler
add_compile_definitions(APP_NAME="${APP_PLC_NAME}")
add_compile_definitions(APP_VERSION="${APP_PLC_VERSION_NUMBER}")
add_compile_definitions(BUILD_NUM=${BUILD_NUMBER})

# Include app source code file(s)
add_executable(${APP_PLC_NAME}
    ${APP_PLC_SRC_DIRECTORY}/config.c
    ${APP_PLC_SRC_DIRECTORY}/main.c
    ${APP_PLC_SRC_DIRECTORY}/plc.c
    ${APP_PLC_SRC_DIRECTORY}/resource1.c
    ${APP_PLC_SRC_DIRECTORY}/tasks.c
    ${APP_PLC_SRC_DIRECTORY}/resource0.c
)

# Link to built libraries
target_link_libraries(${APP_PLC_NAME} LINK_PUBLIC
    pico_stdlib
    FreeRTOS
    hardware_spi
    hardware_adc)

# Enable/disable STDIO via USB and UART
pico_enable_stdio_usb(${APP_PLC_NAME} 1)
pico_enable_stdio_uart(${APP_PLC_NAME} 0)

# Enable extra build products
pico_add_extra_outputs(${APP_PLC_NAME})
