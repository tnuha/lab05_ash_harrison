#include <FreeRTOS.h>
#include <hardware/gpio.h>
#include <hardware/pio.h>
#include <hardware/pio_instructions.h>
#include <pico/stdlib.h>
#include <stdio.h>
#include <task.h>

#define OUT_PIN 0
#define DELAY_MS 10

void main_task(__unused void *params) {
  int toggle = 0;
  while (1) {
    printf("toggling...\n");
    toggle = !toggle;
    gpio_put(OUT_PIN, toggle);
    vTaskDelay(pdMS_TO_TICKS(DELAY_MS));
  }
}

void unused_task(__unused void *params) {
  while (1) {
    vTaskDelay(1); // delay for one tick
  }
}

int main(void) {
  stdio_init_all();
  gpio_init(OUT_PIN);
  gpio_set_dir(OUT_PIN, GPIO_OUT);
  const char *rtos_name = "FreeRTOS";
  TaskHandle_t task, unused_task;
  xTaskCreate(main_task, "MainThread", configMINIMAL_STACK_SIZE, NULL,
              tskIDLE_PRIORITY + 1UL, &task);
  xTaskCreate(unused_task, "UnusedThread", configMINIMAL_STACK_SIZE, NULL,
              tskIDLE_PRIORITY + 1UL, &unused_task);
  xTaskCreate(unused_task, "UnusedThread2", configMINIMAL_STACK_SIZE, NULL,
              tskIDLE_PRIORITY + 1UL, &unused_task);
  vTaskStartScheduler();

  return 0;
}
