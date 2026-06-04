#include <stdio.h>
#include "br_led_driver.h"
#include "br_board_config.h"
#include <stdint.h>
#include <stdbool.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "esp_log.h"
#include "driver/gpio.h"

// Command types for queue
typedef enum {
    CMD_SET_PATTERN,
    CMD_SET_D11
} br_led_driver_command_type_t;

// Command struct for queue
typedef struct {
    br_led_driver_command_type_t type;
    uint16_t value;
} br_led_driver_command_t;

static const char* TAG = "br_led_driver"; // Tag for logs
static TaskHandle_t br_led_driver_task_handle = NULL; // Task handle for driver task
static QueueHandle_t br_led_driver_queue_handle = NULL; // Queue handle for passing data to the driver

// GPIO logic for writing to the shift register
static void internal_write_pattern(uint16_t pattern) {
    
    gpio_set_level(BR_PIN_SRCLK, 0);

    for(int i = 0; i < 16; i++) {

        gpio_set_level(BR_PIN_RCLK, 0);
        gpio_set_level(BR_PIN_SER, ((pattern >> i) & 1));
        gpio_set_level(BR_PIN_RCLK, 1);

    }

    gpio_set_level(BR_PIN_SRCLK, 1);

}

// GPIO logic for writing state to D11
static void internal_write_d11(bool state) {
    
    gpio_set_level(BR_PIN_LED, state);

}

// Driver task
static void br_led_driver_task(void *pvArguments) {
    ESP_LOGD(TAG, "Successfully created br_led_driver task.");
    
    br_led_driver_command_t recieved_cmd;

    while(1) {

        if(xQueueReceive(br_led_driver_queue_handle, &recieved_cmd, portMAX_DELAY) == pdTRUE) {

            switch(recieved_cmd.type) {

                case CMD_SET_PATTERN:
                    internal_write_pattern(recieved_cmd.value);
                    break;
                case CMD_SET_D11:
                    internal_write_d11((bool)recieved_cmd.value);
                    break;
                default:
                    ESP_LOGE(TAG, "Received unknown command type!");
                    break;

            }

        }

    }
}

static void internal_initialize_pins(void) {

    // Set pin levels
    gpio_set_level(BR_PIN_SER, 0);
    gpio_set_level(BR_PIN_SRCLK, 0);
    gpio_set_level(BR_PIN_RCLK, 0);
    gpio_set_level(BR_PIN_SRCLR, 1); // SRCLR is active low
    gpio_set_level(BR_PIN_LED, 0);

    // pin mask
    uint64_t pin_mask = (1ULL << BR_PIN_SER)    | 
                        (1ULL << BR_PIN_SRCLK)  | 
                        (1ULL << BR_PIN_RCLK)   | 
                        (1ULL << BR_PIN_SRCLR)  | 
                        (1ULL << BR_PIN_LED);
    gpio_config_t io_conf = {
        .pin_bit_mask = pin_mask,
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };

    // Set config
    gpio_config(&io_conf);
    internal_write_pattern(0x0000);

    ESP_LOGD(TAG, "Initialised all needed GPIO pins.");

}

// Create driver task
void br_led_driver_init(void) {

    if(br_led_driver_task_handle != NULL) {
        ESP_LOGW(TAG, "Driver already initialized! Skipping Task creation...");
        return;
    }

    ESP_LOGD(TAG, "Creating br_led_driver task...");

    
    br_led_driver_queue_handle = xQueueCreate(3, sizeof(br_led_driver_command_t));
    
    if(br_led_driver_queue_handle == NULL) {
        ESP_LOGE(TAG, "Failed to create queue! Out of memory. Aborting Task creation...");
        return;
    }
    
    internal_initialize_pins();
    
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
void br_led_driver_start(void) {

    if(br_led_driver_task_handle == NULL) {
        ESP_LOGW(TAG, "Cannot start: Task does not exist. Call br_led_driver_init() first!");
        return;
    }

    vTaskResume(br_led_driver_task_handle);
    ESP_LOGD(TAG, "Task resumed.");

}

// Stop driver task
void br_led_driver_stop(void) {

    if(br_led_driver_task_handle == NULL) {
        ESP_LOGW(TAG, "Cannot stop: Task does not exist. Call br_led_driver_init() first!");
        return;
    }

    vTaskSuspend(br_led_driver_task_handle);
    ESP_LOGD(TAG, "Task suspended.");

}

// Kill driver task
void br_led_driver_kill(void) {
    if(br_led_driver_task_handle != NULL) {
        vTaskDelete(br_led_driver_task_handle);
        vQueueDelete(br_led_driver_queue_handle);
        br_led_driver_task_handle = NULL;
        br_led_driver_queue_handle = NULL;
        ESP_LOGD(TAG, "Killed Task.");
    } else {
        ESP_LOGW(TAG, "Cannot kill: Task does not exist. Call br_led_driver_init() first!");
    }
}

// Sends a pattern to the queue to be send to the shift register
void br_led_driver_set_pattern(uint16_t pattern) {

    if(br_led_driver_queue_handle == NULL) {
        ESP_LOGE(TAG, "Could not set pattern: Task/Queue does not exist!");
        return;
    }
    
    br_led_driver_command_t cmd = { .type = CMD_SET_PATTERN, .value = pattern };

    xQueueSend(br_led_driver_queue_handle, &cmd, 0);

} 

// Sends D11 state to driver queue to turn it off/on
void br_led_driver_set_d11(bool state) {

    if(br_led_driver_queue_handle == NULL) {
        ESP_LOGE(TAG, "Could not set D11: Task/Queue does not exist!");
        return;
    }
    
    ESP_LOGV(TAG, "Set D11 to %d", state);
    br_led_driver_command_t cmd = { .type = CMD_SET_D11, .value = state };

    xQueueSend(br_led_driver_queue_handle, &cmd, 0);

} 