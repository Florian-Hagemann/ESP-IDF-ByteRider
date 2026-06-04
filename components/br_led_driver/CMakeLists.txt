idf_component_register(SRCS "br_led_driver.c"
                    INCLUDE_DIRS "include"
                    REQUIRES br_board_config esp_driver_gpio)
