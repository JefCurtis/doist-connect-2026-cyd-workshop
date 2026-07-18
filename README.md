# Doist Connect Denmark 2026: CYD Workshop

Build, flash, and change a touchscreen game on a Cheap Yellow Display in one hour.

The starter project is **Tap Quest**, a small whack-a-mole-style game. A target moves around the screen, gets smaller as your score rises, flashes the onboard RGB LED, and saves the high score on the device. It works without WiFi so the workshop does not depend on hotel networking.

## Prerequisites: complete these before the workshop

Setup time is not included in the workshop hour. Complete every item in [PREWORK.md](PREWORK.md) before arriving.

- [ ] ESP32-2432S028R CYD with an ILI9341 display and XPT2046 resistive touch
- [ ] Laptop with Git, Python 3, VS Code, and the PlatformIO IDE extension
- [ ] USB data cable and any adapter your laptop needs
- [ ] CH340 USB serial driver installed if your computer needs it
- [ ] CYD appears as a serial device in PlatformIO
- [ ] Repository cloned and dependencies downloaded
- [ ] Both `pio run` and the preflight upload complete successfully
- [ ] Tap Quest appears on the device and responds to touch
- [ ] A project idea described as: "When ___ happens, the device should ___"

Mac users must also install [WhatCable](https://www.whatcable.uk/). When the CYD is attached, **Connected devices: USB Serial, Full Speed (12 Mbps)** confirms the cable carries data. WhatCable may still call it a slow device because the CH340 serial chip does not need high-speed USB.

Run the automated checks from the repository root:

```bash
python3 scripts/doctor.py --build
```

## Hardware and software

### Hardware

| Part | What the workshop expects |
|---|---|
| CYD | ESP32-2432S028R, 2.8-inch 320x240 display |
| Display | ILI9341-compatible SPI display |
| Touch | XPT2046 resistive touchscreen |
| USB | A known data cable, not a charge-only cable |
| Built in | WiFi, Bluetooth, RGB LED, light sensor, microSD slot |
| Optional | Small speaker with the correct connector |

### Software

| Tool | Its job |
|---|---|
| VS Code | Edit and navigate the project |
| Python 3 | Run the optional cross-platform preflight checker |
| PlatformIO | Download libraries, compile C++, upload firmware, and open the serial monitor |
| Arduino framework | Provides the ESP32 runtime, timing, storage, WiFi, and hardware APIs |
| TFT_eSPI | Sends pixel data to the display over SPI |
| XPT2046_Touchscreen | Reads raw touch coordinates from the touch controller |
| LVGL 9 | Creates screens, labels, buttons, styles, and touch events |
| Preferences/NVS | Saves the high score when power is removed |

See [docs/ARCHITECTURE.md](docs/ARCHITECTURE.md) for the complete path from a code edit to a pixel or API response.

## Quick start

```bash
git clone https://github.com/JefCurtis/doist-connect-2026-cyd-workshop.git
cd doist-connect-2026-cyd-workshop
pio device list
pio run -e cyd2usb -t upload
pio device monitor -b 115200
```

`cyd2usb` is the default for newer dual-USB boards. If the colors are inverted, upload the original-board environment instead:

```bash
pio run -e cyd -t upload
```

Uploading replaces whatever firmware is currently installed. You can always restore another project by uploading it again.

## Your one-hour checklist

| Time | Task | Done when |
|---|---|---|
| 0:00 to 0:08 | Connect and upload the starter | Tap Quest opens on your CYD |
| 0:08 to 0:15 | Trace the software layers | You can identify PlatformIO, hardware, UI, game, and data files |
| 0:15 to 0:25 | Change the game title and colors | Your version looks visibly different |
| 0:25 to 0:35 | Change duration, target size, and difficulty | Your rules run on the device |
| 0:35 to 0:45 | Change the RGB LED feedback | A hit produces your chosen feedback |
| 0:45 to 0:55 | Add one small game feature | Your version has one behavior the starter did not |
| 0:55 to 1:00 | Choose a stretch goal | You know which layer to change next |

The exact exercises and file locations are in [docs/EXERCISES.md](docs/EXERCISES.md).

## What the CYD can do in practical terms

| Capability | What that means in a real project |
|---|---|
| 320x240 color touchscreen | Enough room for a focused dashboard, remote control, small game, task list, clock, or status display. Design one clear screen at a time rather than shrinking a desktop interface. |
| ESP32 processor | Fast enough for responsive menus, touch events, timers, basic animation, game logic, JSON parsing, and background network requests. |
| WiFi radio | The device can call REST APIs, receive configuration, serve a small local web page, or send scores to a leaderboard. It needs a normal 2.4 GHz network without a browser-based sign-in page. |
| Bluetooth and ESP-NOW | Projects can act as simple wireless controls or communicate directly with nearby ESP32 devices without normal WiFi infrastructure. |
| Persistent local storage | Settings and high scores can survive a restart without an SD card or server. Storage is small, so save configuration and state rather than large assets. |
| microSD slot | Large images, sound files, logs, or game data can live on removable storage instead of consuming firmware flash. |
| RGB LED, light sensor, and speaker output | The project can react outside the screen with status colors, ambient-light behavior, and optional sound. A speaker is not included on most boards. |
| Low price and USB power | It is practical to dedicate a device to one purpose, leave it on a desk, or give one to every workshop attendee. |

## Where the CYD is constrained in practical terms

| Constraint | What it means in a real project | How this starter handles it |
|---|---|---|
| 4 MB flash | Flash is the device's disk, not its working memory. The default partition gives this firmware about 1.3 MB for compiled code. Fonts, image arrays, libraries, and TLS code consume it quickly. Large media belongs on microSD, and unused features should stay out of the build. | The initial Tap Quest build is roughly 591 KB, leaving useful space for exercises. |
| No PSRAM | There is no large external working-memory chip. PlatformIO exposes about 320 KB of application RAM. One 320x240 RGB565 framebuffer needs 153,600 bytes. Two need 307,200 bytes, before LVGL, WiFi, or your game allocate anything. | LVGL renders through a 20-row, 12,800-byte partial buffer instead of holding the whole screen twice. |
| SPI display, no GPU | Every changed pixel travels over a serial bus. Menus and small animations feel good, but desktop-style effects, video, and frequent full-screen redraws will stutter or consume the processor. | Only the timer, score, and target change during play. |
| Resistive single-touch input | Touch is pressure-based, less precise than a phone, and cannot do multitouch gestures. Tiny controls and gesture-heavy games are frustrating. | The target starts at 58 pixels and never shrinks below 30 pixels. |
| WiFi shares limited RAM | HTTPS certificates, sockets, and JSON can consume a large part of the free heap. Blocking API calls can also freeze touch handling. | The base game is offline. Network work is a separate stretch goal and must not run inside an LVGL event callback. |
| Few free GPIO pins | The display, touch, SD card, LED, light sensor, and backlight already use most pins. Only a few pins are easily available for sensors. | Exercises use hardware already on the board. External add-ons are optional. |
| Board variants | Boards sold under similar names can invert colors or use a different display or touch controller. One firmware configuration will not fix every clone. | PlatformIO includes `cyd` and `cyd2usb` environments. The workshop supports ILI9341 plus XPT2046 boards. |
| USB serial bridge | The classic ESP32 does not provide native USB here. A CH340 chip and working driver create the serial port used for flashing. | Pre-work verifies the cable, driver, serial port, and first upload. |

## How the code is separated

```text
src/
├── main.cpp                   setup and main loop
├── hardware/                  display, touch, and RGB LED
├── game/                      rules and game state
├── ui/                        LVGL screens and events
└── data/                      persistent high-score storage
```

Future WiFi and API code should go into `src/network/` and `src/data/`, not into the UI event handlers.

## Continue after the workshop

Start with the progressive tasks in [docs/EXERCISES.md](docs/EXERCISES.md). Stretch goals include lives, combos, sound, adaptive difficulty, two-device multiplayer, over-the-air updates, and an API-backed leaderboard. The suggested leaderboard contract is in [docs/LEADERBOARD.md](docs/LEADERBOARD.md).

## Working with an AI coding agent

The repository includes two options:

- `.agents/skills/cyd-development/SKILL.md` is a project-local skill following the [Agent Skills standard](https://agentskills.io/specification).
- [docs/AGENT_PROMPT.md](docs/AGENT_PROMPT.md) is a fallback prompt for tools that do not load skills.

The skill teaches the agent the board variant, pin assignments, memory limits, architecture boundaries, safe build process, and common display and touch failures.

## Troubleshooting and references

- [Pre-work and prerequisites](PREWORK.md)
- [Architecture](docs/ARCHITECTURE.md)
- [Hardware and practical limits](docs/HARDWARE.md)
- [Exercises and stretch goals](docs/EXERCISES.md)
- [Troubleshooting](docs/TROUBLESHOOTING.md)
- [CYD community repository](https://github.com/witnessmenow/ESP32-Cheap-Yellow-Display)
- [Community project gallery](https://github.com/witnessmenow/ESP32-Cheap-Yellow-Display/blob/main/PROJECTS.md)
- [LVGL documentation](https://docs.lvgl.io/)
- [PlatformIO documentation](https://docs.platformio.org/)

## License

MIT
