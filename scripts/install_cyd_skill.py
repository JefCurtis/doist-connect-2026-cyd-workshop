#!/usr/bin/env python3
"""Install the portable CYD development skill into another PlatformIO project."""

from __future__ import annotations

import argparse
from pathlib import Path
import shutil
import sys

ROOT = Path(__file__).resolve().parents[1]
SKILL_SOURCE = ROOT / ".agents" / "skills" / "cyd-development"
PROFILE_SOURCE = ROOT / ".cyd-device.json"


def ignore_local_profile(target: Path) -> None:
    exclude = target / ".git" / "info" / "exclude"
    if not exclude.parent.is_dir():
        return

    entry = ".cyd-device.json"
    existing = exclude.read_text() if exclude.exists() else ""
    if entry not in {line.strip() for line in existing.splitlines()}:
        prefix = "" if not existing or existing.endswith("\n") else "\n"
        with exclude.open("a") as file:
            file.write(f"{prefix}# Local CYD workshop device profile\n{entry}\n")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("target", type=Path, help="target project directory")
    parser.add_argument(
        "--force",
        action="store_true",
        help="replace an existing cyd-development skill in the target",
    )
    args = parser.parse_args()

    target = args.target.expanduser().resolve()
    if not target.is_dir():
        print(f"Target directory does not exist: {target}", file=sys.stderr)
        return 1
    if not (target / "platformio.ini").is_file():
        print(f"Target is not a PlatformIO project: {target}", file=sys.stderr)
        return 1

    destination = target / ".agents" / "skills" / "cyd-development"
    if destination.exists():
        if not args.force:
            print(
                f"Skill already exists: {destination}\n"
                "Run again with --force to replace only that skill folder.",
                file=sys.stderr,
            )
            return 1
        shutil.rmtree(destination)

    destination.parent.mkdir(parents=True, exist_ok=True)
    shutil.copytree(SKILL_SOURCE, destination)
    print(f"Installed CYD development skill: {destination}")

    profile_destination = target / ".cyd-device.json"
    ignore_local_profile(target)
    if PROFILE_SOURCE.is_file() and not profile_destination.exists():
        shutil.copy2(PROFILE_SOURCE, profile_destination)
        print(f"Copied verified device profile: {profile_destination}")
    elif profile_destination.exists():
        print(f"Kept existing device profile: {profile_destination}")
    else:
        print("No device profile found. The agent will detect the attached CYD.")

    print(f"Next: open {target} in your coding agent and describe what you want to build.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
