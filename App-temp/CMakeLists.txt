cmake_minimum_required(VERSION 3.14)

# Make project data accessible to compiler
add_compile_definitions(APP_NAME="${APP_TEMP_NAME}")
add_compile_definitions(APP_VERSION="${APP_TEMP_VERSION_NUMBER}")
add_compile_definitions(BUILD_NUM=${BUILD_NUMBER})

# Include app source code file(s)
add_executable(${APP_TEMP_NAME}
    ${APP_TEMP_SRC_DIRECTORY}/main.c
)

# Link to built libraries
target_link_libraries(${APP_TEMP_NAME} LINK_PUBLIC
    pico_stdlib
    FreeRTOS)

# Enable/disable STDIO via USB and UART
pico_enable_stdio_usb(${APP_TEMP_NAME} 1)
pico_enable_stdio_uart(${APP_TEMP_NAME} 1)

# Enable extra build products
pico_add_extra_outputs(${APP_TEMP_NAME})
