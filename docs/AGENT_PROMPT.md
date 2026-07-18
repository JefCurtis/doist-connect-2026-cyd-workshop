# Fallback AI agent prompt

The repository includes an Agent Skill under `.agents/skills/cyd-development/`. If your coding agent does not discover that skill, paste the prompt below at the start of the session.

```text
You are working on firmware for an ESP32-2432S028R Cheap Yellow Display.

Before editing code:
1. Read README.md, PREWORK.md, docs/ARCHITECTURE.md, docs/HARDWARE.md, and AGENTS.md.
2. Read platformio.ini as the source of truth for the board, drivers, pins, library versions, upload speed, and display variant.
3. Identify which layers the request touches: hardware, UI, game logic, local data, network, or API data.

Hardware assumptions:
- ESP32-WROOM-32 with 4 MB flash and no PSRAM
- 320x240 ILI9341-compatible RGB565 display
- XPT2046 resistive single-touch controller
- CH340 USB serial bridge
- Upload speed 460800 and serial monitor 115200
- Original `cyd` and inverted dual-USB `cyd2usb` PlatformIO environments

Engineering rules:
- Keep pin assignments and display flags out of application logic.
- Keep LVGL objects and events in src/ui.
- Keep game rules independent of LVGL in src/game.
- Keep persistence and API formats in src/data.
- Put WiFi and HTTP lifecycle code in src/network.
- Never hardcode or commit WiFi passwords, API tokens, or private endpoints.
- Preserve partial display buffering. Do not add a full or double framebuffer without calculating RAM use.
- Do not perform long delays, WiFi connection loops, or blocking HTTP requests in LVGL event callbacks.
- Design touch targets for a resistive screen. Prefer at least 30 to 44 pixels.
- Preserve an offline path when adding networking.
- Build after changes with `pio run`.
- Do not upload firmware unless the user asks. Uploading replaces the device's current firmware.

When finished, report:
- Files changed
- Architectural layers touched
- Build result and RAM/flash summary
- Hardware behavior that still needs testing
- Any assumptions about the CYD variant
```
