#include <stdio.h>
#include "br_button.h"
#include "br_board_config.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "esp_log.h"
#include "driver/gpio.h"

static const char* TAG = "br_button";
static QueueHandle_t br_button_queue_handle = NULL;

static uint32_t last_interrupt_time = 0;

static void IRAM_ATTR isr_func(void *arg) {

    uint32_t interrupt_time = xTaskGetTickCountFromISR();

    if(interrupt_time - last_interrupt_time > pdMS_TO_TICKS(200)){
        last_interrupt_time = interrupt_time;
        QueueHandle_t queue = (QueueHandle_t) arg;
        uint32_t dummy = 1;
        xQueueSendFromISR(queue, &dummy, NULL);
    }

}

static void button_handler_task(void *pvArguments) {

    uint32_t dummy;
    button_config_t *config = (button_config_t *)pvArguments;

    if(config->onpress == NULL) {

        ESP_LOGE(TAG, "Button needs a onpress function!");
        return;

    }

    while(1) {

        if(xQueueReceive(br_button_queue_handle, &dummy, portMAX_DELAY) == pdTRUE) {

            ESP_LOGD(TAG, "Recieved dummy from isr_func!");
            config->onpress(config->callback_args);

        }

    }
    
}

void br_button_setup(button_config_t *button_config) {
    ESP_LOGD(TAG, "Setting up button...");

    br_button_queue_handle = xQueueCreate(5, sizeof(uint32_t));

    gpio_config_t button_gpio_config = {
        .pin_bit_mask = 1ULL << BR_PIN_SW,
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_NEGEDGE
    };

    gpio_config(&button_gpio_config);

    gpio_install_isr_service(0);
    gpio_isr_handler_add(BR_PIN_SW, isr_func, br_button_queue_handle);

    xTaskCreate(button_handler_task, "button_handler_task", 2048, button_config, 5, NULL);

}
