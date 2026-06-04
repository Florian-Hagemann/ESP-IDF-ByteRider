[Main Overview](../../README.md)
# ByteRider Board Configuration (Board REV: 2.0)

A component that defines every pin in a central place. All pins have the ESP_IDF native ```gpio_num_t``` data type.

## Pin layout

### LED Shift Register (U74HC595AG)
| Signal | GPIO | Description |
| :--- | :--- | :--- |
| `BR_PIN_SER` | **GPIO 0** | Serial Data Input |
| `BR_PIN_SRCLK` | **GPIO 1** | Shift Register Clock |
| `BR_PIN_RCLK` | **GPIO 2** | Latch Register Clock |
| `BR_PIN_SRCLR` | **GPIO 3** | Shift Register Clear |

### On-Board LEDs
| Signal | GPIO | Description |
| :--- | :--- | :--- |
| `BR_PIN_LED` | **GPIO 7** | LEDs (D11 & D11_2) |

### Distance Sensor (HC-SR04)
***WARNING:** The sensor requires that the 9V battery is connected to function.*
| Signal | GPIO | Description |
| :--- | :--- | :--- |
| `BR_PIN_TRIG` | **GPIO 18** | Trigger Output |
| `BR_PIN_ECHO` | **GPIO 19** | Echo Input |

### On-Board Button
| Signal | GPIO | Description |
| :--- | :--- | :--- |
| `BR_PIN_SW` | **GPIO 5** | Button (SW_1) |

### Motors (H-Bridge L298N)
| Signal | GPIO | Description |
| :--- | :--- | :--- |
| `BR_PIN_MOTOR_FWD` | **GPIO 6** | Motors Forward |
| `BR_PIN_MOTOR_BWD` | **GPIO 4** | Motors Backward |

### Servo Motor
| Signal | GPIO | Description |
| :--- | :--- | :--- |
| `BR_PIN_SERVO` | **GPIO 10** | Servo Motor |