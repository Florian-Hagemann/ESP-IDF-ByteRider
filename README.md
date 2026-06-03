# ESP-IDF ByteRider

I'm rewriting the ByteRider robot projects from the original Arduino code over to native **ESP-IDF** to push my coding skills and learn how FreeRTOS and low-level drivers actually work.

## Project Origin & Credits
The **ByteRider** hardware platform was originally designed by Nils Kohl and Lasse Schulze during their FWJ at the **IMS (Institut für Mikroelektronische Systeme)** at Leibniz Universität Hannover as an intern project. 

* **Original Arduino Repository:** [Florian-Hagemann/ByteRider](https://github.com/Florian-Hagemann/ByteRider)

I'm using their awesome hardware layout but replacing the beginner-friendly Arduino shortcuts with native ESP-IDF code.

## Prerequisites & Environment
* **Hardware:** ByteRider Custom PCB (IMS Hannover) + ESP32-C3-DevKitC-02
* **Framework:** ESP-IDF v6.0.1
* **Target Chip:** ESP32-C3