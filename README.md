# ESP-IDF ByteRider

***Note:* This Repository is not finished at the moment.**

I'm rewriting the ByteRider robot projects from the original Arduino code over to native **ESP-IDF** to push my coding skills and learn how FreeRTOS and low-level drivers actually work.

## How to use
**1. Clone the repository:**
   ```bash
   git clone https://github.com/Florian-Hagemann/ESP-IDF-ByteRider.git
   cd ESP-IDF-ByteRider
   ```
**2. Pick a project**

**3. Set idf target**
```bash
idf.py set-target esp32c3
```

**4. Flash, monitor, and enjoy!**
```bash
idf.py flash monitor
```

## Project Origin & Credits
The **ByteRider** hardware platform was originally designed by [Nils Kohl and Lasse Schulze during their FWJ at the **IMS (Institut für Mikroelektronische Systeme)**](https://www.ims.uni-hannover.de/fileadmin/ims/studium/FWJ/2024_Kohl_Schulze_FWJ-Poster.pdf) at Leibniz Universität Hannover as an intern project. 

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
* [br_sonar_distance_driver](./components/br_sonar_sensor_driver/README.md) - Driver for the distance sensor.
* [br_button](./components/br_button/README.md) - Code for button interrupt.
* [br_motor_driver](./components/br_motor_driver/README.md) - DC motor control (L298N H-Bridge).
* [br_servo_driver](./components/br_servo_driver/README.md) - Driver for the servo motor.

### Projects
The example projects from the [original ByteRider Arduino repository](https://github.com/Florian-Hagemann/ByteRider) rewritten for ESP-IDF.
* [01_blink](./projects/01_blink/README.md) - Blink the LEDs
* [02_running_lights](./projects/02_running_lights/README.md) - Stoppable running lights animation.
* [03_distance_sensor](./projects/03_distance_sensor/README.md) - Show distance with LEDs.
* [04_motors](./projects/04_motors/README.md) - Let the ByteRider drive.
* [05_wifi_connectivity](./projects/05_wifi_connectivity/README.md) - Host an Access Point.
* [06_captive_portal](./projects/06_captive_portal/README.md) - Host a captive portal with which you can control the ByteRider.