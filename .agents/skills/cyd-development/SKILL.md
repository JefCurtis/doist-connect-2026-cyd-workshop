---
name: cyd-development
description: Builds, reshapes, flashes, and debugs projects for the ESP32-2432S028R CYD, including Tap Quest, new touchscreen ideas, and ChoreQuest. Use after setup when the user requests a firmware change, describes a project idea, asks what to build next, wants ChoreQuest, or reports a build, upload, display, touch, memory, WiFi, or API problem.
compatibility: Requires PlatformIO and an ESP32-2432S028R with ILI9341-compatible display and XPT2046 resistive touch.
---

# CYD development

Be the hardware and firmware expert. Let the user describe outcomes in plain language instead of asking them to choose files, pins, drivers, or libraries.

## Start every task

1. Find the project root and read `AGENTS.md`, `CLAUDE.md`, and `README.md` when present.
2. Read `platformio.ini`, the project's main configuration header, and `.cyd-device.json` when present.
3. For this workshop repository, also read `docs/ARCHITECTURE.md` and `docs/HARDWARE.md`.
4. Read [hardware-profile.md](references/hardware-profile.md) for board constraints and [layer-checklist.md](references/layer-checklist.md) when a change crosses layers.
5. Classify the request as hardware, UI, application logic, local data, network, or API data.
6. When diagnosing setup or upload problems in the workshop repository, read `docs/TROUBLESHOOTING.md` and run `python3 scripts/doctor.py`.

Treat a saved serial port as a hint because ports can change. Confirm the current port with `pio device list --json-output` before uploading.

## Turn ideas into a small project

When the user gives an idea instead of a precise edit, read [project-workflows.md](references/project-workflows.md).

- Ask one question at a time and only about missing product decisions.
- Propose the smallest useful version that can be built and tested during the workshop.
- Explain what will be postponed.
- Wait for agreement before replacing major application code.
- Build on the tested Tap Quest hardware foundation instead of creating an empty PlatformIO project.

## Work within the layers

- Keep hardware and pins in the project's hardware layer and configuration.
- Keep LVGL screens and events in the UI layer.
- Keep application rules independent of LVGL.
- Keep preferences, files, and API models in the data layer.
- Keep WiFi and HTTP lifecycle in a network layer.
- Keep the main file focused on setup and coordination.

Do not solve a missing serial port in application code. Do not put application rules in a display driver or blocking network calls in an LVGL callback.

## Protect the device

- Preserve partial RGB565 buffering unless RAM use is calculated and measured.
- Assume no PSRAM and about 320 KB of application RAM.
- Keep touch controls about 30 to 44 pixels or larger.
- Preserve a useful offline path when adding WiFi.
- Never commit credentials or print them to chat or serial logs.
- For network work, read [network-safety.md](references/network-safety.md). Never disable certificate verification to make an authenticated request work.
- Use the board environment or inversion setting recorded by the actual screen test, not the number of USB sockets alone.

## Build, upload, and verify

1. Build with the target project's PlatformIO environment.
2. Report RAM and flash from the build summary.
3. Ask before uploading because it replaces the current firmware.
4. Use the current detected serial port rather than assuming one.
5. After upload, ask the user to verify the changed screen, touch behavior, and relevant hardware.
6. Report files and layers changed, build result, memory use, hardware results, and remaining assumptions.

Do not claim hardware success from a build alone.
