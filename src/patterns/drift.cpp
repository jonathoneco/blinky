#include "drift.h"


void PatternDrift::init() {
    FastLED.setBrightness(BRIGHTNESS_MAX);

    UI.addParam("SPEED", {1, 50, 1, false, 10});
    UI.addParam("MAX_HUE_CHANGE", {20, 127, 5, false, 50}); 

    new_hue = random(256);
    new_val = random(V_MIN, V_MAX);

    startOver();
}


void PatternDrift::update() {
    bool done = true;

    for (int i = 0; i < NUM_LEDS; i++) {
        if (step <= steps[i]) {
            int h = map(step, 0, steps[i], old_hue, new_hue);
            h = (h % 256 + 256) % 256;

            int v = map(step, 0, steps[i], old_val, new_val);

            leds[FROM_LEFT(i)] = CHSV(h, 255, v);

            done = false;
        }
    }

    step += UI.getParam("SPEED");

    if (done) startOver();
}


void PatternDrift::startOver() {
    old_hue = new_hue;
    old_val = new_val;

    int hue_change = UI.getParam("MAX_HUE_CHANGE");
    new_hue = random(old_hue - hue_change, old_hue + hue_change);
    new_val = random(V_MIN, V_MAX);

    step = 0;

    int center = random(NUM_LEDS);
    for (int i = 0; i < NUM_LEDS; i++) {
        int dist_from_center = abs(center - i);
        steps[i] = dist_from_center * 50 + random(STEPS_MIN, STEPS_MAX);
    }
}
