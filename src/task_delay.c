#include <FreeRTOS.h>
#include <hardware/gpio.h>
#include <hardware/pio.h>
#include <hardware/pio_instructions.h>
#include <pico/stdlib.h>
#include <stdio.h>
#include <task.h>

#define DELAY_MS 10

#ifndef BUSY_TASKS
#define BUSY_TASKS 1
#endif

void main_task(__unused void *params) {
  int toggle = 0;
  while (1) {
    printf("toggling...\n");
    toggle = !toggle;
    gpio_put(OUT_PIN, toggle);
    vTaskDelay(1);
  }
}

void busy_task(__unused void *params) { while (1) { } }   // never yields

int main(void) {
  stdio_init_all();
  gpio_init(OUT_PIN);
  gpio_set_dir(OUT_PIN, GPIO_OUT);
  const char *rtos_name = "FreeRTOS";
  TaskHandle_t task;
  xTaskCreate(main_task, "MainThread", configMINIMAL_STACK_SIZE, NULL,
              tskIDLE_PRIORITY + 1UL, &task);
  // Number of busy-loop tasks competing with the toggle task (set in CMake)
  for (int i = 0; i < BUSY_TASKS; i++) {
    xTaskCreate(busy_task, "BusyThread", configMINIMAL_STACK_SIZE, NULL,
                tskIDLE_PRIORITY + 1UL, NULL);
  }
  vTaskStartScheduler();

  return 0;
}
