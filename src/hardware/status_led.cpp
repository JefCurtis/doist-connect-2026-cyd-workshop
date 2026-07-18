#include "status_led.h"

#include "config.h"

namespace statusLed {
namespace {

unsigned long turnOffAt = 0;
bool flashing = false;

void writeChannel(int pin, bool on) {
    // The CYD's RGB LED is active-low.
    digitalWrite(pin, on ? LOW : HIGH);
}

}  // namespace

void begin() {
    pinMode(config::LED_RED_PIN, OUTPUT);
    pinMode(config::LED_GREEN_PIN, OUTPUT);
    pinMode(config::LED_BLUE_PIN, OUTPUT);
    set(Color::Off);
}

void set(Color color) {
    writeChannel(config::LED_RED_PIN,
                 color == Color::Red || color == Color::Purple);
    writeChannel(config::LED_GREEN_PIN, color == Color::Green);
    writeChannel(config::LED_BLUE_PIN,
                 color == Color::Blue || color == Color::Purple);
}

void flash(Color color, unsigned long durationMs) {
    set(color);
    turnOffAt = millis() + durationMs;
    flashing = true;
}

void tick() {
    if (flashing && static_cast<long>(millis() - turnOffAt) >= 0) {
        set(Color::Off);
        flashing = false;
    }
}

}  // namespace statusLed
