#include "display_touch.h"

#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>
#include <lvgl.h>

#include "config.h"

#ifndef CYD_INVERT_DISPLAY
#define CYD_INVERT_DISPLAY 0
#endif

namespace {

SPIClass touchSpi(HSPI);
XPT2046_Touchscreen touch(config::TOUCH_CS, config::TOUCH_IRQ);
TFT_eSPI display = TFT_eSPI();

// A full RGB565 framebuffer would use 153,600 bytes. This 20-row partial
// buffer uses 12,800 bytes, leaving RAM for LVGL, game state, and WiFi later.
uint8_t displayBuffer[config::SCREEN_WIDTH * config::DISPLAY_BUFFER_ROWS * 2];

void flushDisplay(lv_display_t* lvDisplay, const lv_area_t* area, uint8_t* pixels) {
    const uint32_t width = area->x2 - area->x1 + 1;
    const uint32_t height = area->y2 - area->y1 + 1;

    display.startWrite();
    display.setAddrWindow(area->x1, area->y1, width, height);
    display.pushColors(reinterpret_cast<uint16_t*>(pixels), width * height, true);
    display.endWrite();

    lv_display_flush_ready(lvDisplay);
}

void readTouch(lv_indev_t*, lv_indev_data_t* data) {
    if (!touch.touched()) {
        data->state = LV_INDEV_STATE_RELEASED;
        return;
    }

    const TS_Point point = touch.getPoint();
    data->point.x = constrain(map(point.x, 200, 3800, 0, config::SCREEN_WIDTH),
                              0, config::SCREEN_WIDTH - 1);
    data->point.y = constrain(map(point.y, 200, 3800, 0, config::SCREEN_HEIGHT),
                              0, config::SCREEN_HEIGHT - 1);
    data->state = LV_INDEV_STATE_PRESSED;
}

}  // namespace

void initDisplayAndTouch() {
    pinMode(config::BACKLIGHT_PIN, OUTPUT);
    digitalWrite(config::BACKLIGHT_PIN, HIGH);

    display.init();
    display.setRotation(1);
    display.invertDisplay(CYD_INVERT_DISPLAY == 1);
    display.fillScreen(TFT_BLACK);

    // The touchscreen has its own SPI controller and pin set.
    touchSpi.begin(config::TOUCH_CLK, config::TOUCH_MISO,
                   config::TOUCH_MOSI, config::TOUCH_CS);
    touch.begin(touchSpi);
    touch.setRotation(1);
}

void initLvgl() {
    lv_init();
    lv_tick_set_cb([]() -> uint32_t { return millis(); });

    lv_display_t* lvDisplay = lv_display_create(config::SCREEN_WIDTH,
                                                 config::SCREEN_HEIGHT);
    lv_display_set_color_format(lvDisplay, LV_COLOR_FORMAT_RGB565);
    lv_display_set_buffers(lvDisplay, displayBuffer, nullptr,
                           sizeof(displayBuffer), LV_DISPLAY_RENDER_MODE_PARTIAL);
    lv_display_set_flush_cb(lvDisplay, flushDisplay);

    lv_indev_t* input = lv_indev_create();
    lv_indev_set_type(input, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(input, readTouch);
}
