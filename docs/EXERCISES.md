# Workshop exercises

The starter already works. Your job is to complete the edit, build, upload, test loop several times and learn which layer owns each change.

## Before the timer starts

- [ ] Complete every prerequisite in the main [README](../README.md)
- [ ] Open the repository in VS Code
- [ ] Connect the CYD with your verified data cable
- [ ] Confirm `pio device list` shows it
- [ ] Keep this page open

## Core hour

### 1. Upload the baseline: 8 minutes

```bash
pio run -e cyd2usb -t upload
```

Use `-e cyd` if the colors are inverted.

- [ ] Tap Quest opens
- [ ] Start responds to touch
- [ ] Green LED feedback appears after a hit
- [ ] A full round reaches the results screen

### 2. Find each layer: 7 minutes

Use [ARCHITECTURE.md](ARCHITECTURE.md) and locate:

- [ ] Platform and library configuration in `platformio.ini`
- [ ] Pin assignments in `include/config.h`
- [ ] Display and touch setup in `src/hardware/`
- [ ] Game rules in `src/game/`
- [ ] LVGL screens in `src/ui/`
- [ ] Persistent storage in `src/data/`

### 3. Make it yours: 10 minutes

In `src/ui/game_ui.cpp`:

- [ ] Rename Tap Quest
- [ ] Rewrite the start-screen instructions
- [ ] Change `COLOR_PRIMARY`
- [ ] Build, upload, and verify the visible changes

### 4. Change the rules: 10 minutes

In `include/config.h`:

- [ ] Change `ROUND_DURATION_MS`
- [ ] Change `STARTING_TARGET_SIZE`
- [ ] Change how often the target shrinks
- [ ] Build, upload, and play the new rules

Change one setting at a time if you want to see exactly what it controls.

### 5. Change hardware feedback: 10 minutes

In `src/ui/game_ui.cpp`, find the call to `statusLed::flash()` after a hit.

- [ ] Change the LED color
- [ ] Change how long it remains lit
- [ ] Build, upload, and verify the physical feedback

### 6. Add one feature: 10 minutes

Choose one:

- [ ] Award two points every fifth hit
- [ ] Stop shrinking the target at a different minimum size
- [ ] Add a different target color after ten hits
- [ ] Show a custom message for scores above a threshold
- [ ] Add a reset-high-score button using `highScoreStore::clear()`

### 7. Pick the next layer: 5 minutes

Write your project as:

> When ___ happens, the device should ___, using ___ as its data source.

Then identify the first layer you need to change:

- [ ] UI
- [ ] Game or application logic
- [ ] Hardware
- [ ] Local data
- [ ] WiFi
- [ ] API data

## Progressive tasks after the workshop

### Game improvements

- Add lives and count taps that miss the target
- Add a combo multiplier for quick hits
- Move the target automatically if it is not hit in time
- Add different target types with different point values
- Build a difficulty-selection screen
- Add a pause state

### Hardware improvements

- Use the light sensor to change difficulty or brightness
- Attach a speaker and add non-blocking sound effects
- Load target artwork from microSD
- Add a physical controller through the I2C connector

### Data improvements

- Store player initials with the local high score
- Keep the five best local scores
- Export a score log to microSD
- Add schema versioning so stored data can evolve safely

### Network stretch goals

- Add an on-device WiFi setup flow
- Fetch a daily challenge configuration from an API
- Submit scores to a shared leaderboard
- Cache a score when offline and retry later
- Add over-the-air firmware updates
- Use ESP-NOW for two-device play without normal WiFi

See [LEADERBOARD.md](LEADERBOARD.md) before starting the API-backed leaderboard.
