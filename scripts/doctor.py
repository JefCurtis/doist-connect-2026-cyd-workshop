#!/usr/bin/env python3
"""Cross-platform preflight checks for the CYD workshop."""

from __future__ import annotations

import argparse
import json
from pathlib import Path
import shutil
import subprocess
import sys

CYD_USB_IDS = ("1A86:7523", "1A86:5523")
ROOT = Path(__file__).resolve().parents[1]


def run(command: list[str], timeout: int = 30) -> subprocess.CompletedProcess[str]:
    return subprocess.run(
        command,
        cwd=ROOT,
        capture_output=True,
        text=True,
        timeout=timeout,
        check=False,
    )


def result(ok: bool, label: str, detail: str) -> bool:
    icon = "PASS" if ok else "FAIL"
    print(f"[{icon}] {label}: {detail}")
    return ok


def check_command(name: str) -> bool:
    path = shutil.which(name)
    if not path:
        return result(False, name, "not found on PATH")
    completed = run([name, "--version"])
    detail = (completed.stdout or completed.stderr).strip().splitlines()[0]
    return result(completed.returncode == 0, name, detail)


def check_platformio_project() -> bool:
    path = ROOT / "platformio.ini"
    return result(path.exists(), "PlatformIO project", str(path))


def check_device() -> tuple[bool, str | None]:
    completed = run(["pio", "device", "list", "--json-output"])
    if completed.returncode != 0:
        detail = (completed.stderr or completed.stdout).strip()
        result(False, "CYD serial device", detail or "device scan failed")
        return False, None

    try:
        devices = json.loads(completed.stdout)
    except json.JSONDecodeError:
        result(False, "CYD serial device", "PlatformIO returned invalid JSON")
        return False, None

    matches = []
    for device in devices:
        text = f"{device.get('description', '')} {device.get('hwid', '')}".upper()
        if "USB SERIAL" in text or any(usb_id in text for usb_id in CYD_USB_IDS):
            matches.append(device.get("port", "unknown port"))

    if not matches:
        visible = ", ".join(device.get("port", "unknown") for device in devices)
        result(
            False,
            "CYD serial device",
            f"no CH340 USB serial device found; visible ports: {visible or 'none'}",
        )
        return False, None

    result(True, "CYD serial device", ", ".join(matches))
    return True, matches[0]


def check_hardware_identity(port: str) -> bool:
    info = run(["pio", "system", "info", "--json-output"])
    if info.returncode != 0:
        return result(False, "ESP32 hardware", "could not read PlatformIO paths")

    try:
        values = json.loads(info.stdout)
        core_dir = Path(values["core_dir"]["value"])
        python_exe = values["python_exe"]["value"]
    except (json.JSONDecodeError, KeyError, TypeError):
        return result(False, "ESP32 hardware", "PlatformIO returned incomplete system information")

    esptool = core_dir / "packages" / "tool-esptoolpy" / "esptool.py"
    if not esptool.exists():
        return result(False, "ESP32 hardware", "esptool is missing; run the build first")

    completed = run([python_exe, str(esptool), "--port", port, "flash_id"], timeout=60)
    output = completed.stdout + completed.stderr
    if completed.returncode != 0:
        return result(False, "ESP32 hardware", "could not query the attached board")

    chip_line = next((line.strip() for line in output.splitlines() if line.startswith("Chip is ")), "")
    flash_line = next((line.strip() for line in output.splitlines() if line.startswith("Detected flash size:")), "")
    chip_ok = "ESP32" in chip_line
    flash_ok = flash_line.endswith("4MB")
    detail = f"{chip_line or 'chip unknown'}; {flash_line or 'flash size unknown'}"
    return result(chip_ok and flash_ok, "ESP32 hardware", detail)


def check_build(environment: str) -> bool:
    print(f"\nBuilding PlatformIO environment: {environment}")
    completed = run(["pio", "run", "-e", environment], timeout=300)
    output = completed.stdout + completed.stderr
    summary = [
        line.strip()
        for line in output.splitlines()
        if line.strip().startswith(("RAM:", "Flash:"))
    ]
    detail = "; ".join(summary) if summary else "build completed"
    if completed.returncode != 0:
        print(output)
        detail = "build failed; see output above"
    return result(completed.returncode == 0, "Firmware build", detail)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--build",
        action="store_true",
        help="also compile firmware and download missing dependencies",
    )
    parser.add_argument(
        "--environment",
        choices=("hello-cyd", "hello-cyd2usb", "cyd", "cyd2usb"),
        default="hello-cyd2usb",
        help="PlatformIO environment to compile (default: hello-cyd2usb)",
    )
    args = parser.parse_args()

    print("CYD workshop preflight\n")
    checks = [
        check_command("git"),
        check_command("pio"),
        check_platformio_project(),
    ]

    device_ok = False
    device_port = None
    if checks[1]:
        device_ok, device_port = check_device()
        checks.append(device_ok)
    if args.build and checks[1] and checks[2]:
        build_ok = check_build(args.environment)
        checks.append(build_ok)
        if build_ok and device_ok and device_port:
            checks.append(check_hardware_identity(device_port))
            print("[INFO] Display and touch: verified after uploading and tapping the Hello CYD test")

    print()
    if all(checks):
        print("All requested checks passed.")
        return 0

    print("One or more checks failed. Read the README prerequisites and docs/TROUBLESHOOTING.md.")
    return 1


if __name__ == "__main__":
    sys.exit(main())
