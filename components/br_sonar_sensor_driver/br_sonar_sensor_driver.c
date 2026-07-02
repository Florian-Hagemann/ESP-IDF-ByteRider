#include <stdio.h>
#include "br_sonar_sensor_driver.h"
#include "br_board_config.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "esp_log.h"
#include "driver/gpio.h"
#include "esp_timer.h"
#include "esp_rom_sys.h"

static const char* TAG = "br_sonar_sensor";
static float distance = 0.0f;
static QueueHandle_t br_sonar_sensor_queue_handle = NULL; // ISR sends echo time to sensor task

static void IRAM_ATTR isr_func(void *arg) {

    static uint64_t echo_start_time = 0;

    if(gpio_get_level(BR_PIN_ECHO) == 1) {

        echo_start_time = esp_timer_get_time();

    } else {

        QueueHandle_t queue = (QueueHandle_t) arg;
        uint64_t time = esp_timer_get_time() - echo_start_time;
        xQueueSendFromISR(queue, &time, NULL);

    }

}

static void sonar_sensor_task(void *pvArguments) {

    uint64_t time;

    while(1) {

        gpio_set_level(BR_PIN_TRIG, 1);

        esp_rom_delay_us(10);

        gpio_set_level(BR_PIN_TRIG, 0);

        if(xQueueReceive(br_sonar_sensor_queue_handle, &time, portMAX_DELAY) == pdTrue) {

            distance = (time * 0.034) / 2; 
            ESP_LOGV(TAG, "Set distance to %f cm", distance);

        }

        vTaskDelay(pdMS_TO_TICKS(100));

    }

}

void br_sonar_sensor_init() {

    ESP_LOGD(TAG, "Setting up sonar sensor");

    br_sonar_sensor_queue_handle = xQueueCreate(5, sizeof(uint64_t));

    gpio_config_t trig_config = {
        .pin_bit_mask = 1ULL << BR_PIN_TRIG,
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };

    gpio_config(&trig_config);

    gpio_config_t echo_config = {
        .pin_bit_mask = 1ULL << BR_PIN_ECHO,
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,
        .intr_type = GPIO_INTR_ANYEDGE
    };

    gpio_config(&echo_config);
    gpio_install_isr_service(0);
    gpio_isr_handler_add(BR_PIN_ECHO, isr_func, br_sonar_sensor_queue_handle);

    xTaskCreate(sonar_sensor_task, "sonar_sensor_task", 2048, NULL, 1, NULL);

}

float br_sonar_sensor_getDistance(void) {
    return distance;
}