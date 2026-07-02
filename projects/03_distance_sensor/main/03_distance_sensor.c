#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "br_led_driver.h"
#include "br_sonar_sensor_driver.h"

void app_main(void)
{   
    br_sonar_sensor_init();
    br_led_driver_init();
    
    float distance;

    while(1) {
        
        distance = br_sonar_sensor_getDistance();

        if(distance < 10) {
            br_led_driver_set_pattern(0x0000);
        } else if (distance < 20) {
            br_led_driver_set_pattern(0x000F);
        } else if (distance < 30) {
            br_led_driver_set_pattern(0x00FF);
        } else if (distance < 40) {
            br_led_driver_set_pattern(0x0FFF);
        } else {
            br_led_driver_set_pattern(0xFFFF);
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }

}
