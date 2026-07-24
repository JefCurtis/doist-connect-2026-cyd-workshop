# Doist Connect Denmark 2026: CYD Workshop

Build, flash, and change a touchscreen game on a Cheap Yellow Display in one hour.

The starter project is **Tap Quest**, a small whack-a-mole-style game. A target moves around the screen, gets smaller as your score rises, flashes the onboard RGB LED, and saves the high score on the device. It works without WiFi so the workshop does not depend on hotel networking.

## What you need

- [ESP32 "Bruce" Cheap Yellow Display](https://www.aliexpress.com/item/1005009383089648.html)
- USB data cable. A charge-only cable may power the screen but cannot connect the device; the setup skill will test this. Mac users can optionally use [WhatCable](https://www.whatcable.uk/) when troubleshooting.
- Laptop with admin access
- An AI coding agent that can read this repository and run terminal commands, such as Claude Code, Codex, or Gemini

### 1. Clone the repository

A simple place to keep the project is your **Documents** folder:

```bash
cd ~/Documents
git clone https://github.com/JefCurtis/cyd.git
cd cyd
```

On Windows PowerShell, use `cd $HOME\Documents` for the first command.

If Git is unfamiliar, ask your AI agent:

```text
Clone https://github.com/JefCurtis/cyd into my Documents folder. When it finishes, tell me how to open the cyd folder as my project.
```

### 2. Connect and open the project

1. Plug the CYD into your laptop with the USB cable.
2. Open the repository folder in Cursor, VS Code, or another AI coding tool.
3. Start an AI agent that can read files and run terminal commands in this folder.

### 3. Run the setup skill

```text
/cyd-init
```

The skill checks before changing anything and asks before installing software or flashing the CYD. It helps install Git, Python 3, and PlatformIO when missing. The first build also downloads the ESP32 compiler and project libraries. It then looks for a connected ESP32 with 4 MB flash, a working screen, and working touch.

If your agent does not recognize `/cyd-init`, tell it:

```text
Read and follow .agents/skills/cyd-init/SKILL.md
```

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

## Choose what to build

Once Tap Quest works, continue with the guided exercises or turn the tested starter into your own project. You can describe the result without knowing source files, pins, or libraries.

| Path | Tell your AI agent |
|---|---|
| Change Tap Quest | `Make each round 20 seconds and change the target to blue.` |
| Build your own idea | `Help me turn this into a two-player scorekeeper. Start with the smallest useful version.` |
| Explore ChoreQuest | `Set up ChoreQuest beside this project for my attached CYD.` |
| Help me choose | `I finished Tap Quest. Ask me one question at a time and help me choose what to build next.` |

The `cyd-development` skill gives the agent the tested hardware constraints, project layers, Hotelnet details, security rules, and build and upload workflow. Read [Build something after Tap Quest](docs/NEXT_PROJECT.md) for more prompts.

If you ask for help choosing, the agent asks what kind of experience you want, whether it should use WiFi or built-in hardware, and how much time you have. It then suggests a few small first versions using the project examples below, the curated ideas in `docs/NEXT_PROJECT.md`, and its general knowledge. You choose one before it changes the code.

## Projects to try

Find more examples in the [Cheap Yellow Display project gallery](https://github.com/witnessmenow/ESP32-Cheap-Yellow-Display/blob/main/PROJECTS.md).

| Project | What you'll build |
|---|---|
| [Aura Weather Display](https://github.com/Surrey-Homeware/Aura) | A polished little weather companion with current conditions and a forecast from Open-Meteo. |
| [ChoreQuest](https://github.com/JefCurtis/chorequest) | A friendly Todoist task tracker with recurring chores, rewards, and satisfying check-offs. |
| [CYD Stream Deck](https://github.com/gahingwoo/cyd-stream-deck) | A six-button Bluetooth media remote that pairs with a Mac or Windows laptop. |
| [GitHub Stats](https://github.com/ATOMNFT/ESP32-CYD-Projects/tree/main/GitHub-Stats) | A tiny desk dashboard showing stars, forks, issues, followers, and recent activity for a repository. |
| [London Underground Arrivals](https://github.com/mgaman/TFL-tube-arrivals-board-ESP32-TFT-Arduino) | A live station board showing the next trains, built from public transit data. |
| [Spotify DIY Thing](https://github.com/witnessmenow/Spotify-Diy-Thing) | A tiny now-playing screen that shows your current Spotify track and album art. |

## Open APIs to try

These APIs require no key for basic use. The agent should test the endpoint before building around it.

| API | Example project |
|---|---|
| [Open-Meteo](https://open-meteo.com/en/docs) | Local weather dashboard |
| [PokéAPI](https://pokeapi.co/) | Pokédex or guessing game |
| [Open Trivia Database](https://opentdb.com/api_config.php) | Touchscreen trivia game |
| [REST Countries](https://restcountries.com/) | Country explorer or travel quiz |
| [Open Library](https://openlibrary.org/developers/api) | Book search or reading picker |
| [Frankfurter](https://frankfurter.dev/) | Currency converter |
| [JokeAPI safe-mode endpoint](https://v2.jokeapi.dev/joke/Any?safe-mode) | Random joke button or joke-of-the-day screen |

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
| About 320 KB RAM and no PSRAM | A modern phone with 8 GB has about 25,000 times more RAM. One full CYD screen already uses nearly half of what is available, so this project renders 20 rows at a time. |
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

Use [Build something after Tap Quest](docs/NEXT_PROJECT.md) to reshape the tested starter, set up ChoreQuest, or choose another project. The progressive tasks in [docs/EXERCISES.md](docs/EXERCISES.md) include lives, combos, sound, adaptive difficulty, two-device multiplayer, over-the-air updates, and an API-backed leaderboard. The suggested leaderboard contract is in [docs/LEADERBOARD.md](docs/LEADERBOARD.md).

## Troubleshooting and references

| Resource | What it covers |
|---|---|
| [AI-guided setup prompt](docs/PREWORK_AGENT.md) | Manual fallback for agents that cannot load the setup skill. |
| [Device compatibility](docs/DEVICE_COMPATIBILITY.md) | How the attached board and Hello test determine compatibility. |
| [Command reference](docs/COMMAND_REFERENCE.md) | Plain-English explanations of build and upload commands. |
| [Architecture](docs/ARCHITECTURE.md) | How PlatformIO, hardware drivers, LVGL, game logic, and data fit together. |
| [Hardware and limits](docs/HARDWARE.md) | Pins, memory, storage, display, touch, networking, and board variants. |
| [Exercises](docs/EXERCISES.md) | The one-hour checklist and progressive stretch goals. |
| [Build something next](docs/NEXT_PROJECT.md) | Guided paths, project ideas, ChoreQuest setup, and copyable AI prompts. |
| [Troubleshooting](docs/TROUBLESHOOTING.md) | Cable, serial, upload, display, touch, build, and WiFi failures. |
| [CYD community repository](https://github.com/witnessmenow/ESP32-Cheap-Yellow-Display) | Community setup notes, examples, pinouts, and hardware information. |
| [CYD project gallery](https://github.com/witnessmenow/ESP32-Cheap-Yellow-Display/blob/main/PROJECTS.md) | Examples of what other people have built. |
| [LVGL documentation](https://docs.lvgl.io/) | UI framework concepts and API reference. |
| [PlatformIO documentation](https://docs.platformio.org/) | Build, library, environment, upload, and serial-monitor documentation. |

## License

MIT
