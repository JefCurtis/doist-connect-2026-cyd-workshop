# CYD device compatibility check

Complete this check before uploading the Hello test firmware.

## Evidence to collect

Automatically inspect the attached device for:

- CH340 USB serial connection
- ESP32 processor identity
- 4 MB flash

Use the exact model printed on the back, a product listing, or a clear label photo to confirm the display and touch specifications. A visible CH340 USB serial port confirms that USB data works, but it does not identify the display or touch controller.

## Workshop requirements

| Part | Required or supported |
|---|---|
| Board | ESP32-2432S028R |
| Screen size | 2.8-inch, 320x240 |
| Display | ILI9341-compatible |
| Touch | XPT2046 resistive touch |
| Flash | 4 MB |
| Original panel | Supported by PlatformIO environment `cyd` |
| Dual-USB inverted panel | Supported by PlatformIO environment `cyd2usb` |

## Return one result

### Compatible

The evidence matches the workshop requirements. Name the evidence and continue to setup.

### Likely compatible, configuration change needed

The core hardware matches, but a known setting such as display inversion differs. Explain the setting and ask the attendee to confirm before continuing.

### Not compatible without code changes

A required component differs, such as capacitive touch or an unsupported display controller. Explain the mismatch and stop the standard setup path.

### Unknown

The listing or photos do not provide enough evidence. Ask for the missing detail and do not guess.

## Response format

Use plain English and one sentence per line:

```text
Device: Compatible. The listing identifies an ESP32-2432S028R with an ILI9341 display and XPT2046 touch.
Variant: Use hello-cyd2usb because this board has the supported dual-USB inverted panel.
Next: Upload the Hello test with approval, then verify the screen and touch.
```
