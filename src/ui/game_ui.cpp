#include "game_ui.h"

#include <Arduino.h>
#include <lvgl.h>

#include "data/high_score_store.h"
#include "game/tap_game.h"
#include "hardware/status_led.h"

namespace gameUi {
namespace {

constexpr uint32_t COLOR_BACKGROUND = 0x0B0C0F;
constexpr uint32_t COLOR_SURFACE = 0x1A1C22;
constexpr uint32_t COLOR_TEXT = 0xF7F7F5;
constexpr uint32_t COLOR_MUTED = 0xB4B7C2;
constexpr uint32_t COLOR_PRIMARY = 0xA93636;
constexpr uint32_t COLOR_PRIMARY_PRESSED = 0x812727;
constexpr uint32_t COLOR_ACCENT = 0x55C5BF;

lv_obj_t* scoreLabel = nullptr;
lv_obj_t* timeLabel = nullptr;
lv_obj_t* targetButton = nullptr;
int highScore = 0;
int shownSecond = -1;
tapGame::Status shownStatus = tapGame::Status::Ready;

void styleScreen(lv_obj_t* screen) {
    lv_obj_set_style_bg_color(screen, lv_color_hex(COLOR_BACKGROUND), 0);
    lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, 0);
    lv_obj_set_style_text_color(screen, lv_color_hex(COLOR_TEXT), 0);
    lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);
}

lv_obj_t* createActionButton(lv_obj_t* parent, const char* text) {
    lv_obj_t* button = lv_btn_create(parent);
    lv_obj_set_size(button, 190, 48);
    lv_obj_set_style_bg_color(button, lv_color_hex(COLOR_PRIMARY), 0);
    lv_obj_set_style_bg_color(button, lv_color_hex(COLOR_PRIMARY_PRESSED),
                              LV_STATE_PRESSED);
    lv_obj_set_style_radius(button, 10, 0);
    lv_obj_set_style_border_width(button, 0, 0);

    lv_obj_t* label = lv_label_create(button);
    lv_label_set_text(label, text);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_16, 0);
    lv_obj_set_style_text_color(label, lv_color_hex(COLOR_TEXT), 0);
    lv_obj_center(label);
    return button;
}

void showReadyScreen();
void showPlayingScreen();
void showResultsScreen();

void startRound(lv_event_t*) {
    tapGame::startRound();
    statusLed::flash(statusLed::Color::Blue, 180);
    showPlayingScreen();
}

void hitTarget(lv_event_t*) {
    tapGame::registerHit();
    statusLed::flash(statusLed::Color::Green, 90);

    const tapGame::State& state = tapGame::state();
    lv_obj_set_size(targetButton, state.targetSize, state.targetSize);
    lv_obj_set_pos(targetButton, state.targetX, state.targetY);

    char scoreText[20];
    snprintf(scoreText, sizeof(scoreText), "Score %d", state.score);
    lv_label_set_text(scoreLabel, scoreText);
}

void addFooter(lv_obj_t* parent, const char* text) {
    lv_obj_t* footer = lv_label_create(parent);
    lv_label_set_text(footer, text);
    lv_obj_set_style_text_font(footer, &lv_font_montserrat_14, 0);
    lv_obj_set_style_text_color(footer, lv_color_hex(COLOR_MUTED), 0);
    lv_obj_align(footer, LV_ALIGN_BOTTOM_MID, 0, -8);
}

void showReadyScreen() {
    lv_obj_t* screen = lv_screen_active();
    lv_obj_clean(screen);
    styleScreen(screen);

    lv_obj_t* title = lv_label_create(screen);
    lv_label_set_text(title, "Tap Quest");
    lv_obj_set_style_text_font(title, &lv_font_montserrat_24, 0);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 30);

    lv_obj_t* description = lv_label_create(screen);
    lv_label_set_text(description, "Hit as many targets as you can\nin 20 seconds.");
    lv_obj_set_style_text_font(description, &lv_font_montserrat_16, 0);
    lv_obj_set_style_text_color(description, lv_color_hex(COLOR_MUTED), 0);
    lv_obj_set_style_text_align(description, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(description, LV_ALIGN_TOP_MID, 0, 72);

    lv_obj_t* startButton = createActionButton(screen, "Start game");
    lv_obj_align(startButton, LV_ALIGN_CENTER, 0, 35);
    lv_obj_add_event_cb(startButton, startRound, LV_EVENT_CLICKED, nullptr);

    char highScoreText[32];
    snprintf(highScoreText, sizeof(highScoreText), "High score: %d", highScore);
    addFooter(screen, highScoreText);

    shownStatus = tapGame::Status::Ready;
}

