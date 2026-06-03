#pragma once

#include <stdint.h>
#include <stdbool.h>

// Functions for the driver task
void br_led_driver_init(void);  // initialize LED
void br_led_driver_start(void); // start driver task
void br_led_driver_stop(void);  // stop driver task
void br_led_driver_kill(void);  // kill driver task

// Functions for controlling LEDs
void br_led_driver_set_pattern(uint16_t pattern);   // writes the pattern to the shift register
void br_led_driver_set_d11(bool state);             // turns d11 and d11_2 on or off
