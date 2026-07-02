#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "br_led_driver.h"
#include "br_sonar_sensor_driver.h"

void app_main(void)
{   
    br_sonar_sensor_init();
    while(1) {
        ESP_LOGI("TAG", "%f cm", br_sonar_sensor_getDistance());
        vTaskDelay(200);
    }

}
