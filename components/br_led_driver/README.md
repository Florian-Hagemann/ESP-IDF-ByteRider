[Main Overview](../../README.md)
# LED Driver
Driver for Shift Register controlled LEDs and onboard LEDs (D11 and D11_2).

## Functions
### Driver task functions
| Function | Description |
| :--- | :--- |
| `br_led_driver_init(void)` | Initializes driver task and pins |
| `br_led_driver_start(void)` | Resumes driver task |
| `br_led_driver_stop(void)` | Suspends driver task |
| `br_led_driver_kill(void)` | Kills driver task |
### LED control functions
| Function | Description |
| :--- | :--- |
| `br_led_driver_set_pattern(uint16_t)` | Sends LED states to the 16 bit shift register |
| `br_led_driver_set_d11(bool)` | Sets state of D11 and D11_2 |


