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

### 2. Connect and open the project

1. Plug the CYD into your laptop with the USB cable.
2. Open the repository folder in Cursor, VS Code, or another AI coding tool.
3. Start an AI agent that can read files and run terminal commands in this folder.

### 3. Run the setup skill

Run:

```text
/skill:cyd-workshop-init
```

The skill checks the attached ESP32 and flash, verifies the serial connection, installs only missing tools with your approval, builds the Hello screen, and asks before flashing it. It defaults safely to the common dual-USB configuration, then uses the actual screen and touch result to confirm compatibility. A hidden model label does not block setup.

If you prefer to run the instructions manually, use the copyable [AI setup prompt](docs/PREWORK_AGENT.md) or the detailed [command reference](docs/COMMAND_REFERENCE.md).

### You are ready when

- [ ] **Device:** ESP32, 4 MB flash, display, and touch are confirmed
- [ ] **Connection:** Laptop sees the CYD serial port
- [ ] **Tools:** Git, Python 3, and PlatformIO are ready
- [ ] **Build:** Hello firmware compiles successfully
- [ ] **Screen:** CYD shows “Hello, CYD!” and changes to “Touch works!” when tapped

The first workshop step replaces this Hello screen with Tap Quest.

Once onboarding is complete, you can also work directly with [ChoreQuest](https://github.com/JefCurtis/chorequest) instead. It uses the same CYD foundation and adds WiFi, the Todoist API, recurring tasks, rewards, and more complex data handling.

## Workshop start: install Tap Quest

After the Hello preflight passes, tell your AI agent:

```text
Replace the Hello test with Tap Quest. Choose the correct board configuration, build it, ask before uploading, and verify that the game starts.
```

The agent will use the device information collected during setup, build the correct Tap Quest configuration, and ask before replacing the Hello firmware. If you prefer to run the command yourself, use the [manual command reference](docs/COMMAND_REFERENCE.md).

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

## Troubleshooting and references

| Resource | What it covers |
|---|---|
| [AI-guided setup prompt](docs/PREWORK_AGENT.md) | Manual fallback for agents that cannot load the setup skill. |
| [Device compatibility](docs/DEVICE_COMPATIBILITY.md) | How the attached board and Hello test determine compatibility. |
| [Command reference](docs/COMMAND_REFERENCE.md) | Plain-English explanations of build and upload commands. |
| [Architecture](docs/ARCHITECTURE.md) | How PlatformIO, hardware drivers, LVGL, game logic, and data fit together. |
| [Hardware and limits](docs/HARDWARE.md) | Pins, memory, storage, display, touch, networking, and board variants. |
| [Exercises](docs/EXERCISES.md) | The one-hour checklist and progressive stretch goals. |
| [Troubleshooting](docs/TROUBLESHOOTING.md) | Cable, serial, upload, display, touch, build, and WiFi failures. |
| [CYD community repository](https://github.com/witnessmenow/ESP32-Cheap-Yellow-Display) | Community setup notes, examples, pinouts, and hardware information. |
| [CYD project gallery](https://github.com/witnessmenow/ESP32-Cheap-Yellow-Display/blob/main/PROJECTS.md) | Examples of what other people have built. |
| [LVGL documentation](https://docs.lvgl.io/) | UI framework concepts and API reference. |
| [PlatformIO documentation](https://docs.platformio.org/) | Build, library, environment, upload, and serial-monitor documentation. |

## License

MIT
