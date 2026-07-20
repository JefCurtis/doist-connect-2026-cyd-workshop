# CYD device compatibility check

Do not block setup because a case hides the model label. Use the attached hardware and the Hello test.

## Before uploading

Automatically check for:

- CH340 USB serial connection
- ESP32 processor
- 4 MB flash

When all three pass, classify the device as **Likely compatible** and continue building the Hello test. USB cannot identify the display or touch controller, so those are confirmed by the actual screen and tap test.

## Choosing a Hello configuration

The only difference between the two workshop configurations is display color inversion. Choosing the wrong one will not damage the device.

| Visible USB sockets | Configuration to try first |
|---|---|
| Two sockets total, normally one USB-C and one Micro-USB | `hello-cyd2usb` |
| One Micro-USB socket | `hello-cyd` |
| Unclear or partly hidden by a case | `hello-cyd2usb` |

If asking about ports, use this exact wording:

> How many physical USB sockets can you see? Count both USB-C and Micro-USB.

This answer is optional and must never block compilation.

## After uploading

| Result | Classification and next step |
|---|---|
| “Hello, CYD!” appears with normal colors and the button changes to “Touch works!” | **Compatible.** Setup is complete. |
| Screen and touch work, but colors are inverted | **Supported variant.** Upload the other Hello configuration. |
| Screen is blank or garbled | **Needs code changes.** The display may use a different controller. |
| Screen works but touch does not | **Needs code changes.** The touch controller or calibration may differ. |

After a successful test, save the passing Hello and Tap Quest environments, current serial port, chip, flash size, display result, and touch result in the gitignored `.cyd-device.json`. Later agent sessions should trust the tested environment but recheck the serial port before uploading.

## Status language

Before the Hello upload:

```text
Device: Likely, the attached board reports an ESP32 processor and 4 MB flash over a working CH340 serial connection.
```

After a successful screen and touch test:

```text
Device: Pass, the Hello screen, colors, and touchscreen all work with the selected configuration.
```
