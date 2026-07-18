# CYD workshop agent guidance

Read these before changing firmware:

- `README.md`
- `docs/ARCHITECTURE.md`
- `docs/HARDWARE.md`
- `.agents/skills/cyd-development/SKILL.md`

## Supported target

- ESP32-2432S028R with 4 MB flash and no PSRAM
- ILI9341-compatible 320x240 display
- XPT2046 resistive touch
- `cyd` and `cyd2usb` PlatformIO environments
- Upload at 460800 baud, monitor at 115200

## Rules

- `platformio.ini` and `include/config.h` are the hardware source of truth.
- Keep hardware, UI, game logic, local data, and future network code separate.
- Keep LVGL calls in `src/ui` or the display adapter.
- Do not block LVGL callbacks with delays, WiFi loops, or HTTP requests.
- Preserve partial rendering unless a memory calculation proves a change is safe.
- Prefer touch targets at least 30 to 44 pixels.
- Keep the game useful offline.
- Never commit credentials or API tokens.
- Run `pio run` after changes.
- Do not flash a connected device unless the user approves replacing its firmware.
- Never add co-author trailers to commits.
