#include "tap_game.h"

#include <Arduino.h>

#include "config.h"

namespace tapGame {
namespace {

State gameState;

void moveTarget() {
    const int maxX = config::SCREEN_WIDTH - gameState.targetSize -
                     config::PLAYFIELD_MARGIN;
    const int minY = config::HUD_HEIGHT + config::PLAYFIELD_MARGIN;
    const int maxY = config::SCREEN_HEIGHT - gameState.targetSize -
                     config::PLAYFIELD_MARGIN;

    gameState.targetX = random(config::PLAYFIELD_MARGIN, maxX + 1);
    gameState.targetY = random(minY, maxY + 1);
}

}  // namespace

void begin() {
    gameState = {
        Status::Ready,
        0,
        0,
        0,
        config::STARTING_TARGET_SIZE,
        0,
        0,
    };
}

void startRound() {
    gameState.status = Status::Playing;
    gameState.score = 0;
    gameState.targetSize = config::STARTING_TARGET_SIZE;
    gameState.startedAt = millis();
    gameState.endsAt = gameState.startedAt + config::ROUND_DURATION_MS;
    moveTarget();
}

void registerHit() {
    if (gameState.status != Status::Playing) return;

    gameState.score++;

    if (gameState.score % config::SHRINK_EVERY_HITS == 0) {
        gameState.targetSize = max(config::MINIMUM_TARGET_SIZE,
                                   gameState.targetSize - config::SHRINK_BY_PIXELS);
    }

    moveTarget();
}

void tick() {
    if (gameState.status == Status::Playing &&
        static_cast<long>(millis() - gameState.endsAt) >= 0) {
        gameState.status = Status::Finished;
    }
}

const State& state() {
    return gameState;
}

int secondsRemaining() {
    if (gameState.status != Status::Playing) return 0;

    const long remaining = static_cast<long>(gameState.endsAt - millis());
    if (remaining <= 0) return 0;
    return (remaining + 999) / 1000;
}

}  // namespace tapGame
