# Hardware and practical limits

## Supported board

The workshop targets the ESP32-2432S028R Cheap Yellow Display:

| Component | Expected hardware |
|---|---|
| Processor | ESP32-WROOM-32 at up to 240 MHz |
| Flash | 4 MB |
| PSRAM | None |
| Display | 2.8-inch, 320x240, ILI9341-compatible, RGB565 |
| Touch | XPT2046 resistive single-touch controller |
| USB serial | CH340 |
| Wireless | 2.4 GHz WiFi and Bluetooth |
| Storage | Internal NVS plus microSD slot |

## Useful built-in hardware

| Feature | Pin or bus | Practical use |
|---|---|---|
| Display | GPIO 2, 12, 13, 14, 15, 21 | UI, images, dashboards, and games |
| Touch | GPIO 25, 32, 33, 36, 39 | Buttons, sliders, drawing, and direct manipulation |
| RGB LED | GPIO 4, 16, 17, active-low | Success, warning, connection, or game feedback |
| Light sensor | GPIO 34 | Automatic brightness or ambient-light game rules |
| Speaker amplifier | GPIO 26 | Beeps or audio when an external speaker is attached |
| microSD | GPIO 5, 18, 19, 23 | Assets, logs, audio, and configuration |
| I2C-friendly connector | GPIO 22 and 27 | A small sensor or controller add-on |

## Flash is not RAM

The advertised 4 MB flash is long-term storage for boot data, firmware partitions, settings, and optional files. It is not all available to the compiled program. The default PlatformIO partition allocates roughly 1.3 MB to this firmware image.

Practical consequences:

- A few small fonts and icons are fine.
- Large bitmap collections embedded as C arrays become expensive quickly.
- Adding libraries can increase firmware even if only a little code is visible.
- Large assets belong on microSD.
- Changing the partition table can create more app space, but reduces room for other features such as OTA slots or a filesystem.

Check every build's summary instead of guessing:

```text
RAM:   11.0% (36,116 bytes of 327,680)
Flash: 45.1% (591,361 bytes of 1,310,720)
```

These are measurements from the initial Tap Quest build. Library versions can change them.

## No PSRAM means no large spare workspace

PSRAM is an external memory chip used by some ESP32 boards for large framebuffers, image decoding, and data sets. The standard CYD does not have it.

Practical consequences:

- Avoid keeping duplicate images or large JSON documents in memory.
- Stream or process data in pieces when possible.
- Use partial display buffers.
- Watch free heap when combining LVGL, WiFi, TLS, and JSON.
- Release HTTP clients and large documents as soon as work is complete.
- Test on hardware. A program can compile successfully and still run out of heap at runtime.

## The display is a serial peripheral

The ESP32 sends display commands and pixels over SPI. There is no desktop GPU or video memory.

Good fits:

- Buttons, labels, charts, menus, and focused dashboards
- Small animated regions
- Board games and reaction games
- Status screens that update a few times per second

Poor fits without substantial optimization:

- Video
- Large transparency effects
- Frequent full-screen animation
- Multiple full-resolution image layers
- Interfaces copied directly from a desktop monitor

## Resistive touch needs larger targets

The screen detects pressure rather than the capacitance of a finger. It provides one touch point and has lower precision near edges.

Use controls at least 30 to 44 pixels where possible. Do not rely on multitouch, pinch gestures, or tiny icon-only controls. Calibration can vary slightly between units.

## Networking has environmental constraints

The ESP32 uses 2.4 GHz WiFi. It usually cannot join hotel or conference networks that require accepting terms in a browser. WPA Enterprise networks may also need special handling.

For development, use a known 2.4 GHz network or a compatible hotspot. Build an offline mode so the device still has a useful screen when the network or API is unavailable.

## Board variants

The name on a marketplace listing is not enough. Common differences include:

- Dual-USB panels that need color inversion
- USB-C connectors missing the resistors needed for USB-C-to-USB-C cables
- ST7789 displays instead of ILI9341
- Capacitive touch instead of XPT2046 resistive touch

This repository handles the common color inversion difference with two PlatformIO environments. Other controllers require driver and pin changes.
