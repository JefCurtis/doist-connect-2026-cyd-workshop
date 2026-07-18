---
name: cyd-development
description: Builds, flashes, debugs, and extends ESP32-2432S028R firmware using PlatformIO, Arduino, LVGL, TFT_eSPI, XPT2046 touch, storage, WiFi, and HTTP APIs. Use after workshop setup when changing firmware, game behavior, hardware, UI, persistence, connectivity, or data code, or diagnosing build, upload, display, touch, memory, and network failures.
compatibility: Requires PlatformIO and an ESP32-2432S028R with ILI9341-compatible display and XPT2046 resistive touch.
---

# CYD development

Use `cyd-workshop-init` for one-time laptop and device setup. Use this skill for ongoing firmware work after setup.

## Start every firmware task

1. Read `../../../AGENTS.md`.
2. Read `../../../docs/ARCHITECTURE.md` and `../../../docs/HARDWARE.md`.
3. Inspect `../../../platformio.ini` and `../../../include/config.h`.
4. Classify the requested change by layer: hardware, UI, game, local data, network, or API data.
5. Run `python3 ../../../scripts/doctor.py` when diagnosing setup or upload problems.

## Work within the layers

- Hardware and pins: `src/hardware/`, `include/config.h`, `platformio.ini`
- LVGL screens and events: `src/ui/`
- Rules and state independent of LVGL: `src/game/`
- Preferences, files, and API models: `src/data/`
- WiFi and HTTP lifecycle: create or use `src/network/`
- Main coordination only: `src/main.cpp`

Do not solve a missing serial port in application code. Do not put game rules in a display driver or blocking network calls in an LVGL callback.

## Preserve device constraints

- Keep partial RGB565 buffering unless RAM use is calculated and measured.
- Assume no PSRAM and about 320 KB of application RAM.
- Keep controls at least 30 to 44 pixels for resistive touch.
- Keep the offline game path when adding WiFi.
- Never commit credentials. Use a gitignored `include/secrets.h` when needed.
- Support `cyd` and `cyd2usb` display inversion environments.

## Verify

```bash
pio run
```

Report RAM and flash usage from the build summary. Upload only when the user approves replacing current firmware:

```bash
pio run -e cyd2usb -t upload
```

Use `-e cyd` for the original non-inverted panel. After hardware testing, report the board variant, port, display, touch, LED, and serial behavior that were actually verified.

For common failures, read `../../../docs/TROUBLESHOOTING.md`. For network work, read `../../../docs/LEADERBOARD.md` before implementing the API client.
