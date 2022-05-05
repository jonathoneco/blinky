#include "music_viz.h"

#include "../common.h"


void PatternMusicViz::init() {
    FastLED.setBrightness(BRIGHTNESS_MAX);

    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB(0, 0, 0);
    }

    base_hue = random(256);
}


void PatternMusicViz::update() {
    // Read incoming data into bins
    while (SerialUSB1.available() > 0) {
        int byte = SerialUSB1.read();

        if (byte == 255) {
            synced = true;
            pos = 0;
            continue;
        }

        if (synced && pos < N_BINS) {
            bins[pos] = byte;
            pos++;
        }
    }

    // Write to LEDs
    for (int led_idx = 0; led_idx < N_BINS; led_idx++) {
        int val = bins[led_idx] * 2;

        int sat = 255;
        if (val > 255) {
            val = 255;
            sat = 255 - val / 2;
        }

        if (val < 20) val = 0;

        int hue = (base_hue + map(led_idx, 0, 300, 0, HUE_CHANGE)) & 0xFF;

        leds[100 - led_idx] = CHSV(hue, sat, val);
        leds[100 + led_idx] = CHSV(hue, sat, val);
        leds[NUM_LEDS_PER_STRIP + 100 - led_idx] = CHSV(hue, sat, val);
        leds[NUM_LEDS_PER_STRIP + 100 + led_idx] = CHSV(hue, sat, val);
    }

    // Cycle through hues
    cnt++;
    if (cnt == HUE_RATE) {
        base_hue = (base_hue - 1 + 256) % 256;
        cnt = 0;
    }
}
