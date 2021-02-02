#include "hsv.h"

#include "../common.h"


void PatternHSV::init() {
    FastLED.setBrightness(BRIGHTNESS_MAX);

    UI.addParam("HUE", {0, 255, 2, true, 0});
    UI.addParam("SATURATION", {0, 255, 5, false, 255});
    UI.addParam("VALUE", {0, 255, 5, false, 127});
}

void PatternHSV::update() {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV(UI.getParam("HUE"), UI.getParam("SATURATION"), UI.getParam("VALUE"));
    }
}
