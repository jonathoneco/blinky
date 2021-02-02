#include "lights.h"

#include "common.h"
#include "pattern_list.h"

#define debug


LightsControl::LightsControl() {
    patternInit();

    FastLED.addLeds<NUM_STRIPS, WS2812B, LED_START_PIN, GRB>(leds, NUM_LEDS_PER_STRIP);
    FastLED.setBrightness(BRIGHTNESS_MAX);

    pattern = NULL;
}

void LightsControl::loadPattern(unsigned short idx) {
    // Clear memory from last pattern
    if (pattern) {
#ifdef debug
        Serial.println(F("Deleting old pattern"));
#endif
        delete pattern;
        pattern = NULL;
    }

    // Blank all LEDs
#ifdef debug
    Serial.println(F("Blanking LEDs"));
#endif
    for (unsigned short i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Black;
    }

    // Get next pattern and initialize
    pattern = patternFactories[idx]->getInstance();
    pattern->init();
}


void LightsControl::update() {
    if (pattern) pattern->update();
}

void LightsControl::show() {
    FastLED.show();
}
