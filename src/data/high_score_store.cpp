#include "high_score_store.h"

#include <Preferences.h>

namespace highScoreStore {
namespace {
constexpr const char* NAMESPACE = "tap-quest";
constexpr const char* SCORE_KEY = "high-score";
}

int load() {
    Preferences preferences;
    preferences.begin(NAMESPACE, true);
    const int score = preferences.getInt(SCORE_KEY, 0);
    preferences.end();
    return score;
}

void save(int score) {
    Preferences preferences;
    preferences.begin(NAMESPACE, false);
    preferences.putInt(SCORE_KEY, score);
    preferences.end();
}

void clear() {
    Preferences preferences;
    preferences.begin(NAMESPACE, false);
    preferences.remove(SCORE_KEY);
    preferences.end();
}

}  // namespace highScoreStore
