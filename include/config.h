#pragma once

#include <Arduino.h>

namespace config {

constexpr int SCREEN_WIDTH = 320;
constexpr int SCREEN_HEIGHT = 240;
constexpr int HUD_HEIGHT = 42;
constexpr int DISPLAY_BUFFER_ROWS = 20;

constexpr int TOUCH_CS = 33;
constexpr int TOUCH_IRQ = 36;
constexpr int TOUCH_MOSI = 32;
constexpr int TOUCH_MISO = 39;
constexpr int TOUCH_CLK = 25;

constexpr int BACKLIGHT_PIN = 21;
constexpr int LED_RED_PIN = 4;
constexpr int LED_GREEN_PIN = 16;
constexpr int LED_BLUE_PIN = 17;
constexpr int LIGHT_SENSOR_PIN = 34;

// Change these during the workshop to alter the game.
constexpr unsigned long ROUND_DURATION_MS = 20000;
constexpr int STARTING_TARGET_SIZE = 58;
constexpr int MINIMUM_TARGET_SIZE = 30;
constexpr int SHRINK_EVERY_HITS = 3;
constexpr int SHRINK_BY_PIXELS = 4;
constexpr int PLAYFIELD_MARGIN = 6;

}  // namespace config
