---
name: cyd-workshop-init
description: Prepares a Mac, Windows, or Linux laptop and attached ESP32-2432S028R CYD for the workshop. Use before prerequisites or when the user asks to initialize, set up, check, or prepare a CYD workshop device.
compatibility: Requires this repository, a USB-connected CYD, admin access, and an AI agent that can run terminal commands.
---

# CYD workshop setup

Prepare the attendee for the workshop by installing the small Hello CYD test. Do not upload Tap Quest.

## Rules

- Read the prerequisites in `../../../README.md`, plus `../../../docs/DEVICE_COMPATIBILITY.md` and `../../../platformio.ini`, first.
- Detect whether the laptop runs macOS, Windows, or Linux and adapt commands accordingly.
- Run every safe, read-only check continuously without asking the user to continue between steps.
- Pause only when software or a system change needs approval, the Hello upload needs approval, or the attendee must confirm the screen and touch result.
- Check before installing. Install only what is missing.
- Do not narrate successful commands or paste their output. At every pause and at completion, show all five status lines defined below, using Pending or Blocked where necessary.
- Ask before uploading the Hello test firmware.
- Never upload the Tap Quest `cyd` or `cyd2usb` environment during setup.
- Prefer `pio device list --json-output` for device detection after PlatformIO is available.
- After the screen and touch pass, save the verified non-secret device details in `.cyd-device.json`. This file is gitignored and helps later agent sessions choose the right build.
- On macOS, do not use `system_profiler SPUSBDataType` as the deciding check. CH340 devices may be absent there while a working `/dev/cu.usbserial*` port exists.

## Workflow

1. Identify whether the laptop runs macOS, Windows, or Linux.
2. Check Git, Python 3, and PlatformIO.
3. Help install missing tools in that order.
4. Run `pio device list --json-output` and identify the CH340 serial port.
5. On macOS, also accept `/dev/cu.usbserial*` or `/dev/cu.wchusbserial*` as proof that the CYD is attached. If `system_profiler` disagrees, trust the serial port and PlatformIO.
6. Treat a detected CH340 serial port, ESP32 processor, and 4 MB flash as likely compatible. Do not block the build on a hidden model label or unknown display variant.
7. Run the cross-platform check and default Hello build immediately:

```bash
python3 scripts/doctor.py --build
```

Use `py -3` or `python` on Windows when needed. The default `hello-cyd2usb` build is safe on either board type and only differs by color inversion.

8. Use visible USB sockets only as an optional variant hint. If asking, say: "How many physical USB sockets can you see? Count both USB-C and Micro-USB." Two sockets, normally one of each type, suggest `hello-cyd2usb`; one Micro-USB socket suggests `hello-cyd`. Never leave Build pending while waiting for this answer.
9. Ask permission, then upload `hello-cyd2usb` by default or `hello-cyd` when the attendee has already confirmed one Micro-USB socket.
10. Ask the attendee to confirm the screen says "Hello, CYD!" and changes to "Touch works!" when tapped. If only the colors are inverted, upload the other Hello environment and test again. A blank or garbled display or failed touch test indicates a different hardware variant that needs code changes.
11. Follow `../../../docs/DEVICE_COMPATIBILITY.md` and classify the device from the actual Hello screen and touch result.
12. Create or update `.cyd-device.json` with this shape, using the environment and port that actually passed. Do not put credentials or WiFi settings in it:

```json
{
  "environment": "cyd2usb",
  "hello_environment": "hello-cyd2usb",
  "serial_port": "/dev/cu.usbserial-10",
  "chip": "ESP32",
  "flash_mb": 4,
  "display": "verified",
  "touch": "verified"
}
```

Use `cyd` and `hello-cyd` when those were the passing environments. Windows and Linux ports should keep their native format.

13. Return exactly five one-sentence lines. Never return only the result of the most recent step:

```text
Device: [Pass after the Hello test, Likely before it, or Blocked after a failed test, plus the detected details.]
Connection: [Pass, Pending, or Blocked, plus whether the laptop sees the CYD serial port.]
Tools: [Pass, Pending, or Blocked, plus Git, Python 3, and PlatformIO status.]
Build: [Pass, Pending, or Blocked, plus whether the Hello firmware compiled and uploaded.]
Ready: [Yes or no, plus the single next action.]
```

If the workflow must pause, complete every other safe check first and then show all five lines before asking one clear question.

For firmware changes after setup, use the separate `cyd-development` skill.
