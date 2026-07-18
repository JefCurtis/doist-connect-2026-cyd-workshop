# Doist Connect Denmark 2026: CYD Workshop

Build, flash, and change a touchscreen game on a Cheap Yellow Display in one hour.

The starter project is **Tap Quest**, a small whack-a-mole-style game. A target moves around the screen, gets smaller as your score rises, flashes the onboard RGB LED, and saves the high score on the device. It works without WiFi so the workshop does not depend on hotel networking.

## Prerequisites: complete these before the workshop

The setup skill works on macOS, Windows, and Linux. It checks the attached device, installs missing software with your approval, and flashes a small **Hello, CYD!** screen. Tap Quest is not installed until the workshop.

### What you need

- ESP32-2432S028R Cheap Yellow Display
- USB data cable. A charge-only cable may power the screen but cannot connect the device; the setup skill will test this. Mac users can optionally use [WhatCable](https://www.whatcable.uk/) when troubleshooting.
- Laptop with admin access
- Git installed
- An AI coding agent that can read this repository and run terminal commands

The recommended board is this [ESP32 "Bruce" CYD package on AliExpress](https://www.aliexpress.com/item/1005009383089648.html). Similar devices should use an ESP32-2432S028R, 2.8-inch 320x240 ILI9341-compatible display, XPT2046 resistive touch, and 4 MB flash.

### 1. Clone the repository

A simple place to keep the project is your **Documents** folder:

```bash
cd ~/Documents
git clone https://github.com/JefCurtis/doist-connect-2026-cyd-workshop.git
cd doist-connect-2026-cyd-workshop
```

On Windows PowerShell, use `cd $HOME\Documents` for the first command.

| Command | What it does |
|---|---|
| `cd` | Moves the terminal into Documents, then into the downloaded project. |
| `git clone` | Downloads the workshop game, setup skills, hardware configuration, and documentation. |

### 2. Connect and open the project

1. Plug the CYD into your laptop with the USB cable.
2. Open the repository folder in Cursor, VS Code, or another AI coding tool.
3. Start an AI agent that can read files and run terminal commands in this folder.

### 3. Run the setup skill

Run:

```text
/skill:cyd-workshop-init
```

The skill checks the attached ESP32 and flash, verifies the serial connection, installs only missing tools with your approval, builds the Hello screen, and asks before flashing it. It uses the model label for display and touch details because those parts cannot identify themselves over USB.

If you prefer to run the instructions manually, use the copyable [AI setup prompt](docs/PREWORK_AGENT.md) or the detailed [command reference](docs/COMMAND_REFERENCE.md).

### You are ready when

- [ ] **Device:** ESP32, 4 MB flash, display, and touch are confirmed
- [ ] **Connection:** Laptop sees the CYD serial port
- [ ] **Tools:** Git, Python 3, and PlatformIO are ready
- [ ] **Build:** Hello firmware compiles successfully
- [ ] **Screen:** CYD shows “Hello, CYD!” and changes to “Touch works!” when tapped

The first workshop step replaces this Hello screen with Tap Quest.

## Hardware and software

### Hardware

| Part | What the workshop expects |
|---|---|
| CYD | Recommended: [ESP32 "Bruce" package](https://www.aliexpress.com/item/1005009383089648.html). Similar ESP32-2432S028R boards should work when they use an ILI9341-compatible display and XPT2046 resistive touch. |
| Display | ILI9341-compatible SPI display |
| Touch | XPT2046 resistive touchscreen |
| USB | A known data cable, not a charge-only cable |
| Built in | WiFi, Bluetooth, RGB LED, light sensor, microSD slot |
| Optional | Small speaker with the correct connector |

### Software

| Tool | Its job |
|---|---|
| VS Code, Cursor, or another editor | Edit and navigate the project. The editor is your choice; the workshop uses PlatformIO to build and upload. |
| Python 3 | Run the optional cross-platform preflight checker |
| PlatformIO | Download libraries, compile C++, upload firmware, and open the serial monitor |
| Arduino framework | Provides the ESP32 runtime, timing, storage, WiFi, and hardware APIs |
| TFT_eSPI | Sends pixel data to the display over SPI |
| XPT2046_Touchscreen | Reads raw touch coordinates from the touch controller |
| LVGL 9 | Creates screens, labels, buttons, styles, and touch events |
| Preferences/NVS | Saves the high score when power is removed |

See [docs/ARCHITECTURE.md](docs/ARCHITECTURE.md) for the complete path from a code edit to a pixel or API response.

## Workshop quick start: install Tap Quest

After the Hello preflight passes, the workshop begins by replacing it with Tap Quest:

```bash
pio run -e cyd2usb -t upload
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

## What the CYD can do

| Capability | In practice |
|---|---|
| 320x240 touchscreen | Build a focused game, task list, remote, clock, or status screen. |
| ESP32 processor | Run responsive UI, timers, simple animation, game logic, and JSON parsing. |
| WiFi | Call APIs, fetch data, or send scores over a normal 2.4 GHz network. |
| Bluetooth and ESP-NOW | Control nearby devices or communicate directly with another ESP32. |
| Local storage and microSD | Save settings and scores internally, or keep larger assets on a card. |
| LED, light sensor, and speaker output | Add color, ambient-light behavior, and optional sound. |

## A few practical limits

| Limit | In practice |
|---|---|
| 4 MB flash | The default app partition is about 1.3 MB. Tap Quest uses about 591 KB, so large images and sound belong on microSD. |
| About 320 KB RAM and no PSRAM | There is not enough memory for multiple full-screen buffers. This project renders 20 rows at a time instead. |
| SPI display, no GPU | Buttons and small animations work well. Video and constant full-screen animation do not. |
| Resistive single-touch screen | Use larger controls. Multitouch and phone-style gestures are not available. |
| WiFi uses extra memory | Keep an offline mode and avoid blocking the touch interface during API calls. |
| Limited free pins and board variants | Prefer built-in hardware and use the matching `cyd` or `cyd2usb` configuration. |

## How the code is separated

```text
src/
├── main.cpp                   setup and main loop
├── hardware/                  shared display, touch, and RGB LED
├── preflight/                 Hello CYD setup screen
├── game/                      Tap Quest rules and game state
├── ui/                        Tap Quest LVGL screens and events
└── data/                      persistent high-score storage
```

Future WiFi and API code should go into `src/network/` and `src/data/`, not into the UI event handlers.

## Continue after the workshop

Start with the progressive tasks in [docs/EXERCISES.md](docs/EXERCISES.md). Stretch goals include lives, combos, sound, adaptive difficulty, two-device multiplayer, over-the-air updates, and an API-backed leaderboard. The suggested leaderboard contract is in [docs/LEADERBOARD.md](docs/LEADERBOARD.md).

## Working with an AI coding agent

The repository includes two project-local skills following the [Agent Skills standard](https://agentskills.io/specification):

- `cyd-workshop-init` handles one-time setup on macOS, Windows, or Linux. It checks the attached device, installs missing tools with approval, and installs the Hello test firmware.
- `cyd-development` is used afterward for game changes, LVGL work, hardware features, troubleshooting, networking, and API stretch goals.

Compatible agents discover `cyd-development` automatically when a request matches its description, so attendees do not need to run it manually. Its hardware rules and workflows apply beyond Tap Quest to other CYD projects built from this repository.

[docs/AGENT_PROMPT.md](docs/AGENT_PROMPT.md) contains fallback instructions for tools that do not load skills.

## Troubleshooting and references

- [AI-guided setup prompt](docs/PREWORK_AGENT.md)
- [Device compatibility rules](docs/DEVICE_COMPATIBILITY.md)
- [Manual command reference](docs/COMMAND_REFERENCE.md)
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
