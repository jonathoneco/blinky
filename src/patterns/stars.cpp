#include "stars.h"

#include "../common.h"


void PatternStars::init() {
    FastLED.setBrightness(BRIGHTNESS_MAX / 2);

    UI.addParam("FADE_RATE", {1, 15, 1, false, 5});
    UI.addParam("SPAWN_RATE", {1, 50, 1, false, 5});
}

void PatternStars::update() {
    int fade = UI.getParam("FADE_RATE");
    int spawn = UI.getParam("SPAWN_RATE");

    for (int i = 0; i < NUM_LEDS; i++) {
        if (leds[i]) {
            if (leds[i].r <= fade) {
                leds[i] = CRGB::Black;
                continue;
            }

            leds[i].r -= fade;
            leds[i].g -= fade;
            leds[i].b -= fade;
            continue;
        }

        int r = random(0, 10000);
        if (r < spawn) leds[i] = CRGB(150, 150, 150);
    }

    // Special event:
    if (random(0, SPECIAL_FREQUENCY) == 0) {
        for (int i = 0; i < NUM_LEDS; i++) {
            int v = random(127, 256);
            leds[i] = CRGB(v, v, v);
        }
    }
}
