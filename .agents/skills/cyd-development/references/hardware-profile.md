# CYD hardware profile

Use this profile when the target project does not already document its board.

| Part | Workshop hardware |
|---|---|
| Board | ESP32-2432S028R Cheap Yellow Display |
| Processor | ESP32-WROOM-32, 240 MHz |
| Flash | 4 MB |
| PSRAM | None |
| Display | 2.8-inch 320x240 ILI9341-compatible RGB565 |
| Touch | XPT2046 resistive single-touch |
| USB serial | CH340 |
| WiFi | 2.4 GHz |
| Upload speed | 460800 |
| Serial monitor | 115200 |

## Built-in hardware

- Display: GPIO 2, 12, 13, 14, 15, and 21
- Touch: GPIO 25, 32, 33, 36, and 39 on a separate SPI bus
- Active-low RGB LED: GPIO 4, 16, and 17
- Light sensor: GPIO 34
- Speaker amplifier output: GPIO 26
- microSD: GPIO 5, 18, 19, and 23
- I2C-friendly connector: GPIO 22 and 27

## Constraints

- Preserve partial display buffering. A full RGB565 frame is 153,600 bytes.
- Keep touch controls about 30 to 44 pixels or larger.
- Avoid large stack allocations, duplicate images, and unbounded JSON documents.
- Keep the main loop responsive. Do not block LVGL callbacks.
- Measure RAM and flash after every build.
- Display inversion differs by panel. Read the project configuration and local device profile instead of guessing from the USB sockets.
