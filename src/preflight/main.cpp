#include <Arduino.h>
#include <lvgl.h>

#include "hardware/display_touch.h"
#include "hardware/status_led.h"

namespace {

constexpr uint32_t BACKGROUND = 0x0B0C0F;
constexpr uint32_t TEXT = 0xF7F7F5;
constexpr uint32_t MUTED = 0xB4B7C2;
constexpr uint32_t PINK = 0xA93636;
constexpr uint32_t TEAL = 0x55C5BF;

lv_obj_t* titleLabel = nullptr;
lv_obj_t* detailLabel = nullptr;
lv_obj_t* testButton = nullptr;

void touchConfirmed(lv_event_t*) {
    lv_label_set_text(titleLabel, "Touch works!");
    lv_label_set_text(detailLabel, "Your CYD is ready for Denmark.");
    lv_obj_set_style_bg_color(testButton, lv_color_hex(TEAL), 0);

    lv_obj_t* buttonLabel = lv_obj_get_child(testButton, 0);
    lv_label_set_text(buttonLabel, LV_SYMBOL_OK " Ready");
    statusLed::flash(statusLed::Color::Green, 800);
    Serial.println("Touch test passed.");
}

void buildHelloScreen() {
    lv_obj_t* screen = lv_screen_active();
    lv_obj_set_style_bg_color(screen, lv_color_hex(BACKGROUND), 0);
    lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, 0);
    lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t* eventLabel = lv_label_create(screen);
    lv_label_set_text(eventLabel, "DOIST CONNECT 2026");
    lv_obj_set_style_text_font(eventLabel, &lv_font_montserrat_14, 0);
    lv_obj_set_style_text_color(eventLabel, lv_color_hex(TEAL), 0);
    lv_obj_align(eventLabel, LV_ALIGN_TOP_MID, 0, 24);

    titleLabel = lv_label_create(screen);
    lv_label_set_text(titleLabel, "Hello, CYD!");
    lv_obj_set_style_text_font(titleLabel, &lv_font_montserrat_24, 0);
    lv_obj_set_style_text_color(titleLabel, lv_color_hex(TEXT), 0);
    lv_obj_align(titleLabel, LV_ALIGN_TOP_MID, 0, 62);

    detailLabel = lv_label_create(screen);
    lv_label_set_text(detailLabel, "Your screen is working.\nNow test the touchscreen.");
    lv_obj_set_style_text_font(detailLabel, &lv_font_montserrat_16, 0);
    lv_obj_set_style_text_color(detailLabel, lv_color_hex(MUTED), 0);
    lv_obj_set_style_text_align(detailLabel, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(detailLabel, LV_ALIGN_TOP_MID, 0, 102);

    testButton = lv_btn_create(screen);
    lv_obj_set_size(testButton, 180, 48);
    lv_obj_align(testButton, LV_ALIGN_BOTTOM_MID, 0, -24);
    lv_obj_set_style_bg_color(testButton, lv_color_hex(PINK), 0);
    lv_obj_set_style_radius(testButton, 10, 0);
    lv_obj_set_style_border_width(testButton, 0, 0);
    lv_obj_add_event_cb(testButton, touchConfirmed, LV_EVENT_CLICKED, nullptr);

    lv_obj_t* buttonLabel = lv_label_create(testButton);
    lv_label_set_text(buttonLabel, "Tap me");
    lv_obj_set_style_text_font(buttonLabel, &lv_font_montserrat_16, 0);
    lv_obj_set_style_text_color(buttonLabel, lv_color_hex(TEXT), 0);
    lv_obj_center(buttonLabel);
}

}  // namespace

void setup() {
    Serial.begin(115200);
    delay(100);
    Serial.println("\nHello CYD preflight starting...");

    initDisplayAndTouch();
    initLvgl();
    statusLed::begin();

    lv_theme_t* theme = lv_theme_default_init(
        lv_display_get_default(), lv_color_hex(PINK), lv_color_hex(TEAL),
        true, &lv_font_montserrat_16);
    lv_display_set_theme(lv_display_get_default(), theme);

    buildHelloScreen();
    Serial.println("Screen test ready. Tap the button.");
}

void loop() {
    lv_timer_handler();
    statusLed::tick();
    delay(5);
}