void showPlayingScreen() {
    lv_obj_t* screen = lv_screen_active();
    lv_obj_clean(screen);
    styleScreen(screen);

    lv_obj_t* hud = lv_obj_create(screen);
    lv_obj_set_size(hud, 320, 42);
    lv_obj_set_pos(hud, 0, 0);
    lv_obj_set_style_bg_color(hud, lv_color_hex(COLOR_SURFACE), 0);
    lv_obj_set_style_bg_opa(hud, LV_OPA_COVER, 0);
    lv_obj_set_style_border_width(hud, 0, 0);
    lv_obj_set_style_radius(hud, 0, 0);
    lv_obj_set_style_pad_all(hud, 0, 0);
    lv_obj_clear_flag(hud, LV_OBJ_FLAG_SCROLLABLE);

    scoreLabel = lv_label_create(hud);
    lv_label_set_text(scoreLabel, "Score 0");
    lv_obj_set_style_text_font(scoreLabel, &lv_font_montserrat_16, 0);
    lv_obj_align(scoreLabel, LV_ALIGN_LEFT_MID, 12, 0);

    timeLabel = lv_label_create(hud);
    lv_label_set_text(timeLabel, "20s");
    lv_obj_set_style_text_font(timeLabel, &lv_font_montserrat_20, 0);
    lv_obj_set_style_text_color(timeLabel, lv_color_hex(COLOR_ACCENT), 0);
    lv_obj_align(timeLabel, LV_ALIGN_RIGHT_MID, -12, 0);

    const tapGame::State& state = tapGame::state();
    targetButton = lv_btn_create(screen);
    lv_obj_set_size(targetButton, state.targetSize, state.targetSize);
    lv_obj_set_pos(targetButton, state.targetX, state.targetY);
    lv_obj_set_style_radius(targetButton, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_bg_color(targetButton, lv_color_hex(COLOR_PRIMARY), 0);
    lv_obj_set_style_bg_color(targetButton, lv_color_hex(COLOR_ACCENT),
                              LV_STATE_PRESSED);
    lv_obj_set_style_border_width(targetButton, 3, 0);
    lv_obj_set_style_border_color(targetButton, lv_color_hex(COLOR_TEXT), 0);
    lv_obj_add_event_cb(targetButton, hitTarget, LV_EVENT_CLICKED, nullptr);

    lv_obj_t* targetMark = lv_label_create(targetButton);
    lv_label_set_text(targetMark, "+1");
    lv_obj_set_style_text_font(targetMark, &lv_font_montserrat_16, 0);
    lv_obj_set_style_text_color(targetMark, lv_color_hex(COLOR_TEXT), 0);
    lv_obj_center(targetMark);

    shownSecond = tapGame::secondsRemaining();
    shownStatus = tapGame::Status::Playing;
}

void showResultsScreen() {
    const int score = tapGame::state().score;
    const bool newHighScore = score > highScore;
    if (newHighScore) {
        highScore = score;
        highScoreStore::save(highScore);
        statusLed::flash(statusLed::Color::Purple, 600);
    } else {
        statusLed::flash(statusLed::Color::Red, 250);
    }

    lv_obj_t* screen = lv_screen_active();
    lv_obj_clean(screen);
    styleScreen(screen);

    lv_obj_t* heading = lv_label_create(screen);
    lv_label_set_text(heading, newHighScore ? "New high score!" : "Time's up");
    lv_obj_set_style_text_font(heading, &lv_font_montserrat_20, 0);
    lv_obj_set_style_text_color(
        heading, lv_color_hex(newHighScore ? COLOR_ACCENT : COLOR_TEXT), 0);
    lv_obj_align(heading, LV_ALIGN_TOP_MID, 0, 30);

    lv_obj_t* result = lv_label_create(screen);
    char resultText[24];
    snprintf(resultText, sizeof(resultText), "%d hits", score);
    lv_label_set_text(result, resultText);
    lv_obj_set_style_text_font(result, &lv_font_montserrat_24, 0);
    lv_obj_align(result, LV_ALIGN_TOP_MID, 0, 72);

    lv_obj_t* replayButton = createActionButton(screen, "Play again");
    lv_obj_align(replayButton, LV_ALIGN_CENTER, 0, 30);
    lv_obj_add_event_cb(replayButton, startRound, LV_EVENT_CLICKED, nullptr);

    char highScoreText[32];
    snprintf(highScoreText, sizeof(highScoreText), "High score: %d", highScore);
    addFooter(screen, highScoreText);

    shownStatus = tapGame::Status::Finished;
}

}  // namespace

void begin() {
    lv_theme_t* theme = lv_theme_default_init(
        lv_display_get_default(), lv_color_hex(COLOR_PRIMARY),
        lv_color_hex(COLOR_ACCENT), true, &lv_font_montserrat_16);
    lv_display_set_theme(lv_display_get_default(), theme);

    highScore = highScoreStore::load();
    showReadyScreen();
}

void tick() {
    const tapGame::Status status = tapGame::state().status;

    if (status == tapGame::Status::Finished && shownStatus != status) {
        showResultsScreen();
        return;
    }

    if (status != tapGame::Status::Playing || !timeLabel) return;

    const int second = tapGame::secondsRemaining();
    if (second != shownSecond) {
        shownSecond = second;
        char timeText[12];
        snprintf(timeText, sizeof(timeText), "%ds", second);
        lv_label_set_text(timeLabel, timeText);
    }
}

}  // namespace gameUi
