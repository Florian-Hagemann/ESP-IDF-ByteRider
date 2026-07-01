[Main Overview](../../README.md)
# Button Driver
Driver for handling tactile buttons using hardware interrupts and FreeRTOS task-based callback execution.

## Functions
### Setup functions
| Function | Description |
| :--- | :--- |
| `br_button_setup(button_config_t*)` | Configures GPIO, installs ISR service, and creates the handler task |

### Data Structures
| Struct | Description |
| :--- | :--- |
| `button_config_t` | Configuration struct containing the callback and its arguments |

### Config Parameters
| Member | Type | Description |
| :--- | :--- | :--- |
| `onpress` | `button_callback_t` | Pointer to the function to be executed on a button press |
| `callback_args` | `void*` | Pointer to custom arguments to be passed into the callback |

## Architecture
The driver utilizes an **ISR (Interrupt Service Routine)** for immediate event detection and a **FreeRTOS task** for safe, decoupled callback execution. Hardware-level debouncing via a 47nF capacitor ensures clean signal edges, allowing for low-latency processing without additional software delay logic.