idf_component_register(SRCS "br_sonar_sensor_driver.c"
                    INCLUDE_DIRS "include"
                    REQUIRES br_board_config esp_driver_gpio esp_timer)
