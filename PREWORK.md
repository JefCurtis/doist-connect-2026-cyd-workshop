# Prerequisites and pre-work

Complete this before the workshop. Setup and driver troubleshooting are not part of the one-hour build.

## Bring

- A compatible Cheap Yellow Display, or arrange to pair with someone bringing one
- USB data cable that you have already tested
- Spare data cable if you have one
- USB adapter or hub required by your laptop
- Laptop charger
- Laptop with administrator access for driver installation
- One small project idea, or a plan to continue with ChoreQuest

## Device and project options

### If you do not have a CYD

You can still attend. Pair with someone who has a device and work together from one laptop or take turns uploading from both laptops. Arrange your pair before the workshop if possible.

### Recommended device

The suggested board is this [ESP32 "Bruce" CYD package on AliExpress](https://www.aliexpress.com/item/1005009383089648.html). It includes the board, a clear acrylic case, touch pen, and cables.

A similar device should work if it is an **ESP32-2432S028R** with a **2.8-inch ILI9341-compatible display** and **XPT2046 resistive touch**. Check the model printed on the back. Nearly identical boards with an ST7789 display or capacitive touch may need different drivers and will not work with the workshop firmware unchanged.

### If you do not have a project idea

Finish Tap Quest with the group, then use [ChoreQuest](https://github.com/JefCurtis/chorequest) as your next project. It builds on the same PlatformIO, LVGL, display, and touch foundation, then adds WiFi, the Todoist API, recurring tasks, rewards, and more complex data handling.

## Install for every operating system

1. Install [Git](https://git-scm.com/downloads).
2. Install [Python 3](https://www.python.org/downloads/) for the preflight checker.
3. Install [Visual Studio Code](https://code.visualstudio.com/), [Cursor](https://www.cursor.com/), or another VS Code-compatible editor.
4. In the editor, install the **PlatformIO IDE** extension.
5. Restart the editor after PlatformIO finishes installing.
6. Open a PlatformIO terminal and verify:

```bash
git --version
python3 --version
pio --version
```

On Windows, the Python command may be `py -3` or `python` instead of `python3`.

If `pio` is not found in your normal terminal, use the PlatformIO terminal inside your editor. You can also use any other code editor if you install and run the PlatformIO CLI separately.

## macOS

[WhatCable](https://www.whatcable.uk/) is optional. It is a useful Mac app for identifying the capabilities of the USB cable and connection you are using. For this workshop, it can help confirm that macOS detects a data device instead of a power-only connection. PlatformIO seeing the CYD serial port is still the definitive check.

Optional WhatCable check:

1. Install WhatCable and connect the CYD with the cable you will bring.
2. Look under **Connected devices**.
3. Confirm it shows **USB Serial, Full Speed (12 Mbps)**.
4. Ignore the "slow USB device or charge-only cable" headline when USB Serial is listed. The CH340 is intentionally a low-bandwidth serial device.

Required check with or without WhatCable:

1. Run `pio device list` and confirm a port similar to `/dev/cu.usbserial-10` appears.
2. If no USB serial port appears, install the [CH340 driver](https://learn.sparkfun.com/tutorials/how-to-install-ch340-drivers/all), restart, and test again.

A charge-only cable may power the screen while providing no serial port. Power alone is not proof that the cable works.

Some dual-USB CYDs have an incorrectly wired USB-C connector and will not work with a USB-C-to-USB-C cable. Use Micro-USB, or use USB-A through an adapter.

## Windows

1. Connect the CYD.
2. Open Device Manager.
3. Look under **Ports (COM & LPT)** for a CH340 or USB Serial entry such as `COM5`.
4. If it is missing or marked with a warning, install the [CH340 driver](https://learn.sparkfun.com/tutorials/how-to-install-ch340-drivers/all).
5. Run `pio device list` and confirm the same COM port appears.

## Linux

1. Connect the CYD.
2. Run `pio device list` and look for `/dev/ttyUSB0` or a similar port.
3. If the port exists but upload reports permission denied, add your user to the serial-device group:

```bash
sudo usermod -aG dialout "$USER"
```

Some distributions use `uucp` instead of `dialout`. Log out and back in after changing group membership.

## Clone and verify the project

```bash
git clone https://github.com/JefCurtis/doist-connect-2026-cyd-workshop.git
cd doist-connect-2026-cyd-workshop
python3 scripts/doctor.py --build
```

On Windows, use `py -3 scripts/doctor.py --build` if `python3` is not available.

The first build downloads the ESP32 platform and libraries. Do it before the workshop because it can take several minutes and needs reliable internet.

## Make the first upload

Newer dual-USB board:

```bash
pio run -e cyd2usb -t upload
```

Original single-Micro-USB board:

```bash
pio run -e cyd -t upload
```

If PlatformIO chooses the wrong port, specify it:

```bash
pio run -e cyd2usb -t upload --upload-port /dev/cu.usbserial-10
```

Replace the example with your macOS, Windows, or Linux port.

## Pre-work exit criteria

Do not consider pre-work complete until all of these are true:

- [ ] `git --version` succeeds
- [ ] A Python 3 version command succeeds
- [ ] `pio --version` succeeds
- [ ] `pio device list` shows the CYD
- [ ] `python3 scripts/doctor.py --build` passes
- [ ] Firmware upload succeeds at 460800 baud
- [ ] Tap Quest appears with normal colors
- [ ] The Start game button responds to touch
- [ ] You can play a complete 20-second round
- [ ] Disconnecting and reconnecting power preserves the high score

If anything fails, use [docs/TROUBLESHOOTING.md](docs/TROUBLESHOOTING.md) before the workshop.
