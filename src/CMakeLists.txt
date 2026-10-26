# Output pin shared by every program (scope probe stays on GP7)
add_compile_definitions(OUT_PIN=7)

# This is the main binary. List your C files here.
add_executable(realtime
    task_delay.c
    # sleep.c
    # timer.c
    )

pico_set_program_name(realtime "realtime_lab")
pico_set_program_version(realtime "0.1")

# Modify the below lines to enable/disable output over UART/USB.
# These are mutually exclusive, only set one.
pico_enable_stdio_uart(realtime 0)
pico_enable_stdio_usb(realtime 1)

# Add the libraries to the build
target_link_libraries(realtime PRIVATE
  pico_stdlib
  pico_multicore
  pico_async_context_freertos
  FreeRTOS-Kernel-Heap4
)

# The CYW43 is the Wifi/Bluetooth module. If the board is set to pico_w, this
# variable will be set and the wireless libraries added.
if(PICO_CYW43_SUPPORTED)
    # For led support on pico_w
    target_link_libraries(realtime PRIVATE
        pico_cyw43_arch_none
    )
endif()

# Another pico macro which generates the uf2 file in addition to the elf
pico_add_extra_outputs(realtime)

find_program(OPENOCD openocd)
find_program(PICOTOOL picotool)

add_custom_target(flash ${PICOTOOL} load -f $<TARGET_FILE:realtime> DEPENDS realtime)
add_custom_target(openocd_flash ${OPENOCD} -s ${OPENOCD_PATH} -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c 'adapter speed 5000' -c program "$<TARGET_FILE:realtime>" verify reset exit' DEPENDS realtime)

# Activity 2
add_executable(irq gpio_interrupt.c)
target_compile_definitions(irq PRIVATE IN_PIN=6)
pico_enable_stdio_uart(irq 0)
pico_enable_stdio_usb(irq 1)
target_link_libraries(irq PRIVATE pico_stdlib)
pico_add_extra_outputs(irq)

# Activity 1: timekeeping (same period as task_delay.c)
add_executable(timer timer.c)
target_compile_definitions(timer PRIVATE DELAY_MS=10)
pico_enable_stdio_uart(timer 0)
pico_enable_stdio_usb(timer 1)
target_link_libraries(timer PRIVATE pico_stdlib)
pico_add_extra_outputs(timer)

add_executable(sleep sleep.c)
target_compile_definitions(sleep PRIVATE DELAY_MS=10)
pico_enable_stdio_uart(sleep 0)
pico_enable_stdio_usb(sleep 1)
target_link_libraries(sleep PRIVATE pico_stdlib)
pico_add_extra_outputs(sleep)
