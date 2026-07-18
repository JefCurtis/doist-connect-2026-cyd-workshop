# AI-guided pre-work instructions

Use the instructions below with an AI coding agent that can read this repository and run terminal commands.

```text
Prepare this macOS, Windows, or Linux laptop and attached CYD for the workshop. Upload only the Hello CYD test, not Tap Quest.

Rules:
- Read the README prerequisites, docs/DEVICE_COMPATIBILITY.md, docs/HARDWARE.md, and platformio.ini before acting.
- Work one step at a time.
- Check before installing anything. Install only what is missing.
- Ask before making a system-level change or installing software.
- After each step, report the result in one plain-English sentence.
- Do not paste successful command output. Summarize it in that one sentence.
- Do not use jargon without explaining it.
- Ask before uploading the Hello test. Never upload the Tap Quest `cyd` or `cyd2usb` environment during setup.

Steps:
1. Identify the operating system and available package manager.
2. Confirm the CYD is attached with a USB cable.
3. Check for Git, Python 3, and PlatformIO.
4. Help install only missing tools in that order.
5. Run `pio device list` and identify the CYD serial port.
6. Ask for the back label or product specification only for the display and touch details that USB cannot identify.
7. Follow docs/DEVICE_COMPATIBILITY.md and choose `hello-cyd` or `hello-cyd2usb`.
8. Run `python3 scripts/doctor.py --build`, adding `--environment hello-cyd` for an original panel and using the correct Python command for the operating system. This queries the attached ESP32 and flash and compiles the Hello test without uploading.
9. If the build fails, fix the setup problem and rerun it. Do not change firmware behavior merely to make setup pass.
10. Ask permission, then upload only the matching Hello environment.
11. Ask the attendee to confirm the screen says "Hello, CYD!" and changes to "Touch works!" when tapped.

Finish with exactly this short format, using one sentence per line:
Device: [Compatible, supported variant, not compatible, or unknown, with reason.]
Connection: [Whether the laptop sees the CYD serial port.]
Tools: [Whether Git, Python 3, and PlatformIO are ready.]
Build: [Whether the Hello firmware compiled and uploaded, including RAM and flash percentages.]
Ready: [Whether the screen and touch tests passed, and the workshop is next.]
```

## Important limitation

An agent cannot identify every display or touch controller from the USB serial connection. It must use the product specifications or model label to choose a Hello environment. The Hello screen and tap provide the final display and touch test before the workshop.
