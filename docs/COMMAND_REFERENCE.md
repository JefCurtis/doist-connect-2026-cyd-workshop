# Manual setup and command reference

Use this if you prefer to complete setup without an AI coding agent, or if you want a detailed explanation of every command and flag.

## Check installed tools

Run these commands one at a time:

```bash
git --version
python3 --version
pio --version
```

| Command part | Plain-English meaning | Why run it |
|---|---|---|
| `git` | Start Git, the tool used to download and track the project. | Confirms the terminal can find Git. |
| `python3` | Start Python 3, which runs the preflight checker. | Confirms Python is available. |
| `pio` | Start PlatformIO. | Confirms the firmware toolchain is available. |
| `--version` | Print the installed version and exit. | Safely checks an installation without changing anything. |

On Windows, use `py -3 --version` or `python --version` when `python3` is unavailable.

## Find the connected device

```bash
pio device list
```

| Command part | Plain-English meaning |
|---|---|
| `pio` | Start PlatformIO. |
| `device` | Use its connected-device tools. |
| `list` | List serial devices visible to the computer. |

This only looks for devices. It does not upload anything. Typical ports are `/dev/cu.usbserial-10` on macOS, `COM5` on Windows, and `/dev/ttyUSB0` on Linux.

## Linux serial permission

Only use this if Linux sees the port but reports permission denied:

```bash
sudo usermod -aG dialout "$USER"
```

| Command part | Plain-English meaning |
|---|---|
| `sudo` | Run with administrator permission. |
| `usermod` | Change a Linux user account. |
| `-aG` | Add the user to an extra group without removing existing groups. |
| `dialout` | The group normally allowed to use serial devices. |
| `"$USER"` | Your current username, filled in by the shell. |

Log out and back in afterward. Some Linux distributions use `uucp` instead of `dialout`.

## Clone the project

```bash
git clone https://github.com/JefCurtis/doist-connect-2026-cyd-workshop.git
cd doist-connect-2026-cyd-workshop
```

| Command part | Plain-English meaning |
|---|---|
| `git clone` | Download a working copy of the repository. |
| The GitHub URL | Identify which repository to download. |
| `cd` | Change the terminal's current folder. |
| Project folder name | Enter the folder Git created. |

## Check setup and compile

```bash
python3 scripts/doctor.py --build
```

| Command part | Plain-English meaning |
|---|---|
| `python3` | Start Python 3. |
| `scripts/doctor.py` | Check Git, PlatformIO, project files, and the CYD serial port. |
| `--build` | Also compile the default `hello-cyd2usb` test firmware after the basic checks pass. |

This does not upload firmware or change the CYD.

## Upload the Hello test during setup

Newer dual-USB board:

```bash
pio run -e hello-cyd2usb -t upload
```

Original single-Micro-USB board:

```bash
pio run -e hello-cyd -t upload
```

Use this small test before the workshop. It displays "Hello, CYD!" and confirms touch when the button is tapped. It does not install Tap Quest.

## Upload Tap Quest during the workshop

Newer dual-USB board:

```bash
pio run -e cyd2usb -t upload
```

Original single-Micro-USB board:

```bash
pio run -e cyd -t upload
```

| Command part | Plain-English meaning |
|---|---|
| `pio run` | Run a PlatformIO job for this project. By itself, it compiles. |
| `-e cyd2usb` | Select the newer dual-USB display configuration. `-e` means environment. |
| `-e cyd` | Select the original display configuration. Use only one environment. |
| `-t upload` | Run the upload target after compiling. This writes firmware to the device. |

To force a specific serial port:

```bash
pio run -e cyd2usb -t upload --upload-port /dev/cu.usbserial-10
```

`--upload-port` tells PlatformIO exactly which serial device to use. Uploading replaces the firmware currently installed on the CYD, but another project can restore it later.
