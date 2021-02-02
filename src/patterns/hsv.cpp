#include "hsv.h"

#include "../common.h"


void PatternHSV::init() {
    FastLED.setBrightness(20);

    color = CHSV(0, 255, 255);
    
    cnt = 0;
}

void PatternHSV::update() {
    if (cnt == 0) color.hue += SHIFT_RATE;

    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = color;
    }

    cnt++;
    if (cnt == SHIFT_CNT) cnt = 0;
}
