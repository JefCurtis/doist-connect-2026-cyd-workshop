# Project workflows

## Choose the smallest useful version

When the user gives an idea rather than a precise edit:

1. Ask one question at a time. Ask only about missing product decisions.
2. Learn the purpose, main input, main output, and whether it needs saved or network data.
3. Propose one small version that can be built and tested during the workshop.
4. State what is postponed.
5. Wait for agreement before replacing major application code.

Do not require the user to know file names, libraries, pins, or architecture terms.

## Path 1: change Tap Quest

Keep the whole starter and make focused UI, rules, hardware-feedback, or storage changes. Build after a small group of related edits so failures remain easy to locate.

## Path 2: turn the starter into another project

Use the working workshop project as the hardware foundation. Do not start from an empty PlatformIO project.

Keep unless the new design truly needs a change:

- `platformio.ini`
- `include/lv_conf.h`
- Display and touch setup in `src/hardware/`
- RGB LED driver in `src/hardware/`
- Partial RGB565 buffering
- The verified board environment from `.cyd-device.json`

Replace or reshape the application-specific UI, rules, and data modules. Keep `main.cpp` focused on initialization and coordination. The local clone can become the user's project; creating a separate GitHub repository is optional and can happen later.

## Path 3: use ChoreQuest

ChoreQuest is a separate complete application at `https://github.com/JefCurtis/chorequest`.

1. Clone it beside the workshop repository instead of copying its source into Tap Quest.
2. From the workshop repository, install this portable skill into it:

   ```bash
   python3 scripts/install_cyd_skill.py ../chorequest
   ```

3. Open the ChoreQuest folder as the coding-agent project.
4. Read its `README.md`, `CLAUDE.md`, `platformio.ini`, and `include/secrets.h.example`.
5. Ask the user for values that cannot be inferred: Todoist token, project ID, and display name. Never echo the token.
6. For the July workshop, configure `WIFI_SSID` as `Hotelnet`, use an empty password, set `TIMEZONE_OFFSET` to `1`, and set `DST_OFFSET` to `1`.
7. Map `.cyd-device.json` to ChoreQuest's `DISPLAY_INVERTED`: `cyd2usb` means `true`, while `cyd` means `false`. Trust the environment that passed the screen test, not the number of USB sockets.
8. Build, report memory, ask before replacing Tap Quest, then verify task loading and touch.

Do not weaken ChoreQuest's Todoist certificate validation.
