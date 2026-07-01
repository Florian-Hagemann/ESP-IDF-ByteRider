#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "br_led_driver.h"
#include "br_button.h"
#include <stdint.h>

volatile bool running = true;
uint16_t pattern = 0x0001;

void pause_start_lights() {
    running = !running;
}

void runner_task(void *pvArguments) {

    while(1) {

        if(running) {

            br_led_driver_set_pattern(pattern);
            pattern <<= 1;
            pattern = (pattern == 0x0000) ? 0x0001 : pattern;

        }

        vTaskDelay(pdMS_TO_TICKS(100));

    }

}

void app_main(void) {

    br_led_driver_init();

    button_config_t config = {
        .onpress = pause_start_lights,
        .callback_args = NULL
    };

    br_button_setup(&config);

    xTaskCreate(runner_task, "runner_task", 2048, NULL, 5, NULL);

}