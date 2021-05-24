#include "white_dot.h"

#include "../common.h"


void PatternWhiteDot::init() {
    FastLED.setBrightness(BRIGHTNESS_MAX);

    pos = 0;

    UI.addParam("POSITION", {0, NUM_LEDS - 1, 1, true, 0});
}

void PatternWhiteDot::update() {
    leds[FROM_LEFT(pos)] = CRGB::Black;

    /* pos++; */
    /* if (pos == NUM_LEDS) pos = 0; */

    pos = UI.getParam("POSITION");

    leds[FROM_LEFT(pos)] = CRGB::White;
}
