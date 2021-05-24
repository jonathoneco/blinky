#include "stars.h"

#include "../common.h"


void PatternStars::init() {
    FastLED.setBrightness(BRIGHTNESS_MAX / 2);

    UI.addParam("FADE_RATE", {1, 10, 1, false, 5});
    UI.addParam("SPAWN_RATE", {1, 50, 1, false, 5});
}

void PatternStars::update() {
    int fade = UI.getParam("FADE_RATE");
    int spawn = UI.getParam("SPAWN_RATE");

    bool all_off = true;
    for (int i = 0; i < NUM_LEDS; i++) {
        if (leds[i]) all_off = false;

        if (leds[i] && random(2) == 0) {
            leds[i].fadeToBlackBy(fade);
            continue;
        }

        if (!event_ongoing && random(0, 50000) < spawn) leds[i] = CRGB(150, 150, 150);
    }

    if (event_ongoing && all_off) event_ongoing = false;

    // Special event:
    if (random(0, SPECIAL_FREQUENCY) == 0) {
        for (int i = 0; i < NUM_LEDS; i++) {
            int v = random(100, 256);
            leds[i] = CRGB(v, v, v);
        }

        event_ongoing = true;
    }
}
