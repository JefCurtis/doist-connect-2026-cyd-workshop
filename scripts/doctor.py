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


def check_device() -> bool:
    completed = run(["pio", "device", "list", "--json-output"])
    if completed.returncode != 0:
        detail = (completed.stderr or completed.stdout).strip()
        return result(False, "CYD serial device", detail or "device scan failed")

    try:
        devices = json.loads(completed.stdout)
    except json.JSONDecodeError:
        return result(False, "CYD serial device", "PlatformIO returned invalid JSON")

    matches = []
    for device in devices:
        text = f"{device.get('description', '')} {device.get('hwid', '')}".upper()
        if "USB SERIAL" in text or any(usb_id in text for usb_id in CYD_USB_IDS):
            matches.append(device.get("port", "unknown port"))

    if not matches:
        visible = ", ".join(device.get("port", "unknown") for device in devices)
        return result(
            False,
            "CYD serial device",
            f"no CH340 USB serial device found; visible ports: {visible or 'none'}",
        )

    return result(True, "CYD serial device", ", ".join(matches))


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
        choices=("cyd", "cyd2usb"),
        default="cyd2usb",
        help="PlatformIO environment to compile (default: cyd2usb)",
    )
    args = parser.parse_args()

    print("CYD workshop preflight\n")
    checks = [
        check_command("git"),
        check_command("pio"),
        check_platformio_project(),
    ]

    if checks[1]:
        checks.append(check_device())
    if args.build and checks[1] and checks[2]:
        checks.append(check_build(args.environment))

    print()
    if all(checks):
        print("All requested checks passed.")
        return 0

    print("One or more checks failed. Read PREWORK.md and docs/TROUBLESHOOTING.md.")
    return 1


if __name__ == "__main__":
    sys.exit(main())
