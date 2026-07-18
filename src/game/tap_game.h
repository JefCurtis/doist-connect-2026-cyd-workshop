#pragma once

namespace tapGame {

enum class Status {
    Ready,
    Playing,
    Finished,
};

struct State {
    Status status;
    int score;
    int targetX;
    int targetY;
    int targetSize;
    unsigned long startedAt;
    unsigned long endsAt;
};

void begin();
void startRound();
void registerHit();
void tick();
const State& state();
int secondsRemaining();

}  // namespace tapGame
