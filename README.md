# ESP8266 OLED Wi-Fi Display Project

An interactive, connected IoT display project built using the ESP8266 development board and an I2C SSD1306 OLED display. The project connects to a local 2.4 GHz Wi-Fi network, performs an internet connectivity (ping) test to `google.com`, and displays status along with an expressive vector smiley face that transitions from **sad** to **happy** upon a successful connection.

Developed on **May 28, 2026**.

## Hardware Setup

Here is the physical wiring and assembly of the ESP8266 board and OLED display:

![Hardware Setup](images/arduino_setup.jpg)

### Wiring Details

| OLED Display Pin | ESP8266 NodeMCU Pin | Description |
| :--- | :--- | :--- |
| **GND** | **GND** | Ground |
| **VCC** | **3V3** | 3.3V Power |
| **SDA** | **D2** (GPIO 4) | I2C Serial Data Line |
| **SCL** (or SCK) | **D1** (GPIO 5) | I2C Serial Clock Line |

*Note: The board is mounted inside a custom yellow 3D-printed enclosure.*

---

## Features

1. **Dynamic Boot Status:** Shows connection status to the `FOOTBALL_EXT_2.4G` Wi-Fi network with loading dots.
2. **Connectivity Test:** Attempts a TCP connection to `google.com:80` to verify full internet access.
3. **Face Expressions:**
   - **Sad Face:** Rendered during network setup and ping check to indicate offline status.
   - **Happy Face:** Rendered once the Google ping completes successfully to confirm full internet access.
4. **Local IP Address Display:** Displays the assigned IP on the screen for easy debugging and access.
5. **Serial Monitor Logging:** Outputs verbose diagnostic messages to the USB interface at `115200` baud.

---

## Software & Tools

This project was built and programmed using:
* **PlatformIO Core (6.1.19):** Used as the primary CLI compiler and project manager, providing a robust Arduino framework compile target for the ESP8266 (`espressif8266` platform and `nodemcuv2` board configuration).
* **Antigravity 2.0:** An advanced autonomous agentic AI pair-programming assistant that pair-programmed the firmware, diagnosed connection speeds, solved the 2.4GHz/5GHz hardware band mismatch, and automated compilation, flashing, and verification.
* **Libraries:**
  - `Adafruit GFX Library` (v1.12.6) for pixel rendering and geometry.
  - `Adafruit SSD1306` (v2.5.16) for screen buffers.
  - Built-in `ESP8266WiFi` for network stack management.

---

## How to Build and Upload

To run this project locally, ensure you have PlatformIO installed, then execute:

```bash
# Build the project and download all libraries
pio run

# Upload the firmware to the ESP8266 via USB
pio run --target upload

# View logs via Serial Monitor
pio device monitor --baud 115200
```
