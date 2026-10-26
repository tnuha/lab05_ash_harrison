#include <pico/stdlib.h>
#include <stdio.h>

// Busy-wait iterations after the GPIO toggle (0 = no delay)
#ifndef BUSY_WAIT
#define BUSY_WAIT 0
#endif

int main(void) {
  int toggle = 0;
  stdio_init_all();
  gpio_init(OUT_PIN);
  gpio_set_dir(OUT_PIN, GPIO_OUT);
  gpio_put(OUT_PIN, toggle);

  while (true) {
    toggle = !toggle;
    gpio_put(OUT_PIN, toggle);
    for (volatile int i = 0; i < BUSY_WAIT; i++);
    sleep_ms(DELAY_MS);
  }
}
