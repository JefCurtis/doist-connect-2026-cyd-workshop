#pragma once

#include <Arduino.h>

namespace statusLed {

enum class Color {
    Off,
    Red,
    Green,
    Blue,
    Purple,
};

void begin();
void set(Color color);
void flash(Color color, unsigned long durationMs = 100);
void tick();

}  // namespace statusLed
