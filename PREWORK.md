# Prerequisites and pre-work

Complete this before the workshop. Setup and driver troubleshooting are not part of the one-hour build.

## Bring

- ESP32-2432S028R Cheap Yellow Display
- USB data cable that you have already tested
- Spare data cable if you have one
- USB adapter or hub required by your laptop
- Laptop charger
- Laptop with administrator access for driver installation
- One small project idea

Check the model printed on the back of the board. This workshop supports the 2.8-inch ILI9341 display with XPT2046 resistive touch. A similar-looking capacitive-touch or ST7789 board may require code changes.

## Install for every operating system

1. Install [Git](https://git-scm.com/downloads).
2. Install [Python 3](https://www.python.org/downloads/) for the preflight checker.
3. Install [Visual Studio Code](https://code.visualstudio.com/).
4. In VS Code, install the **PlatformIO IDE** extension.
5. Restart VS Code after PlatformIO finishes installing.
6. Open a PlatformIO terminal and verify:

```bash
git --version
python3 --version
pio --version
```

On Windows, the Python command may be `py -3` or `python` instead of `python3`.

If `pio` is not found in your normal terminal, use the PlatformIO terminal inside VS Code.

## macOS

1. Install [WhatCable](https://www.whatcable.uk/).
2. Connect the CYD with the cable you will bring.
3. In WhatCable, look under **Connected devices**.
4. Confirm it shows **USB Serial, Full Speed (12 Mbps)**.
5. Ignore the "slow USB device or charge-only cable" headline when USB Serial is listed. The CH340 is intentionally a low-bandwidth serial device.
6. Run `pio device list` and confirm a port similar to `/dev/cu.usbserial-10` appears.
7. If no USB serial port appears, install the [CH340 driver](https://learn.sparkfun.com/tutorials/how-to-install-ch340-drivers/all), restart, and test again.

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
