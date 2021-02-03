#include "flicker.h"


void PatternFlicker::init() {
    FastLED.setBrightness(BRIGHTNESS_MAX);

    UI.addParam("MAX_WAIT", {100, 1000, 25, false, 500});
    UI.addParam("MAX_FLICKER", {10, 30, 1, false, 20});
    UI.addParam("LIGHT_HUE", {0, 255, 1, false, 30});

    for (int i = 0; i < LIGHTS_PER_SIDE; i++) {
        countdowns_left[i] = random(0, UI.getParam("MAX_WAIT"));
        countdowns_right[i] = random(0, UI.getParam("MAX_WAIT"));
        durations_left[i] = 0;
        durations_right[i] = 0;
    }
}


void PatternFlicker::update() {
    CRGB light_color = CHSV(UI.getParam("LIGHT_HUE"), 209, 255);

    for (int i = 0; i < LIGHTS_PER_SIDE; i++) {
        // Left side
        if (durations_left[i] > 0) { // During a flicker
            for (int j = 0; j < LEN_LIGHT; j++) {
                int idx = FROM_LEFT(i * (LEN_GAP + LEN_LIGHT) + j);
                leds[idx] = CRGB::Black;
            }

            durations_left[i]--;
            if (durations_left[i] <= 0) {
                countdowns_left[i] = random(0, UI.getParam("MAX_WAIT"));
            }
        } else { // Counting down to next flicker
            for (int j = 0; j < LEN_LIGHT; j++) {
                int idx = FROM_LEFT(i * (LEN_GAP + LEN_LIGHT) + j);
                leds[idx] = light_color;
            }

            countdowns_left[i]--;
            if (countdowns_left[i] <= 0) {
                durations_left[i] = random(0, UI.getParam("MAX_FLICKER"));
            }
        }


        // Right side
        if (durations_right[i] > 0) { // During a flicker
            for (int j = 0; j < LEN_LIGHT; j++) {
                int idx = FROM_RIGHT(i * (LEN_GAP + LEN_LIGHT) + j);
                leds[idx] = CRGB::Black;
            }

            durations_right[i]--;
            if (durations_right[i] <= 0) {
                countdowns_right[i] = random(0, UI.getParam("MAX_WAIT"));
            }
        } else { // Counting down to next flicker
            for (int j = 0; j < LEN_LIGHT; j++) {
                int idx = FROM_RIGHT(i * (LEN_GAP + LEN_LIGHT) + j);
                leds[idx] = light_color;
            }

            countdowns_right[i]--;
            if (countdowns_right[i] <= 0) {
                durations_right[i] = random(0, UI.getParam("MAX_FLICKER"));
            }
        }
    }
}
