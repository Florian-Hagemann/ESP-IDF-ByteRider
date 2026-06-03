#include <stdio.h>
#include "br_led_driver.h"
#include <stdint.h>
#include <stdbool.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char* TAG = "br_led_driver"; // Tag for logs
static TaskHandle_t br_led_driver_task_handle = NULL;

// Driver task
static void br_led_driver_task(void *pvArguments) {
    ESP_LOGI("Created br_led_driver task.")
}

// Create driver task
void br_led_driver_init(void);

// Start driver task (if stopped)
void br_led_driver_start(void); 

// Stop driver task
void br_led_driver_stop(void);


void br_led_driver_kill(void);  

void br_led_driver_set_pattern(uint16_t pattern);   
void br_led_driver_set_d11(bool state);             