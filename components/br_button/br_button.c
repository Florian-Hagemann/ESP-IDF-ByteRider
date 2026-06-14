#include <stdio.h>
#include "br_button.h"
#include "br_board_config.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "esp_log.h"
#include "driver/gpio.h"

static const char* TAG = "br_button";

void br_button_setup(button_config_t *button_config) {
    ESP_LOGD(TAG, "Setting up button...");
    // TODO: Setup ISR
    // TODO: Setup Button handler to debounce and run the onpress func
}
