# ESP-IDF ByteRider

I'm rewriting the ByteRider robot projects from the original Arduino code over to native **ESP-IDF** to push my coding skills and learn how FreeRTOS and low-level drivers actually work.

## Project Origin & Credits
The **ByteRider** hardware platform was originally designed by Nils Kohl and Lasse Schulze during their FWJ at the **IMS (Institut für Mikroelektronische Systeme)** at Leibniz Universität Hannover as an intern project. 

* **Original Arduino Repository:** [Florian-Hagemann/ByteRider](https://github.com/Florian-Hagemann/ByteRider)

I'm using their awesome hardware layout and replacing my beginner-friendly Arduino shortcuts with native ESP-IDF code.

## Prerequisites & Environment
* **Hardware:** ByteRider Custom PCB (IMS Hannover) + ESP32-C3-DevKitC-02
* **Framework:** ESP-IDF v6.0.1
* **Target Chip:** ESP32-C3

## Repository structure
### Components
Configurations and drivers for the ByteRider.
* [br_board_config](./components/br_board_config/README.md) - Central pin configuration and hardware warnings.
* [br_led_driver](./components/br_led_driver/README.md) - Driver for the U74HC595 shift register and LEDs (D11 & D11_2).
* [br_motor_driver](./components/br_motor_driver/README.md) - DC motor control (L298N H-Bridge).
* [br_servo_driver](./components/br_servo_driver/README.md) - Driver for the servo motor.

## Projects
