#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "br_led_driver.h"

void app_main(void)
{
    br_led_driver_init();

    while(1) {

        br_led_driver_set_pattern((uint16_t)0xFFFF);
        br_led_driver_set_d11(0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        br_led_driver_set_pattern((uint16_t)0x0000);
        br_led_driver_set_d11(1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);

    }
    
}
