/*
# br_board_config

The pin configuration on the ByteRider PCB (Board REV: 2.0).
*/ 

#pragma once
#include "driver/gpio.h"

// Shift register for LEDs (U74HC595AG)
static const gpio_num_t BR_PIN_SER = GPIO_NUM_0;
static const gpio_num_t BR_PIN_SRCLK = GPIO_NUM_1;
static const gpio_num_t BR_PIN_RCLK = GPIO_NUM_2;
static const gpio_num_t BR_PIN_SRCLR = GPIO_NUM_3;

// ByteRider on-board LEDs (D11 & D11_2)
static const gpio_num_t BR_PIN_LED = GPIO_NUM_7;

// Distance sensor (HC-SR04)
// !!! WARNING: absolutely requires that the 9V battery is connected to function !!!
static const gpio_num_t BR_PIN_TRIG = GPIO_NUM_18;
static const gpio_num_t BR_PIN_ECHO = GPIO_NUM_19;

// On-board button
static const gpio_num_t BR_PIN_SW = GPIO_NUM_5;

// Motors (H-Bridge L298N)
static const gpio_num_t BR_PIN_MOTOR_FWD = GPIO_NUM_6;
static const gpio_num_t BR_PIN_MOTOR_BWD = GPIO_NUM_4;

// Servo Motor
static const gpio_num_t BR_PIN_SERVO = GPIO_NUM_10;