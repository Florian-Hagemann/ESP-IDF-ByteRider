#include <stdio.h>
#include "br_led_driver.h"
#include <stdint.h>
#include <stdbool.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char* TAG = "br_led_driver"; // Tag for logs
static TaskHandle_t br_led_driver_task_handle = NULL; // Task handle for driver task

// Driver task
static void br_led_driver_task(void *pvArguments) {
    ESP_LOGD(TAG, "Successfully created br_led_driver task.");
    
    while(1) {

    }
}

// Create driver task
void br_led_driver_init(void) {
    ESP_LOGD(TAG, "Creating br_led_driver task...");
    xTaskCreate(
        br_led_driver_task,
        "br_led_driver_task",
        3072,
        NULL,
        1,
        &br_led_driver_task_handle
    );
}

// Start driver task (if stopped)
void br_led_driver_start(void); 

// Stop driver task
void br_led_driver_stop(void);

// Kill driver task
void br_led_driver_kill(void);  

void br_led_driver_set_pattern(uint16_t pattern);   
void br_led_driver_set_d11(bool state);             