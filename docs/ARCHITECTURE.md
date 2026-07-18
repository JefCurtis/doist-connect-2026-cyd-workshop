# Architecture: from laptop to touchscreen

The repository keeps each responsibility in a separate layer. This makes the project easier to explain, debug, and extend.

## Layer map

| Layer | Main tools | Responsibility | Files |
|---|---|---|---|
| Development | VS Code, Git | Edit source and track changes | Entire repository |
| Build and upload | PlatformIO, compiler, esptool | Resolve libraries, compile C++, create firmware, flash over serial | `platformio.ini` |
| Runtime platform | ESP32 Arduino framework | Startup, main loop, timing, random numbers, Preferences, future WiFi | `src/main.cpp` and framework APIs |
| Display driver | TFT_eSPI | Configure ILI9341 pins and send RGB565 pixels over SPI | `platformio.ini`, `src/hardware/display_touch.cpp` |
| Touch driver | XPT2046_Touchscreen | Read pressure and coordinates over a separate SPI controller | `src/hardware/display_touch.cpp` |
| UI framework | LVGL 9 | Create objects, styles, layouts, input events, and partial rendering | `include/lv_conf.h`, `src/ui/` |
| Game logic | Plain C++ | Track status, score, time, difficulty, and target position | `src/game/` |
| Hardware feedback | Arduino GPIO | Drive the active-low RGB LED without blocking the game loop | `src/hardware/status_led.*` |
| Local data | Preferences/NVS | Persist the high score in flash | `src/data/` |
| Future network | ESP32 WiFi, HTTPClient | Join 2.4 GHz WiFi and exchange HTTP requests | Add `src/network/` |
| Future API data | ArduinoJson and a score client | Serialize and parse leaderboard messages | Add to `src/data/` |

## What happens when you press Upload

1. PlatformIO reads `platformio.ini`.
2. It downloads pinned libraries if they are missing.
3. The compiler turns each C++ source file into machine code for the ESP32.
4. The linker combines the app, Arduino framework, and libraries into firmware.
5. esptool resets the ESP32 through the CH340 serial bridge.
6. Firmware is written to flash.
7. The ESP32 restarts and executes `setup()`.
8. `loop()` repeatedly services LVGL, game timing, and LED timing.

## What happens when you tap the target

1. The XPT2046 touch controller measures the press.
2. `readTouch()` maps raw values into 320x240 screen coordinates.
3. LVGL decides which object received the press.
4. LVGL calls the target's event handler in `game_ui.cpp`.
5. The UI asks `tap_game.cpp` to register a hit.
6. The game updates score, size, and the next position.
7. The UI moves the LVGL object and changes the score label.
8. The hardware layer flashes the RGB LED.
9. LVGL redraws only the changed screen regions.

## Dependency direction

```text
main
├── hardware
├── game
└── UI
    ├── game
    ├── hardware feedback
    └── local data
```

Keep these boundaries when extending the project:

- Hardware files know pins and drivers.
- UI files know LVGL objects and visual state.
- Game files know rules but not LVGL.
- Data files know storage or API formats but not screen layout.
- Network files know connections but not game rules.
- `main.cpp` coordinates modules and stays small.

## Timing rule

LVGL and touch input only stay responsive when `loop()` runs frequently. Do not use long `delay()` calls or make blocking HTTPS calls from an LVGL event callback. Set a flag or queue work, then process it incrementally from the main loop.

## Memory rule

The display is 320 x 240 pixels using RGB565, or 2 bytes per pixel:

```text
320 x 240 x 2 = 153,600 bytes
```

A second full buffer would bring that to 307,200 bytes. PlatformIO reports about 320 KB of application RAM on this board, so double buffering would leave almost nothing for LVGL objects, stacks, WiFi, and TLS.

This project uses 20 rows:

```text
320 x 20 x 2 = 12,800 bytes
```

That trades some display throughput for a much safer memory budget.
