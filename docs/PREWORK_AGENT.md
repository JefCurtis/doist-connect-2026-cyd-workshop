# AI-guided pre-work instructions

Use the instructions below with an AI coding agent that can read this repository and run terminal commands.

```text
Prepare this macOS, Windows, or Linux laptop and attached CYD for the workshop. Upload only the Hello CYD test, not Tap Quest.

Rules:
- Read the README prerequisites, docs/DEVICE_COMPATIBILITY.md, docs/HARDWARE.md, and platformio.ini before acting.
- Run every safe, read-only check continuously. Do not ask me to continue between normal checks.
- Pause only for installation or system-change approval, Hello upload approval, or my visual confirmation.
- Check before installing anything. Install only what is missing.
- Ask before making a system-level change or installing software.
- Prefer `pio device list --json-output` for device detection after PlatformIO is available.
- On macOS, do not treat `system_profiler SPUSBDataType` as definitive. Trust a matching `/dev/cu.usbserial*` port and PlatformIO when they detect the CYD.
- Do not narrate successful commands or paste their output.
- At every pause and at completion, show all five status lines below. Use Pending or Blocked for unfinished checks.
- Do not use jargon without explaining it.
- Ask before uploading the Hello test. Never upload the Tap Quest `cyd` or `cyd2usb` environment during setup.
- After the physical test passes, save only non-secret device details in the gitignored `.cyd-device.json` file for later agent sessions.

Steps:
1. Identify the operating system and available package manager.
2. Check for Git, Python 3, and PlatformIO.
3. Help install only missing tools in that order.
4. Run `pio device list --json-output` and identify the CYD serial port.
5. On macOS, also check `/dev/cu.usbserial*` and `/dev/cu.wchusbserial*`; accept either matching path when PlatformIO sees the same device.
6. Treat a detected CH340 serial port, ESP32 processor, and 4 MB flash as likely compatible. Do not block the build on a hidden model label or unknown display variant.
7. Run `python3 scripts/doctor.py --build`, using the correct Python command for the operating system. This queries the attached board and compiles the default `hello-cyd2usb` test without uploading.
8. If useful, ask: "How many physical USB sockets can you see? Count both USB-C and Micro-USB." Two sockets, normally one of each type, suggest `hello-cyd2usb`; one Micro-USB socket suggests `hello-cyd`. Never leave Build pending for this answer.
9. If the build fails, fix the setup problem and rerun it. Do not change firmware behavior merely to make setup pass.
10. Ask permission, then upload `hello-cyd2usb` by default or `hello-cyd` when one Micro-USB socket was already confirmed.
11. Ask the attendee to confirm the screen says "Hello, CYD!" and changes to "Touch works!" when tapped. If only the colors are inverted, upload the other Hello environment and test again.
12. Follow docs/DEVICE_COMPATIBILITY.md and classify the device from the actual screen and touch result.
13. Save `.cyd-device.json` with the passing Tap Quest environment (`cyd` or `cyd2usb`), passing Hello environment, current serial port, ESP32 chip, 4 MB flash, and verified display and touch results. Do not include WiFi or credentials.

At every pause and at completion, use exactly this short format with one sentence per line:
Device: [Pass after the Hello test, Likely before it, or Blocked after a failed test, plus the reason.]
Connection: [Pass, Pending, or Blocked, plus serial-port status.]
Tools: [Pass, Pending, or Blocked, plus Git, Python 3, and PlatformIO status.]
Build: [Pass, Pending, or Blocked, plus Hello build and upload status and memory percentages when known.]
Ready: [Yes or no, plus the single next action.]

When setup succeeds, use this exact final line:
Ready: Yes. Tell your agent: "Replace the Hello test with Tap Quest. Choose the correct board configuration, build it, ask before uploading, and verify that the game starts."

If you must pause, complete every other safe check first, show all five lines, and then ask one clear question.
```

## Important limitation

An agent cannot identify every display or touch controller from USB. It should build and try the safe default Hello environment rather than blocking on a hidden model label. The Hello screen and tap provide the final display and touch test before the workshop.
