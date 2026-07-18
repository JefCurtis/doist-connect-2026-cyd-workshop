# Troubleshooting

Work from the connection upward. Do not change game code to fix a missing serial port.

## No serial device appears

Symptoms:

- CYD has power but `pio device list` shows no USB serial device
- Upload reports that no port can be found

Check in this order:

1. Use a cable already verified for data.
2. Try another USB port or adapter.
3. On a dual-USB CYD, try Micro-USB or USB-A through an adapter instead of USB-C-to-USB-C.
4. Install or reinstall the CH340 driver.
5. Restart the laptop after driver installation.
6. Disconnect and reconnect the CYD.

Mac users can check WhatCable. **USB Serial, Full Speed (12 Mbps)** means data is working even if the app shows a slow-device warning.

## Upload cannot connect

- Close the serial monitor before uploading. Only one program can own the port.
- Confirm the port did not change after reconnecting.
- Specify it explicitly with `--upload-port`.
- Keep upload speed at 460800. If a specific clone remains unreliable, temporarily try 115200.
- Press and hold BOOT while upload begins, then release it after PlatformIO starts connecting.

## Display is bright but blank

- Confirm the upload completed and the ESP32 restarted.
- Open `pio device monitor -b 115200` and look for `Tap Quest starting...`.
- Confirm the board has an ILI9341-compatible display.
- Do not use an ST7789 board without changing the display driver.

## Colors are inverted

Switch environments and upload again:

```bash
pio run -e cyd -t upload
```

or:

```bash
pio run -e cyd2usb -t upload
```

## Text or graphics are garbled

- Verify the exact board model.
- Confirm `ILI9341_2_DRIVER` remains defined in `platformio.ini`.
- Restore the workshop pin definitions before debugging application code.
- Try the other display environment only for color inversion, not for an entirely different controller.

## Touch does not respond

- Confirm the board uses XPT2046 resistive touch.
- Press rather than lightly brushing the panel.
- Check whether touches are offset rather than absent.
- Restore the touch pin definitions in `include/config.h`.
- If one unit is consistently offset, calibrate its raw minimum and maximum values in `display_touch.cpp`.

## Touch is offset or reversed

The raw touch ranges vary slightly by panel. The starter maps approximately 200 to 3800 into the screen dimensions. Use a touch calibration sketch to measure the unit, then update the map values.

Also confirm both display and touch use rotation 1.

## Build fails while downloading libraries

- Check internet access.
- Retry outside a restricted hotel network.
- Run the first build before the workshop.
- Delete only the failed package from `.pio/libdeps/` if PlatformIO reports a corrupt download.
- Do not randomly upgrade library versions during the workshop.

## Build succeeds but firmware crashes

Open the serial monitor and capture the exception. Common causes include:

- Holding large arrays or JSON documents on the stack
- Allocating a full or double framebuffer
- Running out of heap after enabling WiFi and TLS
- Using an LVGL object after its screen was cleaned
- Doing blocking work inside a touch event callback

Measure before guessing. Print `ESP.getFreeHeap()` before and after large operations.

## WiFi will not connect

- Confirm the network is 2.4 GHz compatible.
- Avoid networks requiring a browser login or terms acceptance.
- Use a known hotspot or travel router.
- Add a timeout. Never leave the device in an infinite connection loop.
- Keep the offline game available when connection fails.
