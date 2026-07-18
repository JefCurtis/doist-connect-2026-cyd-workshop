#include <Arduino.h>
#include <lvgl.h>

#include "config.h"
#include "game/tap_game.h"
#include "hardware/display_touch.h"
#include "hardware/status_led.h"
#include "ui/game_ui.h"

void setup() {
    Serial.begin(115200);
    delay(100);
    Serial.println("\nTap Quest starting...");

    // The light sensor produces enough noise at boot to vary target positions.
    randomSeed(analogRead(config::LIGHT_SENSOR_PIN));

    initDisplayAndTouch();
    initLvgl();
    statusLed::begin();
    tapGame::begin();
    gameUi::begin();

    Serial.println("Ready. Tap Start game.");
}

void loop() {
    lv_timer_handler();
    tapGame::tick();
    gameUi::tick();
    statusLed::tick();
    delay(5);
}
